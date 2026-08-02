/*
********************************************************************************
*
*  File name:	Os_Arch_InterruptHandler_Lcfg.c
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
#include "Std_Types.h"
#include "Os_Types.h"
#include "Os_Arch_Kernal_Lcfg.h"
#include "Os_Arch_Interrupt_Lcfg.h"
#include "Os_Platform_Lcfg.h"
#include "Os_Arch_Context_Types.h"
#include "Os_Arch_Types.h"
#include "Os_Lcfg.h"
#include "Os_Task.h"
#include "Os_Isr.h"
#include "Os_Arch_Exception.h"

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
#define OS_START_SEC_INITVAR_OSCORE0 
#include "Os_MemMap.h"
void Os_Arch_Irq_CounterIsr_SystemTimer_Core0(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_CounterIsr_SystemTimer_Core0); }
void Os_Arch_Irq_MultiCommIsr_OsCore_Core0(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_MultiCommIsr_OsCore_Core0); }
void Os_Arch_Irq_Os_Monitor_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Os_Monitor_Isr); }
void Os_Arch_Irq_GTM_ATOM10_ISRfunc(void) { Os_Arch_Cat1InterruptAsm(GTM_ATOM10_ISRfunc); }
void Os_Arch_Irq_SIUL_External_0_ISRFunc(void) { Os_Arch_Cat1InterruptAsm(SIUL_External_0_ISRFunc); }
void Os_Arch_Irq_SIUL_External_1_ISRFunc(void) { Os_Arch_Cat1InterruptAsm(SIUL_External_1_ISRFunc); }
void Os_Arch_Irq_EDMA_Ch80_IRQHandler(void) { Os_Arch_Cat1InterruptAsm(EDMA_Ch80_IRQHandler); }
#define OS_STOP_SEC_INITVAR_OSCORE0 
#include "Os_MemMap.h"

#define OS_START_SEC_INITVAR_OSCORE1 
#include "Os_MemMap.h"
void Os_Arch_Irq_CounterIsr_SystemTimer_Core1(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_CounterIsr_SystemTimer_Core1); }
void Os_Arch_Irq_MultiCommIsr_OsCore_Core1(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_MultiCommIsr_OsCore_Core1); }
void Os_Arch_Irq_GTM_ATOM40_ISRfunc(void) { Os_Arch_Cat1InterruptAsm(GTM_ATOM40_ISRfunc); }
#define OS_STOP_SEC_INITVAR_OSCORE1 
#include "Os_MemMap.h"

#define OS_START_SEC_INITVAR_OSCORE2 
#include "Os_MemMap.h"
void Os_Arch_Irq_CounterIsr_SystemTimer_Core2(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_CounterIsr_SystemTimer_Core2); }
void Os_Arch_Irq_MultiCommIsr_OsCore_Core2(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_MultiCommIsr_OsCore_Core2); }
void Os_Arch_Irq_FlashDone_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_FlashDone_Isr); }
void Os_Arch_Irq_PIT0_CH4(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_PIT0_CH4); }
void Os_Arch_Irq_PIT0_CH5(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_PIT0_CH5); }
void Os_Arch_Irq_PIT0_CH6(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_PIT0_CH6); }
void Os_Arch_Irq_Can1_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Can1_Isr); }
void Os_Arch_Irq_Can2_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Can2_Isr); }
void Os_Arch_Irq_Can3_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Can3_Isr); }
void Os_Arch_Irq_Can4_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Can4_Isr); }
void Os_Arch_Irq_Adc89_Grp0_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Adc89_Grp0_Isr); }
void Os_Arch_Irq_Adc89_Grp1_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Adc89_Grp1_Isr); }
void Os_Arch_Irq_Adc89_Grp2_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Adc89_Grp2_Isr); }
void Os_Arch_Irq_Adc89_Grp3_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Adc89_Grp3_Isr); }
void Os_Arch_Irq_Adc89_Grp4_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Adc89_Grp4_Isr); }
void Os_Arch_Irq_Adc89_Grp5_Isr(void) { Os_Arch_Cat2InterruptAsm(OsCfg_Isr_Adc89_Grp5_Isr); }
#define OS_STOP_SEC_INITVAR_OSCORE2 
#include "Os_MemMap.h"

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
*    Global Variable
********************************************************************************
*/

