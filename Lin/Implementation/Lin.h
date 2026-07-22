/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/*!        \file  Lin.h
 *        \brief  AUTOSAR LIN Driver
 *
 *      \details  Core part of AUTOSAR LIN Driver
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  14.00.00  2017-12-01  vislpr  -             Implement new common part of AUTOSAR 4 LIN driver
 *  14.00.01  2018-03-06  visap   FIX-3684      Rework review findings
 *  14.00.02  2018-05-14  visjgl  TASK-75803    Added new infixed files for Tms570SciStd
 *  14.00.03  2018-06-05  visjgl  TASK-78012    Bugfix of the infix issue
 *  14.01.00  2018-09-06  visjgl  TASK-88563    MISRA 2012
 *                                TASK-68143    Correct design flaw
 *                                TASK-69412    Implementation improvements
 *  14.01.01  2018-09-18  visjgl  TASK-91063    Add missing MISRA 2012 justification
 *  15.00.00  2020-02-26  visjgl  STORY-11998   Master Slave Prototype
 *  15.00.01  2020-03-25  visjgl  MSR4-214      Quality cleanup Master(ASIL) Slave(QM), ESCAN00105763
 *  15.00.02  2020-09-04  visjgl  LIN-156       Correct Infixing
 *  15.01.00  2021-08-18  visjgl  LIN-316       Polling mode
 **********************************************************************************************************************/


#if !defined (LIN_H)
# define LIN_H

/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
# include "Lin_Cfg.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
/*!
  \name Component version information (decimal version of ALM implementation package)
  \{
*/
# define LIN_SW_MAJOR_VERSION                                   15U
# define LIN_SW_MINOR_VERSION                                   1U
# define LIN_SW_PATCH_VERSION                                   0U
/*! \} */

/*!
  \name Vendor and module identification
  \{
*/
# define LIN_VENDOR_ID                                          0x001EU       /*!< Vendor ID: Vector Informatik GmbH. */
# define LIN_MODULE_ID                                          0x0052U       /*!< Module ID: DrvLin (dez.: 82) */
/*! \} */

/*!
  \name AUTOSAR Software specification version information
  \{
*/
# define LIN_AR_RELEASE_MAJOR_VERSION                           0x04U
# define LIN_AR_RELEASE_MINOR_VERSION                           0x00U
# define LIN_AR_RELEASE_PATCH_VERSION                           0x03U
/*! \} */

/*!
  \name API service IDs
  \{
*/
# define LIN_SID_INIT_ID                                        0x00U /*!< Service ID: Lin_Init() */
# define LIN_SID_GETVERSIONINFO_ID                              0x01U /*!< Service ID: Lin_GetVersionInfo() */
# define LIN_SID_SENDFRAME_ID                                   0x04U /*!< Service ID: Lin_SendFrame() */
# define LIN_SID_GOTOSLEEP_ID                                   0x06U /*!< Service ID: Lin_GoToSleep() */
# define LIN_SID_WAKEUP_ID                                      0x07U /*!< Service ID: Lin_Wakeup() */
# define LIN_SID_GETSTATUS_ID                                   0x08U /*!< Service ID: Lin_GetStatus() */
# define LIN_SID_GOTOSLEEPINTERNAL_ID                           0x09U /*!< Service ID: Lin_GoToSleepInternal() */
# define LIN_SID_CHECKWAKEUP_ID                                 0x0AU /*!< Service ID: Lin_CheckWakeup() */
# define LIN_SID_WAKEUPINTERNAL_ID                              0x0BU /*!< Service ID: Lin_WakeupInternal() */

# define LIN_SID_INTERRUPT_ID                                   0x90U /*!< Service ID: Lin_Interrupt() */
# define LIN_SID_POLL_ID                                        0x91U /*!< Service ID: Lin_Poll() */
# define LIN_SID_TIMEOUT_DURATION_ID                            0xA0U /*!< Service ID: Timeout duration function of hardware implementation */
/*! \} */

/*!
  \name Error codes
  \{
*/
# define LIN_E_NO_ERROR                                         0xFFU /*!< No error. */
# define LIN_E_UNINIT                                           0x00U /*!< API service used without module initialization. */
# define LIN_E_INVALID_CHANNEL                                  0x02U /*!< API service used with an invalid or inactive channel parameter. */
# define LIN_E_INVALID_POINTER                                  0x03U /*!< API service called with invalid configuration pointer. */
# define LIN_E_STATE_TRANSITION                                 0x04U /*!< Invalid state transition for the current state. */
# define LIN_E_PARAM_POINTER                                    0x05U /*!< API service called with a NULL pointer. */
# define LIN_E_PARAM_VALUE                                      0x06U /*!< API service called with invalid parameter value. */
/*! \} */

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define LIN_START_SEC_CODE_ISR
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Lin_Interrupt
 **********************************************************************************************************************/
