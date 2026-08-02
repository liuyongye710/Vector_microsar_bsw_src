#include "SWC_HSPF_IG.h"
#include "SWC_HSPF_IG_private.h"

#define SWC_HSPF_IG_IN_OffstCalFishd   ((uint8_T)1U)
#define SWC_HSPF_IG_IN_OffstCalInit    ((uint8_T)2U)
#define SWC_HSPF_IG_IN_OffstCalRun     ((uint8_T)3U)

real32_T HSPF_uKl30Flt;
real32_T VAR_Hspf_tDBCTempU_f32;
real32_T HSPF_tDBCTempUFlt;
real32_T VAR_Hspf_tDBCTempV_f32;
real32_T HSPF_tDBCTempVFlt;
real32_T VAR_Hspf_tDBCTempW_f32;
real32_T HSPF_tDBCTempWFlt;
real32_T HSPF_tStrrTemp1Flt;
real32_T HSPF_tStrrTemp2Flt;
real32_T HSPF_nSlowFlt;
real32_T HSPF_tCoolantTempFlt;
real32_T HSPF_tDrvBoardTempFlt;
real32_T HSPF_iDcLnkEstFlt;
real32_T VAR_Hspf_uDcLnk_f32;
real32_T HSPF_uDcLnkSlowFlt;
real32_T HSPF_PwrDcLnk;
real32_T HSPF_tStrrTempFlt;
real32_T HSPF_tIGBTTjFlt;
real32_T HSPF_tCoolantTjFlt;
real32_T VAR_Bsw_tCoolantTemp_f32;
real32_T VAR_Hspf_tCoolantTemp_f32;
real32_T VAR_Hspf_tDrvBoardTemp_f32;
real32_T HSPF_iPhaWOffset;
real32_T HSPF_iPhaVOffset;
real32_T HSPF_iPhaUOffset;
uint16_T VAR_Bsw_tDBCTempU_u16;
uint16_T VAR_Bsw_tDBCTempV_u16;
uint16_T VAR_Bsw_tDBCTempW_u16;
uint16_T VAR_Bsw_tStrrTemp1_u16;
uint16_T VAR_Bsw_tStrrTemp2_u16;
uint16_T VAR_Bsw_tDrvBoardTemp_u16;
int16_T VAR_Hspf_tStrrTemp2_s16;
int16_T VAR_Hspf_tStrrTemp1_s16;
uint8_T HSPF_tDBCTempCmpErrSt;
uint8_T HSPF_MotorOpenErrSt;
uint8_T HSPF_InvOpenErrSt;
uint8_T HSPF_stIphaOffCal;
uint8_T HSPF_checkstatus;
boolean_T VAR_Hspf_bSwtTempSttr2_b;
boolean_T HSPF_bt15;
boolean_T HSPF_Crash;
boolean_T HSPF_INV_Open;
boolean_T HSPF_Motor_Open;
boolean_T HSPF_Wake;
boolean_T VAR_Hspf_tDBCCmpErrDelay_b;
boolean_T VAR_Hspf_bSwtTempSttr1_b;
boolean_T VAR_Bsw_Wake_b;
boolean_T VAR_Bsw_Crash_b;
boolean_T VAR_Bsw_INV_Open_b;
boolean_T VAR_Bsw_Motor_Open_b;
boolean_T VAR_Hspf_flgSttr1NoErr_b;
boolean_T VAR_Hspf_flgSttr2NoErr_b;
MdlrefDW_SWC_HSPF_IG_T SWC_HSPF_IG_MdlrefDW;
B_SWC_HSPF_IG_c_T SWC_HSPF_IG_B;
DW_SWC_HSPF_IG_f_T SWC_HSPF_IG_DW;
void SWC_HSPF_IG_Init(void)
{
  real_T tmp;
  real32_T tmp_0;
  uint16_T tmp_1;
  SWC_HSPF_IG_DW.UnitDelay_DSTATE_pp = true;
  VAR_Hspf_flgSttr1NoErr_b = !(VAR_Bsw_tCoolantTemp_f32 != 0.0F);
  VAR_Hspf_flgSttr2NoErr_b = !(VAR_Bsw_tCoolantTemp_f32 != 0.0F);
  tmp = floor(SWC_HSPF_IG_ConstB.Divide);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  VAR_Bsw_tStrrTemp1_u16 = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  tmp = floor(SWC_HSPF_IG_ConstB.Divide1);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  VAR_Bsw_tStrrTemp2_u16 = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  if (VAR_Bsw_tCoolantTemp_f32 > 4095.0F) {
    tmp_0 = 4095.0F;
  } else if (VAR_Bsw_tCoolantTemp_f32 < 0.0F) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = VAR_Bsw_tCoolantTemp_f32;
  }

  VAR_Hspf_tCoolantTemp_f32 = rtCP_tCoolantTem_Table_table[(int32_T)tmp_0];
  tmp_0 = floorf(VAR_Bsw_tCoolantTemp_f32);
  if (rtIsNaNF(tmp_0) || rtIsInfF(tmp_0)) {
    tmp_0 = 0.0F;
  } else {
    tmp_0 = fmodf(tmp_0, 65536.0F);
  }

  VAR_Bsw_tDrvBoardTemp_u16 = (uint16_T)(tmp_0 < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-tmp_0 : (int32_T)(uint16_T)tmp_0);
  if (VAR_Bsw_tDrvBoardTemp_u16 < 4095) {
    tmp_1 = VAR_Bsw_tDrvBoardTemp_u16;
  } else {
    tmp_1 = 4095U;
  }

  VAR_Hspf_tDrvBoardTemp_f32 = rtCP_PCBTem_Table_table[tmp_1];
}

