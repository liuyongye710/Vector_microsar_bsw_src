/********************************************************************************
*
*  File name:   CtAp_FAWDemo_Core2.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
*********************************************************************************/

/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"
#include "IoHwAb.h"
#include "FM.h"
#include "rtwtypes.h"
#include "FM_private.h"
#include "FM_types.h"
#include "Nrd_Proj.h"
#include "Com_Appl.h"
#include "petter.h"
#include "PDU_private.h"
uint32 AppTask1ms2Counter;
uint32 AppTask4ms2Counter;
uint32 AppTask5ms2Counter;
uint32 AppTask10ms2Counter;
uint32 AppTask20ms2Counter;
uint32 AppTask50ms2Counter;
uint32 AppTask100ms2Counter;
uint32 AppTask200ms2Counter;
uint32 AppTask500ms2Counter;
uint32 AppTask1000ms2Counter;
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

FUNC(void, RTE_CODE) RunnableInit_Core2(void)
{
	IoHwAb_Dio_WriteChannel(DO_POWER_Down,1);
}

FUNC(void, RTE_CODE) Runnable1ms_Core2(void)
{
	AppTask1ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable4ms_Core2(void)
{

	AppTask4ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable5ms_Core2(void)
{
	AppTask5ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable10ms_Core2(void)
{
	ADC_ReadBuf();
	Adc_StartConversion();
	AppTask10ms2Counter++;
//		petter_test();
//	PDU_INPUT();
//	PDU_ReMain();
//	PDU_OUTPUT();
//	Com_ReadRxMessage(Hnd_Msg_Rx_CCVSHCU_D3_sO0,&ccvs_hcu);
//	Com_ReadRxMessage(Hnd_Msg_Rx_HCUMCU_D3_sO0,&hcu_mcu);
//	SCT();
//	IoHwAb_Dio_WriteChannel(DO_POWER_Down,bus_kl23_state);
//    Com_WriteTxMessage( Hnd_Msg_Tx_MCU1_D3_sO0,tx_MCU_1);
//    Com_WriteTxMessage( Hnd_Msg_Tx_MCU2_D3_sO0,tx_MCU_2);
//    Com_WriteTxMessage( Hnd_Msg_Tx_MCU3_D3_sO0,tx_MCU_3);

}

FUNC(void, RTE_CODE) Runnable20ms_Core2(void)
{
	AppTask20ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable50ms_Core2(void)
{

	AppTask50ms2Counter++;
	debounceKeyStatusFilter();//BHY
	shutDownRequest();
}

FUNC(void, RTE_CODE) Runnable100ms_Core2(void)
{

	AppTask100ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable200ms_Core2(void)
{
	AppTask200ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable500ms_Core2(void)
{
	AppTask500ms2Counter++;
}

FUNC(void, RTE_CODE) Runnable1000ms_Core2(void)
{
	AppTask1000ms2Counter++;
//	Com_WriteTxMessage( Hnd_Msg_Tx_ECMCU_D3_sO0,tx_EC_MCU);

}
