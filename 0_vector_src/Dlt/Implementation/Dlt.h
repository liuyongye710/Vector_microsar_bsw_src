/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dlt.h
 *      Project:  Diagnostic Log and Trace
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Implements partly the functionality of the AUTOSAR 4.x module DLT based on XCP.
 *
 *
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id       Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-05-12  visml   ESCAN00050129   Creation
 *  01.02.00  2013-03-26  visml   ESCAN00065961   Added DLT_APPL_VAR and DLT_PBCFG     
 *                        visml   ESCAN00065958   Added DLT_XCP_DET_EVENT to the template
 *                        visml   ESCAN00066198   Added default XCP event to A2L file
 *  01.02.01  2013-05-21  visazb  ESCAN00067468   Corrected vesion mismatch
 *  01.03.00  2013-07-02  visore  ESCAN00068516   Compiler warning: parameter 'ConfigPtr' unused in function 'Dlt_Init'
 *                        visore  ESCAN00068517   The DET service and error IDs are not compliant to the AUTOSAR4 specification
 *                        visore  ESCAN00068518   The MISRA justifications are not implemented according WI_MISRAC2004_PES.pdf
 *                        visore  ESCAN00068274   AR4-292: Reporting of DET and DEM errors via DLT
 *                        visore  ESCAN00068519   Signature of Dlt_DetForwardErrorTrace() is not compliant to AUTOSAR4
 *                        visore  ESCAN00070450   No changes here
 *                        visore  ESCAN00070451   No changes here
 *  01.03.01  2013-11-20  visore  ESCAN00071890   No changes here
 *  01.03.02  2014-01-20  visore  ESCAN00072716   Improve DLT include structure
 *  01.03.03  2014-05-21  visore  ESCAN00074824   No changes here
 *  01.05.00  2014-02-25  viszda  ESCAN00081343   FEAT-1311: DLT with AUTOSAR functionality and DLT Transport layer
 *            2015-03-17  viszda  ESCAN00081868   No changes here
 *  01.06.00  2015-04-22  viszda  ESCAN00082261   FEAT-1312: Continue DLT development with AUTOSAR functionality and DLT Transport layer (based on FEAT-1311)
 *                        viszda  ESCAN00082468   Compiler error: error C2065: 'xyz' : undeclared identifier
 *                        viszda  ESCAN00082469   Compiler warning: warning C4244, warning C4101, warning C4189, warning C4100
 *                        viszda  ESCAN00082472   Missing filters, compiler abstractions and exclusive areas
 *                        viszda  ESCAN00082473   Reduce code redundancies and code complexity due to FEAT-1311
 *                        viszda  ESCAN00082474   Change erroneous compiler abstractions and use the correct initialization for global variables
 *                        viszda  ESCAN00083946   No changes here
 *  01.06.01  2015-12-17  viszda  ESCAN00087203   No changes here
 *                        viszda  ESCAN00087212   Wrong DLT module ID
 *  01.07.00  2015-02-01  viszda  ESCAN00087978   Correction of version number in DltCom messages
 *            2016-02-26  viszda  ESCAN00088121   Product release of ASR DLT
 *  01.07.01  2016-06-21  viszda  ESCAN00090043   Get the socket connection state via API
 *            2016-07-25  viszda  ESCAN00091129   Valid DEM Event forwarded to DLT triggers DET Error
 *  01.07.02  2016-11-18  viszda  ESCAN00092787   Control messages from Dlt client are rejected and no response is send.
 *                        viszda  ESCAN00081639   Correction of formal issues
 *                        viszda  ESCAN00092560   Compiler error: The include file 'Det.h' cannot be opened
 *            2016-11-22  viszda  ESCAN00092936   Reduce Stack consumption of Dlt
 *  01.07.03  2018-03-13  viszda  ESCAN00098621   Loss of DLT log data after socket reconnect
 *            2018-03-14  viszda  ESCAN00098730   DLT log message loss if a control request message is received by DLT
 *  01.07.04  2018-05-24  viszda  ESCAN00097255   DLT (XCP) forwards DET errors to uninitialized XCP
 *  02.00.00  2018-11-07  viszda  STORY-8329      Support disabled Rx path and control APIs.
 *  02.01.00  2019-01-29  viszda  STORY-9729      Change data types corresponding to ASR 4.3.1 and change the APIs using those data types.
 *                        viszda  ESCAN00101530   Wrong default values for Dlt_Context
 *                        viszda  ESCAN00102027   Wrong interpretation of application and context id on little endian platforms
 *  03.00.00  2020-03-02  viszda  SWAT-12         Update the BSWMD corresponding to AUTOSAR DLT 4.3.1 specification.
 *            2020-04-08  viszda  ESCAN00106077   Log messages with high log level are filtered
 *  03.01.00  2020-04-13  viszda  SWAT-62         Support the DLT service Store_Config (0x05).
 *                        viszda  SWAT-78         Support the DLT service SWC injection (0xFFF-0xFFFFFFFF).
 *            2020-04-28  viszda  ESCAN00106239   Compiler errors: Multiple elements are undefined
 *  03.02.00  2020-05-14  viszda  SWAT-35         Implement the multi log channel support
 *  03.03.00  2020-06-23  viszda  SWAT-1041       Support of bandwidth management
 *            2020-06-24  viszda  ESCAN00106674   Compiler error: Missing file Dlt_Lcfg.h
 *  03.04.00  2020-07-31  viszda  SWAT-1110       Provide separate exclusive areas for Dlt_MainFunction, Tx and Rx.
 *            2020-07-31  viszda  ESCAN00107008   Wrong length of GetLoginfo response
 *            2020-07-31  viszda  ESCAN00107010   Missing trace status in response of SetLogChannelThreshold
 *  04.00.00  2020-10-29  viszda  SWAT-1165       Use of VStdLib MemCopy instead of local copy loops
 *  04.01.00  2020-11-20  viszda  SWAT-1252       Provide the API to get the default LogLevel
 *  04.02.00  2021-01-11  viszda  SWAT-1296       Add an optional validator to support TCP via SoAd
 *  04.02.01  2021-01-18  viszda  ESCAN00108292   C/S calls cannot be queued for services belonging to DLT server ports
 *  05.00.00  2021-11-29  visore  SWAT-1831       Prepare SafeBSW Release for DLT
 *            2022-05-03  viszda  ESCAN00109334   Compile error due to wrong data types in callback function Dlt_CopyTxData, Dlt_CopyRxData, and Dlt_StartOfReception
 *            2022-05-30  visore  SWAT-1627       Usage of <Mip>_MemMap.h in Dlt
 *********************************************************************************************************************/

