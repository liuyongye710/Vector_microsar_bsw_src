/*
 * File: plook_u32ff_evenx.c
 *
 * Code generated for Simulink model 'TM2_MDCM'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Fri May 26 18:38:45 2023
 */

#include "rtwtypes.h"
#include "plook_u32ff_evenx.h"

/*flash ´úÂë¶Î*/
#define TM2_MDCM_CODE_START
//#include "TM2_MDCM_MemMap.h"

uint32_T plook_u32ff_evenx(real32_T u, real32_T bp0, real32_T bpSpace, uint32_T
  maxIndex, real32_T *fraction)
{
  uint32_T bpIndex;
  real32_T invSpc;
  real32_T fbpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'even'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp0)
  {
    bpIndex = 0U;
    *fraction = (u - bp0) / bpSpace;
  }
  else
  {
    invSpc = 1.0F / bpSpace;
    fbpIndex = (u - bp0) * invSpc;
    if (fbpIndex < ((real32_T)maxIndex))
    {
      bpIndex = (uint32_T)fbpIndex;
      *fraction = (u - ((((real32_T)bpIndex) * bpSpace) + bp0)) * invSpc;
    }
    else
    {
      bpIndex = maxIndex - 1U;
      *fraction = (u - ((((real32_T)(maxIndex - 1U)) * bpSpace) + bp0)) * invSpc;
    }
  }

  return bpIndex;
}

#define TM2_MDCM_CODE_STOP
//#include "TM2_MDCM_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
