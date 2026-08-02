/*
 * File: SWC_MDF_IG.h
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

#ifndef RTW_HEADER_SWC_MDF_IG_h_
#define RTW_HEADER_SWC_MDF_IG_h_
#include <math.h>
#ifndef SWC_MDF_IG_COMMON_INCLUDES_
#define SWC_MDF_IG_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* SWC_MDF_IG_COMMON_INCLUDES_ */

#include "SWC_MDF_IG_types.h"

/* Exported data define */

/* Definition for custom storage class: Define */
#define MDF_GLB_IGBTrun_u8             3U                        /* Referenced by:
                                                                  * '<S13>/MDF_GLB_IGBTrun_u8'
                                                                  * '<S28>/MDF_GLB_IGBTrun_u8'
                                                                  */

/* PWM run状态 */
#define MDF_GLB_MotorPole_u8           4U                        /* Referenced by: '<S3>/MDF_GLB_MotorPole_u8' */
#define MDF_GLB_pi_f32                 3.14159203F               /* Referenced by:
                                                                  * '<S37>/MDF_GLB_pi_f32'
                                                                  * '<S15>/MDF_GLB_pi_f32'
                                                                  * '<S19>/MDF_GLB_pi_f32'
                                                                  */

/* GLB_Pi */

/* Block signals for model 'SWC_MDF_IG' */
#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  uint8_T Switch1;                     /* '<S29>/Switch1' */
  uint8_T Switch1_j;                   /* '<S27>/Switch1' */
  uint8_T Switch1_g;                   /* '<S14>/Switch1' */
} B_SWC_MDF_IG_c_T;

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

/* Block states (default storage) for model 'SWC_MDF_IG' */
#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay1_DSTATE;          /* '<S16>/Unit Delay1' */
  real32_T UnitDelay_DSTATE;           /* '<S31>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_k;        /* '<S31>/Unit Delay1' */
  real32_T UnitDelay2_DSTATE;          /* '<S31>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE;          /* '<S31>/Unit Delay3' */
  real32_T UnitDelay_DSTATE_k;         /* '<S32>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_g;        /* '<S32>/Unit Delay1' */
  real32_T UnitDelay2_DSTATE_e;        /* '<S32>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE_o;        /* '<S32>/Unit Delay3' */
  real32_T UnitDelay_DSTATE_m;         /* '<S33>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_f;        /* '<S33>/Unit Delay1' */
  real32_T UnitDelay2_DSTATE_o;        /* '<S33>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE_a;        /* '<S33>/Unit Delay3' */
  real32_T UnitDelay1_DSTATE_gn;       /* '<S30>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_c;         /* '<S19>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_fp;       /* '<S17>/Unit Delay1' */
  uint8_T UnitDelay_DSTATE_n;          /* '<S37>/Unit Delay' */
  boolean_T UnitDelay2_DSTATE_p;       /* '<S16>/Unit Delay2' */
  boolean_T UnitDelay2_DSTATE_g;       /* '<S30>/Unit Delay2' */
  boolean_T UnitDelay_DSTATE_d;        /* '<S27>/Unit Delay' */
  boolean_T UnitDelay2_DSTATE_b;       /* '<S17>/Unit Delay2' */
  boolean_T PhaseFaultCalc_MODE;       /* '<S10>/PhaseFaultCalc' */
} DW_SWC_MDF_IG_f_T;

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

