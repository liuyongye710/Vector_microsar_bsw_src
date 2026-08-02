/*
********************************************************************************
*
*  File name:	Os_MemMap_Stack.h
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

#ifdef OS_START_SEC_STACK_OSCORE0
#ifdef __HIGHTEC__
#pragma section ".OS_STACK_OSCORE0"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_STACK_OSCORE0"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_STACK_OSCORE0"
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_STACK_OSCORE0"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_STACK_OSCORE0"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_STACK_OSCORE0
#endif


#ifdef OS_STOP_SEC_STACK_OSCORE0
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section farbss restore
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section bss = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_STACK_OSCORE0
#endif


#ifdef OS_START_SEC_STACK_OSCORE1
#ifdef __HIGHTEC__
#pragma section ".OS_STACK_OSCORE1"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_STACK_OSCORE1"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_STACK_OSCORE1"
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_STACK_OSCORE1"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_STACK_OSCORE1"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_STACK_OSCORE1
#endif


#ifdef OS_STOP_SEC_STACK_OSCORE1
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section farbss restore
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section bss = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_STACK_OSCORE1
#endif


#ifdef OS_START_SEC_STACK_OSCORE2
#ifdef __HIGHTEC__
#pragma section ".OS_STACK_OSCORE2"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_STACK_OSCORE2"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_STACK_OSCORE2"
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_STACK_OSCORE2"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_STACK_OSCORE2"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_STACK_OSCORE2
#endif


#ifdef OS_STOP_SEC_STACK_OSCORE2
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section farbss restore
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section bss = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_STACK_OSCORE2
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

