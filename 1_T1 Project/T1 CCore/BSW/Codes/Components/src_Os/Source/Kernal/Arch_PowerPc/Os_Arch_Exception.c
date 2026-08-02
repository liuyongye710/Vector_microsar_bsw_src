/*
********************************************************************************
*
*  File name: Os_Arch_Exception.c
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: JiangGL/2023.09.05
* Change: Fit for CCFC3008.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: JiangGL/2023.11.21
* Change: Concretize the name of the exception interrupt function.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Arch_Exception.h"
#include "Os_Arch_Compiler.h"
#include "T1_AppInterface.h"
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
OS_ARCH_CODE_SECTION(OS_EXCVEC_OSCORE)
OS_ARCH_GLOBAL_EXCINTVEC(OS_EXCVEC_OSCORE)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_CriticalInput)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_MachineCheck)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_Data)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_Instruction)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_ExternalInterrupt)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_Alignment)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_Program)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_PerformanceMonitor)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_Trap)
#ifdef T1_ENABLE
#ifndef T1_DISABLE_T1_FLEX
OS_ARCH_EXCEPTION_ENTRY(T1_OuterExceptionHandler)
#endif
#endif
#if !defined(T1_ENABLE) || defined(T1_DISABLE_T1_FLEX)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_Debug)
#endif
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_EFPU_Data)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_EFPU_Round)
OS_ARCH_EXCEPTION_ENTRY(Os_Arch_Exception_TBD)
