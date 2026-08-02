#ifndef RTW_HEADER_SWC_TPC_IG_FQ_h_
#define RTW_HEADER_SWC_TPC_IG_FQ_h_
#include <math.h>
#ifndef SWC_TPC_IG_FQ_COMMON_INCLUDES_
#define SWC_TPC_IG_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_TPC_IG_FQ_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

#define GLB_TpcCod_BwELect_u8_FQ       3U
#define GLB_TpcCod_BwGene_u8_FQ        2U
#define GLB_TpcCod_FwELect_u8_FQ       1U
#define GLB_TpcCod_FwGene_u8_FQ        4U
#define GLB_TpcCod_MotorBw_u8_FQ       2U
#define GLB_TpcCod_MotorFw_u8_FQ       1U
#define GLB_TpcCod_MotorStop_u8_FQ     0U
#define GLB_TpcCod_NegvTrq_u8_FQ       2U
#define GLB_TpcCod_PosvTrq_u8_FQ       1U
#define GLB_TpcCod_ZeroTrq_u8_FQ       0U
#define GLB_Tpc_MaximumPower_f32_FQ    150.0F
#define GLB_Tpc_MaximumTorque_f32_FQ   310.0F

#ifndef SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay2_DSTATE;
  real32_T UnitDelay2_DSTATE_e;
  real32_T UnitDelay2_DSTATE_l;
  real32_T UnitDelay3_DSTATE;
  real32_T UnitDelay2_DSTATE_o;
  real32_T UnitDelay_DSTATE;
  real32_T UnitDelay_DSTATE_a;
  real32_T UnitDelay1_DSTATE;
  real32_T UnitDelay2_DSTATE_b;
  real32_T UnitDelay_DSTATE_d;
  real32_T UnitDelay2_DSTATE_m;
  real32_T UnitDelay_DSTATE_e;
  real32_T UnitDelay1_DSTATE_f;
  real32_T UnitDelay2_DSTATE_h;
  real32_T UnitDelay_DSTATE_c;
  real32_T UnitDelay1_DSTATE_h;
  real32_T UnitDelay2_DSTATE_bi;
  real32_T UnitDelay_DSTATE_f;
  real32_T UnitDelay1_DSTATE_m;
  real32_T UnitDelay2_DSTATE_d;
  real32_T UnitDelay_DSTATE_k;
  real32_T UnitDelay2_DSTATE_om;
  real32_T UnitDelay2_DSTATE_d1;
  real32_T UnitDelay2_DSTATE_ez;
  real32_T UnitDelay2_DSTATE_j;
  real32_T UnitDelay2_DSTATE_ji;
  real32_T UnitDelay1_DSTATE_d;
  real32_T UnitDelay1_DSTATE_fk;
  real32_T UnitDelay2_DSTATE_er;
  real32_T UnitDelay2_DSTATE_g;
  real32_T UnitDelay_DSTATE_fd;
  real32_T UnitDelay_DSTATE_g;
  real32_T UnitDelay2_DSTATE_f;
  real32_T UnitDelay2_DSTATE_mh;
  real32_T UnitDelay_DSTATE_l;
  real32_T UnitDelay1_DSTATE_g;
  real32_T UnitDelay_DSTATE_i;
  real32_T Delay1_DSTATE;
  real32_T Delay10_DSTATE[2];
  real32_T Delay9_DSTATE[3];
  real32_T Delay7_DSTATE[4];
  real32_T Delay6_DSTATE[5];
  real32_T Delay5_DSTATE[6];
  real32_T Delay4_DSTATE[7];
  real32_T Delay3_DSTATE[8];
  real32_T Delay2_DSTATE[9];
  real32_T Is_Sum;
  int16_T UnitDelay2_DSTATE_ew;
  int16_T UnitDelay2_DSTATE_i;
  int16_T UnitDelay2_DSTATE_mv;
  int16_T UnitDelay2_DSTATE_d2;
  int16_T UnitDelay2_DSTATE_m1;
  int16_T UnitDelay2_DSTATE_c;
  uint16_T UnitDelay_DSTATE_gq;
  uint16_T UnitDelay_DSTATE_e0;
  uint16_T UnitDelay_DSTATE_kw;
  uint16_T UnitDelay_DSTATE_n;
  uint16_T Cnt2L;
  uint16_T Cnt4L;
  uint16_T Cnt6L;
  boolean_T UnitDelay_DSTATE_b;
  boolean_T UnitDelay1_DSTATE_p;
  boolean_T UnitDelay_DSTATE_ae;
  boolean_T UnitDelay_DSTATE_j;
  boolean_T UnitDelay_DSTATE_p;
  boolean_T UnitDelay_DSTATE_bz;
  boolean_T UnitDelay1_DSTATE_c;
  boolean_T UnitDelay1_DSTATE_l;
  boolean_T UnitDelay1_DSTATE_d5;
  boolean_T UnitDelay_DSTATE_jm;
  boolean_T UnitDelay_DSTATE_fi;
  boolean_T UnitDelay_DSTATE_h;
  uint8_T is_active_c46_SWC_TPC_IG_FQ;
  uint8_T is_c46_SWC_TPC_IG_FQ;
  uint8_T is_active_c44_SWC_TPC_IG_FQ;
  uint8_T is_c44_SWC_TPC_IG_FQ;
  uint8_T is_active_c42_SWC_TPC_IG_FQ;
  uint8_T is_c42_SWC_TPC_IG_FQ;
  uint8_T is_active_c40_SWC_TPC_IG_FQ;
  uint8_T is_c40_SWC_TPC_IG_FQ;
  uint8_T is_active_c38_SWC_TPC_IG_FQ;
  uint8_T is_c38_SWC_TPC_IG_FQ;
  uint8_T is_active_c36_SWC_TPC_IG_FQ;
  uint8_T is_c36_SWC_TPC_IG_FQ;
  uint8_T is_active_c34_SWC_TPC_IG_FQ;
  uint8_T is_c34_SWC_TPC_IG_FQ;
  uint8_T is_active_c23_SWC_TPC_IG_FQ;
  uint8_T is_c23_SWC_TPC_IG_FQ;
} DW_SWC_TPC_IG_FQ_f_T;

