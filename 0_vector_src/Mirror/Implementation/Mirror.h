/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!       \file     Mirror.h
 *        \brief    Bus Mirroring header file
 *
 *        \details  Implementation of Bus Mirroring component.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Mueller              vismmu        Vector Informatik GmbH
 *  Simon Gutjahr                 visgsi        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2016-09-30  vismmu  -             Creation
 *  01.00.01  2017-01-10  vismmu  ESCAN00093497 No reset of timeout MirrorDestPduMaxDelay after common transmission
 *            2017-01-10  vismmu  ESCAN00093507 CAN frames shorter than 8 Bytes
 *            2017-01-10  vismmu  ESCAN00093527 Header Base Timestamp too old
 *            2017-01-10  vismmu  ESCAN00093528 Data Timestamp not relative to the Base Timestamp
 *            2017-01-10  vismmu  ESCAN00093529 Config variants Link-time and Post-build do not work
 *            2017-01-10  vismmu  ESCAN00093531 More CAN channels are mirrored than active
 *            2017-01-10  vismmu  ESCAN00093533 CAN channel is not mirrored
 *  01.01.00  2017-03-15  visgsi  FEATC-616     Completion CAN-CAN Mirroring
 *                                ESCAN00094178 Support user defined network Id
 *                                ESCAN00094174 Support CAN range filter
 *                                ESCAN00094351 Support post-build loadable
 *                                ESCAN00094377 Support new API functions
 *                                ESCAN00094378 Improve maintainability of Can-Ip Mirroring
 *                                            - Mirror_CanTxFrame changed to Mirror_ReportCanFrame
 *  02.00.00  2017-03-22  visgsi  STORYC-49     Release FEAT-1656 Mirroring (CDD)
 *  03.00.00  2018-01-22  visgsi  STORYC-2934   CAN-FD support
 *                                ESCAN00097359 Wrong Can Id Type of mirrored messages for Can-Can mirroring
 *                                ESCAN00096630 Wrong values in the mirror header of a Ethernet frame
 *                                ESCAN00098085 Mirror module mirrors on IP destination network when no messages 
 *                                              on the source bus
 *  03.00.01  2018-02-28  visgsi  ESCAN00098439 Compiler error: Undeclared identifier Mirror_RxIndication
 *                                ESCAN00098445 Compiler warning: conversion to 'uint8_least', possible loss of data
 *                                ESCAN00098533 Wrong CAN frames are filtered
 *  03.00.02  2018-07-18  visgsi  ESCAN00099815 Compiler error: syntax error : missing ****
 *                                ESCAN00100080 Mirror transmit buffer is too small in Post-Build configuration
 *  04.00.00  2019-01-28  visgsi  STORY-2631    BETA Version of AUTOSAR Bus Mirroring
 *  04.00.01  2019-03-22  visgsi  STORY-6309    Process3_QM for Gw_Mirror (AUTOSAR Bus Mirroring)
 *                                ESCAN00102601 Invalid CAN Id for LIN to CAN mirroring
 *                                ESCAN00102602 LIN to CAN Id mapping does not work
 *                                ESCAN00102651 Id/Mask filter not according AUTOSAR SWS
 *  04.00.02  2019-04-16  visgsi  ESCAN00102878 Variable in wrong memory section
 *                                ESCAN00102876 Bad memory access when Mirror module is not initialized
 *                                ESCAN00102884 Wrong Module Id
 *  04.00.03  2019-07-12  visgsi  ESCAN00103178 Compiler error: Undeclared identifier LinIf_GetTrcvMode
 *********************************************************************************************************************/
#if !defined (MIRROR_H)
# define MIRROR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Mirror_Cfg.h"
#include "Mirror_Lcfg.h"
#include "Mirror_PBcfg.h"

#include "Mirror_Types.h"
#include "Mirror_Cbk.h"

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Vendor and module identification */
# define MIRROR_VENDOR_ID                           (30u)
# define MIRROR_MODULE_ID                           (48u)

/* AUTOSAR Software specification version information */
# define MIRROR_AR_RELEASE_MAJOR_VERSION            (4u)
# define MIRROR_AR_RELEASE_MINOR_VERSION            (0u)
# define MIRROR_AR_RELEASE_REVISION_VERSION         (3u)

