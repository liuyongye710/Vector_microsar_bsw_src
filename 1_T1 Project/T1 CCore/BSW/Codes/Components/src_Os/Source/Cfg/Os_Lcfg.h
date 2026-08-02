/*
********************************************************************************
*
*  File name:	Os_Lcfg.h
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
#ifndef OS_LCFG_H_
#define OS_LCFG_H_

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
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/*
********************************************************************************
*    Global Variable
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
extern void Os_Task_Default_Init_Task_Core0(void);
extern void Os_Task_Idle_Task_Core0(void);
extern void Os_Task_Task_Init_Core0_QM(void);
extern void Os_Task_Task_10ms_Core0_QM(void);
extern void Os_Task_Task_20ms_Core0_QM(void);
extern void Os_Task_Task_50ms_Core0_QM(void);
extern void Os_Task_Task_100ms_Core0_QM(void);
extern void Os_Task_Task_200ms_Core0_QM(void);
extern void Os_Task_Task_500ms_Core0_QM(void);
extern void Os_Task_Task_1000ms_Core0_QM(void);
extern void Os_Task_Task_2ms_Core0_QM(void);
extern void Os_Task_Default_Init_Task_Core1(void);
extern void Os_Task_Idle_Task_Core1(void);
extern void Os_Task_Task_Init_Core1_QM(void);
extern void Os_Task_Task_5ms_Core1_QM(void);
extern void Os_Task_Task_10ms_Core1_QM(void);
extern void Os_Task_Task_20ms_Core1_QM(void);
extern void Os_Task_Task_50ms_Core1_QM(void);
extern void Os_Task_Task_100ms_Core1_QM(void);
extern void Os_Task_Task_200ms_Core1_QM(void);
extern void Os_Task_Task_500ms_Core1_QM(void);
extern void Os_Task_Task_1000ms_Core1_QM(void);
extern void Os_Task_Default_Init_Task_Core2(void);
extern void Os_Task_Idle_Task_Core2(void);
extern void Os_Task_Task_Init_Core2_QM(void);
extern void Os_Task_Task_1ms_Core2_QM(void);
extern void Os_Task_Task_4ms_Core2_QM(void);
extern void Os_Task_Task_5ms_Core2_QM(void);
extern void Os_Task_Task_10ms_Core2_QM(void);
extern void Os_Task_Task_20ms_Core2_QM(void);
extern void Os_Task_Task_50ms_Core2_QM(void);
extern void Os_Task_Task_100ms_Core2_QM(void);
extern void Os_Task_Task_200ms_Core2_QM(void);
extern void Os_Task_Task_500ms_Core2_QM(void);
extern void Os_Task_Task_1000ms_Core2_QM(void);
extern void GTM_ATOM10_ISRfunc(void);
extern void SIUL_External_0_ISRFunc(void);
extern void SIUL_External_1_ISRFunc(void);
extern void EDMA_Ch80_IRQHandler(void);
extern void GTM_ATOM40_ISRfunc(void);
extern void FLASH_Cmd_Done_ISR(void);
extern void PIT0_CH4_ISR(void);
extern void PIT0_CH5_ISR(void);
extern void PIT0_CH6_ISR(void);
extern void Can1_Isr_Handler(void);
extern void Can2_Isr_Handler(void);
extern void Can3_Isr_Handler(void);
extern void Can4_Isr_Handler(void);
extern void ADC89_GRP0(void);
extern void ADC89_GRP1(void);
extern void ADC89_GRP2(void);
extern void ADC89_GRP3(void);
extern void ADC89_GRP4(void);
extern void ADC89_GRP5(void);
#endif /* OS_LCFG_H_ */

