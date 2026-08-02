/******************************************************************************/
/* FILE NAME: PhC_Drv.c                                                       */
/* VERSION: 2.0                                                               */
/* DESCRIPTION: Three-phase current sampling and diagnostic function          */
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
/*   REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE COPYRIGHT AGREEMENT.     */
/*============================================================================*/
/* HISTORY           	ORIGINAL AUTHOR: lyy                                  */
/* REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                      */
/* ---   -----------  ---------    ---------------------                      */
/* 1.0.0    lyy   24/07/09    Initial version of function.                    */
/* 1.0.1    lyy   24/12/23    Added functions to use DMA to carry ADC results */
/*         					  on the 3007 platform.                           */
/* 1.1.0    lyy   24/12/25    Support switching between CCFC3007 and TC397 chi*/
/*	                          -p platform.
/* 2.0.0	lyy   25/09/01    Using the DMA INTL register for three-phase current
/* 							  acquisition synchronization,and clear the INTL flag
/* 							  using CDNE and CINT. 							  */
/******************************************************************************/



/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "PhC_Drv.h"

#if defined(CHIP_PLATFORM_TC397)
	#include "Gtm.h"
	#include "IfxSrc_reg.h"
	#include "IfxEvadc_reg.h"
	#include "IfxEvadc_regdef.h"
	#include "Dem.h"
#elif defined(CHIP_PLATFORM_CCFC3007PT)
	#include "Adc_Cfg.h"
	#include "eDma_LLDriver.h"
	#include"IoHwAb.h"
#endif



#if defined(CHIP_PLATFORM_TC397)

#elif defined(CHIP_PLATFORM_CCFC3007PT)

#endif
/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                   Static Local Variables Definition              		  **
*******************************************************************************/


/*******************************************************************************
**                     Global Variables Definition              		      **
*******************************************************************************/
#define FAW_CORE0_DMEM0_VALUE_START
#include "FAW_MemMap.h"
/*HW ADC Result Buffers */
#if defined(CHIP_PLATFORM_TC397)
	Adc_ValueGroupType VAR_Adc_RES_Buffer_CUR_MCU_u16[9U];
#elif defined(CHIP_PLATFORM_CCFC3007PT)
	Adc_ValueGroupType VAR_Adc_Res_U[2];
	Adc_ValueGroupType VAR_Adc_Res_V[2];
	Adc_ValueGroupType VAR_Adc_Res_W[2];
	DMA_Type* pM1_eDMA = (DMA_Type*)0XFC0A0000;
	volatile uint32 M1_PhcConvCnt;

	volatile int eint0;
	volatile int eint4;
	volatile int eint16;

#endif
#define FAW_CORE0_DMEM0_VALUE_STOP
#include "FAW_MemMap.h"

#define FAW_CORE1_DMEM1_VALUE_START
#include "FAW_MemMap.h"
	Adc_ValueGroupType M2_VAR_Adc_Res_U[2];
	Adc_ValueGroupType M2_VAR_Adc_Res_V[2];
	Adc_ValueGroupType M2_VAR_Adc_Res_W[2];
	DMA_Type* pM2_eDMA =(DMA_Type*)0XFC0A0000;
	volatile uint32 M2_PhcConvCnt;

	volatile int eint20;
	volatile int eint24;
	volatile int eint28;

#define FAW_CORE1_DMEM1_VALUE_STOP
#include "FAW_MemMap.h"
/*******************************************************************************
**                  Static Local Function Declaration            		      **
*******************************************************************************/


/*******************************************************************************
**                 		  Function Source Code            		              **
*******************************************************************************/

