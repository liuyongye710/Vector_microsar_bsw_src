/*
 * IoHwAb.c
 *
 *  Created on: 2024年12月20日
 *      Author: liuziyu
 */
#include "IoHwAb.h"
#include "Dio.h"
#include "Adc.h"
#include"petter.h"
#include"Os_Types_Cfg.h"
static Adc_ValueGroupType resultbuffer_0_10ms[2];
static Adc_ValueGroupType resultbuffer_1_10ms[2];
static Adc_ValueGroupType resultbuffer_2_10ms[2];
static Adc_ValueGroupType resultbuffer_3_10ms[2];
static Adc_ValueGroupType resultbuffer_4_10ms[2];
static Adc_ValueGroupType resultbuffer_5_10ms[2];
static Adc_ValueGroupType resultbuffer_6_10ms[1];
static Adc_ValueGroupType resultbuffer_7_10ms[1];
static Adc_ValueGroupType resultbuffer_8_10ms[2];
static Adc_ValueGroupType resultbuffer_9_10ms[8];

Adc_ValueGroupType DataBuffer_0_10ms[2];
Adc_ValueGroupType DataBuffer_1_10ms[2];
Adc_ValueGroupType DataBuffer_2_10ms[2];
Adc_ValueGroupType DataBuffer_3_10ms[2];
Adc_ValueGroupType DataBuffer_4_10ms[2];
Adc_ValueGroupType DataBuffer_5_10ms[2];
Adc_ValueGroupType DataBuffer_6_10ms[2];
Adc_ValueGroupType DataBuffer_7_10ms[2];
Adc_ValueGroupType DataBuffer_8_10ms[2];
Adc_ValueGroupType DataBuffer_9_10ms[8];
extern VAR(Adc_RunningGroupType, ADC_VAR) sAdc_RunningGroup[2][18];
void Adc_StartConversion(void)
{
	CoreIdType coreID;
	coreID=GetCoreID();
	if(coreID==OS_CORE_ID_0)
	{
		Adc_StartGroupConversion(1);
		Adc_StartGroupConversion(3);
		Adc_StartGroupConversion(5);
	}
	if(coreID==OS_CORE_ID_1)
	{
		Adc_StartGroupConversion(7);
		Adc_StartGroupConversion(9);
		Adc_StartGroupConversion(11);
	}
	if(coreID==OS_CORE_ID_2)
	{
		Adc_StartGroupConversion(13);
		Adc_StartGroupConversion(15);
		Adc_StartGroupConversion(16);
		Adc_StartGroupConversion(17);
	}
}
void Adc_InitResultBuf(void){
	CoreIdType coreID;
	coreID=GetCoreID();
	if(coreID==OS_CORE_ID_0)
	{
		Adc_SetupResultBuffer(1,DataBuffer_0_10ms);
		Adc_SetupResultBuffer(3,DataBuffer_1_10ms);
		Adc_SetupResultBuffer(5,DataBuffer_2_10ms);
    Adc_EnableHardwareTrigger(1);
    Adc_EnableHardwareTrigger(3);
    Adc_EnableHardwareTrigger(5);
	}
	if(coreID==OS_CORE_ID_1)
	{
		Adc_SetupResultBuffer(7,DataBuffer_3_10ms);
		Adc_SetupResultBuffer(9,DataBuffer_4_10ms);
		Adc_SetupResultBuffer(11,DataBuffer_5_10ms);
	Adc_EnableHardwareTrigger(7);
	Adc_EnableHardwareTrigger(9);
	Adc_EnableHardwareTrigger(11);
	}
	if(coreID==OS_CORE_ID_2)
	{
		Adc_SetupResultBuffer(13,DataBuffer_6_10ms);
		Adc_SetupResultBuffer(15,DataBuffer_7_10ms);
		Adc_SetupResultBuffer(16,DataBuffer_8_10ms);
		Adc_SetupResultBuffer(17,DataBuffer_9_10ms);
	}
}

