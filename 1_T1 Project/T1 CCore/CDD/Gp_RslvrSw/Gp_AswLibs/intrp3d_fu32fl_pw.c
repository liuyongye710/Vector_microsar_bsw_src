/*
 * File: intrp3d_fu32fl_pw.c
 *
 * Code generated for Simulink model 'TM1_MDCM'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:35:05 2022
 */

#include "rtwtypes.h"
//#include "intrp3d_fu32fl_pw.h"

/*flash ´úÂë¶Î*/
#define TM1_MDCM_CODE_START
//#include "TM1_MDCM_MemMap.h"

real32_T intrp3d_fu32fl_pw(const uint32_T bpIndex[], const real32_T frac[],
  const real32_T table[], const uint32_T stride[])
{
  real32_T yL_2d;
  uint32_T offset_2d;
  real32_T yL_1d;
  uint32_T offset_0d;

  /* Column-major Interpolation 3-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  offset_2d = ((bpIndex[2U] * stride[2U]) + (bpIndex[1U] * stride[1U])) +
    bpIndex[0U];
  yL_1d = ((table[offset_2d + 1U] - table[offset_2d]) * frac[0U]) +
    table[offset_2d];
  offset_0d = offset_2d + stride[1U];
  yL_2d = (((((table[offset_0d + 1U] - table[offset_0d]) * frac[0U]) +
             table[offset_0d]) - yL_1d) * frac[1U]) + yL_1d;
  offset_2d += stride[2U];
  yL_1d = ((table[offset_2d + 1U] - table[offset_2d]) * frac[0U]) +
    table[offset_2d];
  offset_0d = offset_2d + stride[1U];
  return ((((((((table[offset_0d + 1U] - table[offset_0d]) * frac[0U]) +
               table[offset_0d]) - yL_1d) * frac[1U]) + yL_1d) - yL_2d) * frac
          [2U]) + yL_2d;
}

#define TM1_MDCM_CODE_STOP
//#include "TM1_MDCM_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
