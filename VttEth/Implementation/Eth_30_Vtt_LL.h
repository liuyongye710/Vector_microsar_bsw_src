/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Vtt_LL.h
 *        \brief  Lower layer header file
 *
 *      \details  Declaration and definition of lower layer part of Ethernet driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  04.00.00  2015-01-16  visfer  ESCAN00080252 FEAT-254: Globale Umbennenung von VIP nach VTT
 *  04.01.00  2015-06-07  visfer  ESCAN00083015 Incorrect handling of multiple pending received frames
 *                                ESCAN00083047 VTT: DET Error on Ethernet Packet Reception during Startup
 *                                ESCAN00083173 Compiler error: incompatible redefinition of function Eth_Receive
 *  04.01.01  2015-10-19  visfer  ESCAN00084541 Module ID not according to AUTOSAR
 *                                ESCAN00086946 uint16 BufferIdx variable overflow on Transmit function
 *  04.02.00  2016-03-30  visfer  ESCAN00089105 osek.h should not be included directly
 *  04.03.00  2016-06-23  visfer  ESCAN00090267 When more than on RxBuffer container is configured the descriptor
 *                                              memory area can get corrupted (QoS usecase)
 *                                ESCAN00090626 Erroneous unlocking of multiple Tx buffers
 *  04.03.01  2016-07-26  visfer  -             -
 *  04.04.00  2016-11-15  visfer  ESCAN00092816 Compiler warning / error "Macro redefinition of ETH_PHYS_ADDR_LEN_BYTE"
 *  05.00.00  2016-11-15  mha/fer ESCAN00094441 Adapt for usage with DrvEth__core
 *  05.00.01  2017-04-01  visfer  ESCAN00094709 Add FrameId to Ethernet Frames
 *  06.00.00  2017-06-01  visfer  ESCAN00094960 Wrong data is transmitted when transmissions is triggered for several
 *                                              frames in a short time interval
 *                                ESCAN00095402 Compiler error: missing infixing at ETH_VAR_NOINIT
 *  06.00.01  2017-07-21  visfer  ESCAN00095997 Compiler warning: Several unreferenced formal parameter warnings
 *  06.01.00  2018-03-07  vismha  STORYC-4575   Update Eth_GeneralTypes.h to version 2.01.00
 *  07.00.00  2018-04-12  visfer  STORYC-4993   STORY-4837 Update to DrvEth__core 3.05.00
 *  08.00.00  2019-02-21  vismha  ESCAN00101760 Compiler error: Undeclared identifier Eth_30_FilterMode
 *                        vismha  STORYC-7729   Update DrvEth_VttEthAsr to DrvEth__coreAsr[3.08.00]
 *  09.00.00  2019-07-25  vismha  ETH-556       Update DrvEth_VttEthAsr to MSR4-R23 DrvEth__coreAsr
 *  10.00.00  2020-03-10  vismha  ESCAN00101760 Compiler error: Undeclared identifier Eth_30_FilterMode
 *                                ESCAN00105781 Compiler error: Dummy statement before local variable declaration
 *                                ESCAN00095147 Compiler error: Missing APIs for Etherstats
 *                                -             Update to Core version 3.10.00
 *  11.00.00  2021-05-07  visdep  ETHCIF-193    Update DrvEth_VttEthAsr to latest Core that implements VLAN ID based 
 *                                              queue handling
 *  11.00.01  2021-06-25  visdep  ESCAN00109453 Compiler warning: conversion from 'uint16' to 'Eth_30_Vtt_RxDescrIterType', 
 *                                              possible loss of data
 *                                ESCAN00109455 Compiler error: unknown memory section in Vtt only usecase
 *  11.00.02  2021-08-25  visdep  ETHCIF-865    Update DrvEth_VttEthAsr to DrvEth__coreAsr@root[9.07.05]
 *  11.01.00  2021-10-03  vistoc  ETHCIF-1      Introduce queue handling on basis of common QoS functionality (VLAN PCP) 
 *                                              in DrvEth_VttEthAsr
 *  11.01.01  2021-11-08  vistoc  				Bugfix for findings in CI
 *  11.01.02  2021-11-10  vistoc  				Bugfix for findings in CI (With new CI config)
 *  11.02.00  2021-11-26  vistoc  ETHCIF-662 	[DrvEth_Vtt] HW Timestamping
 *  11.03.00  2022-05-06     nia  ETHCIF-1636 	DrvEth_VTT - Update to Core 9.08.02
 *								                ESCAN00111770 Changed Datatype to 'Eth_30_Vtt_RxBufferIterType' in Function 
												          'Eth_30_Vtt_LL_InitializeRxDescriptor'
 *********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_VTT_LL_H)
# define ETH_30_VTT_LL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Vtt_Cfg.h"
# if (ETH_30_VTT_ENABLE_HOST_CTRL_INTERFACE == STD_ON) /* COV_ETH_HOST_CTRL_INTERFACE */
#  include "Eth_30_Vtt.h"
#  include "Eth_30_Vtt_LL_HostCtrlIfc.h"
# else
#  include "Eth_30_Vtt_IrqHandler_Int.h"
# endif /* ETH_30_VTT_ENABLE_HOST_CTRL_INTERFACE */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# ifndef ETH_30_VTT_LL_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_VTT_LL_LOCAL_INLINE                                  static /* LOCAL_INLINE */
# endif /* ETH_30_VTT_LL_LOCAL_INLINE */

# define ETH_30_VTT_SW_MAJOR_VERSION                                  (11u)
# define ETH_30_VTT_SW_MINOR_VERSION                                  (02u)
# define ETH_30_VTT_SW_PATCH_VERSION                                  (0u)

# define ETH_30_VTT_LL_DESCRIDX_DELTA_TO_PREVIDX                      (1u)

/*! Descriptor and Buffer Alignment restrictions */
# define ETH_30_VTT_LL_DESC_ALIGN_BYTE                                (1u)
# define ETH_30_VTT_LL_BUFF_ALIGN_BYTE                                (1u)

/* ETH Multicast Defines */
# define ETH_30_VTT_MULTICAST_MASK                                    0x01U
# define ETH_30_VTT_MULTICAST_HASH_31_27_MASK                         0xF8000000U
# define ETH_30_VTT_MULTICAST_HASH_31_27_SHIFT                        27U

/* ETH Filter modes */
# define ETH_30_VTT_FILTER_MULTICAST_MODE                             0U
# define ETH_30_VTT_FILTER_PROMISCUOUS_MODE                           1U