void ADC_ReadBuf(void){
	CoreIdType coreID;
	coreID=GetCoreID();
	if(coreID==OS_CORE_ID_0)
	{
		sAdc_RunningGroup[0][1].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(1,resultbuffer_0_10ms);
		sAdc_RunningGroup[0][3].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(3,resultbuffer_1_10ms);
		sAdc_RunningGroup[0][5].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(5,resultbuffer_2_10ms);
	}
	if(coreID==OS_CORE_ID_1)
	{
		sAdc_RunningGroup[1][7].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(7,resultbuffer_3_10ms);
		sAdc_RunningGroup[1][9].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(9,resultbuffer_4_10ms);
		sAdc_RunningGroup[1][11].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(11,resultbuffer_5_10ms);
	}
	if(coreID==OS_CORE_ID_2)
	{
		sAdc_RunningGroup[2][13].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(13,resultbuffer_6_10ms);
		sAdc_RunningGroup[2][15].GroupStatus = ADC_STREAM_COMPLETED;
		Adc_ReadGroup(15,resultbuffer_7_10ms);
		Adc_ReadGroup(16,resultbuffer_8_10ms);
		Adc_ReadGroup(17,resultbuffer_9_10ms);
	}
}
uint16 IoHwAb_AdcIn_ReadChannel(IoHwAb_AdcHwUnitInputHwChannelType ChannelId)
{
    uint16 result = 0;
    switch(ChannelId)
    {
        case ADC_u_DC1_L1:
            result = resultbuffer_0_10ms[0];
            break;
        case ADC_Temp_IGBT_U:
            result = resultbuffer_0_10ms[1];
            break;
        case ADC_Current_DC1_L1:
            result = resultbuffer_1_10ms[0];
            break;
        case ADC_Temp_IGBT_V:
            result = resultbuffer_1_10ms[1];
            break;
        case ADC_Temp_Motor0:
            result = resultbuffer_2_10ms[0];
            break;
        case ADC_Temp_IGBT_W:
            result = resultbuffer_2_10ms[1];
            break;
        case ADC_u_DCK1_L1:
            result = resultbuffer_3_10ms[0];
            break;
        case ADC_Temp_IGBT_U2:
            result = resultbuffer_3_10ms[1];
            break;
        case ADC_Current_DC2_L1:
            result = resultbuffer_4_10ms[0];
            break;
        case ADC_eFuCurrent1_L1:
            result = resultbuffer_4_10ms[1];
            break;
        case ADC_Temp_Motor1:
            result = resultbuffer_5_10ms[0];
            break;
        case ADC_eFuCurrent2_L1:
            result = resultbuffer_5_10ms[1];
            break;
        case ADC_eFuCurrent3_L1:
            result = resultbuffer_6_10ms[0];
            break;
        case ADC_eFuTemp:
            result = resultbuffer_7_10ms[0];
            break;
        case ADC_u_DCK2_L1:
            result = resultbuffer_8_10ms[0];
            break;
        case ADC_AN_25V_Ref:
            result = resultbuffer_8_10ms[1];
            break;
        case ADC_AD_IO1:
            result = resultbuffer_9_10ms[0];
            break;
        case ADC_AD_IO2:
            result = resultbuffer_9_10ms[1];
            break;
        case ADC_AD_IO3:
            result = resultbuffer_9_10ms[2];
            break;
        case ADC_AD_IO4:
            result = resultbuffer_9_10ms[3];
            break;
        case ADC_AN_KL30:
            result = resultbuffer_9_10ms[4];
            break;
        case ADC_Temp_Water0:
            result = resultbuffer_9_10ms[5];
            break;
        case ADC_Temp_Motor2:
            result = resultbuffer_9_10ms[6];
            break;
        case ADC_AN_15V_BK:
            result = resultbuffer_9_10ms[7];
            break;
        default:
            // 如果通道ID没有匹配，设置默认值
            result = 0;
            break;
    }

    return result;
}

