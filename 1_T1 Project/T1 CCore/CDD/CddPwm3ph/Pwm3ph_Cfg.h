/******************************************************************************/
/* FILE NAME: Pwm3ph_Cfg.h                							          */
/* VERSION: 1.0                                        						  */
/* DESCRIPTION: Three - phase six - channel PWM output drive config file      */
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
/******************************************************************************/


#ifndef PWM3PH_CFG_H_
#define PWM3PH_CFG_H_
/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Cdd_CommonCfg.h"

/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/
/*ATOM 100us ISR Enable*/
#define PERIOD_CHANNEL_100US_ISR     1U
/*PWM闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻柊纰夌秶閹凤拷12闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔稿焻绾板瀚归柨鐔告灮閹风兘鏁撻敓锟� OR 3闁跨喐鏋婚幏宄板窗闁跨喓笑濮ｆ棁顕滈幏鐑芥晸閺傘倖瀚�*/
#define UI8_PWM3PH_PARAMETER_TYPE	 3U

/*PWM输出模式*/
#define UI8_MODE_UP_ON_DOWN_UON		 5U		/* 		下桥仅开U项，上桥全开 */
#define UI8_MODE_UP_UON_DOWN_ON		 4U		/* 		上桥仅开U项，下桥全开 */
#define UI8_MODE_NORMAL				 3U		/*Run 正常控制 */
#define UI8_MODE_UP_ON_DOWN_OFF	 	 2U	    /* 		上桥开、下桥关 */
#define UI8_MODE_UP_OFF_DOWN_ON	 	 1U	    /*ASC   上桥关、下桥开 */
#define UI8_MODE_UP_OFF_DOWN_OFF	 0U		/*FreeWheel 上下桥都关，IDLE模式 */

/* PWM参数相关 */
#define U16_PWM_MAX_FREQ_VALUE		 15000U		/* 最大频率 */
#define U16_PWM_MIN_FREQ_VALUE		 1000U		/* 最小频率 */
#define U16_PWM_DEF_FREQ_VALUE		 10000U		/* 默认频率 */
#define	U16_PWM_MIN_TICKS_VALUE		 10U		/* PWM最小TICKS(导通时间) */
#define	U16_PWM_MIN_DEADTIME_VALUE	 10U		/* PWM最小死区时间TICKS */

/* PWM与实际硬件资源相关 */
#define PWM3PH_TOM_ATOM_SEL					 1U		/*0:TOM;1:ATOM*/
#define UI8_PWM_TOM_ATOM_MOUDLE_SEL		 	 1U		/*TOM/ATOM模块选择;0选择Tom模块，1选择Atom模块*/
#define UI8_PWM_ATOM_CHANNEL_SEL_UL		 2U		/*UT TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_UH		 1U		/*UB TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_VL		 4U		/*VT TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_VH		 3U		/*VB TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_WL		 6U		/*WT TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_WH		 5U		/*WB TOM/ATOM 通道选择*/

#define PWM3PH_TOM_ATOM_SEL_M2			1U		/*0:TOM;1:ATOM*/
#define UI8_PWM_TOM_ATOM_MOUDLE_SEL_M2   4U		/*ATOM Module*/
#define UI8_PWM_ATOM_CHANNEL_SEL_UL_M2  2U		/*UT TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_UH_M2  1U      /*UB TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_VL_M2  4U		/*VT TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_VH_M2	3U		/*VB TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_WL_M2  6U		/*WT TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_WH_M2  5U		/*WB TOM/ATOM 通道选择*/
/*PERIOD TOM/ATOM 通道选择*/
#define UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF		0 //Pwmchannel 9_Motor1_PWM_Trig_P2_0
#define UI8_PWM_ATOM_CHANNEL_SEL_PERIOD_REF_M2  0 //M2 ATOM ISR Source

/*ADC TRIGGER TOM/ATOM 通道选择*/
#define UI8_PWM_TOM_ATOM_CHANNEL_SEL_ADC_TRIG		7//Pwmchannel 10_Motor1_ADC_Trig_P2_7

/*0:多次采样取平均,适用TC23x;1:同步采样,适用TC27x/TC29x*/
//#define UI8_PWM_ADC_MOUDLE_SEL					1U

#define U16_PWM_MAX_PERIOD_VALUE	 50000U 	/* PWM周期最大TICKS */
#define U32_PWM_GTM_CLOCK_VALUE		 80000000U	/* GTM 周期,100M */
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
