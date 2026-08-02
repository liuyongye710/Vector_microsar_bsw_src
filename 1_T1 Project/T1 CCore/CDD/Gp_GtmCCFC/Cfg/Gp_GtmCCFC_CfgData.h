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
* $Name______: Gp_GtmCCFC_CfgData.h$
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
** Gp_GtmCCFC CFG data header file
**
***********************************************************************************************************************/
#ifndef GP_GTMCCFC_CFGDATA_H_
#define GP_GTMCCFC_CFGDATA_H_

/***********************************************************************************************************************
**										Other Header File Inclusion													  **
***********************************************************************************************************************/
#include "Gp_GtmCCFC_Types.h"
/*other FC header file inclusion if necessary*/

/***********************************************************************************************************************
**                        				Global Variables With Declaration											  **
***********************************************************************************************************************/
#define GP_GTMCCFC_CONST_FAR_DATA_ALIGN4_START
#include "Gp_GtmCCFC_MemMap.h"

extern const Gp_GtmCCFC_CopyTableType Gp_GtmCCFC_CopyTable_vcatst[GP_GTMCCFC_MCSNUM];

extern const  uint32  Gp_GtmCCFC_Mcs00_DrvBlk_vcau32[GP_GTMCCFC_CFG_MCS00_DRVBLK_SIZE];
extern const  uint32  Gp_GtmCCFC_Mcs01_DrvBlk_vcau32[GP_GTMCCFC_CFG_MCS01_DRVBLK_SIZE];
extern const  uint32  Gp_GtmCCFC_Mcs02_DrvBlk_vcau32[GP_GTMCCFC_CFG_MCS02_DRVBLK_SIZE];
extern const  uint32  Gp_GtmCCFC_Mcs03_DrvBlk_vcau32[GP_GTMCCFC_CFG_MCS03_DRVBLK_SIZE];

#define GP_GTMCCFC_CONST_FAR_DATA_ALIGN4_STOP
#include "Gp_GtmCCFC_MemMap.h"

#define GP_GTMCCFC_CONST_FAR_DATA_ALIGN4_CALI_START
#include "Gp_GtmCCFC_MemMap.h"

#define GP_GTMCCFC_CONST_FAR_DATA_ALIGN4_CALI_STOP
#include "Gp_GtmCCFC_MemMap.h"

#endif /* GP_GTMCCFC_CFGDATA_H_ */

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
