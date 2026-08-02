/*
********************************************************************************
*
*  File name:	Os_MemMap_Code.h
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
*/

/*
********************************************************************************
*    Includes
********************************************************************************
*/

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define MEMMAP_ERROR

#ifdef OS_START_SEC_CODE
#ifdef __HIGHTEC__
#pragma section ".OS_CODE" ax
#endif
#ifdef __ghs__
#pragma ghs section text = ".OS_CODE"
#endif
#ifdef __TASKING__
#pragma section code ".OS_CODE"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_function_attributes = @ ".OS_CODE"
#endif
#ifdef __clang__
#pragma clang section text = ".OS_CODE"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_CODE
#endif


#ifdef OS_STOP_SEC_CODE
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section code restore
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_function_attributes =
#endif
#ifdef __clang__
#pragma clang section text = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_CODE
#endif


#ifdef MEMMAP_ERROR
    /* #error "Os_MemMap_OsCode.h, wrong pragma command." */
#undef MEMMAP_ERROR
#endif
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

