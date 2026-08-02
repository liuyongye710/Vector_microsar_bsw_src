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
/*!        \file  vMem_30_Fls.h
 *        \brief  vMem_30_Fls header file
 *
 *      \details  The vMem_30_Fls is a component which provides the declaration of functions and function pointer table.
 *                This component is a wrapper which just forwards requests to corresponding Flash driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-01-25  virbmz  STORY-3379      Initial version.
 *                                STORY-3380      instance parameter was added.
 *                                                vMem wrapper works only with one FLS underlying FLS driver!
 *  01.00.01  2018-05-30  virbmz  ESCAN00099561   bugfix in vMem_30_Fls_MemMap.inc
 *  01.01.00  2018-07-11  virbka  STORY-6745      Support multiple Flash Driver instance handling in vMem adapter
 *  01.01.01  2018-08-16  virbmz  ESCAN00100361   MemMap handling not correct
 *  01.01.02  2019-03-28  virbmz  ESCAN00102610   Compiler error: vMem_30_Fls - a space is generated within include
 *                                                Within implementation just added MISRA justification for DUMMY macro
 *  02.00.00  2019-09-18  virbmz  MWDG-46         vMem_30_Fls shall provide a service to check for erased flash
 *  02.00.01  2020-01-09  virbmz  ESCAN00104899   vMem_30_Fls returns MEMIF_BLOCK_FAILED instead of MEMIF_BLOCK_
 *                                                INCONSISTENT for a BlankCheck job
 *  03.00.00  2021-09-30  vireno  MWDG-5525       Update vMem_30_Fls to latest vMemAccM interface
 *********************************************************************************************************************/

#if !defined (VMEM_30_FLS_H)/* COV_VMEM30FLS_COMPATIBILITY */
# define VMEM_30_FLS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_Fls_Types.h"
#include "vMem_30_Fls_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define VMEM_30_FLS_VENDOR_ID                           (30u)
# define VMEM_30_FLS_MODULE_ID                           (0xFFu)

/* AUTOSAR Software specification version information */
# define VMEM_30_FLS_AR_RELEASE_MAJOR_VERSION            (4u)
# define VMEM_30_FLS_AR_RELEASE_MINOR_VERSION            (0u)
# define VMEM_30_FLS_AR_RELEASE_REVISION_VERSION         (3u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_FLS_SW_MAJOR_VERSION                    (3u)
# define VMEM_30_FLS_SW_MINOR_VERSION                    (0u)
# define VMEM_30_FLS_SW_PATCH_VERSION                    (0u)

# define VMEM_30_FLS_INSTANCE_ID_DET                     (0x00u)


# define VMEM_30_FLS_SID_READ                            (0x02u)     /*!< Service ID: vMem_30_Fls_Read() */
# define VMEM_30_FLS_SID_WRITE                           (0x03u)     /*!< Service ID: vMem_30_Fls_Write() */
# define VMEM_30_FLS_SID_ERASE                           (0x04u)     /*!< Service ID: vMem_30_Fls_Erase() */
# define VMEM_30_FLS_SID_BLANK_CHECK                     (0x06u)     /*!< Service ID: vMem_30_Fls_BlankCheck() */

# define VMEM_30_FLS_SID_GET_JOB_RESULT                  (0x0Au)     /*!< Service ID: vMem_30_Fls_Get_Job_Result() */

# define VMEM_30_FLS_SID_GET_VERSION_INFO                (0x10u)     /*!< Service ID: vMem_30_Fls_GetVersionInfo() */

/* ----- Error codes ----- */
# define VMEM_30_FLS_E_NO_ERROR                          (0x00u)    /*!< used to check if no error occurred - use a value unequal to any error code */

# define VMEM_30_FLS_E_PARAM_POINTER                     (0x0Bu)    /*!< Error code: API service used with invalid pointer parameter (NULL) */
# define VMEM_30_FLS_E_PARAM_INSTANCE_ID                 (0x0Cu)    /*!< Error code: API service used with invalid instance identifier parameter. */



/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_Fls_FunctionPointerTable;

#define VMEM_30_FLS_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_FLS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */


# if (VMEM_30_FLS_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_Fls_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     vMem_30_Fls_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_FLS_CODE) vMem_30_Fls_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_FLS_APPL_VAR) versionInfo);
# endif


#define VMEM_30_FLS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap  */

#endif /* VMEM_30_FLS_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Fls.h
 *********************************************************************************************************************/

