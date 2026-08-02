/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 Vector Informatik GmbH.                                                     All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  J1939Nm.h
 *       Module:  SAE J1939 Network Management (J1939Nm)
 *
 *  Description:  Main header of the SAE J1939 Network Management module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Martin Schlodder              vismsr        Vector Informatik GmbH
 *  Thomas Albrecht               vistat        Vector Informatik GmbH
 *  Simon Gutjahr                 visgsi        Vector Informatik GmbH
 *  Matthias Mueller              vismmu        Vector Informatik GmbH
 *  Christian Waibel              viscnw        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version  Date        Author  Change Id      Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  0.01.00  2013-11-01  vismsr   -             First Version.
 *                       vistat   -             Adapted to Vector template and performed MISRA analysis.
 *                                -             Implemented memory and compiler abstraction.
 *  0.01.01  2013-11-04  vismsr  ESCAN00071577  Fixed use case without foreign nodes or commanded address support.
 *  0.01.02  2013-11-14  vismsr  ESCAN00071963  Introduced initial request for AC in dynamic NM.
 *  0.01.03  2013-11-15  vismsr  ESCAN00071970  Fixed handling of dynamically assigned node addresses.
 *  0.02.00  2014-03-05  vismsr  ESCAN00071770  Implemented GetState API.
 *                               ESCAN00073220  Added support for mixed configuration of dynamic nodes and channels.
 *                               ESCAN00073695  Fixed acceptance of wrong address via CommandedAddress.
 *                                -             Cleaned up module state handling, implemented DET reporting.
 *                                -             MISRA analysis performed.
 *                                -             Fixed MemMap/Compiler_Cfg.
 *  0.03.00  2014-06-16  vismsr  ESCAN00071931  Fixed signatures of StartOfReception and RxIndication.
 *                               ESCAN00073893  Handling AC of anonymous communication partners.
 *                               ESCAN00074031  Applied ifdefs to avoid access to unused variable.
 *                               ESCAN00074132  Support for post-build configuration.
 *                               ESCAN00074588  Fixed parameters of AddressClaimedIndication.
 *                               ESCAN00075571  Added source identification.
 *                               ESCAN00075993  Fixed NAME filter handling.
 *  0.04.00  2015-02-05  vismsr  ESCAN00071608  Implemented iterative and request address search modes.
 *                               ESCAN00075579  Implemented address tracking.
 *                               ESCAN00077425  Fixed inclusion of Det.h.
 *                               ESCAN00079739  Implemented NAME management support.
 *                               ESCAN00081066  Added reporting of DEM errors.
 *                                -             Introduced J1939Nm_Dynamic.[ch] and J1939Nm_Int.h.
 *                                -             Added function pointer types for callout functions.
 *                                -             Fixed post-build configuration of dynamic use case,
 *                                -             TP API now hidden in non-dynamic use case.
 *  0.05.00  2015-03-25  vismsr  ESCAN00071606  Added random delay based on NAME before address claim after request.
 *                               ESCAN00075508  Added state change indications to NM.
 *                               ESCAN00075526  Startup delay is now only applied to addresses 128..247.
 *                               ESCAN00080681  Avoid claiming the same address for multiple internal nodes.
 *                               ESCAN00081195  Fixed state check in J1939Nm_NetworkRelease.
 *                               ESCAN00081197  Fixed use case without foreign nodes.
 *                               ESCAN00081305  Fixed delayed transmission of AddressClaimed.
 *                               ESCAN00081349  Fixed check for legitimate values returned by GetAddress.
 *                               ESCAN00081605  Fixed warning in node index assignment.
 *                               ESCAN00081982  GetAddress is no longer called for NCA nodes.
 *                               ESCAN00075508  Added state change indications to NM.
 *                               ESCAN00075526  Startup delay is now only applied to addresses 128..247.
 *                               ESCAN00080681  Avoid claiming the same address for multiple internal nodes.
 *  1.00.00  2015-07-22  vismsr  ESCAN00075032  Added NvM interface, removed GetAddress callback.
 *                               ESCAN00080692  Avoid length check if DLC check in CanIf is active.
 *                               ESCAN00081432  Adapted to separate lists of internal and external nodes.
 *                               ESCAN00082084  Avoid all spontaneous AC transmissions and reaction to received AC.
 *                               ESCAN00083452  Fixed declaration of unused variable searchAlgorithm.
 *                               ESCAN00083512  Fixed detection of external nodes that are offline.
 *                               ESCAN00083543  Adapted NAME API function parameters.
 *                               ESCAN00083576  Fixed DET check for non-J1939 channels.
 *                               ESCAN00083677  Fixed NAME table cleanup if refresh time is disabled.
 *                               ESCAN00083886  Ignoring non-J1939 channels in bus-off handling functions.
 *  1.00.01  2015-09-06  vismsr  ESCAN00081981  Fixed handling of external node addresses.
 *                               ESCAN00083255  Fixed timer handling and mode reports.
 *                               ESCAN00083342  Fixed node restart after address loss.
 *                               ESCAN00083528  Fixed AC transmission after NAME change.
 *                               ESCAN00083582  Fixed DET check for CA PDU ID in TP API.
 *                               ESCAN00083584  Fixed NAME comparison of CommandedAddress.
 *                               ESCAN00084253  Added protection of accesses to current NAME tables.
 *                               ESCAN00084942  Fixed handling of CanIf translation table entries for external nodes.
 *  1.00.02  2015-12-17  vismsr  ESCAN00084911  Changed J1939Nm_SetAddress to restart nodes that are OFFLINE.
 *                               ESCAN00084934  Added check for duplicate NAME to SetName API.
 *                               ESCAN00085021  Fixed address translation table handling for commanded address changes.
 *                               ESCAN00085465  Fixed compiler warning about unused variable 'nodeIdx'.
 *                               ESCAN00085843  Fixed transmission of AC after CA.
 *                               ESCAN00086470  Changed J1939Nm_SetAddress to ignore NCA nodes.
 *  2.00.00  2016-03-14  vismsr  ESCAN00084692  Adapted to changed signature of RequestIndication API.
 *  2.01.00  2016-05-13  vistat  ESCAN00089379  Added check for invalid external node IDs and invalid PDU IDs.
 *                       vismsr  ESCAN00090015  Fixed type cast of initial node of NAME search.
 *  2.01.01  2016-07-13  vismsr  ESCAN00090439  Removed const qualifier from PduInfoType argument of StartOfReception.
 *  3.00.00  2017-05-12  visgsi  STORYC-578     Added Commanded Name Management support.
 *                       vismsr   -             Improved BusOff state and NM mode and state handling.
 *  3.00.01  2018-01-29  vismsr  ESCAN00098163  Fixed J1939Nm_GetNode for external nodes.
 *  4.00.00  2018-03-23  visgsi  STORYC-4018    Added check for J1939NmAcceptsCommandedName.
 *                               ESCAN00098372  Fixed address check of received NAME management messages.
 *                               ESCAN00098881  Fixed handling of broadcast NAME management messages.
 *  5.00.00  2018-05-09  vismsr  STORYC-4646    Implemented routing of AC and handling of address lookup tables.
 *                       visgsi  STORYC-4646    Implemented routing of CA and NM.
 *  5.00.01  2018-12-11  vismmu  ESCAN00095894  Fixed compiler warning about unused parameter in J1939Nm_RxIndication.
 *                       vismsr  ESCAN00100027  Fixed PB handling of NvM data.
 *                       vismmu  ESCAN00100214  Fixed mirroring of NM and CA.
 *                               ESCAN00100216  Fixed syntax error in J1939Nm_SetName.
 *                               ESCAN00100364  Fixed out of bounds access in J1939Nm_DynamicCheckAcCollision.
 *                               ESCAN00100366  Fixed routing of NM modes 5 and 6.
 *                               ESCAN00100630  Fixed reset of CanIf address table entries during network release.
 *                               ESCAN00100631  Fixed transmission of routed CAs.
 *                       vismsr  ESCAN00101512  Fixed compiler errors for gateways without shared channels.
 *  6.00.00  2019-04-16  vismsr  STORY-3856     Added support for external SetName and SetAddress.
 *                               STORY-10147    Deny retry of TP transmission.
 *                               ESCAN00101888  Fixed BusOff delay for channels without address arbitration.
 *                               ESCAN00102416  Fixed check for address configuration capability for CommandedAddress.
 *                               ESCAN00103337  Fixed channel lookup.
 *  6.00.01  2019-12-06  vismsr  PERMIL-1467    Fixed NvM status check.
 *                               ESCAN00103346  Fixed state reporting to NM Interface.
 *  6.00.02  2020-02-26  vismsr  ESCAN00104236  Fixed out-of-bounds access in J1939Nm_(Find|Check)NodeChannelByAddress.
 *  7.00.00  2021-07-16  viscnw  STORY-5070     Change to MISRA2012.
 *                       vismsr  PERMIL-1467    Fixed NvM status check.
 *                       viscnw  PERMIL-1571 	Performed silent analysis.
 *                       viscnw  PERMIL-2118    API Pattern and Code Metrics.
 *                       viscnw  PERMIL 2120    Added CDD.
 *                       viscnw  ESCAN00099389  Fixed invalid NAME change of external node after failed sequence.
 *                       vismsr  ESCAN00103346  Fixed state reporting to NM Interface.
 *                       viscnw  ESCAN00103739  Explicit cast of J1939Nm_NmAckCodeType.
 *                       vismmu  ESCAN00105202  Removed warning about unused variable channelState.
 *                       vismmu  ESCAN00109050  NAME management PDU blocked by DLC check.
 *                       viscnw  ESCAN00109219  Fixed SetName handling of external node.
 *                       viscnw  ESCAN00109329  NameManagement session is blocked waiting for the final address claim.
 *                       viscnw  ESCAN00109394  NACK message from figure A13 of SAEJ1939-81 is not sent.
 *                       vismmu  ESCAN00109518  Address Claim (AC) message missing after Name Management session.
 *                       viscnw  ESCAN00109519  Fixed forwarding of Cannot Claim Address message in a gateway usecase.
 *                       viscnw  ESCAN00109520  Disabled address arbitration of Gateway in shared address space.
 *                       viscnw  ESCAN00109602  Added missing leave command of exclusive area.
 *  7.00.01  2021-07-23  viscnw   -             Fixed Doxygen Marker.
 *  8.00.00  2022-01-13  vimmu   PERMIL-3566 	Solve limitations of J1939-22 CAN-FD.
 *                       viscnw  ESCAN00111094  Confirmation timeout of TxPdu is reached faster.
 *  8.00.01  2022-02-14  viscnw  ESCAN00111115  BETA version - the BSW module is in BETA state
 *  9.00.00  2022-04-13  viscnw  PERMIL-3199    Change ECU name fields including AAC bit
 *********************************************************************************************************************/

