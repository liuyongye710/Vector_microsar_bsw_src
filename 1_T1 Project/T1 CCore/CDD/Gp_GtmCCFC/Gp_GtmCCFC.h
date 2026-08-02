/***********************************************************************************************************************
**--------------------------------------------------------------------------------------------------------------------**
** Copyright (c)  2023 by G-Pulse.		All rights reserved.
** This software is copyright protected and proprietary to G-Pulse.
** G-Pulse grants to you only those rights as set out in the license conditions.
** All other rights remain with G-Pulse.
**--------------------------------------------------------------------------------------------------------------------**
**
* Administrative Information
* $Namespace_: ..\ Gp_GtmCCFC$
* $Class_____: C$
* $Name______: Gp_GtmCCFC.h$
* $ArchiVer__: 1$
* $FcVeri____: 1.0.0$
* $Author____: CaoZijian$
**
**--------------------------------------------------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: No
**--------------------------------------------------------------------------------------------------------------------**
** DESCRIPTION:
**
** Gp_GtmCCFC header file
**
***********************************************************************************************************************/
#ifndef GP_GTMCCFC_H_
#define GP_GTMCCFC_H_

/***********************************************************************************************************************
**                        				Other Header File Inclusion                    								  **
***********************************************************************************************************************/
#include "Gp_GtmCCFC_CfgData.h"

/***********************************************************************************************************************
**										Global Function Prototypes													  **
***********************************************************************************************************************/
#define GP_GTMCCFC_CODE_START
#include "Gp_GtmCCFC_MemMap.h"
/***********************************************************************************************************************
** Function Name    : Gp_GtmCCFC_GtmInit
** Service ID       : None
** Sync/Async       : Synchronous
** Reentrancy       : Non_Reentrancy
** Parameter[in]    : None
** Parameter[inout]	: None
** Parameter[out]   : None
** Return Value     : void
** Description      : Gp_GtmCCFC GTM initialization
the function will initialize GTM module.
***********************************************************************************************************************/
extern void	Gp_GtmCCFC_GtmInit(void);

/***********************************************************************************************************************
** Function Name    : Gp_GtmCCFC_Atom_Init
** Service ID       : None
** Sync/Async       : Synchronous
** Reentrancy       : Non_Reentrancy
** Parameter[in]    : None
** Parameter[inout]	: None
** Parameter[out]   : None
** Return Value     : void
** Description      : Gp_GtmCCFC initialization
the function will initialize GTM_ATOM module.
***********************************************************************************************************************/
extern void	Gp_GtmCCFC_Atom_Init(void);

/***********************************************************************************************************************
** Function Name    : Gp_GtmCCFC_Mcs_Init
** Service ID       : None
** Sync/Async       : Synchronous
** Reentrancy       : Non_Reentrancy
** Parameter[in]    : None
** Parameter[inout]	: None
** Parameter[out]   : None
** Return Value     : void
** Description      : Gp_GtmCCFC initialization
the function will set initial value for all Gp_GtmCCFC variables.
***********************************************************************************************************************/
extern	void	Gp_GtmCCFC_Mcs_Init(void);

#define GP_GTMCCFC_CODE_STOP
#include "Gp_GtmCCFC_MemMap.h"

#endif /* GP_GTMCCFC_H_ */

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
