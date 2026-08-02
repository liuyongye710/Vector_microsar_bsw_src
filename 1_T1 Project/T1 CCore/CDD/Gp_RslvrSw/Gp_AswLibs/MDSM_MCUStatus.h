/*
 * File: MDSM_MCUStatus.h
 *
 * Code generated for Simulink model 'GCU_MDHS'.
 *
 * Model version                  : 1.24
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sat May 21 20:58:29 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MDSM_MCUStatus_h_
#define RTW_HEADER_MDSM_MCUStatus_h_
#include "rtwtypes.h"

typedef enum {
  MDSM_INIT = 1,                       /* Default value */
  MDSM_Ready,
  MDSM_FailureHandle,
  MDSM_TorqueControl,
  MDSM_SpeedControl,
  MDSM_DebugHandle,
  MDSM_ACShortControl,
  MDSM_VoltageControl,
  MDSM_PositionSelfLearning
} MDSM_MCUStatus;

#endif                                 /* RTW_HEADER_MDSM_MCUStatus_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
