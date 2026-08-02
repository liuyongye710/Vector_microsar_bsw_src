/*
 * File: TM1_Global.h
 *
 * Code generated for Simulink model 'TM1_MDHS'.
 *
 * Model version                  : 1.104
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Apr 26 14:22:39 2023
 */

#ifndef RTW_HEADER_TM1_Global_h_
#define RTW_HEADER_TM1_Global_h_
#include "rtwtypes.h"

/*TM1_Global_Calibration*/
#define TM1_Global_CONST_FAR_DATA_ALIGN4_CALI_START
//#include "TM1_Global_MemMap.h"

/* Exported data declaration */
/* Declaration for custom storage class: TM1_Global_Cali */
extern const volatile uint8_T TM1_GLBCal_cntMotorPolePairsNumNULL_ku8;
extern const volatile real32_T TM1_GLBCal_ratEquiFluxNULL_kf32;
extern const volatile real32_T TM1_GLBCal_ratEquiLdNULL_kf32;
extern const volatile real32_T TM1_GLBCal_ratEquiLqNULL_kf32;
extern const volatile real32_T TM1_GLBCal_uDCLinkOverVolErrThdV_kf32;
extern const volatile real32_T TM1_GLBCal_uDCLinkUnderVolErrThdV_kf32;
extern const volatile real32_T TM1_GLBCal_nMotorRatedSpeedrpm_kf32;
extern const volatile real32_T TM1_GLBCal_tqMotorRatedTorqueNm_kf32;
extern const volatile boolean_T TM1_GLBCal_flgUWExchangeflg_kb;
extern const volatile real32_T TM1_GLBCal_tqTorqueUpDownRateNm_kf32;

#define TM1_Global_CONST_FAR_DATA_ALIGN4_CALI_STOP
//#include "TM1_Global_MemMap.h"         /*ConstVariable*/
#define TM1_Global_CONST_FAR_DATA_ALIGN4_START
//#include "TM1_Global_MemMap.h"

/* Declaration for custom storage class: TM1_Global_Const */
extern const real32_T TM1_CosTable12bit_Y[4096];
extern const real32_T TM1_SinTable12bit_Y[4096];

#define TM1_Global_CONST_FAR_DATA_ALIGN4_STOP
//#include "TM1_Global_MemMap.h"
#endif                                 /* RTW_HEADER_TM1_Global_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