#if !defined (J1939NM_H)
# define J1939NM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

# include "J1939Nm_Cfg.h"
# include "J1939Nm_Types.h"

# include "J1939Nm_Lcfg.h"
# include "J1939Nm_PBcfg.h"

# include "ComStack_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define J1939NM_VENDOR_ID                      (30u)
# define J1939NM_MODULE_ID                      (34u)

/* AUTOSAR Specification version information */
# define J1939NM_AR_RELEASE_MAJOR_VERSION       (4u)
# define J1939NM_AR_RELEASE_MINOR_VERSION       (2u)
# define J1939NM_AR_RELEASE_REVISION_VERSION    (2u)

/* Vendor specific BSW module version information */
# define J1939NM_SW_MAJOR_VERSION               (9u)
# define J1939NM_SW_MINOR_VERSION               (0u)
# define J1939NM_SW_PATCH_VERSION               (0u)


/*
 * Development Error Detection
 */

/* ----- API service IDs ----- */
/*! Service ID: J1939Nm_Init() */
# define J1939NM_SID_INIT                       (0x01u)
/*! Service ID: J1939Nm_DeInit() */
# define J1939NM_SID_DEINIT                     (0x02u)
/*! Service ID: J1939Nm_GetVersionInfo() */
# define J1939NM_SID_GETVERSIONINFO             (0x03u)
/*! Service ID: J1939Nm_MainFunction() */
# define J1939NM_SID_MAINFUNCTION               (0x04u)
/*! Service ID: J1939Nm_NetworkRequest() */
# define J1939NM_SID_NETWORKREQUEST             (0x05u)
/*! Service ID: J1939Nm_NetworkRelease() */
# define J1939NM_SID_NETWORKRELEASE             (0x06u)
/*! Service ID: J1939Nm_GetState() */
# define J1939NM_SID_GETSTATE                   (0x0du)
/*! Service ID: J1939Nm_PassiveStartup() */
# define J1939NM_SID_PASSIVESTARTUP             (0x0fu)
/*! Service ID: J1939Nm_GetBusOffDelay() */
# define J1939NM_SID_GETBUSOFFDELAY             (0x10u)
/*! Service ID: J1939Nm_TxConfirmation() */
# define J1939NM_SID_TXCONFIRMATION             (0x40u)
/*! Service ID: J1939Nm_RxIndication() */
# define J1939NM_SID_RXINDICATION               (0x42u)
/*! Service ID: J1939Nm_CopyTxData() */
# define J1939NM_SID_COPYTXDATA                 (0x43u)
/*! Service ID: J1939Nm_CopyRxData() */
# define J1939NM_SID_COPYRXDATA                 (0x44u)
/*! Service ID: J1939Nm_TpRxIndication() */
# define J1939NM_SID_TPRXINDICATION             (0x45u)
/*! Service ID: J1939Nm_StartOfReception() */
# define J1939NM_SID_STARTOFRECEPTION           (0x46u)
/*! Service ID: J1939Nm_RequestIndication() */
# define J1939NM_SID_REQUESTINDICATION          (0x47u)
/*! Service ID: J1939Nm_TpTxConfirmation() */
# define J1939NM_SID_TPTXCONFIRMATION           (0x48u)
/*! Proprietary service ID: J1939Nm_InitMemory() */
# define J1939NM_SID_INITMEMORY                 (0x80u)
/*! Proprietary service ID: J1939Nm_BusOffEnd() */
# define J1939NM_SID_BUSOFFEND                  (0x81u)
/*! Proprietary service ID: J1939Nm_GetNode() */
# define J1939NM_SID_GETNODE                    (0x82u)
/*! Proprietary service ID: J1939Nm_GetFirstUnknownNameIdx() */
# define J1939NM_SID_GETFIRSTUNKNOWNNAMEIDX     (0x83u)
/*! Proprietary service ID: J1939Nm_GetLastNodeIdx() */
# define J1939NM_SID_GETLASTNODEIDX             (0x84u)
/*! Proprietary service ID: J1939Nm_FindNodeByName() */
# define J1939NM_SID_FINDNODEBYNAME             (0x85u)
/*! Proprietary service ID: J1939Nm_FindNodeByAddress() */
# define J1939NM_SID_FINDNODEBYADDRESS          (0x86u)
/*! Proprietary service ID: J1939Nm_FindNodeChannelByName() */
# define J1939NM_SID_FINDNODECHANNELBYNAME      (0x87u)
/*! Proprietary service ID: J1939Nm_SetName() */
# define J1939NM_SID_SETNAME                    (0x88u)
/*! Proprietary service ID: J1939Nm_SetAddress() */
# define J1939NM_SID_SETADDRESS                 (0x89u)
/*! Proprietary service ID: J1939Nm_FindNodeChannelByAddress() */
# define J1939NM_SID_FINDNODECHANNELBYADDRESS   (0x8au)
/*! Proprietary service ID: J1939Nm_CheckNodeChannelByAddress() */
# define J1939NM_SID_CHECKNODECHANNELBYADDRESS  (0x8bu)
/*! Proprietary service ID: J1939Nm_NvMInit_CurrentNodeAddresses() */
# define J1939NM_SID_NVMINIT_CURRENTNODEADDRESSES (0x8cu)
/*! Proprietary service ID: J1939Nm_NvMInit_CurrentNodeNames() */
# define J1939NM_SID_NVMINIT_CURRENTNODENAMES   (0x8du)
/*! Proprietary service ID: J1939Nm_EnableCommunication() */
# define J1939NM_SID_ENABLECOMMUNICATION        (0x90u)
/*! Proprietary service ID: J1939Nm_DisableCommunication() */
# define J1939NM_SID_DISABLECOMMUNICATION       (0x91u)
/*! Proprietary service ID: J1939Nm_CheckRemoteSleepIndication() */
# define J1939NM_SID_CHECKREMOTESLEEPINDICATION (0x92u)
/*! Proprietary service ID: J1939Nm_GetLocalNodeIdentifier() */
# define J1939NM_SID_GETLOCALNODEIDENTIFIER     (0x93u)
/*! Proprietary service ID: J1939Nm_GetNodeIdentifier() */
# define J1939NM_SID_GETNODEIDENTIFIER          (0x94u)
/*! Proprietary service ID: J1939Nm_GetPduData() */
# define J1939NM_SID_GETPDUDATA                 (0x95u)
/*! Proprietary service ID: J1939Nm_GetUserData() */
# define J1939NM_SID_GETUSERDATA                (0x96u)
/*! Proprietary service ID: J1939Nm_RepeatMessageRequest() */
# define J1939NM_SID_REPEATMESSAGEREQUEST       (0x97u)
/*! Proprietary service ID: J1939Nm_RequestBusSynchronization() */
# define J1939NM_SID_REQUESTBUSSYNCHRONIZATION  (0x98u)
/*! Proprietary service ID: J1939Nm_SetSleepReadyBit() */
# define J1939NM_SID_SETSLEEPREADYBIT           (0x99u)
/*! Proprietary service ID: J1939Nm_SetUserData() */
# define J1939NM_SID_SETUSERDATA                (0x9au)

