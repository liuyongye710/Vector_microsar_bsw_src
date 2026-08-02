/*
********************************************************************************
*
*  File name: Os_Arch_Mach_CCFC3008.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2022.01.12
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
* Change: Adding macro operations for reading special registers.
* Cause: Update
********************************************************************************
*/
#ifndef OS_ARCH_MACH_CCFC3008_H_
#define OS_ARCH_MACH_CCFC3008_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Os_Arch_Types.h"
#include "Os_Cfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/* Leading 0 hardware supports macro switches. */
#define OS_CFG_COUNT_LEAD_ZEROS_HARDWARE                (STD_ON)
/* Assembly macro for "mtspr" operation. */
#define Os_Hal_WriteSPR(spr, val)  __asm volatile("mtspr "#spr", %0" "\n" :: "r" (val))
/* Abstraction of reading a core special purpose register. */
#define Os_Hal_ReadSPR(spr, val)   __asm volatile("mfspr %0," #spr "\n" : "=r" (val))

/* Support software triggered interrupt macro definition. */
#define OS_SUPPORT_HARDWARE_TRIGGER_INTERRUPT
/* Core. */
/* MC_ME Register base address. */
#define OS_HAL_MC_ME_BASE_ADDRESS                       (0xFFFB8000U)
/* Interrupt Status Register. */
#define OS_HAL_MC_ME_IS_OFFSET                          (0x0000000CU)
/* Core0 Address Register. */
#define OS_HAL_MC_ME_CADDR1_OFFSET                      (0x000001E4U)
/* Core1 Address Register. */
#define OS_HAL_MC_ME_CADDR3_OFFSET                      (0x000001ECU)
/* Core0 Control Register. */
#define OS_HAL_MC_ME_CCTL1_OFFSET                       (0x000001C6U)
/* Core1 Control Register. */
#define OS_HAL_MC_ME_CCTL3_OFFSET                       (0x000001CAU)
/* Global Status Register. */
#define OS_HAL_MC_ME_GS_OFFSET                          (0x00000000U)
/* Core Control Register. */
#define OS_HAL_MC_ME_MCTL_OFFSET                        (0x00000004U)
/* MC_ME unlock key1. */
#define OS_HAL_MC_ME_KEY1                               (0x00005AF0U)
/* MC_ME unlock key2. */
#define OS_HAL_MC_ME_KEY2                               (0x0000A50FU)
/* Core reset mask. */
#define OS_HAL_MC_ME_CORE_RESET_MASK                    (0x00000001U)
/* ME_CCTL MASK to control core. */
#define OS_HAL_MC_ME_CCTL_MASK                          (0x00FEU)
/* Current chip mode status mask. */
#define OS_HAL_CURRENT_MODE_MAKS                        (0xF0000000U)
/* Mode transition status. */
#define OS_HAL_MTRANS_MASK                              (0x08000000U)
/* Core Address Register. */
#define OS_HAL_MC_ME_CADDR_OFFSET(coreId)               ((coreId)==0?OS_HAL_MC_ME_CADDR1_OFFSET:OS_HAL_MC_ME_CADDR3_OFFSET)
/* Core Control Register. */
#define OS_HAL_MC_ME_CCTL_OFFSET(coreId)                ((coreId)==0?OS_HAL_MC_ME_CCTL1_OFFSET:OS_HAL_MC_ME_CCTL3_OFFSET)

/* Define mcu architecture. */
#define OS_ARCH                                         (ARCH_POWERPC)

/* Timer */
/* Interrupt resource. */
#define OS_ARCH_INTMASKLEVE_SUPPORT                     (STD_ON)

/* Stack resource. */
#define OS_STACK_TYPE_WIDTH                             (4U)
#define OS_STACK_RESERVED                               (0xAAAAAAAAU)
#define OS_GET_STACK_BOTTOM(StackArray)                 (&(StackArray)[0U])
#define OS_GET_STACK_TOP(StackArray, StackSize)         (&(StackArray)[(((StackSize)/OS_STACK_TYPE_WIDTH) - 1U)])
/* The actual stack head offset used. */
#define OS_STACK_TOP_OFFSET                             (16U)

/* Memory Protection Unit. */
/* Number of mpu's REGION. */
#define OS_CORE_CMPU_REGION_CNT                         (12U)
/* The region number of the CMPU used in the stack. */
#define OS_CORE_CMPU_STACK_REGION                       (11U)

