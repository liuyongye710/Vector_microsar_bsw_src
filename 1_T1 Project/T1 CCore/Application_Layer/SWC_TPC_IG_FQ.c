#include "SWC_TPC_IG_FQ.h"
#include "SWC_TPC_IG_FQ_private.h"
#include "look1_iflf_binlcapw.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlcapw.h"

#define SWC_TPC_IG_FQ_IN_CoolantFolw2L ((uint8_T)1U)
#define SWC_TPC_IG_FQ_IN_CoolantFolw4L ((uint8_T)2U)
#define SWC_TPC_IG_FQ_IN_CoolantFolw6L ((uint8_T)3U)
#define SWC_TPC_IG_FQ_IN_CoolantFolw8L ((uint8_T)4U)

#define SWC_TPC_IG_FQ_IN_NormalMode    ((uint8_T)1U)
#define SWC_TPC_IG_FQ_IN_Overheating   ((uint8_T)2U)
#define SWC_TPC_IG_FQ_IN_PowerSave1    ((uint8_T)3U)
#define SWC_TPC_IG_FQ_IN_PowerSave2    ((uint8_T)4U)

real32_T VAR_TpcSmp_uDcLnkMax_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrVoltGen_f32_FQ;
real32_T VAR_TpcMot_TrqGenExCOrg_f32_FQ;
real32_T VAR_TpcMot_TrqElecExCOrg_f32_FQ;
real32_T VAR_TpcMot_TrqGenExC_f32_FQ;
real32_T VAR_TpcMot_GenPwrRef_f32_FQ;
real32_T VAR_TpcMot_TrqElecExC_f32_FQ;
real32_T TPC_TrqMaxTrans_FQ;
real32_T TPC_TrqMinTrans_FQ;
real32_T VAR_TpcSmp_TrqMaxCanSet_f32_FQ;
real32_T VAR_TpcBlk_IsValid_f32_FQ;
real32_T VAR_Tpcblk_TrqLim_f32_FQ;
real32_T VAR_Tpcblk_TrqLim01_f32_FQ;
real32_T VAR_Tpcblk_TrqMax_f32_FQ;
real32_T TPC_TrqMax_FQ;
real32_T VAR_TpcSmp_TrqMinCanSet_f32_FQ;
real32_T VAR_Tpcblk_TrqMin_f32_FQ;
real32_T TPC_TrqMin_FQ;
real32_T VAR_TpcMot_tSttrTempFlt_f32_FQ;
real32_T VAR_TpcMot_CofDertTSttrSave1_f32_FQ;
real32_T VAR_TpcMot_CofDertTSttrSave2_f32_FQ;
real32_T VAR_TpcMot_CofDertTsttr_f32_FQ;
real32_T VAR_TpcMot_tRiseSttr_f32_FQ;
real32_T VAR_TpcMot_CofDertTRiseSttrSave1_f32_FQ;
real32_T VAR_TpcMot_CofDertTRiseSttrSave2_f32_FQ;
real32_T VAR_TpcMot_CofDertTRiseSttr_f32_FQ;
real32_T VAR_TpcTmp_tDbcMax_f32_FQ;
real32_T VAR_TpcTmp_tDbcTempFlt_f32_FQ;
real32_T VAR_TpcTmp_CofDertTDbcSave1_f32_FQ;
real32_T VAR_TpcTmp_CofDertTDbcSave2_f32_FQ;
real32_T VAR_TpcTmp_CofDertDbc_f32_FQ;
real32_T VAR_TpcTmp_tRiseDbc_f32_FQ;
real32_T VAR_TpcTmp_tRiseDbcFlt_f32_FQ;
real32_T VAR_TpcTmp_CofDertTRiseDbcSave1_f32_FQ;
real32_T VAR_TpcTmp_CofDertTRiseDbcSave2_f32_FQ;
real32_T VAR_TpcTmp_CofDertTRiseDbc_f32_FQ;
real32_T VAR_TpcTmp_tCoolantTempFlt_f32_FQ;
real32_T VAR_TpcTmp_CofDertTCoolantSave1_f32_FQ;
real32_T VAR_TpcTmp_CofDertTCoolantSave2_f32_FQ;
real32_T VAR_TpcTmp_CofDertTcoolant_f32_FQ;
real32_T VAR_TpcTmp_CofDertTdrvboard_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrSpdElecQuad1_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrSpdElecQuad3_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrSpdGenQuad4_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrSpdGenQuad2_f32_FQ;
real32_T VAR_TpcSmp_uDcLnkMin_f32_FQ;
real32_T VAR_TpcSmp_cofDertUdrVoltElec_f32_FQ;
real32_T VAR_TpcMot_ElecPwrRef_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ;
real32_T VAR_TpcMot_ElecTrqRef_f32_FQ;
real32_T VAR_TpcMot_ElecTrqLimTsttrWoRamp_f32_FQ;
real32_T VAR_TpcMot_ElecTrqLimTsttr_f32_FQ;
real32_T VAR_TpcMot_GenTrqRef_f32_FQ;
real32_T VAR_TpcMot_GenTrqLimTsttrWoRamp_f32_FQ;
real32_T VAR_TpcMot_GenTrqLimTsttr_f32_FQ;
real32_T VAR_TpcTmp_ElecTrqLimTdbcWoRamp_f32_FQ;
real32_T VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ;
real32_T VAR_TpcTmp_GenTrqLimTdbcWoRamp_f32_FQ;
real32_T VAR_TpcTmp_GenTrqLimTdbc_f32_FQ;
real32_T VAR_TpcTmp_ElecTrqLimTcoolant_f32_FQ;
real32_T VAR_TpcTmp_GenTrqLimTcoolant_f32_FQ;
real32_T VAR_TpcTmp_ElecTrqLimTdrvboard_f32_FQ;
real32_T VAR_TpcTmp_GenTrqLimTdrvboard_f32_FQ;
real32_T VAR_TpcTmp_tIGBTTempFlt_f32_FQ;
real32_T VAR_TpcTmp_tRiseIGBT_f32_FQ;
real32_T VAR_TpcTmp_tRiseIGBTFlt_f32_FQ;
real32_T VAR_TpcTmp_CofDertTIGBTSave1_f32_FQ;
real32_T VAR_TpcTmp_CofDertTIGBTSave2_f32_FQ;
real32_T VAR_TpcTmp_CofDertIGBT_f32_FQ;
real32_T VAR_TpcTmp_CofDertTRiseIGBTSave1_f32_FQ;
real32_T VAR_TpcTmp_CofDertTRiseIGBTSave2_f32_FQ;
real32_T VAR_TpcTmp_CofDertTRiseIGBT_f32_FQ;
real32_T VAR_TpcTmp_ElecTrqLimTIGBTWoRamp_f32_FQ;
real32_T VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ;
real32_T VAR_TpcTmp_GenTrqLimTIGBTWoRamp_f32_FQ;
real32_T VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ;
real32_T VAR_TpcSmp_ElecTrqLimOvrSpd_f32_FQ;
real32_T VAR_TpcSmp_GenTrqLimOvrSpd_f32_FQ;
real32_T VAR_TpcSmp_iDcLnkMax_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrAlowMax_f32_FQ;
real32_T VAR_tpcsmp_PwrLoss_f32_FQ;
real32_T VAR_tpcsmp_ElecPwrDert_f32_FQ;
real32_T VAR_tpcsmp_AddPwrElecOvrCurt_f32_FQ;
real32_T VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ;
real32_T VAR_tpcsmp_yiDelay_f32_FQ;
real32_T VAR_TpcSmp_ErrElecOvrCurt_f32_FQ;
real32_T VAR_tpcsmp_KiProduct_f32_FQ;
real32_T VAR_tpcsmp_KiProductSum_f32_FQ;
real32_T VAR_tpcsmp_KpProduct_f32_FQ;
real32_T VAR_tpcsmp_KpProductSau_f32_FQ;
real32_T VAR_tpcsmp_PIOutput_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrPIDertOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrCurtElec_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrLinearDertOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrLimOvrCurt_f32_FQ;
real32_T VAR_TpcCod_ElecTrqCalcOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_iDcLnkMin_f32_FQ;
real32_T VAR_tpcsmp_PwrLossGen_f32_FQ;
real32_T VAR_tpcsmp_GenPwrDert_f32_FQ;
real32_T VAR_TpcSmp_GenPwrAlowMax_f32_FQ;
real32_T VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_ErrGenOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_GenPwrPIDertOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_cofDertOvrCurtGen_f32_FQ;
real32_T VAR_TpcSmp_GenPwrLinearDertOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_GenPwrLimOvrCurt_f32_FQ;
real32_T VAR_TpcCod_GenTrqCalcOvrCurt_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrLinearDertUdrVolt_f32_FQ;
real32_T VAR_TpcSmp_ElecPwrLimUdrVolt_f32_FQ;
real32_T VAR_TpcCod_ElecTrqCalcUdrVolt_f32_FQ;
real32_T VAR_TpcSmp_GenPwrLinearDertOvrVolt_f32_FQ;
real32_T VAR_TpcSmp_GenPwrPIDertOvrVolt_f32_FQ;
real32_T VAR_TpcSmp_GenPwrLimOvrVolt_f32_FQ;
real32_T VAR_TpcCod_GenTrqCalcOvrVolt_f32_FQ;
real32_T TPC_TDbcTrqMax_FQ;
real32_T VAR_TpcCod_PowerAdd_f32_FQ;
real32_T VAR_TpcCod_PowerIncreaseRate_f32_FQ;
real32_T VAR_TpcCod_CoolantFlowFinReq_f32_FQ;
real32_T VAR_TpcCod_ElecTrqCalcDiag_f32_FQ;
real32_T VAR_TpcCod_GenTrqCalcDiag_f32_FQ;
real32_T VAR_tpcsmp_negOutputjudge_f32_FQ;
real32_T VAR_tpcsmp_posOutputjudge_f32_FQ;
real32_T VAR_tpcsmp_yi_f32_FQ;
real32_T VAR_TpcFuv_ElecTrqLimDiag_f32_FQ;
real32_T VAR_TpcFuv_GenTrqLimDiag_f32_FQ;
real32_T VAR_TpcFuv_ElecPwrLimDiag_f32_FQ;
real32_T VAR_TpcFuv_GenPwrLimDiag_f32_FQ;
real32_T VAR_TpcBlk_IsSum_f32_FQ;
real32_T VAR_TpcCod_CoolantFlowReq_f32_FQ;
int16_T VAR_TpcMot_tSttrTempFlt_u16_FQ;
int16_T VAR_TpcMot_TsttrStableDiff_u16_FQ;
int16_T VAR_TpcTmp_tDbcTempFlt_u16_FQ;
int16_T VAR_TpcTmp_TDbcStableDiff_u16_FQ;
int16_T VAR_TpcTmp_tCoolTempFlt_u16_FQ;
int16_T VAR_TpcTmp_tDbcRiseTempFlt_u16_FQ;
int16_T VAR_TpcTmp_TDbcRiseStableDiff_u16_FQ;
int16_T VAR_TpcTmp_TCoolStableDiff_u16_FQ;
int16_T VAR_TpcTmp_tIgbtTempFlt_u16_FQ;
int16_T VAR_TpcTmp_TIgbtStableDiff_u16_FQ;
int16_T VAR_TpcTmp_tIgbtRiseTempFlt_u16_FQ;
int16_T VAR_TpcTmp_TIgbtRiseStableDiff_u16_FQ;
uint8_T TPC_SgnRotDir_FQ;
uint8_T TPC_SgnTrqMechDir_FQ;
uint8_T TPC_stMotorMod_FQ;
uint8_T TPC_stTrqEmMax_FQ;
uint8_T TPC_stTrqEmMin_FQ;
uint8_T VAR_TpcSmp_iDcLnkOvcWarnState_u8_FQ;
uint8_T VAR_TpcTmp_TIGBTOvHiWarnState_u8_FQ;
uint8_T VAR_TpcTmp_TIGBTOvLoWarnState_u8_FQ;
uint8_T VAR_TpcTmp_TIGBTOvHiErrState_u8_FQ;
uint8_T VAR_TpcSmp_uDcLnkUnvWarnState_u8_FQ;
uint8_T VAR_TpcSmp_uDcLnkUnVLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDrvBoardOvHiWarnState_u8_FQ;
uint8_T VAR_TpcTmp_TCoolantOvHiWarnState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcOvHiWarnState_u8_FQ;
uint8_T VAR_TpcMot_TSttrOvHiWarnState_u8_FQ;
uint8_T VAR_TpcMot_TSttrOvHiLimErrState_u8_FQ;
uint8_T VAR_TpcMot_TSttrOvLoWarnState_u8_FQ;
uint8_T VAR_TpcSmp_uDcLnkOvWarnState_u8_FQ;
uint8_T VAR_TpcSmp_iDcLnkOvCLimErrState_u8_FQ;
uint8_T VAR_TpcSmp_uDcLnkOvVLimErrState_u8_FQ;
uint8_T VAR_TpcSmp_SpdOvHiWarnState_u8_FQ;
uint8_T VAR_TpcSmp_SpdOvHiLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcOvLoWarnState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcUHiLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcULoLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcVHiLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcVLoLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcWHiLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_TDbcWLoLimErrState_u8_FQ;
uint8_T VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ;
uint8_T VAR_TpcTmp_tIGBTOperationMode_u8_FQ;
uint8_T VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ;
uint8_T VAR_TpcTmp_tDbcOperationMode_u8_FQ;
uint8_T VAR_TpcTmp_tCoolantOperationMode_u8_FQ;
uint8_T VAR_TpcMot_tSttrOperationMode_u8_FQ;
uint8_T VAR_TpcMot_tRiseSttrOperationMode_u8_FQ;
boolean_T VAR_TpcSmp_flgLinearDertOvrVoltGen_b_FQ;
boolean_T VAR_TpcMot_flgStartExcLimRamp_b_FQ;
boolean_T VAR_TpcSmp_flgPIDertOvrVoltGen_b_FQ;
boolean_T VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ;
boolean_T TPC_bDernOvrUdc_FQ;
boolean_T VAR_TpcCod_flgMotorElecMode_b_FQ;
boolean_T TPC_bDernExcMax_FQ;
boolean_T TPC_bDernExcMin_FQ;
boolean_T VAR_TpcMot_flgTrqLimTsttrActv_b_FQ;
boolean_T TPC_bDernStrTemp_FQ;
boolean_T VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ;
boolean_T TPC_bDernDbcTemp_FQ;
boolean_T VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ;
boolean_T TPC_bDernCoolantTemp_FQ;
boolean_T VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ;
boolean_T TPC_bDernDrvBoardTemp_FQ;
boolean_T VAR_TpcSmp_flgElecTrqLimOvrSpdActv_b_FQ;
boolean_T VAR_TpcSmp_flgGenTrqLimOvrSpdActv_b_FQ;
boolean_T TPC_bDernMtrSpd_FQ;
boolean_T VAR_TpcSmp_flgLinearDertUdrVoltElec_b_FQ;
boolean_T VAR_TpcSmp_flgPIDertUdrVoltElec_b_FQ;
boolean_T VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ;
boolean_T TPC_bDernUndrUdc_FQ;
boolean_T TPC_bDernCAN_FQ;
boolean_T VAR_tpccod_flgMaxDertExCTrq_b_FQ;
boolean_T VAR_tpccod_flgMaxDertStrTemp_b_FQ;
boolean_T VAR_tpccod_flgMaxDertTempDBC_b_FQ;
boolean_T VAR_tpccod_flgMaxDertTCoolant_b_FQ;
boolean_T VAR_tpccod_flgMaxDertTDrvBoard_b_FQ;
boolean_T VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ;
boolean_T VAR_tpccod_flgMaxDertTIGBT_b_FQ;
boolean_T VAR_tpccod_flgMaxDertMtrSpd_b_FQ;
boolean_T VAR_TpcSmp_flgLinearDertOvrCurtElec_b_FQ;
boolean_T VAR_TpcSmp_flgPIDertOvrCurtElec_b_FQ;
boolean_T VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ;
boolean_T VAR_TpcSmp_flgLinearDertOveCurtGen_b_FQ;
boolean_T VAR_TpcSmp_flgPIDertOvrCurtGen_b_FQ;
boolean_T VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ;
boolean_T VAR_tpccod_flgMaxDertOvrIdc_b_FQ;
boolean_T VAR_tpccod_flgMaxDertUndrUdc_b_FQ;
boolean_T VAR_tpccod_flgMaxDertOvrUdc_b_FQ;
boolean_T VAR_tpccod_flgMaxDertCAN_b_FQ;
boolean_T VAR_tpccod_flgMinDertExCTrq_b_FQ;
boolean_T VAR_tpccod_flgMinDertStrTemp_b_FQ;
boolean_T VAR_tpccod_flgMinDertTempDBC_b_FQ;
boolean_T VAR_tpccod_flgMinDertTCoolant_b_FQ;
boolean_T VAR_tpccod_flgMinDertTDrvBoard_b_FQ;
boolean_T VAR_tpccod_flgMinDertTIGBT_b_FQ;
boolean_T VAR_tpccod_flgMinDertMtrSpd_b_FQ;
boolean_T VAR_tpccod_flgMinDertOvrIdc_b_FQ;
boolean_T VAR_tpccod_flgMinDertUndrUdc_b_FQ;
boolean_T VAR_tpccod_flgMinDertOvrUdc_b_FQ;
boolean_T VAR_tpccod_flgMinDertCAN_b_FQ;
boolean_T TPC_bDernElecOvrIdc_FQ;
boolean_T TPC_bDernGenOvrIdc_FQ;
boolean_T TPC_bDernOvrIdc_FQ;
boolean_T TPC_bDernIGBTTemp_FQ;
boolean_T VAR_TpcFuv_FimTrqLimLv1_b_FQ;
boolean_T VAR_TpcFuv_FimTrqLimLv2_b_FQ;
boolean_T VAR_TpcFuv_FimTrqLimLv3_b_FQ;
boolean_T VAR_TpcFuv_FimTrqLimLv4_b_FQ;
boolean_T VAR_TpcFuv_FimPwrLimLv1_b_FQ;
boolean_T VAR_TpcFuv_FimPwrLimLv2_b_FQ;
boolean_T VAR_TpcFuv_FimPwrLimLv3_b_FQ;
boolean_T VAR_TpcFuv_FimPwrLimLv4_b_FQ;
MdlrefDW_SWC_TPC_IG_FQ_T SWC_TPC_IG_FQ_MdlrefDW;
DW_SWC_TPC_IG_FQ_f_T SWC_TPC_IG_FQ_DW;
void SWC_TPC_IG_FQ_GetHighTemp_Init(real32_T *rty_TModuleTempHighest)
{
  *rty_TModuleTempHighest = 0.0F;
}

