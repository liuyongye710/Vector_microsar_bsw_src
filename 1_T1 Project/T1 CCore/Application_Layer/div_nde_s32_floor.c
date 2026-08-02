/*
 * File: div_nde_s32_floor.c
 *
 * Code generated for Simulink model 'SWC_CSPF_IG'.
 *
 * Model version                  : 2.22
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Jun  5 10:30:46 2025
 */

#include "rtwtypes.h"
#include "div_nde_s32_floor.h"

int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
