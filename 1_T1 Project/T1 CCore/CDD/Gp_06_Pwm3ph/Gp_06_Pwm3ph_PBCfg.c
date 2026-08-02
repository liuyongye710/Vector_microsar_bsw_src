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
* $Name______: Gp_06_Pwm3ph_PBCfg.c$
* $Variant___: 1.0.2$
* $Revision__: 0$
* $Author____: $
**
**--------------------------------------------------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: No
**--------------------------------------------------------------------------------------------------------------------**
** DESCRIPTION:
** Gp_06_Pwm3ph PBCFG source file
***********************************************************************************************************************/

/***********************************************************************************************************************
**                        				Other Header File Inclusion                    								  **
***********************************************************************************************************************/
#include "Gp_06_Pwm3ph_Cfg.h"

/***********************************************************************************************************************
**                        					  Macro Definition                        								  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                        					 Typedef Definition                        								  **
***********************************************************************************************************************/
#define SEC_CONST_CALPRM_START
#include "Gp_06_Pwm3ph_MemMap.h"

#define SEC_CONST_CALPRM_STOP
#include "Gp_06_Pwm3ph_MemMap.h"


#define GP_06_PWM3PH_CONST_FAR_DATA_START
#include "Gp_06_Pwm3ph_MemMap.h"

volatile uint32 *const ui32_Pwm3ph_OnEdge_REF_SR1 = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_REF_SR1);
volatile uint32 *const ui32_Pwm3ph_OffEdge_REF_SR0  = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_REF_SR0);

volatile uint32 *const ui32_Pwm3ph_OnEdge_UT_SR1 = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_UT_SR1);
volatile uint32 *const ui32_Pwm3ph_OffEdge_UT_SR0  = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_UT_SR0);
volatile uint32 *const ui32_Pwm3ph_OnEdge_UB_SR0  = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_UB_SR0);
volatile uint32 *const ui32_Pwm3ph_OffEdge_UB_SR1 = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_UB_SR1);

volatile uint32 *const ui32_Pwm3ph_OnEdge_VT_SR1 = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_VT_SR1);
volatile uint32 *const ui32_Pwm3ph_OffEdge_VT_SR0  = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_VT_SR0);
volatile uint32 *const ui32_Pwm3ph_OnEdge_VB_SR0  = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_VB_SR0);
volatile uint32 *const ui32_Pwm3ph_OffEdge_VB_SR1 = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_VB_SR1);

volatile uint32 *const ui32_Pwm3ph_OnEdge_WT_SR1 = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_WT_SR1);
volatile uint32 *const ui32_Pwm3ph_OffEdge_WT_SR0  = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_WT_SR0);
volatile uint32 *const ui32_Pwm3ph_OnEdge_WB_SR0  = (volatile uint32*)(& UI16_PWM3PH_ONEDGE_WB_SR0);
volatile uint32 *const ui32_Pwm3ph_OffEdge_WB_SR1 = (volatile uint32*)(& UI16_PWM3PH_OFFEDGE_WB_SR1);

#define GP_06_PWM3PH_CONST_FAR_DATA_STOP
#include "Gp_06_Pwm3ph_MemMap.h"

/***********************************************************************************************************************
**                   					Static Local Variables Definition    						          		  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                  					   Global Variables Definition            						  		      **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                						Static Local Function Declaration    					        		      **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                 							  Function Source Code          					  		              **
***********************************************************************************************************************/


/***********************************************************************************************************************
* $History__:$
* V1.0.0; 0     21.08.2019 WYX
* N: new created
* V1.0.1		23.03.2020 WYX
* add Gp_06_Pwm3ph_PortModeSet function
* V1.0.2		07.08.2025 CZJ
* Adapt MCS
***********************************************************************************************************************/