/* Invariant block signals for model 'SWC_MDF_IG' */
#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  const real32_T Abs;                  /* '<S13>/Abs' */
} ConstB_SWC_MDF_IG_h_T;

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_SWC_MDF_IG_T {
  const char_T **errorStatus;
};

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_MDF_IG_T rtm;
} MdlrefDW_SWC_MDF_IG_T;

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T VAR_MDF_OffSetSiteAObs_f32;/* '<S15>/Abs' */
extern real32_T VAR_MDF_OffSetSiteBObs_f32;/* '<S15>/Abs1' */
extern real32_T VAR_MDF_offsetDeltaObs_f32;/* '<S15>/Add2' */
extern real32_T VAR_MDF_3PhaUnbalanceObs_f32;/* '<S34>/Divide' */
extern real32_T VAR_MDF_offsetDeltaFlt_f32;/* '<S18>/Abs1' */
extern uint8_T VAR_MDF_PhaseFaultState_u8;/* '<Root>/Constant3' */
extern uint8_T VAR_MDF_AlOfsNoPlausState_u8;/* '<Root>/Constant6' */
extern uint8_T VAR_MDF_EmacBlkdState_u8;/* '<Root>/Constant1' */
extern uint8_T VAR_MDF_PrfElDrvState_u8;/* '<Root>/Constant4' */
extern uint8_T VAR_MDF_ICtlRatState_u8;/* '<Root>/Constant5' */
extern uint8_T VAR_MDF_OpenCirNoPsblState_u8;/* '<Root>/Constant7' */
extern uint8_T VAR_MDF_DiashCirNoPsblState_u8;/* '<Root>/Constant8' */
extern uint8_T VAR_MDF_OperOutdRngState_u8;/* '<Root>/Constant9' */
extern boolean_T VAR_MDF_PhaseFaultChk_b;/* '<S28>/Logical Operator1' */
extern boolean_T VAR_MDF_bAlOfsChk_b;  /* '<S16>/Logical Operator1' */
extern boolean_T VAR_MDF_bPhaseFault_b;/* '<S30>/Logical Operator1' */
extern boolean_T VAR_MDF_bIsOvHiFault_b;/* '<S27>/Relational Operator' */
extern boolean_T VAR_MDF_bAlfOfsNoPlauseFault_b;/* '<S17>/Logical Operator1' */
extern void SWC_MDF_IG_Disable(void);
extern void SWC_MDF_IG(const real32_T *rtu_HSPF_BUS_HSPF_nSlowFlt, const
  real32_T *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const real32_T
  *rtu_MCF_BUS_MCF_udDes, const real32_T *rtu_MCF_BUS_MCF_uqDes, const real32_T *
  rtu_MCF_BUS_MCF_dtPwm, const real32_T *rtu_MCF_BUS_MCF_iU, const real32_T
  *rtu_MCF_BUS_MCF_iV, const real32_T *rtu_MCF_BUS_MCF_iW, const real32_T
  *rtu_MPC_BUS_MPC_Lq, const real32_T *rtu_MPC_BUS_MPC_Rs, const real32_T
  *rtu_MPC_BUS_MPC_psiExc, const real32_T *rtu_MPC_BUS_MPC_IsFlt, const real32_T
  *rtu_MPC_BUS_MPC_idActFlt, const real32_T *rtu_MPC_BUS_MPC_iqActFlt, const
  real32_T *rtu_Rdc_nWoFlt, const uint8_T *rtu_SCF_BUS_SCF_stGateDrv, const
  uint8_T *rtu_SCF_BUS_SCF_stDrvCtl, uint8_T *rty_MDF_BUS_MDF_stFrwhl, uint8_T
  *rty_MDF_BUS_MDF_bFaultEMBlkWarn, uint8_T *rty_MDF_BUS_MDF_bFaultEMBlkErrS,
  uint8_T *rty_MDF_BUS_MDF_bFaultPwrCmpSt, uint8_T
  *rty_MDF_BUS_MDF_bPhaseFaultSt, uint8_T *rty_MDF_BUS_MDF_bAlfOfsNoPlause,
  uint8_T *rty_MDF_BUS_MDF_bFaultICtlChkSt, uint8_T
  *rty_MDF_BUS_MDF_bOpenCirNoPsblF, uint8_T *rty_MDF_BUS_MDF_bShCirNoPsblFau,
  uint8_T *rty_MDF_BUS_MDF_flagOperOutdRng, uint8_T *rty_MDF_BUS_MDF_IsOvHiErrSt);

/* Model reference registration function */
extern void SWC_MDF_IG_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */
#pragma section ".CAL_CONST"

/* Declaration for custom storage class: iEDS_Parameter */
extern const volatile real32_T CAL_MDF_3PhaUnbalance_f32;
                          /* Referenced by: '<S34>/CAL_MDF_3PhaUnbalance_f32' */