/*******************************************************************************
** Function Name	: PhC_Init
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note	  			: None
** Description	  	: GP ADC initialize
*******************************************************************************/
void M1_PhC_Init(void)
{

#if defined(CHIP_PLATFORM_TC397)

	Adc_SetupResultBuffer(PHC_GROUP_U_CUR,&VAR_Adc_RES_Buffer_CUR_MCU_u16[0U]);/*Setup*/
	Adc_EnableHardwareTrigger(PHC_GROUP_U_CUR);
	Adc_EnableGroupNotification(PHC_GROUP_U_CUR);/*enable notification program*/
#elif defined(CHIP_PLATFORM_CCFC3007PT)
	#if(TEST_USE_MCAL == 1U )
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH1_IRQ54, ADC0DMACH1_Prio);// EQADC01_RFIFO0
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH3_IRQ56, ADC1DMACH3_Prio);// EQADC01_RFIFO1
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH16_IRQ69, ADC2DMACH16_Prio);// EQADC23_RFIFO0

	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH1_IRQ54, &EDMA_Ch1_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH3_IRQ56, &EDMA_Ch3_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH16_IRQ69, &EDMA_Ch16_IRQHandler);

	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH1_IRQ54);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH3_IRQ56);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH16_IRQ69);
	#endif
	/*three phase current*/
	Adc_SetupResultBuffer(PHC_GROUP_U_CUR,VAR_Adc_Res_U);
	Adc_SetupResultBuffer(PHC_GROUP_V_CUR,VAR_Adc_Res_V);
	Adc_SetupResultBuffer(PHC_GROUP_W_CUR,VAR_Adc_Res_W);

	Adc_EnableHardwareTrigger(PHC_GROUP_U_CUR);
	Adc_EnableHardwareTrigger(PHC_GROUP_V_CUR);
	Adc_EnableHardwareTrigger(PHC_GROUP_W_CUR);

#endif

}

void M2_PhC_Init(void)
{
	Adc_SetupResultBuffer(M2_PHC_GROUP_U_CUR,M2_VAR_Adc_Res_U);
	Adc_SetupResultBuffer(M2_PHC_GROUP_V_CUR,M2_VAR_Adc_Res_V);
	Adc_SetupResultBuffer(M2_PHC_GROUP_W_CUR,M2_VAR_Adc_Res_W);
	Adc_EnableHardwareTrigger(M2_PHC_GROUP_U_CUR);
	Adc_EnableHardwareTrigger(M2_PHC_GROUP_V_CUR);
	Adc_EnableHardwareTrigger(M2_PHC_GROUP_W_CUR);
}
/*******************************************************************************
** Function Name	: PhC_GetResult_MCUHwAdc
** Parameter[in] 	: None
** Parameter[out] 	: None
** Return Value	  	: None
** Note	  			: PWM interrupt/ADC finish the Notification function call
** Description	  	: GP ADC get three-phase current ADC data
*******************************************************************************/
#define FAW_CORE0_IMEM0_CODE_START
#include "FAW_MemMap.h"

void M1_PhC_GetResult_MCUHwAdc(PhCOutIFType *out)
{

#if defined(CHIP_PLATFORM_TC397)
	 Adc_StatusType Adc_Status;
	 Adc_Status = Adc_GetGroupStatus(PHC_GROUP_U_CUR);

	 if((Adc_Status == ADC_COMPLETED) || (Adc_Status == ADC_STREAM_COMPLETED))
	 {
		Adc_ReadGroup(PHC_GROUP_U_CUR,&VAR_Adc_RES_Buffer_CUR_MCU_u16[0U]);
	 }

	out->iUNoOff = VAR_Adc_RES_Buffer_CUR_MCU_u16[0U];
	out->iVNoOff = VAR_Adc_RES_Buffer_CUR_MCU_u16[1U];
	out->iWNoOff = VAR_Adc_RES_Buffer_CUR_MCU_u16[2U];

#elif defined(CHIP_PLATFORM_CCFC3007PT)

	while(((pM1_eDMA->INTL.R)& M1_EDMA_DONE_MASK ) != M1_EDMA_DONE_MASK )
	{
		eint0=pM1_eDMA->INTL.B.INT0;
		eint4=pM1_eDMA->INTL.B.INT4;
		eint16=pM1_eDMA->INTL.B.INT16;
		M1_PhcConvCnt++;
	}
  
	out->iUNoOff = VAR_Adc_Res_U[0U]/4;
	out->iVNoOff = VAR_Adc_Res_V[0U]/4;
	out->iWNoOff = VAR_Adc_Res_W[0U]/4;

	pM1_eDMA->CDNE.R = PHC_GROUP_U_CUR_EDMA_CHANNEL_USED;
	pM1_eDMA->CINT.R = PHC_GROUP_U_CUR_EDMA_CHANNEL_USED;

	pM1_eDMA->CDNE.R = PHC_GROUP_V_CUR_EDMA_CHANNEL_USED;
	pM1_eDMA->CINT.R = PHC_GROUP_V_CUR_EDMA_CHANNEL_USED;

	pM1_eDMA->CDNE.R = PHC_GROUP_W_CUR_EDMA_CHANNEL_USED;
	pM1_eDMA->CINT.R = PHC_GROUP_W_CUR_EDMA_CHANNEL_USED;
#endif
}


