/******************************************************************************/
/* FILE NAME: Pwm3ph.c                  							          */
/* VERSION: 1.2.4                                        						  */
/* DESCRIPTION: Three - phase six - channel PWM output drive source file      */
/* -------------------------------------------------------------------------- */
/*   C O P Y R I G H T                                                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2024 by FAW. All rights reserved.                          */
/*                                                                            */
/*   This software is copyright protected and proprietary to FAW.             */
/*   FAW grants to you only those rights as set out in the license            */
/*   conditions.                                                              */
/*   All other rights remain with FAW.                                        */
/*                                                                            */
/*   REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE COPYRIGHT AGREEMENT.     */
/*============================================================================*/
/* HISTORY           	ORIGINAL AUTHOR: lyy                                  */
/* REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                      */
/* ---   -----------  ---------    ---------------------                      */
/* 1.0.0    lyy   24/06/01    Initial version of function.                    */
/* 1.0.1    lyy   24/08/08	  Adding function for dirceting set SR0/SR1 value */
/* 1.0.2    lyy   24/10/30    Change down bridge default level to low.        */
/* 1.0.3    lyy   24/11/01    Porting ASC, FreeWheeling(SPO) function.        */
/* 1.1.0    lyy   24/12/25    Support switching between CCFC3007 and TC397 chi*/
/*	                          -p platforms,add period rising edges trigger in-*/
/*                            -errupt.
 * 1.1.1	lyy   25/03/18    1.fix SPO function logic
 * 							  2.Add dead time calculation function
 * 							  3.fix Carrier Limited logic
 * 1.1.2	lyy   25/03/21    Solve the problem that the lower bridge(UL/VL/WL)
 * 							  closes one cycle late in the SPO state	  	  
 * 1.1.3    lyy   25/04/03    'CAL_PWM_Set_DeadTime_us_f32' local in CAL section,
 							   Dead time limited to 2us to 100us				
/* 1.2.0	lyy	  25/04/18    Big changes! Refactor the lower level code to sup-
							  -port driving dual motors(Only on CCFC3007 handware)
   1.2.1    lyy   25/04/30    fix dutycycle Part3->Part5 changed bug, fix bug in
   	   	   	   	   	   	   	  V1.1.2 in different method				      */
/* 1.2.2    lyy   25/05/07    fix dytycyle changed bug , patch1 patch2 patch3
 * 							  code is tested 								  */
/* 1.2.3    lyy   25/05/30    add atom initial code
 * 1.2.4    lyy   25/10/16    Add the feature that CDD initialization does not
 * 							  require MCAL configuration(M1/M2)			      */
/******************************************************************************/


/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Pwm3ph.h"
#include "Pwm3ph_Cfg.h"
#include "VX1000If.h"
#include "T1_AppInterface.h"

#if defined(CHIP_PLATFORM_TC397)
	#include "Pwm_17_GtmCcu6.h"
	#include "IfxGtm_regdef.h"
	#include "IfxGtm_reg.h"
#elif defined(CHIP_PLATFORM_CCFC3007PT)
	#include "CCFC3007PT.h"
	#include "Pwm_LLDriver.h"
#endif
/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/
#define U16_REGISTER_OFFSET_VALUE    2U			/* register offset */
#include"IoHwAb.h"
#define NONE 		  0
#define RISINGE_EDGES 1
#define FALLING_EDGES 2
#define BOTH_EDGES 	  3
/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/
typedef struct {
	uint8  VAR_Motor_u8;
	uint8  VAR_Pwm_Mode_u8;					/* PWM Mode */
	uint16 VAR_Pwm_Freq_u16;					/* PWM Fre */
	float32 VAR_Pwm_DeadTime_In_f32;			/* PWM DeadTime(uS)*/
	float32 VAR_PwmDutyCyclePhaseU_f32;
	float32 VAR_PwmDutyCyclePhaseV_f32;
	float32 VAR_PwmDutyCyclePhaseW_f32;

	float32 VAR_PwmDutyCyclePhaseU_f32_Last;
	float32 VAR_PwmDutyCyclePhaseV_f32_Last;
	float32 VAR_PwmDutyCyclePhaseW_f32_Last;
}DataConversionInType;

typedef struct{
	uint16 ui16_Pwm_Ticks_OnEdge_UH;
	uint16 ui16_Pwm_Ticks_OffEdge_UH;
	uint16 ui16_Pwm_Ticks_OnEdge_UL;
	uint16 ui16_Pwm_Ticks_OffEdge_UL;

	uint16 ui16_Pwm_Ticks_OnEdge_VH;
	uint16 ui16_Pwm_Ticks_OffEdge_VH;
	uint16 ui16_Pwm_Ticks_OnEdge_VL;
	uint16 ui16_Pwm_Ticks_OffEdge_VL;

	uint16 ui16_Pwm_Ticks_OnEdge_WH;
	uint16 ui16_Pwm_Ticks_OffEdge_WH;
	uint16 ui16_Pwm_Ticks_OnEdge_WL;
	uint16 ui16_Pwm_Ticks_OffEdge_WL;
}DataConversionOutType;

typedef struct{
	uint8 ui8_Pwm_Mode_Last;				/* last PWM Mode */
	uint16 VAR_Pwm_Fault_Flag_u16;		/* Input parameter error flag */
	uint16 ui16_Pwm_Period_Tick_Last;
	uint16 ui16_Pwm_Deadtime_Tick_Last;

	float32 VAR_PwmDutyCyclePhaseU_f32_Last; /* Add */
	float32 VAR_PwmDutyCyclePhaseV_f32_Last;
	float32 VAR_PwmDutyCyclePhaseW_f32_Last;
}PwmStatusFlagType;

typedef struct{
	uint16 ui16_Pwm_Period_SR0;		 /* PWM period TICK */

	uint16 ui16_Pwm_OnEdge_UH_SR1;	 /* U_H_ON(rising edge),SR1 */
	uint16 ui16_Pwm_OffEdge_UH_SR0;	 /* U_H_OFF(falling edge),SR0 */
	uint16 ui16_Pwm_OffEdge_UL_SR0;	 /* U_L_OFF(falling edge),SR0 */
	uint16 ui16_Pwm_OnEdge_UL_SR1;	 /* U_L_ON(rising edge),SR1 */

	uint16 ui16_Pwm_OnEdge_VH_SR1;
	uint16 ui16_Pwm_OffEdge_VH_SR0;
	uint16 ui16_Pwm_OffEdge_VL_SR0;
	uint16 ui16_Pwm_OnEdge_VL_SR1;

	uint16 ui16_Pwm_OnEdge_WH_SR1;
	uint16 ui16_Pwm_OffEdge_WH_SR0;
	uint16 ui16_Pwm_OffEdge_WL_SR0;
	uint16 ui16_Pwm_OnEdge_WL_SR1;
}PwmRegisterValueType;

/*******************************************************************************
**                   Static Local Variables Definition              		  **
*******************************************************************************/
#define FAW_CORE0_DMEM0_VALUE_START
#include "FAW_MemMap.h"

static DataConversionInType M1_DataConversionIn;
static DataConversionOutType M1_DataConversionOut;
static PwmRegisterValueType M1_PwmRegisterValue;
static PwmStatusFlagType M1_PwmStatusFlagType;

#define FAW_CORE0_DMEM0_VALUE_STOP
#include "FAW_MemMap.h"

static DataConversionInType M2_DataConversionIn;
static DataConversionOutType M2_DataConversionOut;
static PwmRegisterValueType M2_PwmRegisterValue;
static PwmStatusFlagType M2_PwmStatusFlagType;
// uint16 ui16_Pwm_Period_Tick; 	 			/* PWM Reference period count */
// static uint16 ui16_DeadTime_Tick;	    /* Dead zone time count value */
// static uint16 ui16_Pwm_DutyU_Tick;			/* U PWM Duty cycle value */
// static uint16 ui16_Pwm_DutyV_Tick;			/* V PWM Duty cycle value */
// static uint16 ui16_Pwm_DutyW_Tick;			/* W PWM Duty cycle value */
/*******************************************************************************
**                     Calibration Variables Definition                       **
*******************************************************************************/
#define XCP_START_SEC_CONST_CORE0_BLOCK0
#include "FAW_MemMap.h"
const volatile float32 CAL_PWM_Set_DeadTime_us_f32 =	 3.4F;	/* Default dead zone time ,2.6Us */
/*
 *	0.94 <  x_Duty <= 0.999
 *	0.06 =< x_Duty <= 0.94
 *	0.001<  x_Duty <  0.06
 * */
