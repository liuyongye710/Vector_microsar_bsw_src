/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*        \file   vFotaH_Services.h
 *        \brief  vFotaH service header file
 *
 *        \details
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined(VFOTAH_SERVICES_H)
#define VFOTAH_SERVICES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "vFotaH.h"
#include "Dcm.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* DCM request message */
#define VFOTAH_DCM_REQ_MSG_MIN_LENGTH               ((Dcm_MsgLenType)0x04u) /*!< UdsMessageChecks: The minimum length of request messages. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_INDEX    ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The start index where the address length is located in request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_MIN      ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The minimum length of memory address length in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_MAX      ((Dcm_MsgLenType)0x04u) /*!< UdsMessageChecks: The maximum length of memory address length in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_INDEX    ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The start index where the size length is located in request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_MIN      ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The minimum length of memory size length in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_MAX      ((Dcm_MsgLenType)0x04u) /*!< UdsMessageChecks: The maximum length of memory size length in the request message. */
#define VFOTAH_DCM_REQ_MSG_OFFSET                   ((Dcm_MsgLenType)0x02u) /*!< UdsMessageChecks: An offset for the minimum size of the request message. */
#define VFOTAH_DCM_REQ_MSG_DATA_PROCESSING_INDEX    ((Dcm_MsgLenType)0x00u) /*!< UdsMessageChecks: The start index of the encoding type in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_INDEX           ((Dcm_MsgLenType)0x02u) /*!< UdsMessageChecks: The start index of the memory address in the request message. */

/* UDS Service IDs */
#define VFOTAH_UDS_SERVICE_ID_0X10_DIAGNOSTIC_SESSION_CONTROL (0x10u) /*!< SID: Diagnostic session control. */
#define VFOTAH_UDS_SERVICE_ID_0X11_ECU_RESET (0x11u) /*!< SID: ECU reset. */
#define VFOTAH_UDS_SERVICE_ID_0X22_READ_DATA_BY_IDENTIFIER (0x22u) /*!< SID: Read Data by Identifier. */
#define VFOTAH_UDS_SERVICE_ID_0X2E_WRITE_DATA_BY_IDENTIFIER (0x2Eu) /*!< SID: Write Data by Identifier. */
#define VFOTAH_UDS_SERVICE_ID_0X31_ROUTINE_CONTROL (0x31u) /*!< SID: Routine Control. */
#define VFOTAH_UDS_SERVICE_ID_0X34_REQUEST_DOWNLOAD (0x34u) /*!< SID: Request Download. */
#define VFOTAH_UDS_SERVICE_ID_0X36_TRANSFER_DATA (0x36u) /*!< SID: Transfer Data. */
#define VFOTAH_UDS_SERVICE_ID_0X37_REQUEST_TRANSFER_EXIT (0x37u) /*!< SID: Request Transfer Exit. */

/* UDS Sub-Services: */

/*  - RoutineControl */
#define VFOTAH_UDS_SUBSERVICE_0X3101_START_OF_ROUTINE (0x01u) /*!< RoutineControl: First byte (StartOfRoutine). */
#define VFOTAH_UDS_SUBSERVICE_0X3102_STOP_OF_ROUTINE (0x02u) /*!< RoutineControl: First byte (EndOfRoutine). */
#define VFOTAH_UDS_SUBSERVICE_0X3103_STATUS_OF_ROUTINE (0x03u) /*!< RoutineControl: First byte (GetResultOfRoutine). */

/* DCM session IDs */
#define VFOTAH_DCM_SESSION_ID_DEFAULT (0x01u) /*!< UdsSessions: Default. */
#define VFOTAH_DCM_SESSION_ID_PROGRAMMING (0x02u) /*!< UdsSessions: Programming. */
#define VFOTAH_DCM_SESSION_ID_EXTENDED (0x03u) /*!< UdsSessions: Extended. */
#if !defined VFOTAH_DCM_SESSION_ID_FOTA
#define VFOTAH_DCM_SESSION_ID_FOTA (0x42u) /*!< UdsSessions: FOTA. */
#endif

