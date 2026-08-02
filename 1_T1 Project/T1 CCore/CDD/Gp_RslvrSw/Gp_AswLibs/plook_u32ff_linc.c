/*
 * File: plook_u32ff_linc.c
 *
 * Code generated for Simulink model 'TM2_MDTM'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:32:14 2022
 */

#include "rtwtypes.h"
#include "linsearch_u32f.h"
#include "plook_u32ff_linc.h"

/*flash ´úÂë¶Î*/
#define TM2_MDTM_CODE_START
//#include "TM2_MDTM_MemMap.h"

uint32_T plook_u32ff_linc(real32_T u, const real32_T bp[], uint32_T maxIndex,
  real32_T *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U])
  {
    bpIndex = 0U;
    *fraction = 0.0F;
  }
  else if (u < bp[maxIndex])
  {
    bpIndex = linsearch_u32f(u, bp, maxIndex >> 1U);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  }
  else
  {
    bpIndex = maxIndex - 1U;
    *fraction = 1.0F;
  }

  return bpIndex;
}

#define TM2_MDTM_CODE_STOP
//#include "TM2_MDTM_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
