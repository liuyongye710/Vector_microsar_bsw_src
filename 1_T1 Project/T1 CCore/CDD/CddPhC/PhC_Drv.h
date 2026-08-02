/******************************************************************************/
/* FILE NAME: PhC_Drv.h                 COPYRIGHT (c) FAW            2024     */
/* VERSION: 1.0                                   All Rights Reserved         */
/* DESCRIPTION: XXXXXXXXXX										              */
/* -------------------------------------------------------------------------- */
/*   C O P Y R I G H T                                                        */
/* ---------------------------------------------------------------------------*/
/*   Copyright (c) 2024 by FAW. All rights reserved.                          */
/*                                                                            */
/*   This software is copyright protected and proprietary to FAW.             */
/*   FAW grants to you only those rights as set out in the license            */
/*   conditions.                                                              */
/*   All other rights remain with FAW.                                        */
/*                                                                            */
/*                                                                            */
/*   REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE COPYRIGHT AGREEMENT.     */
/*                                                                            */
/*============================================================================*/
/* HISTORY           	ORIGINAL AUTHOR: Lyy                                  */
/* REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                      */
/* ---   -----------  ---------    ---------------------                      */
/* 1.0.0    Lyy   24/07/09    Initial version of function.                    */
/******************************************************************************/


#ifndef PHC_DRV_H_
#define PHC_DRV_H_

/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Phc_DrvCfg.h"
#include "Adc.h"
/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/
typedef struct {
	uint16 iUNoOff;
	uint16 iVNoOff;
	uint16 iWNoOff;
} PhCOutIFType;

typedef struct {
	uint8 ADC_UPhaseBISTcnt;
	uint8 ADC_UPhaseBISTerrcnt;
	uint8 ADC_VPhaseBISTcnt;
	uint8 ADC_VPhaseBISTerrcnt;
	uint8 ADC_WPhaseBISTcnt;
	uint8 ADC_WPhaseBISTerrcnt;
}PhCDiagType;
/*******************************************************************************
**                  Global Variables With Extern Linkage               		  **
*******************************************************************************/
/*ADC Result Buffers */

extern	Adc_ValueGroupType VAR_Adc_RES_Buffer_CUR_MCU_u16[9U];

/*******************************************************************************
**                        Global Function Prototypes              	    	  **
*******************************************************************************/
extern void Adc_InitOperationMode_Core0();
extern void Adc_InitOperationMode_Core1();

extern void Adc_RegTrigConversion_Core0(uint64 ExtCount,uint64 ReEntryCnt);
extern void Adc_RegTrigConversion_Core1(uint64 ExtCount,uint64 ReEntryCnt);

extern	void M1_PhC_Init(void);
extern	void M2_PhC_Init(void);

#if(ADC_HW_TRIGGER_USE_DMA == 0U) /*not use DMA*/
/*******************************************************************************
** Function Name	: PhC_GetResult_MCUHwAdc
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note	  			: PWM interrupt/ADC finish the Notification function call
** Description	  	: GP ADC get three-phase current ADC data
*******************************************************************************/
extern	void M1_PhC_GetResult_MCUHwAdc(PhCOutIFType *out);
extern	void M2_PhC_GetResult_MCUHwAdc(PhCOutIFType *out);
#endif



/*******************************************************************************
*
*******************************************************************************/
#endif