/* DCM request message */
#define VFOTAH_DCM_REQ_MSG_MIN_LENGTH               ((Dcm_MsgLenType)0x04u) /*!< UdsMessageChecks: The minimum length of request messages. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_INDEX    ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The start index where the address length is located in request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_MIN      ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The minimum length of memory address length in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_MAX      ((Dcm_MsgLenType)0x04u) /*!< UdsMessageChecks: The maximum length of memory address length in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_INDEX    ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The start index where the size length is located in request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_MIN      ((Dcm_MsgLenType)0x01u) /*!< UdsMessageChecks: The minimum length of memory size length in the request message. */
#define VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_MAX      ((Dcm_MsgLenType)0x04u) /*!< UdsMessageChecks: The maximum length of memory size length in the request message. */
#define VFOTAH_DCM_REQ_MSG_OFFSET                   ((Dcm_MsgLenType)0x02u) /*!< UdsMessageChecks: An offset for the minimum size of the request message. */
#define VFOTAH_DCM_REQ_MSG_USE_COMPRESSION_MASK     ((Dcm_MsgLenType)0xF0u) /*!< UdsMessageChecks: A mask to get the compression type of the request message. */
#define VFOTAH_DCM_REQ_MSG_USE_COMPRESSION_INDEX    ((Dcm_MsgLenType)0x00u) /*!< UdsMessageChecks: The start index of the compression type in the request message. */
#define VFOTAH_DCM_REQ_MSG_USE_COMPRESSION_DISABLED ((Dcm_MsgLenType)0x00u) /*!< UdsMessageChecks: The compression type; DISABLED. */
#define VFOTAH_DCM_REQ_MSG_USE_ENCODING_MASK        ((Dcm_MsgLenType)0x0Fu) /*!< UdsMessageChecks: A mask to get the encoding type of the request message. */
#define VFOTAH_DCM_REQ_MSG_USE_ENCODING_INDEX       ((Dcm_MsgLenType)0x00u) /*!< UdsMessageChecks: The start index of the encoding type in the request message. */
#define VFOTAH_DCM_REQ_MSG_USE_ENCODING_DISABLED    ((Dcm_MsgLenType)0x00u) /*!< UdsMessageChecks: The encoding type; DISABLED. */
#define VFOTAH_DCM_REQ_MSG_MEM_ADDR_INDEX           ((Dcm_MsgLenType)0x02u) /*!< UdsMessageChecks: The start index of the memory address in the request message. */

/* DCM Routine Infos */
#define VFOTAH_ROUTINE_STATUS_COMPLETE (0x00u) /*!< Routine completed successfully. */
#define VFOTAH_ROUTINE_STATUS_ABORTED (0x01u) /*!< Routine failed. */
#define VFOTAH_ROUTINE_STATUS_ACTIVE (0x02u) /*!< Routine is still active. */

#define VFOTAH_NO_ROUTINE_ID (0x00u)

#define VFOTAH_ERASE_ROUTINE_ID (0x01u)
#define VFOTAH_ERASE_ROUTINE_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_ERASE_ROUTINE_INFO_PENDING (uint8)(VFOTAH_ROUTINE_STATUS_ACTIVE)
#define VFOTAH_ERASE_ROUTINE_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_PERFORM_SWITCH_ID (0x02u)
#define VFOTAH_PERFORM_SWITCH_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_PERFORM_SWITCH_INFO_PENDING (uint8)(VFOTAH_ROUTINE_STATUS_ACTIVE)
#define VFOTAH_PERFORM_SWITCH_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_VERIFY_MODULE_ID (0x03u)
#define VFOTAH_VERIFY_MODULE_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_VERIFY_MODULE_INFO_PENDING (uint8)(VFOTAH_ROUTINE_STATUS_ACTIVE)
#define VFOTAH_VERIFY_MODULE_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_MODULE_START_ID (0x04u)
#define VFOTAH_MODULE_START_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_MODULE_START_INFO_PENDING (uint8)(VFOTAH_ROUTINE_STATUS_ACTIVE)
#define VFOTAH_MODULE_START_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_PREPARE_ACTIVATION_ID (0x05u)
#define VFOTAH_PREPARE_ACTIVATION_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_PREPARE_ACTIVATION_INFO_PENDING (uint8)(VFOTAH_ROUTINE_STATUS_ACTIVE)
#define VFOTAH_PREPARE_ACTIVATION_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_UPDATE_COMMIT_ID (0x06u)
#define VFOTAH_UPDATE_COMMIT_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_UPDATE_COMMIT_INFO_PENDING (uint8)(VFOTAH_ROUTINE_STATUS_ACTIVE)
#define VFOTAH_UPDATE_COMMIT_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_ID (0x07u)
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_CHECK_PROGRAMMING_PRECONDITIONS_ID (0x08u)
#define VFOTAH_CHECK_PROGRAMMING_PRECONDITIONS_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_CHECK_PROGRAMMING_PRECONDITIONS_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_CHECK_UPDATE_START_ID (0x09u)
#define VFOTAH_CHECK_UPDATE_START_INFO_COMPLETE (uint8)(VFOTAH_ROUTINE_STATUS_COMPLETE)
#define VFOTAH_CHECK_UPDATE_START_INFO_FAILED (uint8)(VFOTAH_ROUTINE_STATUS_ABORTED)

