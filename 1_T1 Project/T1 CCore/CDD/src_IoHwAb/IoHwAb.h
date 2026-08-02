/*
 * IoHwAb.h
 *
 *  Created on: 2024年12月20日
 *      Author: liuziyu
 */
#ifndef IOHWAB_H_
#define IOHWAB_H_
#include "typedefs.h"
typedef enum
{
    ADC_Current_U_L1,
    ADC_Current_W_L2,
    ADC_u_DC1_L1,
    ADC_Temp_IGBT_U,
    ADC_Current_V_L1,
    ADC_Current_U_L2,
    ADC_Current_DC1_L1,
    ADC_Temp_IGBT_V,
    ADC_Current_W_L1,
    ADC_Current_V_L2,
    ADC_Temp_Motor0,
    ADC_Temp_IGBT_W,
    ADC_Current_U2_L1,
    ADC_Current_W2_L2,
    ADC_u_DCK1_L1,
    ADC_Temp_IGBT_U2,
    ADC_Current_V2_L1,
    ADC_Current_U2_L2,
    ADC_Current_DC2_L1,
    ADC_eFuCurrent1_L1,
    ADC_Current_W2_L1,
    ADC_Current_V2_L2,
    ADC_Temp_Motor1,
    ADC_eFuCurrent2_L1,
    ADC_Decoding_sin_Positive,
    ADC_Decoding_cos_Positive,
    ADC_Decoding_Exc_Positive,
    ADC_eFuCurrent3_L1,
    ADC_Decoding_sin_Negative,
    ADC_Decoding_cos_Negative,
    ADC_Decoding_Exc_Negative,
    ADC_eFuTemp,
    ADC_u_DCK2_L1,
    ADC_AN_25V_Ref,
    ADC_AD_IO1,
    ADC_AD_IO2,
    ADC_AD_IO3,
    ADC_AD_IO4,
    ADC_AN_KL30,
    ADC_Temp_Water0,
    ADC_Temp_Motor2,
    ADC_AN_15V_BK,
} IoHwAb_AdcHwUnitInputHwChannelType;

typedef enum
{
    DO_LED1,
    DO_LED2,
    DO_LED3,
    DO_LED4,
    DO_SA47321_PROG,
    DO_MCU_CLR1,
    DO_MCU_CLR2,
    DO_RT_RDN,
    DO_RT_WRN,
    DO_RT_SOE,
    DO_RT_SAMPLE,
    DO_RT_A0,
    DO_RT_A1,
    DO_RT_RESETN,
    DO_RT_RES0,
    DO_RT_RES1,
    DO_CAN4WAKE,
    DO_PWM_Reset_Driver2,
    DO_DB_15V_SW1,
    DO_DB_15V_SW2,
    DO_POWER_Down,
    DO_RLS_EXC_N_EN,
    DO_RLS_EXC_EN,
    DO_CAN0_S,
    DO_CAN1_S,
    DO_CAN2_S,
    DO_CAN3_S,
    DO_PWM_Reset_Driver,
    DO_Enable245_1,
    DO_Enable245_2,
    DO_Enable245_3,
    DO_ADC_GPIO1,
    DO_SW_K1,
    DO_SW_K2,
    DO_SW_K3,
    DO_SW_K5,
    DO_SW_K6,
    DO_HsD_DIAG_EN,
    DO_HsD_THER,
    DO_eFuRST_Driver,
    DO_HsD_SEH1235,
    DO_HsD_SEL1235,
    DO_HsD_SEH6789,
    DO_HsD_SEL6789,
    DO_HsD_SEH101112,
    DO_HsD_SEL101112,
    DO_SW_K7,
    DO_SW_K8,
    DO_SW_K9,
    DO_SW_K10,
    DO_SW_K11,
    DO_SW_K12,
    DO_FCCU_EOUT,
} IoHwAb_DioOutputHwChannelType;

typedef enum
{
    DI_COL_in,
    DI_BSM24_IN,
    DI_AdhesK5,
    DI_AdhesK6,
    DI_AdhesK7,
    DI_AdhesK8,
    DI_AdhesK9,
    DI_AdhesK12,
    DI_SafeState1,
    DI_SafeState2,
    DI_Fault_UH2,
    DI_Fault_VH2,
    DI_Fault_WH2,
    DI_Fault_UL2,
    DI_Fault_VL2,
    DI_Fault_WL2,
    DI_IL_Dr_D_OUT2,
    DI_RT_DIR,
    DI_Fault_UH,
    DI_Fault_VH,
    DI_Fault_WH,
    DI_Fault_UL,
    DI_Fault_VL,
    DI_Fault_WL,
    DI_IL_Dr_D_OUT1,
    DI_FastC_Wake,
    DI_Switch0,
    DI_Switch1,
    DI_Switch2,
    DI_Switch3,
    DI_ACM_EN,
    DI_eFuFault1,
    DI_eFuFault2,
    DI_eFuFault3,
    DI_eFuFault4,
    DI_eFuFault5,
    DI_IL_Dr_D_OUT3,
    DI_IN_KL15,
    DI_RT_LOT_A,
    DI_RT_DOS_A,
    DI_HsD_nFR1,
    DI_HsD_nFR2,
    DI_HsD_nFR3,
} IoHwAb_DioInputHwChannelType;

