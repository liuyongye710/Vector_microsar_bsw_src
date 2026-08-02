/***********************************************************************************************************************
**--------------------------------------------------------------------------------------------------------------------**
** Copyright (c) 2025 by G-Pulse.		All rights reserved.
** This software is copyright protected and proprietary to G-Pulse.
** G-Pulse grants to you only those rights as set out in the license conditions.
** All other rights remain with G-Pulse.
**--------------------------------------------------------------------------------------------------------------------**
**
* Administrative Information
* $Namespace_: ..\ Gp_GtmCCFC$
* $Class_____: C$
* $Name______: Gp_GtmCCFC_Cfg.h$
* $ArchiVer__: 1$
* $FcVeri____: 1.0.0$
* $Author____: CaoZijian$
*
* $Configuration or generate Date,Time: 11:19 07.08.2025 $
*
**--------------------------------------------------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: Yes
**--------------------------------------------------------------------------------------------------------------------**
** DESCRIPTION:
**
** Gp_GtmCCFC CFG header file
**
***********************************************************************************************************************/
#ifndef GP_GTMCCFC_CFG_H_
#define GP_GTMCCFC_CFG_H_

/***********************************************************************************************************************
**										Other Header File Inclusion													  **
***********************************************************************************************************************/
#include "CCFC3007PT.h"
#include "StandardTypes.h"
#include "common.h"
#include "Mcal.h"
#include "Mcu.h"
#include "intc_lld.h"
#include "Gpt_Irq.h"

/***********************************************************************************************************************
**                        				Macro Definition                        								      **
***********************************************************************************************************************/
/*MCS Scheduling mode configuration*/
/*CCFC3007: 0:accelerated schedule;1:round-robin schedule*/
#define GP_GTMCCFC_CFG_MCSMOD_REG					(0U)

/*number of MCS*/
#define GP_GTMCCFC_MCSNUM 							(4U)

/*MCS00 driver block SIZE*/
#define GP_GTMCCFC_CFG_MCS00_DRVBLK_SIZE			(0xFDU)
/*MCS00 driver RAM SIZE*/
#define GP_GTMCCFC_MCS00_MEM_SIZE					(0x1000U)
/*MCS00 RAM address*/
#define GP_GTMCCFC_MCS00_RAM_ADDR					(0xFFD38000U)

/*MCS01 driver block SIZE*/
#define GP_GTMCCFC_CFG_MCS01_DRVBLK_SIZE			(0xF5U)
/*MCS01 driver RAM SIZE*/
#define GP_GTMCCFC_MCS01_MEM_SIZE					(0x1000U)
/*MCS01 RAM address*/
#define GP_GTMCCFC_MCS01_RAM_ADDR					(0xFFD40000U)

/*MCS02 driver block SIZE*/
#define GP_GTMCCFC_CFG_MCS02_DRVBLK_SIZE			(0xF5U)
/*MCS02 driver RAM SIZE*/
#define GP_GTMCCFC_MCS02_MEM_SIZE					(0x1000U)
/*MCS02 RAM address*/
#define GP_GTMCCFC_MCS02_RAM_ADDR					(0xFFD48000U)

/*MCS02 driver block SIZE*/
#define GP_GTMCCFC_CFG_MCS03_DRVBLK_SIZE			(0x2B8U)
/*MCS02 driver RAM SIZE*/
#define GP_GTMCCFC_MCS03_MEM_SIZE					(0x1000U)
/*MCS02 RAM address*/
#define GP_GTMCCFC_MCS03_RAM_ADDR					(0xFFD50000U)

#endif /* GP_GTMCCFC_CFG_H_ */

/***********************************************************************************************************************
* $ArchiVer History:$
V1:
initial version for MCS.
realize interface description and requirement of memory section.
***********************************************************************************************************************/

/***********************************************************************************************************************
* $FcVer History:$
1.0.0	07.08.2025	CaoZijian
initial code version for V1 architecture.
***********************************************************************************************************************/
