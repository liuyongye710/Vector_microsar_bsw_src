#ifndef RTW_HEADER_SWC_MPC_IG_h_
#define RTW_HEADER_SWC_MPC_IG_h_
#include <math.h>
#ifndef SWC_MPC_IG_COMMON_INCLUDES_
#define SWC_MPC_IG_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_MPC_IG_types.h"

#define MPC_GLB_MotorPole_u8           4U
#define MPC_GLB_SqrtTwo_f32            1.41421294F
#define MPC_GLB_pi_f32                 3.14159203F
#define PRV_CalFltFrq_2ms              500.0F

#ifndef SWC_MPC_IG_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay_DSTATE;
  real32_T UnitDelay_DSTATE_f;
  real32_T UnitDelay_DSTATE_o;
  real32_T UnitDelay_DSTATE_g;
  real32_T UnitDelay_DSTATE_od;
  real32_T UnitDelay_DSTATE_k;
  boolean_T UnitDelay_DSTATE_h;
} DW_SWC_MPC_IG_f_T;

#endif

#ifndef SWC_MPC_IG_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_MPC_IG_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_MPC_IG_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_MPC_IG_T rtm;
} MdlrefDW_SWC_MPC_IG_T;

#endif

extern real32_T MPC_idActFlt;
extern real32_T MPC_iqActFlt;
extern real32_T MPC_Ld;
extern real32_T MPC_Lq;
extern real32_T MPC_LdSubLq;
extern real32_T MPC_psiExc;
extern real32_T MPC_TrqMechFlt;
extern real32_T MPC_dtCorFac;
extern real32_T MPC_Rs;
extern real32_T MPC_TrqMech;
extern real32_T MPC_IsFlt;
extern real32_T MPC_isdMTPA;
extern real32_T MPC_isdFF;
extern real32_T MPC_isdMTPV;
extern real32_T MPC_OmBw;
extern real32_T MPC_Rv;
extern real32_T VAR_MPC_frqPwmVF_f32;
extern real32_T MPC_frqPwmVF;
extern real32_T VAR_MPC_CofRandomPwm_f32;
extern real32_T MPC_CofRandomPwm;
extern real32_T VAR_MPC_TrqMon_f32;
extern void SWC_MPC_IG(const real32_T *rtu_MCF_BUS_MCF_idDes, const real32_T
  *rtu_MCF_BUS_MCF_iqDes, const real32_T *rtu_MCF_BUS_MCF_udDes, const real32_T *
  rtu_MCF_BUS_MCF_Is, const real32_T *rtu_MCF_BUS_MCF_idAct, const real32_T
  *rtu_MCF_BUS_MCF_iqAct, const real32_T *rtu_MCF_BUS_MCF_uDcLnk, const real32_T
  *rtu_MCF_BUS_MCF_VoltModuRate, const real32_T *rtu_TDC_BUS_TDC_TrqDes, const
  real32_T *rtu_HSPF_BUS_HSPF_nSlowFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const uint8_T *rtu_TPC_BUS_TPC_stMotorMod,
  real32_T *rty_MPC_BUS_MPC_LdSubLq, real32_T *rty_MPC_BUS_MPC_Ld, real32_T
  *rty_MPC_BUS_MPC_Lq, real32_T *rty_MPC_BUS_MPC_Rs, real32_T
  *rty_MPC_BUS_MPC_TrqMech, real32_T *rty_MPC_BUS_MPC_TrqMechFlt, real32_T
  *rty_MPC_BUS_MPC_psiExc, real32_T *rty_MPC_BUS_MPC_IsFlt, real32_T
  *rty_MPC_BUS_MPC_idActFlt, real32_T *rty_MPC_BUS_MPC_iqActFlt, real32_T
  *rty_MPC_BUS_MPC_dtCorFac, real32_T *rty_MPC_BUS_MPC_isdMTPA, real32_T
  *rty_MPC_BUS_MPC_isdFF, real32_T *rty_MPC_BUS_MPC_isdMTPV, real32_T
  *rty_MPC_BUS_MPC_OmBw, real32_T *rty_MPC_BUS_MPC_Rv, real32_T
  *rty_MPC_BUS_MPC_frqPwmVF, real32_T *rty_MPC_BUS_MPC_CofRandomPwm);
extern void SWC_MPC_IG_initialize(const char_T **rt_errorStatus);

#pragma section ".CAL_CONST"

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

#pragma section

#ifndef SWC_MPC_IG_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_MPC_IG_T SWC_MPC_IG_MdlrefDW;

#endif

#ifndef SWC_MPC_IG_MDLREF_HIDE_CHILD_

extern DW_SWC_MPC_IG_f_T SWC_MPC_IG_DW;

#endif
#endif

