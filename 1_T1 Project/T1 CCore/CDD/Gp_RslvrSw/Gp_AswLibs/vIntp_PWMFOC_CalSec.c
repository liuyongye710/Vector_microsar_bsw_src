/*
 * File: vIntp_PWMFOC_CalSec.c
 *
 * Code generated for Simulink model 'TM2_DPWM'.
 *
 * Model version                  : 1.552
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Jun  1 10:22:57 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "vIntp_PWMFOC_CalSec.h"

/* Include model header file for global data */
//#include "TM2_DPWM.h"
//#include "TM2_DPWM_private.h"

/*
 * Output and update for atomic system:
 *    '<S22>/vIntp_PWMFOC_CalSec'
 *    '<S24>/vIntp_PWMFOC_CalSec'
 *    '<S26>/vIntp_PWMFOC_CalSec'
 *    '<S27>/vIntp_PWMFOC_CalSec'
 */
uint8_T vIntp_PWMFOC_CalSec(real32_T rtu_Bus_UalphaUbeta, real32_T
  rtu_Bus_UalphaUbeta_c)
{
  uint8_T rty_N_VALUE_0;

  /* Outputs for Atomic SubSystem: '<S28>/CalVaVbVc' */
  /* DataTypeConversion: '<S31>/Data Type Conversion2' incorporates:
   *  Constant: '<S31>/Constant'
   *  Constant: '<S31>/Constant1'
   *  Constant: '<S37>/1//2'
   *  Constant: '<S37>/Sqrt(3)//2'
   *  Constant: '<S38>/-1//2'
   *  Constant: '<S38>/-Sqrt(3)//2'
   *  DataTypeConversion: '<S31>/Data Type Conversion3'
   *  DataTypeConversion: '<S31>/Data Type Conversion4'
   *  Product: '<S31>/Product'
   *  Product: '<S31>/Product1'
   *  Product: '<S37>/Product1'
   *  Product: '<S37>/Product2'
   *  Product: '<S38>/Product1'
   *  Product: '<S38>/Product2'
   *  SignalConversion: '<S32>/TmpSignal ConversionAtSignal ConversionInport1'
   *  Sum: '<S31>/Add'
   *  Sum: '<S37>/Add'
   *  Sum: '<S38>/Add'
   *  Switch: '<S33>/Switch'
   *  Switch: '<S34>/Switch'
   *  Switch: '<S35>/Switch'
   */
  rty_N_VALUE_0 = (uint8_T)(int32_T)(real32_T)fmod((real32_T)(((int32_T)
    (real32_T)fmod((real32_T)((rtu_Bus_UalphaUbeta * 0.866025F -
    rtu_Bus_UalphaUbeta_c * 0.5F > 0.0F) << 1), 256.0) + (rtu_Bus_UalphaUbeta_c >
    0.0F)) + (int32_T)(real32_T)fmod((real32_T)((rtu_Bus_UalphaUbeta *
    -0.866025F + rtu_Bus_UalphaUbeta_c * -0.5F > 0.0F) << 2), 256.0)), 256.0);

  /* End of Outputs for SubSystem: '<S28>/CalVaVbVc' */
  return rty_N_VALUE_0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