#endif

#ifndef SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_TPC_IG_FQ_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_TPC_IG_FQ_T rtm;
} MdlrefDW_SWC_TPC_IG_FQ_T;

#endif

extern real32_T VAR_TpcSmp_uDcLnkMax_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrVoltGen_f32_FQ;
extern real32_T VAR_TpcMot_TrqGenExCOrg_f32_FQ;
extern real32_T VAR_TpcMot_TrqElecExCOrg_f32_FQ;
extern real32_T VAR_TpcMot_TrqGenExC_f32_FQ;
extern real32_T VAR_TpcMot_GenPwrRef_f32_FQ;
extern real32_T VAR_TpcMot_TrqElecExC_f32_FQ;
extern real32_T TPC_TrqMaxTrans_FQ;
extern real32_T TPC_TrqMinTrans_FQ;
extern real32_T VAR_TpcSmp_TrqMaxCanSet_f32_FQ;
extern real32_T VAR_TpcBlk_IsValid_f32_FQ;
extern real32_T VAR_Tpcblk_TrqLim_f32_FQ;
extern real32_T VAR_Tpcblk_TrqLim01_f32_FQ;
extern real32_T VAR_Tpcblk_TrqMax_f32_FQ;
extern real32_T TPC_TrqMax_FQ;
extern real32_T VAR_TpcSmp_TrqMinCanSet_f32_FQ;
extern real32_T VAR_Tpcblk_TrqMin_f32_FQ;
extern real32_T TPC_TrqMin_FQ;
extern real32_T VAR_TpcMot_tSttrTempFlt_f32_FQ;
extern real32_T VAR_TpcMot_CofDertTSttrSave1_f32_FQ;
extern real32_T VAR_TpcMot_CofDertTSttrSave2_f32_FQ;
extern real32_T VAR_TpcMot_CofDertTsttr_f32_FQ;
extern real32_T VAR_TpcMot_tRiseSttr_f32_FQ;
extern real32_T VAR_TpcMot_CofDertTRiseSttrSave1_f32_FQ;
extern real32_T VAR_TpcMot_CofDertTRiseSttrSave2_f32_FQ;
extern real32_T VAR_TpcMot_CofDertTRiseSttr_f32_FQ;
extern real32_T VAR_TpcTmp_tDbcMax_f32_FQ;
extern real32_T VAR_TpcTmp_tDbcTempFlt_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTDbcSave1_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTDbcSave2_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertDbc_f32_FQ;
extern real32_T VAR_TpcTmp_tRiseDbc_f32_FQ;
extern real32_T VAR_TpcTmp_tRiseDbcFlt_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTRiseDbcSave1_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTRiseDbcSave2_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTRiseDbc_f32_FQ;
extern real32_T VAR_TpcTmp_tCoolantTempFlt_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTCoolantSave1_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTCoolantSave2_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTcoolant_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTdrvboard_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrSpdElecQuad1_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrSpdElecQuad3_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrSpdGenQuad4_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrSpdGenQuad2_f32_FQ;
extern real32_T VAR_TpcSmp_uDcLnkMin_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertUdrVoltElec_f32_FQ;
extern real32_T VAR_TpcMot_ElecPwrRef_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrPIDertUdrVolt_f32_FQ;
extern real32_T VAR_TpcMot_ElecTrqRef_f32_FQ;
extern real32_T VAR_TpcMot_ElecTrqLimTsttrWoRamp_f32_FQ;
extern real32_T VAR_TpcMot_ElecTrqLimTsttr_f32_FQ;
extern real32_T VAR_TpcMot_GenTrqRef_f32_FQ;
extern real32_T VAR_TpcMot_GenTrqLimTsttrWoRamp_f32_FQ;
extern real32_T VAR_TpcMot_GenTrqLimTsttr_f32_FQ;
extern real32_T VAR_TpcTmp_ElecTrqLimTdbcWoRamp_f32_FQ;
extern real32_T VAR_TpcTmp_ElecTrqLimTdbc_f32_FQ;
extern real32_T VAR_TpcTmp_GenTrqLimTdbcWoRamp_f32_FQ;
extern real32_T VAR_TpcTmp_GenTrqLimTdbc_f32_FQ;
extern real32_T VAR_TpcTmp_ElecTrqLimTcoolant_f32_FQ;
extern real32_T VAR_TpcTmp_GenTrqLimTcoolant_f32_FQ;
extern real32_T VAR_TpcTmp_ElecTrqLimTdrvboard_f32_FQ;
extern real32_T VAR_TpcTmp_GenTrqLimTdrvboard_f32_FQ;
extern real32_T VAR_TpcTmp_tIGBTTempFlt_f32_FQ;
extern real32_T VAR_TpcTmp_tRiseIGBT_f32_FQ;
extern real32_T VAR_TpcTmp_tRiseIGBTFlt_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTIGBTSave1_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTIGBTSave2_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertIGBT_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTRiseIGBTSave1_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTRiseIGBTSave2_f32_FQ;
extern real32_T VAR_TpcTmp_CofDertTRiseIGBT_f32_FQ;
extern real32_T VAR_TpcTmp_ElecTrqLimTIGBTWoRamp_f32_FQ;
extern real32_T VAR_TpcTmp_ElecTrqLimTIGBT_f32_FQ;
extern real32_T VAR_TpcTmp_GenTrqLimTIGBTWoRamp_f32_FQ;
extern real32_T VAR_TpcTmp_GenTrqLimTIGBT_f32_FQ;
extern real32_T VAR_TpcSmp_ElecTrqLimOvrSpd_f32_FQ;
extern real32_T VAR_TpcSmp_GenTrqLimOvrSpd_f32_FQ;
extern real32_T VAR_TpcSmp_iDcLnkMax_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrAlowMax_f32_FQ;
extern real32_T VAR_tpcsmp_PwrLoss_f32_FQ;
extern real32_T VAR_tpcsmp_ElecPwrDert_f32_FQ;
extern real32_T VAR_tpcsmp_AddPwrElecOvrCurt_f32_FQ;
extern real32_T VAR_tpcsmp_RefPwrElecOvrCurt_f32_FQ;
extern real32_T VAR_tpcsmp_yiDelay_f32_FQ;
extern real32_T VAR_TpcSmp_ErrElecOvrCurt_f32_FQ;
extern real32_T VAR_tpcsmp_KiProduct_f32_FQ;
extern real32_T VAR_tpcsmp_KiProductSum_f32_FQ;
extern real32_T VAR_tpcsmp_KpProduct_f32_FQ;
extern real32_T VAR_tpcsmp_KpProductSau_f32_FQ;
extern real32_T VAR_tpcsmp_PIOutput_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrPIDertOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrCurtElec_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrLinearDertOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrLimOvrCurt_f32_FQ;
extern real32_T VAR_TpcCod_ElecTrqCalcOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_iDcLnkMin_f32_FQ;
extern real32_T VAR_tpcsmp_PwrLossGen_f32_FQ;
extern real32_T VAR_tpcsmp_GenPwrDert_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrAlowMax_f32_FQ;
extern real32_T VAR_tpcsmp_RefPwrGenOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_ErrGenOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrPIDertOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_cofDertOvrCurtGen_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrLinearDertOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrLimOvrCurt_f32_FQ;
extern real32_T VAR_TpcCod_GenTrqCalcOvrCurt_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrLinearDertUdrVolt_f32_FQ;
extern real32_T VAR_TpcSmp_ElecPwrLimUdrVolt_f32_FQ;
extern real32_T VAR_TpcCod_ElecTrqCalcUdrVolt_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrLinearDertOvrVolt_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrPIDertOvrVolt_f32_FQ;
extern real32_T VAR_TpcSmp_GenPwrLimOvrVolt_f32_FQ;
extern real32_T VAR_TpcCod_GenTrqCalcOvrVolt_f32_FQ;
extern real32_T TPC_TDbcTrqMax_FQ;
extern real32_T VAR_TpcCod_PowerAdd_f32_FQ;
extern real32_T VAR_TpcCod_PowerIncreaseRate_f32_FQ;
extern real32_T VAR_TpcCod_CoolantFlowFinReq_f32_FQ;
extern real32_T VAR_TpcCod_ElecTrqCalcDiag_f32_FQ;
extern real32_T VAR_TpcCod_GenTrqCalcDiag_f32_FQ;
extern real32_T VAR_tpcsmp_negOutputjudge_f32_FQ;
extern real32_T VAR_tpcsmp_posOutputjudge_f32_FQ;
extern real32_T VAR_tpcsmp_yi_f32_FQ;
extern real32_T VAR_TpcFuv_ElecTrqLimDiag_f32_FQ;
extern real32_T VAR_TpcFuv_GenTrqLimDiag_f32_FQ;
extern real32_T VAR_TpcFuv_ElecPwrLimDiag_f32_FQ;
extern real32_T VAR_TpcFuv_GenPwrLimDiag_f32_FQ;
extern real32_T VAR_TpcBlk_IsSum_f32_FQ;
extern real32_T VAR_TpcCod_CoolantFlowReq_f32_FQ;
extern int16_T VAR_TpcMot_tSttrTempFlt_u16_FQ;
extern int16_T VAR_TpcMot_TsttrStableDiff_u16_FQ;
extern int16_T VAR_TpcTmp_tDbcTempFlt_u16_FQ;
extern int16_T VAR_TpcTmp_TDbcStableDiff_u16_FQ;
extern int16_T VAR_TpcTmp_tCoolTempFlt_u16_FQ;
extern int16_T VAR_TpcTmp_tDbcRiseTempFlt_u16_FQ;
extern int16_T VAR_TpcTmp_TDbcRiseStableDiff_u16_FQ;
extern int16_T VAR_TpcTmp_TCoolStableDiff_u16_FQ;
extern int16_T VAR_TpcTmp_tIgbtTempFlt_u16_FQ;
extern int16_T VAR_TpcTmp_TIgbtStableDiff_u16_FQ;
extern int16_T VAR_TpcTmp_tIgbtRiseTempFlt_u16_FQ;
extern int16_T VAR_TpcTmp_TIgbtRiseStableDiff_u16_FQ;
extern uint8_T TPC_SgnRotDir_FQ;
extern uint8_T TPC_SgnTrqMechDir_FQ;
extern uint8_T TPC_stMotorMod_FQ;
extern uint8_T TPC_stTrqEmMax_FQ;
extern uint8_T TPC_stTrqEmMin_FQ;
extern uint8_T VAR_TpcSmp_iDcLnkOvcWarnState_u8_FQ;
extern uint8_T VAR_TpcTmp_TIGBTOvHiWarnState_u8_FQ;
extern uint8_T VAR_TpcTmp_TIGBTOvLoWarnState_u8_FQ;
extern uint8_T VAR_TpcTmp_TIGBTOvHiErrState_u8_FQ;
extern uint8_T VAR_TpcSmp_uDcLnkUnvWarnState_u8_FQ;
extern uint8_T VAR_TpcSmp_uDcLnkUnVLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDrvBoardOvHiWarnState_u8_FQ;
extern uint8_T VAR_TpcTmp_TCoolantOvHiWarnState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcOvHiWarnState_u8_FQ;
extern uint8_T VAR_TpcMot_TSttrOvHiWarnState_u8_FQ;
extern uint8_T VAR_TpcMot_TSttrOvHiLimErrState_u8_FQ;
extern uint8_T VAR_TpcMot_TSttrOvLoWarnState_u8_FQ;
extern uint8_T VAR_TpcSmp_uDcLnkOvWarnState_u8_FQ;
extern uint8_T VAR_TpcSmp_iDcLnkOvCLimErrState_u8_FQ;
extern uint8_T VAR_TpcSmp_uDcLnkOvVLimErrState_u8_FQ;
extern uint8_T VAR_TpcSmp_SpdOvHiWarnState_u8_FQ;
extern uint8_T VAR_TpcSmp_SpdOvHiLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcOvLoWarnState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcUHiLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcULoLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcVHiLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcVLoLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcWHiLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_TDbcWLoLimErrState_u8_FQ;
extern uint8_T VAR_TpcTmp_tRiseIGBTOperationMode_u8_FQ;
extern uint8_T VAR_TpcTmp_tIGBTOperationMode_u8_FQ;
extern uint8_T VAR_TpcTmp_tRiseDbcOperationMode_u8_FQ;
extern uint8_T VAR_TpcTmp_tDbcOperationMode_u8_FQ;
extern uint8_T VAR_TpcTmp_tCoolantOperationMode_u8_FQ;
extern uint8_T VAR_TpcMot_tSttrOperationMode_u8_FQ;
extern uint8_T VAR_TpcMot_tRiseSttrOperationMode_u8_FQ;
extern boolean_T VAR_TpcSmp_flgLinearDertOvrVoltGen_b_FQ;
extern boolean_T VAR_TpcMot_flgStartExcLimRamp_b_FQ;
extern boolean_T VAR_TpcSmp_flgPIDertOvrVoltGen_b_FQ;
extern boolean_T VAR_TpcSmp_flgGenPwrLimOvrVoltActv_b_FQ;
extern boolean_T TPC_bDernOvrUdc_FQ;
extern boolean_T VAR_TpcCod_flgMotorElecMode_b_FQ;
extern boolean_T TPC_bDernExcMax_FQ;
extern boolean_T TPC_bDernExcMin_FQ;
extern boolean_T VAR_TpcMot_flgTrqLimTsttrActv_b_FQ;
extern boolean_T TPC_bDernStrTemp_FQ;
extern boolean_T VAR_TpcTmp_flgTrqLimTdbcActv_b_FQ;
extern boolean_T TPC_bDernDbcTemp_FQ;
extern boolean_T VAR_TpcTmp_flgTrqLimTcoolantActv_b_FQ;
extern boolean_T TPC_bDernCoolantTemp_FQ;
extern boolean_T VAR_TpcTmp_flgTrqLimTdrvboardActv_b_FQ;
extern boolean_T TPC_bDernDrvBoardTemp_FQ;
extern boolean_T VAR_TpcSmp_flgElecTrqLimOvrSpdActv_b_FQ;
extern boolean_T VAR_TpcSmp_flgGenTrqLimOvrSpdActv_b_FQ;
extern boolean_T TPC_bDernMtrSpd_FQ;
extern boolean_T VAR_TpcSmp_flgLinearDertUdrVoltElec_b_FQ;
extern boolean_T VAR_TpcSmp_flgPIDertUdrVoltElec_b_FQ;
extern boolean_T VAR_TpcSmp_flgElecPwrLimUdrVoltActv_b_FQ;
extern boolean_T TPC_bDernUndrUdc_FQ;
extern boolean_T TPC_bDernCAN_FQ;
extern boolean_T VAR_tpccod_flgMaxDertExCTrq_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertStrTemp_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertTempDBC_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertTCoolant_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertTDrvBoard_b_FQ;
extern boolean_T VAR_TpcTmp_flgTrqLimTIGBTActv_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertTIGBT_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertMtrSpd_b_FQ;
extern boolean_T VAR_TpcSmp_flgLinearDertOvrCurtElec_b_FQ;
extern boolean_T VAR_TpcSmp_flgPIDertOvrCurtElec_b_FQ;
extern boolean_T VAR_TpcSmp_flgElecPwrLimOvrCurtActv_b_FQ;
extern boolean_T VAR_TpcSmp_flgLinearDertOveCurtGen_b_FQ;
extern boolean_T VAR_TpcSmp_flgPIDertOvrCurtGen_b_FQ;
extern boolean_T VAR_TpcSmp_flgGenPwrLimCurtActv_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertOvrIdc_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertUndrUdc_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertOvrUdc_b_FQ;
extern boolean_T VAR_tpccod_flgMaxDertCAN_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertExCTrq_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertStrTemp_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertTempDBC_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertTCoolant_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertTDrvBoard_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertTIGBT_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertMtrSpd_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertOvrIdc_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertUndrUdc_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertOvrUdc_b_FQ;
extern boolean_T VAR_tpccod_flgMinDertCAN_b_FQ;
extern boolean_T TPC_bDernElecOvrIdc_FQ;
extern boolean_T TPC_bDernGenOvrIdc_FQ;
extern boolean_T TPC_bDernOvrIdc_FQ;
extern boolean_T TPC_bDernIGBTTemp_FQ;
extern boolean_T VAR_TpcFuv_FimTrqLimLv1_b_FQ;
extern boolean_T VAR_TpcFuv_FimTrqLimLv2_b_FQ;
extern boolean_T VAR_TpcFuv_FimTrqLimLv3_b_FQ;
extern boolean_T VAR_TpcFuv_FimTrqLimLv4_b_FQ;
extern boolean_T VAR_TpcFuv_FimPwrLimLv1_b_FQ;
extern boolean_T VAR_TpcFuv_FimPwrLimLv2_b_FQ;
extern boolean_T VAR_TpcFuv_FimPwrLimLv3_b_FQ;
extern boolean_T VAR_TpcFuv_FimPwrLimLv4_b_FQ;
extern void SWC_TPC_IG_FQ_Init(void);
extern void SWC_TPC_IG_FQ(const real32_T *rtu_MPC_BUS_MPC_TrqMechFlt, const
  real32_T *rtu_HSPF_BUS_HSPF_tDBCTempUFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_tDBCTempVFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_tDBCTempWFlt, const real32_T *rtu_HSPF_BUS_HSPF_nSlowFlt,
  const real32_T *rtu_HSPF_BUS_HSPF_tDrvBoardTemp, const real32_T
  *rtu_HSPF_BUS_HSPF_iDcLnkEstFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const real32_T *rtu_HSPF_BUS_HSPF_tIGBTTjFlt,
  const real32_T *rtu_HSPF_BUS_HSPF_tCoolantTjFlt, const real32_T
  *rtu_MCF_BUS_MCF_Is, const real32_T *rtu_TDC_BUS_TDC_TrqDes, real32_T
  *rty_TPC_BUS_TPC_TrqMax, real32_T *rty_TPC_BUS_TPC_TrqMin, boolean_T
  *rty_TPC_BUS_TPC_bDernExcMax, boolean_T *rty_TPC_BUS_TPC_bDernExcMin,
  boolean_T *rty_TPC_BUS_TPC_bDernStrTemp, boolean_T
  *rty_TPC_BUS_TPC_bDernDbcTemp, boolean_T *rty_TPC_BUS_TPC_bDernCoolantTem,
  boolean_T *rty_TPC_BUS_TPC_bDernDrvBoardTe, boolean_T
  *rty_TPC_BUS_TPC_bDernMtrSpd, boolean_T *rty_TPC_BUS_TPC_bDernUndrUdc,
  boolean_T *rty_TPC_BUS_TPC_bDernOvrUdc, boolean_T *rty_TPC_BUS_TPC_bDernCAN,
  uint8_T *rty_TPC_BUS_TPC_stTrqEmMax, uint8_T *rty_TPC_BUS_TPC_stTrqEmMin,
  uint8_T *rty_TPC_BUS_TPC_stMotorMod, real32_T *rty_TPC_BUS_TPC_TDbcTrqMax,
  uint8_T *rty_TPC_BUS_TPC_SgnRotDir, uint8_T *rty_TPC_BUS_TPC_SgnTrqMechDir,
  boolean_T *rty_TPC_BUS_TPC_bDernElecOvrIdc, boolean_T
  *rty_TPC_BUS_TPC_bDernGenOvrIdc, boolean_T *rty_TPC_BUS_TPC_bDernOvrIdc,
  real32_T *rty_TPC_BUS_TPC_TrqMaxTrans, real32_T *rty_TPC_BUS_TPC_TrqMinTrans,
  boolean_T *rty_TPC_BUS_TPC_bDernIGBTTemp, real32_T *rty_DEM_BUS);
