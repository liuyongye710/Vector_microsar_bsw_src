#include "Icu.h"
#include"petter.h"
#include"IoHwAb.h"
//数字量定义
PETTER_TEST_IO_TYPE PETTER_test={0};
//SPI变量定义
uint32 spi_testData[14];
uint32 spi_send=0;
uint32 spi_pian;
uint32 write_9945_4[14];
uint32 read_9945_4[14];
uint32 write_9945_3[14];
uint32 read_9945_3[14];
uint32 write_fpga[15];


void petter_test()
{
//ADC
	PETTER_test.ADC.ADC_u_DC1_L1           = IoHwAb_AdcIn_ReadChannel(ADC_u_DC1_L1);
	PETTER_test.ADC.ADC_Temp_IGBT_U        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_U);
	PETTER_test.ADC.ADC_Current_DC1_L1     = IoHwAb_AdcIn_ReadChannel(ADC_Current_DC1_L1);
	PETTER_test.ADC.ADC_Temp_IGBT_V        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_V);
	PETTER_test.ADC.ADC_Temp_Motor0        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_Motor0);
	PETTER_test.ADC.ADC_Temp_IGBT_W        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_W);
	PETTER_test.ADC.ADC_u_DCK1_L1          = IoHwAb_AdcIn_ReadChannel(ADC_u_DCK1_L1);
	PETTER_test.ADC.ADC_Temp_IGBT_U2       = IoHwAb_AdcIn_ReadChannel(ADC_Temp_IGBT_U2);
	PETTER_test.ADC.ADC_Current_DC2_L1     = IoHwAb_AdcIn_ReadChannel(ADC_Current_DC2_L1);
	PETTER_test.ADC.ADC_eFuCurrent1_L1     = IoHwAb_AdcIn_ReadChannel(ADC_eFuCurrent1_L1);
	PETTER_test.ADC.ADC_Temp_Motor1        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_Motor1);
	PETTER_test.ADC.ADC_eFuCurrent2_L1     = IoHwAb_AdcIn_ReadChannel(ADC_eFuCurrent2_L1);
//	PETTER_test.ADC.ADC_Decoding_sin_Positive  = IoHwAb_AdcIn_ReadChannel(ADC_Decoding_sin_Positive);
//	PETTER_test.ADC.ADC_Decoding_cos_Positive  = IoHwAb_AdcIn_ReadChannel(ADC_Decoding_cos_Positive);
//	PETTER_test.ADC.ADC_Decoding_Exc_Positive  = IoHwAb_AdcIn_ReadChannel(ADC_Decoding_Exc_Positive);
	PETTER_test.ADC.ADC_eFuCurrent3_L1     = IoHwAb_AdcIn_ReadChannel(ADC_eFuCurrent3_L1);
//	PETTER_test.ADC.ADC_Decoding_sin_Negative  = IoHwAb_AdcIn_ReadChannel(ADC_Decoding_sin_Negative);
//	PETTER_test.ADC.ADC_Decoding_cos_Negative  = IoHwAb_AdcIn_ReadChannel(ADC_Decoding_cos_Negative);
//	PETTER_test.ADC.ADC_Decoding_Exc_Negative  = IoHwAb_AdcIn_ReadChannel(ADC_Decoding_Exc_Negative);
	PETTER_test.ADC.ADC_eFuTemp            = IoHwAb_AdcIn_ReadChannel(ADC_eFuTemp);
	PETTER_test.ADC.ADC_u_DCK2_L1          = IoHwAb_AdcIn_ReadChannel(ADC_u_DCK2_L1);
	PETTER_test.ADC.ADC_AN_25V_Ref         = IoHwAb_AdcIn_ReadChannel(ADC_AN_25V_Ref);
	PETTER_test.ADC.ADC_AD_IO1             = IoHwAb_AdcIn_ReadChannel(ADC_AD_IO1);
	PETTER_test.ADC.ADC_AD_IO2             = IoHwAb_AdcIn_ReadChannel(ADC_AD_IO2);
	PETTER_test.ADC.ADC_AD_IO3             = IoHwAb_AdcIn_ReadChannel(ADC_AD_IO3);
	PETTER_test.ADC.ADC_AD_IO4             = IoHwAb_AdcIn_ReadChannel(ADC_AD_IO4);
	PETTER_test.ADC.ADC_AN_KL30            = IoHwAb_AdcIn_ReadChannel(ADC_AN_KL30);
	PETTER_test.ADC.ADC_Temp_Water0        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_Water0);
	PETTER_test.ADC.ADC_Temp_Motor2        = IoHwAb_AdcIn_ReadChannel(ADC_Temp_Motor2);
	PETTER_test.ADC.ADC_AN_15V_BK          = IoHwAb_AdcIn_ReadChannel(ADC_AN_15V_BK);
