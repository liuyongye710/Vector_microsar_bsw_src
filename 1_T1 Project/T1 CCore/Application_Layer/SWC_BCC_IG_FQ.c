#include "SWC_BCC_IG_FQ.h"
#include "SWC_BCC_IG_FQ_private.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlxpw.h"

real32_T BCC_tIGBTTj_FQ;
real32_T BCC_tCoolantTj_FQ;
real32_T VAR_UTjpwr_f32_FQ;
real32_T VAR_UCoolantTj_f32_FQ;
real32_T VAR_UihTjtIGBT_f32_FQ;
real32_T VAR_BCC_iDcLnkEst_f32_FQ;
real32_T VAR_BCC_iDcLnkEstFlt_f32_FQ;
real32_T BCE_iDcLnkEst_FQ;
boolean_T VAR_BCC_flgstGateDrv_b_FQ;
MdlrefDW_SWC_BCC_IG_FQ_T SWC_BCC_IG_FQ_MdlrefDW;
B_SWC_BCC_IG_FQ_c_T SWC_BCC_IG_FQ_B;
DW_SWC_BCC_IG_FQ_f_T SWC_BCC_IG_FQ_DW;
void SWC_BCC_IG_FQ_Disable(void)
{
  if (SWC_BCC_IG_FQ_DW.Tj_MODE) {
    SWC_BCC_IG_FQ_DW.uTjCal1_MODE = false;
    SWC_BCC_IG_FQ_DW.Tj_MODE = false;
  }
}