/*! \brief       Interrupt processing function.
 *  \details     Handles the internal state machine.
 *  \param[in]   ChannelHw: ChannelHw index (not Channel ID) of configuration from where the interrupt occurred.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 *  \note        The user should not call this function directly.
 *  \trace       CREQ-236310, CREQ-211, CREQ-224, CREQ-236312, CREQ-236314, CREQ-236315, CREQ-236316, CREQ-293221
 **********************************************************************************************************************/
FUNC(void, LIN_CODE_ISR) Lin_Interrupt( uint8 ChannelHw );
# define LIN_STOP_SEC_CODE_ISR
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define LIN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
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
 *  \trace       CREQ-216
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_InitMemory( void );

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
 *  \trace       CREQ-216
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_Init( P2CONST(Lin_ConfigType, AUTOMATIC, LIN_PBCFG) Config );

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
 *  \config      LIN_VERSION_INFO_API
 *  \trace       CREQ-214
 *  \note        Configuration parameter LinVersionInfoApi must be enabled.
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_VAR) versioninfo );
# endif

# if ( LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG == STD_ON ) /* COV_LIN_SLAVE_MA_ALWAYS_ON */
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
 *  \config      LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG
 *  \trace       CREQ-236311, CREQ-236312
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_SendFrame( uint8 Channel, P2VAR(Lin_PduType, AUTOMATIC, LIN_APPL_VAR) PduInfoPtr );

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
 *  \config      LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG
 *  \trace       CREQ-236310
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleep( uint8 Channel );
# endif /* LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG == STD_ON */

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
 *  \trace       CREQ-209
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleepInternal( uint8 Channel );

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
 *  \trace       CREQ-211
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_Wakeup( uint8 Channel );

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
 *  \trace       CREQ-211
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternal( uint8 Channel );

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
 *  \trace       CREQ-217
 **********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeup( uint8 Channel );

# if ( LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG == STD_ON ) /* COV_LIN_SLAVE_MA_ALWAYS_ON */
/***********************************************************************************************************************
 *  Lin_GetStatus
 **********************************************************************************************************************/
/*! \brief       Returns the Status.
 *  \details     Returns the Status and sets the Status to operational if necessary (wrong or no interrupt occurred).
 *  \param[in]   Channel: LIN channel to be addressed
 *  \param[out]  SduPtr: Pointer to pointer to shadow buffer or memory mapped LIN Hardware receive buffer, valid till
 *               next send frame.
 *  \return      Lin_StatusType: Information about the current message state.
 *  \pre         LIN interrupts for hardware channel of Channel must be locked.
 *  \context     TASK
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous TRUE
 *  \config      LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG
 *  \note        Do not poll this function. On some platform calling this function on an ongoing frame
 *               transmission/reception disrupt the frame transmission/reception.
 *  \trace       CREQ-236313, CREQ-236310, CREQ-211
 **********************************************************************************************************************/
FUNC(Lin_StatusType, LIN_CODE) Lin_GetStatus( uint8 Channel, P2VAR(Lin_u8PtrType, AUTOMATIC, LIN_APPL_VAR) SduPtr );
# endif /* LIN_EXISTS_MASTER_NODETYPEOFCHANNELCONFIG == STD_ON */

# if ( LIN_POLLING_MODE_SUPPORT == STD_ON )
/***********************************************************************************************************************
 *  Lin_Poll
 **********************************************************************************************************************/
/*! \brief       Polling function.
 *  \details     Calls the interrupt function for all valid channels
 *  \pre         LIN hardware interrupts must be disabled.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      LIN_POLLING_MODE_SUPPORT
 *  \note        If polling mode is enabled, then this function needs to be called regularly and in equidistant time
 *               intervals, depending on the underlying hardware.
 *  \trace       CREQ-293221
 **********************************************************************************************************************/
FUNC(void, LIN_CODE) Lin_Poll( void );
# endif /* LIN_POLLING_MODE_SUPPORT == STD_ON */

# define LIN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* LIN_H */

/***********************************************************************************************************************
 *  END OF FILE: Lin.h
 **********************************************************************************************************************/