/* ----- Error codes ----- */
/*! Proprietary development error code: No error occurred */
# define J1939NM_E_NO_ERROR                     (0x00u)
/*! Error code: An API was called while the module was uninitialized */
# define J1939NM_E_UNINIT                       (0x01u)
/*! Error code: The Init API was called twice */
# define J1939NM_E_REINIT                       (0x02u)
/*! Error code: An API service was called with a NULL pointer */
# define J1939NM_E_PARAM_POINTER                (0x03u)
/*! Error code: An API service was called with a wrong ID */
# define J1939NM_E_INVALID_PDU_SDU_ID           (0x04u)
/*! Error code: An API service was called with a wrong network handle */
# define J1939NM_E_INVALID_NETWORK_ID           (0x05u)
/*! Error code: An API was called with an unsupported PGN */
# define J1939NM_E_INVALID_PGN                  (0x06u)
/*! Error code: An API was called with an illegal priority */
# define J1939NM_E_INVALID_PRIO                 (0x07u)
/*! Error code: An API was called with an illegal node address */
# define J1939NM_E_INVALID_ADDRESS              (0x08u)
/*! Error code: An API was called with an illegal node ID */
# define J1939NM_E_INVALID_NODE                 (0x09u)
/*! Error code: J1939Nm_Init called with invalid init structure */
# define J1939NM_E_INIT_FAILED                  (0x0au)
/*! Proprietary error code: An illegal PDU size was reported by CanIf */
# define J1939NM_E_INVALID_PDU_SIZE             (0x80u)
/*! Proprietary error code: Timeout of transmission confirmation callback */
# define J1939NM_E_TIMEOUT_TXCONF               (0x81u)
/*! Proprietary error code: An external node uses the same NAME as another node */
# define J1939NM_E_DUPLICATE_NAME               (0x82u)
/*! Proprietary error code: API not supported for external nodes */
# define J1939NM_E_EXTERNAL_NODE                (0x83u)
/*! Proprietary error code: An NvM initialization API was called in initialized state */
# define J1939NM_E_RUNNING                      (0x84u)
/*! Proprietary error code: A dummy API was called */
# define J1939NM_E_DUMMY_API                    (0x90u)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*============================================== J1939NM_START_SEC_CODE =============================================*/
# define J1939NM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  J1939Nm_InitMemory()
 **********************************************************************************************************************/