const volatile float32 CAL_Pwm3phB_ClosedThreshold_f32 	=	 0.94F;
const volatile float32 CAL_Pwm3phT_ClosedThreshold_f32 	=	 0.06F;
const volatile float32 CAL_Pwm3ph_DutyMax_f32 			=	 0.999F;
const volatile float32 CAL_Pwm3ph_DutyMin_f32 			=	 0.001F;
const volatile uint16 CAL_Pwm3ph_AdcTriggleOffset_u16 	=	 100U;

#define XCP_STOP_SEC_CONST_CORE0_BLOCK0
#include "FAW_MemMap.h"
/*******************************************************************************
**                     Global Variables Definition              		      **
*******************************************************************************/

uint8 VAR_PWM3phUDuty_ERR_u8;
uint8 VAR_PWM3phVDuty_ERR_u8;
uint8 VAR_PWM3phWDuty_ERR_u8;
/*******************************************************************************
**                  Static Local Function Declaration            		      **
*******************************************************************************/
#if defined(CHIP_PLATFORM_TC397)
static void Pwm3ph_Set_ShadowValSr0(uint8 Moudle,uint8 Channel,uint32 Sr0Value);
static void Pwm3ph_Set_ShadowValSr1(uint8 Moudle,uint8 Channel,uint32 Sr1Value);
#endif 
#if defined(CHIP_PLATFORM_CCFC3007PT)
	static void Pwm3ph_EnablePeriodChIsr(uint8 mode,uint8 Module,uint8 channel);
#endif
static void Pwm3ph_Output_Normal(PwmStatusFlagType* PwmStaFlag, DataConversionOutType* DataConvVar,PwmRegisterValueType* PwmRegVar);	/* Normal mode */
static void Pwm3ph_Output_UpOff_DownOn(PwmStatusFlagType* PwmStaFlag,PwmRegisterValueType* PwmRegVar);	/* ASC */
static void Pwm3ph_Output_UpOff_DownOff(PwmStatusFlagType* PwmStaFlag,PwmRegisterValueType* PwmRegVar);	/* Freewheeling */
static void Pwm3ph_ChangePeriod(uint16 ui16_Period,DataConversionInType* in,PwmRegisterValueType* PwmRegVar);
static void Pwm3ph_GetDataConversion(DataConversionInType* in , DataConversionOutType* out, PwmRegisterValueType* PwmRegVar,PwmStatusFlagType* PwmStaFlag);
/*******************************************************************************
**                 		  Function Source Code            		              **
*******************************************************************************/

/*******************************************************************************
** Function Name	: AB_GTM_ATOM10_ISRfunc
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note
** Description	  	: service handler
*******************************************************************************/
#if defined(CHIP_PLATFORM_CCFC3007PT)
	extern void AB_GTM_ATOM10_ISRfunc(void);
	void GTM_ATOM10_ISRfunc(void)
	{
		T1_TraceEvent(T1_START,T1_CAT1_GTM_ATOM10_ISRfunc_ID);
		AB_GTM_ATOM10_ISRfunc();
		(&GTM_ATOM_1)->CH0_IRQ_NOTIFY.B.CCU0TC = 0;
		(&GTM_ATOM_1)->CH0_IRQ_NOTIFY.B.CCU1TC = 0;
//		Pwm_Atom_isr_handle(1,0,1);
#if(VX1000If_IsVX1000DriverAccessEnabled==true)
	    VX1000If_Event(0x1);
#endif
		T1_TraceEvent(T1_STOP,T1_CAT1_GTM_ATOM10_ISRfunc_ID);
	}

	extern void AB_GTM_ATOM40_ISRfunc(void);
	void GTM_ATOM40_ISRfunc(void)
	{
//		T1_TraceEvent(T1_START,T1_CAT1_GTM_ATOM40_ISRfunc_ID);
		AB_GTM_ATOM40_ISRfunc();
		(&GTM_ATOM_4)->CH0_IRQ_NOTIFY.B.CCU0TC = 0;
		(&GTM_ATOM_4)->CH0_IRQ_NOTIFY.B.CCU1TC = 0;
//		Pwm_Atom_isr_handle(4,0,1);
//		T1_TraceEvent(T1_STOP,T1_CAT1_GTM_ATOM40_ISRfunc_ID);
	}
#endif


/*******************************************************************************
** Function Name	: Pwm3ph_Init
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: CddPwm initial function
** Description	  	: initialize
*******************************************************************************/
void M1_Pwm_3Phases_Init()
{
	Pwm3phInIFType pwm3phInIF_Ptr;
	Pwm3phOutIFType pwm3phOutIF_Ptr;
	pwm3phInIF_Ptr.PwmDutyCyclePhaseU1_f32 = 0.0f;
	pwm3phInIF_Ptr.PwmDutyCyclePhaseV1_f32 =  0.0f;
	pwm3phInIF_Ptr.PwmDutyCyclePhaseW1_f32 =  0.0f;
	pwm3phInIF_Ptr.Pwm_Freq_u16 =  U16_PWM_DEF_FREQ_VALUE;
	pwm3phInIF_Ptr.Pwm_Mode_u8 =  0;

#if defined(CHIP_PLATFORM_TC397)
	/*total Cfg*/
	GTM_ATOM0_AGC_GLB_CTRL.U=0xAAAA0000;//ok0-6

	GTM_ATOM0_AGC_ENDIS_CTRL.U=0x0000AAAA;//ok0-6
	GTM_ATOM0_AGC_OUTEN_CTRL.U=0x0000AAAA;//ok0-6
	GTM_ATOM0_AGC_FUPD_CTRL.U=0x3FFF3FFF;//ok0-6

    /*Period*/
    GTM_ATOM0_CH0_CTRL.B.RST_CCU0=0;
    GTM_ATOM0_CH0_CTRL.B.TRIGOUT=1;
    /*WL*/
    GTM_ATOM0_CH1_CTRL.B.RST_CCU0=1;
    GTM_ATOM0_CH1_CTRL.B.SL=0;
    /*WH*/
	GTM_ATOM0_CH2_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH2_CTRL.B.SL=0;
	/*VL*/
	GTM_ATOM0_CH3_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH3_CTRL.B.SL=0;
	/*VH*/
	GTM_ATOM0_CH4_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH4_CTRL.B.SL=0;
	/*UL*/
	GTM_ATOM0_CH5_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH5_CTRL.B.SL=0;
	/*UH*/
	GTM_ATOM0_CH6_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH6_CTRL.B.SL=0;
	/*ADC Trigger*/
	GTM_ATOM0_CH7_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH7_CTRL.B.SL=0;

#if(PERIOD_CHANNEL_100US_ISR == 1)
	Pwm_17_GtmCcu6_EnableNotification(7,PWM_17_GTMCCU6_RISING_EDGE);
#endif

#elif defined(CHIP_PLATFORM_CCFC3007PT)
	

	/*total Cfg*/
	(&GTM_ATOM_1)->AGC_GLB_CTRL.R=0xAAAA0000;
	(&GTM_ATOM_1)->AGC_ENDIS_CTRL.R=0x0000AAAA;
	(&GTM_ATOM_1)->AGC_OUTEN_CTRL.R=0x0000AAAA;
	(&GTM_ATOM_1)->AGC_FUPD_CTRL.R=0x3FFF3FFF;
	(&GTM_ATOM_1)->AGC_ENDIS_STAT.R=0x0000AAAA;
	(&GTM_ATOM_1)->AGC_OUTEN_STAT.R=0x0000AAAA;
	/*ATOM1_0,Period&trigger ADC*/
	(&GTM_ATOM_1)->CH0_CTRL.R = 0x01000002;
	/*ATOM1_1,UH*/
	(&GTM_ATOM_1)->CH1_CTRL.B.RST_CCU0=1;
	(&GTM_ATOM_1)->CH1_CTRL.B.MODE=0x02;
	(&GTM_ATOM_1)->CH1_CTRL.B.SL=0;
	/*ATOM1_2,UL*/
	(&GTM_ATOM_1)->CH2_CTRL.B.RST_CCU0=1;
	(&GTM_ATOM_1)->CH2_CTRL.B.MODE=0x02;
	(&GTM_ATOM_1)->CH2_CTRL.B.SL=0;

	 /*ATOM1_3,VH*/
	 (&GTM_ATOM_1)->CH3_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_1)->CH3_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_1)->CH3_CTRL.B.SL=0;
	 /*ATOM1_4,VL*/
	 (&GTM_ATOM_1)->CH4_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_1)->CH4_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_1)->CH4_CTRL.B.SL=0;

	 /*ATOM1_5,VH*/
	 (&GTM_ATOM_1)->CH5_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_1)->CH5_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_1)->CH5_CTRL.B.SL=0;
	 /*ATOM1_6,VL*/
	 (&GTM_ATOM_1)->CH6_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_1)->CH6_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_1)->CH6_CTRL.B.SL=0;

	#if(PERIOD_CHANNEL_100US_ISR == 1)
		 Pwm3ph_EnablePeriodChIsr(FALLING_EDGES,UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF);
	#endif