/* ----- Component version information ----- */
# define MIRROR_SW_MAJOR_VERSION                    (4u)
# define MIRROR_SW_MINOR_VERSION                    (0u)
# define MIRROR_SW_PATCH_VERSION                    (3u)

#if !defined(MIRROR_INSTANCE_ID_DET)
# define MIRROR_INSTANCE_ID_DET                     (0x40u)
#endif

/* ----- API service IDs ----- */
# define MIRROR_SID_INIT                            (0x01u) /*!< Service ID: Mirror_Init() */
# define MIRROR_SID_DEINIT                          (0x02u) /*!< Service ID: Mirror_DeInit() */
# define MIRROR_SID_GET_VERSION_INFO                (0x03u) /*!< Service ID: Mirror_GetVersionInfo() */
# define MIRROR_SID_GET_STATIC_FILTER_STATE         (0x23u) /*!< Service ID: Mirror_GetStaticFilterState() */
# define MIRROR_SID_SET_STATIC_FILTER_STATE         (0x14u) /*!< Service ID: Mirror_SetStaticFilterState() */
# define MIRROR_SID_ADD_CAN_RANGE_FILTER            (0x15u) /*!< Service ID: Mirror_AddCanRangeFilter() */
# define MIRROR_SID_ADD_CAN_MASK_FILTER             (0x16u) /*!< Service ID: Mirror_AddCanMaskFilter() */
# define MIRROR_SID_ADD_LIN_RANGE_FILTER            (0x17u) /*!< Service ID: Mirror_AddLinRangeFilter() */
# define MIRROR_SID_ADD_LIN_MASK_FILTER             (0x18u) /*!< Service ID: Mirror_AddLinMaskFilter() */
# define MIRROR_SID_ADD_FLEXRAY_FILTER              (0x19u) /*!< Service ID: Mirror_AddFlexRayFilter() */
# define MIRROR_SID_REMOVE_FILTER                   (0x1Au) /*!< Service ID: Mirror_RemoveFilter() */
# define MIRROR_SID_IS_MIRROR_ACTIVE                (0x20u) /*!< Service ID: Mirror_IsMirrorActive() */
# define MIRROR_SID_OFFLINE                         (0x13u) /*!< Service ID: Mirror_Offline() */
# define MIRROR_SID_GET_DEST_NETWORK                (0x21u) /*!< Service ID: Mirror_GetDestNetwork() */
# define MIRROR_SID_SWITCH_DEST_NETWORK             (0x12u) /*!< Service ID: Mirror_SwitchDestNetwork() */
# define MIRROR_SID_IS_SOURCE_NETWORK_STARTED       (0x22u) /*!< Service ID: Mirror_IsSourceNetworkStarted() */
# define MIRROR_SID_START_SOURCE_NETWORK            (0x10u) /*!< Service ID: Mirror_StartSourceNetwork() */
# define MIRROR_SID_STOP_SOURCE_NETWORK             (0x11u) /*!< Service ID: Mirror_StopSourceNetwork() */
# define MIRROR_SID_GET_NETWORK_TYPE                (0x24u) /*!< Service ID: Mirror_GetNetworkType() */
# define MIRROR_SID_GET_NETWORK_ID                  (0x25u) /*!< Service ID: Mirror_GetNetworkID() */
# define MIRROR_SID_GET_NETWORK_NETWORK_HANDLE      (0x26u) /*!< Service ID: Mirror_GetNetworkHandle() */
# define MIRROR_SID_REPORT_CAN_FRAME                (0x50u) /*!< Service ID: Mirror_ReportCanFrame() */
# define MIRROR_SID_REPORT_LIN_FRAME                (0x51u) /*!< Service ID: Mirror_ReportLinFrame() */
# define MIRROR_SID_REPORT_FLEXRAY_FRAME            (0x52u) /*!< Service ID: Mirror_ReportFlexRayFrame() */
# define MIRROR_SID_REPORT_FLEXRAY_CHANNELSTATUS    (0x53u) /*!< Service ID: Mirror_ReportFlexRayChannelStatus() */
# define MIRROR_SID_TXCONFIRMATION                  (0x40u) /*!< Service ID: Mirror_TxConfirmation() */
# define MIRROR_SID_MAINFUNCTION                    (0x04u) /*!< Service ID: Mirror_MainFunction() */
# define MIRROR_SID_TRIGGER_TRANSMIT                (0x41u) /*!< Service ID: Mirror_TriggerTransmit() */
# define MIRROR_SID_RXINDICATION                    (0x70u) /*!< Service ID: Mirror_RxIndication() */