/*! \brief       Sets the global J1939Nm state to uninitialized.
 *  \details     -
 *  \pre         Module is not initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note       This function should be used if the J1939Nm is not initialized by startup code.
 **********************************************************************************************************************/
FUNC(void, J1939NM_CODE) J1939Nm_InitMemory(void);

/***********************************************************************************************************************
 *  J1939Nm_Init()
 **********************************************************************************************************************/
/*! \brief       Initializes the J1939 Network Management module.
 *  \details      -
 *  \param[in]   config          Pointer to configuration data structure.
 *  \pre         The module must be in the uninitialized state.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note       The config parameter is only required if the configuration is variant or changed at post-build time.
 *  \spec
 *    requires config == J1939Nm_Config_Ptr;
 *  \endspec
 **********************************************************************************************************************/
FUNC(void, J1939NM_CODE) J1939Nm_Init(P2CONST(J1939Nm_ConfigType, AUTOMATIC, J1939NM_PBCFG) config);

/***********************************************************************************************************************
 *  J1939Nm_DeInit()
 **********************************************************************************************************************/
/*! \brief       Resets the J1939 Network Management module to the uninitialized state.
 *  \details      -
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \note       The module is not truly shut down before all services and callback functions have terminated.
 **********************************************************************************************************************/
FUNC(void, J1939NM_CODE) J1939Nm_DeInit(void);

