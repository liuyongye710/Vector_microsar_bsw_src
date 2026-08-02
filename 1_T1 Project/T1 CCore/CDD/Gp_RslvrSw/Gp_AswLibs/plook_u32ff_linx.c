/*
 * File: plook_u32ff_linx.c
 *
 * Code generated for Simulink model 'TM1_MDCM'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:35:05 2022
 */

#include "rtwtypes.h"
#include "linsearch_u32f.h"
#include "plook_u32ff_linx.h"

/*flash ´úÂë¶Î*/
#define TM1_MDCM_CODE_START
//#include "TM1_MDCM_MemMap.h"

uint32_T plook_u32ff_linx(real32_T u, const real32_T bp[], uint32_T maxIndex,
  real32_T *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
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
    bpIndex = linsearch_u32f(u, bp, maxIndex >> 1U);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  }
  else
  {
    bpIndex = maxIndex - 1U;
    *fraction = (u - bp[maxIndex - 1U]) / (bp[maxIndex] - bp[maxIndex - 1U]);
  }

  return bpIndex;
}

#define TM1_MDCM_CODE_STOP
//#include "TM1_MDCM_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
