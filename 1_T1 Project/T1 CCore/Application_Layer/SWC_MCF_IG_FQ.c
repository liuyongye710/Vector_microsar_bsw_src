#include "SWC_MCF_IG_FQ.h"
#include "SWC_MCF_IG_FQ_private.h"
#include "look1_iflf_binlcapw.h"
#include "look1_iflf_binlcpw.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlxpw.h"

real32_T MCF_frqPwm_FQ;
real32_T MCF_cofFrqPwm_FQ;
real32_T VAR_MCF_uDcLnk_f32_FQ;
real32_T MCF_uDcLnk_FQ;
real32_T VAR_MCF_iU_NC_f32_FQ;
real32_T VAR_MCF_iV_NC_f32_FQ;
real32_T VAR_MCF_iW_NC_f32_FQ;
real32_T VAR_MCF_iU_f32_FQ;
real32_T MCF_iU_FQ;
real32_T VAR_MCF_iV_f32_FQ;
real32_T MCF_iV_FQ;
real32_T VAR_MCF_iW_f32_FQ;
real32_T MCF_iW_FQ;
real32_T VAR_MCF_agOffset_f32_FQ;
real32_T VAR_MCF_agRtrEe_f32_FQ;
real32_T VAR_MCF_idAct_f32_FQ;
real32_T MCF_idAct_FQ;
real32_T VAR_MCF_periodCalc_f32_FQ;
real32_T VAR_MCF_UsUseRateDes_f32_FQ;
real32_T VAR_MCF_isdFW_f32_FQ;
real32_T VAR_MCF_idMotHeat_f32_FQ;
real32_T VAR_MCF_idDes_f32_FQ;
real32_T MCF_idDes_FQ;
real32_T VAR_MCF_iqAct_f32_FQ;
real32_T MCF_iqAct_FQ;
real32_T VAR_MCF_udRv_f32_FQ;
real32_T VAR_MCF_MPC_Ld_f32_FQ;
real32_T VAR_MCF_Rdc_nWoFlt_f32_FQ;
real32_T VAR_MCF_MPC_Lq_f32_FQ;
real32_T VAR_MCF_EmfBack_f32_FQ;
real32_T VAR_MCF_uqRv_f32_FQ;
real32_T VAR_MCF_udDes_f32_FQ;
real32_T MCF_udDes_FQ;
real32_T VAR_MCF_uqDes_f32_FQ;
real32_T MCF_uqDes_FQ;
real32_T VAR_MCF_MPC_LdSubLq_f32_FQ;
real32_T VAR_MCF_iqDes_f32_FQ;
real32_T MCF_iqDes_FQ;
real32_T MCF_dtPwm_FQ;
real32_T VAR_MCF_UdDes11ZR_f32_FQ;
real32_T VAR_MCF_UqDes11ZR_f32_FQ;
real32_T VAR_MCF_uAOfsClb_f32_FQ;
real32_T VAR_MCF_uBOfsClb_f32_FQ;
real32_T VAR_MCF_uBetaDeadCpn_f32_FQ;
real32_T VAR_MCF_uAlphaDeadCpn_f32_FQ;
real32_T MCF_dycU_FQ;
real32_T MCF_dycV_FQ;
real32_T MCF_dycW_FQ;
real32_T MCF_tiLock_FQ;
real32_T VAR_MCF_Is_f32_FQ;
real32_T MCF_Is_FQ;
real32_T VAR_MCF_UsUseRateReal_f32_FQ;
real32_T VAR_MCF_usPeak_f32_FQ;
real32_T VAR_MCF_AgRem_f32_FQ;
real32_T MCF_VoltModuRate_FQ;
real32_T VAR_MCF_uAOm_f32_FQ;
real32_T VAR_MCF_uBOm_f32_FQ;
real32_T VAR_MCF_IsSet11ZR_f32_FQ;
real32_T VAR_MCF_IsThetaSet11ZR_f32_FQ;
real32_T VAR_MCF_PCUHeaterPower_f32_FQ;
real32_T VAR_MCF_PowerDcLnk_f32_FQ;
real32_T VAR_MCF_PowerMech_f32_FQ;
real32_T VAR_MCF_PowerMotHeat_f32_FQ;
uint8_T VAR_MCF_HSPF_stIphaOffCal_u8_FQ;
uint8_T MCF_SecVolt_FQ;
uint8_T MCF_stpwmMode_FQ;
uint8_T VAR_MCF_TMAhtChsts_f32_FQ;
boolean_T VAR_MCF_flgMotHeat_b_FQ;
boolean_T VAR_MCF_SCF_flgInitEn_b_FQ;
boolean_T VAR_MCF_FlgDeadCpn_b_FQ;
boolean_T VAR_MCF_flgFw_b_FQ;
MdlrefDW_SWC_MCF_IG_FQ_T SWC_MCF_IG_FQ_MdlrefDW;
B_SWC_MCF_IG_FQ_c_T SWC_MCF_IG_FQ_B;
DW_SWC_MCF_IG_FQ_f_T SWC_MCF_IG_FQ_DW;
void SWC_MCF_IG_FQ_Osc_nrN6(real32_T rtu_MCF_tiY, real32_T rtu_MCF_tiZ, real32_T
  *rty_MCF_tiYout, real32_T *rty_MCF_tiZout)
{
  *rty_MCF_tiYout = -rtu_MCF_tiY;
  *rty_MCF_tiZout = -rtu_MCF_tiZ;
}

