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
* $Name______: Gp_GtmCCFC.c$
* $ArchiVer__: 1$
* $FcVeri____: 1.0.0$
* $Author____: CaoZijian$
**
**--------------------------------------------------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: No
**--------------------------------------------------------------------------------------------------------------------**
** DESCRIPTION:
**
** Gp_GtmCCFC source file
**
***********************************************************************************************************************/

/***********************************************************************************************************************
**										Other Header File Inclusion													  **
***********************************************************************************************************************/
#include "Gp_GtmCCFC.h"
#include "Gp_GtmCCFC_Callout.h"

/***********************************************************************************************************************
**                        				Macro Definition                        								      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**										Static Local Variables Definition											  **
***********************************************************************************************************************/
/*$LV-B$*/
#define GP_GTMCCFC_CLEAR_FAR_DATA_ALIGN4_START
#include "Gp_GtmCCFC_MemMap.h"
//
#define GP_GTMCCFC_CLEAR_FAR_DATA_ALIGN4_STOP
#include "Gp_GtmCCFC_MemMap.h"
//
#define GP_GTMCCFC_CONST_FAR_DATA_ALIGN4_START
#include "Gp_GtmCCFC_MemMap.h"
//
#define GP_GTMCCFC_CONST_FAR_DATA_ALIGN4_STOP
#include "Gp_GtmCCFC_MemMap.h"
/*$LV-E$*/

/***********************************************************************************************************************
**										Static Local Function Declaration											  **
***********************************************************************************************************************/
#define GP_GTMCCFC_COMPILER_OPTIMIZE_START
#include "Gp_GtmCCFC_MemMap.h"

