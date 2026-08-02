#include "SWC_SCF_IG.h"
#include "SWC_SCF_IG_private.h"

#define SWC_SCF_IG_IN_Drv              ((uint8_T)1U)
#define SWC_SCF_IG_IN_Fault            ((uint8_T)2U)
#define SWC_SCF_IG_IN_Init             ((uint8_T)3U)
#define SWC_SCF_IG_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define SWC_SCF_IG_IN_PostDrv          ((uint8_T)4U)
#define SWC_SCF_IG_IN_PreChg           ((uint8_T)1U)
#define SWC_SCF_IG_IN_PreDrv           ((uint8_T)5U)
#define SWC_SCF_IG_IN_ShutDown         ((uint8_T)6U)
#define SWC_SCF_IG_IN_SpdCtrl          ((uint8_T)2U)
#define SWC_SCF_IG_IN_StandBy          ((uint8_T)3U)
#define SWC_SCF_IG_IN_TrqCtrl          ((uint8_T)4U)

int_T SWC_SCF_IG_GlobalTID[1];
const rtTimingBridge *SWC_SCF_IG_TimingBrdg;
uint8_T SCF_stGateDrv;
uint8_T Var_stPWMmode_AfEmrgncy_u8;
uint8_T SCF_stSysCtl;
uint8_T SCF_stPreDrvCtl;
uint8_T SCF_stSys;
uint8_T SCF_stDisChg;
uint8_T SCF_stDrvCtl;
uint8_T SCF_stModeReqToTdc;
boolean_T SCF_flginitPI;
boolean_T SCF_flgEnDchaToMc;
boolean_T SCF_flgUdcLowToTpc;
boolean_T SCF_flgDataStrgBgnToBsw;
boolean_T SCF_LwPwrDwn;
MdlrefDW_SWC_SCF_IG_T SWC_SCF_IG_MdlrefDW;
DW_SWC_SCF_IG_f_T SWC_SCF_IG_DW;
void SWC_SCF_IG_Init(void)
{
  SCF_stSysCtl = 1U;
}

void SWC_SCF_IG_Enable(void)
{
  RT_MODEL_SWC_SCF_IG_T *const SWC_SCF_IG_M = &(SWC_SCF_IG_MdlrefDW.rtm);
  SWC_SCF_IG_DW.presentTicks = rtmGetClockTick0(SWC_SCF_IG_M);
  SWC_SCF_IG_DW.previousTicks = SWC_SCF_IG_DW.presentTicks;
}

void SWC_SCF_IG_Disable(void)
{
  RT_MODEL_SWC_SCF_IG_T *const SWC_SCF_IG_M = &(SWC_SCF_IG_MdlrefDW.rtm);
  SWC_SCF_IG_DW.presentTicks = rtmGetClockTick0(SWC_SCF_IG_M);
  SWC_SCF_IG_DW.elapsedTicks = SWC_SCF_IG_DW.presentTicks -
    SWC_SCF_IG_DW.previousTicks;
  SWC_SCF_IG_DW.previousTicks = SWC_SCF_IG_DW.presentTicks;
  if (SWC_SCF_IG_DW.temporalCounter_i1 + SWC_SCF_IG_DW.elapsedTicks <= 511U) {
    SWC_SCF_IG_DW.temporalCounter_i1 = (uint16_T)
      (SWC_SCF_IG_DW.temporalCounter_i1 + SWC_SCF_IG_DW.elapsedTicks);
  } else {
    SWC_SCF_IG_DW.temporalCounter_i1 = 511U;
  }
}

