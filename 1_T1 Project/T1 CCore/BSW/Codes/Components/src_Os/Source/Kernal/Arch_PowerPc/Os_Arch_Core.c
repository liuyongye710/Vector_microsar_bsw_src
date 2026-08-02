/*
********************************************************************************
*
*  File name: Os_Arch_Core.c
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
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Arch_Core.h"
#include "Os_Arch_Context.h"
#include "Os_Core.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/* Bind interrupts to the corresponding kernel. */
#define OS_HAL_INTC_PSR_MARK(coreId)    ((uint16)(0x8000U >>(coreId)))
/* Os_Arch_IntDisable disbale interrupt level mask. */
#define OS_ARCH_INTDISABLEMASK(coreId)  (OsCfg_Arch_IsrMaskLevel[coreId]->IntDisableMaskLevel)

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
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

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
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*
********************************************************************************
* Function Name: Os_Arch_IntDisable
*
* Explanation: Disable global interrupts using low-level interfaces.
*
* Param: intState: The state acquired.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_IntDisable
(
    P2VAR(Os_Arch_IntState, AUTOMATIC, OS_APPL_DATA) intState
)
{
    uint32 cprAddress;
    CoreIdType coreId;

    /* Get coreId. */
    coreId = Os_Core_GetLogicId();
    /* Get cpr address. */
    __asm volatile("mfspr  %0,  sprg1  "  "\n"  :"=r" (cprAddress):);
    /* Get cpr. */
    *intState = *(volatile uint32*)(cprAddress);
    /* Set cpr. */
    *(volatile uint32*)(cprAddress) = OS_ARCH_INTDISABLEMASK(coreId);
}

/*
********************************************************************************
* Function Name: Os_Arch_ClearPendingIRQ
*
* Explanation: Clear nvic interrupt pending flag.
*
* Param: isrSource: The number of the external interrupt to clear.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_ClearPendingIRQ
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
)
{
    OS_DUMMY_STATEMENT(isrSource);
}

/*
********************************************************************************
* Function Name: Os_Arch_ExceptionVectorTbInit
*
* Explanation: Initialize the interrupt vector table.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_ExceptionVectorTbInit(void)
{
    uint32 exceptionAddress;

    /* Obtain the starting address of the exception vector table. */
   __asm volatile (
       "e_lis      %0,     ROM_OS_EXCVEC_OSCORE_START@h    " "\n"
       "e_or2i     %0,     ROM_OS_EXCVEC_OSCORE_START@l    " "\n"
       :"=r" (exceptionAddress):
   );

    /* Remap Exception Interrupt Vector Table. */
    __asm volatile ("mtspr ivpr, %0" "\n":: "r" (exceptionAddress) );
}

/*
********************************************************************************
* Function Name: Os_Arch_IntVectorTbInit
*
* Explanation: Initialize the interrupt vector table.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE)Os_Arch_IntVectorTbInit(void)
{
    uint32 coreId;
    uint32 irqAddress;
    coreId = Os_Arch_GetCoreId();

    /* Obtain the starting address of the exception vector table. */
    __asm volatile (
        "e_lis      %0,     ROM_OS_IRQVEC_OSCORE_START@h    " "\n"
        "e_or2i     %0,     ROM_OS_IRQVEC_OSCORE_START@l    " "\n"
        :"=r" (irqAddress):
    );
    *((volatile uint32 *)(OS_HAL_INTC1_BASE_ADDRESS + OS_HAL_IACKR_OFFSET(coreId))) = irqAddress;
}

