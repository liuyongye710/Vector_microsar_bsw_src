/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TcpIpXcp.h
 *    Component:  TcpIpXcp Header
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Implementation of XCP over TcpIp based on Vector AUTOSAR Stack
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-10-09  Hr                    First Version
 *  02.00.00  2013-06-04  Hr      ESCAN00059277 Adapt component to SoAd
 *                        Hr      ESCAN00069959 Support ASR4 environment
 *  02.00.01  2013-11-15  Hr      ESCAN00071975 Missing XcpOnEth header in response packet
 *  02.00.02  2014-02-25  Ore     ESCAN00073922 Compiler error: Symbol "TCPIPXCP_EXCLUSIVE_AREA_0" unknown
 *                        Hr      ESCAN00074272 SetPduMode feature leads to continuous transmission
 *  02.00.03  2014-05-09  Hr      ESCAN00075589 Improve robustness of use case "if transmission of XCP on Ethernet frame fails"
 *  02.00.04  2014-07-07  Hr      ESCAN00076800 Rx buffer not aligned to 32Bit
 *                        Hr      ESCAN00076953 Xcp connection terminated in case of Alive Supervision Timeout
 *  02.01.00  2015-02-16  Hr      ESCAN00079998 Missing memory abstraction in header
 *            2015-04-23  Hr      ESCAN00080791 Support Resume Mode
 *  02.02.00  2015-05-05  Hr      ESCAN00082845 Support TxConfirmation timeout timer
 *  02.02.01  2015-11-12  Hr      ESCAN00086397 FEAT-1357: SafeXCP
 *                        Hr      ESCAN00085638 Compiler warning: Modifiable lvalue
 *  03.00.00  2016-08-31  Hr      ESCAN00091918 FEAT-1980: Add Multi Client / Multi Connection support
 *                        Hr      ESCAN00091954 Safe deactivation does not consider TcpIpXcp_Init
 *                        Hr      ESCAN00091955 Safe deactivation shall be performed before DET checks or anything
 *  03.00.01  2017-04-19  Hr      ESCAN00094223 DET error due to incorrect channel id conversion
 *  04.00.00  2019-03-26  Hr      ESCAN00101342 Compiler warning: unreferenced formal parameter
 *                        Hr      ESCAN00100672 Possible buffer overflow when XCP Master ignores MaxCto/Dto
 *                        Hr      STORYC-5256   MISRA-C:2012 Compliance Cp_XcpOnTcpIpAsr
 *                        Hr      STORY-7952    Support IF Modules on different cores for XCP
 *  04.00.01  2020-07-06  Hr      ESCAN00106749 Race condition leads to lost tx frame
 *  05.00.00  2020-08-06  Hr      SWAT-1020     XCP Ethernet Frame Concatenation
 *  06.00.00  2021-08-25  Hr      ESCAN00108979 Compiler error: SoAd_SockAddrIn6Type not defined
 *                        Hr      ESCAN00109203 Compiler error: problematic include structure leads to unknown type in TcpIpXcp.h
 *                        Hr      SWAT-1644     Circular Include: Xcp.h includes TcpIp_Xcp.h, which includes Xcp.h
 *  07.00.00  2021-12-16  Hr      SWAT-1511     TcpIpXcp: Soad Burst Mode support to increase transmission speed for BSD Sockets
 *********************************************************************************************************************/

#if (!defined TCPIPXCP_H_)
# define TCPIPXCP_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"
#include "Xcp_Cfg.h"                /* Include configuration of XCP Protocol Layer */
#include "TcpIpXcp_Cfg.h"
#include "TcpIpXcp_Cbk.h"

/*!
* \defgroup IF Embedded Interfaces
* \{
*/
/*! \defgroup General General */
/*! \defgroup PLInteraction PLInteraction
 * \{
 */