typedef P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataRefType;
/* CRC32 polynomial */
# define ETH_30_VTT_CRC_INITIAL_VALUE32                               (0xFFFFFFFFUL)
# define ETH_30_VTT_CRC_POLYNOMIAL_32                                 (0x04C11DB7UL)
# define ETH_30_VTT_CRC_POLYNOMIAL_32_REFLECT                         (0xEDB88320UL)
# define ETH_30_VTT_CRC_FINAL_XOR_CRC32                               (0xFFFFFFFFUL)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_VTT_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_InitializeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief        Function for initializing an RX descriptor
 *  \details      -
 *  \param[in]    ctrlIdx          Index of Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]    descrRingIdx     Index of descriptor ring to be initialized
 *                [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]    descrIdx         Index of descriptor to be initialized
 *                [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfRxDescr()]
 *  \param[in]    rxBufIdx         Index of buffer to be mapped to the reception descriptor to be initialized
 *                [range: 0 <= rxBufIdx < Eth_30_Vtt_GetSegNumOfRxBufferHandling(rxBufferHandlingIdx)]
 *  \context      TASK
 *  \synchronous  TRUE
 *  \reentrant    FALSE
 *  \pre          -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_InitializeRxDescriptor(
  uint8                                     ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Vtt_RxDescrIterType                descrIdx,
  Eth_30_Vtt_MappedBufferOfRxDescrStateType rxBufIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_InitializeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for initializing a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring to be initialized
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor to be initialized
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous  TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_InitializeTxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_SetDescriptorBaseAddresses()
 *********************************************************************************************************************/
/*! \brief       Function for announcing the descriptor base addresses to hardware
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which descriptors shall be announced
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetDescriptorBaseAddresses(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_InitDescriptorStateVariables()
 *********************************************************************************************************************/
/*! \brief       Function for initializing descriptor state variables, if needed by the lower layer
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be initialized
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous  TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_InitDescriptorStateVariables(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_EnableMiiAccess()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MII access (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller where the MII access shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_EnableMiiAccess(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetCounters()
 *********************************************************************************************************************/
/*! \brief       Function for resetting statistic counters of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which statistic counters should be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetCounters(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_PrepareTxDescriptorForIpChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the IP checksum offload option in a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which checksum offloading shall be enabled
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForIpChecksumOffloading(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_PrepareTxDescriptorForProtocolChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the Protocol checksum offload option in a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which checksum offloading shall be enabled
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_TriggerTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for starting the transmission of a already prepared buffer an descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the transmission shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the transmission shall be triggered
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the transmission shall be triggered
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TriggerTransmission(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_PrepareTxDescriptorForTimestamping()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the timestamping option for a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which timestamping shall be prepared
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which timestamping shall be prepared
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which timestamping shall be prepared
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \param[in]   bufIdx           Index of buffer for which timestamping shall be prepared
 *               [range: 0 <= bufIdx < Eth_30_Vtt_GetSizeOfTxBufferState()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForTimestamping(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx,
  Eth_30_Vtt_TxBufferStateIterType   bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_PrepareTxDescriptorForTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for doing all necessary settings to prepare a TX descriptor for transmission
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be used for transmission
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring to be used for transmission
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor to be transmitted
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \param[in]   bufIdx           Index of buffer to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Vtt_GetSizeOfTxBufferState()]
 *  \param[in]   lenByte          Length of frame to be transmitted
 *  \param[in]   bufPtr           Pointer to buffer to be transmitted
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForTransmission(
          uint8                                                    ctrlIdx,
          Eth_30_Vtt_TxDescrHandlingIterType                       descrRingIdx,
          Eth_30_Vtt_TxDescrIterType                               descrIdx,
          Eth_30_Vtt_TxBufferStateIterType                         bufIdx,
          uint16                                                    lenByte,
  P2CONST(uint8,                              AUTOMATIC, AUTOMATIC) bufPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_RechargeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a TX descriptor, after the transmission of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor which shall be recharged
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_RechargeTxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! \brief       Resets the timestamping request for the given TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timestamping request shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the timestamping request shall be reset
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the timestamping request shall be reset
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetTimestampingInTxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_EnableMac()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_EnableMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_DisableMac()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be disabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_DisableMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_IsMacEnabled()
 *********************************************************************************************************************/
/*! \brief       Function for checking the mode of the MAC (enabled, disabled)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked for mode
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return      TRUE - MAC is enabled
 *  \return      FALSE - MAC is disabled
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsMacEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_WriteMacAddressToRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the configured MAC address to the hardware register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MAC address shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   macAddrPtr       Pointer to physical address to be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_WriteMacAddressToRegister(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_PreResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for hardware specific operations which need to be executed before MAC reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be initialized
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PreResetMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for resetting the MAC (if needed by hardware)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_IsResetMacFinished()
 *********************************************************************************************************************/
/*! \brief       Function for checking for the completion of the reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be checked for completion of reset
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return      TRUE - MAC reset is finished
 *  \return      FALSE - MAC reset is not finished yet
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsResetMacFinished(
  uint8 ctrlIdx);

# if (ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_EnablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_EnablePromiscuousMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_DisablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be disabled
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_DisablePromiscuousMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_CloseAllMulticastFilters()
 *********************************************************************************************************************/
/*! \brief       Function for closing all multicast filters
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which all multicast filters shall be closed
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_CloseAllMulticastFilters(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_SetMulticastFilteringMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling a certain multicast filter mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast filter mode shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetMulticastFilteringMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_SetUpperMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_SetLowerMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetUpperMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetLowerMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the lower multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_CalculateMulticastFilterRegisterHash()
 *********************************************************************************************************************/
/*! \brief       Function for calculating a multicast filter hash value
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   macAddrPtr       Pointer to the physical address for which a hash shall be calculated
 *  \param[out]  hashPtr          Pointer to the variable which contains the calculated hash
 *  \param[out]  isUpperRegPtr    Pointer to the variable which contains the decision which filter register shall be
 *                                used
 *  \param[out]  bucketMaskPtr    Pointer to the variable which contains the mask for the filter register
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_CalculateMulticastFilterRegisterHash(
          uint8                          ctrlIdx,
  P2CONST(uint8,   AUTOMATIC, AUTOMATIC) macAddrPtr,
    P2VAR(uint8,   AUTOMATIC, AUTOMATIC) hashPtr,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) isUpperRegPtr,
    P2VAR(uint32,  AUTOMATIC, AUTOMATIC) bucketMaskPtr);

/***********************************************************************************************************************
 *  Eth_30_Vtt_VCalculateCRC32
 **********************************************************************************************************************/
/*!
 * \brief      Calculates 32-bit CRC value of passed data
 * \details    Calculates 32-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on the IEEE-802.3 CRC32 Standard.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue32 - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue32
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue32 has to be return value of 
 *                                      previous call
 * \return     Calculated CRC32 value     
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(uint32, CRC_CODE) Eth_30_Vtt_VCalculateCRC32(
  Crc_DataRefType CrcDataPtr,
  uint32          CrcLength,
  uint32          CrcStartValue32,
  boolean         CrcIsFirstCall);
# endif /* ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_WriteMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a write operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller  for which the MII write operation shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx          Index of transceiver for which the MII write operation shall be triggered
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx           Index of register for which the MII write operation shall be triggered
 *               [range: 0 <= regIdx < 32]
 *  \param[in]   regVal           Register value that shall be written
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_VTT_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_WriteMiiTrigger(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ReadMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a read operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx          Index of transceiver for which the MII read operation shall be triggered
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx           Index of register for which the MII read operation shall be triggered
 *               [range: 0 <= regIdx < 32]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_VTT_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ReadMiiTrigger(
  uint8 ctrlIdx,
  uint8 trcvIdx,
  uint8 regIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetReadMiiResult()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the result of a read operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation result shall be retrieved
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[out]  regValPtr        Pointer to buffer where register value shall be stored
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_VTT_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetReadMiiResult(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_IsMiiOperationPending()
 *********************************************************************************************************************/
/*! \brief       Function for checking the completion of an operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII operation completion shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_VTT_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsMiiOperationPending(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_SetTxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the TX events for the respective descriptor rings
 *  \details     Function sets TX events by calling Eth_30_Vtt_SetTxEvent() for each TX descriptor ring having a
 *               pending TX event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending TX events shall be queried for
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetTxEvents(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_IsRxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a RX descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= ringIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfEthRxDescr()]
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsRxDescriptorOwnedByDriver(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_IsTxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a TX descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfTxDescr()]
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsTxDescriptorOwnedByDriver(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_IsErrorInRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a error flag was set in a RX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfRxDescr()]
 *  \return      TRUE - error flag is set in descriptor
 *  \return      FALSE - no error flags is set in descriptor
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsErrorInRxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx);


/***********************************************************************************************************************
 *  Eth_30_Vtt_VIsBroadcast
 **********************************************************************************************************************/
/*! \brief       Function to check if the passed physical address is of type broadcast or not
 *  \details     -
 *  \param[in]   PhysAddrPtr  Pointer to physical address
 *  \return      TRUE - physical address is broadcast address
 *  \return      FALSE - physical address is not a broadcast address
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE_ISR) Eth_30_Vtt_VIsBroadcast(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

# if (ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Vtt_VIsOpenMulticast
 **********************************************************************************************************************/
/*! \brief       Function to check if the passed physical address is of type multicast or not
 *  \details     -
 *  \param[in]   PhysAddrPtr  Pointer to physical address
 *  \return      TRUE - physical address is multicast address
 *  \return      FALSE - physical address is not a multicast address
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE_ISR) Eth_30_Vtt_VIsOpenMulticast(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);
# endif /* ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  Eth_30_Vtt_VIsUnicast
 **********************************************************************************************************************/
/*! \brief       Function to check if the passed physical address is of type unicast or not
 *  \details     -
 *  \param[in]   PhysAddrPtr  Pointer to physical address
 *  \return      TRUE - physical address is unicast address
 *  \return      FALSE - physical address is not a unicast address
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE_ISR) Eth_30_Vtt_VIsUnicast(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_SetRxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the RX events for the respective descriptor rings
 *  \details     Functions sets RX events by calling Eth_30_Vtt_SetRxEvent() for each RX descriptor ring having a
 *               pending RX event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending RX events shall be queried for
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetRxEvents(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_RearmMacForReception
 **********************************************************************************************************************/
/*! \brief       Rearms the MAC for being able to receive frames on the respective descriptor ring again
 *  \details     Function sets registers that rearm the RX DMA to receive frames on the respective RX descriptor
 *               ring again.
 *  \param[in]   ctrlIdx          Index of controller that shall be rearmed for reception
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring that shall be rearmed for reception
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Eth controllers
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_RearmMacForReception(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_RechargeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a RX descriptor, after the reception of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor which shall be recharged
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfRxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_RechargeRxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_AdaptRxDescriptorRingAfterReception
 *********************************************************************************************************************/
/*! \brief       Function for HW specific RX descriptor operations which are necessary after a frame has been received
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be adapted
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be adapted
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx        Index of descriptor which shall be adapted
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfRxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_AdaptRxDescriptorRingAfterReception(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetFrameLengthFromRxDescriptor
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the frame length of a received frame from a RX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the frame length shall be retrieved
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the frame length shall be retrieved
 *               [range: 0 <= descrRingIdx < Eth_30_Vtt_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the frame length shall be retrieved
 *               [range: 0 <= descrIdx < Eth_30_Vtt_GetSizeOfRxDescr()]
 *  \return      Length extracted from a RX descriptor
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(uint16, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetFrameLengthFromRxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! \brief       Returns the maximum counter offset within the statistic counter register block
 *  \details     Function returns the maximum counter offset of the Ethernet controllers statistic counters register
 *               block.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return      Maximum offset of the statistic register counter block of the platform.
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(uint16, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetMaxCounterOffset(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetCounterValue
 *********************************************************************************************************************/
/*! \brief       Retrieves the value of the given statistics counter
 *  \details     Function checks if a valid statistics counter is addressed within the counter register block and if
 *               so returns its value.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[in]   counterOffset    Offset into the statistic counter register block
 *  \param[out]  counterValPtr    Value of the statistics counter
 *  \return      E_NOT_OK - Index results in addressing a non existing counter
 *  \return      E_OK - Counter value successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers and counters
 *  \pre         counterIdx must have been checked for being inbound of the statistics counter register block
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetCounterValue(
        uint8                         ctrlIdx,
        uint16                        counterOffset,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) counterValPtr);

# if (ETH_30_VTT_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetRxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of RX statistics counters
 *  \details     Function reads a set of reception statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[out]  rxStatsPtr Pointer to the address where the RX statistics counter values are stored
 *  \return      E_NOT_OK - RX statistics counters not retrieved
 *  \return      E_OK - RX statistics counters successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         ETH_30_VTT_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetRxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetTxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of TX statistics counters
 *  \details     Function reads a set of transmission statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[out]  txStatsPtr Pointer to the address where the TX statistics counter values are stored
 *  \return      E_NOT_OK - TX statistics counters not retrieved
 *  \return      E_OK - TX statistics counters successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         ETH_30_VTT_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr);
# endif /* ETH_30_VTT_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_VTT_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetDropInsuffRxBuffHwCounter()
 *********************************************************************************************************************/
/*! \brief       This function returns the number of reception drop events due to insufficient buffers.
 *  \details     Read the Hw counter of reception drop events due to insufficient buffers if exists and return the 
 *               counter value and if the counter is reset on read or not.
 *  \param[in]   ctrlIdx                    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \param[out]  isHwCtrResetOnReadPtr  Pointer to variable to store if the Hw counter is reset on read
 *  \param[out]  readCtrValuePtr        Pointer to variable where the read count of Rx frame drop is stored
 *  \return      E_OK - Hardware counter values are retrieved successfully
 *  \return      E_NOT_OK - Hardware counter is not available or unable to get the counter value
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetDropInsuffRxBuffHwCounter(
        uint8                                                                       ctrlIdx,
  P2VAR(Eth_30_Vtt_DropInsuffRxBuffOfEthMeasDataCounterType, AUTOMATIC, AUTOMATIC)  readCtrValuePtr,
  P2VAR(boolean,                                              AUTOMATIC, AUTOMATIC) isHwCtrResetOnReadPtr);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetDropInsuffRxBuffHwCounter()
 *********************************************************************************************************************/
/*! \brief       This function resets the counter for reception drop events due to insufficient buffers
 *  \details     Reset the Hw counter used to store the count of number of reception drop events due to insufficient rx
 *               buffers. If the reset is not possible, it will be indicated to the caller.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return      E_OK - Hardware counter reset successfully
 *  \return      E_NOT_OK - Hardware counter is not available or unable to reset the counter
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetDropInsuffRxBuffHwCounter(
  uint8 ctrlIdx);
# endif /* ETH_30_VTT_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_PerformAdditionalHwConfig()
 *********************************************************************************************************************/
/*! \brief       This function performs the controller specific additional configurations.
 *  \details     This function can be used to perform additional hardware specific configurations such as Indirect 
 *               register access, VLAN-ID based frame queuing configurations etc.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Vtt_GetSizeOfEthCtrl()]
 *  \return      E_OK - Hardware specific configuration successful
 *  \return      E_NOT_OK - Hardware specific configuration not successful
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PerformAdditionalHwConfig(
  uint8 ctrlIdx);

/**********************************************************************************************************************
*  Eth_30_Vtt_LL_IsRxPending()
*********************************************************************************************************************/
/*! \brief        Function to determine if a Rx event is pending in the receive interrupt status (unmasked) register
*                for the current descriptor ring
*  \details      -
*  \param[in]    ctrlIdx          Index of controller
*                [range: 0 <= ctrlIdx < Eth_30_TexasMac_GetSizeOfEthCtrl()]
*  \param[in]    descrRingIdx     Index of descriptor ring (list) to be checked for a pending event
*                [range: 0 <= descrRingIdx < Eth_30_TexasMac_GetSizeOfRxDescrHandling()]
*  \return       TRUE -  pending Rx event
*  \return       FALSE - no pending Rx event
*  \context      TASK
*  \synchronous  TRUE
*  \reentrant    FALSE
*  \pre          -
*/
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsRxPending(
	uint8                                   ctrlIdx,
	Eth_30_Vtt_RxDescrHandlingIterType      descrRingIdx);

/**********************************************************************************************************************
*  Eth_30_Vtt_LL_IsTxPending()
*********************************************************************************************************************/
/*! \brief        Function to determine if a Rx event is pending in the transmit interrupt status (unmasked) register
*                for the current descriptor ring
*  \details      -
*  \param[in]    ctrlIdx          Index of controller
*                [range: 0 <= ctrlIdx < Eth_30_TexasMac_GetSizeOfEthCtrl()]
*  \param[in]    descrRingIdx     Index of descriptor ring (list) to be checked for a pending event
*                [range: 0 <= descrRingIdx < Eth_30_TexasMac_GetSizeOfTxDescrHandling()]
*  \return       TRUE -  pending Rx event
*  \return       FALSE - no pending Rx event
*  \context      TASK
*  \synchronous  TRUE
*  \reentrant    FALSE
*  \pre          -
*/
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsTxPending(
	uint8                                   ctrlIdx,
	Eth_30_Vtt_TxDescrHandlingIterType      descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_MainFunction()
 *********************************************************************************************************************/
/*! \brief       MainFunction for hardware specific cyclic operations
 *  \details     -
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_MainFunction( void );

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# ifndef ETH_30_VTT_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_InitializeRxDescriptor
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
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_InitializeRxDescriptor(
  uint8                                     ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Vtt_RxDescrIterType                descrIdx,
  Eth_30_Vtt_MappedBufferOfRxDescrStateType rxBufIdx)
{

  P2VAR(Eth_30_Vtt_RxDescriptorType, AUTOMATIC, ETH_30_VTT_VAR_NOINIT) rxDescr = Eth_30_Vtt_GetAddrRxDescr(descrIdx);
  Eth_30_Vtt_RxDescrIterType localDescrIdx = descrIdx - Eth_30_Vtt_GetRxDescrStartIdxOfRxDescrHandling(descrRingIdx);
  Eth_30_Vtt_RxBufferIterType rxBufOffset = ((Eth_30_Vtt_RxBufferIterType)Eth_30_Vtt_GetRxBufferStartIdxOfRxBufferHandling(descrRingIdx) +
	  (rxBufIdx * (Eth_30_Vtt_RxBufferIterType)Eth_30_Vtt_GetAlignedSegSizeOfRxBufferHandling(descrRingIdx)));

  /* #10 Write buffer address to descriptor */
  rxDescr->DataPtr = (Eth_DataType *)Eth_30_Vtt_GetAddrRxBuffer(rxBufOffset);

  /* #20 Set descriptor as owned by VttCtrl */
  rxDescr->OwnedByDriver = FALSE;

  /* #30 Set maximum allowed packet size */
  rxDescr->AllowedPacketSize = Eth_30_Vtt_GetMaxFrameSizeOfRxBufferHandling(descrRingIdx);

  /* #40 Check if descriptor is last one */
  if (localDescrIdx < (Eth_30_Vtt_GetDescrNumOfRxBufferHandling(descrRingIdx) - 1u))
  {
    /* #410 Set descriptor is not last one */
    rxDescr->LastElement = FALSE;
  }
  else
  {
    /* #420 Set descriptor is last one */
    rxDescr->LastElement = TRUE;
  }

  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_InitializeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_InitializeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_InitializeTxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{

  P2VAR(Eth_30_Vtt_TxDescriptorType, AUTOMATIC, ETH_30_VTT_VAR_NOINIT) txDescr =  Eth_30_Vtt_GetAddrTxDescr(descrIdx);
  Eth_30_Vtt_TxDescrIterType localDescrIdx = descrIdx - Eth_30_Vtt_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx);

  /* #10 Set descriptor as owned by VttCtrl */
  txDescr->OwnedByDriver = FALSE;

  /* #20 Check if descriptor is last one */
  if (localDescrIdx < (Eth_30_Vtt_GetDescrNumOfTxBufferHandling(ctrlIdx) - 1u))
  {
    /* #210 Set descriptor is not last one */
    txDescr->LastElement = FALSE;
  }
  else
  {
    /* #220 Set descriptor is last one */
    txDescr->LastElement = TRUE;
  }

  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_InitializeTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_SetDescriptorBaseAddresses
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
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetDescriptorBaseAddresses(
  uint8 ctrlIdx)
{
  Eth_30_Vtt_TxDescrHandlingIterType txDescrRingIdx;
  Eth_30_Vtt_TxDescrHandlingIterType txDescrRingStartIdx = Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
  Eth_30_Vtt_TxDescrHandlingIterType txDescrRingEndIdx = Eth_30_Vtt_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_RxDescrHandlingIterType rxDescrRingIdx;
  Eth_30_Vtt_RxDescrHandlingIterType rxDescrRingStartIdx = Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
  Eth_30_Vtt_RxDescrHandlingIterType rxDescrRingEndIdx = Eth_30_Vtt_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);

  /* #10 Loop over all Tx descriptor rings */
  for (txDescrRingIdx = txDescrRingStartIdx; txDescrRingIdx < txDescrRingEndIdx; txDescrRingIdx++)
  {
	  /* #110 Retrive Tx descriptor base addresses */
	  P2VAR(Eth_30_Vtt_TxDescriptorType, AUTOMATIC, ETH_30_VTT_VAR_NOINIT) txDescr =
		  Eth_30_Vtt_GetAddrTxDescr(Eth_30_Vtt_GetTxDescrStartIdxOfTxDescrHandling(txDescrRingIdx));
	  /* #120 Call the virtual ethernet controller api to set Tx descriptor base addresses */
	  VttEth_SetTxDescriptorBaseAddress((Eth_30_Vtt_TxDescriptorType*)&txDescr->nanoseconds, txDescrRingIdx);
  }

  /* #20 Loop over all Rx descriptor rings */
  for (rxDescrRingIdx = rxDescrRingStartIdx; rxDescrRingIdx < rxDescrRingEndIdx; rxDescrRingIdx++)
  {
	/* #210 Retrive Rx descriptor base addresses */
    P2VAR(Eth_30_Vtt_RxDescriptorType, AUTOMATIC, ETH_30_VTT_VAR_NOINIT) rxDescr =
	    Eth_30_Vtt_GetAddrRxDescr(Eth_30_Vtt_GetRxDescrStartIdxOfRxDescrHandling(rxDescrRingIdx));
	/* #220 Call the virtual ethernet controller api to set Rx descriptor base addresses */
	VttEth_SetRxDescriptorBaseAddress((Eth_30_Vtt_RxDescriptorType*)&rxDescr->DataPtr, rxDescrRingIdx);
  }

# if(ETH_30_VTT_ENABLE_QOS == STD_ON)
  /* #30 Set QoS */
  Eth_30_Vtt_QosHandlingIdxOfEthCtrlType qosHandlingIdx = Eth_30_Vtt_GetQosHandlingIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_VlanPrioTxDescrRingMapIterType vlanPrioTxDescrRingMapStartIdx = Eth_30_Vtt_GetVlanPrioTxDescrRingMapStartIdxOfQosHandling(qosHandlingIdx);
  Eth_30_Vtt_VlanPrioTxDescrRingMapIterType vlanPrioTxDescrRingMapEndIdx = Eth_30_Vtt_GetVlanPrioTxDescrRingMapEndIdxOfQosHandling(qosHandlingIdx);
  Eth_30_Vtt_VlanPrioTxDescrRingMapIterType vlanPrioTxDescrRingMapIdx;

  Eth_30_Vtt_VlanPrioTxDescrRingMapIterType vlanPrioRxDescrRingMapStartIdx = Eth_30_Vtt_GetVlanPrioRxDescrRingMapStartIdxOfEthCtrlVtt(ctrlIdx);
  Eth_30_Vtt_VlanPrioTxDescrRingMapIterType vlanPrioRxDescrRingMapEndIdx = Eth_30_Vtt_GetVlanPrioRxDescrRingMapEndIdxOfEthCtrlVtt(ctrlIdx);
  Eth_30_Vtt_VlanPrioRxDescrRingMapIterType vlanPrioRxDescrRingMapIdx;
  /* #310 Set QoS enabled in VttCtrl */
  VttEth_SetQoSEnabled();
  /* #320 Set the untagged queue in VttCtrl */
  VttEth_SetUntaggedQueue(ctrlIdx, Eth_30_Vtt_GetUntaggedRxQueue(ctrlIdx), Eth_30_Vtt_GetTxDescrHandlingIdxOfQosHandling(qosHandlingIdx));
  /* #330 Set the VLAN prio queue Mapping in VttCtrl */
  for (vlanPrioTxDescrRingMapIdx = vlanPrioTxDescrRingMapStartIdx; vlanPrioTxDescrRingMapIdx < vlanPrioTxDescrRingMapEndIdx; vlanPrioTxDescrRingMapIdx++)
  {
	  VttEth_SetVlanPrio2TxQueueMapping(ctrlIdx, vlanPrioTxDescrRingMapIdx - vlanPrioTxDescrRingMapStartIdx, Eth_30_Vtt_GetVlanPrioTxDescrRingMap(vlanPrioTxDescrRingMapIdx));
  }

  for (vlanPrioRxDescrRingMapIdx = vlanPrioRxDescrRingMapStartIdx; vlanPrioRxDescrRingMapIdx < vlanPrioRxDescrRingMapEndIdx; vlanPrioRxDescrRingMapIdx++)
  {
	  VttEth_SetVlanPrio2RxQueueMapping(ctrlIdx, vlanPrioRxDescrRingMapIdx - vlanPrioRxDescrRingMapStartIdx, Eth_30_Vtt_GetVlanPrioRxDescrRingMap(vlanPrioRxDescrRingMapIdx));
  }
# endif /* ETH_30_VTT_ENABLE_QOS */

# if(ETH_30_VTT_ENABLE_VLANID_BASED_FRAME_QUEUING == STD_ON)
  /* #40 Set VLAN based queuing */
  Eth_30_Vtt_VlanIdBasedQueuingHandlingIdxOfEthCtrlType vlanIdBasedQueuingHandlingIdx = Eth_30_Vtt_GetVlanIdBasedQueuingHandlingIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType vlanIdTxDescrRingMapStartIdx = Eth_30_Vtt_GetVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(vlanIdBasedQueuingHandlingIdx);
  Eth_30_Vtt_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType vlanIdTxDescrRingMapEndIdx = Eth_30_Vtt_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(vlanIdBasedQueuingHandlingIdx);
  Eth_30_Vtt_VlanIdTxDescrRingMapIterType vlanIdTxDescrRingMapIdx;

  Eth_30_Vtt_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType vlanIdRxDescrRingMapStartIdx = Eth_30_Vtt_GetVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(vlanIdBasedQueuingHandlingIdx);
  Eth_30_Vtt_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType vlanIdRxDescrRingMapEndIdx = Eth_30_Vtt_GetVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(vlanIdBasedQueuingHandlingIdx);
  Eth_30_Vtt_VlanIdRxDescrRingMapIterType vlanIdRxDescrRingMapIdx;

  /* #410 Set VLAN based queuing enabled in VttCtrl */
  VttEth_SetVLANIDBasedQueuingEnabled();
  /* #420 Set the untagged queue in VttCtrl */
  VttEth_SetUntaggedQueue(ctrlIdx, Eth_30_Vtt_UntaggedRxQueue[ctrlIdx], Eth_30_Vtt_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(vlanIdBasedQueuingHandlingIdx));
  /* #430 Set the VLAN ID queue Mapping in VttCtrl */
  for (vlanIdTxDescrRingMapIdx = vlanIdTxDescrRingMapStartIdx; vlanIdTxDescrRingMapIdx < vlanIdTxDescrRingMapEndIdx; vlanIdTxDescrRingMapIdx++)
  {
	  VttEth_SetVlanID2TxQueueMapping(ctrlIdx, Eth_30_Vtt_GetVlanIdOfVlanIdTxDescrRingMap(vlanIdTxDescrRingMapIdx), Eth_30_Vtt_GetQueueIndexOfVlanIdTxDescrRingMap(vlanIdTxDescrRingMapIdx));
  }

  for (vlanIdRxDescrRingMapIdx = vlanIdRxDescrRingMapStartIdx; vlanIdRxDescrRingMapIdx < vlanIdRxDescrRingMapEndIdx; vlanIdRxDescrRingMapIdx++)
  {
	  VttEth_SetVlanID2RxQueueMapping(ctrlIdx, Eth_30_Vtt_GetVlanIdOfVlanIdRxDescrRingMap(vlanIdRxDescrRingMapIdx), Eth_30_Vtt_GetQueueIndexOfVlanIdRxDescrRingMap(vlanIdRxDescrRingMapIdx));
  }
# endif /* ETH_30_VTT_ENABLE_VLANID_BASED_FRAME_QUEUING */

  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

} /* Eth_30_Vtt_LL_SetDescriptorBaseAddresses() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_InitDescriptorStateVariables
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_InitDescriptorStateVariables(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_InitDescriptorStateVariables() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_EnableMiiAccess
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_EnableMiiAccess(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_EnableMiiAccess() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_ResetCounters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetCounters(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_ResetCounters() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_PrepareTxDescriptorForTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForTransmission(
          uint8                                                     ctrlIdx,
          Eth_30_Vtt_TxDescrHandlingIterType                        descrRingIdx,
          Eth_30_Vtt_TxDescrIterType                                descrIdx,
          Eth_30_Vtt_TxBufferStateIterType                          bufIdx,
          uint16                                                    lenByte,
  P2CONST(uint8,                              AUTOMATIC, AUTOMATIC) bufPtr)
{
  /* #10 Call the virtual ethernet controller api to output an ethernet packet */
  VttEth_OutputEthernetPacket(ctrlIdx, lenByte, bufPtr);

  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_PrepareTxDescriptorForTransmission() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_RechargeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_RechargeTxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_RechargeTxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetTimestampingInTxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_ResetTimestampingInTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_PrepareTxDescriptorForIpChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForIpChecksumOffloading(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_PrepareTxDescriptorForIpChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_PrepareTxDescriptorForProtocolChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_PrepareTxDescriptorForProtocolChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_TriggerTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_TriggerTransmission(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{
  Eth_30_Vtt_TxDescrHandlingIterType localDescrRingIdx;
  Eth_30_Vtt_TxDescrHandlingIterType descrRingStartIdx = Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_TxDescrIterType localDescrIdx = descrIdx - Eth_30_Vtt_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx);
  localDescrRingIdx = (uint8)(descrRingIdx - descrRingStartIdx);

  /* #10 Call the virtual ethernet controller api to release the ownership of the descriotor */
  VttEth_SetTxDescriptorOwnedByDriverMultiQueues(ctrlIdx, (uint16)localDescrIdx, FALSE, localDescrRingIdx);

  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_TriggerTransmission() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_PrepareTxDescriptorForTimestamping
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PrepareTxDescriptorForTimestamping(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx,
  Eth_30_Vtt_TxBufferStateIterType   bufIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_PrepareTxDescriptorForTimestamping() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_EnableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_EnableMac(
  uint8 ctrlIdx)
{
  /* #10 Call the virtual ethernet controller api to set the controller mode to ACTIVE */
  VttEth_SetControllerMode(ctrlIdx, ETH_MODE_ACTIVE);
} /* Eth_30_Vtt_LL_EnableMac() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_DisableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_DisableMac(
  uint8 ctrlIdx)
{
  /* #10 Call the virtual ethernet controller api to set the controller mode to DOWN */
  VttEth_SetControllerMode(ctrlIdx, ETH_MODE_DOWN);
} /* Eth_30_Vtt_LL_DisableMac() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_IsMacEnabled
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE)  Eth_30_Vtt_LL_IsMacEnabled(
  uint8 ctrlIdx)
{
  /* #10 Call the virtual ethernet controller api to retrive the controller mode */
  Eth_ModeType ctrlMode;
  VttEth_GetControllerMode(ctrlIdx, &ctrlMode);

  return (ctrlMode == ETH_MODE_ACTIVE);
} /* Eth_30_Vtt_LL_IsMacEnabled() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_WriteMacAddressToRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_WriteMacAddressToRegister(
  uint8                                ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(macAddrPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_WriteMacAddressToRegister() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_PreResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PreResetMac(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_PreResetMac() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_ResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetMac(
  uint8 ctrlIdx)
{
  /* #10 Call the virtual ethernet controller api to set the controller mode to DOWN */
  VttEth_SetControllerMode(ctrlIdx, ETH_MODE_DOWN);
} /* Eth_30_Vtt_LL_ResetMac() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_IsResetMacFinished
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsResetMacFinished(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return TRUE;
} /* Eth_30_Vtt_LL_IsResetMacFinished() */

#  if (ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Vtt_LL_EnablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_EnablePromiscuousMode(
  uint8 ctrlIdx)
{
  /* #10 Set filter mode to promiscuous mode */
  Eth_30_Vtt_SetFilterMode(ctrlIdx, ETH_30_VTT_FILTER_PROMISCUOUS_MODE);
} /* Eth_30_Vtt_LL_PromiscuousModeEnable() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_DisablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_DisablePromiscuousMode(
  uint8 ctrlIdx)
{
  /* #10 Set filter mode to multicast mode */
  Eth_30_Vtt_SetFilterMode(ctrlIdx, ETH_30_VTT_FILTER_MULTICAST_MODE);
} /* Eth_30_Vtt_LL_DisablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_CloseAllMulticastFilters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_CloseAllMulticastFilters(
  uint8 ctrlIdx)
{
  /* #10 Set filter mode to multicast mode */
  Eth_30_Vtt_SetFilterMode(ctrlIdx, ETH_30_VTT_FILTER_MULTICAST_MODE);
} /* Eth_30_Vtt_LL_CloseAllMulticastFilters() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_SetMulticastFilteringMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetMulticastFilteringMode(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_SetMulticastFilteringMode() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_SetUpperMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_SetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_SetLowerMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_SetLowerMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_ResetUpperMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_ResetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_ResetLowerMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_ResetLowerMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_CalculateMulticastFilterRegisterHash
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_CalculateMulticastFilterRegisterHash(
          uint8                          ctrlIdx,
  P2CONST(uint8,   AUTOMATIC, AUTOMATIC) macAddrPtr,
    P2VAR(uint8,   AUTOMATIC, AUTOMATIC) hashPtr,
    P2VAR(boolean, AUTOMATIC, AUTOMATIC) isUpperRegPtr,
    P2VAR(uint32,  AUTOMATIC, AUTOMATIC) bucketMaskPtr)
{
  /* #10 Initialize the output variables for the core */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(macAddrPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  uint32 Crc32 = Eth_30_Vtt_VCalculateCRC32(macAddrPtr, ETH_PHYS_ADDR_LEN_BYTE, 0xFFFFFFFF, TRUE);
  *hashPtr = (uint8)((Crc32 & ETH_30_VTT_MULTICAST_HASH_31_27_MASK) >> ETH_30_VTT_MULTICAST_HASH_31_27_SHIFT);
  *isUpperRegPtr = FALSE; /* No register is set in VTT... */
  *bucketMaskPtr = 0;

} /* Eth_30_Vtt_LL_CalculateMulticastFilterRegisterHash() */

