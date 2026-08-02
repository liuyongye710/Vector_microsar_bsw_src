/*
********************************************************************************
*
*  File name: Os_Arch_Compiler.h
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
*/
#ifndef OS_ARCH_COMPILER_H_
#define OS_ARCH_COMPILER_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Types.h"
#include "Os_Arch_Context_Types.h"
#include "Os_Arch_Mach_MP_Types.h"
#include "Os_SysCall_Types.h"
#include "Os_Cfg.h"
#include "Os_Arch_Mach_CCFC3008.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Function resource. */
#define OS_ARCH_DISABLE()                           __asm("wrteei 0")    /* Interrupt disable. */
#define OS_ARCH_ENABLE()                            __asm("wrteei 1")    /* Interrupt enable. */
#define OS_ARCH_NOP()                               __asm("nop")         /* Execute a null instruction. */
#define OS_ARCH_DSBAR()                                                  /* Data synchronization instruction. */
#define OS_ARCH_ISYNC()                             __asm("se_isync")    /* Instruction synchronization. */
#define OS_ARCH_MSYNC()                             __asm("msync")       /* Memory synchronization. */
#define OS_ARCH_SETSP(x)                            __asm("mr  sp, %0" ::"r"(x)) /* Set sp value. */
/* Declaration of code section for assembler. */
#define OS_ARCH_EXCEPTION_ENTRY(target)             __asm(".align 4");                                 \
                                                    __asm("e_b "#target);

#define OS_ARCH_CODE_SECTION(target)                __asm(".section   \"."#target"\", \"axv\"" "\n");

#define OS_ARCH_GLOBAL_EXCINTVEC(target)            __asm(".align 4"                           "\n");  \
                                                    __asm(".globl    _"#target                 "\n");  \
                                                    __asm("_"#target":"                        "\n");

#define OS_ARCH_EIINT_ENTRY(target)                 __asm(".long "#target                      "\n");

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
/*
********************************************************************************
* Function Name: Os_Arch_Stack_Switch
*
* Explanation: Stack switch.
*
* Param: current: Current context.
*        next: Next context.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_Stack_Switch
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) current,
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) next
)
{
    __asm volatile (
        "e_lwz    r8,     0(%0)       "   "\n"    /* Fetch the first element on the stack. */
        "e_addi   sp,     sp,     -4  "   "\n"    /* Move stack pointer. */
        "e_stw    r8,     0(sp)       "   "\n"    /* Write the element into the stack. */
        "e_stw    sp,     0(%0)       "   "\n"    /* Save current sp. */
        "e_lwz    sp,     0(%1)       "   "\n"    /* Restore the next context sp. */
        :: "r" (current),"r" (next)
    );
}

/*
********************************************************************************
* Function Name: Os_Arch_Stack_Restore
*
* Explanation: Stack restore.
*
* Param: next: Next context.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_Stack_Restore
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) next
)
{
    __asm volatile (
        "e_lwz    sp,     0(%0)       "       "\n"    /* Restor current sp. */
        "e_lwz    r8,     0(sp)       "       "\n"    /* Fetch the first element on the stack. */
        "e_stw    r8,     0(%0)       "       "\n"    /* Write the element back into the variable. */
        "e_addi   sp,     sp,     4   "       "\n"    /* Move stack pointer. */
        :: "r" (next)
    );
}

/*
********************************************************************************
* Function Name: Os_Arch_SysCall
*
* Explanation: System call, Raise the trap0 interrupt.
*
* Param: callData: Systemcall required parameters.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_SysCall
(
    P2VAR(Os_SysCallType, AUTOMATIC, OS_APPL_DATA) callData
)
{
    /* Trigger SysCall. */
    __asm volatile (
        "se_mr  r3, r7" "\n"
        "se_sc        " "\n"
        :
        : "r" (callData)
        : "r3", "memory"
    );
}

#if( OS_CORE_MPU == STD_ON )
/*
********************************************************************************
* Function Name: Os_Arch_CoreMpEnable
*
* Explanation: Enable the Core MPU.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_CoreMpEnable(void)
{
    /* Enable Core mpu function. */
    Os_Hal_WriteSPR (mpu0csr0 , OS_ARCH_CMPU_ENABLE_MASK);
}