void SWC_HSPF_IG(const real32_T *rtu_BSW_uDcLnk, const real32_T
                 *rtu_BCC_BUS_BCC_iDcLnkEst, const real32_T *rtu_Rdc_nWoFlt,
                 const uint16_T *rtu_BSW_tDBCTempU, const uint16_T
                 *rtu_BSW_tDBCTempV, const uint16_T *rtu_BSW_tDBCTempW, const
                 uint16_T *rtu_BSW_iUNoOff, const uint16_T *rtu_BSW_iVNoOff,
                 const uint16_T *rtu_BSW_iWNoOff, const uint8_T
                 *rtu_SCF_BUS_SCF_stPreDrvCtl, real32_T
                 *rty_HSPF_BUS_HSPF_uKl30Flt, real32_T
                 *rty_HSPF_BUS_HSPF_tDBCTempUFlt, real32_T
                 *rty_HSPF_BUS_HSPF_tDBCTempVFlt, real32_T
                 *rty_HSPF_BUS_HSPF_tDBCTempWFlt, real32_T
                 *rty_HSPF_BUS_HSPF_tStrrTemp1Flt, real32_T
                 *rty_HSPF_BUS_HSPF_tStrrTemp2Flt, real32_T
                 *rty_HSPF_BUS_HSPF_nSlowFlt, real32_T
                 *rty_HSPF_BUS_HSPF_tCoolantTempF, real32_T
                 *rty_HSPF_BUS_HSPF_tDrvBoardTemp, real32_T
                 *rty_HSPF_BUS_HSPF_iDcLnkEstFlt, real32_T
                 *rty_HSPF_BUS_HSPF_PwrDcLnk, boolean_T *rty_HSPF_BUS_HSPF_bt15,
                 boolean_T *rty_HSPF_BUS_HSPF_Crash, boolean_T
                 *rty_HSPF_BUS_HSPF_INV_Open, boolean_T
                 *rty_HSPF_BUS_HSPF_Motor_Open, real32_T
                 *rty_HSPF_BUS_HSPF_uDcLnkSlowFlt, boolean_T
                 *rty_HSPF_BUS_HSPF_Wake, real32_T
                 *rty_HSPF_BUS_HSPF_iPhaUOffset, real32_T
                 *rty_HSPF_BUS_HSPF_iPhaVOffset, real32_T
                 *rty_HSPF_BUS_HSPF_iPhaWOffset, uint8_T
                 *rty_HSPF_BUS_HSPF_stIphaOffCal, real32_T
                 *rty_HSPF_BUS_HSPF_tStrrTempFlt, real32_T
                 *rty_HSPF_BUS_HSPF_tIGBTTjFlt, real32_T
                 *rty_HSPF_BUS_HSPF_tCoolantTjFlt, real32_T
                 *rty_HSPF_BUS_HSPF_VerMatchFailu, uint8_T
                 *rty_HSPF_BUS_HSPF_tDBCTempCmpEr, uint8_T
                 *rty_HSPF_BUS_HSPF_MotorOpenErrS, uint8_T
                 *rty_HSPF_BUS_HSPF_InvOpenErrSt, uint8_T
                 *rty_HSPF_BUS_HSPF_checkstatus, boolean_T
                 *rty_HSPF_BUS_HSPF_bSwtTempSttr1, boolean_T
                 *rty_HSPF_BUS_HSPF_bSwtTempSttr2)
{
  int32_T tmp;
  real32_T rtb_CAL_DBCTemLow_Table_e;
  real32_T rtb_CAL_DBCTemLow_Table_h;
  real32_T rtb_Divide;
  real32_T rtb_Divide_ep;
  real32_T rtb_Divide_h;
  real32_T rtb_Product_d_tmp;
  real32_T rtb_UnitDelay1_e;
  real32_T rtb_UnitDelay2;
  real32_T rtb_UnitDelay3_g;
  real32_T rtb_UnitDelay4;
  real32_T rtb_UnitDelay5;
  real32_T rtb_UnitDelay6;
  real32_T rtb_UnitDelay7;
  uint32_T qY;
  uint16_T tmp_0;
  int8_T tmp_1;
  uint8_T tmp_2;
  boolean_T guard1 = false;
  boolean_T rtb_LogicalOperator;
  if (SWC_HSPF_IG_DW.UnitDelay_DSTATE_i) {
    if (VAR_Bsw_tStrrTemp2_u16 < 1023) {
      tmp_0 = VAR_Bsw_tStrrTemp2_u16;
    } else {
      tmp_0 = 1023U;
    }

    VAR_Hspf_tStrrTemp2_s16 = CAL_Hspf_MotTemHigTable_af32[tmp_0];
  } else {
    if (VAR_Bsw_tStrrTemp2_u16 < 1023) {
      tmp_0 = VAR_Bsw_tStrrTemp2_u16;
    } else {
      tmp_0 = 1023U;
    }

    VAR_Hspf_tStrrTemp2_s16 = CAL_Hspf_MotTemLowTable_af32[tmp_0];
  }

  if (VAR_Hspf_tStrrTemp2_s16 >= CAL_Hspf_tSwtTempSttrHiLim_f32) {
    SWC_HSPF_IG_DW.UnitDelay_DSTATE_i = true;
  } else {
    SWC_HSPF_IG_DW.UnitDelay_DSTATE_i = ((!(VAR_Hspf_tStrrTemp2_s16 <=
      CAL_Hspf_tSwtTempSttrLoLim_f32)) && SWC_HSPF_IG_DW.UnitDelay_DSTATE_i);
  }

  VAR_Hspf_bSwtTempSttr2_b = !SWC_HSPF_IG_DW.UnitDelay_DSTATE_i;
  rtb_Divide = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_uKl30FltFrq_f32;
  if (rtb_Divide < 1.0F) {
    rtb_Divide = 1.0F;
  }

  rtb_Product_d_tmp = GLB_HspfFlt_pi_f32 * (real32_T)CAL_Hspf_Multiple_u8;
  rtb_Divide /= rtb_Product_d_tmp + rtb_Divide;
  HSPF_uKl30Flt = (1.0F - rtb_Divide) * VAR_Hspf_uKl30_f32 + rtb_Divide *
    HSPF_uKl30Flt;
  VAR_Bsw_tDBCTempU_u16 = *rtu_BSW_tDBCTempU;
  if (VAR_Bsw_tDBCTempU_u16 < 4095) {
    tmp_0 = VAR_Bsw_tDBCTempU_u16;
  } else {
    tmp_0 = 4095U;
  }

  rtb_Divide = rtCP_CAL_DBCTemLow_Table_table[tmp_0];
  if (!(fabsf(rtb_Divide - SWC_HSPF_IG_DW.UnitDelay1_DSTATE) <=
        CAL_Hspf_tDBCTempROCLim_u8)) {
    SWC_HSPF_IG_DW.UnitDelay2_DSTATE_n = 0U;
  }

  SWC_HSPF_IG_DW.UnitDelay2_DSTATE_n = (uint8_T)((uint32_T)
    SWC_HSPF_IG_DW.UnitDelay2_DSTATE_n + !SWC_HSPF_IG_DW.UnitDelay4_DSTATE_a);
  SWC_HSPF_IG_DW.UnitDelay4_DSTATE_a = (SWC_HSPF_IG_DW.UnitDelay2_DSTATE_n >=
    CAL_Hspf_DBCTempROCLimChkCnt_u8);
  if (SWC_HSPF_IG_DW.UnitDelay4_DSTATE_a) {
    VAR_Hspf_tDBCTempU_f32 = rtb_Divide;
  }

  rtb_Divide_h = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_TmpUFltFrq_f32;
  if (rtb_Divide_h < 1.0F) {
    rtb_Divide_h = 1.0F;
  }

  rtb_Divide_h /= rtb_Product_d_tmp + rtb_Divide_h;
  HSPF_tDBCTempUFlt = (1.0F - rtb_Divide_h) * VAR_Hspf_tDBCTempU_f32 +
    rtb_Divide_h * HSPF_tDBCTempUFlt;
  VAR_Bsw_tDBCTempV_u16 = *rtu_BSW_tDBCTempV;
  if (VAR_Bsw_tDBCTempV_u16 < 4095) {
    tmp_0 = VAR_Bsw_tDBCTempV_u16;
  } else {
    tmp_0 = 4095U;
  }

  rtb_CAL_DBCTemLow_Table_h = rtCP_CAL_DBCTemLow_Table_table_[tmp_0];
  if (!(fabsf(rtb_CAL_DBCTemLow_Table_h - SWC_HSPF_IG_DW.UnitDelay1_DSTATE_m) <=
        CAL_Hspf_tDBCTempROCLim_u8)) {
    SWC_HSPF_IG_DW.UnitDelay2_DSTATE_g = 0U;
  }

  SWC_HSPF_IG_DW.UnitDelay2_DSTATE_g = (uint8_T)((uint32_T)
    SWC_HSPF_IG_DW.UnitDelay2_DSTATE_g + !SWC_HSPF_IG_DW.UnitDelay4_DSTATE_b);
  SWC_HSPF_IG_DW.UnitDelay4_DSTATE_b = (SWC_HSPF_IG_DW.UnitDelay2_DSTATE_g >=
    CAL_Hspf_DBCTempROCLimChkCnt_u8);
  if (SWC_HSPF_IG_DW.UnitDelay4_DSTATE_b) {
    VAR_Hspf_tDBCTempV_f32 = rtb_CAL_DBCTemLow_Table_h;
  }

  rtb_Divide_h = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_TmpVFltFrq_f32;
  if (rtb_Divide_h < 1.0F) {
    rtb_Divide_h = 1.0F;
  }

  rtb_Divide_h /= rtb_Product_d_tmp + rtb_Divide_h;
  HSPF_tDBCTempVFlt = (1.0F - rtb_Divide_h) * VAR_Hspf_tDBCTempV_f32 +
    rtb_Divide_h * HSPF_tDBCTempVFlt;
  VAR_Bsw_tDBCTempW_u16 = *rtu_BSW_tDBCTempW;
  if (VAR_Bsw_tDBCTempW_u16 < 4095) {
    tmp_0 = VAR_Bsw_tDBCTempW_u16;
  } else {
    tmp_0 = 4095U;
  }

  rtb_CAL_DBCTemLow_Table_e = rtCP_CAL_DBCTemLow_Table_tabl_n[tmp_0];
  if (!(fabsf(rtb_CAL_DBCTemLow_Table_e - SWC_HSPF_IG_DW.UnitDelay1_DSTATE_i) <=
        CAL_Hspf_tDBCTempROCLim_u8)) {
    SWC_HSPF_IG_DW.UnitDelay2_DSTATE_gn = 0U;
  }

  SWC_HSPF_IG_DW.UnitDelay2_DSTATE_gn = (uint8_T)((uint32_T)
    SWC_HSPF_IG_DW.UnitDelay2_DSTATE_gn + !SWC_HSPF_IG_DW.UnitDelay4_DSTATE_m);
  SWC_HSPF_IG_DW.UnitDelay4_DSTATE_m = (SWC_HSPF_IG_DW.UnitDelay2_DSTATE_gn >=
    CAL_Hspf_DBCTempROCLimChkCnt_u8);
  if (SWC_HSPF_IG_DW.UnitDelay4_DSTATE_m) {
    VAR_Hspf_tDBCTempW_f32 = rtb_CAL_DBCTemLow_Table_e;
  }

  rtb_Divide_h = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_TmpWFltFrq_f32;
  if (rtb_Divide_h < 1.0F) {
    rtb_Divide_h = 1.0F;
  }

  rtb_Divide_h /= rtb_Product_d_tmp + rtb_Divide_h;
  HSPF_tDBCTempWFlt = (1.0F - rtb_Divide_h) * VAR_Hspf_tDBCTempW_f32 +
    rtb_Divide_h * HSPF_tDBCTempWFlt;
  if (SWC_HSPF_IG_DW.UnitDelay_DSTATE_f) {
    if (VAR_Bsw_tStrrTemp1_u16 < 1023) {
      tmp_0 = VAR_Bsw_tStrrTemp1_u16;
    } else {
      tmp_0 = 1023U;
    }

    VAR_Hspf_tStrrTemp1_s16 = CAL_Hspf_MotTemHigTable_af32[tmp_0];
  } else {
    if (VAR_Bsw_tStrrTemp1_u16 < 1023) {
      tmp_0 = VAR_Bsw_tStrrTemp1_u16;
    } else {
      tmp_0 = 1023U;
    }

    VAR_Hspf_tStrrTemp1_s16 = CAL_Hspf_MotTemLowTable_af32[tmp_0];
  }

  rtb_Divide_h = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_tStrrTmp1FltFrq_f32;
  if (rtb_Divide_h < 1.0F) {
    rtb_Divide_h = 1.0F;
  }

  rtb_Divide_h /= rtb_Product_d_tmp + rtb_Divide_h;
  HSPF_tStrrTemp1Flt = (1.0F - rtb_Divide_h) * (real32_T)VAR_Hspf_tStrrTemp1_s16
    + rtb_Divide_h * HSPF_tStrrTemp1Flt;
  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_tStrrTmp2FltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_tStrrTemp2Flt = (1.0F - rtb_Divide_ep) * (real32_T)
    VAR_Hspf_tStrrTemp2_s16 + rtb_Divide_ep * HSPF_tStrrTemp2Flt;
  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) / CAL_Hspf_nFltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_nSlowFlt = (1.0F - rtb_Divide_ep) * *rtu_Rdc_nWoFlt + rtb_Divide_ep *
    HSPF_nSlowFlt;
  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_tCoolantFltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_tCoolantTempFlt = (1.0F - rtb_Divide_ep) * VAR_Hspf_tCoolantTemp_f32 +
    rtb_Divide_ep * HSPF_tCoolantTempFlt;
  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_CltInletTempFltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_tDrvBoardTempFlt = (1.0F - rtb_Divide_ep) * VAR_Hspf_tDrvBoardTemp_f32 +
    rtb_Divide_ep * HSPF_tDrvBoardTempFlt;
  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_iDcLnkEstFltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_iDcLnkEstFlt = (1.0F - rtb_Divide_ep) * *rtu_BCC_BUS_BCC_iDcLnkEst +
    rtb_Divide_ep * HSPF_iDcLnkEstFlt;
  VAR_Hspf_uDcLnk_f32 = *rtu_BSW_uDcLnk;
  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_uDcLnkFltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_uDcLnkSlowFlt = (1.0F - rtb_Divide_ep) * VAR_Hspf_uDcLnk_f32 +
    rtb_Divide_ep * HSPF_uDcLnkSlowFlt;
  HSPF_PwrDcLnk = HSPF_uDcLnkSlowFlt * HSPF_iDcLnkEstFlt;
  if (VAR_Bsw_bt15_b) {
    if (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_j) {
      tmp_1 = 0;
    } else {
      tmp_1 = CAL_Hspf_bt15ChkAddCnt_u8;
    }
  } else if (SWC_HSPF_IG_DW.UnitDelay3_DSTATE_h) {
    tmp_1 = 0;
  } else {
    tmp_1 = CAL_Hspf_bt15ChkSubCnt_s8;
  }

  SWC_HSPF_IG_DW.UnitDelay_DSTATE_lp += tmp_1;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_j = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_lp >=
    CAL_Hspf_bt15ChkCntHiLim_u8);
  SWC_HSPF_IG_DW.UnitDelay3_DSTATE_h = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_lp <=
    CAL_Hspf_bt15ChkCntLoLim_s8);
  if (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_j) {
    HSPF_bt15 = true;
  } else {
    HSPF_bt15 = ((!SWC_HSPF_IG_DW.UnitDelay3_DSTATE_h) && HSPF_bt15);
  }

  if (SWC_HSPF_IG_DW.UnitDelay3_DSTATE_p) {
    tmp_1 = 0;
  } else {
    tmp_1 = CAL_Hspf_CrashChkSubCnt_s8;
  }

  SWC_HSPF_IG_DW.UnitDelay_DSTATE_a2 += tmp_1;
  SWC_HSPF_IG_DW.UnitDelay3_DSTATE_p = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_a2 <=
    CAL_Hspf_CrashChkCntLoLim_s8);
  if (SWC_HSPF_IG_DW.UnitDelay_DSTATE_a2 >= CAL_Hspf_CrashChkCntHiLim_u8) {
    HSPF_Crash = true;
  } else {
    HSPF_Crash = ((!SWC_HSPF_IG_DW.UnitDelay3_DSTATE_p) && HSPF_Crash);
  }

  if (VAR_Bsw_INV_Open_b) {
    if (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_e) {
      tmp_2 = 0U;
    } else {
      tmp_2 = CAL_Hspf_INVOpenChkAddCnt_u8;
    }
  } else if (SWC_HSPF_IG_DW.UnitDelay3_DSTATE_hn) {
    tmp_2 = 0U;
  } else {
    tmp_2 = (uint8_T)CAL_Hspf_INVOpenChkSubCnt_s8;
  }

  SWC_HSPF_IG_DW.UnitDelay_DSTATE_oy += (int8_T)tmp_2;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_e = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_oy >=
    CAL_Hspf_INVOpenChkCntHiLim_u8);
  SWC_HSPF_IG_DW.UnitDelay3_DSTATE_hn = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_oy <=
    CAL_Hspf_INVOpenChkCntLoLim_s8);
  if (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_e) {
    HSPF_INV_Open = true;
  } else {
    HSPF_INV_Open = ((!SWC_HSPF_IG_DW.UnitDelay3_DSTATE_hn) && HSPF_INV_Open);
  }

  if (VAR_Bsw_Motor_Open_b) {
    if (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_c) {
      tmp_2 = 0U;
    } else {
      tmp_2 = CAL_Hspf_MotorOpenChkAddCnt_u8;
    }
  } else if (SWC_HSPF_IG_DW.UnitDelay3_DSTATE_p0) {
    tmp_2 = 0U;
  } else {
    tmp_2 = (uint8_T)CAL_Hspf_MototOpenChkSubCnt_s8;
  }

  SWC_HSPF_IG_DW.UnitDelay_DSTATE_g += (int8_T)tmp_2;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_c = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_g >=
    CAL_Hspf_MotorOpenChkCntHiLim_u8);
  SWC_HSPF_IG_DW.UnitDelay3_DSTATE_p0 = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_g <=
    CAL_Hspf_MotorOpenChkCntLoLim_s8);
  if (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_c) {
    HSPF_Motor_Open = true;
  } else {
    HSPF_Motor_Open = ((!SWC_HSPF_IG_DW.UnitDelay3_DSTATE_p0) && HSPF_Motor_Open);
  }

  if (SWC_HSPF_IG_DW.UnitDelay3_DSTATE_e) {
    tmp_1 = 0;
  } else {
    tmp_1 = CAL_Hspf_bt15ChkSubCnt_s8;
  }

  SWC_HSPF_IG_DW.UnitDelay_DSTATE_ms += tmp_1;
  SWC_HSPF_IG_DW.UnitDelay3_DSTATE_e = (SWC_HSPF_IG_DW.UnitDelay_DSTATE_ms <=
    CAL_Hspf_bt15ChkCntLoLim_s8);
  if (SWC_HSPF_IG_DW.UnitDelay_DSTATE_ms >= CAL_Hspf_bt15ChkCntHiLim_u8) {
    HSPF_Wake = true;
  } else {
    HSPF_Wake = ((!SWC_HSPF_IG_DW.UnitDelay3_DSTATE_e) && HSPF_Wake);
  }

  if (SWC_HSPF_IG_DW.UnitDelay_DSTATE_pp) {
    if (SWC_HSPF_IG_DW.is_active_c3_SWC_HSPF_IG == 0U) {
      SWC_HSPF_IG_DW.is_active_c3_SWC_HSPF_IG = 1U;
      SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
    } else {
      guard1 = false;
      switch (SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG) {
       case SWC_HSPF_IG_IN_OffstCalFishd:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl != CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
        }
        break;

       case SWC_HSPF_IG_IN_OffstCalInit:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl == CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.cntSelfChkTolCnt_p = 0U;
          HSPF_iPhaUOffset = 0.0F;
          SWC_HSPF_IG_B.flgOfsClb_g = false;
          SWC_HSPF_IG_B.stiOfsClb_o = ((uint8_T)CAL_Hspf_Uncheck_u8);
          SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalRun;
          SWC_HSPF_IG_DW.cntSelfChkValCnt_a = 0U;
          SWC_HSPF_IG_DW.iValSum_b = 0U;
        }
        break;

       default:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl != CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
        } else if (((*rtu_BSW_iUNoOff > CAL_Hspf_iPhaHighSet_u16) ||
                    (*rtu_BSW_iUNoOff < CAL_Hspf_iPhaLowSet_u16)) &&
                   (SWC_HSPF_IG_DW.cntSelfChkTolCnt_p <
                    CAL_Hspf_cntIPhCalOffTolCnt_u16)) {
          tmp = SWC_HSPF_IG_DW.cntSelfChkTolCnt_p + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt_p + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkTolCnt_p = (uint16_T)tmp;
          SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalRun;
          SWC_HSPF_IG_DW.cntSelfChkValCnt_a = 0U;
          SWC_HSPF_IG_DW.iValSum_b = 0U;
        } else {
          tmp = SWC_HSPF_IG_DW.cntSelfChkTolCnt_p + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt_p + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkTolCnt_p = (uint16_T)tmp;
          tmp = SWC_HSPF_IG_DW.cntSelfChkValCnt_a + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkValCnt_a + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkValCnt_a = (uint16_T)tmp;
          qY = SWC_HSPF_IG_DW.iValSum_b + *rtu_BSW_iUNoOff;
          if (qY < SWC_HSPF_IG_DW.iValSum_b) {
            qY = MAX_uint32_T;
          }

          SWC_HSPF_IG_DW.iValSum_b = qY;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt_p >
              CAL_Hspf_cntIPhCalOffTolCnt_u16) {
            SWC_HSPF_IG_B.stiOfsClb_o = ((uint8_T)CAL_Hspf_Failure_u8);
            guard1 = true;
          } else {
            if (SWC_HSPF_IG_DW.cntSelfChkValCnt_a >=
                CAL_Hspf_cntIPhCalOffValCnt_u16) {
              SWC_HSPF_IG_B.stiOfsClb_o = ((uint8_T)CAL_Hspf_Succeed_u8);
              HSPF_iPhaUOffset = (real32_T)SWC_HSPF_IG_DW.iValSum_b / (real32_T)
                CAL_Hspf_cntIPhCalOffValCnt_u16;
              guard1 = true;
            }
          }
        }
        break;
      }

      if (guard1) {
        SWC_HSPF_IG_DW.is_c3_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalFishd;
        SWC_HSPF_IG_B.flgOfsClb_g = true;
      }
    }

    if (SWC_HSPF_IG_DW.is_active_c4_SWC_HSPF_IG == 0U) {
      SWC_HSPF_IG_DW.is_active_c4_SWC_HSPF_IG = 1U;
      SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
    } else {
      guard1 = false;
      switch (SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG) {
       case SWC_HSPF_IG_IN_OffstCalFishd:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl != CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
        }
        break;

       case SWC_HSPF_IG_IN_OffstCalInit:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl == CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.cntSelfChkTolCnt_i = 0U;
          HSPF_iPhaVOffset = 0.0F;
          SWC_HSPF_IG_B.flgOfsClb_j = false;
          SWC_HSPF_IG_B.stiOfsClb_d = ((uint8_T)CAL_Hspf_Uncheck_u8);
          SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalRun;
          SWC_HSPF_IG_DW.cntSelfChkValCnt_k = 0U;
          SWC_HSPF_IG_DW.iValSum_i = 0U;
        }
        break;

       default:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl != CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
        } else if (((*rtu_BSW_iVNoOff > CAL_Hspf_iPhaHighSet_u16) ||
                    (*rtu_BSW_iVNoOff < CAL_Hspf_iPhaLowSet_u16)) &&
                   (SWC_HSPF_IG_DW.cntSelfChkTolCnt_i <
                    CAL_Hspf_cntIPhCalOffTolCnt_u16)) {
          tmp = SWC_HSPF_IG_DW.cntSelfChkTolCnt_i + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt_i + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkTolCnt_i = (uint16_T)tmp;
          SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalRun;
          SWC_HSPF_IG_DW.cntSelfChkValCnt_k = 0U;
          SWC_HSPF_IG_DW.iValSum_i = 0U;
        } else {
          tmp = SWC_HSPF_IG_DW.cntSelfChkTolCnt_i + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt_i + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkTolCnt_i = (uint16_T)tmp;
          tmp = SWC_HSPF_IG_DW.cntSelfChkValCnt_k + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkValCnt_k + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkValCnt_k = (uint16_T)tmp;
          qY = SWC_HSPF_IG_DW.iValSum_i + *rtu_BSW_iVNoOff;
          if (qY < SWC_HSPF_IG_DW.iValSum_i) {
            qY = MAX_uint32_T;
          }

          SWC_HSPF_IG_DW.iValSum_i = qY;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt_i >
              CAL_Hspf_cntIPhCalOffTolCnt_u16) {
            SWC_HSPF_IG_B.stiOfsClb_d = ((uint8_T)CAL_Hspf_Failure_u8);
            guard1 = true;
          } else {
            if (SWC_HSPF_IG_DW.cntSelfChkValCnt_k >=
                CAL_Hspf_cntIPhCalOffValCnt_u16) {
              SWC_HSPF_IG_B.stiOfsClb_d = ((uint8_T)CAL_Hspf_Succeed_u8);
              HSPF_iPhaVOffset = (real32_T)SWC_HSPF_IG_DW.iValSum_i / (real32_T)
                CAL_Hspf_cntIPhCalOffValCnt_u16;
              guard1 = true;
            }
          }
        }
        break;
      }

      if (guard1) {
        SWC_HSPF_IG_DW.is_c4_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalFishd;
        SWC_HSPF_IG_B.flgOfsClb_j = true;
      }
    }

    if (SWC_HSPF_IG_DW.is_active_c6_SWC_HSPF_IG == 0U) {
      SWC_HSPF_IG_DW.is_active_c6_SWC_HSPF_IG = 1U;
      SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
    } else {
      guard1 = false;
      switch (SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG) {
       case SWC_HSPF_IG_IN_OffstCalFishd:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl != CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
        }
        break;

       case SWC_HSPF_IG_IN_OffstCalInit:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl == CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.cntSelfChkTolCnt = 0U;
          HSPF_iPhaWOffset = 0.0F;
          SWC_HSPF_IG_B.flgOfsClb = false;
          SWC_HSPF_IG_B.stiOfsClb = ((uint8_T)CAL_Hspf_Uncheck_u8);
          SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalRun;
          SWC_HSPF_IG_DW.cntSelfChkValCnt = 0U;
          SWC_HSPF_IG_DW.iValSum = 0U;
        }
        break;

       default:
        if (*rtu_SCF_BUS_SCF_stPreDrvCtl != CAL_Hspf_stPreDrvCtl_u8) {
          SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalInit;
        } else if (((*rtu_BSW_iWNoOff > CAL_Hspf_iPhaHighSet_u16) ||
                    (*rtu_BSW_iWNoOff < CAL_Hspf_iPhaLowSet_u16)) &&
                   (SWC_HSPF_IG_DW.cntSelfChkTolCnt <
                    CAL_Hspf_cntIPhCalOffTolCnt_u16)) {
          tmp = SWC_HSPF_IG_DW.cntSelfChkTolCnt + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkTolCnt = (uint16_T)tmp;
          SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalRun;
          SWC_HSPF_IG_DW.cntSelfChkValCnt = 0U;
          SWC_HSPF_IG_DW.iValSum = 0U;
        } else {
          tmp = SWC_HSPF_IG_DW.cntSelfChkTolCnt + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkTolCnt = (uint16_T)tmp;
          tmp = SWC_HSPF_IG_DW.cntSelfChkValCnt + 1;
          if (SWC_HSPF_IG_DW.cntSelfChkValCnt + 1 > 65535) {
            tmp = 65535;
          }

          SWC_HSPF_IG_DW.cntSelfChkValCnt = (uint16_T)tmp;
          qY = SWC_HSPF_IG_DW.iValSum + *rtu_BSW_iWNoOff;
          if (qY < SWC_HSPF_IG_DW.iValSum) {
            qY = MAX_uint32_T;
          }

          SWC_HSPF_IG_DW.iValSum = qY;
          if (SWC_HSPF_IG_DW.cntSelfChkTolCnt > CAL_Hspf_cntIPhCalOffTolCnt_u16)
          {
            SWC_HSPF_IG_B.stiOfsClb = ((uint8_T)CAL_Hspf_Failure_u8);
            guard1 = true;
          } else {
            if (SWC_HSPF_IG_DW.cntSelfChkValCnt >=
                CAL_Hspf_cntIPhCalOffValCnt_u16) {
              SWC_HSPF_IG_B.stiOfsClb = ((uint8_T)CAL_Hspf_Succeed_u8);
              HSPF_iPhaWOffset = (real32_T)SWC_HSPF_IG_DW.iValSum / (real32_T)
                CAL_Hspf_cntIPhCalOffValCnt_u16;
              guard1 = true;
            }
          }
        }
        break;
      }

      if (guard1) {
        SWC_HSPF_IG_DW.is_c6_SWC_HSPF_IG = SWC_HSPF_IG_IN_OffstCalFishd;
        SWC_HSPF_IG_B.flgOfsClb = true;
      }
    }

    rtb_LogicalOperator = (SWC_HSPF_IG_B.flgOfsClb_g &&
      SWC_HSPF_IG_B.flgOfsClb_j && SWC_HSPF_IG_B.flgOfsClb);
    SWC_HSPF_IG_B.LogicalOperator2 = !rtb_LogicalOperator;
    if (rtb_LogicalOperator) {
      if ((SWC_HSPF_IG_B.stiOfsClb_d == ((uint8_T)CAL_Hspf_Succeed_u8)) &&
          (SWC_HSPF_IG_B.stiOfsClb == ((uint8_T)CAL_Hspf_Succeed_u8)) &&
          (SWC_HSPF_IG_B.stiOfsClb_o == ((uint8_T)CAL_Hspf_Succeed_u8))) {
        HSPF_stIphaOffCal = ((uint8_T)CAL_Hspf_Succeed_u8);
      } else {
        HSPF_stIphaOffCal = ((uint8_T)CAL_Hspf_Failure_u8);
      }
    } else {
      HSPF_stIphaOffCal = ((uint8_T)CAL_Hspf_Uncheck_u8);
    }

    if (HSPF_stIphaOffCal == ((uint8_T)CAL_Hspf_Failure_u8)) {
      HSPF_checkstatus = 3U;
    } else {
      HSPF_checkstatus = 2U;
    }
  }

  if (SWC_HSPF_IG_ConstB.LogicalOperator) {
    HSPF_tStrrTempFlt = HSPF_tStrrTemp2Flt;
  } else if (SWC_HSPF_IG_ConstB.LogicalOperator2) {
    HSPF_tStrrTempFlt = HSPF_tStrrTemp1Flt;
  } else if (SWC_HSPF_IG_ConstB.LogicalOperator3) {
    if (HSPF_tStrrTemp1Flt >= HSPF_tStrrTemp2Flt) {
      HSPF_tStrrTempFlt = HSPF_tStrrTemp1Flt;
    } else {
      HSPF_tStrrTempFlt = HSPF_tStrrTemp2Flt;
    }
  } else {
    HSPF_tStrrTempFlt = HSPF_tStrrTemp1Flt;
  }

  rtb_Divide_h = SWC_HSPF_IG_DW.UnitDelay_DSTATE_l;
  if (VAR_Bsw_tCoolantTemp_f32 - SWC_HSPF_IG_DW.UnitDelay_DSTATE_l >= 0.0F) {
    rtb_Divide_ep = VAR_Bsw_tCoolantTemp_f32;
  } else {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay_DSTATE_l;
  }

  rtb_UnitDelay1_e = SWC_HSPF_IG_DW.UnitDelay1_DSTATE_n;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay1_DSTATE_n >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay1_DSTATE_n;
  }

  rtb_UnitDelay2 = SWC_HSPF_IG_DW.UnitDelay2_DSTATE;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay2_DSTATE >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay2_DSTATE;
  }

  rtb_UnitDelay3_g = SWC_HSPF_IG_DW.UnitDelay3_DSTATE_f;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay3_DSTATE_f >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay3_DSTATE_f;
  }

  rtb_UnitDelay4 = SWC_HSPF_IG_DW.UnitDelay4_DSTATE;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay4_DSTATE >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay4_DSTATE;
  }

  rtb_UnitDelay5 = SWC_HSPF_IG_DW.UnitDelay5_DSTATE;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay5_DSTATE >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay5_DSTATE;
  }

  rtb_UnitDelay6 = SWC_HSPF_IG_DW.UnitDelay6_DSTATE;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay6_DSTATE >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay6_DSTATE;
  }

  rtb_UnitDelay7 = SWC_HSPF_IG_DW.UnitDelay7_DSTATE;
  if (!(rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay7_DSTATE >= 0.0F)) {
    rtb_Divide_ep = SWC_HSPF_IG_DW.UnitDelay7_DSTATE;
  }

  if (rtb_Divide_ep - SWC_HSPF_IG_DW.UnitDelay8_DSTATE >= 0.0F) {
    HSPF_tIGBTTjFlt = rtb_Divide_ep;
  } else {
    HSPF_tIGBTTjFlt = SWC_HSPF_IG_DW.UnitDelay8_DSTATE;
  }

  rtb_Divide_ep = (real32_T)((uint8_T)PRV_CalFltFrq_10ms) /
    CAL_Hspf_TmpCoolanTjFltFrq_f32;
  if (rtb_Divide_ep < 1.0F) {
    rtb_Divide_ep = 1.0F;
  }

  rtb_Divide_ep /= rtb_Product_d_tmp + rtb_Divide_ep;
  HSPF_tCoolantTjFlt = (1.0F - rtb_Divide_ep) * VAR_Bsw_tCoolantTemp_f32 +
    rtb_Divide_ep * HSPF_tCoolantTjFlt;
  rtb_LogicalOperator = ((fabsf(HSPF_tDBCTempUFlt - HSPF_tDBCTempVFlt) >=
    CAL_Hspf_tDBCtempOffset_u8) || (fabsf(HSPF_tDBCTempUFlt - HSPF_tDBCTempWFlt)
    >= CAL_Hspf_tDBCtempOffset_u8) || (fabsf(HSPF_tDBCTempVFlt -
    HSPF_tDBCTempWFlt) >= CAL_Hspf_tDBCtempOffset_u8));
  if (!rtb_LogicalOperator) {
    SWC_HSPF_IG_DW.UnitDelay1_DSTATE_f = 0U;
  }

  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_f = (uint16_T)((uint32_T)rtb_LogicalOperator
    + SWC_HSPF_IG_DW.UnitDelay1_DSTATE_f);
  VAR_Hspf_tDBCCmpErrDelay_b = (SWC_HSPF_IG_DW.UnitDelay1_DSTATE_f >=
    CAL_Hspf_tDBCCmpTime_u16);
  if (SWC_HSPF_IG_ConstB.LogicalOperator1_f) {
    HSPF_tDBCTempCmpErrSt = (uint8_T)(VAR_Hspf_tDBCCmpErrDelay_b + 2U);
  } else {
    HSPF_tDBCTempCmpErrSt = 2U;
  }

  HSPF_MotorOpenErrSt = (uint8_T)(!HSPF_INV_Open + 2U);
  HSPF_InvOpenErrSt = (uint8_T)(!HSPF_Motor_Open + 2U);
  if (VAR_Hspf_tStrrTemp1_s16 >= CAL_Hspf_tSwtTempSttrHiLim_f32) {
    SWC_HSPF_IG_DW.UnitDelay_DSTATE_f = true;
  } else {
    SWC_HSPF_IG_DW.UnitDelay_DSTATE_f = ((!(VAR_Hspf_tStrrTemp1_s16 <=
      CAL_Hspf_tSwtTempSttrLoLim_f32)) && SWC_HSPF_IG_DW.UnitDelay_DSTATE_f);
  }

  VAR_Hspf_bSwtTempSttr1_b = !SWC_HSPF_IG_DW.UnitDelay_DSTATE_f;
  *rty_HSPF_BUS_HSPF_uKl30Flt = HSPF_uKl30Flt;
  *rty_HSPF_BUS_HSPF_iDcLnkEstFlt = HSPF_iDcLnkEstFlt;
  *rty_HSPF_BUS_HSPF_PwrDcLnk = HSPF_PwrDcLnk;
  *rty_HSPF_BUS_HSPF_bt15 = HSPF_bt15;
  *rty_HSPF_BUS_HSPF_Crash = HSPF_Crash;
  *rty_HSPF_BUS_HSPF_INV_Open = HSPF_INV_Open;
  *rty_HSPF_BUS_HSPF_Motor_Open = HSPF_Motor_Open;
  *rty_HSPF_BUS_HSPF_uDcLnkSlowFlt = HSPF_uDcLnkSlowFlt;
  *rty_HSPF_BUS_HSPF_Wake = HSPF_Wake;
  *rty_HSPF_BUS_HSPF_iPhaUOffset = HSPF_iPhaUOffset;
  *rty_HSPF_BUS_HSPF_iPhaVOffset = HSPF_iPhaVOffset;
  *rty_HSPF_BUS_HSPF_tDBCTempUFlt = HSPF_tDBCTempUFlt;
  *rty_HSPF_BUS_HSPF_iPhaWOffset = HSPF_iPhaWOffset;
  *rty_HSPF_BUS_HSPF_stIphaOffCal = HSPF_stIphaOffCal;
  *rty_HSPF_BUS_HSPF_tStrrTempFlt = HSPF_tStrrTempFlt;
  *rty_HSPF_BUS_HSPF_tIGBTTjFlt = HSPF_tIGBTTjFlt;
  *rty_HSPF_BUS_HSPF_tCoolantTjFlt = HSPF_tCoolantTjFlt;
  *rty_HSPF_BUS_HSPF_VerMatchFailu = 0.0F;
  *rty_HSPF_BUS_HSPF_tDBCTempCmpEr = HSPF_tDBCTempCmpErrSt;
  *rty_HSPF_BUS_HSPF_MotorOpenErrS = HSPF_MotorOpenErrSt;
  *rty_HSPF_BUS_HSPF_InvOpenErrSt = HSPF_InvOpenErrSt;
  *rty_HSPF_BUS_HSPF_checkstatus = HSPF_checkstatus;
  *rty_HSPF_BUS_HSPF_tDBCTempVFlt = HSPF_tDBCTempVFlt;
  *rty_HSPF_BUS_HSPF_bSwtTempSttr1 = VAR_Hspf_bSwtTempSttr1_b;
  *rty_HSPF_BUS_HSPF_bSwtTempSttr2 = VAR_Hspf_bSwtTempSttr2_b;
  *rty_HSPF_BUS_HSPF_tDBCTempWFlt = HSPF_tDBCTempWFlt;
  *rty_HSPF_BUS_HSPF_tStrrTemp1Flt = HSPF_tStrrTemp1Flt;
  *rty_HSPF_BUS_HSPF_tStrrTemp2Flt = HSPF_tStrrTemp2Flt;
  *rty_HSPF_BUS_HSPF_nSlowFlt = HSPF_nSlowFlt;
  *rty_HSPF_BUS_HSPF_tCoolantTempF = HSPF_tCoolantTempFlt;
  *rty_HSPF_BUS_HSPF_tDrvBoardTemp = HSPF_tDrvBoardTempFlt;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE = rtb_Divide;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_m = rtb_CAL_DBCTemLow_Table_h;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_i = rtb_CAL_DBCTemLow_Table_e;
  SWC_HSPF_IG_DW.UnitDelay_DSTATE_pp = SWC_HSPF_IG_B.LogicalOperator2;
  SWC_HSPF_IG_DW.UnitDelay_DSTATE_l = VAR_Bsw_tCoolantTemp_f32;
  SWC_HSPF_IG_DW.UnitDelay1_DSTATE_n = rtb_Divide_h;
  SWC_HSPF_IG_DW.UnitDelay2_DSTATE = rtb_UnitDelay1_e;
  SWC_HSPF_IG_DW.UnitDelay3_DSTATE_f = rtb_UnitDelay2;
  SWC_HSPF_IG_DW.UnitDelay4_DSTATE = rtb_UnitDelay3_g;
  SWC_HSPF_IG_DW.UnitDelay5_DSTATE = rtb_UnitDelay4;
  SWC_HSPF_IG_DW.UnitDelay6_DSTATE = rtb_UnitDelay5;
  SWC_HSPF_IG_DW.UnitDelay7_DSTATE = rtb_UnitDelay6;
  SWC_HSPF_IG_DW.UnitDelay8_DSTATE = rtb_UnitDelay7;
}

void SWC_HSPF_IG_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_HSPF_IG_T *const SWC_HSPF_IG_M = &(SWC_HSPF_IG_MdlrefDW.rtm);
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetErrorStatusPointer(SWC_HSPF_IG_M, rt_errorStatus);
}
