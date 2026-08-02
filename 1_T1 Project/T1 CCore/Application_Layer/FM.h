#ifndef RTW_HEADER_FM_h_
#define RTW_HEADER_FM_h_
#include <math.h>
#include <stddef.h>
#ifndef FM_COMMON_INCLUDES_
#define FM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "FM_types.h"

#include "model_reference_types.h"

#define SWC_MPC_IG_MDLREF_HIDE_CHILD_
#include "SWC_MPC_IG.h"
#define SWC_TDC_IG_MDLREF_HIDE_CHILD_
#include "SWC_TDC_IG.h"
#define SWC_TPC_IG_MDLREF_HIDE_CHILD_
#include "SWC_TPC_IG.h"
#define SWC_MDF_IG_MDLREF_HIDE_CHILD_
#include "SWC_MDF_IG.h"
#define SWC_SCF_IG_MDLREF_HIDE_CHILD_
#include "SWC_SCF_IG.h"
#define SWC_CSPF_IG_MDLREF_HIDE_CHILD_
#include "SWC_CSPF_IG.h"
#define SWC_HSPF_IG_MDLREF_HIDE_CHILD_
#include "SWC_HSPF_IG.h"
#define SWC_BCC_IG_MDLREF_HIDE_CHILD_
#include "SWC_BCC_IG.h"
#define SWC_MCF_IG_MDLREF_HIDE_CHILD_
#include "SWC_MCF_IG.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

#define CAL_Hspf_Failure_u8            3U
#define CAL_Hspf_Succeed_u8            2U
#define CAL_Hspf_Uncheck_u8            0U
#define CAL_TDC_go_nCtlExtReq_u8       1U
#define GLB_HspfFlt_pi_f32             3.14159203F
#define GLB_RDC_CircAge_f32            360.0F
#define GLB_RDC_Sixty_f32              60.0F
#define GLB_TpcCod_BwELect_u8          3U
#define GLB_TpcCod_BwGene_u8           2U
#define GLB_TpcCod_FwELect_u8          1U
#define GLB_TpcCod_FwGene_u8           4U
#define GLB_TpcCod_MotorBw_u8          2U
#define GLB_TpcCod_MotorFw_u8          1U
#define GLB_TpcCod_MotorStop_u8        0U
#define GLB_TpcCod_NegvTrq_u8          2U
#define GLB_TpcCod_PosvTrq_u8          1U
#define GLB_TpcCod_ZeroTrq_u8          0U
#define GLB_Tpc_MaximumPower_f32       150.0F
#define GLB_Tpc_MaximumTorque_f32      310.0F
#define MCF_ANGLE_CURRENT_150          150.0F
#define MCF_ANGLE_CURRENT_210          210.0F
#define MCF_ANGLE_CURRENT_270          270.0F
#define MCF_ANGLE_CURRENT_30           30.0F
#define MCF_ANGLE_CURRENT_330          330.0F
#define MCF_ANGLE_CURRENT_90           90.0F
#define MCF_CURRENT_SECTOR_1           1U
#define MCF_CURRENT_SECTOR_2           2U
#define MCF_CURRENT_SECTOR_3           3U
#define MCF_CURRENT_SECTOR_4           4U
#define MCF_CURRENT_SECTOR_5           5U
#define MCF_CURRENT_SECTOR_6           6U
#define MCF_GLB_CircAge_f32            360.0F
#define MCF_GLB_DigtValue_u16          4096U
#define MCF_GLB_MotorPole_u8           4U
#define MCF_GLB_OneHalf_f32            0.5F
#define MCF_GLB_Sixty_f32              60.0F
#define MCF_GLB_SqrtThree_f32          1.73205101F
#define MCF_GLB_pi_f32                 3.14159203F
#define MCF_Succeed_u8                 2U
#define MDF_GLB_IGBTrun_u8             3U
#define MDF_GLB_MotorPole_u8           4U
#define MDF_GLB_pi_f32                 3.14159203F
#define MPC_GLB_MotorPole_u8           4U
#define MPC_GLB_SqrtTwo_f32            1.41421294F
#define MPC_GLB_pi_f32                 3.14159203F
#define PRV_CalFltFrq_10ms             100U
#define PRV_CalFltFrq_2ms              500.0F

