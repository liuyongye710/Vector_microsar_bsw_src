
/*
********************************************************************************
*
*  File name: Os_Arch_Exception.h
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
* Change: Specify the name of the exception interrupt function and the entry
*         point for exception interrupt handling.
* Cause: Update
********************************************************************************
* Version: 3.3
* Author/Date: JiangGL/2024.01.09
* Change: Optimizing a type of interruption that cannot record on-site types.
* Cause: Optimize
********************************************************************************
*/
#ifndef OS_ARCH_EXCEPTION_H_
#define OS_ARCH_EXCEPTION_H_
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Arch_Exception_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
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
extern FUNC(void, OS_CODE) Os_Arch_Exception_CriticalInput(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_MachineCheck(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Data(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Instruction(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_ExternalInterrupt(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Alignment(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Program(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_PerformanceMonitor(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Trap(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Debug(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_EFPU_Data(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_EFPU_Round(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_TBD(void);
extern FUNC(void, OS_CODE) Os_Arch_Irq_Unhandled(void);
#if( OS_ARCH_EXCEPTION_ERRIMFORMATION == STD_ON )
extern FUNC(void, OS_CODE) Os_Arch_IsrNest_Push(uint32 address);
extern FUNC(void, OS_CODE) Os_Arch_IsrNest_Pop(void);
extern FUNC(void, OS_CODE) Os_Arch_Exception_Entry
(
    Os_Arch_ExceptionSourceType exceptionSourceType,
    uint32 currentSp
);
#endif /* OS_ARCH_EXCEPTION_ERRIMFORMATION == STD_ON */

extern FUNC(void, OS_CODE) Os_Arch_Cat1InterruptAsm(Os_Arch_Cat1HandlerType isrHandle);

/*
********************************************************************************
* Function Name: Os_Arch_Cat2InterruptAsm
*
* Explanation: The second type of interrupt service function processing entry.
*
* Param: isrconfig: Type 2 Interrupt Configuration Structure
*
* Retval: None
********************************************************************************
*/
#define Os_Arch_Cat2InterruptAsm(isrconfig)                                                      \
__asm volatile("se_mflr      r24                    " "\n");  /* Get lr to r24. */               \
__asm volatile("e_bl Os_Core_GetCurrentContext      " "\n");  /* Get now current context. */     \
__asm volatile("mr           r4,     r3             " "\n");  /* Mov r3 to r4. */                \
__asm volatile("e_lwz        r3,     0(r3)          " "\n");  /* Get Save sp point address. */   \
__asm volatile("e_stw        sp,     0(r3)          " "\n");  /* Save sp point. */               \
__asm volatile("e_lis        r3,     "#isrconfig"@h " "\n");  /* Get 'isrconfig' param. */       \
__asm volatile("e_or2i       r3,     "#isrconfig"@l " "\n");  /* Get 'isrconfig' param. */       \
__asm volatile("e_stwu       r24,    -4(sp)         " "\n");  /* Save lr to stack. */            \
__asm volatile("e_bl Os_Isr_Entry                   " "\n");  /* Call Os_Isr_Entry. */           \
__asm volatile("wrteei       0                      " "\n");  /* Disable interrupt. */           \
__asm volatile("e_lwzu       r24,    0(sp)          " "\n");  /* Restore lr to r24. */           \
__asm volatile("e_bl Os_Core_GetCurrentContext      " "\n");  /* Get now current context. */     \
__asm volatile("e_lwz        r3,     0(r3)          " "\n");  /* Get Save sp point address. */   \
__asm volatile("e_lwz        sp,     0(r3)          " "\n");  /* Set sp point. */                \
__asm volatile("se_mtlr      r24                    " "\n");  /* Restore lr. */

#if( OS_ARCH_EXCEPTION_ERRIMFORMATION == STD_ON )
/* Exception interrupt entry. */
#define _Os_Arch_ExceptionInterruptAsm(sourceType)                                              \
__asm volatile("mr          r4,     sp              " "\n");  /* Give SP to r4.        */       \
__asm volatile("e_lis       r3,     "#sourceType"@h " "\n");  /* Give the address to r3.*/      \
__asm volatile("e_or2i      r3,     "#sourceType"@l " "\n");  /* Give the address to r3.*/      \
__asm volatile("e_bl Os_Arch_Exception_Entry        " "\n");  /* Call Os_Arch_Exception_Entry. */
/* Unusual interrupt handling macro. */
#define Os_Arch_ExceptionInterruptAsm(sourceType) _Os_Arch_ExceptionInterruptAsm(sourceType)
#else
/* Unusual interrupt handling macro. */
#define Os_Arch_ExceptionInterruptAsm(sourceType) Os_FatalError()
#endif /* OS_ARCH_EXCEPTION_ERRIMFORMATION == STD_ON */

#endif /* OS_ARCH_EXCEPTION_H_ */
