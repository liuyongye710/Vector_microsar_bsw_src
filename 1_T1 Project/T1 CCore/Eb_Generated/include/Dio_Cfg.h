/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : DIO
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*
*****************************************************************************/

/**
*   @file    Dio_Cfg.h
*   @version 3.0.0
*
*   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
*   @details Autosar layer of Dio MCAL driver.
*
*   @addtogroup Dio
*   @{
*/
#ifndef DIO_CFG_H
#define DIO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================INCLUDE FILES=======================================*/
#include "Dio_Types.h"
/*=============================SOURCE FILE VERSION INFORMATION==================================*/
#define DIO_CFG_H_VENDOR_ID                     176
#define DIO_CFG_H_MAJOR_VERSION                 4
#define DIO_CFG_H_MINOR_VERSION                 4
#define DIO_CFG_H_patch_VERSION                 0
#define DIO_CFG_H_SW_MAJOR_VERSION              3
#define DIO_CFG_H_SW_MINOR_VERSION              0
#define DIO_CFG_H_SW_PATCH_VERSION              0
/*====================================FILE VERSION CHECKS=======================================*/
#if (DIO_CFG_H_VENDOR_ID != DIO_TYPES_VENDOR_ID)
    #error " NON-MATCHED DATA : DIO_CFG_H_VENDOR_ID "
#endif
#if (DIO_CFG_H_MAJOR_VERSION != DIO_TYPES_MAJOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_H_MAJOR_VERSION "
#endif
#if (DIO_CFG_H_MINOR_VERSION != DIO_TYPES_MINOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_H_MINOR_VERSION "
#endif
#if (DIO_CFG_H_patch_VERSION != DIO_TYPES_patch_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_H_patch_VERSION "
#endif
#if (DIO_CFG_H_SW_MAJOR_VERSION != DIO_TYPES_SW_MAJOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_H_SW_MAJOR_VERSION "
#endif
#if (DIO_CFG_H_SW_MINOR_VERSION != DIO_TYPES_SW_MINOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_H_SW_MINOR_VERSION "
#endif
#if (DIO_CFG_H_SW_PATCH_VERSION != DIO_TYPES_SW_PATCH_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_H_SW_PATCH_VERSION "
#endif

/*=========================================CONSTANTS============================================*/


#define DIO_DEV_ERROR_DETECT    (STD_ON)

#define DIO_VERSION_INFO_API    (STD_ON)

#define DIO_FLIP_CHANNEL_API    (STD_ON)

#define DIO_MASKEDWRITEPORT_API (STD_ON)

#define DIO_READZERO_UNDEFINEDPORTS (STD_ON)

#define DIO_MULTICORE_SUPPORT (STD_OFF)
 
#define DIO_NUM_PORTS_U16 (uint16)(0x16)

#define DIO_NUM_CHANNELS_RIDE_PORT_U16 (uint16)0x10U

#define DIO_ZERO_U16 ((Dio_PortLevelType)0x0U)

#define DIO_NUM_CHANNELS_U16     ((uint16)DIO_NUM_PORTS_U16 * DIO_NUM_CHANNELS_RIDE_PORT_U16)

#define DIO_PRECOMPILE_SUPPORT



#define ncoreid  2

#define DIO_INLINE    LOCAL_INLINE

#define DIO_OFFSET_MAX_VALID_U8 ((uint8)0xFU)
extern CONST(Dio_PortLevelType, DIO_CONST) Dio_ReadAvailablePins[DIO_NUM_PORTS_U16];
extern CONST(Dio_PortLevelType, DIO_CONST) Dio_WriteAvailablePins[DIO_NUM_PORTS_U16];
extern CONST(Dio_ConfigType, DIO_CONST) Dio_ConfigPC;


/**
* @brief          Symbolic name for the port DioPort_0.
*
*/
#define DioConf_DioPort_DioPort_0  ((uint8)0x00U)


/**
* @brief          Symbolic name for the port DI_COL_in.
*/
#define DioConf_DioChannel_DI_COL_in ((uint16)13U)


/**
* @brief          Symbolic name for the port DO_LED1.
*/
#define DioConf_DioChannel_DO_LED1 ((uint16)1U)


/**
* @brief          Symbolic name for the port DO_LED2.
*/
#define DioConf_DioChannel_DO_LED2 ((uint16)2U)


/**
* @brief          Symbolic name for the port DO_LED3.
*/
#define DioConf_DioChannel_DO_LED3 ((uint16)3U)


/**
* @brief          Symbolic name for the port DO_LED4.
*/
#define DioConf_DioChannel_DO_LED4 ((uint16)4U)