extern void SWC_TPC_IG_FQ_initialize(const char_T **rt_errorStatus);

#ifndef SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_

extern void SWC_TPC_IG_FQ_GetHighTemp_Init(real32_T *rty_TModuleTempHighest);
extern void SWC_TPC_IG_FQ_GetHighTemp(real32_T rtu_TModuletemp, real32_T
  rtu_TModuletempDly, real32_T *rty_TModuleTempHighest);

#endif

#pragma section ".CAL_CONST"

extern const volatile uint16_T CAL_TpcBlk_BlkRevTimSet_u16_FQ;
extern const volatile uint16_T CAL_TpcBlk_BlkTimSet_u16_FQ;
extern const volatile real32_T CAL_TpcBlk_MtrBlkIsFirstSet_f32_FQ;
extern const volatile real32_T CAL_TpcBlk_MtrBlkIsSecondSet_f32_FQ;
extern const volatile real32_T CAL_TpcBlk_MtrBlkSpdHighSet_f32_FQ;
extern const volatile real32_T CAL_TpcBlk_MtrBlkSpdLowSet_f32_FQ;
extern const volatile real32_T CAL_TpcBlk_TrqBlkStab_f32_FQ;
extern const volatile real32_T CAL_TpcBlk_TrqDecRamp_f32_FQ;
extern const volatile real32_T CAL_TpcBlk_TrqIncRamp_f32_FQ;
extern const volatile boolean_T CAL_TpcBlk_flgEnBlkFun_b_FQ;
extern const volatile uint16_T CAL_TpcCod_CntHysteresislop_u16_FQ;
extern const volatile real32_T CAL_TpcCod_CoolFlow1LReq_f32_FQ;
extern const volatile real32_T CAL_TpcCod_CoolFlow2LTableX_Udc_af32_FQ[5];
extern const volatile real32_T CAL_TpcCod_CoolFlow2LTableY_Spd_af32_FQ[8];
extern const volatile real32_T CAL_TpcCod_CoolFlow2LTableZ_Trq_af32_FQ[40];
extern const volatile real32_T CAL_TpcCod_CoolFlow4LTableX_Udc_af32_FQ[5];
extern const volatile real32_T CAL_TpcCod_CoolFlow4LTableY_Spd_af32_FQ[8];
extern const volatile real32_T CAL_TpcCod_CoolFlow4LTableZ_Trq_af32_FQ[40];
extern const volatile real32_T CAL_TpcCod_CoolFlow6LTableX_Udc_af32_FQ[5];
extern const volatile real32_T CAL_TpcCod_CoolFlow6LTableY_Spd_af32_FQ[8];
extern const volatile real32_T CAL_TpcCod_CoolFlow6LTableZ_Trq_af32_FQ[40];
extern const volatile boolean_T CAL_TpcCod_FlgUseTrqLimRampSet_b_FQ;
extern const volatile boolean_T CAL_TpcCod_IGBTSampErr_b_FQ;
extern const volatile boolean_T CAL_TpcCod_MotorSampErr_b_FQ;
extern const volatile boolean_T CAL_TpcCod_MotorStallWarn_b_FQ;
extern const volatile real32_T CAL_TpcCod_NTCHighTemp_f32_FQ;
extern const volatile real32_T CAL_TpcCod_NTCLowTemp_f32_FQ;
extern const volatile real32_T CAL_TpcCod_NegSpdDirStop_f32_FQ;
extern const volatile real32_T CAL_TpcCod_NegTrqDirStop_f32_FQ;
extern const volatile real32_T CAL_TpcCod_PosSpdDirStop_f32_FQ;
extern const volatile real32_T CAL_TpcCod_PosSpdHold_f32_FQ;
extern const volatile real32_T CAL_TpcCod_PosSpdStart_f32_FQ;
extern const volatile real32_T CAL_TpcCod_PosTrqDirStop_f32_FQ;
extern const volatile real32_T CAL_TpcCod_PowIncRatLim_f32_FQ;
extern const volatile real32_T CAL_TpcCod_TrqRelay_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv1_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv2_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv3_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv4_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv1_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv2_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv3_f32_FQ;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv4_f32_FQ;
extern const volatile real32_T CAL_TpcMot_ExCElecTableX_Udc_af32_FQ[10];
extern const volatile real32_T CAL_TpcMot_ExCElecTableY_Spd_af32_FQ[14];
extern const volatile real32_T CAL_TpcMot_ExCElecTableZ_Trq_af32_FQ[140];
extern const volatile real32_T CAL_TpcMot_ExCGenTableX_Udc_af32_FQ[10];
extern const volatile real32_T CAL_TpcMot_ExCGenTableY_Spd_af32_FQ[17];
extern const volatile real32_T CAL_TpcMot_ExCGenTableZ_Trq_af32_FQ[170];
extern const volatile real32_T CAL_TpcMot_SttrChgTempDownDiff_f32_FQ;
extern const volatile real32_T CAL_TpcMot_SttrChgTempUpDiff_f32_FQ;
extern const volatile real32_T CAL_TpcMot_SttrTempAdds_f32_FQ;
extern const volatile real32_T CAL_TpcMot_SttrTempDecDiff_f32_FQ;
extern const volatile real32_T CAL_TpcMot_SttrTempKp_f32_FQ;
extern const volatile real32_T CAL_TpcMot_SttrTempMinus_f32_FQ;
extern const volatile real32_T CAL_TpcMot_SttrTempRiseDiff_f32_FQ;
extern const volatile boolean_T CAL_TpcMot_flgPwrRefSwt_b_FQ;
extern const volatile boolean_T CAL_TpcMot_flgTrqRefSwt_b_FQ;
extern const volatile real32_T
  CAL_TpcMot_tRiseSttrDertSave1TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T
  CAL_TpcMot_tRiseSttrDertSave2TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraSave2ToOverheating_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrDertSave1TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tSttrDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tSttrDertSave2TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tSttrDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcMot_tSttrHiLim_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrLoLim_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrTraSave2ToOverheating_f32_FQ;