/***********************************************************************************************************************
 *  Eth_30_Vtt_VCalculateCRC32
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
 **********************************************************************************************************************/
ETH_30_VTT_LL_LOCAL_INLINE FUNC(uint32, CRC_CODE) Eth_30_Vtt_VCalculateCRC32(
  Crc_DataRefType CrcDataPtr,
  uint32          CrcLength,
  uint32          CrcStartValue32,
  boolean         CrcIsFirstCall)
{
  uint32 CrcValue_u32;
  uint8 Crc_LoopCounter;
  uint16 DataPtrAddr_u16 = 0;

  /* #10 Set initial value depending on whether it's the first call or a subsequent call */
  if( CrcIsFirstCall == TRUE )
  {
      CrcValue_u32 = ETH_30_VTT_CRC_INITIAL_VALUE32;
  }
  else
  {
      CrcValue_u32 = (ETH_30_VTT_CRC_FINAL_XOR_CRC32 ^ CrcStartValue32);
  }
  /* #20 Perform CRC calculation for each byte in Crc_DataPtr */
  while ( CrcLength > 0 )
  {
    /* #210 CRC32 routine considers reflection of input and output data. Instead of reflecting input and output data, a
     *      reflected polynomial is used */
    /* #220 XOR next byte of Crc_DataPtr with current CRC value. This is equivalent to calculating CRC value of
     *      concatenated bytes */
    CrcValue_u32 ^= 0xFFuL & (uint32) CrcDataPtr[DataPtrAddr_u16];

    /* #230 Perform modulo-2 division, a bit at a time */
    for ( Crc_LoopCounter = 0; Crc_LoopCounter < 8; Crc_LoopCounter++ )
    {
      /* #2310 If LSB is 1, CRC value is XORed with polynomial */
      /* #2320 Direction of modulo-2 division is reverse compared to Crc8 and Crc16, due to the reflection of the
       *       polynomial */
      if ( (CrcValue_u32 & 1) > 0 )
      {
        CrcValue_u32 = ( CrcValue_u32 >> 1 ) ^ ETH_30_VTT_CRC_POLYNOMIAL_32_REFLECT;
      }
      else
      {
        CrcValue_u32 = ( CrcValue_u32 >> 1 );
      }
    }
    CrcLength--;
    DataPtrAddr_u16++;
  }
  return ETH_30_VTT_CRC_FINAL_XOR_CRC32 ^ CrcValue_u32;
} /* Eth_30_Vtt_VCalculateCRC32() */
#  endif /* ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_WriteMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_WriteMiiTrigger(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(trcvIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(regIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(regVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_WriteMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_ReadMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ReadMiiTrigger(
  uint8 ctrlIdx,
  uint8 trcvIdx,
  uint8 regIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(trcvIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(regIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_ReadMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_GetReadMiiResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetReadMiiResult(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(regValPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_GetReadMiiResult() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_IsMiiOperationPending
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsMiiOperationPending(
  uint8 ctrlIdx)
{
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return FALSE;
} /* Eth_30_Vtt_LL_IsMiiOperationPending() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_SetTxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetTxEvents(
  uint8 ctrlIdx)
{
  sint8_least descrRingIdx;
  Eth_30_Vtt_TxDescrHandlingIterType localDescrRingIdx;
  Eth_30_Vtt_TxDescrHandlingIterType descrRingStartIdx = Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
  Eth_30_Vtt_TxDescrHandlingIterType descrRingEndIdx = Eth_30_Vtt_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) - 1;

  /* #10 Loop over all configured descriptor rings */
  for (descrRingIdx = (sint8_least)descrRingEndIdx; descrRingIdx >= (sint8_least)descrRingStartIdx; descrRingIdx--)
  {
    localDescrRingIdx = (Eth_30_Vtt_TxDescrHandlingIterType)(descrRingIdx - descrRingStartIdx);

    /* #110 Check if there was a Tx event in the current descriptor ring */
    if (Eth_30_Vtt_LL_IsTxPending(ctrlIdx, localDescrRingIdx) == TRUE)
    {
      /* #1110 Set Tx event */
      Eth_30_Vtt_SetTxEvent(ctrlIdx, (Eth_30_Vtt_TxDescrHandlingIterType)localDescrRingIdx);
      VttEth_ResetTxInterruptRaw(ctrlIdx, (uint8)localDescrRingIdx);
    }
  }
} /* Eth_30_Vtt_LL_SetTxEvents() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_IsRxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsRxDescriptorOwnedByDriver(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx)
{
  Eth_30_Vtt_RxDescrHandlingIterType localDescrRingIdx;
  Eth_30_Vtt_RxDescrHandlingIterType descrRingStartIdx = Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_RxDescrIterType localDescrIdx = descrIdx - Eth_30_Vtt_GetRxDescrStartIdxOfRxDescrHandling(descrRingIdx);
  localDescrRingIdx = (uint8)(descrRingIdx - descrRingStartIdx);

  /* #10 Call the virtual ethernet controller api to check if the RX descriptor with index descrIdx is owned by driver */
  return  VttEth_GetRxDescriptorOwnedByDriverMultiQueues(ctrlIdx, (uint16)localDescrIdx, localDescrRingIdx);
} /* Eth_30_Vtt_LL_IsRxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_IsTxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsTxDescriptorOwnedByDriver(
  uint8                              ctrlIdx,
  Eth_30_Vtt_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_TxDescrIterType         descrIdx)
{
  Eth_30_Vtt_TxDescrHandlingIterType localDescrRingIdx;
  Eth_30_Vtt_TxDescrHandlingIterType descrRingStartIdx = Eth_30_Vtt_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_TxDescrIterType localDescrIdx = descrIdx - Eth_30_Vtt_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx);
  localDescrRingIdx = (uint8)(descrRingIdx - descrRingStartIdx);

  /* #10 Call the virtual ethernet controller api to check if the TX descriptor with index descrIdx is owned by driver */
  return  VttEth_GetTxDescriptorOwnedByDriverMultiQueues(ctrlIdx, (uint16)localDescrIdx, localDescrRingIdx);
} /* Eth_30_Vtt_LL_IsTxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_IsErrorInRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsErrorInRxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx)
{
  P2VAR(uint8, AUTOMATIC, ETH_30_VTT_VAR_NOINIT) frameData;
  Eth_30_Vtt_RxBufferIterType bufferOffset;
  uint16 bufIdx;
  boolean isFrameAcceptable;

  bufIdx = Eth_30_Vtt_GetMappedBufferOfRxDescrState(descrIdx);
  bufferOffset = (Eth_30_Vtt_RxBufferIterType)(Eth_30_Vtt_GetRxBufferStartIdxOfRxBufferHandling(descrRingIdx) + (bufIdx * Eth_30_Vtt_GetAlignedSegSizeOfRxBufferHandling(descrRingIdx)));
  frameData =  Eth_30_Vtt_GetAddrRxBuffer(bufferOffset);

  /* #10 Check if frame is acceptable */
  isFrameAcceptable = ((Eth_30_Vtt_VIsUnicast(ctrlIdx, &frameData[ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_DST])) ||
#  if (ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
          (TRUE == Eth_30_Vtt_VIsOpenMulticast(ctrlIdx, &frameData[ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_DST])) ||
#  endif /* ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER */
          (TRUE == Eth_30_Vtt_VIsBroadcast(&frameData[ETH_30_VTT_LL_OFFSET_U8_LT60B_RX_DST])));

  return (isFrameAcceptable == FALSE);
} /* Eth_30_Vtt_LL_IsErrorInRxDescriptor() */