void IoHwAb_Dio_WriteChannel(IoHwAb_DioOutputHwChannelType Ty_OS_Hwa_LowSideProc_IOx, uint8 DIO_Level)
{
    Dio_LevelType dio_level = STD_HIGH;
    Dio_LevelType Dio_level = STD_LOW;

    if(1 == DIO_Level)
    {
    	Dio_level = STD_HIGH;
    	dio_level = STD_LOW;
    }
    switch(Ty_OS_Hwa_LowSideProc_IOx)
    {
        case DO_LED1:
            Dio_WriteChannel(DioConf_DioChannel_DO_LED1, dio_level);
            break;
        case DO_LED2:
            Dio_WriteChannel(DioConf_DioChannel_DO_LED2, dio_level);
            break;
        case DO_LED3:
            Dio_WriteChannel(DioConf_DioChannel_DO_LED3, dio_level);
            break;
        case DO_LED4:
            Dio_WriteChannel(DioConf_DioChannel_DO_LED4, dio_level);
            break;
        case DO_SA47321_PROG:
            Dio_WriteChannel(DioConf_DioChannel_DO_SA47321_PROG, Dio_level);
            break;
        case DO_MCU_CLR1:
            Dio_WriteChannel(DioConf_DioChannel_DO_MCU_CLR1, Dio_level);
            break;
        case DO_MCU_CLR2:
            Dio_WriteChannel(DioConf_DioChannel_DO_MCU_CLR2, Dio_level);
            break;
        case DO_RT_RDN:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_RDN, dio_level);
            break;
        case DO_RT_WRN:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_WRN, dio_level);
            break;
        case DO_RT_SOE:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_SOE, dio_level);
            break;
        case DO_RT_SAMPLE:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_SAMPLE, dio_level);
            break;
        case DO_RT_A0:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_A0, dio_level);
            break;
        case DO_RT_A1:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_A1, dio_level);
            break;
        case DO_RT_RESETN:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_RESETN, dio_level);
            break;
        case DO_RT_RES0:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_RES0, Dio_level);
            break;
        case DO_RT_RES1:
            Dio_WriteChannel(DioConf_DioChannel_DO_RT_RES1, dio_level);
            break;
        case DO_CAN4WAKE:
            Dio_WriteChannel(DioConf_DioChannel_DO_CAN4WAKE, dio_level);
            break;
        case DO_PWM_Reset_Driver2:
            Dio_WriteChannel(DioConf_DioChannel_DO_PWM_Reset_Driver2, dio_level);
            break;
        case DO_DB_15V_SW1:
            Dio_WriteChannel(DioConf_DioChannel_DO_DB_15V_SW1, Dio_level);
            break;
        case DO_DB_15V_SW2:
            Dio_WriteChannel(DioConf_DioChannel_DO_DB_15V_SW2, Dio_level);
            break;
        case DO_POWER_Down:
            Dio_WriteChannel(DioConf_DioChannel_DO_POWER_Down, Dio_level);
            break;
        case DO_RLS_EXC_N_EN:
            Dio_WriteChannel(DioConf_DioChannel_DO_RLS_EXC_N_EN, Dio_level);
            break;
        case DO_RLS_EXC_EN:
            Dio_WriteChannel(DioConf_DioChannel_DO_RLS_EXC_EN, Dio_level);
            break;
        case DO_CAN0_S:
            Dio_WriteChannel(DioConf_DioChannel_DO_CAN0_S, dio_level);
            break;
        case DO_CAN1_S:
            Dio_WriteChannel(DioConf_DioChannel_DO_CAN1_S, dio_level);
            break;
        case DO_CAN2_S:
            Dio_WriteChannel(DioConf_DioChannel_DO_CAN2_S, dio_level);
            break;
        case DO_CAN3_S:
            Dio_WriteChannel(DioConf_DioChannel_DO_CAN3_S, dio_level);
            break;
        case DO_PWM_Reset_Driver:
            Dio_WriteChannel(DioConf_DioChannel_DO_PWM_Reset_Driver, dio_level);
            break;
        case DO_Enable245_1:
            Dio_WriteChannel(DioConf_DioChannel_DO_Enable245_1, dio_level);
            break;
        case DO_Enable245_2:
            Dio_WriteChannel(DioConf_DioChannel_DO_Enable245_2, dio_level);
            break;
        case DO_Enable245_3:
            Dio_WriteChannel(DioConf_DioChannel_DO_Enable245_3, dio_level);
            break;
        case DO_ADC_GPIO1:
            Dio_WriteChannel(DioConf_DioChannel_DO_ADC_GPIO1, Dio_level);
            break;
        case DO_SW_K1:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K1, Dio_level);
            break;
        case DO_SW_K2:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K2, Dio_level);
            break;
        case DO_SW_K3:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K3, Dio_level);
            break;
        case DO_SW_K5:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K5, Dio_level);
            break;
        case DO_SW_K6:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K6, Dio_level);
            break;
        case DO_HsD_DIAG_EN:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_DIAG_EN, Dio_level);
            break;
        case DO_HsD_THER:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_THER, Dio_level);
            break;
        case DO_eFuRST_Driver:
            Dio_WriteChannel(DioConf_DioChannel_DO_eFuRST_Driver, dio_level);
            break;
        case DO_HsD_SEH1235:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_SEH1235, Dio_level);
            break;
        case DO_HsD_SEL1235:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_SEL1235, Dio_level);
            break;
        case DO_HsD_SEH6789:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_SEH6789, Dio_level);
            break;
        case DO_HsD_SEL6789:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_SEL6789, Dio_level);
            break;
        case DO_HsD_SEH101112:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_SEH101112, Dio_level);
            break;
        case DO_HsD_SEL101112:
            Dio_WriteChannel(DioConf_DioChannel_DO_HsD_SEL101112, Dio_level);
            break;
        case DO_SW_K7:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K7, dio_level);
            break;
        case DO_SW_K8:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K8, dio_level);
            break;
        case DO_SW_K9:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K9, dio_level);
            break;
        case DO_SW_K10:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K10, dio_level);
            break;
        case DO_SW_K11:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K11, dio_level);
            break;
        case DO_SW_K12:
            Dio_WriteChannel(DioConf_DioChannel_DO_SW_K12, dio_level);
            break;
        case DO_FCCU_EOUT:
            Dio_WriteChannel(DioConf_DioChannel_DO_FCCU_EOUT, dio_level);
            break;
        default:
            /* 未知通道，不操作 */
            break;
    }
}