# if (J1939NM_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_GetVersionInfo()
 **********************************************************************************************************************/
/*! \brief        Returns the version information of this module.
 *  \details      -
 *  \param[out]   versionInfo     Pointer to the location where the version information shall be stored.
 *  \pre          The versionInfo parameter must not be NULL.
 *  \context      TASK|ISR
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       J1939NM_VERSION_INFO_API
 *  \trace        CREQ-110308
 **********************************************************************************************************************/
FUNC(void, J1939NM_CODE) J1939Nm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939NM_APPL_VAR) versionInfo);
# endif

/***********************************************************************************************************************
 *  J1939Nm_NetworkRequest()
 **********************************************************************************************************************/
/*! \brief       Request the network, since ECU needs to communicate on the bus.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Requesting of network has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different channels.
 *  \synchronous TRUE
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkRequest(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_NetworkRelease()
 **********************************************************************************************************************/
/*! \brief       Release the network, since ECU does not have to communicate on the bus.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Releasing of network has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   TRUE for different channels.
 *  \synchronous FALSE
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_NetworkRelease(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_GetState()
 **********************************************************************************************************************/
/*! \brief       Returns the state and the mode of the network management.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[out]  stateP          Pointer where state of the network management shall be copied to.
 *  \param[out]  modeP           Pointer where the mode of the network management shall be copied to.
 *  \return      E_OK:           No error
 *               E_NOT_OK:       Getting of NM state has failed.
 *  \pre         The pointer parameters must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetState(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                    CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_VAR) stateP,
                                                    CONSTP2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_VAR) modeP);


/**********************************************************************************************************************
 *  NAME management API
 *********************************************************************************************************************/

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_GetNode()
 **********************************************************************************************************************/
/*! \brief       Copies the NAME, the virtual address, and the bus address of the internal or external node designated by
 *               node ID and channel.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \param[in]   nodeId          Node ID.
 *  \param[in]   external        TRUE: Look for an external node. FALSE: Look for an internal node.
 *  \param[out]  name            Pointer to an array of 8 bytes for the 64-bit NAME. If a NULL pointer is provided, the
 *                               NAME will not be copied.
 *  \param[out]  virtAddr        Virtual address of the node, used in MetaData.
 *  \param[out]  busAddr         Actual address of the node as seen on the bus.
 *  \return      E_OK:           The node lookup was successful.
 *               E_NOT_OK:       The node could not be located, e.g. because the provided nodeId or channel are wrong,
 *                               the node is not of the required type (internal/external), the node is not attached to
 *                               the channel, or the node is an external node and currently not online.
 *  \pre         The pointer parameters apart from name must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetNode(NetworkHandleType channel, uint16 nodeId, boolean external,
                                                   P2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) name,
                                                   P2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) virtAddr,
                                                   P2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) busAddr);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_GetFirstUnknownNameIdx()
 **********************************************************************************************************************/
/*! \brief       Returns the node ID of the first external node with an unknown NAME.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \return      Index of first external node with an unknown NAME. If no such nodes are configured, 65535 will be
 *               returned.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(uint16, J1939NM_CODE) J1939Nm_GetFirstUnknownNameIdx(NetworkHandleType channel);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_GetLastNodeIdx()
 **********************************************************************************************************************/
/*! \brief       Returns the ID of the last currently available external node attached to the given channel.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \return      Index of the last external node available on the given channel.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(uint16, J1939NM_CODE) J1939Nm_GetLastNodeIdx(NetworkHandleType channel);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_FindNodeByName()
 **********************************************************************************************************************/
/*! \brief       Looks for an internal or external node attached to the provided channel that matches the provided name
 *               and mask. External nodes are only detected if they sent an AddressClaimed or CannotClaimAddress after
 *               the last request for AC.
 *               Providing a 0 for the node ID will find the first matching node. To implement an iterative search, the
 *               node ID provided to the next call should be set to the successor of the last found node.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \param[in]   external        TRUE: Look for an external node. FALSE: Look for an internal node.
 *  \param[in]   name            Pointer to an array of 8 bytes containing the 64-bit NAME to be looked for.
 *  \param[in]   mask            Pointer to an array of 8 bytes to define the relevant name parts for the search. Only
 *                               those bits of the name are checked which are set to 1 in the mask.
 *  \param[out]  nodeId          The first node ID to look for. On success, the value is changed to the found node ID.
 *  \return      E_OK:           The node lookup was successful.
 *               E_NOT_OK:       No suitable node was found, or the provided channel does not exist.
 *  \pre         The pointer parameters must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_FindNodeByName(NetworkHandleType channel, boolean external,
                                                          P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) name,
                                                          P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) mask,
                                                          P2VAR(uint16, AUTOMATIC, J1939NM_APPL_VAR) nodeId);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_FindNodeByAddress()
 **********************************************************************************************************************/