/***********************************************************************************************************************
*  Eth_30_Vtt_VIsBroadcast
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE_ISR) Eth_30_Vtt_VIsBroadcast(
 P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
 boolean IsBroadcast = TRUE;
 uint8 Idx = 0;

 /* #10 Check if the physical address is broadcast */
 while (Idx < ETH_PHYS_ADDR_LEN_BYTE)
 {
   if (0xFF != PhysAddrPtr[Idx])
   {
     IsBroadcast = FALSE;
     break;
   }
   Idx++;
 }

 return IsBroadcast;
} /* Eth_30_Vtt_VIsBroadcast() */

#  if (ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
*  Eth_30_Vtt_VIsOpenMulticast
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE_ISR) Eth_30_Vtt_VIsOpenMulticast(
         uint8                        ctrlIdx,
 P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
 boolean RetVal = FALSE;

 /* #10 Multicasts may pass in multicast or promiscuous mode */
 if (ETH_30_VTT_FILTER_PROMISCUOUS_MODE == Eth_30_Vtt_GetFilterMode(ctrlIdx))
 {
   RetVal = TRUE;
 }
 else if ((ETH_30_VTT_FILTER_MULTICAST_MODE == Eth_30_Vtt_GetFilterMode(ctrlIdx)) && ((PhysAddrPtr[0] & ETH_30_VTT_MULTICAST_MASK) != 0))
 {
   /* #20 Calculate CRC32 */
   uint32 Crc32 = Eth_30_Vtt_VCalculateCRC32(PhysAddrPtr, ETH_PHYS_ADDR_LEN_BYTE, 0xFFFFFFFF, TRUE);
   uint8 hash = (uint8)((Crc32 & ETH_30_VTT_MULTICAST_HASH_31_27_MASK) >> ETH_30_VTT_MULTICAST_HASH_31_27_SHIFT);

   Eth_30_Vtt_MulticastBucketCountersStartIdxOfEthCtrlType multicastBucketCounterStartIdx = Eth_30_Vtt_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx);
   if (((uint32)Eth_30_Vtt_GetMulticastBucketCounters(multicastBucketCounterStartIdx + hash)) > 0)
   {
     RetVal = TRUE;
   }
 }
 else
 {
   /* Nothing to do */
 }

 return RetVal;
} /* Eth_30_Vtt_VIsOpenMulticast() */
#  endif /* ETH_30_VTT_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  Eth_30_Vtt_VIsUnicast
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE_ISR) Eth_30_Vtt_VIsUnicast(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
  uint8 MacIdx = 0;
  boolean FilterCond = TRUE;
  /* #10 Check if the physical address is broadcast */
  while (ETH_PHYS_ADDR_LEN_BYTE > MacIdx)
  {
    if (Eth_30_Vtt_GetAddrActiveMacAddress(ctrlIdx)[MacIdx] != PhysAddrPtr[MacIdx])
    {
      FilterCond = FALSE;
      break;
    }
    MacIdx++;
  }

  return FilterCond;
} /* Eth_30_Vtt_VIsUnicast() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_SetRxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_SetRxEvents(
  uint8 ctrlIdx)
{
  sint8_least descrRingIdx;
  Eth_30_Vtt_RxDescrHandlingIterType localDescrRingIdx;
  Eth_30_Vtt_RxDescrHandlingIterType descrRingStartIdx = Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
  Eth_30_Vtt_RxDescrHandlingIterType descrRingEndIdx = Eth_30_Vtt_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) - 1;

  /* #10 Loop over all configured descriptor rings */
  for (descrRingIdx = (sint8_least)descrRingEndIdx; descrRingIdx >= (sint8_least)descrRingStartIdx; descrRingIdx--)
  {
    localDescrRingIdx = (Eth_30_Vtt_RxDescrHandlingIterType)(descrRingIdx - descrRingStartIdx);

    /* #110 Check if there was a Rx event in the current descriptor ring */
    if (Eth_30_Vtt_LL_IsRxPending(ctrlIdx, localDescrRingIdx) == TRUE)
    {
      /* #1110 Set Rx event */
      Eth_30_Vtt_SetRxEvent(ctrlIdx, (Eth_30_Vtt_RxDescrHandlingIterType)descrRingIdx);
      VttEth_ResetRxInterruptRaw(ctrlIdx, (uint8)descrRingIdx);
    }
  }
} /* Eth_30_Vtt_LL_SetRxEvents() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_RearmMacForReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_RearmMacForReception(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_RearmMacForReception() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_RechargeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_RechargeRxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx)
{
  Eth_30_Vtt_RxDescrHandlingIterType localDescrRingIdx;
  Eth_30_Vtt_RxDescrHandlingIterType descrRingStartIdx = Eth_30_Vtt_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

  Eth_30_Vtt_RxDescrIterType localDescrIdx = descrIdx - Eth_30_Vtt_GetRxDescrStartIdxOfRxDescrHandling(descrRingIdx);
  localDescrRingIdx = (uint8)(descrRingIdx - descrRingStartIdx);

  /* #10 Call the virtual ethernet controller api to set the ownership of the RX descriptor to false */
  VttEth_SetRxDescriptorOwnedByDriverMultiQueues(ctrlIdx, (uint16)localDescrIdx, FALSE, localDescrRingIdx);
} /* Eth_30_Vtt_LL_RechargeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_AdaptRxDescriptorRingAfterReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_AdaptRxDescriptorRingAfterReception(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Vtt_LL_AdaptRxDescriptorRingAfterReception() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_GetFrameLengthFromRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(uint16, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetFrameLengthFromRxDescriptor(
  uint8                              ctrlIdx,
  Eth_30_Vtt_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Vtt_RxDescrIterType         descrIdx)
{
  /* #10 Retrieve descriptor address */
  P2VAR(Eth_30_Vtt_RxDescriptorType, AUTOMATIC, ETH_30_VTT_VAR_NOINIT) rxDescr = Eth_30_Vtt_GetAddrRxDescr(descrIdx);

  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* #20 Return received packet size */
  return rxDescr->ReceivedPacketSize;
} /* Eth_30_Vtt_LL_GetFrameLengthFromRxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(uint16, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetMaxCounterOffset(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return 0;
} /* Eth_30_Vtt_LL_GetMaxCounterOffset() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetCounterValue
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetCounterValue(
        uint8                         ctrlIdx,
        uint16                        counterOffset,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) counterValPtr)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(counterOffset); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(counterValPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return retVal;
} /* Eth_30_Vtt_LL_GetCounterValue() */