#if !defined(DLT_H)
# define DLT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Dlt_Types.h"
# include "Dlt_Lcfg.h"
# include "SchM_Dlt.h"


# include "Dem.h" /* needed for Dem_EventIdType */

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* vendor and module identification */
# define DLT_VENDOR_ID                       (30u)
# define DLT_MODULE_ID                       (55u) /* ESCAN00087212 */

/* AUTOSAR Software specification version information */
# define DLT_AR_RELEASE_MAJOR_VERSION        (4u)
# define DLT_AR_RELEASE_MINOR_VERSION        (3u)
# define DLT_AR_RELEASE_REVISION_VERSION     (1u)

/* Component version information (decimal version of ALM implementation package) */
# define DLT_SW_MAJOR_VERSION                (5u)
# define DLT_SW_MINOR_VERSION                (0u)
# define DLT_SW_PATCH_VERSION                (0u)

# define DLT_INSTANCE_ID_DET                 (0x00u)

/* API service IDs */
# define DLT_API_ID_INIT                     ((uint8)0x01u) /*!< ASR4.0 Dlt_Init() service ID [Dlt239]. */
# define DLT_API_ID_GETVERSIONINFO           ((uint8)0x02u) /*!< ASR4.0 Dlt_GetVersionInfo() service ID [Dlt271]. */
# define DLT_API_ID_SENDLOGMESSAGE           ((uint8)0x03u) /*!< ASR4.0 Dlt_SendLogMessage() service ID [Dlt241]. */
# define DLT_API_ID_SENDTRACEMESSAGE         ((uint8)0x04u) /*!< ASR4.0 Dlt_SendTraceMessage() service ID [Dlt243]. */
# define DLT_API_ID_REGISTERCONTEXT          ((uint8)0x05u) /*!< ASR4.0 Dlt_RegisterContext() service ID [Dlt245]. */
# define DLT_API_ID_RESETTOFACTORYDEFAULT    ((uint8)0x06u) /*!< ASR4.0 Dlt_ResetToFactoryDefault() service ID [SWS_Dlt_00739]. */
# define DLT_API_ID_DETFORWARDERRORTRACE     ((uint8)0x07u) /*!< ASR4.0 Dlt_DetForwardErrorTrace() service ID [Dlt432]. */
# define DLT_API_ID_SETLOGLEVEL              ((uint8)0x08u) /*!< ASR4.0 Dlt_SetLogLevel() service ID [SWS_Dlt_00252]. */
# define DLT_API_ID_SETTRACESTATUS           ((uint8)0x09u) /*!< ASR4.0 Dlt_SetTraceStatus() service ID [SWS_Dlt_00254]. */
# define DLT_API_ID_GETLOGINFO               ((uint8)0x0Au) /*!< ASR4.0 Dlt_GetLogInfo() service ID [SWS_Dlt_00732]. */
# define DLT_API_ID_SETDEFAULTLOGLEVEL       ((uint8)0x11u) /*!< ASR4.0 Dlt_SetDefaultLogLevel() service ID [SWS_Dlt_00740]. */
# define DLT_API_ID_SETDEFAULTTRACESTATUS    ((uint8)0x12u) /*!< ASR4.0 Dlt_SetDefaultTraceStatus() service ID [SWS_Dlt_00743]. */
# define DLT_API_ID_INJECTCALL               ((uint8)0x14u) /*!< ASR4.0 Dlt_InjectCall() service ID [SWS_Dlt_00259]. */
# define DLT_API_ID_DEMTRIGGERONEVENTSTATUS  ((uint8)0x15u) /*!< ASR4.0 Dlt_DemTriggerOnEventStatus() service ID [Dlt470]. */
# define DLT_API_ID_GETLOGCHANNELNAMES       ((uint8)0x17u) /*!< ASR4.0 Dlt_GetLogChannelNames() service ID [SWS_Dlt_00749]. */
# define DLT_API_ID_GETDEFAULTLOGLEVEL       ((uint8)0x18u) /*!< ASR4.0 Dlt_GetDefaultLogLevel() service ID [SWS_Dlt_00733]. */
# define DLT_API_ID_GETDEFAULTTRACESTATUS    ((uint8)0x19u) /*!< ASR4.0 Dlt_GetDefaultTraceStatus() service ID [SWS_Dlt_00746]. */
# define DLT_API_ID_STORECONFIGURATION       ((uint8)0x1Au) /*!< ASR4.0 Dlt_StoreConfiguration() service ID [SWS_Dlt_00736]. */
# define DLT_API_ID_SETMESSAGEFILTERING      ((uint8)0x1Bu) /*!< ASR4.0 Dlt_SetMessageFiltering() service ID [SWS_Dlt_00770]. */
# define DLT_API_ID_GETTRACESTATUS           ((uint8)0x1Fu) /*!< ASR4.0 Dlt_GetTraceStatus() service ID [SWS_Dlt_00750]. */
# define DLT_API_ID_SETLOGCHANNELASSIGNMENT  ((uint8)0x20u) /*!< ASR4.0 Dlt_SetLogChannelAssignment() service ID [SWS_Dlt_00751]. */
# define DLT_API_ID_SETLOGCHANNELTHRESHOLD   ((uint8)0x21u) /*!< ASR4.0 Dlt_SetLogChannelThreshold() service ID [SWS_Dlt_00752]. */
# define DLT_API_ID_GETLOGCHANNELTHRESHOLD   ((uint8)0x22u) /*!< ASR4.0 Dlt_GetLogChannelThreshold() service ID [SWS_Dlt_00753]. */
# define DLT_API_ID_COPYTXDATA               ((uint8)0x43u) /*!< ASR4.0 Dlt_CopyTxData() service ID [SWS_Dlt_00516]. */
# define DLT_API_ID_COPYRXDATA               ((uint8)0x44u) /*!< ASR4.0 Dlt_CopyRxData() service ID [SWS_Dlt_91008]. */
# define DLT_API_ID_TPRXINDICATION           ((uint8)0x45u) /*!< ASR4.0 Dlt_TpRxIndication() service ID [SWS_Dlt_91007]. */
# define DLT_API_ID_STARTOFRECEPTION         ((uint8)0x46u) /*!< ASR4.0 Dlt_StartOfReception() service ID [SWS_Dlt_91006]. */
# define DLT_API_ID_TPTXCONFIRMATION         ((uint8)0x48u) /*!< ASR4.0 Dlt_TpTxConfirmation() service ID [SWS_Dlt_00756]. */
# define DLT_API_ID_MAINFUNCTION             ((uint8)0x50u) /*!< MSR4.0 Dlt_MainFunction() service ID. */
# define DLT_API_ID_SETSTATE                 ((uint8)0x51u) /*!< MSR4.0 Dlt_SetState() service ID. */
# define DLT_API_ID_GETSTATE                 ((uint8)0x52u) /*!< MSR4.0 Dlt_GetState() service ID. */

