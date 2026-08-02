/*
********************************************************************************
*
* File name: EcuM_Callout_Init.c
*
* Copyright 2019-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
*  Version: 3.0
*  Author/Date : yong.zhang/2020.10.24
*  Change: New created
*  Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: TianL/2024.8.5
* Change: Modify copyright.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "EcuM.h"


#include "Adc.h"
#include "Can.h"
#include "Cal_Appl.h"
#include "Fls.h"
#include "Gpt.h"
#include "Icu.h"
//#include "Lin.h"
#include "Port.h"
#include "Pwm.h"
#include "Spi.h"
#include "Os.h"
#include "SDADC.h"
#include"SC2167.h"
#include "FM_FQ.h"
#include"POWER_Ctrl.h"
#include "T1_AppInterface.h"/* for T1 */
/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"
#include "IoHwAb.h"
#include"smpu_demo.h"
#include "Cdd_Common.h"
#include "VX1000If.h"
#include"eMios.h"
extern CONST(Adc_ConfigType, ADC_CONST) Adc_Config;
extern CONST(Gpt_GtmCmuConfigType, MCL_CONST) Gpt_Gtm_Cmu_PBCfg;
extern CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet;
extern CONST(Spi_ConfigType, SPI_CONST) Spi_Configuration;
extern CONST(EDma_ConfigType, EDMA_CONST) EDma_Config;
extern CONST(SdAdc_TotalConfigType, SDADC_CONST) SdAdc_TotalConfig;
extern CONST(eMIOS_ConfigType, ADC_VAR) eMIOS_Config;
FUNC(void, ECUM_CODE) EcuM_InitZero_core0(void){
//    SMPU_RW_Test(0);
}


FUNC(void, ECUM_CODE) EcuM_InitZero_core1(void){
//    SMPU_RW_Test(0);
}

FUNC(void, ECUM_CODE) EcuM_InitZero_core2(void){
    SMPU_RW_Test(0);
}
#define SDADC_DATA_SIZE 32
#define SDADC_START_SEC_VAR_SHARED_INIT
#include "Sdadc_MemMap.h"
uint32 Buffer[SDADC_DATA_SIZE] = {0};
#define SDADC_STOP_SEC_VAR_SHARED_INIT
#include "Sdadc_MemMap.h"
FUNC(void, ECUM_CODE) EcuM_InitOne_core0(void){

	Spi_Init(&Spi_Configuration);
    EDMA_Init(&EDma_Config);
    Adc_Init(&Adc_Config);
    Adc_InitResultBuf();
    Adc_InitOperationMode_Core0();
	POWER_init();
//    Sdadc_Init(&SdAdc_TotalConfig);
//    Sdadc_SetupResultBuffer(1, Buffer, SDADC_DATA_SIZE);
//    Sdadc_StartModulation(1);
	SC2167_init();
    Pwm_Init(&Pwm_Config);
//	Gp_GtmCCFC_GtmInit();
//	Gp_GtmCCFC_Atom_Init();
//	Gp_GtmCCFC_Mcs_Init();
//	Gp_06_Pwm3ph_Init();
//	Gp_06_RslvrSw_Init();
	FM_initialize();
    M1_Pwm_3Phases_Init();
    M1_PhC_Init();
	Os_Init();
#if(VX1000If_IsVX1000DriverAccessEnabled==true)
    VX1000If_InitAsyncEnd();
#endif
	T1_AppInit();/* for T1 */
}

FUNC(void, ECUM_CODE) EcuM_InitOne_core1(void){
	EDMA_Init(&EDma_Config);
    Adc_Init(&Adc_Config);
    Adc_InitResultBuf();
    Adc_InitOperationMode_Core1();
    GPT_Gtm_Init(&Gpt_Gtm_Cmu_PBCfg);
	Pwm_Init(&Pwm_Config);
	FM_FQ_initialize();
    M2_Pwm_3Phases_Init();
	M2_PhC_Init();
	Os_Init();
#if(VX1000If_IsVX1000DriverAccessEnabled==true)
    VX1000If_InitAsyncEnd();
#endif
	T1_AppInit();/* for T1 */
}

FUNC(void, ECUM_CODE) EcuM_InitOne_core2(void){
	Can_Init(&Can_Config);
	CalAppl_CalSramInit();/* WangM */
    Adc_Init(&Adc_Config);
    Adc_InitResultBuf();
	Fls_Init(&Fls_Config);
	Port_Init(&PortContainer);
    GPT_Gtm_Init(&Gpt_Gtm_Cmu_PBCfg);
    Gpt_Stm_LLD_SetPrescaler(1,1);
	Gpt_Stm_LLD_ModuleEnable(1);
    Gpt_Init(&GptChannelConfigSet);
//    eMIOS_Init(&eMIOS_Config);
//    EMIOS0_PTR->UC[7].C.B.MODE =0X0D;
//    EMIOS0_PTR->UC[7].C.B.EDSEL = 1;
//    EMIOS0_PTR->UC[7].C.B.UCPREN =1 ;
	Spi_Init(&Spi_Configuration);
	Pwm_Init(&Pwm_Config);
	External_ISR_enable();
	IoHwAb_Dio_WriteChannel(DO_Enable245_1, 1);
	IoHwAb_Dio_WriteChannel(DO_Enable245_2, 1);
	IoHwAb_Dio_WriteChannel(DO_Enable245_3, 1);
	IoHwAb_Dio_WriteChannel(DO_CAN0_S, 1);
	IoHwAb_Dio_WriteChannel(DO_CAN1_S, 1);
	IoHwAb_Dio_WriteChannel(DO_CAN2_S, 1);
	IoHwAb_Dio_WriteChannel(DO_CAN3_S, 1);
//	IoHwAb_Dio_WriteChannel(DO_SW1, 1);
#if(VX1000If_IsVX1000DriverAccessEnabled==true)
	VX1000If_Init();
    VX1000If_InitAsyncStart();
    VX1000If_InitAsyncEnd();
#endif
	Os_Init();
	T1_AppInit();/* for T1 */
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#define ECUM_START_SEC_CONFIG_DATA
#include "EcuM_MemMap.h"

CONST(EcuM_DriverInitFuncSt,ECUM_CONFIG_DATA) EcuM_DriverInitFuncTbl[ECUM_NUMBER_OF_CORES]=
{
	{0, EcuM_InitZero_core0, EcuM_InitOne_core0},
	{1, EcuM_InitZero_core1, EcuM_InitOne_core1},
	{2, EcuM_InitZero_core2, EcuM_InitOne_core2},
};

#define ECUM_STOP_SEC_CONFIG_DATA
#include "EcuM_MemMap.h"