uint8 IoHwAb_Dio_ReadChannel(IoHwAb_DioInputHwChannelType ChannelId)
{
    uint8 result = 0;
    uint8 Result = 0;
    switch(ChannelId)
    {
        case DI_COL_in:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_COL_in);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_BSM24_IN:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_BSM24_IN);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_AdhesK5:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_AdhesK5);
            break;
        case DI_AdhesK6:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_AdhesK6);
            break;
        case DI_AdhesK7:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_AdhesK7);
            break;
        case DI_AdhesK8:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_AdhesK8);
            break;
        case DI_AdhesK9:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_AdhesK9);
            break;
        case DI_AdhesK12:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_AdhesK12);
            break;
        case DI_SafeState1:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_SafeState1);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_SafeState2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_SafeState2);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_Fault_UH2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_UH2);
            break;
        case DI_Fault_VH2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_VH2);
            break;
        case DI_Fault_WH2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_WH2);
            break;
        case DI_Fault_UL2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_UL2);
            break;
        case DI_Fault_VL2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_VL2);
            break;
        case DI_Fault_WL2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_WL2);
            break;
        case DI_IL_Dr_D_OUT2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_IL_Dr_D_OUT2);
            break;
        case DI_RT_DIR:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_RT_DIR);
            break;
        case DI_Fault_UH:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_UH);
            break;
        case DI_Fault_VH:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_VH);
            break;
        case DI_Fault_WH:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_WH);
            break;
        case DI_Fault_UL:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_UL);
            break;
        case DI_Fault_VL:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_VL);
            break;
        case DI_Fault_WL:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Fault_WL);
            break;
        case DI_IL_Dr_D_OUT1:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_IL_Dr_D_OUT1);
            break;
        case DI_FastC_Wake:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_FastC_Wake);
            break;
        case DI_Switch0:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Switch0);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_Switch1:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Switch1);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_Switch2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Switch2);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_Switch3:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_Switch3);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_ACM_EN:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_ACM_EN);
            if(result==1)
            {
            	result=0;
            }
            break;
        case DI_eFuFault1:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_eFuFault1);
            break;
        case DI_eFuFault2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_eFuFault2);
            break;
        case DI_eFuFault3:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_eFuFault3);
            break;
        case DI_eFuFault4:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_eFuFault4);
            break;
        case DI_eFuFault5:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_eFuFault5);
            break;
        case DI_IL_Dr_D_OUT3:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_IL_Dr_D_OUT3);
            break;
        case DI_IN_KL15:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_IN_KL15);
            break;
        case DI_RT_LOT_A:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_RT_LOT_A);
            break;
        case DI_RT_DOS_A:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_RT_DOS_A);
            break;
        case DI_HsD_nFR1:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_HsD_nFR1);
            break;
        case DI_HsD_nFR2:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_HsD_nFR2);
            break;
        case DI_HsD_nFR3:
            result = Dio_ReadChannel(DioConf_DioChannel_DI_HsD_nFR3);
            break;
        default:
            /* 未知通道，保持 result = 0 */
            break;
    }
    if(result==1)
    {
    	Result=0;
    }
    if(result==0)
    {
    	Result=1;
    }
    return Result;
}


