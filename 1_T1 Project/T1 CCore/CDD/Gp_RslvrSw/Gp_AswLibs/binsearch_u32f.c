/*
 * File: binsearch_u32f.c
 *
 * Code generated for Simulink model 'TM2_MDTL'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:31:12 2022
 */

#include "rtwtypes.h"
#include "binsearch_u32f.h"

/*flash ´úÂë¶Î*/
#define TM2_MDTL_CODE_START
//#include "TM2_MDTL_MemMap.h"

uint32_T binsearch_u32f(real32_T u, const real32_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T iRght;
  uint32_T bpIdx;

  /* Binary Search */
  bpIdx = startIndex;
  bpIndex = 0U;
  iRght = maxIndex;
  while ((iRght - bpIndex) > 1U)
  {
    if (u < bp[bpIdx])
    {
      iRght = bpIdx;
    }
    else
    {
      bpIndex = bpIdx;
    }

    bpIdx = ((iRght + bpIndex) >> 1U);
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
