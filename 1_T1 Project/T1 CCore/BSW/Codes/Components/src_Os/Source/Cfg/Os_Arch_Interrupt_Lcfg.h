/*
********************************************************************************
*
*  File name:	Os_Arch_Interrupt_Lcfg.h
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : HanCL/2021.01.12
* Change: New create.
* Cause: New
********************************************************************************
*/
#ifndef OS_ARCH_INTERRUPT_LCFG_H_
#define OS_ARCH_INTERRUPT_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

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
extern void Os_Arch_Irq_CounterIsr_SystemTimer_Core0(void);
extern void Os_Arch_Irq_MultiCommIsr_OsCore_Core0(void);
extern void Os_Arch_Irq_Os_Monitor_Isr(void);
extern void Os_Arch_Irq_CounterIsr_SystemTimer_Core1(void);
extern void Os_Arch_Irq_MultiCommIsr_OsCore_Core1(void);
extern void Os_Arch_Irq_CounterIsr_SystemTimer_Core2(void);
extern void Os_Arch_Irq_MultiCommIsr_OsCore_Core2(void);
extern void Os_Arch_Irq_FlashDone_Isr(void);
extern void Os_Arch_Irq_PIT0_CH4(void);
extern void Os_Arch_Irq_PIT0_CH5(void);
extern void Os_Arch_Irq_PIT0_CH6(void);
extern void Os_Arch_Irq_Can1_Isr(void);
extern void Os_Arch_Irq_Can2_Isr(void);
extern void Os_Arch_Irq_Can3_Isr(void);
extern void Os_Arch_Irq_Can4_Isr(void);
extern void Os_Arch_Irq_Adc89_Grp0_Isr(void);
extern void Os_Arch_Irq_Adc89_Grp1_Isr(void);
extern void Os_Arch_Irq_Adc89_Grp2_Isr(void);
extern void Os_Arch_Irq_Adc89_Grp3_Isr(void);
extern void Os_Arch_Irq_Adc89_Grp4_Isr(void);
extern void Os_Arch_Irq_Adc89_Grp5_Isr(void);
#endif /* OS_ARCH_INTERRUPT_LCFG_H_ */