/* ----- Error codes ----- */
# define MIRROR_E_NO_ERROR                          (0x00u) /*!< used to check if no error occurred - use a value unequal to any error code */

/* -----Development Error codes ----- */
# define MIRROR_E_UNINIT                            (0x01u) /*!< Error code: An API was called while the module was uninitialized */
# define MIRROR_E_REINIT                            (0x02u) /*!< Error code: The init API was called twice */
# define MIRROR_E_INIT_FAILED                       (0x03u) /*!< Error code: Mirror_Init was called with an invalid configuration pointer */
# define MIRROR_E_PARAM_POINTER                     (0x10u) /*!< Error code: An API service was called with a NULL pointer */
# define MIRROR_E_INVALID_PDU_SDU_ID                (0x11u) /*!< Error code: An API service was called with a wrong ID */
# define MIRROR_E_INVALID_NETWORK_ID                (0x12u) /*!< Error code: An API service was called with wrong network handle */

/* -----Runtime Error codes ----- */
# define MIRROR_E_QUEUE_OVERRUN                     (0x40u) /*!< Runtime code: A message could not be stored in the queue */
# define MIRROR_E_TRANSMIT_FAILED                   (0x41u) /*!< Runtime code: A message could not be transmitted */

/* -----Vector Error codes ----- */
# define MIRROR_E_TIMEOUT_TXCONF                    (0x75u) /*!< Error code: Missing Tx Confirmation */
# define MIRROR_E_DUMMY_API                         (0x77u) /*!< Error code: A dummy API was called */
# define MIRROR_E_PARAM_CTRL                        (0x78u) /*!< Error code: API service used with invalid controller index */

/* ----- Modes ----- */
# define MIRROR_UNINIT                              (0x00u)
# define MIRROR_INIT                                (0x01u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define MIRROR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

#if (MIRROR_USE_INIT_POINTER == STD_ON)
extern P2CONST(Mirror_ConfigType, MIRROR_VAR_NOINIT, MIRROR_PBCFG) Mirror_ConfigDataPtr;
#endif

#define MIRROR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/*================================================= MIRROR_START_SEC_CODE ===========================================*/
# define MIRROR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */

/**********************************************************************************************************************
 *  Mirror_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_InitMemory(void);

/**********************************************************************************************************************
 * Mirror_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module Mirror. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   configPtr    Configuration structure for initializing the module, must not be NULL_PTR.
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         Mirror_InitMemory has been called unless Mirror_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_Init(P2CONST(Mirror_ConfigType, AUTOMATIC, MIRROR_PBCFG) configPtr);

/**********************************************************************************************************************
 *  Mirror_DeInit()
 *********************************************************************************************************************/
/*! \brief       Resets the Mirror module to the uninitialized state.
 *  \details     The module is not truly shut down before all services and callback functions have terminated.
 *  \pre         The module must be in the initialized state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_DeInit(void);

# if (MIRROR_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Mirror_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     Mirror_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_VERSION_INFO_API == STD_ON.
 *  \trace       CREQ-107318
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MIRROR_APPL_VAR) versioninfo);
# endif

/**********************************************************************************************************************
 * Mirror_GetStaticFilterState()
 *********************************************************************************************************************/
/*! \brief       Returns the state of a pre-configured filter.
 *  \details     Can be used for all types of source channels.
 *  \param[in]   network  ComM channel that corresponds to the source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \param[out]  isActive Pointer to where to store the current filter state
 *  \return      E_OK: Filter state copied to isActive.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_GetStaticFilterState(NetworkHandleType network, uint8 filterId, boolean* isActive);

/**********************************************************************************************************************
 * Mirror_SetStaticFilterState()
 *********************************************************************************************************************/
