/*
 * File: TM1_RSD.c
 *
 * Code generated for Simulink model 'TM1_RSD'.
 *
 * Model version                  : 1.80
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Mon Jun 17 14:05:18 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TM1_Global.h"
#include "TM1_RSD.h"
#include "TM1_RSD_private.h"
#include "look1_iflf_binlxpw.h"

/* Exported data definition */

/*MeasurementVariable*/
#define TM1_RSD_CLEAR_FAR_DATA_ALIGN4_START
//#include "TM1_RSD_MemMap.h"

/* Definition for custom storage class: TM1_RSD_Monitor */
real32_T TM1_BSW_timPosTimeTrigerTimeStamp_vf32;
real32_T TM1_BSW_timTimeCurTrigerTimeStamp_vf32;
real32_T TM1_BSW_timTimeDelayGenTimeF_vf32;
real32_T TM1_BSW_uDsadcCosValVol_vf32;
real32_T TM1_BSW_uDsadcSinValVol_vf32;
real32_T TM1_RSD_agESpdPIDrads_vf32;
real32_T TM1_RSD_agErrEAngleNULL_vf32;
uint16_T TM1_RSD_agMotorEAnglePLLNULL_vu16;
uint16_T TM1_RSD_cntMotorEAngleDSADCNULL_vu16;
uint16_T TM1_RSD_cntMotorEAngleNULL_vu16;
real32_T TM1_RSD_nESpdPIDrads_vf32;
real32_T TM1_RSD_nMSpdPIDrads_vf32;
real32_T TM1_RSD_nMotorESpdDSADCrads_vf32;
real32_T TM1_RSD_nMotorMSpdrads_vf32;
real32_T TM1_RSD_nMotorMSpdrpm_vf32;
uint16_T TM1_RSD_timDSADCEAngleAtanNULL_vu16;
real32_T TM1_RSD_timDSADCTimeComps_vf32;
real32_T TM1_uDsadcCosValVol_vf32;
real32_T TM1_uDsadcSinValVol_vf32;

#define TM1_RSD_CLEAR_FAR_DATA_ALIGN4_STOP
//#include "TM1_RSD_MemMap.h"

/* Block states (default storage) */

/*MeasurementVariable*/
#define TM1_RSD_CLEAR_FAR_DATA_ALIGN4_START
//#include "TM1_RSD_MemMap.h"

DW_TM1_RSD_T TM1_RSD_DW;

#define TM1_RSD_CLEAR_FAR_DATA_ALIGN4_STOP
//#include "TM1_RSD_MemMap.h"