#define VFOTAH_ROUTINE_NONE_ID (0x0Au)

/* Module state as reported by ReadResumeInfo */
#define VFOTAH_RESUME_MODULE_STATE_PART_VALID       (0x00u)
#define VFOTAH_RESUME_MODULE_STATE_MODULE_VALID     (0x01u)
#define VFOTAH_RESUME_MODULE_STATE_MODULE_INVALID   (0x02u)
#define VFOTAH_RESUME_MODULE_STATE_ERASE_STARTED    (0x03u)
#define VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED     (0x04u)
#define VFOTAH_RESUME_MODULE_STATE_ERASED           (0x05u)

/* Routine operation */
#define VFOTAH_VERIFY_OPTION_CRC                    (0x01u)
#define VFOTAH_VERIFY_OPTION_SIGNATURE              (0x02u)

#define VFOTAH_MODULE_START_DNLD                    (0x00u)
#define VFOTAH_MODULE_START_SYNC                    (0x01u)

#define VFOTAH_PARTITION_SWITCH_OPTION_REVERT       (0x00u)
#define VFOTAH_PARTITION_SWITCH_OPTION_ACTIVATE     (0x01u)
#define VFOTAH_PARTITION_SWITCH_OPTION_PENDING      (0x02u)
#define VFOTAH_PARTITION_SWITCH_OPTION_NONE         (0xffu)

/* Verification Level */
#define VFOTAH_VERIFICATION_LEVEL_CRC               (0x00u)
#define VFOTAH_VERIFICATION_LEVEL_SIGNATURE         (0x01u)

/* Check Programming Dependencies status values */
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SUCCESS (0x00u)         /*!< Software is consistent. */
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_GENERAL_FAILURE (0x01u) /*!< An undefined error leads to inconsistent modules. */
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_HWSW_INCOMP (0x02u)     /*!< The software is incompatible to the hardware. */
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SWSW_INCOMP (0x03u)     /*!< At least one module is inconsistent. */
#define VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_BLOCK_MISSING (0x04u)   /*!< Missing block installation. */

#if !defined VFOTAH_REQUEST_DOWNLOAD_RESPONSE_LENGTH
# define VFOTAH_REQUEST_DOWNLOAD_RESPONSE_LENGTH    (0x05u) /*!< RequestDownload: ResponseLength; 1 byte for LengthFormatIdentifier and 2 bytes for BlockLength. */
#endif

#if !defined VFOTAH_REQUEST_DOWNLOAD_LENGTHFORMATIDENTIFIER
# define VFOTAH_REQUEST_DOWNLOAD_LENGTHFORMATIDENTIFIER (0x40u) /*!< RequestDownload: LengthFormatIdentifier; bit 7-4: Length in bytes, bit 3-0: Reserved (set to 0). */
#endif

/* Security access type for reprogramming */
#if !defined (VFOTAH_UDS_SECURITY_ACCESS_TYPE)
# define VFOTAH_UDS_SECURITY_ACCESS_TYPE            (0x11u)
#endif

#define VFOTAH_PROGRESS_RESULT                      (100u)  /*!< The progress is currently not supported and always signals 100%. */