/*! \brief       Looks for an internal or external node that matches the provided virtual address. External nodes are
 *               only detected if they sent an AddressClaimed or CannotClaimAddress after the last request for AC.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \param[in]   external        TRUE: Look for an external node. FALSE: Look for an internal node.
 *  \param[in]   virtAddr        Virtual address of the wanted node.
 *  \param[out]  nodeId          Found node ID.
 *  \return      E_OK:           The node lookup was successful.
 *               E_NOT_OK:       No suitable node was found, or the provided channel does not exist.
 *  \pre         The pointer parameter must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_FindNodeByAddress(NetworkHandleType channel, boolean external,
                                                             uint8 virtAddr,
                                                             P2VAR(uint16, AUTOMATIC, J1939NM_APPL_VAR) nodeId);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_FindNodeChannelByName()
 **********************************************************************************************************************/
/*! \brief       Looks for the channel to which an external node with the provided NAME is attached. The function takes
 *               the channel on which the NAME is visible and returns the channel on which the corresponding external
 *               node actually resides. It returns E_NOT_OK for internal nodes and for external nodes that have not sent
 *               an AddressClaimed or CannotClaimAddress after the last request for AC.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \param[in]   name            NAME of the wanted external node.
 *  \param[out]  nodeChannel     Found channel.
 *  \return      E_OK:           The channel lookup was successful.
 *               E_NOT_OK:       The external node was not found, the NAME belongs to an internal node, or the provided
 *                               channel does not exist.
 *  \pre         The pointer parameters must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE)
J1939Nm_FindNodeChannelByName(NetworkHandleType channel, P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) name,
                              P2VAR(NetworkHandleType, AUTOMATIC, J1939NM_APPL_VAR) nodeChannel);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_SetName()
 **********************************************************************************************************************/
/*! \brief       Sets a new NAME for the designated node. The node will claim the new NAME afterwards.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \param[in]   nodeId          Node ID.
 *  \param[in]   external        TRUE: Change NAME of an external node using NAME management messages.
 *                               FALSE: Change NAME of an internal node.
 *  \param[in]   name            Pointer to an array of 8 bytes containing the new 64-bit NAME.
 *  \return      E_OK:           The NAME change was successful.
 *               E_NOT_OK:       The NAME could not be changed, e.g. because the provided nodeId or channel were wrong,
 *                               or the node is an external node.
 *  \pre         The pointer parameter must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetName(NetworkHandleType channel, uint16 nodeId, boolean external,
                                                   P2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) name);
# endif

# if (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  J1939Nm_SetAddress()
 **********************************************************************************************************************/
/*! \brief       Sets a new address for the designated node. The node will claim the new address afterwards.
 *  \details      -
 *  \param[in]   channel         Communication channel.
 *  \param[in]   nodeId          Node ID.
 *  \param[in]   external        TRUE: Change address of an external node using CommandedAddress.
 *                               FALSE: Change address of an internal node.
 *  \param[in]   busAddr         The new actual address of the node.
 *  \return      E_OK:           The address change was successful.
 *               E_NOT_OK:       The address could not be changed, e.g. because the provided nodeId or channel were
 *                               wrong, or the node is an external node.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetAddress(NetworkHandleType channel, uint16 nodeId, boolean external,
                                                      uint8 busAddr);
# endif

# if ((J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON))
/***********************************************************************************************************************
 *  J1939Nm_FindNodeChannelByAddress()
 **********************************************************************************************************************/
/*! \brief       Looks for the channel to which an external node with the provided virtual address is attached. The
 *               function takes the channel on which the address is visible and returns the channel on which the
 *               corresponding external node actually resides. It returns E_NOT_OK for internal nodes and for external
 *               nodes that have not sent an AddressClaimed or CannotClaimAddress after the last request for AC.
 *  \details      -
 *  \param[in]   routedChannel   Communication channel on which the node is also visible.
 *  \param[in]   virtAddr        Virtual address of the wanted external node.
 *  \param[out]  attachedChannel Communication channel to which the node is attached.
 *  \return      E_OK:           The channel lookup was successful.
 *               E_NOT_OK:       The external node was not found, the address belongs to an internal node, or the
 *                               provided channel does not exist.
 *  \pre         The pointer parameter must not be NULL.
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_NAME_MANAGEMENT_SUPPORT or J1939NM_GATEWAY_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE)
J1939Nm_FindNodeChannelByAddress(NetworkHandleType routedChannel, uint8 virtAddr,
                                 P2VAR(NetworkHandleType, AUTOMATIC, J1939NM_APPL_VAR) attachedChannel);
# endif

# if ((J1939NM_CA_PG_SUPPORT == STD_ON) || (J1939NM_GATEWAY_SUPPORT == STD_ON) || (J1939NM_NAME_MANAGEMENT_SUPPORT == STD_ON))
/***********************************************************************************************************************
 *  J1939Nm_CheckNodeChannelByAddress()
 **********************************************************************************************************************/