void SWC_SCF_IG(const boolean_T *rtu_HSPF_BUS_HSPF_bt15, const real32_T
                *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const boolean_T
                *rtu_PDU_stMainRly, const boolean_T *rtu_PDU_stPreChgRly, const
                uint8_T *rtu_CSPF_BUS_Calc_mod_HCUReqMot, const boolean_T
                *rtu_CSPF_BUS_Calc_st_ActvDischg, const real32_T *rtu_Rdc_nWoFlt,
                const boolean_T *rtu_flg_ov, const boolean_T *rtu_flg_oc,
                boolean_T *rty_SCF_BUS_SCF_flgDataStrgBgnT, uint8_T
                *rty_SCF_BUS_SCF_stSysCtl, uint8_T *rty_SCF_BUS_SCF_stGateDrv,
                uint8_T *rty_SCF_BUS_SCF_stDrvCtl, uint8_T
                *rty_SCF_BUS_SCF_stDisChg, uint8_T *rty_SCF_BUS_SCF_stPreDrvCtl,
                boolean_T *rty_SCF_BUS_SCF_flginitPI, boolean_T
                *rty_SCF_BUS_SCF_flgEnDchaToMc, uint8_T *rty_SCF_BUS_SCF_stSys,
                uint8_T *rty_SCF_BUS_SCF_stModeReqToTdc, uint8_T
                *rty_SCF_BUS_SCF_stPwmMode, boolean_T
                *rty_SCF_BUS_SCF_flgUdcLowToTpc, boolean_T
                *rty_SCF_BUS_SCF_bHvReady_write, boolean_T
                *rty_SCF_BUS_SCF_flgEmgReqInvDch, boolean_T
                *rty_SCF_BUS_SCF_flgActvDcha, uint8_T
                *rty_SCF_BUS_SCF_stFFAction, uint8_T
                *rty_SCF_BUS_SCF_FIM_ReqFailrMod, boolean_T
                *rty_SCF_BUS_SCF_LwPwrDwn)
{
  RT_MODEL_SWC_SCF_IG_T *const SWC_SCF_IG_M = &(SWC_SCF_IG_MdlrefDW.rtm);
  boolean_T rtb_LogicalOperator2_l;
  boolean_T rtb_LogicalOperator3;
  boolean_T rtb_RelationalOperator11;
  boolean_T rtb_RelationalOperator4_o;
  rtb_RelationalOperator11 = (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt < 60.0F);
  rtb_RelationalOperator4_o = (fabsf(*rtu_Rdc_nWoFlt) >=
    CAL_TpcSmp_ThresOverSpd_f32);
  rtb_LogicalOperator3 = ((*rtu_flg_ov) || (*rtu_flg_oc) ||
    rtb_RelationalOperator4_o);
  rtb_LogicalOperator2_l = !*rtu_HSPF_BUS_HSPF_bt15;
  SWC_SCF_IG_DW.presentTicks = rtmGetClockTick0(SWC_SCF_IG_M);
  SWC_SCF_IG_DW.elapsedTicks = SWC_SCF_IG_DW.presentTicks -
    SWC_SCF_IG_DW.previousTicks;
  SWC_SCF_IG_DW.previousTicks = SWC_SCF_IG_DW.presentTicks;
  if (SWC_SCF_IG_DW.temporalCounter_i1 + SWC_SCF_IG_DW.elapsedTicks <= 511U) {
    SWC_SCF_IG_DW.temporalCounter_i1 = (uint16_T)
      (SWC_SCF_IG_DW.temporalCounter_i1 + SWC_SCF_IG_DW.elapsedTicks);
  } else {
    SWC_SCF_IG_DW.temporalCounter_i1 = 511U;
  }

  if (SWC_SCF_IG_DW.is_active_c1_SWC_SCF_IG == 0U) {
    SWC_SCF_IG_DW.is_active_c1_SWC_SCF_IG = 1U;
    SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_Init;
    SWC_SCF_IG_DW.temporalCounter_i1 = 0U;
    SCF_stSys = 0U;
    SCF_stDrvCtl = 0U;
    SCF_stPreDrvCtl = 0U;
  } else {
    switch (SWC_SCF_IG_DW.is_c1_SWC_SCF_IG) {
     case SWC_SCF_IG_IN_Drv:
      if (rtb_LogicalOperator3) {
        SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_NO_ACTIVE_CHILD;
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_Fault;
        SCF_stSys = 5U;
        SCF_stDisChg = 0U;
      } else if ((!*rtu_PDU_stMainRly) && (*rtu_CSPF_BUS_Calc_st_ActvDischg)) {
        SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_NO_ACTIVE_CHILD;
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_PostDrv;
        SCF_stSys = 6U;
        SCF_stDrvCtl = 7U;
        SCF_stPreDrvCtl = 0U;
        SCF_stDisChg = 1U;
      } else {
        switch (SWC_SCF_IG_DW.is_Drv) {
         case SWC_SCF_IG_IN_PreChg:
          SCF_stSys = 1U;
          SCF_stDrvCtl = 17U;
          SCF_stPreDrvCtl = 0U;
          if ((*rtu_PDU_stMainRly) && (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt > 300.0F))
          {
            SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_StandBy;
            SCF_stSys = 2U;
            SCF_stDrvCtl = 3U;
            SCF_stPreDrvCtl = 0U;
          }
          break;

         case SWC_SCF_IG_IN_SpdCtrl:
          SCF_stSys = 3U;
          SCF_stDrvCtl = 12U;
          SCF_stModeReqToTdc = 2U;
          SCF_stPreDrvCtl = 0U;
          if (*rtu_CSPF_BUS_Calc_mod_HCUReqMot != 2) {
            SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_StandBy;
            SCF_stSys = 2U;
            SCF_stDrvCtl = 3U;
            SCF_stPreDrvCtl = 0U;
          }
          break;

         case SWC_SCF_IG_IN_StandBy:
          SCF_stSys = 2U;
          SCF_stDrvCtl = 3U;
          SCF_stPreDrvCtl = 0U;
          if (*rtu_CSPF_BUS_Calc_mod_HCUReqMot == 1) {
            SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_TrqCtrl;
            SCF_stSys = 3U;
            SCF_stDrvCtl = 9U;
            SCF_stModeReqToTdc = 1U;
            SCF_stPreDrvCtl = 0U;
          } else {
            if (*rtu_CSPF_BUS_Calc_mod_HCUReqMot == 2) {
              SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_SpdCtrl;
              SCF_stSys = 3U;
              SCF_stDrvCtl = 12U;
              SCF_stModeReqToTdc = 2U;
              SCF_stPreDrvCtl = 0U;
            }
          }
          break;

         default:
          SCF_stSys = 3U;
          SCF_stDrvCtl = 9U;
          SCF_stModeReqToTdc = 1U;
          SCF_stPreDrvCtl = 0U;
          if (*rtu_CSPF_BUS_Calc_mod_HCUReqMot != 1) {
            SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_StandBy;
            SCF_stSys = 2U;
            SCF_stDrvCtl = 3U;
            SCF_stPreDrvCtl = 0U;
          }
          break;
        }
      }
      break;

     case SWC_SCF_IG_IN_Fault:
      SCF_stSys = 5U;
      SCF_stDisChg = 0U;
      if (rtb_RelationalOperator11 && (!rtb_LogicalOperator2_l)) {
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_ShutDown;
        SCF_stSys = 15U;
        SCF_LwPwrDwn = true;
      }
      break;

     case SWC_SCF_IG_IN_Init:
      SCF_stSys = 0U;
      SCF_stDrvCtl = 0U;
      SCF_stPreDrvCtl = 0U;
      if (rtb_LogicalOperator2_l && (SWC_SCF_IG_DW.temporalCounter_i1 >= 500U))
      {
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_PreDrv;
        SCF_stSys = 0U;
        SCF_stDrvCtl = 2U;
        SCF_stPreDrvCtl = 3U;
      }
      break;

     case SWC_SCF_IG_IN_PostDrv:
      SCF_stSys = 6U;
      SCF_stDrvCtl = 7U;
      SCF_stPreDrvCtl = 0U;
      SCF_stDisChg = 1U;
      if (rtb_LogicalOperator3) {
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_Fault;
        SCF_stSys = 5U;
        SCF_stDisChg = 0U;
      } else {
        if (rtb_RelationalOperator11) {
          SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_ShutDown;
          SCF_stSys = 15U;
          SCF_LwPwrDwn = true;
        }
      }
      break;

     case SWC_SCF_IG_IN_PreDrv:
      SCF_stSys = 0U;
      SCF_stDrvCtl = 2U;
      SCF_stPreDrvCtl = 3U;
      if (rtb_LogicalOperator3) {
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_Fault;
        SCF_stSys = 5U;
        SCF_stDisChg = 0U;
      } else if (*rtu_CSPF_BUS_Calc_st_ActvDischg) {
        SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_PostDrv;
        SCF_stSys = 6U;
        SCF_stDrvCtl = 7U;
        SCF_stPreDrvCtl = 0U;
        SCF_stDisChg = 1U;
      } else {
        if (*rtu_PDU_stPreChgRly) {
          SWC_SCF_IG_DW.is_c1_SWC_SCF_IG = SWC_SCF_IG_IN_Drv;
          SWC_SCF_IG_DW.is_Drv = SWC_SCF_IG_IN_PreChg;
          SCF_stSys = 1U;
          SCF_stDrvCtl = 17U;
          SCF_stPreDrvCtl = 0U;
        }
      }
      break;

     default:
      SCF_stSys = 15U;
      SCF_LwPwrDwn = true;
      break;
    }
  }

  rtb_RelationalOperator11 = ((SCF_stSys == 5) && rtb_RelationalOperator4_o);
  rtb_RelationalOperator4_o = ((SCF_stSys == 3) || (SCF_stSys == 6));
  if (rtb_RelationalOperator11) {
    SCF_stGateDrv = 1U;
  } else if (rtb_RelationalOperator4_o) {
    SCF_stGateDrv = 3U;
  } else {
    SCF_stGateDrv = 0U;
  }

  SCF_flginitPI = !rtb_RelationalOperator4_o;
  SCF_flgEnDchaToMc = (SCF_stDrvCtl == 7);
  SCF_flgUdcLowToTpc = (((SCF_stSys == 0) || (SCF_stSys == 1)) &&
                        (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt < 350.0F));
  *rty_SCF_BUS_SCF_flgDataStrgBgnT = SCF_flgDataStrgBgnToBsw;
  *rty_SCF_BUS_SCF_stModeReqToTdc = SCF_stModeReqToTdc;
  *rty_SCF_BUS_SCF_stPwmMode = SCF_stGateDrv;
  *rty_SCF_BUS_SCF_flgUdcLowToTpc = SCF_flgUdcLowToTpc;
  *rty_SCF_BUS_SCF_bHvReady_write = false;
  *rty_SCF_BUS_SCF_flgEmgReqInvDch = false;
  *rty_SCF_BUS_SCF_flgActvDcha = false;
  *rty_SCF_BUS_SCF_stFFAction = 0U;
  *rty_SCF_BUS_SCF_FIM_ReqFailrMod = 0U;
  *rty_SCF_BUS_SCF_LwPwrDwn = SCF_LwPwrDwn;
  *rty_SCF_BUS_SCF_stSysCtl = SCF_stSysCtl;
  *rty_SCF_BUS_SCF_stGateDrv = SCF_stGateDrv;
  *rty_SCF_BUS_SCF_stDrvCtl = SCF_stDrvCtl;
  *rty_SCF_BUS_SCF_stDisChg = SCF_stDisChg;
  *rty_SCF_BUS_SCF_stPreDrvCtl = SCF_stPreDrvCtl;
  *rty_SCF_BUS_SCF_flginitPI = SCF_flginitPI;
  *rty_SCF_BUS_SCF_flgEnDchaToMc = SCF_flgEnDchaToMc;
  *rty_SCF_BUS_SCF_stSys = SCF_stSys;
  if ((SCF_stSys == 5) && (*rtu_flg_ov)) {
    Var_stPWMmode_AfEmrgncy_u8 = 1U;
  } else {
    rtb_RelationalOperator11 = (((SCF_stSys == 5) && (*rtu_flg_oc)) ||
      rtb_RelationalOperator11);
    if (rtb_RelationalOperator11 && (*rtu_Rdc_nWoFlt >= 6000.0F)) {
      Var_stPWMmode_AfEmrgncy_u8 = 1U;
    } else if (rtb_RelationalOperator11 && (*rtu_Rdc_nWoFlt < 6000.0F)) {
      Var_stPWMmode_AfEmrgncy_u8 = 0U;
    } else {
      Var_stPWMmode_AfEmrgncy_u8 = 2U;
    }
  }
}

void SWC_SCF_IG_initialize(const char_T **rt_errorStatus, const rtTimingBridge
  *timingBridge, int_T mdlref_TID0, int_T mdlref_TriggerTID)
{
  RT_MODEL_SWC_SCF_IG_T *const SWC_SCF_IG_M = &(SWC_SCF_IG_MdlrefDW.rtm);
  SWC_SCF_IG_GlobalTID[0] = mdlref_TID0;
  SWC_SCF_IG_M->Timing.mdlref_TriggerTID = mdlref_TriggerTID;
  SWC_SCF_IG_TimingBrdg = timingBridge;
  rtmSetErrorStatusPointer(SWC_SCF_IG_M, rt_errorStatus);
}
