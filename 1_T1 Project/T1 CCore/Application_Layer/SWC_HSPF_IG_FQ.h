#ifndef RTW_HEADER_SWC_HSPF_IG_FQ_h_
#define RTW_HEADER_SWC_HSPF_IG_FQ_h_
#include <math.h>
#ifndef SWC_HSPF_IG_FQ_COMMON_INCLUDES_
#define SWC_HSPF_IG_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_HSPF_IG_FQ_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

#define CAL_Hspf_Failure_u8_FQ         3U
#define CAL_Hspf_Succeed_u8_FQ         2U
#define CAL_Hspf_Uncheck_u8_FQ         0U
#define GLB_HspfFlt_pi_f32_FQ          3.14159203F
#define PRV_CalFltFrq_10ms_FQ          100U

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  uint8_T stiOfsClb;
  uint8_T stiOfsClb_d;
  uint8_T stiOfsClb_o;
  boolean_T LogicalOperator2;
  boolean_T flgOfsClb;
  boolean_T flgOfsClb_j;
  boolean_T flgOfsClb_g;
} B_SWC_HSPF_IG_FQ_c_T;

#endif

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  real_T UnitDelay_DSTATE;
  real_T UnitDelay2_DSTATE;
  real_T UnitDelay2_DSTATE_g;
  real_T UnitDelay2_DSTATE_gn;
  real_T UnitDelay1_DSTATE;
  real32_T UnitDelay_DSTATE_b;
  real32_T UnitDelay1_DSTATE_n;
  real32_T UnitDelay3_DSTATE;
  real32_T UnitDelay_DSTATE_n;
  real32_T UnitDelay1_DSTATE_m;
  real32_T UnitDelay3_DSTATE_b;
  real32_T UnitDelay_DSTATE_a;
  real32_T UnitDelay1_DSTATE_i;
  real32_T UnitDelay3_DSTATE_l;
  real32_T UnitDelay_DSTATE_bw;
  real32_T UnitDelay_DSTATE_h;
  real32_T UnitDelay_DSTATE_m;
  real32_T UnitDelay_DSTATE_d;
  real32_T UnitDelay_DSTATE_j;
  real32_T UnitDelay_DSTATE_o;
  real32_T UnitDelay_DSTATE_e;
  real32_T UnitDelay_DSTATE_m4;
  real32_T UnitDelay_DSTATE_l;
  real32_T UnitDelay1_DSTATE_nw;
  real32_T UnitDelay2_DSTATE_a;
  real32_T UnitDelay3_DSTATE_f;
  real32_T UnitDelay4_DSTATE;
  real32_T UnitDelay5_DSTATE;
  real32_T UnitDelay6_DSTATE;
  real32_T UnitDelay7_DSTATE;
  real32_T UnitDelay8_DSTATE;
  real32_T UnitDelay_DSTATE_p;
  uint32_T iValSum;
  uint32_T iValSum_i;
  uint32_T iValSum_b;
  uint16_T cntSelfChkTolCnt;
  uint16_T cntSelfChkValCnt;
  uint16_T cntSelfChkTolCnt_i;
  uint16_T cntSelfChkValCnt_k;
  uint16_T cntSelfChkTolCnt_p;
  uint16_T cntSelfChkValCnt_a;
  int8_T UnitDelay_DSTATE_lp;
  int8_T UnitDelay_DSTATE_a2;
  int8_T UnitDelay_DSTATE_oy;
  int8_T UnitDelay_DSTATE_g;
  int8_T UnitDelay_DSTATE_ms;
  boolean_T UnitDelay4_DSTATE_a;
  boolean_T UnitDelay4_DSTATE_b;
  boolean_T UnitDelay4_DSTATE_m;
  boolean_T UnitDelay_DSTATE_f;
  boolean_T UnitDelay1_DSTATE_j;
  boolean_T UnitDelay3_DSTATE_h;
  boolean_T UnitDelay2_DSTATE_av;
  boolean_T UnitDelay1_DSTATE_jb;
  boolean_T UnitDelay3_DSTATE_p;
  boolean_T UnitDelay2_DSTATE_f;
  boolean_T UnitDelay1_DSTATE_e;
  boolean_T UnitDelay3_DSTATE_hn;
  boolean_T UnitDelay2_DSTATE_gr;
  boolean_T UnitDelay1_DSTATE_c;
  boolean_T UnitDelay3_DSTATE_p0;
  boolean_T UnitDelay2_DSTATE_d;
  boolean_T UnitDelay3_DSTATE_e;
  boolean_T UnitDelay2_DSTATE_m;
  boolean_T UnitDelay_DSTATE_pp;
  uint8_T is_active_c6_SWC_HSPF_IG_FQ;
  uint8_T is_c6_SWC_HSPF_IG_FQ;
  uint8_T is_active_c4_SWC_HSPF_IG_FQ;
  uint8_T is_c4_SWC_HSPF_IG_FQ;
  uint8_T is_active_c3_SWC_HSPF_IG_FQ;
  uint8_T is_c3_SWC_HSPF_IG_FQ;
} DW_SWC_HSPF_IG_FQ_f_T;

