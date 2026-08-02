/*
 * File: intrp1d_fu32fl_pw.c
 *
 * Code generated for Simulink model 'TM2_MDTM'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:32:14 2022
 */

#include "rtwtypes.h"
#include "intrp1d_fu32fl_pw.h"

/*flash ´úÂë¶Î*/
#define TM2_MDTM_CODE_START
//#include "TM2_MDTM_MemMap.h"

real32_T intrp1d_fu32fl_pw(uint32_T bpIndex, real32_T frac, const real32_T
  table[])
{
  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return ((table[bpIndex + 1U] - table[bpIndex]) * frac) + table[bpIndex];
}

#define TM2_MDTM_CODE_STOP
//#include "TM2_MDTM_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
