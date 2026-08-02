/*
 * File: BINARYSEARCH_real32_T_Above_iR.c
 *
 * Code generated for Simulink model 'TM2_MDSP'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Mar  9 16:07:07 2023
 */

#include "rtwtypes.h"
#include "BINARYSEARCH_real32_T_Above_iR.h"

/*flash ´úÂë¶Î*/
#define TM2_MDSP_CODE_START
//#include "TM2_MDSP_MemMap.h"

/* Lookup Binary Search Utility BINARYSEARCH_real32_T_Above_iR */
void BINARYSEARCH_real32_T_Above_iR(uint32_T *piRght, real32_T u, const real32_T
  *pData, uint32_T iHi)
{
  uint32_T iLeft;

  /* Find the location of current input value in the data table. */
  iLeft = 0U;
  *piRght = iHi;
  if (u <= pData[0] )
  {
    /* Less than or equal to the smallest point in the table. */
    *piRght = 0U;
  }
  else if (u >= pData[iHi] )
  {
    /* Greater than or equal to the largest point in the table. */
  }
  else
  {
    uint32_T i;

    /* Do a binary search. */
    while (( *piRght - iLeft ) > 1U )
    {
      /* Get the average of the left and right indices using to Floor rounding. */
      i = (iLeft + *piRght) >> 1;

      /* Move either the right index or the left index so that */
      /*  LeftDataPoint < CurrentValue <= RightDataPoint */
      if (u <= pData[i] )
      {
        *piRght = i;
      }
      else
      {
        iLeft = i;
      }
    }
  }
}

#define TM2_MDSP_CODE_STOP
//#include "TM2_MDSP_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
