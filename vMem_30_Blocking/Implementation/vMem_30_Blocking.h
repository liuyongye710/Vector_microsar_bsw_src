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
/*!        \file  vMem_30_Blocking.h
 *        \brief  vMem_30_Blocking header file
 *
 *      \details  This is the header file of the vMem_30_Blocking. It declares the interfaces of the vMem_30_Blocking. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author          Change Id                Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2019-02-26  virck           FEAT-4629                Initial version.
 *  01.00.01  2019-04-26  virbka          ESCAN00102983            Det_ErrorReport is also invoked when no error occurs
 *                                                                 within service ReleaseLock
 *  02.00.00  2020-01-13  virstl          MWDG-106                 vMem_30_Blocking shall provide a service to check
 *                                                                 for erased flash
 *  03.00.00  2021-09-22  virjwa,virbka   MWDG-5527                Update vMem_30_Blocking to latest vMemAccM interface
 *********************************************************************************************************************/

#if !defined (VMEM_30_BLOCKING_H)
# define VMEM_30_BLOCKING_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "vMem_30_Blocking_Cfg.h"
# include "vMem_30_Blocking_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_BLOCKING_SW_MAJOR_VERSION                    (3u)
# define VMEM_30_BLOCKING_SW_MINOR_VERSION                    (0u)
# define VMEM_30_BLOCKING_SW_PATCH_VERSION                    (0u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_BLOCKING_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_Blocking_FunctionPointerTable;

#define VMEM_30_BLOCKING_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_BLOCKING_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (VMEM_30_BLOCKING_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_Blocking_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     vMem_30_Blocking_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \config      GetVersionInfo API is enabled via pre-compile switch.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-298401
 *********************************************************************************************************************/
FUNC(void, VMEM_30_BLOCKING_CODE) vMem_30_Blocking_GetVersionInfo(vMem_30_Blocking_VersionInfoPtrType VersionInfo);
# endif

# define VMEM_30_BLOCKING_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_BLOCKING_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Blocking.h
 *********************************************************************************************************************/
