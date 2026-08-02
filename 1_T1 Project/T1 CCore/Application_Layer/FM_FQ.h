#ifndef RTW_HEADER_FM_FQ_h_
#define RTW_HEADER_FM_FQ_h_
#include <stddef.h>
#ifndef FM_FQ_COMMON_INCLUDES_
#define FM_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "FM_FQ_types.h"

#include "model_reference_types.h"

#define SWC_MPC_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_MPC_IG_FQ.h"
#define SWC_TDC_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_TDC_IG_FQ.h"
#define SWC_TPC_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_TPC_IG_FQ.h"
#define SWC_MDF_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_MDF_IG_FQ.h"
#define SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_SCF_IG_FQ.h"
#define SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_HSPF_IG_FQ.h"
#define SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_BCC_IG_FQ.h"
#define SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_MCF_IG_FQ.h"
#define SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_
#include "SWC_SMO_IG_FQ.h"

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

#define CAL_Hspf_Failure_u8_FQ         3U
#define CAL_Hspf_Succeed_u8_FQ         2U
#define CAL_Hspf_Uncheck_u8_FQ         0U
#define CAL_TDC_go_nCtlExtReq_u8_FQ    1U
#define GLB_HspfFlt_pi_f32_FQ          3.14159203F
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
#define MCF_ANGLE_CURRENT_150_FQ       150.0F
#define MCF_ANGLE_CURRENT_210_FQ       210.0F
#define MCF_ANGLE_CURRENT_270_FQ       270.0F
#define MCF_ANGLE_CURRENT_30_FQ        30.0F
#define MCF_ANGLE_CURRENT_330_FQ       330.0F
#define MCF_ANGLE_CURRENT_90_FQ        90.0F
#define MCF_CURRENT_SECTOR_1_FQ        1U
#define MCF_CURRENT_SECTOR_2_FQ        2U
#define MCF_CURRENT_SECTOR_3_FQ        3U
#define MCF_CURRENT_SECTOR_4_FQ        4U
#define MCF_CURRENT_SECTOR_5_FQ        5U
#define MCF_CURRENT_SECTOR_6_FQ        6U
#define MCF_GLB_CircAge_f32_FQ         360.0F
#define MCF_GLB_DigtValue_u16_FQ       4096U
#define MCF_GLB_MotorPole_u8_FQ        4U
#define MCF_GLB_OneHalf_f32_FQ         0.5F
#define MCF_GLB_Sixty_f32_FQ           60.0F
#define MCF_GLB_SqrtThree_f32_FQ       1.73205101F
#define MCF_GLB_pi_f32_FQ              3.14159203F
#define MCF_Succeed_u8_FQ              2U
#define MDF_GLB_IGBTrun_u8_FQ          3U
#define MDF_GLB_MotorPole_u8_FQ        4U
#define MDF_GLB_pi_f32_FQ              3.14159203F
#define MPC_GLB_MotorPole_u8_FQ        4U
#define MPC_GLB_SqrtTwo_f32_FQ         1.41421294F
#define MPC_GLB_pi_f32_FQ              3.14159203F
#define PRV_CalFltFrq_10ms_FQ          100U
#define PRV_CalFltFrq_2ms_FQ           500.0F

