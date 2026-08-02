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
/*        \file
 *        \brief  vFotaH_Priv header file
 *
 *        \details -
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

#ifndef VFOTAH_PRIV_H
#define VFOTAH_PRIV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ----- API service IDs ----- */
typedef uint8 vFotaH_ServiceId;
#define VFOTAH_SID_INIT_MEMORY                  (vFotaH_ServiceId)(0x00u) /*!< Service ID: vFotaH_InitMemory() */
#define VFOTAH_SID_INIT                         (vFotaH_ServiceId)(0x01u) /*!< Service ID: vFotaH_Init() */
#define VFOTAH_SID_GET_VERSION_INFO             (vFotaH_ServiceId)(0x02u) /*!< Service ID: vFotaH_GetVersionInfo() */
#define VFOTAH_SID_MAIN_FUNCTION                (vFotaH_ServiceId)(0x03u) /*!< Service ID: vFotaH_MainFunction() */
#define VFOTAH_SID_SESSION_CHANGE_NOTIFICATION  (vFotaH_ServiceId)(0x04u) /*!< Service ID: vFotaH_DcmSessionChangeNotification() */
#define VFOTAH_SID_DIAGNOSTIC_SERVICE_0x34      (vFotaH_ServiceId)(0x06u) /*!< Service ID: vFotaH_DcmRequestDownload() */
#define VFOTAH_SID_DIAGNOSTIC_SERVICE_0x36      (vFotaH_ServiceId)(0x07u) /*!< Service ID: vFotaH_DcmTransferData() */
#define VFOTAH_SID_DIAGNOSTIC_SERVICE_0x37      (vFotaH_ServiceId)(0x08u) /*!< Service ID: vFotaH_DcmRequestTransferExit() */
#define VFOTAH_SID_FOTASTATE_NVM_JOBEND         (vFotaH_ServiceId)(0x09u) /*!< Service ID: vFotaH_NvMFotaStateJobEnd() */
#define VFOTAH_SID_READ_RESUME_INFO             (vFotaH_ServiceId)(0x10u) /*!< Service ID: vFotaH_DcmReadResumeInfo() */
#define VFOTAH_SID_READ_ACTIVE_SW_VERSION       (vFotaH_ServiceId)(0x11u) /*!< Service ID: vFotaH_DcmReadActiveSoftwareVersion() */
#define VFOTAH_SID_READ_INACTIVE_SW_VERSION     (vFotaH_ServiceId)(0x12u) /*!< Service ID: vFotaH_DcmReadInactiveSoftwareVersion() */
#define VFOTAH_SID_MODULE_START_START           (vFotaH_ServiceId)(0x13u) /*!< Service ID: vFotaH_DcmModuleStartStart() */
#define VFOTAH_SID_MODULE_START_RESULT          (vFotaH_ServiceId)(0x14u) /*!< Service ID: vFotaH_DcmModuleStartResult() */
#define VFOTAH_SID_ERASE_START                  (vFotaH_ServiceId)(0x15u) /*!< Service ID: vFotaH_DcmEraseStart() */
#define VFOTAH_SID_ERASE_RESULT                 (vFotaH_ServiceId)(0x16u) /*!< Service ID: vFotaH_DcmEraseResult() */
#define VFOTAH_SID_SWITCH_BANK_START            (vFotaH_ServiceId)(0x17u) /*!< Service ID: vFotaH_DcmPerformPartitionSwitchStart() */
#define VFOTAH_SID_SWITCH_BANK_RESULT           (vFotaH_ServiceId)(0x18u) /*!< Service ID: vFotaH_DcmPerformPartitionSwitchResult() */
#define VFOTAH_SID_PREPARE_ACTIVATION_START     (vFotaH_ServiceId)(0x19u) /*!< Service ID: vFotaH_DcmPrepareActivationStart() */
#define VFOTAH_SID_PREPARE_ACTIVATION_RESULT    (vFotaH_ServiceId)(0x1Au) /*!< Service ID: vFotaH_DcmPrepareActivationResult() */
#define VFOTAH_SID_VERIFY_MODULE_START          (vFotaH_ServiceId)(0x1Bu) /*!< Service ID: vFotaH_DcmVerifyModuleStart() */
#define VFOTAH_SID_VERIFY_MODULE_RESULT         (vFotaH_ServiceId)(0x1Cu) /*!< Service ID: vFotaH_DcmVerifyModuleResult() */
#define VFOTAH_SID_UPDATE_COMMIT_START          (vFotaH_ServiceId)(0x1Du) /*!< Service ID: vFotaH_DcmUpdateCommitStart() */
#define VFOTAH_SID_UPDATE_COMMIT_RESULT         (vFotaH_ServiceId)(0x1Eu) /*!< Service ID: vFotaH_DcmUpdateCommitResult() */
#define VFOTAH_SID_UPDATE_START                 (vFotaH_ServiceId)(0x1Fu) /*!< Service ID: vFotaH_DcmUpdateStart() */
#define VFOTAH_SID_CHCK_PROG_PRECONDITIONS      (vFotaH_ServiceId)(0x20u) /*!< Service ID: vFotaH_DcmCheckProgrammingPreconditions() */
#define VFOTAH_SID_CHCK_PROG_DEPENDENCIES       (vFotaH_ServiceId)(0x21u) /*!< Service ID: vFotaH_DcmCheckProgrammingDependencies() */
#define VFOTAH_SID_READ_INACTIVE_SW_FINGERPRINT (vFotaH_ServiceId)(0x22u) /*!< Service ID: vFotaH_DcmReadInactiveSoftwareFingerprint() */
#define VFOTAH_SID_READ_ACTIVE_SW_FINGERPRINT   (vFotaH_ServiceId)(0x23u) /*!< Service ID: vFotaH_DcmReadActiveSoftwareFingerprint() */
#define VFOTAH_SID_WRITE_INACTIVE_SW_FINGERPRINT (vFotaH_ServiceId)(0x24u) /*!< Service ID: vFotaH_DcmWriteInactiveSoftwareFingerprint() */
#define VFOTAH_SID_DOWNLOAD_RESUME_STATUS       (vFotaH_ServiceId)(0x25u) /*!< Service ID: vFotaH_DcmReadDownloadResumStatus() */
#define VFOTAH_SID_SW_VERSION_LENGTH            (vFotaH_ServiceId)(0x26u) /*!< Service ID: vFotaH_DcmReadSoftwareVersionLength() */
#define VFOTAH_SID_SW_FINGERPRINT_LENGTH        (vFotaH_ServiceId)(0x27u) /*!< Service ID: vFotaH_DcmReadSoftwareFingerprintLength() */
#define VFOTAH_SID_READ_COMMIT_STATUS           (vFotaH_ServiceId)(0x28u) /*!< Service ID: vFotaH_DcmReadCommitStatus() */