/* INTC_1 */
#define OS_HAL_INTC1_BASE_ADDRESS                       (0xFC040000U)
#define OS_HAL_INTC_BCR_OFFSET                          (0x00000000U)
#define OS_HAL_INTC_MPROT_OFFSET                        (0x00000004U)
#define OS_HAL_INTC_CPR0_OFFSET                         (0x00000010U)
#define OS_HAL_INTC_CPR1_OFFSET                         (0x00000014U)
#define OS_HAL_INTC_CPR2_OFFSET                         (0x00000018U)
#define OS_HAL_INTC_IACKR0_OFFSET                       (0x00000020U)
#define OS_HAL_INTC_IACKR1_OFFSET                       (0x00000024U)
#define OS_HAL_INTC_IACKR2_OFFSET                       (0x00000028U)
#define OS_HAL_INTC_EOIR0_OFFSET                        (0x00000030U)
#define OS_HAL_INTC_EOIR1_OFFSET                        (0x00000034U)
#define OS_HAL_INTC_EOIR2_OFFSET                        (0x00000038U)
#define OS_HAL_INTC_PSR_OFFSET(n)                       (0x00000060U + ((n) << 1U))
#define OS_HAL_INTC_SSCIR(n)                            (0x00000040U + (n))

#define OS_HAL_CPR_OFFSET(coreId)                       (OS_HAL_INTC_CPR0_OFFSET + ((uint32)(coreId) << 2U))
#define OS_HAL_IACKR_OFFSET(coreId)                     (OS_HAL_INTC_IACKR0_OFFSET + ((uint32)(coreId) << 2U))

#define OS_CAT1_MASKLEVE                                (0x80U)
#define OS_CAT2_MASKLEVE                                (0x40U)

/* Software interrupts numbers. */
#define OS_HAL_INTC_SOFT_INTERRUPTS_NUM                 (32U)
/* Mask to trigger software Interrupt by SSCRI. */
#define OS_HAL_INTC_SSCIR_TRIGGER_MSK                   (0x02U)
/* Mask to trigger software Interrupt by PSR. */
#define OS_HAL_INTC_PSR_TRIGGER_MSK                     (0x0100U)
/* Mask to acknowledge software Interrupt. */
#define OS_HAL_INTC_SSCIR_ACK_MSK                       (0x01U)

/* Semaphores2. */
/* Semaphores2 base address. */
#define OS_HAL_SEMA4_BASE_ADDRESS                       (0xFC03C000U)
/* Semaphores2 gate address. */
#define OS_HAL_SEMA4_GATE_ADDRESS(gateId)               (OS_HAL_SEMA4_BASE_ADDRESS + (gateId))
/* The gate is unlocked. */
#define OS_HAL_SEMA4_GATE_FREE                          (0U)
/* The gate lock value. */
#define OS_HAL_SEMA4_GATE_LOCK(coreId)                  ((uint8)(coreId) + 1U)

/* PIT Timer. */
/* PIT_0 Base address. */
#define OS_HAL_PIT0_BASE_ADDRESS                        (0xFFF84000U)
/* PIT_1 Base address. */
#define OS_HAL_PIT1_BASE_ADDRESS                        (0xFFF80000U)
#define OS_HAL_PIT_MCR_OFFSET                           (0x00000000U)
#define OS_HAL_PIT_LDVAL_OFFSET(n)                      (0x0100U + ((n) << 4U))
#define OS_HAL_PIT_CVAL_OFFSET(n)                       (0x0104U + ((n) << 4U))
#define OS_HAL_PIT_TCTRL_OFFSET(n)                      (0x0108U + ((n) << 4U))
#define OS_HAL_PIT_TFLG_OFFSET(n)                       (0x010CU + ((n) << 4U))

/* STM Timer. */
#define OS_HAL_STM0_BASE_ADDRESS                        (0xFC068000U)
#define OS_HAL_STM1_BASE_ADDRESS                        (0xFC06C000U)
#define OS_HAL_STM2_BASE_ADDRESS                        (0xFC070000U)
#define OS_HAL_STM_CR_OFFSET                            (0x00000000U)
#define OS_HAL_STM_CNT_OFFSET                           (0x00000004U)
#define OS_HAL_STM_CCR_OFFSET(n)                        (0x0010U + ((n) << 4U))
#define OS_HAL_STM_CIR_OFFSET(n)                        (0x0014U + ((n) << 4U))
#define OS_HAL_STM_CMP_OFFSET(n)                        (0x0018U + ((n) << 4U))

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
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#if( OS_CFG_COUNT_LEAD_ZEROS_HARDWARE == STD_ON )
/*
********************************************************************************
* Function Name: Os_Arch_CntLeadZeros
*
* Explanation: Count leading zeros.
*
* Param: sdata: Value to calculate.
*
* Retval: Value of Calculated.
********************************************************************************
*/
LOCAL_INLINE FUNC(uint32, OS_CODE) Os_Arch_CntLeadZeros(uint32 sdata)
{
    uint32 result = OS_ZERO_VALUE ;

    __asm volatile(
        "cntlzw.     %0,     %1"     "\n"
        :"=r" (result): "r" (sdata)
    );

    return result;
}
#endif /* OS_CFG_COUNT_LEAD_ZEROS_HARDWARE == STD_ON */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* OS_ARCH_MACH_CCFC3008_H_ */