/* 三相不平衡度阈值 */
extern const volatile real32_T CAL_MDF_DIffAlOfsMax_f32;
                           /* Referenced by: '<S18>/CAL_MDF_DIffAlOfsMax_f32' */

/* 角度差值阈值 */
extern const volatile real32_T CAL_MDF_IsMaxSet_f32;
                               /* Referenced by: '<S27>/CAL_MDF_IsMaxSet_f32' */

/* 相电流最大值设定值 */
extern const volatile real32_T CAL_MDF_IsPhaseFault_f32;
                           /* Referenced by: '<S28>/CAL_MDF_IsPhaseFault_f32' */

/* 缺相诊断Is阈值 */
extern const volatile real32_T CAL_MDF_OfsDeltaAgFltFrq_f32;
                       /* Referenced by: '<S18>/CAL_MDF_OfsDeltaAgFltFrq_f32' */

/* 偏移角度差值滤波频率 */
extern const volatile real32_T CAL_MDF_UdcFwMin_f32;
                               /* Referenced by: '<S37>/CAL_MDF_UdcFwMin_f32' */

/* Freewheel状态判断电压阈值 */
extern const volatile real32_T CAL_MDF_UsFrwhlMax_f32;
                             /* Referenced by: '<S37>/CAL_MDF_UsFrwhlMax_f32' */
extern const volatile real32_T CAL_MDF_cofnAbsPhaseFault_Y_af32[46];
                                   /* Referenced by: '<S28>/1-D Lookup Table' */
extern const volatile real32_T CAL_MDF_nAbsPhaseFault_X_af32[46];
                                   /* Referenced by: '<S28>/1-D Lookup Table' */
extern const volatile real32_T CAL_MDF_nAbsPhaseFault_f32;
                         /* Referenced by: '<S28>/CAL_MDF_nAbsPhaseFault_f32' */

/* 缺相故障判断转速绝对值阈值 */
extern const volatile real32_T CAL_MDF_nThresAlOfsNoPlauseFaultMax_f32;
            /* Referenced by: '<S13>/CAL_MDF_nThresAlOfsNoPlauseFaultMax_f32' */

/* 角度合理性诊断转速阈值 */
extern const volatile real32_T CAL_MDF_nThresAlOfsNoPlauseFaultMin_f32;
            /* Referenced by: '<S13>/CAL_MDF_nThresAlOfsNoPlauseFaultMin_f32' */

/* 角度合理性诊断转速阈值 */
extern const volatile uint8_T CAL_MDF_stFrwhlPhd_u8;
                              /* Referenced by: '<S37>/CAL_MDF_stFrwhlPhd_u8' */
extern const volatile uint8_T CAL_MDF_stFrwhlWiIs_u8;
                             /* Referenced by: '<S37>/CAL_MDF_stFrwhlWiIs_u8' */
extern const volatile uint8_T CAL_MDF_stFrwhlWoIs_u8;
                             /* Referenced by: '<S37>/CAL_MDF_stFrwhlWoIs_u8' */
extern const volatile real32_T CAL_MDF_tiAgComp_f32;
                               /* Referenced by: '<S15>/CAL_MDF_tiAgComp_f32' */

/* 角度补偿时间 */
extern const volatile real32_T CAL_MDF_tiAlfOfsNoPlauseFault_f32;
                  /* Referenced by: '<S17>/CAL_MDF_tiAlfOfsNoPlauseFault_f32' */

/* 角度合理性诊断延时时间 */
extern const volatile real32_T CAL_MDF_tiOffsetSteady_f32;
                         /* Referenced by: '<S16>/CAL_MDF_tiOffsetSteady_f32' */

/* 稳态时间阈值 */
extern const volatile real32_T CAL_MDF_tiPhaFaultDelay_f32;
                        /* Referenced by: '<S30>/CAL_MDF_tiPhaFaultDelay_f32' */

/* 缺相诊断故障延时 */
extern const volatile real32_T CAL_MDF_trqOfsNoPlausFault_f32;
                     /* Referenced by: '<S13>/CAL_MDF_trqOfsNoPlausFault_f32' */

/* 角度合理性诊断扭矩需求值阈值 */
#pragma section