/**
* @brief          Symbolic name for the port DO_SA47321_PROG.
*/
#define DioConf_DioChannel_DO_SA47321_PROG ((uint16)14U)




/**
* @brief          Symbolic name for the port DioPort_1.
*
*/
#define DioConf_DioPort_DioPort_1  ((uint8)0x01U)


/**
* @brief          Symbolic name for the port DO_FCCU_EOUT.
*/
#define DioConf_DioChannel_DO_FCCU_EOUT ((uint16)27U)




/**
* @brief          Symbolic name for the port DioPort_2.
*
*/
#define DioConf_DioPort_DioPort_2  ((uint8)0x02U)


/**
* @brief          Symbolic name for the port DI_BSM24_IN.
*/
#define DioConf_DioChannel_DI_BSM24_IN ((uint16)39U)


/**
* @brief          Symbolic name for the port DO_MCU_CLR1.
*/
#define DioConf_DioChannel_DO_MCU_CLR1 ((uint16)43U)


/**
* @brief          Symbolic name for the port DO_MCU_CLR2.
*/
#define DioConf_DioChannel_DO_MCU_CLR2 ((uint16)44U)




/**
* @brief          Symbolic name for the port DioPort_3.
*
*/
#define DioConf_DioPort_DioPort_3  ((uint8)0x03U)


/**
* @brief          Symbolic name for the port DI_RT_DIR.
*/
#define DioConf_DioChannel_DI_RT_DIR ((uint16)55U)


/**
* @brief          Symbolic name for the port DI_RT_LOT_A.
*/
#define DioConf_DioChannel_DI_RT_LOT_A ((uint16)58U)


/**
* @brief          Symbolic name for the port DI_RT_DOS_A.
*/
#define DioConf_DioChannel_DI_RT_DOS_A ((uint16)62U)


/**
* @brief          Symbolic name for the port DO_RT_RDN.
*/
#define DioConf_DioChannel_DO_RT_RDN ((uint16)48U)


/**
* @brief          Symbolic name for the port DO_RT_WRN.
*/
#define DioConf_DioChannel_DO_RT_WRN ((uint16)49U)


/**
* @brief          Symbolic name for the port DO_RT_SOE.
*/
#define DioConf_DioChannel_DO_RT_SOE ((uint16)50U)


/**
* @brief          Symbolic name for the port DO_RT_SAMPLE.
*/
#define DioConf_DioChannel_DO_RT_SAMPLE ((uint16)51U)


/**
* @brief          Symbolic name for the port DO_RT_A0.
*/
#define DioConf_DioChannel_DO_RT_A0 ((uint16)52U)


/**
* @brief          Symbolic name for the port DO_RT_A1.
*/
#define DioConf_DioChannel_DO_RT_A1 ((uint16)53U)


/**
* @brief          Symbolic name for the port DO_RT_RESETN.
*/
#define DioConf_DioChannel_DO_RT_RESETN ((uint16)54U)


/**
* @brief          Symbolic name for the port DO_RT_RES0.
*/
#define DioConf_DioChannel_DO_RT_RES0 ((uint16)56U)


/**
* @brief          Symbolic name for the port DO_RT_RES1.
*/
#define DioConf_DioChannel_DO_RT_RES1 ((uint16)57U)




/**
* @brief          Symbolic name for the port DioPort_4.
*
*/
#define DioConf_DioPort_DioPort_4  ((uint8)0x04U)


/**
* @brief          Symbolic name for the port DI_AdhesK5.
*/
#define DioConf_DioChannel_DI_AdhesK5 ((uint16)70U)


/**
* @brief          Symbolic name for the port DI_AdhesK6.
*/
#define DioConf_DioChannel_DI_AdhesK6 ((uint16)71U)


/**
* @brief          Symbolic name for the port DI_AdhesK7.
*/
#define DioConf_DioChannel_DI_AdhesK7 ((uint16)72U)


/**
* @brief          Symbolic name for the port DI_AdhesK8.
*/
#define DioConf_DioChannel_DI_AdhesK8 ((uint16)73U)


/**
* @brief          Symbolic name for the port DI_AdhesK9.
*/
#define DioConf_DioChannel_DI_AdhesK9 ((uint16)75U)


/**
* @brief          Symbolic name for the port DI_AdhesK12.
*/
#define DioConf_DioChannel_DI_AdhesK12 ((uint16)76U)




/**
* @brief          Symbolic name for the port DioPort_5.
*
*/
#define DioConf_DioPort_DioPort_5  ((uint8)0x05U)


/**
* @brief          Symbolic name for the port DO_CAN4WAKE.
*/
#define DioConf_DioChannel_DO_CAN4WAKE ((uint16)91U)




