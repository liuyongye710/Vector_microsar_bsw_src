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
/*!        \file  Eth_30_Tc3xx_LL.h
 *        \brief  Lower layer header file
 *
 *      \details  Declaration and definition of lower layer part of Ethernet driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  00.01.00  2017-08-01  visbgr  -             Initial creation
 *  00.02.00  2018-01-03  visbgr  STORY-3570    TASK-60515 Provide DrvETh_Tc3xx Beta version using TriBoard TC3X9 V2.0
 *  01.00.00  2018-02-19  visbgr  STORY-4098    TASK-65966 Review Integration and Core Update
 *  02.00.00  2018-05-14  visbgr  STORYC-5156   TASK-73499 Implement prototype QoS support in implementation
 *                                STORYC-5967   TASK-82306 Testing and bugfixing of QoS RX prototype implementation
 *                                STORYC-5968   TASK-82307 Testing and bugfixing of FQTSS prototype implementation
 *                                STORYC-5155   TASK-73501 Finalize QoS support implementation
 *  02.01.00  2019-02-18  visbgr  STORY-10652   Update Core DrvEth_Tc3xxEthAsr
 *  03.00.00  2019-03-18  visbgr  ESCAN00101437 Possible memory violation in case of multi Eth driver configuration
 *                                ESCAN00101808 Compiler warning: Calling function without prototype
 *                                              Appl_UnlockEndinit / Appl_LockEndinit
 *                                ESCAN00101709 Missing overflow handling during global time retrieval
 *  03.00.01  2019-04-02  visbgr  STORYC-8019   Review Integration of DMA Review for TC3xx
 *                                ESCAN00101663 Memory corruption possible if RX buffers are configured smaller than
 *                                              1522 bytes
 *                                ESCAN00102625 Possible loss of interrupt could lead to stuck communication on
 *                                              Ethernet
 *  04.00.00  2019-08-27  viskha  ETH-786       Update DrvEth_Tc3xxEthAsr to MSR4-R23 DrvEth__coreAsr
 *  04.00.01  2020-02-11  visken  ESCAN00103315 Not considered Application Hint GETH_AI.H001 Preparation for Software
 *                                              Reset (GETH_TC.002 update)
 *                                ETH-1694      Introduce further handling that is needed for bugfix of ESCAN00103315
 *                                ESCAN00105289 Possible Endless-Loop in IRQ handler in case frame is received during 
 *                                              mode transition from ACTIVE to DOWN
 *                                ESCAN00105184 Update Core DrvEth_Tc3xxEthAsr
 *  04.00.02  2020-04-14  viskha  ESCAN00106019 Compiler error: undeclared identifier "CtrlIdx"
 *                                ESCAN00105914 Not considered Application Hint GETH_AI.H001 together with
 *                                              GETH_TC.002 - Preparation for Software Reset
 *  04.01.00  2020-05-11  viskha  ETH-2057      Allow triggering PPS signal from TC3xx to external chip on a given
 *                                              timer value in the MAC
 *  05.00.00  2020-03-23  vircnt  ETH-1899      Update to latest DrvEth__coreAsr
 *            2020-06-17  virstl  ETH-2367      Check CDD for consistency
 *            2020-06-25  vircnt  ETH-1905      Integrate bugfixes and features from main development branch
 *            2020-07-15  vircnt  ETH-2716      Update DrvEth_Tc3xxAsr to trunk of DrvEth__coreAsr
 *  06.00.00  2020-09-25  virbks  ETH-3270      Update DrvEth_Tc3xxEthAsr to DrvEth__coreAsr[9.01.04]
 *            2020-09-28  virstl  ETH-3244      Safety ready DrvEth_Tc3xxEthAsr (Silent)
 *  06.01.00  2020-10-22  virbks  ETH-3295      Support QoS and checksum offloading enabled at the same time
 *  06.02.00  2021-03-17  visdep  ETHCIF-138    Introduce assignment of Ethernet frames to queues based on VLAN ID
 *  06.03.00  2021-06-14  visdep  ETHCIF-402    Detect API calls in incorrect partition - EthTc3xx
 *  06.04.00  2021-08-25  visdep  ETHCIF-763    DrvEth_Tc3xx - Update to latest core to fix ESCAN00109626
 *                                ETHCIF-20     Bring Advanced MC Distribution for Ethernet to Production Quality - Eth
 *                                ESCAN00109601 Incorrect descriptor address/index in multiple location in multi 
 *                                              controller use-case
 *                                ESCAN00109970 Possible wrong tail pointer assignment for Tx Qos queues
 *  20.00.00  2020-08-19  vircnt  ETH-3010      Split component into units
 *            2020-09-09  vircnt  ETH-3064      Safety-ready Tc3xx extension
 *            2020-12-22  visdep  ETH-3463      Updated the Implementation version
 *            2021-07-29  vircnt  ETHCIF-469    Updated Implementation to feature compability with version 6.3.0 
 *            2021-11-12  vircnt  ETHCIF-832    Updated Implementation to feature compability with version 6.4.0 
 *                                ESCAN00110734 Incorrect initialization of descriptor base addresses
 *            2021-11-25  vircnt  ESCAN00110268 Invalid rx buffer mapping in rx descriptor initialization for some of 
 *                                              the Rx buffers when sum of size of all Rx buffers is more that max value
 *                                              of uint16.
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_LL_H)
# define ETH_30_TC3XX_LL_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Int.h"
# include "Eth_30_Tc3xx_Cfg.h"
# include "Eth_30_Tc3xx_LL_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# ifndef ETH_30_TC3XX_LL_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_LOCAL_INLINE                                LOCAL_INLINE
# endif /* ETH_30_TC3XX_LL_LOCAL_INLINE */

# define ETH_30_TC3XX_SW_MAJOR_VERSION                                (20u)
# define ETH_30_TC3XX_SW_MINOR_VERSION                                (0u)
# define ETH_30_TC3XX_SW_PATCH_VERSION                                (0u)

/*! PPS identifiers */
# define ETH_30_TC3XX_PPS_TIME_SECONDS_HI                             (0x0u)
# define ETH_30_TC3XX_PPS_TIME_NANOSECONDS_RANGE                      (0x7FFFFFFFu)

/* ETH ApiIds */
# define ETH_30_TC3XX_SID_ARM_PPS_EVENT_ON_TIME                       (0x45u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_ArmPpsEventOnTime
 **********************************************************************************************************************/
/*! \brief       Configures the controller to trigger the Pps single pulse on the given time.
 *  \details     -
 *  \param[in]   CtrlIdx       Index of controller
 *  \param[in]   TimestampPtr  Pointer to the provided time stamp
 *  \return      E_NOT_OK - PPS signal trigger configuration failed
 *  \return      E_OK - PPS signal trigger configuration successful / not enabled
 *  \context     TASK
 *  \reentrant   TRUE - for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 *  \trace       CREQ-Eth-PPS
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ArmPpsEventOnTime(
    uint8 CtrlIdx,
    P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) TimestampPtr);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_LL_H */

/* Module-specific exclusive areas: */

/* module specific MISRA deviations:
  MD_Eth_30_Tc3xx_0306:
    Reason:     Descriptor word accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk because descriptor pointers are only available with 32 bit length
    Prevention: Covered by code review.
 */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/