/*! \brief       Sets the state of a pre-configured filter.
 *  \details     Can be used for all types of source channels.
 *  \param[in]   network  ComM channel that corresponds to the source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \param[in]   isActive TRUE: Activate filter, FALSE: Deactivate filter
 *  \return      E_OK: Filter state updated from isActive
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SetStaticFilterState(NetworkHandleType network, uint8 filterId, boolean isActive);

/**********************************************************************************************************************
 * Mirror_RemoveFilter()
 *********************************************************************************************************************/
/*! \brief       Removes a filter that was added at runtime.
 *  \details     Can be used for CAN and LIN
 *  \param[in]   network  ComM channel that corresponds to the source bus to which the filter is attached
 *  \param[in]   filterId Id of the filter.
 *  \return      E_OK: Filter was removed.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_RemoveFilter(NetworkHandleType network, uint8 filterId);

/**********************************************************************************************************************
 * Mirror_IsMirrorActive()
 *********************************************************************************************************************/
/*! \brief       Returns the global mirroring state.
 *  \details     -
 *  \return      TRUE: Bus Mirroring module is active
 *  \return      FALSE: Bus Mirroring module is inactive
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(boolean, MIRROR_CODE) Mirror_IsMirrorActive(void);

/**********************************************************************************************************************
 * Mirror_Offline()
 *********************************************************************************************************************/
/*! \brief       Completely disables any mirroring activities.
 *  \details     Source buses are reset to disabled, queued messages are purged, and the destination bus is reset to
 *               the default destination. Pre-configured filters are disabled, and filters added at runtime are removed.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, MIRROR_CODE) Mirror_Offline(void);

/**********************************************************************************************************************
 * Mirror_GetDestNetwork()
 *********************************************************************************************************************/
/*! \brief       Returns the currently selected destination bus.
 *  \details     -
 *  \return      ComM channel that corresponds to the currently active destination network.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(NetworkHandleType, MIRROR_CODE) Mirror_GetDestNetwork(void);

/**********************************************************************************************************************
 * Mirror_SwitchDestNetwork()
 *********************************************************************************************************************/
/*! \brief       Changes the destination bus to the given ComM channel.
 *  \details     The previously active destination bus and all source buses are disabled.
 *  \param[in]   network    ComM channel corresponding to the destination bus that shall be enabled.
 *  \return      E_OK: Destination bus was changed.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_SwitchDestNetwork(NetworkHandleType network);

/**********************************************************************************************************************
 * Mirror_IsSourceNetworkStarted()
 *********************************************************************************************************************/
/*! \brief       Returns the state of a source bus.
 *  \details     -
 *  \param[in]   network  ComM channel corresponding to the source bus that shall be checked.
 *  \return      TRUE: Source bus is active.
 *  \return      FALSE: Source bus is inactive.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(boolean, MIRROR_CODE) Mirror_IsSourceNetworkStarted(NetworkHandleType network);

/**********************************************************************************************************************
 *  Mirror_StartSourceNetwork()
 *********************************************************************************************************************/
/*! \brief       Activates a source bus.
 *  \details     -
 *  \param[in]   network    ComM channel corresponding to the source bus that shall be started.
 *  \return      E_OK: Source bus was activated.
 *  \return      E_NOT_OK: Function was called with invalid parameters
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StartSourceNetwork(NetworkHandleType network);

/**********************************************************************************************************************
 *  Mirror_StopSourceNetwork()
 *********************************************************************************************************************/
/*! \brief       Deactivates a source bus.
 *  \details     -
 *  \param[in]   network    ComM channel corresponding to the source bus that shall be stopped.
 *  \return      E_OK: Source bus was deactivated.
 *  \return      E_NOT_OK: Function was called with invalid parameters.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_StopSourceNetwork(NetworkHandleType network);

/**********************************************************************************************************************
 * Mirror_GetNetworkType()
 *********************************************************************************************************************/
/*! \brief       Returns the network type of the given network.
 *  \details     Can be used for source and destination networks.
 *  \param[in]   network   ComM channel corresponding to one of the buses configured as source or destination bus.
 *  \return      Network type of the bus identified by "network", or MIRROR_NT_INVALID if the bus is not configured 
 *               for Mirror.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Mirror_NetworkType, MIRROR_CODE)  Mirror_GetNetworkType(NetworkHandleType network);

/**********************************************************************************************************************
 * Mirror_GetNetworkId()
 *********************************************************************************************************************/