/**
* @brief          Symbolic name for the port DioPort_6.
*
*/
#define DioConf_DioPort_DioPort_6  ((uint8)0x06U)


/**
* @brief          Symbolic name for the port DO_RT_CSn_M1.
*/
#define DioConf_DioChannel_DO_RT_CSn_M1 ((uint16)109U)




/**
* @brief          Symbolic name for the port DioPort_7.
*
*/
#define DioConf_DioPort_DioPort_7  ((uint8)0x07U)




/**
* @brief          Symbolic name for the port DioPort_8.
*
*/
#define DioConf_DioPort_DioPort_8  ((uint8)0x08U)


/**
* @brief          Symbolic name for the port DI_SafeState1.
*/
#define DioConf_DioChannel_DI_SafeState1 ((uint16)139U)


/**
* @brief          Symbolic name for the port DI_SafeState2.
*/
#define DioConf_DioChannel_DI_SafeState2 ((uint16)140U)




/**
* @brief          Symbolic name for the port DioPort_9.
*
*/
#define DioConf_DioPort_DioPort_9  ((uint8)0x09U)


/**
* @brief          Symbolic name for the port DI_Fault_UH2.
*/
#define DioConf_DioChannel_DI_Fault_UH2 ((uint16)147U)


/**
* @brief          Symbolic name for the port DI_Fault_VH2.
*/
#define DioConf_DioChannel_DI_Fault_VH2 ((uint16)148U)


/**
* @brief          Symbolic name for the port DI_Fault_WH2.
*/
#define DioConf_DioChannel_DI_Fault_WH2 ((uint16)149U)


/**
* @brief          Symbolic name for the port DI_Fault_UL2.
*/
#define DioConf_DioChannel_DI_Fault_UL2 ((uint16)150U)


/**
* @brief          Symbolic name for the port DI_Fault_VL2.
*/
#define DioConf_DioChannel_DI_Fault_VL2 ((uint16)151U)


/**
* @brief          Symbolic name for the port DI_Fault_WL2.
*/
#define DioConf_DioChannel_DI_Fault_WL2 ((uint16)152U)


/**
* @brief          Symbolic name for the port DI_IL_Dr_D_OUT2.
*/
#define DioConf_DioChannel_DI_IL_Dr_D_OUT2 ((uint16)153U)


/**
* @brief          Symbolic name for the port DO_PWM_Reset_Driver2.
*/
#define DioConf_DioChannel_DO_PWM_Reset_Driver2 ((uint16)145U)


/**
* @brief          Symbolic name for the port DO_Enable245_2.
*/
#define DioConf_DioChannel_DO_Enable245_2 ((uint16)146U)


/**
* @brief          Symbolic name for the port DO_Enable245_3.
*/
#define DioConf_DioChannel_DO_Enable245_3 ((uint16)154U)




/**
* @brief          Symbolic name for the port DioPort_10.
*
*/
#define DioConf_DioPort_DioPort_10  ((uint8)0x0aU)




/**
* @brief          Symbolic name for the port DioPort_11.
*
*/
#define DioConf_DioPort_DioPort_11  ((uint8)0x0bU)


/**
* @brief          Symbolic name for the port DO_ADC_GPIO1.
*/
#define DioConf_DioChannel_DO_ADC_GPIO1 ((uint16)179U)




/**
* @brief          Symbolic name for the port DioPort_12.
*
*/
#define DioConf_DioPort_DioPort_12  ((uint8)0x0cU)


/**
* @brief          Symbolic name for the port DI_Fault_UH.
*/
#define DioConf_DioChannel_DI_Fault_UH ((uint16)194U)


/**
* @brief          Symbolic name for the port DI_Fault_VH.
*/
#define DioConf_DioChannel_DI_Fault_VH ((uint16)195U)


/**
* @brief          Symbolic name for the port DI_Fault_WH.
*/
#define DioConf_DioChannel_DI_Fault_WH ((uint16)196U)


/**
* @brief          Symbolic name for the port DI_Fault_UL.
*/
#define DioConf_DioChannel_DI_Fault_UL ((uint16)197U)


/**
* @brief          Symbolic name for the port DI_Fault_VL.
*/
#define DioConf_DioChannel_DI_Fault_VL ((uint16)198U)


/**
* @brief          Symbolic name for the port DI_Fault_WL.
*/
#define DioConf_DioChannel_DI_Fault_WL ((uint16)199U)


/**
* @brief          Symbolic name for the port DI_IL_Dr_D_OUT1.
*/
#define DioConf_DioChannel_DI_IL_Dr_D_OUT1 ((uint16)200U)