#endif

	#if ( _CDD_SIMULATION == 0 )
		 M1_Pwm3ph_SetOutput(&pwm3phInIF_Ptr);
	#else
		 Pwm3ph_SetOutput(&pwm3phInIF_Ptr,&pwm3phOutIF_Ptr);
	#endif

}

void M2_Pwm_3Phases_Init()
{
	Pwm3phInIFType pwm3phInIF_Ptr;
	Pwm3phOutIFType pwm3phOutIF_Ptr;
	pwm3phInIF_Ptr.PwmDutyCyclePhaseU1_f32 = 0.0f;
	pwm3phInIF_Ptr.PwmDutyCyclePhaseV1_f32 =  0.0f;
	pwm3phInIF_Ptr.PwmDutyCyclePhaseW1_f32 =  0.0f;
	pwm3phInIF_Ptr.Pwm_Freq_u16 =  U16_PWM_DEF_FREQ_VALUE;
	pwm3phInIF_Ptr.Pwm_Mode_u8 =  0;

#if defined(CHIP_PLATFORM_TC397)
	/*total Cfg*/
	GTM_ATOM0_AGC_GLB_CTRL.U=0xAAAA0000;//ok0-6

	GTM_ATOM0_AGC_ENDIS_CTRL.U=0x0000AAAA;//ok0-6
	GTM_ATOM0_AGC_OUTEN_CTRL.U=0x0000AAAA;//ok0-6
	GTM_ATOM0_AGC_FUPD_CTRL.U=0x3FFF3FFF;//ok0-6

    /*Period*/
    GTM_ATOM0_CH0_CTRL.B.RST_CCU0=0;
    GTM_ATOM0_CH0_CTRL.B.TRIGOUT=1;
    /*WL*/
    GTM_ATOM0_CH1_CTRL.B.RST_CCU0=1;
    GTM_ATOM0_CH1_CTRL.B.SL=0;
    /*WH*/
	GTM_ATOM0_CH2_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH2_CTRL.B.SL=0;
	/*VL*/
	GTM_ATOM0_CH3_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH3_CTRL.B.SL=0;
	/*VH*/
	GTM_ATOM0_CH4_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH4_CTRL.B.SL=0;
	/*UL*/
	GTM_ATOM0_CH5_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH5_CTRL.B.SL=0;
	/*UH*/
	GTM_ATOM0_CH6_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH6_CTRL.B.SL=0;
	/*ADC Trigger*/
	GTM_ATOM0_CH7_CTRL.B.RST_CCU0=1;
	GTM_ATOM0_CH7_CTRL.B.SL=0;

#if(PERIOD_CHANNEL_100US_ISR == 1)
	Pwm_17_GtmCcu6_EnableNotification(7,PWM_17_GTMCCU6_RISING_EDGE);
#endif

#elif defined(CHIP_PLATFORM_CCFC3007PT)
	

	/*total Cfg*/
	(&GTM_ATOM_4)->AGC_GLB_CTRL.R=0xAAAA0000;
	(&GTM_ATOM_4)->AGC_ENDIS_CTRL.R=0x0000AAAA;
	(&GTM_ATOM_4)->AGC_OUTEN_CTRL.R=0x0000AAAA;
	(&GTM_ATOM_4)->AGC_FUPD_CTRL.R=0x3FFF3FFF;
	(&GTM_ATOM_4)->AGC_ENDIS_STAT.R=0x0000AAAA;
	(&GTM_ATOM_4)->AGC_OUTEN_STAT.R=0x0000AAAA;
	/*ATOM1_0,Period&trigger ADC*/
	(&GTM_ATOM_4)->CH0_CTRL.R = 0x01000002;
	/*ATOM1_1,UH*/
	(&GTM_ATOM_4)->CH1_CTRL.B.RST_CCU0=1;
	(&GTM_ATOM_4)->CH1_CTRL.B.MODE=0x02;
	(&GTM_ATOM_4)->CH1_CTRL.B.SL=0;
	/*ATOM1_2,UL*/
	(&GTM_ATOM_4)->CH2_CTRL.B.RST_CCU0=1;
	(&GTM_ATOM_4)->CH2_CTRL.B.MODE=0x02;
	(&GTM_ATOM_4)->CH2_CTRL.B.SL=0;

	 /*ATOM1_3,VH*/
	 (&GTM_ATOM_4)->CH3_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_4)->CH3_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_4)->CH3_CTRL.B.SL=0;
	 /*ATOM1_4,VL*/
	 (&GTM_ATOM_4)->CH4_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_4)->CH4_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_4)->CH4_CTRL.B.SL=0;

	 /*ATOM1_5,VH*/
	 (&GTM_ATOM_4)->CH5_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_4)->CH5_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_4)->CH5_CTRL.B.SL=0;
	 /*ATOM1_6,VL*/
	 (&GTM_ATOM_4)->CH6_CTRL.B.RST_CCU0=1;
	 (&GTM_ATOM_4)->CH6_CTRL.B.MODE=0x02;
	 (&GTM_ATOM_4)->CH6_CTRL.B.SL=0;

	#if(PERIOD_CHANNEL_100US_ISR == 1)
		 Pwm3ph_EnablePeriodChIsr(FALLING_EDGES,UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF_M2);
	#endif

#endif

	#if ( _CDD_SIMULATION == 0 )
		 M2_Pwm3ph_SetOutput(&pwm3phInIF_Ptr);
	#else
		 Pwm3ph_SetOutput(&pwm3phInIF_Ptr,&pwm3phOutIF_Ptr);
	#endif

}
/*******************************************************************************
** Function Name	: Pwm3ph_EnablePeriodChIsr
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	:
** Description	  	: Pwm3ph_EnablePeriodChIsr
*******************************************************************************/
#if defined(CHIP_PLATFORM_CCFC3007PT)
	void Pwm3ph_EnablePeriodChIsr(uint8 mode,uint8 Module,uint8 channel)
	{

	#if(TEST_USE_MCAL == 1U )
		(void)INTC_LLD_Set_IRQ_Handle((IntrId)INTR_ID_841, &GTM_ATOM10_ISRfunc);
		(void)INTC_LLD_Set_IRQ_Priority((IntrId)INTR_ID_841, ATOM10_Prio);
		(void)INTC_LLD_Set_IRQ_Enable((IntrId)INTR_ID_841);
	#endif 
		if (mode == BOTH_EDGES)
		{
			(void)GTM_ATOM_LLD_Channel_IsEnableInterrupt \
			( \
				Module, \
				channel, \
				ATOM_IRQ_CCU0TC, \
				GPT_GTM_Enable \
			);
			(void)GTM_ATOM_LLD_Channel_IsEnableInterrupt \
			( \
				Module, \
				channel, \
				ATOM_IRQ_CCU1TC, \
				GPT_GTM_Enable \
			);
		}
		else if(mode == FALLING_EDGES)
		{
			(void)GTM_ATOM_LLD_Channel_IsEnableInterrupt \
			( \
				Module, \
				channel, \
				ATOM_IRQ_CCU0TC, \
				GPT_GTM_Enable \
			);
			(void)GTM_ATOM_LLD_Channel_IsEnableInterrupt \
			( \
				Module, \
				channel, \
				ATOM_IRQ_CCU1TC, \
				GPT_GTM_Disable \
			);
		}
		else if(mode == RISINGE_EDGES)
		{
			(void)GTM_ATOM_LLD_Channel_IsEnableInterrupt \
			( \
				Module, \
				channel, \
				ATOM_IRQ_CCU0TC, \
				GPT_GTM_Disable \
			);
			(void)GTM_ATOM_LLD_Channel_IsEnableInterrupt \
			( \
				Module, \
				channel, \
				ATOM_IRQ_CCU1TC, \
				GPT_GTM_Enable \
			);
		}
		else
		{
			/* Do nothing */
		}
	}
#endif


/*******************************************************************************
** Function Name	: Pwm3ph_SetOutput
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	:
**
** Description	  	:
*******************************************************************************/
#define FAW_CORE0_IMEM0_CODE_START
#include "FAW_MemMap.h"

