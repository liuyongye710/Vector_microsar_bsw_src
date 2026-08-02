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
/*!       \file   FvM.h
 *        \brief  FVM header file
 *
 *      \details  This is the header file of the Freshness Value Manager.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2016-11-29  vishho
 *  01.01.00  2017-02-08  vishho  FEATC-1154: FvM support additional TMC Features
 *  01.01.01  2017-02-14  vishho  ESCAN00093994: Rest Counter Rx Sync not functional
 *  01.02.00  2017-02-20  vishho  FEATC-1186: Release TMC Security Modules: Freshness Handling (FvM)
 *            2017-02-28  visfrm  FEATC-1186: Release TMC Security Modules: Freshness Handling (FvM)
 *            2017-03-07  vishho  ESCAN00094274: FvM does not check the ClearAcceptanceWindow above boundary
 *  02.00.00  2017-05-04  vishho  STORYC-764: SecOC Start Timing in FvM
 *            2017-05-09  vishho  STORYC-766: Inform FV overflow
 *            2017-05-10  visfrm  STORYC-765: Overflow of Trip/Reset/Message Counter Behavior
 *            2017-05-12  vishho  ESCAN00094804: Compiler error: GetFreshnessValueLayoutInfoPreviousIdxOfRxFreshnessValueInfo not defined
 *            2017-05-16  visfrm  STORYC-163: API Pattern, ReviewHelper, MISRA for FvM
 *  02.01.00  2017-06-12  vishho  STORYC-161: 100% C/DC for FvM implementation
 *  02.02.00  2017-07-13  vishho  STORYC-1700: Inform FV overflow also in case of Tx Messages
 *            2017-07-18  vishho  STORYC-1556: FvM_Jaspar - transmit messages with default Trip/Reset counter, before SyncMessage is received
 *  02.03.00  2017-08-09  vishho  STORYC-2127: Cleanup FvM Backlog
 *  02.03.01  2017-10-11  vishho  ESCAN00096921: Freshness Value calculation fails on Rx side if Reset Counter reaches Max Value
 *  03.00.00  2017-11-20  vishho  STORYC-3182: Allow the reception of the same sync message
 *  03.01.00  2018-01-25  vishho  STORYC-2716: Support Freshness Value Layout for Ethernet.
 *  03.02.00  2018-02-19  vishho  ESCAN00098437: Compiler warning: 'SecOCFreshnessValueLength' : unreferenced formal parameter
 *            2018-02-21  vishho  STORYC-3903: Add Development Mode for Sync Messages in FvM
 *            2018-03-09  vishho  STORYC-2715: Support TripCounter storage in NvM
 *  03.02.01  2018-03-21  vishho  ESCAN00098859: Freshness values not initialized after wrap around of Trip Counter
 *            2018-03-23  vishho  ESCAN00098886: Message Counter is incremented (carry processing) on Rx Side although the message counter reached its max value
 *            2018-03-26  vishho  ESCAN00098912: After the start up time expired the FvM returns E_BUSY instead of E_NOT_OK
 *  04.00.00  2018-04-18  vishho  STORYC-4520: Use Default Freshness if out of Sync after start acceptance time
 *            2018-04-24  vishho  STORYC-4522: Store Trip Counter for normal Jaspar in NvM
 *  04.00.01  2018-05-14  vishho  ESCAN00099405: Message counter overflow occurs
 *  04.01.00  2018-05-16  vishho  STORYC-4521: Trip Counter Flag
 *            2018-05-23  vishho  ESCAN00099486: Compiler error: NvM_WriteBlock cannot be found
 *            2018-05-24  vishho  ESCAN00099492: Compiler error: FvM_GetSyncState undefined assuming extern returning int
 *            2018-05-23  visssg  STORYC-4402: MISRA-C:2012 FvM
 *  05.00.00  2018-09-14  visbbk  ESCAN00100582: Incorrect Reset Counter can be stored for received message during start up
 *            2018-09-18  vishho  STORYC-5056: [FVM_Jaspar] API to Restart VerfyStart timing - without resetting the freshness values
 *            2018-09-20  vishho  ESCAN00100497: Smaller TripCounter from SyncMessage is stored if FVM development mode is active
 *            2018-09-20  vishho  ESCAN00100441: MISRA deviation: MISRA-C:2012 Rule 8.5 FvM_VerificationStatusCallout
 *            2018-09-20  vishho  ESCAN00100442: MISRA deviation: MISRA-C:2012 Rule 2.2
 *            2018-09-20  visbbk  STORYC-6127: FvM: Report diagnostic event, if no TripResetSyncMessage is received
 *  05.01.00  2018-10-10  visbbk  STORYC-6547: [SEC] Suppress sending of Secured PDUs during startup
 *  05.01.01  2019-02-11  vishho  ESCAN00102042: Memory is overwritten if TripFlags are used
 *            2019-02-11  visbbk  ESCAN00101945: Synchronized message reception timeout is not reloaded
 *  05.01.02  2019-03-19  vishho  ESCAN00102524: FvM can not always provide a freshness value during startup
 *            2019-03-19  vishho  ESCAN00102531: Plus one Sync try is not considered if Reset Flag Bit size is one
 *  06.00.00  2019-05-20  vishho  STORYC-7255: Fvm_Jaspar: inform TripCounterMaxReached for Rx usecase without ResetCounter
 *  06.01.00  2019-06-24  visssg  STORYC-8180: Do not store unauthenticated freshness values during startup time
 *            2019-06-26  visssg  STORYC-8195: FvM: Development Mode for Ethernet use case
 *  06.02.00  2019-08-13  vishho  COM-93  Handle NVM read errors for reading the stored TripCounter
 *  07.00.00  2019-08-21  vishho  COM-963 [SEC] FvM Master / Slave for Mazda Step 1
 *            2019-10-31  vishho  COM-990 Make FvM_ResetTripAndResetCounter usable if Trip counter is not saved in NvM
 *  07.01.00  2019-11-26  vishho  ESCAN00104842: FvM accepts old message counter if message counter reached max value
 *            2019-11-27  vishho  COM-1226 FvM return E_BUSY in case of same Trip/ResetCounter
 *  07.02.00  2020-01-22  vishho  COM-1295 Bugfix FVM Master
 *  08.00.00  2020-05-27  visssg  COM-1520 Support Helix QAC 2019-2
 *  09.00.00  2020-10-01  visbbk  COM-1682 Trip and Reset Counter in separate messages
 *            2020-11-18  vishho  COM-2018: Remove the AUTHOR IDENTIY
 *            2020-11-20  vismvi  ESCAN00107679: Misbehavior of a memcopy function under certain conditions
 *  10.00.00  2020-12-11  vismvi  COM-1947 Support PF4_PostBuildSelectable and PBL
 *            2021-01-11  vismvi  COM-2234 Support FVM_LOCAL_INLINE
 *  10.00.01  2021-02-24  vishho  ESCAN00108675: Compiler error: A Post Build Loadable configuration with NOT all Use Cases does not compile.
 *********************************************************************************************************************/