//ADC

	IoHwAb_Dio_WriteChannel(DO_LED1, PETTER_test.DO_LED1);
	IoHwAb_Dio_WriteChannel(DO_LED2, PETTER_test.DO_LED2);
	IoHwAb_Dio_WriteChannel(DO_LED3, PETTER_test.DO_LED3);
	IoHwAb_Dio_WriteChannel(DO_LED4, PETTER_test.DO_LED4);
	IoHwAb_Dio_WriteChannel(DO_SA47321_PROG, PETTER_test.DO_SA47321_PROG);
	IoHwAb_Dio_WriteChannel(DO_MCU_CLR1, PETTER_test.DO_MCU_CLR1);
	IoHwAb_Dio_WriteChannel(DO_MCU_CLR2, PETTER_test.DO_MCU_CLR2);
	IoHwAb_Dio_WriteChannel(DO_RT_RDN, PETTER_test.DO_RT_RDN);
	IoHwAb_Dio_WriteChannel(DO_RT_WRN, PETTER_test.DO_RT_WRN);
	IoHwAb_Dio_WriteChannel(DO_RT_SOE, PETTER_test.DO_RT_SOE);
	IoHwAb_Dio_WriteChannel(DO_RT_SAMPLE, PETTER_test.DO_RT_SAMPLE);
	IoHwAb_Dio_WriteChannel(DO_RT_A0, PETTER_test.DO_RT_A0);
	IoHwAb_Dio_WriteChannel(DO_RT_A1, PETTER_test.DO_RT_A1);
	IoHwAb_Dio_WriteChannel(DO_RT_RESETN, PETTER_test.DO_RT_RESETN);
	IoHwAb_Dio_WriteChannel(DO_RT_RES0, PETTER_test.DO_RT_RES0);
	IoHwAb_Dio_WriteChannel(DO_RT_RES1, PETTER_test.DO_RT_RES1);
	IoHwAb_Dio_WriteChannel(DO_CAN4WAKE, PETTER_test.DO_CAN4WAKE);
	IoHwAb_Dio_WriteChannel(DO_PWM_Reset_Driver2, PETTER_test.DO_PWM_Reset_Driver2);
	IoHwAb_Dio_WriteChannel(DO_DB_15V_SW1, PETTER_test.DO_DB_15V_SW1);
	IoHwAb_Dio_WriteChannel(DO_DB_15V_SW2, PETTER_test.DO_DB_15V_SW2);
	IoHwAb_Dio_WriteChannel(DO_POWER_Down, PETTER_test.DO_POWER_Down);
	IoHwAb_Dio_WriteChannel(DO_RLS_EXC_N_EN, PETTER_test.DO_RLS_EXC_N_EN);
	IoHwAb_Dio_WriteChannel(DO_RLS_EXC_EN, PETTER_test.DO_RLS_EXC_EN);
	IoHwAb_Dio_WriteChannel(DO_CAN0_S, PETTER_test.DO_CAN0_S);
	IoHwAb_Dio_WriteChannel(DO_CAN1_S, PETTER_test.DO_CAN1_S);
	IoHwAb_Dio_WriteChannel(DO_CAN2_S, PETTER_test.DO_CAN2_S);
	IoHwAb_Dio_WriteChannel(DO_CAN3_S, PETTER_test.DO_CAN3_S);
	IoHwAb_Dio_WriteChannel(DO_PWM_Reset_Driver, PETTER_test.DO_PWM_Reset_Driver);
	IoHwAb_Dio_WriteChannel(DO_Enable245_1, PETTER_test.DO_Enable245_1);
	IoHwAb_Dio_WriteChannel(DO_Enable245_2, PETTER_test.DO_Enable245_2);
	IoHwAb_Dio_WriteChannel(DO_Enable245_3, PETTER_test.DO_Enable245_3);
	IoHwAb_Dio_WriteChannel(DO_ADC_GPIO1, PETTER_test.DO_ADC_GPIO1);
	IoHwAb_Dio_WriteChannel(DO_SW_K1, PETTER_test.DO_SW_K1);
	IoHwAb_Dio_WriteChannel(DO_SW_K2, PETTER_test.DO_SW_K2);
	IoHwAb_Dio_WriteChannel(DO_SW_K3, PETTER_test.DO_SW_K3);
	IoHwAb_Dio_WriteChannel(DO_SW_K5, PETTER_test.DO_SW_K5);
	IoHwAb_Dio_WriteChannel(DO_SW_K6, PETTER_test.DO_SW_K6);
	IoHwAb_Dio_WriteChannel(DO_HsD_DIAG_EN, PETTER_test.DO_HsD_DIAG_EN);
	IoHwAb_Dio_WriteChannel(DO_HsD_THER, PETTER_test.DO_HsD_THER);
	IoHwAb_Dio_WriteChannel(DO_eFuRST_Driver, PETTER_test.DO_eFuRST_Driver);
	IoHwAb_Dio_WriteChannel(DO_HsD_SEH1235, PETTER_test.DO_HsD_SEH1235);
	IoHwAb_Dio_WriteChannel(DO_HsD_SEL1235, PETTER_test.DO_HsD_SEL1235);
	IoHwAb_Dio_WriteChannel(DO_HsD_SEH6789, PETTER_test.DO_HsD_SEH6789);
	IoHwAb_Dio_WriteChannel(DO_HsD_SEL6789, PETTER_test.DO_HsD_SEL6789);
	IoHwAb_Dio_WriteChannel(DO_HsD_SEH101112, PETTER_test.DO_HsD_SEH101112);
	IoHwAb_Dio_WriteChannel(DO_HsD_SEL101112, PETTER_test.DO_HsD_SEL101112);
	IoHwAb_Dio_WriteChannel(DO_SW_K7, PETTER_test.DO_SW_K7);
	IoHwAb_Dio_WriteChannel(DO_SW_K8, PETTER_test.DO_SW_K8);
	IoHwAb_Dio_WriteChannel(DO_SW_K9, PETTER_test.DO_SW_K9);
	IoHwAb_Dio_WriteChannel(DO_SW_K10, PETTER_test.DO_SW_K10);
	IoHwAb_Dio_WriteChannel(DO_SW_K11, PETTER_test.DO_SW_K11);
	IoHwAb_Dio_WriteChannel(DO_SW_K12, PETTER_test.DO_SW_K12);
	IoHwAb_Dio_WriteChannel(DO_FCCU_EOUT, PETTER_test.DO_FCCU_EOUT);