/* Error codes */
# define DLT_E_NO_ERROR                      ((uint8)0x00u) /*!< Error code: No error. */
# define DLT_E_PARAM                         ((uint8)0x01u) /*!< Error code: Development [SWS_Dlt_00727]. */
# define DLT_E_PARAM_POINTER                 ((uint8)0x02u) /*!< Error code: Development [SWS_Dlt_00727]. */
# define DLT_E_INIT_FAILED                   ((uint8)0x03u) /*!< Error code: Development [SWS_Dlt_00727]. */
# define DLT_E_REGISTRATION                  ((uint8)0x04u) /*!< Error code: Development [SWS_Dlt_00727]. */
# define DLT_E_MSG_LOOSE                     ((uint8)0x05u) /*!< Error code: [SWS_Dlt_00447]. */
# define DLT_E_SKIPPED_TRANSMISSION          ((uint8)0x05u) /*!< Error code: Runtime [SWS_Dlt_00728]. */
# define DLT_E_DEPRECATED_PARAMETER          ((uint8)0x06u) /*!< Error code: Runtime [SWS_Dlt_00728]. */
# define DLT_E_MULTIPLE_REQUESTS             ((uint8)0x07u) /*!< Error code: Runtime [SWS_Dlt_00728]. */
# define DLT_E_UNINITIALIZED                 ((uint8)0x10u) /*!< Error code: Development; DLT is not initialized. */
# define DLT_E_INVALID_STATE                 ((uint8)0x11u) /*!< Error code: Runtime; DLT is in an invalid state. */