#if !defined (FVM_H)
# define FVM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "FvM_Cfg.h"
# include "FvM_Lcfg.h"
# include "FvM_PBcfg.h"
# include "SecOC_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define FVM_VENDOR_ID                           30u
# define FVM_MODULE_ID                           255u

/* AUTOSAR Software specification version information */
# define FVM_AR_RELEASE_MAJOR_VERSION            4u
# define FVM_AR_RELEASE_MINOR_VERSION            3u
# define FVM_AR_RELEASE_REVISION_VERSION         0u

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define FVM_SW_MAJOR_VERSION                    10u
# define FVM_SW_MINOR_VERSION                    0u
# define FVM_SW_PATCH_VERSION                    1u

# define FVM_INSTANCE_ID_DET                     0u

/* ----- API service IDs ----- */
# define FVM_SID_INIT                            0x00u  /* !< Service ID: FvM_Init() */
# define FVM_SID_GET_VERSION_INFO                0x10u  /* !< Service ID: FvM_GetVersionInfo() */
# define FVM_SID_GET_RX_FRESHNESS                0x11u  /* !< Service ID: SecOC_GetRxFreshness() */
# define FVM_SID_GET_TX_FRESHNESS                0x12u  /* !< Service ID: SecOC_GetTxFreshnessTruncData() */
# define FVM_SID_TX_FRESHNESS_CONFIRMATION       0x13u  /* !< Service ID: FvM_TxFreshnessConfirmation() */
# define FVM_SID_VERIFICATION_STATUS_CALLOUT     0x14u  /* !< Service ID: FvM_VerificationStatusCallout() */
# define FVM_SID_DEINIT                          0x15u  /* !< Service ID: FvM_DeInit() */
# define FVM_SID_SET_DEVELOPMENT_MODE            0x50u  /* !< Service ID: FvM_SetDevelopmentMode() */
# define FVM_SID_RESET_TRIP_AND_RESET_COUNTER    0x16u  /* !< Service ID: FvM_ResetTripAndResetCounter() */
# define FVM_SID_FVM_RESTART_START_UP_ACCEPTANCE_TIME 0x17u     /* !< Service ID: FvM_RestartStartUpAcceptanceTime() */