typedef struct {
  real32_T MPC_LdSubLq;
  real32_T MPC_Ld;
  real32_T MPC_Lq;
  real32_T MPC_Rs;
  real32_T MPC_TrqMech;
  real32_T MPC_TrqMechFlt;
  real32_T MPC_psiExc;
  real32_T MPC_IsFlt;
  real32_T MPC_idActFlt;
  real32_T MPC_iqActFlt;
  real32_T MPC_dtCorFac;
  real32_T MPC_isdMTPA;
  real32_T MPC_isdFF;
  real32_T MPC_isdMTPV;
  real32_T MPC_OmBw;
  real32_T MPC_Rv;
  real32_T MPC_frqPwmVF;
  real32_T MPC_CofRandomPwm;
  real32_T TDC_TrqDes;
  real32_T TPC_TrqMax;
  real32_T TPC_TrqMin;
  real32_T TPC_TDbcTrqMax;
  real32_T TPC_TrqMaxTrans;
  real32_T TPC_TrqMinTrans;
  real32_T TPC_o25;
  real32_T HSPF_uKl30Flt;
  real32_T HSPF_tDBCTempUFlt;
  real32_T HSPF_tDBCTempVFlt;
  real32_T HSPF_tDBCTempWFlt;
  real32_T HSPF_tStrrTemp1Flt;
  real32_T HSPF_tStrrTemp2Flt;
  real32_T HSPF_nSlowFlt;
  real32_T HSPF_tCoolantTempFlt;
  real32_T HSPF_tDrvBoardTempFlt;
  real32_T HSPF_iDcLnkEstFlt;
  real32_T HSPF_PwrDcLnk;
  real32_T HSPF_uDcLnkSlowFlt;
  real32_T HSPF_iPhaUOffset;
  real32_T HSPF_iPhaVOffset;
  real32_T HSPF_iPhaWOffset;
  real32_T HSPF_tStrrTempFlt;
  real32_T HSPF_tIGBTTjFlt;
  real32_T HSPF_tCoolantTjFlt;
  real32_T HSPF_VerMatchFailureErr;
  real32_T BCC_iDcLnkEst;
  real32_T BCC_tIGBTTj;
  real32_T BCC_tCoolantTj;
  real32_T MCF_idDes;
  real32_T MCF_iqDes;
  real32_T MCF_udDes;
  real32_T MCF_uqDes;
  real32_T MCF_dycU;
  real32_T MCF_dycV;
  real32_T MCF_dycW;
  real32_T MCF_frqPwm;
  real32_T MCF_cofFrqPwm;
  real32_T MCF_dtPwm;
  real32_T MCF_tiLock;
  real32_T MCF_Is;
  real32_T MCF_idAct;
  real32_T MCF_iqAct;
  real32_T MCF_uDcLnk;
  real32_T MCF_iU;
  real32_T MCF_iV;
  real32_T MCF_iW;
  real32_T MCF_VoltModuRate;
  real32_T MCF_ialpha;
  real32_T MCF_ibeta;
  real32_T MCF_uAlCalc;
  real32_T MCF_uBCalc;
  real32_T SMO_Observer_o1;
  real32_T SMO_Observer_o2;
  real32_T SMO_Observer_o3;
  uint8_T TPC_stTrqEmMax;
  uint8_T TPC_stTrqEmMin;
  uint8_T TPC_stMotorMod;
  uint8_T TPC_SgnRotDir;
  uint8_T TPC_SgnTrqMechDir;
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
  uint8_T SCF_stSysCtl;
  uint8_T SCF_stGateDrv;
  uint8_T SCF_stDrvCtl;
  uint8_T SCF_stDisChg;
  uint8_T SCF_stPreDrvCtl;
  uint8_T SCF_stSys;
  uint8_T SCF_stModeReqToTdc;
  uint8_T SCF_stPwmMode;
  uint8_T SCF_stFFAction;
  uint8_T SCF_FIM_ReqFailrMod;
  uint8_T SCF_stMotor_state;
  uint8_T SCF_flginitEn_Nctl;
  uint8_T SCF_flgZReset;
  uint8_T HSPF_stIphaOffCal;
  uint8_T HSPF_tDBCTempCmpErrSt;
  uint8_T HSPF_MotorOpenErrSt;
  uint8_T HSPF_InvOpenErrSt;
  uint8_T HSPF_checkstatus;
  uint8_T MCF_SecVolt;
  uint8_T MCF_stpwmMode;
  boolean_T TDC_flgTrqLmtActv;
  boolean_T TPC_bDernExcMax;
  boolean_T TPC_bDernExcMin;
  boolean_T TPC_bDernStrTemp;
  boolean_T TPC_bDernDbcTemp;
  boolean_T TPC_bDernCoolantTemp;
  boolean_T TPC_bDernDrvBoardTemp;
  boolean_T TPC_bDernMtrSpd;
  boolean_T TPC_bDernUndrUdc;
  boolean_T TPC_bDernOvrUdc;
  boolean_T TPC_bDernCAN;
  boolean_T TPC_bDernElecOvrIdc;
  boolean_T TPC_bDernGenOvrIdc;
  boolean_T TPC_bDernOvrIdc;
  boolean_T TPC_bDernIGBTTemp;
  boolean_T SCF_flgDataStrgBgnToBsw;
  boolean_T SCF_flginitPI;
  boolean_T SCF_flgEnDchaToMc;
  boolean_T SCF_flgUdcLowToTpc;
  boolean_T SCF_bHvReady_write;
  boolean_T SCF_flgEmgReqInvDcha;
  boolean_T SCF_flgActvDcha;
  boolean_T SCF_LwPwrDwn;
  boolean_T HSPF_bt15;
  boolean_T HSPF_Crash;
  boolean_T HSPF_INV_Open;
  boolean_T HSPF_Motor_Open;
  boolean_T HSPF_Wake;
  boolean_T HSPF_bSwtTempSttr1;
  boolean_T HSPF_bSwtTempSttr2;
} B_FM_FQ_T;