/*! * \defgroup Communication Communication */
/*! * \defgroup Control Control */
/*! \} */ 
/*! \} */ 

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define V_TCPIPXCP_COMPONENT_VERSION          (0x0700u)
#define V_TCPIPXCP_COMPONENT_RELEASE_VERSION  (0x00u)

/* vendor and module identification */
#define TCPIPXCP_VENDOR_ID                    (30u)
#define TCPIPXCP_MODULE_ID                    (255u)

/* AUTOSAR Software Specification Version Information */
#define TCPIPXCP_AR_MAJOR_VERSION             (0x04u)
#define TCPIPXCP_AR_MINOR_VERSION             (0x00u)
#define TCPIPXCP_AR_PATCH_VERSION             (0x03u)

/* Component Version Information */
#define TCPIPXCP_SW_MAJOR_VERSION             (V_TCPIPXCP_COMPONENT_VERSION >> 8u)
#define TCPIPXCP_SW_MINOR_VERSION             (V_TCPIPXCP_COMPONENT_VERSION & 0x00FFu)
#define TCPIPXCP_SW_PATCH_VERSION             V_TCPIPXCP_COMPONENT_RELEASE_VERSION


/* Interrupt enable and disable functions */
# define TcpIpXcp_EnterCritical()            SchM_Enter_Xcp_TCPIPXCP_EXCLUSIVE_AREA_0()
# define TcpIpXcp_LeaveCritical()            SchM_Exit_Xcp_TCPIPXCP_EXCLUSIVE_AREA_0()

#if defined ( ApplXcpInterruptDisable )
#else
#  define ApplXcpInterruptDisable()           SchM_Enter_Xcp_TCPIPXCP_EXCLUSIVE_AREA_0()
#endif
#if defined ( ApplXcpInterruptEnable )
#else
#  define ApplXcpInterruptEnable()            SchM_Exit_Xcp_TCPIPXCP_EXCLUSIVE_AREA_0()
#endif

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
# define kXcponTcpIp_Control_Disable   0x00u
# define kXcponTcpIp_Control_Enable    0x01u
#endif

#define TCPIPXCP_HEADER_SIZE                  4u

#define TCPIPXCP_RXINDICATION_SERVICE_ID      0u /*!< Service ID: Xcp_SoAdRxIndication() */
#define TCPIPXCP_TXCONFIRMATION_SERVICE_ID    1u /*!< Service ID: Xcp_SoAdTxConfirmation() */
#define TCPIPXCP_SOCONMODECHG_SERVICE_ID      2u /*!< Service ID: Xcp_SoConModeChg() */
#define TCPIPXCP_SEND_SERVICE_ID              3u /*!< Service ID: TcpIpXcp_Send() */
#define TCPIPXCP_SENDFLUSH_SERVICE_ID         4u /*!< Service ID: TcpIpXcp_SendFlush() */
#define TCPIPXCP_TLSERVICE_SERVICE_ID         5u /*!< Service ID: TcpIpXcp_TLService() */
#define TCPIPXCP_MAINFUNCTION_SERVICE_ID      6u /*!< Service ID: TcpIpXcp_MainFunction() */
#define TCPIPXCP_INIT_SERVICE_ID              7u /*!< Service ID: Xcp_Init() */
#define TCPIPXCP_GETVERSIONINFO_SERVICE_ID    8u /*!< Service ID: TcpIpXcp_GetVersionInfo() */
#define TCPIPXCP_CONTROL_SERVICE_ID           9u /*!< Service ID: - */
#define TCPIPXCP_SETPDUMODE_SERVICE_ID       10u /*!< Service ID: TcpIpXcp_SetPduMode() */
#define TCPIPXCP_DAQRESUMEGET_SERVICE_ID     11u /*!< Service ID: TcpIpXcp_DaqResumeGet() */
#define TCPIPXCP_DAQRESUMESTORE_SERVICE_ID   12u /*!< Service ID: TcpIpXcp_DaqResumeStore() */

