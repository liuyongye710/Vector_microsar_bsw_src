#include "SWC_TDC_IG_FQ.h"
#include "SWC_TDC_IG_FQ_private.h"
#include "look1_iflf_binlxpw.h"

real32_T VAR_TDC_trqRmp_f32_FQ;
real32_T TDC_TrqDes_FQ;
boolean_T TDC_flgTrqLmtActv_FQ;
MdlrefDW_SWC_TDC_IG_FQ_T SWC_TDC_IG_FQ_MdlrefDW;
DW_SWC_TDC_IG_FQ_f_T SWC_TDC_IG_FQ_DW;
void SWC_TDC_IG_FQ(const real32_T *rtu_TPC_BUS_TPC_TrqMax, const real32_T
                   *rtu_TPC_BUS_TPC_TrqMin, const real32_T *rtu_Rdc_nWoFlt,
                   const uint8_T *rtu_SCF_BUS_SCF_stModeReqToTdc, const uint8_T *
                   rtu_SCF_BUS_SCF_flginitEn_Nctl, real32_T
                   *rty_TDC_BUS_TDC_TrqDes, boolean_T
                   *rty_TDC_BUS_TDC_flgTrqLmtActv)
{
  real32_T rtb_Abs;
  real32_T rtb_tdc_Kp;
  real32_T rtb_tdc_TrqPiIncMax;
  real32_T rtb_tdc_TrqPiIncMin;
  real32_T rtb_tdc_xDevSpd;
  rtb_tdc_xDevSpd = CAL_SMO_NmSp_f32_FQ - *rtu_Rdc_nWoFlt;
  rtb_Abs = fabsf(rtb_tdc_xDevSpd);
  if (*rtu_SCF_BUS_SCF_stModeReqToTdc == 1) {
    rtb_tdc_TrqPiIncMax = 0.0F;
    rtb_tdc_TrqPiIncMin = 0.0F;
    rtb_tdc_xDevSpd = 0.0F;
    rtb_tdc_Kp = 0.0F;
    rtb_Abs = 0.0F;
    SWC_TDC_IG_FQ_DW.UnitDelay_DSTATE = 0.0F;
  } else if (*rtu_SCF_BUS_SCF_stModeReqToTdc == 2) {
    rtb_tdc_TrqPiIncMax = CAL_TDC_trqIncMax_f32_FQ;
    rtb_tdc_TrqPiIncMin = -CAL_TDC_trqIncMax_f32_FQ;
    if (0 == ((uint8_T)CAL_TDC_go_nCtlExtReq_u8_FQ)) {
      rtb_tdc_Kp = 0.0F;
    } else {
      rtb_tdc_Kp = look1_iflf_binlxpw(rtb_Abs, ((const real32_T *)
        &(CAL_TDC_n_Error_X_Af32_FQ[0])), ((const real32_T *)
        &(CAL_TDC_KpNCtl_Y_Af32_FQ[0])), 9U);
    }

    rtb_Abs = look1_iflf_binlxpw(rtb_Abs, ((const real32_T *)
      &(CAL_TDC_n_Error_X_Af32_FQ[0])), ((const real32_T *)
      &(CAL_TDC_KiNCtl_Y_Af32_FQ[0])), 9U) * CAL_TDC_DeltaT_f32_FQ;
  } else {
    rtb_tdc_TrqPiIncMax = 0.0F;
    rtb_tdc_TrqPiIncMin = 0.0F;
    rtb_tdc_xDevSpd = 0.0F;
    rtb_tdc_Kp = 0.0F;
    rtb_Abs = 0.0F;
    SWC_TDC_IG_FQ_DW.UnitDelay_DSTATE = 0.0F;
  }

  if (*rtu_SCF_BUS_SCF_flginitEn_Nctl != 0) {
    rtb_tdc_Kp = 0.0F;
  } else {
    rtb_tdc_Kp = (rtb_tdc_xDevSpd - SWC_TDC_IG_FQ_DW.UnitDelay_DSTATE_f) *
      rtb_tdc_Kp + rtb_Abs * rtb_tdc_xDevSpd;
    if (rtb_tdc_Kp > rtb_tdc_TrqPiIncMax) {
      rtb_tdc_Kp = rtb_tdc_TrqPiIncMax;
    } else {
      if (rtb_tdc_Kp < rtb_tdc_TrqPiIncMin) {
        rtb_tdc_Kp = rtb_tdc_TrqPiIncMin;
      }
    }
  }

  rtb_tdc_TrqPiIncMax = rtb_tdc_Kp + SWC_TDC_IG_FQ_DW.UnitDelay_DSTATE;
  if (rtb_tdc_TrqPiIncMax > *rtu_TPC_BUS_TPC_TrqMax) {
    rtb_tdc_TrqPiIncMin = *rtu_TPC_BUS_TPC_TrqMax;
  } else if (rtb_tdc_TrqPiIncMax < *rtu_TPC_BUS_TPC_TrqMin) {
    rtb_tdc_TrqPiIncMin = *rtu_TPC_BUS_TPC_TrqMin;
  } else {
    rtb_tdc_TrqPiIncMin = rtb_tdc_TrqPiIncMax;
  }

  rtb_tdc_Kp = rtb_tdc_TrqPiIncMin - SWC_TDC_IG_FQ_DW.UnitDelay2_DSTATE;
  VAR_TDC_trqRmp_f32_FQ = CAL_TDC_TrqRamp_f32_FQ;
  if (rtb_tdc_Kp <= VAR_TDC_trqRmp_f32_FQ) {
    if (-rtb_tdc_Kp <= VAR_TDC_trqRmp_f32_FQ) {
      SWC_TDC_IG_FQ_DW.UnitDelay2_DSTATE = rtb_tdc_TrqPiIncMin;
    } else {
      SWC_TDC_IG_FQ_DW.UnitDelay2_DSTATE -= VAR_TDC_trqRmp_f32_FQ;
    }
  } else {
    SWC_TDC_IG_FQ_DW.UnitDelay2_DSTATE += VAR_TDC_trqRmp_f32_FQ;
  }

  if (CAL_trqDesOvrdflg_f32_FQ) {
    TDC_TrqDes_FQ = CAL_trqDesOvrdVal_f32_FQ;
  } else {
    TDC_TrqDes_FQ = SWC_TDC_IG_FQ_DW.UnitDelay2_DSTATE;
  }

  TDC_flgTrqLmtActv_FQ = ((rtb_tdc_TrqPiIncMax > *rtu_TPC_BUS_TPC_TrqMax) ||
    (rtb_tdc_TrqPiIncMax < *rtu_TPC_BUS_TPC_TrqMin));
  *rty_TDC_BUS_TDC_TrqDes = TDC_TrqDes_FQ;
  *rty_TDC_BUS_TDC_flgTrqLmtActv = TDC_flgTrqLmtActv_FQ;
  SWC_TDC_IG_FQ_DW.UnitDelay_DSTATE = SWC_TDC_IG_FQ_DW.UnitDelay2_DSTATE;
  SWC_TDC_IG_FQ_DW.UnitDelay_DSTATE_f = rtb_tdc_xDevSpd;
}

void SWC_TDC_IG_FQ_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_TDC_IG_FQ_T *const SWC_TDC_IG_FQ_M = &(SWC_TDC_IG_FQ_MdlrefDW.rtm);
  rtmSetErrorStatusPointer(SWC_TDC_IG_FQ_M, rt_errorStatus);
}