#if ( _CDD_SIMULATION == 0 )
void M1_Pwm3ph_SetOutput(const Pwm3phInIFType* in)
#else
void Pwm3ph_SetOutput(const Pwm3phInIFType* in, Pwm3phOutIFType* out )
#endif
{
	M1_DataConversionIn.VAR_Motor_u8 = 1;
	M1_DataConversionIn.VAR_Pwm_Freq_u16 = in->Pwm_Freq_u16;
	M1_DataConversionIn.VAR_Pwm_Mode_u8 = in->Pwm_Mode_u8;
	M1_DataConversionIn.VAR_PwmDutyCyclePhaseU_f32 = in->PwmDutyCyclePhaseU1_f32;
	M1_DataConversionIn.VAR_PwmDutyCyclePhaseV_f32 = in->PwmDutyCyclePhaseV1_f32;
	M1_DataConversionIn.VAR_PwmDutyCyclePhaseW_f32 = in->PwmDutyCyclePhaseW1_f32;

	Pwm3ph_GetDataConversion(&M1_DataConversionIn,&M1_DataConversionOut,&M1_PwmRegisterValue,&M1_PwmStatusFlagType);// PwmDutyCyclePhase(X)_f32鏉烆剟鏁撻弬銈嗗闁跨喐鏋�?�幏锟� ui16_Pwm_Ticks_(On/Off)Edge_(WH/WL)

	

	switch(M1_DataConversionIn.VAR_Pwm_Mode_u8)
	{
		case UI8_MODE_UP_OFF_DOWN_OFF:/* 0 SPO */
		{
			Pwm3ph_Output_UpOff_DownOff(&M1_PwmStatusFlagType,&M1_PwmRegisterValue);

			M1_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_UP_OFF_DOWN_OFF;
			break;
		}
		case UI8_MODE_NORMAL:/* 3 Normal */
		{
			if(M1_PwmStatusFlagType.ui8_Pwm_Mode_Last == UI8_MODE_UP_OFF_DOWN_ON)
			{
			

			}
			Pwm3ph_Output_Normal(&M1_PwmStatusFlagType,&M1_DataConversionOut,&M1_PwmRegisterValue);

			M1_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_NORMAL;
			break;
		}
		case UI8_MODE_UP_OFF_DOWN_ON:/* 1 ASC*/
		{
			
			Pwm3ph_Output_UpOff_DownOn(&M1_PwmStatusFlagType,&M1_PwmRegisterValue);

			M1_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_UP_OFF_DOWN_ON;
			break;
		}

		default:
		{
			Pwm3ph_Output_UpOff_DownOff(&M1_PwmStatusFlagType,&M1_PwmRegisterValue);

			M1_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_UP_OFF_DOWN_OFF;
			break;
		}

	}
	M1_PwmStatusFlagType.VAR_PwmDutyCyclePhaseU_f32_Last =  M1_DataConversionIn.VAR_PwmDutyCyclePhaseU_f32;
	M1_PwmStatusFlagType.VAR_PwmDutyCyclePhaseV_f32_Last =  M1_DataConversionIn.VAR_PwmDutyCyclePhaseV_f32;
	M1_PwmStatusFlagType.VAR_PwmDutyCyclePhaseW_f32_Last =  M1_DataConversionIn.VAR_PwmDutyCyclePhaseW_f32;

	M1_DataConversionIn.VAR_PwmDutyCyclePhaseU_f32_Last = M1_DataConversionIn.VAR_PwmDutyCyclePhaseU_f32;
	M1_DataConversionIn.VAR_PwmDutyCyclePhaseV_f32_Last = M1_DataConversionIn.VAR_PwmDutyCyclePhaseV_f32;
	M1_DataConversionIn.VAR_PwmDutyCyclePhaseW_f32_Last = M1_DataConversionIn.VAR_PwmDutyCyclePhaseW_f32;

#if defined(CHIP_PLATFORM_TC397)
	/*W*/
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WL,ui16_Pwm_OffEdge_WL_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WL,ui16_Pwm_OnEdge_WL_SR1);
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WH,ui16_Pwm_OffEdge_WH_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WH,ui16_Pwm_OnEdge_WH_SR1);
	/*V*/
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VL,ui16_Pwm_OffEdge_VL_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VL,ui16_Pwm_OnEdge_VL_SR1);
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VH,ui16_Pwm_OffEdge_VH_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VH,ui16_Pwm_OnEdge_VH_SR1);
    /*U*/
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UL,ui16_Pwm_OffEdge_UL_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UL,ui16_Pwm_OnEdge_UL_SR1);
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UH,ui16_Pwm_OffEdge_UH_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UH,ui16_Pwm_OnEdge_UH_SR1);
#elif defined(CHIP_PLATFORM_CCFC3007PT)
	/*W*/
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_WL,\
		M1_PwmRegisterValue.ui16_Pwm_OffEdge_WL_SR0,M1_PwmRegisterValue.ui16_Pwm_OnEdge_WL_SR1);
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_WH,\
		M1_PwmRegisterValue.ui16_Pwm_OffEdge_WH_SR0,M1_PwmRegisterValue.ui16_Pwm_OnEdge_WH_SR1);								
	/*V*/
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_VL,\
		M1_PwmRegisterValue.ui16_Pwm_OffEdge_VL_SR0,M1_PwmRegisterValue.ui16_Pwm_OnEdge_VL_SR1);
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_VH,\
		M1_PwmRegisterValue.ui16_Pwm_OffEdge_VH_SR0,M1_PwmRegisterValue.ui16_Pwm_OnEdge_VH_SR1);	
    /*U*/
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_UL,\
		M1_PwmRegisterValue.ui16_Pwm_OffEdge_UL_SR0,M1_PwmRegisterValue.ui16_Pwm_OnEdge_UL_SR1);
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,UI8_PWM_ATOM_CHANNEL_SEL_UH,\
		M1_PwmRegisterValue.ui16_Pwm_OffEdge_UH_SR0,M1_PwmRegisterValue.ui16_Pwm_OnEdge_UH_SR1);	
#endif

#if ( _CDD_SIMULATION == 1 )
    out->Pwm_Ticks_OnEdge_WH_ui16 = ui16_Pwm_OnEdge_WH_SR1;
	out->Pwm_Ticks_OffEdge_WH_ui16 = ui16_Pwm_OffEdge_WH_SR0;
	out->Pwm_Ticks_OnEdge_WL_ui16 = ui16_Pwm_OnEdge_WL_SR1;
	out->Pwm_Ticks_OffEdge_WL_ui16 = ui16_Pwm_OffEdge_WL_SR0;

	out->Pwm_Ticks_OnEdge_VH_ui16 = ui16_Pwm_OnEdge_VH_SR1;
	out->Pwm_Ticks_OffEdge_VH_ui16 = ui16_Pwm_OffEdge_VH_SR0;
	out->Pwm_Ticks_OnEdge_VL_ui16 = ui16_Pwm_OnEdge_VL_SR1;
	out->Pwm_Ticks_OffEdge_VL_ui16 = ui16_Pwm_OffEdge_VL_SR0;

	out->Pwm_Ticks_OnEdge_UH_ui16 = ui16_Pwm_OnEdge_UH_SR1;
	out->Pwm_Ticks_OffEdge_UH_ui16 = ui16_Pwm_OffEdge_UH_SR0;
	out->Pwm_Ticks_OnEdge_UL_ui16 = ui16_Pwm_OnEdge_UL_SR1;
	out->Pwm_Ticks_OffEdge_UL_ui16 = ui16_Pwm_OffEdge_UL_SR0;
#endif 
}

