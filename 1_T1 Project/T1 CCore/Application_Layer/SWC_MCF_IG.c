#include "SWC_MCF_IG.h"
#include "SWC_MCF_IG_private.h"
#include "look1_iflf_binlcapw.h"
#include "look1_iflf_binlcpw.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlxpw.h"

#define FAW_CORE0_DMEM0_VALUE_START
#include "FAW_MemMap.h"
real32_T MCF_frqPwm;
real32_T MCF_cofFrqPwm;
real32_T VAR_MCF_uDcLnk_f32;
real32_T MCF_uDcLnk;
real32_T VAR_MCF_iU_NC_f32;
real32_T VAR_MCF_iV_NC_f32;
real32_T VAR_MCF_iW_NC_f32;
real32_T VAR_MCF_iU_f32;
real32_T MCF_iU;
real32_T VAR_MCF_iV_f32;
real32_T MCF_iV;
real32_T VAR_MCF_iW_f32;
real32_T MCF_iW;
real32_T VAR_MCF_agOffset_f32;
real32_T VAR_MCF_agRtrEe_f32;
real32_T VAR_MCF_idAct_f32;
real32_T MCF_idAct;
real32_T VAR_MCF_periodCalc_f32;
real32_T VAR_MCF_UsUseRateDes_f32;
real32_T VAR_MCF_isdFW_f32;
real32_T VAR_MCF_idMotHeat_f32;
real32_T VAR_MCF_idDes_f32;
real32_T MCF_idDes;
real32_T VAR_MCF_MPC_LdSubLq_f32;
real32_T VAR_MCF_iqDes_f32;
real32_T MCF_iqDes;
real32_T VAR_MCF_iqAct_f32;
real32_T MCF_iqAct;
real32_T VAR_MCF_udRv_f32;
real32_T VAR_MCF_MPC_Ld_f32;
real32_T VAR_MCF_Rdc_nWoFlt_f32;
real32_T VAR_MCF_MPC_Lq_f32;
real32_T VAR_MCF_EmfBack_f32;
real32_T VAR_MCF_uqRv_f32;
real32_T VAR_MCF_udDes_f32;
real32_T MCF_udDes;
real32_T VAR_MCF_uqDes_f32;
real32_T MCF_uqDes;
real32_T MCF_dtPwm;
real32_T VAR_MCF_UdDes11ZR_f32;
real32_T VAR_MCF_UqDes11ZR_f32;
real32_T VAR_MCF_uAOfsClb_f32;
real32_T VAR_MCF_uBOfsClb_f32;
real32_T VAR_MCF_uBetaDeadCpn_f32;
real32_T VAR_MCF_uAlphaDeadCpn_f32;
real32_T MCF_dycU;
real32_T MCF_dycV;
real32_T MCF_dycW;
real32_T MCF_tiLock;
real32_T VAR_MCF_Is_f32;
real32_T MCF_Is;
real32_T VAR_MCF_UsUseRateReal_f32;
real32_T VAR_MCF_usPeak_f32;
real32_T VAR_MCF_AgRem_f32;
real32_T MCF_VoltModuRate;
real32_T VAR_MCF_uAOm_f32;
real32_T VAR_MCF_uBOm_f32;
real32_T VAR_MCF_IsSet11ZR_f32;
real32_T VAR_MCF_IsThetaSet11ZR_f32;
real32_T VAR_MCF_PCUHeaterPower_f32;
real32_T VAR_MCF_PowerDcLnk_f32;
real32_T VAR_MCF_PowerMech_f32;
real32_T VAR_MCF_PowerMotHeat_f32;
uint8_T VAR_MCF_HSPF_stIphaOffCal_u8;
uint8_T MCF_SecVolt;
uint8_T MCF_stpwmMode;
uint8_T VAR_MCF_TMAhtChsts_f32;
boolean_T VAR_MCF_flgMotHeat_b;
boolean_T VAR_MCF_SCF_flgInitEn_b;
boolean_T VAR_MCF_FlgDeadCpn_b;
boolean_T VAR_MCF_flgFw_b;
MdlrefDW_SWC_MCF_IG_T SWC_MCF_IG_MdlrefDW;
B_SWC_MCF_IG_c_T SWC_MCF_IG_B;
DW_SWC_MCF_IG_f_T SWC_MCF_IG_DW;
#define FAW_CORE0_DMEM0_VALUE_STOP
#include "FAW_MemMap.h"

void SWC_MCF_IG_Osc_nrN6(real32_T rtu_MCF_tiY, real32_T rtu_MCF_tiZ, real32_T
  *rty_MCF_tiYout, real32_T *rty_MCF_tiZout)
{
  *rty_MCF_tiYout = -rtu_MCF_tiY;
  *rty_MCF_tiZout = -rtu_MCF_tiZ;
}