/* Module Status Flags */
#define VFOTAH_MODULE_STATUS_COMMIT                 (0x01u) /*!< Flag to signal a module with commit status. */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VFOTAH_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/*!< NvM block used to store information about the Modules, e.g. fingerprint */
extern VAR(vFotaH_NvMInfoBlockType, VFOTAH_VAR_NOINIT) vFotaH_NvMInfoBlock[VFOTAH_NUMBER_OF_MODULES];

#define VFOTAH_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/*
 * APIs called by vFotaH:
 */
/**********************************************************************************************************************
 *  vFotaH_Serv_InitMemory()
 *********************************************************************************************************************/
/*! \fn          vFotaH_Serv_InitMemory
 *  \brief       Initializes the service specific global data of vFotaH which must be available before initialization.
 *  \details     -        
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Serv_InitMemory(void);

/**********************************************************************************************************************
 *  vFotaH_Serv_PreInit()
 *********************************************************************************************************************/
/*! \fn          vFotaH_Serv_PreInit
 *  \brief       Pre-initializes the service specific global data of vFotaH.
 *  \details     -        
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
 *********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_Serv_PreInit(void);

/**********************************************************************************************************************
 *  vFotaH_Serv_Init()
 *********************************************************************************************************************/
/*! \fn          vFotaH_Serv_Init
 *  \brief       Initializes the service specific global data of vFotaH.
 *  \details     -        
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
 *********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Serv_Init(void);


/***********************************************************************************************************************
 *  vFotaH_DcmReadSoftwareVersionLength()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmReadSoftwareVersionLength()
 *  \brief         Gets data length of the data element.
 *  \details       This function is a request from the DCM to return the data length of a data
 *                 element. /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadDataLengthFnc.
 *  \param[in]     opStatus       The operation status
 *  \param[out]    DataLength     Data length
 *  \return        DCM_E_OK       The operation is finished
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadSoftwareVersionLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, VFOTAH_VAR_NOINIT) DataLength);*/

/***********************************************************************************************************************
*  vFotaH_DcmReadActiveSoftwareVersion()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmReadActiveSoftwareVersion()
 *  \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to get a data value of a DID/PID.
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     opStatus       The operation status
 *  \param[out]    Data           Data buffer
 *  \return        DCM_E_OK       Read operation succeeded
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadActiveSoftwareVersion(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data);*/

/***********************************************************************************************************************
*  vFotaH_DcmReadInactiveSoftwareVersion()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmReadInactiveSoftwareVersion()
 *  \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to get a data value of a DID/PID.
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     opStatus       The operation status
 *  \param[out]    Data           Data buffer
 *  \return        DCM_E_OK       Read operation succeeded
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadInactiveSoftwareVersion(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data);*/

/***********************************************************************************************************************
*  vFotaH_DcmReadActiveSoftwareFingerprint()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmReadActiveSoftwareFingerprint()
 *  \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to get a data value of a DID/PID.
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     opStatus       The operation status
 *  \param[out]    Data           Data buffer
 *  \return        DCM_E_OK       Read operation succeeded
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadActiveSoftwareFingerprint(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data);*/

/***********************************************************************************************************************
 *  vFotaH_DcmReadSoftwareFingerprintLength()
***********************************************************************************************************************/
/*! 
 *  \fn            vFotaH_DcmReadSoftwareFingerprintLength()
 *  \brief         Gets data length of the fingerprint information.
 *  \details       This function is a request from the DCM to return the data length of a data
 *                 element. /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadDataLengthFnc.
 *  \param[in]     opStatus       The operation status
 *  \param[out]    DataLength     Data length
 *  \return        DCM_E_OK       The operation is finished
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadSoftwareFingerprintLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, VFOTAH_VAR_NOINIT) DataLength);*/

/***********************************************************************************************************************
*  vFotaH_DcmReadInactiveSoftwareFingerprint()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmReadInactiveSoftwareFingerprint()
 *  \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to get a data value of a DID/PID.
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     opStatus       The operation status
 *  \param[out]    Data           Data buffer
 *  \return        DCM_E_OK       Read operation succeeded
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadInactiveSoftwareFingerprint(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data);*/

