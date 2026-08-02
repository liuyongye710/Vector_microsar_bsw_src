/***********************************************************************************************************************
**--------------------------------------------------------------------------------------------------------------------**
** Copyright (c) 2019 by G-Pulse.		All rights reserved.
** This software is copyright protected and proprietary to G-Pulse.
** G-Pulse grants to you only those rights as set out in the license conditions.
** All other rights remain with G-Pulse.
**--------------------------------------------------------------------------------------------------------------------**
**
* Administrative Information
* $Namespace_: ..\ Gp_06_Pwm3ph$
* $Class_____: C$
* $Name______: Gp_06_Pwm3ph_Cfg.h$
* $Variant___: 1.0.2$
* $Revision__: 0$
* $Author____: CaoZijian$
**
**--------------------------------------------------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: Yes
**--------------------------------------------------------------------------------------------------------------------**
** DESCRIPTION:
** Gp_06_Pwm3ph CFG header file
***********************************************************************************************************************/

#ifndef GP_06_PWM3PH_CFG_H_
#define GP_06_PWM3PH_CFG_H_

/***********************************************************************************************************************
**                        				Other Header File Inclusion                    								  **
***********************************************************************************************************************/

#include "Gp_06_Pwm3ph_Types.h"
#include "Gp_GtmCCFC.h"
#include "StandardTypes.h"
#include "Port.h"

/***********************************************************************************************************************
**                        				Macro Definition             					            		  		  **
***********************************************************************************************************************/
#define UI32_PWM3PH_GTM_CLOCK_VALUE		    	((uint32)80000000U)			/*GTM clock frequency:Hz*/

#define UI32_PWM3PH_ATOM0_ADDR					((uint32)0xFFD0D000U)		/*ATOM0 base address*/
#define UI32_PWM3PH_MODULE_OFFSET				((uint32)0x00000800U)		/*module offset*/

#define	UI32_PWM3PH_REG_MCS0_STRG				(*(uint32*)0xFFD3002C)		/*MCS0 STRG register*/
#define	UI32_PWM3PH_REG_MCS1_STRG				(*(uint32*)0xFFD3102C)		/*MCS1 STRG register*/
#define	UI32_PWM3PH_REG_MCS2_STRG				(*(uint32*)0xFFD3202C)		/*MCS2 STRG register*/

#define UI16_PWM3PH_MAX_FREQ_VALUE		 		((uint16)10000U)			/*maximum frequency*/
#define UI16_PWM3PH_MIN_FREQ_VALUE		 		((uint16)1000U)				/*minimum frequency*/
#define UI16_PWM3PH_DEF_FREQ_VALUE		 		((uint16)10000U)			/*default frequency*/

#define	F32_PWM3PH_MAX_DUTY_VALUE				((float32)1.0F)				/*maximum duty cycle*/
#define	F32_PWM3PH_MIN_DUTY_VALUE				((float32)0.0F)				/*minimum duty cycle*/

#define F32_PWM3PH_DEF_DEADTIME					(3.2e-6F)					/*default dead time, 3.2Us*/

#define UI8_PWM3PH_ATOMMODULE_REF		    	((uint8)1U)					/*reference channel ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_REF					((uint8)0U)					/*reference channel ATOM channel ID*/

#define UI8_PWM3PH_ATOMMOUDLE_UT		    	((uint8)1U)					/*UT ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_UT					((uint8)1U)					/*UT channel ATOM channel ID*/
#define UI8_PWM3PH_ATOMMOUDLE_UB		    	((uint8)1U)					/*UB ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_UB					((uint8)2U)					/*UB channel ATOM channel ID*/

#define UI8_PWM3PH_ATOMMOUDLE_VT		    	((uint8)1U)					/*UT ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_VT					((uint8)3U)					/*UT channel ATOM channel ID*/
#define UI8_PWM3PH_ATOMMOUDLE_VB		    	((uint8)1U)					/*UB ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_VB					((uint8)4U)					/*UB channel ATOM channel ID*/

#define UI8_PWM3PH_ATOMMOUDLE_WT		    	((uint8)1U)					/*UT ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_WT					((uint8)5U)					/*UT channel ATOM channel ID*/
#define UI8_PWM3PH_ATOMMOUDLE_WB		    	((uint8)1U)					/*UB ATOM module ID*/
#define UI8_PWM3PH_ATOMCHL_WB					((uint8)6U)					/*UB channel ATOM channel ID*/