#define FAW_CORE0_IMEM0_CODE_STOP
#include "FAW_MemMap.h"
/*******************************************************************************
** Function Name	: M2_Pwm3ph_SetOutput
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	:
**
** Description	  	:
*******************************************************************************/
#if ( _CDD_SIMULATION == 0 )
void M2_Pwm3ph_SetOutput(const Pwm3phInIFType* in)
#else
void Pwm3ph_SetOutput(const Pwm3phInIFType* in, Pwm3phOutIFType* out )
#endif
{
	M2_DataConversionIn.VAR_Motor_u8 = 2;
	M2_DataConversionIn.VAR_Pwm_Freq_u16 = in->Pwm_Freq_u16;
	M2_DataConversionIn.VAR_Pwm_Mode_u8 = in->Pwm_Mode_u8;
	M2_DataConversionIn.VAR_PwmDutyCyclePhaseU_f32 = in->PwmDutyCyclePhaseU1_f32;
	M2_DataConversionIn.VAR_PwmDutyCyclePhaseV_f32 = in->PwmDutyCyclePhaseV1_f32;
	M2_DataConversionIn.VAR_PwmDutyCyclePhaseW_f32 = in->PwmDutyCyclePhaseW1_f32;

	Pwm3ph_GetDataConversion(&M2_DataConversionIn,&M2_DataConversionOut,&M2_PwmRegisterValue,&M2_PwmStatusFlagType);// PwmDutyCyclePhase(X)_f32鏉烆剟鏁撻弬銈嗗闁跨喐鏋�?�幏锟� ui16_Pwm_Ticks_(On/Off)Edge_(WH/WL)

	switch(M2_DataConversionIn.VAR_Pwm_Mode_u8)
	{
		case UI8_MODE_UP_OFF_DOWN_OFF:
		{
			Pwm3ph_Output_UpOff_DownOff(&M2_PwmStatusFlagType,&M2_PwmRegisterValue);

			M2_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_UP_OFF_DOWN_OFF;
			break;
		}
		case UI8_MODE_NORMAL:
		{
			Pwm3ph_Output_Normal(&M2_PwmStatusFlagType,&M2_DataConversionOut,&M2_PwmRegisterValue);

			M2_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_NORMAL;
			break;
		}
		case UI8_MODE_UP_OFF_DOWN_ON:
		{
			Pwm3ph_Output_UpOff_DownOn(&M2_PwmStatusFlagType,&M2_PwmRegisterValue);

			M2_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_UP_OFF_DOWN_ON;
			break;
		}

		default:
		{
			Pwm3ph_Output_UpOff_DownOff(&M2_PwmStatusFlagType,&M2_PwmRegisterValue);

			M2_PwmStatusFlagType.ui8_Pwm_Mode_Last=UI8_MODE_UP_OFF_DOWN_OFF;
			break;
		}

	}

#if defined(CHIP_PLATFORM_TC397)
	/*W*/
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WL,ui16_Pwm_OffEdge_WL_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WL,ui16_Pwm_OnEdge_WL_SR1);
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WH,ui16_Pwm_OffEdge_WH_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_WH,ui16_Pwm_OnEdge_WH_SR1);
	/*V*/
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VL,ui16_Pwm_OffEdge_VL_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VL,ui16_Pwm_OnEdge_VL_SR1);
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VH,ui16_Pwm_OffEdge_VH_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_VH,ui16_Pwm_OnEdge_VH_SR1);
    /*U*/
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UL,ui16_Pwm_OffEdge_UL_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UL,ui16_Pwm_OnEdge_UL_SR1);
	Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UH,ui16_Pwm_OffEdge_UH_SR0);
	Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_UH,ui16_Pwm_OnEdge_UH_SR1);
#elif defined(CHIP_PLATFORM_CCFC3007PT)
	/*W*/
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_WL_M2,\
		M2_PwmRegisterValue.ui16_Pwm_OffEdge_WL_SR0,M2_PwmRegisterValue.ui16_Pwm_OnEdge_WL_SR1);
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_WH_M2,\
		M2_PwmRegisterValue.ui16_Pwm_OffEdge_WH_SR0,M2_PwmRegisterValue.ui16_Pwm_OnEdge_WH_SR1);								
	/*V*/
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_VL_M2,\
		M2_PwmRegisterValue.ui16_Pwm_OffEdge_VL_SR0,M2_PwmRegisterValue.ui16_Pwm_OnEdge_VL_SR1);
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_VH_M2,\
		M2_PwmRegisterValue.ui16_Pwm_OffEdge_VH_SR0,M2_PwmRegisterValue.ui16_Pwm_OnEdge_VH_SR1);	
    /*U*/
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_UL_M2,\
		M2_PwmRegisterValue.ui16_Pwm_OffEdge_UL_SR0,M2_PwmRegisterValue.ui16_Pwm_OnEdge_UL_SR1);
	GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,UI8_PWM_ATOM_CHANNEL_SEL_UH_M2,\
		M2_PwmRegisterValue.ui16_Pwm_OffEdge_UH_SR0,M2_PwmRegisterValue.ui16_Pwm_OnEdge_UH_SR1);	
#endif

}
#if defined(CHIP_PLATFORM_TC397)
/*******************************************************************************
** Function Name	: Pwm3ph_Set_ShadowValSr0
** Parameter[in] 	: uint8 Moudle,uint8 Channel,uint32 Sr0Value
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	闁跨喐鏋婚幏绋畂ne
** Description	  	: Set_ShadowValSr0
*******************************************************************************/

static void Pwm3ph_Set_ShadowValSr0(uint8 Moudle,uint8 Channel,uint32 Sr0Value)
{
#if (_CDD_SIMULATION == STD_OFF)
	#if (PWM3PH_TOM_ATOM_SEL == 0U)
	Gtm_SetTomShadowValSr0(Moudle,Channel,(uint16)Sr0Value);
	#elif (PWM3PH_TOM_ATOM_SEL == 1U)
	Ifx_GTM_ATOM_CH *atomch=(Ifx_GTM_ATOM_CH *)\
							(((uint32)&(MODULE_GTM.ATOM[Moudle].CH0.RDADDR.U))\
							+0x80*Channel);
	atomch->SR0.U=Sr0Value;
	#endif
#endif
}

/*******************************************************************************
** Function Name	: Pwm3ph_Set_ShadowValSr1
** Parameter[in] 	: uint8 Moudle,uint8 Channel,uint32 Sr1Value
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	闁跨喐鏋婚幏绋畂ne
** Description	  	: Set_ShadowValSr1
*******************************************************************************/

static void Pwm3ph_Set_ShadowValSr1(uint8 Moudle,uint8 Channel,uint32 Sr1Value)
{
#if (_CDD_SIMULATION == STD_OFF)
	#if (PWM3PH_TOM_ATOM_SEL == 0U)
	Gtm_SetTomShadowValSr1(Moudle,Channel,(uint16)Sr1Value);
	#elif (PWM3PH_TOM_ATOM_SEL == 1U)
	Ifx_GTM_ATOM_CH *atomch=(Ifx_GTM_ATOM_CH *)\
							(((uint32)&(MODULE_GTM.ATOM[Moudle].CH0.RDADDR.U))\
							+0x80*Channel);
	atomch->SR1.U=Sr1Value;
	#endif
#endif
}
#endif
/*******************************************************************************
** Function Name	: Pwm3ph_Output_UpOff_DownOff
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	??None
** Description	  	: UpOff_DownOff
*******************************************************************************/
static void Pwm3ph_Output_UpOff_DownOff(PwmStatusFlagType* PwmStaFlag,PwmRegisterValueType* PwmRegVar)
{

	{
		/* U ?? */
		PwmRegVar->ui16_Pwm_OnEdge_UH_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		PwmRegVar->ui16_Pwm_OffEdge_UH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		/* CM0 defines the edge to SL value, CM1 defines the edge to ~SL value */
		PwmRegVar->ui16_Pwm_OffEdge_UL_SR0 = U16_REGISTER_OFFSET_VALUE;/*SR0*/
		PwmRegVar->ui16_Pwm_OnEdge_UL_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE; /*SR1*/

		/* V ?? */
		PwmRegVar->ui16_Pwm_OnEdge_VH_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		PwmRegVar->ui16_Pwm_OffEdge_VH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OffEdge_VL_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OnEdge_VL_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE; /*SR1*/

		/* W ?? */
		PwmRegVar->ui16_Pwm_OnEdge_WH_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		PwmRegVar->ui16_Pwm_OffEdge_WH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OffEdge_WL_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OnEdge_WL_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE; /*SR1*/
	}

}

/*******************************************************************************
** Function Name	: Pwm3ph_Output_UpOff_DownOn
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	閿熸枻鎷種one
** Description	  	: Output_UpOff_DownOn
*******************************************************************************/