/***********************************************************************************************************************
 *  vFotaH_DcmVerifyModuleStart()
***********************************************************************************************************************/
/*! 
 *  \fn            vFotaH_DcmVerifyModuleStart()
 *  \brief         Starts a verify execution.
 *  \details       This function is a request from DCM to start a verify operation, either CRC or Signature.
 *  \param[in]     In_ModuleHd        The module handle.
 *  \param[in]     In_VerifyOption    The verify option (CRC or Signature).
 *  \param[in]     In_ComplexData     The CRC or Signature data (dynamic request signal).
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Status of the routine
 *  \param[in]     DataLength         Concrete length of the dynamic request signal
 *  \param[out]    ErrorCode                   Optional error code:
 *                                             - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                             - DCM_E_BUSYREPEATREQUEST: The vFotaH is busy, repeat request later.
 *                                             - DCM_E_REQUESTSEQUENCEERROR: The module info was not set with moduleStart.
 *                                             - DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT: The passed length is not in valid range.
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmVerifyModuleStart(
  uint8 In_ModuleHd,
  uint8 In_VerifyOption,
  P2CONST(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) In_ComplexData,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  uint16 DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmVerifyModuleResult()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmVerifyModuleResult()
 *  \brief         Reads a verify results.
 *  \details       This function is a request from DCM to read a routine results.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    Out_Progress       Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmVerifyModuleResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmUpdateStart()
***********************************************************************************************************************/
/*! 
 *  \fn            vFotaH_DcmUpdateStart()
 *  \brief         Initiates a update sequence.
 *  \details       This function is a request from DCM to start a update sequence.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmUpdateStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmModuleStartStart()
***********************************************************************************************************************/
/*! 
 *  \fn            vFotaH_DcmModuleStartStart()
 *  \brief         Is used to initiate a update sequence of a module.
 *  \details       This function is a request from DCM to start a module update sequence.
 *  \param[in]     In_RoutineOption   Ether download or sync operation.
 *  \param[in]     In_ModuleHd        The module handle.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    ErrorCode          Optional error code:
 *                                    - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                    - DCM_E_BUSYREPEATREQUEST: The vFotaH is busy, repeat request later.
 *                                    - DCM_E_REQUESTSEQUENCEERROR: Another module is in state download started.
 *                                                                  This module must be handled first.
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmModuleStartStart(
  uint8 In_RoutineOption,
  uint8 In_ModuleHd,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmModuleStartResult()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmModuleStartResult()
 *  \brief         Reads a routine results.
 *  \details       This function is a request from DCM to read a routine results.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    Out_Progress       Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmModuleStartResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmPrepareActivationStart()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmPrepareActivationStart()
 *  \brief         Prepare the activation by creating a backup if required.
 *  \details       -
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPrepareActivationStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmPrepareActivationResult()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmPrepareActivationResult()
 *  \brief         Reads a routine results.
 *  \details       This function is a request from DCM to read a routine results.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    Out_Progress       Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPrepareActivationResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmPerformPartitionSwitchStart()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmPerformPartitionSwitchStart()
 *  \brief         Performs a partition switch.
 *  \details       After a partition switch is requested an reset will performed and the switch is executed by the FBL.
 *  \param[in]     In_SwitchOption    Activation or Revert operation.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    ErrorCode          Optional error code:
 *                                    - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                    - DCM_E_BUSYREPEATREQUEST: The vFotaH is busy, repeat request later.
 *                                    - DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION: Error in vSwUpdM handling.
 *                                    - DCM_E_REQUESTSEQUENCEERROR: Missing check of ProgrammingPreconditions or ProgrammingDependencies.
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPerformPartitionSwitchStart(
  uint8 In_SwitchOption,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmPerformPartitionSwitchResult()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmPerformPartitionSwitchResult()
 *  \brief         Reads a routine results.
 *  \details       This function is a request from DCM to read a routine results.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    Out_Progress       Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPerformPartitionSwitchResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmUpdateCommitStart()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmUpdateCommitStart()
 *  \brief         Starts a routine execution.
 *  \details       This function is a request from DCM to start a routine execution.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmUpdateCommitStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmUpdateCommitResult()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmUpdateCommitResult()
 *  \brief         Reads a routine results.
 *  \details       This function is a request from DCM to read a routine results.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    Out_Progress       Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmUpdateCommitResult(
  Dcm_OpStatusType OpStatus, P2VAR(uint8,
  AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmEraseStart()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmEraseStart()
 *  \brief         Starts a erase routine execution.
 *  \details       This function erases one module. It can only be used in combination with ModuleStart.
 *  \param[in]     In_ALFI                     Address and length format
 *  \param[in]     In_ComplexAddressAndLength  Variable-length input data provided in the routine control request
 *  \param[in]     OpStatus                    The operation status
 *  \param[out]    Out_RoutineInfo             Fixed-length output data to provide in the routine control response
 *  \param[in]     DataLength                  Concrete length of the dynamic request signal
 *  \param[out]    ErrorCode                   Optional error code:
 *                                             - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                             - DCM_E_BUSYREPEATREQUEST: The vFotaH is busy, repeat request later.
 *                                             - DCM_E_REQUESTSEQUENCEERROR: The module info was not set with moduleStart.
 *                                             - DCM_E_REQUESTOUTOFRANGE: The passed address or length are not in valid range.
 *  \return        DCM_E_OK                    The operation is finished
 *  \return        DCM_E_PENDING               The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP           Forces a RCR-RP response
 *                                             The call out will called again once the response is sent. The OpStatus
 *                                             parameter will contain the transmission result
 *  \return        DCM_E_NOT_OK                The operation has failed. A concrete NRC shall be set, otherwise the DCM
 *                                             sends NRC 0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmEraseStart(
  uint8 In_ALFI,
  P2CONST(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) In_ComplexAddressAndLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  uint16 DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmEraseResult()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmEraseResult()
 *  \brief         Reads a routine results.
 *  \details       This function is a request from DCM to read a routine results.
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    Out_Progress       Fixed-length output data to provide in the routine control response
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmEraseResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmCheckProgrammingDependencies()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmCheckProgrammingDependencies()
 *  \brief         Check whether software is consistent.
 *  \details       -
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    ErrorCode                   Optional error code:
 *                                             - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                             - DCM_E_BUSYREPEATREQUEST: The vFotaH is busy, repeat request later.
 *                                             - DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION: Error in vSwUpdM handling.
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmCheckProgrammingDependencies(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmCheckProgrammingPreconditions()
***********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmCheckProgrammingPreconditions()
 *  \brief         Check whether vehicle is in a safe state.
 *  \details       -
 *  \param[in]     OpStatus           The operation status
 *  \param[out]    Out_RoutineInfo    Fixed-length output data to provide in the routine control response
 *  \param[out]    ErrorCode                   Optional error code:
 *                                             - DCM_E_BUSYREPEATREQUEST: The vFotaH is busy, repeat request later.
 *  \return        DCM_E_OK           The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmCheckProgrammingPreconditions(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/**********************************************************************************************************************
 *  vFotaH_DcmRequestDownload()
 *********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmRequestDownload()
 *  \brief         Starts a sequence of transfer data.
 *  \details       This is the Request Download service. It gets all data required for the upcoming received data. It
 *                 prepares the vSwUpdM according to the request (opens the inactive partition, opens the corresponding 
 *                 module, optionally creates a new segment, opens the segment, erases the corresponding region and
 *                 starts the stream).
 *  \param[in]     opStatus              The current status of DCM:
 *                                        - DCM_INITIAL: The initial call to this service.
 *                                        - DCM_PENDING: repeated call to this service.
 *                                        - DCM_CANCEL:  This service is forced to be terminated.
 *  \param[in,out] pMsgContext           Pointer to the request data and the response data.
 *  \param[out]    ErrorCode             Optional error code:
 *                                        - DCM_E_POSITIVERESPONSE: no error occurred.
 *                                        - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                        - DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT: Invalid message length.
 *                                        - DCM_E_REQUESTOUTOFRANGE: Number of address/length bytes invalid.
 *                                        - DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT: Request message too short.
 *                                        - DCM_E_GENERALPROGRAMMINGFAILURE: Error occurred during download.
 *  \return        DCM_E_NOT_OK          Error because of invalid pointer or service called before initialization.
 *  \return        DCM_E_PENDING         Service is still pending.
 *  \return        DCM_E_PROCESSINGDONE  Service finished successfully or with failure.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 *  \ingroup       service
 *********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmRequestDownload(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode);*/

