/*
********************************************************************************
*
* File name: E2E.c
*
* Copyright 2019-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJipeng/2019.04.20
* Change: New created
* Cause: New
********************************************************************************
* Version: 2.0
* Author/Date: WangHe/2019.11.22
* Change: Format modification.
* Cause:  Optimization
********************************************************************************
* Version: 3.0
* Author/Date : Baowanglong/2020.03.27
* Change: Nothing
* Cause: Update to V3.0
********************************************************************************
* Version: 3.1
* Author/Date : Tanjingyang/2020.09.29
* Change: 1.Add function of MemMap
*         2.Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date : TanJY/2020.11.03
* Change: Modify code format.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: XieYN/2021.08.12
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "E2E.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

/*
********************************************************************************
* Function Name: E2E_GetVersionInfo
*
* Explanation: Returns the version information of this module.(Synchronous)
*
* param: VersionInfo:Pointer to standard version information structure.
*
* retval: None
********************************************************************************
*/
FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
)
/* [SWS_E2E_00032] */
{
    if( NULL_PTR != VersionInfo )
    {
        /* [SWS_E2E_00033] */
        VersionInfo->vendorID = E2E_VENDOR_ID;
        /* [SWS_E2E_00033] */
        VersionInfo->moduleID = E2E_MODULE_ID;
        /* [SWS_E2E_00033] */
        VersionInfo->sw_major_version = E2E_SW_MAJOR_VERSION;
        /* [SWS_E2E_00033] */
        VersionInfo->sw_minor_version = E2E_SW_MINOR_VERSION;
        /* [SWS_E2E_00033] */
        VersionInfo->sw_patch_version = E2E_SW_PATCH_VERSION;
    }
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
