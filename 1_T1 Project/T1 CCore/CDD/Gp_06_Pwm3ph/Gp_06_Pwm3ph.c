/*******************************************************************************
**----------------------------------------------------------------------------**
** Copyright (c) 2017 by G-Pulse.		All rights reserved.
** This software is copyright protected and proprietary to G-Pulse.
** G-Pulse grants to you only those rights as set out in the license conditions.
** All other rights remain with G-Pulse.
**----------------------------------------------------------------------------**
**
* Administrative Information
* $Namespace_: ..\ Gp_06_Pwm3ph$
* $Class_____: C$
* $Name______: Gp_06_Pwm3ph.c$
* $Variant___: 1.0.2$
* $Revision__: 0$
* $Author____: CaoZijian$
**
**----------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: No
**----------------------------------------------------------------------------**
** DESCRIPTION:
** Gp_06_Pwm3ph source file
*******************************************************************************/

/***********************************************************************************************************************
**                      						Other Header File Inclusion                         				  **
***********************************************************************************************************************/

#include "Gp_06_Pwm3ph.h"

/***********************************************************************************************************************
**                          						Macro Definition   		                    		    		  **
***********************************************************************************************************************/

#define U16_REGISTER_OFFSET_VALUE	(1U)		/*register offset*/

/***********************************************************************************************************************
**                          						Typedef Definition         				                		  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                  							 Static Local Variables Definition     				         		  **
***********************************************************************************************************************/
#define GP_06_PWM3PH_INIT_FAR_DATA_START
#include "Gp_06_Pwm3ph_MemMap.h"
//
#define GP_06_PWM3PH_INIT_FAR_DATA_STOP
#include "Gp_06_Pwm3ph_MemMap.h"
//
//
#define GP_06_PWM3PH_CLEAR_FAR_DATA_START
#include "Gp_06_Pwm3ph_MemMap.h"

uint32 ui32_Pwm3ph_Period_SR0;		 			/*SR0 value*/

uint32 ui32_Pwm3ph_Period_Tick; 	 			/*period tick*/
uint32 ui32_Pwm3ph_Period_Tick_Back; 	 		/*period tick backup*/

uint16 ui16_Pwm3ph_DeadTime_Tick;				/*dead time tick*/
uint32 ui32_Pwm3phU_DutyTick;					/*U duty tick*/
uint32 ui32_Pwm3phU_DutyTick_Back;				/*U duty tick backup*/
uint32 ui32_Pwm3phV_DutyTick;					/*V duty tick*/
uint32 ui32_Pwm3phV_DutyTick_Back;				/*V duty tick backup*/
uint32 ui32_Pwm3phW_DutyTick;					/*W duty tick*/
uint32 ui32_Pwm3phW_DutyTick_Back;				/*W duty tick backup*/
uint16 ui16_Pwm3ph_MiniPulse_Tick;				/*minimum pulse width tick*/

uint32	ui32_Pwm3ph_Timestamp_u32;				/*time stamp*/

/*MCS00*/
volatile uint32* pui32_Pwm3ph_Mcs0_PwmMode;				/*PWM output mode*/
volatile uint32* pui32_Pwm3ph_Mcs0_PwmPerdTick;			/*PWM output period*/
volatile uint32* pui32_Pwm3ph_Mcs0_DeadTimeTick;			/*PWM dead time:uint,tick*/
volatile uint32* pui32_Pwm3ph_Mcs0_DutyTickU;			/*PWM U phase duty cycle:tick*/

volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt0; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt1; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt2; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt3; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt4; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt5; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt6; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt7; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt8; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs0_Chl0Cnt9; 			/*MCS channel task counter*/

volatile uint32* pui32_Pwm3ph_Mcs0_TimeStamp0; 			/*Time stamp0*/
volatile uint32* pui32_Pwm3ph_Mcs0_TimeStamp1; 			/*Time stamp1*/
volatile uint32* pui32_Pwm3ph_Mcs0_TimeStamp2; 			/*Time stamp2*/

