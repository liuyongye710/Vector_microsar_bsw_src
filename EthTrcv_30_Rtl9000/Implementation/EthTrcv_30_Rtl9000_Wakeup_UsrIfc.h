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
/*         \file  EthTrcv_30_Rtl9000_Wakeup_UsrIfc.h
 *        \brief  Ethernet transceiver driver header providing the user interface for wake-up inspection
 *
 *      \details  Header file containing the declaration for functions to be used by the user to perform the wake-up
 *                reason detection.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK in the module's header file
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_RTL9000_WAKEUP_USRIFC_H)
# define ETHTRCV_30_RTL9000_WAKEUP_USRIFC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Rtl9000_Lcfg.h"
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if ( ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_RTL9000_WAKEUP_TYPE )
/**********************************************************************************************************************
 *  PRIVATE DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define ETHTRCV_30_RTL9000_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToGeneral()
 *********************************************************************************************************************/
/*! \brief         Sets a general wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToGeneral(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToBus()
 *********************************************************************************************************************/
/*! \brief         Sets a bus wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToBus(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToInternal()
 *********************************************************************************************************************/
/*! \brief         Sets an internal wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToInternal(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToReset()
 *********************************************************************************************************************/
/*! \brief         Sets a reset as wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToReset(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToPowerOn()
 *********************************************************************************************************************/
/*! \brief         Sets a power-on as wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToPowerOn(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToPin()
 *********************************************************************************************************************/
/*! \brief         Sets a pin toggle as wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToPin(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_SetWakeupReasonToSysErr()
 *********************************************************************************************************************/
/*! \brief         Sets a system error as wake-up reason of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_SetWakeupReasonToSysErr(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_IsWakeupReasonPending()
 *********************************************************************************************************************/
/*! \brief         Checks if any wake-up reason of the transceiver with the index TrcvIdx is pending.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \return        result        TRUE: Some wake-up reason pending
 *                               FALSE: No wake-up reason pending
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(boolean, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_IsWakeupReasonPending(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Rtl9000_ClearWakeupReasons()
 *********************************************************************************************************************/
/*! \brief         Clears all pending wakeup reasons of the transceiver with the index TrcvIdx.
 *  \details       -
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Wake-up has to be enabled
 */
FUNC(void, ETHTRCV_30_RTL9000_CODE) EthTrcv_30_Rtl9000_ClearWakeupReasons(
    EthTrcv_30_Rtl9000_EthTrcvIterType TrcvIdx);


#  define ETHTRCV_30_RTL9000_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
# endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED */
#endif /* ETHTRCV_30_RTL9000_WAKEUP_USRIFC_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Rtl9000_Wakeup_UsrIfc.h
 *********************************************************************************************************************/