#define GP_GTMCCFC_CODE_START
#include "Gp_GtmCCFC_MemMap.h"
//
//
#define GP_GTMCCFC_CODE_STOP
#include "Gp_GtmCCFC_MemMap.h"
//
#define GP_GTMCCFC_COMPILER_OPTIMIZE_STOP
#include "Gp_GtmCCFC_MemMap.h"
/***********************************************************************************************************************
**										Function Source Code														  **
***********************************************************************************************************************/
#define GP_GTMCCFC_COMPILER_OPTIMIZE_START
#include "Gp_GtmCCFC_MemMap.h"
//
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
void	Gp_GtmCCFC_GtmInit(void)
{
	/*enable GTM module*/
	GTMINT.GTMMCR.B.MDIS = 0x0U;

	/*GTM exit stop status*/
	while (GTMINT.GTMMCR.B.STPS == 0x1U);

	/*disable register protection.*/
	GTM.CTRL.B.RF_PROT = 0x0U;

	/*issue a global reset to the GTM to ensure default register values (RF_PROT protected)*/
	GTM.RST.B.RST = 0x0U;

	GPT_GTM_CMU_LLD_IsEnableClock(0,0);
	GPT_GTM_CMU_LLD_IsEnableClock(1,0);
	GPT_GTM_CMU_LLD_IsEnableClock(2,0);

	GPT_GTM_CMU_LLD_SetClockCount(0,0);
	GPT_GTM_CMU_LLD_SetClockCount(1,0);
	GPT_GTM_CMU_LLD_SetClockCount(2,0);

	GPT_GTM_CMU_LLD_IsEnableClock(0,1);
	GPT_GTM_CMU_LLD_IsEnableClock(1,1);
	GPT_GTM_CMU_LLD_IsEnableClock(2,1);

//	GTM_ATOM_1.CH0_RDADDR.B.RDADDR0 = 0x77U;
//	GTM_ATOM_1.CH1_RDADDR.B.RDADDR0 = 0x78U;
//	GTM_ATOM_1.CH2_RDADDR.B.RDADDR0 = 0x79U;
//	GTM_ATOM_1.CH3_RDADDR.B.RDADDR0 = 0x8FU;
//	GTM_ATOM_1.CH4_RDADDR.B.RDADDR0 = 0x90U;
//	GTM_ATOM_1.CH5_RDADDR.B.RDADDR0 = 0xA7U;
//	GTM_ATOM_1.CH6_RDADDR.B.RDADDR0 = 0xA8U;
	/*Disable the global reset and force interrupt functionality.*/
	GTM.CTRL.B.RF_PROT = 0x1u;

	/*clock divider*/
	GTM_CMU.CLK_CTRL[0].B.CLK_CNT = 0;
   	GTM_CMU.CLK_CTRL[1].B.CLK_CNT = 0;
   	GTM_CMU.CLK_CTRL[2].B.CLK_CNT = 0;

	GTM_TBU.CHEN.B.ENDIS_CH1 = 1;
	GTM_TBU.CH1_CTRL.B.CH_CLK_SRC = 0;
	GTM_TBU.CH1_CTRL.B.CH_MODE = 0;
	GTM_TBU.CHEN.B.ENDIS_CH1 = 2;
}

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
void	Gp_GtmCCFC_Atom_Init(void)
{


	{
		/*ATOM0_0*/
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH0 = 1;
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH1 = 1;
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH2 = 1;
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH3 = 1;
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH4 = 1;
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH5 = 1;
		GTM_ATOM_1.AGC_GLB_CTRL.B.RST_CH6 = 1;


		GTM_ATOM_1.CH0_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH0_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH0_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH0_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH0_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH0_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH0_CTRL.B.TRIGOUT = 1U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH0_CTRL.B.RST_CCU0 = 0U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH0_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH0_CTRL.B.SL = 0U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH0_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH0_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH0_IRQ_EN.B.CCU0TC_IRQ_EN = 1U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH0_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/

		/*ATOM0_1*/
		GTM_ATOM_1.CH1_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH1_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH1_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH1_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH1_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH1_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH1_CTRL.B.TRIGOUT = 0U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH1_CTRL.B.RST_CCU0 = 1U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH1_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH1_CTRL.B.SL = 0U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH1_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH1_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH1_IRQ_EN.B.CCU0TC_IRQ_EN = 0U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH1_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/

		/*ATOM0_2*/
		GTM_ATOM_1.CH2_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH2_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH2_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH2_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH2_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH2_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH2_CTRL.B.TRIGOUT = 0U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH2_CTRL.B.RST_CCU0 = 1U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH2_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH2_CTRL.B.SL = 1U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH2_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH2_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH2_IRQ_EN.B.CCU0TC_IRQ_EN = 0U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH2_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/

		/*ATOM0_3*/
		GTM_ATOM_1.CH3_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH3_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH3_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH3_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH3_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH3_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH3_CTRL.B.TRIGOUT = 0U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH3_CTRL.B.RST_CCU0 = 1U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH3_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH3_CTRL.B.SL = 0U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH3_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH3_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH3_IRQ_EN.B.CCU0TC_IRQ_EN = 0U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH3_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/

		/*ATOM0_4*/
		GTM_ATOM_1.CH4_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH4_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH4_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH4_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH4_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH4_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH4_CTRL.B.TRIGOUT = 0U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH4_CTRL.B.RST_CCU0 = 1U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH4_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH4_CTRL.B.SL = 1U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH4_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH4_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH4_IRQ_EN.B.CCU0TC_IRQ_EN = 0U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH4_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/

		/*ATOM0_5*/
		GTM_ATOM_1.CH5_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH5_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH5_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH5_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH5_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH5_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH5_CTRL.B.TRIGOUT = 0U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH5_CTRL.B.RST_CCU0 = 1U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH5_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH5_CTRL.B.SL = 0U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH5_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH5_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH5_IRQ_EN.B.CCU0TC_IRQ_EN = 0U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH5_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/

		/*ATOM0_6*/
		GTM_ATOM_1.CH6_SR0.B.SR0 = 10000U;				/*SR0*/
		GTM_ATOM_1.CH6_SR1.B.SR1 = 5000U;				/*SR1*/
		GTM_ATOM_1.CH6_CM0.B.CM0 = 10000U;      		/*CM0*/
		GTM_ATOM_1.CH6_CM1.B.CM1 = 5000U;     			/*CM1*/
		GTM_ATOM_1.CH6_CN0.B.CN0 = 9999U;				/*CN0*/

		GTM_ATOM_1.CH6_CTRL.B.OSM = 0U;					/*One-shot mode (rw) */
		GTM_ATOM_1.CH6_CTRL.B.TRIGOUT = 0U;				/*Trigger output selection (TRIG_CHx) of module ATOM_CHx:TRIG_CCU0 (rw)*/
		GTM_ATOM_1.CH6_CTRL.B.RST_CCU0 = 1U;			/*Reset source of CCU0 (rw): TRIG_[x-1]*/
		GTM_ATOM_1.CH6_CTRL.B.CLK_SRC_SR = 0U;			/*Shadow register for CMU clock source register CLK_SRC (rw)*/
		GTM_ATOM_1.CH6_CTRL.B.SL = 1U;					/*Signal level for pulse of PWM (rw) */
		GTM_ATOM_1.CH6_CTRL.B.MODE = 2U;				/*ATOM channel mode(rw)*/

		GTM_ATOM_1.CH6_IRQ_EN.B.CCU1TC_IRQ_EN = 0U;		/*CCU1 interrupt enable */
		GTM_ATOM_1.CH6_IRQ_EN.B.CCU0TC_IRQ_EN = 0U;		/*CCU0 interrupt enable */

		GTM_ATOM_1.CH6_IRQ_MODE.B.IRQ_MODE = 2U;		/*Pulse-Notify mode*/
	}
	{

		/*ATOM write address*/
		GTM_ATOM_1.CH0_RDADDR.B.RDADDR0 = 0x77U;
		GTM_ATOM_1.CH1_RDADDR.B.RDADDR0 = 0x78U;
		GTM_ATOM_1.CH2_RDADDR.B.RDADDR0 = 0x79U;
		GTM_ATOM_1.CH3_RDADDR.B.RDADDR0 = 0x8FU;
		GTM_ATOM_1.CH4_RDADDR.B.RDADDR0 = 0x90U;
		GTM_ATOM_1.CH5_RDADDR.B.RDADDR0 = 0xA7U;
		GTM_ATOM_1.CH6_RDADDR.B.RDADDR0 = 0xA8U;


		/*ARU enable*/
		GTM_ATOM_1.CH0_CTRL.B.ARU_EN = 1U;
		GTM_ATOM_1.CH1_CTRL.B.ARU_EN = 1U;
		GTM_ATOM_1.CH2_CTRL.B.ARU_EN = 1U;
		GTM_ATOM_1.CH3_CTRL.B.ARU_EN = 1U;
		GTM_ATOM_1.CH4_CTRL.B.ARU_EN = 1U;
		GTM_ATOM_1.CH5_CTRL.B.ARU_EN = 1U;
		GTM_ATOM_1.CH6_CTRL.B.ARU_EN = 1U;
	}
	{
		/*Enable update CM0, CM1 and CLK_SRC from SR0, SR1 and CLK_SRC_SR (rw)*/
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL0 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL1 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL2 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL3 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL4 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL5 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_GLB_CTRL.B.UPEN_CTRL6 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;

		GTM_ATOM_1.AGC_INT_TRIG.B.INT_TRIG0 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_FUPD_CTRL.B.FUPD_CTRL1 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_FUPD_CTRL.B.FUPD_CTRL2 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_FUPD_CTRL.B.FUPD_CTRL3 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_FUPD_CTRL.B.FUPD_CTRL4 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_FUPD_CTRL.B.FUPD_CTRL5 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_FUPD_CTRL.B.FUPD_CTRL6 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;

		/*selection of time base used for comparison (rw)*/
		GTM_ATOM_1.AGC_ACT_TB.B.TBU_SEL = 0U;

		/*enable channel on an update trigger*/
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL0 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL1 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL2 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL3 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL4 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL5 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_CTRL.B.ENDIS_CTRL6 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;

		/*enable channel*/
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT0 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT1 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT2 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT3 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT4 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT5 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_ENDIS_STAT.B.ENDIS_STAT6 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;

		/*enable channel output on an update trigger*/
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL0 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL1 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL2 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL3 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL4 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL5 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_CTRL.B.OUTEN_CTRL6 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;

		/*enable channel output*/
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT0 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT1 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT2 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT3 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT4 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT5 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
		GTM_ATOM_1.AGC_OUTEN_STAT.B.OUTEN_STAT6 = GP_GTMCCFC_DOUBLE_BIT_ENABLE;
	}
}

