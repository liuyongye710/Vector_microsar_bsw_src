/*
********************************************************************************
*
*  File name: Os_Arch_Core.h
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
* Change: Add ROM_OS_IRQVEC_OSCORE_START statement.
* Cause: Update
********************************************************************************
*/
#ifndef OS_ARCH_CORE_H_
#define OS_ARCH_CORE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Types.h"
#include "Os_Arch_Types.h"
#include "Os_Arch_Lcfg.h"
#include "Os_Arch_Mach.h"
#include "Os_Arch_Kernal_Lcfg.h"
#include "Os_Arch_Interrupt_Lcfg.h"
#include "Os_SysCall_Types.h"
#include "Os_Spinlock_Types.h"
#include "Os_Arch_Compiler.h"
#include "Os_SysCall.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Disable all interrupts mask. */
#define OS_ARCH_INTDISABLEALLMASK   (0xFFFF)
#define OS_ARCH_FPU_ENABLE_MASK     (0x0000007CU)

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
extern const uint32 ROM_OS_IRQVEC_OSCORE_START[];

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
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/*
********************************************************************************
* Function Name: Os_Arch_GetCoreId
*
* Explanation: Get physical core id.
*
* Param: None
*
* Retval: Physical core id.
********************************************************************************
*/
LOCAL_INLINE FUNC(uint32, OS_CODE) Os_Arch_GetCoreId(void)
{
    uint32 result = OS_ZERO_VALUE;

    __asm volatile (
        "mfspr      %0,     pir         "    "\n" /* Get core id. */
        :"=r"(result):
    );

    return result;
}

/*
********************************************************************************
* Function Name: Os_Arch_IntDisableAll
*
* Explanation: Disable global interrupts using low-level interfaces.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_IntDisableAll(void)
{
    OS_ARCH_DISABLE();
}

/*
********************************************************************************
* Function Name: Os_Arch_IntEnableAll
*
* Explanation: Enable global interrupts using low-level interfaces.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_IntEnableAll(void)
{
    OS_ARCH_ENABLE();
}

/*
********************************************************************************
* Function Name: Os_Arch_Nop
*
* Explanation: Machine dry run once using the underlying interface.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_Nop(void)
{
    OS_ARCH_NOP();
}

/*
********************************************************************************
* Function Name: Os_Arch_Fpu_Init
*
* Explanation: Initialize the FPU.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_Fpu_Init(void)
{
    /* Do nothing. */
}

/*
********************************************************************************
* Function Name: Os_Arch_IntLevelIsHigher
*
* Explanation: Determine the current priority higher than configuring priority.
*
* Param: currentLevel: Current priority and configuring priority.
*        intLevel: Target level.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(boolean, OS_CODE) Os_Arch_IntLevelIsHigher
(
    Os_IntLevelType currentLevel,
    Os_IntLevelType intLevel
)
{
    boolean ret;

    if( OS_ZERO_VALUE == intLevel )
    {
        ret = TRUE;
    }
    else
    {
        if( currentLevel <= intLevel )
        {
            ret = TRUE;
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Arch_IntLevelIsLower
*
* Explanation: Determine the current priority lower than configuring priority.
*
* Param: currentLevel: Current priority and configuring priority.
*        intLevel: Target level.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(boolean, OS_CODE) Os_Arch_IntLevelIsLower
(
    Os_IntLevelType currentLevel,
    Os_IntLevelType intLevel
)
{
    boolean ret;

    if( (OS_ZERO_VALUE == currentLevel) && (OS_ZERO_VALUE != intLevel) )
    {
        ret = TRUE;
    }
    else
    {
        if( (intLevel <= currentLevel) && (OS_ZERO_VALUE != intLevel) )
        {
            ret = TRUE;
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Arch_SpinUnlock
*
* Explanation: Release the given spinlock.
*
* Param: spinlock: The spinlock to check. Parameter must not be NULL.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_SpinUnlock
(
    P2VAR(volatile Os_SpinlockType, AUTOMATIC, OS_APPL_DATA) spinlock
)
{
    /* Lock the spinlock. */
    *(volatile uint32*)(spinlock) = OS_SPINLOCK_UNLOCK;
}

/*
********************************************************************************
* Function Name: Os_Arch_GetIntMaskLevel
*
* Explanation: Get interrupt mask by set basepri reg.
*
* Param: None
*
* Retval: interrupt mask level.
********************************************************************************
*/
LOCAL_INLINE FUNC(Os_IntLevelType, OS_CODE) Os_Arch_GetIntMaskLevel(void)
{
    uint32 result = OS_ZERO_VALUE;
    uint32 cprAddress;

    /* Get cpr address. */
    __asm volatile("mfspr  %0,  sprg1  "  "\n"  :"=r" (cprAddress):);
    /* Get cpr. */
    result = *(volatile uint32*)(cprAddress);

    return (Os_IntLevelType)result;
}