/* Output and update for atomic system: '<Root>/TM1_RSD_CalPwmEAngle_sys' */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_CalPwmEAngle_sys(void)
{
  real32_T rtb_DataTypeConversion2;
  real32_T rtb_Switch;

  /* Switch: '<S5>/Switch' incorporates:
   *  Constant: '<S5>/Constant2'
   *  Constant: '<S5>/Constant3'
   *  Inport: '<Root>/TM1_BSW_timPosTimeTrigerTimeStamp_vf32'
   *  Inport: '<Root>/TM1_BSW_timTimeCurTrigerTimeStamp_vf32'
   *  Sum: '<S5>/Subtract1'
   *
   * Block description for '<Root>/TM1_BSW_timPosTimeTrigerTimeStamp_vf32':
   *  锟斤拷锟紸 DSADC 锟叫讹拷时锟斤拷锟�
   *
   * Block description for '<Root>/TM1_BSW_timTimeCurTrigerTimeStamp_vf32':
   *  锟斤拷锟紸 FOC 锟叫讹拷时锟斤拷锟�
   */
  if (TM1_RSD_TimeStampChange_kb) {
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch = TM1_BSW_timTimeCurTrigerTimeStamp_vf32 -
      TM1_BSW_timPosTimeTrigerTimeStamp_vf32;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Gain: '<S5>/Gain' incorporates:
   *  Constant: '<S5>/Constant4'
   */
  rtb_DataTypeConversion2 = 0.5F * TM1_RSD_TimeStampOverSet_kf32;

  /* If: '<S5>/If' incorporates:
   *  Constant: '<S6>/Constant4'
   *  Constant: '<S7>/Constant4'
   *  Gain: '<S5>/Gain1'
   *  Sum: '<S6>/Subtract'
   *  Sum: '<S7>/Subtract'
   */
  if (rtb_Switch > rtb_DataTypeConversion2) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    rtb_Switch -= TM1_RSD_TimeStampOverSet_kf32;

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem' */
  } else {
    if (rtb_Switch < -rtb_DataTypeConversion2) {
      /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S7>/Action Port'
       */
      rtb_Switch += TM1_RSD_TimeStampOverSet_kf32;

      /* End of Outputs for SubSystem: '<S5>/If Action Subsystem1' */
    }
  }

  /* End of If: '<S5>/If' */

  /* Sum: '<S4>/Add2' incorporates:
   *  Constant: '<S4>/PA_TM1_RSD_cntGPTA0_CLOCKNULL_ku32'
   *  Constant: '<S4>/PA_TM1_RSD_timtComps_kf1'
   *  DataTypeConversion: '<S4>/Data Type Conversion2'
   *  Gain: '<S4>/Gain'
   *  Inport: '<Root>/TM1_BSW_timTimeDelayGenTimeF_vf32'
   *  Product: '<S4>/Divide4'
   *
   * Block description for '<Root>/TM1_BSW_timTimeDelayGenTimeF_vf32':
   *  锟斤拷锟紸 DSADC delay时锟斤拷锟�
   */
  TM1_RSD_timDSADCTimeComps_vf32 = (rtb_Switch / (real32_T)
    TM1_RSD_cntGPTA0_CLOCKNULL_ku32 + TM1_BSW_timTimeDelayGenTimeF_vf32) +
    1.0E-6F * TM1_RSD_timtComps_kf32;

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Constant: '<S3>/PA_TM1_RSD_ratEAngleOffsetNULL_kf32'
   *  Constant: '<S3>/PA_TM1_RSD_timCurPositSampTErrus_kf32'
   *  Gain: '<S3>/Gain'
   *  Gain: '<S3>/Gain1'
   *  Product: '<S3>/Product4'
   *  Sum: '<S3>/Add'
   *  Sum: '<S3>/Subtract'
   */
  rtb_Switch = (real32_T)floor(((TM1_RSD_timDSADCTimeComps_vf32 - 1.0E-6F *
    TM1_RSD_timCurPositSampTErrus_kf32) * TM1_RSD_nMotorESpdDSADCrads_vf32 *
    651.898621F + (real32_T)TM1_RSD_cntMotorEAngleDSADCNULL_vu16) -
    TM1_RSD_ratEAngleOffsetNULL_kf32);
  if (rtIsNaNF(rtb_Switch) || rtIsInfF(rtb_Switch)) {
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch = (real32_T)fmod(rtb_Switch, 4.294967296E+9);
  }

  /* Math: '<S3>/Math Function1' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   */
  TM1_RSD_cntMotorEAngleNULL_vu16 = (uint16_T)((uint16_T)(rtb_Switch < 0.0F ?
    -(int32_T)(uint32_T)-rtb_Switch : (int32_T)(uint32_T)rtb_Switch) % 4096);
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/*
 * Output and update for action system:
 *    '<S16>/If Action Subsystem'
 *    '<S20>/If Action Subsystem'
 */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_IfActionSubsystem(real32_T rtu_In1, real32_T *rty_Out1)
{
  /* Sum: '<S17>/Subtract' incorporates:
   *  Constant: '<S17>/Constant'
   */
  *rty_Out1 = rtu_In1 - 6.28318548F;
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/*
 * Output and update for action system:
 *    '<S16>/If Action Subsystem1'
 *    '<S20>/If Action Subsystem1'
 */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_IfActionSubsystem1(real32_T rtu_In1, real32_T *rty_Out1)
{
  /* Sum: '<S18>/Subtract' incorporates:
   *  Constant: '<S18>/Constant'
   */
  *rty_Out1 = rtu_In1 + 6.28318548F;
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/*
 * Output and update for action system:
 *    '<S29>/If Action Subsystem3'
 *    '<S30>/If Action Subsystem3'
 *    '<S38>/If Action Subsystem3'
 *    '<S42>/If Action Subsystem3'
 */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_IfActionSubsystem3(real32_T rtu_In1, real32_T *rty_Out1)
{
  /* Product: '<S34>/Multiply' */
  *rty_Out1 = -rtu_In1;
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/* Output and update for atomic system: '<Root>/TM1_RSD_DSADCDecoder_sys' */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_DSADCDecoder_sys(void)
{
  real32_T rtb_Gain_h;
  real32_T rtb_Sum4;
  real32_T rtb_Merge;
  real32_T rtb_Merge_e;

  /* Gain: '<S11>/Gain' incorporates:
   *  Constant: '<S11>/PA_TM1_RSD_nSpeed_Manrpm_kf32'
   */
  rtb_Gain_h = 0.104719758F * TM1_RSD_nSpeed_Manrpm_kf32;

  /* Sum: '<S16>/Sum4' incorporates:
   *  Constant: '<S16>/PA_TM2_RSD_frqDSADCFreqHZ_ku16'
   *  Gain: '<S11>/GLBCal_Ke_MotorPolePairsNum_NULL'
   *  Product: '<S16>/Multiply'
   *  UnitDelay: '<S16>/Unit Delay1'
   */
  rtb_Sum4 = (real32_T)TM1_GLBCal_cntMotorPolePairsNumNULL_ku8 * rtb_Gain_h *
    TM1_RSD_frqDSADCycleS_kf32 + TM1_RSD_DW.UnitDelay1_DSTATE;

  /* If: '<S16>/If1' incorporates:
   *  Constant: '<S16>/Constant2'
   *  Inport: '<S19>/In1'
   */
  if (rtb_Sum4 >= 6.28318548F) {
    /* Outputs for IfAction SubSystem: '<S16>/If Action Subsystem' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    TM1_RSD_IfActionSubsystem(rtb_Sum4, &rtb_Merge);

    /* End of Outputs for SubSystem: '<S16>/If Action Subsystem' */
  } else if (rtb_Sum4 < 0.0F) {
    /* Outputs for IfAction SubSystem: '<S16>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S18>/Action Port'
     */
    TM1_RSD_IfActionSubsystem1(rtb_Sum4, &rtb_Merge);

    /* End of Outputs for SubSystem: '<S16>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S16>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S19>/Action Port'
     */
    rtb_Merge = rtb_Sum4;

    /* End of Outputs for SubSystem: '<S16>/If Action Subsystem2' */
  }

  /* End of If: '<S16>/If1' */

  /* Switch: '<S11>/Switch' incorporates:
   *  Constant: '<S11>/PA_TM1_RSD_flgManEangleflg_kb'
   */
  if (TM1_RSD_flgManEangleflg_kb) {
    /* Gain: '<S16>/2pi_4096' */
    rtb_Sum4 = 651.898621F * rtb_Merge;

    /* DataTypeConversion: '<S16>/Data Type Conversion' */
    if (rtb_Sum4 < 0.0F) {
      rtb_Sum4 = (real32_T)ceil(rtb_Sum4);
    } else {
      rtb_Sum4 = (real32_T)floor(rtb_Sum4);
    }

    if (rtIsNaNF(rtb_Sum4) || rtIsInfF(rtb_Sum4)) {
      rtb_Sum4 = 0.0F;
    } else {
      rtb_Sum4 = (real32_T)fmod(rtb_Sum4, 65536.0);
    }

    /* Math: '<S16>/Math Function1' incorporates:
     *  DataTypeConversion: '<S16>/Data Type Conversion'
     */
    TM1_RSD_cntMotorEAngleDSADCNULL_vu16 = (uint16_T)((uint16_T)(rtb_Sum4 < 0.0F
      ? (int32_T)(uint16_T)-(int16_T)(uint16_T)-rtb_Sum4 : (int32_T)(uint16_T)
      rtb_Sum4) % 4096);
  } else {
    /* Math: '<S10>/Math Function2' incorporates:
     *  Constant: '<S10>/PA_TM1_GLBCal_cntMotorPolePairsNumNULL_ku8'
     *  Constant: '<S10>/RSD_cntResolverPolePairsNumNULL_ku8'
     *  DataTypeConversion: '<S10>/Data Type Conversion1'
     *  Product: '<S10>/Divide'
     *  Product: '<S10>/Product'
     *  UnitDelay: '<S9>/Unit Delay1'
     */
    TM1_RSD_cntMotorEAngleDSADCNULL_vu16 = (uint16_T)((uint16_T)((uint32_T)
      (uint16_T)(TM1_RSD_cntResolverPolePairsNumNULL_ku8 == 0U ? MAX_uint32_T :
                 (uint32_T)TM1_RSD_agMotorEAnglePLLNULL_vu16 /
                 TM1_RSD_cntResolverPolePairsNumNULL_ku8) *
      TM1_GLBCal_cntMotorPolePairsNumNULL_ku8) % 4096);
  }

  /* End of Switch: '<S11>/Switch' */

  /* SignalConversion: '<S9>/Signal Conversion1' incorporates:
   *  Inport: '<Root>/TM1_BSW_uDsadcCosValVol_vf32'
   *
   * Block description for '<Root>/TM1_BSW_uDsadcCosValVol_vf32':
   *  锟斤拷锟紸 DSADC COS
   */
  TM1_uDsadcCosValVol_vf32 = TM1_BSW_uDsadcCosValVol_vf32;

  /* SignalConversion: '<S9>/Signal Conversion' incorporates:
   *  Inport: '<Root>/TM1_BSW_uDsadcSinValVol_vf32'
   *
   * Block description for '<Root>/TM1_BSW_uDsadcSinValVol_vf32':
   *  锟斤拷锟紸 DSADC SIN
   */
  TM1_uDsadcSinValVol_vf32 = TM1_BSW_uDsadcSinValVol_vf32;

  /* If: '<S30>/If1' incorporates:
   *  Inport: '<S37>/In1'
   */
  if (TM1_uDsadcCosValVol_vf32 >= 0.0F) {
    /* Outputs for IfAction SubSystem: '<S30>/If Action Subsystem4' incorporates:
     *  ActionPort: '<S37>/Action Port'
     */
    TM1_RSD_DW.UnitDelay1_DSTATE = TM1_uDsadcCosValVol_vf32;

    /* End of Outputs for SubSystem: '<S30>/If Action Subsystem4' */
  } else {
    /* Outputs for IfAction SubSystem: '<S30>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S36>/Action Port'
     */
    TM1_RSD_IfActionSubsystem3(TM1_uDsadcCosValVol_vf32,
      &TM1_RSD_DW.UnitDelay1_DSTATE);

    /* End of Outputs for SubSystem: '<S30>/If Action Subsystem3' */
  }

  /* End of If: '<S30>/If1' */

  /* If: '<S29>/If1' incorporates:
   *  Inport: '<S35>/In1'
   */
  if (TM1_uDsadcSinValVol_vf32 >= 0.0F) {
    /* Outputs for IfAction SubSystem: '<S29>/If Action Subsystem4' incorporates:
     *  ActionPort: '<S35>/Action Port'
     */
    rtb_Sum4 = TM1_uDsadcSinValVol_vf32;

    /* End of Outputs for SubSystem: '<S29>/If Action Subsystem4' */
  } else {
    /* Outputs for IfAction SubSystem: '<S29>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S34>/Action Port'
     */
    TM1_RSD_IfActionSubsystem3(TM1_uDsadcSinValVol_vf32, &rtb_Sum4);

    /* End of Outputs for SubSystem: '<S29>/If Action Subsystem3' */
  }

  /* End of If: '<S29>/If1' */

  /* If: '<S28>/If' */
  if ((TM1_RSD_DW.UnitDelay1_DSTATE == 0.0F) && (rtb_Sum4 == 0.0F)) {
    /* Outputs for IfAction SubSystem: '<S28>/If Action Subsystem' incorporates:
     *  ActionPort: '<S31>/Action Port'
     */
    /* SignalConversion: '<S31>/OutportBuffer_InsertedFor_Out1_at_inport_0' incorporates:
     *  Constant: '<S31>/Constant'
     */
    rtb_Sum4 = 0.0F;

    /* End of Outputs for SubSystem: '<S28>/If Action Subsystem' */
  } else if (TM1_RSD_DW.UnitDelay1_DSTATE >= rtb_Sum4) {
    /* Outputs for IfAction SubSystem: '<S28>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S32>/Action Port'
     */
    /* Product: '<S32>/Divide' */
    rtb_Sum4 = 1.0F / TM1_uDsadcCosValVol_vf32 * TM1_uDsadcSinValVol_vf32;

    /* If: '<S38>/If1' incorporates:
     *  Inport: '<S41>/In1'
     */
    if (rtb_Sum4 >= 0.0F) {
      /* Outputs for IfAction SubSystem: '<S38>/If Action Subsystem4' incorporates:
       *  ActionPort: '<S41>/Action Port'
       */
      rtb_Merge_e = rtb_Sum4;

      /* End of Outputs for SubSystem: '<S38>/If Action Subsystem4' */
    } else {
      /* Outputs for IfAction SubSystem: '<S38>/If Action Subsystem3' incorporates:
       *  ActionPort: '<S40>/Action Port'
       */
      TM1_RSD_IfActionSubsystem3(rtb_Sum4, &rtb_Merge_e);

      /* End of Outputs for SubSystem: '<S38>/If Action Subsystem3' */
    }

    /* End of If: '<S38>/If1' */

    /* Lookup_n-D: '<S32>/1-D Lookup Table' */
    rtb_Sum4 = look1_iflf_binlxpw(rtb_Merge_e, TM1_RSD_ConstP.pooled8,
      TM1_RSD_ConstP.pooled7, 900U);

    /* Chart: '<S32>/Chart' */
    if (TM1_uDsadcCosValVol_vf32 >= 0.0F) {
      if (!(TM1_uDsadcSinValVol_vf32 >= 0.0F)) {
        /* SignalConversion: '<S32>/OutportBufferForOut1' */
        rtb_Sum4 = 6.28318548F - rtb_Sum4;
      }
    } else if (TM1_uDsadcSinValVol_vf32 >= 0.0F) {
      /* SignalConversion: '<S32>/OutportBufferForOut1' */
      rtb_Sum4 = 3.14159274F - rtb_Sum4;
    } else {
      /* SignalConversion: '<S32>/OutportBufferForOut1' */
      rtb_Sum4 += 3.14159274F;
    }

    /* End of Chart: '<S32>/Chart' */
    /* End of Outputs for SubSystem: '<S28>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S28>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S33>/Action Port'
     */
    /* Product: '<S33>/Divide' */
    rtb_Sum4 = TM1_uDsadcCosValVol_vf32 / TM1_uDsadcSinValVol_vf32;

    /* If: '<S42>/If1' incorporates:
     *  Inport: '<S45>/In1'
     */
    if (rtb_Sum4 >= 0.0F) {
      /* Outputs for IfAction SubSystem: '<S42>/If Action Subsystem4' incorporates:
       *  ActionPort: '<S45>/Action Port'
       */
      rtb_Merge_e = rtb_Sum4;

      /* End of Outputs for SubSystem: '<S42>/If Action Subsystem4' */
    } else {
      /* Outputs for IfAction SubSystem: '<S42>/If Action Subsystem3' incorporates:
       *  ActionPort: '<S44>/Action Port'
       */
      TM1_RSD_IfActionSubsystem3(rtb_Sum4, &rtb_Merge_e);

      /* End of Outputs for SubSystem: '<S42>/If Action Subsystem3' */
    }

    /* End of If: '<S42>/If1' */

    /* Lookup_n-D: '<S33>/1-D Lookup Table' */
    rtb_Sum4 = look1_iflf_binlxpw(rtb_Merge_e, TM1_RSD_ConstP.pooled8,
      TM1_RSD_ConstP.pooled7, 900U);

    /* Chart: '<S33>/Chart' */
    if (TM1_uDsadcSinValVol_vf32 >= 0.0F) {
      if (TM1_uDsadcCosValVol_vf32 >= 0.0F) {
        /* SignalConversion: '<S33>/OutportBufferForOut1' */
        rtb_Sum4 = 1.57079637F - rtb_Sum4;
      } else {
        /* SignalConversion: '<S33>/OutportBufferForOut1' */
        rtb_Sum4 += 1.57079637F;
      }
    } else if (TM1_uDsadcCosValVol_vf32 >= 0.0F) {
      /* SignalConversion: '<S33>/OutportBufferForOut1' */
      rtb_Sum4 += 4.71238899F;
    } else {
      /* SignalConversion: '<S33>/OutportBufferForOut1' */
      rtb_Sum4 = 4.71238899F - rtb_Sum4;
    }

    /* End of Chart: '<S33>/Chart' */
    /* End of Outputs for SubSystem: '<S28>/If Action Subsystem2' */
  }

  /* End of If: '<S28>/If' */

  /* Gain: '<S13>/Gain1' */
  rtb_Sum4 *= 651.898621F;

  /* DataTypeConversion: '<S13>/Data Type Conversion' */
  rtb_Sum4 = (real32_T)floor(rtb_Sum4);
  if (rtIsNaNF(rtb_Sum4) || rtIsInfF(rtb_Sum4)) {
    rtb_Sum4 = 0.0F;
  } else {
    rtb_Sum4 = (real32_T)fmod(rtb_Sum4, 65536.0);
  }

  /* Math: '<S13>/Math Function1' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion'
   */
  TM1_RSD_timDSADCEAngleAtanNULL_vu16 = (uint16_T)((uint16_T)(rtb_Sum4 < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-rtb_Sum4 : (int32_T)(uint16_T)
    rtb_Sum4) % 4096);

  /* Sum: '<S13>/Subtract' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion1'
   *  UnitDelay: '<S9>/Unit Delay1'
   */
  TM1_RSD_agErrEAngleNULL_vf32 = (real32_T)(TM1_RSD_timDSADCEAngleAtanNULL_vu16
    - TM1_RSD_agMotorEAnglePLLNULL_vu16);

  /* If: '<S13>/If' */
  if (TM1_RSD_agErrEAngleNULL_vf32 > 2500.0F) {
    /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    /* Sum: '<S25>/Subtract' incorporates:
     *  Constant: '<S25>/Constant'
     */
    TM1_RSD_agErrEAngleNULL_vf32 = TM1_RSD_agErrEAngleNULL_vf32 - 4096.0F;

    /* End of Outputs for SubSystem: '<S13>/If Action Subsystem' */
  } else {
    if (TM1_RSD_agErrEAngleNULL_vf32 < -2500.0F) {
      /* Outputs for IfAction SubSystem: '<S13>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S26>/Action Port'
       */
      /* Sum: '<S26>/Subtract' incorporates:
       *  Constant: '<S26>/Constant'
       */
      TM1_RSD_agErrEAngleNULL_vf32 = TM1_RSD_agErrEAngleNULL_vf32 + 4096.0F;

      /* End of Outputs for SubSystem: '<S13>/If Action Subsystem1' */
    }
  }

  /* End of If: '<S13>/If' */

  /* Sum: '<S47>/Sum4' incorporates:
   *  Constant: '<S15>/PA_TM1_RSD_frqDSADCFreqHZ_ku16'
   *  Gain: '<S15>/ Ki  '
   *  Product: '<S47>/Divide'
   *  UnitDelay: '<S47>/Unit Delay2'
   */
  TM1_RSD_DW.UnitDelay2_DSTATE += TM1_RSD_ratPLLKiNULL_kf32 *
    TM1_RSD_agErrEAngleNULL_vf32 * TM1_RSD_frqDSADCycleS_kf32;

  /* Sum: '<S48>/Sum4' incorporates:
   *  Constant: '<S15>/PA_TM1_RSD_frqDSADCFreqHZ_ku16'
   *  Gain: '<S15>/Kp'
   *  Product: '<S48>/Divide'
   *  Sum: '<S15>/Add4'
   *  UnitDelay: '<S47>/Unit Delay2'
   *  UnitDelay: '<S48>/Unit Delay2'
   */
  TM1_RSD_DW.UnitDelay2_DSTATE_p += (TM1_RSD_ratPLLKpNULL_kf32 *
    TM1_RSD_agErrEAngleNULL_vf32 + TM1_RSD_DW.UnitDelay2_DSTATE) *
    TM1_RSD_frqDSADCycleS_kf32;

  /* Sum: '<S15>/Add1' incorporates:
   *  Gain: '<S15>/Kd'
   *  UnitDelay: '<S48>/Unit Delay2'
   */
  TM1_RSD_agESpdPIDrads_vf32 = TM1_RSD_ratPLLKdNULL_kf32 *
    TM1_RSD_agErrEAngleNULL_vf32 + TM1_RSD_DW.UnitDelay2_DSTATE_p;

  /* Switch: '<S11>/Switch2' incorporates:
   *  Constant: '<S11>/PA_TM1_RSD_flgManEangleflg_kb'
   *  Gain: '<S11>/KeRSD_ResolverPolePairsNum_NULL'
   */
  if (TM1_RSD_flgManEangleflg_kb) {
    TM1_RSD_nESpdPIDrads_vf32 = (real32_T)
      TM1_RSD_cntResolverPolePairsNumNULL_ku8 * rtb_Gain_h;
  } else {
    TM1_RSD_nESpdPIDrads_vf32 = TM1_RSD_agESpdPIDrads_vf32;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Product: '<S14>/Divide' incorporates:
   *  Constant: '<S14>/PA_TM1_RSD_cntResolverPolePairsNumNULL_ku8'
   */
  TM1_RSD_nMSpdPIDrads_vf32 = TM1_RSD_nESpdPIDrads_vf32 / (real32_T)
    TM1_RSD_cntResolverPolePairsNumNULL_ku8;

  /* Outputs for Atomic SubSystem: '<S14>/LowPassFilter' */
  /* Sum: '<S46>/Sum1' incorporates:
   *  Constant: '<S46>/One'
   *  Constant: '<S46>/PA_TM2_RSD_cntResolverPolePairsNumNULL_ku8'
   *  Delay: '<S46>/Err_sign_Previous'
   *  Product: '<S46>/Product'
   *  Product: '<S46>/Product1'
   *  Sum: '<S46>/Subtract1'
   */
  TM1_RSD_nMotorMSpdrads_vf32 = (1.0F -
    TM1_RSD_facMotorMSpdFilterFactorNULL_kf32) * TM1_RSD_nMotorMSpdrads_vf32 +
    TM1_RSD_nMSpdPIDrads_vf32 * TM1_RSD_facMotorMSpdFilterFactorNULL_kf32;

  /* End of Outputs for SubSystem: '<S14>/LowPassFilter' */

  /* Product: '<S14>/Product1' incorporates:
   *  Constant: '<S14>/Constant'
   */
  TM1_RSD_nMotorMSpdrpm_vf32 = TM1_RSD_nMotorMSpdrads_vf32 * 9.54929638F;

  /* Product: '<S14>/Product' incorporates:
   *  Constant: '<S14>/PA_TM1_GLBCal_cntMotorPolePairsNumNULL_ku8'
   */
  TM1_RSD_nMotorESpdDSADCrads_vf32 = (real32_T)
    TM1_GLBCal_cntMotorPolePairsNumNULL_ku8 * TM1_RSD_nMSpdPIDrads_vf32;

  /* Sum: '<S20>/Sum4' incorporates:
   *  Constant: '<S15>/PA_TM1_RSD_frqDSADCFreqHZ_ku16'
   *  Product: '<S20>/Divide'
   *  UnitDelay: '<S20>/Unit Delay1'
   */
  rtb_Gain_h = TM1_RSD_agESpdPIDrads_vf32 * TM1_RSD_frqDSADCycleS_kf32 +
    TM1_RSD_DW.UnitDelay1_DSTATE_f;

  /* If: '<S20>/If1' incorporates:
   *  Constant: '<S20>/Constant2'
   *  Inport: '<S24>/In1'
   *  UnitDelay: '<S20>/Unit Delay1'
   */
  if (rtb_Gain_h >= 6.28318548F) {
    /* Outputs for IfAction SubSystem: '<S20>/If Action Subsystem' incorporates:
     *  ActionPort: '<S22>/Action Port'
     */
    TM1_RSD_IfActionSubsystem(rtb_Gain_h, &TM1_RSD_DW.UnitDelay1_DSTATE_f);

    /* End of Outputs for SubSystem: '<S20>/If Action Subsystem' */
  } else if (rtb_Gain_h < 0.0F) {
    /* Outputs for IfAction SubSystem: '<S20>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S23>/Action Port'
     */
    TM1_RSD_IfActionSubsystem1(rtb_Gain_h, &TM1_RSD_DW.UnitDelay1_DSTATE_f);

    /* End of Outputs for SubSystem: '<S20>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<S20>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    TM1_RSD_DW.UnitDelay1_DSTATE_f = rtb_Gain_h;

    /* End of Outputs for SubSystem: '<S20>/If Action Subsystem2' */
  }

  /* End of If: '<S20>/If1' */

  /* Gain: '<S21>/Gain1' incorporates:
   *  UnitDelay: '<S20>/Unit Delay1'
   */
  rtb_Sum4 = 651.898621F * TM1_RSD_DW.UnitDelay1_DSTATE_f;

  /* DataTypeConversion: '<S21>/Data Type Conversion' */
  if (rtb_Sum4 < 0.0F) {
    rtb_Sum4 = (real32_T)ceil(rtb_Sum4);
  } else {
    rtb_Sum4 = (real32_T)floor(rtb_Sum4);
  }

  if (rtIsNaNF(rtb_Sum4) || rtIsInfF(rtb_Sum4)) {
    rtb_Sum4 = 0.0F;
  } else {
    rtb_Sum4 = (real32_T)fmod(rtb_Sum4, 65536.0);
  }

  /* Math: '<S21>/Math Function1' incorporates:
   *  DataTypeConversion: '<S21>/Data Type Conversion'
   */
  TM1_RSD_agMotorEAnglePLLNULL_vu16 = (uint16_T)((uint16_T)(rtb_Sum4 < 0.0F ?
    (int32_T)(uint16_T)-(int16_T)(uint16_T)-rtb_Sum4 : (int32_T)(uint16_T)
    rtb_Sum4) % 4096);

  /* Update for UnitDelay: '<S16>/Unit Delay1' */
  TM1_RSD_DW.UnitDelay1_DSTATE = rtb_Merge;
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/* Model step function */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_step(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/TM1_RSD_DSADCDecoder_sys' */
  TM1_RSD_DSADCDecoder_sys();

  /* End of Outputs for SubSystem: '<Root>/TM1_RSD_DSADCDecoder_sys' */

  /* Outputs for Atomic SubSystem: '<Root>/TM1_RSD_CalPwmEAngle_sys' */
  TM1_RSD_CalPwmEAngle_sys();

  /* End of Outputs for SubSystem: '<Root>/TM1_RSD_CalPwmEAngle_sys' */
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/* Model initialize function */

/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */

  /* custom signals */
  TM1_uDsadcCosValVol_vf32 = 0.0F;
  TM1_uDsadcSinValVol_vf32 = 0.0F;
  TM1_RSD_agErrEAngleNULL_vf32 = 0.0F;
  TM1_RSD_agESpdPIDrads_vf32 = 0.0F;
  TM1_RSD_nESpdPIDrads_vf32 = 0.0F;
  TM1_RSD_nMSpdPIDrads_vf32 = 0.0F;
  TM1_RSD_nMotorMSpdrpm_vf32 = 0.0F;
  TM1_RSD_nMotorESpdDSADCrads_vf32 = 0.0F;
  TM1_RSD_timDSADCTimeComps_vf32 = 0.0F;
  TM1_RSD_cntMotorEAngleDSADCNULL_vu16 = 0U;
  TM1_RSD_timDSADCEAngleAtanNULL_vu16 = 0U;
  TM1_RSD_agMotorEAnglePLLNULL_vu16 = 0U;

  /* states (dwork) */
  (void) memset((void *)&TM1_RSD_DW, 0,
                sizeof(DW_TM1_RSD_T));
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/* Model terminate function */
/*flash code*/
#define TM1_RSD_CODE_START
//#include "TM1_RSD_MemMap.h"

void TM1_RSD_terminate(void)
{
  /* (no terminate code required) */
}

#define TM1_RSD_CODE_STOP
//#include "TM1_RSD_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
