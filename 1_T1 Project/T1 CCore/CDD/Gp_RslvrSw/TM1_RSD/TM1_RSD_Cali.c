/*
 * File: TM1_RSD_Cali.c
 *
 * Code generated for Simulink model 'TM1_RSD'.
 *
 * Model version                  : 1.80
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Mon Jun 17 14:05:18 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtwtypes.h"
#include "TM1_RSD_types.h"

/* Exported data definition */
 volatile real32_T TM1_RSD_ratEAngleOffsetNULL_kf32 = 1140.0F;
  volatile boolean_T TM1_RSD_flgManEangleflg_kb = 0;
   volatile real32_T TM1_RSD_nSpeed_Manrpm_kf32 = 0.0F;
/*TM1_RSD Calibration*/
#define TM1_RSD_CONST_FAR_DATA_ALIGN4_CALI_START
//#include "TM1_RSD_MemMap.h"

/* Definition for custom storage class: TM1_RSD_Cali */
//const volatile uint8_T TM1_GLBCal_cntMotorPolePairsNumNULL_ku8 = 4U;
const volatile boolean_T TM1_RSD_TimeStampChange_kb = 0;
const volatile real32_T TM1_RSD_TimeStampOverSet_kf32 = 1.6777216E+7F;
const volatile uint32_T TM1_RSD_cntGPTA0_CLOCKNULL_ku32 =80000000U; //200000000U;
const volatile uint8_T TM1_RSD_cntResolverPolePairsNumNULL_ku8 =6U;
const volatile real32_T TM1_RSD_facMotorMSpdFilterFactorNULL_kf32 = 0.01F;

const volatile real32_T TM1_RSD_frqDSADCycleS_kf32 = 10.2E-5F;


const volatile real32_T TM1_RSD_ratPLLKdNULL_kf32 = 2.0F;
const volatile real32_T TM1_RSD_ratPLLKiNULL_kf32 = 20000.0F;
const volatile real32_T TM1_RSD_ratPLLKpNULL_kf32 = 1500.0F;
const volatile real32_T TM1_RSD_timCurPositSampTErrus_kf32 = 0.0F;
const volatile real32_T TM1_RSD_timtComps_kf32 = 0.0F;

#define TM1_RSD_CONST_FAR_DATA_ALIGN4_CALI_STOP
//#include "TM1_RSD_MemMap.h"

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