static void Pwm3ph_Output_UpOff_DownOn(PwmStatusFlagType* PwmStaFlag,PwmRegisterValueType* PwmRegVar)
{
	if(PwmStaFlag->ui8_Pwm_Mode_Last == UI8_MODE_NORMAL) /* V1.2.2 Patch3 */
	{
		if(PwmStaFlag->VAR_PwmDutyCyclePhaseU_f32_Last > 0.999)
		{
			PwmRegVar->ui16_Pwm_OnEdge_UH_SR1 = PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;
			PwmRegVar->ui16_Pwm_OffEdge_UH_SR0 = U16_REGISTER_OFFSET_VALUE;
			PwmRegVar->ui16_Pwm_OffEdge_UL_SR0 = PwmRegVar->ui16_Pwm_Period_SR0;
			PwmRegVar->ui16_Pwm_OnEdge_UL_SR1 = U16_REGISTER_OFFSET_VALUE + PwmStaFlag->ui16_Pwm_Deadtime_Tick_Last;
		}
		else
		{
			PwmRegVar->ui16_Pwm_OnEdge_UH_SR1 = PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			PwmRegVar->ui16_Pwm_OffEdge_UH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
			PwmRegVar->ui16_Pwm_OffEdge_UL_SR0 = U16_REGISTER_OFFSET_VALUE + PwmRegVar->ui16_Pwm_Period_SR0;  /*SR0*/
			PwmRegVar->ui16_Pwm_OnEdge_UL_SR1 = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}

		if(PwmStaFlag->VAR_PwmDutyCyclePhaseV_f32_Last > 0.999)
		{
			PwmRegVar->ui16_Pwm_OnEdge_VH_SR1 = PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;
			PwmRegVar->ui16_Pwm_OffEdge_VH_SR0 = U16_REGISTER_OFFSET_VALUE;
			PwmRegVar->ui16_Pwm_OffEdge_VL_SR0 = PwmRegVar->ui16_Pwm_Period_SR0;
			PwmRegVar->ui16_Pwm_OnEdge_VL_SR1 = U16_REGISTER_OFFSET_VALUE + PwmStaFlag->ui16_Pwm_Deadtime_Tick_Last;
		}
		else
		{
			PwmRegVar->ui16_Pwm_OnEdge_VH_SR1 = PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			PwmRegVar->ui16_Pwm_OffEdge_VH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
			PwmRegVar->ui16_Pwm_OffEdge_VL_SR0 = U16_REGISTER_OFFSET_VALUE+ PwmRegVar->ui16_Pwm_Period_SR0;  /*SR0*/
			PwmRegVar->ui16_Pwm_OnEdge_VL_SR1 = U16_REGISTER_OFFSET_VALUE; /*SR1*/	
		}

		if(PwmStaFlag->VAR_PwmDutyCyclePhaseW_f32_Last > 0.999)
		{
			PwmRegVar->ui16_Pwm_OnEdge_WH_SR1 = PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;
			PwmRegVar->ui16_Pwm_OffEdge_WH_SR0 = U16_REGISTER_OFFSET_VALUE;
			PwmRegVar->ui16_Pwm_OffEdge_WL_SR0 = PwmRegVar->ui16_Pwm_Period_SR0;
			PwmRegVar->ui16_Pwm_OnEdge_WL_SR1 = U16_REGISTER_OFFSET_VALUE + PwmStaFlag->ui16_Pwm_Deadtime_Tick_Last;
		}
		else
		{
			PwmRegVar->ui16_Pwm_OnEdge_WH_SR1 = PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			PwmRegVar->ui16_Pwm_OffEdge_WH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
			PwmRegVar->ui16_Pwm_OffEdge_WL_SR0 = U16_REGISTER_OFFSET_VALUE+ PwmRegVar->ui16_Pwm_Period_SR0;  /*SR0*/
			PwmRegVar->ui16_Pwm_OnEdge_WL_SR1 = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}
	}
	else
	{
		/* U  */
		/* 100% SL(SL=LOW)*/\
		PwmRegVar->ui16_Pwm_OnEdge_UH_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		PwmRegVar->ui16_Pwm_OffEdge_UH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OffEdge_UL_SR0 = U16_REGISTER_OFFSET_VALUE + PwmRegVar->ui16_Pwm_Period_SR0;  /*SR0*/
		PwmRegVar->ui16_Pwm_OnEdge_UL_SR1 = \
					U16_REGISTER_OFFSET_VALUE; /*SR1*/


		/* V  */
		PwmRegVar->ui16_Pwm_OnEdge_VH_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		PwmRegVar->ui16_Pwm_OffEdge_VH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OffEdge_VL_SR0 = U16_REGISTER_OFFSET_VALUE+ PwmRegVar->ui16_Pwm_Period_SR0;  /*SR0*/
		PwmRegVar->ui16_Pwm_OnEdge_VL_SR1 = \
					U16_REGISTER_OFFSET_VALUE; /*SR1*/

		/* W  */
		PwmRegVar->ui16_Pwm_OnEdge_WH_SR1 = \
			PwmRegVar->ui16_Pwm_Period_SR0 + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		PwmRegVar->ui16_Pwm_OffEdge_WH_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
		PwmRegVar->ui16_Pwm_OffEdge_WL_SR0 = U16_REGISTER_OFFSET_VALUE+ PwmRegVar->ui16_Pwm_Period_SR0;  /*SR0*/
		PwmRegVar->ui16_Pwm_OnEdge_WL_SR1 = \
				U16_REGISTER_OFFSET_VALUE; /*SR1*/
	}
}
#define FAW_CORE0_IMEM0_CODE_START
#include "FAW_MemMap.h"
/*******************************************************************************
** Function Name	: Pwm3ph_Output_Normal
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	闁跨喐鏋婚幏绋畂ne
** Description	  	: Output_Normal
*******************************************************************************/
static void Pwm3ph_Output_Normal(PwmStatusFlagType* PwmStaFlag, DataConversionOutType* DataConvVar,PwmRegisterValueType* PwmRegVar)
{
	
	{
		PwmRegVar->ui16_Pwm_OnEdge_UH_SR1 = DataConvVar->ui16_Pwm_Ticks_OnEdge_UH;
		PwmRegVar->ui16_Pwm_OffEdge_UH_SR0 = DataConvVar->ui16_Pwm_Ticks_OffEdge_UH;
		PwmRegVar->ui16_Pwm_OffEdge_UL_SR0 = DataConvVar->ui16_Pwm_Ticks_OffEdge_UL;
		PwmRegVar->ui16_Pwm_OnEdge_UL_SR1 = DataConvVar->ui16_Pwm_Ticks_OnEdge_UL;
	
		PwmRegVar->ui16_Pwm_OnEdge_VH_SR1 = DataConvVar-> ui16_Pwm_Ticks_OnEdge_VH;
		PwmRegVar->ui16_Pwm_OffEdge_VH_SR0 = DataConvVar-> ui16_Pwm_Ticks_OffEdge_VH;
		PwmRegVar->ui16_Pwm_OffEdge_VL_SR0 = DataConvVar-> ui16_Pwm_Ticks_OffEdge_VL;
		PwmRegVar->ui16_Pwm_OnEdge_VL_SR1 = DataConvVar-> ui16_Pwm_Ticks_OnEdge_VL;
	
		PwmRegVar->ui16_Pwm_OnEdge_WH_SR1 = DataConvVar->ui16_Pwm_Ticks_OnEdge_WH;
		PwmRegVar->ui16_Pwm_OffEdge_WH_SR0 = DataConvVar->ui16_Pwm_Ticks_OffEdge_WH;
		PwmRegVar->ui16_Pwm_OffEdge_WL_SR0 = DataConvVar->ui16_Pwm_Ticks_OffEdge_WL;
		PwmRegVar->ui16_Pwm_OnEdge_WL_SR1 = DataConvVar->ui16_Pwm_Ticks_OnEdge_WL;
	}

}

/*******************************************************************************
** Function Name	: Pwm3ph_ChangePeriod
** Parameter[in] 	: uint16 ui16_Period
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	闁跨喐鏋婚幏绋畂ne
** Description	  	: ChangePeriod
*******************************************************************************/
static	void  Pwm3ph_ChangePeriod(uint16 ui16_Period,DataConversionInType* in,PwmRegisterValueType* PwmRegVar)
{
	if(ui16_Period <= U16_PWM_MAX_PERIOD_VALUE)
	{
		// PwmStaFlag->ui16_Pwm_Period_Tick_Last = ui16_Period;
//		PwmRegVar->ui16_Pwm_Period_SR0 = ui16_Period;

		#if defined(CHIP_PLATFORM_TC397)
				/*Period*/
				Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
							UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF,(ui16_Pwm_Period_SR0/2U));

				Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
						UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF,ui16_Pwm_Period_SR0);
				/*Trigger ADC*/
				Pwm3ph_Set_ShadowValSr1(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
						UI8_PWM_TOM_ATOM_CHANNEL_SEL_ADC_TRIG,(ui16_Pwm_Period_SR0/2U));
				Pwm3ph_Set_ShadowValSr0(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
						UI8_PWM_TOM_ATOM_CHANNEL_SEL_ADC_TRIG,ui16_Pwm_Period_SR0);

		#elif defined(CHIP_PLATFORM_CCFC3007PT)
			if(in->VAR_Motor_u8==1)
			{
				PwmRegVar->ui16_Pwm_Period_SR0 = ui16_Period;

				GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL,\
					UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF,\
					PwmRegVar->ui16_Pwm_Period_SR0,\
					(PwmRegVar->ui16_Pwm_Period_SR0/2U));
			}
			else if(in->VAR_Motor_u8==2)
			{
				PwmRegVar->ui16_Pwm_Period_SR0 = ui16_Period;
				
				GTM_ATOM_LLD_Channel_SetShadowRegister(UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2,\
					UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF_M2,\
					PwmRegVar->ui16_Pwm_Period_SR0,\
					(PwmRegVar->ui16_Pwm_Period_SR0/2U));
			}
			else
			{

			}		
		#endif
	}
}
/*******************************************************************************
** Function Name	: Pwm3ph_GetDataConversion
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	闁跨喐鏋婚幏绋畂ne
** Description	  	: GetDataConversion
*******************************************************************************/
int sr0=0x1f41;
int sr1=2;
int sr0H=0x1f41;
int sr1H=2;