#define TCPIPXCP_E_NO_ERROR                   0u /*!< used to check if no error occurred - use a value unequal to any error code */
#define TCPIPXCP_E_PARAM_POINTER              1u /*!< Error code: API service used with invalid pointer parameter (NULL) */
#define TCPIPXCP_E_INV_SOCK_IDX               2u /*!< Error code: A wrong channel id */
#define TCPIPXCP_E_WRONG_CONTROL_COMMAND      3u /*!< Error code: A wrong control command */
#define TCPIPXCP_E_NOT_INITIALIZED            4u /*!< Error code: API service used without module initialization */

/* Initialization status of XCP. */
#define TCPIPXCP_UNINIT   0u
#define TCPIPXCP_INIT     1u

#if !defined ( TCPIPXCP_PROTOCOL_FORMAT ) /* COV_TCPIPXCP_UNSUPPORTED_FEATURE */
# define TCPIPXCP_PROTOCOL_FORMAT TCPIPXCP_PROTOCOL_UDP
#endif

#if !defined ( TCPIPXCP_CONF_TIMEOUT ) /* COV_TCPIPXCP_MSR_COMPATIBILITY */
# define TCPIPXCP_CONF_TIMEOUT 25u
#endif

/* The function XcpGetSessionStatus is required for the protection against multiple connections. */
#if defined ( TCPIPXCP_MULTI_CONN_PROT_ENABLED )
  #if !defined ( XCP_ENABLE_GET_SESSION_STATUS_API )
    #define XCP_ENABLE_GET_SESSION_STATUS_API
  #endif
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define TCPIPXCP_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern CONST(uint8, TCPIPXCP_CONST) TcpIpXcp_MainVersion;
extern CONST(uint8, TCPIPXCP_CONST) TcpIpXcp_SubVersion;
extern CONST(uint8, TCPIPXCP_CONST) TcpIpXcp_ReleaseVersion;

#define TCPIPXCP_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( TCPIPXCP_ENABLE_CONTROL == STD_ON )
# define TCPIPXCP_START_SEC_VAR_INIT_UNSPECIFIED_SAFE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* TL Enable/Disable state */
extern VAR(uint8, TCPIPXCP_VAR_INIT) TcpIpXcp_ControlState;

# define TCPIPXCP_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define TCPIPXCP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Service Functions */
/**********************************************************************************************************************
 *  TcpIpXcp_Send()
 *********************************************************************************************************************/
/*! \brief       Transmission function of XCP transport layer.
 *  \details     TcpIpXcp_Send transmits the passed message. It must not be called again until transmission was confirmed.
 *  \param[in]   Xcp_Channel             The XCP channel.
 *  \param[in]   len                     The length of the message.
 *  \param[in]   msg                     The message itself.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \ingroup     Communication
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_Send( uint8 Xcp_Channel, uint16 len, P2CONST(uint8, AUTOMATIC, TCPIPXCP_APPL_DATA) msg );

/**********************************************************************************************************************
 *  TcpIpXcp_SendFlush()
 *********************************************************************************************************************/
/*! \brief       Flushes any transmit buffers.
 *  \details     -
 *  \param[in]   Xcp_Channel             The XCP channel.
 *  \param[in]   XcpFlushTypeSel         CTO and/or DTO message.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \ingroup     Communication
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_SendFlush( uint8 Xcp_Channel, uint8 XcpFlushTypeSel );

/**********************************************************************************************************************
 *  TcpIpXcp_TLService()
 *********************************************************************************************************************/
/*! \brief       Transport layer specific XCP commands.
 *  \details     -
 *  \param[in]   Xcp_Channel             The XCP channel.
 *  \param[in]   pCmd                    The command to handle.
 *  \return      XCP_CMD_UNKNOWN         Transport layer commands are not supported by TcpIpXcp.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \ingroup     Communication
 *********************************************************************************************************************/
extern FUNC(uint8, TCPIPXCP_CODE) TcpIpXcp_TLService( uint8 Xcp_Channel, P2CONST(uint8, AUTOMATIC, TCPIPXCP_APPL_DATA) pCmd );