/*GPIO Configuration*/
#define UI32_PWM3PH_CFG_REF_GPIO                (PWM_triADC)				/*PH[10] 1010b(10)*/
#define UI32_PWM3PH_CFG_UT_GPIO                 (PWM_UH)				/*PH[04] 1010b(10)*/
#define UI32_PWM3PH_CFG_UB_GPIO                 (PWM_UL)				/*PF[05] 1010b(10)*/
#define UI32_PWM3PH_CFG_VT_GPIO                 (PWM_VH)				/*PH[11] 1011b(11)*/
#define UI32_PWM3PH_CFG_VB_GPIO                 (PWM_VL)				/*PF[15] 1011b(11)*/
#define UI32_PWM3PH_CFG_WT_GPIO                 (PWM_WH)				/*PH[12] 1010b(10)*/
#define UI32_PWM3PH_CFG_WB_GPIO                 (PWM_WL)				/*PF[08] 1011b(11)*/
/*PIN alternate mode*/
#define UI32_PWM3PH_CFG_REF_ALTMOD              (PORT_ALT10_FUNC_MODE)		/*PH[10] 1010b(10)*/
#define UI32_PWM3PH_CFG_UT_ALTMOD               (PORT_ALT10_FUNC_MODE)		/*PH[04] 1010b(10)*/
#define UI32_PWM3PH_CFG_UB_ALTMOD               (PORT_ALT10_FUNC_MODE)		/*PF[05] 1010b(10)*/
#define UI32_PWM3PH_CFG_VT_ALTMOD               (PORT_ALT11_FUNC_MODE)		/*PH[11] 1011b(11)*/
#define UI32_PWM3PH_CFG_VB_ALTMOD               (PORT_ALT11_FUNC_MODE)		/*PF[15] 1011b(11)*/
#define UI32_PWM3PH_CFG_WT_ALTMOD               (PORT_ALT10_FUNC_MODE)		/*PH[12] 1010b(10)*/
#define UI32_PWM3PH_CFG_WB_ALTMOD               (PORT_ALT11_FUNC_MODE)		/*PF[08] 1011b(11)*/

/*ATOM SRx map*/
#define UI16_PWM3PH_ONEDGE_REF_SR1      		GTM_ATOM_1.CH0_SR1.R
#define UI16_PWM3PH_OFFEDGE_REF_SR0       		GTM_ATOM_1.CH0_SR0.R

#define UI16_PWM3PH_ONEDGE_UT_SR1      			GTM_ATOM_1.CH1_SR1.R
#define UI16_PWM3PH_OFFEDGE_UT_SR0       		GTM_ATOM_1.CH1_SR0.R
#define UI16_PWM3PH_OFFEDGE_UB_SR1       		GTM_ATOM_1.CH2_SR1.R
#define UI16_PWM3PH_ONEDGE_UB_SR0      	    	GTM_ATOM_1.CH2_SR0.R

#define UI16_PWM3PH_ONEDGE_VT_SR1      	    	GTM_ATOM_1.CH3_SR1.R
#define UI16_PWM3PH_OFFEDGE_VT_SR0       		GTM_ATOM_1.CH3_SR0.R
#define UI16_PWM3PH_OFFEDGE_VB_SR1       		GTM_ATOM_1.CH4_SR1.R
#define UI16_PWM3PH_ONEDGE_VB_SR0       		GTM_ATOM_1.CH4_SR0.R

#define UI16_PWM3PH_ONEDGE_WT_SR1      	    	GTM_ATOM_1.CH5_SR1.R
#define UI16_PWM3PH_OFFEDGE_WT_SR0       		GTM_ATOM_1.CH5_SR0.R
#define UI16_PWM3PH_OFFEDGE_WB_SR1       		GTM_ATOM_1.CH6_SR1.R
#define UI16_PWM3PH_ONEDGE_WB_SR0      			GTM_ATOM_1.CH6_SR0.R

/*MCS00 variable address*/
/*base address(0xFFD38000) + map offset*/
#define PUI32_PWM3PH_MCS0_CHL0CNT0_ADDR 		((uint32*)0xFFD3802CU)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt0 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT1_ADDR 		((uint32*)0xFFD38030U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt1 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT2_ADDR 		((uint32*)0xFFD38034U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt2 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT3_ADDR 		((uint32*)0xFFD38038U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt3 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT4_ADDR 		((uint32*)0xFFD3803CU)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt4 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT5_ADDR 		((uint32*)0xFFD38040U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt5 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT6_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt6 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT7_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt7 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT8_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt8 address*/
#define PUI32_PWM3PH_MCS0_CHL0CNT9_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt9 address*/