/**********************************************************************************************************************
 *  vFotaH_DcmTransferData()
 *********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmTransferData()
 *  \brief         Provides data in the transfer data sequence.
 *  \details       This is the transfer data service. Indicates the vSwUpdM that stream data is available. The vSwUpdM
 *                 gets the data asynchronously via calls to vFotaH_vSwUpdMCopyStreamData.
 *  \param[in]     opStatus              The current status of DCM:
 *                                        - DCM_INITIAL: The initial call to this service.
 *                                        - DCM_PENDING: repeated call to this service.
 *                                        - DCM_CANCEL:  This service is forced to be terminated.
 *  \param[in,out] pMsgContext           Pointer to the request data and the response data.
 *  \param[out]    ErrorCode             Optional error code:
 *                                        - DCM_E_POSITIVERESPONSE: no error occurred.
 *                                        - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                        - DCM_E_GENERALPROGRAMMINGFAILURE: Error occurred during writing.
 *                                        - DCM_E_REQUESTSEQUENCEERROR: The order of 0x34, 0x36 and 0x37 was violated. 
 *  \return        DCM_E_NOT_OK          Error because of invalid pointer or service called before initialization.
 *  \return        DCM_E_PENDING         Service is still pending.
 *  \return        DCM_E_PROCESSINGDONE  Service finished successfully or with failure.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 *  \pre           The calls to 0x34 have to be finished successfully.
 *  \ingroup       service
 *********************************************************************************************************************/
