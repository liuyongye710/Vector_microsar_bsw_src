/*
 * File: plook_u32ff_binx.c
 *
 * Code generated for Simulink model 'TM2_MDTL'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:31:12 2022
 */

#include "rtwtypes.h"
#include "binsearch_u32f.h"
#include "plook_u32ff_binx.h"

/*flash ´úÂë¶Î*/
#define TM2_MDTL_CODE_START
//#include "TM2_MDTL_MemMap.h"

uint32_T plook_u32ff_binx(real32_T u, const real32_T bp[], uint32_T maxIndex,
  real32_T *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U])
  {
    bpIndex = 0U;
    *fraction = (u - bp[0U]) / (bp[1U] - bp[0U]);
  }
  else if (u < bp[maxIndex])
  {
    bpIndex = binsearch_u32f(u, bp, maxIndex >> 1U, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  }
  else
  {
    bpIndex = maxIndex - 1U;
    *fraction = (u - bp[maxIndex - 1U]) / (bp[maxIndex] - bp[maxIndex - 1U]);
  }

  return bpIndex;
}

#define TM2_MDTL_CODE_STOP
//#include "TM2_MDTL_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