#define FAW_CORE0_DMEM0_VALUE_START
#include "FAW_MemMap.h"
void SWC_MCF_IG(const real32_T *rtu_HSPF_BUS_HSPF_iPhaUOffset, const real32_T
                *rtu_HSPF_BUS_HSPF_iPhaVOffset, const real32_T
                *rtu_HSPF_BUS_HSPF_iPhaWOffset, const uint8_T
                *rtu_HSPF_BUS_HSPF_stIphaOffCal, const real32_T
                *rtu_HSPF_BUS_HSPF_tStrrTempFlt, const real32_T
                *rtu_MPC_BUS_MPC_LdSubLq, const real32_T *rtu_MPC_BUS_MPC_Ld,
                const real32_T *rtu_MPC_BUS_MPC_Lq, const real32_T
                *rtu_MPC_BUS_MPC_Rs, const real32_T *rtu_MPC_BUS_MPC_TrqMechFlt,
                const real32_T *rtu_MPC_BUS_MPC_psiExc, const real32_T
                *rtu_MPC_BUS_MPC_isdMTPA, const real32_T *rtu_MPC_BUS_MPC_isdFF,
                const real32_T *rtu_MPC_BUS_MPC_isdMTPV, const real32_T
                *rtu_MPC_BUS_MPC_OmBw, const real32_T *rtu_MPC_BUS_MPC_Rv, const
                real32_T *rtu_MPC_BUS_MPC_frqPwmVF, const real32_T
                *rtu_MPC_BUS_MPC_CofRandomPwm, const real32_T
                *rtu_TDC_BUS_TDC_TrqDes, const real32_T
                *rtu_BCC_BUS_BCC_iDcLnkEst, const real32_T *rtu_RDC_agRtrEe,
                const uint16_T *rtu_CDD_iUNoOff, const uint16_T *rtu_CDD_iVNoOf,
                const uint16_T *rtu_CDD_iWNoOf, const real32_T *rtu_CDD_uDcLnk,
                const real32_T *rtu_Rdc_nWoFlt, const boolean_T
                *rtu_SCF_BUS_SCF_flginitPI, const boolean_T
                *rtu_SCF_BUS_SCF_flgEnDchaToMc, const uint8_T
                *rtu_SCF_BUS_SCF_stPwmMode, real32_T *rty_MCF_BUS_MCF_idDes,
                real32_T *rty_MCF_BUS_MCF_iqDes, real32_T *rty_MCF_BUS_MCF_udDes,
                real32_T *rty_MCF_BUS_MCF_uqDes, real32_T *rty_MCF_BUS_MCF_dycU,
                real32_T *rty_MCF_BUS_MCF_dycV, real32_T *rty_MCF_BUS_MCF_dycW,
                uint8_T *rty_MCF_BUS_MCF_SecVolt, real32_T
                *rty_MCF_BUS_MCF_frqPwm, real32_T *rty_MCF_BUS_MCF_cofFrqPwm,
                real32_T *rty_MCF_BUS_MCF_dtPwm, real32_T
                *rty_MCF_BUS_MCF_tiLock, uint8_T *rty_MCF_BUS_MCF_stpwmMode,
                real32_T *rty_MCF_BUS_MCF_Is, real32_T *rty_MCF_BUS_MCF_idAct,
                real32_T *rty_MCF_BUS_MCF_iqAct, real32_T
                *rty_MCF_BUS_MCF_uDcLnk, real32_T *rty_MCF_BUS_MCF_iU, real32_T *
                rty_MCF_BUS_MCF_iV, real32_T *rty_MCF_BUS_MCF_iW, real32_T
                *rty_MCF_BUS_MCF_VoltModuRate)
{
  int32_T rtb_MCF_isqDesCalc_0;
  real32_T rtb_Add_as;
  real32_T rtb_DirectLookupTablenD1;
  real32_T rtb_Divide2;
  real32_T rtb_MCF_DeadVoltage;
  real32_T rtb_MCF_UMin;
  real32_T rtb_MCF_coefAlphaErr;
  real32_T rtb_MCF_frqPwmCalc_j;
  real32_T rtb_MCF_ialpha;
  real32_T rtb_MCF_ibeta;
  real32_T rtb_MCF_ratTa1;
  real32_T rtb_MCF_uBCalc;
  real32_T rtb_MCF_uaBase;
  real32_T rtb_MCF_ubBase;
  real32_T rtb_Product11;
  real32_T rtb_Product2;
  real32_T rtb_Product6;
  real32_T rtb_Product9_i;
  real32_T rtb_Subtract;
  real32_T rtb_Subtract2_l;
  uint8_T rtb_Gain1;
  uint8_T rtb_Gain3;
  boolean_T rtb_Compare_ct;
  boolean_T rtb_Switch2_g;
  if ((uint16_T)(SWC_MCF_IG_DW.UnitDelay1_DSTATE_c + 1U) > 1024) {
    SWC_MCF_IG_DW.UnitDelay1_DSTATE_c = 1U;
  } else {
    SWC_MCF_IG_DW.UnitDelay1_DSTATE_c++;
  }

  if (CAL_MCF_flgRpwmFrqRandom_b) {
    rtb_MCF_uBCalc = (rtCP_Constant_Value_lx[SWC_MCF_IG_DW.UnitDelay1_DSTATE_c -
                      1] - 1.0F) * *rtu_MPC_BUS_MPC_CofRandomPwm + 1.0F;
  } else {
    rtb_MCF_uBCalc = 1.0F;
  }

  if (CAL_MCF_flgVF_b) {
    rtb_MCF_frqPwmCalc_j = *rtu_MPC_BUS_MPC_frqPwmVF;
  } else {
    rtb_MCF_frqPwmCalc_j = CAL_MCF_FixFreq_f32;
  }

  rtb_Product2 = rtb_MCF_uBCalc * rtb_MCF_frqPwmCalc_j;
  rtb_Subtract = rtb_Product2 - SWC_MCF_IG_DW.UnitDelay2_DSTATE;
  if (rtb_Subtract <= CAL_MCF_FrqRmp_f32) {
    if (-rtb_Subtract <= CAL_MCF_FrqRmp_f32) {
      SWC_MCF_IG_DW.UnitDelay2_DSTATE = rtb_Product2;
    } else {
      SWC_MCF_IG_DW.UnitDelay2_DSTATE -= CAL_MCF_FrqRmp_f32;
    }
  } else {
    SWC_MCF_IG_DW.UnitDelay2_DSTATE += CAL_MCF_FrqRmp_f32;
  }

  if (SWC_MCF_IG_DW.UnitDelay2_DSTATE > 10000.0F) {
    MCF_frqPwm = 10000.0F;
  } else if (SWC_MCF_IG_DW.UnitDelay2_DSTATE < 2000.0F) {
    MCF_frqPwm = 2000.0F;
  } else {
    MCF_frqPwm = SWC_MCF_IG_DW.UnitDelay2_DSTATE;
  }

  MCF_cofFrqPwm = MCF_frqPwm / 10000.0F;
  rtb_Product2 = *rtu_CDD_uDcLnk * CAL_MCF_cofFltWe_f32;
  SWC_MCF_IG_DW.UnitDelay_DSTATE = (1.0F - CAL_MCF_cofFltWe_f32) *
    SWC_MCF_IG_DW.UnitDelay_DSTATE + rtb_Product2;
  SWC_MCF_IG_DW.UnitDelay_DSTATE_m = (1.0F - CAL_MCF_cofFltWe_f32) *
    SWC_MCF_IG_DW.UnitDelay_DSTATE_m + rtb_Product2;
  if (CAL_MCF_bUseduDclnkSet_b) {
    VAR_MCF_uDcLnk_f32 = CAL_MCF_uDclnkSet_f32;
  } else if (CAL_MCF_flgLowOrHvudcLnk_b) {
    VAR_MCF_uDcLnk_f32 = SWC_MCF_IG_DW.UnitDelay_DSTATE;
  } else {
    VAR_MCF_uDcLnk_f32 = SWC_MCF_IG_DW.UnitDelay_DSTATE_m;
  }

  MCF_uDcLnk = VAR_MCF_uDcLnk_f32;
  VAR_MCF_HSPF_stIphaOffCal_u8 = *rtu_HSPF_BUS_HSPF_stIphaOffCal;
  if (VAR_MCF_HSPF_stIphaOffCal_u8 == ((uint8_T)MCF_Succeed_u8)) {
    rtb_Divide2 = *rtu_HSPF_BUS_HSPF_iPhaUOffset;
  } else {
    rtb_Divide2 = (real32_T)((uint16_T)MCF_GLB_DigtValue_u16) *
      MCF_GLB_OneHalf_f32;
  }

  VAR_MCF_iU_NC_f32 = ((real32_T)*rtu_CDD_iUNoOff - rtb_Divide2) *
    CAL_MCF_iUCnvFac_f32;
  if (VAR_MCF_HSPF_stIphaOffCal_u8 == ((uint8_T)MCF_Succeed_u8)) {
    rtb_Divide2 = *rtu_HSPF_BUS_HSPF_iPhaVOffset;
  } else {
    rtb_Divide2 = (real32_T)((uint16_T)MCF_GLB_DigtValue_u16) *
      MCF_GLB_OneHalf_f32;
  }

  VAR_MCF_iV_NC_f32 = ((real32_T)*rtu_CDD_iVNoOf - rtb_Divide2) *
    CAL_MCF_iVCnvFac_f32;
  if (VAR_MCF_HSPF_stIphaOffCal_u8 == ((uint8_T)MCF_Succeed_u8)) {
    rtb_Divide2 = *rtu_HSPF_BUS_HSPF_iPhaWOffset;
  } else {
    rtb_Divide2 = (real32_T)((uint16_T)MCF_GLB_DigtValue_u16) *
      MCF_GLB_OneHalf_f32;
  }

  VAR_MCF_iW_NC_f32 = ((real32_T)*rtu_CDD_iWNoOf - rtb_Divide2) *
    CAL_MCF_iWCnvFac_f32;
  switch (CAL_MCF_stChangePha_u8) {
   case 1:
    VAR_MCF_iU_f32 = VAR_MCF_iU_NC_f32;
    break;

   case 2:
    VAR_MCF_iU_f32 = VAR_MCF_iU_NC_f32;
    break;

   case 3:
    VAR_MCF_iU_f32 = VAR_MCF_iV_NC_f32;
    break;

   case 4:
    VAR_MCF_iU_f32 = VAR_MCF_iW_NC_f32;
    break;

   case 5:
    VAR_MCF_iU_f32 = VAR_MCF_iV_NC_f32;
    break;

   default:
    VAR_MCF_iU_f32 = VAR_MCF_iW_NC_f32;
    break;
  }

  MCF_iU = VAR_MCF_iU_f32;
  switch (CAL_MCF_stChangePha_u8) {
   case 1:
    VAR_MCF_iV_f32 = VAR_MCF_iV_NC_f32;
    break;

   case 2:
    VAR_MCF_iV_f32 = VAR_MCF_iW_NC_f32;
    break;

   case 3:
    VAR_MCF_iV_f32 = VAR_MCF_iU_NC_f32;
    break;

   case 4:
    VAR_MCF_iV_f32 = VAR_MCF_iU_NC_f32;
    break;

   case 5:
    VAR_MCF_iV_f32 = VAR_MCF_iW_NC_f32;
    break;

   default:
    VAR_MCF_iV_f32 = VAR_MCF_iV_NC_f32;
    break;
  }

  MCF_iV = VAR_MCF_iV_f32;
  switch (CAL_MCF_stChangePha_u8) {
   case 1:
    VAR_MCF_iW_f32 = VAR_MCF_iW_NC_f32;
    break;

   case 2:
    VAR_MCF_iW_f32 = VAR_MCF_iV_NC_f32;
    break;

   case 3:
    VAR_MCF_iW_f32 = VAR_MCF_iW_NC_f32;
    break;

   case 4:
    VAR_MCF_iW_f32 = VAR_MCF_iV_NC_f32;
    break;

   case 5:
    VAR_MCF_iW_f32 = VAR_MCF_iU_NC_f32;
    break;

   default:
    VAR_MCF_iW_f32 = VAR_MCF_iU_NC_f32;
    break;
  }

  MCF_iW = VAR_MCF_iW_f32;
  if (CAL_MCF_flgInternalOffset_b) {
    VAR_MCF_agOffset_f32 = CAL_MCF_OffsetInternal_f32;
  } else {
    VAR_MCF_agOffset_f32 = 0.0F;
  }

  VAR_MCF_agRtrEe_f32 = VAR_MCF_agOffset_f32 + *rtu_RDC_agRtrEe;
  if (360.0F <= VAR_MCF_agRtrEe_f32) {
    VAR_MCF_agRtrEe_f32 -= 360.0F;
  } else {
    if (VAR_MCF_agRtrEe_f32 <= 0.0F) {
      VAR_MCF_agRtrEe_f32 += 360.0F;
    }
  }

  rtb_MCF_UMin = VAR_MCF_agRtrEe_f32 * (real32_T)((uint16_T)
    MCF_GLB_DigtValue_u16) / MCF_GLB_CircAge_f32;
  if (rtb_MCF_UMin > 4095.0F) {
    rtb_Product2 = 4095.0F;
    rtb_MCF_UMin = 4095.0F;
  } else {
    if (rtb_MCF_UMin < 0.0F) {
      rtb_Product2 = 0.0F;
    } else {
      rtb_Product2 = rtb_MCF_UMin;
    }

    if (rtb_MCF_UMin < 0.0F) {
      rtb_MCF_UMin = 0.0F;
    }
  }

  rtb_MCF_uBCalc = rtCP_LookupCosTable_table_b[(int32_T)rtb_Product2];
  rtb_MCF_ialpha = ((2.0F * MCF_iU - MCF_iV) - MCF_iW) * 0.33333F;
  rtb_MCF_UMin = rtCP_LookupSinTable_table_a[(int32_T)rtb_MCF_UMin];
  rtb_MCF_ibeta = (MCF_iV - MCF_iW) * 0.33333F * MCF_GLB_SqrtThree_f32;
  VAR_MCF_idAct_f32 = rtb_MCF_uBCalc * rtb_MCF_ialpha + rtb_MCF_UMin *
    rtb_MCF_ibeta;
  MCF_idAct = VAR_MCF_idAct_f32;
  rtb_Subtract = *rtu_MPC_BUS_MPC_isdMTPA - *rtu_MPC_BUS_MPC_isdMTPA;
  rtb_Product2 = rtb_MCF_frqPwmCalc_j - SWC_MCF_IG_DW.UnitDelay2_DSTATE_e;
  if (rtb_Product2 <= CAL_MCF_FrqRmp_f32) {
    if (-rtb_Product2 <= CAL_MCF_FrqRmp_f32) {
      SWC_MCF_IG_DW.UnitDelay2_DSTATE_e = rtb_MCF_frqPwmCalc_j;
    } else {
      SWC_MCF_IG_DW.UnitDelay2_DSTATE_e -= CAL_MCF_FrqRmp_f32;
    }
  } else {
    SWC_MCF_IG_DW.UnitDelay2_DSTATE_e += CAL_MCF_FrqRmp_f32;
  }

  if (SWC_MCF_IG_DW.UnitDelay2_DSTATE_e > 10000.0F) {
    rtb_MCF_uaBase = 10000.0F;
  } else if (SWC_MCF_IG_DW.UnitDelay2_DSTATE_e < 2000.0F) {
    rtb_MCF_uaBase = 2000.0F;
  } else {
    rtb_MCF_uaBase = SWC_MCF_IG_DW.UnitDelay2_DSTATE_e;
  }

  rtb_MCF_ubBase = 1.0F / rtb_MCF_uaBase;
  VAR_MCF_periodCalc_f32 = rtb_MCF_ubBase;
  if (VAR_MCF_UsUseRateReal_f32 > 20.0F) {
    rtb_MCF_frqPwmCalc_j = 20.0F;
  } else if (VAR_MCF_UsUseRateReal_f32 < -1.0F) {
    rtb_MCF_frqPwmCalc_j = -1.0F;
  } else {
    rtb_MCF_frqPwmCalc_j = VAR_MCF_UsUseRateReal_f32;
  }

  rtb_MCF_ratTa1 = fabsf(*rtu_Rdc_nWoFlt);
  rtb_Divide2 = look1_iflf_binlcapw(rtb_MCF_ratTa1, ((const real32_T *)
    &(CAL_MCF_UsUseRateDesTableX_Spd_af32[0])), ((const real32_T *)
    &(CAL_MCF_UsUseRateDesTableY_UsRes_af32[0])), 10U);
  if (rtb_Divide2 > 0.92F) {
    rtb_Divide2 = 0.92F;
  } else {
    if (rtb_Divide2 < 1.0E-6F) {
      rtb_Divide2 = 1.0E-6F;
    }
  }

  VAR_MCF_UsUseRateDes_f32 = 1.0F / rtb_Divide2 - 1.0F;
  rtb_Product2 = rtb_MCF_frqPwmCalc_j - VAR_MCF_UsUseRateDes_f32;
  rtb_Subtract2_l = *rtu_MPC_BUS_MPC_isdMTPV - *rtu_MPC_BUS_MPC_isdMTPA;
  if (*rtu_SCF_BUS_SCF_flginitPI) {
    VAR_MCF_isdFW_f32 = 0.0F;
  } else {
    VAR_MCF_isdFW_f32 += CAL_MCF_isdfwKi_f32 * 10000.0F * VAR_MCF_periodCalc_f32
      * rtb_Product2 + (rtb_Product2 - SWC_MCF_IG_DW.Delay2_DSTATE) *
      CAL_MCF_isdfwKp_f32;
    if (VAR_MCF_isdFW_f32 > rtb_Subtract) {
      VAR_MCF_isdFW_f32 = rtb_Subtract;
    } else {
      if (VAR_MCF_isdFW_f32 < rtb_Subtract2_l) {
        VAR_MCF_isdFW_f32 = rtb_Subtract2_l;
      }
    }
  }

  if (CAL_MCF_flgUseFF_b) {
    VAR_MCF_isdFW_f32 += *rtu_MPC_BUS_MPC_isdFF - *rtu_MPC_BUS_MPC_isdMTPA;
  }

  if (VAR_MCF_isdFW_f32 > rtb_Subtract) {
    VAR_MCF_isdFW_f32 = rtb_Subtract;
  } else {
    if (VAR_MCF_isdFW_f32 < rtb_Subtract2_l) {
      VAR_MCF_isdFW_f32 = rtb_Subtract2_l;
    }
  }

  VAR_MCF_flgMotHeat_b = false;
  if (SWC_MCF_IG_DW.UnitDelay_DSTATE_i) {
    SWC_MCF_IG_B.uDLookupTable = look1_iflf_binlxpw
      (*rtu_HSPF_BUS_HSPF_tStrrTempFlt, ((const real32_T *)
        &(CAL_tStrrTempFltMotHeat_af32[0])), ((const real32_T *)
        &(CAL_cofPowerLimitMotHeat_af32[0])), 8U);
    if (CAL_PowerMotHeat_f32 > CAL_MCF_UpPowerHeat_f32) {
      rtb_Divide2 = CAL_MCF_UpPowerHeat_f32;
    } else if (CAL_PowerMotHeat_f32 < 0.0F) {
      rtb_Divide2 = 0.0F;
    } else {
      rtb_Divide2 = CAL_PowerMotHeat_f32;
    }

    VAR_MCF_PCUHeaterPower_f32 = rtb_Divide2 * SWC_MCF_IG_B.uDLookupTable;
    VAR_MCF_PowerDcLnk_f32 = *rtu_BCC_BUS_BCC_iDcLnkEst * MCF_uDcLnk * 0.001F;
    VAR_MCF_PowerMech_f32 = *rtu_MPC_BUS_MPC_TrqMechFlt * *rtu_Rdc_nWoFlt *
      0.000104712039F;
    VAR_MCF_PowerMotHeat_f32 = VAR_MCF_PowerDcLnk_f32 - VAR_MCF_PowerMech_f32;
    rtb_Subtract = VAR_MCF_PowerMotHeat_f32 - VAR_MCF_PCUHeaterPower_f32;
    if (VAR_MCF_flgMotHeat_b) {
      if (SWC_MCF_IG_DW.UnitDelay_DSTATE_g > CAL_MCF_UpLimitIMotHeat_f32) {
        SWC_MCF_IG_DW.UnitDelay_DSTATE_g = CAL_MCF_UpLimitIMotHeat_f32;
      } else {
        if (SWC_MCF_IG_DW.UnitDelay_DSTATE_g < CAL_MCF_DownLimitIMotHeat_f32) {
          SWC_MCF_IG_DW.UnitDelay_DSTATE_g = CAL_MCF_DownLimitIMotHeat_f32;
        }
      }

      SWC_MCF_IG_DW.UnitDelay_DSTATE_g += rtb_Subtract * CAL_MCF_KiMotHeat_f32;
    } else {
      SWC_MCF_IG_DW.UnitDelay_DSTATE_g = 0.0F;
    }

    rtb_Subtract = rtb_Subtract * CAL_MCF_KpMotHeat_f32 +
      SWC_MCF_IG_DW.UnitDelay_DSTATE_g;
    if (rtb_Subtract > CAL_MCF_UpLimitPIMotHeat_f32) {
      rtb_Subtract = CAL_MCF_UpLimitPIMotHeat_f32;
    } else {
      if (rtb_Subtract < CAL_MCF_DownLimitPIMotHeat_f32) {
        rtb_Subtract = CAL_MCF_DownLimitPIMotHeat_f32;
      }
    }

    if (rtb_Subtract >= *rtu_MPC_BUS_MPC_isdMTPA) {
      SWC_MCF_IG_B.Switch = 0.0F;
    } else {
      SWC_MCF_IG_B.Switch = rtb_Subtract - *rtu_MPC_BUS_MPC_isdMTPA;
    }
  }

  if (VAR_MCF_flgMotHeat_b) {
    VAR_MCF_idMotHeat_f32 = SWC_MCF_IG_B.Switch;
  } else {
    VAR_MCF_idMotHeat_f32 = 0.0F;
  }

  if (CAL_MCF_flgUseisTheta_b) {
    rtb_Divide2 = 11.375F * CAL_MCF_isThetaSet_f32;
    if (rtb_Divide2 > 4095.0F) {
      rtb_Divide2 = 4095.0F;
    } else {
      if (rtb_Divide2 < 0.0F) {
        rtb_Divide2 = 0.0F;
      }
    }

    VAR_MCF_idDes_f32 = CAL_MCF_isSet_f32 * rtCP_Constant_Value_m[(int32_T)
      rtb_Divide2];
  } else if (CAL_MCF_flgUseisdqSet_b) {
    VAR_MCF_idDes_f32 = CAL_MCF_isdSet_f32;
  } else if (*rtu_SCF_BUS_SCF_flgEnDchaToMc) {
    VAR_MCF_idDes_f32 = CAL_MCF_DisChaisdDes_f32;
  } else {
    VAR_MCF_idDes_f32 = (VAR_MCF_isdFW_f32 + VAR_MCF_idMotHeat_f32) +
      *rtu_MPC_BUS_MPC_isdMTPA;
  }

  MCF_idDes = VAR_MCF_idDes_f32;
  VAR_MCF_MPC_LdSubLq_f32 = *rtu_MPC_BUS_MPC_LdSubLq;
  rtb_Divide2 = (VAR_MCF_MPC_LdSubLq_f32 * VAR_MCF_idDes_f32 +
                 *rtu_MPC_BUS_MPC_psiExc) * 1.5F * (real32_T)((uint8_T)
    MCF_GLB_MotorPole_u8);
  if (rtb_Divide2 > 255.0F) {
    rtb_Divide2 = 255.0F;
  } else {
    if (rtb_Divide2 < 0.01F) {
      rtb_Divide2 = 0.01F;
    }
  }

  VAR_MCF_iqDes_f32 = *rtu_TDC_BUS_TDC_TrqDes / rtb_Divide2;
  if (CAL_MCF_flgUseisTheta_b) {
    rtb_Divide2 = 11.375F * CAL_MCF_isThetaSet_f32;
    if (rtb_Divide2 > 4095.0F) {
      rtb_Divide2 = 4095.0F;
    } else {
      if (rtb_Divide2 < 0.0F) {
        rtb_Divide2 = 0.0F;
      }
    }

    VAR_MCF_iqDes_f32 = CAL_MCF_isSet_f32 * rtCP_McFwc_SinTable_table[(int32_T)
      rtb_Divide2];
  } else if (CAL_MCF_flgUseisdqSet_b) {
    VAR_MCF_iqDes_f32 = CAL_MCF_isqSet_f32;
  } else if (*rtu_SCF_BUS_SCF_flgEnDchaToMc) {
    VAR_MCF_iqDes_f32 = CAL_MCF_DisChaisqDes_f32;
  } else {
    rtb_Subtract = CAL_MCF_isMax_f32 * CAL_MCF_isMax_f32 - VAR_MCF_idDes_f32 *
      VAR_MCF_idDes_f32;
    if (rtb_Subtract <= VAR_MCF_iqDes_f32 * VAR_MCF_iqDes_f32) {
      if (VAR_MCF_iqDes_f32 >= 0.0F) {
        rtb_MCF_isqDesCalc_0 = 1;
      } else {
        rtb_MCF_isqDesCalc_0 = -1;
      }

      VAR_MCF_iqDes_f32 = sqrtf(rtb_Subtract) * (real32_T)rtb_MCF_isqDesCalc_0;
    }
  }

  MCF_iqDes = VAR_MCF_iqDes_f32;
  VAR_MCF_iqAct_f32 = rtb_MCF_uBCalc * rtb_MCF_ibeta - rtb_MCF_UMin *
    rtb_MCF_ialpha;
  MCF_iqAct = VAR_MCF_iqAct_f32;
  VAR_MCF_udRv_f32 = *rtu_MPC_BUS_MPC_Rv * MCF_idAct;
  rtb_MCF_UMin = MCF_idDes - MCF_idAct;
  rtb_MCF_uaBase /= 10000.0F;
  rtb_Product11 = *rtu_MPC_BUS_MPC_OmBw * rtb_MCF_uaBase;
  VAR_MCF_MPC_Ld_f32 = *rtu_MPC_BUS_MPC_Ld;
  VAR_MCF_SCF_flgInitEn_b = *rtu_SCF_BUS_SCF_flginitPI;
  rtb_Add_as = *rtu_MPC_BUS_MPC_Rv + *rtu_MPC_BUS_MPC_Rs;
  rtb_MCF_uaBase *= rtb_MCF_ubBase;
  VAR_MCF_Rdc_nWoFlt_f32 = *rtu_Rdc_nWoFlt;
  rtb_Product6 = VAR_MCF_Rdc_nWoFlt_f32 * 0.0666666701F * MCF_GLB_pi_f32 * 2.0F;
  VAR_MCF_MPC_Lq_f32 = *rtu_MPC_BUS_MPC_Lq;
  rtb_MCF_uBCalc = MCF_iqDes - MCF_iqAct;
  if (VAR_MCF_SCF_flgInitEn_b) {
    SWC_MCF_IG_DW.UnitDelay_DSTATE_n = 0.0F;
  } else {
    if (CAL_MCF_flgUseUsOver_b) {
      rtb_Divide2 = CAL_MCF_udOverGain_f32 * SWC_MCF_IG_DW.Delay_DSTATE;
    } else {
      rtb_Divide2 = 0.0F;
    }

    SWC_MCF_IG_DW.UnitDelay_DSTATE_n += (rtb_Product11 * rtb_Add_as *
      rtb_MCF_UMin * CAL_MCF_udki_f32 * rtb_MCF_uaBase - rtb_Product6 *
      VAR_MCF_MPC_Lq_f32 * rtb_MCF_uBCalc * rtb_Product11 * (rtb_MCF_uaBase *
      CAL_MCF_udDecoupki_f32)) - rtb_Divide2;
  }

  rtb_Subtract = (rtb_Product11 * VAR_MCF_MPC_Ld_f32 * rtb_MCF_UMin *
                  CAL_MCF_udkp_f32 - VAR_MCF_udRv_f32) +
    SWC_MCF_IG_DW.UnitDelay_DSTATE_n;
  rtb_Subtract2_l = MCF_uDcLnk * 0.667F;
  if (VAR_MCF_SCF_flgInitEn_b) {
    SWC_MCF_IG_DW.UnitDelay1_DSTATE = 0.0F;
  } else {
    if (CAL_MCF_flgUseUsOver_b) {
      rtb_Divide2 = CAL_MCF_uqOverGain_f32 * SWC_MCF_IG_DW.Delay1_DSTATE;
    } else {
      rtb_Divide2 = 0.0F;
    }

    SWC_MCF_IG_DW.UnitDelay1_DSTATE += (rtb_Product6 * VAR_MCF_MPC_Ld_f32 *
      rtb_MCF_UMin * rtb_Product11 * (rtb_MCF_uaBase * CAL_MCF_uqDecoupki_f32) +
      rtb_Product11 * rtb_Add_as * rtb_MCF_uBCalc * CAL_MCF_uqki_f32 *
      rtb_MCF_uaBase) - rtb_Divide2;
  }

  SWC_MCF_IG_DW.UnitDelay_DSTATE_l = (1.0F - CAL_MCF_cofFltWe_f32) *
    SWC_MCF_IG_DW.UnitDelay_DSTATE_l + rtb_Product6 * CAL_MCF_cofFltWe_f32;
  VAR_MCF_EmfBack_f32 = SWC_MCF_IG_DW.UnitDelay_DSTATE_l *
    *rtu_MPC_BUS_MPC_psiExc;
  VAR_MCF_uqRv_f32 = *rtu_MPC_BUS_MPC_Rv * MCF_iqAct;
  rtb_Product11 = ((rtb_Product11 * VAR_MCF_MPC_Lq_f32 * rtb_MCF_uBCalc *
                    CAL_MCF_uqkp_f32 + SWC_MCF_IG_DW.UnitDelay1_DSTATE) +
                   VAR_MCF_EmfBack_f32) - VAR_MCF_uqRv_f32;
  rtb_Divide2 = sqrtf(rtb_Subtract * rtb_Subtract + rtb_Product11 *
                      rtb_Product11);
  if (rtb_Divide2 > 1.0E+6F) {
    rtb_Divide2 = 1.0E+6F;
  } else {
    if (rtb_Divide2 < 1.0E-6F) {
      rtb_Divide2 = 1.0E-6F;
    }
  }

  rtb_Divide2 = rtb_Subtract2_l / rtb_Divide2;
  rtb_Switch2_g = !(rtb_Divide2 - 1.0F >= 0.0F);
  if (CAL_MCF_flgUseUsdqSet_b) {
    VAR_MCF_udDes_f32 = CAL_MCF_UsdScalSet_f32;
    VAR_MCF_uqDes_f32 = CAL_MCF_UsqScalSet_f32;
  } else {
    if (rtb_Switch2_g) {
      VAR_MCF_udDes_f32 = rtb_Divide2 * rtb_Subtract;
    } else {
      VAR_MCF_udDes_f32 = rtb_Subtract;
    }

    if (rtb_Switch2_g) {
      VAR_MCF_uqDes_f32 = rtb_Divide2 * rtb_Product11;
    } else {
      VAR_MCF_uqDes_f32 = rtb_Product11;
    }
  }

  MCF_udDes = VAR_MCF_udDes_f32;
  MCF_uqDes = VAR_MCF_uqDes_f32;
  MCF_dtPwm = 1.0F / MCF_frqPwm;
  if (CAL_MCF_flgUse1113ZR_b) {
    rtb_MCF_uBCalc = VAR_MCF_agRtrEe_f32 * -12.0F;
    rtb_Divide2 = floorf(rtb_MCF_uBCalc * 0.00277777785F);
    if (rtIsNaNF(rtb_Divide2) || rtIsInfF(rtb_Divide2)) {
      rtb_Divide2 = 0.0F;
    } else {
      rtb_Divide2 = fmodf(rtb_Divide2, 256.0F);
    }

    rtb_MCF_UMin = (rtb_MCF_uBCalc - (real32_T)(rtb_Divide2 < 0.0F ? (int32_T)
      (int8_T)-(int8_T)(uint8_T)-rtb_Divide2 : (int32_T)(int8_T)(uint8_T)
      rtb_Divide2) * 360.0F) * ((real32_T)((uint16_T)MCF_GLB_DigtValue_u16) /
      MCF_GLB_CircAge_f32);
    if (rtb_MCF_UMin > 4095.0F) {
      rtb_Divide2 = 4095.0F;
    } else if (rtb_MCF_UMin < 0.0F) {
      rtb_Divide2 = 0.0F;
    } else {
      rtb_Divide2 = rtb_MCF_UMin;
    }

    rtb_MCF_uBCalc = rtCP_LookupCosTable_table[(int32_T)rtb_Divide2];
    VAR_MCF_IsSet11ZR_f32 = look1_iflf_binlxpw(*rtu_Rdc_nWoFlt, ((const real32_T
      *)&(CAL_MCF_HarmIn1113ZRX_Spd_af32[0])), ((const real32_T *)
      &(CAL_MCF_HarmIn11ZRY_Is_af32[0])), 22U);
    VAR_MCF_IsThetaSet11ZR_f32 = look1_iflf_binlxpw(*rtu_Rdc_nWoFlt, ((const
      real32_T *)&(CAL_MCF_HarmIn1113ZRX_Spd_af32[0])), ((const real32_T *)
      &(CAL_MCF_HarmIn11ZRY_Thetam_af32[0])), 22U);
    if (CAL_MCF_flgHarmInIsThetaTab11ZR_b) {
      rtb_MCF_uaBase = VAR_MCF_IsSet11ZR_f32;
      rtb_Add_as = VAR_MCF_IsThetaSet11ZR_f32;
    } else {
      rtb_MCF_uaBase = CAL_MCF_IsSet11ZR_f32;
      rtb_Add_as = CAL_MCF_IsThetaSet11ZR_f32;
    }

    rtb_Add_as *= 11.375F;
    if (rtb_Add_as > 4095.0F) {
      rtb_Divide2 = 4095.0F;
      rtb_Add_as = 4095.0F;
    } else {
      if (rtb_Add_as < 0.0F) {
        rtb_Divide2 = 0.0F;
      } else {
        rtb_Divide2 = rtb_Add_as;
      }

      if (rtb_Add_as < 0.0F) {
        rtb_Add_as = 0.0F;
      }
    }

    rtb_Product6 = rtb_MCF_uaBase * rtCP_LookupCosineTab_table[(int32_T)
      rtb_Divide2];
    rtb_Product9_i = (real32_T)((uint8_T)MCF_GLB_MotorPole_u8) * 0.0166666675F *
      *rtu_Rdc_nWoFlt * 2.0F * MCF_GLB_pi_f32;
    rtb_Divide2 = (*rtu_MPC_BUS_MPC_Lq + *rtu_MPC_BUS_MPC_Ld) * rtb_Product9_i *
      5.5F;
    rtb_MCF_uaBase *= rtCP_LookupSineTab_table[(int32_T)rtb_Add_as];
    rtb_Product9_i = (*rtu_MPC_BUS_MPC_Ld - *rtu_MPC_BUS_MPC_Lq) *
      rtb_Product9_i * 5.5F;
    rtb_Add_as = (rtb_Product6 * 0.006F + rtb_Divide2 * rtb_MCF_uaBase) -
      rtb_Product9_i * 0.0F;
    if (rtb_MCF_UMin > 4095.0F) {
      rtb_MCF_UMin = 4095.0F;
    } else {
      if (rtb_MCF_UMin < 0.0F) {
        rtb_MCF_UMin = 0.0F;
      }
    }

    rtb_MCF_UMin = rtCP_LookupSinTable_table[(int32_T)rtb_MCF_UMin];
    rtb_Divide2 = (rtb_MCF_uaBase * 0.006F - rtb_Divide2 * rtb_Product6) -
      rtb_Product9_i * 0.0F;
    SWC_MCF_IG_B.MCF_udDes11ZR = rtb_Add_as * rtb_MCF_uBCalc - rtb_Divide2 *
      rtb_MCF_UMin;
    SWC_MCF_IG_B.MCF_uqDes11ZR = rtb_Divide2 * rtb_MCF_uBCalc + rtb_Add_as *
      rtb_MCF_UMin;
    VAR_MCF_UdDes11ZR_f32 = SWC_MCF_IG_B.MCF_udDes11ZR;
  } else {
    VAR_MCF_UdDes11ZR_f32 = 0.0F;
  }

  rtb_MCF_uBCalc = MCF_udDes + VAR_MCF_UdDes11ZR_f32;
  SWC_MCF_IG_DW.UnitDelay_DSTATE_m0 = (1.0F - CAL_MCF_cofFltN_f32) *
    SWC_MCF_IG_DW.UnitDelay_DSTATE_m0 + *rtu_Rdc_nWoFlt * CAL_MCF_cofFltN_f32;
  rtb_MCF_ubBase = SWC_MCF_IG_DW.UnitDelay_DSTATE_m0 * (real32_T)((uint8_T)
    MCF_GLB_MotorPole_u8) / MCF_GLB_Sixty_f32 * (CAL_MCF_perCpnAg_f32 *
    rtb_MCF_ubBase) * MCF_GLB_CircAge_f32 + VAR_MCF_agRtrEe_f32;
  rtb_Divide2 = rtb_MCF_ubBase - MCF_GLB_CircAge_f32;
  if (rtb_Divide2 >= 0.0F) {
    rtb_MCF_ubBase = rtb_Divide2;
  } else {
    if (!(rtb_MCF_ubBase >= 0.0F)) {
      rtb_MCF_ubBase += MCF_GLB_CircAge_f32;
    }
  }

  rtb_MCF_ubBase = rtb_MCF_ubBase * (real32_T)((uint16_T)MCF_GLB_DigtValue_u16) /
    MCF_GLB_CircAge_f32;
  if (rtb_MCF_ubBase > 4095.0F) {
    rtb_Divide2 = 4095.0F;
  } else if (rtb_MCF_ubBase < 0.0F) {
    rtb_Divide2 = 0.0F;
  } else {
    rtb_Divide2 = rtb_MCF_ubBase;
  }

  rtb_Divide2 = rtCP_LookupCosTable_table_g[(int32_T)rtb_Divide2];
  if (CAL_MCF_flgUse1113ZR_b) {
    VAR_MCF_UqDes11ZR_f32 = SWC_MCF_IG_B.MCF_uqDes11ZR;
  } else {
    VAR_MCF_UqDes11ZR_f32 = 0.0F;
  }

  rtb_MCF_UMin = MCF_uqDes + VAR_MCF_UqDes11ZR_f32;
  if (rtb_MCF_ubBase > 4095.0F) {
    rtb_MCF_ubBase = 4095.0F;
  } else {
    if (rtb_MCF_ubBase < 0.0F) {
      rtb_MCF_ubBase = 0.0F;
    }
  }

  rtb_MCF_ubBase = rtCP_LookupSinTable_table_e[(int32_T)rtb_MCF_ubBase];
  VAR_MCF_uAOfsClb_f32 = rtb_MCF_uBCalc * rtb_Divide2 - rtb_MCF_UMin *
    rtb_MCF_ubBase;
  VAR_MCF_uBOfsClb_f32 = rtb_MCF_UMin * rtb_Divide2 + rtb_MCF_uBCalc *
    rtb_MCF_ubBase;
  if (CAL_MCF_flgOverModu_b) {
    VAR_MCF_usPeak_f32 = sqrtf(VAR_MCF_uAOfsClb_f32 * VAR_MCF_uAOfsClb_f32 +
      VAR_MCF_uBOfsClb_f32 * VAR_MCF_uBOfsClb_f32);
    rtb_MCF_uBCalc = MCF_uDcLnk / MCF_GLB_SqrtThree_f32 *
      CAL_MCF_cofOverModu_f32;
    rtb_Switch2_g = (VAR_MCF_usPeak_f32 <= rtb_MCF_uBCalc);
    if (fabsf(VAR_MCF_uBOfsClb_f32) <= 0.0001F) {
      rtb_MCF_ubBase = 0.0001F;
    } else {
      rtb_MCF_ubBase = VAR_MCF_uBOfsClb_f32;
    }

    rtb_Gain3 = (uint8_T)((rtb_MCF_ubBase >= 0.0F) << 7);
    if (fabsf(VAR_MCF_uAOfsClb_f32) <= 0.0001F) {
      rtb_Divide2 = 0.0001F;
    } else {
      rtb_Divide2 = VAR_MCF_uAOfsClb_f32;
    }

    rtb_Gain1 = (uint8_T)((rtb_Divide2 >= 0.0F) << 7);
    rtb_MCF_ubBase /= rtb_Divide2;
    rtb_Divide2 = fabsf(rtb_MCF_ubBase);
    rtb_Compare_ct = (rtb_Divide2 >= 1.0F);
    if (rtb_Compare_ct) {
      rtb_Divide2 = 1.0F / rtb_Divide2;
    }

    switch ((int32_T)((((((uint32_T)rtb_Gain1 << 1) + rtb_Gain3) + ((uint32_T)
                (rtb_Compare_ct << 7) << 2)) >> 2) >> 5)) {
     case 0:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j[(int32_T)
        rtb_Divide2]) * 1.49011612E-8F + 180.0F;
      break;

     case 1:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = 180.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 2:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = 360.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 3:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j[(int32_T)
        rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 4:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = 270.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_tabl_j[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 5:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j[(int32_T)
        rtb_Divide2]) * 1.49011612E-8F + 90.0F;
      break;

     case 6:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j[(int32_T)
        rtb_Divide2]) * 1.49011612E-8F + 270.0F;
      break;

     default:
      rtb_Divide2 *= 1024.0F;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Divide2 = 90.0F - (real32_T)(58672U * rtCP_DirectLookupTablenD_tabl_j
        [(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;
    }

    VAR_MCF_AgRem_f32 = rtb_Divide2 - (real32_T)(int32_T)fmodf((real32_T)
      (int32_T)floorf(rtb_Divide2 / 60.0F), 256.0F) * 60.0F;
    if (rtb_MCF_uBCalc > 1000.0F) {
      rtb_MCF_uBCalc = 1000.0F;
    } else {
      if (rtb_MCF_uBCalc < 0.001F) {
        rtb_MCF_uBCalc = 0.001F;
      }
    }

    MCF_VoltModuRate = VAR_MCF_usPeak_f32 / rtb_MCF_uBCalc;
    if (rtb_Switch2_g) {
      rtb_Divide2 = 1.0F;
    } else {
      rtb_Divide2 = look2_iflf_binlxpw(VAR_MCF_AgRem_f32 * 1023.0F /
        MCF_GLB_Sixty_f32, MCF_VoltModuRate, rtCP_OmTable_bp01Data,
        rtCP_OmTable_bp02Data, rtCP_OmTable_tableData, rtCP_OmTable_maxIndex,
        1024U) * CAL_MCF_cofOverModu_f32;
    }

    VAR_MCF_uAOm_f32 = VAR_MCF_uAOfsClb_f32 * rtb_Divide2;
    VAR_MCF_uBOm_f32 = rtb_Divide2 * VAR_MCF_uBOfsClb_f32;
  }

  if (CAL_MCF_FlgUpdateDyc_b) {
    SWC_MCF_IG_DW.UnitDelay_1_DSTATE = CAL_MCF_DycUSet_f32;
  }

  if (rtb_MCF_ratTa1 >= CAL_MCF_nDpwmOff_f32) {
    SWC_MCF_IG_DW.UnitDelay_DSTATE_hv = false;
  } else {
    SWC_MCF_IG_DW.UnitDelay_DSTATE_hv = ((rtb_MCF_ratTa1 <=
      CAL_MCF_nDpwmOffDelay_f32) || SWC_MCF_IG_DW.UnitDelay_DSTATE_hv);
  }

  if (CAL_MCF_flgOverModu_b) {
    rtb_Add_as = VAR_MCF_uAOm_f32;
  } else {
    rtb_Add_as = VAR_MCF_uAOfsClb_f32;
  }

  rtb_MCF_ubBase = MCF_uDcLnk * MCF_GLB_OneHalf_f32;
  if (rtb_MCF_ubBase > 700.0F) {
    rtb_MCF_ubBase = 700.0F;
  } else {
    if (rtb_MCF_ubBase < 0.0001F) {
      rtb_MCF_ubBase = 0.0001F;
    }
  }

  rtb_MCF_uaBase = rtb_Add_as / rtb_MCF_ubBase;
  rtb_MCF_UMin = rtb_Add_as * MCF_GLB_OneHalf_f32;
  if (CAL_MCF_flgOverModu_b) {
    rtb_MCF_uBCalc = VAR_MCF_uBOm_f32;
  } else {
    rtb_MCF_uBCalc = VAR_MCF_uBOfsClb_f32;
  }

  rtb_Product6 = rtb_MCF_uBCalc * 0.866F;
  rtb_Divide2 = ((0.0F - rtb_MCF_UMin) - rtb_Product6) / rtb_MCF_ubBase;
  rtb_MCF_ubBase = (rtb_Product6 - rtb_MCF_UMin) / rtb_MCF_ubBase;
  if (rtb_MCF_uaBase >= rtb_MCF_ubBase) {
    rtb_Product6 = rtb_MCF_uaBase;
  } else {
    rtb_Product6 = rtb_MCF_ubBase;
  }

  if (!(rtb_Product6 >= rtb_Divide2)) {
    rtb_Product6 = rtb_Divide2;
  }

  if (rtb_MCF_uaBase <= rtb_MCF_ubBase) {
    rtb_MCF_UMin = rtb_MCF_uaBase;
  } else {
    rtb_MCF_UMin = rtb_MCF_ubBase;
  }

  if (!(rtb_MCF_UMin <= rtb_Divide2)) {
    rtb_MCF_UMin = rtb_Divide2;
  }

  switch (CAL_MCF_stDpwm_u8) {
   case 1:
    rtb_Product6 = MCF_dtPwm * MCF_GLB_OneHalf_f32 * MCF_GLB_OneHalf_f32;
    break;

   case 2:
    rtb_Product6 = ((rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
                     MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32) +
                    rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
                    MCF_GLB_OneHalf_f32) * MCF_GLB_OneHalf_f32;
    break;

   case 3:
    if (((!(rtb_MCF_uaBase > rtb_MCF_ubBase)) || (!(rtb_MCF_ubBase > rtb_Divide2)))
        && ((!(rtb_MCF_ubBase > rtb_Divide2)) || (!(rtb_Divide2 > rtb_MCF_uaBase)))
        && ((!(rtb_Divide2 > rtb_MCF_uaBase)) || (!(rtb_MCF_uaBase >
           rtb_MCF_ubBase)))) {
      rtb_Product6 = rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32;
    } else {
      rtb_Product6 = rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32;
    }
    break;

   case 4:
    if (((rtb_MCF_uaBase > rtb_MCF_ubBase) && (rtb_MCF_ubBase > rtb_Divide2)) ||
        ((rtb_MCF_ubBase > rtb_Divide2) && (rtb_Divide2 > rtb_MCF_uaBase)) ||
        ((rtb_Divide2 > rtb_MCF_uaBase) && (rtb_MCF_uaBase > rtb_MCF_ubBase))) {
      rtb_Product6 = rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32;
    } else {
      rtb_Product6 = rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32;
    }
    break;

   case 5:
    if (rtb_Product6 * MCF_GLB_OneHalf_f32 + rtb_MCF_UMin * MCF_GLB_OneHalf_f32 >=
        0.0F) {
      rtb_Product6 = rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32;
    } else {
      rtb_Product6 = rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32;
    }
    break;

   case 6:
    if (rtb_Product6 * MCF_GLB_OneHalf_f32 + rtb_MCF_UMin * MCF_GLB_OneHalf_f32 <
        0.0F) {
      rtb_Product6 = rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32;
    } else {
      rtb_Product6 = rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
        MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32;
    }
    break;

   case 7:
    rtb_Product6 = rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
      MCF_GLB_OneHalf_f32;
    break;

   case 8:
    rtb_Product6 = rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
      MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32;
    break;

   default:
    rtb_Product6 = ((rtb_MCF_UMin * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
                     MCF_GLB_OneHalf_f32 + MCF_dtPwm * MCF_GLB_OneHalf_f32) +
                    rtb_Product6 * MCF_dtPwm * MCF_GLB_OneHalf_f32 *
                    MCF_GLB_OneHalf_f32) * MCF_GLB_OneHalf_f32;
    break;
  }

  rtb_MCF_UMin = (rtb_MCF_uaBase * MCF_dtPwm * -0.25F + rtb_Product6) * 2.0F;
  rtb_MCF_ubBase = (rtb_MCF_ubBase * MCF_dtPwm * -0.25F + rtb_Product6) * 2.0F;
  rtb_MCF_uaBase = (rtb_Divide2 * MCF_dtPwm * -0.25F + rtb_Product6) * 2.0F;
  if (rtb_MCF_ratTa1 > CAL_MCF_SpdOffDeadCpn_f32) {
    SWC_MCF_IG_DW.UnitDelay_DSTATE_c = false;
  } else {
    SWC_MCF_IG_DW.UnitDelay_DSTATE_c = ((rtb_MCF_ratTa1 <=
      CAL_MCF_SpdOnDeadCpn_f32) || SWC_MCF_IG_DW.UnitDelay_DSTATE_c);
  }

  rtb_MCF_ratTa1 = fabsf(*rtu_TDC_BUS_TDC_TrqDes);
  VAR_MCF_FlgDeadCpn_b = ((!(rtb_MCF_ratTa1 > CAL_MCF_TrqOffDeadCpn_f32)) &&
    SWC_MCF_IG_DW.UnitDelay_DSTATE_c && CAL_MCF_FlgUseDeadCpn_b && (MCF_idDes <=
    0.0F));
  if (VAR_MCF_FlgDeadCpn_b) {
    if (fabsf(MCF_iqDes) <= 0.0001F) {
      rtb_MCF_DeadVoltage = 0.0001F;
    } else {
      rtb_MCF_DeadVoltage = MCF_iqDes;
    }

    rtb_Gain3 = (uint8_T)((rtb_MCF_DeadVoltage >= 0.0F) << 7);
    if (fabsf(MCF_idDes) <= 0.0001F) {
      rtb_Product9_i = 0.0001F;
    } else {
      rtb_Product9_i = MCF_idDes;
    }

    rtb_Gain1 = (uint8_T)((rtb_Product9_i >= 0.0F) << 7);
    rtb_MCF_DeadVoltage /= rtb_Product9_i;
    rtb_Product9_i = fabsf(rtb_MCF_DeadVoltage);
    rtb_Switch2_g = (rtb_Product9_i >= 1.0F);
    if (rtb_Switch2_g) {
      rtb_Product9_i = 1.0F / rtb_Product9_i;
    }

    switch ((int32_T)((((((uint32_T)rtb_Gain1 << 1) + rtb_Gain3) + ((uint32_T)
                (rtb_Switch2_g << 7) << 2)) >> 2) >> 5)) {
     case 0:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_Divide2]) * 1.49011612E-8F + 180.0F;
      break;

     case 1:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = 180.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 2:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = 360.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 3:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 4:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = 270.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;

     case 5:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_Divide2]) * 1.49011612E-8F + 90.0F;
      break;

     case 6:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = (real32_T)(58672U * rtCP_DirectLookupTablenD_table_
        [(int32_T)rtb_Divide2]) * 1.49011612E-8F + 270.0F;
      break;

     default:
      rtb_Divide2 = 1024.0F * rtb_Product9_i;
      if (rtb_Divide2 > 1024.0F) {
        rtb_Divide2 = 1024.0F;
      }

      rtb_Product9_i = 90.0F - (real32_T)(58672U *
        rtCP_DirectLookupTablenD_table_[(int32_T)rtb_Divide2]) * 1.49011612E-8F;
      break;
    }

    rtb_Product9_i += VAR_MCF_agRtrEe_f32;
    rtb_Divide2 = floorf(rtb_Product9_i * 0.00277777785F);
    if (rtIsNaNF(rtb_Divide2) || rtIsInfF(rtb_Divide2)) {
      rtb_Divide2 = 0.0F;
    } else {
      rtb_Divide2 = fmodf(rtb_Divide2, 256.0F);
    }

    rtb_Product9_i -= (real32_T)(rtb_Divide2 < 0.0F ? (int32_T)(int8_T)-(int8_T)
      (uint8_T)-rtb_Divide2 : (int32_T)(int8_T)(uint8_T)rtb_Divide2) * 360.0F;
    rtb_Divide2 = rtb_Product9_i - CAL_MCF_AgDiffCurrSec_f32;
    if ((rtb_Divide2 > MCF_ANGLE_CURRENT_30) && (rtb_Divide2 <=
         MCF_ANGLE_CURRENT_90)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_2);
    } else if ((rtb_Divide2 > MCF_ANGLE_CURRENT_90) && (rtb_Divide2 <=
                MCF_ANGLE_CURRENT_150)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_3);
    } else if ((rtb_Divide2 > MCF_ANGLE_CURRENT_150) && (rtb_Divide2 <=
                MCF_ANGLE_CURRENT_210)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_4);
    } else if ((rtb_Divide2 > MCF_ANGLE_CURRENT_210) && (rtb_Divide2 <=
                MCF_ANGLE_CURRENT_270)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_5);
    } else if ((rtb_Divide2 > MCF_ANGLE_CURRENT_270) && (rtb_Divide2 <=
                MCF_ANGLE_CURRENT_330)) {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_6);
    } else {
      rtb_Gain3 = ((uint8_T)MCF_CURRENT_SECTOR_1);
    }

    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_MCF_DeadVoltage = rtCP_DirectLookupTablenD_table[rtb_Gain1];
    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_DirectLookupTablenD1 = rtCP_DirectLookupTablenD1_table[rtb_Gain1];
    rtb_MCF_coefAlphaErr = (rtb_MCF_DeadVoltage - rtb_DirectLookupTablenD1) *
      0.5F;
    rtb_Product6 = look1_iflf_binlcpw(rtb_MCF_ratTa1, ((const real32_T *)
      &(CAL_MCF_AgRangeDeadCpnX_Trq_af32[0])), ((const real32_T *)
      &(CAL_MCF_AgRangeDeadCpnY_Ag_af32[0])), 6U);
    rtb_Divide2 = floorf(rtb_Product9_i * 0.0166666675F);
    if (rtIsNaNF(rtb_Divide2) || rtIsInfF(rtb_Divide2)) {
      rtb_Divide2 = 0.0F;
    } else {
      rtb_Divide2 = fmodf(rtb_Divide2, 256.0F);
    }

    rtb_Divide2 = (rtb_Product9_i - (real32_T)(rtb_Divide2 < 0.0F ? (int32_T)
      (int8_T)-(int8_T)(uint8_T)-rtb_Divide2 : (int32_T)(int8_T)(uint8_T)
      rtb_Divide2) * 60.0F) - 30.0F;
    if (rtb_Divide2 < 0.0F) {
      rtb_Product9_i = fabsf(rtb_Divide2);
      if (rtb_Product9_i < rtb_Product6) {
        rtb_Product9_i = rtb_MCF_DeadVoltage - (1.0F - rtb_Product9_i /
          rtb_Product6) * rtb_MCF_coefAlphaErr;
      } else {
        rtb_Product9_i = rtb_MCF_DeadVoltage;
      }
    } else if (rtb_Divide2 < rtb_Product6) {
      rtb_Product9_i = (1.0F - rtb_Divide2 / rtb_Product6) *
        rtb_MCF_coefAlphaErr + rtb_DirectLookupTablenD1;
    } else {
      rtb_Product9_i = rtb_DirectLookupTablenD1;
    }

    rtb_MCF_DeadVoltage = CAL_MCF_DeadTimeCpn_f32 * 1.0E-6F / MCF_dtPwm *
      MCF_uDcLnk;
    SWC_MCF_IG_B.MCF_uAlphaDeadCpn = rtb_Product9_i * rtb_MCF_DeadVoltage;
    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_MCF_coefAlphaErr = rtCP_DirectLookupTablenD2_table[rtb_Gain1];
    if ((uint8_T)(rtb_Gain3 - 1) < 5) {
      rtb_Gain1 = (uint8_T)(rtb_Gain3 - 1);
    } else {
      rtb_Gain1 = 5U;
    }

    rtb_Product9_i = rtCP_DirectLookupTablenD3_table[rtb_Gain1];
    rtb_DirectLookupTablenD1 = (rtb_MCF_coefAlphaErr - rtb_Product9_i) * 0.5F;
    if (rtb_Divide2 < 0.0F) {
      rtb_Divide2 = fabsf(rtb_Divide2);
      if (rtb_Divide2 < rtb_Product6) {
        rtb_Product9_i = rtb_MCF_coefAlphaErr - (1.0F - rtb_Divide2 /
          rtb_Product6) * rtb_DirectLookupTablenD1;
      } else {
        rtb_Product9_i = rtb_MCF_coefAlphaErr;
      }
    } else {
      if (rtb_Divide2 < rtb_Product6) {
        rtb_Product9_i += (1.0F - rtb_Divide2 / rtb_Product6) *
          rtb_DirectLookupTablenD1;
      }
    }

    SWC_MCF_IG_B.MCF_uBetaDeadCpn = rtb_Product9_i * rtb_MCF_DeadVoltage;
    VAR_MCF_uBetaDeadCpn_f32 = SWC_MCF_IG_B.MCF_uBetaDeadCpn;
    VAR_MCF_uAlphaDeadCpn_f32 = SWC_MCF_IG_B.MCF_uAlphaDeadCpn;
  } else {
    VAR_MCF_uBetaDeadCpn_f32 = 0.0F;
    VAR_MCF_uAlphaDeadCpn_f32 = 0.0F;
  }

  rtb_MCF_uBCalc += VAR_MCF_uBetaDeadCpn_f32;
  rtb_Add_as += VAR_MCF_uAlphaDeadCpn_f32;
  rtb_Add_as *= 0.866F;
  rtb_Product9_i = rtb_MCF_uBCalc * MCF_GLB_OneHalf_f32;
  rtb_Gain3 = (uint8_T)(((uint32_T)((rtb_Add_as - rtb_Product9_i > 0.0F) << 1) +
    (rtb_MCF_uBCalc > 0.0F)) + (((0.0F - rtb_Add_as) - rtb_Product9_i > 0.0F) <<
    2));
  if (rtb_Gain3 > 6) {
    rtb_Gain3 = 6U;
  } else {
    if (rtb_Gain3 < 1) {
      rtb_Gain3 = 1U;
    }
  }

  if (MCF_uDcLnk > 1000.0F) {
    rtb_Divide2 = 1000.0F;
  } else if (MCF_uDcLnk < 0.0001F) {
    rtb_Divide2 = 0.0001F;
  } else {
    rtb_Divide2 = MCF_uDcLnk;
  }

  if (rtb_MCF_frqPwmCalc_j + 1.0F < 0.0001F) {
    rtb_Product6 = 0.0001F;
  } else {
    rtb_Product6 = rtb_MCF_frqPwmCalc_j + 1.0F;
  }

  rtb_Product6 = MCF_dtPwm / rtb_Divide2 * MCF_GLB_SqrtThree_f32 *
    look1_iflf_binlxpw(1.0F / rtb_Product6 * 1.1547F, ((const real32_T *)
    &(CAL_MCF_FfcTx_af32[0])), ((const real32_T *)&(CAL_MCF_FfcTy_af32[0])), 10U);
  switch (rtb_Gain3) {
   case 1:
    rtb_Divide2 = (rtb_Product9_i - rtb_Add_as) * rtb_Product6;
    rtb_Product6 *= rtb_Product9_i + rtb_Add_as;
    break;

   case 2:
    rtb_Divide2 = (rtb_Product9_i + rtb_Add_as) * rtb_Product6;
    rtb_Product6 = -(rtb_MCF_uBCalc * rtb_Product6);
    break;

   case 3:
    rtb_Divide2 = -((rtb_Product9_i - rtb_Add_as) * rtb_Product6);
    rtb_Product6 *= rtb_MCF_uBCalc;
    break;

   case 4:
    rtb_Divide2 = -(rtb_MCF_uBCalc * rtb_Product6);
    rtb_Product6 *= rtb_Product9_i - rtb_Add_as;
    break;

   case 5:
    rtb_Divide2 = rtb_MCF_uBCalc * rtb_Product6;
    rtb_Product6 = -((rtb_Product9_i + rtb_Add_as) * rtb_Product6);
    break;

   default:
    SWC_MCF_IG_Osc_nrN6((rtb_Product9_i + rtb_Add_as) * rtb_Product6,
                        (rtb_Product9_i - rtb_Add_as) * rtb_Product6,
                        &rtb_Divide2, &rtb_Product6);
    break;
  }

  rtb_MCF_uBCalc = (MCF_dtPwm * MCF_GLB_OneHalf_f32 + MCF_GLB_OneHalf_f32 *
                    rtb_Divide2) + MCF_GLB_OneHalf_f32 * rtb_Product6;
  rtb_Divide2 = rtb_MCF_uBCalc - rtb_Divide2;
  switch (rtb_Gain3) {
   case 1:
    rtb_Product9_i = rtb_Divide2;
    rtb_Add_as = rtb_MCF_uBCalc;
    rtb_MCF_uBCalc = rtb_Divide2 - rtb_Product6;
    break;

   case 2:
    rtb_Product9_i = rtb_MCF_uBCalc;
    rtb_Add_as = rtb_Divide2 - rtb_Product6;
    rtb_MCF_uBCalc = rtb_Divide2;
    break;

   case 3:
    rtb_Product9_i = rtb_MCF_uBCalc;
    rtb_Add_as = rtb_Divide2;
    rtb_MCF_uBCalc = rtb_Divide2 - rtb_Product6;
    break;

   case 4:
    rtb_Product9_i = rtb_Divide2 - rtb_Product6;
    rtb_Add_as = rtb_Divide2;
    break;

   case 5:
    rtb_Product9_i = rtb_Divide2 - rtb_Product6;
    rtb_Add_as = rtb_MCF_uBCalc;
    rtb_MCF_uBCalc = rtb_Divide2;
    break;

   default:
    rtb_Product9_i = rtb_Divide2;
    rtb_Add_as = rtb_Divide2 - rtb_Product6;
    break;
  }

  if ((rtb_MCF_ratTa1 <= CAL_MCF_trqDpwmOff_f32) &&
      SWC_MCF_IG_DW.UnitDelay_DSTATE_hv && CAL_MCF_flgDpwm_b) {
    rtb_Product9_i = MCF_dtPwm - rtb_MCF_UMin;
    rtb_Add_as = MCF_dtPwm - rtb_MCF_ubBase;
    rtb_MCF_uBCalc = MCF_dtPwm - rtb_MCF_uaBase;
  }

  if (rtb_Product9_i >= rtb_Add_as) {
    rtb_Divide2 = rtb_Product9_i;
  } else {
    rtb_Divide2 = rtb_Add_as;
  }

  if (!(rtb_Divide2 >= rtb_MCF_uBCalc)) {
    rtb_Divide2 = rtb_MCF_uBCalc;
  }

  rtb_Divide2 = MCF_dtPwm - rtb_Divide2;
  rtb_MCF_ratTa1 = rtb_Product9_i + rtb_Divide2;
  rtb_MCF_ubBase = rtb_Add_as + rtb_Divide2;
  rtb_MCF_UMin = rtb_MCF_uBCalc + rtb_Divide2;
  rtb_Divide2 = MCF_dtPwm - CAL_MCF_ratNarrWave_f32 * 1.0E-6F;
  if (CAL_MCF_flgNWS_b && ((rtb_Product9_i >= rtb_Divide2) || (rtb_Add_as >=
        rtb_Divide2) || (rtb_MCF_uBCalc >= rtb_Divide2))) {
    rtb_Product9_i = rtb_MCF_ratTa1;
    rtb_Add_as = rtb_MCF_ubBase;
    rtb_MCF_uBCalc = rtb_MCF_UMin;
  }

  if (CAL_MCF_FlgUseSetDyc_b) {
    rtb_Divide2 = SWC_MCF_IG_DW.UnitDelay_1_DSTATE;
  } else {
    rtb_Divide2 = rtb_Product9_i / MCF_dtPwm;
  }

  if (rtb_Divide2 > CAL_MCF_ratUp_f32) {
    rtb_Divide2 = CAL_MCF_ratUp_f32;
  }

  if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
    MCF_dycW = rtb_Divide2;
  } else {
    MCF_dycW = CAL_MCF_ratLo_f32;
  }

  if (CAL_MCF_FlgUpdateDyc_b) {
    SWC_MCF_IG_DW.UnitDelay_2_DSTATE = CAL_MCF_DycVSet_f32;
  }

  if (CAL_MCF_FlgUseSetDyc_b) {
    rtb_Divide2 = SWC_MCF_IG_DW.UnitDelay_2_DSTATE;
  } else {
    rtb_Divide2 = rtb_Add_as / MCF_dtPwm;
  }

  if (rtb_Divide2 > CAL_MCF_ratUp_f32) {
    rtb_Divide2 = CAL_MCF_ratUp_f32;
  }

  if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
    rtb_MCF_ratTa1 = rtb_Divide2;
  } else {
    rtb_MCF_ratTa1 = CAL_MCF_ratLo_f32;
  }

  if (CAL_MCF_FlgUpdateDyc_b) {
    SWC_MCF_IG_DW.UnitDelay_3_DSTATE = CAL_MCF_DycWSet_f32;
  }

  if (CAL_MCF_FlgUseSetDyc_b) {
    rtb_Divide2 = SWC_MCF_IG_DW.UnitDelay_3_DSTATE;
  } else {
    rtb_Divide2 = rtb_MCF_uBCalc / MCF_dtPwm;
  }

  if (rtb_Divide2 > CAL_MCF_ratUp_f32) {
    rtb_Divide2 = CAL_MCF_ratUp_f32;
  }

  switch (CAL_MCF_stChangePha_u8) {
   case 1:
    MCF_dycU = MCF_dycW;
    MCF_dycV = rtb_MCF_ratTa1;
    if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
      MCF_dycW = rtb_Divide2;
    } else {
      MCF_dycW = CAL_MCF_ratLo_f32;
    }
    break;

   case 2:
    MCF_dycU = MCF_dycW;
    if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
      MCF_dycV = rtb_Divide2;
    } else {
      MCF_dycV = CAL_MCF_ratLo_f32;
    }

    MCF_dycW = rtb_MCF_ratTa1;
    break;

   case 3:
    MCF_dycU = rtb_MCF_ratTa1;
    MCF_dycV = MCF_dycW;
    if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
      MCF_dycW = rtb_Divide2;
    } else {
      MCF_dycW = CAL_MCF_ratLo_f32;
    }
    break;

   case 4:
    MCF_dycU = rtb_MCF_ratTa1;
    if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
      MCF_dycV = rtb_Divide2;
    } else {
      MCF_dycV = CAL_MCF_ratLo_f32;
    }
    break;

   case 5:
    if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
      MCF_dycU = rtb_Divide2;
    } else {
      MCF_dycU = CAL_MCF_ratLo_f32;
    }

    MCF_dycV = MCF_dycW;
    MCF_dycW = rtb_MCF_ratTa1;
    break;

   default:
    if (rtb_Divide2 > CAL_MCF_ratLo_f32) {
      MCF_dycU = rtb_Divide2;
    } else {
      MCF_dycU = CAL_MCF_ratLo_f32;
    }

    MCF_dycV = rtb_MCF_ratTa1;
    break;
  }

  switch (rtb_Gain3) {
   case 1:
    MCF_SecVolt = 2U;
    break;

   case 2:
    MCF_SecVolt = 6U;
    break;

   case 3:
    MCF_SecVolt = 1U;
    break;

   case 4:
    MCF_SecVolt = 4U;
    break;

   case 5:
    MCF_SecVolt = 3U;
    break;

   default:
    MCF_SecVolt = 5U;
    break;
  }

  MCF_tiLock = look1_iflf_binlcpw(MCF_frqPwm, ((const real32_T *)
    &(CAL_MCF_DeadTimeTableX_Frq_af32[0])), ((const real32_T *)
    &(CAL_MCF_DeadTimeTableY_Ti_af32[0])), 14U);
  if (CAL_MCF_FlgUseSetDyc_b) {
    MCF_stpwmMode = CAL_MCF_stPwmMode_u8;
  } else {
    MCF_stpwmMode = *rtu_SCF_BUS_SCF_stPwmMode;
  }

  VAR_MCF_Is_f32 = sqrtf(rtb_MCF_ialpha * rtb_MCF_ialpha + rtb_MCF_ibeta *
    rtb_MCF_ibeta);
  MCF_Is = VAR_MCF_Is_f32;
  *rty_MCF_BUS_MCF_idDes = MCF_udDes;
  *rty_MCF_BUS_MCF_cofFrqPwm = MCF_cofFrqPwm;
  *rty_MCF_BUS_MCF_dtPwm = MCF_dtPwm;
  *rty_MCF_BUS_MCF_tiLock = MCF_tiLock;
  *rty_MCF_BUS_MCF_stpwmMode = MCF_stpwmMode;
  *rty_MCF_BUS_MCF_Is = MCF_Is;
  *rty_MCF_BUS_MCF_idAct = MCF_idAct;
  *rty_MCF_BUS_MCF_iqAct = MCF_iqAct;
  *rty_MCF_BUS_MCF_uDcLnk = MCF_uDcLnk;
  *rty_MCF_BUS_MCF_iU = MCF_iU;
  *rty_MCF_BUS_MCF_iV = MCF_iV;
  *rty_MCF_BUS_MCF_iqDes = MCF_uqDes;
  *rty_MCF_BUS_MCF_iW = MCF_iW;
  *rty_MCF_BUS_MCF_VoltModuRate = MCF_VoltModuRate;
  *rty_MCF_BUS_MCF_udDes = MCF_idDes;
  *rty_MCF_BUS_MCF_uqDes = MCF_iqDes;
  *rty_MCF_BUS_MCF_dycU = MCF_dycU;
  *rty_MCF_BUS_MCF_dycV = MCF_dycV;
  *rty_MCF_BUS_MCF_dycW = MCF_dycW;
  *rty_MCF_BUS_MCF_SecVolt = MCF_SecVolt;
  *rty_MCF_BUS_MCF_frqPwm = MCF_frqPwm;
  rtb_Divide2 = sqrtf(MCF_udDes * MCF_udDes + MCF_uqDes * MCF_uqDes);
  if (rtb_Divide2 > 1023.0F) {
    rtb_Divide2 = 1023.0F;
  } else {
    if (rtb_Divide2 < 0.01F) {
      rtb_Divide2 = 0.01F;
    }
  }

  VAR_MCF_UsUseRateReal_f32 = rtb_Subtract2_l / rtb_Divide2 - 1.0F;
  SWC_MCF_IG_DW.Delay1_DSTATE = rtb_Product11 - VAR_MCF_uqDes_f32;
  SWC_MCF_IG_DW.Delay_DSTATE = rtb_Subtract - VAR_MCF_udDes_f32;
  SWC_MCF_IG_DW.UnitDelay_DSTATE_e = (1.0F - CAL_MCF_cofFltPowerHeat_f32) *
    SWC_MCF_IG_DW.UnitDelay_DSTATE_e + VAR_MCF_PowerMotHeat_f32 *
    CAL_MCF_cofFltPowerHeat_f32;
  if ((SWC_MCF_IG_B.uDLookupTable < 100.0F) && (!VAR_MCF_flgMotHeat_b)) {
    VAR_MCF_TMAhtChsts_f32 = CAL_MCF_Part_ActiveHeat_u8;
  } else if (VAR_MCF_flgMotHeat_b && (VAR_MCF_PCUHeaterPower_f32 -
              SWC_MCF_IG_DW.UnitDelay_DSTATE_e <= CAL_MCF_DeltaPower_f32)) {
    VAR_MCF_TMAhtChsts_f32 = CAL_MCF_ActiveHeatNormal_u8;
  } else {
    VAR_MCF_TMAhtChsts_f32 = CAL_MCF_ActiveHeatInit_u8;
  }

  VAR_MCF_flgFw_b = (rtb_MCF_frqPwmCalc_j - VAR_MCF_UsUseRateDes_f32 <= 0.0F);
  SWC_MCF_IG_DW.Delay2_DSTATE = rtb_Product2;
  SWC_MCF_IG_DW.UnitDelay_DSTATE_i = VAR_MCF_flgMotHeat_b;
}
#define FAW_CORE0_DMEM0_VALUE_STOP
#include "FAW_MemMap.h"

void SWC_MCF_IG_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_MCF_IG_T *const SWC_MCF_IG_M = &(SWC_MCF_IG_MdlrefDW.rtm);
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetErrorStatusPointer(SWC_MCF_IG_M, rt_errorStatus);
}
