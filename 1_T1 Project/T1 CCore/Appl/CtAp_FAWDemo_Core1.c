/********************************************************************************
*
*  File name:   CtAp_FAWDemo_Core1.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
*********************************************************************************/

/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"
#include "FM.h"
#include "rtwtypes.h"
#include "FM_private.h"
#include "FM_types.h"
#include "Nrd_Proj.h"
#include "Com_Appl.h"
#include"IoHwAb.h"
#include"PETTER.h"
#include"Adc_AutoSar_Wrapper.h"
#include "petter.h"
#include "Nvm_Appl.h"
#include "Cdd_Interface.h"
#include "PhC_Drv.h"
#include "Pwm3ph.h"
#include "SC2167.h"
#include "Compiler.h"
#include "Platform_Types.h"
#include "FM_FQ.h"
#include "FM_FQ_private.h"
#include "FM_FQ_types.h"
#include "Nrd_Proj.h"
#include "SDADC.h"
/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/
uint32 AppTask5ms1Counter;
uint32 AppTask10ms1Counter;
uint32 AppTask20ms1Counter;
uint32 AppTask50ms1Counter;
uint32 AppTask100ms1Counter;
uint32 AppTask200ms1Counter;
uint32 AppTask500ms1Counter;
uint32 AppTask1000ms1Counter;
FUNC(void, RTE_CODE) RunnableInit_Core1(void)
{
//	FM_FQ_initialize();
//    M2_Pwm_3Phases_Init();
//	M2_PhC_Init();
}

FUNC(void, RTE_CODE) Runnable5ms_Core1(void)
{
//	tri_2ms_FQ();
	AppTask5ms1Counter++;
}

FUNC(void, RTE_CODE) Runnable10ms_Core1(void)
{
	ADC_ReadBuf();
	uDcLnk_FQ=((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_u_DC1_L1))*5/4095)*267.857;
//	tri_10ms_FQ();
	AppTask10ms1Counter++;
}

FUNC(void, RTE_CODE) Runnable20ms_Core1(void)
{
	AppTask20ms1Counter++;
}

FUNC(void, RTE_CODE) Runnable50ms_Core1(void)
{
	AppTask50ms1Counter++;
}

FUNC(void, RTE_CODE) Runnable100ms_Core1(void)
{
	AppTask100ms1Counter++;
}

FUNC(void, RTE_CODE) Runnable200ms_Core1(void)
{
	AppTask200ms1Counter++;
}

FUNC(void, RTE_CODE) Runnable500ms_Core1(void)
{
	AppTask500ms1Counter++;
}
FUNC(void, RTE_CODE) Runnable1000ms_Core1(void)
{
	AppTask1000ms1Counter++;
}