typedef struct {
  real32_T MPC_LdSubLq_c;
  real32_T MPC_Ld_c;
  real32_T MPC_Lq_j;
  real32_T MPC_Rs_p;
  real32_T MPC_TrqMech_n;
  real32_T MPC_TrqMechFlt_e;
  real32_T MPC_psiExc_o;
  real32_T MPC_IsFlt_e;
  real32_T MPC_idActFlt_l;
  real32_T MPC_iqActFlt_o;
  real32_T MPC_dtCorFac_l;
  real32_T MPC_isdMTPA_p;
  real32_T MPC_isdFF_c;
  real32_T MPC_isdMTPV_a;
  real32_T MPC_OmBw_o;
  real32_T MPC_Rv_a;
  real32_T MPC_frqPwmVF_f;
  real32_T MPC_CofRandomPwm_n;
  real32_T TDC_TrqDes_j;
  real32_T TPC_TrqMax_k;
  real32_T TPC_TrqMin_b;
  real32_T TPC_TDbcTrqMax_j;
  real32_T TPC_TrqMaxTrans_b;
  real32_T TPC_TrqMinTrans_o;
  real32_T TPC_o25;
  real32_T Nm_HCUReqMCUTq;
  real32_T rpm_HCUReqMCUSpd;
  real32_T HSPF_uKl30Flt_g;
  real32_T HSPF_tDBCTempUFlt_o;
  real32_T HSPF_tDBCTempVFlt_i;
  real32_T HSPF_tDBCTempWFlt_k;
  real32_T HSPF_tStrrTemp1Flt_b;
  real32_T HSPF_tStrrTemp2Flt_e;
  real32_T HSPF_nSlowFlt_o;
  real32_T HSPF_tCoolantTempFlt_l;
  real32_T HSPF_tDrvBoardTempFlt_m;
  real32_T HSPF_iDcLnkEstFlt_c;
  real32_T HSPF_PwrDcLnk_a;
  real32_T HSPF_uDcLnkSlowFlt_g;
  real32_T HSPF_iPhaUOffset_o;
  real32_T HSPF_iPhaVOffset_e;
  real32_T HSPF_iPhaWOffset_m;
  real32_T HSPF_tStrrTempFlt_f;
  real32_T HSPF_tIGBTTjFlt_j;
  real32_T HSPF_tCoolantTjFlt_l;
  real32_T HSPF_VerMatchFailureErr_b;
  real32_T BCC_iDcLnkEst;
  real32_T BCC_tIGBTTj_f;
  real32_T BCC_tCoolantTj_d;
  real32_T MCF_idDes_c;
  real32_T MCF_iqDes_n;
  real32_T MCF_udDes_j;
  real32_T MCF_uqDes_j;
  real32_T MCF_dycU_b;
  real32_T MCF_dycV_l;
  real32_T MCF_dycW_p;
  real32_T MCF_frqPwm_d;
  real32_T MCF_cofFrqPwm_d;
  real32_T MCF_dtPwm_a;
  real32_T MCF_tiLock_b;
  real32_T MCF_Is_g;
  real32_T MCF_idAct_p;
  real32_T MCF_iqAct_g;
  real32_T MCF_uDcLnk_o;
  real32_T MCF_iU_d;
  real32_T MCF_iV_o;
  real32_T MCF_iW_m;
  real32_T MCF_VoltModuRate_f;
  int16_T Calc_perc_TotDrvTorqRaw;
  int16_T Calc_Nm_TotDrvTorqRaw;
  int16_T Calc_perc_EngPedalRaw;
  int16_T Calc_rpm_TMCurAvalMaxSpeed;
  int16_T Nm_HCUMCU2ReqMCUTq;
  int16_T rpm_HCUMCU2ReqMCUSpd;
  int16_T Calc_rpm_MCU2TMCurAvalMaxSpeed;
  int16_T Calc_Nm_ReferenceMCTorque;
  int16_T Calc_z_ETC2GearRatio;
  int16_T Calc_rpm_MtrReqSpdLimit;
  int16_T Cale_Nm_MtrReqTqLimit;
  int16_T Calc_Nm_MtrReqTqFric;
  int16_T Calc_rpm_Mtr2ReqSpdLimit;
  int16_T Calc_Nm_Mtr2ReqTqLimit;
  int16_T Calc_Nm_Mtr2ReqTqFric;
  uint8_T TPC_stTrqEmMax_d;
  uint8_T TPC_stTrqEmMin_o;
  uint8_T TPC_stMotorMod_g;
  uint8_T TPC_SgnRotDir_h;
  uint8_T TPC_SgnTrqMechDir_h;
  uint8_T MDF_stFrwhl;
  uint8_T MDF_bFaultEMBlkWarnSt;
  uint8_T MDF_bFaultEMBlkErrSt;
  uint8_T MDF_bFaultPwrCmpSt;
  uint8_T MDF_bPhaseFaultSt;
  uint8_T MDF_bAlfOfsNoPlauseFaultSt;
  uint8_T MDF_bFaultICtlChkSt;
  uint8_T MDF_bOpenCirNoPsblFaultSt;
  uint8_T MDF_bShCirNoPsblFaultSt;
  uint8_T MDF_flagOperOutdRngFaultSt;
  uint8_T MDF_IsOvHiErrSt;
  uint8_T SCF_stSysCtl_b;
  uint8_T SCF_stGateDrv_j;
  uint8_T SCF_stDrvCtl_f;
  uint8_T SCF_stDisChg_e;
  uint8_T SCF_stPreDrvCtl_i;
  uint8_T SCF_stSys_i;
  uint8_T SCF_stModeReqToTdc_k;
  uint8_T SCF_stPwmMode;
  uint8_T SCF_stFFAction_e;
  uint8_T SCF_FIM_ReqFailrMod_m;
  uint8_T Calc_st_ParkingBrkSW;
  uint8_T Calc_gear_TransmissionRequested;
  uint8_T Calc_st_EPSwitch;
  uint8_T Calc_st_MsgSwitchC;
  uint8_T Calc_st_MsgSwitchL;
  uint8_T Calc_bool_FootBrake;
  uint8_T Calc_st_HCUReqInhibitSftGear;
  uint8_T Calc_st_HCUReqAutoChgN;
  uint8_T Calc_mod_HCUReqMotWorkMode;
  uint8_T Calc_st_HCUReqMotRotaDir;
  uint8_T Calc_st_HCUAllowMotWorkEn;
  uint8_T Calc_st_NegtvRelayState;
  uint8_T Calc_st_PostvRelayState;
  uint8_T Calc_st_PreChargHiVoltRelayStat;
  uint8_T Calc_st_HCUReqHiPowerOff;
  uint8_T Calc_mod_HCUMCU2ReqMotWorkMode;
  uint8_T Calc_st_HCUMCU2ReqMotRotaDir;
  uint8_T Calc_st_HCUMCU2AllowMotWorkEn;
  uint8_T Calc_st_MCU2NegtvRelayState;
  uint8_T Calc_st_MCU2PostvRelayState;
  uint8_T Calc_st_MCU2PreChargHiVoltRelay;
  uint8_T Calc_st_HCUMCU2ReqHiPowerOff;
  uint8_T Calc_st_MCU2ActvDischgCommand;
  uint8_T Calc_gear_HTransmissionRequeste;
  uint8_T Calc_st_TCHandEPSwitch;
  uint8_T Calc_st_ShiftInProcess;
  uint8_T Calc_gear_ETC2SelectGear;
  uint8_T Calc_gear_ETC2CurrentGear;
  uint8_T Calc_st_MtrOverridConMode;
  uint8_T Calc_st_MtrReqSpdContCond;
  uint8_T Calc_st_MtrOverrideConModePrior;
  uint8_T Calc_st_Mtr2OverridConMode;
  uint8_T Calc_st_Mtr2ReqSpdContCond;
  uint8_T Calc_st_Mtr2OverrideConModePrio;
  uint8_T HSPF_stIphaOffCal_b;
  uint8_T HSPF_tDBCTempCmpErrSt_n;
  uint8_T HSPF_MotorOpenErrSt_p;
  uint8_T HSPF_InvOpenErrSt_j;
  uint8_T HSPF_checkstatus_h;
  uint8_T MCF_SecVolt_i;
  uint8_T MCF_stpwmMode_c;
  boolean_T TDC_flgTrqLmtActv_l;
  boolean_T TPC_bDernExcMax_n;
  boolean_T TPC_bDernExcMin_i;
  boolean_T TPC_bDernStrTemp_b;
  boolean_T TPC_bDernDbcTemp_p;
  boolean_T TPC_bDernCoolantTemp_f;
  boolean_T TPC_bDernDrvBoardTemp_d;
  boolean_T TPC_bDernMtrSpd_k;
  boolean_T TPC_bDernUndrUdc_g;
  boolean_T TPC_bDernOvrUdc_p;
  boolean_T TPC_bDernCAN_f;
  boolean_T TPC_bDernElecOvrIdc_c;
  boolean_T TPC_bDernGenOvrIdc_d;
  boolean_T TPC_bDernOvrIdc_m;
  boolean_T TPC_bDernIGBTTemp_k;
  boolean_T SCF_flgDataStrgBgnToBsw_d;
  boolean_T SCF_flginitPI_e;
  boolean_T SCF_flgEnDchaToMc_i;
  boolean_T SCF_flgUdcLowToTpc_b;
  boolean_T SCF_bHvReady_write_b;
  boolean_T SCF_flgEmgReqInvDcha_f;
  boolean_T SCF_flgActvDcha_k;
  boolean_T SCF_LwPwrDwn_o;
  boolean_T Calc_st_ActvDischgCommand;
  boolean_T HSPF_bt15_j;
  boolean_T HSPF_Crash_l;
  boolean_T HSPF_INV_Open_c;
  boolean_T HSPF_Motor_Open_f;
  boolean_T HSPF_Wake_d;
  boolean_T HSPF_bSwtTempSttr1;
  boolean_T HSPF_bSwtTempSttr2;
} B_FM_T;

typedef struct {
  real32_T Delay_DSTATE;
  real32_T UnitDelay2_DSTATE;
  real32_T UnitDelay_DSTATE;
  real32_T Delay1_DSTATE;
  real32_T Delay1_DSTATE_d;
  real32_T Delay10_DSTATE[2];
  real32_T Delay9_DSTATE[3];
  real32_T Delay7_DSTATE[4];
  real32_T Delay6_DSTATE[5];
  real32_T Delay5_DSTATE[6];
  real32_T Delay4_DSTATE[7];
  real32_T Delay3_DSTATE[8];
  real32_T Delay2_DSTATE[9];
  real32_T Delay8_DSTATE;
  real32_T Delay11_DSTATE[2];
  real32_T Delay18_DSTATE[3];
  real32_T Delay17_DSTATE[4];
  real32_T Delay16_DSTATE[5];
  real32_T Delay15_DSTATE[6];
  real32_T Delay14_DSTATE[7];
  real32_T Delay13_DSTATE[8];
  real32_T Delay12_DSTATE[9];
  real32_T UnitDelay_DSTATE_n;
  real32_T UnitDelay1_DSTATE;
  real32_T UnitDelay_DSTATE_h;
  real32_T UnitDelay_DSTATE_i;
  real32_T UnitDelay_DSTATE_f;
  uint16_T UnitDelay_DSTATE_o;
  boolean_T Delay2_DSTATE_h;
} DW_FM_T;

