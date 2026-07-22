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
/*!        \file  vMem_30_Blocking_Types.h
 *        \brief  vMem types header file
 *
 *      \details  Defines vMem_30_Blocking types and symbols used for parameter checks.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (VMEM_30_BLOCKING_TYPES_H)
# define VMEM_30_BLOCKING_TYPES_H

# include "Std_Types.h"
# include "vMemAccM_vMemApi.h"

#if !defined (VMEM_30_BLOCKING_LOCAL) /* COV_VMEM_30_BLOCKING_COMPATIBILITY */
# define VMEM_30_BLOCKING_LOCAL static
#endif

#if !defined (VMEM_30_BLOCKING_LOCAL_INLINE) /* COV_VMEM_30_BLOCKING_COMPATIBILITY */
# define VMEM_30_BLOCKING_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef vMemAccM_vMemConstDataPtrType     vMem_30_Blocking_ConstDataPtrType;
typedef vMemAccM_vMemDataPtrType          vMem_30_Blocking_DataPtrType;
typedef vMemAccM_vMemJobResultType        vMem_30_Blocking_JobResultType;

typedef vMemAccM_vMemInstanceIdType       vMem_30_Blocking_InstanceIdType;

/* Used as address offset from the configured nv memory base address to access a certain NV memory memory area */
typedef vMemAccM_vMemAddressType          vMem_30_Blocking_AddressType;

/* Specifies the number of bytes to read/write/erase/compare */
typedef vMemAccM_vMemLengthType           vMem_30_Blocking_LengthType;

typedef P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_BLOCKING_APPL_VAR) vMem_30_Blocking_VersionInfoPtrType;

/* Specifies the config pointer type for the init service. */
typedef vMemAccM_vMemConfigPtrType        vMem_30_Blocking_ConfigPtrType;

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Vendor and module identification */
# define VMEM_30_BLOCKING_VENDOR_ID                           (30u)
# define VMEM_30_BLOCKING_MODULE_ID                           (0xFFu)

# define VMEM_30_BLOCKING_INSTANCE_ID_DET                     (0x00u)

# define VMEM_30_BLOCKING_SID_GET_VERSION_INFO                (0x10u)     /*!< Service ID: vMem_30_Blocking_GetVersionInfo() */
# define VMEM_30_BLOCKING_SID_ACQUIRE_LOCK                    (0x20u)     /*!< Service ID: vMem_30_Blocking_AcquireLock() (HW specific request) */
# define VMEM_30_BLOCKING_SID_RELEASE_LOCK                    (0x21u)     /*!< Service ID: vMem_30_Blocking_ReleaseLock() */

/* ----- Error codes ----- */
# define VMEM_30_BLOCKING_E_NO_ERROR                          (0x00u)    /*!< used to check if no error occurred - use a value unequal to any error code. */
# define VMEM_30_BLOCKING_E_PARAM_POINTER                     (0x0Bu)    /*!< Error code: API service used with invalid pointer parameter (NULL). */
# define VMEM_30_BLOCKING_E_PARAM_LENGTH                      (0x0Du)    /*!< Error code: API service used with invalid length parameter. */
# define VMEM_30_BLOCKING_E_PENDING                           (0x13u)    /*!< Error code: Another lock was already acquired. */
# define VMEM_30_BLOCKING_E_NOT_LOCK_OWNER                    (0x14u)    /*!< Error code: Another client or nobody holds (owns) the current lock */
#endif /* VMEM_30_BLOCKING_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Blocking_Types.h
 *********************************************************************************************************************/
