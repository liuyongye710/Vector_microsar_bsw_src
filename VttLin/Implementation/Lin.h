
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
 *  -------------------------------------------------------------------------------------------------------------------
 *           File:  Lin.h
 *      Component:  AUTOSAR LIN Driver
 *         Module:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *      Generator:  DrvLin_VttCanoeAsr / DrvLin_CanoeemuAsr
 *
 *  Target system:  Canoe
 *       Compiler:  Ansi

 *    Derivatives:  VTT/EMU
 *
 *    Description:  Application-Interface of the AUTOSAR LIN Driver
 *                  Declaration of functions, variables and constants
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Lutz Pflueger                 vislpr        Vector Informatik GmbH
 *  David Tiran                   visdat        Vector Informatik GmbH
 *  Jan Gaukel                    visjgl        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  05.00.00  2013-08-12  vislpr  -             Port Canoeemu to VIP
 *  05.01.00  2014-07-17  vislpr  -             Atomic access to VipCntrl, bugfixing
 *  06.00.00  2014-09-29  vislpr  -             Add Canoeemu to VIP, ComStackLib, R11, PB-S
 *  06.00.01  2014-11-20  vislpr  -             HL Part was updated
 *  07.00.00  2015-01-29  vislpr  ESCAN00080255 FEAT-254: Globale Umbennenung von VIP nach VTT
 *                        vislpr  ESCAN00081345 FEAT-427: SafeBSW Step I
 *  07.01.00  2015-06-15  vislpr  ESCAN00083109 VTT Lin shall derive its interrupt offset from the values configured in the OS
 *  07.02.00  2015-06-15  vislpr  -             Remove EMU and HL part dependencies
 *  07.03.00  2016-04-15  vislpr  -             HL Part was updated
 *  08.00.00  2018-09-19  visdat  ESCAN00095805 Compiler warning: Unreferenced formal parameter
 *            2018-09-19  visdat  STORYC-6280   MISRA-C2012: DrvLin_VttCanoeAsr
 *  11.00.00  2019-12-04  visjgl  STORY-11998   Master Slave support
 *  11.01.00  2020-07-03  visjgl  LIN-79        Wakeup support
 *  11.01.01  2020-08-19  visjgl  LIN-132       Add support for generated ISR
 *  11.02.00  2021-01-05  visjgl  LIN-112       LIN Slave support
 *  11.02.01  2021-04-08  visjgl  LIN-322       Fix Product findings
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Friedrich Kiesel              visfki        Vector Informatik GmbH
 *  Lutz Pflueger                 vislpr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY - CORE -
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  04.00.00  2012-07-20  visfki  ESCAN00059300 Implementation of High Level AUTOSAR 4 LIN Driver
 *  04.01.00  2012-11-20  visfki  ESCAN00061782 AR4-220: Remove STATIC
 *                                ESCAN00063147 Rename Lin_WakeUp to Lin_Wakeup
 *  04.02.00  2013-02-08  visfki  ESCAN00064956 AR4-325: Implement Post-Build Loadable
 *                                ESCAN00065149 Compiler error: LIN_CH_OPERATIONAL changed in ASR4 to LIN_OPERATIONAL
 *  05.00.00  2013-09-19  vislpr  ESCAN00066851 Improve include structure for EcuM headers
 *                                ESCAN00079533 AR4-260: Remove ProdErrorDetection configuration switch
 *                                ESCAN00069952 Justify MISRA Warnings on functions
 *                                ESCAN00067708 AR4-328: Predefined Runtime Measurement Points
 *  05.00.01  2013-11-19  vislpr  ESCAN00071647 Remove MISRA warning 0850/3453
 *                                ESCAN00072030 Change RTM macros
 *  05.00.02  2013-11-21  vislpr  ESCAN00072030 Fix MISRA Warnings and GNU Compiler error on RTM
 *  06.00.00  2014-10-01  vislpr  ESCAN00076482 AR4-832: External wake up via LIN transceiver
 *                                ESCAN00078696 AR4-698: Post-Build Selectable (Identity Manager)
 *  06.00.01  2014-11-14  vislpr  ESCAN00079471 Compiler error: lin.c: 'Lin_Dev_InitDetect'/'LIN_DEV_INITVALUE'
 *  06.00.02  2014-11-14  vislpr  ESCAN00079588 Compiler error: Identifier Channel not declared
 *  06.00.03  2014-12-02  vislpr  -             Change wakeup handling
 *  07.00.00  2014-12-12  vislpr  ESCAN00080307 FEAT-427: SafeBSW Step I
 *  07.00.01  2015-01-27  vislpr  ESCAN00080823 Add channel DET check for out of bounds of channel id and channel idx
 *                        vislpr  ESCAN00080824 Use LOCAL_INLINE macro of Compiler.h instead "static inline"
 *  07.00.02  2015-03-26  vislpr  ESCAN00082080 Remove redundant code in Lin_GoToSleep
 *  07.00.03  2015-05-26  vislpr  ESCAN00083154 Dem.h not included if Dem repoting enabled
 *                        vislpr  ESCAN00083156 EcuM_BswErrorHook() are used on precompile with Selectable enabled
 *  07.01.00  2015-07-13  vislpr  ESCAN00081794 FEAT-1275: SafeBSW Step 2
 *  07.01.01  2015-09-15  vislpr  ESCAN00085267 Unkown return value 0x01u of Lin_GetStatus() in case of LIN_TX_BUSY error
 *  07.01.02  2015-10-23  vislpr  ESCAN00086056 Check data length parameter of Lin_SendFrame()
 *  07.02.00  2015-11-04  vislpr  ESCAN00086254 Unification the register base address struct and typedef for each driver
 *            2015-11-04  vislpr  ESCAN00086267 Code refactoring
 *            2015-11-16  vislpr  ESCAN00086493 Remove Lin_GetRxPin() Macro.
 *            2015-11-16  vislpr  ESCAN00086494 Do not set the state to wake after calling Lin_CheckWakeup()
 *            2015-11-17  vislpr  ESCAN00086546 Inconsistency of wakeup support between Lin, LinIf and EcuM in variant Post Build
 *  07.03.00  2016-01-27  vislpr  ESCAN00087812 FEAT-1688: SafeBSW Step 4
 *  07.03.01  2016-03-16  vislpr  -             SafeBSW review rework
 *  07.04.00  2016-04-13  vislpr  -             SafeBSW review rework (ISR)
 *********************************************************************************************************************/

