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
/*!        \file  vMem_30_MmFlashRO.h
 *        \brief  vMem_30_MmFlashRO header file
 *
 *      \details  This is the header file of the vMem_30_MmFlashRO. It declares the interfaces of the vMem_30_MmFlashRO. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author          Change Id                Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-08-13  virbka          STORYC-6230              Initial Version
 *            2018-08-23  vircre
 *  2.00.00   2019-09-19  vircre          MWDG-29                  vMem_30_MmFlashRO shall provide a service to check
 *                                                                 for erased flash
 *  3.00.00   2021-10-15  virbka          MWDG-42                  vMem_30_MmFlashRO shall realize Read Access to the
 *                                                                 Flash over Memcpy
 *            2021-12-06  virbka          MWDG-5528                Update vMem_30_MmFlashRO to latest vMemAccM interface
 *********************************************************************************************************************/

#if !defined (VMEM_30_MMFLASHRO_H)
# define VMEM_30_MMFLASHRO_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_MmFlashRO_Cfg.h"
# include "vMem_30_MmFlashRO_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_MMFLASHRO_SW_MAJOR_VERSION                    (3u)
# define VMEM_30_MMFLASHRO_SW_MINOR_VERSION                    (0u)
# define VMEM_30_MMFLASHRO_SW_PATCH_VERSION                    (0u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_MMFLASHRO_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_MmFlashRO_FunctionPointerTable;

#define VMEM_30_MMFLASHRO_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_MMFLASHRO_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_MmFlashRO_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information. This service is always available.
 *  \details     vMem_30_MmFlashRO_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150071
 *********************************************************************************************************************/
FUNC(void, VMEM_30_MMFLASHRO_CODE) vMem_30_MmFlashRO_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_MMFLASHRO_APPL_VAR) VersionInfo);

# define VMEM_30_MMFLASHRO_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_MMFLASHRO_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_MmFlashRO.h
 *********************************************************************************************************************/