static	void Pwm3ph_GetDataConversion(DataConversionInType* in , DataConversionOutType* out, PwmRegisterValueType* PwmRegVar, PwmStatusFlagType* PwmStaFlag)
{

	if((in->VAR_Pwm_Freq_u16>U16_PWM_MAX_FREQ_VALUE) || \
				(in->VAR_Pwm_Freq_u16<U16_PWM_MIN_FREQ_VALUE))
	{

		in->VAR_Pwm_Freq_u16 = U16_PWM_DEF_FREQ_VALUE;
	}

	
	uint16 ui16_Pwm_Period_Tick = \
				(uint16)(((float32)U32_PWM_GTM_CLOCK_VALUE)/((float32)in->VAR_Pwm_Freq_u16));

	uint16 ui16_DeadTime_Tick = \
			(uint16)(CAL_PWM_Set_DeadTime_us_f32 * U32_PWM_GTM_CLOCK_VALUE / 1000000);

	if((ui16_DeadTime_Tick < (2 * U32_PWM_GTM_CLOCK_VALUE / 1000000)) || (CAL_PWM_Set_DeadTime_us_f32 > (100 * U32_PWM_GTM_CLOCK_VALUE / 1000000)))
	{
		ui16_DeadTime_Tick = \
				(uint16)(2 * U32_PWM_GTM_CLOCK_VALUE / 1000000);

	}

	in->VAR_Pwm_DeadTime_In_f32 = (float32)ui16_DeadTime_Tick * 1000000 / U32_PWM_GTM_CLOCK_VALUE ;



	Pwm3ph_ChangePeriod(ui16_Pwm_Period_Tick,in,PwmRegVar);// wth 20210121 change for random pwm

	PwmStaFlag->ui16_Pwm_Period_Tick_Last = ui16_Pwm_Period_Tick;
	PwmStaFlag->ui16_Pwm_Deadtime_Tick_Last = ui16_DeadTime_Tick;

	uint16 ui16_Pwm_DutyU_Tick = \
			(uint16)(in->VAR_PwmDutyCyclePhaseU_f32*(float32)ui16_Pwm_Period_Tick);
	uint16 ui16_Pwm_DutyV_Tick = \
			(uint16)(in->VAR_PwmDutyCyclePhaseV_f32*(float32)ui16_Pwm_Period_Tick);
	uint16 ui16_Pwm_DutyW_Tick = \
			(uint16)(in->VAR_PwmDutyCyclePhaseW_f32*(float32)ui16_Pwm_Period_Tick);


/***********************************************************************************/
	/* W */
	if(  (in->VAR_PwmDutyCyclePhaseW_f32>CAL_Pwm3phB_ClosedThreshold_f32) && (in->VAR_PwmDutyCyclePhaseW_f32<=CAL_Pwm3ph_DutyMax_f32 ) )
	{
		/*example: period=100,duty=40,dead_time=2, OnEdge=(100-(40-2))/2 = 31,SR1=31 */
		out->ui16_Pwm_Ticks_OnEdge_WH = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyW_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2, OffEdge=(100+(40-2))/2 = 69,SR0=69 */
		out->ui16_Pwm_Ticks_OffEdge_WH = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyW_Tick - ui16_DeadTime_Tick))/2U);

		out->ui16_Pwm_Ticks_OnEdge_WL =  \
				ui16_Pwm_Period_Tick ; /*SR0*/
		out->ui16_Pwm_Ticks_OffEdge_WL = U16_REGISTER_OFFSET_VALUE; /*SR1*/

	}
	else if( (in->VAR_PwmDutyCyclePhaseW_f32 <= CAL_Pwm3phB_ClosedThreshold_f32)&&(in->VAR_PwmDutyCyclePhaseW_f32 >= CAL_Pwm3phT_ClosedThreshold_f32) )
	{
		/*example: period=100,duty=40,dead_time=2, OnEdge=(100-(40-2))/2 = 31,SR1=31*/
		out->ui16_Pwm_Ticks_OnEdge_WH = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyW_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2, OffEdge=(100+(40-2))/2 = 69,SR0=69*/
		out->ui16_Pwm_Ticks_OffEdge_WH = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyW_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2, OnEdge=(100+(40+2))/2 = 71,SR0=71*/
		out->ui16_Pwm_Ticks_OnEdge_WL = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyW_Tick + ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2, OffEdge=(100-(40+2))/2 = 29,SR0=29*/
		out->ui16_Pwm_Ticks_OffEdge_WL = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyW_Tick + ui16_DeadTime_Tick))/2U);
	}
	else if( (in->VAR_PwmDutyCyclePhaseW_f32 < CAL_Pwm3phT_ClosedThreshold_f32)&&(in->VAR_PwmDutyCyclePhaseW_f32>=CAL_Pwm3ph_DutyMin_f32)  )
	{

		out->ui16_Pwm_Ticks_OnEdge_WH = \
			ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
		out->ui16_Pwm_Ticks_OffEdge_WH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

		/*example: period=100,duty=40,dead_time=2, OnEdge=(100+(40+2))/2 = 71,SR0=71 */
		out->ui16_Pwm_Ticks_OnEdge_WL = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyW_Tick + ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2, OffEdge=(100-(40+2))/2 = 29,SR0=29 */
		out->ui16_Pwm_Ticks_OffEdge_WL = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyW_Tick + ui16_DeadTime_Tick))/2U);
	}
	else if(in->VAR_PwmDutyCyclePhaseW_f32<CAL_Pwm3ph_DutyMin_f32)
	{
		if(in->VAR_PwmDutyCyclePhaseW_f32_Last > 0.999  )  /* V1.2.2 Patch2: if last ductcycle in 5 section */
		{
			out->ui16_Pwm_Ticks_OnEdge_WH =  ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_WH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_WL =  U16_REGISTER_OFFSET_VALUE + ui16_DeadTime_Tick; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_WL = ui16_Pwm_Period_Tick ; /*SR1*/
		}
		else
		{
			out->ui16_Pwm_Ticks_OnEdge_WH =  ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_WH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_WL =  U16_REGISTER_OFFSET_VALUE ; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_WL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE ; /*SR1*/
		}
	}
	else if(in->VAR_PwmDutyCyclePhaseW_f32>CAL_Pwm3ph_DutyMax_f32)/*in->VAR_PwmDutyCyclePhaseW_f32>0->999*/
	{
		if((in->VAR_PwmDutyCyclePhaseW_f32_Last <= 0.999 ) || (PwmStaFlag->ui8_Pwm_Mode_Last == UI8_MODE_UP_OFF_DOWN_ON))  /* V1.2.2 Patch1 : if last ductcycle in 3 section*/
		{
			out->ui16_Pwm_Ticks_OnEdge_WH = U16_REGISTER_OFFSET_VALUE+ui16_DeadTime_Tick;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_WH =ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_WL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_WL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}
		else
		{
			out->ui16_Pwm_Ticks_OnEdge_WH = U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_WH =ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_WL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_WL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}
	}
	
	else
	{
		VAR_PWM3phWDuty_ERR_u8 = 1;
	}

