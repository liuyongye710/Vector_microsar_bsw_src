/*
********************************************************************************
*
*  File name:	Os_MemMap_Var.h
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

/* Const section */

#ifdef OS_START_SEC_CONST
#ifdef __HIGHTEC__
#pragma section ".OS_CONST"
#endif
#ifdef __ghs__
#pragma ghs section rodata = ".OS_CONST"
#endif
#ifdef __TASKING__
#pragma section farrom ".OS_CONST"
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_CONST"
#endif
#ifdef __clang__
#pragma clang section rodata = ".OS_CONST"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_CONST
#endif
#ifdef OS_STOP_SEC_CONST
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section farrom restore
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section rodata = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_CONST
#endif


/* OSCORE0 const section */

#ifdef OS_START_SEC_VAR_OSCORE0
#ifdef __HIGHTEC__
#pragma section ".OS_VAR_OSCORE0"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_VAR_OSCORE0"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_VAR_OSCORE0"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_VAR_OSCORE0"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_VAR_OSCORE0"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_VAR_OSCORE0
#endif


#ifdef OS_STOP_SEC_VAR_OSCORE0
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
#undef OS_STOP_SEC_VAR_OSCORE0
#endif


#ifdef OS_START_SEC_INITVAR_OSCORE0
#ifdef __HIGHTEC__
#pragma section ".OS_INITVAR_OSCORE0"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_INITVAR_OSCORE0"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_INITVAR_OSCORE0"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_INITVAR_OSCORE0"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_INITVAR_OSCORE0"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_INITVAR_OSCORE0
#endif


#ifdef OS_STOP_SEC_INITVAR_OSCORE0
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_INITVAR_OSCORE0
#endif


#ifdef OS_START_SEC_NOCACHE_VAR_OSCORE0
#ifdef __HIGHTEC__
#pragma section ".OS_NOCACHE_VAR_OSCORE0"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_NOCACHE_VAR_OSCORE0"
#endif
#ifdef __TASKING__
#pragma section .farbss ".OS_NOCACHE_VAR_OSCORE0"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_NOCACHE_VAR_OSCORE0"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_NOCACHE_VAR_OSCORE0"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_NOCACHE_VAR_OSCORE0
#endif


#ifdef OS_STOP_SEC_NOCACHE_VAR_OSCORE0
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
#undef OS_STOP_SEC_NOCACHE_VAR_OSCORE0
#endif


#ifdef OS_START_SEC_NOCACHE_INITVAR_OSCORE0
#ifdef __HIGHTEC__
#pragma section ".OS_NOCACHE_INITVAR_OSCORE0"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_NOCACHE_INITVAR_OSCORE0"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_NOCACHE_INITVAR_OSCORE0"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_NOCACHE_INITVAR_OSCORE0"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_NOCACHE_INITVAR_OSCORE0"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_NOCACHE_INITVAR_OSCORE0
#endif


#ifdef OS_STOP_SEC_NOCACHE_INITVAR_OSCORE0
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_NOCACHE_INITVAR_OSCORE0
#endif


/* OSCORE1 const section */

#ifdef OS_START_SEC_VAR_OSCORE1
#ifdef __HIGHTEC__
#pragma section ".OS_VAR_OSCORE1"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_VAR_OSCORE1"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_VAR_OSCORE1"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_VAR_OSCORE1"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_VAR_OSCORE1"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_VAR_OSCORE1
#endif


#ifdef OS_STOP_SEC_VAR_OSCORE1
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
#undef OS_STOP_SEC_VAR_OSCORE1
#endif


#ifdef OS_START_SEC_INITVAR_OSCORE1
#ifdef __HIGHTEC__
#pragma section ".OS_INITVAR_OSCORE1"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_INITVAR_OSCORE1"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_INITVAR_OSCORE1"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_INITVAR_OSCORE1"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_INITVAR_OSCORE1"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_INITVAR_OSCORE1
#endif


#ifdef OS_STOP_SEC_INITVAR_OSCORE1
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_INITVAR_OSCORE1
#endif


#ifdef OS_START_SEC_NOCACHE_VAR_OSCORE1
#ifdef __HIGHTEC__
#pragma section ".OS_NOCACHE_VAR_OSCORE1"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_NOCACHE_VAR_OSCORE1"
#endif
#ifdef __TASKING__
#pragma section .farbss ".OS_NOCACHE_VAR_OSCORE1"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_NOCACHE_VAR_OSCORE1"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_NOCACHE_VAR_OSCORE1"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_NOCACHE_VAR_OSCORE1
#endif


#ifdef OS_STOP_SEC_NOCACHE_VAR_OSCORE1
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
#undef OS_STOP_SEC_NOCACHE_VAR_OSCORE1
#endif


#ifdef OS_START_SEC_NOCACHE_INITVAR_OSCORE1
#ifdef __HIGHTEC__
#pragma section ".OS_NOCACHE_INITVAR_OSCORE1"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_NOCACHE_INITVAR_OSCORE1"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_NOCACHE_INITVAR_OSCORE1"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_NOCACHE_INITVAR_OSCORE1"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_NOCACHE_INITVAR_OSCORE1"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_NOCACHE_INITVAR_OSCORE1
#endif