#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_MDF_IG_T SWC_MDF_IG_MdlrefDW;

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

#ifndef SWC_MDF_IG_MDLREF_HIDE_CHILD_

/* Block signals (default storage) */
extern B_SWC_MDF_IG_c_T SWC_MDF_IG_B;

/* Block states (default storage) */
extern DW_SWC_MDF_IG_f_T SWC_MDF_IG_DW;

#endif                                 /*SWC_MDF_IG_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Abs1' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Constant' : Unused code path elimination
 * Block '<S6>/Constant' : Unused code path elimination
 * Block '<S38>/CnvFac' : Unused code path elimination
 * Block '<S38>/MDF_GLB_pi_f32' : Unused code path elimination
 * Block '<S38>/Product5' : Unused code path elimination
 * Block '<S39>/Add' : Unused code path elimination
 * Block '<S39>/Add1' : Unused code path elimination
 * Block '<S39>/MDF_GLB_pi_f32' : Unused code path elimination
 * Block '<S39>/Product' : Unused code path elimination
 * Block '<S39>/Product1' : Unused code path elimination
 * Block '<S39>/Product2' : Unused code path elimination
 * Block '<S39>/Product3' : Unused code path elimination
 * Block '<S39>/Product4' : Unused code path elimination
 * Block '<S39>/Product5' : Unused code path elimination
 * Block '<S39>/cnv' : Unused code path elimination
 * Block '<S45>/Constant' : Unused code path elimination
 * Block '<S45>/Constant1' : Unused code path elimination
 * Block '<S45>/MDF_GLB_IGBTrun_u8' : Unused code path elimination
 * Block '<S45>/Relational Operator' : Unused code path elimination
 * Block '<S45>/Switch' : Unused code path elimination
 * Block '<S45>/Switch1' : Unused code path elimination
 * Block '<S45>/Switch2' : Unused code path elimination
 * Block '<S45>/constant' : Unused code path elimination
 * Block '<S46>/Add' : Unused code path elimination
 * Block '<S46>/Add1' : Unused code path elimination
 * Block '<S46>/Add4' : Unused code path elimination
 * Block '<S46>/Add5' : Unused code path elimination
 * Block '<S46>/Add6' : Unused code path elimination
 * Block '<S46>/CAL_MDF_IsErrFlt_f32' : Unused code path elimination
 * Block '<S46>/Constant' : Unused code path elimination
 * Block '<S46>/Product' : Unused code path elimination
 * Block '<S46>/Product1' : Unused code path elimination
 * Block '<S46>/Product4' : Unused code path elimination
 * Block '<S46>/Product6' : Unused code path elimination
 * Block '<S46>/Sqrt1' : Unused code path elimination
 * Block '<S46>/Unit Delay' : Unused code path elimination
 * Block '<S47>/Add' : Unused code path elimination
 * Block '<S47>/Add1' : Unused code path elimination
 * Block '<S47>/CAL_MDF_Pwr3PhaFlt_f32' : Unused code path elimination
 * Block '<S47>/Constant' : Unused code path elimination
 * Block '<S47>/Product' : Unused code path elimination
 * Block '<S47>/Product1' : Unused code path elimination
 * Block '<S47>/Unit Delay' : Unused code path elimination
 * Block '<S48>/Add' : Unused code path elimination
 * Block '<S48>/Add1' : Unused code path elimination
 * Block '<S48>/Add2' : Unused code path elimination
 * Block '<S48>/Add3' : Unused code path elimination
 * Block '<S48>/Add4' : Unused code path elimination
 * Block '<S48>/CAL_MDF_UsErrFlt_f32' : Unused code path elimination
 * Block '<S48>/Constant' : Unused code path elimination
 * Block '<S48>/Product' : Unused code path elimination
 * Block '<S48>/Product3' : Unused code path elimination
 * Block '<S48>/Product4' : Unused code path elimination
 * Block '<S48>/Product5' : Unused code path elimination
 * Block '<S48>/Sqrt' : Unused code path elimination
 * Block '<S48>/Unit Delay' : Unused code path elimination
 * Block '<S49>/Add' : Unused code path elimination
 * Block '<S49>/Add1' : Unused code path elimination
 * Block '<S49>/Add2' : Unused code path elimination
 * Block '<S49>/CAL_MDF_PwrDcLinkEstFlt_f32' : Unused code path elimination
 * Block '<S49>/Constant1' : Unused code path elimination
 * Block '<S49>/Product' : Unused code path elimination
 * Block '<S49>/Product1' : Unused code path elimination
 * Block '<S49>/Product2' : Unused code path elimination
 * Block '<S49>/Unit Delay' : Unused code path elimination
 * Block '<S41>/2-D powloss lookup Table' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S16>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S17>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S30>/Data Type Conversion1' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SWC_MDF_IG'
 * '<S1>'   : 'SWC_MDF_IG/MDF_10ms'
 * '<S2>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc'
 * '<S3>'   : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc'
 * '<S4>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus'
 * '<S5>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaEMBlk'
 * '<S6>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaICtlRat'
 * '<S7>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaIsMax'
 * '<S8>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaOpenCirNoPsbl'
 * '<S9>'   : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaOperOutdRng'
 * '<S10>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault'
 * '<S11>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPrfElDrv'
 * '<S12>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaShCirNoPsbl'
 * '<S13>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/DFCFlag'
 * '<S14>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/OfsNoPlausFaultCalc'
 * '<S15>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc'
 * '<S16>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/DFCFlag/On_Delay'
 * '<S17>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/OfsNoPlausFaultCalc/On_Delay'
 * '<S18>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/OfsNoPlausFaultCalc/mdf_offsetJudge'
 * '<S19>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/OfsNoPlausFaultCalc/mdf_offsetJudge/MDF_DeltaAgFilter'
 * '<S20>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/OfsNoPlausFaultCalc/mdf_offsetJudge/MDF_DeltaAgFilter/Saturation Dynamic'
 * '<S21>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc/Subsystem1'
 * '<S22>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc/Subsystem1/Compare To Constant'
 * '<S23>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc/Subsystem1/Compare To Constant1'
 * '<S24>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc/Subsystem1/Compare To Constant2'
 * '<S25>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc/Subsystem1/Compare To Constant3'
 * '<S26>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaAlOfsNoPlaus/mdf_tanDelta_Calc/Subsystem1/Compare To Constant4'
 * '<S27>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaIsMax/Subsystem'
 * '<S28>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/DFCFlag'
 * '<S29>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc'
 * '<S30>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/On_Delay'
 * '<S31>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/Sum_iU'
 * '<S32>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/Sum_iV'
 * '<S33>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/Sum_iW'
 * '<S34>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/UnbalanceDegCompare'
 * '<S35>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/iPhaMax'
 * '<S36>'  : 'SWC_MDF_IG/MDF_10ms/MDF_Fuc/DiaPhaseFault/PhaseFaultCalc/iPhamin'
 * '<S37>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/FreewheelCalc'
 * '<S38>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/OmMechCalc'
 * '<S39>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/UsdqCalc'
 * '<S40>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc'
 * '<S41>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/pwrlossCalc'
 * '<S42>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/FreewheelCalc/Model Info'
 * '<S43>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/OmMechCalc/Model Info'
 * '<S44>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/UsdqCalc/Model Info'
 * '<S45>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/Us_Is_Select'
 * '<S46>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_IsErrCalc'
 * '<S47>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_Pwr3PhaFlt'
 * '<S48>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_UsErrCalc'
 * '<S49>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_pwr3PhaMdlFildCalc'
 * '<S50>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/Us_Is_Select/Model Info'
 * '<S51>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_IsErrCalc/Model Info'
 * '<S52>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_Pwr3PhaFlt/Model Info'
 * '<S53>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_UsErrCalc/Model Info'
 * '<S54>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/mdf_DiaElDrvCalc/mdf_pwr3PhaMdlFildCalc/Model Info'
 * '<S55>'  : 'SWC_MDF_IG/MDF_10ms/MDF_ParaCalc/pwrlossCalc/Model Info'
 */
#endif                                 /* RTW_HEADER_SWC_MDF_IG_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
