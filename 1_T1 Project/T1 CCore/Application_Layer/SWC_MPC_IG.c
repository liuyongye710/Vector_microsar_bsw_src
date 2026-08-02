#include "SWC_MPC_IG.h"
#include "SWC_MPC_IG_private.h"
#include "look1_iflf_binlcapw.h"
#include "look1_iflf_binlcpw.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlcapw.h"
#include "look2_iflf_binlcpw.h"
#include "look2_iflf_binlxpw.h"

real32_T MPC_idActFlt;
real32_T MPC_iqActFlt;
real32_T MPC_Ld;
real32_T MPC_Lq;
real32_T MPC_LdSubLq;
real32_T MPC_psiExc;
real32_T MPC_TrqMechFlt;
real32_T MPC_dtCorFac;
real32_T MPC_Rs;
real32_T MPC_TrqMech;
real32_T MPC_IsFlt;
real32_T MPC_isdMTPA;
real32_T MPC_isdFF;
real32_T MPC_isdMTPV;
real32_T MPC_OmBw;
real32_T MPC_Rv;
real32_T VAR_MPC_frqPwmVF_f32;
real32_T MPC_frqPwmVF;
real32_T VAR_MPC_CofRandomPwm_f32;
real32_T MPC_CofRandomPwm;
real32_T VAR_MPC_TrqMon_f32;
MdlrefDW_SWC_MPC_IG_T SWC_MPC_IG_MdlrefDW;
DW_SWC_MPC_IG_f_T SWC_MPC_IG_DW;
void SWC_MPC_IG(const real32_T *rtu_MCF_BUS_MCF_idDes, const real32_T
                *rtu_MCF_BUS_MCF_iqDes, const real32_T *rtu_MCF_BUS_MCF_udDes,
                const real32_T *rtu_MCF_BUS_MCF_Is, const real32_T
                *rtu_MCF_BUS_MCF_idAct, const real32_T *rtu_MCF_BUS_MCF_iqAct,
                const real32_T *rtu_MCF_BUS_MCF_uDcLnk, const real32_T
                *rtu_MCF_BUS_MCF_VoltModuRate, const real32_T
                *rtu_TDC_BUS_TDC_TrqDes, const real32_T
                *rtu_HSPF_BUS_HSPF_nSlowFlt, const real32_T
                *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const uint8_T
                *rtu_TPC_BUS_TPC_stMotorMod, real32_T *rty_MPC_BUS_MPC_LdSubLq,
                real32_T *rty_MPC_BUS_MPC_Ld, real32_T *rty_MPC_BUS_MPC_Lq,
                real32_T *rty_MPC_BUS_MPC_Rs, real32_T *rty_MPC_BUS_MPC_TrqMech,
                real32_T *rty_MPC_BUS_MPC_TrqMechFlt, real32_T
                *rty_MPC_BUS_MPC_psiExc, real32_T *rty_MPC_BUS_MPC_IsFlt,
                real32_T *rty_MPC_BUS_MPC_idActFlt, real32_T
                *rty_MPC_BUS_MPC_iqActFlt, real32_T *rty_MPC_BUS_MPC_dtCorFac,
                real32_T *rty_MPC_BUS_MPC_isdMTPA, real32_T
                *rty_MPC_BUS_MPC_isdFF, real32_T *rty_MPC_BUS_MPC_isdMTPV,
                real32_T *rty_MPC_BUS_MPC_OmBw, real32_T *rty_MPC_BUS_MPC_Rv,
                real32_T *rty_MPC_BUS_MPC_frqPwmVF, real32_T
                *rty_MPC_BUS_MPC_CofRandomPwm)
{
  real32_T rtb_Abs;
  real32_T rtb_Abs1;
  rtb_Abs1 = PRV_CalFltFrq_2ms / CAL_MPC_idActCutOffFrq_f32;
  if (rtb_Abs1 < 1.0F) {
    rtb_Abs1 = 1.0F;
  }

  rtb_Abs1 /= MPC_GLB_pi_f32 * 2.0F + rtb_Abs1;
  MPC_idActFlt = (1.0F - rtb_Abs1) * *rtu_MCF_BUS_MCF_idAct + rtb_Abs1 *
    MPC_idActFlt;
  rtb_Abs = fabsf(MPC_idActFlt);
  rtb_Abs1 = PRV_CalFltFrq_2ms / CAL_MPC_iqActCutOffFrq_f32;
  if (rtb_Abs1 < 1.0F) {
    rtb_Abs1 = 1.0F;
  }

  rtb_Abs1 /= MPC_GLB_pi_f32 * 2.0F + rtb_Abs1;
  MPC_iqActFlt = (1.0F - rtb_Abs1) * *rtu_MCF_BUS_MCF_iqAct + rtb_Abs1 *
    MPC_iqActFlt;
  rtb_Abs1 = fabsf(MPC_iqActFlt);
  if (CAL_MPC_flgUseLdq_b) {
    MPC_Ld = CAL_MPC_Ld_f32;
    MPC_Lq = CAL_MPC_Lq_f32;
  } else {
    MPC_Ld = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, rtCP_uD_LdTable_bp01Data,
      rtCP_uD_LdTable_bp02Data, rtCP_uD_LdTable_tableData,
      rtCP_uD_LdTable_maxIndex, 19U);
    MPC_Lq = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, rtCP_uD_LqTable_bp01Data,
      rtCP_uD_LqTable_bp02Data, rtCP_uD_LqTable_tableData,
      rtCP_uD_LqTable_maxIndex, 19U);
  }

  if (CAL_MPC_flgDesOrAct_b) {
    rtb_Abs = fabsf(*rtu_MCF_BUS_MCF_idDes);
    rtb_Abs1 = fabsf(*rtu_MCF_BUS_MCF_iqDes);
  }

  if (CAL_MPC_flgUseLdSubLq_b) {
    MPC_LdSubLq = MPC_Ld - MPC_Lq;
  } else if ((*rtu_TPC_BUS_TPC_stMotorMod == 1) || (*rtu_TPC_BUS_TPC_stMotorMod ==
              3)) {
    MPC_LdSubLq = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, ((const real32_T *)
      &(CAL_MPC_LdSubLqCAx_af32[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAy_af32[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAzMot_af32[0])), rtCP_LdSubLqMot_maxIndex, 18U);
  } else {
    MPC_LdSubLq = look2_iflf_binlcpw(rtb_Abs, rtb_Abs1, ((const real32_T *)
      &(CAL_MPC_LdSubLqCAx_af32[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAy_af32[0])), ((const real32_T *)
      &(CAL_MPC_LdSubLqCAzGen_af32[0])), rtCP_LdSubLqGen_maxIndex, 18U);
  }

  MPC_psiExc = CAL_MPC_Psi_f32;
  rtb_Abs = (MPC_idActFlt * MPC_LdSubLq * MPC_iqActFlt + MPC_iqActFlt *
             MPC_psiExc) * (real32_T)((uint8_T)MPC_GLB_MotorPole_u8) * 1.5F;
  rtb_Abs1 = PRV_CalFltFrq_2ms / CAL_MPC_TrqMechCutOffFrq_f32;
  if (rtb_Abs1 < 0.0F) {
    rtb_Abs1 = 0.0F;
  }

  rtb_Abs1 /= MPC_GLB_pi_f32 * 2.0F + rtb_Abs1;
  SWC_MPC_IG_DW.UnitDelay_DSTATE_o = (1.0F - rtb_Abs1) * rtb_Abs + rtb_Abs1 *
    SWC_MPC_IG_DW.UnitDelay_DSTATE_o;
  if (SWC_MPC_IG_DW.UnitDelay_DSTATE_o > 350.0F) {
    MPC_TrqMechFlt = 350.0F;
  } else if (SWC_MPC_IG_DW.UnitDelay_DSTATE_o < -350.0F) {
    MPC_TrqMechFlt = -350.0F;
  } else {
    MPC_TrqMechFlt = SWC_MPC_IG_DW.UnitDelay_DSTATE_o;
  }

  switch (*rtu_TPC_BUS_TPC_stMotorMod) {
   case 1:
    MPC_dtCorFac = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnFwdMotTableX_n_af32[0])), ((const real32_T *)
      &(CAL_MPC_tCpnFwdMotTableY_tCpn_af32[0])), 15U);
    break;

   case 2:
    MPC_dtCorFac = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnBwdGenTableX_n_af32[0])), ((const real32_T *)
      &(CAL_MPC_tCpnBwdGenTableY_tCpn_af32[0])), 15U);
    break;

   case 3:
    MPC_dtCorFac = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnBwdMotTableX_n_af32[0])), ((const real32_T *)
      &(CAL_MPC_tCpnBwdMotTableY_tCpn_af32[0])), 15U);
    break;

   case 4:
    MPC_dtCorFac = look1_iflf_binlcapw(fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt), ((
      const real32_T *)&(CAL_MPC_tCpnFwdGenTableX_n_af32[0])), ((const real32_T *)
      &(CAL_MPC_tCpnFwdGenTableY_tCpn_af32[0])), 15U);
    break;

   default:
    MPC_dtCorFac = 0.6F;
    break;
  }

  if (CAL_MPC_flgUseRs_b) {
    MPC_Rs = CAL_MPC_Rs_f32;
  } else {
    MPC_Rs = look1_iflf_binlcpw(*rtu_HSPF_BUS_HSPF_tStrrTempFlt,
      rtCP_Rs_TempStr_Tab_bp01Data, rtCP_Rs_TempStr_Tab_tableData, 22U);
  }

  if (rtb_Abs > 350.0F) {
    MPC_TrqMech = 350.0F;
  } else if (rtb_Abs < -350.0F) {
    MPC_TrqMech = -350.0F;
  } else {
    MPC_TrqMech = rtb_Abs;
  }

  rtb_Abs = PRV_CalFltFrq_2ms / CAL_MPC_IsCutOffFrq_f32;
  if (rtb_Abs < 1.0F) {
    rtb_Abs = 1.0F;
  }

  rtb_Abs /= MPC_GLB_pi_f32 * 2.0F + rtb_Abs;
  MPC_IsFlt = (1.0F - rtb_Abs) * *rtu_MCF_BUS_MCF_Is + rtb_Abs * MPC_IsFlt;
  rtb_Abs = fabsf(*rtu_TDC_BUS_TDC_TrqDes);
  MPC_isdMTPA = look1_iflf_binlxpw(rtb_Abs, ((const real32_T *)
    &(CAL_MPC_MtpaTableX_Trq_af32[0])), ((const real32_T *)
    &(CAL_MPC_MtpaTableY_isd_af32[0])), 14U);
  rtb_Abs1 = fabsf(*rtu_HSPF_BUS_HSPF_nSlowFlt);
  rtb_Abs = look2_iflf_binlxpw(rtb_Abs1, rtb_Abs, ((const real32_T *)
    &(CAL_MPC_isdFFTableX_Spd_af32[0])), ((const real32_T *)
    &(CAL_MPC_isdFFTableY_Trq_af32[0])), ((const real32_T *)
    &(CAL_MPC_isdFFTableZ_isd_af32[0])), rtCP_MPC_isdFFTable_isd_maxInde, 17U);
  MPC_isdFF = look1_iflf_binlxpw(*rtu_MCF_BUS_MCF_uDcLnk, ((const real32_T *)
    &(CAL_MPC_isdFFTableX_Udc_af32[0])), ((const real32_T *)
    &(CAL_MPC_isdFFTableY_UdcCof_af32[0])), 7U) * rtb_Abs;
  if ((*rtu_TPC_BUS_TPC_stMotorMod == 1) || (*rtu_TPC_BUS_TPC_stMotorMod == 3))
  {
    MPC_isdMTPV = look2_iflf_binlxpw(*rtu_MCF_BUS_MCF_uDcLnk, rtb_Abs1, ((const
      real32_T *)&(CAL_MPC_MtpvTableX_Udc_af32[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableY_N_af32[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableZ_idMot_af32[0])), rtCP_MTPV_Mot_maxIndex, 8U);
  } else {
    MPC_isdMTPV = look2_iflf_binlxpw(*rtu_MCF_BUS_MCF_uDcLnk, rtb_Abs1, ((const
      real32_T *)&(CAL_MPC_MtpvTableX_Udc_af32[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableY_N_af32[0])), ((const real32_T *)
      &(CAL_MPC_MtpvTableZ_idGen_af32[0])), rtCP_MTPV_Gen_maxIndex, 8U);
  }

  MPC_OmBw = look1_iflf_binlcapw(rtb_Abs1, ((const real32_T *)
    &(CAL_MPC_OmbwTableX_Spd_af32[0])), ((const real32_T *)
    &(CAL_MPC_OmbwTableY_Ombw_af32[0])), 10U);
  MPC_Rv = look1_iflf_binlcapw(rtb_Abs1, ((const real32_T *)
    &(CAL_MPC_RvTableX_Spd_af32[0])), ((const real32_T *)
    &(CAL_MPC_RvTableY_Rv_af32[0])), 10U);
  VAR_MPC_frqPwmVF_f32 = look2_iflf_binlcapw(*rtu_MCF_BUS_MCF_VoltModuRate,
    *rtu_MCF_BUS_MCF_Is / MPC_GLB_SqrtTwo_f32, ((const real32_T *)
    &(CAL_MPC_frqPwmVFTableY_VoltModuRate_af32[0])), ((const real32_T *)
    &(CAL_MPC_frqPwmVFTableX_Is_af32[0])), ((const real32_T *)
    &(CAL_MPC_frqPwmVFTableZ_Frq_af32[0])), rtCP_VFTable_maxIndex, 13U);
  MPC_frqPwmVF = VAR_MPC_frqPwmVF_f32;
  VAR_MPC_CofRandomPwm_f32 = look1_iflf_binlcpw(rtb_Abs1, ((const real32_T *)
    &(CAL_MPC_nCofRpwm_X_af32[0])), ((const real32_T *)&(CAL_MPC_cofRpwm_Y_af32
    [0])), 16U);
  MPC_CofRandomPwm = VAR_MPC_CofRandomPwm_f32;
  *rty_MPC_BUS_MPC_LdSubLq = MPC_LdSubLq;
  *rty_MPC_BUS_MPC_iqActFlt = MPC_iqActFlt;
  *rty_MPC_BUS_MPC_dtCorFac = MPC_dtCorFac;
  *rty_MPC_BUS_MPC_isdMTPA = MPC_isdMTPA;
  *rty_MPC_BUS_MPC_isdFF = MPC_isdFF;
  *rty_MPC_BUS_MPC_isdMTPV = MPC_isdMTPV;
  *rty_MPC_BUS_MPC_OmBw = MPC_OmBw;
  *rty_MPC_BUS_MPC_Rv = MPC_Rv;
  *rty_MPC_BUS_MPC_frqPwmVF = MPC_frqPwmVF;
  *rty_MPC_BUS_MPC_CofRandomPwm = MPC_CofRandomPwm;
  *rty_MPC_BUS_MPC_Ld = MPC_Ld;
  *rty_MPC_BUS_MPC_Lq = MPC_Lq;
  *rty_MPC_BUS_MPC_Rs = MPC_Rs;
  *rty_MPC_BUS_MPC_TrqMech = MPC_TrqMech;
  *rty_MPC_BUS_MPC_TrqMechFlt = MPC_TrqMechFlt;
  *rty_MPC_BUS_MPC_psiExc = MPC_psiExc;
  *rty_MPC_BUS_MPC_IsFlt = MPC_IsFlt;
  *rty_MPC_BUS_MPC_idActFlt = MPC_idActFlt;
  rtb_Abs = PRV_CalFltFrq_2ms / CAL_MPC_udActCutOffFrq_f32;
  if (rtb_Abs < 1.0F) {
    rtb_Abs = 1.0F;
  }

  rtb_Abs /= MPC_GLB_pi_f32 * 2.0F + rtb_Abs;
  SWC_MPC_IG_DW.UnitDelay_DSTATE_od = (1.0F - rtb_Abs) * *rtu_MCF_BUS_MCF_udDes
    + rtb_Abs * SWC_MPC_IG_DW.UnitDelay_DSTATE_od;
  rtb_Abs = PRV_CalFltFrq_2ms / CAL_MPC_uqActCutOffFrq_f32;
  if (rtb_Abs < 1.0F) {
    rtb_Abs = 1.0F;
  }

  rtb_Abs /= MPC_GLB_pi_f32 * 2.0F + rtb_Abs;
  SWC_MPC_IG_DW.UnitDelay_DSTATE_k = (1.0F - rtb_Abs) * *rtu_MCF_BUS_MCF_udDes +
    rtb_Abs * SWC_MPC_IG_DW.UnitDelay_DSTATE_k;
  if (rtb_Abs1 >= CAL_MPC_nTrqMonMax_f32) {
    SWC_MPC_IG_DW.UnitDelay_DSTATE_h = true;
  } else {
    SWC_MPC_IG_DW.UnitDelay_DSTATE_h = ((!(rtb_Abs1 <= CAL_MPC_nTrqMonMin_f32)) &&
      SWC_MPC_IG_DW.UnitDelay_DSTATE_h);
  }

  if (SWC_MPC_IG_DW.UnitDelay_DSTATE_h) {
    rtb_Abs = sqrtf(SWC_MPC_IG_DW.UnitDelay_DSTATE_od *
                    SWC_MPC_IG_DW.UnitDelay_DSTATE_od +
                    SWC_MPC_IG_DW.UnitDelay_DSTATE_k *
                    SWC_MPC_IG_DW.UnitDelay_DSTATE_k);
    if (rtb_Abs > 10000.0F) {
      rtb_Abs = 10000.0F;
    } else {
      if (rtb_Abs < 0.0001F) {
        rtb_Abs = 0.0001F;
      }
    }

    if (rtb_Abs1 <= CAL_MPC_nSetTrqMonMin_f32) {
      if (*rtu_HSPF_BUS_HSPF_nSlowFlt < 0.0F) {
        rtb_Abs1 = -CAL_MPC_nSetTrqMonMin_f32;
      } else {
        rtb_Abs1 = CAL_MPC_nSetTrqMonMin_f32;
      }
    } else {
      rtb_Abs1 = *rtu_HSPF_BUS_HSPF_nSlowFlt;
    }

    VAR_MPC_TrqMon_f32 = ((MPC_idActFlt * SWC_MPC_IG_DW.UnitDelay_DSTATE_od +
      MPC_iqActFlt * SWC_MPC_IG_DW.UnitDelay_DSTATE_k) * 1.5F * (1.0F -
      *rtu_MCF_BUS_MCF_uDcLnk * CAL_MPC_CofUdc_f32 / rtb_Abs) - MPC_IsFlt *
                          MPC_IsFlt * (MPC_Rs + CAL_MPC_Rcmp_f32) * 1.5F) /
      rtb_Abs1 * 9.55F;
  } else {
    VAR_MPC_TrqMon_f32 = MPC_TrqMech;
  }
}

void SWC_MPC_IG_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_MPC_IG_T *const SWC_MPC_IG_M = &(SWC_MPC_IG_MdlrefDW.rtm);
  rtmSetErrorStatusPointer(SWC_MPC_IG_M, rt_errorStatus);
}