volatile uint32* pui32_Pwm3ph_Mcs0_TimeIntl0; 			/*time interval0*/
volatile uint32* pui32_Pwm3ph_Mcs0_TimeIntl1; 			/*time interval1*/
volatile uint32* pui32_Pwm3ph_Mcs0_TimeIntl2; 			/*time interval2*/

/*MCS01*/
volatile uint32* pui32_Pwm3ph_Mcs1_PwmMode;				/*PWM output mode*/
volatile uint32* pui32_Pwm3ph_Mcs1_PwmPerdTick;			/*PWM output period*/
volatile uint32* pui32_Pwm3ph_Mcs1_DeadTimeTick;			/*PWM dead time:uint,tick*/
volatile uint32* pui32_Pwm3ph_Mcs1_DutyTickV;			/*PWM U phase duty cycle:tick*/

volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt0; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt1; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt2; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt3; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt4; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt5; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt6; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt7; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt8; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs1_Chl0Cnt9; 			/*MCS channel task counter*/

volatile uint32* pui32_Pwm3ph_Mcs1_TimeStamp0; 			/*Time stamp0*/
volatile uint32* pui32_Pwm3ph_Mcs1_TimeStamp1; 			/*Time stamp1*/
volatile uint32* pui32_Pwm3ph_Mcs1_TimeStamp2; 			/*Time stamp2*/

volatile uint32* pui32_Pwm3ph_Mcs1_TimeIntl0; 			/*time interval0*/
volatile uint32* pui32_Pwm3ph_Mcs1_TimeIntl1; 			/*time interval1*/
volatile uint32* pui32_Pwm3ph_Mcs1_TimeIntl2; 			/*time interval2*/

/*MCS02*/
volatile uint32* pui32_Pwm3ph_Mcs2_PwmMode;				/*PWM output mode*/
volatile uint32* pui32_Pwm3ph_Mcs2_PwmPerdTick;			/*PWM output period*/
volatile uint32* pui32_Pwm3ph_Mcs2_DeadTimeTick;		/*PWM dead time:uint,tick*/
volatile uint32* pui32_Pwm3ph_Mcs2_DutyTickW;			/*PWM U phase duty cycle:tick*/

volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt0; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt1; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt2; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt3; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt4; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt5; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt6; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt7; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt8; 			/*MCS channel task counter*/
volatile uint32* pui32_Pwm3ph_Mcs2_Chl0Cnt9; 			/*MCS channel task counter*/

volatile uint32* pui32_Pwm3ph_Mcs2_TimeStamp0; 			/*Time stamp0*/
volatile uint32* pui32_Pwm3ph_Mcs2_TimeStamp1; 			/*Time stamp1*/
volatile uint32* pui32_Pwm3ph_Mcs2_TimeStamp2; 			/*Time stamp2*/

volatile uint32* pui32_Pwm3ph_Mcs2_TimeIntl0; 			/*time interval0*/
volatile uint32* pui32_Pwm3ph_Mcs2_TimeIntl1; 			/*time interval1*/
volatile uint32* pui32_Pwm3ph_Mcs2_TimeIntl2; 			/*time interval2*/

/***********************************************************************************************************************
**                     							Global Variables Definition            					  		      **
***********************************************************************************************************************/
uint8 ui8_Pwm3ph_Mode;							/*Pwm3ph mode*/
uint32 ui32_Pwm3ph_Freq;						/*Pwm3ph frequency*/
float32 f32_Pwm3ph_DeadTime_In;					/*Pwm3ph dead time*/

float32 f32_Pwm3phDutyCyclePhaseU;				/*Pwm3ph U duty cycle*/
float32 f32_Pwm3phDutyCyclePhaseV;				/*Pwm3ph V duty cycle*/
float32 f32_Pwm3phDutyCyclePhaseW;				/*Pwm3ph W duty cycle*/