/**
* @brief          Symbolic name for the port DO_PWM_Reset_Driver.
*/
#define DioConf_DioChannel_DO_PWM_Reset_Driver ((uint16)192U)


/**
* @brief          Symbolic name for the port DO_Enable245_1.
*/
#define DioConf_DioChannel_DO_Enable245_1 ((uint16)193U)


/**
* @brief          Symbolic name for the port DO_CAN0_S.
*/
#define DioConf_DioChannel_DO_CAN0_S ((uint16)201U)


/**
* @brief          Symbolic name for the port DO_CAN1_S.
*/
#define DioConf_DioChannel_DO_CAN1_S ((uint16)202U)


/**
* @brief          Symbolic name for the port DO_CAN2_S.
*/
#define DioConf_DioChannel_DO_CAN2_S ((uint16)203U)


/**
* @brief          Symbolic name for the port DO_CAN3_S.
*/
#define DioConf_DioChannel_DO_CAN3_S ((uint16)204U)




/**
* @brief          Symbolic name for the port DioPort_13.
*
*/
#define DioConf_DioPort_DioPort_13  ((uint8)0x0dU)


/**
* @brief          Symbolic name for the port DO_SW4.
*/
#define DioConf_DioChannel_DO_SW4 ((uint16)208U)


/**
* @brief          Symbolic name for the port DO_DB_15V_SW1.
*/
#define DioConf_DioChannel_DO_DB_15V_SW1 ((uint16)209U)


/**
* @brief          Symbolic name for the port DO_DB_15V_SW2.
*/
#define DioConf_DioChannel_DO_DB_15V_SW2 ((uint16)211U)


/**
* @brief          Symbolic name for the port DO_POWER_Down.
*/
#define DioConf_DioChannel_DO_POWER_Down ((uint16)212U)


/**
* @brief          Symbolic name for the port DO_RLS_EXC_N_EN.
*/
#define DioConf_DioChannel_DO_RLS_EXC_N_EN ((uint16)221U)


/**
* @brief          Symbolic name for the port DO_RLS_EXC_EN.
*/
#define DioConf_DioChannel_DO_RLS_EXC_EN ((uint16)222U)




/**
* @brief          Symbolic name for the port DioPort_14.
*
*/
#define DioConf_DioPort_DioPort_14  ((uint8)0x0eU)


/**
* @brief          Symbolic name for the port DI_FastC_Wake.
*/
#define DioConf_DioChannel_DI_FastC_Wake ((uint16)224U)


/**
* @brief          Symbolic name for the port DI_Switch0.
*/
#define DioConf_DioChannel_DI_Switch0 ((uint16)226U)


/**
* @brief          Symbolic name for the port DI_Switch1.
*/
#define DioConf_DioChannel_DI_Switch1 ((uint16)227U)


/**
* @brief          Symbolic name for the port DI_Switch2.
*/
#define DioConf_DioChannel_DI_Switch2 ((uint16)228U)


/**
* @brief          Symbolic name for the port DI_Switch3.
*/
#define DioConf_DioChannel_DI_Switch3 ((uint16)229U)


/**
* @brief          Symbolic name for the port DI_ACM_EN.
*/
#define DioConf_DioChannel_DI_ACM_EN ((uint16)230U)


/**
* @brief          Symbolic name for the port DO_SW_K1.
*/
#define DioConf_DioChannel_DO_SW_K1 ((uint16)234U)


/**
* @brief          Symbolic name for the port DO_SW_K2.
*/
#define DioConf_DioChannel_DO_SW_K2 ((uint16)235U)


/**
* @brief          Symbolic name for the port DO_SW_K3.
*/
#define DioConf_DioChannel_DO_SW_K3 ((uint16)236U)


/**
* @brief          Symbolic name for the port DO_SW_K5.
*/
#define DioConf_DioChannel_DO_SW_K5 ((uint16)237U)


/**
* @brief          Symbolic name for the port DO_SW_K6.
*/
#define DioConf_DioChannel_DO_SW_K6 ((uint16)238U)




/**
* @brief          Symbolic name for the port DioPort_15.
*
*/
#define DioConf_DioPort_DioPort_15  ((uint8)0x0fU)




/**
* @brief          Symbolic name for the port DioPort_16.
*
*/
#define DioConf_DioPort_DioPort_16  ((uint8)0x10U)



/**
* @brief          Symbolic name for the port DI_IOrest.
*/
#define DioConf_DioChannel_DI_IOrest ((uint16)258U)




