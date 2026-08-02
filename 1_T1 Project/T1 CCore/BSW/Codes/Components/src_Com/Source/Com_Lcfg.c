/*
********************************************************************************
*
*  File name:   Com_Lcfg.c
*
*  Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : WangJP/2021.08.14
* Change: New created 
* Cause: New
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Com_Lcfg.h"
#include "Com_Cfg.h"
#include "CanIf.h"
#include "Com_Types.h"

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
#define COM_START_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotoperatingmodeMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotRotDirtionMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotSysStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_highprecisionMotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotCurMaxOutphighprecisionTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_CurMaxOutpTqofMotMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotSpdMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_highUPwroffAllwedMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ActvdisChrgStMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotFailrStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgCnterMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgChksumMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotTqECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotAvlMaxGennhighprecisionTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotAvlMaxGennTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgCnterMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgChksumMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotoperatingmodeMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotRotDirtionMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotSysStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_highprecisionMotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_otCurMaxOutphighprecisionTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_CurMaxOutpTqofMotMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotSpdMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_highUPwroffAllwedMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ActvdisChrgStMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotFailrStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgCnterMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgChksumMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotCtrllerbusUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotCtrllerbusCurMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotCtrllerTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_otAvlMaxGennhighprecisionTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotAvlMaxGennTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgCnterMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MsgChksumMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_amberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_redstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_malFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashamberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashredstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashmalFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn8leastsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spnSecbyteDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FMiDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn3mostsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_occurrenceCntDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_spnCnvnMetHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_amberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_redstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_malFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashamberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashredstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashmalFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn8leastsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spnSecbyteDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FMiDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn3mostsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_occurrenceCntDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_spnCnvnMetHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotCtrllerbusUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MotCtrllerbusCurMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MotCtrllerTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_DCDC_VouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_DCDC_CouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDC_Mode_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_DCDC_Enable_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_DCDC_Sleep_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDC_Precharge_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_DCDC_Fault_Clear_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_DCDC_Dir_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_DCDC_Dir_Check_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDC_Counter_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDC_Checksum_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_APCUhighUbusUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_APCUMotworkingStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_APCUMotFailrStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_APCUOutpCurAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_amberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_redstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_malFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashamberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashredstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashmalFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn8leastsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spnSecbyteDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FMiDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn3mostsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_occurrenceCntDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_spnCnvnMetHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_DCDCInpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCInpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCOutpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCOutpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCworkingStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCFltStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_amberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_redstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_malFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashamberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashredstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashmalFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn8leastsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spnSecbyteDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FMiDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn3mostsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_occurrenceCntDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_spnCnvnMetHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_amberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_redstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_malFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashamberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashredstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashmalFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn8leastsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spnSecbyteDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FMiDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn3mostsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_occurrenceCntDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_spnCnvnMetHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_OPCUhighUbusUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_OPCUMotFailrStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_OPCUworkingStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_oilPUMPMotIvterTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_oilPUMPMotOutpCurOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_mainPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_mainnegtiveRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_pduFailrStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_preChrgnRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_fuelcellRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_PTCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_AcsoryRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MECURlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DCDCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_mainPosRlyPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_MECUPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_BattpackHeatgPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_BattpackHeatgNegRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_hydroCoolgRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_acRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DirtCurChrg1PosRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DirtCurChrg1NegRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DirtCurChrg2NegRlyStsRelayState20_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_DirtCurChrg2NegRlyStsRelayState21_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_PwrBattURelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_BattheatPTCRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_WtrCoolgRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_insulationRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_sulationMonrdetectsUResdIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_insulationMonrSysStsIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_insulationMonrAlrmIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint16, COM_VAR_NO_INIT) Com_bufptr_MECUbusbarUMECU1Reserved_MECU1Reserved_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_ProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_amberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_redstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_malFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashamberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashredstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FlashmalFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn8leastsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spnSecbyteDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_FMiDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_spn3mostsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(uint8, COM_VAR_NO_INIT) Com_bufptr_occurrenceCntDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;
static VAR(boolean, COM_VAR_NO_INIT) Com_bufptr_spnCnvnMetHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx;

#define COM_STOP_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

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
#define COM_START_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

VAR(Com_TxInterMonitor_st, COM_VAR_NO_INIT)         COM_TxIM_Var[COM_TXPDU_NUM];
VAR(Com_RxInterMonitor_st, COM_VAR_NO_INIT)         COM_RxIM_Var[COM_RXPDU_NUM];
VAR(Com_RxSignalMonitor_st, COM_VAR_NO_INIT)        COM_RxSigIM_Var[COM_RXSIG_NUM];
VAR(Com_SignalGroupMonitor_st, COM_VAR_NO_INIT)     COM_TxSigGrpIM_Var[COM_TXGRP_NUM + 1U];
VAR(Com_SignalGroupMonitor_st, COM_VAR_NO_INIT)     COM_RXSigGrpIM_Var[COM_RXGRP_NUM + 1U];
static VAR(Com_SigSendStaType, COM_VAR_NO_INIT) 	Com_SigSendSta_Var[COM_TXSIG_NUM];

#define COM_STOP_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_INIT
#include "Com_MemMap.h"

VAR(uint16, COM_VAR_INIT) Com_RxSigGrpUpdateCtn[COM_RXGRP_NUM + 1U] = {0U};
VAR(uint8, COM_VAR_INIT) Com_RxSigGrpDataSta[COM_RXGRP_NUM + 1U] = {0U};

#define COM_STOP_SEC_VAR_INIT
#include "Com_MemMap.h"

#if (COM_TXSIGNALFILTER_SUPPORTED == STD_ON)

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
	



#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#endif 

#define COM_START_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

#if ((COM_METADATA_SUPPORT == STD_ON) && (COM_TXMETADATA_NUM > COM_INIT_ZERO))
#endif /* ((COM_METADATA_SUPPORT == STD_ON) && (COM_TXMETADATA_NUM > COM_INIT_ZERO))  */

#define COM_STOP_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_INIT
#include "Com_MemMap.h"

#if ((COM_METADATA_SUPPORT == STD_ON) && (COM_TXMETADATA_NUM > COM_INIT_ZERO))
#endif /* ((COM_METADATA_SUPPORT == STD_ON) && (COM_TXMETADATA_NUM > COM_INIT_ZERO)) */