void SWC_MCF_IG_FQ(const real32_T *rtu_HSPF_BUS_HSPF_iPhaUOffset, const real32_T
                   *rtu_HSPF_BUS_HSPF_iPhaVOffset, const real32_T
                   *rtu_HSPF_BUS_HSPF_iPhaWOffset, const uint8_T
                   *rtu_HSPF_BUS_HSPF_stIphaOffCal, const real32_T
                   *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const real32_T
                   *rtu_MPC_BUS_MPC_LdSubLq, const real32_T *rtu_MPC_BUS_MPC_Ld,
                   const real32_T *rtu_MPC_BUS_MPC_Lq, const real32_T
                   *rtu_MPC_BUS_MPC_Rs, const real32_T
                   *rtu_MPC_BUS_MPC_TrqMechFlt, const real32_T
                   *rtu_MPC_BUS_MPC_psiExc, const real32_T
                   *rtu_MPC_BUS_MPC_isdMTPA, const real32_T
                   *rtu_MPC_BUS_MPC_isdFF, const real32_T
                   *rtu_MPC_BUS_MPC_isdMTPV, const real32_T
                   *rtu_MPC_BUS_MPC_OmBw, const real32_T *rtu_MPC_BUS_MPC_Rv,
                   const real32_T *rtu_MPC_BUS_MPC_frqPwmVF, const real32_T
                   *rtu_MPC_BUS_MPC_CofRandomPwm, const real32_T
                   *rtu_TDC_trqDes_TDC_TrqDes, const real32_T
                   *rtu_BCC_BUS_BCC_iDcLnkEst, const real32_T *rtu_RDC_agRtrEe,
                   const uint16_T *rtu_CDD_iUNoOff, const uint16_T
                   *rtu_CDD_iVNoOf, const uint16_T *rtu_CDD_iWNoOf, const
                   real32_T *rtu_CDD_uDcLnk, const real32_T *rtu_Rdc_nWoFlt,
                   const boolean_T *rtu_SCF_BUS_SCF_flginitPI, const boolean_T
                   *rtu_SCF_BUS_SCF_flgEnDchaToMc, const uint8_T
                   *rtu_SCF_BUS_SCF_stPwmMode, const real32_T *rtu_SMO_iq_ref,
                   real32_T *rty_MCF_BUS_MCF_idDes, real32_T
                   *rty_MCF_BUS_MCF_iqDes, real32_T *rty_MCF_BUS_MCF_udDes,
                   real32_T *rty_MCF_BUS_MCF_uqDes, real32_T
                   *rty_MCF_BUS_MCF_dycU, real32_T *rty_MCF_BUS_MCF_dycV,
                   real32_T *rty_MCF_BUS_MCF_dycW, uint8_T
                   *rty_MCF_BUS_MCF_SecVolt, real32_T *rty_MCF_BUS_MCF_frqPwm,
                   real32_T *rty_MCF_BUS_MCF_cofFrqPwm, real32_T
                   *rty_MCF_BUS_MCF_dtPwm, real32_T *rty_MCF_BUS_MCF_tiLock,
                   uint8_T *rty_MCF_BUS_MCF_stpwmMode, real32_T
                   *rty_MCF_BUS_MCF_Is, real32_T *rty_MCF_BUS_MCF_idAct,
                   real32_T *rty_MCF_BUS_MCF_iqAct, real32_T
                   *rty_MCF_BUS_MCF_uDcLnk, real32_T *rty_MCF_BUS_MCF_iU,
                   real32_T *rty_MCF_BUS_MCF_iV, real32_T *rty_MCF_BUS_MCF_iW,
                   real32_T *rty_MCF_BUS_MCF_VoltModuRate, real32_T
                   *rty_MCF_BUS_MCF_ialpha, real32_T *rty_MCF_BUS_MCF_ibeta,
                   real32_T *rty_MCF_BUS_MCF_uAlCalc, real32_T
                   *rty_MCF_BUS_MCF_uBCalc)
{
  int32_T rtb_MCF_isqDesCalc_0;
  real32_T rtb_Add_as;
  real32_T rtb_MCF_UMin;
  real32_T rtb_MCF_frqPwmCalc_j;
  real32_T rtb_MCF_ialpha;
  real32_T rtb_MCF_ibeta;
  real32_T rtb_MCF_ratTaSv;
  real32_T rtb_MCF_ratTbSv;
  real32_T rtb_MCF_uAlCalc;
  real32_T rtb_MCF_uBCalc;
  real32_T rtb_MCF_ubBase;
  real32_T rtb_MCF_uqDesPI11ZR;
  real32_T rtb_Product11;
  real32_T rtb_Product2;
  real32_T rtb_Product9_i;
  real32_T rtb_Saturation_o;
  real32_T rtb_Subtract1_f;
  real32_T rtb_Subtract2_l;
  real32_T rtb_Subtract_e;
  uint8_T rtb_Gain1;
  uint8_T rtb_Gain3;
  boolean_T rtb_Compare_ct;
  boolean_T rtb_Switch2_g;
  if ((uint16_T)(SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE_c + 1U) > 1024) {
    SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE_c = 1U;
  } else {
    SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE_c++;
  }

  if (CAL_MCF_flgRpwmFrqRandom_b_FQ) {
    rtb_MCF_ibeta = (rtCP_Constant_Value_lx[SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE_c
                     - 1] - 1.0F) * *rtu_MPC_BUS_MPC_CofRandomPwm + 1.0F;
  } else {
    rtb_MCF_ibeta = 1.0F;
  }

  if (CAL_MCF_flgVF_b_FQ) {
    rtb_MCF_frqPwmCalc_j = *rtu_MPC_BUS_MPC_frqPwmVF;
  } else {
    rtb_MCF_frqPwmCalc_j = CAL_MCF_FixFreq_f32_FQ;
  }

  rtb_Product2 = rtb_MCF_ibeta * rtb_MCF_frqPwmCalc_j;
  rtb_MCF_ibeta = rtb_Product2 - SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE;
  if (rtb_MCF_ibeta <= CAL_MCF_FrqRmp_f32_FQ) {
    if (-rtb_MCF_ibeta <= CAL_MCF_FrqRmp_f32_FQ) {
      SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE = rtb_Product2;
    } else {
      SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE -= CAL_MCF_FrqRmp_f32_FQ;
    }
  } else {
    SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE += CAL_MCF_FrqRmp_f32_FQ;
  }

  if (SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE > 10000.0F) {
    MCF_frqPwm_FQ = 10000.0F;
  } else if (SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE < 2000.0F) {
    MCF_frqPwm_FQ = 2000.0F;
  } else {
    MCF_frqPwm_FQ = SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE;
  }

  MCF_cofFrqPwm_FQ = MCF_frqPwm_FQ / 10000.0F;
  rtb_Product2 = *rtu_CDD_uDcLnk * CAL_MCF_cofFltWe_f32_FQ;
  SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE = (1.0F - CAL_MCF_cofFltWe_f32_FQ) *
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE + rtb_Product2;
  SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_m = (1.0F - CAL_MCF_cofFltWe_f32_FQ) *
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_m + rtb_Product2;
  if (CAL_MCF_bUseduDclnkSet_b_FQ) {
    VAR_MCF_uDcLnk_f32_FQ = CAL_MCF_uDclnkSet_f32_FQ;
  } else if (CAL_MCF_flgLowOrHvudcLnk_b_FQ) {
    VAR_MCF_uDcLnk_f32_FQ = SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE;
  } else {
    VAR_MCF_uDcLnk_f32_FQ = SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_m;
  }

  MCF_uDcLnk_FQ = VAR_MCF_uDcLnk_f32_FQ;
  VAR_MCF_HSPF_stIphaOffCal_u8_FQ = *rtu_HSPF_BUS_HSPF_stIphaOffCal;
  if (VAR_MCF_HSPF_stIphaOffCal_u8_FQ == ((uint8_T)MCF_Succeed_u8_FQ)) {
    rtb_MCF_uqDesPI11ZR = *rtu_HSPF_BUS_HSPF_iPhaUOffset;
  } else {
    rtb_MCF_uqDesPI11ZR = (real32_T)((uint16_T)MCF_GLB_DigtValue_u16_FQ) *
      MCF_GLB_OneHalf_f32_FQ;
  }

  VAR_MCF_iU_NC_f32_FQ = ((real32_T)*rtu_CDD_iUNoOff - rtb_MCF_uqDesPI11ZR) *
    CAL_MCF_iUCnvFac_f32_FQ;
  if (VAR_MCF_HSPF_stIphaOffCal_u8_FQ == ((uint8_T)MCF_Succeed_u8_FQ)) {
    rtb_MCF_uqDesPI11ZR = *rtu_HSPF_BUS_HSPF_iPhaVOffset;
  } else {
    rtb_MCF_uqDesPI11ZR = (real32_T)((uint16_T)MCF_GLB_DigtValue_u16_FQ) *
      MCF_GLB_OneHalf_f32_FQ;
  }

  VAR_MCF_iV_NC_f32_FQ = ((real32_T)*rtu_CDD_iVNoOf - rtb_MCF_uqDesPI11ZR) *
    CAL_MCF_iVCnvFac_f32_FQ;
  if (VAR_MCF_HSPF_stIphaOffCal_u8_FQ == ((uint8_T)MCF_Succeed_u8_FQ)) {
    rtb_MCF_uqDesPI11ZR = *rtu_HSPF_BUS_HSPF_iPhaWOffset;
  } else {
    rtb_MCF_uqDesPI11ZR = (real32_T)((uint16_T)MCF_GLB_DigtValue_u16_FQ) *
      MCF_GLB_OneHalf_f32_FQ;
  }

  VAR_MCF_iW_NC_f32_FQ = ((real32_T)*rtu_CDD_iWNoOf - rtb_MCF_uqDesPI11ZR) *
    CAL_MCF_iWCnvFac_f32_FQ;
  switch (CAL_MCF_stChangePha_u8_FQ) {
   case 1:
    VAR_MCF_iU_f32_FQ = VAR_MCF_iU_NC_f32_FQ;
    break;

   case 2:
    VAR_MCF_iU_f32_FQ = VAR_MCF_iU_NC_f32_FQ;
    break;

   case 3:
    VAR_MCF_iU_f32_FQ = VAR_MCF_iV_NC_f32_FQ;
    break;

   case 4:
    VAR_MCF_iU_f32_FQ = VAR_MCF_iW_NC_f32_FQ;
    break;

   case 5:
    VAR_MCF_iU_f32_FQ = VAR_MCF_iV_NC_f32_FQ;
    break;

   default:
    VAR_MCF_iU_f32_FQ = VAR_MCF_iW_NC_f32_FQ;
    break;
  }

  MCF_iU_FQ = VAR_MCF_iU_f32_FQ;
  switch (CAL_MCF_stChangePha_u8_FQ) {
   case 1:
    VAR_MCF_iV_f32_FQ = VAR_MCF_iV_NC_f32_FQ;
    break;

   case 2:
    VAR_MCF_iV_f32_FQ = VAR_MCF_iW_NC_f32_FQ;
    break;

   case 3:
    VAR_MCF_iV_f32_FQ = VAR_MCF_iU_NC_f32_FQ;
    break;

   case 4:
    VAR_MCF_iV_f32_FQ = VAR_MCF_iU_NC_f32_FQ;
    break;

   case 5:
    VAR_MCF_iV_f32_FQ = VAR_MCF_iW_NC_f32_FQ;
    break;

   default:
    VAR_MCF_iV_f32_FQ = VAR_MCF_iV_NC_f32_FQ;
    break;
  }

  MCF_iV_FQ = VAR_MCF_iV_f32_FQ;
  switch (CAL_MCF_stChangePha_u8_FQ) {
   case 1:
    VAR_MCF_iW_f32_FQ = VAR_MCF_iW_NC_f32_FQ;
    break;

   case 2:
    VAR_MCF_iW_f32_FQ = VAR_MCF_iV_NC_f32_FQ;
    break;

   case 3:
    VAR_MCF_iW_f32_FQ = VAR_MCF_iW_NC_f32_FQ;
    break;

   case 4:
    VAR_MCF_iW_f32_FQ = VAR_MCF_iV_NC_f32_FQ;
    break;

   case 5:
    VAR_MCF_iW_f32_FQ = VAR_MCF_iU_NC_f32_FQ;
    break;

   default:
    VAR_MCF_iW_f32_FQ = VAR_MCF_iU_NC_f32_FQ;
    break;
  }

  MCF_iW_FQ = VAR_MCF_iW_f32_FQ;
  rtb_MCF_ialpha = ((2.0F * MCF_iU_FQ - MCF_iV_FQ) - MCF_iW_FQ) * 0.33333F;
  rtb_MCF_ibeta = (MCF_iV_FQ - MCF_iW_FQ) * 0.33333F * MCF_GLB_SqrtThree_f32_FQ;
  if (CAL_MCF_flgInternalOffset_b_FQ) {
    VAR_MCF_agOffset_f32_FQ = CAL_MCF_OffsetInternal_f32_FQ;
  } else {
    VAR_MCF_agOffset_f32_FQ = 0.0F;
  }

  VAR_MCF_agRtrEe_f32_FQ = VAR_MCF_agOffset_f32_FQ + *rtu_RDC_agRtrEe;
  if (360.0F <= VAR_MCF_agRtrEe_f32_FQ) {
    VAR_MCF_agRtrEe_f32_FQ -= 360.0F;
  } else {
    if (VAR_MCF_agRtrEe_f32_FQ <= 0.0F) {
      VAR_MCF_agRtrEe_f32_FQ += 360.0F;
    }
  }

  rtb_MCF_ubBase = VAR_MCF_agRtrEe_f32_FQ * (real32_T)((uint16_T)
    MCF_GLB_DigtValue_u16_FQ) / MCF_GLB_CircAge_f32_FQ;
  if (rtb_MCF_ubBase > 4095.0F) {
    rtb_Product2 = 4095.0F;
    rtb_MCF_ubBase = 4095.0F;
  } else {
    if (rtb_MCF_ubBase < 0.0F) {
      rtb_Product2 = 0.0F;
    } else {
      rtb_Product2 = rtb_MCF_ubBase;
    }

    if (rtb_MCF_ubBase < 0.0F) {
      rtb_MCF_ubBase = 0.0F;
    }
  }

  rtb_MCF_uAlCalc = rtCP_LookupCosTable_table_b[(int32_T)rtb_Product2];
  rtb_MCF_ubBase = rtCP_LookupSinTable_table_a[(int32_T)rtb_MCF_ubBase];
  VAR_MCF_idAct_f32_FQ = rtb_MCF_uAlCalc * rtb_MCF_ialpha + rtb_MCF_ubBase *
    rtb_MCF_ibeta;
  MCF_idAct_FQ = VAR_MCF_idAct_f32_FQ;
  rtb_Subtract1_f = *rtu_MPC_BUS_MPC_isdMTPA - *rtu_MPC_BUS_MPC_isdMTPA;
  rtb_Product2 = rtb_MCF_frqPwmCalc_j - SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e;
  if (rtb_Product2 <= CAL_MCF_FrqRmp_f32_FQ) {
    if (-rtb_Product2 <= CAL_MCF_FrqRmp_f32_FQ) {
      SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e = rtb_MCF_frqPwmCalc_j;
    } else {
      SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e -= CAL_MCF_FrqRmp_f32_FQ;
    }
  } else {
    SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e += CAL_MCF_FrqRmp_f32_FQ;
  }

  if (SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e > 10000.0F) {
    rtb_MCF_UMin = 10000.0F;
  } else if (SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e < 2000.0F) {
    rtb_MCF_UMin = 2000.0F;
  } else {
    rtb_MCF_UMin = SWC_MCF_IG_FQ_DW.UnitDelay2_DSTATE_e;
  }

  rtb_MCF_uBCalc = 1.0F / rtb_MCF_UMin;
  VAR_MCF_periodCalc_f32_FQ = rtb_MCF_uBCalc;
  if (VAR_MCF_UsUseRateReal_f32_FQ > 20.0F) {
    rtb_MCF_frqPwmCalc_j = 20.0F;
  } else if (VAR_MCF_UsUseRateReal_f32_FQ < -1.0F) {
    rtb_MCF_frqPwmCalc_j = -1.0F;
  } else {
    rtb_MCF_frqPwmCalc_j = VAR_MCF_UsUseRateReal_f32_FQ;
  }

  rtb_Saturation_o = fabsf(*rtu_Rdc_nWoFlt);
  rtb_MCF_uqDesPI11ZR = look1_iflf_binlcapw(rtb_Saturation_o, ((const real32_T *)
    &(CAL_MCF_UsUseRateDesTableX_Spd_af32_FQ[0])), ((const real32_T *)
    &(CAL_MCF_UsUseRateDesTableY_UsRes_af32_FQ[0])), 10U);
  if (rtb_MCF_uqDesPI11ZR > 0.92F) {
    rtb_MCF_uqDesPI11ZR = 0.92F;
  } else {
    if (rtb_MCF_uqDesPI11ZR < 1.0E-6F) {
      rtb_MCF_uqDesPI11ZR = 1.0E-6F;
    }
  }

  VAR_MCF_UsUseRateDes_f32_FQ = 1.0F / rtb_MCF_uqDesPI11ZR - 1.0F;
  rtb_Product2 = rtb_MCF_frqPwmCalc_j - VAR_MCF_UsUseRateDes_f32_FQ;
  rtb_Subtract2_l = *rtu_MPC_BUS_MPC_isdMTPV - *rtu_MPC_BUS_MPC_isdMTPA;
  if (*rtu_SCF_BUS_SCF_flginitPI) {
    VAR_MCF_isdFW_f32_FQ = 0.0F;
  } else {
    VAR_MCF_isdFW_f32_FQ += CAL_MCF_isdfwKi_f32_FQ * 10000.0F *
      VAR_MCF_periodCalc_f32_FQ * rtb_Product2 + (rtb_Product2 -
      SWC_MCF_IG_FQ_DW.Delay2_DSTATE) * CAL_MCF_isdfwKp_f32_FQ;
    if (VAR_MCF_isdFW_f32_FQ > rtb_Subtract1_f) {
      VAR_MCF_isdFW_f32_FQ = rtb_Subtract1_f;
    } else {
      if (VAR_MCF_isdFW_f32_FQ < rtb_Subtract2_l) {
        VAR_MCF_isdFW_f32_FQ = rtb_Subtract2_l;
      }
    }
  }

  if (CAL_MCF_flgUseFF_b_FQ) {
    VAR_MCF_isdFW_f32_FQ += *rtu_MPC_BUS_MPC_isdFF - *rtu_MPC_BUS_MPC_isdMTPA;
  }

  if (VAR_MCF_isdFW_f32_FQ > rtb_Subtract1_f) {
    VAR_MCF_isdFW_f32_FQ = rtb_Subtract1_f;
  } else {
    if (VAR_MCF_isdFW_f32_FQ < rtb_Subtract2_l) {
      VAR_MCF_isdFW_f32_FQ = rtb_Subtract2_l;
    }
  }

  VAR_MCF_flgMotHeat_b_FQ = false;
  if (SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_i) {
    SWC_MCF_IG_FQ_B.uDLookupTable = look1_iflf_binlxpw
      (*rtu_HSPF_BUS_HSPF_tStrrTempFlt, ((const real32_T *)
        &(CAL_tStrrTempFltMotHeat_af32_FQ[0])), ((const real32_T *)
        &(CAL_cofPowerLimitMotHeat_af32_FQ[0])), 8U);
    if (CAL_PowerMotHeat_f32_FQ > CAL_MCF_UpPowerHeat_f32_FQ) {
      rtb_MCF_uqDesPI11ZR = CAL_MCF_UpPowerHeat_f32_FQ;
    } else if (CAL_PowerMotHeat_f32_FQ < 0.0F) {
      rtb_MCF_uqDesPI11ZR = 0.0F;
    } else {
      rtb_MCF_uqDesPI11ZR = CAL_PowerMotHeat_f32_FQ;
    }

    VAR_MCF_PCUHeaterPower_f32_FQ = rtb_MCF_uqDesPI11ZR *
      SWC_MCF_IG_FQ_B.uDLookupTable;
    VAR_MCF_PowerDcLnk_f32_FQ = *rtu_BCC_BUS_BCC_iDcLnkEst * MCF_uDcLnk_FQ *
      0.001F;
    VAR_MCF_PowerMech_f32_FQ = *rtu_MPC_BUS_MPC_TrqMechFlt * *rtu_Rdc_nWoFlt *
      0.000104712039F;
    VAR_MCF_PowerMotHeat_f32_FQ = VAR_MCF_PowerDcLnk_f32_FQ -
      VAR_MCF_PowerMech_f32_FQ;
    rtb_Subtract1_f = VAR_MCF_PowerMotHeat_f32_FQ -
      VAR_MCF_PCUHeaterPower_f32_FQ;
    if (VAR_MCF_flgMotHeat_b_FQ) {
      if (SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g > CAL_MCF_UpLimitIMotHeat_f32_FQ)
      {
        SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g = CAL_MCF_UpLimitIMotHeat_f32_FQ;
      } else {
        if (SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g <
            CAL_MCF_DownLimitIMotHeat_f32_FQ) {
          SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g = CAL_MCF_DownLimitIMotHeat_f32_FQ;
        }
      }

      SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g += rtb_Subtract1_f *
        CAL_MCF_KiMotHeat_f32_FQ;
    } else {
      SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g = 0.0F;
    }

    rtb_Subtract1_f = rtb_Subtract1_f * CAL_MCF_KpMotHeat_f32_FQ +
      SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_g;
    if (rtb_Subtract1_f > CAL_MCF_UpLimitPIMotHeat_f32_FQ) {
      rtb_Subtract1_f = CAL_MCF_UpLimitPIMotHeat_f32_FQ;
    } else {
      if (rtb_Subtract1_f < CAL_MCF_DownLimitPIMotHeat_f32_FQ) {
        rtb_Subtract1_f = CAL_MCF_DownLimitPIMotHeat_f32_FQ;
      }
    }

    if (rtb_Subtract1_f >= *rtu_MPC_BUS_MPC_isdMTPA) {
      SWC_MCF_IG_FQ_B.Switch = 0.0F;
    } else {
      SWC_MCF_IG_FQ_B.Switch = rtb_Subtract1_f - *rtu_MPC_BUS_MPC_isdMTPA;
    }
  }

  if (VAR_MCF_flgMotHeat_b_FQ) {
    VAR_MCF_idMotHeat_f32_FQ = SWC_MCF_IG_FQ_B.Switch;
  } else {
    VAR_MCF_idMotHeat_f32_FQ = 0.0F;
  }

  if (CAL_MCF_flgUseisTheta_b_FQ) {
    rtb_MCF_uqDesPI11ZR = 11.375F * CAL_MCF_isThetaSet_f32_FQ;
    if (rtb_MCF_uqDesPI11ZR > 4095.0F) {
      rtb_MCF_uqDesPI11ZR = 4095.0F;
    } else {
      if (rtb_MCF_uqDesPI11ZR < 0.0F) {
        rtb_MCF_uqDesPI11ZR = 0.0F;
      }
    }

    VAR_MCF_idDes_f32_FQ = CAL_MCF_isSet_f32_FQ * rtCP_Constant_Value_m[(int32_T)
      rtb_MCF_uqDesPI11ZR];
  } else if (CAL_MCF_flgUseisdqSet_b_FQ) {
    VAR_MCF_idDes_f32_FQ = CAL_MCF_isdSet_f32_FQ;
  } else if (*rtu_SCF_BUS_SCF_flgEnDchaToMc) {
    VAR_MCF_idDes_f32_FQ = CAL_MCF_DisChaisdDes_f32_FQ;
  } else {
    VAR_MCF_idDes_f32_FQ = (VAR_MCF_isdFW_f32_FQ + VAR_MCF_idMotHeat_f32_FQ) +
      *rtu_MPC_BUS_MPC_isdMTPA;
  }

  MCF_idDes_FQ = VAR_MCF_idDes_f32_FQ;
  VAR_MCF_iqAct_f32_FQ = rtb_MCF_uAlCalc * rtb_MCF_ibeta - rtb_MCF_ubBase *
    rtb_MCF_ialpha;
  MCF_iqAct_FQ = VAR_MCF_iqAct_f32_FQ;
  VAR_MCF_udRv_f32_FQ = *rtu_MPC_BUS_MPC_Rv * MCF_idAct_FQ;
  rtb_Subtract_e = MCF_idDes_FQ - MCF_idAct_FQ;
  rtb_MCF_UMin /= 10000.0F;
  rtb_Product11 = *rtu_MPC_BUS_MPC_OmBw * rtb_MCF_UMin;
  VAR_MCF_MPC_Ld_f32_FQ = *rtu_MPC_BUS_MPC_Ld;
  VAR_MCF_SCF_flgInitEn_b_FQ = *rtu_SCF_BUS_SCF_flginitPI;
  rtb_Add_as = *rtu_MPC_BUS_MPC_Rv + *rtu_MPC_BUS_MPC_Rs;
  rtb_MCF_ubBase = rtb_MCF_uBCalc * rtb_MCF_UMin;
  VAR_MCF_Rdc_nWoFlt_f32_FQ = *rtu_Rdc_nWoFlt;
  rtb_MCF_UMin = VAR_MCF_Rdc_nWoFlt_f32_FQ * 0.0666666701F * MCF_GLB_pi_f32_FQ *
    2.0F;
  VAR_MCF_MPC_Lq_f32_FQ = *rtu_MPC_BUS_MPC_Lq;
  rtb_MCF_uAlCalc = *rtu_SMO_iq_ref - MCF_iqAct_FQ;
  if (VAR_MCF_SCF_flgInitEn_b_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_n = 0.0F;
  } else {
    if (CAL_MCF_flgUseUsOver_b_FQ) {
      rtb_MCF_uqDesPI11ZR = CAL_MCF_udOverGain_f32_FQ *
        SWC_MCF_IG_FQ_DW.Delay_DSTATE;
    } else {
      rtb_MCF_uqDesPI11ZR = 0.0F;
    }

    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_n += (rtb_Product11 * rtb_Add_as *
      rtb_Subtract_e * CAL_MCF_udki_f32_FQ * rtb_MCF_ubBase - rtb_MCF_UMin *
      VAR_MCF_MPC_Lq_f32_FQ * rtb_MCF_uAlCalc * rtb_Product11 * (rtb_MCF_ubBase *
      CAL_MCF_udDecoupki_f32_FQ)) - rtb_MCF_uqDesPI11ZR;
  }

  rtb_Subtract1_f = (rtb_Product11 * VAR_MCF_MPC_Ld_f32_FQ * rtb_Subtract_e *
                     CAL_MCF_udkp_f32_FQ - VAR_MCF_udRv_f32_FQ) +
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_n;
  rtb_Subtract2_l = MCF_uDcLnk_FQ * 0.667F;
  if (VAR_MCF_SCF_flgInitEn_b_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE = 0.0F;
  } else {
    if (CAL_MCF_flgUseUsOver_b_FQ) {
      rtb_MCF_uqDesPI11ZR = CAL_MCF_uqOverGain_f32_FQ *
        SWC_MCF_IG_FQ_DW.Delay1_DSTATE;
    } else {
      rtb_MCF_uqDesPI11ZR = 0.0F;
    }

    SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE += (rtb_MCF_UMin * VAR_MCF_MPC_Ld_f32_FQ *
      rtb_Subtract_e * rtb_Product11 * (rtb_MCF_ubBase *
      CAL_MCF_uqDecoupki_f32_FQ) + rtb_Product11 * rtb_Add_as * rtb_MCF_uAlCalc *
      CAL_MCF_uqki_f32_FQ * rtb_MCF_ubBase) - rtb_MCF_uqDesPI11ZR;
  }

  SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_l = (1.0F - CAL_MCF_cofFltWe_f32_FQ) *
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_l + rtb_MCF_UMin * CAL_MCF_cofFltWe_f32_FQ;
  VAR_MCF_EmfBack_f32_FQ = SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_l *
    *rtu_MPC_BUS_MPC_psiExc;
  VAR_MCF_uqRv_f32_FQ = *rtu_MPC_BUS_MPC_Rv * MCF_iqAct_FQ;
  rtb_Product11 = ((rtb_Product11 * VAR_MCF_MPC_Lq_f32_FQ * rtb_MCF_uAlCalc *
                    CAL_MCF_uqkp_f32_FQ + SWC_MCF_IG_FQ_DW.UnitDelay1_DSTATE) +
                   VAR_MCF_EmfBack_f32_FQ) - VAR_MCF_uqRv_f32_FQ;
  rtb_MCF_uqDesPI11ZR = sqrtf(rtb_Subtract1_f * rtb_Subtract1_f + rtb_Product11 *
    rtb_Product11);
  if (rtb_MCF_uqDesPI11ZR > 1.0E+6F) {
    rtb_MCF_uqDesPI11ZR = 1.0E+6F;
  } else {
    if (rtb_MCF_uqDesPI11ZR < 1.0E-6F) {
      rtb_MCF_uqDesPI11ZR = 1.0E-6F;
    }
  }

  rtb_MCF_uAlCalc = rtb_Subtract2_l / rtb_MCF_uqDesPI11ZR;
  rtb_Switch2_g = !(rtb_MCF_uAlCalc - CAL_MCF_OverPointSet_f32_FQ >= 0.0F);
  if (CAL_MCF_flgUseUsdqSet_b_FQ) {
    VAR_MCF_udDes_f32_FQ = CAL_MCF_UsdScalSet_f32_FQ;
    VAR_MCF_uqDes_f32_FQ = CAL_MCF_UsqScalSet_f32_FQ;
  } else {
    if (rtb_Switch2_g) {
      VAR_MCF_udDes_f32_FQ = rtb_MCF_uAlCalc * rtb_Subtract1_f;
    } else {
      VAR_MCF_udDes_f32_FQ = rtb_Subtract1_f;
    }

    if (rtb_Switch2_g) {
      VAR_MCF_uqDes_f32_FQ = rtb_MCF_uAlCalc * rtb_Product11;
    } else {
      VAR_MCF_uqDes_f32_FQ = rtb_Product11;
    }
  }

  MCF_udDes_FQ = VAR_MCF_udDes_f32_FQ;
  MCF_uqDes_FQ = VAR_MCF_uqDes_f32_FQ;
  VAR_MCF_MPC_LdSubLq_f32_FQ = *rtu_MPC_BUS_MPC_LdSubLq;
  rtb_MCF_uqDesPI11ZR = (VAR_MCF_MPC_LdSubLq_f32_FQ * VAR_MCF_idDes_f32_FQ +
    *rtu_MPC_BUS_MPC_psiExc) * 1.5F * (real32_T)((uint8_T)
    MCF_GLB_MotorPole_u8_FQ);
  if (rtb_MCF_uqDesPI11ZR > 255.0F) {
    rtb_MCF_uqDesPI11ZR = 255.0F;
  } else {
    if (rtb_MCF_uqDesPI11ZR < 0.01F) {
      rtb_MCF_uqDesPI11ZR = 0.01F;
    }
  }

  VAR_MCF_iqDes_f32_FQ = *rtu_TDC_trqDes_TDC_TrqDes / rtb_MCF_uqDesPI11ZR;
  if (CAL_MCF_flgUseisTheta_b_FQ) {
    rtb_MCF_uqDesPI11ZR = 11.375F * CAL_MCF_isThetaSet_f32_FQ;
    if (rtb_MCF_uqDesPI11ZR > 4095.0F) {
      rtb_MCF_uqDesPI11ZR = 4095.0F;
    } else {
      if (rtb_MCF_uqDesPI11ZR < 0.0F) {
        rtb_MCF_uqDesPI11ZR = 0.0F;
      }
    }

    VAR_MCF_iqDes_f32_FQ = CAL_MCF_isSet_f32_FQ * rtCP_McFwc_SinTable_table
      [(int32_T)rtb_MCF_uqDesPI11ZR];
  } else if (CAL_MCF_flgUseisdqSet_b_FQ) {
    VAR_MCF_iqDes_f32_FQ = CAL_MCF_isqSet_f32_FQ;
  } else if (*rtu_SCF_BUS_SCF_flgEnDchaToMc) {
    VAR_MCF_iqDes_f32_FQ = CAL_MCF_DisChaisqDes_f32_FQ;
  } else {
    rtb_MCF_uAlCalc = CAL_MCF_isMax_f32_FQ * CAL_MCF_isMax_f32_FQ -
      VAR_MCF_idDes_f32_FQ * VAR_MCF_idDes_f32_FQ;
    if (rtb_MCF_uAlCalc <= VAR_MCF_iqDes_f32_FQ * VAR_MCF_iqDes_f32_FQ) {
      if (VAR_MCF_iqDes_f32_FQ >= 0.0F) {
        rtb_MCF_isqDesCalc_0 = 1;
      } else {
        rtb_MCF_isqDesCalc_0 = -1;
      }

      VAR_MCF_iqDes_f32_FQ = sqrtf(rtb_MCF_uAlCalc) * (real32_T)
        rtb_MCF_isqDesCalc_0;
    }
  }

  MCF_iqDes_FQ = VAR_MCF_iqDes_f32_FQ;
  MCF_dtPwm_FQ = 1.0F / MCF_frqPwm_FQ;
  if (CAL_MCF_flgUse1113ZR_b_FQ) {
    rtb_MCF_uAlCalc = VAR_MCF_agRtrEe_f32_FQ * -12.0F;
    rtb_MCF_uqDesPI11ZR = floorf(rtb_MCF_uAlCalc * 0.00277777785F);
    if (rtIsNaNF(rtb_MCF_uqDesPI11ZR) || rtIsInfF(rtb_MCF_uqDesPI11ZR)) {
      rtb_MCF_uqDesPI11ZR = 0.0F;
    } else {
      rtb_MCF_uqDesPI11ZR = fmodf(rtb_MCF_uqDesPI11ZR, 256.0F);
    }

    rtb_Subtract_e = (rtb_MCF_uAlCalc - (real32_T)(rtb_MCF_uqDesPI11ZR < 0.0F ?
      (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_MCF_uqDesPI11ZR : (int32_T)(int8_T)
      (uint8_T)rtb_MCF_uqDesPI11ZR) * 360.0F) * ((real32_T)((uint16_T)
      MCF_GLB_DigtValue_u16_FQ) / MCF_GLB_CircAge_f32_FQ);
    if (rtb_Subtract_e > 4095.0F) {
      rtb_MCF_uAlCalc = 4095.0F;
    } else if (rtb_Subtract_e < 0.0F) {
      rtb_MCF_uAlCalc = 0.0F;
    } else {
      rtb_MCF_uAlCalc = rtb_Subtract_e;
    }

    rtb_MCF_uAlCalc = rtCP_LookupCosTable_table[(int32_T)rtb_MCF_uAlCalc];
    VAR_MCF_IsSet11ZR_f32_FQ = look1_iflf_binlxpw(*rtu_Rdc_nWoFlt, ((const
      real32_T *)&(CAL_MCF_HarmIn1113ZRX_Spd_af32_FQ[0])), ((const real32_T *)
      &(CAL_MCF_HarmIn11ZRY_Is_af32_FQ[0])), 22U);
    VAR_MCF_IsThetaSet11ZR_f32_FQ = look1_iflf_binlxpw(*rtu_Rdc_nWoFlt, ((const
      real32_T *)&(CAL_MCF_HarmIn1113ZRX_Spd_af32_FQ[0])), ((const real32_T *)
      &(CAL_MCF_HarmIn11ZRY_Thetam_af32_FQ[0])), 22U);
    if (CAL_MCF_flgHarmInIsThetaTab11ZR_b_FQ) {
      rtb_Add_as = VAR_MCF_IsSet11ZR_f32_FQ;
      rtb_MCF_ubBase = VAR_MCF_IsThetaSet11ZR_f32_FQ;
    } else {
      rtb_Add_as = CAL_MCF_IsSet11ZR_f32_FQ;
      rtb_MCF_ubBase = CAL_MCF_IsThetaSet11ZR_f32_FQ;
    }

    rtb_MCF_ubBase *= 11.375F;
    if (rtb_MCF_ubBase > 4095.0F) {
      rtb_MCF_uqDesPI11ZR = 4095.0F;
      rtb_MCF_ubBase = 4095.0F;
    } else {
      if (rtb_MCF_ubBase < 0.0F) {
        rtb_MCF_uqDesPI11ZR = 0.0F;
      } else {
        rtb_MCF_uqDesPI11ZR = rtb_MCF_ubBase;
      }

      if (rtb_MCF_ubBase < 0.0F) {
        rtb_MCF_ubBase = 0.0F;
      }
    }

    rtb_MCF_UMin = rtb_Add_as * rtCP_LookupCosineTab_table[(int32_T)
      rtb_MCF_uqDesPI11ZR];
    rtb_Product9_i = (real32_T)((uint8_T)MCF_GLB_MotorPole_u8_FQ) *
      0.0166666675F * *rtu_Rdc_nWoFlt * 2.0F * MCF_GLB_pi_f32_FQ;
    rtb_MCF_uqDesPI11ZR = (*rtu_MPC_BUS_MPC_Lq + *rtu_MPC_BUS_MPC_Ld) *
      rtb_Product9_i * 5.5F;
    rtb_Add_as *= rtCP_LookupSineTab_table[(int32_T)rtb_MCF_ubBase];
    rtb_Product9_i = (*rtu_MPC_BUS_MPC_Ld - *rtu_MPC_BUS_MPC_Lq) *
      rtb_Product9_i * 5.5F;
    rtb_MCF_ubBase = (rtb_MCF_UMin * 0.006F + rtb_MCF_uqDesPI11ZR * rtb_Add_as)
      - rtb_Product9_i * 0.0F;
    if (rtb_Subtract_e > 4095.0F) {
      rtb_Subtract_e = 4095.0F;
    } else {
      if (rtb_Subtract_e < 0.0F) {
        rtb_Subtract_e = 0.0F;
      }
    }

    rtb_Subtract_e = rtCP_LookupSinTable_table[(int32_T)rtb_Subtract_e];
    rtb_MCF_uqDesPI11ZR = (rtb_Add_as * 0.006F - rtb_MCF_uqDesPI11ZR *
      rtb_MCF_UMin) - rtb_Product9_i * 0.0F;
    SWC_MCF_IG_FQ_B.MCF_udDes11ZR = rtb_MCF_ubBase * rtb_MCF_uAlCalc -
      rtb_MCF_uqDesPI11ZR * rtb_Subtract_e;
    SWC_MCF_IG_FQ_B.MCF_uqDes11ZR = rtb_MCF_uqDesPI11ZR * rtb_MCF_uAlCalc +
      rtb_MCF_ubBase * rtb_Subtract_e;
    VAR_MCF_UdDes11ZR_f32_FQ = SWC_MCF_IG_FQ_B.MCF_udDes11ZR;
  } else {
    VAR_MCF_UdDes11ZR_f32_FQ = 0.0F;
  }

  rtb_MCF_uAlCalc = MCF_udDes_FQ + VAR_MCF_UdDes11ZR_f32_FQ;
  SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_m0 = (1.0F - CAL_MCF_cofFltN_f32_FQ) *
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_m0 + *rtu_Rdc_nWoFlt *
    CAL_MCF_cofFltN_f32_FQ;
  rtb_MCF_uBCalc = SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_m0 * (real32_T)((uint8_T)
    MCF_GLB_MotorPole_u8_FQ) / MCF_GLB_Sixty_f32_FQ * (CAL_MCF_perCpnAg_f32_FQ *
    rtb_MCF_uBCalc) * MCF_GLB_CircAge_f32_FQ + VAR_MCF_agRtrEe_f32_FQ;
  rtb_MCF_uqDesPI11ZR = rtb_MCF_uBCalc - MCF_GLB_CircAge_f32_FQ;
  if (rtb_MCF_uqDesPI11ZR >= 0.0F) {
    rtb_MCF_uBCalc = rtb_MCF_uqDesPI11ZR;
  } else {
    if (!(rtb_MCF_uBCalc >= 0.0F)) {
      rtb_MCF_uBCalc += MCF_GLB_CircAge_f32_FQ;
    }
  }

  rtb_MCF_uBCalc = rtb_MCF_uBCalc * (real32_T)((uint16_T)
    MCF_GLB_DigtValue_u16_FQ) / MCF_GLB_CircAge_f32_FQ;
  if (rtb_MCF_uBCalc > 4095.0F) {
    rtb_MCF_uqDesPI11ZR = 4095.0F;
  } else if (rtb_MCF_uBCalc < 0.0F) {
    rtb_MCF_uqDesPI11ZR = 0.0F;
  } else {
    rtb_MCF_uqDesPI11ZR = rtb_MCF_uBCalc;
  }

  rtb_MCF_uqDesPI11ZR = rtCP_LookupCosTable_table_g[(int32_T)rtb_MCF_uqDesPI11ZR];
  if (CAL_MCF_flgUse1113ZR_b_FQ) {
    VAR_MCF_UqDes11ZR_f32_FQ = SWC_MCF_IG_FQ_B.MCF_uqDes11ZR;
  } else {
    VAR_MCF_UqDes11ZR_f32_FQ = 0.0F;
  }

  rtb_Subtract_e = MCF_uqDes_FQ + VAR_MCF_UqDes11ZR_f32_FQ;
  if (rtb_MCF_uBCalc > 4095.0F) {
    rtb_MCF_uBCalc = 4095.0F;
  } else {
    if (rtb_MCF_uBCalc < 0.0F) {
      rtb_MCF_uBCalc = 0.0F;
    }
  }

  rtb_MCF_uBCalc = rtCP_LookupSinTable_table_e[(int32_T)rtb_MCF_uBCalc];
  VAR_MCF_uAOfsClb_f32_FQ = rtb_MCF_uAlCalc * rtb_MCF_uqDesPI11ZR -
    rtb_Subtract_e * rtb_MCF_uBCalc;
  VAR_MCF_uBOfsClb_f32_FQ = rtb_Subtract_e * rtb_MCF_uqDesPI11ZR +
    rtb_MCF_uAlCalc * rtb_MCF_uBCalc;
  if (CAL_MCF_flgOverModu_b_FQ) {
    VAR_MCF_usPeak_f32_FQ = sqrtf(VAR_MCF_uAOfsClb_f32_FQ *
      VAR_MCF_uAOfsClb_f32_FQ + VAR_MCF_uBOfsClb_f32_FQ *
      VAR_MCF_uBOfsClb_f32_FQ);
    rtb_MCF_uAlCalc = MCF_uDcLnk_FQ / MCF_GLB_SqrtThree_f32_FQ *
      CAL_MCF_cofOverModu_f32_FQ;
    rtb_Switch2_g = (VAR_MCF_usPeak_f32_FQ <= rtb_MCF_uAlCalc);
    if (fabsf(VAR_MCF_uBOfsClb_f32_FQ) <= 0.0001F) {
      rtb_MCF_uqDesPI11ZR = 0.0001F;
    } else {
      rtb_MCF_uqDesPI11ZR = VAR_MCF_uBOfsClb_f32_FQ;
    }

    rtb_Gain3 = (uint8_T)((rtb_MCF_uqDesPI11ZR >= 0.0F) << 7);
    if (fabsf(VAR_MCF_uAOfsClb_f32_FQ) <= 0.0001F) {
      rtb_MCF_uBCalc = 0.0001F;
    } else {
      rtb_MCF_uBCalc = VAR_MCF_uAOfsClb_f32_FQ;
    }

    rtb_Gain1 = (uint8_T)((rtb_MCF_uBCalc >= 0.0F) << 7);
    rtb_MCF_uqDesPI11ZR /= rtb_MCF_uBCalc;
    rtb_MCF_uBCalc = fabsf(rtb_MCF_uqDesPI11ZR);
    rtb_Compare_ct = (rtb_MCF_uBCalc >= 1.0F);
    if (rtb_Compare_ct) {
      rtb_MCF_uBCalc = 1.0F / rtb_MCF_uBCalc;
    }

    switch ((int32_T)((((((uint32_T)rtb_Gain1 << 1) + rtb_Gain3) + ((uint32_T)
                (rtb_Compare_ct << 7) << 2)) >> 2) >> 5)) {
     case 0:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F + 180.0F;
      break;

     case 1:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = 180.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;

     case 2:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = 360.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;

     case 3:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F;
      break;

     case 4:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = 270.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;

     case 5:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F + 90.0F;
      break;

     case 6:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F + 270.0F;
      break;

     default:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uBCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uBCalc = 90.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;
    }

    VAR_MCF_AgRem_f32_FQ = rtb_MCF_uBCalc - (real32_T)(int32_T)fmodf((real32_T)
      (int32_T)floorf(rtb_MCF_uBCalc / 60.0F), 256.0F) * 60.0F;
    if (rtb_MCF_uAlCalc > 1000.0F) {
      rtb_MCF_uAlCalc = 1000.0F;
    } else {
      if (rtb_MCF_uAlCalc < 0.001F) {
        rtb_MCF_uAlCalc = 0.001F;
      }
    }

    MCF_VoltModuRate_FQ = VAR_MCF_usPeak_f32_FQ / rtb_MCF_uAlCalc;
    if (rtb_Switch2_g) {
      rtb_MCF_uBCalc = 1.0F;
    } else {
      rtb_MCF_uBCalc = look2_iflf_binlxpw(VAR_MCF_AgRem_f32_FQ * 1023.0F /
        MCF_GLB_Sixty_f32_FQ, MCF_VoltModuRate_FQ, rtCP_OmTable_bp01Data,
        rtCP_OmTable_bp02Data, rtCP_OmTable_tableData, rtCP_OmTable_maxIndex,
        1024U) * CAL_MCF_cofOverModu_f32_FQ;
    }

    VAR_MCF_uAOm_f32_FQ = VAR_MCF_uAOfsClb_f32_FQ * rtb_MCF_uBCalc;
    VAR_MCF_uBOm_f32_FQ = rtb_MCF_uBCalc * VAR_MCF_uBOfsClb_f32_FQ;
    rtb_Add_as = VAR_MCF_uBOm_f32_FQ;
  } else {
    rtb_Add_as = VAR_MCF_uBOfsClb_f32_FQ;
  }

  if (rtb_Saturation_o > CAL_MCF_SpdOffDeadCpn_f32_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_c = false;
  } else {
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_c = ((rtb_Saturation_o <=
      CAL_MCF_SpdOnDeadCpn_f32_FQ) || SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_c);
  }

  rtb_Subtract_e = fabsf(*rtu_TDC_trqDes_TDC_TrqDes);
  VAR_MCF_FlgDeadCpn_b_FQ = ((!(rtb_Subtract_e > CAL_MCF_TrqOffDeadCpn_f32_FQ)) &&
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_c && CAL_MCF_FlgUseDeadCpn_b_FQ &&
    (MCF_idDes_FQ <= 0.0F));
  if (VAR_MCF_FlgDeadCpn_b_FQ) {
    if (fabsf(MCF_iqDes_FQ) <= 0.0001F) {
      rtb_MCF_ubBase = 0.0001F;
    } else {
      rtb_MCF_ubBase = MCF_iqDes_FQ;
    }

    rtb_Gain3 = (uint8_T)((rtb_MCF_ubBase >= 0.0F) << 7);
    if (fabsf(MCF_idDes_FQ) <= 0.0001F) {
      rtb_MCF_uAlCalc = 0.0001F;
    } else {
      rtb_MCF_uAlCalc = MCF_idDes_FQ;
    }

    rtb_Gain1 = (uint8_T)((rtb_MCF_uAlCalc >= 0.0F) << 7);
    rtb_MCF_ubBase /= rtb_MCF_uAlCalc;
    rtb_MCF_uAlCalc = fabsf(rtb_MCF_ubBase);
    rtb_Switch2_g = (rtb_MCF_uAlCalc >= 1.0F);
    if (rtb_Switch2_g) {
      rtb_MCF_uAlCalc = 1.0F / rtb_MCF_uAlCalc;
    }

    switch ((int32_T)((((((uint32_T)rtb_Gain1 << 1) + rtb_Gain3) + ((uint32_T)
                (rtb_Switch2_g << 7) << 2)) >> 2) >> 5)) {
     case 0:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F + 180.0F;
      break;

     case 1:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = 180.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;

     case 2:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = 360.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;

     case 3:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F;
      break;

     case 4:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = 270.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;

     case 5:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F + 90.0F;
      break;

     case 6:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_MCF_uqDesPI11ZR]) * 1.49011612E-8F + 270.0F;
      break;

     default:
      rtb_MCF_uqDesPI11ZR = 1024.0F * rtb_MCF_uAlCalc;
      if (rtb_MCF_uqDesPI11ZR > 1024.0F) {
        rtb_MCF_uqDesPI11ZR = 1024.0F;
      }

      rtb_MCF_uAlCalc = 90.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_MCF_uqDesPI11ZR]) *
        1.49011612E-8F;
      break;
    }

    rtb_MCF_uAlCalc += VAR_MCF_agRtrEe_f32_FQ;
    rtb_MCF_uqDesPI11ZR = floorf(rtb_MCF_uAlCalc * 0.00277777785F);
    if (rtIsNaNF(rtb_MCF_uqDesPI11ZR) || rtIsInfF(rtb_MCF_uqDesPI11ZR)) {
      rtb_MCF_uqDesPI11ZR = 0.0F;
    } else {
      rtb_MCF_uqDesPI11ZR = fmodf(rtb_MCF_uqDesPI11ZR, 256.0F);
    }

    rtb_MCF_uAlCalc -= (real32_T)(rtb_MCF_uqDesPI11ZR < 0.0F ? (int32_T)(int8_T)
      -(int8_T)(uint8_T)-rtb_MCF_uqDesPI11ZR : (int32_T)(int8_T)(uint8_T)
      rtb_MCF_uqDesPI11ZR) * 360.0F;
    rtb_MCF_uBCalc = rtb_MCF_uAlCalc - CAL_MCF_AgDiffCurrSec_f32_FQ;
    if ((rtb_MCF_uBCalc > MCF_ANGLE_CURRENT_30_FQ) && (rtb_MCF_uBCalc <=
         MCF_ANGLE_CURRENT_90_FQ)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_2_FQ);
    } else if ((rtb_MCF_uBCalc > MCF_ANGLE_CURRENT_90_FQ) && (rtb_MCF_uBCalc <=
                MCF_ANGLE_CURRENT_150_FQ)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_3_FQ);
    } else if ((rtb_MCF_uBCalc > MCF_ANGLE_CURRENT_150_FQ) && (rtb_MCF_uBCalc <=
                MCF_ANGLE_CURRENT_210_FQ)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_4_FQ);
    } else if ((rtb_MCF_uBCalc > MCF_ANGLE_CURRENT_210_FQ) && (rtb_MCF_uBCalc <=
                MCF_ANGLE_CURRENT_270_FQ)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_5_FQ);
    } else if ((rtb_MCF_uBCalc > MCF_ANGLE_CURRENT_270_FQ) && (rtb_MCF_uBCalc <=
                MCF_ANGLE_CURRENT_330_FQ)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_6_FQ);
    } else {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_1_FQ);
    }

    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_MCF_ubBase = rtCP_DirectLookupTablenD_table[rtb_Gain1];
    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_Product9_i = rtCP_DirectLookupTablenD1_table[rtb_Gain1];
    rtb_MCF_UMin = (rtb_MCF_ubBase - rtb_Product9_i) * 0.5F;
    rtb_MCF_uBCalc = look1_iflf_binlcpw(rtb_Subtract_e, ((const real32_T *)
      &(CAL_MCF_AgRangeDeadCpnX_Trq_af32_FQ[0])), ((const real32_T *)
      &(CAL_MCF_AgRangeDeadCpnY_Ag_af32_FQ[0])), 6U);
    rtb_MCF_uqDesPI11ZR = floorf(rtb_MCF_uAlCalc * 0.0166666675F);
    if (rtIsNaNF(rtb_MCF_uqDesPI11ZR) || rtIsInfF(rtb_MCF_uqDesPI11ZR)) {
      rtb_MCF_uqDesPI11ZR = 0.0F;
    } else {
      rtb_MCF_uqDesPI11ZR = fmodf(rtb_MCF_uqDesPI11ZR, 256.0F);
    }

    rtb_MCF_uqDesPI11ZR = (rtb_MCF_uAlCalc - (real32_T)(rtb_MCF_uqDesPI11ZR <
      0.0F ? (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_MCF_uqDesPI11ZR : (int32_T)
      (int8_T)(uint8_T)rtb_MCF_uqDesPI11ZR) * 60.0F) - 30.0F;
    if (rtb_MCF_uqDesPI11ZR < 0.0F) {
      rtb_MCF_uAlCalc = fabsf(rtb_MCF_uqDesPI11ZR);
      if (rtb_MCF_uAlCalc < rtb_MCF_uBCalc) {
        rtb_MCF_uAlCalc = rtb_MCF_ubBase - (1.0F - rtb_MCF_uAlCalc /
          rtb_MCF_uBCalc) * rtb_MCF_UMin;
      } else {
        rtb_MCF_uAlCalc = rtb_MCF_ubBase;
      }
    } else if (rtb_MCF_uqDesPI11ZR < rtb_MCF_uBCalc) {
      rtb_MCF_uAlCalc = (1.0F - rtb_MCF_uqDesPI11ZR / rtb_MCF_uBCalc) *
        rtb_MCF_UMin + rtb_Product9_i;
    } else {
      rtb_MCF_uAlCalc = rtb_Product9_i;
    }

    rtb_MCF_ubBase = CAL_MCF_DeadTimeCpn_f32_FQ * 1.0E-6F / MCF_dtPwm_FQ *
      MCF_uDcLnk_FQ;
    SWC_MCF_IG_FQ_B.MCF_uAlphaDeadCpn = rtb_MCF_uAlCalc * rtb_MCF_ubBase;
    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_MCF_UMin = rtCP_DirectLookupTablenD2_table[rtb_Gain1];
    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_MCF_uAlCalc = rtCP_DirectLookupTablenD3_table[rtb_Gain1];
    rtb_Product9_i = (rtb_MCF_UMin - rtb_MCF_uAlCalc) * 0.5F;
    if (rtb_MCF_uqDesPI11ZR < 0.0F) {
      rtb_MCF_uAlCalc = fabsf(rtb_MCF_uqDesPI11ZR);
      if (rtb_MCF_uAlCalc < rtb_MCF_uBCalc) {
        rtb_MCF_uAlCalc = rtb_MCF_UMin - (1.0F - rtb_MCF_uAlCalc /
          rtb_MCF_uBCalc) * rtb_Product9_i;
      } else {
        rtb_MCF_uAlCalc = rtb_MCF_UMin;
      }
    } else {
      if (rtb_MCF_uqDesPI11ZR < rtb_MCF_uBCalc) {
        rtb_MCF_uAlCalc += (1.0F - rtb_MCF_uqDesPI11ZR / rtb_MCF_uBCalc) *
          rtb_Product9_i;
      }
    }

    SWC_MCF_IG_FQ_B.MCF_uBetaDeadCpn = rtb_MCF_uAlCalc * rtb_MCF_ubBase;
    VAR_MCF_uBetaDeadCpn_f32_FQ = SWC_MCF_IG_FQ_B.MCF_uBetaDeadCpn;
  } else {
    VAR_MCF_uBetaDeadCpn_f32_FQ = 0.0F;
  }

  rtb_MCF_uBCalc = rtb_Add_as + VAR_MCF_uBetaDeadCpn_f32_FQ;
  if (CAL_MCF_flgOverModu_b_FQ) {
    rtb_MCF_UMin = VAR_MCF_uAOm_f32_FQ;
  } else {
    rtb_MCF_UMin = VAR_MCF_uAOfsClb_f32_FQ;
  }

  if (VAR_MCF_FlgDeadCpn_b_FQ) {
    VAR_MCF_uAlphaDeadCpn_f32_FQ = SWC_MCF_IG_FQ_B.MCF_uAlphaDeadCpn;
  } else {
    VAR_MCF_uAlphaDeadCpn_f32_FQ = 0.0F;
  }

  rtb_MCF_uAlCalc = rtb_MCF_UMin + VAR_MCF_uAlphaDeadCpn_f32_FQ;
  if (CAL_MCF_FlgUpdateDyc_b_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay_1_DSTATE = CAL_MCF_DycUSet_f32_FQ;
  }

  if (rtb_Saturation_o >= CAL_MCF_nDpwmOff_f32_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_hv = false;
  } else {
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_hv = ((rtb_Saturation_o <=
      CAL_MCF_nDpwmOffDelay_f32_FQ) || SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_hv);
  }

  rtb_MCF_ubBase = MCF_uDcLnk_FQ * MCF_GLB_OneHalf_f32_FQ;
  if (rtb_MCF_ubBase > 700.0F) {
    rtb_MCF_ubBase = 700.0F;
  } else {
    if (rtb_MCF_ubBase < 0.0001F) {
      rtb_MCF_ubBase = 0.0001F;
    }
  }

  rtb_MCF_uqDesPI11ZR = rtb_MCF_UMin / rtb_MCF_ubBase;
  rtb_Product9_i = rtb_MCF_uqDesPI11ZR * MCF_dtPwm_FQ * -0.25F;
  rtb_MCF_UMin *= MCF_GLB_OneHalf_f32_FQ;
  rtb_Add_as *= 0.866F;
  rtb_Saturation_o = ((0.0F - rtb_MCF_UMin) - rtb_Add_as) / rtb_MCF_ubBase;
  rtb_MCF_ubBase = (rtb_Add_as - rtb_MCF_UMin) / rtb_MCF_ubBase;
  if (rtb_MCF_uqDesPI11ZR >= rtb_MCF_ubBase) {
    rtb_Add_as = rtb_MCF_uqDesPI11ZR;
  } else {
    rtb_Add_as = rtb_MCF_ubBase;
  }

  if (!(rtb_Add_as >= rtb_Saturation_o)) {
    rtb_Add_as = rtb_Saturation_o;
  }

  if (rtb_MCF_uqDesPI11ZR <= rtb_MCF_ubBase) {
    rtb_MCF_UMin = rtb_MCF_uqDesPI11ZR;
  } else {
    rtb_MCF_UMin = rtb_MCF_ubBase;
  }

  if (!(rtb_MCF_UMin <= rtb_Saturation_o)) {
    rtb_MCF_UMin = rtb_Saturation_o;
  }

  switch (CAL_MCF_stDpwm_u8_FQ) {
   case 1:
    rtb_MCF_uqDesPI11ZR = MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
      MCF_GLB_OneHalf_f32_FQ;
    break;

   case 2:
    rtb_MCF_uqDesPI11ZR = ((rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ
      * MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ) +
      rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
      MCF_GLB_OneHalf_f32_FQ) * MCF_GLB_OneHalf_f32_FQ;
    break;

   case 3:
    if (((!(rtb_MCF_uqDesPI11ZR > rtb_MCF_ubBase)) || (!(rtb_MCF_ubBase >
           rtb_Saturation_o))) && ((!(rtb_MCF_ubBase > rtb_Saturation_o)) ||
         (!(rtb_Saturation_o > rtb_MCF_uqDesPI11ZR))) && ((!(rtb_Saturation_o >
           rtb_MCF_uqDesPI11ZR)) || (!(rtb_MCF_uqDesPI11ZR > rtb_MCF_ubBase))))
    {
      rtb_MCF_uqDesPI11ZR = rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
        MCF_GLB_OneHalf_f32_FQ;
    } else {
      rtb_MCF_uqDesPI11ZR = rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ
        * MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ;
    }
    break;

   case 4:
    if (((rtb_MCF_uqDesPI11ZR > rtb_MCF_ubBase) && (rtb_MCF_ubBase >
          rtb_Saturation_o)) || ((rtb_MCF_ubBase > rtb_Saturation_o) &&
         (rtb_Saturation_o > rtb_MCF_uqDesPI11ZR)) || ((rtb_Saturation_o >
          rtb_MCF_uqDesPI11ZR) && (rtb_MCF_uqDesPI11ZR > rtb_MCF_ubBase))) {
      rtb_MCF_uqDesPI11ZR = rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
        MCF_GLB_OneHalf_f32_FQ;
    } else {
      rtb_MCF_uqDesPI11ZR = rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ
        * MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ;
    }
    break;

   case 5:
    if (rtb_Add_as * MCF_GLB_OneHalf_f32_FQ + rtb_MCF_UMin *
        MCF_GLB_OneHalf_f32_FQ >= 0.0F) {
      rtb_MCF_uqDesPI11ZR = rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
        MCF_GLB_OneHalf_f32_FQ;
    } else {
      rtb_MCF_uqDesPI11ZR = rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ
        * MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ;
    }
    break;

   case 6:
    if (rtb_Add_as * MCF_GLB_OneHalf_f32_FQ + rtb_MCF_UMin *
        MCF_GLB_OneHalf_f32_FQ < 0.0F) {
      rtb_MCF_uqDesPI11ZR = rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
        MCF_GLB_OneHalf_f32_FQ;
    } else {
      rtb_MCF_uqDesPI11ZR = rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ
        * MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ;
    }
    break;

   case 7:
    rtb_MCF_uqDesPI11ZR = rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
      MCF_GLB_OneHalf_f32_FQ;
    break;

   case 8:
    rtb_MCF_uqDesPI11ZR = rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
      MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ;
    break;

   default:
    rtb_MCF_uqDesPI11ZR = ((rtb_MCF_UMin * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ
      * MCF_GLB_OneHalf_f32_FQ + MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ) +
      rtb_Add_as * MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ *
      MCF_GLB_OneHalf_f32_FQ) * MCF_GLB_OneHalf_f32_FQ;
    break;
  }

  rtb_MCF_UMin = (rtb_Product9_i + rtb_MCF_uqDesPI11ZR) * 2.0F;
  rtb_MCF_ubBase = (rtb_MCF_ubBase * MCF_dtPwm_FQ * -0.25F + rtb_MCF_uqDesPI11ZR)
    * 2.0F;
  rtb_Product9_i = (rtb_Saturation_o * MCF_dtPwm_FQ * -0.25F +
                    rtb_MCF_uqDesPI11ZR) * 2.0F;
  rtb_MCF_ratTbSv = rtb_MCF_uAlCalc * 0.866F;
  rtb_MCF_ratTaSv = rtb_MCF_uBCalc * MCF_GLB_OneHalf_f32_FQ;
  rtb_Gain3 = (uint8_T)(((uint32_T)((rtb_MCF_ratTbSv - rtb_MCF_ratTaSv > 0.0F) <<
    1) + (rtb_MCF_uBCalc > 0.0F)) + (((0.0F - rtb_MCF_ratTbSv) - rtb_MCF_ratTaSv
    > 0.0F) << 2));
  if (rtb_Gain3 > 6) {
    rtb_Gain3 = 6U;
  } else {
    if (rtb_Gain3 < 1) {
      rtb_Gain3 = 1U;
    }
  }

  if (MCF_uDcLnk_FQ > 1000.0F) {
    rtb_MCF_uqDesPI11ZR = 1000.0F;
  } else if (MCF_uDcLnk_FQ < 0.0001F) {
    rtb_MCF_uqDesPI11ZR = 0.0001F;
  } else {
    rtb_MCF_uqDesPI11ZR = MCF_uDcLnk_FQ;
  }

  if (rtb_MCF_frqPwmCalc_j + 1.0F < 0.0001F) {
    rtb_Saturation_o = 0.0001F;
  } else {
    rtb_Saturation_o = rtb_MCF_frqPwmCalc_j + 1.0F;
  }

  rtb_Add_as = MCF_dtPwm_FQ / rtb_MCF_uqDesPI11ZR * MCF_GLB_SqrtThree_f32_FQ *
    look1_iflf_binlxpw(1.0F / rtb_Saturation_o * 1.1547F, ((const real32_T *)
    &(CAL_MCF_FfcTx_af32_FQ[0])), ((const real32_T *)&(CAL_MCF_FfcTy_af32_FQ[0])),
                       10U);
  switch (rtb_Gain3) {
   case 1:
    rtb_Saturation_o = (rtb_MCF_ratTaSv - rtb_MCF_ratTbSv) * rtb_Add_as;
    rtb_MCF_uqDesPI11ZR = (rtb_MCF_ratTaSv + rtb_MCF_ratTbSv) * rtb_Add_as;
    break;

   case 2:
    rtb_Saturation_o = (rtb_MCF_ratTaSv + rtb_MCF_ratTbSv) * rtb_Add_as;
    rtb_MCF_uqDesPI11ZR = -(rtb_MCF_uBCalc * rtb_Add_as);
    break;

   case 3:
    rtb_Saturation_o = -((rtb_MCF_ratTaSv - rtb_MCF_ratTbSv) * rtb_Add_as);
    rtb_MCF_uqDesPI11ZR = rtb_MCF_uBCalc * rtb_Add_as;
    break;

   case 4:
    rtb_Saturation_o = -(rtb_MCF_uBCalc * rtb_Add_as);
    rtb_MCF_uqDesPI11ZR = (rtb_MCF_ratTaSv - rtb_MCF_ratTbSv) * rtb_Add_as;
    break;

   case 5:
    rtb_Saturation_o = rtb_MCF_uBCalc * rtb_Add_as;
    rtb_MCF_uqDesPI11ZR = -((rtb_MCF_ratTaSv + rtb_MCF_ratTbSv) * rtb_Add_as);
    break;

   default:
    SWC_MCF_IG_FQ_Osc_nrN6((rtb_MCF_ratTaSv + rtb_MCF_ratTbSv) * rtb_Add_as,
      (rtb_MCF_ratTaSv - rtb_MCF_ratTbSv) * rtb_Add_as, &rtb_Saturation_o,
      &rtb_MCF_uqDesPI11ZR);
    break;
  }

  rtb_Add_as = (MCF_dtPwm_FQ * MCF_GLB_OneHalf_f32_FQ + MCF_GLB_OneHalf_f32_FQ *
                rtb_Saturation_o) + MCF_GLB_OneHalf_f32_FQ * rtb_MCF_uqDesPI11ZR;
  rtb_Saturation_o = rtb_Add_as - rtb_Saturation_o;
  switch (rtb_Gain3) {
   case 1:
    rtb_MCF_ratTaSv = rtb_Saturation_o;
    rtb_MCF_ratTbSv = rtb_Add_as;
    rtb_Add_as = rtb_Saturation_o - rtb_MCF_uqDesPI11ZR;
    break;

   case 2:
    rtb_MCF_ratTaSv = rtb_Add_as;
    rtb_MCF_ratTbSv = rtb_Saturation_o - rtb_MCF_uqDesPI11ZR;
    rtb_Add_as = rtb_Saturation_o;
    break;

   case 3:
    rtb_MCF_ratTaSv = rtb_Add_as;
    rtb_MCF_ratTbSv = rtb_Saturation_o;
    rtb_Add_as = rtb_Saturation_o - rtb_MCF_uqDesPI11ZR;
    break;

   case 4:
    rtb_MCF_ratTaSv = rtb_Saturation_o - rtb_MCF_uqDesPI11ZR;
    rtb_MCF_ratTbSv = rtb_Saturation_o;
    break;

   case 5:
    rtb_MCF_ratTaSv = rtb_Saturation_o - rtb_MCF_uqDesPI11ZR;
    rtb_MCF_ratTbSv = rtb_Add_as;
    rtb_Add_as = rtb_Saturation_o;
    break;

   default:
    rtb_MCF_ratTaSv = rtb_Saturation_o;
    rtb_MCF_ratTbSv = rtb_Saturation_o - rtb_MCF_uqDesPI11ZR;
    break;
  }

  if ((rtb_Subtract_e <= CAL_MCF_trqDpwmOff_f32_FQ) &&
      SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_hv && CAL_MCF_flgDpwm_b_FQ) {
    rtb_MCF_ratTaSv = MCF_dtPwm_FQ - rtb_MCF_UMin;
    rtb_MCF_ratTbSv = MCF_dtPwm_FQ - rtb_MCF_ubBase;
    rtb_Add_as = MCF_dtPwm_FQ - rtb_Product9_i;
  }

  if (rtb_MCF_ratTaSv >= rtb_MCF_ratTbSv) {
    rtb_Saturation_o = rtb_MCF_ratTaSv;
  } else {
    rtb_Saturation_o = rtb_MCF_ratTbSv;
  }

  if (!(rtb_Saturation_o >= rtb_Add_as)) {
    rtb_Saturation_o = rtb_Add_as;
  }

  rtb_Saturation_o = MCF_dtPwm_FQ - rtb_Saturation_o;
  rtb_MCF_uqDesPI11ZR = rtb_MCF_ratTaSv + rtb_Saturation_o;
  rtb_Subtract_e = rtb_MCF_ratTbSv + rtb_Saturation_o;
  rtb_MCF_ubBase = rtb_Add_as + rtb_Saturation_o;
  rtb_Saturation_o = MCF_dtPwm_FQ - CAL_MCF_ratNarrWave_f32_FQ * 1.0E-6F;
  if (CAL_MCF_flgNWS_b_FQ && ((rtb_MCF_ratTaSv >= rtb_Saturation_o) ||
       (rtb_MCF_ratTbSv >= rtb_Saturation_o) || (rtb_Add_as >= rtb_Saturation_o)))
  {
    rtb_MCF_ratTaSv = rtb_MCF_uqDesPI11ZR;
    rtb_MCF_ratTbSv = rtb_Subtract_e;
    rtb_Add_as = rtb_MCF_ubBase;
  }

  if (CAL_MCF_FlgUseSetDyc_b_FQ) {
    rtb_Saturation_o = SWC_MCF_IG_FQ_DW.UnitDelay_1_DSTATE;
  } else {
    rtb_Saturation_o = rtb_MCF_ratTaSv / MCF_dtPwm_FQ;
  }

  if (rtb_Saturation_o > CAL_MCF_ratUp_f32_FQ) {
    rtb_Saturation_o = CAL_MCF_ratUp_f32_FQ;
  }

  if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
    MCF_dycW_FQ = rtb_Saturation_o;
  } else {
    MCF_dycW_FQ = CAL_MCF_ratLo_f32_FQ;
  }

  if (CAL_MCF_FlgUpdateDyc_b_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay_2_DSTATE = CAL_MCF_DycVSet_f32_FQ;
  }

  if (CAL_MCF_FlgUseSetDyc_b_FQ) {
    rtb_Saturation_o = SWC_MCF_IG_FQ_DW.UnitDelay_2_DSTATE;
  } else {
    rtb_Saturation_o = rtb_MCF_ratTbSv / MCF_dtPwm_FQ;
  }

  if (rtb_Saturation_o > CAL_MCF_ratUp_f32_FQ) {
    rtb_Saturation_o = CAL_MCF_ratUp_f32_FQ;
  }

  if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
    rtb_MCF_uqDesPI11ZR = rtb_Saturation_o;
  } else {
    rtb_MCF_uqDesPI11ZR = CAL_MCF_ratLo_f32_FQ;
  }

  if (CAL_MCF_FlgUpdateDyc_b_FQ) {
    SWC_MCF_IG_FQ_DW.UnitDelay_3_DSTATE = CAL_MCF_DycWSet_f32_FQ;
  }

  if (CAL_MCF_FlgUseSetDyc_b_FQ) {
    rtb_Saturation_o = SWC_MCF_IG_FQ_DW.UnitDelay_3_DSTATE;
  } else {
    rtb_Saturation_o = rtb_Add_as / MCF_dtPwm_FQ;
  }

  if (rtb_Saturation_o > CAL_MCF_ratUp_f32_FQ) {
    rtb_Saturation_o = CAL_MCF_ratUp_f32_FQ;
  }

  switch (CAL_MCF_stChangePha_u8_FQ) {
   case 1:
    MCF_dycU_FQ = MCF_dycW_FQ;
    MCF_dycV_FQ = rtb_MCF_uqDesPI11ZR;
    if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
      MCF_dycW_FQ = rtb_Saturation_o;
    } else {
      MCF_dycW_FQ = CAL_MCF_ratLo_f32_FQ;
    }
    break;

   case 2:
    MCF_dycU_FQ = MCF_dycW_FQ;
    if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
      MCF_dycV_FQ = rtb_Saturation_o;
    } else {
      MCF_dycV_FQ = CAL_MCF_ratLo_f32_FQ;
    }

    MCF_dycW_FQ = rtb_MCF_uqDesPI11ZR;
    break;

   case 3:
    MCF_dycU_FQ = rtb_MCF_uqDesPI11ZR;
    MCF_dycV_FQ = MCF_dycW_FQ;
    if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
      MCF_dycW_FQ = rtb_Saturation_o;
    } else {
      MCF_dycW_FQ = CAL_MCF_ratLo_f32_FQ;
    }
    break;

   case 4:
    MCF_dycU_FQ = rtb_MCF_uqDesPI11ZR;
    if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
      MCF_dycV_FQ = rtb_Saturation_o;
    } else {
      MCF_dycV_FQ = CAL_MCF_ratLo_f32_FQ;
    }
    break;

   case 5:
    if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
      MCF_dycU_FQ = rtb_Saturation_o;
    } else {
      MCF_dycU_FQ = CAL_MCF_ratLo_f32_FQ;
    }

    MCF_dycV_FQ = MCF_dycW_FQ;
    MCF_dycW_FQ = rtb_MCF_uqDesPI11ZR;
    break;

   default:
    if (rtb_Saturation_o > CAL_MCF_ratLo_f32_FQ) {
      MCF_dycU_FQ = rtb_Saturation_o;
    } else {
      MCF_dycU_FQ = CAL_MCF_ratLo_f32_FQ;
    }

    MCF_dycV_FQ = rtb_MCF_uqDesPI11ZR;
    break;
  }

  switch (rtb_Gain3) {
   case 1:
    MCF_SecVolt_FQ = 2U;
    break;

   case 2:
    MCF_SecVolt_FQ = 6U;
    break;

   case 3:
    MCF_SecVolt_FQ = 1U;
    break;

   case 4:
    MCF_SecVolt_FQ = 4U;
    break;

   case 5:
    MCF_SecVolt_FQ = 3U;
    break;

   default:
    MCF_SecVolt_FQ = 5U;
    break;
  }

  MCF_tiLock_FQ = look1_iflf_binlcpw(MCF_frqPwm_FQ, ((const real32_T *)
    &(CAL_MCF_DeadTimeTableX_Frq_af32_FQ[0])), ((const real32_T *)
    &(CAL_MCF_DeadTimeTableY_Ti_af32_FQ[0])), 14U);
  if (CAL_MCF_FlgUseSetDyc_b_FQ) {
    MCF_stpwmMode_FQ = CAL_MCF_stPwmMode_u8_FQ;
  } else {
    MCF_stpwmMode_FQ = *rtu_SCF_BUS_SCF_stPwmMode;
  }

  VAR_MCF_Is_f32_FQ = sqrtf(rtb_MCF_ialpha * rtb_MCF_ialpha + rtb_MCF_ibeta *
    rtb_MCF_ibeta);
  MCF_Is_FQ = VAR_MCF_Is_f32_FQ;
  *rty_MCF_BUS_MCF_idDes = MCF_udDes_FQ;
  *rty_MCF_BUS_MCF_cofFrqPwm = MCF_cofFrqPwm_FQ;
  *rty_MCF_BUS_MCF_dtPwm = MCF_dtPwm_FQ;
  *rty_MCF_BUS_MCF_tiLock = MCF_tiLock_FQ;
  *rty_MCF_BUS_MCF_stpwmMode = MCF_stpwmMode_FQ;
  *rty_MCF_BUS_MCF_Is = MCF_Is_FQ;
  *rty_MCF_BUS_MCF_idAct = MCF_idAct_FQ;
  *rty_MCF_BUS_MCF_iqAct = MCF_iqAct_FQ;
  *rty_MCF_BUS_MCF_uDcLnk = MCF_uDcLnk_FQ;
  *rty_MCF_BUS_MCF_iU = MCF_iU_FQ;
  *rty_MCF_BUS_MCF_iV = MCF_iV_FQ;
  *rty_MCF_BUS_MCF_iqDes = MCF_uqDes_FQ;
  *rty_MCF_BUS_MCF_iW = MCF_iW_FQ;
  *rty_MCF_BUS_MCF_VoltModuRate = MCF_VoltModuRate_FQ;
  *rty_MCF_BUS_MCF_ialpha = rtb_MCF_ialpha;
  *rty_MCF_BUS_MCF_ibeta = rtb_MCF_ibeta;
  *rty_MCF_BUS_MCF_uAlCalc = rtb_MCF_uAlCalc;
  *rty_MCF_BUS_MCF_uBCalc = rtb_MCF_uBCalc;
  *rty_MCF_BUS_MCF_udDes = MCF_idDes_FQ;
  *rty_MCF_BUS_MCF_uqDes = MCF_iqDes_FQ;
  *rty_MCF_BUS_MCF_dycU = MCF_dycU_FQ;
  *rty_MCF_BUS_MCF_dycV = MCF_dycV_FQ;
  *rty_MCF_BUS_MCF_dycW = MCF_dycW_FQ;
  *rty_MCF_BUS_MCF_SecVolt = MCF_SecVolt_FQ;
  *rty_MCF_BUS_MCF_frqPwm = MCF_frqPwm_FQ;
  rtb_MCF_uqDesPI11ZR = sqrtf(MCF_udDes_FQ * MCF_udDes_FQ + MCF_uqDes_FQ *
    MCF_uqDes_FQ);
  if (rtb_MCF_uqDesPI11ZR > 1023.0F) {
    rtb_MCF_uqDesPI11ZR = 1023.0F;
  } else {
    if (rtb_MCF_uqDesPI11ZR < 0.01F) {
      rtb_MCF_uqDesPI11ZR = 0.01F;
    }
  }

  VAR_MCF_UsUseRateReal_f32_FQ = rtb_Subtract2_l / rtb_MCF_uqDesPI11ZR - 1.0F;
  SWC_MCF_IG_FQ_DW.Delay1_DSTATE = rtb_Product11 - VAR_MCF_uqDes_f32_FQ;
  SWC_MCF_IG_FQ_DW.Delay_DSTATE = rtb_Subtract1_f - VAR_MCF_udDes_f32_FQ;
  SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_e = (1.0F - CAL_MCF_cofFltPowerHeat_f32_FQ) *
    SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_e + VAR_MCF_PowerMotHeat_f32_FQ *
    CAL_MCF_cofFltPowerHeat_f32_FQ;
  if ((SWC_MCF_IG_FQ_B.uDLookupTable < 100.0F) && (!VAR_MCF_flgMotHeat_b_FQ)) {
    VAR_MCF_TMAhtChsts_f32_FQ = CAL_MCF_Part_ActiveHeat_u8_FQ;
  } else if (VAR_MCF_flgMotHeat_b_FQ && (VAR_MCF_PCUHeaterPower_f32_FQ -
              SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_e <= CAL_MCF_DeltaPower_f32_FQ))
  {
    VAR_MCF_TMAhtChsts_f32_FQ = CAL_MCF_ActiveHeatNormal_u8_FQ;
  } else {
    VAR_MCF_TMAhtChsts_f32_FQ = CAL_MCF_ActiveHeatInit_u8_FQ;
  }

  VAR_MCF_flgFw_b_FQ = (rtb_MCF_frqPwmCalc_j - VAR_MCF_UsUseRateDes_f32_FQ <=
                        0.0F);
  SWC_MCF_IG_FQ_DW.Delay2_DSTATE = rtb_Product2;
  SWC_MCF_IG_FQ_DW.UnitDelay_DSTATE_i = VAR_MCF_flgMotHeat_b_FQ;
}

void SWC_MCF_IG_FQ_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_MCF_IG_FQ_T *const SWC_MCF_IG_FQ_M = &(SWC_MCF_IG_FQ_MdlrefDW.rtm);
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetErrorStatusPointer(SWC_MCF_IG_FQ_M, rt_errorStatus);
}