/*! \brief       Checks whether an external node with the provided virtual address which is attached to the provided
 *               'attachedChannel' is visible on the provided 'routedChannel'. If the NULL address is provided, the
 *               function checks whether there is a routing relation from the provided 'attachedChannel' to the provided
 *               'routedChannel'. The function returns FALSE for internal nodes and for external nodes that have not sent
 *               an AddressClaimed or CannotClaimAddress after the last request for AC or which are not visible on both
 *               channels.
 *  \details      -
 *  \param[in]   attachedChannel Communication channel to which the node is attached.
 *  \param[in]   virtAddr        Virtual address of the external node.
 *  \param[in]   routedChannel   Communication channel on which the node is also visible.
 *  \return      TRUE:           The node is visible on both channels.
 *               FALSE:          The provided virtual address was not found or belongs to an internal node, or the
 *                               provided channels do not exist, or the node is not visible on both channels.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      J1939NM_CA_PG_SUPPORT or J1939NM_GATEWAY_SUPPORT or J1939NM_NAME_MANAGEMENT_SUPPORT
 *  \trace       CREQ-110502
 **********************************************************************************************************************/
FUNC(boolean, J1939NM_CODE) J1939Nm_CheckNodeChannelByAddress(NetworkHandleType attachedChannel, uint8 virtAddr,
                                                              NetworkHandleType routedChannel);
# endif


/**********************************************************************************************************************
 *  Dummy Functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  J1939Nm_CheckRemoteSleepIndication()
 **********************************************************************************************************************/
/*! \brief       Check if remote sleep indication takes place or not.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmRemoteSleepIndPtr  Pointer where check result of remote sleep indication shall be copied to.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Checking of remote sleep indication bits has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE)
J1939Nm_CheckRemoteSleepIndication(CONST(NetworkHandleType, AUTOMATIC) channel,
                                   CONSTP2VAR(boolean, AUTOMATIC, J1939NM_APPL_VAR) nmRemoteSleepIndPtr);

/***********************************************************************************************************************
 *  J1939Nm_DisableCommunication()
 **********************************************************************************************************************/
/*! \brief       Disable the NM PDU transmission ability.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Releasing of network has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_DisableCommunication(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_EnableCommunication()
 **********************************************************************************************************************/
/*! \brief       Enable the NM PDU transmission ability.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Releasing of network has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_EnableCommunication(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_GetLocalNodeIdentifier()
 **********************************************************************************************************************/
/*! \brief       Get node identifier configured for the local node.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmNodeIdPtr     Pointer where node identifier of the local node shall be copied to.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Getting of the node identifier of the local node has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE)
J1939Nm_GetLocalNodeIdentifier(CONST(NetworkHandleType, AUTOMATIC) channel,
                               CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmNodeIdPtr);

/***********************************************************************************************************************
 *  J1939Nm_GetNodeIdentifier()
 **********************************************************************************************************************/
/*! \brief       Get node identifier out of the last successfully received NM-message.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmNodeIdPtr     Pointer where node identifier out of the last successfully received NM-message
 *                               shall be copied to.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Getting of the node identifier out of the last received NM-message has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE)
J1939Nm_GetNodeIdentifier(CONST(NetworkHandleType, AUTOMATIC) channel,
                          CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmNodeIdPtr);

/***********************************************************************************************************************
 *  J1939Nm_GetPduData()
 **********************************************************************************************************************/
/*! \brief       Get node identifier out of the last successfully received NM-message.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmPduDataPtr    Pointer where NM PDU shall be copied to.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Getting of NM PDU data has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetPduData(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                      CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmPduDataPtr);

/***********************************************************************************************************************
 *  J1939Nm_GetUserData()
 **********************************************************************************************************************/
/*! \brief       Get user data out of the last successfully received NM message.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmUserDataPtr   Pointer where user data out of the last successfully received NM message shall be copied
 *                               to.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Getting of user data has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetUserData(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                       CONSTP2VAR(uint8, AUTOMATIC, J1939NM_APPL_VAR) nmUserDataPtr);

/***********************************************************************************************************************
 *  J1939Nm_PassiveStartUp()
 **********************************************************************************************************************/
/*! \brief       Passive startup of the NM. It triggers the transition from Bus-Sleep Mode to the
 *               Network Mode without requesting the network.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Passive startup of network management has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_PassiveStartUp(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_RepeatMessageRequest()
 **********************************************************************************************************************/
/*! \brief       Request a Repeat Message Request to be transmitted next on the bus.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Repeat Message Request has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_RepeatMessageRequest(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_RequestBusSynchronization()
 **********************************************************************************************************************/
/*! \brief       Request bus synchronization.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Requesting of bus synchronization has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_RequestBusSynchronization(CONST(NetworkHandleType, AUTOMATIC) channel);

/***********************************************************************************************************************
 *  J1939Nm_SetSleepReadyBit()
 **********************************************************************************************************************/