#define GP_06_PWM3PH_CLEAR_FAR_DATA_STOP
#include "Gp_06_Pwm3ph_MemMap.h"
//
#define GP_06_PWM3PH_COMPILER_OPTIMIZE_START
#include "Gp_06_Pwm3ph_MemMap.h"
//
#define GP_06_PWM3PH_CODE_START
#include "Gp_06_Pwm3ph_MemMap.h"
/***********************************************************************************************************************
**                  						Static Local Function Declaration				            		      **
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_MapMcsVar(void);
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_EnableTrigger(void);
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_Enable_OutputChl(uint8 ui8_Module,uint8 ui8_Chl);
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_Output_UpOff_DownOff(void);
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_ChangePeriod(void);
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_DataUpdate(void);
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_UVWDutyToTick(float32 f32_Pwm3phDutyCycle, uint32* pui32_Pwm3phX_DutyTick);
/***********************************************************************************************************************
**                 		  					Function Source Code            		   					              **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_MapMcsVar
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: map CPU pointers to MCS runtime variable
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_MapMcsVar(void)
{
	/*point to MCS00 variable address*/
	pui32_Pwm3ph_Mcs0_PwmMode = PUI32_PWM3PH_MCS0_PWMMODE_ADDR;					/*PWM output mode*/
	pui32_Pwm3ph_Mcs0_PwmPerdTick = PUI32_PWM3PH_MCS0_PWMPERDTICK_ADDR;			/*PWM output period*/
	pui32_Pwm3ph_Mcs0_DutyTickU = PUI32_PWM3PH_MCS0_DUTYTICKU_ADDR;				/*PWM U phase duty cycle:tick*/

	pui32_Pwm3ph_Mcs0_Chl0Cnt0 = PUI32_PWM3PH_MCS0_CHL0CNT0_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt1 = PUI32_PWM3PH_MCS0_CHL0CNT1_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt2 = PUI32_PWM3PH_MCS0_CHL0CNT2_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt3 = PUI32_PWM3PH_MCS0_CHL0CNT3_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt4 = PUI32_PWM3PH_MCS0_CHL0CNT4_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt5 = PUI32_PWM3PH_MCS0_CHL0CNT5_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt6 = PUI32_PWM3PH_MCS0_CHL0CNT6_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt7 = PUI32_PWM3PH_MCS0_CHL0CNT7_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt8 = PUI32_PWM3PH_MCS0_CHL0CNT8_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs0_Chl0Cnt9 = PUI32_PWM3PH_MCS0_CHL0CNT9_ADDR; 			    /*MCS channel task counter*/

	pui32_Pwm3ph_Mcs0_TimeStamp0 = PUI32_PWM3PH_MCS0_TIMESTAMP0_ADDR; 			/*Time stamp0*/
	pui32_Pwm3ph_Mcs0_TimeStamp1 = PUI32_PWM3PH_MCS0_TIMESTAMP1_ADDR; 			/*Time stamp1*/
	pui32_Pwm3ph_Mcs0_TimeStamp2 = PUI32_PWM3PH_MCS0_TIMESTAMP2_ADDR; 			/*Time stamp2*/

	pui32_Pwm3ph_Mcs0_TimeIntl0 = PUI32_PWM3PH_MCS0_TIMEINTL0_ADDR; 			/*time interval0*/
	pui32_Pwm3ph_Mcs0_TimeIntl1 = PUI32_PWM3PH_MCS0_TIMEINTL1_ADDR; 			/*time interval1*/
	pui32_Pwm3ph_Mcs0_TimeIntl2 = PUI32_PWM3PH_MCS0_TIMEINTL2_ADDR; 			/*time interval2*/

	/*point to MCS01 variable address*/
	pui32_Pwm3ph_Mcs1_PwmMode = PUI32_PWM3PH_MCS1_PWMMODE_ADDR;					/*PWM output mode*/
	pui32_Pwm3ph_Mcs1_DeadTimeTick = PUI32_PWM3PH_MCS1_DEADTIMETICK_ADDR;		/*PWM dead time:uint,tick*/
	pui32_Pwm3ph_Mcs1_DutyTickV = PUI32_PWM3PH_MCS1_DUTYTICKV_ADDR;				/*PWM U phase duty cycle:tick*/

	pui32_Pwm3ph_Mcs1_Chl0Cnt0 = PUI32_PWM3PH_MCS1_CHL0CNT0_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt1 = PUI32_PWM3PH_MCS1_CHL0CNT1_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt2 = PUI32_PWM3PH_MCS1_CHL0CNT2_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt3 = PUI32_PWM3PH_MCS1_CHL0CNT3_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt4 = PUI32_PWM3PH_MCS1_CHL0CNT4_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt5 = PUI32_PWM3PH_MCS1_CHL0CNT5_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt6 = PUI32_PWM3PH_MCS1_CHL0CNT6_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt7 = PUI32_PWM3PH_MCS1_CHL0CNT7_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt8 = PUI32_PWM3PH_MCS1_CHL0CNT8_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs1_Chl0Cnt9 = PUI32_PWM3PH_MCS1_CHL0CNT9_ADDR; 			    /*MCS channel task counter*/

	pui32_Pwm3ph_Mcs1_TimeStamp0 = PUI32_PWM3PH_MCS1_TIMESTAMP0_ADDR; 			/*Time stamp0*/
	pui32_Pwm3ph_Mcs1_TimeStamp1 = PUI32_PWM3PH_MCS1_TIMESTAMP1_ADDR; 			/*Time stamp1*/
	pui32_Pwm3ph_Mcs1_TimeStamp2 = PUI32_PWM3PH_MCS1_TIMESTAMP2_ADDR; 			/*Time stamp2*/

	pui32_Pwm3ph_Mcs1_TimeIntl0 = PUI32_PWM3PH_MCS1_TIMEINTL0_ADDR; 			/*time interval0*/
	pui32_Pwm3ph_Mcs1_TimeIntl1 = PUI32_PWM3PH_MCS1_TIMEINTL1_ADDR; 			/*time interval1*/
	pui32_Pwm3ph_Mcs1_TimeIntl2 = PUI32_PWM3PH_MCS1_TIMEINTL2_ADDR; 			/*time interval2*/

	/*point to MCS02 variable address*/
	pui32_Pwm3ph_Mcs2_PwmMode = PUI32_PWM3PH_MCS2_PWMMODE_ADDR;					/*PWM output mode*/
	pui32_Pwm3ph_Mcs2_PwmPerdTick = PUI32_PWM3PH_MCS2_PWMPERDTICK_ADDR;			/*PWM output period*/
	pui32_Pwm3ph_Mcs2_DutyTickW = PUI32_PWM3PH_MCS2_DUTYTICKW_ADDR;				/*PWM U phase duty cycle:tick*/

	pui32_Pwm3ph_Mcs2_Chl0Cnt0 = PUI32_PWM3PH_MCS2_CHL0CNT0_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt1 = PUI32_PWM3PH_MCS2_CHL0CNT1_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt2 = PUI32_PWM3PH_MCS2_CHL0CNT2_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt3 = PUI32_PWM3PH_MCS2_CHL0CNT3_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt4 = PUI32_PWM3PH_MCS2_CHL0CNT4_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt5 = PUI32_PWM3PH_MCS2_CHL0CNT5_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt6 = PUI32_PWM3PH_MCS2_CHL0CNT6_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt7 = PUI32_PWM3PH_MCS2_CHL0CNT7_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt8 = PUI32_PWM3PH_MCS2_CHL0CNT8_ADDR; 			    /*MCS channel task counter*/
	pui32_Pwm3ph_Mcs2_Chl0Cnt9 = PUI32_PWM3PH_MCS2_CHL0CNT9_ADDR; 			    /*MCS channel task counter*/

	pui32_Pwm3ph_Mcs2_TimeStamp0 = PUI32_PWM3PH_MCS2_TIMESTAMP0_ADDR; 			/*Time stamp0*/
	pui32_Pwm3ph_Mcs2_TimeStamp1 = PUI32_PWM3PH_MCS2_TIMESTAMP1_ADDR; 			/*Time stamp1*/
	pui32_Pwm3ph_Mcs2_TimeStamp2 = PUI32_PWM3PH_MCS2_TIMESTAMP2_ADDR; 			/*Time stamp2*/

	pui32_Pwm3ph_Mcs2_TimeIntl0 = PUI32_PWM3PH_MCS2_TIMEINTL0_ADDR; 			/*time interval0*/
	pui32_Pwm3ph_Mcs2_TimeIntl1 = PUI32_PWM3PH_MCS2_TIMEINTL1_ADDR; 			/*time interval1*/
	pui32_Pwm3ph_Mcs2_TimeIntl2 = PUI32_PWM3PH_MCS2_TIMEINTL2_ADDR; 			/*time interval2*/
}

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_EnableTrigger
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: enable ATOM channel, set channel pin mode
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_EnableTrigger(void)
{
	/*enable reference channel*/
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMODULE_REF,UI8_PWM3PH_ATOMCHL_REF);
	/*enable UVW channel*/
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMOUDLE_UT,UI8_PWM3PH_ATOMCHL_UT);
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMOUDLE_UB,UI8_PWM3PH_ATOMCHL_UB);
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMOUDLE_VT,UI8_PWM3PH_ATOMCHL_VT);
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMOUDLE_VB,UI8_PWM3PH_ATOMCHL_VB);
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMOUDLE_WT,UI8_PWM3PH_ATOMCHL_WT);
	Gp_06_Pwm3ph_Enable_OutputChl(UI8_PWM3PH_ATOMMOUDLE_WB,UI8_PWM3PH_ATOMCHL_WB);

	/*set reference channel pin mode*/
	Port_SetPinMode(UI32_PWM3PH_CFG_REF_GPIO, UI32_PWM3PH_CFG_REF_ALTMOD);
	/*set UVW pin mode*/
	Port_SetPinMode(UI32_PWM3PH_CFG_UT_GPIO, UI32_PWM3PH_CFG_UT_ALTMOD);
	Port_SetPinMode(UI32_PWM3PH_CFG_UB_GPIO, UI32_PWM3PH_CFG_UB_ALTMOD);
	Port_SetPinMode(UI32_PWM3PH_CFG_VT_GPIO, UI32_PWM3PH_CFG_VT_ALTMOD);
	Port_SetPinMode(UI32_PWM3PH_CFG_VB_GPIO, UI32_PWM3PH_CFG_VB_ALTMOD);
	Port_SetPinMode(UI32_PWM3PH_CFG_WT_GPIO, UI32_PWM3PH_CFG_WT_ALTMOD);
	Port_SetPinMode(UI32_PWM3PH_CFG_WB_GPIO, UI32_PWM3PH_CFG_WB_ALTMOD);
}

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_Enable_OutputChl
** Parameter[in] 	: uint8 ui8_Module
** Parameter[in] 	: uint8 ui8_Chl
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: enable ATOM channel
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_Enable_OutputChl(uint8 ui8_Module, uint8 ui8_Chl)
{
	uint32 ui32_RegVal = *(volatile uint32*)(UI32_PWM3PH_ATOM0_ADDR + (ui8_Module * UI32_PWM3PH_MODULE_OFFSET) + 0x48U);
	ui32_RegVal &= ~(0x03U << (2U * ui8_Chl));
	ui32_RegVal |= 0x02U << (2U * ui8_Chl);
	*(volatile uint32*)(UI32_PWM3PH_ATOM0_ADDR + (ui8_Module * UI32_PWM3PH_MODULE_OFFSET) + 0x48) = ui32_RegVal;
}

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_Output_UpOff_DownOff
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: free-wheel mode: H off, L OFF
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_Output_UpOff_DownOff(void)
{
	/*U*/
	*ui32_Pwm3ph_OnEdge_UT_SR1 = ui32_Pwm3ph_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
	*ui32_Pwm3ph_OffEdge_UT_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
	*ui32_Pwm3ph_OnEdge_UB_SR0 = ui32_Pwm3ph_Period_Tick + U16_REGISTER_OFFSET_VALUE; /*SR0*/
	*ui32_Pwm3ph_OffEdge_UB_SR1 = U16_REGISTER_OFFSET_VALUE; /*SR1*/

	/*V*/
	*ui32_Pwm3ph_OnEdge_VT_SR1 = ui32_Pwm3ph_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
	*ui32_Pwm3ph_OffEdge_VT_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
	*ui32_Pwm3ph_OnEdge_VB_SR0 = ui32_Pwm3ph_Period_Tick + U16_REGISTER_OFFSET_VALUE; /*SR0*/
	*ui32_Pwm3ph_OffEdge_VB_SR1 = U16_REGISTER_OFFSET_VALUE; /*SR1*/

	/*W*/
	*ui32_Pwm3ph_OnEdge_WT_SR1 = ui32_Pwm3ph_Period_Tick + U16_REGISTER_OFFSET_VALUE;  /*SR1*/
	*ui32_Pwm3ph_OffEdge_WT_SR0 = U16_REGISTER_OFFSET_VALUE; /*SR0*/
	*ui32_Pwm3ph_OnEdge_WB_SR0 = ui32_Pwm3ph_Period_Tick + U16_REGISTER_OFFSET_VALUE; /*SR0*/
	*ui32_Pwm3ph_OffEdge_WB_SR1 = U16_REGISTER_OFFSET_VALUE; /*SR1*/
}