#define PUI32_PWM3PH_MCS0_TIMESTAMP0_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeStamp0 address*/
#define PUI32_PWM3PH_MCS0_TIMESTAMP1_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeStamp1 address*/
#define PUI32_PWM3PH_MCS0_TIMESTAMP2_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeStamp2 address*/

#define PUI32_PWM3PH_MCS0_TIMEINTL0_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeIntl0 address*/
#define PUI32_PWM3PH_MCS0_TIMEINTL1_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeIntl1 address*/
#define PUI32_PWM3PH_MCS0_TIMEINTL2_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeIntl2 address*/

#define PUI32_PWM3PH_MCS0_PWMMODE_ADDR 			((uint32*)0xFFD38044U)		/*variable ui32_Pwm3ph_Mcs_Mod address*/
#define PUI32_PWM3PH_MCS0_PWMPERDTICK_ADDR 		((uint32*)0xFFD38048U)		/*variable ui32_Pwm3ph_Mcs_PerdTick address*/
#define PUI32_PWM3PH_MCS0_DEADTIMETICK_ADDR 	((uint32*)0xFFD3804CU)		/*variable ui32_Pwm3ph_Mcs_DeadTimeTick address*/
#define PUI32_PWM3PH_MCS0_DUTYTICKU_ADDR 		((uint32*)0xFFD38050U)		/*variable ui32_Pwm3ph_Mcs_DutyTickU address*/

/*MCS01 variable address*/
/*base address(0xFFD40000) + map offset*/
#define PUI32_PWM3PH_MCS1_CHL0CNT0_ADDR 		((uint32*)0xFFD40024U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt0 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT1_ADDR 		((uint32*)0xFFD40028U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt1 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT2_ADDR 		((uint32*)0xFFD4002CU)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt2 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT3_ADDR 		((uint32*)0xFFD40030U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt3 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT4_ADDR 		((uint32*)0xFFD40034U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt4 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT5_ADDR 		((uint32*)0xFFD40038U)		/*variable ui32_Pwm3ph_Mcs_Chl0Cnt5 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT6_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt6 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT7_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt7 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT8_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt8 address*/
#define PUI32_PWM3PH_MCS1_CHL0CNT9_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_Chl0Cnt9 address*/

#define PUI32_PWM3PH_MCS1_TIMESTAMP0_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeStamp0 address*/
#define PUI32_PWM3PH_MCS1_TIMESTAMP1_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeStamp1 address*/
#define PUI32_PWM3PH_MCS1_TIMESTAMP2_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeStamp2 address*/

#define PUI32_PWM3PH_MCS1_TIMEINTL0_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeIntl0 address*/
#define PUI32_PWM3PH_MCS1_TIMEINTL1_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeIntl1 address*/
#define PUI32_PWM3PH_MCS1_TIMEINTL2_ADDR 		((uint32*)0x0U)				/*variable ui32_Pwm3ph_Mcs_TimeIntl2 address*/

#define PUI32_PWM3PH_MCS1_PWMMODE_ADDR 			((uint32*)0xFFD4003CU)		/*variable ui32_Pwm3ph_Mcs_Mod address*/
#define PUI32_PWM3PH_MCS1_PWMPERDTICK_ADDR 		((uint32*)0xFFD40040U)		/*variable ui32_Pwm3ph_Mcs_PerdTick address*/
#define PUI32_PWM3PH_MCS1_DEADTIMETICK_ADDR 	((uint32*)0xFFD40044U)		/*variable ui32_Pwm3ph_Mcs_DeadTimeTick address*/
#define PUI32_PWM3PH_MCS1_DUTYTICKV_ADDR 		((uint32*)0xFFD4004CU)		/*variable ui32_Pwm3ph_Mcs_DutyTickV address*/

