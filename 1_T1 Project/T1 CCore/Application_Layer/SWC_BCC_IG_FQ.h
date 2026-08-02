#ifndef RTW_HEADER_SWC_BCC_IG_FQ_h_
#define RTW_HEADER_SWC_BCC_IG_FQ_h_
#include <math.h>
#ifndef SWC_BCC_IG_FQ_COMMON_INCLUDES_
#define SWC_BCC_IG_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_BCC_IG_FQ_types.h"

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay3;
  real32_T UnitDelay2;
} B_SWC_BCC_IG_FQ_c_T;

#endif

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay_DSTATE;
  real32_T UnitDelay1_DSTATE;
  real32_T UnitDelay2_DSTATE;
  real32_T UnitDelay3_DSTATE;
  real32_T UnitDelay2_DSTATE_e;
  real32_T UnitDelay_DSTATE_e;
  real32_T UnitDelay_DSTATE_g;
  real32_T UnitDelay_DSTATE_c;
  real32_T UnitDelay_DSTATE_n;
  real32_T UnitDelay_DSTATE_k;
  uint8_T UnitDelay_DSTATE_h;
  boolean_T Tj_MODE;
  boolean_T uTjCal1_MODE;
} DW_SWC_BCC_IG_FQ_f_T;

#endif

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  const boolean_T RelationalOperator;
  const boolean_T RelationalOperator1;
  const boolean_T RelationalOperator2;
  const boolean_T RelationalOperator3;
  const boolean_T RelationalOperator4;
  const boolean_T RelationalOperator5;
} ConstB_SWC_BCC_IG_FQ_h_T;

#endif

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_BCC_IG_FQ_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_BCC_IG_FQ_T rtm;
} MdlrefDW_SWC_BCC_IG_FQ_T;

#endif

extern real32_T BCC_tIGBTTj_FQ;
extern real32_T BCC_tCoolantTj_FQ;
extern real32_T VAR_UTjpwr_f32_FQ;
extern real32_T VAR_UCoolantTj_f32_FQ;
extern real32_T VAR_UihTjtIGBT_f32_FQ;
extern real32_T VAR_BCC_iDcLnkEst_f32_FQ;
extern real32_T VAR_BCC_iDcLnkEstFlt_f32_FQ;
extern real32_T BCE_iDcLnkEst_FQ;
extern boolean_T VAR_BCC_flgstGateDrv_b_FQ;
extern void SWC_BCC_IG_FQ_Disable(void);
extern void SWC_BCC_IG_FQ(const real32_T *rtu_MCF_BUS_MCF_dycU, const real32_T
  *rtu_MCF_BUS_MCF_dycV, const real32_T *rtu_MCF_BUS_MCF_dycW, const uint8_T
  *rtu_MCF_BUS_MCF_SecVolt, const real32_T *rtu_MCF_BUS_MCF_frqPwm, const
  real32_T *rtu_MCF_BUS_MCF_tiLock, const real32_T *rtu_MCF_BUS_MCF_iU, const
  real32_T *rtu_MCF_BUS_MCF_iV, const real32_T *rtu_MCF_BUS_MCF_iW, const
  uint8_T *rtu_TPC_BUS_TPC_stMotorMod, const real32_T
  *rtu_HSPF_BUS_HSPF_tDBCTempUFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_tDBCTempVFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_tDBCTempWFlt, const real32_T
  *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const uint8_T *rtu_SCF_BUS_SCF_stGateDrv,
  real32_T *rty_BCC_BUS_BCC_iDcLnkEst, real32_T *rty_BCC_BUS_BCC_tIGBTTj,
  real32_T *rty_BCC_BUS_BCC_tCoolantTj);
extern void SWC_BCC_IG_FQ_initialize(const char_T **rt_errorStatus);

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
extern const volatile real32_T CAL_tiPwmLim_f32_FQ;

#pragma section

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_BCC_IG_FQ_T SWC_BCC_IG_FQ_MdlrefDW;

#endif

#ifndef SWC_BCC_IG_FQ_MDLREF_HIDE_CHILD_

extern B_SWC_BCC_IG_FQ_c_T SWC_BCC_IG_FQ_B;
extern DW_SWC_BCC_IG_FQ_f_T SWC_BCC_IG_FQ_DW;

#endif
#endif