/**
* @brief          Symbolic name for the port DioPort_17.
*
*/
#define DioConf_DioPort_DioPort_17  ((uint8)0x11U)




/**
* @brief          Symbolic name for the port DioPort_18.
*
*/
#define DioConf_DioPort_DioPort_18  ((uint8)0x12U)



/**
* @brief          Symbolic name for the port DO_eFuRST_Driver.
*/
#define DioConf_DioChannel_DO_eFuRST_Driver ((uint16)294U)



/**
* @brief          Symbolic name for the port DI_HsD_nFR1.
*/
#define DioConf_DioChannel_DI_HsD_nFR1 ((uint16)302U)



/**
* @brief          Symbolic name for the port DI_HsD_nFR2.
*/
#define DioConf_DioChannel_DI_HsD_nFR2 ((uint16)303U)



/**
* @brief          Symbolic name for the port DI_HsD_nFR3.
*/
#define DioConf_DioChannel_DI_HsD_nFR3 ((uint16)304U)



/**
* @brief          Symbolic name for the port DO_HsD_DIAG_EN.
*/
#define DioConf_DioChannel_DO_HsD_DIAG_EN ((uint16)289U)



/**
* @brief          Symbolic name for the port DO_HsD_THER.
*/
#define DioConf_DioChannel_DO_HsD_THER ((uint16)292U)



/**
* @brief          Symbolic name for the port DO_HsD_SEH1235.
*/
#define DioConf_DioChannel_DO_HsD_SEH1235 ((uint16)293U)



/**
* @brief          Symbolic name for the port DO_HsD_SEL1235.
*/
#define DioConf_DioChannel_DO_HsD_SEL1235 ((uint16)295U)



/**
* @brief          Symbolic name for the port DO_HsD_SEH6789.
*/
#define DioConf_DioChannel_DO_HsD_SEH6789 ((uint16)296U)



/**
* @brief          Symbolic name for the port DO_HsD_SEL6789.
*/
#define DioConf_DioChannel_DO_HsD_SEL6789 ((uint16)297U)



/**
* @brief          Symbolic name for the port DO_HsD_SEH101112.
*/
#define DioConf_DioChannel_DO_HsD_SEH101112 ((uint16)298U)



/**
* @brief          Symbolic name for the port DO_HsD_SEL101112.
*/
#define DioConf_DioChannel_DO_HsD_SEL101112 ((uint16)299U)




/**
* @brief          Symbolic name for the port DioPort_19.
*
*/
#define DioConf_DioPort_DioPort_19  ((uint8)0x13U)



/**
* @brief          Symbolic name for the port DI_eFuFault1.
*/
#define DioConf_DioChannel_DI_eFuFault1 ((uint16)305U)



/**
* @brief          Symbolic name for the port DI_eFuFault2.
*/
#define DioConf_DioChannel_DI_eFuFault2 ((uint16)306U)



/**
* @brief          Symbolic name for the port DI_eFuFault3.
*/
#define DioConf_DioChannel_DI_eFuFault3 ((uint16)307U)



/**
* @brief          Symbolic name for the port DI_eFuFault4.
*/
#define DioConf_DioChannel_DI_eFuFault4 ((uint16)308U)



/**
* @brief          Symbolic name for the port DI_eFuFault5.
*/
#define DioConf_DioChannel_DI_eFuFault5 ((uint16)309U)



/**
* @brief          Symbolic name for the port DI_IL_Dr_D_OUT3.
*/
#define DioConf_DioChannel_DI_IL_Dr_D_OUT3 ((uint16)310U)



/**
* @brief          Symbolic name for the port DI_IN_KL15.
*/
#define DioConf_DioChannel_DI_IN_KL15 ((uint16)311U)



/**
* @brief          Symbolic name for the port DO_SW_K7.
*/
#define DioConf_DioChannel_DO_SW_K7 ((uint16)312U)



/**
* @brief          Symbolic name for the port DO_SW_K8.
*/
#define DioConf_DioChannel_DO_SW_K8 ((uint16)313U)



/**
* @brief          Symbolic name for the port DO_SW_K9.
*/
#define DioConf_DioChannel_DO_SW_K9 ((uint16)314U)



/**
* @brief          Symbolic name for the port DO_SW_K10.
*/
#define DioConf_DioChannel_DO_SW_K10 ((uint16)315U)



/**
* @brief          Symbolic name for the port DO_SW_K11.
*/
#define DioConf_DioChannel_DO_SW_K11 ((uint16)316U)



/**
* @brief          Symbolic name for the port DO_SW_K12.
*/
#define DioConf_DioChannel_DO_SW_K12 ((uint16)317U)









#endif  /* DIO_CFG_H */
