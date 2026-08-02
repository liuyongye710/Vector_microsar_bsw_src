/********************************************************************************
*
*  File name:   CtAp_FAWDemo_Core0.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
*********************************************************************************/

/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"
#include "petter.h"
#include "IoHwAb.h"
#include "Nvm_Appl.h"

#include "Cdd_Interface.h"
#include "PhC_Drv.h"
#include "Pwm3ph.h"

#include "SC2167.h"

#include "Compiler.h"
#include "Platform_Types.h"
#include "FM.h"
#include "rtwtypes.h"
#include "FM_private.h"
#include "FM_types.h"
#include "Nrd_Proj.h"
#include "Com_Appl.h"
#include "IoHwAb.h"
#include"SDADC.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/
#define XCP_START_SEC_CONST_CORE0_BLOCK0
#include "FAW_MemMap.h"
    // const
const volatile uint8 xcpTest_U8_CalData01 = 0x88;
const volatile uint8 xcpTest_U8_CalData02 = 0x51;
const volatile uint8 xcpTest_U8_CalData03 = 0x52;
const volatile uint8 xcpTest_U8_CalData04 = 0x53;
const volatile uint8 xcpTest_U8_CalData05 = 0x54;
const volatile uint8 xcpTest_U8_CalData06 = 0x55;
const volatile uint8 xcpTest_U8_CalData07 = 0x56;
const volatile uint8 xcpTest_U8_CalData08 = 0x57;
const volatile uint8 xcpTest_U8_CalData09 = 0x58;
const volatile uint8 xcpTest_U8_CalData10 = 0x59;
const volatile uint16 xcpTest_U16_CalData01 = 0x1110;
const volatile uint16 xcpTest_U16_CalData02 = 0xDD11;
const volatile uint16 xcpTest_U16_CalData03 = 0xDD12;
const volatile uint16 xcpTest_U16_CalData04 = 0xDD13;
const volatile uint16 xcpTest_U16_CalData05 = 0xDD14;
const volatile uint16 xcpTest_U16_CalData06 = 0xDD15;
const volatile uint16 xcpTest_U16_CalData07 = 0xDD16;
const volatile uint16 xcpTest_U16_CalData08 = 0xDD17;
const volatile uint16 xcpTest_U16_CalData09 = 0xDD18;
const volatile uint16 xcpTest_U16_CalData10 = 0xDD19;
const volatile uint32 xcpTest_U32_CalData01 = 0xAAAAAA;
const volatile uint32 xcpTest_U32_CalData02 = 0x1AFE11;
const volatile uint32 xcpTest_U32_CalData03 = 0x1AFE12;
const volatile uint32 xcpTest_U32_CalData04 = 0x1AFE13;
const volatile uint32 xcpTest_U32_CalData05 = 0x1AFE14;
const volatile uint32 xcpTest_U32_CalData06 = 0x1AFE15;
const volatile uint32 xcpTest_U32_CalData07 = 0x1AFE16;
const volatile uint32 xcpTest_U32_CalData08 = 0x1AFE17;
const volatile uint32 xcpTest_U32_CalData09 = 0x1AFE18;
const volatile uint32 xcpTest_U32_CalData10 = 0x1AFE19;
#define XCP_STOP_SEC_CONST_CORE0_BLOCK0
#include "FAW_MemMap.h"

uint8 xcpTest;
/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/
uint32 AppTask2ms0Counter;
uint32 AppTask10ms0Counter;
uint32 AppTask20ms0Counter;
uint32 AppTask50ms0Counter;
uint32 AppTask100ms0Counter;
uint32 AppTask200ms0Counter;
uint32 AppTask500ms0Counter;
uint32 AppTask1000ms0Counter;
FUNC(void, RTE_CODE) RunnableInit_Core0(void)
{
	xcpTest = xcpTest_U8_CalData01;
}

FUNC(void, RTE_CODE) Runnable2ms_Core0(void)
{
	tri_2ms();
	FAW_CDD_ExecTimeCal(&isrExcutionTime);
	FAW_CDD_ExecTimeCal(&isrASWExcutionTime);
	AppTask2ms0Counter++;
}

FUNC(void, RTE_CODE) Runnable10ms_Core0(void)
{
	ADC_ReadBuf();
//	real32_T E_U;
//	real32_T E_V;
//	real32_T E_W;
//	uDcLnk=((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_u_DC1_L1))*5/4095)*267.857;
//	E_U=((uint16_T)(IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_U))*5/4095);
//	tDBCTempU=-29.73*(E_U*E_U*E_U)+ 343.6*(E_U*E_U)-1366*E_U+1908;
//	E_V=((uint16_T)(IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_V))*5/4095);
//	tDBCTempV=-29.73*(E_V*E_V*E_V)+343.6*(E_V*E_V)-1366*E_V+1908;
//	E_W=((uint16_T)(IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_W))*5/4095);
//	tDBCTempW=-29.73*(E_W*E_W*E_W)+343.6*(E_W*E_W)-1366*E_W+1908;
//	tmoterTempV=(uint16_T)(((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_Temp_Motor1))*5/4095)*308.5-382.3);
//	VAR_Bsw_bt15_b=(boolean_T)(IoHwAb_Dio_ReadChannel(DI_IN_KL15));
//	IoHwAb_Dio_WriteChannel(DO_SW1, 1);
//	IoHwAb_Dio_WriteChannel(DO_SW_K2, 1);
//	VAR_flg_ov_b=ISR_ERR_Flags.Busbar_OV;
//	VAR_flg_oc_b=ISR_ERR_Flags.Mmotor_CURRENT_OC;
//	tri_10ms();
//	lv_power_down_enable=(uint8)SCF_LwPwrDwn;
//	Emgercy_SWITCH_PWMMODE(Var_stPWMmode_AfEmrgncy_u8);
	AppTask10ms0Counter++;
}

FUNC(void, RTE_CODE) Runnable20ms_Core0(void)
{
	AppTask20ms0Counter++;
}

FUNC(void, RTE_CODE) Runnable50ms_Core0(void)
{
	AppTask50ms0Counter++;
}

FUNC(void, RTE_CODE) Runnable100ms_Core0(void)
{
	AppTask100ms0Counter++;

}

FUNC(void, RTE_CODE) Runnable200ms_Core0(void)
{
	AppTask200ms0Counter++;
}

FUNC(void, RTE_CODE) Runnable500ms_Core0(void)
{
	AppTask500ms0Counter++;
}

FUNC(void, RTE_CODE) Runnable1000ms_Core0(void)
{
	AppTask1000ms0Counter++;

}