extern const volatile real32_T CAL_TpcMot_tSttrTrqLimRamp_f32_FQ;
extern const volatile uint8_T CAL_TpcSmp_CntElecOvrCurt_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_CntElecUdrVolt_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_CntGenOvrCurt_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_CntGenOvrVolt_u8_FQ;
extern const volatile boolean_T CAL_TpcSmp_CurtModeSelc_b_FQ;
extern const volatile real32_T CAL_TpcSmp_ElecOvrCurtKi_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_ElecOvrCurtKp_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_ElecOvrCurtypLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_ElecUdrVoltKi_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_ElecUdrVoltKp_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_ElecUdrVoltypLim_f32_FQ;
extern const volatile uint8_T CAL_TpcSmp_FacElecOvrCurt_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_FacElecUdrVolt_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_FacGenOvrCurt_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_FacGenOvrVolt_u8_FQ;
extern const volatile real32_T CAL_TpcSmp_GenOvrCurtKi_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_GenOvrCurtKp_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_GenOvrCurtypLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_GenOvrVoltKi_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_GenOvrVoltKp_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_GenOvrVoltypLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_OvSpdWarnHiLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_OvSpdWarnLoLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimElecTableX_iDc_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimElecTableY_Cof_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimGenTableX_iDc_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimGenTableY_Cof_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd1TableX_Spd_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd1TableY_Cof_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd2TableX_Spd_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd2TableY_Cof_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd3TableX_Spd_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd3TableY_Cof_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd4TableX_Spd_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd4TableY_Cof_af32_FQ[7];
extern const volatile real32_T CAL_TpcSmp_OvrVoltGenTableX_uDc_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_OvrVoltGenTableY_Cof_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_PwrAddMaxGen_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_PwrAddMax_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_SystemEffiElec_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_SystemEffiGen_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_ThresOverSpd_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_TrqAddMaxGen_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_TrqAddMax_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_UdrVoltElecTableX_uDc_af32_FQ[5];
extern const volatile real32_T CAL_TpcSmp_UdrVoltElecTableY_Cof_af32_FQ[5];
extern const volatile boolean_T CAL_TpcSmp_flgUsePwrLossGen_b_FQ;
extern const volatile boolean_T CAL_TpcSmp_flgUsePwrLoss_b_FQ;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMaxMax_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMaxMin_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMinMax_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMinMin_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_iDcLnkOvCElecLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_iDcLnkOvCGenLim_f32_FQ;
extern const volatile uint8_T CAL_TpcSmp_nCtlExtReq_u8_FQ;
extern const volatile uint8_T CAL_TpcSmp_nCtlIntReq_u8_FQ;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMaxMax_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMaxMin_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMinMax_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMinMin_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_uDcLnkOvVLim_f32_FQ;
extern const volatile real32_T CAL_TpcSmp_uDcLnkUnVLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolChgTempDownDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolChgTempUpDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolTempAdds_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolTempDecDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolTempKp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolTempMinus_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_CoolTempRiseDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempAdds_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempDecDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempKp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempMinus_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempRiseDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCTempAdds_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCTempDecDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCTempKp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCTempMinus_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DBCTempRiseDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DbcChgTempDownDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DbcChgTempUpDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DbcRiseChgTempDownDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_DbcRiseChgTempUpDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBRiseTTempAdds_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempDecDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempKp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempMinus_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempRiseDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTTempAdds_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTTempDecDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTTempKp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTTempMinus_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IGBTTempRiseDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IgbtChgTempDownDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IgbtChgTempUpDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IgbtRiseChgTempDownDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_IgbtRiseChgTempUpDiff_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave1TableX_tSttr_af32_FQ
  [9];
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave2TableX_tSttr_af32_FQ
  [9];
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tCoolantTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tCoolantTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tCoolantTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tCoolantTraSave2ToOverheating_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDBCTrqLimRamp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave1TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave2TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tDbcTempUHiLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTempULoLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTempVHiLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTempVLoLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTempWHiLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTempWLoLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcThrPhLoLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDbcTraSave2ToOverheating_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tDrvboardDertTableX_tDrv_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tDrvboardDertTableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave1TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave2TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTTempHiLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tIGBTTempLoLim_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraSave2ToOverheating_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tIGBTTrqLimRamp_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave1TableX_tSttr_af32_FQ
  [9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave2TableX_tSttr_af32_FQ
  [9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraSave2ToOverheating_f32_FQ;
extern const volatile real32_T
  CAL_TpcTmp_tRiseIGBTDertSave1TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTDertSave1TableY_Cof_af32_FQ[9];
extern const volatile real32_T
  CAL_TpcTmp_tRiseIGBTDertSave2TableX_tSttr_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTDertSave2TableY_Cof_af32_FQ[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraNormalToSave1_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraSave1ToNormal_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraSave1ToSave2_f32_FQ;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraSave2ToOverheating_f32_FQ;
extern const volatile uint8_T CAL_Tpc_NormalMode_u8_FQ;
extern const volatile uint8_T CAL_Tpc_OverheatingMode_u8_FQ;
extern const volatile uint8_T CAL_Tpc_Powersave1Mode_u8_FQ;
extern const volatile uint8_T CAL_Tpc_Powersave2Mode_u8_FQ;
extern const volatile real32_T CAL_Tpc_TrqReduceRevStep_f32_FQ;
extern const volatile real32_T CAL_Tpc_TrqRevStep_f32_FQ;
extern const volatile real32_T CAL_Tpc_TrqRiseRevStep_f32_FQ;
extern const volatile uint8_T CAL_Tpcmot_CofuDclnk_u8_FQ;
extern const volatile real32_T CAL_Tpcmot_TrqDiffExc_f32_FQ;
extern const volatile real32_T CAL_Tpcmot_TrqDiffGen_f32_FQ;
extern const volatile boolean_T CAL_Tpcmot_flgOpenExcLimRamp_b_FQ;
extern const volatile real32_T CAL_Tpcmot_uDcHiset_f32_FQ;
extern const volatile real32_T CAL_Tpcmot_uDcLoset_f32_FQ;
extern const volatile real32_T CAL_trqMaxOvrdVal_f32_FQ;
extern const volatile boolean_T CAL_trqMaxOvrdflg_b_FQ;
extern const volatile real32_T CAL_trqMinOvrdVal_f32_FQ;
extern const volatile boolean_T CAL_trqMinOvrdflg_b_FQ;

#pragma section

#ifndef SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_TPC_IG_FQ_T SWC_TPC_IG_FQ_MdlrefDW;

#endif

#ifndef SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_

extern DW_SWC_TPC_IG_FQ_f_T SWC_TPC_IG_FQ_DW;

#endif
#endif