void SWC_TPC_IG_FQ_GetHighTemp(real32_T rtu_TModuletemp, real32_T
  rtu_TModuletempDly, real32_T *rty_TModuleTempHighest)
{
  *rty_TModuleTempHighest = fmaxf(rtu_TModuletemp, rtu_TModuletempDly);
}

void SWC_TPC_IG_FQ_Init(void)
{
  SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE = 300.0F;
  SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l = 300.0F;
  SWC_TPC_IG_FQ_DW.UnitDelay3_DSTATE = 310.0F;
  SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_o = 310.0F;
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_b);
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_m);
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_h);
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_bi);
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_d);
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_er);
  SWC_TPC_IG_FQ_GetHighTemp_Init(&SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_g);
}

void SWC_TPC_IG_FQ(const real32_T *rtu_MPC_BUS_MPC_TrqMechFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDBCTempUFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDBCTempVFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDBCTempWFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_nSlowFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDrvBoardTemp, const real32_T
                   *rtu_HSPF_BUS_HSPF_iDcLnkEstFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tIGBTTjFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tCoolantTjFlt, const real32_T
                   *rtu_MCF_BUS_MCF_Is, const real32_T *rtu_TDC_BUS_TDC_TrqDes,
                   real32_T *rty_TPC_BUS_TPC_TrqMax, real32_T
                   *rty_TPC_BUS_TPC_TrqMin, boolean_T
                   *rty_TPC_BUS_TPC_bDernExcMax, boolean_T
                   *rty_TPC_BUS_TPC_bDernExcMin, boolean_T
                   *rty_TPC_BUS_TPC_bDernStrTemp, boolean_T
                   *rty_TPC_BUS_TPC_bDernDbcTemp, boolean_T
                   *rty_TPC_BUS_TPC_bDernCoolantTem, boolean_T
                   *rty_TPC_BUS_TPC_bDernDrvBoardTe, boolean_T
                   *rty_TPC_BUS_TPC_bDernMtrSpd, boolean_T
                   *rty_TPC_BUS_TPC_bDernUndrUdc, boolean_T
                   *rty_TPC_BUS_TPC_bDernOvrUdc, boolean_T
                   *rty_TPC_BUS_TPC_bDernCAN, uint8_T
                   *rty_TPC_BUS_TPC_stTrqEmMax, uint8_T
                   *rty_TPC_BUS_TPC_stTrqEmMin, uint8_T
                   *rty_TPC_BUS_TPC_stMotorMod, real32_T
                   *rty_TPC_BUS_TPC_TDbcTrqMax, uint8_T
                   *rty_TPC_BUS_TPC_SgnRotDir, uint8_T
                   *rty_TPC_BUS_TPC_SgnTrqMechDir, boolean_T
                   *rty_TPC_BUS_TPC_bDernElecOvrIdc, boolean_T
                   *rty_TPC_BUS_TPC_bDernGenOvrIdc, boolean_T
                   *rty_TPC_BUS_TPC_bDernOvrIdc, real32_T
                   *rty_TPC_BUS_TPC_TrqMaxTrans, real32_T
                   *rty_TPC_BUS_TPC_TrqMinTrans, boolean_T
                   *rty_TPC_BUS_TPC_bDernIGBTTemp, real32_T *rty_DEM_BUS)
{
  int_T idxDelay;
  real32_T rtb_Abs1_p;
  real32_T rtb_Abs_ns;
  real32_T rtb_Add3_a;
  real32_T rtb_Add7_l;
  real32_T rtb_DataTypeConversion1;
  real32_T rtb_Product1;
  real32_T rtb_Subtract_fv;
  real32_T rtb_Switch2_b;
  real32_T rtb_Switch_dc;
  real32_T rtb_Switch_iy;
  real32_T rtb_Switch_lt_tmp;
  real32_T rtb_tpccod_TrqMax;
  real32_T rtb_tpccod_TrqMin;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T rtb_RelationalOperator3_fry;
  boolean_T rtb_RelationalOperator3_pj;
  boolean_T rtb_RelationalOperator_mt;
  if (1000.0F > CAL_TpcSmp_uDcLnkMaxMax_f32_FQ) {
    VAR_TpcSmp_uDcLnkMax_f32_FQ = CAL_TpcSmp_uDcLnkMaxMax_f32_FQ;
  } else if (1000.0F < CAL_TpcSmp_uDcLnkMaxMin_f32_FQ) {
    VAR_TpcSmp_uDcLnkMax_f32_FQ = CAL_TpcSmp_uDcLnkMaxMin_f32_FQ;
  } else {
    VAR_TpcSmp_uDcLnkMax_f32_FQ = 1000.0F;
  }

  rtb_Product1 = VAR_TpcSmp_uDcLnkMax_f32_FQ - *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt;
  VAR_TpcSmp_cofDertOvrVoltGen_f32_FQ = look1_iflf_binlcapw(rtb_Product1, ((
    const real32_T *)&(CAL_TpcSmp_OvrVoltGenTableX_uDc_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrVoltGenTableY_Cof_af32_FQ[0])), 4U);
  VAR_TpcSmp_flgLinearDertOvrVoltGen_b_FQ = (1.0F -
    VAR_TpcSmp_cofDertOvrVoltGen_f32_FQ > 1.0E-6F);
  rtb_Switch_lt_tmp = fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt);
  rtb_Abs_ns = roundf(*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt / (real32_T)
                      CAL_Tpcmot_CofuDclnk_u8_FQ);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_DataTypeConversion1 = 0.0F;
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_DataTypeConversion1 = fmodf(rtb_Abs_ns, 65536.0F);
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  rtb_DataTypeConversion1 = (real32_T)((uint32_T)(rtb_DataTypeConversion1 < 0.0F
    ? (int32_T)(uint16_T)-(int16_T)(uint16_T)-rtb_DataTypeConversion1 : (int32_T)
    (uint16_T)rtb_DataTypeConversion1) * CAL_Tpcmot_CofuDclnk_u8_FQ + ((uint32_T)
    CAL_Tpcmot_CofuDclnk_u8_FQ >> 1));
  VAR_TpcMot_TrqGenExCOrg_f32_FQ = -look2_iflf_binlcapw(rtb_Switch_lt_tmp,
    rtb_DataTypeConversion1, ((const real32_T *)
    &(CAL_TpcMot_ExCGenTableY_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcMot_ExCGenTableX_Udc_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcMot_ExCGenTableZ_Trq_af32_FQ[0])), rtCP_GenExCTable_maxIndex, 17U);
  VAR_TpcMot_TrqElecExCOrg_f32_FQ = look2_iflf_binlcapw(rtb_Switch_lt_tmp,
    (real32_T)((uint32_T)(rtb_Abs_ns < 0.0F ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-rtb_Abs_ns : (int32_T)(uint16_T)rtb_Abs_ns) *
               CAL_Tpcmot_CofuDclnk_u8_FQ + ((uint32_T)
    CAL_Tpcmot_CofuDclnk_u8_FQ >> 1)), ((const real32_T *)
    &(CAL_TpcMot_ExCElecTableY_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcMot_ExCElecTableX_Udc_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcMot_ExCElecTableZ_Trq_af32_FQ[0])), rtCP_ElecExCTable_maxIndex, 14U);
  if (CAL_Tpcmot_flgOpenExcLimRamp_b_FQ) {
    VAR_TpcMot_flgStartExcLimRamp_b_FQ = (((rtb_DataTypeConversion1 <=
      CAL_Tpcmot_uDcLoset_f32_FQ) || (rtb_DataTypeConversion1 >=
      CAL_Tpcmot_uDcHiset_f32_FQ)) && ((VAR_TpcMot_TrqElecExCOrg_f32_FQ -
      *rtu_TDC_BUS_TDC_TrqDes <= CAL_Tpcmot_TrqDiffExc_f32_FQ) ||
      (*rtu_TDC_BUS_TDC_TrqDes - VAR_TpcMot_TrqGenExCOrg_f32_FQ <=
       CAL_Tpcmot_TrqDiffGen_f32_FQ)));
  } else {
    VAR_TpcMot_flgStartExcLimRamp_b_FQ = false;
  }

  if (!SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_b) {
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE = VAR_TpcMot_TrqGenExCOrg_f32_FQ;
  } else {
    rtb_DataTypeConversion1 = VAR_TpcMot_TrqGenExCOrg_f32_FQ -
      SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE;
    if (rtb_DataTypeConversion1 <= CAL_Tpc_TrqRiseRevStep_f32_FQ) {
      if (-rtb_DataTypeConversion1 <= CAL_Tpc_TrqReduceRevStep_f32_FQ) {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE = VAR_TpcMot_TrqGenExCOrg_f32_FQ;
      } else {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE -= CAL_Tpc_TrqReduceRevStep_f32_FQ;
      }
    } else {
      SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE += CAL_Tpc_TrqRiseRevStep_f32_FQ;
    }
  }

  if (VAR_TpcMot_flgStartExcLimRamp_b_FQ) {
    VAR_TpcMot_TrqGenExC_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE;
  } else {
    VAR_TpcMot_TrqGenExC_f32_FQ = VAR_TpcMot_TrqGenExCOrg_f32_FQ;
  }

  if (CAL_TpcMot_flgPwrRefSwt_b_FQ) {
    VAR_TpcMot_GenPwrRef_f32_FQ = rtb_Switch_lt_tmp *
      VAR_TpcMot_TrqGenExC_f32_FQ / 9550.0F;
  } else {
    VAR_TpcMot_GenPwrRef_f32_FQ = -GLB_Tpc_MaximumPower_f32_FQ;
  }

  SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e += rtb_Product1 *
    CAL_TpcSmp_GenOvrVoltKi_f32_FQ;
  rtb_Product1 *= CAL_TpcSmp_GenOvrVoltKp_f32_FQ;
  if (rtb_Product1 > CAL_TpcSmp_GenOvrVoltypLim_f32_FQ) {
    rtb_Product1 = CAL_TpcSmp_GenOvrVoltypLim_f32_FQ;
  } else {
    if (rtb_Product1 < -CAL_TpcSmp_GenOvrVoltypLim_f32_FQ) {
      rtb_Product1 = -CAL_TpcSmp_GenOvrVoltypLim_f32_FQ;
    }
  }

  rtb_DataTypeConversion1 = SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e + rtb_Product1;
  if (rtb_DataTypeConversion1 > -VAR_TpcMot_GenPwrRef_f32_FQ) {
    rtb_Switch2_b = -VAR_TpcMot_GenPwrRef_f32_FQ;
  } else if (rtb_DataTypeConversion1 < 0.0F) {
    rtb_Switch2_b = 0.0F;
  } else {
    rtb_Switch2_b = rtb_DataTypeConversion1;
  }

  VAR_TpcSmp_flgPIDertOvrVoltGen_b_FQ = (rtb_Switch2_b !=
    -VAR_TpcMot_GenPwrRef_f32_FQ);
  if (VAR_TpcSmp_flgLinearDertOvrVoltGen_b_FQ ||
      VAR_TpcSmp_flgPIDertOvrVoltGen_b_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_gq = (uint16_T)((uint32_T)
      !VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ +
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_gq);
    if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_gq >= 65535) {
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_gq = MAX_uint16_T;
    }
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_gq = 0U;
  }

  VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ = ((uint32_T)
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_gq * CAL_TpcSmp_FacGenOvrVolt_u8_FQ >
    CAL_TpcSmp_CntGenOvrVolt_u8_FQ);
  if ((*rtu_HSPF_BUS_HSPF_nSlowFlt >= CAL_TpcCod_NegSpdDirStop_f32_FQ) &&
      (*rtu_HSPF_BUS_HSPF_nSlowFlt <= CAL_TpcCod_PosSpdDirStop_f32_FQ)) {
    TPC_SgnRotDir_FQ = ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ);
  } else if (*rtu_HSPF_BUS_HSPF_nSlowFlt > CAL_TpcCod_PosSpdDirStop_f32_FQ) {
    TPC_SgnRotDir_FQ = ((uint8_T)GLB_TpcCod_MotorFw_u8_FQ);
  } else {
    TPC_SgnRotDir_FQ = ((uint8_T)GLB_TpcCod_MotorBw_u8_FQ);
  }

  rtb_RelationalOperator_mt = (TPC_SgnRotDir_FQ != ((uint8_T)
    GLB_TpcCod_MotorStop_u8_FQ));
  TPC_bDernOvrUdc_FQ = (rtb_RelationalOperator_mt &&
                        VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ);
  if ((*rtu_MPC_BUS_MPC_TrqMechFlt >= CAL_TpcCod_NegTrqDirStop_f32_FQ) &&
      (*rtu_MPC_BUS_MPC_TrqMechFlt <= CAL_TpcCod_PosTrqDirStop_f32_FQ)) {
    TPC_SgnTrqMechDir_FQ = ((uint8_T)GLB_TpcCod_ZeroTrq_u8_FQ);
  } else if (*rtu_MPC_BUS_MPC_TrqMechFlt > CAL_TpcCod_PosTrqDirStop_f32_FQ) {
    TPC_SgnTrqMechDir_FQ = ((uint8_T)GLB_TpcCod_PosvTrq_u8_FQ);
  } else {
    TPC_SgnTrqMechDir_FQ = ((uint8_T)GLB_TpcCod_NegvTrq_u8_FQ);
  }

  if ((TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorBw_u8_FQ)) &&
      (TPC_SgnTrqMechDir_FQ != ((uint8_T)GLB_TpcCod_NegvTrq_u8_FQ))) {
    TPC_stMotorMod_FQ = ((uint8_T)GLB_TpcCod_FwELect_u8_FQ);
  } else if ((TPC_SgnRotDir_FQ == ((uint8_T)GLB_TpcCod_MotorBw_u8_FQ)) &&
             (TPC_SgnTrqMechDir_FQ == ((uint8_T)GLB_TpcCod_PosvTrq_u8_FQ))) {
    TPC_stMotorMod_FQ = ((uint8_T)GLB_TpcCod_BwGene_u8_FQ);
  } else if ((TPC_SgnRotDir_FQ == ((uint8_T)GLB_TpcCod_MotorFw_u8_FQ)) &&
             (TPC_SgnTrqMechDir_FQ == ((uint8_T)GLB_TpcCod_NegvTrq_u8_FQ))) {
    TPC_stMotorMod_FQ = ((uint8_T)GLB_TpcCod_FwGene_u8_FQ);
  } else {
    TPC_stMotorMod_FQ = ((uint8_T)GLB_TpcCod_BwELect_u8_FQ);
  }

  VAR_TpcCod_flgMotorElecMode_b_FQ = ((TPC_stMotorMod_FQ == ((uint8_T)
    GLB_TpcCod_FwELect_u8_FQ)) || (TPC_stMotorMod_FQ == ((uint8_T)
    GLB_TpcCod_FwGene_u8_FQ)));
  if (!SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_ae) {
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l = VAR_TpcMot_TrqElecExCOrg_f32_FQ;
  } else {
    rtb_Subtract_fv = VAR_TpcMot_TrqElecExCOrg_f32_FQ -
      SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l;
    if (rtb_Subtract_fv <= CAL_Tpc_TrqRiseRevStep_f32_FQ) {
      if (-rtb_Subtract_fv <= CAL_Tpc_TrqReduceRevStep_f32_FQ) {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l = VAR_TpcMot_TrqElecExCOrg_f32_FQ;
      } else {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l -= CAL_Tpc_TrqReduceRevStep_f32_FQ;
      }
    } else {
      SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l += CAL_Tpc_TrqRiseRevStep_f32_FQ;
    }
  }

  if (VAR_TpcMot_flgStartExcLimRamp_b_FQ) {
    VAR_TpcMot_TrqElecExC_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_l;
  } else {
    VAR_TpcMot_TrqElecExC_f32_FQ = VAR_TpcMot_TrqElecExCOrg_f32_FQ;
  }

  if (VAR_TpcCod_flgMotorElecMode_b_FQ) {
    TPC_TrqMaxTrans_FQ = VAR_TpcMot_TrqElecExC_f32_FQ;
    if (fabsf(VAR_TpcMot_TrqElecExC_f32_FQ) - fabsf(VAR_TpcMot_TrqGenExC_f32_FQ)
        > -1.0E-6F) {
      if (*rtu_HSPF_BUS_HSPF_nSlowFlt < CAL_TpcCod_PosSpdHold_f32_FQ) {
        TPC_TrqMinTrans_FQ = -VAR_TpcMot_TrqElecExC_f32_FQ;
      } else if (*rtu_HSPF_BUS_HSPF_nSlowFlt > CAL_TpcCod_PosSpdStart_f32_FQ) {
        TPC_TrqMinTrans_FQ = VAR_TpcMot_TrqGenExC_f32_FQ;
      } else {
        TPC_TrqMinTrans_FQ = (VAR_TpcMot_TrqGenExC_f32_FQ +
                              VAR_TpcMot_TrqElecExC_f32_FQ) /
          (CAL_TpcCod_PosSpdStart_f32_FQ - CAL_TpcCod_PosSpdHold_f32_FQ) *
          (*rtu_HSPF_BUS_HSPF_nSlowFlt - CAL_TpcCod_PosSpdHold_f32_FQ) +
          -VAR_TpcMot_TrqElecExC_f32_FQ;
      }
    } else {
      TPC_TrqMinTrans_FQ = VAR_TpcMot_TrqGenExC_f32_FQ;
    }
  } else {
    if (fabsf(VAR_TpcMot_TrqElecExC_f32_FQ) - fabsf(VAR_TpcMot_TrqGenExC_f32_FQ)
        > -1.0E-6F) {
      if (*rtu_HSPF_BUS_HSPF_nSlowFlt > -CAL_TpcCod_PosSpdHold_f32_FQ) {
        TPC_TrqMaxTrans_FQ = VAR_TpcMot_TrqElecExC_f32_FQ;
      } else if (*rtu_HSPF_BUS_HSPF_nSlowFlt < -CAL_TpcCod_PosSpdStart_f32_FQ) {
        TPC_TrqMaxTrans_FQ = -VAR_TpcMot_TrqGenExC_f32_FQ;
      } else {
        TPC_TrqMaxTrans_FQ = (VAR_TpcMot_TrqElecExC_f32_FQ +
                              VAR_TpcMot_TrqGenExC_f32_FQ) /
          (CAL_TpcCod_PosSpdStart_f32_FQ - CAL_TpcCod_PosSpdHold_f32_FQ) *
          (*rtu_HSPF_BUS_HSPF_nSlowFlt + CAL_TpcCod_PosSpdStart_f32_FQ) +
          -VAR_TpcMot_TrqGenExC_f32_FQ;
      }
    } else {
      TPC_TrqMaxTrans_FQ = -VAR_TpcMot_TrqGenExC_f32_FQ;
    }

    TPC_TrqMinTrans_FQ = -VAR_TpcMot_TrqElecExC_f32_FQ;
  }

  VAR_TpcSmp_TrqMaxCanSet_f32_FQ = 1000.0F;
  if (TPC_TrqMaxTrans_FQ <= VAR_TpcSmp_TrqMaxCanSet_f32_FQ) {
    rtb_Switch_dc = TPC_TrqMaxTrans_FQ;
  } else {
    rtb_Switch_dc = VAR_TpcSmp_TrqMaxCanSet_f32_FQ;
  }

  if (rtb_Switch_lt_tmp <= CAL_TpcBlk_MtrBlkSpdLowSet_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_j = true;
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_j = ((!(rtb_Switch_lt_tmp >=
      CAL_TpcBlk_MtrBlkSpdHighSet_f32_FQ)) &&
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_j);
  }

  VAR_TpcBlk_IsValid_f32_FQ = *rtu_MCF_BUS_MCF_Is / 1.414F;
  rtb_Subtract_fv = CAL_TpcBlk_MtrBlkIsFirstSet_f32_FQ * (real32_T)
    CAL_TpcBlk_BlkTimSet_u16_FQ;
  if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_j) {
    if (VAR_TpcBlk_IsValid_f32_FQ > CAL_TpcBlk_MtrBlkIsFirstSet_f32_FQ) {
      SWC_TPC_IG_FQ_DW.Is_Sum += VAR_TpcBlk_IsValid_f32_FQ;
    } else {
      if (VAR_TpcBlk_IsValid_f32_FQ < CAL_TpcBlk_MtrBlkIsSecondSet_f32_FQ) {
        SWC_TPC_IG_FQ_DW.Is_Sum -= VAR_TpcBlk_IsValid_f32_FQ;
      }
    }
  } else {
    SWC_TPC_IG_FQ_DW.Is_Sum -= VAR_TpcBlk_IsValid_f32_FQ;
  }

  if (SWC_TPC_IG_FQ_DW.Is_Sum < 0.0F) {
    SWC_TPC_IG_FQ_DW.Is_Sum = 0.0F;
  }

  if (SWC_TPC_IG_FQ_DW.Is_Sum > rtb_Subtract_fv) {
    SWC_TPC_IG_FQ_DW.Is_Sum = (real32_T)(rtb_Subtract_fv + 1.0);
  }

  VAR_TpcBlk_IsSum_f32_FQ = SWC_TPC_IG_FQ_DW.Is_Sum;
  if (VAR_TpcBlk_IsSum_f32_FQ >= rtb_Subtract_fv) {
    VAR_Tpcblk_TrqLim_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_o -
      CAL_TpcBlk_TrqDecRamp_f32_FQ;
    if (!(VAR_Tpcblk_TrqLim_f32_FQ > CAL_TpcBlk_TrqBlkStab_f32_FQ)) {
      VAR_Tpcblk_TrqLim_f32_FQ = CAL_TpcBlk_TrqBlkStab_f32_FQ;
    }
  } else {
    VAR_Tpcblk_TrqLim_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay3_DSTATE;
  }

  if (VAR_TpcBlk_IsSum_f32_FQ <= CAL_TpcBlk_MtrBlkIsSecondSet_f32_FQ * (real32_T)
      CAL_TpcBlk_BlkRevTimSet_u16_FQ) {
    VAR_Tpcblk_TrqLim01_f32_FQ = CAL_TpcBlk_TrqIncRamp_f32_FQ +
      SWC_TPC_IG_FQ_DW.UnitDelay3_DSTATE;
    if (!(VAR_Tpcblk_TrqLim01_f32_FQ < GLB_Tpc_MaximumTorque_f32_FQ)) {
      VAR_Tpcblk_TrqLim01_f32_FQ = GLB_Tpc_MaximumTorque_f32_FQ;
    }
  } else {
    VAR_Tpcblk_TrqLim01_f32_FQ = VAR_Tpcblk_TrqLim_f32_FQ;
  }

  if (CAL_TpcBlk_flgEnBlkFun_b_FQ) {
    VAR_Tpcblk_TrqMax_f32_FQ = VAR_Tpcblk_TrqLim01_f32_FQ;
  } else {
    VAR_Tpcblk_TrqMax_f32_FQ = GLB_Tpc_MaximumTorque_f32_FQ;
  }

  if (!(rtb_Switch_dc <= VAR_Tpcblk_TrqMax_f32_FQ)) {
    rtb_Switch_dc = VAR_Tpcblk_TrqMax_f32_FQ;
  }

  if (!SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_p) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE = rtb_Switch_dc;
  } else {
    if (rtb_Switch_dc >= 0.0F) {
      if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE >= 0.0F) {
        rtb_Subtract_fv = rtb_Switch_dc - SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE;
        if (!(rtb_Subtract_fv <= CAL_Tpc_TrqRevStep_f32_FQ)) {
          rtb_Subtract_fv = CAL_Tpc_TrqRevStep_f32_FQ;
        }
      } else {
        rtb_Subtract_fv = -SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE;
      }
    } else if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE > 0.0F) {
      rtb_Subtract_fv = -SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE;
    } else {
      rtb_Subtract_fv = rtb_Switch_dc - SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE;
      if (!(rtb_Subtract_fv > -CAL_Tpc_TrqRevStep_f32_FQ)) {
        rtb_Subtract_fv = -CAL_Tpc_TrqRevStep_f32_FQ;
      }
    }

    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE += rtb_Subtract_fv;
  }

  if (CAL_TpcCod_FlgUseTrqLimRampSet_b_FQ) {
    rtb_tpccod_TrqMax = SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE;
  } else {
    rtb_tpccod_TrqMax = rtb_Switch_dc;
  }

  if (CAL_trqMaxOvrdflg_b_FQ) {
    TPC_TrqMax_FQ = CAL_trqMaxOvrdVal_f32_FQ;
  } else {
    TPC_TrqMax_FQ = rtb_tpccod_TrqMax;
  }

  VAR_TpcSmp_TrqMinCanSet_f32_FQ = -1000.0F;
  if (TPC_TrqMinTrans_FQ >= VAR_TpcSmp_TrqMinCanSet_f32_FQ) {
    rtb_Switch_iy = TPC_TrqMinTrans_FQ;
  } else {
    rtb_Switch_iy = VAR_TpcSmp_TrqMinCanSet_f32_FQ;
  }

  VAR_Tpcblk_TrqMin_f32_FQ = -VAR_Tpcblk_TrqMax_f32_FQ;
  if (!(rtb_Switch_iy >= VAR_Tpcblk_TrqMin_f32_FQ)) {
    rtb_Switch_iy = VAR_Tpcblk_TrqMin_f32_FQ;
  }

  if (!SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_bz) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a = rtb_Switch_iy;
  } else {
    if (rtb_Switch_iy >= 0.0F) {
      if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a >= 0.0F) {
        rtb_Subtract_fv = rtb_Switch_iy - SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a;
        if (!(rtb_Subtract_fv <= CAL_Tpc_TrqRevStep_f32_FQ)) {
          rtb_Subtract_fv = CAL_Tpc_TrqRevStep_f32_FQ;
        }
      } else {
        rtb_Subtract_fv = -SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a;
      }
    } else if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a > 0.0F) {
      rtb_Subtract_fv = -SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a;
    } else {
      rtb_Subtract_fv = rtb_Switch_iy - SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a;
      if (!(rtb_Subtract_fv > -CAL_Tpc_TrqRevStep_f32_FQ)) {
        rtb_Subtract_fv = -CAL_Tpc_TrqRevStep_f32_FQ;
      }
    }

    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a += rtb_Subtract_fv;
  }

  if (CAL_TpcCod_FlgUseTrqLimRampSet_b_FQ) {
    rtb_tpccod_TrqMin = SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_a;
  } else {
    rtb_tpccod_TrqMin = rtb_Switch_iy;
  }

  if (CAL_trqMinOvrdflg_b_FQ) {
    TPC_TrqMin_FQ = CAL_trqMinOvrdVal_f32_FQ;
  } else {
    TPC_TrqMin_FQ = rtb_tpccod_TrqMin;
  }

  if ((TPC_stMotorMod_FQ == ((uint8_T)GLB_TpcCod_FwELect_u8_FQ)) ||
      (TPC_stMotorMod_FQ == ((uint8_T)GLB_TpcCod_FwGene_u8_FQ))) {
    TPC_bDernExcMax_FQ = (*rtu_TDC_BUS_TDC_TrqDes >=
                          VAR_TpcMot_TrqElecExC_f32_FQ);
    TPC_bDernExcMin_FQ = (*rtu_TDC_BUS_TDC_TrqDes <= VAR_TpcMot_TrqGenExC_f32_FQ);
  } else {
    TPC_bDernExcMax_FQ = (*rtu_TDC_BUS_TDC_TrqDes >= fabsf
                          (VAR_TpcMot_TrqGenExC_f32_FQ));
    TPC_bDernExcMin_FQ = (*rtu_TDC_BUS_TDC_TrqDes <=
                          -VAR_TpcMot_TrqElecExC_f32_FQ);
  }

  rtb_Abs_ns = roundf(*rtu_HSPF_BUS_HSPF_tStrrTempFlt);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  VAR_TpcMot_tSttrTempFlt_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
    rtb_Abs_ns);
  rtb_Subtract_fv = (real32_T)VAR_TpcMot_tSttrTempFlt_u16_FQ -
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE;
  if (rtb_Subtract_fv >= CAL_TpcMot_SttrTempRiseDiff_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE += CAL_TpcMot_SttrTempAdds_f32_FQ;
  } else {
    if (rtb_Subtract_fv <= CAL_TpcMot_SttrTempDecDiff_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE += CAL_TpcMot_SttrTempMinus_f32_FQ;
    }
  }

  rtb_Switch_iy = rtb_Subtract_fv - (real32_T)VAR_TpcMot_TsttrStableDiff_u16_FQ;
  if ((rtb_Switch_iy >= CAL_TpcMot_SttrChgTempUpDiff_f32_FQ) || (rtb_Switch_iy <=
       CAL_TpcMot_SttrChgTempDownDiff_f32_FQ)) {
    rtb_Abs_ns = floorf(rtb_Subtract_fv);
    if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
      rtb_Abs_ns = 0.0F;
    } else {
      rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
    }

    VAR_TpcMot_TsttrStableDiff_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
      (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
      rtb_Abs_ns);
  }

  rtb_Abs_ns = CAL_TpcMot_SttrTempKp_f32_FQ * (real32_T)
    VAR_TpcMot_TsttrStableDiff_u16_FQ;
  if (rtb_Abs_ns > 0.9F) {
    rtb_Abs_ns = 0.9F;
  } else {
    if (rtb_Abs_ns < -0.9F) {
      rtb_Abs_ns = -0.9F;
    }
  }

  VAR_TpcMot_tSttrTempFlt_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE +
    rtb_Abs_ns;
  VAR_TpcMot_CofDertTSttrSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcMot_tSttrTempFlt_f32_FQ, ((const real32_T *)
      &(CAL_TpcMot_tSttrDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcMot_tSttrDertSave1TableY_Cof_af32_FQ[0])), 8U);
  if (SWC_TPC_IG_FQ_DW.is_active_c36_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c36_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c36_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcMot_tSttrOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c36_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcMot_tSttrTempFlt_f32_FQ >
          CAL_TpcMot_tSttrTraNormalToSave1_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c36_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcMot_tSttrOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcMot_tSttrTempFlt_f32_FQ <
          CAL_TpcMot_tSttrTraSave1ToNormal_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c36_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcMot_tSttrOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcMot_tSttrTempFlt_f32_FQ >
            CAL_TpcMot_tSttrTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c36_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcMot_tSttrOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcMot_tSttrTempFlt_f32_FQ >
          CAL_TpcMot_tSttrTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c36_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcMot_tSttrOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcMot_tSttrTempFlt_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_b, &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_b);
  VAR_TpcMot_CofDertTSttrSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_b, ((const real32_T *)
      &(CAL_TpcMot_tSttrDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcMot_tSttrDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcMot_tSttrOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcMot_tSttrOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ)) {
    VAR_TpcMot_CofDertTsttr_f32_FQ = VAR_TpcMot_CofDertTSttrSave1_f32_FQ;
  } else {
    if ((VAR_TpcMot_tSttrOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ) ||
        (VAR_TpcMot_tSttrOperationMode_u8_FQ == CAL_Tpc_OverheatingMode_u8_FQ))
    {
      VAR_TpcMot_CofDertTsttr_f32_FQ = VAR_TpcMot_CofDertTSttrSave2_f32_FQ;
    }
  }

  VAR_TpcMot_tRiseSttr_f32_FQ = VAR_TpcMot_tSttrTempFlt_f32_FQ -
    *rtu_HSPF_BUS_HSPF_tCoolantTjFlt;
  VAR_TpcMot_CofDertTRiseSttrSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcMot_tRiseSttr_f32_FQ, ((const real32_T *)
      &(CAL_TpcMot_tRiseSttrDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T
       *)&(CAL_TpcMot_tRiseSttrDertSave1TableY_Cof_af32_FQ[0])), 8U);
  if (SWC_TPC_IG_FQ_DW.is_active_c34_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c34_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c34_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcMot_tRiseSttrOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c34_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcMot_tRiseSttr_f32_FQ >
          CAL_TpcMot_tRiseSttrTraNormalToSave1_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c34_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcMot_tRiseSttrOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcMot_tRiseSttr_f32_FQ <
          CAL_TpcMot_tRiseSttrTraSave1ToNormal_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c34_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcMot_tRiseSttrOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcMot_tRiseSttr_f32_FQ >
            CAL_TpcMot_tRiseSttrTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c34_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcMot_tRiseSttrOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcMot_tRiseSttr_f32_FQ >
          CAL_TpcMot_tRiseSttrTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c34_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcMot_tRiseSttrOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcMot_tRiseSttr_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_m, &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_m);
  VAR_TpcMot_CofDertTRiseSttrSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_m, ((const real32_T *)
      &(CAL_TpcMot_tRiseSttrDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T
       *)&(CAL_TpcMot_tRiseSttrDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcMot_tRiseSttrOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcMot_tRiseSttrOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ))
  {
    VAR_TpcMot_CofDertTRiseSttr_f32_FQ = VAR_TpcMot_CofDertTRiseSttrSave1_f32_FQ;
  } else {
    if ((VAR_TpcMot_tRiseSttrOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ)
        || (VAR_TpcMot_tRiseSttrOperationMode_u8_FQ ==
            CAL_Tpc_OverheatingMode_u8_FQ)) {
      VAR_TpcMot_CofDertTRiseSttr_f32_FQ =
        VAR_TpcMot_CofDertTRiseSttrSave2_f32_FQ;
    }
  }

  if (VAR_TpcMot_CofDertTsttr_f32_FQ <= VAR_TpcMot_CofDertTRiseSttr_f32_FQ) {
    rtb_Switch_iy = VAR_TpcMot_CofDertTsttr_f32_FQ;
  } else {
    rtb_Switch_iy = VAR_TpcMot_CofDertTRiseSttr_f32_FQ;
  }

  VAR_TpcMot_flgTrqLimTsttrActv_b_FQ = (1.0F - rtb_Switch_iy > 1.0E-6F);
  TPC_bDernStrTemp_FQ = VAR_TpcMot_flgTrqLimTsttrActv_b_FQ;
  if (*rtu_HSPF_BUS_HSPF_tDBCTempUFlt >= *rtu_HSPF_BUS_HSPF_tDBCTempVFlt) {
    rtb_Switch_dc = *rtu_HSPF_BUS_HSPF_tDBCTempUFlt;
  } else {
    rtb_Switch_dc = *rtu_HSPF_BUS_HSPF_tDBCTempVFlt;
  }

  if (rtb_Switch_dc >= *rtu_HSPF_BUS_HSPF_tDBCTempWFlt) {
    VAR_TpcTmp_tDbcMax_f32_FQ = rtb_Switch_dc;
  } else {
    VAR_TpcTmp_tDbcMax_f32_FQ = *rtu_HSPF_BUS_HSPF_tDBCTempWFlt;
  }

  rtb_Abs_ns = roundf(VAR_TpcTmp_tDbcMax_f32_FQ);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  VAR_TpcTmp_tDbcTempFlt_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
    rtb_Abs_ns);
  rtb_Subtract_fv = (real32_T)VAR_TpcTmp_tDbcTempFlt_u16_FQ -
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_f;
  if (rtb_Subtract_fv >= CAL_TpcTmp_DBCTempRiseDiff_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_f += CAL_TpcTmp_DBCTempAdds_f32_FQ;
  } else {
    if (rtb_Subtract_fv <= CAL_TpcTmp_DBCTempDecDiff_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_f += CAL_TpcTmp_DBCTempMinus_f32_FQ;
    }
  }

  rtb_Switch_dc = rtb_Subtract_fv - (real32_T)VAR_TpcTmp_TDbcStableDiff_u16_FQ;
  if ((rtb_Switch_dc >= CAL_TpcTmp_DbcChgTempUpDiff_f32_FQ) || (rtb_Switch_dc <=
       CAL_TpcTmp_DbcChgTempDownDiff_f32_FQ)) {
    rtb_Abs_ns = floorf(rtb_Subtract_fv);
    if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
      rtb_Abs_ns = 0.0F;
    } else {
      rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
    }

    VAR_TpcTmp_TDbcStableDiff_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
      (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
      rtb_Abs_ns);
  }

  rtb_Abs_ns = CAL_TpcTmp_DBCTempKp_f32_FQ * (real32_T)
    VAR_TpcTmp_TDbcStableDiff_u16_FQ;
  if (rtb_Abs_ns > 0.9F) {
    rtb_Abs_ns = 0.9F;
  } else {
    if (rtb_Abs_ns < -0.9F) {
      rtb_Abs_ns = -0.9F;
    }
  }

  VAR_TpcTmp_tDbcTempFlt_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_f +
    rtb_Abs_ns;
  VAR_TpcTmp_CofDertTDbcSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcTmp_tDbcTempFlt_f32_FQ, ((const real32_T *)
      &(CAL_TpcTmp_tDbcDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tDbcDertSave1TableY_Cof_af32_FQ[0])), 8U);
  if (SWC_TPC_IG_FQ_DW.is_active_c40_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c40_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c40_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcTmp_tDbcOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c40_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcTmp_tDbcTempFlt_f32_FQ > CAL_TpcTmp_tDbcTraNormalToSave1_f32_FQ)
      {
        SWC_TPC_IG_FQ_DW.is_c40_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcTmp_tDbcOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcTmp_tDbcTempFlt_f32_FQ < CAL_TpcTmp_tDbcTraSave1ToNormal_f32_FQ)
      {
        SWC_TPC_IG_FQ_DW.is_c40_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcTmp_tDbcOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcTmp_tDbcTempFlt_f32_FQ >
            CAL_TpcTmp_tDbcTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c40_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcTmp_tDbcOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcTmp_tDbcTempFlt_f32_FQ >
          CAL_TpcTmp_tDbcTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c40_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcTmp_tDbcOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcTmp_tDbcTempFlt_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_h, &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_h);
  VAR_TpcTmp_CofDertTDbcSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_h, ((const real32_T *)
      &(CAL_TpcTmp_tDbcDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tDbcDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcTmp_tDbcOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcTmp_tDbcOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ)) {
    VAR_TpcTmp_CofDertDbc_f32_FQ = VAR_TpcTmp_CofDertTDbcSave1_f32_FQ;
  } else {
    if ((VAR_TpcTmp_tDbcOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ) ||
        (VAR_TpcTmp_tDbcOperationMode_u8_FQ == CAL_Tpc_OverheatingMode_u8_FQ)) {
      VAR_TpcTmp_CofDertDbc_f32_FQ = VAR_TpcTmp_CofDertTDbcSave2_f32_FQ;
    }
  }

  rtb_Abs_ns = roundf(*rtu_HSPF_BUS_HSPF_tCoolantTjFlt);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  VAR_TpcTmp_tCoolTempFlt_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
    rtb_Abs_ns);
  VAR_TpcTmp_tRiseDbc_f32_FQ = VAR_TpcTmp_tDbcTempFlt_f32_FQ - (real32_T)
    VAR_TpcTmp_tCoolTempFlt_u16_FQ;
  rtb_Abs_ns = roundf(VAR_TpcTmp_tRiseDbc_f32_FQ);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  VAR_TpcTmp_tDbcRiseTempFlt_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
    rtb_Abs_ns);
  rtb_Subtract_fv = (real32_T)VAR_TpcTmp_tDbcRiseTempFlt_u16_FQ -
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_h;
  if (rtb_Subtract_fv >= CAL_TpcTmp_DBCRiseTempRiseDiff_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_h += CAL_TpcTmp_DBCRiseTempAdds_f32_FQ;
  } else {
    if (rtb_Subtract_fv <= CAL_TpcTmp_DBCRiseTempDecDiff_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_h += CAL_TpcTmp_DBCRiseTempMinus_f32_FQ;
    }
  }

  rtb_Switch_dc = rtb_Subtract_fv - (real32_T)
    VAR_TpcTmp_TDbcRiseStableDiff_u16_FQ;
  if ((rtb_Switch_dc >= CAL_TpcTmp_DbcRiseChgTempUpDiff_f32_FQ) ||
      (rtb_Switch_dc <= CAL_TpcTmp_DbcRiseChgTempDownDiff_f32_FQ)) {
    rtb_Abs_ns = floorf(rtb_Subtract_fv);
    if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
      rtb_Abs_ns = 0.0F;
    } else {
      rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
    }

    VAR_TpcTmp_TDbcRiseStableDiff_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ?
      (int32_T)(int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)
      (uint16_T)rtb_Abs_ns);
  }

  rtb_Abs_ns = CAL_TpcTmp_DBCRiseTempKp_f32_FQ * (real32_T)
    VAR_TpcTmp_TDbcRiseStableDiff_u16_FQ;
  if (rtb_Abs_ns > 0.9F) {
    rtb_Abs_ns = 0.9F;
  } else {
    if (rtb_Abs_ns < -0.9F) {
      rtb_Abs_ns = -0.9F;
    }
  }

  VAR_TpcTmp_tRiseDbcFlt_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_h +
    rtb_Abs_ns;
  VAR_TpcTmp_CofDertTRiseDbcSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcTmp_tRiseDbcFlt_f32_FQ, ((const real32_T *)
      &(CAL_TpcTmp_tRiseDbcDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tRiseDbcDertSave1TableY_Cof_af32_FQ[0])), 8U);
  if (SWC_TPC_IG_FQ_DW.is_active_c42_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c42_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c42_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c42_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcTmp_tRiseDbcFlt_f32_FQ >
          CAL_TpcTmp_tRiseDbcTraNormalToSave1_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c42_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcTmp_tRiseDbcFlt_f32_FQ <
          CAL_TpcTmp_tRiseDbcTraSave1ToNormal_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c42_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcTmp_tRiseDbcFlt_f32_FQ >
            CAL_TpcTmp_tRiseDbcTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c42_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcTmp_tRiseDbcFlt_f32_FQ >
          CAL_TpcTmp_tRiseDbcTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c42_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcTmp_tRiseDbcFlt_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_bi,
    &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_bi);
  VAR_TpcTmp_CofDertTRiseDbcSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_bi, ((const real32_T *)
      &(CAL_TpcTmp_tRiseDbcDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tRiseDbcDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ))
  {
    VAR_TpcTmp_CofDertTRiseDbc_f32_FQ = VAR_TpcTmp_CofDertTRiseDbcSave1_f32_FQ;
  } else {
    if ((VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ)
        || (VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ ==
            CAL_Tpc_OverheatingMode_u8_FQ)) {
      VAR_TpcTmp_CofDertTRiseDbc_f32_FQ = VAR_TpcTmp_CofDertTRiseDbcSave2_f32_FQ;
    }
  }

  if (VAR_TpcTmp_CofDertDbc_f32_FQ <= VAR_TpcTmp_CofDertTRiseDbc_f32_FQ) {
    rtb_Switch_dc = VAR_TpcTmp_CofDertDbc_f32_FQ;
  } else {
    rtb_Switch_dc = VAR_TpcTmp_CofDertTRiseDbc_f32_FQ;
  }

  VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ = (1.0F - rtb_Switch_dc > 1.0E-6F);
  TPC_bDernDbcTemp_FQ = VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ;
  rtb_Subtract_fv = (real32_T)VAR_TpcTmp_tCoolTempFlt_u16_FQ -
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_m;
  if (rtb_Subtract_fv >= CAL_TpcTmp_CoolTempRiseDiff_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_m += CAL_TpcTmp_CoolTempAdds_f32_FQ;
  } else {
    if (rtb_Subtract_fv <= CAL_TpcTmp_CoolTempDecDiff_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_m += CAL_TpcTmp_CoolTempMinus_f32_FQ;
    }
  }

  rtb_Abs1_p = rtb_Subtract_fv - (real32_T)VAR_TpcTmp_TCoolStableDiff_u16_FQ;
  if ((rtb_Abs1_p >= CAL_TpcTmp_CoolChgTempUpDiff_f32_FQ) || (rtb_Abs1_p <=
       CAL_TpcTmp_CoolChgTempDownDiff_f32_FQ)) {
    rtb_Abs_ns = floorf(rtb_Subtract_fv);
    if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
      rtb_Abs_ns = 0.0F;
    } else {
      rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
    }

    VAR_TpcTmp_TCoolStableDiff_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
      (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
      rtb_Abs_ns);
  }

  rtb_Abs_ns = CAL_TpcTmp_CoolTempKp_f32_FQ * (real32_T)
    VAR_TpcTmp_TCoolStableDiff_u16_FQ;
  if (rtb_Abs_ns > 0.9F) {
    rtb_Abs_ns = 0.9F;
  } else {
    if (rtb_Abs_ns < -0.9F) {
      rtb_Abs_ns = -0.9F;
    }
  }

  VAR_TpcTmp_tCoolantTempFlt_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_m +
    rtb_Abs_ns;
  VAR_TpcTmp_CofDertTCoolantSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcTmp_tCoolantTempFlt_f32_FQ, ((const real32_T *)
      &(CAL_TpcTmp_tCoolantDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tCoolantDertSave1TableY_Cof_af32_FQ[0])), 8U);
  if (SWC_TPC_IG_FQ_DW.is_active_c38_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c38_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c38_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcTmp_tCoolantOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c38_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcTmp_tCoolantTempFlt_f32_FQ >
          CAL_TpcTmp_tCoolantTraNormalToSave1_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c38_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcTmp_tCoolantOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcTmp_tCoolantTempFlt_f32_FQ <
          CAL_TpcTmp_tCoolantTraSave1ToNormal_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c38_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcTmp_tCoolantOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcTmp_tCoolantTempFlt_f32_FQ >
            CAL_TpcTmp_tCoolantTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c38_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcTmp_tCoolantOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcTmp_tCoolantTempFlt_f32_FQ >
          CAL_TpcTmp_tCoolantTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c38_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcTmp_tCoolantOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcTmp_tCoolantTempFlt_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_d, &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_d);
  VAR_TpcTmp_CofDertTCoolantSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_d, ((const real32_T *)
      &(CAL_TpcTmp_tCoolantDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tCoolantDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcTmp_tCoolantOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcTmp_tCoolantOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ))
  {
    VAR_TpcTmp_CofDertTcoolant_f32_FQ = VAR_TpcTmp_CofDertTCoolantSave1_f32_FQ;
  } else {
    if ((VAR_TpcTmp_tCoolantOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ)
        || (VAR_TpcTmp_tCoolantOperationMode_u8_FQ ==
            CAL_Tpc_OverheatingMode_u8_FQ)) {
      VAR_TpcTmp_CofDertTcoolant_f32_FQ = VAR_TpcTmp_CofDertTCoolantSave2_f32_FQ;
    }
  }

  VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ = (1.0F -
    VAR_TpcTmp_CofDertTcoolant_f32_FQ > 1.0E-6F);
  TPC_bDernCoolantTemp_FQ = VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ;
  VAR_TpcTmp_CofDertTdrvboard_f32_FQ = look1_iflf_binlcapw
    (*rtu_HSPF_BUS_HSPF_tDrvBoardTemp, ((const real32_T *)
      &(CAL_TpcTmp_tDrvboardDertTableX_tDrv_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tDrvboardDertTableY_Cof_af32_FQ[0])), 8U);
  VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ = (1.0F -
    VAR_TpcTmp_CofDertTdrvboard_f32_FQ > 1.0E-6F);
  TPC_bDernDrvBoardTemp_FQ = VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ;
  if (*rtu_HSPF_BUS_HSPF_nSlowFlt >= 0.0F) {
    rtb_Subtract_fv = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Subtract_fv = 0.0F;
  }

  VAR_TpcSmp_cofDertOvrSpdElecQuad1_f32_FQ = look1_iflf_binlcapw(rtb_Subtract_fv,
    ((const real32_T *)&(CAL_TpcSmp_OvrSpdQurd1TableX_Spd_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrSpdQurd1TableY_Cof_af32_FQ[0])), 6U);
  if (*rtu_HSPF_BUS_HSPF_nSlowFlt <= 0.0F) {
    rtb_Subtract_fv = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Subtract_fv = 0.0F;
  }

  VAR_TpcSmp_cofDertOvrSpdElecQuad3_f32_FQ = look1_iflf_binlcapw(fabsf
    (rtb_Subtract_fv), ((const real32_T *)
                        &(CAL_TpcSmp_OvrSpdQurd3TableX_Spd_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrSpdQurd3TableY_Cof_af32_FQ[0])), 6U);
  if (VAR_TpcSmp_cofDertOvrSpdElecQuad1_f32_FQ <=
      VAR_TpcSmp_cofDertOvrSpdElecQuad3_f32_FQ) {
    rtb_Abs1_p = VAR_TpcSmp_cofDertOvrSpdElecQuad1_f32_FQ;
  } else {
    rtb_Abs1_p = VAR_TpcSmp_cofDertOvrSpdElecQuad3_f32_FQ;
  }

  VAR_TpcSmp_flgElecTrqLimOvrSpdActv_b_FQ = (1.0F - rtb_Abs1_p > 1.0E-6F);
  if (*rtu_HSPF_BUS_HSPF_nSlowFlt >= 0.0F) {
    rtb_Subtract_fv = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Subtract_fv = 0.0F;
  }

  VAR_TpcSmp_cofDertOvrSpdGenQuad4_f32_FQ = look1_iflf_binlcapw(rtb_Subtract_fv,
    ((const real32_T *)&(CAL_TpcSmp_OvrSpdQurd4TableX_Spd_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrSpdQurd4TableY_Cof_af32_FQ[0])), 6U);
  if (*rtu_HSPF_BUS_HSPF_nSlowFlt <= 0.0F) {
    rtb_Subtract_fv = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Subtract_fv = 0.0F;
  }

  VAR_TpcSmp_cofDertOvrSpdGenQuad2_f32_FQ = look1_iflf_binlcapw(fabsf
    (rtb_Subtract_fv), ((const real32_T *)
                        &(CAL_TpcSmp_OvrSpdQurd2TableX_Spd_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrSpdQurd2TableY_Cof_af32_FQ[0])), 6U);
  if (VAR_TpcSmp_cofDertOvrSpdGenQuad4_f32_FQ <=
      VAR_TpcSmp_cofDertOvrSpdGenQuad2_f32_FQ) {
    rtb_Add7_l = VAR_TpcSmp_cofDertOvrSpdGenQuad4_f32_FQ;
  } else {
    rtb_Add7_l = VAR_TpcSmp_cofDertOvrSpdGenQuad2_f32_FQ;
  }

  VAR_TpcSmp_flgGenTrqLimOvrSpdActv_b_FQ = (1.0F - rtb_Add7_l > 1.0E-6F);
  TPC_bDernMtrSpd_FQ = (VAR_TpcSmp_flgElecTrqLimOvrSpdActv_b_FQ ||
                        VAR_TpcSmp_flgGenTrqLimOvrSpdActv_b_FQ);
  if (-1000.0F > CAL_TpcSmp_uDcLnkMinMax_f32_FQ) {
    VAR_TpcSmp_uDcLnkMin_f32_FQ = CAL_TpcSmp_uDcLnkMinMax_f32_FQ;
  } else if (-1000.0F < CAL_TpcSmp_uDcLnkMinMin_f32_FQ) {
    VAR_TpcSmp_uDcLnkMin_f32_FQ = CAL_TpcSmp_uDcLnkMinMin_f32_FQ;
  } else {
    VAR_TpcSmp_uDcLnkMin_f32_FQ = -1000.0F;
  }

  rtb_Subtract_fv = *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt -
    VAR_TpcSmp_uDcLnkMin_f32_FQ;
  VAR_TpcSmp_cofDertUdrVoltElec_f32_FQ = look1_iflf_binlcapw(rtb_Subtract_fv, ((
    const real32_T *)&(CAL_TpcSmp_UdrVoltElecTableX_uDc_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_UdrVoltElecTableY_Cof_af32_FQ[0])), 4U);
  VAR_TpcSmp_flgLinearDertUdrVoltElec_b_FQ = (1.0F -
    VAR_TpcSmp_cofDertUdrVoltElec_f32_FQ > 1.0E-6F);
  if (CAL_TpcMot_flgPwrRefSwt_b_FQ) {
    VAR_TpcMot_ElecPwrRef_f32_FQ = rtb_Switch_lt_tmp *
      VAR_TpcMot_TrqElecExC_f32_FQ / 9550.0F;
  } else {
    VAR_TpcMot_ElecPwrRef_f32_FQ = GLB_Tpc_MaximumPower_f32_FQ;
  }

  SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om += rtb_Subtract_fv *
    CAL_TpcSmp_ElecUdrVoltKi_f32_FQ;
  rtb_Subtract_fv *= CAL_TpcSmp_ElecUdrVoltKp_f32_FQ;
  if (rtb_Subtract_fv > CAL_TpcSmp_ElecUdrVoltypLim_f32_FQ) {
    rtb_Subtract_fv = CAL_TpcSmp_ElecUdrVoltypLim_f32_FQ;
  } else {
    if (rtb_Subtract_fv < -CAL_TpcSmp_ElecUdrVoltypLim_f32_FQ) {
      rtb_Subtract_fv = -CAL_TpcSmp_ElecUdrVoltypLim_f32_FQ;
    }
  }

  rtb_Add3_a = SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om + rtb_Subtract_fv;
  if (rtb_Add3_a > VAR_TpcMot_ElecPwrRef_f32_FQ) {
    VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ = VAR_TpcMot_ElecPwrRef_f32_FQ;
  } else if (rtb_Add3_a < 0.0F) {
    VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ = 0.0F;
  } else {
    VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ = rtb_Add3_a;
  }

  VAR_TpcSmp_flgPIDertUdrVoltElec_b_FQ = (VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ
    != VAR_TpcMot_ElecPwrRef_f32_FQ);
  if (VAR_TpcSmp_flgLinearDertUdrVoltElec_b_FQ ||
      VAR_TpcSmp_flgPIDertUdrVoltElec_b_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_e0 = (uint16_T)((uint32_T)
      !SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_c +
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_e0);
    if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_e0 >= 65535) {
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_e0 = MAX_uint16_T;
    }
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_e0 = 0U;
  }

  SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_c = ((uint32_T)
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_e0 * CAL_TpcSmp_FacElecUdrVolt_u8_FQ >
    CAL_TpcSmp_CntElecUdrVolt_u8_FQ);
  VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ =
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_c;
  TPC_bDernUndrUdc_FQ = (rtb_RelationalOperator_mt &&
    VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ);
  TPC_bDernCAN_FQ = ((rtb_tpccod_TrqMax == VAR_TpcSmp_TrqMaxCanSet_f32_FQ) ||
                     (rtb_tpccod_TrqMin == VAR_TpcSmp_TrqMinCanSet_f32_FQ));
  rtb_RelationalOperator3_pj = ((TPC_stMotorMod_FQ == ((uint8_T)
    GLB_TpcCod_FwELect_u8_FQ)) || (TPC_stMotorMod_FQ == ((uint8_T)
    GLB_TpcCod_FwGene_u8_FQ)));
  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertExCTrq_b_FQ = ((fabsf(rtb_tpccod_TrqMax -
      VAR_TpcMot_TrqElecExC_f32_FQ) <= 0.001F) && (*rtu_TDC_BUS_TDC_TrqDes >
      VAR_TpcMot_TrqElecExC_f32_FQ));
  } else {
    rtb_Abs_ns = fabsf(VAR_TpcMot_TrqGenExC_f32_FQ);
    rtb_RelationalOperator3_fry = (*rtu_TDC_BUS_TDC_TrqDes > rtb_Abs_ns);
    rtb_Abs_ns -= rtb_tpccod_TrqMax;
    rtb_Abs_ns = fabsf(rtb_Abs_ns);
    VAR_tpccod_flgMaxDertExCTrq_b_FQ = ((rtb_Abs_ns <= 0.001F) &&
      rtb_RelationalOperator3_fry);
  }

  if (CAL_TpcMot_flgTrqRefSwt_b_FQ) {
    VAR_TpcMot_ElecTrqRef_f32_FQ = VAR_TpcMot_TrqElecExC_f32_FQ;
  } else {
    VAR_TpcMot_ElecTrqRef_f32_FQ = GLB_Tpc_MaximumTorque_f32_FQ;
  }

  VAR_TpcMot_ElecTrqLimTsttrWoRamp_f32_FQ = rtb_Switch_iy *
    VAR_TpcMot_ElecTrqRef_f32_FQ;
  rtb_Abs_ns = VAR_TpcMot_ElecTrqLimTsttrWoRamp_f32_FQ -
    VAR_TpcMot_ElecTrqLimTsttr_f32_FQ;
  if (rtb_Abs_ns <= CAL_TpcMot_tSttrTrqLimRamp_f32_FQ) {
    if (-rtb_Abs_ns <= CAL_TpcMot_tSttrTrqLimRamp_f32_FQ) {
      VAR_TpcMot_ElecTrqLimTsttr_f32_FQ =
        VAR_TpcMot_ElecTrqLimTsttrWoRamp_f32_FQ;
    } else {
      VAR_TpcMot_ElecTrqLimTsttr_f32_FQ -= CAL_TpcMot_tSttrTrqLimRamp_f32_FQ;
    }
  } else {
    VAR_TpcMot_ElecTrqLimTsttr_f32_FQ += CAL_TpcMot_tSttrTrqLimRamp_f32_FQ;
  }

  if (CAL_TpcMot_flgTrqRefSwt_b_FQ) {
    VAR_TpcMot_GenTrqRef_f32_FQ = VAR_TpcMot_TrqGenExC_f32_FQ;
  } else {
    VAR_TpcMot_GenTrqRef_f32_FQ = -GLB_Tpc_MaximumTorque_f32_FQ;
  }

  VAR_TpcMot_GenTrqLimTsttrWoRamp_f32_FQ = rtb_Switch_iy *
    VAR_TpcMot_GenTrqRef_f32_FQ;
  rtb_Abs_ns = VAR_TpcMot_GenTrqLimTsttrWoRamp_f32_FQ -
    VAR_TpcMot_GenTrqLimTsttr_f32_FQ;
  if (rtb_Abs_ns <= CAL_TpcMot_tSttrTrqLimRamp_f32_FQ) {
    if (-rtb_Abs_ns <= CAL_TpcMot_tSttrTrqLimRamp_f32_FQ) {
      VAR_TpcMot_GenTrqLimTsttr_f32_FQ = VAR_TpcMot_GenTrqLimTsttrWoRamp_f32_FQ;
    } else {
      VAR_TpcMot_GenTrqLimTsttr_f32_FQ -= CAL_TpcMot_tSttrTrqLimRamp_f32_FQ;
    }
  } else {
    VAR_TpcMot_GenTrqLimTsttr_f32_FQ += CAL_TpcMot_tSttrTrqLimRamp_f32_FQ;
  }

  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertStrTemp_b_FQ = ((fabsf
      (VAR_TpcMot_ElecTrqLimTsttr_f32_FQ - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcMot_flgTrqLimTsttrActv_b_FQ);
  } else {
    VAR_tpccod_flgMaxDertStrTemp_b_FQ = (VAR_TpcMot_flgTrqLimTsttrActv_b_FQ &&
      (fabsf(fabsf(VAR_TpcMot_GenTrqLimTsttr_f32_FQ) - rtb_tpccod_TrqMax) <=
       0.001F));
  }

  VAR_TpcTmp_ElecTrqLimTdbcWoRamp_f32_FQ = rtb_Switch_dc *
    VAR_TpcMot_ElecTrqRef_f32_FQ;
  rtb_Abs_ns = VAR_TpcTmp_ElecTrqLimTdbcWoRamp_f32_FQ -
    VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ;
  if (rtb_Abs_ns <= CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ) {
    if (-rtb_Abs_ns <= CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ) {
      VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ = VAR_TpcTmp_ElecTrqLimTdbcWoRamp_f32_FQ;
    } else {
      VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ -= CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ;
    }
  } else {
    VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ += CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ;
  }

  VAR_TpcTmp_GenTrqLimTdbcWoRamp_f32_FQ = rtb_Switch_dc *
    VAR_TpcMot_GenTrqRef_f32_FQ;
  rtb_Switch_dc = VAR_TpcTmp_GenTrqLimTdbcWoRamp_f32_FQ -
    VAR_TpcTmp_GenTrqLimTdbc_f32_FQ;
  if (rtb_Switch_dc <= CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ) {
    if (-rtb_Switch_dc <= CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ) {
      VAR_TpcTmp_GenTrqLimTdbc_f32_FQ = VAR_TpcTmp_GenTrqLimTdbcWoRamp_f32_FQ;
    } else {
      VAR_TpcTmp_GenTrqLimTdbc_f32_FQ -= CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ;
    }
  } else {
    VAR_TpcTmp_GenTrqLimTdbc_f32_FQ += CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ;
  }

  VAR_TpcTmp_ElecTrqLimTcoolant_f32_FQ = VAR_TpcTmp_CofDertTcoolant_f32_FQ *
    VAR_TpcMot_ElecTrqRef_f32_FQ;
  VAR_TpcTmp_GenTrqLimTcoolant_f32_FQ = VAR_TpcTmp_CofDertTcoolant_f32_FQ *
    VAR_TpcMot_GenTrqRef_f32_FQ;
  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertTempDBC_b_FQ = ((fabsf(VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ
      - rtb_tpccod_TrqMax) <= 0.001F) && VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ);
  } else {
    VAR_tpccod_flgMaxDertTempDBC_b_FQ = (VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ &&
      (fabsf(fabsf(VAR_TpcTmp_GenTrqLimTdbc_f32_FQ) - rtb_tpccod_TrqMax) <=
       0.001F));
  }

  VAR_TpcTmp_ElecTrqLimTdrvboard_f32_FQ = VAR_TpcTmp_CofDertTdrvboard_f32_FQ *
    VAR_TpcMot_ElecTrqRef_f32_FQ;
  VAR_TpcTmp_GenTrqLimTdrvboard_f32_FQ = VAR_TpcTmp_CofDertTdrvboard_f32_FQ *
    VAR_TpcMot_GenTrqRef_f32_FQ;
  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertTCoolant_b_FQ = ((fabsf
      (VAR_TpcTmp_ElecTrqLimTcoolant_f32_FQ - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ);
    VAR_tpccod_flgMaxDertTDrvBoard_b_FQ = ((fabsf
      (VAR_TpcTmp_ElecTrqLimTdrvboard_f32_FQ - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ);
  } else {
    VAR_tpccod_flgMaxDertTCoolant_b_FQ = (VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ &&
      (fabsf(fabsf(VAR_TpcTmp_GenTrqLimTcoolant_f32_FQ) - rtb_tpccod_TrqMax) <=
       0.001F));
    VAR_tpccod_flgMaxDertTDrvBoard_b_FQ =
      (VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ && (fabsf(fabsf
         (VAR_TpcTmp_GenTrqLimTdrvboard_f32_FQ) - rtb_tpccod_TrqMax) <= 0.001F));
  }

  rtb_Abs_ns = roundf(*rtu_HSPF_BUS_HSPF_tIGBTTjFlt);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  VAR_TpcTmp_tIgbtTempFlt_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
    rtb_Abs_ns);
  rtb_Switch_dc = (real32_T)VAR_TpcTmp_tIgbtTempFlt_u16_FQ -
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_fk;
  if (rtb_Switch_dc >= CAL_TpcTmp_IGBTTempRiseDiff_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_fk += CAL_TpcTmp_IGBTTempAdds_f32_FQ;
  } else {
    if (rtb_Switch_dc <= CAL_TpcTmp_IGBTTempDecDiff_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_fk += CAL_TpcTmp_IGBTTempMinus_f32_FQ;
    }
  }

  rtb_Switch_iy = rtb_Switch_dc - (real32_T)VAR_TpcTmp_TIgbtStableDiff_u16_FQ;
  if ((rtb_Switch_iy >= CAL_TpcTmp_IgbtChgTempUpDiff_f32_FQ) || (rtb_Switch_iy <=
       CAL_TpcTmp_IgbtChgTempDownDiff_f32_FQ)) {
    rtb_Abs_ns = floorf(rtb_Switch_dc);
    if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
      rtb_Abs_ns = 0.0F;
    } else {
      rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
    }

    VAR_TpcTmp_TIgbtStableDiff_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
      (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
      rtb_Abs_ns);
  }

  rtb_Abs_ns = CAL_TpcTmp_IGBTTempKp_f32_FQ * (real32_T)
    VAR_TpcTmp_TIgbtStableDiff_u16_FQ;
  if (rtb_Abs_ns > 0.9F) {
    rtb_Abs_ns = 0.9F;
  } else {
    if (rtb_Abs_ns < -0.9F) {
      rtb_Abs_ns = -0.9F;
    }
  }

  VAR_TpcTmp_tIGBTTempFlt_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_fk +
    rtb_Abs_ns;
  VAR_TpcTmp_tRiseIGBT_f32_FQ = VAR_TpcTmp_tIGBTTempFlt_f32_FQ - (real32_T)
    VAR_TpcTmp_tCoolTempFlt_u16_FQ;
  rtb_Abs_ns = roundf(VAR_TpcTmp_tRiseIGBT_f32_FQ);
  if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
    rtb_Abs_ns = 0.0F;
  } else {
    rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
  }

  VAR_TpcTmp_tIgbtRiseTempFlt_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ? (int32_T)
    (int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)(uint16_T)
    rtb_Abs_ns);
  rtb_Switch_dc = (real32_T)VAR_TpcTmp_tIgbtRiseTempFlt_u16_FQ -
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_d;
  if (rtb_Switch_dc >= CAL_TpcTmp_IGBTRiseTempRiseDiff_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_d += CAL_TpcTmp_IGBRiseTTempAdds_f32_FQ;
  } else {
    if (rtb_Switch_dc <= CAL_TpcTmp_IGBTRiseTempDecDiff_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_d +=
        CAL_TpcTmp_IGBTRiseTempMinus_f32_FQ;
    }
  }

  rtb_Switch_iy = rtb_Switch_dc - (real32_T)
    VAR_TpcTmp_TIgbtRiseStableDiff_u16_FQ;
  if ((rtb_Switch_iy >= CAL_TpcTmp_IgbtRiseChgTempUpDiff_f32_FQ) ||
      (rtb_Switch_iy <= CAL_TpcTmp_IgbtRiseChgTempDownDiff_f32_FQ)) {
    rtb_Abs_ns = floorf(rtb_Switch_dc);
    if (rtIsNaNF(rtb_Abs_ns) || rtIsInfF(rtb_Abs_ns)) {
      rtb_Abs_ns = 0.0F;
    } else {
      rtb_Abs_ns = fmodf(rtb_Abs_ns, 65536.0F);
    }

    VAR_TpcTmp_TIgbtRiseStableDiff_u16_FQ = (int16_T)(rtb_Abs_ns < 0.0F ?
      (int32_T)(int16_T)-(int16_T)(uint16_T)-rtb_Abs_ns : (int32_T)(int16_T)
      (uint16_T)rtb_Abs_ns);
  }

  rtb_Abs_ns = CAL_TpcTmp_IGBTRiseTempKp_f32_FQ * (real32_T)
    VAR_TpcTmp_TIgbtRiseStableDiff_u16_FQ;
  if (rtb_Abs_ns > 0.9F) {
    rtb_Abs_ns = 0.9F;
  } else {
    if (rtb_Abs_ns < -0.9F) {
      rtb_Abs_ns = -0.9F;
    }
  }

  VAR_TpcTmp_tRiseIGBTFlt_f32_FQ = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_d +
    rtb_Abs_ns;
  if (SWC_TPC_IG_FQ_DW.is_active_c44_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c44_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c44_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcTmp_tIGBTOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c44_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcTmp_tIGBTTempFlt_f32_FQ >
          CAL_TpcTmp_tIGBTTraNormalToSave1_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c44_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcTmp_tIGBTOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcTmp_tIGBTTempFlt_f32_FQ <
          CAL_TpcTmp_tIGBTTraSave1ToNormal_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c44_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcTmp_tIGBTOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcTmp_tIGBTTempFlt_f32_FQ >
            CAL_TpcTmp_tIGBTTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c44_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcTmp_tIGBTOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcTmp_tIGBTTempFlt_f32_FQ >
          CAL_TpcTmp_tIGBTTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c44_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcTmp_tIGBTOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcTmp_tIGBTTempFlt_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_er,
    &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_er);
  if (SWC_TPC_IG_FQ_DW.is_active_c46_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c46_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c46_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
    VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
  } else {
    switch (SWC_TPC_IG_FQ_DW.is_c46_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_NormalMode:
      if (VAR_TpcTmp_tRiseIGBTFlt_f32_FQ >
          CAL_TpcTmp_tRiseIGBTTraNormalToSave1_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c46_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave1;
        VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ = CAL_Tpc_Powersave1Mode_u8_FQ;
      }
      break;

     case SWC_TPC_IG_FQ_IN_Overheating:
      break;

     case SWC_TPC_IG_FQ_IN_PowerSave1:
      if (VAR_TpcTmp_tRiseIGBTFlt_f32_FQ <
          CAL_TpcTmp_tRiseIGBTTraSave1ToNormal_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c46_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_NormalMode;
        VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ = CAL_Tpc_NormalMode_u8_FQ;
      } else {
        if (VAR_TpcTmp_tRiseIGBTFlt_f32_FQ >
            CAL_TpcTmp_tRiseIGBTTraSave1ToSave2_f32_FQ) {
          SWC_TPC_IG_FQ_DW.is_c46_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_PowerSave2;
          VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ = CAL_Tpc_Powersave2Mode_u8_FQ;
        }
      }
      break;

     default:
      if (VAR_TpcTmp_tRiseIGBTFlt_f32_FQ >
          CAL_TpcTmp_tRiseIGBTTraSave2ToOverheating_f32_FQ) {
        SWC_TPC_IG_FQ_DW.is_c46_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_Overheating;
        VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ = CAL_Tpc_OverheatingMode_u8_FQ;
      }
      break;
    }
  }

  SWC_TPC_IG_FQ_GetHighTemp(VAR_TpcTmp_tRiseIGBTFlt_f32_FQ,
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_g, &SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_g);
  VAR_TpcTmp_CofDertTIGBTSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcTmp_tIGBTTempFlt_f32_FQ, ((const real32_T *)
      &(CAL_TpcTmp_tIGBTDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tIGBTDertSave1TableY_Cof_af32_FQ[0])), 8U);
  VAR_TpcTmp_CofDertTIGBTSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_er, ((const real32_T *)
      &(CAL_TpcTmp_tIGBTDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T *)
      &(CAL_TpcTmp_tIGBTDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcTmp_tIGBTOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcTmp_tIGBTOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ)) {
    VAR_TpcTmp_CofDertIGBT_f32_FQ = VAR_TpcTmp_CofDertTIGBTSave1_f32_FQ;
  } else {
    if ((VAR_TpcTmp_tIGBTOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ) ||
        (VAR_TpcTmp_tIGBTOperationMode_u8_FQ == CAL_Tpc_OverheatingMode_u8_FQ))
    {
      VAR_TpcTmp_CofDertIGBT_f32_FQ = VAR_TpcTmp_CofDertTIGBTSave2_f32_FQ;
    }
  }

  VAR_TpcTmp_CofDertTRiseIGBTSave1_f32_FQ = look1_iflf_binlxpw
    (VAR_TpcTmp_tRiseIGBTFlt_f32_FQ, ((const real32_T *)
      &(CAL_TpcTmp_tRiseIGBTDertSave1TableX_tSttr_af32_FQ[0])), ((const real32_T
       *)&(CAL_TpcTmp_tRiseIGBTDertSave1TableY_Cof_af32_FQ[0])), 8U);
  VAR_TpcTmp_CofDertTRiseIGBTSave2_f32_FQ = look1_iflf_binlxpw
    (SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_g, ((const real32_T *)
      &(CAL_TpcTmp_tRiseIGBTDertSave2TableX_tSttr_af32_FQ[0])), ((const real32_T
       *)&(CAL_TpcTmp_tRiseIGBTDertSave2TableY_Cof_af32_FQ[0])), 8U);
  if ((VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ == CAL_Tpc_NormalMode_u8_FQ) ||
      (VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ == CAL_Tpc_Powersave1Mode_u8_FQ))
  {
    VAR_TpcTmp_CofDertTRiseIGBT_f32_FQ = VAR_TpcTmp_CofDertTRiseIGBTSave1_f32_FQ;
  } else {
    if ((VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ == CAL_Tpc_Powersave2Mode_u8_FQ)
        || (VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ ==
            CAL_Tpc_OverheatingMode_u8_FQ)) {
      VAR_TpcTmp_CofDertTRiseIGBT_f32_FQ =
        VAR_TpcTmp_CofDertTRiseIGBTSave2_f32_FQ;
    }
  }

  if (VAR_TpcTmp_CofDertIGBT_f32_FQ <= VAR_TpcTmp_CofDertTRiseIGBT_f32_FQ) {
    rtb_Switch_iy = VAR_TpcTmp_CofDertIGBT_f32_FQ;
  } else {
    rtb_Switch_iy = VAR_TpcTmp_CofDertTRiseIGBT_f32_FQ;
  }

  VAR_TpcTmp_ElecTrqLimTIGBTWoRamp_f32_FQ = rtb_Switch_iy *
    VAR_TpcMot_ElecTrqRef_f32_FQ;
  rtb_Switch_dc = VAR_TpcTmp_ElecTrqLimTIGBTWoRamp_f32_FQ -
    VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ;
  if (rtb_Switch_dc <= CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ) {
    if (-rtb_Switch_dc <= CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ) {
      VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ =
        VAR_TpcTmp_ElecTrqLimTIGBTWoRamp_f32_FQ;
    } else {
      VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ -= CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ;
    }
  } else {
    VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ += CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ;
  }

  VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ = (1.0F - rtb_Switch_iy > 1.0E-6F);
  VAR_TpcTmp_GenTrqLimTIGBTWoRamp_f32_FQ = rtb_Switch_iy *
    VAR_TpcMot_GenTrqRef_f32_FQ;
  rtb_Switch_dc = VAR_TpcTmp_GenTrqLimTIGBTWoRamp_f32_FQ -
    VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ;
  if (rtb_Switch_dc <= CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ) {
    if (-rtb_Switch_dc <= CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ) {
      VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ = VAR_TpcTmp_GenTrqLimTIGBTWoRamp_f32_FQ;
    } else {
      VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ -= CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ;
    }
  } else {
    VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ += CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ;
  }

  VAR_TpcSmp_ElecTrqLimOvrSpd_f32_FQ = rtb_Abs1_p * VAR_TpcMot_ElecTrqRef_f32_FQ;
  VAR_TpcSmp_GenTrqLimOvrSpd_f32_FQ = rtb_Add7_l * VAR_TpcMot_GenTrqRef_f32_FQ;
  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertTIGBT_b_FQ = ((fabsf(VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ
      - rtb_tpccod_TrqMax) <= 0.001F) && VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ);
    VAR_tpccod_flgMaxDertMtrSpd_b_FQ = ((fabsf
      (VAR_TpcSmp_ElecTrqLimOvrSpd_f32_FQ - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcSmp_flgElecTrqLimOvrSpdActv_b_FQ);
  } else {
    VAR_tpccod_flgMaxDertTIGBT_b_FQ = (VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ &&
      (fabsf(fabsf(VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ) - rtb_tpccod_TrqMax) <=
       0.001F));
    VAR_tpccod_flgMaxDertMtrSpd_b_FQ = ((fabsf(fabsf
      (VAR_TpcSmp_GenTrqLimOvrSpd_f32_FQ) - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcSmp_flgGenTrqLimOvrSpdActv_b_FQ);
  }

  if (1000.0F > CAL_TpcSmp_iDcLnkMaxMax_f32_FQ) {
    VAR_TpcSmp_iDcLnkMax_f32_FQ = CAL_TpcSmp_iDcLnkMaxMax_f32_FQ;
  } else if (1000.0F < CAL_TpcSmp_iDcLnkMaxMin_f32_FQ) {
    VAR_TpcSmp_iDcLnkMax_f32_FQ = CAL_TpcSmp_iDcLnkMaxMin_f32_FQ;
  } else {
    VAR_TpcSmp_iDcLnkMax_f32_FQ = 1000.0F;
  }

  VAR_TpcSmp_ElecPwrAlowMax_f32_FQ = VAR_TpcSmp_iDcLnkMax_f32_FQ *
    *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt / 1000.0F;
  if (CAL_TpcSmp_flgUsePwrLoss_b_FQ) {
    VAR_tpcsmp_PwrLoss_f32_FQ = look2_iflf_binlcapw
      (VAR_TpcSmp_ElecPwrAlowMax_f32_FQ, rtb_Switch_lt_tmp,
       rtCP_uDLookupTable_bp01Data, rtCP_uDLookupTable_bp02Data,
       rtCP_uDLookupTable_tableData, rtCP_uDLookupTable_maxIndex, 33U);
  } else {
    VAR_tpcsmp_PwrLoss_f32_FQ = 0.0F;
  }

  VAR_tpcsmp_ElecPwrDert_f32_FQ = (VAR_TpcSmp_ElecPwrAlowMax_f32_FQ -
    VAR_tpcsmp_PwrLoss_f32_FQ) * CAL_TpcSmp_SystemEffiElec_f32_FQ;
  rtb_Switch_iy = rtb_Switch_lt_tmp * CAL_TpcSmp_TrqAddMax_f32_FQ / 9550.0F;
  if (rtb_Switch_iy < CAL_TpcSmp_PwrAddMax_f32_FQ) {
    VAR_tpcsmp_AddPwrElecOvrCurt_f32_FQ = rtb_Switch_iy;
  } else {
    VAR_tpcsmp_AddPwrElecOvrCurt_f32_FQ = CAL_TpcSmp_PwrAddMax_f32_FQ;
  }

  VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ = (VAR_TpcSmp_ElecPwrAlowMax_f32_FQ -
    VAR_tpcsmp_PwrLoss_f32_FQ) + VAR_tpcsmp_AddPwrElecOvrCurt_f32_FQ;
  VAR_tpcsmp_yiDelay_f32_FQ = VAR_tpcsmp_yi_f32_FQ;
  if (*rtu_HSPF_BUS_HSPF_iDcLnkEstFlt >= 0.0F) {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_iDcLnkEstFlt;
  } else {
    rtb_Switch_iy = 0.0F;
  }

  VAR_TpcSmp_ErrElecOvrCurt_f32_FQ = VAR_TpcSmp_ElecPwrAlowMax_f32_FQ -
    *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt * rtb_Switch_iy / 1000.0F;
  VAR_tpcsmp_KiProduct_f32_FQ = VAR_TpcSmp_ErrElecOvrCurt_f32_FQ *
    CAL_TpcSmp_ElecOvrCurtKi_f32_FQ;
  VAR_tpcsmp_KiProductSum_f32_FQ = VAR_tpcsmp_yiDelay_f32_FQ +
    VAR_tpcsmp_KiProduct_f32_FQ;
  VAR_tpcsmp_KpProduct_f32_FQ = VAR_TpcSmp_ErrElecOvrCurt_f32_FQ *
    CAL_TpcSmp_ElecOvrCurtKp_f32_FQ;
  if (VAR_tpcsmp_KpProduct_f32_FQ > CAL_TpcSmp_ElecOvrCurtypLim_f32_FQ) {
    VAR_tpcsmp_KpProductSau_f32_FQ = CAL_TpcSmp_ElecOvrCurtypLim_f32_FQ;
  } else if (VAR_tpcsmp_KpProduct_f32_FQ < -CAL_TpcSmp_ElecOvrCurtypLim_f32_FQ)
  {
    VAR_tpcsmp_KpProductSau_f32_FQ = -CAL_TpcSmp_ElecOvrCurtypLim_f32_FQ;
  } else {
    VAR_tpcsmp_KpProductSau_f32_FQ = VAR_tpcsmp_KpProduct_f32_FQ;
  }

  VAR_tpcsmp_PIOutput_f32_FQ = VAR_tpcsmp_KiProductSum_f32_FQ +
    VAR_tpcsmp_KpProductSau_f32_FQ;
  if (VAR_tpcsmp_PIOutput_f32_FQ > 0.0F) {
    rtb_Abs_ns = 0.0F;
  } else if (VAR_tpcsmp_PIOutput_f32_FQ < -VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ)
  {
    rtb_Abs_ns = -VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ;
  } else {
    rtb_Abs_ns = VAR_tpcsmp_PIOutput_f32_FQ;
  }

  VAR_TpcSmp_ElecPwrPIDertOvrCurt_f32_FQ = rtb_Abs_ns +
    VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ;
  rtb_Switch_iy = VAR_TpcSmp_iDcLnkMax_f32_FQ - rtb_Switch_iy;
  VAR_TpcSmp_cofDertOvrCurtElec_f32_FQ = look1_iflf_binlcapw(rtb_Switch_iy, ((
    const real32_T *)&(CAL_TpcSmp_OvrCurtLimElecTableX_iDc_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrCurtLimElecTableY_Cof_af32_FQ[0])), 4U);
  VAR_TpcSmp_ElecPwrLinearDertOvrCurt_f32_FQ =
    VAR_TpcSmp_cofDertOvrCurtElec_f32_FQ * VAR_TpcMot_ElecPwrRef_f32_FQ;
  if (CAL_TpcSmp_CurtModeSelc_b_FQ) {
    VAR_TpcSmp_ElecPwrLimOvrCurt_f32_FQ = VAR_tpcsmp_ElecPwrDert_f32_FQ;
  } else if (VAR_TpcSmp_ElecPwrPIDertOvrCurt_f32_FQ <
             VAR_TpcSmp_ElecPwrLinearDertOvrCurt_f32_FQ) {
    VAR_TpcSmp_ElecPwrLimOvrCurt_f32_FQ = VAR_TpcSmp_ElecPwrPIDertOvrCurt_f32_FQ;
  } else {
    VAR_TpcSmp_ElecPwrLimOvrCurt_f32_FQ =
      VAR_TpcSmp_ElecPwrLinearDertOvrCurt_f32_FQ;
  }

  if (TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ)) {
    rtb_Abs_ns = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Abs_ns = 0.0F;
  }

  rtb_Abs1_p = fabsf(rtb_Abs_ns);
  if (rtb_Abs1_p != 0.0F) {
    VAR_TpcCod_ElecTrqCalcOvrCurt_f32_FQ = VAR_TpcSmp_ElecPwrLimOvrCurt_f32_FQ *
      9550.0F / rtb_Abs1_p;
  } else {
    VAR_TpcCod_ElecTrqCalcOvrCurt_f32_FQ = GLB_Tpc_MaximumTorque_f32_FQ;
  }

  VAR_TpcSmp_flgLinearDertOvrCurtElec_b_FQ = (1.0F -
    VAR_TpcSmp_cofDertOvrCurtElec_f32_FQ > 1.0E-6F);
  VAR_TpcSmp_flgPIDertOvrCurtElec_b_FQ = (VAR_TpcSmp_ElecPwrPIDertOvrCurt_f32_FQ
    != VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ);
  if (VAR_TpcSmp_flgLinearDertOvrCurtElec_b_FQ ||
      VAR_TpcSmp_flgPIDertOvrCurtElec_b_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_kw = (uint16_T)((uint32_T)
      !VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ +
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_kw);
    if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_kw >= 65535) {
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_kw = MAX_uint16_T;
    }
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_kw = 0U;
  }

  VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ = ((uint32_T)
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_kw * CAL_TpcSmp_FacElecOvrCurt_u8_FQ >
    CAL_TpcSmp_CntElecOvrCurt_u8_FQ);
  if (-1000.0F > CAL_TpcSmp_iDcLnkMinMax_f32_FQ) {
    VAR_TpcSmp_iDcLnkMin_f32_FQ = CAL_TpcSmp_iDcLnkMinMax_f32_FQ;
  } else if (-1000.0F < CAL_TpcSmp_iDcLnkMinMin_f32_FQ) {
    VAR_TpcSmp_iDcLnkMin_f32_FQ = CAL_TpcSmp_iDcLnkMinMin_f32_FQ;
  } else {
    VAR_TpcSmp_iDcLnkMin_f32_FQ = -1000.0F;
  }

  rtb_Abs1_p = VAR_TpcSmp_iDcLnkMin_f32_FQ * *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt /
    1000.0F;
  if (CAL_TpcSmp_flgUsePwrLossGen_b_FQ) {
    VAR_tpcsmp_PwrLossGen_f32_FQ = look2_iflf_binlcapw(rtb_Abs1_p,
      rtb_Switch_lt_tmp, rtCP_uDLookupTable_bp01Data_p,
      rtCP_uDLookupTable_bp02Data_a, rtCP_uDLookupTable_tableData_b,
      rtCP_uDLookupTable_maxIndex_i, 33U);
  } else {
    VAR_tpcsmp_PwrLossGen_f32_FQ = 0.0F;
  }

  VAR_tpcsmp_GenPwrDert_f32_FQ = (rtb_Abs1_p - VAR_tpcsmp_PwrLossGen_f32_FQ) *
    CAL_TpcSmp_SystemEffiGen_f32_FQ;
  VAR_TpcSmp_GenPwrAlowMax_f32_FQ = fabsf(rtb_Abs1_p);
  rtb_Switch_iy = (real32_T)(rtb_Switch_lt_tmp * CAL_TpcSmp_TrqAddMaxGen_f32_FQ /
    9550.0);
  if (!(rtb_Switch_iy < CAL_TpcSmp_PwrAddMaxGen_f32_FQ)) {
    rtb_Switch_iy = CAL_TpcSmp_PwrAddMaxGen_f32_FQ;
  }

  VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ = (VAR_TpcSmp_GenPwrAlowMax_f32_FQ +
    VAR_tpcsmp_PwrLossGen_f32_FQ) + rtb_Switch_iy;
  if (*rtu_HSPF_BUS_HSPF_iDcLnkEstFlt <= 0.0F) {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_iDcLnkEstFlt;
  } else {
    rtb_Switch_iy = 0.0F;
  }

  VAR_TpcSmp_ErrGenOvrCurt_f32_FQ = VAR_TpcSmp_GenPwrAlowMax_f32_FQ - fabsf
    (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt * rtb_Switch_iy / 1000.0F);
  SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g += VAR_TpcSmp_ErrGenOvrCurt_f32_FQ *
    CAL_TpcSmp_GenOvrCurtKi_f32_FQ;
  rtb_Abs1_p = VAR_TpcSmp_ErrGenOvrCurt_f32_FQ * CAL_TpcSmp_GenOvrCurtKp_f32_FQ;
  if (rtb_Abs1_p > CAL_TpcSmp_GenOvrCurtypLim_f32_FQ) {
    rtb_Abs1_p = CAL_TpcSmp_GenOvrCurtypLim_f32_FQ;
  } else {
    if (rtb_Abs1_p < -CAL_TpcSmp_GenOvrCurtypLim_f32_FQ) {
      rtb_Abs1_p = -CAL_TpcSmp_GenOvrCurtypLim_f32_FQ;
    }
  }

  rtb_Switch_dc = SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g + rtb_Abs1_p;
  if (rtb_Switch_dc > 0.0F) {
    rtb_Abs_ns = 0.0F;
  } else if (rtb_Switch_dc < -VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ) {
    rtb_Abs_ns = -VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ;
  } else {
    rtb_Abs_ns = rtb_Switch_dc;
  }

  rtb_Add7_l = rtb_Abs_ns + VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ;
  VAR_TpcSmp_GenPwrPIDertOvrCurt_f32_FQ = -rtb_Add7_l;
  rtb_Switch_iy = fabsf(rtb_Switch_iy);
  rtb_Switch_iy = fabsf(VAR_TpcSmp_iDcLnkMin_f32_FQ) - rtb_Switch_iy;
  VAR_TpcSmp_cofDertOvrCurtGen_f32_FQ = look1_iflf_binlcapw(rtb_Switch_iy, ((
    const real32_T *)&(CAL_TpcSmp_OvrCurtLimGenTableX_iDc_af32_FQ[0])), ((const
    real32_T *)&(CAL_TpcSmp_OvrCurtLimGenTableY_Cof_af32_FQ[0])), 4U);
  VAR_TpcSmp_GenPwrLinearDertOvrCurt_f32_FQ =
    VAR_TpcSmp_cofDertOvrCurtGen_f32_FQ * VAR_TpcMot_GenPwrRef_f32_FQ;
  if (CAL_TpcSmp_CurtModeSelc_b_FQ) {
    VAR_TpcSmp_GenPwrLimOvrCurt_f32_FQ = VAR_tpcsmp_GenPwrDert_f32_FQ;
  } else if (VAR_TpcSmp_GenPwrPIDertOvrCurt_f32_FQ >
             VAR_TpcSmp_GenPwrLinearDertOvrCurt_f32_FQ) {
    VAR_TpcSmp_GenPwrLimOvrCurt_f32_FQ = VAR_TpcSmp_GenPwrPIDertOvrCurt_f32_FQ;
  } else {
    VAR_TpcSmp_GenPwrLimOvrCurt_f32_FQ =
      VAR_TpcSmp_GenPwrLinearDertOvrCurt_f32_FQ;
  }

  if (TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ)) {
    rtb_Abs_ns = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Abs_ns = 0.0F;
  }

  rtb_Abs_ns = fabsf(rtb_Abs_ns);
  if (rtb_Abs_ns != 0.0F) {
    VAR_TpcCod_GenTrqCalcOvrCurt_f32_FQ = VAR_TpcSmp_GenPwrLimOvrCurt_f32_FQ *
      9550.0F / rtb_Abs_ns;
  } else {
    VAR_TpcCod_GenTrqCalcOvrCurt_f32_FQ = -GLB_Tpc_MaximumTorque_f32_FQ;
  }

  VAR_TpcSmp_flgLinearDertOveCurtGen_b_FQ = (1.0F -
    VAR_TpcSmp_cofDertOvrCurtGen_f32_FQ > 1.0E-6F);
  VAR_TpcSmp_flgPIDertOvrCurtGen_b_FQ = (rtb_Add7_l !=
    VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ);
  if (VAR_TpcSmp_flgLinearDertOveCurtGen_b_FQ ||
      VAR_TpcSmp_flgPIDertOvrCurtGen_b_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_n = (uint16_T)((uint32_T)
      !VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ +
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_n);
    if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_n >= 65535) {
      SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_n = MAX_uint16_T;
    }
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_n = 0U;
  }

  VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ = ((uint32_T)
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_n * CAL_TpcSmp_FacGenOvrCurt_u8_FQ >
    CAL_TpcSmp_CntGenOvrCurt_u8_FQ);
  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertOvrIdc_b_FQ = ((fabsf
      (VAR_TpcCod_ElecTrqCalcOvrCurt_f32_FQ - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ);
  } else {
    VAR_tpccod_flgMaxDertOvrIdc_b_FQ = ((fabsf(fabsf
      (VAR_TpcCod_GenTrqCalcOvrCurt_f32_FQ) - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ);
  }

  VAR_TpcSmp_ElecPwrLinearDertUdrVolt_f32_FQ =
    VAR_TpcSmp_cofDertUdrVoltElec_f32_FQ * VAR_TpcMot_ElecPwrRef_f32_FQ;
  if (VAR_TpcSmp_ElecPwrLinearDertUdrVolt_f32_FQ <
      VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ) {
    VAR_TpcSmp_ElecPwrLimUdrVolt_f32_FQ =
      VAR_TpcSmp_ElecPwrLinearDertUdrVolt_f32_FQ;
  } else {
    VAR_TpcSmp_ElecPwrLimUdrVolt_f32_FQ = VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ;
  }

  if (TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ)) {
    rtb_Abs_ns = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Abs_ns = 0.0F;
  }

  rtb_Abs_ns = fabsf(rtb_Abs_ns);
  if (rtb_Abs_ns != 0.0F) {
    VAR_TpcCod_ElecTrqCalcUdrVolt_f32_FQ = VAR_TpcSmp_ElecPwrLimUdrVolt_f32_FQ *
      9550.0F / rtb_Abs_ns;
  } else {
    VAR_TpcCod_ElecTrqCalcUdrVolt_f32_FQ = GLB_Tpc_MaximumTorque_f32_FQ;
  }

  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertUndrUdc_b_FQ = ((fabsf
      (VAR_TpcCod_ElecTrqCalcUdrVolt_f32_FQ - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ);
  } else {
    VAR_tpccod_flgMaxDertUndrUdc_b_FQ = false;
  }

  VAR_TpcSmp_GenPwrLinearDertOvrVolt_f32_FQ =
    VAR_TpcSmp_cofDertOvrVoltGen_f32_FQ * VAR_TpcMot_GenPwrRef_f32_FQ;
  VAR_TpcSmp_GenPwrPIDertOvrVolt_f32_FQ = -rtb_Switch2_b;
  if (VAR_TpcSmp_GenPwrLinearDertOvrVolt_f32_FQ >
      VAR_TpcSmp_GenPwrPIDertOvrVolt_f32_FQ) {
    VAR_TpcSmp_GenPwrLimOvrVolt_f32_FQ =
      VAR_TpcSmp_GenPwrLinearDertOvrVolt_f32_FQ;
  } else {
    VAR_TpcSmp_GenPwrLimOvrVolt_f32_FQ = VAR_TpcSmp_GenPwrPIDertOvrVolt_f32_FQ;
  }

  if (TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ)) {
    rtb_Abs_ns = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Abs_ns = 0.0F;
  }

  rtb_Switch2_b = fabsf(rtb_Abs_ns);
  if (rtb_Switch2_b != 0.0F) {
    VAR_TpcCod_GenTrqCalcOvrVolt_f32_FQ = VAR_TpcSmp_GenPwrLimOvrVolt_f32_FQ *
      9550.0F / rtb_Switch2_b;
  } else {
    VAR_TpcCod_GenTrqCalcOvrVolt_f32_FQ = -GLB_Tpc_MaximumTorque_f32_FQ;
  }

  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMaxDertOvrUdc_b_FQ = false;
  } else {
    VAR_tpccod_flgMaxDertOvrUdc_b_FQ = ((fabsf(fabsf
      (VAR_TpcCod_GenTrqCalcOvrVolt_f32_FQ) - rtb_tpccod_TrqMax) <= 0.001F) &&
      VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ);
  }

  VAR_tpccod_flgMaxDertCAN_b_FQ = (fabsf(VAR_TpcSmp_TrqMaxCanSet_f32_FQ -
    rtb_tpccod_TrqMax) <= 0.001F);
  if (VAR_tpccod_flgMaxDertExCTrq_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_ExCTrq;
  } else if (VAR_tpccod_flgMaxDertStrTemp_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_StrTemp;
  } else if (VAR_tpccod_flgMaxDertTempDBC_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_TempDBC;
  } else if (VAR_tpccod_flgMaxDertTCoolant_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_TCoolant;
  } else if (VAR_tpccod_flgMaxDertTDrvBoard_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_TDrvBoard;
  } else if (VAR_tpccod_flgMaxDertTIGBT_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_TempIGBT;
  } else if (VAR_tpccod_flgMaxDertMtrSpd_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_N;
  } else if (VAR_tpccod_flgMaxDertOvrIdc_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_OvrIdc;
  } else if (VAR_tpccod_flgMaxDertUndrUdc_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_UndrUdc;
  } else if (VAR_tpccod_flgMaxDertOvrUdc_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_OvrUdc;
  } else if (VAR_tpccod_flgMaxDertCAN_b_FQ) {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_CAN;
  } else {
    TPC_stTrqEmMax_FQ = (uint8_T)bDern_Inactive;
  }

  if (rtb_RelationalOperator3_pj) {
    VAR_tpccod_flgMinDertExCTrq_b_FQ = ((fabsf(rtb_tpccod_TrqMin -
      VAR_TpcMot_TrqGenExC_f32_FQ) <= 0.001F) && (*rtu_TDC_BUS_TDC_TrqDes <
      VAR_TpcMot_TrqGenExC_f32_FQ));
    VAR_tpccod_flgMinDertStrTemp_b_FQ = ((fabsf(VAR_TpcMot_GenTrqLimTsttr_f32_FQ
      - rtb_tpccod_TrqMin) <= 0.001F) && VAR_TpcMot_flgTrqLimTsttrActv_b_FQ);
    VAR_tpccod_flgMinDertTempDBC_b_FQ = ((fabsf(VAR_TpcTmp_GenTrqLimTdbc_f32_FQ
      - rtb_tpccod_TrqMin) <= 0.001F) && VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ);
    VAR_tpccod_flgMinDertTCoolant_b_FQ = ((fabsf
      (VAR_TpcTmp_GenTrqLimTcoolant_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ);
    VAR_tpccod_flgMinDertTDrvBoard_b_FQ = ((fabsf
      (VAR_TpcTmp_GenTrqLimTdrvboard_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ);
    VAR_tpccod_flgMinDertTIGBT_b_FQ = ((fabsf(VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ -
      rtb_tpccod_TrqMin) <= 0.001F) && VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ);
    VAR_tpccod_flgMinDertMtrSpd_b_FQ = ((fabsf(VAR_TpcSmp_GenTrqLimOvrSpd_f32_FQ
      - rtb_tpccod_TrqMin) <= 0.001F) && VAR_TpcSmp_flgGenTrqLimOvrSpdActv_b_FQ);
    VAR_tpccod_flgMinDertOvrIdc_b_FQ = ((fabsf
      (VAR_TpcCod_GenTrqCalcOvrCurt_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ);
    VAR_tpccod_flgMinDertUndrUdc_b_FQ = false;
    VAR_tpccod_flgMinDertOvrUdc_b_FQ = ((fabsf
      (VAR_TpcCod_GenTrqCalcOvrVolt_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ);
  } else {
    VAR_tpccod_flgMinDertExCTrq_b_FQ = ((fabsf(rtb_tpccod_TrqMin -
      (-VAR_TpcMot_TrqElecExC_f32_FQ)) <= 0.001F) && (*rtu_TDC_BUS_TDC_TrqDes <
      -VAR_TpcMot_TrqElecExC_f32_FQ));
    VAR_tpccod_flgMinDertStrTemp_b_FQ = (VAR_TpcMot_flgTrqLimTsttrActv_b_FQ &&
      (fabsf(-VAR_TpcMot_ElecTrqLimTsttr_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F));
    VAR_tpccod_flgMinDertTempDBC_b_FQ = (VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ &&
      (fabsf(-VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F));
    VAR_tpccod_flgMinDertTCoolant_b_FQ = (VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ &&
      (fabsf(-VAR_TpcTmp_ElecTrqLimTcoolant_f32_FQ - rtb_tpccod_TrqMin) <=
       0.001F));
    VAR_tpccod_flgMinDertTDrvBoard_b_FQ =
      (VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ && (fabsf
        (-VAR_TpcTmp_ElecTrqLimTdrvboard_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F));
    VAR_tpccod_flgMinDertTIGBT_b_FQ = (VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ &&
      (fabsf(-VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F));
    VAR_tpccod_flgMinDertMtrSpd_b_FQ = ((fabsf
      (-VAR_TpcSmp_ElecTrqLimOvrSpd_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcSmp_flgElecTrqLimOvrSpdActv_b_FQ);
    VAR_tpccod_flgMinDertOvrIdc_b_FQ = ((fabsf
      (-VAR_TpcCod_ElecTrqCalcOvrCurt_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ);
    VAR_tpccod_flgMinDertUndrUdc_b_FQ = ((fabsf
      (-VAR_TpcCod_ElecTrqCalcUdrVolt_f32_FQ - rtb_tpccod_TrqMin) <= 0.001F) &&
      VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ);
    VAR_tpccod_flgMinDertOvrUdc_b_FQ = false;
  }

  VAR_tpccod_flgMinDertCAN_b_FQ = (fabsf(VAR_TpcSmp_TrqMinCanSet_f32_FQ -
    rtb_tpccod_TrqMin) <= 0.001F);
  if (VAR_tpccod_flgMinDertExCTrq_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_ExCTrq;
  } else if (VAR_tpccod_flgMinDertStrTemp_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_StrTemp;
  } else if (VAR_tpccod_flgMinDertTempDBC_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_TempDBC;
  } else if (VAR_tpccod_flgMinDertTCoolant_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_TCoolant;
  } else if (VAR_tpccod_flgMinDertTDrvBoard_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_TDrvBoard;
  } else if (VAR_tpccod_flgMinDertTIGBT_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_TempIGBT;
  } else if (VAR_tpccod_flgMinDertMtrSpd_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_N;
  } else if (VAR_tpccod_flgMinDertOvrIdc_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_OvrIdc;
  } else if (VAR_tpccod_flgMinDertUndrUdc_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_UndrUdc;
  } else if (VAR_tpccod_flgMinDertOvrUdc_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_OvrUdc;
  } else if (VAR_tpccod_flgMinDertCAN_b_FQ) {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_CAN;
  } else {
    TPC_stTrqEmMin_FQ = (uint8_T)bDern_Inactive;
  }

  TPC_TDbcTrqMax_FQ = VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ;
  TPC_bDernElecOvrIdc_FQ = (rtb_RelationalOperator_mt &&
    VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ);
  TPC_bDernGenOvrIdc_FQ = (rtb_RelationalOperator_mt &&
    VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ);
  TPC_bDernOvrIdc_FQ = (TPC_bDernElecOvrIdc_FQ || TPC_bDernGenOvrIdc_FQ);
  TPC_bDernIGBTTemp_FQ = VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ;
  *rty_TPC_BUS_TPC_TrqMax = TPC_TrqMax_FQ;
  *rty_TPC_BUS_TPC_bDernUndrUdc = TPC_bDernUndrUdc_FQ;
  *rty_TPC_BUS_TPC_bDernOvrUdc = TPC_bDernOvrUdc_FQ;
  *rty_TPC_BUS_TPC_bDernCAN = TPC_bDernCAN_FQ;
  *rty_TPC_BUS_TPC_stTrqEmMax = TPC_stTrqEmMax_FQ;
  *rty_TPC_BUS_TPC_stTrqEmMin = TPC_stTrqEmMin_FQ;
  *rty_TPC_BUS_TPC_stMotorMod = TPC_stMotorMod_FQ;
  *rty_TPC_BUS_TPC_TDbcTrqMax = TPC_TDbcTrqMax_FQ;
  *rty_TPC_BUS_TPC_SgnRotDir = TPC_SgnRotDir_FQ;
  *rty_TPC_BUS_TPC_SgnTrqMechDir = TPC_SgnTrqMechDir_FQ;
  *rty_TPC_BUS_TPC_bDernElecOvrIdc = TPC_bDernElecOvrIdc_FQ;
  *rty_TPC_BUS_TPC_TrqMin = TPC_TrqMin_FQ;
  *rty_TPC_BUS_TPC_bDernGenOvrIdc = TPC_bDernGenOvrIdc_FQ;
  *rty_TPC_BUS_TPC_bDernOvrIdc = TPC_bDernOvrIdc_FQ;
  *rty_TPC_BUS_TPC_TrqMaxTrans = TPC_TrqMaxTrans_FQ;
  *rty_TPC_BUS_TPC_TrqMinTrans = TPC_TrqMinTrans_FQ;
  *rty_TPC_BUS_TPC_bDernIGBTTemp = TPC_bDernIGBTTemp_FQ;
  *rty_TPC_BUS_TPC_bDernExcMax = TPC_bDernExcMax_FQ;
  *rty_TPC_BUS_TPC_bDernExcMin = TPC_bDernExcMin_FQ;
  *rty_TPC_BUS_TPC_bDernStrTemp = TPC_bDernStrTemp_FQ;
  *rty_TPC_BUS_TPC_bDernDbcTemp = TPC_bDernDbcTemp_FQ;
  *rty_TPC_BUS_TPC_bDernCoolantTem = TPC_bDernCoolantTemp_FQ;
  *rty_TPC_BUS_TPC_bDernDrvBoardTe = TPC_bDernDrvBoardTemp_FQ;
  *rty_TPC_BUS_TPC_bDernMtrSpd = TPC_bDernMtrSpd_FQ;
  rtb_Switch2_b = look2_iflf_binlcapw(*rtu_HSPF_BUS_HSPF_nSlowFlt,
    *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, ((const real32_T *)
    &(CAL_TpcCod_CoolFlow2LTableY_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcCod_CoolFlow2LTableX_Udc_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcCod_CoolFlow2LTableZ_Trq_af32_FQ[0])), rtCP_CoolantFlow2L_maxIndex,
    8U);
  rtb_tpccod_TrqMax = look2_iflf_binlcapw(*rtu_HSPF_BUS_HSPF_nSlowFlt,
    *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, ((const real32_T *)
    &(CAL_TpcCod_CoolFlow4LTableY_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcCod_CoolFlow4LTableX_Udc_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcCod_CoolFlow4LTableZ_Trq_af32_FQ[0])), rtCP_CoolantFlow4L_maxIndex,
    8U);
  rtb_tpccod_TrqMin = look2_iflf_binlcapw(*rtu_HSPF_BUS_HSPF_nSlowFlt,
    *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, ((const real32_T *)
    &(CAL_TpcCod_CoolFlow6LTableY_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcCod_CoolFlow6LTableX_Udc_af32_FQ[0])), ((const real32_T *)
    &(CAL_TpcCod_CoolFlow6LTableZ_Trq_af32_FQ[0])), rtCP_CoolantFlow6L_maxIndex,
    8U);
  rtb_RelationalOperator_mt = (CAL_TpcCod_MotorStallWarn_b_FQ ||
    CAL_TpcCod_MotorSampErr_b_FQ || CAL_TpcCod_IGBTSampErr_b_FQ);
  VAR_TpcCod_PowerAdd_f32_FQ = *rtu_TDC_BUS_TDC_TrqDes -
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_i;
  VAR_TpcCod_PowerIncreaseRate_f32_FQ = (((((((((VAR_TpcCod_PowerAdd_f32_FQ +
    SWC_TPC_IG_FQ_DW.Delay1_DSTATE) + SWC_TPC_IG_FQ_DW.Delay10_DSTATE[0]) +
    SWC_TPC_IG_FQ_DW.Delay9_DSTATE[0]) + SWC_TPC_IG_FQ_DW.Delay7_DSTATE[0]) +
    SWC_TPC_IG_FQ_DW.Delay6_DSTATE[0]) + SWC_TPC_IG_FQ_DW.Delay5_DSTATE[0]) +
    SWC_TPC_IG_FQ_DW.Delay4_DSTATE[0]) + SWC_TPC_IG_FQ_DW.Delay3_DSTATE[0]) +
    SWC_TPC_IG_FQ_DW.Delay2_DSTATE[0]) / 10.0F;
  if (SWC_TPC_IG_FQ_DW.is_active_c23_SWC_TPC_IG_FQ == 0U) {
    SWC_TPC_IG_FQ_DW.is_active_c23_SWC_TPC_IG_FQ = 1U;
    SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw2L;
    VAR_TpcCod_CoolantFlowReq_f32_FQ = 2.0F;
  } else {
    guard1 = false;
    guard2 = false;
    switch (SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ) {
     case SWC_TPC_IG_FQ_IN_CoolantFolw2L:
      if (rtb_RelationalOperator_mt || (VAR_TpcCod_PowerIncreaseRate_f32_FQ >=
           CAL_TpcCod_PowIncRatLim_f32_FQ)) {
        SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw8L;
        VAR_TpcCod_CoolantFlowReq_f32_FQ = 8.0F;
        SWC_TPC_IG_FQ_DW.Cnt6L = 0U;
      } else {
        if (*rtu_TDC_BUS_TDC_TrqDes >= rtb_Switch2_b) {
          SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw4L;
          VAR_TpcCod_CoolantFlowReq_f32_FQ = 4.0F;
          SWC_TPC_IG_FQ_DW.Cnt2L = 0U;
        }
      }
      break;

     case SWC_TPC_IG_FQ_IN_CoolantFolw4L:
      if (rtb_RelationalOperator_mt || (VAR_TpcCod_PowerIncreaseRate_f32_FQ >=
           CAL_TpcCod_PowIncRatLim_f32_FQ)) {
        SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw8L;
        VAR_TpcCod_CoolantFlowReq_f32_FQ = 8.0F;
        SWC_TPC_IG_FQ_DW.Cnt6L = 0U;
      } else if (*rtu_TDC_BUS_TDC_TrqDes < rtb_Switch2_b -
                 CAL_TpcCod_TrqRelay_f32_FQ) {
        idxDelay = SWC_TPC_IG_FQ_DW.Cnt2L + 1;
        if (SWC_TPC_IG_FQ_DW.Cnt2L + 1 > 65535) {
          idxDelay = 65535;
        }

        SWC_TPC_IG_FQ_DW.Cnt2L = (uint16_T)idxDelay;
        if (SWC_TPC_IG_FQ_DW.Cnt2L > CAL_TpcCod_CntHysteresislop_u16_FQ) {
          SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw2L;
          VAR_TpcCod_CoolantFlowReq_f32_FQ = 2.0F;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      break;

     case SWC_TPC_IG_FQ_IN_CoolantFolw6L:
      if (*rtu_TDC_BUS_TDC_TrqDes < rtb_tpccod_TrqMax -
          CAL_TpcCod_TrqRelay_f32_FQ) {
        idxDelay = SWC_TPC_IG_FQ_DW.Cnt4L + 1;
        if (SWC_TPC_IG_FQ_DW.Cnt4L + 1 > 65535) {
          idxDelay = 65535;
        }

        SWC_TPC_IG_FQ_DW.Cnt4L = (uint16_T)idxDelay;
        if (SWC_TPC_IG_FQ_DW.Cnt4L > CAL_TpcCod_CntHysteresislop_u16_FQ) {
          SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw4L;
          VAR_TpcCod_CoolantFlowReq_f32_FQ = 4.0F;
          SWC_TPC_IG_FQ_DW.Cnt2L = 0U;
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }
      break;

     default:
      if ((*rtu_TDC_BUS_TDC_TrqDes < rtb_tpccod_TrqMin -
           CAL_TpcCod_TrqRelay_f32_FQ) && (!rtb_RelationalOperator_mt)) {
        idxDelay = SWC_TPC_IG_FQ_DW.Cnt6L + 1;
        if (SWC_TPC_IG_FQ_DW.Cnt6L + 1 > 65535) {
          idxDelay = 65535;
        }

        SWC_TPC_IG_FQ_DW.Cnt6L = (uint16_T)idxDelay;
        if (SWC_TPC_IG_FQ_DW.Cnt6L > CAL_TpcCod_CntHysteresislop_u16_FQ) {
          SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw6L;
          VAR_TpcCod_CoolantFlowReq_f32_FQ = 6.0F;
          SWC_TPC_IG_FQ_DW.Cnt4L = 0U;
        }
      }
      break;
    }

    if (guard2) {
      if ((*rtu_TDC_BUS_TDC_TrqDes >= rtb_tpccod_TrqMin) ||
          rtb_RelationalOperator_mt || (VAR_TpcCod_PowerIncreaseRate_f32_FQ >=
           CAL_TpcCod_PowIncRatLim_f32_FQ)) {
        SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw8L;
        VAR_TpcCod_CoolantFlowReq_f32_FQ = 8.0F;
        SWC_TPC_IG_FQ_DW.Cnt6L = 0U;
      }
    }

    if (guard1) {
      if (*rtu_TDC_BUS_TDC_TrqDes >= rtb_tpccod_TrqMax) {
        SWC_TPC_IG_FQ_DW.is_c23_SWC_TPC_IG_FQ = SWC_TPC_IG_FQ_IN_CoolantFolw6L;
        VAR_TpcCod_CoolantFlowReq_f32_FQ = 6.0F;
        SWC_TPC_IG_FQ_DW.Cnt4L = 0U;
      }
    }
  }

  if (*rtu_HSPF_BUS_HSPF_tDBCTempUFlt <= *rtu_HSPF_BUS_HSPF_tDBCTempVFlt) {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_tDBCTempUFlt;
  } else {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_tDBCTempVFlt;
  }

  if (!(rtb_Switch_iy <= *rtu_HSPF_BUS_HSPF_tDBCTempWFlt)) {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_tDBCTempWFlt;
  }

  if (rtb_Switch_iy <= CAL_TpcCod_NTCLowTemp_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_jm = true;
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_jm = ((!(rtb_Switch_iy >=
      CAL_TpcCod_NTCHighTemp_f32_FQ)) && SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_jm);
  }

  if (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_jm) {
    VAR_TpcCod_CoolantFlowFinReq_f32_FQ = CAL_TpcCod_CoolFlow1LReq_f32_FQ;
  } else {
    VAR_TpcCod_CoolantFlowFinReq_f32_FQ = VAR_TpcCod_CoolantFlowReq_f32_FQ;
  }

  VAR_TpcFuv_FimTrqLimLv1_b_FQ = false;
  VAR_TpcFuv_FimTrqLimLv2_b_FQ = false;
  VAR_TpcFuv_FimTrqLimLv3_b_FQ = false;
  VAR_TpcFuv_FimTrqLimLv4_b_FQ = false;
  if (VAR_TpcFuv_FimTrqLimLv4_b_FQ) {
    VAR_TpcFuv_ElecTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv4_f32_FQ *
      VAR_TpcMot_ElecTrqRef_f32_FQ;
    VAR_TpcFuv_GenTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv4_f32_FQ *
      VAR_TpcMot_GenTrqRef_f32_FQ;
  } else if (VAR_TpcFuv_FimTrqLimLv3_b_FQ) {
    VAR_TpcFuv_ElecTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv3_f32_FQ *
      VAR_TpcMot_ElecTrqRef_f32_FQ;
    VAR_TpcFuv_GenTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv3_f32_FQ *
      VAR_TpcMot_GenTrqRef_f32_FQ;
  } else if (VAR_TpcFuv_FimTrqLimLv2_b_FQ) {
    VAR_TpcFuv_ElecTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv2_f32_FQ *
      VAR_TpcMot_ElecTrqRef_f32_FQ;
    VAR_TpcFuv_GenTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv2_f32_FQ *
      VAR_TpcMot_GenTrqRef_f32_FQ;
  } else if (VAR_TpcFuv_FimTrqLimLv1_b_FQ) {
    VAR_TpcFuv_ElecTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv1_f32_FQ *
      VAR_TpcMot_ElecTrqRef_f32_FQ;
    VAR_TpcFuv_GenTrqLimDiag_f32_FQ = CAL_TpcFuv_CofTrqLimLv1_f32_FQ *
      VAR_TpcMot_GenTrqRef_f32_FQ;
  } else {
    VAR_TpcFuv_ElecTrqLimDiag_f32_FQ = VAR_TpcMot_ElecTrqRef_f32_FQ;
    VAR_TpcFuv_GenTrqLimDiag_f32_FQ = VAR_TpcMot_GenTrqRef_f32_FQ;
  }

  VAR_TpcFuv_FimPwrLimLv1_b_FQ = false;
  VAR_TpcFuv_FimPwrLimLv2_b_FQ = false;
  VAR_TpcFuv_FimPwrLimLv3_b_FQ = false;
  VAR_TpcFuv_FimPwrLimLv4_b_FQ = false;
  if (VAR_TpcFuv_FimPwrLimLv4_b_FQ) {
    VAR_TpcFuv_ElecPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv4_f32_FQ *
      VAR_TpcMot_ElecPwrRef_f32_FQ;
    VAR_TpcFuv_GenPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv4_f32_FQ *
      VAR_TpcMot_GenPwrRef_f32_FQ;
  } else if (VAR_TpcFuv_FimPwrLimLv3_b_FQ) {
    VAR_TpcFuv_ElecPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv3_f32_FQ *
      VAR_TpcMot_ElecPwrRef_f32_FQ;
    VAR_TpcFuv_GenPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv3_f32_FQ *
      VAR_TpcMot_GenPwrRef_f32_FQ;
  } else if (VAR_TpcFuv_FimPwrLimLv2_b_FQ) {
    VAR_TpcFuv_ElecPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv2_f32_FQ *
      VAR_TpcMot_ElecPwrRef_f32_FQ;
    VAR_TpcFuv_GenPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv2_f32_FQ *
      VAR_TpcMot_GenPwrRef_f32_FQ;
  } else if (VAR_TpcFuv_FimPwrLimLv1_b_FQ) {
    VAR_TpcFuv_ElecPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv1_f32_FQ *
      VAR_TpcMot_ElecPwrRef_f32_FQ;
    VAR_TpcFuv_GenPwrLimDiag_f32_FQ = CAL_TpcFuv_CofPwrLimLv1_f32_FQ *
      VAR_TpcMot_GenPwrRef_f32_FQ;
  } else {
    VAR_TpcFuv_ElecPwrLimDiag_f32_FQ = VAR_TpcMot_ElecPwrRef_f32_FQ;
    VAR_TpcFuv_GenPwrLimDiag_f32_FQ = VAR_TpcMot_GenPwrRef_f32_FQ;
  }

  if (TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ)) {
    rtb_Abs_ns = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Abs_ns = 0.0F;
  }

  rtb_Switch2_b = fabsf(rtb_Abs_ns);
  if (rtb_Switch2_b != 0.0F) {
    VAR_TpcCod_ElecTrqCalcDiag_f32_FQ = VAR_TpcFuv_ElecPwrLimDiag_f32_FQ *
      9550.0F / rtb_Switch2_b;
  } else {
    VAR_TpcCod_ElecTrqCalcDiag_f32_FQ = GLB_Tpc_MaximumTorque_f32_FQ;
  }

  if (TPC_SgnRotDir_FQ != ((uint8_T)GLB_TpcCod_MotorStop_u8_FQ)) {
    rtb_Abs_ns = *rtu_HSPF_BUS_HSPF_nSlowFlt;
  } else {
    rtb_Abs_ns = 0.0F;
  }

  rtb_Switch2_b = fabsf(rtb_Abs_ns);
  if (rtb_Switch2_b != 0.0F) {
    VAR_TpcCod_GenTrqCalcDiag_f32_FQ = VAR_TpcFuv_GenPwrLimDiag_f32_FQ * 9550.0F
      / rtb_Switch2_b;
  } else {
    VAR_TpcCod_GenTrqCalcDiag_f32_FQ = -GLB_Tpc_MaximumTorque_f32_FQ;
  }

  VAR_TpcSmp_iDcLnkOvcWarnState_u8_FQ = (uint8_T)
    ((VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ ||
      VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ) + 2U);
  if (rtb_Switch_dc >= 0.0F) {
    if (0.0F - rtb_Abs1_p >= 0.0F) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g = 0.0F - rtb_Abs1_p;
    } else {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g = 0.0F;
    }
  } else {
    if (rtb_Switch_dc <= -VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ) {
      SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g = -VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ
        - rtb_Abs1_p;
      if (!(SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g <= 0.0F)) {
        SWC_TPC_IG_FQ_DW.UnitDelay1_DSTATE_g = 0.0F;
      }
    }
  }

  rtb_Switch_iy = -VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ -
    VAR_tpcsmp_KpProductSau_f32_FQ;
  if (rtb_Switch_iy <= 0.0F) {
    VAR_tpcsmp_negOutputjudge_f32_FQ = rtb_Switch_iy;
  } else {
    VAR_tpcsmp_negOutputjudge_f32_FQ = 0.0F;
  }

  if (0.0F - VAR_tpcsmp_KpProductSau_f32_FQ >= 0.0F) {
    VAR_tpcsmp_posOutputjudge_f32_FQ = 0.0F - VAR_tpcsmp_KpProductSau_f32_FQ;
  } else {
    VAR_tpcsmp_posOutputjudge_f32_FQ = 0.0F;
  }

  if (VAR_tpcsmp_PIOutput_f32_FQ >= 0.0F) {
    VAR_tpcsmp_yi_f32_FQ = VAR_tpcsmp_posOutputjudge_f32_FQ;
  } else if (VAR_tpcsmp_PIOutput_f32_FQ <= -VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ)
  {
    VAR_tpcsmp_yi_f32_FQ = VAR_tpcsmp_negOutputjudge_f32_FQ;
  } else {
    VAR_tpcsmp_yi_f32_FQ = VAR_tpcsmp_KiProductSum_f32_FQ;
  }

  VAR_TpcTmp_TIGBTOvHiWarnState_u8_FQ = (uint8_T)
    (VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ + 2U);
  VAR_TpcTmp_TIGBTOvLoWarnState_u8_FQ = (uint8_T)
    ((VAR_TpcTmp_tIGBTTempFlt_f32_FQ <= CAL_TpcTmp_tIGBTTempLoLim_f32_FQ) + 2U);
  VAR_TpcTmp_TIGBTOvHiErrState_u8_FQ = (uint8_T)((VAR_TpcTmp_tIGBTTempFlt_f32_FQ
    >= CAL_TpcTmp_tIGBTTempHiLim_f32_FQ) + 2U);
  VAR_TpcSmp_uDcLnkUnvWarnState_u8_FQ = (uint8_T)
    (VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ + 2U);
  if (rtb_Add3_a >= VAR_TpcMot_ElecPwrRef_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om = VAR_TpcMot_ElecPwrRef_f32_FQ -
      rtb_Subtract_fv;
    if (!(SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om >= 0.0F)) {
      SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om = 0.0F;
    }
  } else {
    if (rtb_Add3_a <= 0.0F) {
      if (0.0F - rtb_Subtract_fv <= 0.0F) {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om = 0.0F - rtb_Subtract_fv;
      } else {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_om = 0.0F;
      }
    }
  }

  SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_fi = ((*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt <=
    CAL_TpcSmp_uDcLnkUnVLim_f32_FQ) || SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_fi);
  VAR_TpcSmp_uDcLnkUnVLimErrState_u8_FQ = (uint8_T)
    (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_fi + 2U);
  VAR_TpcTmp_TDrvBoardOvHiWarnState_u8_FQ = (uint8_T)
    (VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ + 2U);
  VAR_TpcTmp_TCoolantOvHiWarnState_u8_FQ = (uint8_T)
    (VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ + 2U);
  VAR_TpcTmp_TDbcOvHiWarnState_u8_FQ = (uint8_T)
    (VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ + 2U);
  VAR_TpcMot_TSttrOvHiWarnState_u8_FQ = (uint8_T)
    (VAR_TpcMot_flgTrqLimTsttrActv_b_FQ + 2U);
  VAR_TpcMot_TSttrOvHiLimErrState_u8_FQ = (uint8_T)
    ((VAR_TpcMot_tSttrTempFlt_f32_FQ >= CAL_TpcMot_tSttrHiLim_f32_FQ) + 2U);
  VAR_TpcMot_TSttrOvLoWarnState_u8_FQ = (uint8_T)
    ((VAR_TpcMot_tSttrTempFlt_f32_FQ <= CAL_TpcMot_tSttrLoLim_f32_FQ) + 2U);
  VAR_TpcSmp_uDcLnkOvWarnState_u8_FQ = (uint8_T)
    (VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ + 2U);
  if (rtb_DataTypeConversion1 >= -VAR_TpcMot_GenPwrRef_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e = -VAR_TpcMot_GenPwrRef_f32_FQ -
      rtb_Product1;
    if (!(SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e >= 0.0F)) {
      SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e = 0.0F;
    }
  } else {
    if (rtb_DataTypeConversion1 <= 0.0F) {
      if (0.0F - rtb_Product1 <= 0.0F) {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e = 0.0F - rtb_Product1;
      } else {
        SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_e = 0.0F;
      }
    }
  }

  VAR_TpcSmp_iDcLnkOvCLimErrState_u8_FQ = (uint8_T)
    (((*rtu_HSPF_BUS_HSPF_iDcLnkEstFlt >= CAL_TpcSmp_iDcLnkOvCElecLim_f32_FQ) ||
      (*rtu_HSPF_BUS_HSPF_iDcLnkEstFlt <= CAL_TpcSmp_iDcLnkOvCGenLim_f32_FQ)) +
     2U);
  VAR_TpcSmp_uDcLnkOvVLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt >= CAL_TpcSmp_uDcLnkOvVLim_f32_FQ) + 2U);
  if (rtb_Switch_lt_tmp > CAL_TpcSmp_OvSpdWarnHiLim_f32_FQ) {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_h = true;
  } else {
    SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_h = ((!(rtb_Switch_lt_tmp <
      CAL_TpcSmp_OvSpdWarnLoLim_f32_FQ)) && SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_h);
  }

  VAR_TpcSmp_SpdOvHiWarnState_u8_FQ = (uint8_T)
    (SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_h + 2U);
  VAR_TpcSmp_SpdOvHiLimErrState_u8_FQ = (uint8_T)((rtb_Switch_lt_tmp >=
    CAL_TpcSmp_ThresOverSpd_f32_FQ) + 2U);
  if (*rtu_HSPF_BUS_HSPF_tDBCTempUFlt <= *rtu_HSPF_BUS_HSPF_tDBCTempVFlt) {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_tDBCTempUFlt;
  } else {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_tDBCTempVFlt;
  }

  if (!(rtb_Switch_iy <= *rtu_HSPF_BUS_HSPF_tDBCTempWFlt)) {
    rtb_Switch_iy = *rtu_HSPF_BUS_HSPF_tDBCTempWFlt;
  }

  VAR_TpcTmp_TDbcOvLoWarnState_u8_FQ = (uint8_T)((rtb_Switch_iy <=
    CAL_TpcTmp_tDbcThrPhLoLim_f32_FQ) + 2U);
  VAR_TpcTmp_TDbcUHiLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_tDBCTempUFlt >= CAL_TpcTmp_tDbcTempUHiLim_f32_FQ) + 2U);
  VAR_TpcTmp_TDbcULoLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_tDBCTempUFlt <= CAL_TpcTmp_tDbcTempULoLim_f32_FQ) + 2U);
  VAR_TpcTmp_TDbcVHiLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_tDBCTempVFlt >= CAL_TpcTmp_tDbcTempVHiLim_f32_FQ) + 2U);
  VAR_TpcTmp_TDbcVLoLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_tDBCTempVFlt <= CAL_TpcTmp_tDbcTempVLoLim_f32_FQ) + 2U);
  VAR_TpcTmp_TDbcWHiLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_tDBCTempWFlt >= CAL_TpcTmp_tDbcTempWHiLim_f32_FQ) + 2U);
  VAR_TpcTmp_TDbcWLoLimErrState_u8_FQ = (uint8_T)
    ((*rtu_HSPF_BUS_HSPF_tDBCTempWFlt <= CAL_TpcTmp_tDbcTempWLoLim_f32_FQ) + 2U);
  *rty_DEM_BUS = 0.0F;
  SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_b = true;
  SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_ae = true;
  SWC_TPC_IG_FQ_DW.UnitDelay3_DSTATE = VAR_Tpcblk_TrqLim01_f32_FQ;
  SWC_TPC_IG_FQ_DW.UnitDelay2_DSTATE_o = VAR_Tpcblk_TrqLim_f32_FQ;
  SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_p = true;
  SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_bz = true;
  SWC_TPC_IG_FQ_DW.UnitDelay_DSTATE_i = *rtu_TDC_BUS_TDC_TrqDes;
  SWC_TPC_IG_FQ_DW.Delay1_DSTATE = VAR_TpcCod_PowerAdd_f32_FQ;
  SWC_TPC_IG_FQ_DW.Delay10_DSTATE[0] = SWC_TPC_IG_FQ_DW.Delay10_DSTATE[1];
  SWC_TPC_IG_FQ_DW.Delay10_DSTATE[1] = VAR_TpcCod_PowerAdd_f32_FQ;
  SWC_TPC_IG_FQ_DW.Delay9_DSTATE[0] = SWC_TPC_IG_FQ_DW.Delay9_DSTATE[1];
  SWC_TPC_IG_FQ_DW.Delay9_DSTATE[1] = SWC_TPC_IG_FQ_DW.Delay9_DSTATE[2];
  SWC_TPC_IG_FQ_DW.Delay9_DSTATE[2] = VAR_TpcCod_PowerAdd_f32_FQ;
  SWC_TPC_IG_FQ_DW.Delay7_DSTATE[0] = SWC_TPC_IG_FQ_DW.Delay7_DSTATE[1];
  SWC_TPC_IG_FQ_DW.Delay7_DSTATE[1] = SWC_TPC_IG_FQ_DW.Delay7_DSTATE[2];
  SWC_TPC_IG_FQ_DW.Delay7_DSTATE[2] = SWC_TPC_IG_FQ_DW.Delay7_DSTATE[3];
  SWC_TPC_IG_FQ_DW.Delay7_DSTATE[3] = VAR_TpcCod_PowerAdd_f32_FQ;
  SWC_TPC_IG_FQ_DW.Delay6_DSTATE[0] = SWC_TPC_IG_FQ_DW.Delay6_DSTATE[1];
  SWC_TPC_IG_FQ_DW.Delay6_DSTATE[1] = SWC_TPC_IG_FQ_DW.Delay6_DSTATE[2];
  SWC_TPC_IG_FQ_DW.Delay6_DSTATE[2] = SWC_TPC_IG_FQ_DW.Delay6_DSTATE[3];
  SWC_TPC_IG_FQ_DW.Delay6_DSTATE[3] = SWC_TPC_IG_FQ_DW.Delay6_DSTATE[4];
  SWC_TPC_IG_FQ_DW.Delay6_DSTATE[4] = VAR_TpcCod_PowerAdd_f32_FQ;
  for (idxDelay = 0; idxDelay < 5; idxDelay++) {
    SWC_TPC_IG_FQ_DW.Delay5_DSTATE[idxDelay] =
      SWC_TPC_IG_FQ_DW.Delay5_DSTATE[idxDelay + 1];
  }

  SWC_TPC_IG_FQ_DW.Delay5_DSTATE[5] = VAR_TpcCod_PowerAdd_f32_FQ;
  for (idxDelay = 0; idxDelay < 6; idxDelay++) {
    SWC_TPC_IG_FQ_DW.Delay4_DSTATE[idxDelay] =
      SWC_TPC_IG_FQ_DW.Delay4_DSTATE[idxDelay + 1];
  }

  SWC_TPC_IG_FQ_DW.Delay4_DSTATE[6] = VAR_TpcCod_PowerAdd_f32_FQ;
  for (idxDelay = 0; idxDelay < 7; idxDelay++) {
    SWC_TPC_IG_FQ_DW.Delay3_DSTATE[idxDelay] =
      SWC_TPC_IG_FQ_DW.Delay3_DSTATE[idxDelay + 1];
  }

  SWC_TPC_IG_FQ_DW.Delay3_DSTATE[7] = VAR_TpcCod_PowerAdd_f32_FQ;
  for (idxDelay = 0; idxDelay < 8; idxDelay++) {
    SWC_TPC_IG_FQ_DW.Delay2_DSTATE[idxDelay] =
      SWC_TPC_IG_FQ_DW.Delay2_DSTATE[idxDelay + 1];
  }

  SWC_TPC_IG_FQ_DW.Delay2_DSTATE[8] = VAR_TpcCod_PowerAdd_f32_FQ;
}

void SWC_TPC_IG_FQ_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_TPC_IG_FQ_T *const SWC_TPC_IG_FQ_M = &(SWC_TPC_IG_FQ_MdlrefDW.rtm);
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetErrorStatusPointer(SWC_TPC_IG_FQ_M, rt_errorStatus);
}
