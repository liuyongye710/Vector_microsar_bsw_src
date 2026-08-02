#include "PDU.h"
#include "rtwtypes.h"
#include "PDU_private.h"
#include "IoHwAb.h"
void PDU_INPUT(void) {
	PDU_EfuseT3Current = 0;
	PDU_EfuseT5Current = 0;
	PDU_EfuseT1Current = 10*(((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_eFuCurrent1_L1)))*5/4095-2.5);
	PDU_EfuseT2Current = 10*(((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_eFuCurrent2_L1)))*5/4095-2.5);
	PDU_EfuseT4Current = 10*(((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_eFuCurrent3_L1)))*5/4095-2.5);
	PDU_flgK9StateRaw = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_AdhesK9);
	PDU_EfuseTemp = (real32_T)IoHwAb_AdcIn_ReadChannel(ADC_eFuTemp);
	PDU_EfuseT3CutFaultRead = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_eFuFault3);
	PDU_EfuseT5CutFaultRead = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_eFuFault5);
	PDU_EfuseT1CutFaultRead = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_eFuFault1);
	PDU_EfuseT2CutFaultRead = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_eFuFault2);
	PDU_EfuseT4CutFaultRead = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_eFuFault4);
	PDU_flgKL15 = !(boolean_T)(IoHwAb_Dio_ReadChannel(DI_IN_KL15));
	PDU_BatteryVoltage = 750*((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_u_DC1_L1))*5/4095)/2.8;
	PDU_MainPosVoltage = 750*((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_u_DCK2_L1))*5/4095)/3.74;
	PDU_flgChargeCAN = 0;
	PDU_AttVoltage = 750*((real32_T)(IoHwAb_AdcIn_ReadChannel(ADC_u_DCK1_L1))*5/4095)/3.74;
	PDU_flgK5StateRaw = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_AdhesK5);
	PDU_flgK6StateRaw = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_AdhesK6);
	PDU_flgK7StateRaw = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_AdhesK7);
	PDU_flgK8StateRaw = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_AdhesK8);
	PDU_flgK12StateRaw = !(boolean_T)IoHwAb_Dio_ReadChannel(DI_AdhesK12);
	PDU_flgOverVol = 0;
	return;
}

void PDU_OUTPUT(void) {
	IoHwAb_Dio_WriteChannel(DO_SW_K1, PDU_MainPosCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K2, PDU_AttCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K3, PDU_K3Cmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K5, PDU_PTCCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K6, PDU_BatHeatCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K7, PDU_MECUCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K8, PDU_ACCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K9, PDU_K9Cmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K10, PDU_K10Cmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K11, PDU_MainNegCmd);
	IoHwAb_Dio_WriteChannel(DO_SW_K12, PDU_ReserveCmd);
	if (PDU_EfuseT1Cmd) {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM1, 10000, 16384);
	}
	else {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM1, 10000, 0);
	}
	if (PDU_EfuseT2Cmd) {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM2, 10000, 16384);
	}
	else {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM2, 10000, 0);
	}
	if (PDU_EfuseT3Cmd) {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM3, 10000, 16384);
	}
	else {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM3, 10000, 0);
	}
	if (PDU_EfuseT4Cmd) {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM4, 10000, 16384);
	}
	else {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM4, 10000, 0);
	}
	if (PDU_EfuseT5Cmd) {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM5, 10000, 16384);
	}
	else {
		IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM5, 10000, 0);
	}
	return;
}