//DO

//DIO_READ
	PETTER_test.DIO_read.DI_COL_in = IoHwAb_Dio_ReadChannel(DI_COL_in);
	PETTER_test.DIO_read.DI_BSM24_IN = IoHwAb_Dio_ReadChannel(DI_BSM24_IN);
	PETTER_test.DIO_read.DI_AdhesK5 = IoHwAb_Dio_ReadChannel(DI_AdhesK5);
	PETTER_test.DIO_read.DI_AdhesK6 = IoHwAb_Dio_ReadChannel(DI_AdhesK6);
	PETTER_test.DIO_read.DI_AdhesK7 = IoHwAb_Dio_ReadChannel(DI_AdhesK7);
	PETTER_test.DIO_read.DI_AdhesK8 = IoHwAb_Dio_ReadChannel(DI_AdhesK8);
	PETTER_test.DIO_read.DI_AdhesK9 = IoHwAb_Dio_ReadChannel(DI_AdhesK9);
	PETTER_test.DIO_read.DI_AdhesK12 = IoHwAb_Dio_ReadChannel(DI_AdhesK12);
	PETTER_test.DIO_read.DI_SafeState1 = IoHwAb_Dio_ReadChannel(DI_SafeState1);
	PETTER_test.DIO_read.DI_SafeState2 = IoHwAb_Dio_ReadChannel(DI_SafeState2);
	PETTER_test.DIO_read.DI_Fault_UH2 = IoHwAb_Dio_ReadChannel(DI_Fault_UH2);
	PETTER_test.DIO_read.DI_Fault_VH2 = IoHwAb_Dio_ReadChannel(DI_Fault_VH2);
	PETTER_test.DIO_read.DI_Fault_WH2 = IoHwAb_Dio_ReadChannel(DI_Fault_WH2);
	PETTER_test.DIO_read.DI_Fault_UL2 = IoHwAb_Dio_ReadChannel(DI_Fault_UL2);
	PETTER_test.DIO_read.DI_Fault_VL2 = IoHwAb_Dio_ReadChannel(DI_Fault_VL2);
	PETTER_test.DIO_read.DI_Fault_WL2 = IoHwAb_Dio_ReadChannel(DI_Fault_WL2);
	PETTER_test.DIO_read.DI_IL_Dr_D_OUT2 = IoHwAb_Dio_ReadChannel(DI_IL_Dr_D_OUT2);
	PETTER_test.DIO_read.DI_RT_DIR = IoHwAb_Dio_ReadChannel(DI_RT_DIR);
	PETTER_test.DIO_read.DI_Fault_UH = IoHwAb_Dio_ReadChannel(DI_Fault_UH);
	PETTER_test.DIO_read.DI_Fault_VH = IoHwAb_Dio_ReadChannel(DI_Fault_VH);
	PETTER_test.DIO_read.DI_Fault_WH = IoHwAb_Dio_ReadChannel(DI_Fault_WH);
	PETTER_test.DIO_read.DI_Fault_UL = IoHwAb_Dio_ReadChannel(DI_Fault_UL);
	PETTER_test.DIO_read.DI_Fault_VL = IoHwAb_Dio_ReadChannel(DI_Fault_VL);
	PETTER_test.DIO_read.DI_Fault_WL = IoHwAb_Dio_ReadChannel(DI_Fault_WL);
	PETTER_test.DIO_read.DI_IL_Dr_D_OUT1 = IoHwAb_Dio_ReadChannel(DI_IL_Dr_D_OUT1);
	PETTER_test.DIO_read.DI_FastC_Wake = IoHwAb_Dio_ReadChannel(DI_FastC_Wake);
	PETTER_test.DIO_read.DI_Switch0 = IoHwAb_Dio_ReadChannel(DI_Switch0);
	PETTER_test.DIO_read.DI_Switch1 = IoHwAb_Dio_ReadChannel(DI_Switch1);
	PETTER_test.DIO_read.DI_Switch2 = IoHwAb_Dio_ReadChannel(DI_Switch2);
	PETTER_test.DIO_read.DI_Switch3 = IoHwAb_Dio_ReadChannel(DI_Switch3);
	PETTER_test.DIO_read.DI_ACM_EN = IoHwAb_Dio_ReadChannel(DI_ACM_EN);
	PETTER_test.DIO_read.DI_eFuFault1 = IoHwAb_Dio_ReadChannel(DI_eFuFault1);
	PETTER_test.DIO_read.DI_eFuFault2 = IoHwAb_Dio_ReadChannel(DI_eFuFault2);
	PETTER_test.DIO_read.DI_eFuFault3 = IoHwAb_Dio_ReadChannel(DI_eFuFault3);
	PETTER_test.DIO_read.DI_eFuFault4 = IoHwAb_Dio_ReadChannel(DI_eFuFault4);
	PETTER_test.DIO_read.DI_eFuFault5 = IoHwAb_Dio_ReadChannel(DI_eFuFault5);
	PETTER_test.DIO_read.DI_IL_Dr_D_OUT3 = IoHwAb_Dio_ReadChannel(DI_IL_Dr_D_OUT3);
	PETTER_test.DIO_read.DI_IN_KL15 = IoHwAb_Dio_ReadChannel(DI_IN_KL15);
	PETTER_test.DIO_read.DI_RT_LOT_A = IoHwAb_Dio_ReadChannel(DI_RT_LOT_A);
	PETTER_test.DIO_read.DI_RT_DOS_A = IoHwAb_Dio_ReadChannel(DI_RT_DOS_A);
	PETTER_test.DIO_read.DI_HsD_nFR1 = IoHwAb_Dio_ReadChannel(DI_HsD_nFR1);
	PETTER_test.DIO_read.DI_HsD_nFR2 = IoHwAb_Dio_ReadChannel(DI_HsD_nFR2);
	PETTER_test.DIO_read.DI_HsD_nFR3 = IoHwAb_Dio_ReadChannel(DI_HsD_nFR3);

//DIO_READ
//PO
	IoHwAb_PwmOut_SetPeriodAndDuty(PO_eFuPWM3,PETTER_test.PO_eFuPWM3.Period,PETTER_test.PO_eFuPWM3.DutyCycle);
}