/*! \brief       Set the NM Coordinator Sleep Ready bit in the Control Bit Vector.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmSleepReadyBit  Value written to ReadySleep Bit in CBV.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Writing of remote sleep indication bit has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetSleepReadyBit(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                            CONST(boolean, AUTOMATIC) nmSleepReadyBit);

/***********************************************************************************************************************
 *  J1939Nm_SetUserData()
 **********************************************************************************************************************/
/*! \brief       Set user data for NM messages transmitted next on the bus.
 *  \details      -
 *  \param[in]   channel         Identification of the NM-channel.
 *  \param[in]   nmUserDataPtr   Pointer where the user data for the next transmitted NM message shall be copied from.
 *  \return      E_OK:           No error,
 *               E_NOT_OK:       Setting of user data has failed.
 *  \pre          -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function is not yet implemented, and returns always E_NOT_OK.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetUserData(CONST(NetworkHandleType, AUTOMATIC) channel,
                                                       CONSTP2CONST(uint8, AUTOMATIC, J1939NM_APPL_DATA) nmUserDataPtr);

# define J1939NM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*============================================== J1939NM_STOP_SEC_CODE ==============================================*/

/***********************************************************************************************************************
 *  EXCLUSIVE AREA DEFINITION
 **********************************************************************************************************************/
/*!
 * \exclusivearea  J1939NM_EXCLUSIVE_AREA_RXPDULOCK
 *                 Ensures the consistency of the CommandedAddress state.
 * \protects       J1939Nm_CaMgmt
 * \usedin         J1939Nm_InternalStartOfReception, J1939Nm_InternalSetAddressOfExternalNode
 * \exclude        -
 * \length         SHORT Only a few flags are checked. No calls to functions.
 * \endexclusivearea
 */

/*!
 * \exclusivearea  J1939NM_EXCLUSIVE_AREA_TXPDULOCK
 *                 Ensures the consistency of the Tx PDU state.
 * \protects       J1939Nm_TxPduState
 * \usedin         J1939Nm_InternalSendAc, J1939Nm_InternalSendExtNodeAc, J1939Nm_InternalSendNm
 * \exclude        J1939Nm_DynamicHandleNm, J1939Nm_DynamicNmRequestIndication, J1939Nm_InternalProcessNmQueue
 * \length         SHORT Only a few flags are checked. No calls to functions.
 * \endexclusivearea
 */

/*!
 * \exclusivearea  J1939NM_EXCLUSIVE_AREA_NAMELOCK
 *                 Ensures the consistency of current NAME table.
 * \protects       J1939Nm_NodeName
 * \usedin         J1939Nm_InternalSendExtNodeAc, J1939Nm_InternalUpdateName, J1939Nm_InternalCheckUniquenessOfNameInInternalNodes,
 *                 J1939Nm_InternalCheckUniquenessOfNameInExternalNodes, J1939Nm_InternalNmSendName, J1939Nm_InternalNmSendSetPending,
 *                 J1939Nm_InternalNmHandleSetPendingName, J1939Nm_InternalNmHandleAdoptPendingName, J1939Nm_InternalTpRxIndication,
 *                 J1939Nm_InternalGetExternalNode, J1939Nm_InternalGetInternalNode, J1939Nm_InternalFindExternalNodeByName,
 *                 J1939Nm_InternalFindInternalNodeByName, J1939Nm_InternalFindNodeChannelByName, J1939Nm_InternalSetAddressOfExternalNode,
 *                 J1939Nm_InternalAcHandlingOfConflictingExtNodeAddress, J1939Nm_InternalAcHandlingOfAlreadyRegisteredName,
 *                 J1939Nm_InternalAcHandlingOfNotYetRegisteredName, J1939Nm_DynamicInit, J1939Nm_DynamicCheckAcCollision,
 *                 J1939Nm_DynamicAddressClaimedNotification, J1939Nm_InternalSendAc, J1939Nm_InternalCheckAcCollisionOfTransmittedAc
 * \exclude        All functions
 * \length         SHORT Only a few flags are checked.
 * \endexclusivearea
 */

/*!
 * \exclusivearea  J1939NM_EXCLUSIVE_AREA_NMQUEUELOCK
 *                 Ensures the consistency of the NmQueue.
 * \protects       J1939Nm_NmQueue
 * \usedin         J1939Nm_InternalUpdateNmQueue, J1939Nm_InternalProcessNmQueue
 * \exclude        J1939Nm_DynamicHandleNm, J1939Nm_InternalSetNameOfExternalNode
 * \length         SHORT Only a few flags are checked.
 * \endexclusivearea
 */

/*!
 * \exclusivearea  J1939NM_EXCLUSIVE_AREA_NMACTIVELOCK
 *                 Ensures the consistency of NameManagement state.
 * \protects       J1939_NmMgmt
 * \usedin         J1939Nm_InternalNmSendName, J1939Nm_InternalNmSendAck, J1939Nm_InternalNmHandleSetPendingName,
 *                 J1939Nm_InternalNmHandleAdoptPendingName
 * \exclude        J1939Nm_DynamicHandleNm, J1939Nm_DynamicNmRequestIndication
 * \length         SHORT Only a few flags are checked.
 * \endexclusivearea
 */

#endif /* J1939NM_H */

/**********************************************************************************************************************
 *  END OF FILE: J1939Nm.h
 *********************************************************************************************************************/