struct tag_RTM_FM_FQ_T {
  const char_T *errorStatus;
  struct {
    uint32_T clockTick1;
    uint32_T clockTick3;
  } Timing;
};

extern B_FM_FQ_T FM_FQ_B;
extern real32_T RDC_agRtrEe_FQ;
extern uint16_T iUNoOff_FQ;
extern uint16_T iVNoOff_FQ;
extern uint16_T iWNoOff_FQ;
extern real32_T uDcLnk_FQ;
extern uint16_T tDBCTempU_FQ;
extern uint16_T tDBCTempV_FQ;
extern uint16_T tDBCTempW_FQ;
extern real32_T VAR_Hspf_uKl30_f32_FQ;
extern boolean_T VAR_Bsw_bt15_b_FQ;
extern uint8_T VAR_ccvs_hcu_u8_FQ;
extern uint8_T VAR_hcu_mcu_u8_FQ;
extern boolean_T VAR_flg_ov_b_FQ;
extern boolean_T VAR_flg_oc_b_FQ;
extern void FM_FQ_initialize(void);
extern void FM_FQ_terminate(void);
extern void tri_100us_FQ(void);
extern void tri_2ms_FQ(void);
extern void tri_10ms_FQ(void);

#pragma section ".CAL_CONST"

extern const volatile real32_T CAL_BCC_AgGenCoe_f32_FQ;
extern const volatile real32_T CAL_BCC_dycLowLimt_f32_FQ;
extern const volatile real32_T CAL_BCC_dycUpLimt_f32_FQ;
extern const volatile boolean_T CAL_BCC_flgDelayDyc_b_FQ;
extern const volatile boolean_T CAL_BCC_flgEnableIdc_b_FQ;
extern const volatile boolean_T CAL_BCC_flgEnableTj_b_FQ;
extern const volatile real32_T CAL_BCC_iDcEstflt_f32_FQ;
extern const volatile real32_T CAL_BCC_tiFull_f32_FQ;
extern const volatile real32_T CAL_CoolantFlowReq_u8_FQ;
extern const volatile real32_T CAL_Hspf_CltInletTempFltFrq_f32_FQ;
extern const volatile uint8_T CAL_Hspf_CrashChkAddCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_CrashChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_CrashChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_CrashChkSubCnt_s8_FQ;
extern const volatile uint8_T CAL_Hspf_DBCTempROCLimChkCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_INVOpenChkAddCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_INVOpenChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_INVOpenChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_INVOpenChkSubCnt_s8_FQ;
extern const volatile uint8_T CAL_Hspf_MotTemHigTable_af32_FQ[1024];
extern const volatile int8_T CAL_Hspf_MotTemLowTable_af32_FQ[1024];
extern const volatile uint8_T CAL_Hspf_MotorOpenChkAddCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_MotorOpenChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_MotorOpenChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_MototOpenChkSubCnt_s8_FQ;
extern const volatile uint8_T CAL_Hspf_Multiple_u8_FQ;
extern const volatile real32_T CAL_Hspf_TmpCoolanTjFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_TmpUFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_TmpVFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_TmpWFltFrq_f32_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkAddCnt_u8_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkSubCnt_s8_FQ;
extern const volatile uint16_T CAL_Hspf_cntIPhCalOffTolCnt_u16_FQ;
extern const volatile uint16_T CAL_Hspf_cntIPhCalOffValCnt_u16_FQ;
extern const volatile real32_T CAL_Hspf_iDcLnkEstFltFrq_f32_FQ;
extern const volatile uint16_T CAL_Hspf_iPhaHighSet_u16_FQ;
extern const volatile uint16_T CAL_Hspf_iPhaLowSet_u16_FQ;
extern const volatile real32_T CAL_Hspf_nFltFrq_f32_FQ;
extern const volatile uint8_T CAL_Hspf_stPreDrvCtl_u8_FQ;
extern const volatile real32_T CAL_Hspf_tCoolantFltFrq_f32_FQ;
extern const volatile uint16_T CAL_Hspf_tDBCCmpTime_u16_FQ;
extern const volatile uint8_T CAL_Hspf_tDBCTempROCLim_u8_FQ;
extern const volatile uint8_T CAL_Hspf_tDBCtempOffset_u8_FQ;
extern const volatile real32_T CAL_Hspf_tStrrTmp1FltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_tStrrTmp2FltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_tSwtTempSttrHiLim_f32_FQ;
extern const volatile real32_T CAL_Hspf_tSwtTempSttrLoLim_f32_FQ;
extern const volatile real32_T CAL_Hspf_uDcLnkFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_uKl30FltFrq_f32_FQ;
extern const volatile uint8_T CAL_MCF_ActiveHeatInit_u8_FQ;
extern const volatile uint8_T CAL_MCF_ActiveHeatNormal_u8_FQ;
extern const volatile real32_T CAL_MCF_AgDiffCurrSec_f32_FQ;
extern const volatile real32_T CAL_MCF_AgRangeDeadCpnX_Trq_af32_FQ[7];
extern const volatile real32_T CAL_MCF_AgRangeDeadCpnY_Ag_af32_FQ[7];
extern const volatile real32_T CAL_MCF_DeadTimeCpn_f32_FQ;
extern const volatile real32_T CAL_MCF_DeadTimeTableX_Frq_af32_FQ[15];
extern const volatile real32_T CAL_MCF_DeadTimeTableY_Ti_af32_FQ[15];
extern const volatile real32_T CAL_MCF_DeltaPower_f32_FQ;
extern const volatile real32_T CAL_MCF_DisChaisdDes_f32_FQ;
extern const volatile real32_T CAL_MCF_DisChaisqDes_f32_FQ;
extern const volatile real32_T CAL_MCF_DownLimitIMotHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_DownLimitPIMotHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_DycUSet_f32_FQ;
extern const volatile real32_T CAL_MCF_DycVSet_f32_FQ;
extern const volatile real32_T CAL_MCF_DycWSet_f32_FQ;
extern const volatile real32_T CAL_MCF_FfcTx_af32_FQ[11];
extern const volatile real32_T CAL_MCF_FfcTy_af32_FQ[11];
extern const volatile real32_T CAL_MCF_FixFreq_f32_FQ;
extern const volatile boolean_T CAL_MCF_FlgUpdateDyc_b_FQ;
extern const volatile boolean_T CAL_MCF_FlgUseDeadCpn_b_FQ;
extern const volatile boolean_T CAL_MCF_FlgUseSetDyc_b_FQ;
extern const volatile real32_T CAL_MCF_FrqRmp_f32_FQ;
extern const volatile real32_T CAL_MCF_HalfFreq_f32_FQ;
extern const volatile real32_T CAL_MCF_HarmIn1113ZRX_Spd_af32_FQ[23];
extern const volatile real32_T CAL_MCF_HarmIn11ZRY_Is_af32_FQ[23];
extern const volatile real32_T CAL_MCF_HarmIn11ZRY_Thetam_af32_FQ[23];
extern const volatile real32_T CAL_MCF_IsSet11ZR_f32_FQ;
extern const volatile real32_T CAL_MCF_IsThetaSet11ZR_f32_FQ;
extern const volatile real32_T CAL_MCF_KiMotHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_KpMotHeat_f32_FQ;
extern const volatile uint8_T CAL_MCF_Non_ActiveHeat_u8_FQ;
extern const volatile real32_T CAL_MCF_OffsetInternal_f32_FQ;
extern const volatile real32_T CAL_MCF_OverPointSet_f32_FQ;
extern const volatile uint8_T CAL_MCF_Part_ActiveHeat_u8_FQ;
extern const volatile real32_T CAL_MCF_SpdActiveHeat_af32_FQ[9];
extern const volatile real32_T CAL_MCF_SpdOffActiveHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_SpdOffDeadCpn_f32_FQ;
extern const volatile real32_T CAL_MCF_SpdOnDeadCpn_f32_FQ;
extern const volatile real32_T CAL_MCF_TrqOffActiveHeat_af32_FQ[9];
extern const volatile real32_T CAL_MCF_TrqOffDeadCpn_f32_FQ;
extern const volatile real32_T CAL_MCF_UpLimitIMotHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_UpLimitPIMotHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_UpPowerHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_UsUseRateDesTableX_Spd_af32_FQ[11];
extern const volatile real32_T CAL_MCF_UsUseRateDesTableY_UsRes_af32_FQ[11];
extern const volatile real32_T CAL_MCF_UsdScalSet_f32_FQ;
extern const volatile real32_T CAL_MCF_UsqScalSet_f32_FQ;
extern const volatile boolean_T CAL_MCF_bUseduDclnkSet_b_FQ;
extern const volatile real32_T CAL_MCF_cofFltN_f32_FQ;
extern const volatile real32_T CAL_MCF_cofFltPowerHeat_f32_FQ;
extern const volatile real32_T CAL_MCF_cofFltWe_f32_FQ;
extern const volatile real32_T CAL_MCF_cofOverModu_f32_FQ;
extern const volatile boolean_T CAL_MCF_flgCalibOffset_b_FQ;
extern const volatile boolean_T CAL_MCF_flgDpwm_b_FQ;
extern const volatile boolean_T CAL_MCF_flgHarmInIsThetaTab11ZR_b_FQ;
extern const volatile boolean_T CAL_MCF_flgInternalOffset_b_FQ;
extern const volatile boolean_T CAL_MCF_flgLowOrHvudcLnk_b_FQ;
extern const volatile boolean_T CAL_MCF_flgMotHeat_b_FQ;
extern const volatile boolean_T CAL_MCF_flgNWS_b_FQ;
extern const volatile boolean_T CAL_MCF_flgOfsClbTest_b_FQ;
extern const volatile boolean_T CAL_MCF_flgOverModu_b_FQ;
extern const volatile boolean_T CAL_MCF_flgRpwmFrqRandom_b_FQ;
extern const volatile boolean_T CAL_MCF_flgUse1113ZR_b_FQ;
extern const volatile boolean_T CAL_MCF_flgUseFF_b_FQ;
extern const volatile boolean_T CAL_MCF_flgUseUsOver_b_FQ;
extern const volatile boolean_T CAL_MCF_flgUseUsdqSet_b_FQ;
extern const volatile boolean_T CAL_MCF_flgUseisTheta_b_FQ;
extern const volatile boolean_T CAL_MCF_flgUseisdqSet_b_FQ;
extern const volatile boolean_T CAL_MCF_flgVF_b_FQ;
extern const volatile real32_T CAL_MCF_iUCnvFac_f32_FQ;
extern const volatile real32_T CAL_MCF_iVCnvFac_f32_FQ;
extern const volatile real32_T CAL_MCF_iWCnvFac_f32_FQ;
extern const volatile real32_T CAL_MCF_isMax_f32_FQ;
extern const volatile real32_T CAL_MCF_isSet_f32_FQ;
extern const volatile real32_T CAL_MCF_isThetaSet_f32_FQ;
extern const volatile real32_T CAL_MCF_isdSet_f32_FQ;
extern const volatile real32_T CAL_MCF_isdfwKi_f32_FQ;
extern const volatile real32_T CAL_MCF_isdfwKp_f32_FQ;
extern const volatile real32_T CAL_MCF_isqSet_f32_FQ;
extern const volatile real32_T CAL_MCF_nDpwmOffDelay_f32_FQ;
extern const volatile real32_T CAL_MCF_nDpwmOff_f32_FQ;
extern const volatile real32_T CAL_MCF_perCpnAg_f32_FQ;
extern const volatile real32_T CAL_MCF_ratLo_f32_FQ;
extern const volatile real32_T CAL_MCF_ratNarrWave_f32_FQ;
extern const volatile real32_T CAL_MCF_ratUp_f32_FQ;
extern const volatile uint8_T CAL_MCF_stChangePha_u8_FQ;
extern const volatile uint8_T CAL_MCF_stDpwm_u8_FQ;
extern const volatile uint8_T CAL_MCF_stPwmMode_u8_FQ;
extern const volatile real32_T CAL_MCF_trqDpwmOff_f32_FQ;
extern const volatile real32_T CAL_MCF_uDclnkSet_f32_FQ;
extern const volatile real32_T CAL_MCF_udDecoupki_f32_FQ;
extern const volatile real32_T CAL_MCF_udOverGain_f32_FQ;
extern const volatile real32_T CAL_MCF_udki_f32_FQ;
extern const volatile real32_T CAL_MCF_udkp_f32_FQ;
extern const volatile real32_T CAL_MCF_uqDecoupki_f32_FQ;
extern const volatile real32_T CAL_MCF_uqOverGain_f32_FQ;
extern const volatile real32_T CAL_MCF_uqki_f32_FQ;
extern const volatile real32_T CAL_MCF_uqkp_f32_FQ;
extern const volatile real32_T CAL_MDF_3PhaUnbalance_f32_FQ;
extern const volatile real32_T CAL_MDF_DIffAlOfsMax_f32_FQ;
extern const volatile real32_T CAL_MDF_IsMaxSet_f32_FQ;
extern const volatile real32_T CAL_MDF_IsPhaseFault_f32_FQ;
extern const volatile real32_T CAL_MDF_OfsDeltaAgFltFrq_f32_FQ;
extern const volatile real32_T CAL_MDF_UdcFwMin_f32_FQ;
extern const volatile real32_T CAL_MDF_UsFrwhlMax_f32_FQ;
extern const volatile real32_T CAL_MDF_cofnAbsPhaseFault_Y_af32_FQ[46];
extern const volatile real32_T CAL_MDF_nAbsPhaseFault_X_af32_FQ[46];
extern const volatile real32_T CAL_MDF_nAbsPhaseFault_f32_FQ;
extern const volatile real32_T CAL_MDF_nThresAlOfsNoPlauseFaultMax_f32_FQ;
extern const volatile real32_T CAL_MDF_nThresAlOfsNoPlauseFaultMin_f32_FQ;
extern const volatile uint8_T CAL_MDF_stFrwhlPhd_u8_FQ;
extern const volatile uint8_T CAL_MDF_stFrwhlWiIs_u8_FQ;
extern const volatile uint8_T CAL_MDF_stFrwhlWoIs_u8_FQ;
extern const volatile real32_T CAL_MDF_tiAgComp_f32_FQ;
extern const volatile real32_T CAL_MDF_tiAlfOfsNoPlauseFault_f32_FQ;
extern const volatile real32_T CAL_MDF_tiOffsetSteady_f32_FQ;
extern const volatile real32_T CAL_MDF_tiPhaFaultDelay_f32_FQ;
extern const volatile real32_T CAL_MDF_trqOfsNoPlausFault_f32_FQ;
extern const volatile real32_T CAL_MPC_CofUdc_f32_FQ;
extern const volatile real32_T CAL_MPC_IsCutOffFrq_f32_FQ;
extern const volatile real32_T CAL_MPC_LdSubLqCAx_af32_FQ[18];
extern const volatile real32_T CAL_MPC_LdSubLqCAy_af32_FQ[15];
extern const volatile real32_T CAL_MPC_LdSubLqCAzGen_af32_FQ[270];
extern const volatile real32_T CAL_MPC_LdSubLqCAzMot_af32_FQ[270];
extern const volatile real32_T CAL_MPC_Ld_f32_FQ;
extern const volatile real32_T CAL_MPC_Lq_f32_FQ;
extern const volatile real32_T CAL_MPC_MtpaTableX_Trq_af32_FQ[16];
extern const volatile real32_T CAL_MPC_MtpaTableY_isd_af32_FQ[16];
extern const volatile real32_T CAL_MPC_MtpvTableX_Udc_af32_FQ[8];
extern const volatile real32_T CAL_MPC_MtpvTableY_N_af32_FQ[15];
extern const volatile real32_T CAL_MPC_MtpvTableZ_idGen_af32_FQ[120];
extern const volatile real32_T CAL_MPC_MtpvTableZ_idMot_af32_FQ[120];
extern const volatile real32_T CAL_MPC_OmbwTableX_Spd_af32_FQ[11];
extern const volatile real32_T CAL_MPC_OmbwTableY_Ombw_af32_FQ[11];
extern const volatile real32_T CAL_MPC_Psi_f32_FQ;
extern const volatile real32_T CAL_MPC_Rcmp_f32_FQ;
extern const volatile real32_T CAL_MPC_Rs_f32_FQ;
extern const volatile real32_T CAL_MPC_RvTableX_Spd_af32_FQ[11];
extern const volatile real32_T CAL_MPC_RvTableY_Rv_af32_FQ[11];
extern const volatile real32_T CAL_MPC_TrqMechCutOffFrq_f32_FQ;
extern const volatile real32_T CAL_MPC_cofRpwm_Y_af32_FQ[17];
extern const volatile boolean_T CAL_MPC_flgDesOrAct_b_FQ;
extern const volatile boolean_T CAL_MPC_flgUseLdSubLq_b_FQ;
extern const volatile boolean_T CAL_MPC_flgUseLdq_b_FQ;
extern const volatile boolean_T CAL_MPC_flgUseRs_b_FQ;
extern const volatile real32_T CAL_MPC_frqPwmVFTableX_Is_af32_FQ[11];
extern const volatile real32_T CAL_MPC_frqPwmVFTableY_VoltModuRate_af32_FQ[13];
extern const volatile real32_T CAL_MPC_frqPwmVFTableZ_Frq_af32_FQ[143];
extern const volatile real32_T CAL_MPC_idActCutOffFrq_f32_FQ;
extern const volatile real32_T CAL_MPC_iqActCutOffFrq_f32_FQ;
extern const volatile real32_T CAL_MPC_isdFFTableX_Spd_af32_FQ[17];
extern const volatile real32_T CAL_MPC_isdFFTableX_Udc_af32_FQ[8];
extern const volatile real32_T CAL_MPC_isdFFTableY_Trq_af32_FQ[17];
extern const volatile real32_T CAL_MPC_isdFFTableY_UdcCof_af32_FQ[8];
extern const volatile real32_T CAL_MPC_isdFFTableZ_isd_af32_FQ[289];
extern const volatile real32_T CAL_MPC_nCofRpwm_X_af32_FQ[17];
extern const volatile real32_T CAL_MPC_nSetTrqMonMin_f32_FQ;
extern const volatile real32_T CAL_MPC_nTrqMonMax_f32_FQ;
extern const volatile real32_T CAL_MPC_nTrqMonMin_f32_FQ;
extern const volatile real32_T CAL_MPC_tCpnBwdGenTableX_n_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnBwdGenTableY_tCpn_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnBwdMotTableX_n_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnBwdMotTableY_tCpn_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnFwdGenTableX_n_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnFwdGenTableY_tCpn_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnFwdMotTableX_n_af32_FQ[16];
extern const volatile real32_T CAL_MPC_tCpnFwdMotTableY_tCpn_af32_FQ[16];
extern const volatile real32_T CAL_MPC_udActCutOffFrq_f32_FQ;
extern const volatile real32_T CAL_MPC_uqActCutOffFrq_f32_FQ;
extern const volatile real32_T CAL_PowerMotHeat_f32_FQ;
extern const volatile boolean_T CAL_SCF_stMainRly_b_FQ;
extern const volatile uint8_T CAL_SCF_stModeReq_b_FQ;
extern const volatile boolean_T CAL_SCF_stPreChgRly_b_FQ;
extern const volatile real32_T CAL_SMO_NmSp_f32_FQ;
extern const volatile real32_T CAL_TDC_DeltaT_f32_FQ;
extern const volatile real32_T CAL_TDC_KiNCtl_Y_Af32_FQ[10];
extern const volatile real32_T CAL_TDC_KpNCtl_Y_Af32_FQ[10];
extern const volatile real32_T CAL_TDC_TrqRamp_f32_FQ;
extern const volatile real32_T CAL_TDC_n_Error_X_Af32_FQ[10];
extern const volatile real32_T CAL_TDC_trqIncMax_f32_FQ;
extern const volatile real32_T CAL_TjCoolantFlowTab_af32_FQ[6];
extern const volatile real32_T CAL_TjDycMax_f32_FQ;
extern const volatile real32_T CAL_TjDycMin_f32_FQ;
extern const volatile real32_T CAL_Tj_cofFltCoolant_f32_FQ;
extern const volatile real32_T CAL_TjrthLv4DhIhTab_af32_FQ[6];
extern const volatile real32_T CAL_TjrthLv4IhIhTab_af32_FQ[6];
extern const volatile real32_T CAL_TjrthLv4IhNtcTab_af32_FQ[6];
extern const volatile real32_T CAL_TjrthLv4dhntc_f32_FQ;
extern const volatile real32_T CAL_TjrthLv4dlih_f32_FQ;
extern const volatile real32_T CAL_TjrthLv4dlntc_f32_FQ;
extern const volatile real32_T CAL_TjrthLv4ilih_f32_FQ;
extern const volatile real32_T CAL_TjrthLv4ilntc_f32_FQ;
extern const volatile uint8_T CAL_TjstUVW_u8_FQ;
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
extern const volatile real32_T CAL_cofPowerLimitMotHeat_af32_FQ[9];
extern const volatile real32_T CAL_tStrrTempFltMotHeat_af32_FQ[9];
extern const volatile real32_T CAL_tiPwmLim_f32_FQ;
extern const volatile real32_T CAL_trqDesOvrdVal_f32_FQ;
extern const volatile boolean_T CAL_trqDesOvrdflg_f32_FQ;
extern const volatile real32_T CAL_trqMaxOvrdVal_f32_FQ;
extern const volatile boolean_T CAL_trqMaxOvrdflg_b_FQ;
extern const volatile real32_T CAL_trqMinOvrdVal_f32_FQ;
extern const volatile boolean_T CAL_trqMinOvrdflg_b_FQ;

#pragma section

extern RT_MODEL_FM_FQ_T *const FM_FQ_M;

#endif

