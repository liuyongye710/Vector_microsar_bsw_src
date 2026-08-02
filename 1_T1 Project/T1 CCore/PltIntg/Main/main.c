/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
* @file     main.c
* @version  1.0
* @date     2023 - 04 - 17
* @brief    Initial version.
*
*****************************************************************************/
#include "main.h"
#include "Mcu.h"
#include "EcuM.h"
#include "Os_Core.h"
#include"Mcu_LLDriver.h"

void Asm_InitRamSection (uint32 romStart, uint32 ramStart, uint32 ramEnd)
{
    while(ramStart <= ramEnd)
    {
        *(volatile uint32*)(ramStart) = *(volatile uint32*)(romStart);
        romStart+=4;
        ramStart+=4;
    }
}

void Asm_ClearRamSection (uint32 ramStart, uint32 ramEnd)
{
    while(ramStart <= ramEnd)
    {
        *(volatile uint32*)(ramStart) = 0;
        ramStart+=4;
    }
}

#define ASM_INIT_RAM_SECTION(ramStart,ramEnd,romStart)     \
    __asm volatile (                                       \
        "e_lis      r3,     ("#romStart")@h    " "\n"      \
        "e_or2i     r3,     ("#romStart")@l    " "\n"      \
        "e_lis      r4,     ("#ramStart")@h    " "\n"      \
        "e_or2i     r4,     ("#ramStart")@l    " "\n"      \
        "e_lis      r5,     ("#ramEnd")@h      " "\n"      \
        "e_or2i     r5,     ("#ramEnd")@l      " "\n"      \
        "e_bl       Asm_InitRamSection          " "\n"     \
    )

#define ASM_CLEAR_RAM_SECTION(ramStart,ramEnd)             \
    __asm volatile (                                       \
        "e_lis      r3,     ("#ramStart")@h    " "\n"      \
        "e_or2i     r3,     ("#ramStart")@l    " "\n"      \
        "e_lis      r4,     ("#ramEnd")@h      " "\n"      \
        "e_or2i     r4,     ("#ramEnd")@l      " "\n"      \
        "e_bl       Asm_ClearRamSection          " "\n"    \
    )

#define Os_Hal_ReadDefineVal(val,def)                      \
    __asm volatile (                                       \
        "e_lis      %0,     ("#def")@h    " "\n"           \
        "e_or2i     %0,     ("#def")@l    " "\n"           \
        :"=r" (val):                                       \
    )


void mpu_Init (void)
{
    uint32 address;
    Os_Hal_WriteSPR (mpu0csr0 , 0);

    Os_Hal_WriteSPR (mas0 , 0xA0800000 | OS_ARCH_CMPU_MAS0_IOVR_MSK | OS_ARCH_CMPU_MAS0_I_MSK | OS_ARCH_CMPU_MAS0_ESEL(0));
    Os_Hal_WriteSPR (mas1 , 0);
    Os_Hal_ReadDefineVal (address, RAM_OS_GLOBAL_NOCACHE_VAR_END - 1);
    Os_Hal_WriteSPR (mas2 , address); /*upper address*/
    Os_Hal_ReadDefineVal (address, RAM_OS_GLOBAL_NOCACHE_VAR_START);
    Os_Hal_WriteSPR (mas3 , address); /*lower address*/
    __asm volatile("mpuwe" "\n");
    __asm volatile("mpusync" "\n");

    Os_Hal_WriteSPR (mas0 , 0xA0800000 | OS_ARCH_CMPU_MAS0_IOVR_MSK | OS_ARCH_CMPU_MAS0_I_MSK | OS_ARCH_CMPU_MAS0_ESEL(1));
    Os_Hal_WriteSPR (mas1 , 0);
    Os_Hal_ReadDefineVal (address, RAM_OS_GLOBAL_NOCACHE_INITVAR_END - 1);
    Os_Hal_WriteSPR (mas2 , address); /*upper address*/
    Os_Hal_ReadDefineVal (address, RAM_OS_GLOBAL_NOCACHE_INITVAR_START);
    Os_Hal_WriteSPR (mas3 , address); /*lower address*/
    __asm volatile("mpuwe" "\n");
    __asm volatile("mpusync" "\n");

   Os_Hal_WriteSPR (mpu0csr0 , 0xFC01);   /* Bypass all permissions. */
}

/*
    PIT: 75Mhz
    STM: 25Mhz
*/
void main(void)
{
    uint32 coreId = Os_Core_GetLogicId();
    
    uint32 SprDbcr0_Value[3] = {0};
    SprDbcr0_Value[coreId] = MFSPR(SPR_DBCR0);
    SprDbcr0_Value[coreId] |= 0x40000000;
    MTSPR(SPR_DBCR0, SprDbcr0_Value[coreId]);
    
    uint32 Msr_Value[3] = {0};
    Msr_Value[coreId] = MFMSR();
    Msr_Value[coreId] |= 0x200U;
    MTMSR(Msr_Value[coreId]);
    if(OS_CORE_ID_2 == coreId )
    {
        ASM_CLEAR_RAM_SECTION(RAM_OS_GLOBAL_NOCACHE_VAR_START, RAM_OS_GLOBAL_NOCACHE_VAR_END);
        ASM_CLEAR_RAM_SECTION(RAM_OS_VAR_OSCORE2_START, RAM_OS_VAR_OSCORE2_END);
        ASM_CLEAR_RAM_SECTION(RAM_OS_VAR_OSCORE1_START, RAM_OS_VAR_OSCORE1_END);
        ASM_CLEAR_RAM_SECTION(RAM_OS_VAR_OSCORE0_START, RAM_OS_VAR_OSCORE0_END);
        ASM_CLEAR_RAM_SECTION(RAM_APP_INITVAR_DMEM0_START, RAM_APP_INITVAR_DMEM0_END);
        ASM_CLEAR_RAM_SECTION(RAM_APP_INITVAR_DMEM1_START, RAM_APP_INITVAR_DMEM1_END);

        ASM_INIT_RAM_SECTION(RAM_OS_GLOBAL_NOCACHE_INITVAR_START, RAM_OS_GLOBAL_NOCACHE_INITVAR_END, ROM_OS_GLOBAL_NOCACHE_INITVAR_START);
        ASM_INIT_RAM_SECTION(RAM_OS_INITVAR_OSCORE2_START, RAM_OS_INITVAR_OSCORE2_END, ROM_OS_INITVAR_OSCORE2_START);
        ASM_INIT_RAM_SECTION(RAM_OS_INITVAR_OSCORE1_START, RAM_OS_INITVAR_OSCORE1_END, ROM_OS_INITVAR_OSCORE1_START);
        ASM_INIT_RAM_SECTION(RAM_OS_INITVAR_OSCORE0_START,RAM_OS_INITVAR_OSCORE0_END, ROM_OS_INITVAR_OSCORE0_START);
        ASM_INIT_RAM_SECTION(RAM_APP_INITVAR_DMEM0_START,RAM_APP_INITVAR_DMEM0_END, ROM_APP_INITVAR_DMEM0_START);
        ASM_INIT_RAM_SECTION(RAM_APP_INITVAR_DMEM1_START,RAM_APP_INITVAR_DMEM1_END, ROM_APP_INITVAR_DMEM1_START);
        
        Mcu_Init(&McuModuleConfiguration);
        Mcu_InitClock(0);
        Mcu_SetMode(0);
        while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
        {
        }

        Mcu_DistributePllClock();
    }
    else
    {
    	Mcu_LLD_Enable_DCache();
    }
    mpu_Init();
    EcuM_Init();
}
