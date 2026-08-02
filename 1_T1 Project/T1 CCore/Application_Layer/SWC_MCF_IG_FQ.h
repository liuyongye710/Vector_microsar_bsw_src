#ifndef RTW_HEADER_SWC_MCF_IG_FQ_h_
#define RTW_HEADER_SWC_MCF_IG_FQ_h_
#include <math.h>
#ifndef SWC_MCF_IG_FQ_COMMON_INCLUDES_
#define SWC_MCF_IG_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_MCF_IG_FQ_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

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

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T MCF_udDes11ZR;
  real32_T MCF_uqDes11ZR;
  real32_T MCF_uAlphaDeadCpn;
  real32_T MCF_uBetaDeadCpn;
  real32_T uDLookupTable;
  real32_T Switch;
} B_SWC_MCF_IG_FQ_c_T;

#endif

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay2_DSTATE;
  real32_T UnitDelay_DSTATE;
  real32_T UnitDelay_DSTATE_m;
  real32_T UnitDelay2_DSTATE_e;
  real32_T UnitDelay_DSTATE_h;
  real32_T Delay2_DSTATE;
  real32_T Delay3_DSTATE;
  real32_T Delay_DSTATE;
  real32_T UnitDelay_DSTATE_n;
  real32_T Delay1_DSTATE;
  real32_T UnitDelay1_DSTATE;
  real32_T UnitDelay_DSTATE_l;
  real32_T UnitDelay_DSTATE_m0;
  real32_T UnitDelay_1_DSTATE;
  real32_T UnitDelay_2_DSTATE;
  real32_T UnitDelay_3_DSTATE;
  real32_T UnitDelay_DSTATE_e;
  real32_T UnitDelay_DSTATE_g;
  uint16_T UnitDelay1_DSTATE_c;
  boolean_T UnitDelay_DSTATE_i;
  boolean_T UnitDelay_DSTATE_c;
  boolean_T UnitDelay_DSTATE_hv;
} DW_SWC_MCF_IG_FQ_f_T;

#endif

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_MCF_IG_FQ_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_MCF_IG_FQ_T rtm;
} MdlrefDW_SWC_MCF_IG_FQ_T;

#endif