/* ----- Error codes ----- */
# define FVM_E_NO_ERROR                          0x00u  /* !< used to check if no error occurred - use a value unequal to any error code */
# define FVM_E_PARAM_CONFIG                      0x0Au  /* !< Error code: API service FvM_Init() called with wrong parameter */
# define FVM_E_PARAM                             0x0Bu  /* !< Error code: API service called with wrong parameter */
# define FVM_E_PARAM_POINTER                     0x0Cu  /* !< Error code: API service used with invalid pointer parameter (NULL) */
# define FVM_E_UNINIT                            0x10u  /* !< Error code: API service used without module initialization */
# define FVM_E_ALREADY_INITIALIZED               0x11u  /* !< Error code: The service FvM_Init() is called while the module is already initialized */
# define FVM_E_INVALID_REQUEST                   0x12u  /* !< Error code: Invalid request */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# if(FVM_USE_INIT_POINTER == STD_ON)
#  define FVM_START_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
extern P2CONST(FvM_ConfigType, FVM_VAR_ZERO_INIT, FVM_PBCFG) FvM_ConfigDataPtr;
#  define FVM_STOP_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FVM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  FvM_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, FVM_CODE) FvM_InitMemory(void);

/**********************************************************************************************************************
  FvM_DeInit
**********************************************************************************************************************/
/*! \brief       DeInitialization function
 *  \details     This function sets the module state to uninitialized.
 *  \trace       CREQ-117899
 *  \pre         Interrupts are disabled.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
**********************************************************************************************************************/
FUNC(void, FVM_CODE) FvM_DeInit(void);

/**********************************************************************************************************************
 * FvM_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module FvM. It initializes all variables and sets the module state to
 *               initialized.
 *  \param[in]   ConfigPtr               Configuration structure for initializing the module
 *  \trace       CREQ-117898
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         FvM_InitMemory has been called unless FvM_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, FVM_CODE) FvM_Init(P2CONST(FvM_ConfigType, AUTOMATIC, FVM_PBCFG) ConfigPtr);

# if (FVM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  FvM_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     FvM_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      FVM_VERSION_INFO_API
 *********************************************************************************************************************/
FUNC(void, FVM_CODE) FvM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FVM_APPL_VAR) versioninfo);
# endif


# if (FVM_LATESTTRIPCOUNTERWITHOUTRESETCOUNTER == STD_ON)
/**********************************************************************************************************************
 *  FvM_TripCounterReadErrorDetected()
 *********************************************************************************************************************/
/*! \brief       Reports read error of NVM
 *  \details     FvM_TripCounterReadErrorDetected() reports that a NVM read error occurred and the stored TripCounter
                 can not be read.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      FVM_LATESTTRIPCOUNTERWITHOUTRESETCOUNTER
 *********************************************************************************************************************/
FUNC(void, FVM_CODE) FvM_TripCounterReadErrorDetected(void);
# endif


# if (FVM_STARTUPCYCLECOUNTER == STD_ON)
/**********************************************************************************************************************
  FvM_RestartStartUpAcceptanceTime
**********************************************************************************************************************/
/*!
 * \brief      Restarts the Start Up Acceptance Time.
 * \details    -
 * \pre        -
 * \context    TASK|ISR2
 * \synchronous TRUE
 * \reentrant  FALSE
 * \config     FVM_STARTUPCYCLECOUNTER
 */
FUNC(void, FVM_CODE) FvM_RestartStartUpAcceptanceTime(void);
# endif

# if(FVM_DEVMODEENABLED == STD_ON)
/***********************************************************************************************************************
 *  FvM_SetDevelopmentMode()
 **********************************************************************************************************************/
/*!
 * \brief      Enables/Disables the development mode.
 * \details    -
 * \param[in]  enableDevMode        TRUE  - Development Mode is enabled.
 *                                  FALSE - Development Mode is disabled
 * \pre        -
 * \context    TASK|ISR2
 * \synchronous TRUE
 * \reentrant  FALSE
 * \config     FVM_DEVMODEENABLED
 * \trace CREQ-151254
 */
FUNC(void, FVM_CODE) FvM_SetDevelopmentMode(boolean enableDevMode);
# endif

# if (FVM_LATESTTRIPCOUNTER  == STD_ON)
/***********************************************************************************************************************
 *  FvM_ResetTripAndResetCounter()
 **********************************************************************************************************************/
/*!
 * \brief      Resets the Trip And the Reset Counter
 * \details    -
 * \pre        -
 * \context    TASK|ISR2
 * \synchronous TRUE
 * \reentrant  FALSE
 * \config     Normal Trip Counter use case must be used.
 */
FUNC(void, FVM_CODE) FvM_ResetTripAndResetCounter(void);
# endif

# if(FVM_TXFRESHNESSVALUEINFO == STD_ON)
/**********************************************************************************************************************
 *  SecOC_SPduTxConfirmation()
 *********************************************************************************************************************/