typedef struct {
  const real32_T Gain;
} ConstB_FM_T;

struct tag_RTM_FM_T {
  const char_T *errorStatus;
  struct {
    uint32_T clockTick3;
  } Timing;
};

extern B_FM_T FM_B;
extern DW_FM_T FM_DW;
extern const ConstB_FM_T FM_ConstB;
extern real32_T RDC_agRtrEe;
extern uint16_T iUNoOff;
extern uint16_T iVNoOff;
extern uint16_T iWNoOff;
extern real32_T uDcLnk;
extern uint16_T tDBCTempU;
extern uint16_T tDBCTempV;
extern uint16_T tDBCTempW;
extern uint16_T tmoterTempV;
extern real32_T VAR_Hspf_uKl30_f32;
extern boolean_T VAR_Bsw_bt15_b;
extern uint8_T VAR_ccvs_hcu_u8[8];
extern uint8_T VAR_hcu_mcu_u8[8];
extern boolean_T VAR_flg_ov_b;
extern boolean_T VAR_flg_oc_b;
extern real32_T Var_rdc_Ag_f32;
extern real32_T RDC_ArctanAgRtr_CmPn;
extern real32_T RDC_Delta_Theta;
extern real32_T RDC_Delta_Theta_Flt;
extern real32_T RDC_Arctan_nWoFlt;
extern boolean_T Var_rdc_initend_b;
extern real32_T CAL_RDC_nWofltDelay_u16;
extern real32_T GLB_RDC_MotorPole_u8;
extern void FM_initialize(void);
extern void FM_terminate(void);
extern void tri_100us(void);
extern void tri_2ms(void);
extern void tri_10ms(void);

#pragma section ".CAL_CONST"

