#include "SWC_SCF_IG_FQ.h"
#include "SWC_SCF_IG_FQ_private.h"

#define SWC_SCF_IG_FQ_IN_Action        ((uint8_T)1U)
#define SWC_SCF_IG_FQ_IN_AlignStage    ((uint8_T)1U)
#define SWC_SCF_IG_FQ_IN_Drv           ((uint8_T)1U)
#define SWC_SCF_IG_FQ_IN_Fault         ((uint8_T)2U)
#define SWC_SCF_IG_FQ_IN_Init          ((uint8_T)3U)
#define SWC_SCF_IG_FQ_IN_OpenStage     ((uint8_T)2U)
#define SWC_SCF_IG_FQ_IN_PostDrv       ((uint8_T)4U)
#define SWC_SCF_IG_FQ_IN_PreChg        ((uint8_T)2U)
#define SWC_SCF_IG_FQ_IN_PreDrv        ((uint8_T)5U)
#define SWC_SCF_IG_FQ_IN_RunStage      ((uint8_T)3U)
#define SWC_SCF_IG_FQ_IN_ShutDown      ((uint8_T)6U)
#define SWC_SCF_IG_FQ_IN_StandBy       ((uint8_T)3U)
#define SWC_SCF_IG_FQ_IN_ThetaAlign    ((uint8_T)4U)
#define SWC_SCF_IG_F_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

int_T SWC_SCF_IG_FQ_GlobalTID[1];
const rtTimingBridge *SWC_SCF_IG_FQ_TimingBrdg;
uint8_T SCF_stGateDrv_FQ;
uint8_T Var_stPWMmode_AfEmrgncy_u8_FQ;
uint8_T SCF_stSysCtl_FQ;
uint8_T SCF_stPreDrvCtl_FQ;
uint8_T SCF_stSys_FQ;
uint8_T SCF_stDisChg_FQ;
uint8_T SCF_stDrvCtl_FQ;
uint8_T SCF_stModeReqToTdc_FQ;
uint8_T SCF_stMotor_state_FQ;
boolean_T SCF_flginitPI_FQ;
boolean_T SCF_flgUdcLowToTpc_FQ;
boolean_T Var_flgEnMosSwitch_b_FQ;
boolean_T SCF_flgDataStrgBgnToBsw_FQ;
boolean_T SCF_flgEnDchaToMc_FQ;
boolean_T SCF_LwPwrDwn_FQ;
MdlrefDW_SWC_SCF_IG_FQ_T SWC_SCF_IG_FQ_MdlrefDW;
B_SWC_SCF_IG_FQ_c_T SWC_SCF_IG_FQ_B;
DW_SWC_SCF_IG_FQ_f_T SWC_SCF_IG_FQ_DW;
void SWC_SCF_IG_FQ_Init(void)
{
  SCF_stSysCtl_FQ = 1U;
}

void SWC_SCF_IG_FQ_Enable(void)
{
  RT_MODEL_SWC_SCF_IG_FQ_T *const SWC_SCF_IG_FQ_M = &(SWC_SCF_IG_FQ_MdlrefDW.rtm);
  SWC_SCF_IG_FQ_DW.presentTicks = rtmGetClockTick0(SWC_SCF_IG_FQ_M);
  SWC_SCF_IG_FQ_DW.previousTicks = SWC_SCF_IG_FQ_DW.presentTicks;
}

void SWC_SCF_IG_FQ_Disable(void)
{
  RT_MODEL_SWC_SCF_IG_FQ_T *const SWC_SCF_IG_FQ_M = &(SWC_SCF_IG_FQ_MdlrefDW.rtm);
  SWC_SCF_IG_FQ_DW.presentTicks = rtmGetClockTick0(SWC_SCF_IG_FQ_M);
  SWC_SCF_IG_FQ_DW.elapsedTicks = SWC_SCF_IG_FQ_DW.presentTicks -
    SWC_SCF_IG_FQ_DW.previousTicks;
  SWC_SCF_IG_FQ_DW.previousTicks = SWC_SCF_IG_FQ_DW.presentTicks;
  if (SWC_SCF_IG_FQ_DW.temporalCounter_i2 + SWC_SCF_IG_FQ_DW.elapsedTicks <=
      511U) {
    SWC_SCF_IG_FQ_DW.temporalCounter_i2 = (uint16_T)
      (SWC_SCF_IG_FQ_DW.temporalCounter_i2 + SWC_SCF_IG_FQ_DW.elapsedTicks);
  } else {
    SWC_SCF_IG_FQ_DW.temporalCounter_i2 = 511U;
  }
}

