/******************************************************************************/
/* FILE NAME: PhC_DrvCfg.h                COPYRIGHT (c) FAW            2024   */
/* VERSION: 2.0                                   All Rights Reserved         */
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
/* HISTORY           	ORIGINAL AUTHOR: lyy                                  */
/* REV      AUTHOR      DATE       DESCRIPTION OF CHANGE                      */
/* ---   -----------  ---------    ---------------------                      */
/* 1.0.0    lyy   24/07/09    Initial version of function.
/* 2.0.0	lyy   25/09/01    Define DMA channel and ADC channel related	  */
/* 							  configurations 						     	  */
/******************************************************************************/
#ifndef PHC_DRVCFG_H_
#define PHC_DRVCFG_H_

/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Cdd_CommonCfg.h"


/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/
// #define ADC_HW_TRIGGER_USE_DMA					0U

// #define	ADC_HW_TRIGGER_GTM_MODULE				0U
// #define	ADC_HW_TRIGGER_GTM_CHANNEL_CH0			7U



/* M1 Phase Current ADC&DMA Cfg*/
#define	PHC_GROUP_U_CUR		ADC_GROUP_AdcGroup_Current1_U1_W2
#define	PHC_GROUP_V_CUR		ADC_GROUP_AdcGroup_Current1_V1_U2
#define	PHC_GROUP_W_CUR		ADC_GROUP_AdcGroup_Current1_W1_V2

#define PHC_GROUP_U_CUR_EDMA_CHANNEL_USED	0
#define PHC_GROUP_V_CUR_EDMA_CHANNEL_USED	4
#define PHC_GROUP_W_CUR_EDMA_CHANNEL_USED	16


/* M2 Phase Current ADC&DMA Cfg*/
#define	M2_PHC_GROUP_U_CUR		ADC_GROUP_AdcGroup_Current2_U1_W2
#define	M2_PHC_GROUP_V_CUR		ADC_GROUP_AdcGroup_Current2_V1_U2
#define	M2_PHC_GROUP_W_CUR		ADC_GROUP_AdcGroup_Current2_W1_V2

#define M2_PHC_GROUP_U_CUR_EDMA_CHANNEL_USED	20
#define M2_PHC_GROUP_V_CUR_EDMA_CHANNEL_USED	24
#define M2_PHC_GROUP_W_CUR_EDMA_CHANNEL_USED	28


/* Code Uesd Cfg*/
#define M1_EDMA_DONE_MASK		((1 << PHC_GROUP_U_CUR_EDMA_CHANNEL_USED) | \
							    (1 << PHC_GROUP_V_CUR_EDMA_CHANNEL_USED) | \
							    (1 << PHC_GROUP_W_CUR_EDMA_CHANNEL_USED))

#define M2_EDMA_DONE_MASK		((1 << M2_PHC_GROUP_U_CUR_EDMA_CHANNEL_USED) | \
							    (1 << M2_PHC_GROUP_V_CUR_EDMA_CHANNEL_USED) | \
							    (1 << M2_PHC_GROUP_W_CUR_EDMA_CHANNEL_USED))

/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/




/*******************************************************************************
**                  Global Variables With Extern Linkage               		  **
*******************************************************************************/





/*******************************************************************************
**                        Global Function Prototypes              	    	  **
*******************************************************************************/






#endif


/*******************************************************************************

*******************************************************************************/