typedef enum
{
    PO_eFuPWM1,
    PO_eFuPWM2,
    PO_eFuPWM3,
    PO_eFuPWM4,
    PO_eFuPWM5,
    PO_PWM_EFN,
    PO_PWM_UL,
    PO_PWM_VL,
    PO_PWM_WL,
    PO_PWM_UH,
    PO_PWM_VH,
    PO_PWM_WH,
    PO_PWM_actADC,
    PO_PWM_UH2,
    PO_PWM_VH2,
    PO_PWM_WH2,
    PO_PWM_UL2,
    PO_PWM_WL2,
    PO_PWM_VL2,
    PO_PWM2_actADC,
    PO_SDCRC,
    PO_RTS_EXC,
    PO_RTS_EXC_N,
    PO_SA47321_WatchDog,
    PO_SA47321_ERR,
    PO_PWM_triggered_ADC_soft_decoding_diagnosis_Positive,
    PO_PWM_triggered_ADC_soft_decoding_diagnosis_Negative,
} IoHwAb_PwmOutputHwChannelType;

typedef struct {
	uint8 Busbar_OV;              // 对应 FAULT_BUSBAR_OV
	uint8 SA47321_nINT_ERROR;
	uint8 Smotor_CURRENT_OC;		//对应FAULT_Smotor_CURRENT_OC
	uint8 Mmotor_IGBT_ERROR;       // 对应 FAULT_Mmotor_IGBT_ERROR
	uint8 Efuse_CURRENT_OC;        // 对应 FAULT_Efuse_CURRENT_OC
	uint8 Smotor_IGBT_ERROR;       // 对应 FAULT_Smotor_IGBT_ERROR
	uint8 Mmotor_CURRENT_OC;       // 对应 FAULT_Mmotor_CURRENT_OC
	uint8 Efuse_ERROR;             // 对应 FAULT_Efuse_ERROR
}FaultCounter;
typedef struct {
	bool Busbar_OV;              // 对应 FAULT_BUSBAR_OV
	bool SA47321_nINT_ERROR;
	bool Smotor_CURRENT_OC;		//对应FAULT_Smotor_CURRENT_OC
	bool Mmotor_IGBT_ERROR;       // 对应 FAULT_Mmotor_IGBT_ERROR
	bool Efuse_CURRENT_OC;        // 对应 FAULT_Efuse_CURRENT_OC
	bool Smotor_IGBT_ERROR;       // 对应 FAULT_Smotor_IGBT_ERROR
	bool Mmotor_CURRENT_OC;       // 对应 FAULT_Mmotor_CURRENT_OC
	bool Efuse_ERROR;             // 对应 FAULT_Efuse_ERROR
}FaultFlags;
extern void Adc_StartConversion(void);
extern void Adc_InitResultBuf(void);
extern void ADC_ReadBuf(void);
extern void IoHwAb_Dio_WriteChannel(IoHwAb_DioOutputHwChannelType Ty_OS_Hwa_LowSideProc_IOx, uint8 DIO_Level);
extern uint8 IoHwAb_Dio_ReadChannel(IoHwAb_DioInputHwChannelType ChannelId);
extern void IoHwAb_PwmOut_SetPeriodAndDuty (IoHwAb_PwmOutputHwChannelType ChannelId,  uint32 Period,  uint16 DutyCycle);
extern void External_ISR_enable(void);
extern void Emgercy_SPO(void);
extern void Emgercy_ASC(void);
extern void Emgercy_SWITCH_PWMMODE(uint8 PWMmode_AfEmrgncy);
extern void Handle_BUSBAR_OV(void);
extern void Handle_SA47321_nINT_ERROR(void);
extern void Handle_Smotor_CURRENT_OC(void);
extern void Handle_Mmotor_IGBT_ERROR(void);
extern void Handle_Efuse_CURRENT_OC(void);
extern void Handle_Smotor_IGBT_ERROR(void);
extern void Handle_Mmotor_CURRENT_OC(void);
extern void Handle_Efuse_ERROR(void);
#endif /* IOHWAB_H_ */
