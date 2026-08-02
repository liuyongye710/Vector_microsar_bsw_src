/*
 * File: look1_iflf_binlcpw.c
 *
 * Code generated for Simulink model 'TM1_MDFM'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:38:23 2022
 */

#include "rtwtypes.h"
#include "look1_iflf_binlcpw.h"

/*flash ´úÂë¶Î*/
#define TM1_MDFM_CODE_START
//#include "TM1_MDFM_MemMap.h"

real32_T look1_iflf_binlcpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex)
{
  real32_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U])
  {
    iLeft = 0U;
    frac = 0.0F;
  }
  else if (u0 < bp0[maxIndex])
  {
    /* Binary Search */
    bpIdx = (maxIndex >> 1U);
    iLeft = 0U;
    iRght = maxIndex;
    while ((iRght - iLeft) > 1U)
    {
      if (u0 < bp0[bpIdx])
      {
        iRght = bpIdx;
      }
      else
      {
        iLeft = bpIdx;
      }

      bpIdx = ((iRght + iLeft) >> 1U);
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  }
  else
  {
    iLeft = maxIndex - 1U;
    frac = 1.0F;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return ((table[iLeft + 1U] - table[iLeft]) * frac) + table[iLeft];
}

#define TM1_MDFM_CODE_STOP
//#include "TM1_MDFM_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