/*
********************************************************************************
* Function Name: Os_Arch_IntAllDisable
*
* Explanation: Disable all interrupts using low-level interfaces.
*
* Param: intState: The state acquired.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_IntAllDisable
(
    P2VAR(Os_Arch_IntState, AUTOMATIC, OS_APPL_DATA) intState
)
{
    uint32 cprAddress;

    /* Get cpr address. */
    __asm volatile("mfspr  %0,  sprg1  "  "\n"  :"=r" (cprAddress):);
    /* Get cpr. */
    *intState = *(volatile uint32*)(cprAddress);
    /* Set cpr. */
    *(volatile uint32*)(cprAddress) = OS_ARCH_INTDISABLEALLMASK;
}

/*
********************************************************************************
* Function Name: Os_Arch_IntEnable
*
* Explanation: Enable global interrupts using low-level interfaces.
*
* Param: intState: The state to set.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_IntEnable(Os_Arch_IntState intState)
{
    uint32 cprAddress;

    /* Get cpr address. */
    __asm volatile("mfspr  %0,  sprg1  "  "\n"  :"=r" (cprAddress):);
    /* Set cpr. */
    *(volatile uint32*)(cprAddress) = intState;
}

#if( OS_CFG_MULTI_CORE == STD_ON )
/*
********************************************************************************
* Function Name: Os_Arch_StartCore
*
* Explanation: Start the core at the passed address.
*
* Param: coreId: The core Id that was started.
*        startAddr: Core start address.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_StartCore
(
    CoreIdType coreId,
    uint32 startAddr
)
{
    uint32 mode;
    boolean bol;

    /* Set reset vector for core0, core0 will be reset on the next mode transition. */
    *(volatile uint32*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_CADDR_OFFSET(coreId)) = (startAddr | OS_HAL_MC_ME_CORE_RESET_MASK);
    /* Set modes in which core_0 will run. */
    *(volatile uint16*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_CCTL_OFFSET(coreId)) = OS_HAL_MC_ME_CCTL_MASK;
    /* Get CURRENT_MODE. */
    mode = *(volatile uint32*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_GS_OFFSET) & OS_HAL_CURRENT_MODE_MAKS;
    /* Enter key1 to unlock. */
    *(volatile uint32*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_MCTL_OFFSET) = mode | OS_HAL_MC_ME_KEY1;
    /* Enter key2 to unlock. */
    *(volatile uint32*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_MCTL_OFFSET) = mode | OS_HAL_MC_ME_KEY2;
    /* Waiting for end of transaction. */
    do
    {
        if( OS_ZERO_VALUE != (*(volatile uint32*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_GS_OFFSET) & OS_HAL_MTRANS_MASK) )
        {
            bol = TRUE;
        }
        else
        {
            bol = FALSE;
        }
    } while( TRUE == bol );

    /* Check mode has successfully been entered. */
    do
    {
        if( mode != (*(volatile uint32*)(OS_HAL_MC_ME_BASE_ADDRESS + OS_HAL_MC_ME_GS_OFFSET) & OS_HAL_CURRENT_MODE_MAKS) )
        {
            bol = TRUE;
        }
        else
        {
            bol = FALSE;
        }
    } while( TRUE == bol );
}
#endif /* OS_CFG_MULTI_CORE == STD_ON */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
extern FUNC(void, OS_CODE) Os_Arch_IntDisable
(
    P2VAR(Os_Arch_IntState, AUTOMATIC, OS_APPL_DATA) intState
);
extern FUNC(void, OS_CODE) Os_Arch_SetIntMaskLevel(Os_IntLevelType leve);
extern FUNC(void, OS_CODE) Os_Arch_IntEnableSource
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
);
extern FUNC(void, OS_CODE) Os_Arch_IntDisableSource
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
);
extern FUNC(void, OS_CODE) Os_Arch_ClearPendingIRQ
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
);
extern FUNC(void, OS_CODE) Os_Arch_ExceptionVectorTbInit(void);
extern FUNC(void, OS_CODE) Os_Arch_IntVectorTbInit(void);
extern FUNC(void, OS_CODE) Os_Arch_Trigger_Core(CoreIdType coreId);
extern FUNC(void, OS_CODE) Os_Arch_ClrMultiInt(CoreIdType coreId);
extern FUNC_P2VAR(Os_Arch_ContextDynType, OS_APPL_DATA, OS_CODE) Os_Arch_GetNextContext(void);
extern FUNC(void, OS_CODE) Os_Arch_SetNextContext
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) context
);
FUNC(boolean, OS_CODE) Os_Arch_LoadExclusive
(
    P2CONST(volatile uint32, AUTOMATIC, OS_APPL_CONST) addr
);
FUNC(boolean, OS_CODE) Os_Arch_StoreExclusive
(
    P2VAR(volatile uint32, AUTOMATIC, OS_APPL_DATA) addr,
    uint32 value
);
extern FUNC(Os_SpinlockType, OS_CODE) Os_Arch_SpinTryLock
(
    P2VAR(volatile Os_SpinlockType, AUTOMATIC, OS_APPL_DATA) spinlock
);
extern FUNC(void, OS_CODE) Os_Arch_HardwareInit(void);

#endif /* OS_ARCH_CORE_H_ */
