/*
 * File: rt_modf.c
 *
 * Code generated for Simulink model 'TM2_MDSA'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Dec  6 09:28:08 2022
 */

#include "rtwtypes.h"
#include <float.h>
#include <math.h>
#include "rt_modf.h"

/*flash ´úÂë¶Î*/
#define TM2_MDSA_CODE_START
//#include "TM2_MDSA_MemMap.h"

real32_T rt_modf(real32_T u0, real32_T u1)
{
  real32_T y;
  boolean_T yEq;
  real32_T q;
  y = u0;
  if (u0 == 0.0F)
  {
    y = 0.0F;
  }
  else
  {
    if (u1 != 0.0F)
    {
      y = (real32_T)fmod((real_T)u0, (real_T)u1);
      yEq = (boolean_T)(y == 0.0F);
      if ((!((int32_T)yEq)) && (u1 > ((real32_T)floor((real_T)u1))))
      {
        q = (real32_T)fabs((real_T)(u0 / u1));
        yEq = (boolean_T)(((real32_T)fabs((real_T)(q - ((real32_T)floor((real_T)
          (q + 0.5F)))))) <= (FLT_EPSILON * q));
      }

      if (yEq)
      {
        y = 0.0F;
      }
      else
      {
        if ((u0 < 0.0F) != (u1 < 0.0F))
        {
          y += u1;
        }
      }
    }
  }

  return y;
}

#define TM2_MDSA_CODE_STOP
//#include "TM2_MDSA_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
