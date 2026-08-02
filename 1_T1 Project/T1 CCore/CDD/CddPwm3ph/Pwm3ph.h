/******************************************************************************/
/* FILE NAME: Pwm3ph.h                  							          */
/* VERSION: 1.2.0                                      						  */
/* DESCRIPTION: Three - phase six - channel PWM output drive head file        */
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
/*                                                                            */
/*============================================================================*/
/* HISTORY           	ORIGINAL AUTHOR: lyy                                  */
/* REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                      */
/* ---   -----------  ---------    ---------------------                      */
/* 1.0.0    lyy   24/06/01    Initial version of function.                    */
/* 1.2.0    lyy   25/04/18    Addition of Motor 2 Resource Definition         */
/******************************************************************************/

#ifndef PWM_3PH_H_
#define PWM_3PH_H_


/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Pwm3ph_Cfg.h"


/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/

typedef struct {
	float32 PwmDutyCyclePhaseU1_f32;
	float32 PwmDutyCyclePhaseV1_f32;
	float32 PwmDutyCyclePhaseW1_f32;
	uint16  Pwm_Freq_u16;
	uint8   Pwm_Mode_u8;
} Pwm3phInIFType;

typedef struct {
	uint16 Pwm_Ticks_OnEdge_UH_ui16;
	uint16 Pwm_Ticks_OffEdge_UH_ui16;
	uint16 Pwm_Ticks_OnEdge_UL_ui16;
	uint16 Pwm_Ticks_OffEdge_UL_ui16;
	uint16 Pwm_Ticks_OnEdge_VH_ui16;
	uint16 Pwm_Ticks_OffEdge_VH_ui16;
	uint16 Pwm_Ticks_OnEdge_VL_ui16;
	uint16 Pwm_Ticks_OffEdge_VL_ui16;
	uint16 Pwm_Ticks_OnEdge_WH_ui16;
	uint16 Pwm_Ticks_OffEdge_WH_ui16;
	uint16 Pwm_Ticks_OnEdge_WL_ui16;
	uint16 Pwm_Ticks_OffEdge_WL_ui16;
} Pwm3phOutIFType;
/*******************************************************************************
**                  Global Variables With Extern Linkage               		  **
*******************************************************************************/
// extern	uint8 VAR_Pwm_Mode_u8;
// extern	uint16 VAR_Pwm_Freq_u16;
// extern	float32 VAR_Pwm_DeadTime_In_f32;

// extern	float32 VAR_PwmDutyCyclePhaseU_f32;
// extern	float32 VAR_PwmDutyCyclePhaseV_f32;
// extern	float32 VAR_PwmDutyCyclePhaseW_f32;

// extern	uint16 ui16_Pwm_Fault_Flag_Last;
// extern	uint32 ui32_Pwm_Fault_Counter;
// extern  uint16 ui16_Pwm_Period_Tick;

//float32 CAL_PWM_Set_DeadTime_us_f32 =	 3.4F;	/* Default dead zone time ,2.6Us */
/*******************************************************************************
**                        Global Function Prototypes              	    	  **
*******************************************************************************/
extern void M1_Pwm_3Phases_Init();
extern void M2_Pwm_3Phases_Init();
extern void Pwm_3Phases_Setup();

#if (_CDD_SIMULATION == 0)
extern void M1_Pwm3ph_SetOutput(const Pwm3phInIFType* in);
extern void M2_Pwm3ph_SetOutput(const Pwm3phInIFType* in);
#else
extern void Pwm3ph_SetOutput(const Pwm3phInIFType* in, Pwm3phOutIFType* out );
#endif


/*******************************************************************************
**
*******************************************************************************/
#endif /* PWM_3PH_H_ */
