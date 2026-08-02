/*
 * File: SWC_MDF_IG.c
 *
 * Code generated for Simulink model 'SWC_MDF_IG'.
 *
 * Model version                  : 2.33
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri Oct 10 08:12:51 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "SWC_MDF_IG.h"
#include "SWC_MDF_IG_private.h"
#include "look1_iflf_binlxpw.h"

/* Exported block signals */
real32_T VAR_MDF_OffSetSiteAObs_f32;   /* '<S15>/Abs' */
real32_T VAR_MDF_OffSetSiteBObs_f32;   /* '<S15>/Abs1' */
real32_T VAR_MDF_offsetDeltaObs_f32;   /* '<S15>/Add2' */
real32_T VAR_MDF_3PhaUnbalanceObs_f32; /* '<S34>/Divide' */
real32_T VAR_MDF_offsetDeltaFlt_f32;   /* '<S18>/Abs1' */
uint8_T VAR_MDF_PhaseFaultState_u8;    /* '<Root>/Constant3' */
uint8_T VAR_MDF_AlOfsNoPlausState_u8;  /* '<Root>/Constant6' */
uint8_T VAR_MDF_EmacBlkdState_u8;      /* '<Root>/Constant1' */
uint8_T VAR_MDF_PrfElDrvState_u8;      /* '<Root>/Constant4' */
uint8_T VAR_MDF_ICtlRatState_u8;       /* '<Root>/Constant5' */
uint8_T VAR_MDF_OpenCirNoPsblState_u8; /* '<Root>/Constant7' */
uint8_T VAR_MDF_DiashCirNoPsblState_u8;/* '<Root>/Constant8' */
uint8_T VAR_MDF_OperOutdRngState_u8;   /* '<Root>/Constant9' */
boolean_T VAR_MDF_PhaseFaultChk_b;     /* '<S28>/Logical Operator1' */
boolean_T VAR_MDF_bAlOfsChk_b;         /* '<S16>/Logical Operator1' */
boolean_T VAR_MDF_bPhaseFault_b;       /* '<S30>/Logical Operator1' */
boolean_T VAR_MDF_bIsOvHiFault_b;      /* '<S27>/Relational Operator' */
boolean_T VAR_MDF_bAlfOfsNoPlauseFault_b;/* '<S17>/Logical Operator1' */
MdlrefDW_SWC_MDF_IG_T SWC_MDF_IG_MdlrefDW;

/* Block signals (default storage) */
B_SWC_MDF_IG_c_T SWC_MDF_IG_B;

/* Block states (default storage) */
DW_SWC_MDF_IG_f_T SWC_MDF_IG_DW;

/* Disable for referenced model: 'SWC_MDF_IG' */
void SWC_MDF_IG_Disable(void)
{
  /* Disable for Enabled SubSystem: '<S10>/PhaseFaultCalc' */
  if (SWC_MDF_IG_DW.PhaseFaultCalc_MODE) {
    /* Disable for Logic: '<S30>/Logical Operator1' incorporates:
     *  Outport: '<S29>/MDF_bPhaseFault'
     */
    VAR_MDF_bPhaseFault_b = false;
    SWC_MDF_IG_DW.PhaseFaultCalc_MODE = false;
  }

  /* End of Disable for SubSystem: '<S10>/PhaseFaultCalc' */
}