#endif

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  const real_T Divide;
  const real_T Divide1;
  const boolean_T LogicalOperator1;
  const boolean_T LogicalOperator;
  const boolean_T LogicalOperator4;
  const boolean_T LogicalOperator2;
  const boolean_T LogicalOperator5;
  const boolean_T LogicalOperator6;
  const boolean_T LogicalOperator3;
  const boolean_T Compare;
  const boolean_T Compare_j;
  const boolean_T LogicalOperator1_f;
} ConstB_SWC_HSPF_IG_FQ_h_T;

#endif

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_HSPF_IG_FQ_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_HSPF_IG_FQ_T rtm;
} MdlrefDW_SWC_HSPF_IG_FQ_T;

#endif

extern real32_T VAR_Hspf_uKl30_f32_FQ;
extern boolean_T VAR_Bsw_bt15_b_FQ;
extern real32_T HSPF_uKl30Flt_FQ;
extern real32_T VAR_Hspf_tDBCTempU_f32_FQ;
extern real32_T HSPF_tDBCTempUFlt_FQ;
extern real32_T VAR_Hspf_tDBCTempV_f32_FQ;
extern real32_T HSPF_tDBCTempVFlt_FQ;
extern real32_T VAR_Hspf_tDBCTempW_f32_FQ;
extern real32_T HSPF_tDBCTempWFlt_FQ;
extern real32_T HSPF_tStrrTemp1Flt_FQ;
extern real32_T HSPF_tStrrTemp2Flt_FQ;
extern real32_T HSPF_nSlowFlt_FQ;
extern real32_T HSPF_tCoolantTempFlt_FQ;
extern real32_T HSPF_tDrvBoardTempFlt_FQ;
extern real32_T HSPF_iDcLnkEstFlt_FQ;
extern real32_T VAR_Hspf_uDcLnk_f32_FQ;
extern real32_T HSPF_uDcLnkSlowFlt_FQ;
extern real32_T HSPF_PwrDcLnk_FQ;
extern real32_T HSPF_tStrrTempFlt_FQ;
extern real32_T HSPF_tIGBTTjFlt_FQ;
extern real32_T HSPF_tCoolantTjFlt_FQ;
extern real32_T VAR_Bsw_tCoolantTemp_f32_FQ;
extern real32_T VAR_Hspf_tCoolantTemp_f32_FQ;
extern real32_T VAR_Hspf_tDrvBoardTemp_f32_FQ;
extern real32_T HSPF_iPhaWOffset_FQ;
extern real32_T HSPF_iPhaVOffset_FQ;
extern real32_T HSPF_iPhaUOffset_FQ;
extern uint16_T VAR_Bsw_tDBCTempU_u16_FQ;
extern uint16_T VAR_Bsw_tDBCTempV_u16_FQ;
extern uint16_T VAR_Bsw_tDBCTempW_u16_FQ;
extern uint16_T VAR_Bsw_tStrrTemp1_u16_FQ;
extern uint16_T VAR_Bsw_tStrrTemp2_u16_FQ;
extern uint16_T VAR_Bsw_tDrvBoardTemp_u16_FQ;
extern int16_T VAR_Hspf_tStrrTemp2_s16_FQ;
extern int16_T VAR_Hspf_tStrrTemp1_s16_FQ;
extern uint8_T HSPF_tDBCTempCmpErrSt_FQ;
extern uint8_T HSPF_MotorOpenErrSt_FQ;
extern uint8_T HSPF_InvOpenErrSt_FQ;
extern uint8_T HSPF_stIphaOffCal_FQ;
extern uint8_T HSPF_checkstatus_FQ;
extern boolean_T VAR_Hspf_bSwtTempSttr2_b_FQ;
extern boolean_T HSPF_bt15_FQ;
extern boolean_T HSPF_Crash_FQ;
extern boolean_T HSPF_INV_Open_FQ;
extern boolean_T HSPF_Motor_Open_FQ;
extern boolean_T HSPF_Wake_FQ;
extern boolean_T VAR_Hspf_tDBCCmpErrDelay_b_FQ;
extern boolean_T VAR_Hspf_bSwtTempSttr1_b_FQ;
extern boolean_T VAR_Bsw_Wake_b_FQ;
extern boolean_T VAR_Bsw_Crash_b_FQ;
extern boolean_T VAR_Bsw_INV_Open_b_FQ;
extern boolean_T VAR_Bsw_Motor_Open_b_FQ;
extern boolean_T VAR_Hspf_flgSttr1NoErr_b_FQ;
extern boolean_T VAR_Hspf_flgSttr2NoErr_b_FQ;
extern void SWC_HSPF_IG_FQ_Init(void);
extern void SWC_HSPF_IG_FQ(const real32_T *rtu_BSW_uDcLnk, const real32_T
  *rtu_BCC_BUS_BCC_iDcLnkEst, const real32_T *rtu_Rdc_nWoFlt, const uint16_T
  *rtu_BSW_tDBCTempU, const uint16_T *rtu_BSW_tDBCTempV, const uint16_T
  *rtu_BSW_tDBCTempW, const uint16_T *rtu_BSW_iUNoOff, const uint16_T
  *rtu_BSW_iVNoOff, const uint16_T *rtu_BSW_iWNoOff, const uint8_T
  *rtu_SCF_BUS_SCF_stPreDrvCtl, real32_T *rty_HSPF_BUS_HSPF_uKl30Flt, real32_T
  *rty_HSPF_BUS_HSPF_tDBCTempUFlt, real32_T *rty_HSPF_BUS_HSPF_tDBCTempVFlt,
  real32_T *rty_HSPF_BUS_HSPF_tDBCTempWFlt, real32_T
  *rty_HSPF_BUS_HSPF_tStrrTemp1Flt, real32_T *rty_HSPF_BUS_HSPF_tStrrTemp2Flt,
  real32_T *rty_HSPF_BUS_HSPF_nSlowFlt, real32_T
  *rty_HSPF_BUS_HSPF_tCoolantTempF, real32_T *rty_HSPF_BUS_HSPF_tDrvBoardTemp,
  real32_T *rty_HSPF_BUS_HSPF_iDcLnkEstFlt, real32_T *rty_HSPF_BUS_HSPF_PwrDcLnk,
  boolean_T *rty_HSPF_BUS_HSPF_bt15, boolean_T *rty_HSPF_BUS_HSPF_Crash,
  boolean_T *rty_HSPF_BUS_HSPF_INV_Open, boolean_T *rty_HSPF_BUS_HSPF_Motor_Open,
  real32_T *rty_HSPF_BUS_HSPF_uDcLnkSlowFlt, boolean_T *rty_HSPF_BUS_HSPF_Wake,
  real32_T *rty_HSPF_BUS_HSPF_iPhaUOffset, real32_T
  *rty_HSPF_BUS_HSPF_iPhaVOffset, real32_T *rty_HSPF_BUS_HSPF_iPhaWOffset,
  uint8_T *rty_HSPF_BUS_HSPF_stIphaOffCal, real32_T
  *rty_HSPF_BUS_HSPF_tStrrTempFlt, real32_T *rty_HSPF_BUS_HSPF_tIGBTTjFlt,
  real32_T *rty_HSPF_BUS_HSPF_tCoolantTjFlt, real32_T
  *rty_HSPF_BUS_HSPF_VerMatchFailu, uint8_T *rty_HSPF_BUS_HSPF_tDBCTempCmpEr,
  uint8_T *rty_HSPF_BUS_HSPF_MotorOpenErrS, uint8_T
  *rty_HSPF_BUS_HSPF_InvOpenErrSt, uint8_T *rty_HSPF_BUS_HSPF_checkstatus,
  boolean_T *rty_HSPF_BUS_HSPF_bSwtTempSttr1, boolean_T
  *rty_HSPF_BUS_HSPF_bSwtTempSttr2);