#ifdef OS_STOP_SEC_NOCACHE_INITVAR_OSCORE1
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_NOCACHE_INITVAR_OSCORE1
#endif


/* OSCORE2 const section */

#ifdef OS_START_SEC_VAR_OSCORE2
#ifdef __HIGHTEC__
#pragma section ".OS_VAR_OSCORE2"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_VAR_OSCORE2"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_VAR_OSCORE2"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_VAR_OSCORE2"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_VAR_OSCORE2"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_VAR_OSCORE2
#endif


#ifdef OS_STOP_SEC_VAR_OSCORE2
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
#undef OS_STOP_SEC_VAR_OSCORE2
#endif


#ifdef OS_START_SEC_INITVAR_OSCORE2
#ifdef __HIGHTEC__
#pragma section ".OS_INITVAR_OSCORE2"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_INITVAR_OSCORE2"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_INITVAR_OSCORE2"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_INITVAR_OSCORE2"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_INITVAR_OSCORE2"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_INITVAR_OSCORE2
#endif


#ifdef OS_STOP_SEC_INITVAR_OSCORE2
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_INITVAR_OSCORE2
#endif


#ifdef OS_START_SEC_NOCACHE_VAR_OSCORE2
#ifdef __HIGHTEC__
#pragma section ".OS_NOCACHE_VAR_OSCORE2"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_NOCACHE_VAR_OSCORE2"
#endif
#ifdef __TASKING__
#pragma section .farbss ".OS_NOCACHE_VAR_OSCORE2"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_NOCACHE_VAR_OSCORE2"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_NOCACHE_VAR_OSCORE2"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_NOCACHE_VAR_OSCORE2
#endif


#ifdef OS_STOP_SEC_NOCACHE_VAR_OSCORE2
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
#undef OS_STOP_SEC_NOCACHE_VAR_OSCORE2
#endif


#ifdef OS_START_SEC_NOCACHE_INITVAR_OSCORE2
#ifdef __HIGHTEC__
#pragma section ".OS_NOCACHE_INITVAR_OSCORE2"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_NOCACHE_INITVAR_OSCORE2"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_NOCACHE_INITVAR_OSCORE2"
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_NOCACHE_INITVAR_OSCORE2"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_NOCACHE_INITVAR_OSCORE2"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_NOCACHE_INITVAR_OSCORE2
#endif


#ifdef OS_STOP_SEC_NOCACHE_INITVAR_OSCORE2
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__


#endif
#ifdef __DCC__


#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_NOCACHE_INITVAR_OSCORE2
#endif


#ifdef OS_START_SEC_GLOBAL_NOCACHE_VAR
#ifdef __HIGHTEC__
#pragma section ".OS_GLOBAL_NOCACHE_VAR"
#endif
#ifdef __ghs__
#pragma ghs section bss = ".OS_GLOBAL_NOCACHE_VAR"
#endif
#ifdef __TASKING__
#pragma section farbss ".OS_GLOBAL_NOCACHE_VAR"
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_GLOBAL_NOCACHE_VAR"
#endif
#ifdef __clang__
#pragma clang section bss = ".OS_GLOBAL_NOCACHE_VAR"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_GLOBAL_NOCACHE_VAR
#endif


#ifdef OS_STOP_SEC_GLOBAL_NOCACHE_VAR
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
#undef OS_STOP_SEC_GLOBAL_NOCACHE_VAR
#endif


#ifdef OS_START_SEC_GLOBAL_NOCACHE_INITVAR
#ifdef __HIGHTEC__
#pragma section ".OS_GLOBAL_NOCACHE_INITVAR"
#endif
#ifdef __ghs__
#pragma ghs section data = ".OS_GLOBAL_NOCACHE_INITVAR"
#endif
#ifdef __TASKING__
#pragma section fardata ".OS_GLOBAL_NOCACHE_INITVAR"
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes = @ ".OS_GLOBAL_NOCACHE_INITVAR"
#endif
#ifdef __clang__
#pragma clang section data = ".OS_GLOBAL_NOCACHE_INITVAR"
#endif
#undef MEMMAP_ERROR
#undef OS_START_SEC_GLOBAL_NOCACHE_INITVAR
#endif
#ifdef OS_STOP_SEC_GLOBAL_NOCACHE_INITVAR
#ifdef __HIGHTEC__
#pragma section
#endif
#ifdef __ghs__
#pragma ghs section
#endif
#ifdef __TASKING__
#pragma section fardata restore
#endif
#ifdef __GNU__

#endif
#ifdef __DCC__

#endif
#ifdef __IAR__
#pragma default_variable_attributes =
#endif
#ifdef __clang__
#pragma clang section data = ""
#endif
#undef MEMMAP_ERROR
#undef OS_STOP_SEC_GLOBAL_NOCACHE_INITVAR
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

