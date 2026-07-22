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
/*!        \file  Eth_30_Tc3xx.h
 *        \brief  Public header file of Ethernet controller driver
 *
 *      \details  Provides access to the Ethernet controller drivers API.
 *
 *********************************************************************************************************************/
/********************************************************************************************************************** 
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2016-10-04  visfer  -             Initial creation
 *  01.00.01  2016-11-28  visfer  ESCAN00093063 Transmission stops when upper layers request to free several 
 *                                              provided buffers
 *  01.00.01  2016-11-28  visfer  ESCAN00093163 Compiler error due to wrong API infixing in compiler_cfg.h and memmap.h
 *  02.00.00  2017-02-15  vismha  ESCAN00094012 Changes due to DrvEth_VttEthAsr migration
 *                        visfer  ESCAN00093414 Pre- and Post-ControllerInit Callouts are missing
 *                        visfer  ESCAN00093412 Review Integration and refacturing of code, comments and detailed design
 *                        visfer  ESCAN00093704 Compiler error: undeclared identifiers 
 *                                              Eth_30_Tc3xx_MulticastBucketCounters, Eth_30_Tc3xx_PromiscuousModeCounter
 *  03.00.00  2017-05-02  vismha  ESCAN00094983 Extend Core for support of FEC and ENET drivers with extended feature
 *                                              set
 *  03.00.01  2017-05-29  visfer  ESCAN00095318 Compiler error: Det.h referenced although Dev Error Report is switched
 *                                              off
 *  03.00.02  2017-06-29  visfer  ESCAN00095679 Add return value to Eth_30_Tc3xx_LL_TimeSync_SetHwTime()
 *  03.01.00  2017-07-04  visdrr  FEATC-1245    FEAT-2151: Extended Ethernet Bus Diagnostic
 *  03.02.00  2017-07-25  visbgr  ESCAN00095826 Changes due to DrvEth_S6J3xEthAsr migration
 *  03.02.01  2017-09-07  visfer  ESCAN00096586 MemMap.h template does not contain correct handling 
 *                                              ETH_30_TC3XX_STOP_SEC_APPL_CODE
 *  03.02.02  2017-09-11  visfer  ESCAN00096614 Compiler warning: Variable FrameId is possibly uinitialized
 *  03.02.03  2017-09-11  visfer  ESCAN00096760 Time synchronization using gPTP is not possible
 *  05.00.00  2018-03-01  visbgr  STORYC-422    FEAT-2876,S-456 [SAFE] SafeBSW for Eth(Core) (ASIL B), P3REQ,CAD,TST,REV
 *                        visbgr  STORYC-423    FEAT-2876,S-457 [SAFE] SafeBSW for Eth(Core) (ASIL B), S1 ComStackLib
 *                        visbgr  STORYC-424    FEAT-2876,S-458 [SAFE] SafeBSW for Eth(Core) (ASIL B), S1Tst
 *                        visbgr  ESCAN00097402 Init API uses incorrect API Id for DET reporting
 *                        visbgr  ESCAN00097133 Memory violation in case Eth_30_<derivative>_Pending[Rx|Tx]Events
 *                                              is not initialized with zero
 *                        visbgr  STORYC-5619   DrvEth__coreAsr: Improve include structure in the implementation
 *            2018-07-27  visdrr  ESCAN00100196 DET-Check in VTransmit missing: API call with NULL_PTR possible
 *  06.00.00  2018-08-08  visdrr  STORYC-428    FEAT-2876,S-463 [SAFE] SafeBSW for Eth(Core) (ASIL B), S1REV
 *                                ESCAN00098835 Missing DET check for parameter RxStatusPtr of Eth_Receive API
 *            2018-08-09  visdrr  STORYC-6235   FEAT-2876 [SAFE] SafeBSW for Eth(Core) SilentAnalysis Rework:
 *                                              Rework HL/LL-Interface
 *                                STORYC-6236   FEAT-2876 [SAFE] SafeBSW for Eth(Core) SilentAnalysis Rework:
 *                                              Add runtime checks at locations with Ethernet buffer access
 *  06.00.01  2019-04-24  viskob  ESCAN00103483 Compiler error: Eth_30_<MSN>_Ctrl2ProtectedAreaIdMap is undefined
 *                                ESCAN00103327 MISRA deviation: MISRA-C:2004 Rule 5.1 - ID 4:0779
 *  06.00.02  2019-08-08  viskob  ESCAN00103936 Counter measure tag spelling error causes traceability findings
 *            2019-08-19  viskob  ESCAN00104035 Out of bounds read-access possible: Incorrect source MAC address is
 *                                              written to the register and used for transmission, if [..].
 *  07.00.00  2019-04-29  visdrr  STORYC-7882   Interface between DrvEth__coreAsr and DrvEthSwitch__coreAsr according to
 *                                              ASR4.4.x (DrvEth__coreAsr)
 *  07.01.00  2019-08-28  visdrr  FEAT-4936     Support of MSTAR MSE102x
 *                                ESCAN00104035 Out of bounds read-access possible: Incorrect source MAC address is 
 *                                              written to the register and used for transmission, if more than one 
 *                                              Ethernet controller configuration or driver is used
 *            2019-09-27  visdrr  ESCAN00103936 Counter measure tag spelling error causes traceability findings
 *  07.01.01  2019-10-21  viskob  ETH-1047      Support of Mse102x - DrvEth QM
 *  07.02.00  2019-09-06  viskob  ETH-833       Merge branch 6.xx.xx into trunk.
 *  08.00.00  2019-11-11  viskob  ETH-1099      DrvEth__coreAsr - Merge 7.xx.xx into trunk.
 *  08.01.00  2020-03-27  visdep  ETH-1255      Provide information about dropped frames due to insufficient Tx/Rx
 *                                              software buffers
 *            2020-04-16  visdrr  PS-273        Introduce buffer warning level callout for the reception path
 *            2020-04-16  visdrr  ESCAN00106007 Access to buffer and descriptor variables of incorrect Ethernet
 *                                              controller/channel happens in multi-Ethernet controller configurations
 *            2020-04-16  visdrr  ESCAN00105184 Tx buffers get not freed on lower prior queues when QoS is used in
 *                                              polling mode and high amount of traffic is communicated on higher prior
 *                                              QoS queues
 *  08.01.01  2020-07-09  vircnt  ETH-2145      Update MISRA justifications
 *                                ETH-2716      Support of DrvEth_Tc3xxEthAsr
 *  08.01.02  2020-07-13  visdrr  ESCAN00106470 Inconsistent descriptor state possible in transmission path:
 *                                              Memory barrier missing between setting up and triggering transmission
 *  08.01.03  2020-08-07  visdep  ESCAN00107011 Compiler error: Wrong memory class in 
 *                                              Eth_30_Tc3xx_Internal_ClearMeasurementData
 *  08.01.04  2020-08-10  visdrr  ESCAN00106987 Frame loss in higher priority queues under high bus load in polling mode
 *                                              with QoS enabled
 *            2020-08-10  visdrr  ESCAN00105184 Tx buffers get not freed on lower prior queues when QoS is used in
 *                                              polling mode and high amount of traffic is communicated on higher prior
 *                                              QoS queues
 *  08.01.05  2020-09-22  visdrr  ESCAN00107263 Tx buffer start offset is not correct in
 *                                              ProvideTxBuffer_HandleValidBuffer
 *            2020-09-22  visdrr  ESCAN00107236 Compiler error: Appl_Eth_30_Tc3xx_MemoryBarrier function is undefined
 *                                              when ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_ON
 *            2020-09-22  visdrr  ESCAN00106769 Invalid buffer- or descriptor alignment could be undetected in multi-
 *                                              channel configuration
 *  08.01.06  2020-10-07  vircnt  ESCAN00107156 Receiving and transmitting frames does not work in interrupt mode if 
 *                                              development error detection is disabled
 *  08.01.07  2020-10-27  virstl  ESCAN00107683 Untagged frames to a Tx queue mapping configuration has no efffect
 *  08.01.08  2021-01-22  visdrr  ESCAN00108359 Eth_30_Tc3xx_VTransmit fails due to a wrong buffer index check in multi-
 *                                              channel configurations
 *  08.02.00  2021-03-16  visdep  ETHCIF-138    Introduce assignment of Ethernet frames to queues based on VLAN ID
 *  08.03.00  2021-04-08  viskob  ETHCIF-384    Merge change of uint32 reg_base_addr into Core
 *  08.04.00  2021-06-14  visdep  ETHCIF-402    Detect API calls in incorrect partition - EthTc3xx
 *  08.04.01  2021-06-21  visdep  ETHCIF-671    Removed some dummy statements
 *  08.04.02  2021-08-12  visdep  ETHCIF-191    S32G Core Update + HW Setup
 *  08.05.00  2021-09-01  visdep  ETHCIF-20     Bring Advanced MC Distribution for Ethernet to Production Quality - Eth
 *  20.00.00  2020-08-19  vircnt  ETH-3010      Split component into units
 *                        vircnt  ESCAN00107156 Receiving and transmitting frames does not work in interrupt mode if 
 *                                              development error detection is disabled
 *            2020-12-22  visdep  ETH-3463      Updated the Implementation version
 *            2021-11-12  vircnt  ETHCIF-832    Integrate changes from version 8.05.00
 *            2021-11-20  virskl  ESCAN00110538 Potential misbehaviour of Eth_UpdatePhysAddrFilter 
 *                                              when Eth_BswSplitSupport is enabled
 *********************************************************************************************************************/

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