/* Output and update for referenced model: 'SWC_MDF_IG' */
void SWC_MDF_IG(const real32_T *rtu_HSPF_BUS_HSPF_nSlowFlt, const real32_T
                *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const real32_T
                *rtu_MCF_BUS_MCF_udDes, const real32_T *rtu_MCF_BUS_MCF_uqDes,
                const real32_T *rtu_MCF_BUS_MCF_dtPwm, const real32_T
                *rtu_MCF_BUS_MCF_iU, const real32_T *rtu_MCF_BUS_MCF_iV, const
                real32_T *rtu_MCF_BUS_MCF_iW, const real32_T *rtu_MPC_BUS_MPC_Lq,
                const real32_T *rtu_MPC_BUS_MPC_Rs, const real32_T
                *rtu_MPC_BUS_MPC_psiExc, const real32_T *rtu_MPC_BUS_MPC_IsFlt,
                const real32_T *rtu_MPC_BUS_MPC_idActFlt, const real32_T
                *rtu_MPC_BUS_MPC_iqActFlt, const real32_T *rtu_Rdc_nWoFlt, const
                uint8_T *rtu_SCF_BUS_SCF_stGateDrv, const uint8_T
                *rtu_SCF_BUS_SCF_stDrvCtl, uint8_T *rty_MDF_BUS_MDF_stFrwhl,
                uint8_T *rty_MDF_BUS_MDF_bFaultEMBlkWarn, uint8_T
                *rty_MDF_BUS_MDF_bFaultEMBlkErrS, uint8_T
                *rty_MDF_BUS_MDF_bFaultPwrCmpSt, uint8_T
                *rty_MDF_BUS_MDF_bPhaseFaultSt, uint8_T
                *rty_MDF_BUS_MDF_bAlfOfsNoPlause, uint8_T
                *rty_MDF_BUS_MDF_bFaultICtlChkSt, uint8_T
                *rty_MDF_BUS_MDF_bOpenCirNoPsblF, uint8_T
                *rty_MDF_BUS_MDF_bShCirNoPsblFau, uint8_T
                *rty_MDF_BUS_MDF_flagOperOutdRng, uint8_T
                *rty_MDF_BUS_MDF_IsOvHiErrSt)
{
  real32_T rtb_Abs_o0;
  real32_T rtb_Abs_p;
  real32_T rtb_Add;
  real32_T rtb_Add_br;
  real32_T rtb_Add_e;
  real32_T rtb_Product;
  real32_T rtb_Product_a;
  real32_T rtb_Switch1;
  real32_T rtb_UnitDelay;
  real32_T rtb_UnitDelay1_e;
  real32_T rtb_UnitDelay1_g;
  real32_T rtb_UnitDelay1_l;
  real32_T rtb_UnitDelay2;
  real32_T rtb_UnitDelay2_j;
  real32_T rtb_UnitDelay2_o;
  real32_T rtb_UnitDelay_c;
  real32_T rtb_UnitDelay_l;
  uint8_T rtb_Gain3;
  boolean_T rtb_RelationalOperator1_e;
  boolean_T rtb_RelationalOperator_p;
  iEDS_Enum_stDrvCtl_def rtb_DataTypeConversion1;

  /* Outputs for Enabled SubSystem: '<S7>/Subsystem' incorporates:
   *  EnablePort: '<S27>/Enable'
   */
  /* RelationalOperator: '<S27>/Relational Operator' incorporates:
   *  Constant: '<S27>/CAL_MDF_IsMaxSet_f32'
   */
  VAR_MDF_bIsOvHiFault_b = (*rtu_MPC_BUS_MPC_IsFlt > CAL_MDF_IsMaxSet_f32);

  /* Logic: '<S27>/Logical Operator' incorporates:
   *  UnitDelay: '<S27>/Unit Delay'
   */
  SWC_MDF_IG_DW.UnitDelay_DSTATE_d = (VAR_MDF_bIsOvHiFault_b ||
    SWC_MDF_IG_DW.UnitDelay_DSTATE_d);

  /* Switch: '<S27>/Switch1' incorporates:
   *  UnitDelay: '<S27>/Unit Delay'
   */
  if (SWC_MDF_IG_DW.UnitDelay_DSTATE_d) {
    /* Switch: '<S27>/Switch1' incorporates:
     *  Constant: '<S27>/Constant5'
     */
    SWC_MDF_IG_B.Switch1_j = 3U;
  } else {
    /* Switch: '<S27>/Switch1' incorporates:
     *  Constant: '<S27>/Constant6'
     */
    SWC_MDF_IG_B.Switch1_j = 2U;
  }

  /* End of Switch: '<S27>/Switch1' */
  /* End of Outputs for SubSystem: '<S7>/Subsystem' */

  /* Product: '<S37>/Product' incorporates:
   *  Constant: '<S37>/MDF_GLB_pi_f32'
   *  Constant: '<S3>/MDF_GLB_MotorPole_u8'
   *  Gain: '<S37>/1//60*2'
   */
  rtb_Product = 0.0333333351F * *rtu_HSPF_BUS_HSPF_nSlowFlt * MDF_GLB_pi_f32 *
    (real32_T)((uint8_T)MDF_GLB_MotorPole_u8) * *rtu_MPC_BUS_MPC_psiExc;

  /* Sum: '<S37>/Add' incorporates:
   *  Constant: '<S37>/MDF_GLB_pi_f32'
   *  Gain: '<S37>/1//(3*sqrt(6))'
   *  Product: '<S37>/Product5'
   */
  rtb_Add = rtb_Product - *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt * MDF_GLB_pi_f32 *
    0.136082768F;

  /* Switch: '<S37>/Switch1' incorporates:
   *  Constant: '<S37>/CAL_MDF_UdcFwMin_f32'
   *  Constant: '<S37>/CAL_MDF_stFrwhlWoIs_u8'
   *  Constant: '<S37>/Constant'
   *  Logic: '<S37>/Logical Operator1'
   *  RelationalOperator: '<S37>/Relational Operator2'
   *  RelationalOperator: '<S37>/Relational Operator4'
   *  UnitDelay: '<S37>/Unit Delay'
   */
  if ((*rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt < CAL_MDF_UdcFwMin_f32) || (rtb_Add <
       0.0F)) {
    SWC_MDF_IG_DW.UnitDelay_DSTATE_n = CAL_MDF_stFrwhlWoIs_u8;
  } else {
    /* Sum: '<S37>/Add1' incorporates:
     *  Constant: '<S37>/CAL_MDF_UsFrwhlMax_f32'
     */
    rtb_Product -= CAL_MDF_UsFrwhlMax_f32;

    /* Switch: '<S37>/Switch' incorporates:
     *  Logic: '<S37>/Logical Operator'
     *  RelationalOperator: '<S37>/Relational Operator'
     *  RelationalOperator: '<S37>/Relational Operator1'
     *  RelationalOperator: '<S37>/Relational Operator3'
     *  Switch: '<S37>/Switch2'
     */
    if ((rtb_Add > 0.0F) && (rtb_Product < 0.0F)) {
      /* UnitDelay: '<S37>/Unit Delay' incorporates:
       *  Constant: '<S37>/CAL_MDF_stFrwhlWiIs_u8'
       */
      SWC_MDF_IG_DW.UnitDelay_DSTATE_n = CAL_MDF_stFrwhlWiIs_u8;
    } else {
      if (rtb_Product >= 0.0F) {
        /* Switch: '<S37>/Switch2' incorporates:
         *  Constant: '<S37>/CAL_MDF_stFrwhlPhd_u8'
         *  UnitDelay: '<S37>/Unit Delay'
         */
        SWC_MDF_IG_DW.UnitDelay_DSTATE_n = CAL_MDF_stFrwhlPhd_u8;
      }
    }

    /* End of Switch: '<S37>/Switch' */
  }

  /* End of Switch: '<S37>/Switch1' */

  /* Constant: '<Root>/Constant3' */
  VAR_MDF_PhaseFaultState_u8 = 0U;

  /* Abs: '<S2>/Abs' */
  rtb_Add = fabsf(*rtu_Rdc_nWoFlt);

  /* Logic: '<S28>/Logical Operator1' incorporates:
   *  Abs: '<S2>/Abs'
   *  Constant: '<S28>/CAL_MDF_IsPhaseFault_f32'
   *  Constant: '<S28>/CAL_MDF_nAbsPhaseFault_f32'
   *  Constant: '<S28>/MDF_GLB_IGBTrun_u8'
   *  DataTypeConversion: '<S28>/Data Type Conversion'
   *  Logic: '<S28>/Logical Operator'
   *  Lookup_n-D: '<S28>/1-D Lookup Table'
   *  RelationalOperator: '<S28>/Relational Operator'
   *  RelationalOperator: '<S28>/Relational Operator1'
   *  RelationalOperator: '<S28>/Relational Operator2'
   */
  VAR_MDF_PhaseFaultChk_b = ((VAR_MDF_PhaseFaultState_u8 != 0) &&
    (*rtu_SCF_BUS_SCF_stGateDrv == ((uint8_T)MDF_GLB_IGBTrun_u8)) &&
    (*rtu_MPC_BUS_MPC_IsFlt > CAL_MDF_IsPhaseFault_f32) && ((look1_iflf_binlxpw
    (rtb_Add, ((const real32_T *)&(CAL_MDF_nAbsPhaseFault_X_af32[0])), ((const
    real32_T *)&(CAL_MDF_cofnAbsPhaseFault_Y_af32[0])), 45U) != 0.0F) &&
    (rtb_Add >= CAL_MDF_nAbsPhaseFault_f32)));

  /* Outputs for Enabled SubSystem: '<S10>/PhaseFaultCalc' incorporates:
   *  EnablePort: '<S29>/Enable'
   */
  if (VAR_MDF_PhaseFaultChk_b) {
    SWC_MDF_IG_DW.PhaseFaultCalc_MODE = true;

    /* Abs: '<S31>/Abs' */
    rtb_Product = fabsf(*rtu_MCF_BUS_MCF_iU);

    /* UnitDelay: '<S31>/Unit Delay' */
    rtb_UnitDelay = SWC_MDF_IG_DW.UnitDelay_DSTATE;

    /* UnitDelay: '<S31>/Unit Delay1' */
    rtb_UnitDelay1_g = SWC_MDF_IG_DW.UnitDelay1_DSTATE_k;

    /* UnitDelay: '<S31>/Unit Delay2' */
    rtb_UnitDelay2 = SWC_MDF_IG_DW.UnitDelay2_DSTATE;

    /* Sum: '<S31>/Add' incorporates:
     *  UnitDelay: '<S31>/Unit Delay'
     *  UnitDelay: '<S31>/Unit Delay1'
     *  UnitDelay: '<S31>/Unit Delay2'
     *  UnitDelay: '<S31>/Unit Delay3'
     */
    rtb_Switch1 = (((rtb_Product + SWC_MDF_IG_DW.UnitDelay_DSTATE) +
                    SWC_MDF_IG_DW.UnitDelay1_DSTATE_k) +
                   SWC_MDF_IG_DW.UnitDelay2_DSTATE) +
      SWC_MDF_IG_DW.UnitDelay3_DSTATE;

    /* Abs: '<S32>/Abs' */
    rtb_Abs_p = fabsf(*rtu_MCF_BUS_MCF_iV);

    /* UnitDelay: '<S32>/Unit Delay' */
    rtb_UnitDelay_c = SWC_MDF_IG_DW.UnitDelay_DSTATE_k;

    /* UnitDelay: '<S32>/Unit Delay1' */
    rtb_UnitDelay1_l = SWC_MDF_IG_DW.UnitDelay1_DSTATE_g;

    /* UnitDelay: '<S32>/Unit Delay2' */
    rtb_UnitDelay2_o = SWC_MDF_IG_DW.UnitDelay2_DSTATE_e;

    /* Sum: '<S32>/Add' incorporates:
     *  UnitDelay: '<S32>/Unit Delay'
     *  UnitDelay: '<S32>/Unit Delay1'
     *  UnitDelay: '<S32>/Unit Delay2'
     *  UnitDelay: '<S32>/Unit Delay3'
     */
    rtb_Add_e = (((rtb_Abs_p + SWC_MDF_IG_DW.UnitDelay_DSTATE_k) +
                  SWC_MDF_IG_DW.UnitDelay1_DSTATE_g) +
                 SWC_MDF_IG_DW.UnitDelay2_DSTATE_e) +
      SWC_MDF_IG_DW.UnitDelay3_DSTATE_o;

    /* Switch: '<S35>/Switch' incorporates:
     *  RelationalOperator: '<S35>/Relational Operator1'
     */
    if (rtb_Switch1 >= rtb_Add_e) {
      rtb_Product_a = rtb_Switch1;
    } else {
      rtb_Product_a = rtb_Add_e;
    }

    /* End of Switch: '<S35>/Switch' */

    /* Abs: '<S33>/Abs' */
    rtb_Abs_o0 = fabsf(*rtu_MCF_BUS_MCF_iW);

    /* UnitDelay: '<S33>/Unit Delay' */
    rtb_UnitDelay_l = SWC_MDF_IG_DW.UnitDelay_DSTATE_m;

    /* UnitDelay: '<S33>/Unit Delay1' */
    rtb_UnitDelay1_e = SWC_MDF_IG_DW.UnitDelay1_DSTATE_f;

    /* UnitDelay: '<S33>/Unit Delay2' */
    rtb_UnitDelay2_j = SWC_MDF_IG_DW.UnitDelay2_DSTATE_o;

    /* Sum: '<S33>/Add' incorporates:
     *  UnitDelay: '<S33>/Unit Delay'
     *  UnitDelay: '<S33>/Unit Delay1'
     *  UnitDelay: '<S33>/Unit Delay2'
     *  UnitDelay: '<S33>/Unit Delay3'
     */
    rtb_Add_br = (((rtb_Abs_o0 + SWC_MDF_IG_DW.UnitDelay_DSTATE_m) +
                   SWC_MDF_IG_DW.UnitDelay1_DSTATE_f) +
                  SWC_MDF_IG_DW.UnitDelay2_DSTATE_o) +
      SWC_MDF_IG_DW.UnitDelay3_DSTATE_a;

    /* Switch: '<S35>/Switch1' incorporates:
     *  RelationalOperator: '<S35>/Relational Operator2'
     */
    if (!(rtb_Product_a >= rtb_Add_br)) {
      rtb_Product_a = rtb_Add_br;
    }

    /* End of Switch: '<S35>/Switch1' */

    /* Product: '<S35>/Product' incorporates:
     *  Constant: '<S35>/AverageFac'
     */
    rtb_Product_a *= 0.2F;

    /* Switch: '<S36>/Switch' incorporates:
     *  RelationalOperator: '<S36>/Relational Operator1'
     */
    if (!(rtb_Switch1 <= rtb_Add_e)) {
      rtb_Switch1 = rtb_Add_e;
    }

    /* End of Switch: '<S36>/Switch' */

    /* Switch: '<S36>/Switch1' incorporates:
     *  RelationalOperator: '<S36>/Relational Operator2'
     */
    if (!(rtb_Switch1 <= rtb_Add_br)) {
      rtb_Switch1 = rtb_Add_br;
    }

    /* End of Switch: '<S36>/Switch1' */

    /* Switch: '<S34>/Switch' incorporates:
     *  Constant: '<S34>/Constant1'
     *  RelationalOperator: '<S34>/Relational Operator'
     */
    if (rtb_Product_a >= 1.0E-6F) {
      rtb_Add_e = rtb_Product_a;
    } else {
      rtb_Add_e = 1.0E-6F;
    }

    /* End of Switch: '<S34>/Switch' */

    /* Product: '<S34>/Divide' incorporates:
     *  Constant: '<S36>/AverageFac'
     *  Product: '<S36>/Product'
     *  Sum: '<S34>/Add'
     */
    VAR_MDF_3PhaUnbalanceObs_f32 = (rtb_Product_a - rtb_Switch1 * 0.2F) * (1.0F /
      rtb_Add_e);

    /* RelationalOperator: '<S34>/Relational Operator1' incorporates:
     *  Constant: '<S34>/CAL_MDF_3PhaUnbalance_f32'
     */
    rtb_RelationalOperator1_e = (VAR_MDF_3PhaUnbalanceObs_f32 >=
      CAL_MDF_3PhaUnbalance_f32);

    /* Switch: '<S30>/Switch' incorporates:
     *  Constant: '<S30>/CAL_MDF_tiPhaFaultDelay_f32'
     *  Constant: '<S30>/unitTime'
     *  RelationalOperator: '<S30>/Relational Operator1'
     *  Sum: '<S30>/Sum1'
     *  UnitDelay: '<S30>/Unit Delay1'
     *  UnitDelay: '<S30>/Unit Delay2'
     */
    if ((int32_T)rtb_RelationalOperator1_e > (int32_T)
        SWC_MDF_IG_DW.UnitDelay2_DSTATE_g) {
      SWC_MDF_IG_DW.UnitDelay1_DSTATE_gn = CAL_MDF_tiPhaFaultDelay_f32;
    }

    SWC_MDF_IG_DW.UnitDelay1_DSTATE_gn -= 0.01F;

    /* End of Switch: '<S30>/Switch' */

    /* Saturate: '<S30>/Saturation' incorporates:
     *  UnitDelay: '<S30>/Unit Delay1'
     */
    if (SWC_MDF_IG_DW.UnitDelay1_DSTATE_gn > 10000.0F) {
      rtb_Switch1 = 10000.0F;
    } else if (SWC_MDF_IG_DW.UnitDelay1_DSTATE_gn < -10000.0F) {
      rtb_Switch1 = -10000.0F;
    } else {
      rtb_Switch1 = SWC_MDF_IG_DW.UnitDelay1_DSTATE_gn;
    }

    /* End of Saturate: '<S30>/Saturation' */

    /* Logic: '<S30>/Logical Operator1' incorporates:
     *  Constant: '<S30>/-unitTime'
     *  RelationalOperator: '<S30>/Relational Operator'
     */
    VAR_MDF_bPhaseFault_b = (rtb_RelationalOperator1_e && (rtb_Switch1 <= -0.01F));

    /* Switch: '<S29>/Switch1' */
    if (VAR_MDF_bPhaseFault_b) {
      /* Switch: '<S29>/Switch1' incorporates:
       *  Constant: '<S29>/Constant5'
       */
      SWC_MDF_IG_B.Switch1 = 3U;
    } else {
      /* Switch: '<S29>/Switch1' incorporates:
       *  Constant: '<S29>/Constant6'
       */
      SWC_MDF_IG_B.Switch1 = 2U;
    }

    /* End of Switch: '<S29>/Switch1' */

    /* Update for UnitDelay: '<S31>/Unit Delay' */
    SWC_MDF_IG_DW.UnitDelay_DSTATE = rtb_Product;

    /* Update for UnitDelay: '<S31>/Unit Delay1' */
    SWC_MDF_IG_DW.UnitDelay1_DSTATE_k = rtb_UnitDelay;

    /* Update for UnitDelay: '<S31>/Unit Delay2' */
    SWC_MDF_IG_DW.UnitDelay2_DSTATE = rtb_UnitDelay1_g;

    /* Update for UnitDelay: '<S31>/Unit Delay3' */
    SWC_MDF_IG_DW.UnitDelay3_DSTATE = rtb_UnitDelay2;

    /* Update for UnitDelay: '<S32>/Unit Delay' */
    SWC_MDF_IG_DW.UnitDelay_DSTATE_k = rtb_Abs_p;

    /* Update for UnitDelay: '<S32>/Unit Delay1' */
    SWC_MDF_IG_DW.UnitDelay1_DSTATE_g = rtb_UnitDelay_c;

    /* Update for UnitDelay: '<S32>/Unit Delay2' */
    SWC_MDF_IG_DW.UnitDelay2_DSTATE_e = rtb_UnitDelay1_l;

    /* Update for UnitDelay: '<S32>/Unit Delay3' */
    SWC_MDF_IG_DW.UnitDelay3_DSTATE_o = rtb_UnitDelay2_o;

    /* Update for UnitDelay: '<S33>/Unit Delay' */
    SWC_MDF_IG_DW.UnitDelay_DSTATE_m = rtb_Abs_o0;

    /* Update for UnitDelay: '<S33>/Unit Delay1' */
    SWC_MDF_IG_DW.UnitDelay1_DSTATE_f = rtb_UnitDelay_l;

    /* Update for UnitDelay: '<S33>/Unit Delay2' */
    SWC_MDF_IG_DW.UnitDelay2_DSTATE_o = rtb_UnitDelay1_e;

    /* Update for UnitDelay: '<S33>/Unit Delay3' */
    SWC_MDF_IG_DW.UnitDelay3_DSTATE_a = rtb_UnitDelay2_j;

    /* Update for UnitDelay: '<S30>/Unit Delay2' */
    SWC_MDF_IG_DW.UnitDelay2_DSTATE_g = rtb_RelationalOperator1_e;
  } else {
    if (SWC_MDF_IG_DW.PhaseFaultCalc_MODE) {
      /* Disable for Logic: '<S30>/Logical Operator1' incorporates:
       *  Outport: '<S29>/MDF_bPhaseFault'
       */
      VAR_MDF_bPhaseFault_b = false;
      SWC_MDF_IG_DW.PhaseFaultCalc_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S10>/PhaseFaultCalc' */

  /* Product: '<S15>/Product5' incorporates:
   *  Constant: '<S15>/Constant'
   *  Constant: '<S15>/MDF_GLB_pi_f32'
   *  Constant: '<S38>/CnvFac1'
   *  Constant: '<S3>/MDF_GLB_MotorPole_u8'
   *  Product: '<S38>/Divide'
   *  Product: '<S38>/Product1'
   */
  rtb_Product = *rtu_HSPF_BUS_HSPF_nSlowFlt / 60.0F * (real32_T)((uint8_T)
    MDF_GLB_MotorPole_u8) * 2.0F * MDF_GLB_pi_f32;

  /* Product: '<S15>/Product1' */
  rtb_UnitDelay = rtb_Product * *rtu_MPC_BUS_MPC_Lq * *rtu_MPC_BUS_MPC_iqActFlt;

  /* Abs: '<S15>/Abs' incorporates:
   *  Product: '<S15>/Product'
   *  Sum: '<S15>/Add'
   */
  VAR_MDF_OffSetSiteAObs_f32 = fabsf((*rtu_MCF_BUS_MCF_udDes -
    *rtu_MPC_BUS_MPC_idActFlt * *rtu_MPC_BUS_MPC_Rs) + rtb_UnitDelay);

  /* Switch: '<S21>/Switch' incorporates:
   *  Abs: '<S21>/Abs'
   *  Constant: '<S21>/Constant'
   *  Constant: '<S22>/Constant'
   *  RelationalOperator: '<S22>/Compare'
   */
  if (fabsf(VAR_MDF_OffSetSiteAObs_f32) <= 0.0001F) {
    rtb_UnitDelay1_g = 0.0001F;
  } else {
    rtb_UnitDelay1_g = VAR_MDF_OffSetSiteAObs_f32;
  }

  /* End of Switch: '<S21>/Switch' */

  /* Gain: '<S21>/Gain3' incorporates:
   *  Constant: '<S24>/Constant'
   *  RelationalOperator: '<S24>/Compare'
   */
  rtb_Gain3 = (uint8_T)((rtb_UnitDelay1_g >= 0.0F) << 7);

  /* Sum: '<S15>/Add1' incorporates:
   *  Product: '<S15>/Product2'
   */
  rtb_UnitDelay = (*rtu_MPC_BUS_MPC_iqActFlt * *rtu_MPC_BUS_MPC_Rs +
                   rtb_UnitDelay) - *rtu_MCF_BUS_MCF_uqDes;

  /* Abs: '<S15>/Abs1' */
  VAR_MDF_OffSetSiteBObs_f32 = fabsf(rtb_UnitDelay);

  /* Switch: '<S21>/Switch1' incorporates:
   *  Abs: '<S21>/Abs1'
   *  Constant: '<S21>/Constant1'
   *  Constant: '<S23>/Constant'
   *  RelationalOperator: '<S23>/Compare'
   */
  if (fabsf(VAR_MDF_OffSetSiteBObs_f32) <= 0.0001F) {
    rtb_UnitDelay = 0.0001F;
  } else {
    rtb_UnitDelay = VAR_MDF_OffSetSiteBObs_f32;
  }

  /* End of Switch: '<S21>/Switch1' */

  /* Product: '<S21>/Divide' */
  rtb_UnitDelay1_g /= rtb_UnitDelay;

  /* Abs: '<S21>/Abs2' */
  rtb_UnitDelay1_g = fabsf(rtb_UnitDelay1_g);

  /* RelationalOperator: '<S26>/Compare' incorporates:
   *  Constant: '<S26>/Constant'
   */
  rtb_RelationalOperator1_e = (rtb_UnitDelay1_g >= 1.0F);

  /* Switch: '<S21>/Switch2' incorporates:
   *  Constant: '<S21>/Constant2'
   *  Product: '<S21>/Divide1'
   */
  if (rtb_RelationalOperator1_e) {
    rtb_UnitDelay1_g = 1.0F / rtb_UnitDelay1_g;
  }

  /* End of Switch: '<S21>/Switch2' */

  /* MultiPortSwitch: '<S21>/Multiport Switch' incorporates:
   *  Constant: '<S21>/Constant10'
   *  Constant: '<S21>/Constant3'
   *  Constant: '<S21>/Constant4'
   *  Constant: '<S21>/Constant5'
   *  Constant: '<S21>/Constant7'
   *  Constant: '<S21>/Constant8'
   *  Constant: '<S21>/Constant9'
   *  Constant: '<S25>/Constant'
   *  Gain: '<S21>/Gain1'
   *  Gain: '<S21>/Gain2'
   *  Gain: '<S21>/Gain3'
   *  Gain: '<S21>/Gain4'
   *  LookupNDDirect: '<S21>/Direct Lookup Table (n-D)'
   *  RelationalOperator: '<S25>/Compare'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   *  Sum: '<S21>/Add2'
   *  Sum: '<S21>/Add3'
   *  Sum: '<S21>/Add5'
   *  Sum: '<S21>/Add6'
   *  Sum: '<S21>/Add7'
   *  Sum: '<S21>/Add8'
   *
   * About '<S21>/Direct Lookup Table (n-D)':
   *  1-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  switch ((int32_T)((((((uint32_T)((rtb_UnitDelay >= 0.0F) << 7) << 1) +
                       rtb_Gain3) + ((uint32_T)(rtb_RelationalOperator1_e << 7) <<
              2)) >> 2) >> 5)) {
   case 0:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = (real32_T)(58672U * rtCP_DirectLookupTablenD_table
      [(int32_T)rtb_UnitDelay]) * 1.49011612E-8F + 180.0F;
    break;

   case 1:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = 180.0F - (real32_T)(58672U *
      rtCP_DirectLookupTablenD_table[(int32_T)rtb_UnitDelay]) * 1.49011612E-8F;
    break;

   case 2:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = 360.0F - (real32_T)(58672U *
      rtCP_DirectLookupTablenD_table[(int32_T)rtb_UnitDelay]) * 1.49011612E-8F;
    break;

   case 3:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = (real32_T)(58672U * rtCP_DirectLookupTablenD_table
      [(int32_T)rtb_UnitDelay]) * 1.49011612E-8F;
    break;

   case 4:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = 270.0F - (real32_T)(58672U *
      rtCP_DirectLookupTablenD_table[(int32_T)rtb_UnitDelay]) * 1.49011612E-8F;
    break;

   case 5:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = (real32_T)(58672U * rtCP_DirectLookupTablenD_table
      [(int32_T)rtb_UnitDelay]) * 1.49011612E-8F + 90.0F;
    break;

   case 6:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = (real32_T)(58672U * rtCP_DirectLookupTablenD_table
      [(int32_T)rtb_UnitDelay]) * 1.49011612E-8F + 270.0F;
    break;

   default:
    /* LookupNDDirect: '<S21>/Direct Lookup Table (n-D)' incorporates:
     *  Gain: '<S21>/Gain'
     *
     * About '<S21>/Direct Lookup Table (n-D)':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_UnitDelay = 1024.0F * rtb_UnitDelay1_g;
    if (rtb_UnitDelay > 1024.0F) {
      rtb_UnitDelay = 1024.0F;
    }

    rtb_UnitDelay1_g = 90.0F - (real32_T)(58672U *
      rtCP_DirectLookupTablenD_table[(int32_T)rtb_UnitDelay]) * 1.49011612E-8F;
    break;
  }

  /* End of MultiPortSwitch: '<S21>/Multiport Switch' */

  /* Sum: '<S15>/Add2' incorporates:
   *  Constant: '<S15>/CAL_MDF_tiAgComp_f32'
   *  Constant: '<S15>/Constant3'
   *  Constant: '<S15>/MDF_GLB_pi_f32'
   *  Product: '<S15>/Divide1'
   *  Product: '<S15>/Product3'
   */
  VAR_MDF_offsetDeltaObs_f32 = rtb_UnitDelay1_g - rtb_Product * 180.0F /
    MDF_GLB_pi_f32 * *rtu_MCF_BUS_MCF_dtPwm * CAL_MDF_tiAgComp_f32;

  /* Constant: '<Root>/Constant6' */
  VAR_MDF_AlOfsNoPlausState_u8 = 0U;

  /* DataTypeConversion: '<S1>/Data Type Conversion1' */
  rtb_DataTypeConversion1 = (iEDS_Enum_stDrvCtl_def)*rtu_SCF_BUS_SCF_stDrvCtl;

  /* Logic: '<S13>/Logical Operator' incorporates:
   *  Constant: '<S13>/CAL_MDF_nThresAlOfsNoPlauseFaultMax_f32'
   *  Constant: '<S13>/CAL_MDF_nThresAlOfsNoPlauseFaultMin_f32'
   *  Constant: '<S13>/CAL_MDF_trqOfsNoPlausFault_f32'
   *  Constant: '<S13>/MDF_GLB_IGBTrun_u8'
   *  Constant: '<S13>/iEDS_Enum_stDrvCtl_def.Drv_OffsetAcc'
   *  Constant: '<S13>/iEDS_Enum_stDrvCtl_def.Drv_OffsetFw'
   *  Logic: '<S13>/Logical Operator1'
   *  Logic: '<S13>/Logical Operator2'
   *  RelationalOperator: '<S13>/Relational Operator1'
   *  RelationalOperator: '<S13>/Relational Operator2'
   *  RelationalOperator: '<S13>/Relational Operator3'
   *  RelationalOperator: '<S13>/Relational Operator4'
   *  RelationalOperator: '<S13>/Relational Operator5'
   *  RelationalOperator: '<S13>/Relational Operator6'
   */
  rtb_RelationalOperator1_e = ((VAR_MDF_AlOfsNoPlausState_u8 != 0) &&
    ((Drv_OffsetAcc != rtb_DataTypeConversion1) && (rtb_DataTypeConversion1 !=
    Drv_OffsetFw)) && (SWC_MDF_IG_ConstB.Abs <= CAL_MDF_trqOfsNoPlausFault_f32) &&
    (*rtu_SCF_BUS_SCF_stGateDrv == ((uint8_T)MDF_GLB_IGBTrun_u8)) && ((rtb_Add >
    CAL_MDF_nThresAlOfsNoPlauseFaultMin_f32) && (rtb_Add <
    CAL_MDF_nThresAlOfsNoPlauseFaultMax_f32)));

  /* Switch: '<S16>/Switch' incorporates:
   *  Constant: '<S16>/CAL_MDF_tiOffsetSteady_f32'
   *  Constant: '<S16>/Ts2'
   *  RelationalOperator: '<S16>/Relational Operator1'
   *  Sum: '<S16>/Sum1'
   *  UnitDelay: '<S16>/Unit Delay2'
   */
  if ((int32_T)rtb_RelationalOperator1_e > (int32_T)
      SWC_MDF_IG_DW.UnitDelay2_DSTATE_p) {
    SWC_MDF_IG_DW.UnitDelay1_DSTATE = CAL_MDF_tiOffsetSteady_f32;
  }

  SWC_MDF_IG_DW.UnitDelay1_DSTATE -= 0.01F;

  /* End of Switch: '<S16>/Switch' */

  /* Logic: '<S16>/Logical Operator1' incorporates:
   *  Constant: '<S16>/Ts1'
   *  RelationalOperator: '<S16>/Relational Operator'
   *  UnitDelay: '<S16>/Unit Delay1'
   */
  VAR_MDF_bAlOfsChk_b = (rtb_RelationalOperator1_e &&
    (SWC_MDF_IG_DW.UnitDelay1_DSTATE <= -0.01F));

  /* Outputs for Enabled SubSystem: '<S4>/OfsNoPlausFaultCalc' incorporates:
   *  EnablePort: '<S14>/Enable'
   */
  if (VAR_MDF_bAlOfsChk_b) {
    /* Product: '<S19>/Divide' incorporates:
     *  Constant: '<S18>/CAL_MDF_OfsDeltaAgFltFrq_f32'
     *  Constant: '<S18>/PRV_CalFltFrq_10ms'
     */
    rtb_Add = 100.0F / CAL_MDF_OfsDeltaAgFltFrq_f32;

    /* Switch: '<S20>/Switch' incorporates:
     *  Constant: '<S19>/Constant'
     *  RelationalOperator: '<S20>/UpperRelop'
     *  Switch: '<S20>/Switch2'
     */
    if (rtb_Add < 1.0F) {
      rtb_Add = 1.0F;
    }

    /* End of Switch: '<S20>/Switch' */

    /* Product: '<S19>/Divide1' incorporates:
     *  Constant: '<S19>/CAL_Mdf_Multiple_u8'
     *  Constant: '<S19>/MDF_GLB_pi_f32'
     *  Product: '<S19>/Product2'
     *  Sum: '<S19>/Add'
     */
    rtb_Add /= MDF_GLB_pi_f32 * 2.0F + rtb_Add;

    /* Sum: '<S19>/Sum1' incorporates:
     *  Constant: '<S19>/One'
     *  Product: '<S19>/Product'
     *  Product: '<S19>/Product1'
     *  Sum: '<S19>/Subtract1'
     *  UnitDelay: '<S19>/Unit Delay'
     */
    SWC_MDF_IG_DW.UnitDelay_DSTATE_c = (1.0F - rtb_Add) *
      VAR_MDF_offsetDeltaObs_f32 + rtb_Add * SWC_MDF_IG_DW.UnitDelay_DSTATE_c;

    /* Abs: '<S18>/Abs1' incorporates:
     *  UnitDelay: '<S19>/Unit Delay'
     */
    VAR_MDF_offsetDeltaFlt_f32 = fabsf(SWC_MDF_IG_DW.UnitDelay_DSTATE_c);

    /* RelationalOperator: '<S18>/Relational Operator' incorporates:
     *  Constant: '<S18>/CAL_MDF_DIffAlOfsMax_f32'
     */
    rtb_RelationalOperator_p = (VAR_MDF_offsetDeltaFlt_f32 >
      CAL_MDF_DIffAlOfsMax_f32);

    /* Switch: '<S17>/Switch' incorporates:
     *  Constant: '<S17>/CAL_MDF_tiAlfOfsNoPlauseFault_f32'
     *  Constant: '<S17>/unitTime'
     *  RelationalOperator: '<S17>/Relational Operator1'
     *  Sum: '<S17>/Sum1'
     *  UnitDelay: '<S17>/Unit Delay1'
     *  UnitDelay: '<S17>/Unit Delay2'
     */
    if ((int32_T)rtb_RelationalOperator_p > (int32_T)
        SWC_MDF_IG_DW.UnitDelay2_DSTATE_b) {
      SWC_MDF_IG_DW.UnitDelay1_DSTATE_fp = CAL_MDF_tiAlfOfsNoPlauseFault_f32;
    }

    SWC_MDF_IG_DW.UnitDelay1_DSTATE_fp -= 0.01F;

    /* End of Switch: '<S17>/Switch' */

    /* Saturate: '<S17>/Saturation' incorporates:
     *  UnitDelay: '<S17>/Unit Delay1'
     */
    if (SWC_MDF_IG_DW.UnitDelay1_DSTATE_fp > 10000.0F) {
      rtb_Switch1 = 10000.0F;
    } else if (SWC_MDF_IG_DW.UnitDelay1_DSTATE_fp < -10000.0F) {
      rtb_Switch1 = -10000.0F;
    } else {
      rtb_Switch1 = SWC_MDF_IG_DW.UnitDelay1_DSTATE_fp;
    }

    /* End of Saturate: '<S17>/Saturation' */

    /* Logic: '<S17>/Logical Operator1' incorporates:
     *  Constant: '<S17>/-unitTime'
     *  RelationalOperator: '<S17>/Relational Operator'
     */
    VAR_MDF_bAlfOfsNoPlauseFault_b = (rtb_RelationalOperator_p && (rtb_Switch1 <=
      -0.01F));

    /* Switch: '<S14>/Switch1' */
    if (VAR_MDF_bAlfOfsNoPlauseFault_b) {
      /* Switch: '<S14>/Switch1' incorporates:
       *  Constant: '<S14>/Constant5'
       */
      SWC_MDF_IG_B.Switch1_g = 3U;
    } else {
      /* Switch: '<S14>/Switch1' incorporates:
       *  Constant: '<S14>/Constant6'
       */
      SWC_MDF_IG_B.Switch1_g = 2U;
    }

    /* End of Switch: '<S14>/Switch1' */

    /* Update for UnitDelay: '<S17>/Unit Delay2' */
    SWC_MDF_IG_DW.UnitDelay2_DSTATE_b = rtb_RelationalOperator_p;
  }

  /* End of Outputs for SubSystem: '<S4>/OfsNoPlausFaultCalc' */

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   *  UnitDelay: '<S37>/Unit Delay'
   */
  *rty_MDF_BUS_MDF_stFrwhl = SWC_MDF_IG_DW.UnitDelay_DSTATE_n;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_flagOperOutdRng = 0U;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_IsOvHiErrSt = SWC_MDF_IG_B.Switch1_j;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   *  Constant: '<S5>/Constant1'
   */
  *rty_MDF_BUS_MDF_bFaultEMBlkWarn = 0U;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   *  Constant: '<S5>/Constant1'
   */
  *rty_MDF_BUS_MDF_bFaultEMBlkErrS = 0U;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_bFaultPwrCmpSt = 0U;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_bPhaseFaultSt = SWC_MDF_IG_B.Switch1;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_bAlfOfsNoPlause = SWC_MDF_IG_B.Switch1_g;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   *  Constant: '<S6>/Constant1'
   */
  *rty_MDF_BUS_MDF_bFaultICtlChkSt = 0U;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_bOpenCirNoPsblF = 0U;

  /* SignalConversion generated from: '<Root>/MDF_BUS' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  *rty_MDF_BUS_MDF_bShCirNoPsblFau = 0U;

  /* Constant: '<Root>/Constant1' */
  VAR_MDF_EmacBlkdState_u8 = 0U;

  /* Constant: '<Root>/Constant4' */
  VAR_MDF_PrfElDrvState_u8 = 0U;

  /* Constant: '<Root>/Constant5' */
  VAR_MDF_ICtlRatState_u8 = 0U;

  /* Constant: '<Root>/Constant7' */
  VAR_MDF_OpenCirNoPsblState_u8 = 0U;

  /* Constant: '<Root>/Constant8' */
  VAR_MDF_DiashCirNoPsblState_u8 = 0U;

  /* Constant: '<Root>/Constant9' */
  VAR_MDF_OperOutdRngState_u8 = 0U;

  /* Update for UnitDelay: '<S16>/Unit Delay2' */
  SWC_MDF_IG_DW.UnitDelay2_DSTATE_p = rtb_RelationalOperator1_e;
}

/* Model initialize function */
void SWC_MDF_IG_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_MDF_IG_T *const SWC_MDF_IG_M = &(SWC_MDF_IG_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(SWC_MDF_IG_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
