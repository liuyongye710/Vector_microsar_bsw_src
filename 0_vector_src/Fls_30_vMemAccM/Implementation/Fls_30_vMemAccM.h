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
/*!        \file  Fls_30_vMemAccM.h
 *        \brief  Fls_30_vMemAccM header file
 *
 *      \details  Fls_30_vMemAccM shall act as an AUTOSAR Fls Driver for the module above in order
 *                to use non AUTOSAR vMemAccM.
 *                Therefore the Fls_30_vMemAccM provides the basic functionality of the vMemAccM in its role as an adapter.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-04-24  virbka  STORYC-4878   Initial version
 *  01.00.01  2018-05-18  virbka  STORYC-5853   DummyStatement added in vFlsAcc_GetVersionInfo
 *  01.00.02  2018-06-05  virbka  ESCAN00099591 Compiler error: "unknown type name" in vFlsAcc_Cfg.h
 *  02.00.00  2018-06-13  virbka  STORYC-5681   Change of <Mip> inside all working products  to "Fls_30_vMemAccM"
 *  02.00.01  2018-10-23  virbka  ESCAN00101115 Missing CREQ Trace of SetMode Function
 *  02.00.02  2019-01-15  virbka  ESCAN00101547 Fls_30_vMemAccM maps job result for corrected ECC errors incorrectly to job result failed
 *  02.01.00  2019-08-21  virewe  MWDG-45       Fls_30_vMemAccM shall provide a service to check whether a memory area
 *                                              is erased
 *  02.02.00  2019-09-05  virewe  MWDG-1819     Ensure RAM alignment within Fls_30_vMemAccM
 *  03.00.00  2019-09-20  virjwa  MWDG-1818     Write Job within Fls_30_vMemAccM shall be splitted to reduce RAM Buffer size
 *  03.01.00  2019-11-28  virewe  ESCAN00104895 Fls_30_vMemAccM rejects request (error may be reported to DET).
 *  03.02.00  2020-02-25  vireno  MWDG-2907     Fls_30_vMemAccM optionally notifies Fee when a job ends.
 *  04.00.00  2020-07-14  virjwa  MWDG-3141     Fls_30_vMemAccM shall forward a cancel request directly to the vMemAccM
 *  05.00.00  2020-09-16  virbka  MWDG-3508     Fls_30_vMemAccM shall provide an ECC safe read service
 *  05.01.00  2020-10-30  virbmz  MWDG-3287     Fls_30_vMemAccM shall distinguish between failed comparison and unequal data
 *                        virljs
 *  06.00.00  2021-08-19  virbmz  MWDG-5109     Fls_30_vMemAccM shall handle vMemAccM job notification
 *********************************************************************************************************************/

#if !defined (FLS_30_VMEMACCM_H)/* COV_FLS_30_VMEMACCM_COMPATIBILITY */
# define FLS_30_VMEMACCM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Fls_30_vMemAccM_Types.h"
#include "Fls_30_vMemAccM_Cfg.h"

#include "MemIf_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define FLS_30_VMEMACCM_VENDOR_ID                           (30u)
# define FLS_30_VMEMACCM_MODULE_ID                           (255u)
# define FLS_30_VMEMACCM_INSTANCE_ID                         (0u)



/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define FLS_30_VMEMACCM_SW_MAJOR_VERSION                    (6u)
# define FLS_30_VMEMACCM_SW_MINOR_VERSION                    (0u)
# define FLS_30_VMEMACCM_SW_PATCH_VERSION                    (0u)



/* ----- Public API identifier ----- */
# define FLS_30_VMEMACCM_SID_READ                            (0x01u)     /*!< Service ID: Fls_30_vMemAccM_Read() */
# define FLS_30_VMEMACCM_SID_WRITE                           (0x02u)     /*!< Service ID: Fls_30_vMemAccM_Write() */
# define FLS_30_VMEMACCM_SID_ERASE                           (0x03u)     /*!< Service ID: Fls_30_vMemAccM_Erase() */
# define FLS_30_VMEMACCM_SID_COMPARE                         (0x04u)     /*!< Service ID: Fls_30_vMemAccM_Compare() */
# define FLS_30_VMEMACCM_SID_BLANKCHECK                      (0x05u)     /*!< Service ID: Fls_30_vMemAccM_BlankCheck() */
# define FLS_30_VMEMACCM_SID_READBLANK                       (0x06u)     /*!< Service ID: Fls_30_vMemAccM_ReadBlank() */
# define FLS_30_VMEMACCM_SID_GET_VERSION_INFO                (0x10u)     /*!< Service ID: Fls_30_vMemAccM_GetVersionInfo() */