#define COM_STOP_SEC_VAR_INIT
#include "Com_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
	
	
CONST(Com_GwMappingSigDscpType, COM_CONFIG_DATA) Com_GwDscpInfo[COM_GWSIGNALDSCP_NUM + 1U] =
{
	{
		0U,
	}
};
#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#if (COM_MULTICORE_SUPPORT == STD_ON)
#define COM_START_SEC_GLOBAL_VAR_INIT
#include "Com_MemMap.h"
VAR(Com_PduIndexType, COM_VAR_INIT) COM_rxPduIndexCAN_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_rxPduIndexLIN_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_rxPduIndexFR_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_rxPduIndexETH_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_txPduIndexCAN_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_txPduIndexLIN_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_txPduIndexFR_Core0[1] = {65535U,};
VAR(Com_PduIndexType, COM_VAR_INIT) COM_txPduIndexETH_Core0[1] = {65535U,};
#define COM_STOP_SEC_GLOBAL_VAR_INIT
#include "Com_MemMap.h"
#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_RxPduIndex_Can[COM_CORE_NUM] = {
	{
		0U,
		COM_rxPduIndexCAN_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_RxPduIndex_Lin[COM_CORE_NUM] = {
	{
		0U,
		COM_rxPduIndexLIN_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_RxPduIndex_Fr[COM_CORE_NUM] = {
	{
		0U,
		COM_rxPduIndexFR_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_RxPduIndex_Eth[COM_CORE_NUM] = {
	{
		0U,
		COM_rxPduIndexETH_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_TxPduIndex_Can[COM_CORE_NUM] = {
	{
		0U,
		COM_txPduIndexCAN_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_TxPduIndex_Lin[COM_CORE_NUM] = {
	{
		0U,
		COM_txPduIndexLIN_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_TxPduIndex_Fr[COM_CORE_NUM] = {
	{
		0U,
		COM_txPduIndexFR_Core0
	},
};
CONST(Com_PduIndexInfo_st, COM_CONFIG_DATA)Com_TxPduIndex_Eth[COM_CORE_NUM] = {
	{
		0U,
		COM_txPduIndexETH_Core0
	},
};
#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#endif /* COM_MULTICORE_SUPPORT == STD_ON */

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"

CONST(uint16, COM_CONFIG_DATA) Com_RxPduInfoRef_5ms[COM_RXPDU_NUM_5MS + 1U] =
{
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U,
    8U,
    9U,
    10U,
    11U,
    12U,
    13U,
    14U,
    15U,
    16U,
    17U,
    18U,
    19U,
    20U,
    65535U
};
CONST(Com_RxPduInfoTableType, COM_CONFIG_DATA) Com_RxPduInfoTable[COM_RXPDU_TOTAL_TABLES] =
{
    {
        Com_RxPduInfoRef_5ms,
        COM_RXPDU_NUM_5MS
    }
};
CONST(uint16, COM_CONFIG_DATA) Com_TxPduInfoRef_5ms[COM_TXPDU_NUM_5MS + 1U] =
{
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U,
    8U,
    9U,
    10U,
    11U,
    12U,
    13U,
    14U,
    15U,
    16U,
    17U,
    18U,
    19U,
    20U,
    21U,
    22U,
    65535U
};
CONST(Com_TxPduInfoTableType, COM_CONFIG_DATA) Com_TxPduInfoTable[COM_TXPDU_TOTAL_TABLES] =
{
    {
        Com_TxPduInfoRef_5ms,
        COM_TXPDU_NUM_5MS
    }
};
CONST(uint16, COM_CONFIG_DATA) Com_GwInfoRef_5ms[COM_GWINFO_NUM_5MS + 1U] =
{
    65535U
};
CONST(uint16, COM_CONFIG_DATA) Com_GwDscpInfoRef_5ms[COM_GWDSCPINFO_NUM_5MS + 1U] =
{
    65535U
};
CONST(Com_GatewayInfoTableType, COM_CONFIG_DATA) Com_GatewayInfoTable[COM_GATEWAYINFO_TOTAL_TABLES] =
{
    {
        Com_GwInfoRef_5ms,
        Com_GwDscpInfoRef_5ms,
        COM_GWINFO_NUM_5MS,
        COM_GWDSCPINFO_NUM_5MS
    }
};

#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(COM_TxSigGrpInfo_st, COM_CONFIG_DATA) Com_TxSigGrpInfo[COM_TXGRP_NUM + 1U] = {
	{
		0U,
	}
};
CONST(COM_RxSigGrpInfo_st, COM_CONFIG_DATA) Com_RxSigGrpInfo[COM_RXGRP_NUM + 1U] = {
	{
		0U,
	}
};

CONST(uint16, COM_CONFIG_DATA) Com_PduGrpVectorMatch[COM_PDUGRP_MATCH_SIZE] = {
	2U,
	2U,
	2U,
	2U,
	2U,
	2U,
	2U,
	2U,
	2U,
	0U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	4U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	3U,
	1U,
	1U,
	1U,
	5U,
	5U,
	5U,
	5U,
	5U,
	5U,
};
CONST(COM_TxModeInfo_st, COM_CONFIG_DATA) Com_TxModeInfo[COM_TXPDU_NUM] = {
	{TRUE, 0U, 0U, 0U},
	{TRUE, 1U, 1U, 255U},
	{TRUE, 2U, 2U, 0U},
	{TRUE, 3U, 3U, 0U},
	{TRUE, 4U, 4U, 0U},
	{TRUE, 5U, 5U, 0U},
	{TRUE, 6U, 6U, 255U},
	{TRUE, 7U, 7U, 255U},
	{TRUE, 8U, 8U, 0U},
	{TRUE, 9U, 9U, 0U},
	{TRUE, 10U, 10U, 0U},
	{TRUE, 11U, 11U, 0U},
	{TRUE, 12U, 12U, 255U},
	{TRUE, 13U, 13U, 0U},
	{TRUE, 14U, 14U, 255U},
	{TRUE, 15U, 15U, 255U},
	{TRUE, 16U, 16U, 0U},
	{TRUE, 17U, 17U, 0U},
	{TRUE, 18U, 18U, 0U},
	{TRUE, 19U, 19U, 0U},
	{TRUE, 20U, 20U, 0U},
	{TRUE, 21U, 21U, 0U},
	{TRUE, 22U, 22U, 255U},

};
CONST(Com_TxMode_st, COM_CONFIG_DATA) Com_TxModeTrue[COM_TXPDU_NUM] = {
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_PREDIOC, 0U, 0U, 0U, 2U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
};
CONST(Com_TxMode_st, COM_CONFIG_DATA) Com_TxModeFalse[COM_TXPDU_NUM] = {
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_PREDIOC, 0U, 0U, 0U, 2U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
	{COM_TXMODE_DIRECT, 0U, 0U, 0U, 0U, 0U},
};
#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"
#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(Com_SignalBaseInfo_st, COM_CONFIG_DATA) Com_SignalBaseInfo[COM_RXSIG_NUM + COM_TXSIG_NUM] =
{
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTOPERATINGMODEMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTROTDIRTIONMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTSYSSTSMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_HIGHPRECISIONMOTTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 0U, 4U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTCURMAXOUTPHIGHPRECISIONTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_CURMAXOUTPTQOFMOTMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTSPDMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_HIGHUPWROFFALLWEDMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {6U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_ACTVDISCHRGSTMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {6U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTFAILRSTSMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {6U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MSGCNTERMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 0U, 4U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU1_D3_SO0_MSGCHKSUMMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_ECMCU_D3_SO0_MOTTQECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {19U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU3_D3_SO0_MOTAVLMAXGENNHIGHPRECISIONTQMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU3_D3_SO0_MOTAVLMAXGENNTQMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU3_D3_SO0_MSGCNTERMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 0U, 4U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU3_D3_SO0_MSGCHKSUMMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTOPERATINGMODEMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTROTDIRTIONMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTSYSSTSMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_HIGHPRECISIONMOTTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 0U, 4U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_OTCURMAXOUTPHIGHPRECISIONTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_CURMAXOUTPTQOFMOTMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTSPDMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_HIGHUPWROFFALLWEDMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {6U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_ACTVDISCHRGSTMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {6U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTFAILRSTSMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {6U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MSGCNTERMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 0U, 4U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU21_D3_SO0_MSGCHKSUMMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERBUSUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERBUSCURMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {2U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {5U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU23_D3_SO0_OTAVLMAXGENNHIGHPRECISIONTQMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_MCU23_D3_SO0_MOTAVLMAXGENNTQMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU23_D3_SO0_MSGCNTERMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 0U, 4U, 47U},
    /* Tx COMCONF_COMSIGNAL_MCU23_D3_SO0_MSGCHKSUMMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {7U, 1U, 4U, 4U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_PROTLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_AMBERWARNLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_REDSTOPLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_MALFCTINDCRLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHPROTLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHAMBERWARNLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHREDSTOPLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHMALFCTINDCRLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPN8LEASTSIGNIFICANTBITSDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPNSECBYTEDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FMIDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 1U, 0U, 5U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPN3MOSTSIGNIFICANTBITSDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 1U, 5U, 3U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_OCCURRENCECNTDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {5U, 1U, 0U, 7U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPNCNVNMETHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {5U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_PROTLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_AMBERWARNLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_REDSTOPLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_MALFCTINDCRLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHPROTLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHAMBERWARNLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHREDSTOPLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHMALFCTINDCRLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {1U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPN8LEASTSIGNIFICANTBITSDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPNSECBYTEDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FMIDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 1U, 0U, 5U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPN3MOSTSIGNIFICANTBITSDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 1U, 5U, 3U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_OCCURRENCECNTDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {5U, 1U, 0U, 7U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPNCNVNMETHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {5U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERBUSUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {0U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERBUSCURMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {2U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {4U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX */
    {5U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_VOUSET_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {1U, 2U, 0U, 16U, 6U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_COUSET_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {3U, 2U, 0U, 12U, 8U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_MODE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {2U, 1U, 4U, 2U, 4U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_ENABLE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {2U, 1U, 6U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_SLEEP_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {2U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_PRECHARGE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {4U, 1U, 0U, 2U, 3U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_FAULT_CLEAR_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {4U, 1U, 2U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_DIR_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {4U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_DIR_CHECK_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {6U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_COUNTER_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {6U, 1U, 0U, 4U, 3U},
    /* Tx COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_CHECKSUM_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX */
    {7U, 1U, 0U, 8U, 1U},
    /* Tx COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUHIGHUBUSUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUMOTWORKINGSTSAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUMOTFAILRSTSAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUOUTPCURAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_APCU2_OJCG_C_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_PROTLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_AMBERWARNLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_REDSTOPLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_MALFCTINDCRLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHPROTLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHAMBERWARNLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHREDSTOPLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHMALFCTINDCRLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPNSECBYTEDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FMIDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 5U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 5U, 3U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_OCCURRENCECNTDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 0U, 7U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPNCNVNMETHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCINPUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCINPCURDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCOUTPUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCOUTPCURDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCWORKINGSTSDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {6U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCFLTSTSDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {6U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_PROTLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_AMBERWARNLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_REDSTOPLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_MALFCTINDCRLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHPROTLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHAMBERWARNLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHREDSTOPLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHMALFCTINDCRLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPNSECBYTEDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FMIDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 5U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 5U, 3U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_OCCURRENCECNTDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 0U, 7U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPNCNVNMETHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_PROTLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_AMBERWARNLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_REDSTOPLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_MALFCTINDCRLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHPROTLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHAMBERWARNLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHREDSTOPLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHMALFCTINDCRLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPNSECBYTEDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FMIDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 5U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 5U, 3U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_OCCURRENCECNTDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 0U, 7U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPNCNVNMETHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 7U, 1U, 0U},
    /* Tx COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUHIGHUBUSUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUMOTFAILRSTSOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {7U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUWORKINGSTSOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX */
    {7U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_OPCU2_OJCG_C_OILPUMPMOTIVTERTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_OPCU2_OJCG_C_OILPUMPMOTOUTPCUROPCU2_OPCU2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINPOSRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINNEGTIVERLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PDUFAILRSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PRECHRGNRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_FUELCELLRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PTCRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_ACSORYRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MECURLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_DCDCRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINPOSRLYPWRONSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MECUPWRONSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_BATTPACKHEATGPOSRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {6U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_BATTPACKHEATGNEGRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {6U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_HYDROCOOLGRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {7U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_ACRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX */
    {7U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG1POSRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG1NEGRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG2NEGRLYSTSRELAYSTATE20_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG2NEGRLYSTSRELAYSTATE21_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_PWRBATTURELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_BATTHEATPTCRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_WTRCOOLGRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 3U, 3U, 48U},
    /* Tx COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_SULATIONMONRDETECTSURESDIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONMONRSYSSTSIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 3U, 47U},
    /* Tx COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONMONRALRMIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_MECU1RESERVED_OJCG_C_MECUBUSBARUMECU1RESERVED_MECU1RESERVED_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 2U, 0U, 16U, 50U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_PROTLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_AMBERWARNLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_REDSTOPLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_MALFCTINDCRLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {0U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHPROTLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 0U, 2U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHAMBERWARNLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 2U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHREDSTOPLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 4U, 2U, 48U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHMALFCTINDCRLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {1U, 1U, 6U, 2U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {2U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPNSECBYTEDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {3U, 1U, 0U, 8U, 45U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FMIDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 0U, 5U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {4U, 1U, 5U, 3U, 46U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_OCCURRENCECNTDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 0U, 7U, 47U},
    /* Tx COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPNCNVNMETHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX */
    {5U, 1U, 7U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODETSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDSPDCTRLCDNSTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODEPRIOTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDSPDSPDLIMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDTQTQLIMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {3U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDTQFRACTNALTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 0U, 4U, 47U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_MSGCNTERTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {7U, 1U, 0U, 4U, 47U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_MSGCHKSUMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {7U, 1U, 4U, 4U, 46U},
    /* Rx COMCONF_COMSIGNAL_EEC2HCU_D3_SO0_ACCRPEDLAPPOSN_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_PRKGBRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_BRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {3U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMREQEDGEARTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {2U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMMODE2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TC1HANDLE_D3_SO0_TRSMREQEDGEARTC1HANDLE_TC1HANDLE_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {2U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_ETC1_D3_SO0_SHIFTINPROCETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_ETC2_D3_SO0_SELEDGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_ETC2_D3_SO0_ACTGEARRATETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_ETC2_D3_SO0_CURGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {3U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_REQHCUTOCTRLTHEMOTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_TRSMGEARSELFLRNINGSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 2U, 4U, 48U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_HOLDCURGEARREQAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 6U, 2U, 46U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_CLUSTSAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_SERSPARALLELMODESTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_CLUCNSEDTQAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {2U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_SWTSTOFTHEFPICKERAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {6U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_DRVGFSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {6U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_PRKGFSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {6U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_AMT3_D3_SO0_PTOBINDINGSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {6U, 1U, 6U, 2U, 46U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_HIGHPRECISIONMOTTQREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 4U, 4U, 46U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTTQREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTSPDREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {2U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTWORKENACMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTNEGHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTPOSHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTPRECHRGHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 6U, 2U, 46U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_HIGHUPWROFFREQOFMOTHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTACTVDISCHRGCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MAXSPDLIMUNDERCURLOADHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {6U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_HIGHPRECISIONMOTTQREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 4U, 4U, 46U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTTQREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTSPDREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {2U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTWORKENACMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTNEGHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTPOSHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTPRECHRGHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {4U, 1U, 6U, 2U, 46U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_HIGHUPWROFFREQOFMOTHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTACTVDISCHRGCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MAXSPDLIMUNDERCURLOADHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {6U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_SC_D3_SO0_PTOSWTCMDSC_SC_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODETSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDSPDCTRLCDNSTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODEPRIOTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {0U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDSPDSPDLIMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {1U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDTQTQLIMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {3U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDTQFRACTNALTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {5U, 1U, 0U, 4U, 47U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_MSGCNTERTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {7U, 1U, 0U, 4U, 47U},
    /* Rx COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_MSGCHKSUMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX */
    {7U, 1U, 4U, 4U, 46U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VIN_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 2U, 6U, 10U, 7U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VOUT_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 2U, 0U, 12U, 8U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_COUT_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 2U, 4U, 12U, 7U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_MODEFB_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 5U, 2U, 4U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_DIRFB_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 4U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_CMDSRC_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_FAULTLEVEL_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 0U, 3U, 3U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_STATE_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 4U, 4U, 2U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_COUNTER1_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 0U, 4U, 3U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_CHECKSUM1_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {7U, 1U, 0U, 8U, 1U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUTLIMIT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 2U, 6U, 10U, 7U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 1U, 0U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 1U, 1U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 1U, 2U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 1U, 4U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 1U, 5U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 0U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 1U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 2U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 4U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 5U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 6U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {2U, 1U, 7U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 0U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 1U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OUT_SC_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 2U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OUT_SC_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 4U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 5U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 6U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 1U, 7U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 0U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 1U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_PSFB_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 2U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_BOOSTSUB1_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_BOOSTSUB2_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 4U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_CAN_TIMEOUT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 5U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_CAN_E2E_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 6U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_INITIAL_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 7U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PRECHARGE_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 0U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 1U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HARD_FAILURE_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 2U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_PSFB_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_COUT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 4U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_VIN_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 5U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOV_VOUT_BOOST_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 6U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOV_VOUT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 7U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_BOOSTSUB1_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 0U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_BOOSTSUB2_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 1U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_BOOSTSUB1_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 2U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_BOOSTSUB2_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 3U, 1U, 0U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_SOFTVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {1U, 2U, 0U, 16U, 6U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_HARDVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {3U, 2U, 0U, 16U, 6U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_DCLINK_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {4U, 1U, 0U, 8U, 1U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_SR_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {5U, 1U, 0U, 8U, 1U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_TSFM_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {6U, 1U, 0U, 8U, 1U},
    /* Rx COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_PSFB_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX */
    {7U, 1U, 0U, 8U, 1U},
    /* Rx COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCOUTPUREQHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCWORKINGEANABLECMDHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX */
    {1U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUAPCU_OJCG_C_AIRPUMPMOTWORKINGENAHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCUOPCU_OJCG_C_OILPUMPMOTWORKINGENACMDHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_MAINPOSHIGHURLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_FUELCELLRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {1U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_BATTHEATPTCRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {1U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_ACSORYRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {4U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_PTCRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {4U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_MECURLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {4U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_DCDCRLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {4U, 1U, 6U, 2U, 46U},
    /* Rx COMCONF_COMSIGNAL_HCU3_OJCG_C_ACRLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX */
    {5U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1NEGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 2U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG2POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG2NEGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 1U, 6U, 2U, 46U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_WTRCOOLGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {1U, 1U, 0U, 2U, 47U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_INSULATIONTESTERCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {1U, 1U, 4U, 2U, 48U},
    /* Rx COMCONF_COMSIGNAL_BMS5_OJCG_C_MAINNEGRLYSTSBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX */
    {5U, 1U, 0U, 3U, 47U},
    /* Rx COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSUMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX */
    {0U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSCURMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX */
    {2U, 2U, 0U, 16U, 50U},
    /* Rx COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTTMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX */
    {4U, 1U, 0U, 8U, 45U},
    /* Rx COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERTMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX */
    {5U, 1U, 0U, 8U, 45U}
};
#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_NO_INIT
#include "Com_MemMap.h"
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MCU1_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_ECMCU_D3_sO0;
static Com_PduTpMonitorType Com_PduTpMonitor_ECMCU_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MCU3_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MCU21_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MCU22_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MCU23_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DM1MCU_D3_sO0;
static Com_PduTpMonitorType Com_PduTpMonitor_DM1MCU_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DM1MCU2_D3_sO0;
static Com_PduTpMonitorType Com_PduTpMonitor_DM1MCU2_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MCU2_D3_sO0;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_APCU1_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_APCU2_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DM1APCU_OjcG_c;
static Com_PduTpMonitorType Com_PduTpMonitor_DM1APCU_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DCDC1_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DM1DCDC_OjcG_c;
static Com_PduTpMonitorType Com_PduTpMonitor_DM1DCDC_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DM1OPCU_OjcG_c;
static Com_PduTpMonitorType Com_PduTpMonitor_DM1OPCU_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_OPCU1_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_OPCU2_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_RelayState_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_RelayState2_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_IMCU1PTU_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_MECU1Reserved_OjcG_c;
static VAR(Com_PduTriggerMonitorType, COM_VAR_NO_INIT) Com_TxTriggerM_DM1PTU_OjcG_c;
static Com_PduTpMonitorType Com_PduTpMonitor_DM1PTU_OjcG_c;
#define COM_STOP_SEC_VAR_NO_INIT
#include "Com_MemMap.h"


#define COM_START_SEC_VAR_NO_INIT
#include "Com_MemMap.h"
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MCU1_D3_sO0[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_ECMCU_D3_sO0[9U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MCU3_D3_sO0[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MCU21_D3_sO0[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MCU22_D3_sO0[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MCU23_D3_sO0[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DM1MCU_D3_sO0[12U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DM1MCU2_D3_sO0[12U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MCU2_D3_sO0[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DCDC_Cmd1_VR82BV[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_APCU1_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_APCU2_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DM1APCU_OjcG_c[12U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DCDC1_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DM1DCDC_OjcG_c[12U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DM1OPCU_OjcG_c[12U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_OPCU1_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_OPCU2_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_RelayState_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_RelayState2_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_IMCU1PTU_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_MECU1Reserved_OjcG_c[2U];
static VAR(uint32, COM_VAR_NO_INIT) Com_PduData_DM1PTU_OjcG_c[12U];
#define COM_STOP_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
VAR(COM_TxPduInfo_st, COM_CONFIG_DATA) Com_TxPduInfo[COM_TXPDU_NUM] = {/* WangM CONST-->VAR */
	{
		/* MCU1_D3_sO0 */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[0U],
		&Com_TxTriggerM_MCU1_D3_sO0,
		NULL_PTR,
		0U,
		0U,
		1U,
		0U,
		0U,
		0U,
		13U,
		(uint8*)Com_PduData_MCU1_D3_sO0,
		0U,
		0U,
	},
	{
		/* ECMCU_D3_sO0 */
		34U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[1U],
		&Com_TxTriggerM_ECMCU_D3_sO0,
		&Com_PduTpMonitor_ECMCU_D3_sO0,
		1U,
		1U,
		2U,
		0U,
		0U,
		13U,
		14U,
		(uint8*)Com_PduData_ECMCU_D3_sO0,
		1U,
		0U,
	},
	{
		/* MCU3_D3_sO0 */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[2U],
		&Com_TxTriggerM_MCU3_D3_sO0,
		NULL_PTR,
		2U,
		2U,
		3U,
		0U,
		0U,
		14U,
		18U,
		(uint8*)Com_PduData_MCU3_D3_sO0,
		2U,
		0U,
	},
	{
		/* MCU21_D3_sO0 */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[3U],
		&Com_TxTriggerM_MCU21_D3_sO0,
		NULL_PTR,
		3U,
		3U,
		4U,
		0U,
		0U,
		18U,
		31U,
		(uint8*)Com_PduData_MCU21_D3_sO0,
		3U,
		0U,
	},
	{
		/* MCU22_D3_sO0 */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[4U],
		&Com_TxTriggerM_MCU22_D3_sO0,
		NULL_PTR,
		4U,
		4U,
		5U,
		0U,
		0U,
		31U,
		35U,
		(uint8*)Com_PduData_MCU22_D3_sO0,
		4U,
		0U,
	},
	{
		/* MCU23_D3_sO0 */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[5U],
		&Com_TxTriggerM_MCU23_D3_sO0,
		NULL_PTR,
		5U,
		5U,
		6U,
		0U,
		0U,
		35U,
		39U,
		(uint8*)Com_PduData_MCU23_D3_sO0,
		5U,
		0U,
	},
	{
		/* DM1MCU_D3_sO0 */
		48U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[6U],
		&Com_TxTriggerM_DM1MCU_D3_sO0,
		&Com_PduTpMonitor_DM1MCU_D3_sO0,
		6U,
		6U,
		7U,
		0U,
		0U,
		39U,
		53U,
		(uint8*)Com_PduData_DM1MCU_D3_sO0,
		6U,
		0U,
	},
	{
		/* DM1MCU2_D3_sO0 */
		48U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[7U],
		&Com_TxTriggerM_DM1MCU2_D3_sO0,
		&Com_PduTpMonitor_DM1MCU2_D3_sO0,
		7U,
		7U,
		8U,
		0U,
		0U,
		53U,
		67U,
		(uint8*)Com_PduData_DM1MCU2_D3_sO0,
		7U,
		0U,
	},
	{
		/* MCU2_D3_sO0 */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[8U],
		&Com_TxTriggerM_MCU2_D3_sO0,
		NULL_PTR,
		8U,
		8U,
		9U,
		0U,
		0U,
		67U,
		71U,
		(uint8*)Com_PduData_MCU2_D3_sO0,
		8U,
		0U,
	},
	{
		/* DCDC_Cmd1_VR82BV */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[9U],
		NULL_PTR,
		NULL_PTR,
		9U,
		9U,
		10U,
		0U,
		0U,
		71U,
		82U,
		(uint8*)Com_PduData_DCDC_Cmd1_VR82BV,
		24U,
		0U,
	},
	{
		/* APCU1_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[10U],
		&Com_TxTriggerM_APCU1_OjcG_c,
		NULL_PTR,
		10U,
		10U,
		11U,
		0U,
		0U,
		82U,
		86U,
		(uint8*)Com_PduData_APCU1_OjcG_c,
		28U,
		0U,
	},
	{
		/* APCU2_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[11U],
		&Com_TxTriggerM_APCU2_OjcG_c,
		NULL_PTR,
		11U,
		11U,
		12U,
		0U,
		0U,
		86U,
		87U,
		(uint8*)Com_PduData_APCU2_OjcG_c,
		29U,
		0U,
	},
	{
		/* DM1APCU_OjcG_c */
		48U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[12U],
		&Com_TxTriggerM_DM1APCU_OjcG_c,
		&Com_PduTpMonitor_DM1APCU_OjcG_c,
		12U,
		12U,
		13U,
		0U,
		0U,
		87U,
		101U,
		(uint8*)Com_PduData_DM1APCU_OjcG_c,
		30U,
		0U,
	},
	{
		/* DCDC1_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[13U],
		&Com_TxTriggerM_DCDC1_OjcG_c,
		NULL_PTR,
		13U,
		13U,
		14U,
		0U,
		0U,
		101U,
		108U,
		(uint8*)Com_PduData_DCDC1_OjcG_c,
		31U,
		0U,
	},
	{
		/* DM1DCDC_OjcG_c */
		48U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[14U],
		&Com_TxTriggerM_DM1DCDC_OjcG_c,
		&Com_PduTpMonitor_DM1DCDC_OjcG_c,
		14U,
		14U,
		15U,
		0U,
		0U,
		108U,
		122U,
		(uint8*)Com_PduData_DM1DCDC_OjcG_c,
		32U,
		0U,
	},
	{
		/* DM1OPCU_OjcG_c */
		48U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[15U],
		&Com_TxTriggerM_DM1OPCU_OjcG_c,
		&Com_PduTpMonitor_DM1OPCU_OjcG_c,
		15U,
		15U,
		16U,
		0U,
		0U,
		122U,
		136U,
		(uint8*)Com_PduData_DM1OPCU_OjcG_c,
		33U,
		0U,
	},
	{
		/* OPCU1_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[16U],
		&Com_TxTriggerM_OPCU1_OjcG_c,
		NULL_PTR,
		16U,
		16U,
		17U,
		0U,
		0U,
		136U,
		139U,
		(uint8*)Com_PduData_OPCU1_OjcG_c,
		34U,
		0U,
	},
	{
		/* OPCU2_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[17U],
		&Com_TxTriggerM_OPCU2_OjcG_c,
		NULL_PTR,
		17U,
		17U,
		18U,
		0U,
		0U,
		139U,
		141U,
		(uint8*)Com_PduData_OPCU2_OjcG_c,
		35U,
		0U,
	},
	{
		/* RelayState_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[18U],
		&Com_TxTriggerM_RelayState_OjcG_c,
		NULL_PTR,
		18U,
		18U,
		19U,
		0U,
		0U,
		141U,
		156U,
		(uint8*)Com_PduData_RelayState_OjcG_c,
		36U,
		0U,
	},
	{
		/* RelayState2_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[19U],
		&Com_TxTriggerM_RelayState2_OjcG_c,
		NULL_PTR,
		19U,
		19U,
		20U,
		0U,
		0U,
		156U,
		163U,
		(uint8*)Com_PduData_RelayState2_OjcG_c,
		37U,
		0U,
	},
	{
		/* IMCU1PTU_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[20U],
		&Com_TxTriggerM_IMCU1PTU_OjcG_c,
		NULL_PTR,
		20U,
		20U,
		21U,
		0U,
		0U,
		163U,
		167U,
		(uint8*)Com_PduData_IMCU1PTU_OjcG_c,
		38U,
		0U,
	},
	{
		/* MECU1Reserved_OjcG_c */
		8U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[21U],
		&Com_TxTriggerM_MECU1Reserved_OjcG_c,
		NULL_PTR,
		21U,
		21U,
		22U,
		0U,
		0U,
		167U,
		168U,
		(uint8*)Com_PduData_MECU1Reserved_OjcG_c,
		39U,
		0U,
	},
	{
		/* DM1PTU_OjcG_c */
		48U,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		&COM_TxIM_Var[22U],
		&Com_TxTriggerM_DM1PTU_OjcG_c,
		&Com_PduTpMonitor_DM1PTU_OjcG_c,
		22U,
		22U,
		23U,
		0U,
		0U,
		168U,
		182U,
		(uint8*)Com_PduData_DM1PTU_OjcG_c,
		40U,
		0U,
	},
};

#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"
#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotoperatingmodeMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotRotDirtionMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotSysStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highprecisionMotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotCurMaxOutphighprecisionTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_CurMaxOutpTqofMotMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 125;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotSpdMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highUPwroffAllwedMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ActvdisChrgStMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotFailrStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgCnterMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgChksumMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotTqECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotAvlMaxGennhighprecisionTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotAvlMaxGennTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgCnterMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgChksumMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotoperatingmodeMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotRotDirtionMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotSysStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highprecisionMotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_otCurMaxOutphighprecisionTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_CurMaxOutpTqofMotMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 125;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotSpdMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highUPwroffAllwedMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ActvdisChrgStMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotFailrStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgCnterMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgChksumMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerbusUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerbusCurMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_otAvlMaxGennhighprecisionTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotAvlMaxGennTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgCnterMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgChksumMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_amberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_redstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_malFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashamberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashredstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashmalFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn8leastsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spnSecbyteDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FMiDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn3mostsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_occurrenceCntDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_spnCnvnMetHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_amberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_redstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_malFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashamberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashredstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashmalFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn8leastsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spnSecbyteDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FMiDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn3mostsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_occurrenceCntDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_spnCnvnMetHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerbusUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerbusCurMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx = 64;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_VouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_CouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Mode_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Enable_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Sleep_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Precharge_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Fault_Clear_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Dir_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Dir_Check_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Counter_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Checksum_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_APCUhighUbusUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_APCUMotworkingStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_APCUMotFailrStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_APCUOutpCurAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_dbc_Tx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_amberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_redstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_malFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashamberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashredstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashmalFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn8leastsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spnSecbyteDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FMiDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn3mostsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_occurrenceCntDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_spnCnvnMetHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDCInpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCInpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCOutpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCOutpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCworkingStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCFltStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_amberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_redstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_malFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashamberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashredstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashmalFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn8leastsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spnSecbyteDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FMiDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn3mostsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_occurrenceCntDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_spnCnvnMetHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_amberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_redstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_malFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashamberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashredstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashmalFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn8leastsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spnSecbyteDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FMiDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn3mostsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_occurrenceCntDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_spnCnvnMetHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_OPCUhighUbusUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_OPCUMotFailrStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_OPCUworkingStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_oilPUMPMotIvterTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_oilPUMPMotOutpCurOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx = 255;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_mainPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_mainnegtiveRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_pduFailrStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_preChrgnRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_fuelcellRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_PTCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_AcsoryRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MECURlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_mainPosRlyPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MECUPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_BattpackHeatgPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_BattpackHeatgNegRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_hydroCoolgRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_acRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg1PosRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg1NegRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg2NegRlyStsRelayState20_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg2NegRlyStsRelayState21_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_PwrBattURelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_BattheatPTCRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_WtrCoolgRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx = 7;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_insulationRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_sulationMonrdetectsUResdIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_insulationMonrSysStsIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_insulationMonrAlrmIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MECUbusbarUMECU1Reserved_MECU1Reserved_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_amberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_redstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_malFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashamberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashredstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FlashmalFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn8leastsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spnSecbyteDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_FMiDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_spn3mostsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_occurrenceCntDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_spnCnvnMetHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx = 0;

#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"
#define COM_START_SEC_VAR_INIT
#include "Com_MemMap.h"

#define COM_STOP_SEC_VAR_INIT
#include "Com_MemMap.h"
#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(COM_TxSignalInfo_st, COM_CONFIG_DATA) Com_TxSignalInfo[COM_TXSIG_NUM] = {
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotoperatingmodeMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTOPERATINGMODEMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotoperatingmodeMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTOPERATINGMODEMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotRotDirtionMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTROTDIRTIONMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotRotDirtionMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTROTDIRTIONMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotSysStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTSYSSTSMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotSysStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTSYSSTSMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_highprecisionMotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_HIGHPRECISIONMOTTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_highprecisionMotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_HIGHPRECISIONMOTTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCurMaxOutphighprecisionTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTCURMAXOUTPHIGHPRECISIONTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCurMaxOutphighprecisionTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTCURMAXOUTPHIGHPRECISIONTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotTqMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTTQMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_CurMaxOutpTqofMotMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_CURMAXOUTPTQOFMOTMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_CurMaxOutpTqofMotMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_CURMAXOUTPTQOFMOTMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotSpdMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTSPDMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotSpdMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTSPDMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_highUPwroffAllwedMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_HIGHUPWROFFALLWEDMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_highUPwroffAllwedMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_HIGHUPWROFFALLWEDMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ActvdisChrgStMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_ACTVDISCHRGSTMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_ActvdisChrgStMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_ACTVDISCHRGSTMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotFailrStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTFAILRSTSMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotFailrStsMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MOTFAILRSTSMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgCnterMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MSGCNTERMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgCnterMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MSGCNTERMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgChksumMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU1_D3_SO0_MSGCHKSUMMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgChksumMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU1_D3_SO0_MSGCHKSUMMCU1_MCU1_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		1U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotTqECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_ECMCU_D3_SO0_MOTTQECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotTqECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_ECMCU_D3_SO0_MOTTQECMCU_ECMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		2U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotAvlMaxGennhighprecisionTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU3_D3_SO0_MOTAVLMAXGENNHIGHPRECISIONTQMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotAvlMaxGennhighprecisionTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU3_D3_SO0_MOTAVLMAXGENNHIGHPRECISIONTQMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		2U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotAvlMaxGennTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU3_D3_SO0_MOTAVLMAXGENNTQMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotAvlMaxGennTqMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU3_D3_SO0_MOTAVLMAXGENNTQMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		2U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgCnterMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU3_D3_SO0_MSGCNTERMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgCnterMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU3_D3_SO0_MSGCNTERMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		2U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgChksumMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU3_D3_SO0_MSGCHKSUMMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgChksumMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU3_D3_SO0_MSGCHKSUMMCU3_MCU3_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotoperatingmodeMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTOPERATINGMODEMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotoperatingmodeMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTOPERATINGMODEMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotRotDirtionMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTROTDIRTIONMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotRotDirtionMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTROTDIRTIONMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotSysStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTSYSSTSMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotSysStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTSYSSTSMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_highprecisionMotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_HIGHPRECISIONMOTTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_highprecisionMotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_HIGHPRECISIONMOTTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_otCurMaxOutphighprecisionTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_OTCURMAXOUTPHIGHPRECISIONTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_otCurMaxOutphighprecisionTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_OTCURMAXOUTPHIGHPRECISIONTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotTqMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTTQMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_CurMaxOutpTqofMotMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_CURMAXOUTPTQOFMOTMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_CurMaxOutpTqofMotMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_CURMAXOUTPTQOFMOTMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotSpdMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTSPDMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotSpdMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTSPDMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_highUPwroffAllwedMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_HIGHUPWROFFALLWEDMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_highUPwroffAllwedMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_HIGHUPWROFFALLWEDMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ActvdisChrgStMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_ACTVDISCHRGSTMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_ActvdisChrgStMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_ACTVDISCHRGSTMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotFailrStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTFAILRSTSMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotFailrStsMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MOTFAILRSTSMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgCnterMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MSGCNTERMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgCnterMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MSGCNTERMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgChksumMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU21_D3_SO0_MSGCHKSUMMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgChksumMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU21_D3_SO0_MSGCHKSUMMCU21_MCU21_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		4U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCtrllerbusUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERBUSUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCtrllerbusUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERBUSUMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		4U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCtrllerbusCurMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERBUSCURMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCtrllerbusCurMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERBUSCURMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		4U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		4U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCtrllerTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCtrllerTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU22_D3_SO0_MOTCTRLLERTMCU22_MCU22_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		5U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_otAvlMaxGennhighprecisionTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU23_D3_SO0_OTAVLMAXGENNHIGHPRECISIONTQMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_otAvlMaxGennhighprecisionTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU23_D3_SO0_OTAVLMAXGENNHIGHPRECISIONTQMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		5U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotAvlMaxGennTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU23_D3_SO0_MOTAVLMAXGENNTQMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotAvlMaxGennTqMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU23_D3_SO0_MOTAVLMAXGENNTQMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		5U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgCnterMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU23_D3_SO0_MSGCNTERMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgCnterMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU23_D3_SO0_MSGCNTERMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		5U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MsgChksumMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU23_D3_SO0_MSGCHKSUMMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MsgChksumMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU23_D3_SO0_MSGCHKSUMMCU23_MCU23_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_PROTLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_ProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_PROTLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_amberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_AMBERWARNLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_amberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_AMBERWARNLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_redstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_REDSTOPLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_redstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_REDSTOPLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_malFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_MALFCTINDCRLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_malFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_MALFCTINDCRLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHPROTLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashProtlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHPROTLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashamberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHAMBERWARNLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashamberWarnlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHAMBERWARNLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashredstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHREDSTOPLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashredstoplampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHREDSTOPLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashmalFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHMALFCTINDCRLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashmalFctIndcrlampDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FLASHMALFCTINDCRLAMPDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn8leastsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPN8LEASTSIGNIFICANTBITSDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spn8leastsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPN8LEASTSIGNIFICANTBITSDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnSecbyteDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPNSECBYTEDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spnSecbyteDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPNSECBYTEDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FMiDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FMIDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FMiDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_FMIDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn3mostsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPN3MOSTSIGNIFICANTBITSDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spn3mostsignificantbitsDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPN3MOSTSIGNIFICANTBITSDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_occurrenceCntDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_OCCURRENCECNTDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_occurrenceCntDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_OCCURRENCECNTDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnCnvnMetHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPNCNVNMETHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spnCnvnMetHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU_D3_SO0_SPNCNVNMETHODDM1MCU_DM1MCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_PROTLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_ProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_PROTLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_amberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_AMBERWARNLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_amberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_AMBERWARNLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_redstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_REDSTOPLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_redstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_REDSTOPLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_malFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_MALFCTINDCRLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_malFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_MALFCTINDCRLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHPROTLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashProtlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHPROTLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashamberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHAMBERWARNLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashamberWarnlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHAMBERWARNLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashredstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHREDSTOPLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashredstoplampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHREDSTOPLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashmalFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHMALFCTINDCRLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FlashmalFctIndcrlampDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FLASHMALFCTINDCRLAMPDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn8leastsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPN8LEASTSIGNIFICANTBITSDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spn8leastsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPN8LEASTSIGNIFICANTBITSDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnSecbyteDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPNSECBYTEDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spnSecbyteDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPNSECBYTEDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FMiDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FMIDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_FMiDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_FMIDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn3mostsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPN3MOSTSIGNIFICANTBITSDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spn3mostsignificantbitsDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPN3MOSTSIGNIFICANTBITSDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_occurrenceCntDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_OCCURRENCECNTDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_occurrenceCntDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_OCCURRENCECNTDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnCnvnMetHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPNCNVNMETHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_spnCnvnMetHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1MCU2_D3_SO0_SPNCNVNMETHODDM1MCU2_DM1MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCtrllerbusUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERBUSUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCtrllerbusUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERBUSUMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCtrllerbusCurMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERBUSCURMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCtrllerbusCurMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERBUSCURMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MotCtrllerTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		COM_TRANS_TRIGGERED_WR,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX],
		(void*) &Com_bufptr_MotCtrllerTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MCU2_D3_SO0_MOTCTRLLERTMCU2_MCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_VouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_VOUSET_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_VouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_VOUSET_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_CouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_COUSET_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_CouSet_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_COUSET_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Mode_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_MODE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Mode_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_MODE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Enable_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_ENABLE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Enable_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_ENABLE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Sleep_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_SLEEP_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Sleep_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_SLEEP_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Precharge_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_PRECHARGE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Precharge_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_PRECHARGE_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Fault_Clear_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_FAULT_CLEAR_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Fault_Clear_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_FAULT_CLEAR_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Dir_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_DIR_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Dir_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_DIR_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Dir_Check_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_DIR_CHECK_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Dir_Check_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_DIR_CHECK_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Counter_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_COUNTER_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Counter_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_COUNTER_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDC_Checksum_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_CHECKSUM_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX],
		(void*) &Com_bufptr_DCDC_Checksum_DCDC_Cmd1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC_CMD1_VR82BV_DCDC_CHECKSUM_DCDC_CMD1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_TX]
	},
	{
		10U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_APCUhighUbusUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUHIGHUBUSUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_APCUhighUbusUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUHIGHUBUSUAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		10U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_APCUMotworkingStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUMOTWORKINGSTSAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_APCUMotworkingStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUMOTWORKINGSTSAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		10U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_APCUMotFailrStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUMOTFAILRSTSAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_APCUMotFailrStsAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUMOTFAILRSTSAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		10U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_APCUOutpCurAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUOUTPCURAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_APCUOutpCurAPCU1_APCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_APCU1_OJCG_C_APCUOUTPCURAPCU1_APCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_APCU2_OJCG_C_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_APCU2_OJCG_C_APCUTAPCU2_APCU2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_PROTLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_ProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_PROTLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_amberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_AMBERWARNLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_amberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_AMBERWARNLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_redstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_REDSTOPLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_redstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_REDSTOPLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_malFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_MALFCTINDCRLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_malFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_MALFCTINDCRLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHPROTLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashProtlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHPROTLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashamberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHAMBERWARNLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashamberWarnlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHAMBERWARNLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashredstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHREDSTOPLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashredstoplampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHREDSTOPLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashmalFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHMALFCTINDCRLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashmalFctIndcrlampDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FLASHMALFCTINDCRLAMPDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn8leastsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn8leastsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnSecbyteDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPNSECBYTEDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnSecbyteDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPNSECBYTEDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FMiDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FMIDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FMiDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_FMIDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn3mostsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn3mostsignificantbitsDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_occurrenceCntDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_OCCURRENCECNTDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_occurrenceCntDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_OCCURRENCECNTDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnCnvnMetHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPNCNVNMETHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnCnvnMetHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1APCU_OJCG_C_SPNCNVNMETHODDM1APCU_DM1APCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCInpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCINPUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCInpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCINPUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCInpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCINPCURDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCInpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCINPCURDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCOutpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCOUTPUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCOutpUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCOUTPUDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCOutpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCOUTPCURDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCOutpCurDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCOUTPCURDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCTDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCworkingStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCWORKINGSTSDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCworkingStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCWORKINGSTSDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCFltStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCFLTSTSDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCFltStsDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DCDC1_OJCG_C_DCDCFLTSTSDCDC1_DCDC1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_PROTLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_ProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_PROTLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_amberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_AMBERWARNLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_amberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_AMBERWARNLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_redstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_REDSTOPLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_redstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_REDSTOPLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_malFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_MALFCTINDCRLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_malFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_MALFCTINDCRLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHPROTLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashProtlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHPROTLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashamberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHAMBERWARNLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashamberWarnlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHAMBERWARNLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashredstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHREDSTOPLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashredstoplampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHREDSTOPLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashmalFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHMALFCTINDCRLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashmalFctIndcrlampDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FLASHMALFCTINDCRLAMPDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn8leastsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn8leastsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnSecbyteDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPNSECBYTEDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnSecbyteDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPNSECBYTEDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FMiDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FMIDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FMiDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_FMIDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn3mostsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn3mostsignificantbitsDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_occurrenceCntDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_OCCURRENCECNTDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_occurrenceCntDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_OCCURRENCECNTDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnCnvnMetHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPNCNVNMETHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnCnvnMetHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1DCDC_OJCG_C_SPNCNVNMETHODDM1DCDC_DM1DCDC_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_PROTLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_ProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_PROTLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_amberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_AMBERWARNLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_amberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_AMBERWARNLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_redstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_REDSTOPLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_redstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_REDSTOPLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_malFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_MALFCTINDCRLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_malFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_MALFCTINDCRLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHPROTLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashProtlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHPROTLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashamberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHAMBERWARNLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashamberWarnlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHAMBERWARNLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashredstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHREDSTOPLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashredstoplampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHREDSTOPLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashmalFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHMALFCTINDCRLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashmalFctIndcrlampDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FLASHMALFCTINDCRLAMPDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn8leastsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn8leastsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnSecbyteDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPNSECBYTEDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnSecbyteDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPNSECBYTEDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FMiDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FMIDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FMiDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_FMIDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn3mostsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn3mostsignificantbitsDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_occurrenceCntDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_OCCURRENCECNTDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_occurrenceCntDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_OCCURRENCECNTDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnCnvnMetHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPNCNVNMETHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnCnvnMetHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1OPCU_OJCG_C_SPNCNVNMETHODDM1OPCU_DM1OPCU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		16U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_OPCUhighUbusUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUHIGHUBUSUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_OPCUhighUbusUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUHIGHUBUSUOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		16U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_OPCUMotFailrStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUMOTFAILRSTSOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_OPCUMotFailrStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUMOTFAILRSTSOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		16U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_OPCUworkingStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUWORKINGSTSOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_OPCUworkingStsOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_OPCU1_OJCG_C_OPCUWORKINGSTSOPCU1_OPCU1_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		17U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_oilPUMPMotIvterTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_OPCU2_OJCG_C_OILPUMPMOTIVTERTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_oilPUMPMotIvterTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_OPCU2_OJCG_C_OILPUMPMOTIVTERTOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		17U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_oilPUMPMotOutpCurOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_OPCU2_OJCG_C_OILPUMPMOTOUTPCUROPCU2_OPCU2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_oilPUMPMotOutpCurOPCU2_OPCU2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_OPCU2_OJCG_C_OILPUMPMOTOUTPCUROPCU2_OPCU2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_mainPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINPOSRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_mainPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINPOSRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_mainnegtiveRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINNEGTIVERLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_mainnegtiveRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINNEGTIVERLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_pduFailrStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PDUFAILRSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_pduFailrStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PDUFAILRSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_preChrgnRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PRECHRGNRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_preChrgnRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PRECHRGNRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_fuelcellRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_FUELCELLRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_fuelcellRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_FUELCELLRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_PTCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PTCRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_PTCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_PTCRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_AcsoryRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_ACSORYRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_AcsoryRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_ACSORYRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MECURlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MECURLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_MECURlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MECURLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DCDCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_DCDCRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DCDCRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_DCDCRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_mainPosRlyPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINPOSRLYPWRONSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_mainPosRlyPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MAINPOSRLYPWRONSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MECUPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MECUPWRONSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_MECUPwronStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_MECUPWRONSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_BattpackHeatgPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_BATTPACKHEATGPOSRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_BattpackHeatgPosRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_BATTPACKHEATGPOSRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_BattpackHeatgNegRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_BATTPACKHEATGNEGRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_BattpackHeatgNegRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_BATTPACKHEATGNEGRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_hydroCoolgRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_HYDROCOOLGRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_hydroCoolgRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_HYDROCOOLGRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_acRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_ACRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_acRlyStsRelayState_RelayState_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE_OJCG_C_ACRLYSTSRELAYSTATE_RELAYSTATE_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DirtCurChrg1PosRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG1POSRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DirtCurChrg1PosRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG1POSRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DirtCurChrg1NegRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG1NEGRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DirtCurChrg1NegRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG1NEGRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DirtCurChrg2NegRlyStsRelayState20_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG2NEGRLYSTSRELAYSTATE20_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DirtCurChrg2NegRlyStsRelayState20_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG2NEGRLYSTSRELAYSTATE20_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_DirtCurChrg2NegRlyStsRelayState21_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG2NEGRLYSTSRELAYSTATE21_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_DirtCurChrg2NegRlyStsRelayState21_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_DIRTCURCHRG2NEGRLYSTSRELAYSTATE21_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_PwrBattURelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_PWRBATTURELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_PwrBattURelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_PWRBATTURELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_BattheatPTCRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_BATTHEATPTCRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_BattheatPTCRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_BATTHEATPTCRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_WtrCoolgRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_WTRCOOLGRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_WtrCoolgRlyStsRelayState2_RelayState2_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_RELAYSTATE2_OJCG_C_WTRCOOLGRLYSTSRELAYSTATE2_RELAYSTATE2_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_insulationRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_insulationRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONRIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_sulationMonrdetectsUResdIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_SULATIONMONRDETECTSURESDIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_sulationMonrdetectsUResdIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_SULATIONMONRDETECTSURESDIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_insulationMonrSysStsIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONMONRSYSSTSIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_insulationMonrSysStsIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONMONRSYSSTSIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_insulationMonrAlrmIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONMONRALRMIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_insulationMonrAlrmIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_IMCU1PTU_OJCG_C_INSULATIONMONRALRMIMCU1PTU_IMCU1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		21U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_MECUbusbarUMECU1Reserved_MECU1Reserved_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_MECU1RESERVED_OJCG_C_MECUBUSBARUMECU1RESERVED_MECU1RESERVED_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_MECUbusbarUMECU1Reserved_MECU1Reserved_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_MECU1RESERVED_OJCG_C_MECUBUSBARUMECU1RESERVED_MECU1RESERVED_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_ProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_PROTLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_ProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_PROTLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_amberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_AMBERWARNLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_amberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_AMBERWARNLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_redstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_REDSTOPLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_redstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_REDSTOPLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_malFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_MALFCTINDCRLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_malFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_MALFCTINDCRLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHPROTLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashProtlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHPROTLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashamberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHAMBERWARNLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashamberWarnlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHAMBERWARNLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashredstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHREDSTOPLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashredstoplampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHREDSTOPLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FlashmalFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHMALFCTINDCRLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FlashmalFctIndcrlampDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FLASHMALFCTINDCRLAMPDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn8leastsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn8leastsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPN8LEASTSIGNIFICANTBITSDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnSecbyteDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPNSECBYTEDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnSecbyteDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPNSECBYTEDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_FMiDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FMIDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_FMiDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_FMIDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spn3mostsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spn3mostsignificantbitsDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPN3MOSTSIGNIFICANTBITSDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_occurrenceCntDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_OCCURRENCECNTDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_occurrenceCntDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_OCCURRENCECNTDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
	{
		22U,
		COM_SIG_NO_GROUP_DEF,
		(void*) &Com_SigInitVal_spnCnvnMetHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		COM_TRANS_PENDING,
		&Com_SigSendSta_Var[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPNCNVNMETHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX],
		(void*) &Com_bufptr_spnCnvnMetHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_dbc_Tx,
		NULL_PTR,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COMCONF_COMSIGNAL_DM1PTU_OJCG_C_SPNCNVNMETHODDM1PTU_DM1PTU_FAW3_HVAC_V2_0DBC_DBC_TX]
	},
};

#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"
#define COM_START_SEC_VAR_INIT
#include "Com_MemMap.h"
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_TSC1Mtr_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_EEC2HCU_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_CCVSHCU_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_TC1_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_TC1Handle_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_ETC1_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_ETC2_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_AMT3_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_HCUMCU_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_HCUMCU2_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_SC_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_TSC1Mtr2_D3_sO0[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_DCDC_Status1_VR82BV[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_DCDC_Status2_VR82BV[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_DCDC_Status3_VR82BV[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_HCUDCDC_OjcG_c[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_HCUAPCU_OjcG_c[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_HCUOPCU_OjcG_c[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_HCU3_OjcG_c[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_BMS5_OjcG_c[2U] = {0x00U,0x00U,};
VAR(uint32, COM_VAR_INIT) COM_gstMsgmsg_DATA_MCU2_OjcG_c[2U] = {0x00U,0x00U,};
#define COM_STOP_SEC_VAR_INIT
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_NO_INIT
#include "Com_MemMap.h"
#define COM_STOP_SEC_VAR_NO_INIT
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
VAR(COM_RxPduInfo_st, COM_CONFIG_DATA) Com_RxPduInfo[COM_RXPDU_NUM] = {/* WangM CONST-->VAR */
	{
		/* TSC1Mtr_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[0],
		23U,
		24U,
		0U,
		0U,
		0U,
		8U,
		(uint8*)COM_gstMsgmsg_DATA_TSC1Mtr_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_TSC1Mtr_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* EEC2HCU_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[1],
		24U,
		25U,
		0U,
		0U,
		8U,
		9U,
		(uint8*)COM_gstMsgmsg_DATA_EEC2HCU_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_EEC2HCU_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* CCVSHCU_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[2],
		25U,
		26U,
		0U,
		0U,
		9U,
		11U,
		(uint8*)COM_gstMsgmsg_DATA_CCVSHCU_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_CCVSHCU_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* TC1_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[3],
		26U,
		27U,
		0U,
		0U,
		11U,
		13U,
		(uint8*)COM_gstMsgmsg_DATA_TC1_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_TC1_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* TC1Handle_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[4],
		27U,
		28U,
		0U,
		0U,
		13U,
		14U,
		(uint8*)COM_gstMsgmsg_DATA_TC1Handle_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_TC1Handle_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* ETC1_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[5],
		28U,
		29U,
		0U,
		0U,
		14U,
		15U,
		(uint8*)COM_gstMsgmsg_DATA_ETC1_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_ETC1_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* ETC2_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[6],
		29U,
		30U,
		0U,
		0U,
		15U,
		18U,
		(uint8*)COM_gstMsgmsg_DATA_ETC2_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_ETC2_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* AMT3_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[7],
		30U,
		31U,
		0U,
		0U,
		18U,
		28U,
		(uint8*)COM_gstMsgmsg_DATA_AMT3_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_AMT3_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		600U,
		600U,
	},
	{
		/* HCUMCU_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[8],
		31U,
		32U,
		0U,
		0U,
		28U,
		39U,
		(uint8*)COM_gstMsgmsg_DATA_HCUMCU_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_HCUMCU_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* HCUMCU2_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[9],
		32U,
		33U,
		0U,
		0U,
		39U,
		50U,
		(uint8*)COM_gstMsgmsg_DATA_HCUMCU2_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_HCUMCU2_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* SC_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[10],
		33U,
		34U,
		0U,
		0U,
		50U,
		51U,
		(uint8*)COM_gstMsgmsg_DATA_SC_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_SC_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* TSC1Mtr2_D3_sO0 */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[11],
		34U,
		35U,
		0U,
		0U,
		51U,
		59U,
		(uint8*)COM_gstMsgmsg_DATA_TSC1Mtr2_D3_sO0,
		NULL_PTR,
		Com_RxIpduCallout_TSC1Mtr2_D3_sO0,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* DCDC_Status1_VR82BV */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[12],
		35U,
		36U,
		0U,
		0U,
		59U,
		69U,
		(uint8*)COM_gstMsgmsg_DATA_DCDC_Status1_VR82BV,
		NULL_PTR,
		Com_RxIpduCallout_DCDC_Status1_VR82BV,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* DCDC_Status2_VR82BV */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[13],
		36U,
		37U,
		0U,
		0U,
		69U,
		112U,
		(uint8*)COM_gstMsgmsg_DATA_DCDC_Status2_VR82BV,
		NULL_PTR,
		Com_RxIpduCallout_DCDC_Status2_VR82BV,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* DCDC_Status3_VR82BV */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[14],
		37U,
		38U,
		0U,
		0U,
		112U,
		118U,
		(uint8*)COM_gstMsgmsg_DATA_DCDC_Status3_VR82BV,
		NULL_PTR,
		Com_RxIpduCallout_DCDC_Status3_VR82BV,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* HCUDCDC_OjcG_c */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[15],
		38U,
		39U,
		0U,
		0U,
		118U,
		120U,
		(uint8*)COM_gstMsgmsg_DATA_HCUDCDC_OjcG_c,
		NULL_PTR,
		Com_RxIpduCallout_HCUDCDC_OjcG_c,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* HCUAPCU_OjcG_c */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[16],
		39U,
		40U,
		0U,
		0U,
		120U,
		121U,
		(uint8*)COM_gstMsgmsg_DATA_HCUAPCU_OjcG_c,
		NULL_PTR,
		Com_RxIpduCallout_HCUAPCU_OjcG_c,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* HCUOPCU_OjcG_c */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[17],
		40U,
		41U,
		0U,
		0U,
		121U,
		122U,
		(uint8*)COM_gstMsgmsg_DATA_HCUOPCU_OjcG_c,
		NULL_PTR,
		Com_RxIpduCallout_HCUOPCU_OjcG_c,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* HCU3_OjcG_c */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[18],
		41U,
		42U,
		0U,
		0U,
		122U,
		130U,
		(uint8*)COM_gstMsgmsg_DATA_HCU3_OjcG_c,
		NULL_PTR,
		Com_RxIpduCallout_HCU3_OjcG_c,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
	{
		/* BMS5_OjcG_c */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[19],
		42U,
		43U,
		0U,
		0U,
		130U,
		137U,
		(uint8*)COM_gstMsgmsg_DATA_BMS5_OjcG_c,
		NULL_PTR,
		Com_RxIpduCallout_BMS5_OjcG_c,
		COM_PDU_SIGPRCS_DEFERRED,
		100U,
		100U,
	},
	{
		/* MCU2_OjcG_c */
		COM_PDU_TYPE_NORMAL,
		COM_PDU_TYPE_ACTIVE_CONTROL,
		8U,
		&COM_RxIM_Var[20],
		43U,
		44U,
		0U,
		0U,
		137U,
		141U,
		(uint8*)COM_gstMsgmsg_DATA_MCU2_OjcG_c,
		NULL_PTR,
		Com_RxIpduCallout_MCU2_OjcG_c,
		COM_PDU_SIGPRCS_DEFERRED,
		200U,
		200U,
	},
};

#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_OvrdCtrlmodeTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqedSpdCtrlCdnsTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_OvrdCtrlmodePrioTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_ReqedSpdSpdLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqedTqTqLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqedTqfrActnalTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgCnterTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgChksumTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_AccrPedlapPosn_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_PrkgBrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_BrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_TrsmReqedgearTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_Trsmmode2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_TrsmReqedgearTC1Handle_TC1Handle_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ShiftinProcETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_SeledgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_ActgearRatETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_CurgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqHCUtoCtrltheMotAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_TrsmgearselfLrningStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_holdCurgearReqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_CluStsAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_SersparallelmodeStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_CluCnsedTqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_SwtStoftheFpickerAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DrvgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_PrkgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ptobindingStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_theReqedMotoperatingmodeHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highprecisionMotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 255;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotSpdReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotworkEnaCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotNeghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotPoshighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotpreChrghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highUPwroffReqofMotHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotActvdisChrgCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MaxSpdLimUnderCurloadHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 65535;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_theReqedMotoperatingmodeHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highprecisionMotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 255;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotSpdReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotworkEnaCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotNeghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotPoshighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotpreChrghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_highUPwroffReqofMotHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotActvdisChrgCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MaxSpdLimUnderCurloadHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 65535;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ptoSwtCmdSC_SC_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_OvrdCtrlmodeTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqedSpdCtrlCdnsTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_OvrdCtrlmodePrioTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 3;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_ReqedSpdSpdLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqedTqTqLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 125;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_ReqedTqfrActnalTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 15;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgCnterTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MsgChksumTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_VIn_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Cout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_ModeFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_DirFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Cmdsrc_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Faultlevel_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_State_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Counter1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Checksum1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_CoutLimit_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vin_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vin_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vin_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vin_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vin_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vin_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Vout_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Cout_OC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Cout_OC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Cout_OC_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Cout_OC_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Out_SC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Out_SC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_PSFB_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_PSFB_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_PSFB_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_SR_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_SR_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_SR_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_OC_PSFB_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_OC_BoostSub1_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_OC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_CAN_Timeout_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_CAN_E2E_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Initial_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Precharge_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_PSFB_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Hard_Failure_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOC_PSFB_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOC_Cout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOC_Vin_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOV_Vout_Boost_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOV_Vout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOC_BoostSub1_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HOC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_BoostSub1_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(boolean, COM_CONFIG_DATA) Com_SigInitVal_DCDC_BoostSub2_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_SoftVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_DCDC_HardVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Temp_Dclink_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Temp_SR_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Temp_TSFM_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDC_Temp_PSFB_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCOutpUReqHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCworkingeanableCmdHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_airPUMPMotworkingEnaHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_oilPUMPMotworkingEnaCmdHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_mainPoshighURlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_fuelcellRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_BattheatPTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_AcsoryRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_PTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MECURlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DCDCRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_acRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg1PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg1NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg2PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_DirtCurChrg2NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_WtrCoolgRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_insulationtesterCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 3;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_mainNegRlyStsBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 7;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerbusUMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 0;
CONST(uint16, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerbusCurMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 32000;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 64;
CONST(uint8, COM_CONFIG_DATA) Com_SigInitVal_MotCtrllerTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 64;
#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"


#define COM_START_SEC_VAR_INIT
#include "Com_MemMap.h"
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_OvrdCtrlmodeTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqedSpdCtrlCdnsTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_OvrdCtrlmodePrioTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_ReqedSpdSpdLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqedTqTqLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqedTqfrActnalTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MsgCnterTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MsgChksumTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_AccrPedlapPosn_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_PrkgBrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_BrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_TrsmReqedgearTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_Trsmmode2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_TrsmReqedgearTC1Handle_TC1Handle_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ShiftinProcETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_SeledgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_ActgearRatETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_CurgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqHCUtoCtrltheMotAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_TrsmgearselfLrningStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_holdCurgearReqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_CluStsAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_SersparallelmodeStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_CluCnsedTqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_SwtStoftheFpickerAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DrvgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_PrkgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ptobindingStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_theReqedMotoperatingmodeHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_highprecisionMotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_MotSpdReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotworkEnaCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotNeghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotPoshighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotpreChrghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_highUPwroffReqofMotHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotActvdisChrgCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_MaxSpdLimUnderCurloadHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_theReqedMotoperatingmodeHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_highprecisionMotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_MotSpdReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotworkEnaCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotNeghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotPoshighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotpreChrghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_highUPwroffReqofMotHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotActvdisChrgCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_MaxSpdLimUnderCurloadHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ptoSwtCmdSC_SC_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_OvrdCtrlmodeTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqedSpdCtrlCdnsTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_OvrdCtrlmodePrioTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_ReqedSpdSpdLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqedTqTqLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_ReqedTqfrActnalTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MsgCnterTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MsgChksumTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_DCDC_VIn_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_DCDC_Cout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_ModeFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_DirFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Cmdsrc_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Faultlevel_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_State_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Counter1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Checksum1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_DCDC_CoutLimit_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vin_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vin_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vin_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vin_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vin_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vin_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Vout_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Cout_OC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Cout_OC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Cout_OC_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Cout_OC_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Out_SC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Out_SC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_PSFB_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_PSFB_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_PSFB_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_SR_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_SR_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_SR_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_OC_PSFB_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_OC_BoostSub1_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_OC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_CAN_Timeout_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_CAN_E2E_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Initial_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Precharge_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_PSFB_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_Hard_Failure_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOC_PSFB_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOC_Cout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOC_Vin_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOV_Vout_Boost_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOV_Vout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOC_BoostSub1_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_HOC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_BoostSub1_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(boolean, COM_VAR_INIT) Com_SigRteValue_DCDC_BoostSub2_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_DCDC_SoftVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_DCDC_HardVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Temp_Dclink_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Temp_SR_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Temp_TSFM_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDC_Temp_PSFB_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDCOutpUReqHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDCworkingeanableCmdHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_airPUMPMotworkingEnaHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_oilPUMPMotworkingEnaCmdHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_mainPoshighURlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_fuelcellRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_BattheatPTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_AcsoryRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_PTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MECURlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DCDCRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_acRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DirtCurChrg1PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DirtCurChrg1NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DirtCurChrg2PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_DirtCurChrg2NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_WtrCoolgRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_insulationtesterCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_mainNegRlyStsBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_MotCtrllerbusUMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint16, COM_VAR_INIT) Com_SigRteValue_MotCtrllerbusCurMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
VAR(uint8, COM_VAR_INIT) Com_SigRteValue_MotCtrllerTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx = 0U;
#define COM_STOP_SEC_VAR_INIT
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_INIT
#include "Com_MemMap.h"
#if (COM_RXUPDATEBITCFG_SUPPORT == STD_ON)
VAR(uint16, COM_VAR_INIT) rxSigUpdateCtn[COM_RXSIG_NUM] = {0U};
#endif
#define COM_STOP_SEC_VAR_INIT
#include "Com_MemMap.h"
#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
VAR(COM_RxSignalInfo_st, COM_CONFIG_DATA) Com_RxSignalInfo[COM_RXSIG_NUM] = {
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_TSC1Mtr_D3_sO0,
		(void *)&Com_SigInitVal_OvrdCtrlmodeTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODETSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_OvrdCtrlmodeTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODETSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedSpdCtrlCdnsTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDSPDCTRLCDNSTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedSpdCtrlCdnsTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDSPDCTRLCDNSTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_OvrdCtrlmodePrioTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODEPRIOTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_OvrdCtrlmodePrioTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODEPRIOTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedSpdSpdLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDSPDSPDLIMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedSpdSpdLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDSPDSPDLIMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedTqTqLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDTQTQLIMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedTqTqLimTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDTQTQLIMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedTqfrActnalTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDTQFRACTNALTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedTqfrActnalTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_REQEDTQFRACTNALTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MsgCnterTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_MSGCNTERTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MsgCnterTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_MSGCNTERTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		0U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MsgChksumTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_MSGCHKSUMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MsgChksumTSC1Mtr_TSC1Mtr_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_MSGCHKSUMTSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		1U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_EEC2HCU_D3_sO0,
		(void *)&Com_SigInitVal_AccrPedlapPosn_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_EEC2HCU_D3_SO0_ACCRPEDLAPPOSN_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_AccrPedlapPosn_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_EEC2HCU_D3_SO0_ACCRPEDLAPPOSN_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		2U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_CCVSHCU_D3_sO0,
		(void *)&Com_SigInitVal_PrkgBrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_PRKGBRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_PrkgBrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_PRKGBRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		2U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_BrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_BRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_BrkSwtCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_BRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_TC1_D3_sO0,
		(void *)&Com_SigInitVal_TrsmReqedgearTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMREQEDGEARTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_TrsmReqedgearTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMREQEDGEARTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		3U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_Trsmmode2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMMODE2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_Trsmmode2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMMODE2TC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		4U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_TC1Handle_D3_sO0,
		(void *)&Com_SigInitVal_TrsmReqedgearTC1Handle_TC1Handle_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TC1HANDLE_D3_SO0_TRSMREQEDGEARTC1HANDLE_TC1HANDLE_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_TrsmReqedgearTC1Handle_TC1Handle_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TC1HANDLE_D3_SO0_TRSMREQEDGEARTC1HANDLE_TC1HANDLE_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		5U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_ETC1_D3_sO0,
		(void *)&Com_SigInitVal_ShiftinProcETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_ETC1_D3_SO0_SHIFTINPROCETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ShiftinProcETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_ETC1_D3_SO0_SHIFTINPROCETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_ETC2_D3_sO0,
		(void *)&Com_SigInitVal_SeledgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_ETC2_D3_SO0_SELEDGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_SeledgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_ETC2_D3_SO0_SELEDGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ActgearRatETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_ETC2_D3_SO0_ACTGEARRATETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ActgearRatETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_ETC2_D3_SO0_ACTGEARRATETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		6U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_CurgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_ETC2_D3_SO0_CURGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_CurgearETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_ETC2_D3_SO0_CURGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_AMT3_D3_sO0,
		(void *)&Com_SigInitVal_ReqHCUtoCtrltheMotAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_REQHCUTOCTRLTHEMOTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqHCUtoCtrltheMotAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_REQHCUTOCTRLTHEMOTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_TrsmgearselfLrningStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_TRSMGEARSELFLRNINGSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_TrsmgearselfLrningStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_TRSMGEARSELFLRNINGSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_holdCurgearReqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_HOLDCURGEARREQAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_holdCurgearReqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_HOLDCURGEARREQAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_CluStsAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_CLUSTSAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_CluStsAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_CLUSTSAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_SersparallelmodeStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_SERSPARALLELMODESTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_SersparallelmodeStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_SERSPARALLELMODESTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_CluCnsedTqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_CLUCNSEDTQAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_CluCnsedTqAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_CLUCNSEDTQAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_SwtStoftheFpickerAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_SWTSTOFTHEFPICKERAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_SwtStoftheFpickerAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_SWTSTOFTHEFPICKERAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DrvgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_DRVGFSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_DrvgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_DRVGFSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_PrkgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_PRKGFSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_PrkgFStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_PRKGFSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		7U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ptobindingStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_AMT3_D3_SO0_PTOBINDINGSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ptobindingStAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_AMT3_D3_SO0_PTOBINDINGSTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_HCUMCU_D3_sO0,
		(void *)&Com_SigInitVal_theReqedMotoperatingmodeHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_theReqedMotoperatingmodeHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_highprecisionMotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_HIGHPRECISIONMOTTQREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_highprecisionMotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_HIGHPRECISIONMOTTQREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTTQREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotTqReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTTQREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotSpdReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTSPDREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotSpdReqedHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTSPDREQEDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotworkEnaCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTWORKENACMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotworkEnaCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTWORKENACMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotNeghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTNEGHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotNeghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTNEGHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotPoshighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTPOSHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotPoshighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTPOSHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotpreChrghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTPRECHRGHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotpreChrghighURlyCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTPRECHRGHIGHURLYCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_highUPwroffReqofMotHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_HIGHUPWROFFREQOFMOTHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_highUPwroffReqofMotHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_HIGHUPWROFFREQOFMOTHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotActvdisChrgCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTACTVDISCHRGCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotActvdisChrgCmdHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MOTACTVDISCHRGCMDHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		8U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MaxSpdLimUnderCurloadHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MAXSPDLIMUNDERCURLOADHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MaxSpdLimUnderCurloadHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU_D3_SO0_MAXSPDLIMUNDERCURLOADHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_HCUMCU2_D3_sO0,
		(void *)&Com_SigInitVal_theReqedMotoperatingmodeHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_theReqedMotoperatingmodeHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_highprecisionMotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_HIGHPRECISIONMOTTQREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_highprecisionMotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_HIGHPRECISIONMOTTQREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTTQREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotTqReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTTQREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotSpdReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTSPDREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotSpdReqedHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTSPDREQEDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotworkEnaCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTWORKENACMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotworkEnaCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTWORKENACMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotNeghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTNEGHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotNeghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTNEGHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotPoshighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTPOSHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotPoshighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTPOSHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotpreChrghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTPRECHRGHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotpreChrghighURlyCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTPRECHRGHIGHURLYCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_highUPwroffReqofMotHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_HIGHUPWROFFREQOFMOTHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_highUPwroffReqofMotHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_HIGHUPWROFFREQOFMOTHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotActvdisChrgCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTACTVDISCHRGCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MotActvdisChrgCmdHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MOTACTVDISCHRGCMDHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		9U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MaxSpdLimUnderCurloadHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MAXSPDLIMUNDERCURLOADHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MaxSpdLimUnderCurloadHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_MAXSPDLIMUNDERCURLOADHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		10U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_SC_D3_sO0,
		(void *)&Com_SigInitVal_ptoSwtCmdSC_SC_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_SC_D3_SO0_PTOSWTCMDSC_SC_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ptoSwtCmdSC_SC_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_SC_D3_SO0_PTOSWTCMDSC_SC_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_TSC1Mtr2_D3_sO0,
		(void *)&Com_SigInitVal_OvrdCtrlmodeTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODETSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_OvrdCtrlmodeTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODETSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedSpdCtrlCdnsTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDSPDCTRLCDNSTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedSpdCtrlCdnsTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDSPDCTRLCDNSTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_OvrdCtrlmodePrioTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODEPRIOTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_OvrdCtrlmodePrioTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODEPRIOTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedSpdSpdLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDSPDSPDLIMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedSpdSpdLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDSPDSPDLIMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedTqTqLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDTQTQLIMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedTqTqLimTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDTQTQLIMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_ReqedTqfrActnalTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDTQFRACTNALTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_ReqedTqfrActnalTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_REQEDTQFRACTNALTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MsgCnterTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_MSGCNTERTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MsgCnterTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_MSGCNTERTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		11U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MsgChksumTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_MSGCHKSUMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX],
		(void *)&Com_SigRteValue_MsgChksumTSC1Mtr2_TSC1Mtr2_FAW_MCD_MCU_CAN_V1_4_1_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_MSGCHKSUMTSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_DCDC_Status1_VR82BV,
		(void *)&Com_SigInitVal_DCDC_VIn_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VIN_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_VIn_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VIN_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VOUT_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VOUT_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Cout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_COUT_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Cout_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_COUT_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_ModeFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_MODEFB_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_ModeFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_MODEFB_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_DirFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_DIRFB_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_DirFB_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_DIRFB_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Cmdsrc_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_CMDSRC_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Cmdsrc_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_CMDSRC_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Faultlevel_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_FAULTLEVEL_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Faultlevel_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_FAULTLEVEL_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_State_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_STATE_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_State_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_STATE_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Counter1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_COUNTER1_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Counter1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_COUNTER1_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		12U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Checksum1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_CHECKSUM1_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Checksum1_DCDC_Status1_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_CHECKSUM1_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_DCDC_Status2_VR82BV,
		(void *)&Com_SigInitVal_DCDC_CoutLimit_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUTLIMIT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_CoutLimit_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUTLIMIT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vin_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vin_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vin_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vin_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vin_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vin_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_OV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vin_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vin_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vin_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vin_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vin_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vin_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VIN_UV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_OV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_OV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_OV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_OV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_UV_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_UV_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Vout_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Vout_UV_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_VOUT_UV_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Cout_OC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Cout_OC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Cout_OC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Cout_OC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Cout_OC_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Cout_OC_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Cout_OC_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Cout_OC_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUT_OC_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Out_SC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OUT_SC_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Out_SC_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OUT_SC_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Out_SC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OUT_SC_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Out_SC_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OUT_SC_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_PSFB_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_PSFB_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_PSFB_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_PSFB_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_PSFB_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_PSFB_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_OT_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_SR_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_SR_OT_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_SR_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_SR_OT_level3_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL3_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_SR_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_SR_OT_level4_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_SR_OT_LEVEL4_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_OC_PSFB_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_PSFB_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_OC_PSFB_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_PSFB_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_OC_BoostSub1_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_BOOSTSUB1_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_OC_BoostSub1_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_BOOSTSUB1_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_OC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_BOOSTSUB2_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_OC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_OC_BOOSTSUB2_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_CAN_Timeout_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_CAN_TIMEOUT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_CAN_Timeout_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_CAN_TIMEOUT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_CAN_E2E_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_CAN_E2E_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_CAN_E2E_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_CAN_E2E_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Initial_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_INITIAL_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Initial_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_INITIAL_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Precharge_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PRECHARGE_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Precharge_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PRECHARGE_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_PSFB_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_PSFB_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_PSFB_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Hard_Failure_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HARD_FAILURE_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Hard_Failure_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HARD_FAILURE_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOC_PSFB_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_PSFB_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOC_PSFB_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_PSFB_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOC_Cout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_COUT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOC_Cout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_COUT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOC_Vin_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_VIN_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOC_Vin_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_VIN_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOV_Vout_Boost_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOV_VOUT_BOOST_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOV_Vout_Boost_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOV_VOUT_BOOST_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOV_Vout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOV_VOUT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOV_Vout_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOV_VOUT_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOC_BoostSub1_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_BOOSTSUB1_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOC_BoostSub1_level1_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_BOOSTSUB1_LEVEL1_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HOC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_BOOSTSUB2_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HOC_BoostSub2_level2_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_HOC_BOOSTSUB2_LEVEL2_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_BoostSub1_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_BOOSTSUB1_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_BoostSub1_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_BOOSTSUB1_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		13U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_BoostSub2_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_BOOSTSUB2_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_BoostSub2_CS_Failure_DCDC_Status2_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_BOOSTSUB2_CS_FAILURE_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_DCDC_Status3_VR82BV,
		(void *)&Com_SigInitVal_DCDC_SoftVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_SOFTVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_SoftVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_SOFTVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_HardVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_HARDVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_HardVer_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_HARDVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Temp_Dclink_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_DCLINK_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Temp_Dclink_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_DCLINK_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Temp_SR_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_SR_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Temp_SR_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_SR_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Temp_TSFM_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_TSFM_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Temp_TSFM_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_TSFM_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		14U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDC_Temp_PSFB_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_PSFB_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX],
		(void *)&Com_SigRteValue_DCDC_Temp_PSFB_DCDC_Status3_CAN_Matrix_DCDC_V0_1_20250414_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_TEMP_PSFB_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_HCUDCDC_OjcG_c,
		(void *)&Com_SigInitVal_DCDCOutpUReqHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCOUTPUREQHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DCDCOutpUReqHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCOUTPUREQHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		15U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDCworkingeanableCmdHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCWORKINGEANABLECMDHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DCDCworkingeanableCmdHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCWORKINGEANABLECMDHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		16U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_HCUAPCU_OjcG_c,
		(void *)&Com_SigInitVal_airPUMPMotworkingEnaHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUAPCU_OJCG_C_AIRPUMPMOTWORKINGENAHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_airPUMPMotworkingEnaHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUAPCU_OJCG_C_AIRPUMPMOTWORKINGENAHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		17U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_HCUOPCU_OjcG_c,
		(void *)&Com_SigInitVal_oilPUMPMotworkingEnaCmdHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCUOPCU_OJCG_C_OILPUMPMOTWORKINGENACMDHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_oilPUMPMotworkingEnaCmdHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCUOPCU_OJCG_C_OILPUMPMOTWORKINGENACMDHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_HCU3_OjcG_c,
		(void *)&Com_SigInitVal_mainPoshighURlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_MAINPOSHIGHURLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_mainPoshighURlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_MAINPOSHIGHURLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_fuelcellRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_FUELCELLRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_fuelcellRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_FUELCELLRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_BattheatPTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_BATTHEATPTCRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_BattheatPTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_BATTHEATPTCRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_AcsoryRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_ACSORYRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_AcsoryRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_ACSORYRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_PTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_PTCRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_PTCRlyCtrlCmdHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_PTCRLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MECURlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_MECURLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_MECURlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_MECURLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DCDCRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_DCDCRLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DCDCRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_DCDCRLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		18U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_acRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_HCU3_OJCG_C_ACRLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_acRlyclosingReqHCU3_HCU3_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_HCU3_OJCG_C_ACRLYCLOSINGREQHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_BMS5_OjcG_c,
		(void *)&Com_SigInitVal_DirtCurChrg1PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DirtCurChrg1PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DirtCurChrg1NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1NEGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DirtCurChrg1NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1NEGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DirtCurChrg2PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG2POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DirtCurChrg2PosRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG2POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_DirtCurChrg2NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG2NEGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_DirtCurChrg2NegRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG2NEGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_WtrCoolgRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_WTRCOOLGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_WtrCoolgRlyCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_WTRCOOLGRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_insulationtesterCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_INSULATIONTESTERCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_insulationtesterCtrlCmdBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_INSULATIONTESTERCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		19U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_mainNegRlyStsBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_BMS5_OJCG_C_MAINNEGRLYSTSBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_mainNegRlyStsBMS5_BMS5_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_BMS5_OJCG_C_MAINNEGRLYSTSBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		Com_RxIpduTimeout_MCU2_OjcG_c,
		(void *)&Com_SigInitVal_MotCtrllerbusUMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSUMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_MotCtrllerbusUMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSUMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotCtrllerbusCurMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSCURMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_MotCtrllerbusCurMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSCURMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTTMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_MotTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTTMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
	{
		20U,
		COM_SIG_NO_GROUP_DEF,
		NULL_PTR,
		(void *)&Com_SigInitVal_MotCtrllerTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		&COM_RxSigIM_Var[COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERTMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX],
		(void *)&Com_SigRteValue_MotCtrllerTMCU2_MCU2_FAW3_HVAC_V2_0DBC_dbc_Rx,
		NULL_PTR,
		(Com_SignalBaseInfo_st*)&Com_SignalBaseInfo[COM_TXSIG_NUM + COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERTMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX]
	},
};

#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"

#define COM_START_SEC_CONFIG_DATA
#include "Com_MemMap.h"
CONST(Com_GwMappingSigType, COM_CONFIG_DATA) Com_GwInfo[COM_GWSIGNAL_NUM + 1U] = {
	{
		0U,
	}
};
#define COM_STOP_SEC_CONFIG_DATA
#include "Com_MemMap.h"