/***********************************************************************************************************************
** Function Name    : Gp_GtmCCFC_Mcs_Init
** Service ID       : None
** Sync/Async       : Synchronous
** Reentrancy       : Non_Reentrancy
** Parameter[in]    : None
** Parameter[inout]	: None
** Parameter[out]   : None
** Return Value     : void
** Description      : Gp_GtmCCFC MCS initialization
the function will write MCS driver code to MCS RAM.
***********************************************************************************************************************/
void	Gp_GtmCCFC_Mcs_Init(void)
{
	/*get structure pointer*/
	const Gp_GtmCCFC_CopyTableType* CopyTable_ptst = &Gp_GtmCCFC_CopyTable_vcatst[0U];

	/*define local variable*/
	uint32	McsNumCnt_u32 = 0U;
	uint32	McsSrcSize_u32 = 0U;
	uint32*	McsSrc_pu32;
	uint32*	McsDest_pu32;

	/*wait for MCSxx RAM clear to finish*/
	while (GTM_MCS_0.CTRL.B.RAM_RST == 1U);
	while (GTM_MCS_1.CTRL.B.RAM_RST == 1U);
	while (GTM_MCS_2.CTRL.B.RAM_RST == 1U);
	while (GTM_MCS_3.CTRL.B.RAM_RST == 1U);

	/*load MCS code into GTM RAM*/
	for (McsNumCnt_u32 = 0U; McsNumCnt_u32 < GP_GTMCCFC_MCSNUM; McsNumCnt_u32++)
	{
		McsSrc_pu32 = CopyTable_ptst[McsNumCnt_u32].Src_pu32;
		McsSrcSize_u32 = CopyTable_ptst[McsNumCnt_u32].SrcSize;
		McsDest_pu32 = CopyTable_ptst[McsNumCnt_u32].Dest_pu32;

		while (McsSrcSize_u32)
		{
			/*firstly assign value, then++*/
			*McsDest_pu32++ = *McsSrc_pu32++;
			McsSrcSize_u32--;
		}
	}

	/*MCS scheduling mode*/
	GTM_MCS_0.CTRL.B.SCHED = GP_GTMCCFC_CFG_MCSMOD_REG;
	GTM_MCS_1.CTRL.B.SCHED = GP_GTMCCFC_CFG_MCSMOD_REG;
	GTM_MCS_2.CTRL.B.SCHED = GP_GTMCCFC_CFG_MCSMOD_REG;
	GTM_MCS_3.CTRL.B.SCHED = GP_GTMCCFC_CFG_MCSMOD_REG;

//	/*ATOM write address*/
//	GTM_ATOM_1.CH0_RDADDR.B.RDADDR0 = 0x77U;
//	GTM_ATOM_1.CH1_RDADDR.B.RDADDR0 = 0x78U;
//	GTM_ATOM_1.CH2_RDADDR.B.RDADDR0 = 0x79U;
//	GTM_ATOM_1.CH3_RDADDR.B.RDADDR0 = 0x8FU;
//	GTM_ATOM_1.CH4_RDADDR.B.RDADDR0 = 0x90U;
//	GTM_ATOM_1.CH5_RDADDR.B.RDADDR0 = 0xA7U;
//	GTM_ATOM_1.CH6_RDADDR.B.RDADDR0 = 0xA8U;
//
//
//	/*ARU enable*/
//	GTM_ATOM_1.CH0_CTRL.B.ARU_EN = 1U;
//	GTM_ATOM_1.CH1_CTRL.B.ARU_EN = 1U;
//	GTM_ATOM_1.CH2_CTRL.B.ARU_EN = 1U;
//	GTM_ATOM_1.CH3_CTRL.B.ARU_EN = 1U;
//	GTM_ATOM_1.CH4_CTRL.B.ARU_EN = 1U;
//	GTM_ATOM_1.CH5_CTRL.B.ARU_EN = 1U;
//	GTM_ATOM_1.CH6_CTRL.B.ARU_EN = 1U;

	/*MCS channel task enable*/
	GTM_MCS_0.CH0_CTRL.B.EN = 1U;
	GTM_MCS_1.CH0_CTRL.B.EN = 1U;
	GTM_MCS_2.CH0_CTRL.B.EN = 1U;
	GTM_MCS_3.CH0_CTRL.B.EN = 1U;
}

#define GP_GTMCCFC_CODE_STOP
#include "Gp_GtmCCFC_MemMap.h"
//
#define GP_GTMCCFC_COMPILER_OPTIMIZE_STOP
#include "Gp_GtmCCFC_MemMap.h"

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
