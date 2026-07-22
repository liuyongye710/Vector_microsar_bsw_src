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
/*!        \file  vMem_30_XXRam.h
 *        \brief  vMem_30_XXRam header file
 *
 *      \details  This is the header file of the vMem_30_XXRam. It declares the interfaces of the vMem_30_XXRam. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author          Change Id                Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2019-11-29  virstl virewe   MWDG-2400                Provide a vMem working on RAM only
 *  02.00.00  2021-04-23  virbmz virbka   MWDG-3232                vMem RAM shall hold buffers internally
 *  02.01.00  2021-10-15  vireno          MWDG-5907                Update vMem_30_XXRam ID and header creation
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXRAM_H)
# define VMEM_30_XXRAM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXRam_Cfg.h"
# include "vMem_30_XXRam_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_XXRAM_SW_MAJOR_VERSION                    (2u)
# define VMEM_30_XXRAM_SW_MINOR_VERSION                    (1u)
# define VMEM_30_XXRAM_SW_PATCH_VERSION                    (0u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMEM_30_XXRAM_START_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! The vMem footer will be placed at the end of the vMem (after the code, data, etc.) and marks the end of the driver. */
extern CONST(uint32, AUTOMATIC) vMem_30_XXRam_Footer;

#define VMEM_30_XXRAM_STOP_SEC_FOOTER_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXRAM_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_XXRam_FunctionPointerTable;

# define VMEM_30_XXRAM_STOP_SEC_HEADER_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_XXRAM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXRam_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_InitMemory(void);

# if (VMEM_30_XXRAM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  vMem_30_XXRam_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     vMem_30_XXRam_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \config      GetVersionInfo API is enabled via pre-compile switch.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150071
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXRAM_CODE) vMem_30_XXRam_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_XXRAM_APPL_VAR) VersionInfo);
# endif

# define VMEM_30_XXRAM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_XXRAM_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXRam.h
 *********************************************************************************************************************/