# define DLT_INVALID_LOG_CHANNEL_INDEX       ((uint16)0xFFFFu)

# ifndef DLT_DEM_EVENT_LOG_LEVEL /* COV_DLT_MSR_COMPATIBILITY */
#  define DLT_DEM_EVENT_LOG_LEVEL DLT_LOG_INFO
# endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

 /* Check the version of Dlt_Cfg.h */
# if (  (DLT_CFG_MAJOR_VERSION != (6u)) \
     || (DLT_CFG_MINOR_VERSION != (0u)) )
#  error "Version numbers of Dlt_Cfg.h are inconsistent"
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 FUNCTIONLIKEMACRO */ /* MD_MSR_FctLikeMacro */

# if !defined(DLT_DUMMY_STATEMENT)     /* COV_DLT_MSR_COMPATIBILITY */
#  if defined (DLT_USE_DUMMY_STATEMENT)  
# define DLT_DUMMY_STATEMENT(statement) ((void)(statement))
#  else
# define DLT_DUMMY_STATEMENT(statement)
#  endif
# endif

# if !defined(DLT_DUMMY_STATEMENT_CONST)     /* COV_DLT_MSR_COMPATIBILITY */
#  if defined (DLT_USE_DUMMY_STATEMENT_CONST)  
# define DLT_DUMMY_STATEMENT_CONST(statement) ((void)(statement))
#  else
# define DLT_DUMMY_STATEMENT_CONST(statement)
#  endif
# endif


/* PRQA L:FUNCTIONLIKEMACRO */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define DLT_START_SEC_CONST_8
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


extern CONST(uint8, DLT_CONST)                     Dlt_ModuleTable[256];

# define DLT_STOP_SEC_CONST_8
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#  define DLT_START_SEC_VAR_NO_INIT_32
#  include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Variable is loaded with the last DET error code */
extern VAR(uint32, DLT_VAR_NO_INIT)                 Dlt_DetErrorCode;

