#include "SWC_MPC_IG_FQ.h"
#include "SWC_MPC_IG_FQ_private.h"
#include "look1_iflf_binlcapw.h"
#include "look1_iflf_binlcpw.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlcapw.h"
#include "look2_iflf_binlcpw.h"
#include "look2_iflf_binlxpw.h"

real32_T MPC_idActFlt_FQ;
real32_T MPC_iqActFlt_FQ;
real32_T MPC_Ld_FQ;
real32_T MPC_Lq_FQ;
real32_T MPC_LdSubLq_FQ;
real32_T MPC_psiExc_FQ;
real32_T MPC_TrqMechFlt_FQ;
real32_T MPC_dtCorFac_FQ;
real32_T MPC_Rs_FQ;
real32_T MPC_TrqMech_FQ;
real32_T MPC_IsFlt_FQ;
real32_T MPC_isdMTPA_FQ;
real32_T MPC_isdFF_FQ;
real32_T MPC_isdMTPV_FQ;
real32_T MPC_OmBw_FQ;
real32_T MPC_Rv_FQ;
real32_T VAR_MPC_frqPwmVF_f32_FQ;
real32_T MPC_frqPwmVF_FQ;
real32_T VAR_MPC_CofRandomPwm_f32_FQ;
real32_T MPC_CofRandomPwm_FQ;
real32_T VAR_MPC_TrqMon_f32_FQ;
MdlrefDW_SWC_MPC_IG_FQ_T SWC_MPC_IG_FQ_MdlrefDW;
DW_SWC_MPC_IG_FQ_f_T SWC_MPC_IG_FQ_DW;
void SWC_MPC_IG_FQ(const real32_T *rtu_MCF_BUS_MCF_idDes, const real32_T
                   *rtu_MCF_BUS_MCF_iqDes, const real32_T *rtu_MCF_BUS_MCF_udDes,
                   const real32_T *rtu_MCF_BUS_MCF_Is, const real32_T
                   *rtu_MCF_BUS_MCF_idAct, const real32_T *rtu_MCF_BUS_MCF_iqAct,
                   const real32_T *rtu_MCF_BUS_MCF_uDcLnk, const real32_T
                   *rtu_MCF_BUS_MCF_VoltModuRate, const real32_T
                   *rtu_TDC_BUS_TDC_TrqDes, const real32_T
                   *rtu_HSPF_BUS_HSPF_nSlowFlt, const real32_T
                   *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const uint8_T
                   *rtu_TPC_BUS_TPC_stMotorMod, real32_T
                   *rty_MPC_BUS_MPC_LdSubLq, real32_T *rty_MPC_BUS_MPC_Ld,
                   real32_T *rty_MPC_BUS_MPC_Lq, real32_T *rty_MPC_BUS_MPC_Rs,
                   real32_T *rty_MPC_BUS_MPC_TrqMech, real32_T
                   *rty_MPC_BUS_MPC_TrqMechFlt, real32_T *rty_MPC_BUS_MPC_psiExc,
                   real32_T *rty_MPC_BUS_MPC_IsFlt, real32_T
                   *rty_MPC_BUS_MPC_idActFlt, real32_T *rty_MPC_BUS_MPC_iqActFlt,
                   real32_T *rty_MPC_BUS_MPC_dtCorFac, real32_T
                   *rty_MPC_BUS_MPC_isdMTPA, real32_T *rty_MPC_BUS_MPC_isdFF,
                   real32_T *rty_MPC_BUS_MPC_isdMTPV, real32_T
                   *rty_MPC_BUS_MPC_OmBw, real32_T *rty_MPC_BUS_MPC_Rv, real32_T
                   *rty_MPC_BUS_MPC_frqPwmVF, real32_T
                   *rty_MPC_BUS_MPC_CofRandomPwm)
{
  real32_T rtb_Abs;
  real32_T rtb_Abs1;
  rtb_Abs1 = PRV_CalFltFrq_2ms_FQ / CAL_MPC_idActCutOffFrq_f32_FQ;
  if (rtb_Abs1 < 1.0F) {
    rtb_Abs1 = 1.0F;
  }

  rtb_Abs1 /= MPC_GLB_pi_f32_FQ * 2.0F + rtb_Abs1;
  MPC_idActFlt_FQ = (1.0F - rtb_Abs1) * *rtu_MCF_BUS_MCF_idAct + rtb_Abs1 *
    MPC_idActFlt_FQ;
  rtb_Abs = fabsf(MPC_idActFlt_FQ);
  rtb_Abs1 = PRV_CalFltFrq_2ms_FQ / CAL_MPC_iqActCutOffFrq_f32_FQ;
  if (rtb_Abs1 < 1.0F) {
    rtb_Abs1 = 1.0F;
  }

  rtb_Abs1 /= MPC_GLB_pi_f32_FQ * 2.0F + rtb_Abs1;
  MPC_iqActFlt_FQ = (1.0F - rtb_Abs1) * *rtu_MCF_BUS_MCF_iqAct + rtb_Abs1 *
    MPC_iqActFlt_FQ;
  rtb_Abs1 = fabsf(MPC_iqActFlt_FQ);
  if (CAL_MPC_flgUseLdq_b_FQ) {
    MPC_Ld_FQ = CAL_MPC_Ld_f32_FQ;
    MPC_Lq_FQ = CAL_MPC_Lq_f32_FQ;
  } else {
    MPC_Ld_FQ = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, rtCP_uD_LdTable_bp01Data,
      rtCP_uD_LdTable_bp02Data, rtCP_uD_LdTable_tableData,
      rtCP_uD_LdTable_maxIndex, 19U);
    MPC_Lq_FQ = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, rtCP_uD_LqTable_bp01Data,
      rtCP_uD_LqTable_bp02Data, rtCP_uD_LqTable_tableData,
      rtCP_uD_LqTable_maxIndex, 19U);
  }

  if (CAL_MPC_flgDesOrAct_b_FQ) {
    rtb_Abs = fabsf(*rtu_MCF_BUS_MCF_idDes);
    rtb_Abs1 = fabsf(*rtu_MCF_BUS_MCF_iqDes);
  }

  if (CAL_MPC_flgUseLdSubLq_b_FQ) {
    MPC_LdSubLq_FQ = MPC_Ld_FQ - MPC_Lq_FQ;
  } else if ((*rtu_TPC_BUS_TPC_stMotorMod == 1) || (*rtu_TPC_BUS_TPC_stMotorMod ==
              3)) {
    MPC_LdSubLq_FQ = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, ((const real32_T *)
      &(CAL_MPC_LdSubLqCAx_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAy_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAzMot_af32_FQ[0])), rtCP_LdSubLqMot_maxIndex, 18U);
  } else {
    MPC_LdSubLq_FQ = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, ((const real32_T *)
      &(CAL_MPC_LdSubLqCAx_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAy_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAzGen_af32_FQ[0])), rtCP_LdSubLqGen_maxIndex, 18U);
  }

  MPC_psiExc_FQ = CAL_MPC_Psi_f32_FQ;
  rtb_Abs = (MPC_idActFlt_FQ * MPC_LdSubLq_FQ * MPC_iqActFlt_FQ +
             MPC_iqActFlt_FQ * MPC_psiExc_FQ) * (real32_T)((uint8_T)
    MPC_GLB_MotorPole_u8_FQ) * 1.5F;
  rtb_Abs1 = PRV_CalFltFrq_2ms_FQ / CAL_MPC_TrqMechCutOffFrq_f32_FQ;
  if (rtb_Abs1 < 0.0F) {
    rtb_Abs1 = 0.0F;
  }

  rtb_Abs1 /= MPC_GLB_pi_f32_FQ * 2.0F + rtb_Abs1;
  SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_o = (1.0F - rtb_Abs1) * rtb_Abs + rtb_Abs1 *
    SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_o;
  if (SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_o > 350.0F) {
    MPC_TrqMechFlt_FQ = 350.0F;
  } else if (SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_o < -350.0F) {
    MPC_TrqMechFlt_FQ = -350.0F;
  } else {
    MPC_TrqMechFlt_FQ = SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_o;
  }

  switch (*rtu_TPC_BUS_TPC_stMotorMod) {
   case 1:
    MPC_dtCorFac_FQ = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnFwdMotTableX_n_af32_FQ[0])), ((const
      real32_T *)&(CAL_MPC_tCpnFwdMotTableY_tCpn_af32_FQ[0])), 15U);
    break;

   case 2:
    MPC_dtCorFac_FQ = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnBwdGenTableX_n_af32_FQ[0])), ((const
      real32_T *)&(CAL_MPC_tCpnBwdGenTableY_tCpn_af32_FQ[0])), 15U);
    break;

   case 3:
    MPC_dtCorFac_FQ = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnBwdMotTableX_n_af32_FQ[0])), ((const
      real32_T *)&(CAL_MPC_tCpnBwdMotTableY_tCpn_af32_FQ[0])), 15U);
    break;

   case 4:
    MPC_dtCorFac_FQ = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnFwdGenTableX_n_af32_FQ[0])), ((const
      real32_T *)&(CAL_MPC_tCpnFwdGenTableY_tCpn_af32_FQ[0])), 15U);
    break;

   default:
    MPC_dtCorFac_FQ = 0.6F;
    break;
  }

  if (CAL_MPC_flgUseRs_b_FQ) {
    MPC_Rs_FQ = CAL_MPC_Rs_f32_FQ;
  } else {
    MPC_Rs_FQ = look1_iflf_binlcpw(*rtu_HSPF_BUS_HSPF_tStrrTempFlt,
      rtCP_Rs_TempStr_Tab_bp01Data, rtCP_Rs_TempStr_Tab_tableData, 22U);
  }

  if (rtb_Abs > 350.0F) {
    MPC_TrqMech_FQ = 350.0F;
  } else if (rtb_Abs < -350.0F) {
    MPC_TrqMech_FQ = -350.0F;
  } else {
    MPC_TrqMech_FQ = rtb_Abs;
  }

  rtb_Abs = PRV_CalFltFrq_2ms_FQ / CAL_MPC_IsCutOffFrq_f32_FQ;
  if (rtb_Abs < 1.0F) {
    rtb_Abs = 1.0F;
  }

  rtb_Abs /= MPC_GLB_pi_f32_FQ * 2.0F + rtb_Abs;
  MPC_IsFlt_FQ = (1.0F - rtb_Abs) * *rtu_MCF_BUS_MCF_Is + rtb_Abs * MPC_IsFlt_FQ;
  rtb_Abs = fabsf(*rtu_TDC_BUS_TDC_TrqDes);
  MPC_isdMTPA_FQ = look1_iflf_binlxpw(rtb_Abs, ((const real32_T *)
    &(CAL_MPC_MtpaTableX_Trq_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_MtpaTableY_isd_af32_FQ[0])), 15U);
  rtb_Abs1 = fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt);
  rtb_Abs = look2_iflf_binlxpw(rtb_Abs1, rtb_Abs, ((const real32_T *)
    &(CAL_MPC_isdFFTableX_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_isdFFTableY_Trq_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_isdFFTableZ_isd_af32_FQ[0])), rtCP_MPC_isdFFTable_isd_maxInde, 17U);
  MPC_isdFF_FQ = look1_iflf_binlxpw(*rtu_MCF_BUS_MCF_uDcLnk, ((const real32_T *)
    &(CAL_MPC_isdFFTableX_Udc_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_isdFFTableY_UdcCof_af32_FQ[0])), 7U) * rtb_Abs;
  if ((*rtu_TPC_BUS_TPC_stMotorMod == 1) || (*rtu_TPC_BUS_TPC_stMotorMod == 3))
  {
    MPC_isdMTPV_FQ = look2_iflf_binlxpw(*rtu_MCF_BUS_MCF_uDcLnk, rtb_Abs1, ((
      const real32_T *)&(CAL_MPC_MtpvTableX_Udc_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableY_N_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableZ_idMot_af32_FQ[0])), rtCP_MTPV_Mot_maxIndex, 8U);
  } else {
    MPC_isdMTPV_FQ = look2_iflf_binlxpw(*rtu_MCF_BUS_MCF_uDcLnk, rtb_Abs1, ((
      const real32_T *)&(CAL_MPC_MtpvTableX_Udc_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableY_N_af32_FQ[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableZ_idGen_af32_FQ[0])), rtCP_MTPV_Gen_maxIndex, 8U);
  }

  MPC_OmBw_FQ = look1_iflf_binlcapw(rtb_Abs1, ((const real32_T *)
    &(CAL_MPC_OmbwTableX_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_OmbwTableY_Ombw_af32_FQ[0])), 10U);
  MPC_Rv_FQ = look1_iflf_binlcapw(rtb_Abs1, ((const real32_T *)
    &(CAL_MPC_RvTableX_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_RvTableY_Rv_af32_FQ[0])), 10U);
  VAR_MPC_frqPwmVF_f32_FQ = look2_iflf_binlcapw(*rtu_MCF_BUS_MCF_VoltModuRate,
    *rtu_MCF_BUS_MCF_Is / MPC_GLB_SqrtTwo_f32_FQ, ((const real32_T *)
    &(CAL_MPC_frqPwmVFTableY_VoltModuRate_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_frqPwmVFTableX_Is_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_frqPwmVFTableZ_Frq_af32_FQ[0])), rtCP_VFTable_maxIndex, 13U);
  MPC_frqPwmVF_FQ = VAR_MPC_frqPwmVF_f32_FQ;
  VAR_MPC_CofRandomPwm_f32_FQ = look1_iflf_binlcpw(rtb_Abs1, ((const real32_T *)
    &(CAL_MPC_nCofRpwm_X_af32_FQ[0])), ((const real32_T *)
    &(CAL_MPC_cofRpwm_Y_af32_FQ[0])), 16U);
  MPC_CofRandomPwm_FQ = VAR_MPC_CofRandomPwm_f32_FQ;
  *rty_MPC_BUS_MPC_LdSubLq = MPC_LdSubLq_FQ;
  *rty_MPC_BUS_MPC_iqActFlt = MPC_iqActFlt_FQ;
  *rty_MPC_BUS_MPC_dtCorFac = MPC_dtCorFac_FQ;
  *rty_MPC_BUS_MPC_isdMTPA = MPC_isdMTPA_FQ;
  *rty_MPC_BUS_MPC_isdFF = MPC_isdFF_FQ;
  *rty_MPC_BUS_MPC_isdMTPV = MPC_isdMTPV_FQ;
  *rty_MPC_BUS_MPC_OmBw = MPC_OmBw_FQ;
  *rty_MPC_BUS_MPC_Rv = MPC_Rv_FQ;
  *rty_MPC_BUS_MPC_frqPwmVF = MPC_frqPwmVF_FQ;
  *rty_MPC_BUS_MPC_CofRandomPwm = MPC_CofRandomPwm_FQ;
  *rty_MPC_BUS_MPC_Ld = MPC_Ld_FQ;
  *rty_MPC_BUS_MPC_Lq = MPC_Lq_FQ;
  *rty_MPC_BUS_MPC_Rs = MPC_Rs_FQ;
  *rty_MPC_BUS_MPC_TrqMech = MPC_TrqMech_FQ;
  *rty_MPC_BUS_MPC_TrqMechFlt = MPC_TrqMechFlt_FQ;
  *rty_MPC_BUS_MPC_psiExc = MPC_psiExc_FQ;
  *rty_MPC_BUS_MPC_IsFlt = MPC_IsFlt_FQ;
  *rty_MPC_BUS_MPC_idActFlt = MPC_idActFlt_FQ;
  rtb_Abs = PRV_CalFltFrq_2ms_FQ / CAL_MPC_udActCutOffFrq_f32_FQ;
  if (rtb_Abs < 1.0F) {
    rtb_Abs = 1.0F;
  }

  rtb_Abs /= MPC_GLB_pi_f32_FQ * 2.0F + rtb_Abs;
  SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_od = (1.0F - rtb_Abs) *
    *rtu_MCF_BUS_MCF_udDes + rtb_Abs * SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_od;
  rtb_Abs = PRV_CalFltFrq_2ms_FQ / CAL_MPC_uqActCutOffFrq_f32_FQ;
  if (rtb_Abs < 1.0F) {
    rtb_Abs = 1.0F;
  }

  rtb_Abs /= MPC_GLB_pi_f32_FQ * 2.0F + rtb_Abs;
  SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_k = (1.0F - rtb_Abs) *
    *rtu_MCF_BUS_MCF_udDes + rtb_Abs * SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_k;
  if (rtb_Abs1 >= CAL_MPC_nTrqMonMax_f32_FQ) {
    SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_h = true;
  } else {
    SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_h = ((!(rtb_Abs1 <=
      CAL_MPC_nTrqMonMin_f32_FQ)) && SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_h);
  }

  if (SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_h) {
    rtb_Abs = sqrtf(SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_od *
                    SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_od +
                    SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_k *
                    SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_k);
    if (rtb_Abs > 10000.0F) {
      rtb_Abs = 10000.0F;
    } else {
      if (rtb_Abs < 0.0001F) {
        rtb_Abs = 0.0001F;
      }
    }

    if (rtb_Abs1 <= CAL_MPC_nSetTrqMonMin_f32_FQ) {
      if (*rtu_HSPF_BUS_HSPF_nSlowFlt < 0.0F) {
        rtb_Abs1 = -CAL_MPC_nSetTrqMonMin_f32_FQ;
      } else {
        rtb_Abs1 = CAL_MPC_nSetTrqMonMin_f32_FQ;
      }
    } else {
      rtb_Abs1 = *rtu_HSPF_BUS_HSPF_nSlowFlt;
    }

    VAR_MPC_TrqMon_f32_FQ = ((MPC_idActFlt_FQ *
      SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_od + MPC_iqActFlt_FQ *
      SWC_MPC_IG_FQ_DW.UnitDelay_DSTATE_k) * 1.5F * (1.0F -
      *rtu_MCF_BUS_MCF_uDcLnk * CAL_MPC_CofUdc_f32_FQ / rtb_Abs) - MPC_IsFlt_FQ *
      MPC_IsFlt_FQ * (MPC_Rs_FQ + CAL_MPC_Rcmp_f32_FQ) * 1.5F) / rtb_Abs1 *
      9.55F;
  } else {
    VAR_MPC_TrqMon_f32_FQ = MPC_TrqMech_FQ;
  }
}

void SWC_MPC_IG_FQ_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_MPC_IG_FQ_T *const SWC_MPC_IG_FQ_M = &(SWC_MPC_IG_FQ_MdlrefDW.rtm);
  rtmSetErrorStatusPointer(SWC_MPC_IG_FQ_M, rt_errorStatus);
}