/* PRQA S 0777 3 */ /* MD_MSR_Rule5.1 */
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmTransferData(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode);*/

/**********************************************************************************************************************
 *  vFotaH_DcmRequestTransferExit()
 *********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmRequestTransferExit()
 *  \brief         Finalizes the transfer data sequence.
 *  \details       This is the request transfer exit service. It forwards the vSwUpdM the end of the download sequence
 *                 (it ends the stream, finalizes the updated segment, closes the segment, finalizes the module and
 *                 closes the module).
 *  \param[in]     opStatus              The current status of DCM:
 *                                        - DCM_INITIAL: The initial call to this service.
 *                                        - DCM_PENDING: repeated call to this service.
 *                                        - DCM_CANCEL:  This service is forced to be terminated.
 *  \param[in,out] pMsgContext           Pointer to the request data and the response data.
 *  \param[out]    ErrorCode             Optional error code:
 *                                        - DCM_E_POSITIVERESPONSE: no error occurred.
 *                                        - DCM_E_CONDITIONSNOTCORRECT: Any condition is invalid.
 *                                        - DCM_E_GENERALPROGRAMMINGFAILURE: Error occurred during writing.
 *                                        - DCM_E_REQUESTSEQUENCEERROR: The order of 0x34, 0x36 and 0x37 was violated. 
 *  \return        DCM_E_NOT_OK          Error because of invalid pointer or service called before initialization.
 *  \return        DCM_E_PENDING         Service is still pending.
 *  \return        DCM_E_OK              Service finished successfully or with failure.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 *  \pre           The calls to 0x36 have to be finished successfully.
 *  \ingroup       service
 *********************************************************************************************************************/
/* PRQA S 0777 3 */ /* MD_MSR_Rule5.1 */
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmRequestTransferExit(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode);*/

/***********************************************************************************************************************
 *  vFotaH_DcmReadDownloadResumeAddress()
***********************************************************************************************************************/
/*! 
 *  \fn            vFotaH_DcmReadDownloadResumeAddress()
 *  \brief         Reads the Resume address.
 *  \details       This function reads the address of Resume information which is only valid in module state
 *                 VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED
 *  \param[in]     opStatus       The operation status
 *  \param[out]    Data           Data buffer
 *  \return        DCM_E_OK       Read operation succeeded
 *  \return        DCM_E_NOT_OK   The operation has failed
 *  \return        DCM_E_PENDING  The operation not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/* FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadDownloadResumeAddress(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data); */

/**********************************************************************************************************************
 *  vFotaH_DcmReadResumeInfo()
 *********************************************************************************************************************/