/*! \brief       Called to indicate the successful initiated transmission.
 *  \details     SecOC_SPduTxConfirmation() is called by the SecOC to indicate that a transmission was successful initiated.
 *  \param[in]   SecOCFreshnessValueID           fershness value id.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE, for different freshness value ids.
 *  \synchronous TRUE
 *  \config      FVM_TXFRESHNESSVALUEINFO
 */
# endif

/***********************************************************************************************************************
 *  SecOC_GetTxFreshnessTruncData()
 **********************************************************************************************************************/
/*!
 * \brief          Getter for freshness values on transmission side.
 * \details        This interface is used by the SecOC to obtain the current freshness value.
 * \param[in]      SecOCFreshnessValueID      Holds the identifier of the freshness value.
 * \param[out]     SecOCFreshnessValue        Holds the current freshness value.
 * \param[in,out] SecOCFreshnessValueLength Holds the length of the provided freshness in bits.
 * \param[out]     SecOCTruncatedFreshnessValue Holds the truncated freshness to be included into the Secured I-PDU.
 * \param[in,out] SecOCTruncatedFreshnessValueLength  Provides the truncated freshness length configured for this freshness.
 * \pre            -
 * \return         Std_ReturnType
 *                 E_OK:     request successful
 *                 E_NOT_OK: request failed, a freshness value cannot be provided due to
 *                           general issues for freshness or this FreshnessValueId.
 *                 E_BUSY:   The freshness information can temporarily not be provided
 * \context        TASK
 * \reentrant      TRUE, for different freshness value ids.
 * \synchronous    TRUE
 * \config         FVM_TXFRESHNESSVALUEINFO
 */

/***********************************************************************************************************************
 *  SecOC_GetRxFreshness()
 **********************************************************************************************************************/
/*!
 * \brief      Getter for freshness values on reception side.
 * \details    This interface is used by the SecOC to obtain the current freshness value.
 * \param[in]  SecOCFreshnessValueID      Holds the identifier of the freshness value.
 * \param[in]  SecOCTruncatedFreshnessValue Holds the truncated freshness value that was contained in the Secured I-PDU.
 * \param[in]  SecOCTruncatedFreshnessValueLength  Holds the length in bits of the truncated freshness value.
 * \param[in]  SecOCAuthVerifyAttempts     Holds the number of authentication verify attempts of this PDU since the last reception.
 *                                         The value is 0 for the first attempt and incremented on every unsuccessful verification attempt.
 * \param[out]     SecOCFreshnessValue         Holds the number of authentication verify attempts of this PDU since the last reception.
 *                                             The value is 0 for the first attempt and incremented on every unsuccessful verification attempt.
 * \param[in,out] SecOCFreshnessValueLength Holds the length in bits of the freshness value.
 * \pre            -
 * \return         Std_ReturnType
 *                  E_OK:     request successful
 *                  E_NOT_OK: request failed, a freshness value cannot be provided due to
 *                            general issues for freshness or this FreshnessValueId.
 *                  E_BUSY:   The freshness information can temporarily not be provided
 * \context        TASK
 * \reentrant      TRUE, for different freshness value ids.
 * \synchronous    TRUE
 * \config         FVM_RXFRESHNESSVALUEINFO
 */

# define FVM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

/*!
* \exclusivearea FVM_EXCLUSIVE_AREA_RX_FRESHNESS
* Ensures consistency of global RAM variables.
* \protects Global RAM variables used of Rx path.
* \usedin SecOC_GetRxFreshness, FvM_VerificationStatusCallout
* \exclude All functions provided by FvM.
* \length SHORT depending on the API and the call graph.
* \endexclusivearea
*/

/*!
* \exclusivearea FVM_EXCLUSIVE_AREA_TX_FRESHNESS
* Ensures consistency of global RAM variables.
* \protects Global RAM variables used of Tx path.
* \usedin SecOC_GetTxFreshnessTruncData, SecOC_SPduTxConfirmation
* \exclude All functions provided by FvM.
* \length SHORT depending on the API and the call graph.
* \endexclusivearea
*/

/*!
* \exclusivearea FVM_EXCLUSIVE_AREA_SYNC_STATE
* Ensures consistency of global RAM variables.
* \protects Global RAM variables used for synchronization.
* \usedin FvM_MainFunction
* \exclude All functions provided by FvM.
* \length SHORT depending on the API and the call graph.
* \endexclusivearea
*/

/*!
* \exclusivearea FVM_EXCLUSIVE_AREA_BOTH_FRESHNESS
* Ensures consistency of global RAM variables.
* \protects Global RAM variables.
* \usedin FvM_MainFunction
* \exclude All functions provided by FvM.
* \length SHORT depending on the API and the call graph.
* \endexclusivearea
*/
#endif /* FVM_H */

/**********************************************************************************************************************
 *  END OF FILE: FvM.h
 *********************************************************************************************************************/