#  define DLT_STOP_SEC_VAR_NO_INIT_32
#  include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define DLT_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# if defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) /* COV_DLT_FILTER_ASR_XCP */
/* Variable is loaded with DEM event status code. */
extern VAR(Dlt_DemEventStatusType, DLT_VAR_NO_INIT) Dlt_DemEventStatus;

/* Variable is loaded with message ID of non-verbose message . */
extern VAR(Dlt_MessageIDType, DLT_VAR_NO_INIT)      Dlt_NonVerboseMessageId;

#  if (DLT_USE_VERBOSE_MODE == STD_ON)
/* Buffer is loaded with payload of verbose message. */
extern VAR(uint8, DLT_VAR_NO_INIT)                  Dlt_VerboseMessageData[DLT_MAX_MESSAGE_LENGTH];
#  endif
# endif /* defined (DLT_USE_COMLAYER_XCP) && (DLT_USE_COMLAYER_XCP == STD_ON) */

# define DLT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define DLT_START_SEC_CODE
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Dlt_InitMemory
**********************************************************************************************************************/
/*! \brief       Power-up memory initialization
 *  \details     Initializes component variables in *_INIT_* sections at power up.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-106553
 *  \note        Use this function in case these variables are not initialized by the startup code.
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_InitMemory(void);

/**********************************************************************************************************************
 *  Dlt_Init
**********************************************************************************************************************/
/*! \brief       Initializes component
 *  \details     Initializes all component variables and sets the component state to initialized.
 *  \param[in]   ConfigPtr        Component configuration structure
 *  \pre         Interrupts are disabled.
 *  \pre         Module is uninitialized.
 *  \pre         Dlt_InitMemory has been called unless Dlt_ModuleInitialized is initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \spec        requires ConfigPtr != NULL_PTR;
 *  \endspec
 *  \synchronous TRUE
 *  \trace       CREQ-106553
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_Init(P2CONST(Dlt_ConfigType, AUTOMATIC, DLT_PBCFG) ConfigPtr);

# if(DLT_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Dlt_GetVersionInfo()
**********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo      Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \spec        requires VersionInfo != NULL_PTR;
 *  \endspec
 *  \config      This function is only available if (DLT_VERSION_INFO_API = STD_ON).
 *  \trace       CREQ-106554
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DLT_APPL_VAR) VersionInfo);
# endif

/**********************************************************************************************************************
 *  Dlt_DetForwardErrorTrace()
**********************************************************************************************************************/
/*! \brief       Service to forward error reports from Det to Dlt.
 *  \details     Builds and sends a log message containing all passed data.
 *  \param[in]   ModuleId         Module ID of calling module.
 *  \param[in]   InstanceId       The identifier of the index based instance of a module.
 *  \param[in]   ApiId            ID of API service in which error is detected.
 *  \param[in]   ErrorId          ID of detected development error.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_DetForwardErrorTrace(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**********************************************************************************************************************
 *  Dlt_DemTriggerOnEventStatus()
**********************************************************************************************************************/
/*! \brief       This service is provided by the Dem in order to call Dlt upon status changes.
 *  \details     Builds and sends a log message containing the passed data.
 *  \param[in]   EventId          Module ID of calling module.
 *  \param[in]   EventStatusOld   The identifier of the index based instance of a module.
 *  \param[in]   EventStatusNew   ID of API service in which error is detected.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \spec        requires EventId < DLT_NUM_DEM_EVENTS && EventId > 0;
 *  \endspec
 *********************************************************************************************************************/
FUNC(void, DLT_CODE) Dlt_DemTriggerOnEventStatus(Dem_EventIdType EventId,
                                                 Dem_EventStatusExtendedType EventStatusOld,
                                                 Dem_EventStatusExtendedType EventStatusNew);