/*! \brief       Returns the network ID of the given network.
 *  \details     Can be used for source and destination networks.
 *  \param[in]   network   ComM channel corresponding to on of the buses configured as source or destination bus.
 *  \return      Network ID of the bus identified by "network", or 0xFF if the bus is not configured for Mirror.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(uint8, MIRROR_CODE)  Mirror_GetNetworkId(NetworkHandleType network);

/**********************************************************************************************************************
 * Mirror_GetNetworkHandle()
 *********************************************************************************************************************/
/*! \brief       Returns the network handle (ComMChannel) of the bus identified by the given network type and 
 *               network ID.
 *  \details     -
 *  \param[in]   networkType   Network type of the bus to be identified.
 *  \param[in]   networkId     Network ID of the bus to be identified.
 *  \return      ComM channel that corresponds to the bus identified by the given network type and network ID:
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(NetworkHandleType, MIRROR_CODE)  Mirror_GetNetworkHandle(Mirror_NetworkType networkType, uint8 networkId);

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_AddCanRangeFilter()
*********************************************************************************************************************/
/*! \brief       Creates a CAN ID range filter.
*  \details     -
*  \param[in]   network   ComM channel that corresponds to the CAN bus to which the filter shall be attached.
*  \param[out]  filterId  Id of the newly created filter.
*  \param[in]   lowerId   Lower CAN ID of the range.
*  \param[in]   upperId   Upper CAN ID of the range.
*  \return      E_OK: New filter created.
*  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
*                         network was free.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   TRUE for different networks.
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddCanRangeFilter(NetworkHandleType network, uint8* filterId,
  uint32 lowerId, uint32 upperId);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_CAN == STD_ON)
/**********************************************************************************************************************
*  Mirror_AddCanMaskFilter()
*********************************************************************************************************************/
/*! \brief       Creates a CAN ID mask filter.
*  \details     -
*  \param[in]   network   ComM channel that corresponds to the CAN bus to which the filter shall be attached.
*  \param[out]  filterId  Id of the newly created filter.
*  \param[in]   id        CAN ID used to match a received or transmitted CAN ID:
*  \param[in]   mask      Mask that defines the bits of "id" that are relevant for comparison with the actual CAN ID.
*  \return      E_OK: New filter created.
*  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
*                         network was free.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   TRUE for different networks.
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_CAN == STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddCanMaskFilter(NetworkHandleType network, uint8* filterId,
  uint32 id, uint32 mask);
#endif /* (MIRROR_SOURCE_CHANNEL_CAN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_AddLinRangeFilter()
*********************************************************************************************************************/
/*! \brief       Creates a LIN ID range filter.
*  \details     -
*  \param[in]   network   ComM channel that corresponds to the LIN bus to which the filter shall be attached.
*  \param[out]  filterId  Id of the newly created filter.
*  \param[in]   lowerId   Lower frame ID of the range.
*  \param[in]   upperId   Upper frame ID of the range.
*  \return      E_OK: New filter created.
*  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
*                         network was free.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   TRUE for different networks.
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddLinRangeFilter(NetworkHandleType network, uint8* filterId,
  uint32 lowerId, uint32 upperId);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_LIN == STD_ON)
/**********************************************************************************************************************
*  Mirror_AddLinMaskFilter()
*********************************************************************************************************************/
/*! \brief       Creates a LIN ID mask filter.
*  \details     -
*  \param[in]   network   ComM channel that corresponds to the LIN bus to which the filter shall be attached.
*  \param[out]  filterId  Id of the newly created filter.
*  \param[in]   id        Frame ID used to match a received or transmitted frame ID.
*  \param[in]   mask      Mask that defines the bits of "id" that are relevant for comparison with the actual frame ID.
*  \return      E_OK: New filter created.
*  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
*                         network was free.
*  \pre         Module is initialized.
*  \context     TASK
*  \reentrant   TRUE for different networks.
*  \synchronous TRUE
*  \config      This function is only available if MIRROR_SOURCE_CHANNEL_LIN == STD_ON.
*********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddLinMaskFilter(NetworkHandleType network, uint8* filterId,
  uint32 id, uint32 mask);
#endif /* (MIRROR_SOURCE_CHANNEL_LIN == STD_ON) */

