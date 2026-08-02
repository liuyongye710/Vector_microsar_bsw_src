#include "SWC_SMO_IG_FQ.h"
#include "SWC_SMO_IG_FQ_private.h"
#include "rt_modf_snf.h"

int_T SWC_SMO_IG_FQ_GlobalTID[1];
const rtTimingBridge *SWC_SMO_IG_FQ_TimingBrdg;
MdlrefDW_SWC_SMO_IG_FQ_T SWC_SMO_IG_FQ_MdlrefDW;
DW_SWC_SMO_IG_FQ_f_T SWC_SMO_IG_FQ_DW;
void SWC_SMO_IG_FQ_Init(void)
{
  SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = -1;
  SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PrevRese = 2;
  SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PrevRes = 2;
}

void SWC_SMO_IG_FQ_Enable(void)
{
  SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_RESE = true;
  SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_SYSTEM_E = 1U;
  SWC_SMO_IG_FQ_DW.Integrator_SYSTEM_ENABLE = 1U;
}

void SWC_SMO_IG_FQ(const uint8_T *rtu_SCF_BUS_SCF_stMotor_state, const uint8_T
                   *rtu_SCF_BUS_SCF_flgZReset, const real32_T
                   *rtu_MCF_BUS_MCF_iqDes, const real32_T
                   *rtu_MCF_BUS_MCF_ialpha, const real32_T
                   *rtu_MCF_BUS_MCF_ibeta, const real32_T
                   *rtu_MCF_BUS_MCF_uAlCalc, const real32_T
                   *rtu_MCF_BUS_MCF_uBCalc, real32_T *rty_SMO_SpN, real32_T
                   *rty_SMO_iq_ref, real32_T *rty_SMO_theta_fd)
{
  RT_MODEL_SWC_SMO_IG_FQ_T *const SWC_SMO_IG_FQ_M = &(SWC_SMO_IG_FQ_MdlrefDW.rtm);
  int32_T rtb_Switch_j;
  real32_T rtb_Gain11;
  real32_T rtb_IntegralGain;
  real32_T rtb_Sign;
  real32_T rtb_ZeroGain;
  real32_T rtb_ebetak;
  int8_T rtPrevAction;
  boolean_T rtb_NotEqual;
  if (SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_RESE) {
    SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_ELAP = 0U;
  } else {
    SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_ELAP = rtmGetClockTick0
      (SWC_SMO_IG_FQ_M) - SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV;
  }

  SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV = rtmGetClockTick0
    (SWC_SMO_IG_FQ_M);
  SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_RESE = false;
  if (CAL_SMO_NmSp_f32_FQ >= 0.0F) {
    rtb_Switch_j = 600;
  } else {
    rtb_Switch_j = -600;
  }

  rtPrevAction = SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem;
  SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = -1;
  switch (*rtu_SCF_BUS_SCF_stMotor_state) {
   case 1:
    SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = 0;
    break;

   case 2:
    SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = 1;
    break;

   case 3:
    SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = 2;
    break;

   case 4:
    SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = 3;
    break;

   case 5:
    SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem = 4;
    break;
  }

  switch (SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem) {
   case 0:
    *rty_SMO_theta_fd = 0.0F;
    *rty_SMO_iq_ref = 0.0F;
    break;

   case 1:
    *rty_SMO_theta_fd = 0.0F;
    *rty_SMO_iq_ref = 1.0F;
    break;

   case 2:
    if (SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem != rtPrevAction) {
      SWC_SMO_IG_FQ_DW.IfActionSubsystem2_RESET_ELAPS_ = true;
      SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_SYSTEM_m = 1U;
      SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_SYSTE_e = 1U;
    }

    if (SWC_SMO_IG_FQ_DW.IfActionSubsystem2_RESET_ELAPS_) {
      SWC_SMO_IG_FQ_DW.IfActionSubsystem2_ELAPS_T = 0U;
    } else {
      SWC_SMO_IG_FQ_DW.IfActionSubsystem2_ELAPS_T =
        SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV -
        SWC_SMO_IG_FQ_DW.IfActionSubsystem2_PREV_T;
    }

    SWC_SMO_IG_FQ_DW.IfActionSubsystem2_PREV_T =
      SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV;
    SWC_SMO_IG_FQ_DW.IfActionSubsystem2_RESET_ELAPS_ = false;
    if (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_SYSTEM_m == 0) {
      if ((*rtu_SCF_BUS_SCF_flgZReset > 0) &&
          (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
        SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_DSTATE_i = 0.0F;
      } else {
        SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_DSTATE_i += 0.001F * (real32_T)
          SWC_SMO_IG_FQ_DW.IfActionSubsystem2_ELAPS_T
          * SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U_n;
      }
    }

    if (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_SYSTE_e == 0) {
      if ((*rtu_SCF_BUS_SCF_flgZReset > 0) &&
          (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PrevRes <= 0)) {
        SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_DSTAT_k = 0.0F;
      } else {
        SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_DSTAT_k += 0.001F * (real32_T)
          SWC_SMO_IG_FQ_DW.IfActionSubsystem2_ELAPS_T
          * SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PREV__e;
      }
    }

    *rty_SMO_theta_fd = rt_modf_snf
      (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_DSTAT_k, 6.28318548F);
    *rty_SMO_iq_ref = 1.0F;
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_SYSTEM_m = 0U;
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PrevRese = (int8_T)
      (*rtu_SCF_BUS_SCF_flgZReset > 0);
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U_n = 0.104719758F * (real32_T)
      rtb_Switch_j * 4.0F * SWC_SMO_IG_FQ_ConstB.Divide;
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_SYSTE_e = 0U;
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PrevRes = (int8_T)
      (*rtu_SCF_BUS_SCF_flgZReset > 0);
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PREV__e =
      SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_DSTATE_i;
    break;

   case 3:
    if (SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem != rtPrevAction) {
      SWC_SMO_IG_FQ_DW.IfActionSubsystem4_RESET_ELAPS_ = true;
      SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_SYSTEM_ = 1U;
    }

    if (SWC_SMO_IG_FQ_DW.IfActionSubsystem4_RESET_ELAPS_) {
      SWC_SMO_IG_FQ_DW.IfActionSubsystem4_ELAPS_T = 0U;
    } else {
      SWC_SMO_IG_FQ_DW.IfActionSubsystem4_ELAPS_T =
        SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV -
        SWC_SMO_IG_FQ_DW.IfActionSubsystem4_PREV_T;
    }

    SWC_SMO_IG_FQ_DW.IfActionSubsystem4_PREV_T =
      SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV;
    SWC_SMO_IG_FQ_DW.IfActionSubsystem4_RESET_ELAPS_ = false;
    if (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_SYSTEM_ == 0) {
      SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_DSTATE += 0.001F * (real32_T)
        SWC_SMO_IG_FQ_DW.IfActionSubsystem4_ELAPS_T
        * SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PREV_U;
    }

    *rty_SMO_theta_fd = rt_modf_snf
      (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_DSTATE, 6.28318548F);
    SWC_SMO_IG_FQ_DW.UnitDelay_DSTATE_j += 0.01F;
    if (SWC_SMO_IG_FQ_DW.UnitDelay_DSTATE_j >= 1.0F) {
      rtb_ZeroGain = 1.0F;
    } else {
      rtb_ZeroGain = SWC_SMO_IG_FQ_DW.UnitDelay_DSTATE_j;
    }

    *rty_SMO_iq_ref = 1.0F - rtb_ZeroGain * 0.7F;
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_SYSTEM_ = 0U;
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator1_PREV_U = 0.104719758F * (real32_T)
      rtb_Switch_j * 4.0F;
    break;

   case 4:
    *rty_SMO_theta_fd = SWC_SMO_IG_FQ_DW.UnitDelay1_DSTATE;
    *rty_SMO_iq_ref = *rtu_MCF_BUS_MCF_iqDes;
    break;
  }

  if (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_SYSTEM_E == 0) {
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_DSTATE += 0.001F * (real32_T)
      SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_ELAP *
      SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U;
  }

  SWC_SMO_IG_FQ_DW.UnitDelay1_DSTATE = rt_modf_snf
    (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_DSTATE, 6.28318548F);
  rtb_ebetak = SWC_SMO_IG_FQ_DW.UnitDelay4_DSTATE;
  rtb_IntegralGain = (0.0F - SWC_SMO_IG_FQ_DW.UnitDelay3_DSTATE * cosf
                      (SWC_SMO_IG_FQ_DW.UnitDelay1_DSTATE)) -
    SWC_SMO_IG_FQ_DW.UnitDelay4_DSTATE * sinf(SWC_SMO_IG_FQ_DW.UnitDelay1_DSTATE);
  if (SWC_SMO_IG_FQ_DW.Integrator_SYSTEM_ENABLE == 0) {
    SWC_SMO_IG_FQ_DW.Integrator_DSTATE += 0.001F * (real32_T)
      SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_ELAP *
      SWC_SMO_IG_FQ_DW.Integrator_PREV_U;
  }

  rtb_Sign = 707.0F * rtb_IntegralGain + SWC_SMO_IG_FQ_DW.Integrator_DSTATE;
  if (rtb_Sign > 18849.5566F) {
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U = 18849.5566F;
  } else if (rtb_Sign < -18849.5566F) {
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U = -18849.5566F;
  } else {
    SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U = rtb_Sign;
  }

  SWC_SMO_IG_FQ_DW.Delay_DSTATE +=
    (SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_PREV_U -
     SWC_SMO_IG_FQ_DW.Delay_DSTATE) * 0.003F;
  *rty_SMO_SpN = 0.25F * SWC_SMO_IG_FQ_DW.Delay_DSTATE * 9.54929638F;
  rtb_ZeroGain = 0.0F * rtb_Sign;
  if (rtb_Sign > 18849.5566F) {
    rtb_Sign -= 18849.5566F;
  } else if (rtb_Sign >= -18849.5566F) {
    rtb_Sign = 0.0F;
  } else {
    rtb_Sign -= -18849.5566F;
  }

  rtb_NotEqual = (rtb_ZeroGain != rtb_Sign);
  if (rtb_Sign < 0.0F) {
    rtb_Sign = -1.0F;
  } else if (rtb_Sign > 0.0F) {
    rtb_Sign = 1.0F;
  } else if (rtb_Sign == 0.0F) {
    rtb_Sign = 0.0F;
  } else {
    rtb_Sign = (rtNaNF);
  }

  if (rtIsNaNF(rtb_Sign)) {
    rtb_ZeroGain = 0.0F;
  } else {
    rtb_ZeroGain = fmodf(rtb_Sign, 256.0F);
  }

  rtb_IntegralGain *= 40000.0F;
  rtb_Sign = SWC_SMO_IG_FQ_DW.UnitDelay2_DSTATE - *rtu_MCF_BUS_MCF_ibeta;
  if (rtb_Sign < 0.0F) {
    rtb_Sign = -1.0F;
  } else if (rtb_Sign > 0.0F) {
    rtb_Sign = 1.0F;
  } else if (rtb_Sign == 0.0F) {
    rtb_Sign = 0.0F;
  } else {
    rtb_Sign = (rtNaNF);
  }

  SWC_SMO_IG_FQ_DW.UnitDelay2_DSTATE = ((0.869719625F *
    SWC_SMO_IG_FQ_DW.UnitDelay2_DSTATE - 0.0186915882F *
    SWC_SMO_IG_FQ_DW.UnitDelay4_DSTATE) + 0.0186915882F *
    *rtu_MCF_BUS_MCF_uBCalc) - 0.0373831764F * rtb_Sign;
  rtb_Gain11 = 1.86915874F * rtb_Sign;
  rtb_Sign = 0.0001F * SWC_SMO_IG_FQ_DW.UnitDelay2_DSTATE_g;
  SWC_SMO_IG_FQ_DW.UnitDelay4_DSTATE += rtb_Sign *
    SWC_SMO_IG_FQ_DW.UnitDelay3_DSTATE + rtb_Gain11;
  rtb_ebetak *= rtb_Sign;
  rtb_Sign = SWC_SMO_IG_FQ_DW.UnitDelay5_DSTATE - *rtu_MCF_BUS_MCF_ialpha;
  if (rtb_Sign < 0.0F) {
    rtb_Sign = -1.0F;
  } else if (rtb_Sign > 0.0F) {
    rtb_Sign = 1.0F;
  } else if (rtb_Sign == 0.0F) {
    rtb_Sign = 0.0F;
  } else {
    rtb_Sign = (rtNaNF);
  }

  SWC_SMO_IG_FQ_DW.UnitDelay5_DSTATE = ((0.869719625F *
    SWC_SMO_IG_FQ_DW.UnitDelay5_DSTATE - 0.0186915882F *
    SWC_SMO_IG_FQ_DW.UnitDelay3_DSTATE) + 0.0186915882F *
    *rtu_MCF_BUS_MCF_uAlCalc) - 0.0373831764F * rtb_Sign;
  SWC_SMO_IG_FQ_DW.UnitDelay_DSTATE = SWC_SMO_IG_FQ_DW.UnitDelay1_DSTATE;
  switch (SWC_SMO_IG_FQ_DW.SwitchCase1_ActiveSubsystem) {
   case 0:
   case 1:
   case 4:
    break;

   case 2:
    SWC_SMO_IG_FQ_DW.IfActionSubsystem2_PREV_T =
      SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV;
    SWC_SMO_IG_FQ_DW.IfActionSubsystem2_RESET_ELAPS_ = false;
    break;

   case 3:
    SWC_SMO_IG_FQ_DW.IfActionSubsystem4_PREV_T =
      SWC_SMO_IG_FQ_DW.TmpModelReferenceSubsystem_PREV;
    SWC_SMO_IG_FQ_DW.IfActionSubsystem4_RESET_ELAPS_ = false;
    break;
  }

  SWC_SMO_IG_FQ_DW.UnitDelay3_DSTATE = (1.86915874F * rtb_Sign +
    SWC_SMO_IG_FQ_DW.UnitDelay3_DSTATE) - rtb_ebetak;
  SWC_SMO_IG_FQ_DW.DiscreteTimeIntegrator_SYSTEM_E = 0U;
  SWC_SMO_IG_FQ_DW.Integrator_SYSTEM_ENABLE = 0U;
  if (rtb_IntegralGain < 0.0F) {
    rtb_ebetak = -1.0F;
  } else if (rtb_IntegralGain > 0.0F) {
    rtb_ebetak = 1.0F;
  } else if (rtb_IntegralGain == 0.0F) {
    rtb_ebetak = 0.0F;
  } else {
    rtb_ebetak = (rtNaNF);
  }

  if (rtIsNaNF(rtb_ebetak)) {
    rtb_ebetak = 0.0F;
  } else {
    rtb_ebetak = fmodf(rtb_ebetak, 256.0F);
  }

  if (rtb_NotEqual && ((int8_T)(rtb_ZeroGain < 0.0F ? (int32_T)(int8_T)-(int8_T)
        (uint8_T)-rtb_ZeroGain : (int32_T)(int8_T)(uint8_T)rtb_ZeroGain) ==
                       (rtb_ebetak < 0.0F ? (int32_T)(int8_T)-(int8_T)(uint8_T)
                        -rtb_ebetak : (int32_T)(int8_T)(uint8_T)rtb_ebetak))) {
    SWC_SMO_IG_FQ_DW.Integrator_PREV_U = 0.0F;
  } else {
    SWC_SMO_IG_FQ_DW.Integrator_PREV_U = rtb_IntegralGain;
  }

  SWC_SMO_IG_FQ_DW.UnitDelay2_DSTATE_g = SWC_SMO_IG_FQ_DW.Delay_DSTATE;
}

void SWC_SMO_IG_FQ_initialize(const char_T **rt_errorStatus, const
  rtTimingBridge *timingBridge, int_T mdlref_TID0, int_T mdlref_TriggerTID)
{
  RT_MODEL_SWC_SMO_IG_FQ_T *const SWC_SMO_IG_FQ_M = &(SWC_SMO_IG_FQ_MdlrefDW.rtm);
  rt_InitInfAndNaN(sizeof(real_T));
  SWC_SMO_IG_FQ_GlobalTID[0] = mdlref_TID0;
  SWC_SMO_IG_FQ_M->Timing.mdlref_TriggerTID = mdlref_TriggerTID;
  SWC_SMO_IG_FQ_TimingBrdg = timingBridge;
  rtmSetErrorStatusPointer(SWC_SMO_IG_FQ_M, rt_errorStatus);
}