/*
********************************************************************************
* Function Name: Os_Arch_HardwareInit
*
* Explanation: Chip hardware initialization Kernel related.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_HardwareInit(void)
{
    uint32 coreId;
    uint32 intcCprBaseAddress;

    /* Get Core id. */
    coreId = Os_Arch_GetCoreId();
    /* Anomaly vector table remapping. */
    Os_Arch_ExceptionVectorTbInit ();
    /* Anomaly vector table remapping. */
    Os_Arch_IntVectorTbInit();

    /* Obtain the CPR address of coreId. */
    intcCprBaseAddress = OS_HAL_INTC1_BASE_ADDRESS + OS_HAL_CPR_OFFSET(coreId);
    /* Set interrupt operation priority to minimum. */
    *(volatile uint32 *)(intcCprBaseAddress) = OS_ZERO_VALUE;
    /* Save the address of (INTC_CPR) in sprg1. */
    __asm volatile("mtspr sprg1, %0" "\n"::"r"(intcCprBaseAddress));
    /* FPU function initialization. */
    Os_Arch_Fpu_Init();
}

/*
********************************************************************************
* Function Name: Os_Arch_IntEnableSource
*
* Explanation: Enable interrupt source.
*
* Param: isrSource: Interrupt configuration of to enable.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_IntEnableSource
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
)
{
    uint16 regvalue;
    uint32 coreId = Os_Arch_GetCoreId();

    if( NULL_PTR != isrSource )
    {
        *((volatile uint32 *)(OS_HAL_INTC1_BASE_ADDRESS +
            OS_HAL_INTC_BCR_OFFSET)) = OS_ZERO_VALUE;
        /* Obtain the PSR2 address of coreId. */
        regvalue = OS_HAL_INTC_PSR_MARK(coreId);
        /* Calculate Priority. */
        regvalue |= isrSource->level;
        /* Configure the priority of the corresponding kernel. */
        *(volatile uint16 *)(OS_HAL_INTC1_BASE_ADDRESS +
            OS_HAL_INTC_PSR_OFFSET((uint32)(isrSource->number))) = regvalue;
    }
}

/*
********************************************************************************
* Function Name: Os_Arch_IntDisableSource
*
* Explanation: Enable interrupt source.
*
* Param: isrSource: Interrupt configuration of to disable.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_IntDisableSource
(
    P2CONST(Os_Arch_IsrSourceType, AUTOMATIC, OS_APPL_CONST) isrSource
)
{
    uint16 regvalue;
    uint32 coreId = Os_Arch_GetCoreId();

    if( NULL_PTR != isrSource )
    {
        /* Obtain the PSR2 address of coreId. */
        regvalue = OS_HAL_INTC_PSR_MARK(coreId);
        /* Configure the priority of the corresponding kernel. */
        *((volatile uint16 *)(OS_HAL_INTC1_BASE_ADDRESS +
            OS_HAL_INTC_PSR_OFFSET((uint32)(isrSource->number)))) = regvalue;
    }
}

/*
********************************************************************************
* Function Name: Os_Arch_SetIntMaskLevel
*
* Explanation: Set interrupt mask by set basepri reg.
*
* Param: level: interrupt mask level.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_SetIntMaskLevel(Os_IntLevelType leve)
{
    uint32 coreId = OS_ZERO_VALUE;
    uint32 cprAddress;

    coreId = Os_Arch_GetCoreId();

    /* Get cpr address. */
    __asm volatile("mfspr  %0,  sprg1  "  "\n"  :"=r" (cprAddress):);

    /* Masking is Class I interrupts. */
    if( OS_CAT1_MASKLEVE == leve )
    {
        leve = OsCfg_Arch_IsrMaskLevel[coreId]->Cat1MaskLevel;
    }
    /* Masked is Class II interrupts. */
    else if( OS_CAT2_MASKLEVE == leve )
    {
        /* Obtain the current running priority. */
        Os_IntLevelType currentLevel = Os_Arch_GetIntMaskLevel ();

        leve = OsCfg_Arch_IsrMaskLevel[coreId]->Cat2MaskLevel;
        /* Determine the relationship between the priority to be set and the
           current running priority. */
        if( leve < currentLevel )
        {
            leve = currentLevel;
        }
    }
    /* Mask other level interrupts. */
    else
    {
        /* Do nothing. */
    }
    /* Set interrupt operation priority. */
    *(volatile uint32*)(cprAddress) = leve;
}