#  if (ETH_30_VTT_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetRxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetRxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  rxStatsPtr->RxStatsDropEvents           = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsOctets               = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts                 = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsBroadcastPkts        = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsMulticastPkts        = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsCrcAlignErrors       = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsUndersizePkts        = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsOversizePkts         = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsFragments            = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsJabbers              = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsCollisions           = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts64Octets         = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts65to127Octets    = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts128to255Octets   = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts256to511Octets   = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts512to1023Octets  = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxStatsPkts1024to1518Octets = ETH_RXTX_STATS_INV_COUNTER_VAL;
  rxStatsPtr->RxUnicastFrames             = ETH_RXTX_STATS_INV_COUNTER_VAL;

  return E_OK;
} /* Eth_30_Vtt_LL_GetRxStats() */

/**********************************************************************************************************************
 *  Eth_30_Vtt_LL_GetTxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  txStatsPtr->TxNumberOfOctets = ETH_RXTX_STATS_INV_COUNTER_VAL;
  txStatsPtr->TxNUcastPkts     = ETH_RXTX_STATS_INV_COUNTER_VAL;
  txStatsPtr->TxUniCastPkts    = ETH_RXTX_STATS_INV_COUNTER_VAL;

  return E_OK;
} /* Eth_30_Vtt_LL_GetTxStats() */
#  endif /* ETH_30_VTT_ENABLE_GET_ETHER_STATS_API */