#if !defined (LIN_H)
# define LIN_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Lin_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*!
  \defgroup  LinIdentification Lin Identification
  \brief  Vendor and module identification of this implementation.
  \{
*/
# define LIN_VENDOR_ID                30u       /* !< the vendor ID of this implementation. */
# define LIN_MODULE_ID                82u       /* !< the module ID of this implementation. */
/*!
  \}
*/

/*!
  \defgroup  LinSWVersion Lin version number
  \brief  Version number of this implementation.
  \{
*/
# define LIN_SW_MAJOR_VERSION         11u
# define LIN_SW_MINOR_VERSION         2u
# define LIN_SW_PATCH_VERSION         1u
/*!
  \}
*/

/*!
  \defgroup  LinARReleaseVersion Lin AUTOSAR release version number
  \brief  Version number of AUTOSAR release on which the appropriate implementation is based on.
  \{
*/
# define LIN_AR_RELEASE_MAJOR_VERSION    4u
# define LIN_AR_RELEASE_MINOR_VERSION    0u
# define LIN_AR_RELEASE_PATCH_VERSION    3u
/*!
  \}
*/

/*!
  \defgroup  LinApiIds Lin Module Service Identifiers
  \brief  Unique identifier of a LIN module service.
  \{
*/
# define LIN_SID_INIT_ID              0u        /* !< Service ID: Lin_Init() */
# define LIN_SID_GETVERSIONINFO_ID    1u        /* !< Service ID: Lin_GetVersionInfo() */
# define LIN_SID_SENDFRAME_ID         4u        /* !< Service ID: Lin_SendFrame() */
# define LIN_SID_GOTOSLEEP_ID         6u        /* !< Service ID: Lin_GoToSleep() */
# define LIN_SID_WAKEUP_ID            7u        /* !< Service ID: Lin_Wakeup() */
# define LIN_SID_GETSTATUS_ID         8u        /* !< Service ID: Lin_GetStatus() */
# define LIN_SID_GOTOSLEEPINTERNAL_ID 9u        /* !< Service ID: Lin_GoToSleepInternal() */
# define LIN_SID_CHECKWAKEUP_ID       10u       /* !< Service ID: Lin_CheckWakeup() */
# define LIN_SID_WAKEUPINTERNAL_ID    11u       /* !< Service ID: Lin_WakeupInternal() */
# define LIN_SID_INTERRUPT_ID         144u      /* !< Service ID: Lin_Interrupt() */
/*!
  \}
*/

/* Interrupt calling type */
# define LIN_ISR_CAT2 0u        /* !< Interrupt category 2: Using Os (ISR() macro) */
# define LIN_ISR_CAT1 1u        /* !< Interrupt category 1: Call ISR direct (compiler depend) */
# define LIN_ISR_VOID 2u        /* !< Use ISR void/void prototype */

/* Generator compatibility version */
# define LIN_HL_GENERATORMSR_COMPATIBILITY_VERSION 0x1400u      /* !< Compatibilitiy version of base Generator */
# define LIN_LL_GENERATORMSR_COMPATIBILITY_VERSION 0x1400u

# define LIN_E_TIMEOUT_TYPE_DET STD_ON

# if ( LIN_EXISTS_SLAVE_NODETYPEOFCHANNELCONFIG == STD_ON )
/* Slave sate values */
#  define LIN_SLAVE_STATE_UNKNOWN           0u
#  define LIN_SLAVE_STATE_FRAME_COMPLETE    1u
#  define LIN_SLAVE_STATE_HEADER_ERROR      2u
#  define LIN_SLAVE_STATE_ANY_ERROR         3u
#  define LIN_SLAVE_STATE_NO_RESPONSE_ERROR 4u
/* 3D polling values */
#  define LIN_FRAME_3D_POLL_STATE_POLLING         0u    /* also poll the 3d frame in 1ms task */
#  define LIN_FRAME_3D_POLL_STATE_WAITING_FOR_BUS 1u    /* wait for 3d frame to be requested by master */
/* state machine for not polling during sleep or wakeup frame transmission */
#  define LIN_POLLING_LINHEADER_DISABLED         0u
#  define LIN_POLLING_LINHEADER_ENABLED          1u
#  define LIN_POLLING_LINHEADER_ONCE_AFTER_INIT  2u
# endif

/*!
  \defgroup  LinDetErrorCodes Lin Det Error Codes
  \brief  Lin development error IDs.
  \{
*/
# define LIN_E_NO_ERROR         255u    /* !< No error. */
# define LIN_E_UNINIT           0u      /* !< API service used without module initialization. */
# define LIN_E_INVALID_CHANNEL  2u      /* !< API service used with an invalid or inactive channel parameter. */
# define LIN_E_INVALID_POINTER  3u      /* !< API service called with invalid configuration pointer. */
# define LIN_E_STATE_TRANSITION 4u      /* !< Invalid state transition for the current state. */
# define LIN_E_PARAM_POINTER    5u      /* !< API service called with a NULL pointer. */
# define LIN_E_PARAM_VALUE      6u      /* !< API service called with invalid parameter value. */
/*!
  \}
*/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define LIN_START_SEC_CODE_ISR
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Lin_Interrupt
 **********************************************************************************************************************/
/*! \brief       Interrupt processing function.
 *  \details     Handles the internal state machine.
 *  \param[in]   ChanneHw ChannelHw index (not Channel ID) of configuration from where the interrupt occurred.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 *  \note        The user should not call this function directly.
 *  \trace       CREQ-208, CREQ-209, CREQ-211, CREQ-217, CREQ-224, DSGN-Lin23162, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(void, LIN_CODE_ISR) Lin_Interrupt(uint8 ChannelHw);
# define LIN_STOP_SEC_CODE_ISR
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */


# define LIN_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Lin_InitMemory
 **********************************************************************************************************************/
/*! \brief       Initializes the module memory.
 *  \details     Sets the module state to uninitialized. Must be called in case LIN_VAR_ZERO_INIT variables are not
 *               initialized with 0 after reset.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This service function has to be called before Lin_Init() function.
 *  \trace       CREQ-216, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_InitMemory(void);

/***********************************************************************************************************************
 *  Lin_Init
 **********************************************************************************************************************/
/*! \brief       Initializes the Lin Driver.
 *  \details     Initializes the LIN module channel hardware and sets the state to initialize.
 *  \param[in]   Config: Pointer to a selected configuration structure.
 *  \pre         Lin interrupts must be locked.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-216, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_PBCFG) Config);

# if ( LIN_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  Lin_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     Returns the version information of this module as decimal numbers.
 *  \param[in]   versioninfo: Pointer to where to store the version information of this module. The version information
 *                            are in decimal.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-214
 *  \note        Configuration parameter LinVersionInfoApi must be enabled.
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_VAR) versioninfo);
# endif

/***********************************************************************************************************************
 *  Lin_SendFrame
 **********************************************************************************************************************/
/*! \brief       Generates a LIN frame.
 *  \details     Generates a LIN frame on the addressed LIN channel.
 *  \param[in]   Channel: LIN Channel ID of hardware channel to be addressed.
 *  \param[in]   PduInfoPtr: Pointer to PDU containing the PID, Checksum model, Response type, Dl and SDU data pointer.
 *  \return      E_OK: send command has been accepted.
 *  \return      E_NOT_OK: send command has not been accepted, development or production error occurred.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 *  \trace       CREQ-208, DSGN-Lin23162
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_SendFrame(uint8 Channel, P2VAR(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr);

/***********************************************************************************************************************
 *  Lin_GoToSleep
 **********************************************************************************************************************/
/*! \brief       Transmits a go-to-sleep command.
 *  \details     Transmits a go-to-sleep command on the addressed LIN channel and sets the channel into sleep mode.
 *  \param[in]   Channel: LIN Channel ID of hardware channel to be addressed.
 *  \return      E_OK: Sleep command has been accepted.
 *  \return      E_NOT_OK: Sleep command has not been accepted, development or production error occurred.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 *  \trace       CREQ-209, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleep(uint8 Channel);

/***********************************************************************************************************************
 *  Lin_GoToSleepInternal
 **********************************************************************************************************************/
/*! \brief       Sets the channel to sleep mode.
 *  \details     Sets the channel to sleep mode without sending a go-to-sleep command.
 *  \param[in]   Channel: LIN Channel ID of hardware channel to be addressed.
 *  \return      E_OK: Sleep command has been accepted
 *  \return      E_NOT_OK: Sleep command has not been accepted, development or production error occurred
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous TRUE
 *  \trace       CREQ-209, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleepInternal(uint8 Channel);

/***********************************************************************************************************************
 *  Lin_Wakeup
 **********************************************************************************************************************/
/*! \brief       Sends a wakeup frame.
 *  \details     Sends a wakeup frame on the addressed LIN channel.
 *  \param[in]   Channel: LIN Channel ID of hardware channel to be addressed.
 *  \return      E_OK: Wake-up request has been accepted.
 *  \return      E_NOT_OK: Wake-up request has not been accepted, development or production error occurred.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 *  \trace       CREQ-211, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_Wakeup(uint8 Channel);

/***********************************************************************************************************************
 *  Lin_WakeupInternal
 **********************************************************************************************************************/
/*! \brief       Sets the channel state to LIN_CH_OPERATIONAL.
 *  \details     Sets the channel state to LIN_CH_OPERATIONAL without generating a wake up pulse.
 *  \param[in]   Channel: LIN Channel ID of hardware channel to be addressed.
 *  \return      E_OK: Wake-up request has been accepted
 *  \return      E_NOT_OK: Wake-up request has not been accepted, development or production error occurred
 *  \pre         LIN interrupts for hardware channel of Channel must be locked..
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous TRUE
 *  \trace       CREQ-211, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternal(uint8 Channel);

/***********************************************************************************************************************
 *  Lin_CheckWakeup
 **********************************************************************************************************************/
/*! \brief       Checks if a wakeup has occurred on the addressed Lin Channel.
 *  \details     Lin_CheckWakeup called by the LIN Interface module to identify the corresponding LIN channel. If a
 *               wakeup occurred on the channel the status are reported to LinIf and EcuM.
 *  \param[in]   Channel: LIN Channel ID of hardware channel to be addressed.
 *  \return      E_OK: No error has occurred during execution of the API
 *  \return      E_NOT_OK:  An error has occurred during execution of the API
 *  \pre         The LIN driver shall have been initialized before this service is called.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous TRUE
 *  \trace       CREQ-217, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeup(uint8 Channel);

/***********************************************************************************************************************
 *  Lin_GetStatus
 **********************************************************************************************************************/
/*! \brief       Returns the Status.
 *  \details     Returns the Status and sets the Status to operational if necessary (wrong or no interrupt occurred).
 *  \param[in]   Channel: LIN channel to be addressed
 *  \param[out]  Lin_SduPtr: Pointer to pointer to shadow buffer or memory mapped LIN Hardware receive buffer
 *  \return      Lin_StatusType: Information about the current message state.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous TRUE
 *  \note        Do not poll this function. On some platform calling this function on an ongoing frame
 *               transmission/reception disrupt the frame transmission/reception.
 *  \trace       CREQ-208, CREQ-209, CREQ-211, CREQ-216, DSGN-Lin23162, DSGN-Lin22334
 **********************************************************************************************************************/
FUNC(Lin_StatusType, LIN_CODE) Lin_GetStatus(uint8 Channel, P2VAR(Lin_u8PtrType, AUTOMATIC, LIN_APPL_VAR) Lin_SduPtr);

# if( LIN_SLAVE_POLL_WORKAROUND == STD_ON )
/***********************************************************************************************************************
 *  VTTLin_Slave1msPoll
 **********************************************************************************************************************/
/*! \brief       Polls the MSG for LIN Slave
 *  \details     Polls the LinIf to regulary update the MSG buffer of the CANoe.
 *  \pre         LIN stack needs to be initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        This function will update the values of the MSG in CANoe internal buffer, by polling the LinIf.
 *  \config      LIN_SLAVE_POLL_WORKAROUND
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) VTTLin_Slave1msPoll(void);
# endif/* LIN_SLAVE_POLL_WORKAROUND == STD_ON */

/***********************************************************************************************************************
 *  VttLin_OnStateChange
 **********************************************************************************************************************/
/*! \brief       Configures the CANoe channel
 *  \details     Configures the CANoe channel
 *  \pre         Is to be called from VttCntrl_Base_UserCallout_OnStateChange or instead of.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) VttLin_OnStateChange(uint8 action, uint8 oldState, uint8 newState);

# define LIN_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* LIN_H */

/**********************************************************************************************************************
 *  END OF FILE: Lin.h
 *********************************************************************************************************************/
