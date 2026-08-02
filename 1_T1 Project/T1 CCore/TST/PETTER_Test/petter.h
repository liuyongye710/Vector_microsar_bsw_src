#ifndef PETTER_H_
#define PETTER_H_
#include "Platform_Types.h"
typedef struct{
	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_eFuPWM1;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_eFuPWM2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_eFuPWM3;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_eFuPWM4;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_eFuPWM5;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_EFN;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_UL;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_VL;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_WL;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_UH;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_VH;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_WH;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_triADC;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_UH2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_VH2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_WH2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_UL2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_WL2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM_VL2;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_PWM2_triADC;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_SA7321_ERR;

	struct {
	    uint32 Period;
	    uint16 DutyCycle;
	} PO_SA7321_WatchDog;
	uint8 DO_LED1;
	uint8 DO_LED2;
	uint8 DO_LED3;
	uint8 DO_LED4;
	uint8 DO_SA47321_PROG;
	uint8 DO_MCU_CLR1;
	uint8 DO_MCU_CLR2;
	uint8 DO_RT_RDN;
	uint8 DO_RT_WRN;
	uint8 DO_RT_SOE;
	uint8 DO_RT_SAMPLE;
	uint8 DO_RT_A0;
	uint8 DO_RT_A1;
	uint8 DO_RT_RESETN;
	uint8 DO_RT_RES0;
	uint8 DO_RT_RES1;
	uint8 DO_CAN4WAKE;
	uint8 DO_PWM_Reset_Driver2;
	uint8 DO_DB_15V_SW1;
	uint8 DO_DB_15V_SW2;
	uint8 DO_POWER_Down;
	uint8 DO_RLS_EXC_N_EN;
	uint8 DO_RLS_EXC_EN;
	uint8 DO_CAN0_S;
	uint8 DO_CAN1_S;
	uint8 DO_CAN2_S;
	uint8 DO_CAN3_S;
	uint8 DO_PWM_Reset_Driver;
	uint8 DO_Enable245_1;
	uint8 DO_Enable245_2;
	uint8 DO_Enable245_3;
	uint8 DO_ADC_GPIO1;
	uint8 DO_SW_K1;
	uint8 DO_SW_K2;
	uint8 DO_SW_K3;
	uint8 DO_SW_K5;
	uint8 DO_SW_K6;
	uint8 DO_HsD_DIAG_EN;
	uint8 DO_HsD_THER;
	uint8 DO_eFuRST_Driver;
	uint8 DO_HsD_SEH1235;
	uint8 DO_HsD_SEL1235;
	uint8 DO_HsD_SEH6789;
	uint8 DO_HsD_SEL6789;
	uint8 DO_HsD_SEH101112;
	uint8 DO_HsD_SEL101112;
	uint8 DO_SW_K7;
	uint8 DO_SW_K8;
	uint8 DO_SW_K9;
	uint8 DO_SW_K10;
	uint8 DO_SW_K11;
	uint8 DO_SW_K12;
	uint8 DO_FCCU_EOUT;

	struct{
		uint16 ADC_Current_U_L1;
		uint16 ADC_Current_W_L2;
		uint16 ADC_u_DC1_L1;
		uint16 ADC_Temp_IGBT_U;
		uint16 ADC_Current_V_L1;
		uint16 ADC_Current_U_L2;
		uint16 ADC_Current_DC1_L1;
		uint16 ADC_Temp_IGBT_V;
		uint16 ADC_Current_W_L1;
		uint16 ADC_Current_V_L2;
		uint16 ADC_Temp_Motor0;
		uint16 ADC_Temp_IGBT_W;
		uint16 ADC_Current_U2_L1;
		uint16 ADC_Current_W2_L2;
		uint16 ADC_u_DCK1_L1;
		uint16 ADC_Temp_IGBT_U2;
		uint16 ADC_Current_V2_L1;
		uint16 ADC_Current_U2_L2;
		uint16 ADC_Current_DC2_L1;
		uint16 ADC_eFuCurrent1_L1;
		uint16 ADC_Current_W2_L1;
		uint16 ADC_Current_V2_L2;
		uint16 ADC_Temp_Motor1;
		uint16 ADC_eFuCurrent2_L1;
		uint16 ADC_Decoding_sin_Positive;
		uint16 ADC_Decoding_cos_Positive;
		uint16 ADC_Decoding_Exc_Positive;
		uint16 ADC_eFuCurrent3_L1;
		uint16 ADC_Decoding_sin_Negative;
		uint16 ADC_Decoding_cos_Negative;
		uint16 ADC_Decoding_Exc_Negative;
		uint16 ADC_eFuTemp;
		uint16 ADC_u_DCK2_L1;
		uint16 ADC_AN_25V_Ref;
		uint16 ADC_AD_IO1;
		uint16 ADC_AD_IO2;
		uint16 ADC_AD_IO3;
		uint16 ADC_AD_IO4;
		uint16 ADC_AN_KL30;
		uint16 ADC_Temp_Water0;
		uint16 ADC_Temp_Motor2;
		uint16 ADC_AN_15V_BK;

	}ADC;

	struct{
		uint8 DI_COL_in;
		uint8 DI_BSM24_IN;
		uint8 DI_AdhesK5;
		uint8 DI_AdhesK6;
		uint8 DI_AdhesK7;
		uint8 DI_AdhesK8;
		uint8 DI_AdhesK9;
		uint8 DI_AdhesK12;
		uint8 DI_SafeState1;
		uint8 DI_SafeState2;
		uint8 DI_Fault_UH2;
		uint8 DI_Fault_VH2;
		uint8 DI_Fault_WH2;
		uint8 DI_Fault_UL2;
		uint8 DI_Fault_VL2;
		uint8 DI_Fault_WL2;
		uint8 DI_IL_Dr_D_OUT2;
		uint8 DI_RT_DIR;
		uint8 DI_Fault_UH;
		uint8 DI_Fault_VH;
		uint8 DI_Fault_WH;
		uint8 DI_Fault_UL;
		uint8 DI_Fault_VL;
		uint8 DI_Fault_WL;
		uint8 DI_IL_Dr_D_OUT1;
		uint8 DI_FastC_Wake;
		uint8 DI_Switch0;
		uint8 DI_Switch1;
		uint8 DI_Switch2;
		uint8 DI_Switch3;
		uint8 DI_ACM_EN;
		uint8 DI_eFuFault1;
		uint8 DI_eFuFault2;
		uint8 DI_eFuFault3;
		uint8 DI_eFuFault4;
		uint8 DI_eFuFault5;
		uint8 DI_IL_Dr_D_OUT3;
		uint8 DI_IN_KL15;
		uint8 DI_RT_LOT_A;
		uint8 DI_RT_DOS_A;
		uint8 DI_HsD_nFR1;
		uint8 DI_HsD_nFR2;
		uint8 DI_HsD_nFR3;

	}DIO_read;
}PETTER_TEST_IO_TYPE;
extern PETTER_TEST_IO_TYPE PETTER_test;
//SPI变量定义
extern uint32 spi_testData[14];
extern uint32 spi_send;
extern uint32 spi_pian;
extern uint32 write_9945_4[14];
extern uint32 read_9945_4[14];
extern uint32 write_9945_3[14];
extern uint32 read_9945_3[14];
extern uint32 write_fpga[15];

#endif