extern real32_T MCF_frqPwm_FQ;
extern real32_T MCF_cofFrqPwm_FQ;
extern real32_T VAR_MCF_uDcLnk_f32_FQ;
extern real32_T MCF_uDcLnk_FQ;
extern real32_T VAR_MCF_iU_NC_f32_FQ;
extern real32_T VAR_MCF_iV_NC_f32_FQ;
extern real32_T VAR_MCF_iW_NC_f32_FQ;
extern real32_T VAR_MCF_iU_f32_FQ;
extern real32_T MCF_iU_FQ;
extern real32_T VAR_MCF_iV_f32_FQ;
extern real32_T MCF_iV_FQ;
extern real32_T VAR_MCF_iW_f32_FQ;
extern real32_T MCF_iW_FQ;
extern real32_T VAR_MCF_agOffset_f32_FQ;
extern real32_T VAR_MCF_agRtrEe_f32_FQ;
extern real32_T VAR_MCF_idAct_f32_FQ;
extern real32_T MCF_idAct_FQ;
extern real32_T VAR_MCF_periodCalc_f32_FQ;
extern real32_T VAR_MCF_UsUseRateDes_f32_FQ;
extern real32_T VAR_MCF_isdFW_f32_FQ;
extern real32_T VAR_MCF_idMotHeat_f32_FQ;
extern real32_T VAR_MCF_idDes_f32_FQ;
extern real32_T MCF_idDes_FQ;
extern real32_T VAR_MCF_iqAct_f32_FQ;
extern real32_T MCF_iqAct_FQ;
extern real32_T VAR_MCF_udRv_f32_FQ;
extern real32_T VAR_MCF_MPC_Ld_f32_FQ;
extern real32_T VAR_MCF_Rdc_nWoFlt_f32_FQ;
extern real32_T VAR_MCF_MPC_Lq_f32_FQ;
extern real32_T VAR_MCF_EmfBack_f32_FQ;
extern real32_T VAR_MCF_uqRv_f32_FQ;
extern real32_T VAR_MCF_udDes_f32_FQ;
extern real32_T MCF_udDes_FQ;
extern real32_T VAR_MCF_uqDes_f32_FQ;
extern real32_T MCF_uqDes_FQ;
extern real32_T VAR_MCF_MPC_LdSubLq_f32_FQ;
extern real32_T VAR_MCF_iqDes_f32_FQ;
extern real32_T MCF_iqDes_FQ;
extern real32_T MCF_dtPwm_FQ;
extern real32_T VAR_MCF_UdDes11ZR_f32_FQ;
extern real32_T VAR_MCF_UqDes11ZR_f32_FQ;
extern real32_T VAR_MCF_uAOfsClb_f32_FQ;
extern real32_T VAR_MCF_uBOfsClb_f32_FQ;
extern real32_T VAR_MCF_uBetaDeadCpn_f32_FQ;
extern real32_T VAR_MCF_uAlphaDeadCpn_f32_FQ;
extern real32_T MCF_dycU_FQ;
extern real32_T MCF_dycV_FQ;
extern real32_T MCF_dycW_FQ;
extern real32_T MCF_tiLock_FQ;
extern real32_T VAR_MCF_Is_f32_FQ;
extern real32_T MCF_Is_FQ;
extern real32_T VAR_MCF_UsUseRateReal_f32_FQ;
extern real32_T VAR_MCF_usPeak_f32_FQ;
extern real32_T VAR_MCF_AgRem_f32_FQ;
extern real32_T MCF_VoltModuRate_FQ;
extern real32_T VAR_MCF_uAOm_f32_FQ;
extern real32_T VAR_MCF_uBOm_f32_FQ;
extern real32_T VAR_MCF_IsSet11ZR_f32_FQ;
extern real32_T VAR_MCF_IsThetaSet11ZR_f32_FQ;
extern real32_T VAR_MCF_PCUHeaterPower_f32_FQ;
extern real32_T VAR_MCF_PowerDcLnk_f32_FQ;
extern real32_T VAR_MCF_PowerMech_f32_FQ;
extern real32_T VAR_MCF_PowerMotHeat_f32_FQ;
extern uint8_T VAR_MCF_HSPF_stIphaOffCal_u8_FQ;
extern uint8_T MCF_SecVolt_FQ;
extern uint8_T MCF_stpwmMode_FQ;
extern uint8_T VAR_MCF_TMAhtChsts_f32_FQ;
extern boolean_T VAR_MCF_flgMotHeat_b_FQ;
extern boolean_T VAR_MCF_SCF_flgInitEn_b_FQ;
extern boolean_T VAR_MCF_FlgDeadCpn_b_FQ;
extern boolean_T VAR_MCF_flgFw_b_FQ;
extern void SWC_MCF_IG_FQ(const real32_T *rtu_HSPF_BUS_HSPF_iPhaUOffset, const
  real32_T *rtu_HSPF_BUS_HSPF_iPhaVOffset, const real32_T
  *rtu_HSPF_BUS_HSPF_iPhaWOffset, const uint8_T *rtu_HSPF_BUS_HSPF_stIphaOffCal,
  const real32_T *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const real32_T
  *rtu_MPC_BUS_MPC_LdSubLq, const real32_T *rtu_MPC_BUS_MPC_Ld, const real32_T
  *rtu_MPC_BUS_MPC_Lq, const real32_T *rtu_MPC_BUS_MPC_Rs, const real32_T
  *rtu_MPC_BUS_MPC_TrqMechFlt, const real32_T *rtu_MPC_BUS_MPC_psiExc, const
  real32_T *rtu_MPC_BUS_MPC_isdMTPA, const real32_T *rtu_MPC_BUS_MPC_isdFF,
  const real32_T *rtu_MPC_BUS_MPC_isdMTPV, const real32_T *rtu_MPC_BUS_MPC_OmBw,
  const real32_T *rtu_MPC_BUS_MPC_Rv, const real32_T *rtu_MPC_BUS_MPC_frqPwmVF,
  const real32_T *rtu_MPC_BUS_MPC_CofRandomPwm, const real32_T
  *rtu_TDC_trqDes_TDC_TrqDes, const real32_T *rtu_BCC_BUS_BCC_iDcLnkEst, const
  real32_T *rtu_RDC_agRtrEe, const uint16_T *rtu_CDD_iUNoOff, const uint16_T
  *rtu_CDD_iVNoOf, const uint16_T *rtu_CDD_iWNoOf, const real32_T
  *rtu_CDD_uDcLnk, const real32_T *rtu_Rdc_nWoFlt, const boolean_T
  *rtu_SCF_BUS_SCF_flginitPI, const boolean_T *rtu_SCF_BUS_SCF_flgEnDchaToMc,
  const uint8_T *rtu_SCF_BUS_SCF_stPwmMode, const real32_T *rtu_SMO_iq_ref,
  real32_T *rty_MCF_BUS_MCF_idDes, real32_T *rty_MCF_BUS_MCF_iqDes, real32_T
  *rty_MCF_BUS_MCF_udDes, real32_T *rty_MCF_BUS_MCF_uqDes, real32_T
  *rty_MCF_BUS_MCF_dycU, real32_T *rty_MCF_BUS_MCF_dycV, real32_T
  *rty_MCF_BUS_MCF_dycW, uint8_T *rty_MCF_BUS_MCF_SecVolt, real32_T
  *rty_MCF_BUS_MCF_frqPwm, real32_T *rty_MCF_BUS_MCF_cofFrqPwm, real32_T
  *rty_MCF_BUS_MCF_dtPwm, real32_T *rty_MCF_BUS_MCF_tiLock, uint8_T
  *rty_MCF_BUS_MCF_stpwmMode, real32_T *rty_MCF_BUS_MCF_Is, real32_T
  *rty_MCF_BUS_MCF_idAct, real32_T *rty_MCF_BUS_MCF_iqAct, real32_T
  *rty_MCF_BUS_MCF_uDcLnk, real32_T *rty_MCF_BUS_MCF_iU, real32_T
  *rty_MCF_BUS_MCF_iV, real32_T *rty_MCF_BUS_MCF_iW, real32_T
  *rty_MCF_BUS_MCF_VoltModuRate, real32_T *rty_MCF_BUS_MCF_ialpha, real32_T
  *rty_MCF_BUS_MCF_ibeta, real32_T *rty_MCF_BUS_MCF_uAlCalc, real32_T
  *rty_MCF_BUS_MCF_uBCalc);
extern void SWC_MCF_IG_FQ_initialize(const char_T **rt_errorStatus);

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

extern void SWC_MCF_IG_FQ_Osc_nrN6(real32_T rtu_MCF_tiY, real32_T rtu_MCF_tiZ,
  real32_T *rty_MCF_tiYout, real32_T *rty_MCF_tiZout);

#endif

#pragma section ".CAL_CONST"

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
extern const volatile real32_T CAL_PowerMotHeat_f32_FQ;
extern const volatile real32_T CAL_cofPowerLimitMotHeat_af32_FQ[9];
extern const volatile real32_T CAL_tStrrTempFltMotHeat_af32_FQ[9];

#pragma section

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_MCF_IG_FQ_T SWC_MCF_IG_FQ_MdlrefDW;

#endif

#ifndef SWC_MCF_IG_FQ_MDLREF_HIDE_CHILD_

extern B_SWC_MCF_IG_FQ_c_T SWC_MCF_IG_FQ_B;
extern DW_SWC_MCF_IG_FQ_f_T SWC_MCF_IG_FQ_DW;

#endif
#endif