/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_ChangePeriod
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: change period
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void  Gp_06_Pwm3ph_ChangePeriod(void)
{
	ui32_Pwm3ph_Period_SR0 = ui32_Pwm3ph_Period_Tick;

	/*set reference channel SRx*/
	*ui32_Pwm3ph_OnEdge_REF_SR1 = ui32_Pwm3ph_Period_SR0/2U;
	*ui32_Pwm3ph_OffEdge_REF_SR0 = ui32_Pwm3ph_Period_SR0;
}

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_DataUpdate
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: the function converts the input parameters into tick value.
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_DataUpdate(void)
{
	/*period tick value calculation*/
	if(ui32_Pwm3ph_Freq > UI16_PWM3PH_MAX_FREQ_VALUE)
	{
		ui32_Pwm3ph_Freq = UI16_PWM3PH_MAX_FREQ_VALUE;
	}
	else if(ui32_Pwm3ph_Freq < UI16_PWM3PH_MIN_FREQ_VALUE)
	{
		ui32_Pwm3ph_Freq = UI16_PWM3PH_MIN_FREQ_VALUE;
	}
	else
	{
		/*for MISRA-C*/
	}

	ui32_Pwm3ph_Period_Tick  = UI32_PWM3PH_GTM_CLOCK_VALUE / ui32_Pwm3ph_Freq;

	/*U V W duty cycle tick value calculation*/
	Gp_06_Pwm3ph_UVWDutyToTick(f32_Pwm3phDutyCyclePhaseU, &ui32_Pwm3phU_DutyTick);
	Gp_06_Pwm3ph_UVWDutyToTick(f32_Pwm3phDutyCyclePhaseV, &ui32_Pwm3phV_DutyTick);
	Gp_06_Pwm3ph_UVWDutyToTick(f32_Pwm3phDutyCyclePhaseW, &ui32_Pwm3phW_DutyTick);

}

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_UVWDutyToTick
** Parameter[in] 	: float32 f32_Pwm3phDutyCycle
** Parameter[out] 	: uint32* pui32_Pwm3phX_DutyTick
** Return Value	  	: None
** Note			  	: None
** Description	  	: the function converts UVW duty cycle into TICK value
***********************************************************************************************************************/
GP_06_PWM3PH_INLINE_ void Gp_06_Pwm3ph_UVWDutyToTick(float32 f32_Pwm3phDutyCycle, uint32* pui32_Pwm3phX_DutyTick)
{
	float32 f32_Pwm3phDutyCycle_Intr;
	f32_Pwm3phDutyCycle_Intr = f32_Pwm3phDutyCycle;

	/*UVW duty cycle tick value calculation*/
	if(f32_Pwm3phDutyCycle_Intr < F32_PWM3PH_MIN_DUTY_VALUE)
	{
		f32_Pwm3phDutyCycle_Intr = F32_PWM3PH_MIN_DUTY_VALUE;
	}
	else if(f32_Pwm3phDutyCycle_Intr > F32_PWM3PH_MAX_DUTY_VALUE)
	{
		f32_Pwm3phDutyCycle_Intr = F32_PWM3PH_MAX_DUTY_VALUE;
	}
	else
	{
		/*for MISR-C*/
	}

	*pui32_Pwm3phX_DutyTick = (uint32)(f32_Pwm3phDutyCycle_Intr * ((float32)ui32_Pwm3ph_Period_Tick));
}

