/******************************************************************************/
/* FILE NAME: XXXX.h                 COPYRIGHT (c) FAW            2024        */
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
/* 1.0.0    Lyy   24/01/01    Initial version of function.                    */
/******************************************************************************/


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "IoHwAb.h"
#include "Cdd_Common.h"
/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                  Global Variables With Extern Linkage               		  **
*******************************************************************************/


/*******************************************************************************
**                        Global Function Prototypes              	    	  **
*******************************************************************************/
extern FaultCounter ISR_ERR_status;
extern FaultFlags ISR_ERR_Flags;
extern StmMeasInfo isrExcutionTime;
extern StmMeasInfo isrASWExcutionTime;



#endif 



/*******************************************************************************
*
*******************************************************************************/
