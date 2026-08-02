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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01.h
 *        \brief  vMem_30_XXspi01 header file
 *
 *      \details  This is the header file of the vMem_30_XXspi01. It declares the interfaces of the vMem_30_XXspi01. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author          Change Id                Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2018-04-23  virlra          STORY-7318               Initial version of vMem_30_XXspi01.
 *  01.01.00  2019-04-29  virzlu          STORYC-7852              Support non-uniform sector layout.
 *                                        STORYC-8070              Support of BurstWrite and BurstErase.
 *  01.01.01  2019-05-29  virzlu          ESCAN00103111            Extended progress check for ISSI flashes (IS25*) doesn't work.
 *  01.02.00  2019-08-02  virzlu          CTM-425                  Support of multi-die devices.
 *  02.00.00  2020-02-18  virzlu          PS-106                   Update to vMem__core [2.01.00]
 *                                        ESCAN00104475            Inappropriate behavior in case the initialization of
 *                                                                 external flash device fails.
 *  02.01.00  2020-09-24  virwsl          CTM-1506                 Improve handling of the hybrid sector layout.
 *                                        CTM-1595                 Support of automated device selection during runtime.
 *                                        CTM-1750(ESCAN00106655)  Stuck in endless loop in case of an erase error or a program error.
 *                                        CTM-2084(ESCAN00107381)  Incorrect report of successful job after result check
 *                                                                 indicates a failed memory access.
 *                                        ESCAN00107608            vMem does not recognize failed Spi sequence transmissions.
 *  02.01.01  2020-11-20  virzlu          ESCAN00107968            Compiler warning: function
 *                                                                 "vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteRegisterSeqExt"
 *                                                                 was declared but never referenced.
 *                                        ESCAN00107967            PageSize: Cast of the value of the pageSize to a
 *                                                                 smaller type causes an issue during blank check operation.
 *  02.02.00  2021-02-04  virzlu          CTM-721                  Support of Quad SPI.
 *  02.02.01  2021-06-14  virzlu          ESCAN00109486            Compiler warning: Expression without effect.
 *  02.02.02  2021-07-27  virzlu          ESCAN00109847            Inconsistent Spi configuration for S70FS01GS.
 *  03.00.00  2021-11-08  virzlu          CTM-3716                 Update to new vMem solution interface.
 *  03.00.01  2022-02-17  virzlu          ESCAN00110922            Job fails - Initialization of the external flash device fails,
 *                                                                 because of incorrectly configured register size.
 *********************************************************************************************************************/

#if !defined (VMEM_30_XXSPI01_H)
# define VMEM_30_XXSPI01_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_XXspi01_Cfg.h"
# include "vMem_30_XXspi01_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_XXSPI01_SW_MAJOR_VERSION                    (3u)
# define VMEM_30_XXSPI01_SW_MINOR_VERSION                    (0u)
# define VMEM_30_XXSPI01_SW_PATCH_VERSION                    (1u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_XXspi01_FunctionPointerTable;

#define VMEM_30_XXSPI01_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_XXSPI01_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     vMem_30_XXspi01_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \config      GetVersionInfo API is enabled via pre-compile switch.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150071
 *********************************************************************************************************************/
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_XXSPI01_APPL_VAR) VersionInfo);

# define VMEM_30_XXSPI01_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_XXSPI01_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01.h
 *********************************************************************************************************************/