/*
********************************************************************************
* Function Name: Os_Arch_Trigger_Core
*
* Explanation: Trigger the given core softirq.
*
* Param: coreId: Core ID to trigger.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_Trigger_Core(CoreIdType coreId)
{
    uint32 pu1Unit;
    const Os_Arch_IsrSourceType* isrSource = OS_CORE_GETMULTICOMMISRSOURCE(coreId);

    /* Get the interrupt. */
    pu1Unit = (uint32)(isrSource->number);
    if( OS_HAL_INTC_SOFT_INTERRUPTS_NUM > pu1Unit )
    {
        /* Trigger the softirq. */
        *(volatile uint8*)(OS_HAL_INTC1_BASE_ADDRESS + OS_HAL_INTC_SSCIR(pu1Unit)) =
            OS_HAL_INTC_SSCIR_TRIGGER_MSK;
    }
    else
    {
        /* Trigger the peripheral irq. */
        *(volatile uint16*)(OS_HAL_INTC1_BASE_ADDRESS + OS_HAL_INTC_PSR_OFFSET(pu1Unit))
            |= OS_HAL_INTC_PSR_TRIGGER_MSK;
    }

    OS_ARCH_ISYNC();
}

/*
********************************************************************************
* Function Name: Os_Arch_ClrMultiInt
*
* Explanation: Clear the given core softirq.
*
* Param: coreId: Core Id to clear softirq.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_ClrMultiInt(CoreIdType coreId)
{
    uint32 pu1Unit;
    const Os_Arch_IsrSourceType* isrSource = OS_CORE_GETMULTICOMMISRSOURCE(coreId);

    pu1Unit = (uint32)(isrSource->number);
    if( OS_HAL_INTC_SOFT_INTERRUPTS_NUM > pu1Unit )
    {
        /* Clear generate Directed CPU Interrupt. */
        *(volatile uint8*)(OS_HAL_INTC1_BASE_ADDRESS + OS_HAL_INTC_SSCIR(pu1Unit)) =
            OS_HAL_INTC_SSCIR_ACK_MSK;
    }
    else
    {
        /* Do nothing. */
    }
}

/*
********************************************************************************
* Function Name: Os_Arch_GetNextContext
*
* Explanation: Get the context of the core.
*
* Param: None
*
* Retval: Core context.
********************************************************************************
*/
FUNC_P2VAR(Os_Arch_ContextDynType, OS_APPL_DATA, OS_CODE) Os_Arch_GetNextContext(void)
{
    return Os_CoreCfgData[Os_Core_GetLogicId()]->coreDyn->context;
}

/*
********************************************************************************
* Function Name: Os_Arch_SetNextContext
*
* Explanation: Set the context of the core.
*
* Param: context: Core context to be set.
*
* Retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Arch_SetNextContext
(
    P2VAR(Os_Arch_ContextDynType, AUTOMATIC, OS_APPL_DATA) context
)
{
    CoreIdType coreId;
    Os_CoreDynType* coreDyn;

    /* Get the current logical core Id. */
    coreId = Os_Core_GetLogicId();
    /* Get the current core dyn. */
    coreDyn = OS_CORE_GETDYN(coreId);
    coreDyn->context = context;
}