void IoHwAb_PwmOut_SetPeriodAndDuty(IoHwAb_PwmOutputHwChannelType ChannelId, uint32 Period, uint16 dutyCycle)
{
    uint16 DutyCycle;
    DutyCycle = dutyCycle * 2;  // 将占空比乘以2

    switch(ChannelId)
    {
        case PO_eFuPWM1:
            Pwm_SetPeriodAndDuty(0, Period, DutyCycle);
            break;
        case PO_eFuPWM2:
            Pwm_SetPeriodAndDuty(1, Period, DutyCycle);
            break;
        case PO_eFuPWM3:
            Pwm_SetPeriodAndDuty(2, Period, DutyCycle);
            break;
        case PO_eFuPWM4:
            Pwm_SetPeriodAndDuty(3, Period, DutyCycle);
            break;
        case PO_eFuPWM5:
            Pwm_SetPeriodAndDuty(4, Period, DutyCycle);
            break;
        case PO_PWM_EFN:
            Pwm_SetPeriodAndDuty(5, Period, DutyCycle);
            break;
        case PO_PWM_UL:
            Pwm_SetPeriodAndDuty(6, Period, DutyCycle);
            break;
        case PO_PWM_VL:
            Pwm_SetPeriodAndDuty(7, Period, DutyCycle);
            break;
        case PO_PWM_WL:
            Pwm_SetPeriodAndDuty(8, Period, DutyCycle);
            break;
        case PO_PWM_UH:
            Pwm_SetPeriodAndDuty(9, Period, DutyCycle);
            break;
        case PO_PWM_VH:
            Pwm_SetPeriodAndDuty(10, Period, DutyCycle);
            break;
        case PO_PWM_WH:
            Pwm_SetPeriodAndDuty(11, Period, DutyCycle);
            break;
        case PO_PWM_actADC:
            Pwm_SetPeriodAndDuty(12, Period, DutyCycle);
            break;
        case PO_PWM_UH2:
            Pwm_SetPeriodAndDuty(13, Period, DutyCycle);
            break;
        case PO_PWM_VH2:
            Pwm_SetPeriodAndDuty(14, Period, DutyCycle);
            break;
        case PO_PWM_WH2:
            Pwm_SetPeriodAndDuty(15, Period, DutyCycle);
            break;
        case PO_PWM_UL2:
            Pwm_SetPeriodAndDuty(16, Period, DutyCycle);
            break;
        case PO_PWM_WL2:
            Pwm_SetPeriodAndDuty(17, Period, DutyCycle);
            break;
        case PO_PWM_VL2:
            Pwm_SetPeriodAndDuty(18, Period, DutyCycle);
            break;
        case PO_PWM2_actADC:
            Pwm_SetPeriodAndDuty(19, Period, DutyCycle);
            break;
        case PO_SDCRC:
            Pwm_SetPeriodAndDuty(20, Period, DutyCycle);
            break;
        case PO_RTS_EXC:
            Pwm_SetPeriodAndDuty(21, Period, DutyCycle);
            break;
        case PO_RTS_EXC_N:
            Pwm_SetPeriodAndDuty(22, Period, DutyCycle);
            break;
        case PO_SA47321_WatchDog:
            Pwm_SetPeriodAndDuty(23, Period, DutyCycle);
            break;
        case PO_SA47321_ERR:
            Pwm_SetPeriodAndDuty(24, Period, DutyCycle);
            break;
        case PO_PWM_triggered_ADC_soft_decoding_diagnosis_Positive:
            Pwm_SetPeriodAndDuty(25, Period, DutyCycle);
            break;
        case PO_PWM_triggered_ADC_soft_decoding_diagnosis_Negative:
            Pwm_SetPeriodAndDuty(26, Period, DutyCycle);
            break;
        default:
            /* invalid channel id */
            break;
    }
}


