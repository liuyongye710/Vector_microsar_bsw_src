/*
 * File: linsearch_u32f.c
 *
 * Code generated for Simulink model 'TM1_MDCM'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:35:05 2022
 */

#include "rtwtypes.h"
#include "linsearch_u32f.h"

/*flash ´úÂë¶Î*/
#define TM1_MDCM_CODE_START
//#include "TM1_MDCM_MemMap.h"

uint32_T linsearch_u32f(real32_T u, const real32_T bp[], uint32_T startIndex)
{
  uint32_T bpIndex;

  /* Linear Search */
  for (bpIndex = startIndex; u < bp[bpIndex]; bpIndex--)
  {
  }

  while (u >= bp[bpIndex + 1U])
  {
    bpIndex++;
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