#if !defined(ETH_30_TC3XX_H)
# define ETH_30_TC3XX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
# include "Eth_30_Tc3xx_Generic.h"
# include "Eth_30_Tc3xx_CtrlModeHdl.h"
# include "Eth_30_Tc3xx_MacHdl.h"
# include "Eth_30_Tc3xx_MiiAccess.h"
# include "Eth_30_Tc3xx_Rx.h"
# include "Eth_30_Tc3xx_Statistics.h"
# include "Eth_30_Tc3xx_TimeSync.h"
# include "Eth_30_Tc3xx_TrafficHandling.h"
# include "Eth_30_Tc3xx_Tx.h"
# include "Eth_30_Tc3xx_LL.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* AUTOSAR 4.x Software Specification Version Information */
# define ETH_30_TC3XX_AR_RELEASE_MAJOR_VERSION                        (0x04u)
# define ETH_30_TC3XX_AR_RELEASE_MINOR_VERSION                        (0x01u)
# define ETH_30_TC3XX_AR_RELEASE_REVISION_VERSION                     (0x01u)


/*!
 * \exclusivearea ETH_30_TC3XX_EXCLUSIVE_AREA_DATA
 * Protects the consistency of data and sequences used in the Ethernet controller driver
 * \protects Global data consistency and sequences
 * \usedin  Eth_30_Tc3xx_UpdatePhysAddrFilter, Eth_30_Tc3xx_Receive, Eth_30_Tc3xx_ReceiveFifo, Eth_30_Tc3xx_GetRxStats,
 *          Eth_30_Tc3xx_GetTxStats, Eth_30_Tc3xx_GetAndResetMeasurementData, Eth_30_Tc3xx_ProvideTxBuffer,
 *          Eth_30_Tc3xx_Transmit, Eth_30_Tc3xx_VTransmit, Eth_30_Tc3xx_TxConfirmation, Eth_30_Tc3xx_TxConfirmationFifo
 * \exclude  Concurrent calls to the "usedin" functions.
 * \length LONG This exclusive area covers calls to several sub-functions.
 * \endexclusivearea
 *
 * \exclusivearea ETH_30_TC3XX_EXCLUSIVE_AREA_MII
 * Protects the consistency of the MII management access
 * \protects MII management read/write accesses that are performed asynchronously
 * \usedin   Eth_30_Tc3xx_WriteMii, Eth_30_Tc3xx_ReadMii
 * \exclude  Concurrent calls to the "usedin" functions.
 * \length MEDIUM This exclusive area covers the triggering of a MII management operation, the waiting for the operation
 *                to finish and the retrieval of the data
 * \endexclusivearea
 *
 * \exclusivearea ETH_30_TC3XX_EXCLUSIVE_AREA_MULTICAST_FILTER
 * Protects the consistency of the promiscuous mode counter
 * \protects promiscuous mode counter read/write accesses that are performed asynchronously from different cores
 * \usedin   Eth_30_Tc3xx_UpdatePhysAddrFilter
 * \exclude  Concurrent calls to the "usedin" functions.
 * \length MEDIUM This exclusive area covers the update of MAC address filter of a Ethernet controller and
 * reading and writing the promiscuous mode counter
 * \endexclusivearea
 *
 */

#endif /* ETH_30_TC3XX_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx.h
 *********************************************************************************************************************/