/* ----- Error codes ----- */
# define FLS_30_VMEMACCM_E_NO_ERROR                          (0x00u)    /*!< used to check if no error occurred - use a value unequal to any error code */

# define FLS_30_VMEMACCM_E_NOT_INITIALIZED                   (0x05u)    /*!< Error code: Module is not initialized */
# define FLS_30_VMEMACCM_E_BUSY                              (0x06u)    /*!< Error code: Module is busy */
# define FLS_30_VMEMACCM_E_PARAM_POINTER                     (0x0Au)    /*!< Error code: API service used with invalid pointer parameter (NULL) */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/**********************************************************************************************************************
 * Fls_30_vMemAccM_Init
 *********************************************************************************************************************/
/*!
 * \brief       Initializes the module.
 * \details     Initializes the module.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace       CREQ-217119
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Init(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Read
 *********************************************************************************************************************/
/*!
 * \brief       The Read service uses the given address, pointer and length to read the data from the flash.
 * \details     Sets up the read job so that it can be processed later within the main function handling.
 * \param[in]   SourceAddress pointing to the first byte of the request.
 * \param[out]  TargetAddressPtr pointing to the job buffer. Parameter must not be NULL_PTR and must stay valid until job is completed.
 * \param[in]   Length of the data in bytes.
 * \return      E_OK job accepted, E_NOT_OK otherwise
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous FALSE
 * \trace       CREQ-156258
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Read
(
  Fls_30_vMemAccM_AddressType SourceAddress,
  uint8 *TargetAddressPtr,
  Fls_30_vMemAccM_LengthType Length
);


 /**********************************************************************************************************************
  * Fls_30_vMemAccM_Write
  *********************************************************************************************************************/
 /*!
  * \brief       The Write service uses the given address, pointer and length to write the data to the flash.
  * \details     Sets up the write job so that it can be processed later within the main function handling.
  * \param[in]   TargetAddress pointing to the first byte of the request.
  * \param[in]   SourceAddressPtr pointing to the job buffer. Parameter must not be NULL_PTR and must stay valid until job is completed.
  * \param[in]   Length of the data in bytes. Value depends on hardware, normally at least a page size.
  * \return      E_OK job accepted, E_NOT_OK otherwise
  * \pre         -
  * \context     TASK
  * \reentrant   FALSE
  * \synchronous FALSE
  * \trace       CREQ-156398
  */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Write
(
  Fls_30_vMemAccM_AddressType TargetAddress,
  const uint8 *SourceAddressPtr,
  Fls_30_vMemAccM_LengthType Length
);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Erase
 *********************************************************************************************************************/
/*!
 * \brief       The Erase service uses the given address and length to erase flash sector(s).
 * \details     Sets up the erase job so that it can be processed later within the main function handling.
 * \param[in]   TargetAddress pointing to the first byte of the request.
 * \param[in]   Length of the data in bytes. Keep in mind that the memory is only sector-wise erasable.
 *              Hence, requested length has to be aligned to sector size.
 * \return      E_OK job accepted, E_NOT_OK otherwise
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous FALSE
 * \trace       CREQ-156399
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Erase
(
  Fls_30_vMemAccM_AddressType TargetAddress,
  Fls_30_vMemAccM_LengthType Length
);


#if(FLS_30_VMEMACCM_COMPARE_API == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_Compare
 *********************************************************************************************************************/
/*!
 * \brief       The Compare service uses the given address, pointer and length to read the data from the flash and compare it.
 * \details     Sets up the compare job so that it can be processed later within the main function handling.
 * \param[in]   SourceAddress pointing to the first byte of the request.
 * \param[in]   TargetAddressPtr pointing to the job buffer. Parameter must not be NULL_PTR and must stay valid until job is completed.
 * \param[in]   Length of the data in bytes.
 * \return      E_OK job accepted, E_NOT_OK otherwise
 * \pre         FLS_30_VMEMACCM_COMPARE_API == STD_ON
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous FALSE
 * \trace       CREQ-156400
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Compare
(
  Fls_30_vMemAccM_AddressType SourceAddress,
  const uint8 *TargetAddressPtr,
  Fls_30_vMemAccM_LengthType Length
);
#endif


#if(FLS_30_VMEMACCM_BLANK_CHECK_API == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_BlankCheck
 *********************************************************************************************************************/