/*MCS02 variable address*/
/*base address(0xFFD48000) + map offset*/
#define PUI32_PWM3PH_MCS2_CHL0CNT0_ADDR     	((uint32*)0xFFD48024U)	    /*variable ui32_Pwm3ph_Mcs_Chl0Cnt0 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT1_ADDR     	((uint32*)0xFFD48028U)	    /*variable ui32_Pwm3ph_Mcs_Chl0Cnt1 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT2_ADDR     	((uint32*)0xFFD4802CU)	    /*variable ui32_Pwm3ph_Mcs_Chl0Cnt2 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT3_ADDR     	((uint32*)0xFFD48030U)	    /*variable ui32_Pwm3ph_Mcs_Chl0Cnt3 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT4_ADDR     	((uint32*)0xFFD48034U)	    /*variable ui32_Pwm3ph_Mcs_Chl0Cnt4 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT5_ADDR     	((uint32*)0xFFD48038U)	    /*variable ui32_Pwm3ph_Mcs_Chl0Cnt5 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT6_ADDR     	((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_Chl0Cnt6 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT7_ADDR     	((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_Chl0Cnt7 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT8_ADDR     	((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_Chl0Cnt8 address*/
#define PUI32_PWM3PH_MCS2_CHL0CNT9_ADDR     	((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_Chl0Cnt9 address*/

#define PUI32_PWM3PH_MCS2_TIMESTAMP0_ADDR 	    ((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_TimeStamp0 address*/
#define PUI32_PWM3PH_MCS2_TIMESTAMP1_ADDR 	    ((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_TimeStamp1 address*/
#define PUI32_PWM3PH_MCS2_TIMESTAMP2_ADDR 	    ((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_TimeStamp2 address*/

#define PUI32_PWM3PH_MCS2_TIMEINTL0_ADDR 	    ((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_TimeIntl0 address*/
#define PUI32_PWM3PH_MCS2_TIMEINTL1_ADDR 	    ((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_TimeIntl1 address*/
#define PUI32_PWM3PH_MCS2_TIMEINTL2_ADDR 	    ((uint32*)0x0U)	            /*variable ui32_Pwm3ph_Mcs_TimeIntl2 address*/

#define PUI32_PWM3PH_MCS2_PWMMODE_ADDR 	        ((uint32*)0xFFD4803CU)	    /*variable ui32_Pwm3ph_Mcs_Mod address*/
#define PUI32_PWM3PH_MCS2_PWMPERDTICK_ADDR 	    ((uint32*)0xFFD48040U)	    /*variable ui32_Pwm3ph_Mcs_PerdTick address*/
#define PUI32_PWM3PH_MCS2_DEADTIMETICK_ADDR 	((uint32*)0xFFD48044U)	    /*variable ui32_Pwm3ph_Mcs_DeadTimeTick address*/
#define PUI32_PWM3PH_MCS2_DUTYTICKW_ADDR 	    ((uint32*)0xFFD48050U)	    /*variable ui32_Pwm3ph_Mcs_DutyTickW address*/

/**********************************************************************************************************************/
#define SEC_CONST_CALPRM_START
#include "Gp_06_Pwm3ph_MemMap.h"


#define SEC_CONST_CALPRM_STOP
#include "Gp_06_Pwm3ph_MemMap.h"

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_UT_SR1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_UT_SR0;
extern volatile uint32 *const ui32_Pwm3ph_OnEdge_UB_SR0;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_UB_SR1;

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_VT_SR1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_VT_SR0;
extern volatile uint32 *const ui32_Pwm3ph_OnEdge_VB_SR0;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_VB_SR1;

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_WT_SR1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_WT_SR0;
extern volatile uint32 *const ui32_Pwm3ph_OnEdge_WB_SR0;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_WB_SR1;

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_REF_SR1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_REF_SR0;

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_UT_CM1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_UT_CM0;
extern volatile uint32 *const ui32_Pwm3ph_OnEdge_UB_CM0;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_UB_CM1;

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_VT_CM1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_VT_CM0;
extern volatile uint32 *const ui32_Pwm3ph_OnEdge_VB_CM0;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_VB_CM1;

extern volatile uint32 *const ui32_Pwm3ph_OnEdge_WT_CM1;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_WT_CM0;
extern volatile uint32 *const ui32_Pwm3ph_OnEdge_WB_CM0;
extern volatile uint32 *const ui32_Pwm3ph_OffEdge_WB_CM1;

/***********************************************************************************************************************
**                        				Typedef Definition 	 	                      								  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                        				Global Variables With Extern Linkage                			  		  	  **
***********************************************************************************************************************/


/***********************************************************************************************************************
**                 						Global Function Prototypes          					  		              **
***********************************************************************************************************************/


#endif /*GP_06_PWM3PH_CFG_H_*/

/***********************************************************************************************************************
* $History__:$
* V1.0.0; 0     21.08.2019 WYX
* N: new created
* V1.0.1		23.03.2020 WYX
* add Gp_06_Pwm3ph_PortModeSet function
* V1.0.2		07.08.2025 CZJ
* Adapt MCS
***********************************************************************************************************************/