extern const volatile real32_T CAL_BCC_AgGenCoe_f32;
extern const volatile real32_T CAL_BCC_dycLowLimt_f32;
extern const volatile real32_T CAL_BCC_dycUpLimt_f32;
extern const volatile boolean_T CAL_BCC_flgDelayDyc_b;
extern const volatile boolean_T CAL_BCC_flgEnableIdc_b;
extern const volatile boolean_T CAL_BCC_flgEnableTj_b;
extern const volatile real32_T CAL_BCC_iDcEstflt_f32;
extern const volatile real32_T CAL_BCC_tiFull_f32;
extern const volatile real32_T CAL_CoolantFlowReq_u8;
extern const volatile real32_T CAL_Hspf_CltInletTempFltFrq_f32;
extern const volatile int8_T CAL_Hspf_CrashChkCntHiLim_u8;
extern const volatile int8_T CAL_Hspf_CrashChkCntLoLim_s8;
extern const volatile int8_T CAL_Hspf_CrashChkSubCnt_s8;
extern const volatile uint8_T CAL_Hspf_DBCTempROCLimChkCnt_u8;
extern const volatile uint8_T CAL_Hspf_INVOpenChkAddCnt_u8;
extern const volatile uint8_T CAL_Hspf_INVOpenChkCntHiLim_u8;
extern const volatile int8_T CAL_Hspf_INVOpenChkCntLoLim_s8;
extern const volatile int8_T CAL_Hspf_INVOpenChkSubCnt_s8;
extern const volatile uint8_T CAL_Hspf_MotTemHigTable_af32[1024];
extern const volatile int8_T CAL_Hspf_MotTemLowTable_af32[1024];
extern const volatile uint8_T CAL_Hspf_MotorOpenChkAddCnt_u8;
extern const volatile uint8_T CAL_Hspf_MotorOpenChkCntHiLim_u8;
extern const volatile int8_T CAL_Hspf_MotorOpenChkCntLoLim_s8;
extern const volatile int8_T CAL_Hspf_MototOpenChkSubCnt_s8;
extern const volatile uint8_T CAL_Hspf_Multiple_u8;
extern const volatile real32_T CAL_Hspf_TmpCoolanTjFltFrq_f32;
extern const volatile real32_T CAL_Hspf_TmpUFltFrq_f32;
extern const volatile real32_T CAL_Hspf_TmpVFltFrq_f32;
extern const volatile real32_T CAL_Hspf_TmpWFltFrq_f32;
extern const volatile int8_T CAL_Hspf_bt15ChkAddCnt_u8;
extern const volatile int8_T CAL_Hspf_bt15ChkCntHiLim_u8;
extern const volatile int8_T CAL_Hspf_bt15ChkCntLoLim_s8;
extern const volatile int8_T CAL_Hspf_bt15ChkSubCnt_s8;
extern const volatile uint16_T CAL_Hspf_cntIPhCalOffTolCnt_u16;
extern const volatile uint16_T CAL_Hspf_cntIPhCalOffValCnt_u16;
extern const volatile real32_T CAL_Hspf_iDcLnkEstFltFrq_f32;
extern const volatile uint16_T CAL_Hspf_iPhaHighSet_u16;
extern const volatile uint16_T CAL_Hspf_iPhaLowSet_u16;
extern const volatile real32_T CAL_Hspf_nFltFrq_f32;
extern const volatile uint8_T CAL_Hspf_stPreDrvCtl_u8;
extern const volatile real32_T CAL_Hspf_tCoolantFltFrq_f32;
extern const volatile uint16_T CAL_Hspf_tDBCCmpTime_u16;
extern const volatile uint8_T CAL_Hspf_tDBCTempROCLim_u8;
extern const volatile uint8_T CAL_Hspf_tDBCtempOffset_u8;
extern const volatile real32_T CAL_Hspf_tStrrTmp1FltFrq_f32;
extern const volatile real32_T CAL_Hspf_tStrrTmp2FltFrq_f32;
extern const volatile real32_T CAL_Hspf_tSwtTempSttrHiLim_f32;
extern const volatile real32_T CAL_Hspf_tSwtTempSttrLoLim_f32;
extern const volatile real32_T CAL_Hspf_uDcLnkFltFrq_f32;
extern const volatile real32_T CAL_Hspf_uKl30FltFrq_f32;
extern const volatile uint8_T CAL_MCF_ActiveHeatInit_u8;
extern const volatile uint8_T CAL_MCF_ActiveHeatNormal_u8;
extern const volatile real32_T CAL_MCF_AgDiffCurrSec_f32;
extern const volatile real32_T CAL_MCF_AgRangeDeadCpnX_Trq_af32[7];
extern const volatile real32_T CAL_MCF_AgRangeDeadCpnY_Ag_af32[7];
extern const volatile real32_T CAL_MCF_DeadTimeCpn_f32;
extern const volatile real32_T CAL_MCF_DeadTimeTableX_Frq_af32[15];
extern const volatile real32_T CAL_MCF_DeadTimeTableY_Ti_af32[15];
extern const volatile real32_T CAL_MCF_DeltaPower_f32;
extern const volatile real32_T CAL_MCF_DisChaisdDes_f32;
extern const volatile real32_T CAL_MCF_DisChaisqDes_f32;
extern const volatile real32_T CAL_MCF_DownLimitIMotHeat_f32;
extern const volatile real32_T CAL_MCF_DownLimitPIMotHeat_f32;
extern const volatile real32_T CAL_MCF_DycUSet_f32;
extern const volatile real32_T CAL_MCF_DycVSet_f32;
extern const volatile real32_T CAL_MCF_DycWSet_f32;
extern const volatile real32_T CAL_MCF_FfcTx_af32[11];
extern const volatile real32_T CAL_MCF_FfcTy_af32[11];
extern const volatile real32_T CAL_MCF_FixFreq_f32;
extern const volatile boolean_T CAL_MCF_FlgUpdateDyc_b;
extern const volatile boolean_T CAL_MCF_FlgUseDeadCpn_b;
extern const volatile boolean_T CAL_MCF_FlgUseSetDyc_b;
extern const volatile real32_T CAL_MCF_FrqRmp_f32;
extern const volatile real32_T CAL_MCF_HalfFreq_f32;
extern const volatile real32_T CAL_MCF_HarmIn1113ZRX_Spd_af32[23];
extern const volatile real32_T CAL_MCF_HarmIn11ZRY_Is_af32[23];
extern const volatile real32_T CAL_MCF_HarmIn11ZRY_Thetam_af32[23];
extern const volatile real32_T CAL_MCF_IsSet11ZR_f32;
extern const volatile real32_T CAL_MCF_IsThetaSet11ZR_f32;
extern const volatile real32_T CAL_MCF_KiMotHeat_f32;
extern const volatile real32_T CAL_MCF_KpMotHeat_f32;
extern const volatile uint8_T CAL_MCF_Non_ActiveHeat_u8;
extern const volatile real32_T CAL_MCF_OffsetInternal_f32;
extern const volatile real32_T CAL_MCF_OverPointSet_f32;
extern const volatile uint8_T CAL_MCF_Part_ActiveHeat_u8;
extern const volatile real32_T CAL_MCF_SpdActiveHeat_af32[9];
extern const volatile real32_T CAL_MCF_SpdOffActiveHeat_f32;
extern const volatile real32_T CAL_MCF_SpdOffDeadCpn_f32;
extern const volatile real32_T CAL_MCF_SpdOnDeadCpn_f32;
extern const volatile real32_T CAL_MCF_TrqOffActiveHeat_af32[9];
extern const volatile real32_T CAL_MCF_TrqOffDeadCpn_f32;
extern const volatile real32_T CAL_MCF_UpLimitIMotHeat_f32;
extern const volatile real32_T CAL_MCF_UpLimitPIMotHeat_f32;
extern const volatile real32_T CAL_MCF_UpPowerHeat_f32;
extern const volatile real32_T CAL_MCF_UsUseRateDesTableX_Spd_af32[11];
extern const volatile real32_T CAL_MCF_UsUseRateDesTableY_UsRes_af32[11];
extern const volatile real32_T CAL_MCF_UsdScalSet_f32;
extern const volatile real32_T CAL_MCF_UsqScalSet_f32;
extern const volatile boolean_T CAL_MCF_bUseduDclnkSet_b;
extern const volatile real32_T CAL_MCF_cofFltN_f32;
extern const volatile real32_T CAL_MCF_cofFltPowerHeat_f32;
extern const volatile real32_T CAL_MCF_cofFltWe_f32;
extern const volatile real32_T CAL_MCF_cofOverModu_f32;
extern const volatile boolean_T CAL_MCF_flgCalibOffset_b;
extern const volatile boolean_T CAL_MCF_flgDpwm_b;
extern const volatile boolean_T CAL_MCF_flgHarmInIsThetaTab11ZR_b;
extern const volatile boolean_T CAL_MCF_flgInternalOffset_b;
extern const volatile boolean_T CAL_MCF_flgLowOrHvudcLnk_b;
extern const volatile boolean_T CAL_MCF_flgMotHeat_b;
extern const volatile boolean_T CAL_MCF_flgNWS_b;
extern const volatile boolean_T CAL_MCF_flgOfsClbTest_b;
extern const volatile boolean_T CAL_MCF_flgOverModu_b;
extern const volatile boolean_T CAL_MCF_flgRpwmFrqRandom_b;
extern const volatile boolean_T CAL_MCF_flgUse1113ZR_b;
extern const volatile boolean_T CAL_MCF_flgUseFF_b;
extern const volatile boolean_T CAL_MCF_flgUseUsOver_b;
extern const volatile boolean_T CAL_MCF_flgUseUsdqSet_b;
extern const volatile boolean_T CAL_MCF_flgUseisTheta_b;
extern const volatile boolean_T CAL_MCF_flgUseisdqSet_b;
extern const volatile boolean_T CAL_MCF_flgVF_b;
extern const volatile real32_T CAL_MCF_iUCnvFac_f32;
extern const volatile real32_T CAL_MCF_iVCnvFac_f32;
extern const volatile real32_T CAL_MCF_iWCnvFac_f32;
extern const volatile real32_T CAL_MCF_isMax_f32;
extern const volatile real32_T CAL_MCF_isSet_f32;
extern const volatile real32_T CAL_MCF_isThetaSet_f32;
extern const volatile real32_T CAL_MCF_isdSet_f32;
extern const volatile real32_T CAL_MCF_isdfwKi_f32;
extern const volatile real32_T CAL_MCF_isdfwKp_f32;
extern const volatile real32_T CAL_MCF_isqSet_f32;
extern const volatile real32_T CAL_MCF_nDpwmOffDelay_f32;
extern const volatile real32_T CAL_MCF_nDpwmOff_f32;
extern const volatile real32_T CAL_MCF_perCpnAg_f32;
extern const volatile real32_T CAL_MCF_ratLo_f32;
extern const volatile real32_T CAL_MCF_ratNarrWave_f32;
extern const volatile real32_T CAL_MCF_ratUp_f32;
extern const volatile uint8_T CAL_MCF_stChangePha_u8;
extern const volatile uint8_T CAL_MCF_stDpwm_u8;
extern const volatile uint8_T CAL_MCF_stPwmMode_u8;
extern const volatile real32_T CAL_MCF_trqDpwmOff_f32;
extern const volatile real32_T CAL_MCF_uDclnkSet_f32;
extern const volatile real32_T CAL_MCF_udDecoupki_f32;
extern const volatile real32_T CAL_MCF_udOverGain_f32;
extern const volatile real32_T CAL_MCF_udki_f32;
extern const volatile real32_T CAL_MCF_udkp_f32;
extern const volatile real32_T CAL_MCF_uqDecoupki_f32;
extern const volatile real32_T CAL_MCF_uqOverGain_f32;
extern const volatile real32_T CAL_MCF_uqki_f32;
extern const volatile real32_T CAL_MCF_uqkp_f32;
extern const volatile real32_T CAL_MDF_3PhaUnbalance_f32;
extern const volatile real32_T CAL_MDF_DIffAlOfsMax_f32;
extern const volatile real32_T CAL_MDF_IsMaxSet_f32;
extern const volatile real32_T CAL_MDF_IsPhaseFault_f32;
extern const volatile real32_T CAL_MDF_OfsDeltaAgFltFrq_f32;
extern const volatile real32_T CAL_MDF_UdcFwMin_f32;
extern const volatile real32_T CAL_MDF_UsFrwhlMax_f32;
extern const volatile real32_T CAL_MDF_cofnAbsPhaseFault_Y_af32[46];
extern const volatile real32_T CAL_MDF_nAbsPhaseFault_X_af32[46];
extern const volatile real32_T CAL_MDF_nAbsPhaseFault_f32;
extern const volatile real32_T CAL_MDF_nThresAlOfsNoPlauseFaultMax_f32;
extern const volatile real32_T CAL_MDF_nThresAlOfsNoPlauseFaultMin_f32;
extern const volatile uint8_T CAL_MDF_stFrwhlPhd_u8;
extern const volatile uint8_T CAL_MDF_stFrwhlWiIs_u8;
extern const volatile uint8_T CAL_MDF_stFrwhlWoIs_u8;
extern const volatile real32_T CAL_MDF_tiAgComp_f32;
extern const volatile real32_T CAL_MDF_tiAlfOfsNoPlauseFault_f32;
extern const volatile real32_T CAL_MDF_tiOffsetSteady_f32;
extern const volatile real32_T CAL_MDF_tiPhaFaultDelay_f32;
extern const volatile real32_T CAL_MDF_trqOfsNoPlausFault_f32;
extern const volatile real32_T CAL_MPC_CofUdc_f32;
extern const volatile real32_T CAL_MPC_IsCutOffFrq_f32;
extern const volatile real32_T CAL_MPC_LdSubLqCAx_af32[18];
extern const volatile real32_T CAL_MPC_LdSubLqCAy_af32[15];
extern const volatile real32_T CAL_MPC_LdSubLqCAzGen_af32[270];
extern const volatile real32_T CAL_MPC_LdSubLqCAzMot_af32[270];
extern const volatile real32_T CAL_MPC_Ld_f32;
extern const volatile real32_T CAL_MPC_Lq_f32;
extern const volatile real32_T CAL_MPC_MtpaTableX_Trq_af32[15];
extern const volatile real32_T CAL_MPC_MtpaTableY_isd_af32[15];
extern const volatile real32_T CAL_MPC_MtpvTableX_Udc_af32[8];
extern const volatile real32_T CAL_MPC_MtpvTableY_N_af32[15];
extern const volatile real32_T CAL_MPC_MtpvTableZ_idGen_af32[120];
extern const volatile real32_T CAL_MPC_MtpvTableZ_idMot_af32[120];
extern const volatile real32_T CAL_MPC_OmbwTableX_Spd_af32[11];
extern const volatile real32_T CAL_MPC_OmbwTableY_Ombw_af32[11];
extern const volatile real32_T CAL_MPC_Psi_f32;
extern const volatile real32_T CAL_MPC_Rcmp_f32;
extern const volatile real32_T CAL_MPC_Rs_f32;
extern const volatile real32_T CAL_MPC_RvTableX_Spd_af32[11];
extern const volatile real32_T CAL_MPC_RvTableY_Rv_af32[11];
extern const volatile real32_T CAL_MPC_TrqMechCutOffFrq_f32;
extern const volatile real32_T CAL_MPC_cofRpwm_Y_af32[17];
extern const volatile boolean_T CAL_MPC_flgDesOrAct_b;
extern const volatile boolean_T CAL_MPC_flgUseLdSubLq_b;
extern const volatile boolean_T CAL_MPC_flgUseLdq_b;
extern const volatile boolean_T CAL_MPC_flgUseRs_b;
extern const volatile real32_T CAL_MPC_frqPwmVFTableX_Is_af32[11];
extern const volatile real32_T CAL_MPC_frqPwmVFTableY_VoltModuRate_af32[13];
extern const volatile real32_T CAL_MPC_frqPwmVFTableZ_Frq_af32[143];
extern const volatile real32_T CAL_MPC_idActCutOffFrq_f32;
extern const volatile real32_T CAL_MPC_iqActCutOffFrq_f32;
extern const volatile real32_T CAL_MPC_isdFFTableX_Spd_af32[17];
extern const volatile real32_T CAL_MPC_isdFFTableX_Udc_af32[8];
extern const volatile real32_T CAL_MPC_isdFFTableY_Trq_af32[17];
extern const volatile real32_T CAL_MPC_isdFFTableY_UdcCof_af32[8];
extern const volatile real32_T CAL_MPC_isdFFTableZ_isd_af32[289];
extern const volatile real32_T CAL_MPC_nCofRpwm_X_af32[17];
extern const volatile real32_T CAL_MPC_nSetTrqMonMin_f32;
extern const volatile real32_T CAL_MPC_nTrqMonMax_f32;
extern const volatile real32_T CAL_MPC_nTrqMonMin_f32;
extern const volatile real32_T CAL_MPC_tCpnBwdGenTableX_n_af32[16];
extern const volatile real32_T CAL_MPC_tCpnBwdGenTableY_tCpn_af32[16];
extern const volatile real32_T CAL_MPC_tCpnBwdMotTableX_n_af32[16];
extern const volatile real32_T CAL_MPC_tCpnBwdMotTableY_tCpn_af32[16];
extern const volatile real32_T CAL_MPC_tCpnFwdGenTableX_n_af32[16];
extern const volatile real32_T CAL_MPC_tCpnFwdGenTableY_tCpn_af32[16];
extern const volatile real32_T CAL_MPC_tCpnFwdMotTableX_n_af32[16];
extern const volatile real32_T CAL_MPC_tCpnFwdMotTableY_tCpn_af32[16];
extern const volatile real32_T CAL_MPC_udActCutOffFrq_f32;
extern const volatile real32_T CAL_MPC_uqActCutOffFrq_f32;
extern const volatile real32_T CAL_PowerMotHeat_f32;
extern const volatile real32_T CAL_RDC_NRestrict_f32;
extern const volatile boolean_T CAL_RDC_Switch_Ag_bool;
extern const volatile boolean_T CAL_RDC_flgCorrectOrReal_b;
extern const volatile real32_T CAL_RDC_tiRsvlAngleSample_f32;
extern const volatile boolean_T CAL_SCF_stMainRly_b;
extern const volatile boolean_T CAL_SCF_stPreChgRly_b;
extern const volatile real32_T CAL_TDC_DeltaT_f32;
extern const volatile real32_T CAL_TDC_KiNCtl_Y_Af32[10];
extern const volatile real32_T CAL_TDC_KpNCtl_Y_Af32[10];
extern const volatile real32_T CAL_TDC_TrqRamp_f32;
extern const volatile real32_T CAL_TDC_n_Error_X_Af32[10];
extern const volatile real32_T CAL_TDC_trqIncMax_f32;
extern const volatile real32_T CAL_TjCoolantFlowTab_af32[6];
extern const volatile real32_T CAL_TjDycMax_f32;
extern const volatile real32_T CAL_TjDycMin_f32;
extern const volatile real32_T CAL_Tj_cofFltCoolant_f32;
extern const volatile real32_T CAL_TjrthLv4DhIhTab_af32[6];
extern const volatile real32_T CAL_TjrthLv4IhIhTab_af32[6];
extern const volatile real32_T CAL_TjrthLv4IhNtcTab_af32[6];
extern const volatile real32_T CAL_TjrthLv4dhntc_f32;
extern const volatile real32_T CAL_TjrthLv4dlih_f32;
extern const volatile real32_T CAL_TjrthLv4dlntc_f32;
extern const volatile real32_T CAL_TjrthLv4ilih_f32;
extern const volatile real32_T CAL_TjrthLv4ilntc_f32;
extern const volatile uint8_T CAL_TjstUVW_u8;
extern const volatile uint16_T CAL_TpcBlk_BlkRevTimSet_u16;
extern const volatile uint16_T CAL_TpcBlk_BlkTimSet_u16;
extern const volatile real32_T CAL_TpcBlk_MtrBlkIsFirstSet_f32;
extern const volatile real32_T CAL_TpcBlk_MtrBlkIsSecondSet_f32;
extern const volatile real32_T CAL_TpcBlk_MtrBlkSpdHighSet_f32;
extern const volatile real32_T CAL_TpcBlk_MtrBlkSpdLowSet_f32;
extern const volatile real32_T CAL_TpcBlk_TrqBlkStab_f32;
extern const volatile real32_T CAL_TpcBlk_TrqDecRamp_f32;
extern const volatile real32_T CAL_TpcBlk_TrqIncRamp_f32;
extern const volatile boolean_T CAL_TpcBlk_flgEnBlkFun_b;
extern const volatile uint16_T CAL_TpcCod_CntHysteresislop_u16;
extern const volatile real32_T CAL_TpcCod_CoolFlow1LReq_f32;
extern const volatile real32_T CAL_TpcCod_CoolFlow2LTableX_Udc_af32[5];
extern const volatile real32_T CAL_TpcCod_CoolFlow2LTableY_Spd_af32[8];
extern const volatile real32_T CAL_TpcCod_CoolFlow2LTableZ_Trq_af32[40];
extern const volatile real32_T CAL_TpcCod_CoolFlow4LTableX_Udc_af32[5];
extern const volatile real32_T CAL_TpcCod_CoolFlow4LTableY_Spd_af32[8];
extern const volatile real32_T CAL_TpcCod_CoolFlow4LTableZ_Trq_af32[40];
extern const volatile real32_T CAL_TpcCod_CoolFlow6LTableX_Udc_af32[5];
extern const volatile real32_T CAL_TpcCod_CoolFlow6LTableY_Spd_af32[8];
extern const volatile real32_T CAL_TpcCod_CoolFlow6LTableZ_Trq_af32[40];
extern const volatile boolean_T CAL_TpcCod_FlgUseTrqLimRampSet_b;
extern const volatile boolean_T CAL_TpcCod_IGBTSampErr_b;
extern const volatile boolean_T CAL_TpcCod_MotorSampErr_b;
extern const volatile boolean_T CAL_TpcCod_MotorStallWarn_b;
extern const volatile real32_T CAL_TpcCod_NTCHighTemp_f32;
extern const volatile real32_T CAL_TpcCod_NTCLowTemp_f32;
extern const volatile real32_T CAL_TpcCod_NegSpdDirStop_f32;
extern const volatile real32_T CAL_TpcCod_NegTrqDirStop_f32;
extern const volatile real32_T CAL_TpcCod_PosSpdDirStop_f32;
extern const volatile real32_T CAL_TpcCod_PosSpdHold_f32;
extern const volatile real32_T CAL_TpcCod_PosSpdStart_f32;
extern const volatile real32_T CAL_TpcCod_PosTrqDirStop_f32;
extern const volatile real32_T CAL_TpcCod_PowIncRatLim_f32;
extern const volatile real32_T CAL_TpcCod_TrqRelay_f32;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv1_f32;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv2_f32;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv3_f32;
extern const volatile real32_T CAL_TpcFuv_CofPwrLimLv4_f32;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv1_f32;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv2_f32;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv3_f32;
extern const volatile real32_T CAL_TpcFuv_CofTrqLimLv4_f32;
extern const volatile real32_T CAL_TpcMot_ExCElecTableX_Udc_af32[10];
extern const volatile real32_T CAL_TpcMot_ExCElecTableY_Spd_af32[14];
extern const volatile real32_T CAL_TpcMot_ExCElecTableZ_Trq_af32[140];
extern const volatile real32_T CAL_TpcMot_ExCGenTableX_Udc_af32[10];
extern const volatile real32_T CAL_TpcMot_ExCGenTableY_Spd_af32[17];
extern const volatile real32_T CAL_TpcMot_ExCGenTableZ_Trq_af32[170];
extern const volatile real32_T CAL_TpcMot_SttrChgTempDownDiff_f32;
extern const volatile real32_T CAL_TpcMot_SttrChgTempUpDiff_f32;
extern const volatile real32_T CAL_TpcMot_SttrTempAdds_f32;
extern const volatile real32_T CAL_TpcMot_SttrTempDecDiff_f32;
extern const volatile real32_T CAL_TpcMot_SttrTempKp_f32;
extern const volatile real32_T CAL_TpcMot_SttrTempMinus_f32;
extern const volatile real32_T CAL_TpcMot_SttrTempRiseDiff_f32;
extern const volatile boolean_T CAL_TpcMot_flgPwrRefSwt_b;
extern const volatile boolean_T CAL_TpcMot_flgTrqRefSwt_b;
extern const volatile real32_T CAL_TpcMot_tRiseSttrDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcMot_tRiseSttrTraSave2ToOverheating_f32;
extern const volatile real32_T CAL_TpcMot_tSttrDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcMot_tSttrDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcMot_tSttrDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcMot_tSttrDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcMot_tSttrHiLim_f32;
extern const volatile real32_T CAL_TpcMot_tSttrLoLim_f32;
extern const volatile real32_T CAL_TpcMot_tSttrTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcMot_tSttrTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcMot_tSttrTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcMot_tSttrTraSave2ToOverheating_f32;
extern const volatile real32_T CAL_TpcMot_tSttrTrqLimRamp_f32;
extern const volatile uint8_T CAL_TpcSmp_CntElecOvrCurt_u8;
extern const volatile uint8_T CAL_TpcSmp_CntElecUdrVolt_u8;
extern const volatile uint8_T CAL_TpcSmp_CntGenOvrCurt_u8;
extern const volatile uint8_T CAL_TpcSmp_CntGenOvrVolt_u8;
extern const volatile boolean_T CAL_TpcSmp_CurtModeSelc_b;
extern const volatile real32_T CAL_TpcSmp_ElecOvrCurtKi_f32;
extern const volatile real32_T CAL_TpcSmp_ElecOvrCurtKp_f32;
extern const volatile real32_T CAL_TpcSmp_ElecOvrCurtypLim_f32;
extern const volatile real32_T CAL_TpcSmp_ElecUdrVoltKi_f32;
extern const volatile real32_T CAL_TpcSmp_ElecUdrVoltKp_f32;
extern const volatile real32_T CAL_TpcSmp_ElecUdrVoltypLim_f32;
extern const volatile uint8_T CAL_TpcSmp_FacElecOvrCurt_u8;
extern const volatile uint8_T CAL_TpcSmp_FacElecUdrVolt_u8;
extern const volatile uint8_T CAL_TpcSmp_FacGenOvrCurt_u8;
extern const volatile uint8_T CAL_TpcSmp_FacGenOvrVolt_u8;
extern const volatile real32_T CAL_TpcSmp_GenOvrCurtKi_f32;
extern const volatile real32_T CAL_TpcSmp_GenOvrCurtKp_f32;
extern const volatile real32_T CAL_TpcSmp_GenOvrCurtypLim_f32;
extern const volatile real32_T CAL_TpcSmp_GenOvrVoltKi_f32;
extern const volatile real32_T CAL_TpcSmp_GenOvrVoltKp_f32;
extern const volatile real32_T CAL_TpcSmp_GenOvrVoltypLim_f32;
extern const volatile real32_T CAL_TpcSmp_OvSpdWarnHiLim_f32;
extern const volatile real32_T CAL_TpcSmp_OvSpdWarnLoLim_f32;
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimElecTableX_iDc_af32[5];
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimElecTableY_Cof_af32[5];
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimGenTableX_iDc_af32[5];
extern const volatile real32_T CAL_TpcSmp_OvrCurtLimGenTableY_Cof_af32[5];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd1TableX_Spd_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd1TableY_Cof_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd2TableX_Spd_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd2TableY_Cof_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd3TableX_Spd_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd3TableY_Cof_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd4TableX_Spd_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrSpdQurd4TableY_Cof_af32[7];
extern const volatile real32_T CAL_TpcSmp_OvrVoltGenTableX_uDc_af32[5];
extern const volatile real32_T CAL_TpcSmp_OvrVoltGenTableY_Cof_af32[5];
extern const volatile real32_T CAL_TpcSmp_PwrAddMaxGen_f32;
extern const volatile real32_T CAL_TpcSmp_PwrAddMax_f32;
extern const volatile real32_T CAL_TpcSmp_SystemEffiElec_f32;
extern const volatile real32_T CAL_TpcSmp_SystemEffiGen_f32;
extern const volatile real32_T CAL_TpcSmp_ThresOverSpd_f32;
extern const volatile real32_T CAL_TpcSmp_TrqAddMaxGen_f32;
extern const volatile real32_T CAL_TpcSmp_TrqAddMax_f32;
extern const volatile real32_T CAL_TpcSmp_UdrVoltElecTableX_uDc_af32[5];
extern const volatile real32_T CAL_TpcSmp_UdrVoltElecTableY_Cof_af32[5];
extern const volatile boolean_T CAL_TpcSmp_flgUsePwrLossGen_b;
extern const volatile boolean_T CAL_TpcSmp_flgUsePwrLoss_b;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMaxMax_f32;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMaxMin_f32;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMinMax_f32;
extern const volatile real32_T CAL_TpcSmp_iDcLnkMinMin_f32;
extern const volatile real32_T CAL_TpcSmp_iDcLnkOvCElecLim_f32;
extern const volatile real32_T CAL_TpcSmp_iDcLnkOvCGenLim_f32;
extern const volatile uint8_T CAL_TpcSmp_nCtlExtReq_u8;
extern const volatile uint8_T CAL_TpcSmp_nCtlIntReq_u8;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMaxMax_f32;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMaxMin_f32;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMinMax_f32;
extern const volatile real32_T CAL_TpcSmp_uDcLnkMinMin_f32;
extern const volatile real32_T CAL_TpcSmp_uDcLnkOvVLim_f32;
extern const volatile real32_T CAL_TpcSmp_uDcLnkUnVLim_f32;
extern const volatile real32_T CAL_TpcTmp_CoolChgTempDownDiff_f32;
extern const volatile real32_T CAL_TpcTmp_CoolChgTempUpDiff_f32;
extern const volatile real32_T CAL_TpcTmp_CoolTempAdds_f32;
extern const volatile real32_T CAL_TpcTmp_CoolTempDecDiff_f32;
extern const volatile real32_T CAL_TpcTmp_CoolTempKp_f32;
extern const volatile real32_T CAL_TpcTmp_CoolTempMinus_f32;
extern const volatile real32_T CAL_TpcTmp_CoolTempRiseDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempAdds_f32;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempDecDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempKp_f32;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempMinus_f32;
extern const volatile real32_T CAL_TpcTmp_DBCRiseTempRiseDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DBCTempAdds_f32;
extern const volatile real32_T CAL_TpcTmp_DBCTempDecDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DBCTempKp_f32;
extern const volatile real32_T CAL_TpcTmp_DBCTempMinus_f32;
extern const volatile real32_T CAL_TpcTmp_DBCTempRiseDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DbcChgTempDownDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DbcChgTempUpDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DbcRiseChgTempDownDiff_f32;
extern const volatile real32_T CAL_TpcTmp_DbcRiseChgTempUpDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IGBRiseTTempAdds_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempDecDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempKp_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempMinus_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTRiseTempRiseDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTTempAdds_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTTempDecDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTTempKp_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTTempMinus_f32;
extern const volatile real32_T CAL_TpcTmp_IGBTTempRiseDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IgbtChgTempDownDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IgbtChgTempUpDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IgbtRiseChgTempDownDiff_f32;
extern const volatile real32_T CAL_TpcTmp_IgbtRiseChgTempUpDiff_f32;
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tCoolantDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tCoolantTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcTmp_tCoolantTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcTmp_tCoolantTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcTmp_tCoolantTraSave2ToOverheating_f32;
extern const volatile real32_T CAL_TpcTmp_tDBCTrqLimRamp_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tDbcDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tDbcTempUHiLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTempULoLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTempVHiLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTempVLoLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTempWHiLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTempWLoLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcThrPhLoLim_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcTmp_tDbcTraSave2ToOverheating_f32;
extern const volatile real32_T CAL_TpcTmp_tDrvboardDertTableX_tDrv_af32[9];
extern const volatile real32_T CAL_TpcTmp_tDrvboardDertTableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tIGBTTempHiLim_f32;
extern const volatile real32_T CAL_TpcTmp_tIGBTTempLoLim_f32;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcTmp_tIGBTTraSave2ToOverheating_f32;
extern const volatile real32_T CAL_TpcTmp_tIGBTTrqLimRamp_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseDbcTraSave2ToOverheating_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTDertSave1TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTDertSave1TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTDertSave2TableX_tSttr_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTDertSave2TableY_Cof_af32[9];
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraNormalToSave1_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraSave1ToNormal_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraSave1ToSave2_f32;
extern const volatile real32_T CAL_TpcTmp_tRiseIGBTTraSave2ToOverheating_f32;
extern const volatile uint8_T CAL_Tpc_NormalMode_u8;
extern const volatile uint8_T CAL_Tpc_OverheatingMode_u8;
extern const volatile uint8_T CAL_Tpc_Powersave1Mode_u8;
extern const volatile uint8_T CAL_Tpc_Powersave2Mode_u8;
extern const volatile real32_T CAL_Tpc_TrqReduceRevStep_f32;
extern const volatile real32_T CAL_Tpc_TrqRevStep_f32;
extern const volatile real32_T CAL_Tpc_TrqRiseRevStep_f32;
extern const volatile uint8_T CAL_Tpcmot_CofuDclnk_u8;
extern const volatile real32_T CAL_Tpcmot_TrqDiffExc_f32;
extern const volatile real32_T CAL_Tpcmot_TrqDiffGen_f32;
extern const volatile boolean_T CAL_Tpcmot_flgOpenExcLimRamp_b;
extern const volatile real32_T CAL_Tpcmot_uDcHiset_f32;
extern const volatile real32_T CAL_Tpcmot_uDcLoset_f32;
extern const volatile real32_T CAL_cofPowerLimitMotHeat_af32[9];
extern const volatile real32_T CAL_tStrrTempFltMotHeat_af32[9];
extern const volatile real32_T CAL_tiPwmLim_f32;
extern const volatile real32_T CAL_trqDesOvrdVal_f32;
extern const volatile boolean_T CAL_trqDesOvrdflg_f32;
extern const volatile real32_T CAL_trqMaxOvrdVal_f32;
extern const volatile boolean_T CAL_trqMaxOvrdflg_b;
extern const volatile real32_T CAL_trqMinOvrdVal_f32;
extern const volatile boolean_T CAL_trqMinOvrdflg_b;
extern const volatile int16_T DCEMS_sC_Nm_EngRefTorqDefault;
extern const volatile int16_T DCEMS_sC_Nm_EngRefTorqHighLmt;
extern const volatile int16_T DCEMS_sC_Nm_EngRefTorqLowLmt;
extern const volatile int16_T PMSM_Nm_EngDrvTorq_EEC1;
extern const volatile int16_T PMSM_Nm_HCUReqMCUTq_MCU1;
extern const volatile int16_T PMSM_Nm_HCUReqMCUTq_MCU2;
extern const volatile int16_T PMSM_Nm_ReferenceMCTorque_EC;
extern const volatile int16_T PMSM_Nm_ReqTqFric_MTR1;
extern const volatile int16_T PMSM_Nm_ReqTqFric_MTR2;
extern const volatile int16_T PMSM_Nm_ReqTqLimit_MTR1;
extern const volatile int16_T PMSM_Nm_ReqTqLimit_MTR2;
extern const volatile boolean_T PMSM_bool_ActvDischgCommand_MCU1;
extern const volatile boolean_T PMSM_bool_ActvDischgCommand_MCU2;
extern const volatile boolean_T PMSM_bool_CurrentGear_ETC2;
extern const volatile boolean_T PMSM_bool_EPSwitch_TC1HCU;
extern const volatile boolean_T PMSM_bool_EPSwitch_TC1Hd;
extern const volatile boolean_T PMSM_bool_EngDrvTorq_EEC1;
extern const volatile boolean_T PMSM_bool_EngPedal_EEC2;
extern const volatile boolean_T PMSM_bool_FootBrake_CCVS;
extern const volatile boolean_T PMSM_bool_GearRatio_ETC2;
extern const volatile boolean_T PMSM_bool_HCUAllowMotWorkEn_MCU1;
extern const volatile boolean_T PMSM_bool_HCUAllowMotWorkEn_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqAutoChgN_TC1HCU;
extern const volatile boolean_T PMSM_bool_HCUReqHiPowerOff_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqHiPowerOff_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqInhibitSftGear_TC1HCU;
extern const volatile boolean_T PMSM_bool_HCUReqMCUSpd_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMCUSpd_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqMCUTq_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMCUTq_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqMotRotaDir_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMotRotaDir_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqMotWorkMode_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMotWorkMode_MCU2;
extern const volatile boolean_T PMSM_bool_MsgSwitchC_TC1HCU;
extern const volatile boolean_T PMSM_bool_MsgSwitchL_TC1HCU;
extern const volatile boolean_T PMSM_bool_NegtvRelayState_MCU1;
extern const volatile boolean_T PMSM_bool_NegtvRelayState_MCU2;
extern const volatile boolean_T PMSM_bool_NmEngDrvTorq_EEC1;
extern const volatile boolean_T PMSM_bool_OverrideConModePriority_MTR1;
extern const volatile boolean_T PMSM_bool_OverrideConModePriority_MTR2;
extern const volatile boolean_T PMSM_bool_ParkingBrkSW_CCVS;
extern const volatile boolean_T PMSM_bool_PostvRelayState_MCU1;
extern const volatile boolean_T PMSM_bool_PostvRelayState_MCU2;
extern const volatile boolean_T PMSM_bool_PreChargHiVoltRelayState_MCU1;
extern const volatile boolean_T PMSM_bool_PreChargHiVoltRelayState_MCU2;
extern const volatile boolean_T PMSM_bool_ReferenceMCTorque_EC;
extern const volatile boolean_T PMSM_bool_ReqSpdContCond_MTR1;
extern const volatile boolean_T PMSM_bool_ReqSpdContCond_MTR2;
extern const volatile boolean_T PMSM_bool_ReqSpdLimit_MTR1;
extern const volatile boolean_T PMSM_bool_ReqSpdLimit_MTR2;
extern const volatile boolean_T PMSM_bool_ReqTqFric_MTR1;
extern const volatile boolean_T PMSM_bool_ReqTqFric_MTR2;
extern const volatile boolean_T PMSM_bool_ReqTqLimit_MTR1;
extern const volatile boolean_T PMSM_bool_ReqTqLimit_MTR2;
extern const volatile boolean_T PMSM_bool_SelectGear_ETC2;
extern const volatile boolean_T PMSM_bool_ShiftInProcess_ETC1;
extern const volatile boolean_T PMSM_bool_TMCurAvalMaxSpeed_MCU1;
extern const volatile boolean_T PMSM_bool_TMCurAvalMaxSpeed_MCU2;
extern const volatile boolean_T PMSM_bool_TransmissionRequestedGear_TC1HCU;
extern const volatile boolean_T PMSM_bool_TransmissionRequestedGear_TC1Hd;
extern const volatile boolean_T PMSM_bool_overridConMode_MTR1;
extern const volatile boolean_T PMSM_bool_overridConMode_MTR2;
extern const volatile uint8_T PMSM_gear_CurrentGear_ETC2;
extern const volatile uint8_T PMSM_gear_SelectGear_ETC2;
extern const volatile uint8_T PMSM_gear_TransmissionRequestedGear_TC1HCU;
extern const volatile uint8_T PMSM_gear_TransmissionRequestedGear_TC1Hd;
extern const volatile uint8_T PMSM_mod_HCUReqMotWorkMode_MCU1;
extern const volatile uint8_T PMSM_mod_HCUReqMotWorkMode_MCU2;
extern const volatile uint8_T PMSM_overridConMode_MTR1;
extern const volatile uint8_T PMSM_overridConMode_MTR2;
extern const volatile int16_T PMSM_perc_EngDrvTorq_EEC1;
extern const volatile int16_T PMSM_perc_EngPedal_EEC2;
extern const volatile int16_T PMSM_rpm_HCUReqMCUSpd_MCU1;
extern const volatile int16_T PMSM_rpm_HCUReqMCUSpd_MCU2;
extern const volatile int16_T PMSM_rpm_ReqSpdLimit_MTR1;
extern const volatile int16_T PMSM_rpm_ReqSpdLimit_MTR2;
extern const volatile int16_T PMSM_rpm_TMCurAvalMaxSpeed_MCU1;
extern const volatile int16_T PMSM_rpm_TMCurAvalMaxSpeed_MCU2;
extern const volatile uint8_T PMSM_sC_OverrideConModePriority_MTR1;
extern const volatile uint8_T PMSM_sC_OverrideConModePriority_MTR2;
extern const volatile uint8_T PMSM_sC_ReqSpdContCond_MTR1;
extern const volatile uint8_T PMSM_sC_ReqSpdContCond_MTR2;
extern const volatile uint8_T PMSM_sC_bool_FootBrake_CCVS;
extern const volatile uint8_T PMSM_st_ActvDischgCommand_MCU1;
extern const volatile uint8_T PMSM_st_ActvDischgCommand_MCU2;
extern const volatile uint8_T PMSM_st_EPSwitch_TC1HCU;
extern const volatile uint8_T PMSM_st_EPSwitch_TC1Hd;
extern const volatile uint8_T PMSM_st_HCUAllowMotWorkEn_MCU1;
extern const volatile uint8_T PMSM_st_HCUAllowMotWorkEn_MCU2;
extern const volatile uint8_T PMSM_st_HCUReqAutoChgN_TC1HCU;
extern const volatile uint8_T PMSM_st_HCUReqHiPowerOff_MCU1;
extern const volatile uint8_T PMSM_st_HCUReqHiPowerOff_MCU2;
extern const volatile uint8_T PMSM_st_HCUReqInhibitSftGear_TC1HCU;
extern const volatile uint8_T PMSM_st_HCUReqMotRotaDir_MCU1;
extern const volatile uint8_T PMSM_st_HCUReqMotRotaDir_MCU2;
extern const volatile uint8_T PMSM_st_MsgSwitchC_TC1HCU;
extern const volatile uint8_T PMSM_st_MsgSwitchL_TC1HCU;
extern const volatile uint8_T PMSM_st_NegtvRelayState_MCU1;
extern const volatile uint8_T PMSM_st_NegtvRelayState_MCU2;
extern const volatile uint8_T PMSM_st_ParkingBrkSW_CCVS;
extern const volatile uint8_T PMSM_st_PostvRelayState_MCU1;
extern const volatile uint8_T PMSM_st_PostvRelayState_MCU2;
extern const volatile uint8_T PMSM_st_PreChargHiVoltRelayState_MCU1;
extern const volatile uint8_T PMSM_st_PreChargHiVoltRelayState_MCU2;
extern const volatile uint8_T PMSM_st_ShiftInProcess_ETC1;
extern const volatile int16_T PMSM_z_GearRatio_ETC2;
extern const volatile real32_T RDC_COSTABLE[4096];
extern const volatile real32_T RDC_SINTABLE[4096];

#pragma section

extern RT_MODEL_FM_T *const FM_M;

#endif