/***********************************************************************************/
	/* V */
	if(  (in->VAR_PwmDutyCyclePhaseV_f32>CAL_Pwm3phB_ClosedThreshold_f32) && (in->VAR_PwmDutyCyclePhaseV_f32<=CAL_Pwm3ph_DutyMax_f32 ) )
	{
		/*example: period=100,duty=40,dead_time=2,OnEdge=(100-(40-2))/2 = 31,SR1=31*/
		out->ui16_Pwm_Ticks_OnEdge_VH = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyV_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100+(40-2))/2 = 69,SR0=69*/
		out->ui16_Pwm_Ticks_OffEdge_VH = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyV_Tick - ui16_DeadTime_Tick))/2U);

		out->ui16_Pwm_Ticks_OnEdge_VL =  \
			ui16_Pwm_Period_Tick ; /*SR0*/

		out->ui16_Pwm_Ticks_OffEdge_VL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
	}
	else if( (in->VAR_PwmDutyCyclePhaseV_f32 <= CAL_Pwm3phB_ClosedThreshold_f32)&&(in->VAR_PwmDutyCyclePhaseV_f32 >= CAL_Pwm3phT_ClosedThreshold_f32) )
	{
		/*example: period=100,duty=40,dead_time=2,OnEdge=(100-(40-2))/2 = 31,SR1=31*/
		out->ui16_Pwm_Ticks_OnEdge_VH = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyV_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100+(40-2))/2 = 69,SR0=69*/
		out->ui16_Pwm_Ticks_OffEdge_VH = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyV_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OnEdge=(100+(40+2))/2 = 71,SR0=71*/
		out->ui16_Pwm_Ticks_OnEdge_VL = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyV_Tick + ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100-(40+2))/2 = 29,SR0=29*/
		out->ui16_Pwm_Ticks_OffEdge_VL = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyV_Tick + ui16_DeadTime_Tick))/2U);
	}
	else if((in->VAR_PwmDutyCyclePhaseV_f32 < CAL_Pwm3phT_ClosedThreshold_f32)&&(in->VAR_PwmDutyCyclePhaseV_f32>=CAL_Pwm3ph_DutyMin_f32) )
	{

		out->ui16_Pwm_Ticks_OnEdge_VH = \
				ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/

		out->ui16_Pwm_Ticks_OffEdge_VH = U16_REGISTER_OFFSET_VALUE; /*SR0*/


		/*example: period=100,duty=40,dead_time=2,nEdge=(100+(40+2))/2 = 71,SR0=71*/
		out->ui16_Pwm_Ticks_OnEdge_VL = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyV_Tick + ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100-(40+2))/2 = 29,SR0=29*/
		out->ui16_Pwm_Ticks_OffEdge_VL = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyV_Tick + ui16_DeadTime_Tick))/2U);
	}
	else if( in->VAR_PwmDutyCyclePhaseV_f32<CAL_Pwm3ph_DutyMin_f32 )
	{
		if(in->VAR_PwmDutyCyclePhaseV_f32_Last > 0.999  )   /* V1.2.2 Patch2: if last ductcycle in 5 section */
		{
			out->ui16_Pwm_Ticks_OnEdge_VH =  ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_VH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_VL =  U16_REGISTER_OFFSET_VALUE + ui16_DeadTime_Tick; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_VL = ui16_Pwm_Period_Tick ; /*SR1*/
		}
		else
		{
			out->ui16_Pwm_Ticks_OnEdge_VH =  ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_VH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_VL =  U16_REGISTER_OFFSET_VALUE ; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_VL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE ; /*SR1*/
		}
	}
	else if(in->VAR_PwmDutyCyclePhaseV_f32>CAL_Pwm3ph_DutyMax_f32)/*VAR_PwmDutyCyclePhaseV_f32>0.999*/
	{
		if((in->VAR_PwmDutyCyclePhaseV_f32_Last <= 0.999 ) || (PwmStaFlag->ui8_Pwm_Mode_Last == UI8_MODE_UP_OFF_DOWN_ON))  /* V1.2.2 Patch1 : if last ductcycle in 3 section*/
		{
			out->ui16_Pwm_Ticks_OnEdge_VH = U16_REGISTER_OFFSET_VALUE+ui16_DeadTime_Tick;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_VH =ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_VL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_VL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}
		else
		{
			out->ui16_Pwm_Ticks_OnEdge_VH = U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_VH =ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_VL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_VL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}

	}
	else
	{
		VAR_PWM3phVDuty_ERR_u8 = 1;
	}


/***********************************************************************************/
	/* U */
	if(  (in->VAR_PwmDutyCyclePhaseU_f32>CAL_Pwm3phB_ClosedThreshold_f32) && (in->VAR_PwmDutyCyclePhaseU_f32<=CAL_Pwm3ph_DutyMax_f32 ) )//�?0.94 < X <= 0.999�?
	{
		/*example: period=100,duty=40,dead_time=2,OnEdge=(100-(40-2))/2 = 31,SR1=31*/
		out->ui16_Pwm_Ticks_OnEdge_UH = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyU_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100+(40-2))/2 = 69,SR0=69*/
		out->ui16_Pwm_Ticks_OffEdge_UH = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyU_Tick - ui16_DeadTime_Tick))/2U);

		out->ui16_Pwm_Ticks_OnEdge_UL = \
				ui16_Pwm_Period_Tick ; /*SR0*/
		out->ui16_Pwm_Ticks_OffEdge_UL = U16_REGISTER_OFFSET_VALUE; /*SR1*/


	}
	else if( (in->VAR_PwmDutyCyclePhaseU_f32 <= CAL_Pwm3phB_ClosedThreshold_f32)&&(in->VAR_PwmDutyCyclePhaseU_f32 >= CAL_Pwm3phT_ClosedThreshold_f32) ) //�?0.06 <= X < 0.94�?
	{
		/*example: period=100,duty=40,dead_time=2, OnEdge=(100-(40-2))/2 = 31,SR1=31*/
		out->ui16_Pwm_Ticks_OnEdge_UH = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyU_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100+(40-2))/2 = 69,SR0=69*/
		out->ui16_Pwm_Ticks_OffEdge_UH = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyU_Tick - ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OnEdge=(100+(40+2))/2 = 71,SR0=71*/
		out->ui16_Pwm_Ticks_OnEdge_UL = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyU_Tick + ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100-(40+2))/2 = 29,SR0=29*/
		out->ui16_Pwm_Ticks_OffEdge_UL = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyU_Tick + ui16_DeadTime_Tick))/2U);
	}
	else if((in->VAR_PwmDutyCyclePhaseU_f32 < CAL_Pwm3phT_ClosedThreshold_f32)&&(in->VAR_PwmDutyCyclePhaseU_f32>=CAL_Pwm3ph_DutyMin_f32) ) //�?0.001 <= X < 0.06 �?
	{

		out->ui16_Pwm_Ticks_OnEdge_UH = \
			ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/

		out->ui16_Pwm_Ticks_OffEdge_UH = U16_REGISTER_OFFSET_VALUE; /*SR0*/


		/*example: period=100,duty=40,dead_time=2,OnEdge=(100+(40+2))/2 = 71,SR0=71 */
		out->ui16_Pwm_Ticks_OnEdge_UL = (uint16)((ui16_Pwm_Period_Tick + \
				(ui16_Pwm_DutyU_Tick + ui16_DeadTime_Tick))/2U);
		/*example: period=100,duty=40,dead_time=2,OffEdge=(100-(40+2))/2 = 29,SR0=29*/
		out->ui16_Pwm_Ticks_OffEdge_UL = (uint16)((ui16_Pwm_Period_Tick - \
				(ui16_Pwm_DutyU_Tick + ui16_DeadTime_Tick))/2U);
	}
	else if( in->VAR_PwmDutyCyclePhaseU_f32<CAL_Pwm3ph_DutyMin_f32 )  /* X < 0.001 */
	{
		if(in->VAR_PwmDutyCyclePhaseU_f32_Last > 0.999  )  /* V1.2.2 Patch2: if last ductcycle in 5 section */
		{
			out->ui16_Pwm_Ticks_OnEdge_UH =  ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_UH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_UL =  U16_REGISTER_OFFSET_VALUE + ui16_DeadTime_Tick; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_UL = ui16_Pwm_Period_Tick ; /*SR1*/
		}
		else
		{
			out->ui16_Pwm_Ticks_OnEdge_UH =  ui16_Pwm_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_UH = U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_UL =  U16_REGISTER_OFFSET_VALUE ; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_UL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE ; /*SR1*/
		}
	}

	else if(in->VAR_PwmDutyCyclePhaseU_f32>CAL_Pwm3ph_DutyMax_f32)  /* ( X > 0.999) */
	{

		if((in->VAR_PwmDutyCyclePhaseU_f32_Last <= 0.999 ) || (PwmStaFlag->ui8_Pwm_Mode_Last == UI8_MODE_UP_OFF_DOWN_ON))  /* V1.2.2 Patch1 : if last ductcycle in 3 section*/
		{
			out->ui16_Pwm_Ticks_OnEdge_UH = U16_REGISTER_OFFSET_VALUE+ui16_DeadTime_Tick;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_UH =ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_UL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_UL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}
		else
		{
			out->ui16_Pwm_Ticks_OnEdge_UH = U16_REGISTER_OFFSET_VALUE;  /*SR1*/
			out->ui16_Pwm_Ticks_OffEdge_UH =ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/

			out->ui16_Pwm_Ticks_OnEdge_UL = ui16_Pwm_Period_Tick+U16_REGISTER_OFFSET_VALUE; /*SR0*/
			out->ui16_Pwm_Ticks_OffEdge_UL = U16_REGISTER_OFFSET_VALUE; /*SR1*/
		}

//		out->ui16_Pwm_Ticks_OnEdge_UH = sr0H; /*SR0*/
//		out->ui16_Pwm_Ticks_OffEdge_UH = sr1H; /*SR1*/
//
//		out->ui16_Pwm_Ticks_OnEdge_UL = sr0; /*SR0*/
//		out->ui16_Pwm_Ticks_OffEdge_UL = sr1; /*SR1*/
	}
	else
	{
		VAR_PWM3phUDuty_ERR_u8 = 1;
	}

}
#define FAW_CORE0_IMEM0_CODE_STOP
#include "FAW_MemMap.h"
/*******************************************************************************

*******************************************************************************/