/**********************************************************************************************************************
 *  TcpIpXcp_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization.
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     General
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_InitMemory( void );

/**********************************************************************************************************************
 * TcpIpXcp_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes the TcpIpXcp module.
 *  \details     This function initializes the module TcpIpXcp. It initializes all variables and sets the module state to
 *               initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization.
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         TcpIpXcp_InitMemory has been called unless it is initialized by start-up code.
 *  \ingroup     General
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_Init( P2CONST(TcpIpXcp_ConfigType, AUTOMATIC, TCPIPXCP_PBCFG) ConfigPtr );

/**********************************************************************************************************************
 *  TcpIpXcp_MainFunction()
 *********************************************************************************************************************/
/*! \fn          void TcpIpXcp_MainFunction(void)
 *  \brief       Cyclically executed API service of the XCP transport layer.
 *  \details     The TcpIpXcp_MainFunction performs cyclical tasks like managing TX confirmation timeout.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     General
 *********************************************************************************************************************/
/* extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_MainFunction( void ); */

#if ( TCPIPXCP_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  TcpIpXcp_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo             Pointer to where to store the version information. Parameter must not be NULL.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      Available only if TCPIPXCP_VERSION_INFO_API == STD_ON.
 *  \pre         -
 *  \ingroup     General
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, TCPIPXCP_APPL_DATA) versioninfo );
#endif

#if ( TCPIPXCP_ENABLE_PDUMODE == STD_ON )
/**********************************************************************************************************************
 *  TcpIpXcp_SetPduMode()
 *********************************************************************************************************************/
/*! \brief       Set the requested channel active or inactive.
 *  \details     -
 *  \param[in]   XcpNwH             The XCP network handle.
 *  \param[in]   PduMode            The PDU mode (active/inactive).
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if TCPIPXCP_ENABLE_PDUMODE == STD_ON.
 *  \ingroup     Control
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_SetPduMode( NetworkHandleType XcpNwH, TcpIpXcp_PduSetModeType PduMode );
#else
# define TcpIpXcp_SetPduMode( XcpNwH, PduMode )
#endif

#if defined ( XCP_ENABLE_DAQ_RESUME )
/**********************************************************************************************************************
 *  TcpIpXcp_DaqResumeGet()
 *********************************************************************************************************************/
/*! \brief       Get resume information to restore the state.
 *  \details     -
 *  \param[in]   resumeData         Pointer to resume information.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if XCP_ENABLE_DAQ_RESUME == STD_ON.
 *  \ingroup     Control
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_DaqResumeGet( CONSTP2VAR(SoAd_SockAddrInet6Type, AUTOMATIC, TCPIPXCP_APPL_DATA) resumeData );

/**********************************************************************************************************************
 *  TcpIpXcp_DaqResumeStore()
 *********************************************************************************************************************/
/*! \brief       Store resume information.
 *  \details     -
 *  \param[in]   resumeData         Pointer to resume information.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      Available only if XCP_ENABLE_DAQ_RESUME == STD_ON.
 *  \ingroup     Control
 *********************************************************************************************************************/
extern FUNC(void, TCPIPXCP_CODE) TcpIpXcp_DaqResumeStore( CONSTP2CONST(SoAd_SockAddrInet6Type, AUTOMATIC, TCPIPXCP_APPL_DATA) resumeData );
#endif

#define TCPIPXCP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \exclusivearea TCPIPXCP_EXCLUSIVE_AREA_0
 *                Ensures consistency of code that runs on BSW core. They may be interrupted by application functionality or time critical CAT1 interrupts.
 * \protects      TcpIpXcp_ConfTimeoutTimer
 * \usedin        TcpIpXcp_MainFunction
 * \exclude       none
 * \length        SHORT - Access to status variables is protected.
 * \endexclusivearea
 */

#endif
  /* TCPIPXCP_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TcpIpXcp.h
 *********************************************************************************************************************/