/***********************************************************************************************************************
** Function Name	: Gp_06_Pwm3ph_Init
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: the function is called after GTM initiation
** Description	  	: Pwm3ph initiation
***********************************************************************************************************************/
void Gp_06_Pwm3ph_Init(void)
{
	/*PWM parameter initialization*/
	f32_Pwm3ph_DeadTime_In = F32_PWM3PH_DEF_DEADTIME;
	ui32_Pwm3ph_Freq = UI16_PWM3PH_DEF_FREQ_VALUE;
	f32_Pwm3phDutyCyclePhaseU = 0.0f;
	f32_Pwm3phDutyCyclePhaseV = 0.0f;
	f32_Pwm3phDutyCyclePhaseW = 0.0f;

	/*map CPU pointers to MCS runtime variable*/
	Gp_06_Pwm3ph_MapMcsVar();

	/*converts the input parameters into tick value*/
	Gp_06_Pwm3ph_DataUpdate();

	/*change period*/
	Gp_06_Pwm3ph_ChangePeriod();

	/*set H off,L off*/
	Gp_06_Pwm3ph_Output_UpOff_DownOff();
	/*interrupt trigger enable*/
	Gp_06_Pwm3ph_EnableTrigger();
}
/**********************************************************************************************************************
** Function Name	: Gp_06_Pwm3phSetOutput_CddIo
** Parameter[in] 	: uint8 ui8_Mode
** Parameter[in] 	: uint32 ui32_Freq
** Parameter[in] 	: float32 f32_DutyCyclePhaseU
** Parameter[in] 	: float32 f32_DutyCyclePhaseV
** Parameter[in] 	: float32 f32_DutyCyclePhaseW
** Parameter[out] 	: None
** Return Value	  	: None
** Note			  	: None
** Description	  	: the function writes PWM parameters to MCS RAM.
**********************************************************************************************************************/
void Gp_06_Pwm3phSetOutput_CddIo
(
	uint8 ui8_Mode,
	uint32 ui32_Freq,
	float32 f32_DutyCyclePhaseU,
	float32 f32_DutyCyclePhaseV,
	float32 f32_DutyCyclePhaseW
)
{
	/*define local variable*/
	uint32 ui32_PwmMode;
	uint32 ui32_PwmPerdTick;
	uint32 ui32_DutyTickU;
	uint32 ui32_DutyTickV;
	uint32 ui32_DutyTickW;

	/*Pwm3ph mode*/
	ui8_Pwm3ph_Mode	= ui8_Mode;
	/*Pwm3ph frequency*/
	ui32_Pwm3ph_Freq = ui32_Freq;

	/*U duty cycle*/
	f32_Pwm3phDutyCyclePhaseU = f32_DutyCyclePhaseU;
	/*V duty cycle*/
	f32_Pwm3phDutyCyclePhaseV = f32_DutyCyclePhaseV;
	/*W duty cycle*/
	f32_Pwm3phDutyCyclePhaseW = f32_DutyCyclePhaseW;

	/*period tick value calculation*/
	if(ui32_Pwm3ph_Freq > UI16_PWM3PH_MAX_FREQ_VALUE)
	{
		ui32_Pwm3ph_Freq = UI16_PWM3PH_MAX_FREQ_VALUE;
	}
	else if(ui32_Pwm3ph_Freq < UI16_PWM3PH_MIN_FREQ_VALUE)
	{
		ui32_Pwm3ph_Freq = UI16_PWM3PH_MIN_FREQ_VALUE;
	}
	else
	{
		/*for MISRA-C*/
	}

	ui32_Pwm3ph_Period_Tick  = UI32_PWM3PH_GTM_CLOCK_VALUE / ui32_Pwm3ph_Freq;

	/*duty cycle tick value calculation*/
	Gp_06_Pwm3ph_UVWDutyToTick(f32_Pwm3phDutyCyclePhaseU, &ui32_Pwm3phU_DutyTick);
	Gp_06_Pwm3ph_UVWDutyToTick(f32_Pwm3phDutyCyclePhaseV, &ui32_Pwm3phV_DutyTick);
	Gp_06_Pwm3ph_UVWDutyToTick(f32_Pwm3phDutyCyclePhaseW, &ui32_Pwm3phW_DutyTick);

	ui32_PwmMode = (uint32)ui8_Pwm3ph_Mode;
	ui32_PwmPerdTick = ui32_Pwm3ph_Period_Tick;
	ui32_DutyTickU = ui32_Pwm3phU_DutyTick;
	ui32_DutyTickV = ui32_Pwm3phV_DutyTick;
	ui32_DutyTickW = ui32_Pwm3phW_DutyTick;

	/*write PWM parameters into MCS0 ram*/
	*PUI32_PWM3PH_MCS0_PWMMODE_ADDR	= ui32_PwmMode;
	*PUI32_PWM3PH_MCS0_PWMPERDTICK_ADDR	= ui32_PwmPerdTick;
	*PUI32_PWM3PH_MCS0_DUTYTICKU_ADDR = ui32_DutyTickU;

	/*write PWM parameters into MCS1 ram*/
	*PUI32_PWM3PH_MCS1_PWMMODE_ADDR	= ui32_PwmMode;
	*PUI32_PWM3PH_MCS1_PWMPERDTICK_ADDR	= ui32_PwmPerdTick;
	*PUI32_PWM3PH_MCS1_DUTYTICKV_ADDR = ui32_DutyTickV;

	/*write PWM parameters into MCS2 ram*/
	*PUI32_PWM3PH_MCS2_PWMMODE_ADDR	= ui32_PwmMode;
	*PUI32_PWM3PH_MCS2_PWMPERDTICK_ADDR	= ui32_PwmPerdTick;
	*PUI32_PWM3PH_MCS2_DUTYTICKW_ADDR = ui32_DutyTickW;

	/*set MCS0 trigger control register to 1:GTM_MCS_x.STRG.B.TRGx*/
	UI32_PWM3PH_REG_MCS0_STRG = 1U;
	UI32_PWM3PH_REG_MCS1_STRG = 1U;
	UI32_PWM3PH_REG_MCS2_STRG = 1U;
}

#define GP_06_PWM3PH_CODE_STOP
#include "Gp_06_Pwm3ph_MemMap.h"
//
#define GP_06_PWM3PH_COMPILER_OPTIMIZE_STOP
#include "Gp_06_Pwm3ph_MemMap.h"

/***********************************************************************************************************************
* $History__:$
* V1.0.0; 0     21.08.2019 WYX
* N: new created
* V1.0.1		23.03.2020 WYX
* add Gp_06_Pwm3ph_PortModeSet function
* V1.0.2		29.07.2025 CZJ
* Adapt MCS
***********************************************************************************************************************/
