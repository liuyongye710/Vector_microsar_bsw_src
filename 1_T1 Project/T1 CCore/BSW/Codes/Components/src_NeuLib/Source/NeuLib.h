/*
********************************************************************************
*
* File name: NeuLib.h
*
* Copyright 2023-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: ZhangDX/2023.08.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: ChenQJ/2023.08.01
* Change: Update version to 3.8.0.1.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: KangJH/204.08.07
* Change: 1.Add NeuLib_memcpy32 function declaration.
*         2.Update version to 3.11.0.2.
* Cause: Update
********************************************************************************
* Version: 3.3
* Author/Date: TianG/2024.10.12
* Change: 1.Add a memory-map label to function.
*         2.Modify copyright.
*         3.Update version to 3.11.0.3.
*         4.Modify FUNC_P2VAR error.
* Cause: Bugfix
********************************************************************************
*/
#ifndef NEULIB_H_
#define NEULIB_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "NeuLib_Cfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* AUTOSAR Version. */
#define NEULIB_AR_RELEASE_MAJOR_VERSION         (4U)
#define NEULIB_AR_RELEASE_MINOR_VERSION         (4U)
#define NEULIB_AR_RELEASE_REVISION_VERSION      (0U)

/* Vendor and module identification */
#define NEULIB_VENDOR_ID                        (119U)
#define NEULIB_MODULE_ID                        (170U)

/* Component version information (decimal version of ALM implementation package) */
#define NEULIB_SW_MAJOR_VERSION                 (3U)
#define NEULIB_SW_MINOR_VERSION                 (11U)
#define NEULIB_SW_PATCH_VERSION                 (0U)
#define NEULIB_SW_REVISION_VERSION              (3U)

/* API service IDs */
#define NEULIB_SID_MEM_SET                      (0x00U)    /*!< Service ID: NeuLib_MemClr(), NeuLib_memset(). */
#define NEULIB_SID_MEM_COPY                     (0x01U)    /*!< Service ID: NeuLib_memcpy().                  */
#define NEULIB_SID_MEM_CMP                      (0x04U)    /*!< Service ID: NeuLib_memcmp().                  */
#define NEULIB_SID_MEM_MOVE                     (0x05U)    /*!< Service ID: NeuLib_memmove().                 */
#define NEULIB_SID_STR_LEN                      (0x06U)    /*!< Service ID: NeuLib_strlen().                  */
#define NEULIB_SID_STR_NCMP                     (0x07U)    /*!< Service ID: NeuLib_strncmp().                 */

/* Error codes */
#define NEULIB_E_NO_ERROR                       (0x00U)    /*!< Used to check if no error occurred.                             */
#define NEULIB_E_PARAM_POINTER                  (0x01U)    /*!< Error code: API used with invalid pointer parameter (NULL_PTR). */
#define NEULIB_E_PARAM_SIZE                     (0x02U)    /*!< Error code: NeuLib_MemCpy_s() used with invalid dst size.       */

#if (NEULIB_DEV_ERROR_DETECT == STD_ON)
/* Det_ReportError calls the mapping. */
#define NEULIB_DET_REPORT_ERROR(_api, _errorId)                                             \
        do                                                                                  \
        {                                                                                   \
            (void)Det_ReportError(NEULIB_MODULE_ID, NEULIB_VENDOR_ID, (_api), (_errorId));  \
        } while (0U)

/* Development Error Tracer */
#define NeuLib_CheckDetReturnVoid(_assertion, _api, _errId)     \
    do                                                          \
    {                                                           \
        if (!(_assertion))                                      \
        {                                                       \
            NEULIB_DET_REPORT_ERROR((_api), (_errId));          \
            return;                                             \
        }                                                       \
    } while (0U)

#define NeuLib_CheckDetReturnValue(_assertion, _api, _errId, _ret)  \
    do                                                              \
    {                                                               \
        if (!(_assertion))                                          \
        {                                                           \
            NEULIB_DET_REPORT_ERROR((_api), (_errId));              \
            return (_ret);                                          \
        }                                                           \
    } while (0U)
#else   /* (NEULIB_DEV_ERROR_DETECT == STD_ON) */
#define NEULIB_DET_REPORT_ERROR(_api, _errorId)
#define NeuLib_CheckDetReturnVoid(_assertion, _api, _errId)
#define NeuLib_CheckDetReturnValue(_assertion, _api, _errId, _ret)
#endif  /* (NEULIB_DEV_ERROR_DETECT == STD_ON) */

#define NeuLib_memclr(_dst, _cnt)           NeuLib_memset((_dst), 0u, (_cnt))

/*
********************************************************************************
*    Global Types
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
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define NEULIB_START_SEC_CODE
#include "NeuLib_MemMap.h"
FUNC(void, NEULIB_CODE) NeuLib_memcpy(
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    CONST(uint32, NEULIB_CONST) size
);
FUNC(void, NEULIB_CODE) NeuLib_memcpy32(
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    CONST(uint32, NEULIB_CONST) size
);
FUNC(void, NEULIB_CODE) NeuLib_memset(
    volatile P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr,
    uint8 value,
    CONST(uint32, NEULIB_CONST) len
);
FUNC(boolean, NEULIB_CODE) NeuLib_memcmp(
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) dstPtr,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr,
    uint32 n
);
FUNC_P2VAR(void, NEULIB_APPL_DATA, NEULIB_CODE) NeuLib_memmove(
    P2VAR(void, AUTOMATIC, NEULIB_APPL_DATA) dstPtr ,
    P2CONST(void, AUTOMATIC, NEULIB_APPL_CONST) srcPtr ,
    uint32 count
);
FUNC(uint32, NEULIB_CODE) NeuLib_strlen(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str
);
FUNC(sint8, NEULIB_CODE) NeuLib_strcmp(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str1,
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str2
);
FUNC(sint8, NEULIB_CODE) NeuLib_strncmp(
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str1,
    P2CONST(char, AUTOMATIC, NEULIB_APPL_CONST) str2,
    uint32 cnt
);
#define NEULIB_STOP_SEC_CODE
#include "NeuLib_MemMap.h"

#endif  /* #ifndef NEULIB_H_ */
