/*
 * File: intrp2d_l_pw.c
 *
 * Code generated for Simulink model 'TM2_MDTL'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:31:12 2022
 */

#include "rtwtypes.h"
#include "intrp2d_l_pw.h"

/*flash ´úÂë¶Î*/
#define TM2_MDTL_CODE_START
//#include "TM2_MDTL_MemMap.h"

real_T intrp2d_l_pw(const uint32_T bpIndex[], const real_T frac[], const real_T
                    table[], const uint32_T stride)
{
  real_T yL_1d;
  uint32_T offset_1d;

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  offset_1d = (bpIndex[1U] * stride) + bpIndex[0U];
  yL_1d = ((table[offset_1d + 1U] - table[offset_1d]) * frac[0U]) +
    table[offset_1d];
  offset_1d += stride;
  return (((((table[offset_1d + 1U] - table[offset_1d]) * frac[0U]) +
            table[offset_1d]) - yL_1d) * frac[1U]) + yL_1d;
}

#define TM2_MDTL_CODE_STOP
//#include "TM2_MDTL_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