#if (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON)
/**********************************************************************************************************************
 *  Mirror_AddFlexRayFilter()
 *********************************************************************************************************************/
/*! \brief       Creates a FlexRay filter.
 *  \details     -
 *  \param[in]   network          ComM channel that corresponds to the FlexRay bus to which the filter shall be attached.
 *  \param[out]  filterId         Id of the newly created filter.
 *  \param[in]   lowerSlotId      Lower slot ID of a range of slot IDs.
 *  \param[in]   upperSlotId      Upper slot ID of a range of slot IDs.
 *  \param[in]   lowerBaseCycle   Lower base cycle of a range of cycles.
 *  \param[in]   upperBaseCycle   Upper base cycle of a range of cycles.
 *  \param[in]   cycleRepetition  Repetition pattern of selected cycles (2^n).
 *  \param[in]   frChannel        FlexRay channel assignment.
 *  \return      E_OK: New filter created.
 *  \return      E_NOT_OK: Creation of filter failed because of invalid parameters or because no filter on the given
 *                         network was free.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE for different networks.
 *  \synchronous TRUE
 *  \config      This function is only available if MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, MIRROR_CODE) Mirror_AddFlexRayFilter(NetworkHandleType network, uint8* filterId, uint16 lowerSlotId,
                                                          uint16 upperSlotId, uint8 lowerBaseCycle, uint8 upperBaseCycle,
                                                          uint8 cycleRepetition, Mirror_FlexRayChannelType frChannel);
#endif /* (MIRROR_SOURCE_CHANNEL_FLEXRAY == STD_ON) */

/**********************************************************************************************************************
 * Mirror_MainFunction()
 *********************************************************************************************************************/
/*! \fn          void Mirror_MainFunction(void)
 *  \brief       Main function for timeout handling and FIFO processing.
 *  \details     This function takes care of the timeout handling and destination channel queue processing.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* declared within SchM_Mirror.h */

# define MIRROR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e{451} */
/*================================================= MIRROR_STOP_SEC_CODE ============================================*/

/*!
 * \exclusivearea  MIRROR_EXCLUSIVE_AREA_QUEUE
 *                 Ensure the consistency of the queue state.
 * \protects       Mirror_GeneralCtx.
 * \usedin         Mirror_Offline, Mirror_SwitchDestNetwork, Mirror_MainFunction.
 * \exclude        -
 * \length         LONG Several internal queue functions and a memory copy function is called.
                        Depending on the data length of the queue element it can take a while.
 * \endexclusivearea
 */

/*!
 * \exclusivearea  MIRROR_EXCLUSIVE_AREA_TXPDU
 *                 Ensure the consistency of the Tx PDU state.
 * \protects       Mirror_GeneralCtx, Mirror_DestChannelCan_FrameLost, Mirror_DestChannelIp_Ctx.
 * \usedin         Mirror_GetDestNetwork, Mirror_TxConfirmation, Mirror_TriggerTransmit, Mirror_MainFunction.
 * \exclude        -
 * \length         SHORT Only a few flags are checked. No calls to functions.
 * \endexclusivearea
 */

/*!
 * \exclusivearea  MIRROR_EXCLUSIVE_AREA_SOURCECHANNEL
 *                 Ensure the consistency of global mirror state and the source channel filter.
 * \protects       Mirror_GeneralCtx, Filter of Source Networks CAN and LIN.
 * \usedin         Mirror_IsSourceNetworkStarted, Mirror_StartSourceNetwork, Mirror_StopSourceNetwork,
 *                 Mirror_ReportCanFrame, Mirror_ReportLinFrame.
 * \exclude        -
 * \length         LONG Several Mirror functions are called. However, the whole processing shouldn't
 *                      take long under normal conditions.
 * \endexclusivearea
 */

#endif /* MIRROR_H */

/**********************************************************************************************************************
 *  END OF FILE: Mirror.h
 *********************************************************************************************************************/