#define VFOTAH_SID_CONFIRMATION                 (vFotaH_ServiceId)(0x30u) /*!< Service ID: vFotaH_vSwUpdMConfirmation() */
#define VFOTAH_SID_COPY_STREAM_DATA             (vFotaH_ServiceId)(0x31u) /*!< Service ID: vFotaH_vSwUpdMCopyStreamData() */
#define VFOTAH_SID_BUSY_CHECK                   (vFotaH_ServiceId)(0x32u) /*!< Service ID: vFotaH_vSwUpdMBusyCheck() */

/* ----- Error codes ----- */
typedef uint8 vFotaH_ErrorCode;
#define VFOTAH_E_NO_ERROR                       (vFotaH_ErrorCode)(0xFFu) /*!< No error */
#define VFOTAH_E_INV_POINTER                    (vFotaH_ErrorCode)(0x01u) /*!< Error code: Invalid pointer is passed (NULL_PTR). */
#define VFOTAH_E_INV_CONFIG                     (vFotaH_ErrorCode)(0x02u) /*!< Error code: API service called with wrong parameter; Due to wrong config. */
#define VFOTAH_E_WRONG_PARAMETER                (vFotaH_ErrorCode)(0x03u) /*!< Error code: API service called with wrong parameter. */
#define VFOTAH_E_NOT_INITIALIZED                (vFotaH_ErrorCode)(0x04u) /*!< Error code: API service used without module initialization. */
#define VFOTAH_E_ALREADY_INITIALIZED            (vFotaH_ErrorCode)(0x05u) /*!< Error code: The service is called while the module is already initialized. */

/* Global Defines */
#define VFOTAH_SESSION_ID_FOTA                  (0x42u) /*!< Fota Session ID */

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
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* VFOTAH_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Priv.h
 *********************************************************************************************************************/