void SWC_SCF_IG_FQ(const boolean_T *rtu_HSPF_BUS_HSPF_bt15, const real32_T
                   *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const boolean_T
                   *rtu_PDU_stMainRly, const boolean_T *rtu_PDU_stPreChgRly,
                   const real32_T *rtu_Rdc_nWoFlt, const boolean_T *rtu_flg_ov,
                   const boolean_T *rtu_flg_oc, boolean_T
                   *rty_SCF_BUS_SCF_flgDataStrgBgnT, uint8_T
                   *rty_SCF_BUS_SCF_stSysCtl, uint8_T *rty_SCF_BUS_SCF_stGateDrv,
                   uint8_T *rty_SCF_BUS_SCF_stDrvCtl, uint8_T
                   *rty_SCF_BUS_SCF_stDisChg, uint8_T
                   *rty_SCF_BUS_SCF_stPreDrvCtl, boolean_T
                   *rty_SCF_BUS_SCF_flginitPI, boolean_T
                   *rty_SCF_BUS_SCF_flgEnDchaToMc, uint8_T
                   *rty_SCF_BUS_SCF_stSys, uint8_T
                   *rty_SCF_BUS_SCF_stModeReqToTdc, uint8_T
                   *rty_SCF_BUS_SCF_stPwmMode, boolean_T
                   *rty_SCF_BUS_SCF_flgUdcLowToTpc, boolean_T
                   *rty_SCF_BUS_SCF_bHvReady_write, boolean_T
                   *rty_SCF_BUS_SCF_flgEmgReqInvDch, boolean_T
                   *rty_SCF_BUS_SCF_flgActvDcha, uint8_T
                   *rty_SCF_BUS_SCF_stFFAction, uint8_T
                   *rty_SCF_BUS_SCF_FIM_ReqFailrMod, boolean_T
                   *rty_SCF_BUS_SCF_LwPwrDwn, uint8_T
                   *rty_SCF_BUS_SCF_stMotor_state, uint8_T
                   *rty_SCF_BUS_SCF_flginitEn_Nctl, uint8_T
                   *rty_SCF_BUS_SCF_flgZReset)
{
  RT_MODEL_SWC_SCF_IG_FQ_T *const SWC_SCF_IG_FQ_M = &(SWC_SCF_IG_FQ_MdlrefDW.rtm);
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator3;
  boolean_T rtb_RelationalOperator11;
  boolean_T rtb_RelationalOperator4;
  boolean_T rtb_RelationalOperator4_o;
  rtb_RelationalOperator11 = (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt < 60.0F);
  rtb_LogicalOperator = !*rtu_HSPF_BUS_HSPF_bt15;
  rtb_RelationalOperator4 = !rtb_LogicalOperator;
  rtb_RelationalOperator4_o = (fabsf(*rtu_Rdc_nWoFlt) >=
    CAL_TpcSmp_ThresOverSpd_f32_FQ);
  rtb_LogicalOperator3 = ((*rtu_flg_ov) || (*rtu_flg_oc) ||
    rtb_RelationalOperator4_o);
  SWC_SCF_IG_FQ_DW.presentTicks = rtmGetClockTick0(SWC_SCF_IG_FQ_M);
  SWC_SCF_IG_FQ_DW.elapsedTicks = SWC_SCF_IG_FQ_DW.presentTicks -
    SWC_SCF_IG_FQ_DW.previousTicks;
  SWC_SCF_IG_FQ_DW.previousTicks = SWC_SCF_IG_FQ_DW.presentTicks;
  if (SWC_SCF_IG_FQ_DW.temporalCounter_i2 + SWC_SCF_IG_FQ_DW.elapsedTicks <=
      511U) {
    SWC_SCF_IG_FQ_DW.temporalCounter_i2 = (uint16_T)
      (SWC_SCF_IG_FQ_DW.temporalCounter_i2 + SWC_SCF_IG_FQ_DW.elapsedTicks);
  } else {
    SWC_SCF_IG_FQ_DW.temporalCounter_i2 = 511U;
  }

  if (SWC_SCF_IG_FQ_DW.temporalCounter_i1 < 32767U) {
    SWC_SCF_IG_FQ_DW.temporalCounter_i1++;
  }

  if (SWC_SCF_IG_FQ_DW.is_active_c1_SWC_SCF_IG_FQ == 0U) {
    SWC_SCF_IG_FQ_DW.is_active_c1_SWC_SCF_IG_FQ = 1U;
    SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_Init;
    SWC_SCF_IG_FQ_DW.temporalCounter_i2 = 0U;
    SCF_stSys_FQ = 0U;
    SCF_stDrvCtl_FQ = 0U;
    SCF_stPreDrvCtl_FQ = 0U;
  } else {
    switch (SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ) {
     case SWC_SCF_IG_FQ_IN_Drv:
      if (rtb_LogicalOperator3) {
        SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_F_IN_NO_ACTIVE_CHILD;
        SWC_SCF_IG_FQ_DW.is_Drv = SWC_SCF_IG_F_IN_NO_ACTIVE_CHILD;
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_Fault;
        SCF_stSys_FQ = 5U;
        SCF_stDisChg_FQ = 0U;
      } else if (!*rtu_PDU_stMainRly) {
        SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_F_IN_NO_ACTIVE_CHILD;
        SWC_SCF_IG_FQ_DW.is_Drv = SWC_SCF_IG_F_IN_NO_ACTIVE_CHILD;
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_PostDrv;
        SCF_stSys_FQ = 6U;
        SCF_stDrvCtl_FQ = 7U;
        SCF_stPreDrvCtl_FQ = 0U;
        SCF_stDisChg_FQ = 0U;
      } else {
        switch (SWC_SCF_IG_FQ_DW.is_Drv) {
         case SWC_SCF_IG_FQ_IN_Action:
          if (CAL_SCF_stModeReq_b_FQ != 1) {
            SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_F_IN_NO_ACTIVE_CHILD;
            SWC_SCF_IG_FQ_DW.is_Drv = SWC_SCF_IG_FQ_IN_StandBy;
            SCF_stSys_FQ = 2U;
            SCF_stDrvCtl_FQ = 3U;
            SCF_stPreDrvCtl_FQ = 0U;
          } else {
            switch (SWC_SCF_IG_FQ_DW.is_Action) {
             case SWC_SCF_IG_FQ_IN_AlignStage:
              if (SWC_SCF_IG_FQ_DW.temporalCounter_i1 >= 8000) {
                SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_FQ_IN_OpenStage;
                SWC_SCF_IG_FQ_DW.temporalCounter_i1 = 0U;
                SWC_SCF_IG_FQ_B.ZReset = 0U;
                SWC_SCF_IG_FQ_DW.cnt = 0U;
              } else {
                SCF_stMotor_state_FQ = 2U;
                SWC_SCF_IG_FQ_B.RestsSingal = 1U;
              }
              break;

             case SWC_SCF_IG_FQ_IN_OpenStage:
              if (SWC_SCF_IG_FQ_DW.temporalCounter_i1 >= 30000) {
                SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_FQ_IN_ThetaAlign;
                SWC_SCF_IG_FQ_DW.temporalCounter_i1 = 0U;
              } else {
                if (SWC_SCF_IG_FQ_DW.cnt == 1) {
                  SWC_SCF_IG_FQ_B.ZReset = 1U;
                }

                SWC_SCF_IG_FQ_DW.cnt = 1U;
                SCF_stMotor_state_FQ = 3U;
                SWC_SCF_IG_FQ_B.RestsSingal = 1U;
              }
              break;

             case SWC_SCF_IG_FQ_IN_RunStage:
              SCF_stSys_FQ = 3U;
              SCF_stDrvCtl_FQ = 12U;
              SCF_stModeReqToTdc_FQ = 2U;
              SCF_stPreDrvCtl_FQ = 0U;
              SCF_stMotor_state_FQ = 5U;
              SWC_SCF_IG_FQ_B.RestsSingal = 0U;
              break;

             default:
              if (SWC_SCF_IG_FQ_DW.temporalCounter_i1 >= 5000) {
                SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_FQ_IN_RunStage;
                SCF_stSys_FQ = 3U;
                SCF_stDrvCtl_FQ = 12U;
                SCF_stModeReqToTdc_FQ = 2U;
                SCF_stPreDrvCtl_FQ = 0U;
              } else {
                SCF_stMotor_state_FQ = 4U;
                SWC_SCF_IG_FQ_B.RestsSingal = 1U;
              }
              break;
            }
          }
          break;

         case SWC_SCF_IG_FQ_IN_PreChg:
          SCF_stSys_FQ = 1U;
          SCF_stDrvCtl_FQ = 17U;
          SCF_stPreDrvCtl_FQ = 0U;
          if (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt > 520.0F) {
            SWC_SCF_IG_FQ_DW.is_Drv = SWC_SCF_IG_FQ_IN_StandBy;
            SCF_stSys_FQ = 2U;
            SCF_stDrvCtl_FQ = 3U;
            SCF_stPreDrvCtl_FQ = 0U;
          }
          break;

         default:
          SCF_stSys_FQ = 2U;
          SCF_stDrvCtl_FQ = 3U;
          SCF_stPreDrvCtl_FQ = 0U;
          if (CAL_SCF_stModeReq_b_FQ == 1) {
            SWC_SCF_IG_FQ_DW.is_Drv = SWC_SCF_IG_FQ_IN_Action;
            SWC_SCF_IG_FQ_DW.is_Action = SWC_SCF_IG_FQ_IN_AlignStage;
            SWC_SCF_IG_FQ_DW.temporalCounter_i1 = 0U;
          } else {
            SCF_stMotor_state_FQ = 1U;
            SWC_SCF_IG_FQ_B.RestsSingal = 0U;
          }
          break;
        }
      }
      break;

     case SWC_SCF_IG_FQ_IN_Fault:
      SCF_stSys_FQ = 5U;
      SCF_stDisChg_FQ = 0U;
      if (rtb_RelationalOperator11 && rtb_RelationalOperator4) {
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_ShutDown;
        SCF_stSys_FQ = 15U;
        SCF_LwPwrDwn_FQ = true;
      }
      break;

     case SWC_SCF_IG_FQ_IN_Init:
      SCF_stSys_FQ = 0U;
      SCF_stDrvCtl_FQ = 0U;
      SCF_stPreDrvCtl_FQ = 0U;
      if (rtb_LogicalOperator && (SWC_SCF_IG_FQ_DW.temporalCounter_i2 >= 500U))
      {
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_PreDrv;
        SCF_stSys_FQ = 0U;
        SCF_stDrvCtl_FQ = 2U;
        SCF_stPreDrvCtl_FQ = 3U;
      }
      break;

     case SWC_SCF_IG_FQ_IN_PostDrv:
      SCF_stSys_FQ = 6U;
      SCF_stDrvCtl_FQ = 7U;
      SCF_stPreDrvCtl_FQ = 0U;
      SCF_stDisChg_FQ = 0U;
      if (rtb_LogicalOperator3) {
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_Fault;
        SCF_stSys_FQ = 5U;
        SCF_stDisChg_FQ = 0U;
      } else {
        if (rtb_RelationalOperator11) {
          SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_ShutDown;
          SCF_stSys_FQ = 15U;
          SCF_LwPwrDwn_FQ = true;
        }
      }
      break;

     case SWC_SCF_IG_FQ_IN_PreDrv:
      SCF_stSys_FQ = 0U;
      SCF_stDrvCtl_FQ = 2U;
      SCF_stPreDrvCtl_FQ = 3U;
      if (rtb_LogicalOperator3) {
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_Fault;
        SCF_stSys_FQ = 5U;
        SCF_stDisChg_FQ = 0U;
      } else if (rtb_RelationalOperator4) {
        SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_PostDrv;
        SCF_stSys_FQ = 6U;
        SCF_stDrvCtl_FQ = 7U;
        SCF_stPreDrvCtl_FQ = 0U;
        SCF_stDisChg_FQ = 0U;
      } else {
        if (*rtu_PDU_stPreChgRly) {
          SWC_SCF_IG_FQ_DW.is_c1_SWC_SCF_IG_FQ = SWC_SCF_IG_FQ_IN_Drv;
          SWC_SCF_IG_FQ_DW.is_Drv = SWC_SCF_IG_FQ_IN_PreChg;
          SCF_stSys_FQ = 1U;
          SCF_stDrvCtl_FQ = 17U;
          SCF_stPreDrvCtl_FQ = 0U;
        }
      }
      break;

     default:
      SCF_stSys_FQ = 15U;
      SCF_LwPwrDwn_FQ = true;
      break;
    }
  }

  rtb_LogicalOperator = ((SCF_stSys_FQ == 3) || (SCF_stSys_FQ == 6));
  if (rtb_LogicalOperator) {
    SCF_stGateDrv_FQ = 3U;
  } else {
    SCF_stGateDrv_FQ = 0U;
  }

  SCF_flginitPI_FQ = !rtb_LogicalOperator;
  SCF_flgUdcLowToTpc_FQ = (((SCF_stSys_FQ == 0) || (SCF_stSys_FQ == 1)) &&
    (*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt < 350.0F));
  *rty_SCF_BUS_SCF_flgDataStrgBgnT = SCF_flgDataStrgBgnToBsw_FQ;
  *rty_SCF_BUS_SCF_stModeReqToTdc = SCF_stModeReqToTdc_FQ;
  *rty_SCF_BUS_SCF_stPwmMode = SCF_stGateDrv_FQ;
  *rty_SCF_BUS_SCF_flgUdcLowToTpc = SCF_flgUdcLowToTpc_FQ;
  *rty_SCF_BUS_SCF_bHvReady_write = false;
  *rty_SCF_BUS_SCF_flgEmgReqInvDch = false;
  *rty_SCF_BUS_SCF_flgActvDcha = false;
  *rty_SCF_BUS_SCF_stFFAction = 0U;
  *rty_SCF_BUS_SCF_FIM_ReqFailrMod = 0U;
  *rty_SCF_BUS_SCF_LwPwrDwn = SCF_LwPwrDwn_FQ;
  *rty_SCF_BUS_SCF_stMotor_state = SCF_stMotor_state_FQ;
  *rty_SCF_BUS_SCF_stSysCtl = SCF_stSysCtl_FQ;
  *rty_SCF_BUS_SCF_flginitEn_Nctl = SWC_SCF_IG_FQ_B.RestsSingal;
  *rty_SCF_BUS_SCF_flgZReset = SWC_SCF_IG_FQ_B.ZReset;
  *rty_SCF_BUS_SCF_stGateDrv = SCF_stGateDrv_FQ;
  *rty_SCF_BUS_SCF_stDrvCtl = SCF_stDrvCtl_FQ;
  *rty_SCF_BUS_SCF_stDisChg = SCF_stDisChg_FQ;
  *rty_SCF_BUS_SCF_stPreDrvCtl = SCF_stPreDrvCtl_FQ;
  *rty_SCF_BUS_SCF_flginitPI = SCF_flginitPI_FQ;
  *rty_SCF_BUS_SCF_flgEnDchaToMc = SCF_flgEnDchaToMc_FQ;
  *rty_SCF_BUS_SCF_stSys = SCF_stSys_FQ;
  if ((SCF_stSys_FQ == 5) && (*rtu_flg_ov)) {
    Var_stPWMmode_AfEmrgncy_u8_FQ = 1U;
  } else {
    rtb_RelationalOperator4_o = (((SCF_stSys_FQ == 5) && (*rtu_flg_oc)) ||
      ((SCF_stSys_FQ == 5) && rtb_RelationalOperator4_o));
    if (rtb_RelationalOperator4_o && (*rtu_Rdc_nWoFlt >= 6000.0F)) {
      Var_stPWMmode_AfEmrgncy_u8_FQ = 1U;
    } else if (rtb_RelationalOperator4_o && (*rtu_Rdc_nWoFlt < 6000.0F)) {
      Var_stPWMmode_AfEmrgncy_u8_FQ = 0U;
    } else {
      Var_stPWMmode_AfEmrgncy_u8_FQ = 2U;
    }
  }

  Var_flgEnMosSwitch_b_FQ = (SCF_stDrvCtl_FQ == 7);
}

void SWC_SCF_IG_FQ_initialize(const char_T **rt_errorStatus, const
  rtTimingBridge *timingBridge, int_T mdlref_TID0, int_T mdlref_TriggerTID)
{
  RT_MODEL_SWC_SCF_IG_FQ_T *const SWC_SCF_IG_FQ_M = &(SWC_SCF_IG_FQ_MdlrefDW.rtm);
  SWC_SCF_IG_FQ_GlobalTID[0] = mdlref_TID0;
  SWC_SCF_IG_FQ_M->Timing.mdlref_TriggerTID = mdlref_TriggerTID;
  SWC_SCF_IG_FQ_TimingBrdg = timingBridge;
  rtmSetErrorStatusPointer(SWC_SCF_IG_FQ_M, rt_errorStatus);
}