void External_ISR_enable(void)
{
	SIUL2.DISR0.R=0x0000067B;
	SIUL2.DIRER0.R=0x0000067B;
	SIUL2.DIRSR0.R=0x00000000;
	SIUL2.IREER0.R=0x00000000;
	SIUL2.IFEER0.R=0x0000067B;
	SIUL2.IFER0.R=0x00000000;
}

uint32 DISR0_status;
#define FAULT_Smotor_CURRENT_OC		         (1<<6)
#define FAULT_SA47321_nINT_ERROR	         (1<<0)
#define FAULT_Efuse_CURRENT_OC       		 (1<<1)
#define FAULT_Smotor_IGBT_ERROR      		 (1<<3)
#define FAULT_Mmotor_CURRENT_OC      		 (1<<4)
#define FAULT_Efuse_ERROR      				 (1<<5)
#define FAULT_Mmotor_IGBT_ERROR      		 (1<<9)
#define FAULT_BUSBAR_OV      		         (1<<10)
FaultCounter ISR_ERR_status;
FaultFlags ISR_ERR_Flags;
void SIUL_External_0_ISRFunc(void)
{
	Handle();
}
void SIUL_External_1_ISRFunc(void)
{
	Handle();
}
void Emgercy_SPO()
{
	SIUL2.MSCR_IO[85].R=0x32010000;
	SIUL2.MSCR_MUX[85].R=0;
	SIUL2.GPDO[85].B.PDO = 0;
	SIUL2.MSCR_IO[116].R=0x32010000;
	SIUL2.MSCR_MUX[116].R=0;
	SIUL2.GPDO[116].B.PDO = 0;

	SIUL2.MSCR_IO[95].R=0x32010000;
	SIUL2.MSCR_MUX[95].R=0;
	SIUL2.GPDO[95].B.PDO = 0;
	SIUL2.MSCR_IO[123].R=0x32010000;
	SIUL2.MSCR_MUX[123].R=0;
	SIUL2.GPDO[123].B.PDO = 0;

	SIUL2.MSCR_IO[88].R=0x32010000;
	SIUL2.MSCR_MUX[88].R=0;
	SIUL2.GPDO[88].B.PDO = 0;
	SIUL2.MSCR_IO[124].R=0x32010000;
	SIUL2.MSCR_MUX[124].R=0;
	SIUL2.GPDO[124].B.PDO = 0;
}
void Emgercy_ASC()
{
	SIUL2.MSCR_IO[85].R=0x32010000;
	SIUL2.MSCR_MUX[85].R=0;
	SIUL2.GPDO[85].B.PDO = 0;
	SIUL2.MSCR_IO[116].R=0x32010000;
	SIUL2.MSCR_MUX[116].R=0;
	SIUL2.GPDO[116].B.PDO = 0;

	SIUL2.MSCR_IO[95].R=0x32010000;
	SIUL2.MSCR_MUX[95].R=0;
	SIUL2.GPDO[95].B.PDO = 0;
	SIUL2.MSCR_IO[123].R=0x32010000;
	SIUL2.MSCR_MUX[123].R=0;
	SIUL2.GPDO[123].B.PDO = 0;

	SIUL2.MSCR_IO[88].R=0x32010000;
	SIUL2.MSCR_MUX[88].R=0;
	SIUL2.GPDO[88].B.PDO = 0;
	SIUL2.MSCR_IO[124].R=0x32010000;
	SIUL2.MSCR_MUX[124].R=0;
	SIUL2.GPDO[124].B.PDO = 0;
//	延时
	SIUL2.MSCR_IO[85].R=0x32010000;
	SIUL2.MSCR_MUX[85].R=0;
	SIUL2.GPDO[85].B.PDO = 0;
	SIUL2.MSCR_IO[116].R=0x32010000;
	SIUL2.MSCR_MUX[116].R=0;
	SIUL2.GPDO[116].B.PDO = 1;

	SIUL2.MSCR_IO[95].R=0x32010000;
	SIUL2.MSCR_MUX[95].R=0;
	SIUL2.GPDO[95].B.PDO = 0;
	SIUL2.MSCR_IO[123].R=0x32010000;
	SIUL2.MSCR_MUX[123].R=0;
	SIUL2.GPDO[123].B.PDO = 1;

	SIUL2.MSCR_IO[88].R=0x32010000;
	SIUL2.MSCR_MUX[88].R=0;
	SIUL2.GPDO[88].B.PDO = 0;
	SIUL2.MSCR_IO[124].R=0x32010000;
	SIUL2.MSCR_MUX[124].R=0;
	SIUL2.GPDO[124].B.PDO = 1;
}
void Emgercy_SWITCH_PWMMODE(uint8 PWMmode_AfEmrgncy)
{
	switch(PWMmode_AfEmrgncy)
	{
		case 0:
			Emgercy_SPO();
			break;
		case 1:
			Emgercy_ASC();
			break;
		default:
			break;
	}
}
void Handle()
{
	DISR0_status=SIUL2.DISR0.R;

	if (DISR0_status & FAULT_Smotor_CURRENT_OC) { // S电机过流（位6）
		ISR_ERR_status.Smotor_CURRENT_OC++;
		ISR_ERR_Flags.Smotor_CURRENT_OC=1;
	    Handle_Smotor_CURRENT_OC();
	    SIUL2.DISR0.R |= FAULT_Smotor_CURRENT_OC;
	}
	if (DISR0_status & FAULT_SA47321_nINT_ERROR) { // S电机过流（位6）
		ISR_ERR_status.SA47321_nINT_ERROR++;
		ISR_ERR_Flags.SA47321_nINT_ERROR=1;
		Handle_SA47321_nINT_ERROR();
	    SIUL2.DISR0.R |= FAULT_SA47321_nINT_ERROR;
	}
	if (DISR0_status & FAULT_Efuse_CURRENT_OC) { // 电子保险丝过流（位1）
		ISR_ERR_status.Efuse_CURRENT_OC++;
		ISR_ERR_Flags.Efuse_CURRENT_OC=1;
	    Handle_Efuse_CURRENT_OC();              // 过流处理函数
	    SIUL2.DISR0.R |= FAULT_Efuse_CURRENT_OC;
	}
	if (DISR0_status & FAULT_Smotor_IGBT_ERROR) { // S电机IGBT故障（位3）
		ISR_ERR_status.Smotor_IGBT_ERROR++;
		ISR_ERR_Flags.Smotor_IGBT_ERROR=1;
	    Handle_Smotor_IGBT_ERROR();
	    SIUL2.DISR0.R |= FAULT_Smotor_IGBT_ERROR;
	}
	if (DISR0_status & FAULT_Mmotor_CURRENT_OC) { // M电机过流（位4）
		ISR_ERR_status.Mmotor_CURRENT_OC++;
		ISR_ERR_Flags.Mmotor_CURRENT_OC=1;
	    Handle_Mmotor_CURRENT_OC();
	    SIUL2.DISR0.R |= FAULT_Mmotor_CURRENT_OC;
	}
	if (DISR0_status & FAULT_Efuse_ERROR) {       // 电子保险丝错误（位5）
		ISR_ERR_status.Efuse_ERROR++;
		ISR_ERR_Flags.Efuse_ERROR=1;
	    Handle_Efuse_ERROR();
	    SIUL2.DISR0.R |= FAULT_Efuse_ERROR;
	}
	if (DISR0_status & FAULT_Mmotor_IGBT_ERROR) { // M电机IGBT故障（位9）
		ISR_ERR_status.Mmotor_IGBT_ERROR++;
		ISR_ERR_Flags.Mmotor_IGBT_ERROR=1;
	    Handle_Mmotor_IGBT_ERROR();
	    SIUL2.DISR0.R |= FAULT_Mmotor_IGBT_ERROR;
	}
	if (DISR0_status & FAULT_BUSBAR_OV) {        // 总线过压故障（位10）
	    ISR_ERR_status.Busbar_OV++;
	    ISR_ERR_Flags.Busbar_OV=1;
		Handle_BUSBAR_OV();                     // 总线过压处理函数
	    SIUL2.DISR0.R |= FAULT_BUSBAR_OV;       // 标志位置位
	}
}