/*
********************************************************************************
* Function Name: Os_Arch_CoreMpDisableAll
*
* Explanation: Disable the core-level MPU.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_CoreMpDisableAll(void)
{
    uint32 region;

    /* Disable Core mpu function. */
    Os_Hal_WriteSPR (mpu0csr0 , OS_ARCH_CMPU_DISABLE_MASK);
    /* Disable all the regions. */
    for( region = OS_ARCH_MP_INIT; region < OS_CORE_CMPU_REGION_CNT; region++ )
    {
        /* Disable the protective effect of this CMPU region. */
        Os_Hal_WriteSPR (mas0, OS_ARCH_CMPU_MAS0_VALID_MSK | OS_ARCH_CMPU_MAS0_SEL_MSK | OS_ARCH_CMPU_MAS0_ESEL(region));
        /* Set CMPU region TID and PID_MASK. */
        Os_Hal_WriteSPR (mas1, OS_ZERO_VALUE);
        /* Set CMPU region upper address. */
        Os_Hal_WriteSPR (mas2, OS_ZERO_VALUE);
        /* Set CMPU region lower address. */
        Os_Hal_WriteSPR (mas3, OS_ZERO_VALUE);
        /* Perform write operations on CMPU entries. */
        __asm volatile("mpuwe   " "\n");
        /* MPU instruction synchronization. */
        __asm volatile("mpusync " "\n");
        /* System instruction synchronization. */
        __asm volatile("se_isync" "\n");
    }
}


/*
********************************************************************************
* Function Name: Os_Arch_CoreMpSwitch
*
* Explanation: Switch the core-level MPU region.
*
* Param: mpRegionCfg: The core region configuration Data.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_CoreMpSwitch
(
    P2CONST(Os_Arch_CoreMpRegionCfgType, AUTOMATIC, OS_APPL_CONST) mpRegionCfg
)
{
    /* Set CMPU region access. */
    Os_Hal_WriteSPR (mas0, OS_ARCH_CMPU_MAS0_VALID_MSK | OS_ARCH_CMPU_MAS0_SEL_MSK
                        | (mpRegionCfg->mpuMpat)
                        | OS_ARCH_CMPU_MAS0_ESEL(mpRegionCfg->mpuRegion));
    /* Set CMPU region TID and PID_MASK. */
    Os_Hal_WriteSPR (mas1, OS_ZERO_VALUE);
    /* Set CMPU region upper address. */
    Os_Hal_WriteSPR (mas2, (mpRegionCfg->mpuMpua));
    /* Set CMPU region lower address. */
    Os_Hal_WriteSPR (mas3, (mpRegionCfg->mpuMpla));
    /* Perform write operations on CMPU entries. */
    __asm volatile("mpuwe   " "\n");
    /* MPU instruction synchronization. */
    __asm volatile("mpusync " "\n");
    /* System instruction synchronization. */
    __asm volatile("se_isync" "\n");
}

/*
********************************************************************************
* Function Name: Os_Arch_MpStackSwitch
*
* Explanation: Switch to stack protected address.
*
* Param: startAddr: Stack start address.
*        endAddr: Stack end address.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_MpStackSwitch
(
    P2VAR(Os_Stack_Address, AUTOMATIC, OS_APPL_DATA) startAddr,
    P2VAR(Os_Stack_Address, AUTOMATIC, OS_APPL_DATA) endAddr
)
{
    /* Set CMPU region access. */
    Os_Hal_WriteSPR (mas0, OS_ARCH_CMPU_MAS0_VALID_MSK | OS_ARCH_CMPU_MAS0_SEL_MSK
                         | OS_ARCH_CMPU_MAS0_UW_MSK | OS_ARCH_CMPU_MAS0_URX_MSK
                         | OS_ARCH_CMPU_MAS0_SW_MSK | OS_ARCH_CMPU_MAS0_SRX_MSK
                         | OS_ARCH_CMPU_MAS0_ESEL(OS_CORE_CMPU_STACK_REGION));
    /* Set CMPU region TID and PID_MASK. */
    Os_Hal_WriteSPR (mas1, OS_ZERO_VALUE);
    /* Set CMPU region upper address. */
    Os_Hal_WriteSPR (mas2, (uint32)startAddr);
    /* Set CMPU region lower address. */
    Os_Hal_WriteSPR (mas3, (uint32)endAddr);

    /* Perform write operations on CMPU entries. */
    __asm volatile("mpuwe   " "\n");
    /* Perform write operations on CMPU entries. */
    __asm volatile("mpusync " "\n");
    __asm volatile("se_isync" "\n");
}

#endif /* OS_CORE_MPU == STD_ON */

extern FUNC(void, OS_CODE) Os_Arch_Context_SwitchNext
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) next
);
extern FUNC(void, OS_CODE) Os_Arch_Context_SwitchFirst
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) next
);
extern FUNC(void, OS_CODE) Os_Arch_Context_Switch
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) current,
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) next
);

#endif /* OS_ARCH_COMPILER_H_ */