#  if (ETH_30_VTT_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Vtt_LL_GetDropInsuffRxBuffHwCounter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_GetDropInsuffRxBuffHwCounter(
        uint8                                                                       ctrlIdx,
  P2VAR(Eth_30_Vtt_DropInsuffRxBuffOfEthMeasDataCounterType, AUTOMATIC, AUTOMATIC)  readCtrValuePtr,
  P2VAR(boolean,                                              AUTOMATIC, AUTOMATIC) isHwCtrResetOnReadPtr)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(readCtrValuePtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_VTT_DUMMY_STATEMENT(isHwCtrResetOnReadPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return E_NOT_OK;
} /* Eth_30_Vtt_LL_GetDropInsuffRxBuffHwCounter() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_ResetDropInsuffRxBuffHwCounter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_ResetDropInsuffRxBuffHwCounter(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return E_NOT_OK;
} /* Eth_30_Vtt_LL_ResetDropInsuffRxBuffHwCounter() */
#  endif /* ETH_30_VTT_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_PerformAdditionalHwConfig
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_VTT_CODE) Eth_30_Vtt_LL_PerformAdditionalHwConfig(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_VTT_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return E_OK;
} /* Eth_30_Vtt_LL_PerformAdditionalHwConfig */

  /**********************************************************************************************************************
  * Eth_30_Vtt_LL_IsRxPending
  **********************************************************************************************************************/
  /*!
  * Internal comment removed.
 *
 *
 *
  */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsRxPending(
	uint8                                   ctrlIdx,
	Eth_30_Vtt_RxDescrHandlingIterType      descrRingIdx)
{
	boolean result = FALSE;
	Eth_30_Vtt_RegWidthType pendingDescrCh;

	/* #10 Retrieve the state of RAW pending events in the current descriptor channel */
	pendingDescrCh = VttEth_GetRxInterruptRaw(ctrlIdx);

	/* #20 Check if there is a pending receive event in the current descriptor ring index */
	if ((pendingDescrCh & ((uint32)1u << descrRingIdx)) != 0)
	{
		result = TRUE;
	}

	return result;
} /* Eth_30_TexasMac_LL_IsRxPending() */

  /**********************************************************************************************************************
  * Eth_30_Vtt_LL_IsTxPending
  **********************************************************************************************************************/
  /*!
  * Internal comment removed.
 *
 *
 *
  */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(boolean, ETH_30_VTT_CODE) Eth_30_Vtt_LL_IsTxPending(
	uint8                                   ctrlIdx,
	Eth_30_Vtt_TxDescrHandlingIterType      descrRingIdx)
{
	boolean result = FALSE;
	Eth_30_Vtt_RegWidthType pendingDescrCh;

	/* #10 Retrieve the state of RAW pending events in the current descriptor channel */
	pendingDescrCh = VttEth_GetTxInterruptRaw(ctrlIdx);

	/* #20 Check if there is a pending receive event in the current descriptor ring index */
	if ((pendingDescrCh & ((uint32)1u << descrRingIdx)) != 0)
	{
		result = TRUE;
	}

	return result;
} /* Eth_30_TexasMac_LL_IsTxPending() */

/**********************************************************************************************************************
 * Eth_30_Vtt_LL_MainFunction
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Vtt_3219 */
ETH_30_VTT_LL_LOCAL_INLINE FUNC(void, ETH_30_VTT_CODE) Eth_30_Vtt_LL_MainFunction( void )
{
  /* #10 Nothing to do here */
} /* Eth_30_Vtt_LL_MainFunction() */

# endif /* ETH_30_VTT_UNIT_TEST */

# define ETH_30_VTT_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_VTT_LL_H */

/* Module-specific exclusive areas: */

/* module specific MISRA deviations:

 */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Vtt_LL.h
 *********************************************************************************************************************/