void SWC_BCC_IG_FQ(const real32_T *rtu_MCF_BUS_MCF_dycU, const real32_T
                   *rtu_MCF_BUS_MCF_dycV, const real32_T *rtu_MCF_BUS_MCF_dycW,
                   const uint8_T *rtu_MCF_BUS_MCF_SecVolt, const real32_T
                   *rtu_MCF_BUS_MCF_frqPwm, const real32_T
                   *rtu_MCF_BUS_MCF_tiLock, const real32_T *rtu_MCF_BUS_MCF_iU,
                   const real32_T *rtu_MCF_BUS_MCF_iV, const real32_T
                   *rtu_MCF_BUS_MCF_iW, const uint8_T
                   *rtu_TPC_BUS_TPC_stMotorMod, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDBCTempUFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDBCTempVFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tDBCTempWFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const uint8_T
                   *rtu_SCF_BUS_SCF_stGateDrv, real32_T
                   *rty_BCC_BUS_BCC_iDcLnkEst, real32_T *rty_BCC_BUS_BCC_tIGBTTj,
                   real32_T *rty_BCC_BUS_BCC_tCoolantTj)
{
  real32_T rtb_Product;
  real32_T rtb_dycmax;
  real32_T rtb_dycmid;
  real32_T rtb_dycmin;
  real32_T rtb_tudh_i;
  real32_T rtb_tudl_k;
  real32_T rtb_tuih_c;
  real32_T rtb_tuil_f;
  real32_T rtb_tvdh_m;
  real32_T rtb_tvdl_d;
  real32_T rtb_tvih_h;
  real32_T rtb_tvil_p;
  real32_T rtb_twdh_h;
  real32_T rtb_twdl_f;
  real32_T rtb_twih_d;
  real32_T rtb_twil_g;
  boolean_T rtb_Switch_d;
  if (!CAL_BCC_flgDelayDyc_b_FQ) {
    SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE = *rtu_MCF_BUS_MCF_dycU;
    SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE = *rtu_MCF_BUS_MCF_dycV;
    SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE = *rtu_MCF_BUS_MCF_dycW;
  }

  rtb_Product = *rtu_MCF_BUS_MCF_frqPwm * 1.0E-6F * *rtu_MCF_BUS_MCF_tiLock;
  rtb_Switch_d = ((*rtu_TPC_BUS_TPC_stMotorMod == 2) ||
                  (*rtu_TPC_BUS_TPC_stMotorMod == 4));
  if (CAL_BCC_flgEnableIdc_b_FQ) {
    if (!CAL_BCC_flgDelayDyc_b_FQ) {
      SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_h = *rtu_MCF_BUS_MCF_SecVolt;
    }

    switch (SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_h) {
     case 1:
      if (*rtu_MCF_BUS_MCF_iV >= 0.0F) {
        rtb_twil_g = 2.0F * rtb_Product;
      } else {
        rtb_twil_g = 0.0F;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE >= CAL_BCC_dycUpLimt_f32_FQ) {
        rtb_twdh_h = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        rtb_twdh_h = 0.0F;
      } else {
        rtb_twdh_h = 2.0F * rtb_Product;
      }

      if (*rtu_MCF_BUS_MCF_iV >= 0.0F) {
        rtb_twih_d = 0.0F;
      } else {
        rtb_twih_d = 2.0F * rtb_Product;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE <= CAL_BCC_dycLowLimt_f32_FQ) {
        rtb_twdl_f = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        if (*rtu_MCF_BUS_MCF_iW <= 0.0F) {
          rtb_twdl_f = rtb_Product * CAL_BCC_AgGenCoe_f32_FQ;
        } else {
          rtb_twdl_f = 0.0F;
        }
      } else if (!(*rtu_MCF_BUS_MCF_iW <= 0.0F)) {
        rtb_twdl_f = 0.0F;
      } else {
        rtb_twdl_f = 2.0F * rtb_Product;
      }

      VAR_BCC_iDcLnkEst_f32_FQ = (((SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE) + rtb_twil_g) - rtb_twdh_h) *
        *rtu_MCF_BUS_MCF_iU + (((SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE) + rtb_twih_d) - rtb_twdl_f) *
        -*rtu_MCF_BUS_MCF_iW;
      break;

     case 2:
      if (*rtu_MCF_BUS_MCF_iU >= 0.0F) {
        rtb_twdh_h = 2.0F * rtb_Product;
      } else {
        rtb_twdh_h = 0.0F;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE >= CAL_BCC_dycUpLimt_f32_FQ) {
        rtb_twil_g = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        if (*rtu_MCF_BUS_MCF_iV >= 0.0F) {
          rtb_twil_g = rtb_Product * CAL_BCC_AgGenCoe_f32_FQ;
        } else {
          rtb_twil_g = 0.0F;
        }
      } else if (!(*rtu_MCF_BUS_MCF_iV >= 0.0F)) {
        rtb_twil_g = 0.0F;
      } else {
        rtb_twil_g = 2.0F * rtb_Product;
      }

      if (*rtu_MCF_BUS_MCF_iU >= 0.0F) {
        rtb_twih_d = 0.0F;
      } else {
        rtb_twih_d = 2.0F * rtb_Product;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE <= CAL_BCC_dycLowLimt_f32_FQ) {
        rtb_twdl_f = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        rtb_twdl_f = 0.0F;
      } else {
        rtb_twdl_f = 2.0F * rtb_Product;
      }

      VAR_BCC_iDcLnkEst_f32_FQ = (((SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE) + rtb_twdh_h) - rtb_twil_g) *
        *rtu_MCF_BUS_MCF_iV + (((SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE) + rtb_twih_d) - rtb_twdl_f) *
        -*rtu_MCF_BUS_MCF_iW;
      break;

     case 3:
      if (*rtu_MCF_BUS_MCF_iW >= 0.0F) {
        rtb_twdl_f = 2.0F * rtb_Product;
      } else {
        rtb_twdl_f = 0.0F;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE >= CAL_BCC_dycUpLimt_f32_FQ) {
        rtb_twil_g = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        rtb_twil_g = 0.0F;
      } else {
        rtb_twil_g = 2.0F * rtb_Product;
      }

      if (*rtu_MCF_BUS_MCF_iW >= 0.0F) {
        rtb_twih_d = 0.0F;
      } else {
        rtb_twih_d = 2.0F * rtb_Product;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE <= CAL_BCC_dycLowLimt_f32_FQ) {
        rtb_twdh_h = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        if (*rtu_MCF_BUS_MCF_iU <= 0.0F) {
          rtb_twdh_h = rtb_Product * CAL_BCC_AgGenCoe_f32_FQ;
        } else {
          rtb_twdh_h = 0.0F;
        }
      } else if (!(*rtu_MCF_BUS_MCF_iU <= 0.0F)) {
        rtb_twdh_h = 0.0F;
      } else {
        rtb_twdh_h = 2.0F * rtb_Product;
      }

      VAR_BCC_iDcLnkEst_f32_FQ = (((SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE) + rtb_twdl_f) - rtb_twil_g) *
        *rtu_MCF_BUS_MCF_iV + (((SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE) + rtb_twih_d) - rtb_twdh_h) *
        -*rtu_MCF_BUS_MCF_iU;
      break;

     case 4:
      if (*rtu_MCF_BUS_MCF_iV >= 0.0F) {
        rtb_twil_g = 2.0F * rtb_Product;
      } else {
        rtb_twil_g = 0.0F;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE >= CAL_BCC_dycUpLimt_f32_FQ) {
        rtb_twdl_f = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        if (*rtu_MCF_BUS_MCF_iW >= 0.0F) {
          rtb_twdl_f = rtb_Product * CAL_BCC_AgGenCoe_f32_FQ;
        } else {
          rtb_twdl_f = 0.0F;
        }
      } else if (!(*rtu_MCF_BUS_MCF_iW >= 0.0F)) {
        rtb_twdl_f = 0.0F;
      } else {
        rtb_twdl_f = 2.0F * rtb_Product;
      }

      if (*rtu_MCF_BUS_MCF_iV >= 0.0F) {
        rtb_twih_d = 0.0F;
      } else {
        rtb_twih_d = 2.0F * rtb_Product;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE <= CAL_BCC_dycLowLimt_f32_FQ) {
        rtb_twdh_h = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        rtb_twdh_h = 0.0F;
      } else {
        rtb_twdh_h = 2.0F * rtb_Product;
      }

      VAR_BCC_iDcLnkEst_f32_FQ = (((SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE) + rtb_twil_g) - rtb_twdl_f) *
        *rtu_MCF_BUS_MCF_iW + (((SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE) + rtb_twih_d) - rtb_twdh_h) *
        -*rtu_MCF_BUS_MCF_iU;
      break;

     case 5:
      if (*rtu_MCF_BUS_MCF_iU >= 0.0F) {
        rtb_twdh_h = 2.0F * rtb_Product;
      } else {
        rtb_twdh_h = 0.0F;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE >= CAL_BCC_dycUpLimt_f32_FQ) {
        rtb_twdl_f = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        rtb_twdl_f = 0.0F;
      } else {
        rtb_twdl_f = 2.0F * rtb_Product;
      }

      if (*rtu_MCF_BUS_MCF_iU >= 0.0F) {
        rtb_twih_d = 0.0F;
      } else {
        rtb_twih_d = 2.0F * rtb_Product;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE <= CAL_BCC_dycLowLimt_f32_FQ) {
        rtb_twil_g = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        if (*rtu_MCF_BUS_MCF_iV <= 0.0F) {
          rtb_twil_g = rtb_Product * CAL_BCC_AgGenCoe_f32_FQ;
        } else {
          rtb_twil_g = 0.0F;
        }
      } else if (!(*rtu_MCF_BUS_MCF_iV <= 0.0F)) {
        rtb_twil_g = 0.0F;
      } else {
        rtb_twil_g = 2.0F * rtb_Product;
      }

      VAR_BCC_iDcLnkEst_f32_FQ = (((SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE) + rtb_twdh_h) - rtb_twdl_f) *
        *rtu_MCF_BUS_MCF_iW + (((SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE) + rtb_twih_d) - rtb_twil_g) *
        -*rtu_MCF_BUS_MCF_iV;
      break;

     case 6:
      if (*rtu_MCF_BUS_MCF_iW >= 0.0F) {
        rtb_twdl_f = 2.0F * rtb_Product;
      } else {
        rtb_twdl_f = 0.0F;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE >= CAL_BCC_dycUpLimt_f32_FQ) {
        rtb_twdh_h = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        if (*rtu_MCF_BUS_MCF_iU >= 0.0F) {
          rtb_twdh_h = rtb_Product * CAL_BCC_AgGenCoe_f32_FQ;
        } else {
          rtb_twdh_h = 0.0F;
        }
      } else if (!(*rtu_MCF_BUS_MCF_iU >= 0.0F)) {
        rtb_twdh_h = 0.0F;
      } else {
        rtb_twdh_h = 2.0F * rtb_Product;
      }

      if (*rtu_MCF_BUS_MCF_iW >= 0.0F) {
        rtb_twih_d = 0.0F;
      } else {
        rtb_twih_d = 2.0F * rtb_Product;
      }

      if (SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE <= CAL_BCC_dycLowLimt_f32_FQ) {
        rtb_twil_g = CAL_BCC_tiFull_f32_FQ * rtb_Product;
      } else if (rtb_Switch_d) {
        rtb_twil_g = 0.0F;
      } else {
        rtb_twil_g = 2.0F * rtb_Product;
      }

      VAR_BCC_iDcLnkEst_f32_FQ = (((SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE) + rtb_twdl_f) - rtb_twdh_h) *
        *rtu_MCF_BUS_MCF_iU + (((SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE -
        SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE) + rtb_twih_d) - rtb_twil_g) *
        -*rtu_MCF_BUS_MCF_iV;
      break;

     default:
      VAR_BCC_iDcLnkEst_f32_FQ = 0.0F;
      break;
    }

    rtb_Product = 10000.0F / CAL_BCC_iDcEstflt_f32_FQ;
    if (rtb_Product < 1.0F) {
      rtb_Product = 1.0F;
    }

    rtb_Product /= rtb_Product + 6.283F;
    VAR_BCC_iDcLnkEstFlt_f32_FQ = (1.0F - rtb_Product) *
      VAR_BCC_iDcLnkEst_f32_FQ + rtb_Product * VAR_BCC_iDcLnkEstFlt_f32_FQ;
    VAR_BCC_flgstGateDrv_b_FQ = ((*rtu_SCF_BUS_SCF_stGateDrv == 1) ||
      (*rtu_SCF_BUS_SCF_stGateDrv == 2));
    if (VAR_BCC_flgstGateDrv_b_FQ) {
      BCE_iDcLnkEst_FQ = 0.0F;
    } else {
      BCE_iDcLnkEst_FQ = VAR_BCC_iDcLnkEstFlt_f32_FQ;
    }

    SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_h = *rtu_MCF_BUS_MCF_SecVolt;
  }

  if (CAL_BCC_flgEnableTj_b_FQ) {
    SWC_BCC_IG_FQ_DW.Tj_MODE = true;
    SWC_BCC_IG_FQ_B.UnitDelay3 = SWC_BCC_IG_FQ_DW.UnitDelay3_DSTATE;
    if (*rtu_MCF_BUS_MCF_frqPwm > 20000.0F) {
      rtb_Product = 20000.0F;
    } else if (*rtu_MCF_BUS_MCF_frqPwm < 0.0001F) {
      rtb_Product = 0.0001F;
    } else {
      rtb_Product = *rtu_MCF_BUS_MCF_frqPwm;
    }

    rtb_Product = 1.0F / rtb_Product;
    switch ((int32_T)(((((uint32_T)((*rtu_MCF_BUS_MCF_dycV >=
      *rtu_MCF_BUS_MCF_dycW) << 7) << 1) + ((uint32_T)(*rtu_MCF_BUS_MCF_dycU >= *
      rtu_MCF_BUS_MCF_dycV) << 7)) + ((uint32_T)((*rtu_MCF_BUS_MCF_dycU >=
      *rtu_MCF_BUS_MCF_dycW) << 7) << 2)) >> 7)) {
     case 0:
      rtb_dycmax = *rtu_MCF_BUS_MCF_dycW;
      rtb_dycmid = *rtu_MCF_BUS_MCF_dycV;
      rtb_dycmin = *rtu_MCF_BUS_MCF_dycU;
      break;

     case 1:
      rtb_dycmax = *rtu_MCF_BUS_MCF_dycW;
      rtb_dycmid = *rtu_MCF_BUS_MCF_dycU;
      rtb_dycmin = *rtu_MCF_BUS_MCF_dycV;
      break;

     case 2:
      rtb_dycmax = *rtu_MCF_BUS_MCF_dycV;
      rtb_dycmid = *rtu_MCF_BUS_MCF_dycW;
      rtb_dycmin = *rtu_MCF_BUS_MCF_dycU;
      break;

     case 3:
      rtb_dycmax = 0.0F;
      rtb_dycmid = 0.0F;
      rtb_dycmin = 0.0F;
      break;

     case 4:
      rtb_dycmax = 0.0F;
      rtb_dycmid = 0.0F;
      rtb_dycmin = 0.0F;
      break;

     case 5:
      rtb_dycmax = *rtu_MCF_BUS_MCF_dycU;
      rtb_dycmid = *rtu_MCF_BUS_MCF_dycW;
      rtb_dycmin = *rtu_MCF_BUS_MCF_dycV;
      break;

     case 6:
      rtb_dycmax = *rtu_MCF_BUS_MCF_dycV;
      rtb_dycmid = *rtu_MCF_BUS_MCF_dycU;
      rtb_dycmin = *rtu_MCF_BUS_MCF_dycW;
      break;

     default:
      rtb_dycmax = *rtu_MCF_BUS_MCF_dycU;
      rtb_dycmid = *rtu_MCF_BUS_MCF_dycV;
      rtb_dycmin = *rtu_MCF_BUS_MCF_dycW;
      break;
    }

    rtb_tuih_c = 0.0F;
    rtb_tuil_f = 0.0F;
    rtb_tudh_i = 0.0F;
    rtb_tudl_k = 0.0F;
    rtb_tvih_h = 0.0F;
    rtb_tvil_p = 0.0F;
    rtb_tvdh_m = 0.0F;
    rtb_tvdl_d = 0.0F;
    rtb_twih_d = 0.0F;
    rtb_twil_g = 0.0F;
    rtb_twdh_h = 0.0F;
    rtb_twdl_f = 0.0F;
    rtb_dycmax = (real32_T)(((1.0F - rtb_dycmax) - 0.024F) * 0.5) + 0.024F;
    rtb_dycmid = (real32_T)(((1.0F - rtb_dycmid) - 0.024F) * 0.5);
    rtb_dycmin = (real32_T)(((1.0F - rtb_dycmin) - 0.024F) * 0.5);
    switch (*rtu_MCF_BUS_MCF_SecVolt) {
     case 1:
      rtb_tudl_k = rtb_dycmid + 0.024F;
      rtb_tuih_c = 0.5F - (rtb_dycmid + 0.024F);
      rtb_tvdl_d = rtb_dycmax;
      rtb_tvih_h = 0.5F - rtb_dycmax;
      rtb_twil_g = rtb_dycmin;
      rtb_twdl_f = 0.5F - rtb_dycmin;
      break;

     case 2:
      rtb_tudl_k = rtb_dycmax;
      rtb_tuih_c = 0.5F - rtb_dycmax;
      rtb_tvil_p = rtb_dycmin;
      rtb_tvdh_m = 0.5F - rtb_dycmin;
      rtb_twdl_f = rtb_dycmid + 0.024F;
      rtb_twih_d = 0.5F - (rtb_dycmid + 0.024F);
      break;

     case 3:
      rtb_tudl_k = rtb_dycmax;
      rtb_tuih_c = 0.5F - rtb_dycmax;
      rtb_tvil_p = rtb_dycmid;
      rtb_tvdh_m = 0.5F - rtb_dycmid;
      rtb_twil_g = rtb_dycmin;
      rtb_twdh_h = 0.5F - rtb_dycmin;
      break;

     case 4:
      rtb_tuil_f = rtb_dycmin;
      rtb_tudh_i = 0.5F - rtb_dycmin;
      rtb_tvdl_d = rtb_dycmid + 0.024F;
      rtb_tvih_h = 0.5F - (rtb_dycmid + 0.024F);
      rtb_twdl_f = rtb_dycmax;
      rtb_twih_d = 0.5F - rtb_dycmax;
      break;

     case 5:
      rtb_tuil_f = rtb_dycmin;
      rtb_tudh_i = 0.5F - rtb_dycmin;
      rtb_tvdl_d = rtb_dycmax;
      rtb_tvih_h = 0.5F - rtb_dycmax;
      rtb_twil_g = rtb_dycmid;
      rtb_twdh_h = 0.5F - rtb_dycmid;
      break;

     case 6:
      rtb_tuil_f = rtb_dycmid;
      rtb_tudh_i = 0.5F - rtb_dycmid;
      rtb_tvil_p = rtb_dycmin;
      rtb_tvdh_m = 0.5F - rtb_dycmin;
      rtb_twdl_f = rtb_dycmax;
      rtb_twih_d = 0.5F - rtb_dycmax;
      break;
    }

    SWC_BCC_IG_FQ_B.UnitDelay2 = VAR_UihTjtIGBT_f32_FQ;
    if (rtb_Product >= CAL_tiPwmLim_f32_FQ) {
      if (!SWC_BCC_IG_FQ_DW.uTjCal1_MODE) {
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_e = 0.0F;
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_g = 0.0F;
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_c = 0.0F;
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_n = 0.0F;
        SWC_BCC_IG_FQ_DW.uTjCal1_MODE = true;
      }

      if (CAL_TjstUVW_u8_FQ == 1) {
        if (rtb_tuih_c > 1.0F) {
          rtb_twih_d = 1.0F;
        } else if (rtb_tuih_c < 0.0F) {
          rtb_twih_d = 0.0F;
        } else {
          rtb_twih_d = rtb_tuih_c;
        }

        if (rtb_tuil_f > 1.0F) {
          rtb_twil_g = 1.0F;
        } else if (rtb_tuil_f < 0.0F) {
          rtb_twil_g = 0.0F;
        } else {
          rtb_twil_g = rtb_tuil_f;
        }

        if (rtb_tudh_i > 1.0F) {
          rtb_twdh_h = 1.0F;
        } else if (rtb_tudh_i < 0.0F) {
          rtb_twdh_h = 0.0F;
        } else {
          rtb_twdh_h = rtb_tudh_i;
        }

        if (rtb_tudl_k > 1.0F) {
          rtb_twdl_f = 1.0F;
        } else if (rtb_tudl_k < 0.0F) {
          rtb_twdl_f = 0.0F;
        } else {
          rtb_twdl_f = rtb_tudl_k;
        }
      } else if (CAL_TjstUVW_u8_FQ == 2) {
        if (rtb_tvih_h > 1.0F) {
          rtb_twih_d = 1.0F;
        } else if (rtb_tvih_h < 0.0F) {
          rtb_twih_d = 0.0F;
        } else {
          rtb_twih_d = rtb_tvih_h;
        }

        if (rtb_tvil_p > 1.0F) {
          rtb_twil_g = 1.0F;
        } else if (rtb_tvil_p < 0.0F) {
          rtb_twil_g = 0.0F;
        } else {
          rtb_twil_g = rtb_tvil_p;
        }

        if (rtb_tvdh_m > 1.0F) {
          rtb_twdh_h = 1.0F;
        } else if (rtb_tvdh_m < 0.0F) {
          rtb_twdh_h = 0.0F;
        } else {
          rtb_twdh_h = rtb_tvdh_m;
        }

        if (rtb_tvdl_d > 1.0F) {
          rtb_twdl_f = 1.0F;
        } else if (rtb_tvdl_d < 0.0F) {
          rtb_twdl_f = 0.0F;
        } else {
          rtb_twdl_f = rtb_tvdl_d;
        }
      } else {
        if (rtb_twih_d > 1.0F) {
          rtb_twih_d = 1.0F;
        } else {
          if (rtb_twih_d < 0.0F) {
            rtb_twih_d = 0.0F;
          }
        }

        if (rtb_twil_g > 1.0F) {
          rtb_twil_g = 1.0F;
        } else {
          if (rtb_twil_g < 0.0F) {
            rtb_twil_g = 0.0F;
          }
        }

        if (rtb_twdh_h > 1.0F) {
          rtb_twdh_h = 1.0F;
        } else {
          if (rtb_twdh_h < 0.0F) {
            rtb_twdh_h = 0.0F;
          }
        }

        if (rtb_twdl_f > 1.0F) {
          rtb_twdl_f = 1.0F;
        } else {
          if (rtb_twdl_f < 0.0F) {
            rtb_twdl_f = 0.0F;
          }
        }
      }

      if (SWC_BCC_IG_FQ_ConstB.RelationalOperator) {
        rtb_tvdh_m = fabsf(*rtu_MCF_BUS_MCF_iU);
      } else if (SWC_BCC_IG_FQ_ConstB.RelationalOperator1) {
        rtb_tvdh_m = fabsf(*rtu_MCF_BUS_MCF_iV);
      } else {
        rtb_tvdh_m = fabsf(*rtu_MCF_BUS_MCF_iW);
      }

      if (SWC_BCC_IG_FQ_ConstB.RelationalOperator2) {
        rtb_tuil_f = SWC_BCC_IG_FQ_B.UnitDelay2;
      } else {
        rtb_tuil_f = 0.0F;
      }

      rtb_tudh_i = 0.005F * *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt / rtb_Product;
      rtb_tudl_k = 0.001F * look2_iflf_binlxpw(rtb_tvdh_m, rtb_tuil_f,
        rtCP_uDLookupTable_bp01Data, rtCP_uDLookupTable_bp02Data,
        rtCP_uDLookupTable_tableData, rtCP_uDLookupTable_maxIndex, 17U) *
        rtb_tudh_i;
      if ((rtb_twih_d >= CAL_TjDycMin_f32_FQ) && (rtb_twih_d <=
           CAL_TjDycMax_f32_FQ)) {
        rtb_tvih_h = rtb_tudl_k;
      } else {
        rtb_tvih_h = 0.0F;
      }

      rtb_tuih_c = ((rtb_tuil_f * 2.8E-6F + 0.00072F) * rtb_tvdh_m + (rtb_tuil_f
        * -0.0012F + 0.839F)) * 2.0F * rtb_tvdh_m;
      rtb_twih_d *= rtb_tuih_c;
      rtb_tuih_c *= rtb_twil_g;
      if ((!(rtb_twil_g >= CAL_TjDycMin_f32_FQ)) || (!(rtb_twil_g <=
            CAL_TjDycMax_f32_FQ))) {
        rtb_tudl_k = 0.0F;
      }

      rtb_tvil_p = ((rtb_tuil_f * 1.8E-6F + 0.0012F) * rtb_tvdh_m + (rtb_tuil_f *
        -0.0019F + 1.061F)) * 2.0F * rtb_tvdh_m;
      rtb_twil_g = rtb_twdh_h * rtb_tvil_p;
      rtb_tvdh_m = look2_iflf_binlxpw(rtb_tvdh_m, rtb_tuil_f,
        rtCP_uDLookupTable1_bp01Data, rtCP_uDLookupTable1_bp02Data,
        rtCP_uDLookupTable1_tableData, rtCP_uDLookupTable1_maxIndex, 17U);
      rtb_tudh_i *= 0.001F * rtb_tvdh_m;
      if ((rtb_twdh_h >= CAL_TjDycMin_f32_FQ) && (rtb_twdh_h <=
           CAL_TjDycMax_f32_FQ)) {
        rtb_tuil_f = rtb_tudh_i;
      } else {
        rtb_tuil_f = 0.0F;
      }

      rtb_tvil_p *= rtb_twdl_f;
      if ((!(rtb_twdl_f >= CAL_TjDycMin_f32_FQ)) || (!(rtb_twdl_f <=
            CAL_TjDycMax_f32_FQ))) {
        rtb_tudh_i = 0.0F;
      }

      rtb_twdh_h = 0.7F * rtb_Product;
      VAR_UTjpwr_f32_FQ = (((((((rtb_twih_d + rtb_tuih_c) + rtb_twil_g) +
        rtb_tvil_p) + rtb_tvih_h) + rtb_tudl_k) + rtb_tuil_f) + rtb_tudh_i) *
        rtb_twdh_h + (1.0F - rtb_twdh_h) * SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_e;
      rtb_tvil_p += rtb_tudh_i;
      rtb_twih_d += rtb_tvih_h;
      rtb_tuih_c += rtb_tudl_k;
      rtb_twil_g += rtb_tuil_f;
      SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_g = (((rtb_twih_d * look1_iflf_binlxpw
        (CAL_CoolantFlowReq_u8_FQ, ((const real32_T *)
        &(CAL_TjCoolantFlowTab_af32_FQ[0])), ((const real32_T *)
        &(CAL_TjrthLv4IhNtcTab_af32_FQ[0])), 5U) + rtb_tuih_c *
        CAL_TjrthLv4ilntc_f32_FQ) + rtb_twil_g * CAL_TjrthLv4dhntc_f32_FQ) +
        rtb_tvil_p * CAL_TjrthLv4dlntc_f32_FQ) * rtb_twdh_h + (1.0F - rtb_twdh_h)
        * SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_g;
      if (SWC_BCC_IG_FQ_ConstB.RelationalOperator4) {
        rtb_twdl_f = *rtu_HSPF_BUS_HSPF_tDBCTempUFlt;
      } else if (SWC_BCC_IG_FQ_ConstB.RelationalOperator5) {
        rtb_twdl_f = *rtu_HSPF_BUS_HSPF_tDBCTempVFlt;
      } else {
        rtb_twdl_f = *rtu_HSPF_BUS_HSPF_tDBCTempWFlt;
      }

      VAR_UCoolantTj_f32_FQ = rtb_twdl_f - SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_g;
      SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_c = (1.0F - rtb_twdh_h) *
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_c + (((rtb_twih_d * look1_iflf_binlxpw
        (CAL_CoolantFlowReq_u8_FQ, ((const real32_T *)
        &(CAL_TjCoolantFlowTab_af32_FQ[0])), ((const real32_T *)
        &(CAL_TjrthLv4IhIhTab_af32_FQ[0])), 5U) + rtb_tuih_c *
        CAL_TjrthLv4ilih_f32_FQ) + rtb_twil_g * look1_iflf_binlxpw
        (CAL_CoolantFlowReq_u8_FQ, ((const real32_T *)
        &(CAL_TjCoolantFlowTab_af32_FQ[0])), ((const real32_T *)
        &(CAL_TjrthLv4DhIhTab_af32_FQ[0])), 5U)) + rtb_tvil_p *
        CAL_TjrthLv4dlih_f32_FQ) * rtb_twdh_h;
      VAR_UihTjtIGBT_f32_FQ = SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_c +
        VAR_UCoolantTj_f32_FQ;
      rtb_twil_g = rtb_Product * CAL_Tj_cofFltCoolant_f32_FQ;
      SWC_BCC_IG_FQ_DW.UnitDelay3_DSTATE = (1.0F - rtb_twil_g) *
        SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_n + VAR_UCoolantTj_f32_FQ * rtb_twil_g;
      SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_e = VAR_UTjpwr_f32_FQ;
      SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE_n = SWC_BCC_IG_FQ_DW.UnitDelay3_DSTATE;
    } else {
      SWC_BCC_IG_FQ_DW.uTjCal1_MODE = false;
    }

    BCC_tIGBTTj_FQ = SWC_BCC_IG_FQ_B.UnitDelay2;
    BCC_tCoolantTj_FQ = SWC_BCC_IG_FQ_B.UnitDelay3;
  } else {
    if (SWC_BCC_IG_FQ_DW.Tj_MODE) {
      SWC_BCC_IG_FQ_DW.uTjCal1_MODE = false;
      SWC_BCC_IG_FQ_DW.Tj_MODE = false;
    }

    BCC_tIGBTTj_FQ = *rtu_HSPF_BUS_HSPF_tDBCTempWFlt;
    BCC_tCoolantTj_FQ = 65.0F;
  }

  *rty_BCC_BUS_BCC_iDcLnkEst = BCE_iDcLnkEst_FQ;
  *rty_BCC_BUS_BCC_tIGBTTj = BCC_tIGBTTj_FQ;
  *rty_BCC_BUS_BCC_tCoolantTj = BCC_tCoolantTj_FQ;
  SWC_BCC_IG_FQ_DW.UnitDelay_DSTATE = *rtu_MCF_BUS_MCF_dycU;
  SWC_BCC_IG_FQ_DW.UnitDelay1_DSTATE = *rtu_MCF_BUS_MCF_dycV;
  SWC_BCC_IG_FQ_DW.UnitDelay2_DSTATE = *rtu_MCF_BUS_MCF_dycW;
}

void SWC_BCC_IG_FQ_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_BCC_IG_FQ_T *const SWC_BCC_IG_FQ_M = &(SWC_BCC_IG_FQ_MdlrefDW.rtm);
  rtmSetErrorStatusPointer(SWC_BCC_IG_FQ_M, rt_errorStatus);
}
