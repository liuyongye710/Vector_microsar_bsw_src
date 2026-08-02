#ifndef RTW_HEADER_SWC_TDC_IG_h_
#define RTW_HEADER_SWC_TDC_IG_h_
#include <math.h>
#ifndef SWC_TDC_IG_COMMON_INCLUDES_
#define SWC_TDC_IG_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_TDC_IG_types.h"

#define CAL_TDC_go_nCtlExtReq_u8       1U

#ifndef SWC_TDC_IG_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay_DSTATE;
  real32_T UnitDelay_DSTATE_f;
  real32_T UnitDelay2_DSTATE;
} DW_SWC_TDC_IG_f_T;

#endif

#ifndef SWC_TDC_IG_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_TDC_IG_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_TDC_IG_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_TDC_IG_T rtm;
} MdlrefDW_SWC_TDC_IG_T;

#endif

extern real32_T VAR_TDC_trqRmp_f32;
extern real32_T TDC_TrqDes;
extern boolean_T TDC_flgTrqLmtActv;
extern void SWC_TDC_IG(const real32_T *rtu_TPC_BUS_TPC_TrqMax, const real32_T
  *rtu_TPC_BUS_TPC_TrqMin, const real32_T *rtu_Rdc_nWoFlt, const real32_T
  *rtu_CSPF_BUS_Nm_HCUReqMCUTq, const real32_T *rtu_CSPF_BUS_rpm_HCUReqMCUSpd,
  const uint8_T *rtu_SCF_BUS_SCF_stModeReqToTdc, real32_T
  *rty_TDC_BUS_TDC_TrqDes, boolean_T *rty_TDC_BUS_TDC_flgTrqLmtActv);
extern void SWC_TDC_IG_initialize(const char_T **rt_errorStatus);

#pragma section ".CAL_CONST"

extern const volatile real32_T CAL_TDC_DeltaT_f32;
extern const volatile real32_T CAL_TDC_KiNCtl_Y_Af32[10];
extern const volatile real32_T CAL_TDC_KpNCtl_Y_Af32[10];
extern const volatile real32_T CAL_TDC_TrqRamp_f32;
extern const volatile real32_T CAL_TDC_n_Error_X_Af32[10];
extern const volatile real32_T CAL_TDC_trqIncMax_f32;
extern const volatile real32_T CAL_trqDesOvrdVal_f32;
extern const volatile boolean_T CAL_trqDesOvrdflg_f32;

#pragma section

#ifndef SWC_TDC_IG_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_TDC_IG_T SWC_TDC_IG_MdlrefDW;

#endif

#ifndef SWC_TDC_IG_MDLREF_HIDE_CHILD_

extern DW_SWC_TDC_IG_f_T SWC_TDC_IG_DW;

#endif
#endif