extern void SWC_HSPF_IG_FQ_initialize(const char_T **rt_errorStatus);

#pragma section ".CAL_CONST"

extern const volatile real32_T CAL_Hspf_CltInletTempFltFrq_f32_FQ;
extern const volatile uint8_T CAL_Hspf_CrashChkAddCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_CrashChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_CrashChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_CrashChkSubCnt_s8_FQ;
extern const volatile uint8_T CAL_Hspf_DBCTempROCLimChkCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_INVOpenChkAddCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_INVOpenChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_INVOpenChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_INVOpenChkSubCnt_s8_FQ;
extern const volatile uint8_T CAL_Hspf_MotTemHigTable_af32_FQ[1024];
extern const volatile int8_T CAL_Hspf_MotTemLowTable_af32_FQ[1024];
extern const volatile uint8_T CAL_Hspf_MotorOpenChkAddCnt_u8_FQ;
extern const volatile uint8_T CAL_Hspf_MotorOpenChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_MotorOpenChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_MototOpenChkSubCnt_s8_FQ;
extern const volatile uint8_T CAL_Hspf_Multiple_u8_FQ;
extern const volatile real32_T CAL_Hspf_TmpCoolanTjFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_TmpUFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_TmpVFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_TmpWFltFrq_f32_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkAddCnt_u8_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkCntHiLim_u8_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkCntLoLim_s8_FQ;
extern const volatile int8_T CAL_Hspf_bt15ChkSubCnt_s8_FQ;
extern const volatile uint16_T CAL_Hspf_cntIPhCalOffTolCnt_u16_FQ;
extern const volatile uint16_T CAL_Hspf_cntIPhCalOffValCnt_u16_FQ;
extern const volatile real32_T CAL_Hspf_iDcLnkEstFltFrq_f32_FQ;
extern const volatile uint16_T CAL_Hspf_iPhaHighSet_u16_FQ;
extern const volatile uint16_T CAL_Hspf_iPhaLowSet_u16_FQ;
extern const volatile real32_T CAL_Hspf_nFltFrq_f32_FQ;
extern const volatile uint8_T CAL_Hspf_stPreDrvCtl_u8_FQ;
extern const volatile real32_T CAL_Hspf_tCoolantFltFrq_f32_FQ;
extern const volatile uint16_T CAL_Hspf_tDBCCmpTime_u16_FQ;
extern const volatile uint8_T CAL_Hspf_tDBCTempROCLim_u8_FQ;
extern const volatile uint8_T CAL_Hspf_tDBCtempOffset_u8_FQ;
extern const volatile real32_T CAL_Hspf_tStrrTmp1FltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_tStrrTmp2FltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_tSwtTempSttrHiLim_f32_FQ;
extern const volatile real32_T CAL_Hspf_tSwtTempSttrLoLim_f32_FQ;
extern const volatile real32_T CAL_Hspf_uDcLnkFltFrq_f32_FQ;
extern const volatile real32_T CAL_Hspf_uKl30FltFrq_f32_FQ;

#pragma section

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_HSPF_IG_FQ_T SWC_HSPF_IG_FQ_MdlrefDW;

#endif

#ifndef SWC_HSPF_IG_FQ_MDLREF_HIDE_CHILD_

extern B_SWC_HSPF_IG_FQ_c_T SWC_HSPF_IG_FQ_B;
extern DW_SWC_HSPF_IG_FQ_f_T SWC_HSPF_IG_FQ_DW;

#endif
#endif