/*!
 *  \fn            vFotaH_DcmReadResumeInfo()
 *  \brief         Reads the module resume information from vSwUpdM and responds them.
 *  \details       Reads the Module state from vSwUpdM an reports the state for each individual Module.
 *  \param[in]     OpStatus              The current status of DCM:
 *                                        - DCM_INITIAL: The initial call to this service.
 *                                        - DCM_PENDING: repeated call to this service.
 *                                        - DCM_CANCEL:  This service is forced to be terminated.
 *  \param[in,out] Data                  Pointer to the response data. vFotaH copies resume info into this response.
 *  \return        DCM_E_OK              The service request succeeded.
 *  \return        DCM_E_PENDING         The service request is pending.
 *  \return        DCM_E_NOT_OK          The service request failed.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Data must have at least a length of 10 bytes.
 *  \ingroup       service
 *********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadResumeInfo(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data);*/

/***********************************************************************************************************************
 *  vFotaH_DcmWriteInactiveSoftwareFingerprint()
***********************************************************************************************************************/
/*! 
 *  \fn            vFotaH_DcmWriteInactiveSoftwareFingerprint()
 *  \brief         Writes fingerprint.
 *  \details       This function is a request from the DCM to write the fingerprint
 *                 used during erase operation.
 *  \param[in]     Data         Data buffer
 *  \param[out]    ErrorCode    Negative response code
 *  \return        DCM_E_OK     The operation is finished
 *  \return        DCM_E_NOT_OK The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
***********************************************************************************************************************/
/*FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmWriteInactiveSoftwareFingerprint(
  P2CONST(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode);*/

/**********************************************************************************************************************
 *  vFotaH_DcmSessionChangeNotification()
 *********************************************************************************************************************/
/*!
 *  \fn          vFotaH_DcmSessionChangeNotification()
 *  \brief       Notifies that the active diagnostic session just changed.
 *  \details     vFotaH is notified if the FOTA session or another diagnostic session is entered. Some vFotaH services
 *               are only available in the FOTA session.
 *  \param[in]   formerSesCtrlId         The diagnostic session left.
 *  \param[in]   newSesCtrlId            The diagnostic session entered.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     service
 *********************************************************************************************************************/
/*FUNC(void, VFOTAH_CODE) vFotaH_DcmSessionChangeNotification(
  Dcm_SesCtrlType formerSesCtrlId,
  Dcm_SesCtrlType newSesCtrlId);*/
  
/***********************************************************************************************************************
 *  vFotaH_DcmSecLevelChangeNotification()
***********************************************************************************************************************/
/*! \fn            vFotaH_DcmSecLevelChangeNotification
 *  \brief         This function will be called at a security access level state transition.
 *  \details       -
 *  \param[in]     formerState  Specifies the former security access level ID (source state of transition)
 *  \param[in]     newState     Specifies the new security access level ID (target state of transition)
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function argument values have the same definition as the ones returned by the API
 *                 Dcm_GetSecurityLevel().
***********************************************************************************************************************/
/* FUNC(void, VFOTAH_CODE) vFotaH_DcmSecLevelChangeNotification(Dcm_SecLevelType formerState, Dcm_SecLevelType newState); */

/**********************************************************************************************************************
*  vFotaH_ServicesMainFunction()
*********************************************************************************************************************/
/*! \fn            vFotaH_ServicesMainFunction
 *  \brief         Handle asynchronous work.
 *  \details       -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       partition
*********************************************************************************************************************/
FUNC(void, VFOTAH_CODE) vFotaH_ServicesMainFunction(void);


/**********************************************************************************************************************
*  vFotaH_Rollback()
*********************************************************************************************************************/
/*! \fn            vFotaH_Rollback
 *  \brief         Perform software triggered rollback.
 *  \details       This service can be used to trigger a rollback. It is allowed after activation and before commit.
 *  \return        E_OK          The rollback is triggered.
 *  \return        E_NOT_OK      A rollback is not allowed.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *  \ingroup       service
*********************************************************************************************************************/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Rollback(void);

#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#endif /* VFOTAH_SERVICES_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Services.h
 *********************************************************************************************************************/