/**********************************************************************************************************************
 *  Dlt_SendLogMessage()
**********************************************************************************************************************/
/*! \fn Std_ReturnType Dlt_SendLogMessage(Dlt_SessionIDType parg0, const Dlt_MessageLogInfoType* LogInfo, const uint8* LogData, uint16 LogDataLength)
 *  \brief       The service represents the interface to be used by software components to send log messages.
 *  \details     Builds and sends a log message containing the passed data.
 *  \param[in]   parg0            The session id.
 *  \param[in]   LogInfo          Structure containing the relevant information for filtering the message.
 *  \param[in]   LogData          Pointer to log data. This will be copied to payload of the log message.
 *  \param[in]   LogDataLength    Length of the log data.
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* FUNC(Std_ReturnType, DLT_CODE) Dlt_SendLogMessage(
  Dlt_SessionIDType parg0, 
  P2CONST(Dlt_MessageLogInfoType, AUTOMATIC, DLT_APPL_VAR) LogInfo, 
  P2CONST(uint8, AUTOMATIC, DLT_APPL_VAR) LogData, 
  uint16 LogDataLength);*/


# if (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON)

/**********************************************************************************************************************
 *  Appl_DltDemEventFilterCbk()
**********************************************************************************************************************/
/*! \brief       Checks if DEM event status has changed.
 *  \details     Must be implemented by user and should be used to compare old event status and new event status. The
 *               result should be returned.
 *  \param[in]   EventId          Identification of an Event by assigned event number. The Event number is configured
 *                                in the Dem:
*                                   Min.: 1 (0: Indication of no Event or Failure).
*                                   Max.: Result of configuration of Event Numbers in Dem (Max is either 255 or 65535).
 *  \param[in]   EventStatusOld   Extended event status before change.
 *  \param[in]   EventStatusNew   Detected / reported of event status.
 *  \return      TRUE             The DEM event has passed the filter (log message will be generated by the DLT).
 *  \return      FALSE            The DEM event has not passed the filter (no log message will be generated).
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      This function is only available if (DLT_DEM_EVENT_FILTERING_ENABLED = STD_ON).
 *********************************************************************************************************************/
FUNC(boolean, DLT_CODE) Appl_DltDemEventFilterCbk(
  Dem_EventIdType EventId,
  Dem_EventStatusExtendedType EventStatusOld,
  Dem_EventStatusExtendedType EventStatusNew);

# endif /* (DLT_DEM_EVENT_FILTERING_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  Dlt_MainFunction()
**********************************************************************************************************************/
/*! \fn          void Dlt_MainFunction(void)
 *  \brief       Checks periodically the Dlt status.
 *  \details     Handles cyclically the state machine(s).
 *  \pre         -
 *  \context     TASK|ISR
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
/* FUNC(void, DLT_CODE) Dlt_MainFunction(void); */

# define DLT_STOP_SEC_CODE
# include "Dlt_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  EXCLUSIVE AREA DEFINITION
 **********************************************************************************************************************/
/*!
 * \exclusivearea DLT_EXCLUSIVE_AREA_APIS
 * Protects the global variables against concurrent modifications in case of reentrant calls.
 * \protects Buffers, states, and global variables
 * \usedin Dlt_MainFunction, Dlt_SetState, Dlt_RegisterContext, Dlt_DetForwardErrorTrace, Dlt_DemTriggerOnEventStatus, Dlt_SendLogMessage, Dlt_SendTraceMessage
 * \exclude All other APIs and callback functions.
 * \length LONG This exclusive area covers calls to several sub-functions.
 * \endexclusivearea
 */

/*!
 * \exclusivearea DLT_EXCLUSIVE_AREA_TX
 * Protects the global buffer against concurrent modifications in case of reentrant calls.
 * \protects Dlt_SendPdu_DataLength, Dlt_SendPdu_DataPtr
 * \usedin Dlt_CopyTxData
 * \exclude All APIs and other callback functions.
 * \length MEDIUM Copy of tx data to lower layer's buffer.
 * \endexclusivearea
 */

/*!
 * \exclusivearea DLT_EXCLUSIVE_AREA_RX
 * Protects the global buffer against concurrent modifications in case of reentrant calls.
 * \protects Dlt_ReceiveBuffer, Dlt_CopyRxDataLength, Dlt_CopyRxDataCounter, Dlt_RxIndicationOccured
 * \usedin Dlt_StartOfReception, Dlt_CopyRxData
 * \exclude All APIs and other callback functions.
 * \length MEDIUM Copy of rx data from lower layer's buffer.
 * \endexclusivearea
 */

#endif

/**********************************************************************************************************************
 *  END OF FILE: Dlt.h
 *********************************************************************************************************************/
