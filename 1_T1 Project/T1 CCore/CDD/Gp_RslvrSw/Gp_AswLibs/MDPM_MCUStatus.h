/*
 * File: MDPM_MCUStatus.h
 *
 * Code generated for Simulink model 'GCU_MDFC'.
 *
 * Model version                  : 1.39
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat May 21 21:42:21 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MDPM_MCUStatus_h_
#define RTW_HEADER_MDPM_MCUStatus_h_
#include "rtwtypes.h"

typedef enum {
  MDPM_IDLE = 0,                       /* Default value */
  MDPM_PRECHARGE,
  MDPM_PRECHARGEOK,
  MDPM_AFTERRUN1,
  MDPM_AFTERRUN2,
  MDPM_AFTERRUN3,
  MDPM_AFTERRUN4
} MDPM_MCUStatus;

#endif                                 /* RTW_HEADER_MDPM_MCUStatus_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
