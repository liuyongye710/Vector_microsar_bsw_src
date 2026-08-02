/***********************************************************************************************************************
**--------------------------------------------------------------------------------------------------------------------**
** Copyright (c)  2025 by G-Pulse.		All rights reserved.
** This software is copyright protected and proprietary to G-Pulse.
** G-Pulse grants to you only those rights as set out in the license conditions.
** All other rights remain with G-Pulse.
**--------------------------------------------------------------------------------------------------------------------**
**
* Administrative Information
* $Namespace_: ..\ Gp_GtmCCFC$
* $Class_____: C$
* $Name______: Gp_GtmCCFC_Types.h$
* $ArchiVer__: 1$
* $FcVeri____: 1.0.0$
* $Author____: CaoZijian$
**
**--------------------------------------------------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: No
**--------------------------------------------------------------------------------------------------------------------**
** DESCRIPTION:
**
** Gp_GtmCCFC types header file
**
***********************************************************************************************************************/
#ifndef GP_GTMCCFC_TYPES_H_
#define GP_GTMCCFC_TYPES_H_

/***********************************************************************************************************************
**										Other Header File Inclusion													  **
***********************************************************************************************************************/
#include "Gp_GtmCCFC_Cfg.h"

/***********************************************************************************************************************
**                        				Macro Definition                        								      **
***********************************************************************************************************************/
#define GP_GTMCCFC_UNUSED_PARAMETER(VariableName)	(void)(VariableName)
#define GP_GTMCCFC_NULL_PTR							((void *) 0)

#ifndef GP_GTMCCFC_INLINE_
#if defined __TASKING__
#define GP_GTMCCFC_INLINE_		static inline
#elif defined __HIGHTEC__
#define GP_GTMCCFC_INLINE_		static inline __attribute__	((always_inline))
#endif
#endif

#ifndef GP_GTMCCFC_STATIC_
#define GP_GTMCCFC_STATIC_		static
#endif


#define GP_GTMCCFC_DOUBLE_BIT_ENABLE		(2U)
#define GP_GTMCCFC_DOUBLE_BIT_DISABLE		(1U)
#define GP_GTMCCFC_DOUBLE_BIT_NOCHANGE		(0U)

#define GP_GTMCCFC_DOUBLE_BIT_SET1			(2U)
#define GP_GTMCCFC_DOUBLE_BIT_SET0			(1U)
#define GP_GTMCCFC_DOUBLE_BIT_INGORE		(0U)

#define GP_GTMCCFC_DISABLE					(0x00U)
#define GP_GTMCCFC_ENABLE					(0x01U)

/*fault mask*/
/*MCS channel task blocking fault*/
#define GP_GTMCCFC_MCSTASK_BLK_FLT			((uint32)0x00000001U)
/***********************************************************************************************************************
**										Typedef Definition															  **
***********************************************************************************************************************/
/*For Error Recording.
 *0b 0000 0000 0000 0000 0000 0000 0000 0000	--	0x0			--	No Error
 *0b 0000 0000 0000 0000 0000 0000 0000 0001	--	0x1			--	MCS channel task blocking
 * */

/*$TDST-B$*/
typedef struct Gp_GtmCCFC_FltDiag
{
	uint32	DrvDiagSta_u32;								/*driver diagnosis status*/
	uint32	DrvDiagEvent_u32;							/*driver diagnosis event*/
	uint32	DrvFltCnt_u32;								/*driver fault counter:fault occur number*/
}Gp_GtmCCFC_FltDiagType;
/*$TDST-E$*/

/*$TDST-B$*/
typedef struct Gp_GtmCCFC_CopyTable
{
	uint32*	Src_pu32;			/*source address:MCS driver carry address*/
	uint32	SrcSize;			/*source size:MCS driver block size*/
	uint32*	Dest_pu32;			/*destination address:MCS RAM address*/
	uint32	DestSize;			/*destination size:MCS RAM size*/
}Gp_GtmCCFC_CopyTableType;
/*$TDST-E$*/

#endif /*GP_GTMCCFC_TYPES_H_*/

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