/*!
 * \brief       The BlankCheck service checks whether a memory area, specified by given address and length, has been erased but not (yet) programmed.
 * \details     Sets up the blank check job so that it can be processed later within the main function handling.
 * \param[in]   TargetAddress pointing to the first byte of the request.
 * \param[in]   Length of the data in bytes. Requested length has to be aligned to page size.
 * \return      E_OK job accepted, E_NOT_OK otherwise
 * \pre         FLS_30_VMEMACCM_BLANK_CHECK_API == STD_ON
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous FALSE
 * \trace       CREQ-213410
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_BlankCheck
(
  Fls_30_vMemAccM_AddressType TargetAddress,
  Fls_30_vMemAccM_LengthType Length
);
#endif


#if(FLS_30_VMEMACCM_READBLANK_API == STD_ON)
/**********************************************************************************************************************
 * Fls_30_vMemAccM_ReadBlank
 *********************************************************************************************************************/
/*!
 * \brief       The ReadBlank service uses the given address, pointer and length to read data from the flash. This service
 *              will always perform a blank check before reading data in order to avoid access to erased memory.
 * \details     Sets up the read blank job so that it can be processed later within the main function handling.
 *              If a page is blank, the buffer will be filled with the erase value.
 * \param[in]   SourceAddress pointing to the first byte of the request.
 * \param[out]  TargetAddressPtr pointing to the job buffer. Parameter must not be NULL_PTR and must stay valid until job is completed.
 * \param[in]   Length of the data in bytes.
 * \return      E_OK job accepted, E_NOT_OK otherwise
 * \pre         FLS_30_VMEMACCM_READBLANK_API == STD_ON
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous FALSE
 * \trace       CREQ-260036
 */
FUNC(Std_ReturnType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_ReadBlank
(
  Fls_30_vMemAccM_AddressType SourceAddress,
  uint8 *TargetAddressPtr,
  Fls_30_vMemAccM_LengthType Length
);
#endif


/**********************************************************************************************************************
 * Fls_30_vMemAccM_Cancel
 *********************************************************************************************************************/
/*!
 * \brief       The Cancel service aborts an active operation.
 * \details     Forwards the cancel request to the vMemAccM (if not idle) and also requests reset of internal job handling
 *              (i.e. if job is multi step job and still some steps pending).
 * \param[in]   -
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace       CREQ-156402
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_Cancel (void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_GetJobResult
 *********************************************************************************************************************/
/*!
 * \brief       The GetJobresult service returns the current job status.
 * \details     The GetJobresult service returns the current job status.
 * \param[in]   -
 * \return      Most recent job result.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \trace       CREQ-156401
 */
FUNC(MemIf_JobResultType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_GetJobResult(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_GetStatus
 *********************************************************************************************************************/
/*!
 * \brief       The GetStatus service returns the current driver status.
 * \details     -
 * \param[in]   -
 * \return      Most recent status.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \trace       CREQ-156260
 */
FUNC(MemIf_StatusType, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_GetStatus(void);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_SetMode
 *********************************************************************************************************************/
/*!
 * \brief       The SetMode service sets the flash drivers operation mode. Only implemented for compatibility reasons.
 * \details     This function implements no functionality and will ignore the Mode parameter.
 * \param[in]   Mode sets the flash drivers operation mode.
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \trace       CREQ-160797
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_SetMode(MemIf_ModeType Mode);


/**********************************************************************************************************************
 * Fls_30_vMemAccM_MainFunction
 *********************************************************************************************************************/
/*!
 * \brief       Triggers the async job handling.
 * \details     Triggers the async job handling.
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_MainFunction(void);


# if (FLS_30_VMEMACCM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Fls_30_vMemAccM_GetVersionInfo()
 *********************************************************************************************************************/
/*! 
 * \brief       Returns the version information
 * \details     Fls_30_vMemAccM_GetVersionInfo() returns version information, vendor ID of the component.
 * \param[out]  versionInfo           Pointer to where to store the version information. Parameter must not be NULL.
 * \pre         FLS_30_VMEMACCM_VERSION_INFO_API == STD_ON
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \trace       CREQ-156259
 */
FUNC(void, FLS_30_VMEMACCM_CODE) Fls_30_vMemAccM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_30_VMEMACCM_APPL_VAR) versionInfo);
# endif


#define FLS_30_VMEMACCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#endif /* FLS_30_VMEMACCM_H */

/**********************************************************************************************************************
 *  END OF FILE: Fls_30_vMemAccM.h
 *********************************************************************************************************************/

