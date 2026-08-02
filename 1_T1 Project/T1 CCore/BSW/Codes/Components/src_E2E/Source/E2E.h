/*
********************************************************************************
*
* File name: E2E.h
*
* Copyright 2019-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJiPeng/2019.04.20
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
* Change: Add #define E2E_INIT_0S (0) for signed types
* Cause: QAC
********************************************************************************
* Version: 3.1
* Author/Date : Tanjingyang/2020.09.29
* Change: 1.Add function of MemMap
*         2.Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date : TanJY/2020.11.02
* Change: Modify MemMap section
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date : TanJY/2020.11.03
* Change: Modify code format.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: BaoWL/2021.04.07
* Change: Modify the minor version number.
* Cause: Update.
********************************************************************************
* Version: 3.5
* Author/Date: XieYN/2021.08.13
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: XieYN/2021.10.20
* Change:Nothing.
* Cause: Update to V3.3.0
********************************************************************************
* Version: 3.7
* Author/Date: XieYN/2022.09.13
* Change: Add E2EPW_EndianessType.
* Cause: Update
********************************************************************************
* Version: 3.8
* Author/Date: CaiXY/2023.03.02
* Change: Bugfix for CCOREDBUG-2296.
* Cause: Bugfix
********************************************************************************
* Version: 3.9
* Author/Date : HanXF/2023.5.23
* Change: Modify the minor number.
* Cause: Optimization
*******************************************************************************
* Version: 3.10
* Author/Date: HanXF/2023.5.26
* Change: Add REVISION Version.
* Cause: Optimization
********************************************************************************
* Version: 3.11
* Author/Date: LiDaY/2023.10.8
* Change: Updata Minor Version and Revision Version.
* Cause: Updata
********************************************************************************
* Version: 3.12
* Author/Date: LiDaY/2024.02.05
* Change: Updata Minor Version and Revision Version.
* Cause: Updata
********************************************************************************
* Version: 3.13
* Author/Date: LiDaY/2024.04.25
* Change: 1.Add a memory-map label to function and variable declarations.
*         2.Updata Minor Version and Revision Version.
* Cause: Bugfix
********************************************************************************
* Version: 3.14
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
#ifndef E2E_H_
#define E2E_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h" /* [SWS_E2E_00017] */
#include "Crc.h"
#include "E2E_SM.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* E2E Version. */
#define E2E_VENDOR_ID                   (119U)
#define E2E_MODULE_ID                   (207U)
#define E2E_SW_MAJOR_VERSION            (3U)
#define E2E_SW_MINOR_VERSION            (11U)
#define E2E_SW_PATCH_VERSION            (0U)
#define E2E_SW_REVISION_VERSION         (3U)
#define E2E_AR_RELEASE_MAJOR_VERSION    (4U)
#define E2E_AR_RELEASE_MINOR_VERSION    (2U)
#define E2E_AR_RELEASE_REVISION_VERSION (2U)

/* Error classification. */
#define E2E_E_OK                (0x00U) /* Function completed successfully. */
#define E2E_E_INTERR            (0x19U) /* An internal error has occurred. */
#define E2E_E_INPUTERR_NULL     (0x13U) /* At least one pointer parameter is
                                           a NULL pointer. */
#define E2E_E_INPUTERR_WRONG    (0x17U) /* At least one input parameter is
                                           erroneous. */
#define E2E_E_WRONGSTATE        (0x1AU) /* Function executed in wrong state. */

/* initialize value. */
#define E2E_INIT_0S                     (0U)
#define E2E_INIT_0                      (0U)
#define E2E_INIT_1                      (1U)
#define E2E_INIT_2                      (2U)
#define E2E_INIT_16                     (16U)
#define E2E_INIT_FULL1BYTE              (0xFFU)
#define E2E_INIT_FULL2BYTE              (0xFFFFU)

/* Counter value. */
#define E2E_COUNTER_1                   (1U)

/* number value. */
#define E2E_NUMBER_1                    (1U)

/* 8 bit. */
#define E2E_1BIT                        (1U)
#define E2E_2BIT                        (2U)
#define E2E_4BIT                        (4U)
#define E2E_8BIT                        (8U)
#define E2E_12BIT                       (12U)

/* judge value is 0. */
#define E2E_JUDGE_0                     (0U)
#define E2E_JUDGE_1                     (1U)

/* array index. */
#define E2E_INDEX_0                     (0U)
#define E2E_INDEX_1                     (1U)
#define E2E_INDEX_2                     (2U)
#define E2E_INDEX_3                     (3U)
#define E2E_INDEX_4                     (4U)
#define E2E_INDEX_5                     (5U)
#define E2E_INDEX_6                     (6U)
#define E2E_INDEX_7                     (7U)

/* byte deal with. */
#define E2E_HIGH_NIBBLE                 (0xF0U)
#define E2E_LOW_NIBBLE                  (0x0FU)
#define E2E_HIGH_BYTE                   (0xFF00U)
#define E2E_FULL_BYTE                   (0xFFU)
#define E2E_FULL_2BYTE                  (0xFFFFU)
#define E2E_FULL_4BYTE                  (0xFFFFFFFFU)

/* DUMMY. */
#define E2E_DUMMY_STATEMENT(v)    ((v) = (v))

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef enum
{
    E2E_BIGENDIANESS = 0U,
    E2E_LITTLEENDIANESS,
    E2EPW_OPAQUE
} E2EPW_EndianessType;

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
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

extern FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

#endif /* E2E_H_ */
