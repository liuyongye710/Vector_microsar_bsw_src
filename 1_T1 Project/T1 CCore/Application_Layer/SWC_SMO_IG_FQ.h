#ifndef RTW_HEADER_SWC_SMO_IG_FQ_h_
#define RTW_HEADER_SWC_SMO_IG_FQ_h_
#include <math.h>
#ifndef SWC_SMO_IG_FQ_COMMON_INCLUDES_
#define SWC_SMO_IG_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_SMO_IG_FQ_types.h"

#include "model_reference_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

#ifndef SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay_DSTATE;
  real32_T UnitDelay1_DSTATE;
  real32_T UnitDelay3_DSTATE;
  real32_T DiscreteTimeIntegrator_DSTATE;
  real32_T UnitDelay4_DSTATE;
  real32_T Integrator_DSTATE;
  real32_T Delay_DSTATE;
  real32_T UnitDelay2_DSTATE;
  real32_T UnitDelay2_DSTATE_g;
  real32_T UnitDelay5_DSTATE;
  real32_T DiscreteTimeIntegrator1_DSTATE;
  real32_T UnitDelay_DSTATE_j;
  real32_T DiscreteTimeIntegrator_DSTATE_i;
  real32_T DiscreteTimeIntegrator1_DSTAT_k;
  real32_T DiscreteTimeIntegrator_PREV_U;
  real32_T Integrator_PREV_U;
  real32_T DiscreteTimeIntegrator1_PREV_U;
  real32_T DiscreteTimeIntegrator_PREV_U_n;
  real32_T DiscreteTimeIntegrator1_PREV__e;
  uint32_T TmpModelReferenceSubsystem_ELAP;
  uint32_T TmpModelReferenceSubsystem_PREV;
  uint32_T IfActionSubsystem4_ELAPS_T;
  uint32_T IfActionSubsystem4_PREV_T;
  uint32_T IfActionSubsystem2_ELAPS_T;
  uint32_T IfActionSubsystem2_PREV_T;
  int8_T SwitchCase1_ActiveSubsystem;
  int8_T DiscreteTimeIntegrator_PrevRese;
  int8_T DiscreteTimeIntegrator1_PrevRes;
  uint8_T DiscreteTimeIntegrator_SYSTEM_E;
  uint8_T Integrator_SYSTEM_ENABLE;
  uint8_T DiscreteTimeIntegrator1_SYSTEM_;
  uint8_T DiscreteTimeIntegrator_SYSTEM_m;
  uint8_T DiscreteTimeIntegrator1_SYSTE_e;
  boolean_T TmpModelReferenceSubsystem_RESE;
  boolean_T IfActionSubsystem4_RESET_ELAPS_;
  boolean_T IfActionSubsystem2_RESET_ELAPS_;
} DW_SWC_SMO_IG_FQ_f_T;

#endif

#ifndef SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  const real32_T Divide;
} ConstB_SWC_SMO_IG_FQ_h_T;

#endif

#ifndef SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_SMO_IG_FQ_T {
  const char_T **errorStatus;
  struct {
    int_T mdlref_TriggerTID;
  } Timing;
};

#endif

#ifndef SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_SMO_IG_FQ_T rtm;
} MdlrefDW_SWC_SMO_IG_FQ_T;

#endif

extern void SWC_SMO_IG_FQ_Init(void);
extern void SWC_SMO_IG_FQ_Enable(void);
extern void SWC_SMO_IG_FQ(const uint8_T *rtu_SCF_BUS_SCF_stMotor_state, const
  uint8_T *rtu_SCF_BUS_SCF_flgZReset, const real32_T *rtu_MCF_BUS_MCF_iqDes,
  const real32_T *rtu_MCF_BUS_MCF_ialpha, const real32_T *rtu_MCF_BUS_MCF_ibeta,
  const real32_T *rtu_MCF_BUS_MCF_uAlCalc, const real32_T
  *rtu_MCF_BUS_MCF_uBCalc, real32_T *rty_SMO_SpN, real32_T *rty_SMO_iq_ref,
  real32_T *rty_SMO_theta_fd);
extern void SWC_SMO_IG_FQ_initialize(const char_T **rt_errorStatus, const
  rtTimingBridge *timingBridge, int_T mdlref_TID0, int_T mdlref_TriggerTID);

#pragma section ".CAL_CONST"

extern const volatile real32_T CAL_SMO_NmSp_f32_FQ;

#pragma section

#ifndef SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_SMO_IG_FQ_T SWC_SMO_IG_FQ_MdlrefDW;

#endif

#ifndef SWC_SMO_IG_FQ_MDLREF_HIDE_CHILD_

extern DW_SWC_SMO_IG_FQ_f_T SWC_SMO_IG_FQ_DW;

#endif
#endif