/*
********************************************************************************
* Function Name: Os_Arch_LoadExclusive
*
* Explanation: Uses a load exclusive synchronization instruction for the address,
*              which attempts to mark the address for exclusive access by the
*              current processor, and return the result.
*
* Param: addr: Address value to read from. Parameter must not be NULL.
*
* Retval: 0  Success.
*         1  No success.
********************************************************************************
*/
FUNC(boolean, OS_CODE) Os_Arch_LoadExclusive
(
    P2CONST(volatile uint32, AUTOMATIC, OS_APPL_CONST) addr
)
{
    uint32 spinlockValue;
    boolean ret;

    /* Attempt to obtain spinlock status. */
    spinlockValue = *(const volatile uint32*)(addr);
    if( OS_ZERO_VALUE != spinlockValue )
    {
        ret = OS_SPINLOCK_LOCK;
    }
    else
    {
        ret = OS_SPINLOCK_UNLOCK;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Arch_StoreExclusive
*
* Explanation: Tries to get the lock.
*
* Param: addr: Address of spinlock variable.
*        value: Write the value of spinlock variable.
*
* Retval: Lock state.
*         OS_SPINLOCK_UNLOCK: Get failed.
*         OS_SPINLOCK_LOCK: Get success.
********************************************************************************
*/
FUNC(boolean, OS_CODE) Os_Arch_StoreExclusive
(
    P2VAR(volatile uint32, AUTOMATIC, OS_APPL_DATA) addr,
    uint32 value
)
{
    boolean ret = OS_SPINLOCK_LOCK;
    Os_Arch_IntState intState;
    uint32 gateId;
    uint8 gateValue;

    __asm volatile(
        "msync                          " "\n"
        "e_addi  %0,    %1,     4       " "\n"  /* Get spinlockId address. */
        "e_lwz   %0,    0(%0)           " "\n"  /* Get spinlockId. */
        "e_andi  %0,    %0,     15      " "\n"  /* Get semaphores Id. */
        :"=r"(gateId):"r"(addr)
    );
    /* Disable interrupts. */
    Os_Arch_IntAllDisable(&intState);
    /* Get gate value. */
    gateValue = *(volatile uint8*)(OS_HAL_SEMA4_GATE_ADDRESS(gateId));
    /* The gate is unlocked. */
    if( OS_HAL_SEMA4_GATE_FREE == gateValue )
    {
        /* Get core id. */
        CoreIdType coreId = Os_Core_GetLogicId();
        /* Try to lock gate. */
        *(volatile uint8*)(OS_HAL_SEMA4_GATE_ADDRESS(gateId)) = OS_HAL_SEMA4_GATE_LOCK(coreId);
        /* Get gate state again. */
        gateValue = *(volatile uint8*)(OS_HAL_SEMA4_GATE_ADDRESS(gateId));
        /* The gate lock success. */
        if( OS_HAL_SEMA4_GATE_LOCK(coreId) == gateValue )
        {
            /* The spinlock is unlocking. */
            if( FALSE == Os_Arch_LoadExclusive(addr) )
            {
                /* Lock the spinlock. */
                *(volatile uint32*)(addr) = OS_SPINLOCK_LOCK;
                /* Get spinlock is success. */
                ret = OS_SPINLOCK_UNLOCK;
            }
            /* Unlock the gate. */
            *(volatile uint8*)(OS_HAL_SEMA4_GATE_ADDRESS(gateId)) = OS_HAL_SEMA4_GATE_FREE;
        }
    }
    /* Enable interrupts. */
    Os_Arch_IntEnable(intState);
    OS_DUMMY_STATEMENT(value);

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Arch_SpinTryLock
*
* Explanation: Tries to get the lock.
*
* Param: spinlock: The spinlock to lock. Parameter must not be NULL.
*
* Retval: Lock state.
********************************************************************************
*/
FUNC(Os_SpinlockType, OS_CODE) Os_Arch_SpinTryLock
(
    P2VAR(volatile Os_SpinlockType, AUTOMATIC, OS_APPL_DATA) spinlock
)
{
    Os_SpinlockType result = OS_SPINLOCK_UNLOCK;

    /* If spinlock is free (use load exclusive instruction here). */
    if( FALSE == Os_Arch_LoadExclusive(spinlock) )
    {
        /* Try to get the spinlock (use store exclusive instruction here). */
        if( FALSE == Os_Arch_StoreExclusive(spinlock, OS_SPINLOCK_LOCK) )
        {
            result = OS_SPINLOCK_LOCK;
            /* Memory barrier. */
            OS_ARCH_MSYNC();
        }
    }

    return result;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