void Adc_RegTrigConversion_Core0(uint64 ExtCount,uint64 ReEntryCnt)
{
	if(ExtCount - ((ExtCount >> ReEntryCnt) << ReEntryCnt) ==0 )
	{
		EQADC0_PTR->CFCR0.B.SSE1 = 1;
		EQADC0_PTR->CFCR1.B.SSE3 = 1;
		EQADC1_PTR->CFCR0.B.SSE1 = 1;
	}
}
#define FAW_CORE0_IMEM0_CODE_STOP
#include "FAW_MemMap.h"

void Adc_InitOperationMode_Core0()
{
	Adc_EnableHardwareTrigger(1);
	Adc_EnableHardwareTrigger(3);
	Adc_EnableHardwareTrigger(5);

	EQADC0_PTR->CFCR0.B.MODE1 =1;
	EQADC0_PTR->CFCR1.B.MODE3 =1;
	EQADC1_PTR->CFCR0.B.MODE1 =1;
}
#define FAW_CORE1_IMEM1_CODE_START
#include "FAW_MemMap.h"

void M2_PhC_GetResult_MCUHwAdc(PhCOutIFType *out)
{
	while(((pM2_eDMA->INTL.R)& M2_EDMA_DONE_MASK) != M2_EDMA_DONE_MASK )
	{
//		eint20=pM2_eDMA->INTL.B.INT20;
//		eint24=pM2_eDMA->INTL.B.INT24;
//		eint28=pM2_eDMA->INTL.B.INT28;
		M2_PhcConvCnt++;
	}
 
	out->iUNoOff = M2_VAR_Adc_Res_U[0U]/4;
	out->iVNoOff = M2_VAR_Adc_Res_V[0U]/4;
	out->iWNoOff = M2_VAR_Adc_Res_W[0U]/4;

	pM2_eDMA->CDNE.R = M2_PHC_GROUP_U_CUR_EDMA_CHANNEL_USED;
	pM2_eDMA->CINT.R = M2_PHC_GROUP_U_CUR_EDMA_CHANNEL_USED;

	pM2_eDMA->CDNE.R = M2_PHC_GROUP_V_CUR_EDMA_CHANNEL_USED;
	pM2_eDMA->CINT.R = M2_PHC_GROUP_V_CUR_EDMA_CHANNEL_USED;

	pM2_eDMA->CDNE.R = M2_PHC_GROUP_W_CUR_EDMA_CHANNEL_USED;
	pM2_eDMA->CINT.R = M2_PHC_GROUP_W_CUR_EDMA_CHANNEL_USED;
}



void Adc_RegTrigConversion_Core1(uint64 ExtCount,uint64 ReEntryCnt)
{
	if(ExtCount - ((ExtCount >> ReEntryCnt) << ReEntryCnt) ==0 )
	{
		EQADC1_PTR->CFCR1.B.SSE3 =1;
		EQADC2_PTR->CFCR0.B.SSE1 =1;
		EQADC2_PTR->CFCR1.B.SSE3 =1;
	}
}
#define FAW_CORE1_IMEM1_CODE_STOP
#include "FAW_MemMap.h"

void Adc_InitOperationMode_Core1()
{
	Adc_EnableHardwareTrigger(7);
	Adc_EnableHardwareTrigger(9);
	Adc_EnableHardwareTrigger(11);

	EQADC1_PTR->CFCR1.B.MODE3 =1;
	EQADC2_PTR->CFCR0.B.MODE1 =1;
	EQADC2_PTR->CFCR1.B.MODE3 =1;
}

/*******************************************************************************

*******************************************************************************/
