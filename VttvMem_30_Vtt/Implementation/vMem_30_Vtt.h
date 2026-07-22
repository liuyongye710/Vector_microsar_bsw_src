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
/*!        \file  vMem_30_Vtt.h
 *        \brief  vMem_30_Vtt header file
 *
 *      \details  This is the header file of the vMem_30_Vtt. It declares the interfaces of the vMem_30_Vtt. 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author          Change Id                Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2020-04-27  vireno          MWDG-3038                Initial Version
 *  01.00.00  2020-07-13  vireno, virbka  MWDG-1232                Implemented basic functionality.
 *  01.01.00  2020-08-12  virbmz          MWDG-3679                vMem_30_Vtt shall declare its initialization and main function
 *  01.01.01  2020-10-16  virbmz          ESCAN00107304            vMem_30_Vtt will not register Main-Function/ 
 *                                                                 Init-Functions correctly and API-Infixed Header is not generated
 *  01.01.02  2020-11-24  virljs          ESCAN00107769            Exception in CANoe occurs during a write or read job execution
 *  01.02.00  2021-03-01  virbka          MWDG-4875                VTTvMem: Implement Overwrite Detection
 *  02.00.00  2021-09-02  virbmz          MWDG-5352                Adapt VTT vMem to the new vMem-Solution interface
 *  02.00.01  2021-11-17  virbka          ESCAN00110727            Compiler error: "formal parameter 1 different from declaration"
 *  03.00.00  2021-11-25  virbmz          MWDG-3700                VTT vMem shall simulate parallel memory access via instances
 *  03.01.00  2021-12-21  vireno          MWDG-6205                Update to newest Core Version
 *            2022-01-20  virbmz          MWDG-5040                vMem_30_Vtt: Overwrite Detection per Instance
 *********************************************************************************************************************/

#if !defined (VMEM_30_VTT_H)
# define VMEM_30_VTT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "vMem_30_Vtt_Cfg.h"
# include "vMem_30_Vtt_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define VMEM_30_VTT_SW_MAJOR_VERSION                    (3u)
# define VMEM_30_VTT_SW_MINOR_VERSION                    (1u)
# define VMEM_30_VTT_SW_PATCH_VERSION                    (0u)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_VTT_START_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Global API pointer table */
extern CONST(vMemAccM_vMemApiType, AUTOMATIC) vMem_30_Vtt_FunctionPointerTable;

#define VMEM_30_VTT_STOP_SEC_HEADER_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define VMEM_30_VTT_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_Vtt_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information. This service is always available.
 *  \details     vMem_30_Vtt_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  versioninfo           Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-150071
 *********************************************************************************************************************/
FUNC(void, VMEM_30_VTT_CODE) vMem_30_Vtt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VMEM_30_VTT_APPL_VAR) VersionInfo);

# define VMEM_30_VTT_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* VMEM_30_VTT_H */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_Vtt.h
 *********************************************************************************************************************/

