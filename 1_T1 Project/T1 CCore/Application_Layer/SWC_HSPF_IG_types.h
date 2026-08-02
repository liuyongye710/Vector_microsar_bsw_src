#ifndef RTW_HEADER_SWC_HSPF_IG_types_h_
#define RTW_HEADER_SWC_HSPF_IG_types_h_
#include "rtwtypes.h"

#ifndef DEFINED_TYPEDEF_FOR_BCC_BUS_
#define DEFINED_TYPEDEF_FOR_BCC_BUS_

typedef struct {
  real32_T BCC_iDcLnkEst;
  real32_T BCC_tIGBTTj;
  real32_T BCC_tCoolantTj;
} BCC_BUS;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SCF_BUS_
#define DEFINED_TYPEDEF_FOR_SCF_BUS_

typedef struct {
  boolean_T SCF_flgDataStrgBgnToBsw;
  uint8_T SCF_stSysCtl;
  uint8_T SCF_stGateDrv;
  uint8_T SCF_stDrvCtl;
  uint8_T SCF_stDisChg;
  uint8_T SCF_stPreDrvCtl;
  boolean_T SCF_flginitPI;
  boolean_T SCF_flgEnDchaToMc;
  uint8_T SCF_stSys;
  uint8_T SCF_stModeReqToTdc;
  uint8_T SCF_stPwmMode;
  boolean_T SCF_flgUdcLowToTpc;
  boolean_T SCF_bHvReady_write;
  boolean_T SCF_flgEmgReqInvDcha;
  boolean_T SCF_flgActvDcha;
  uint8_T SCF_stFFAction;
  uint8_T SCF_FIM_ReqFailrMod;
  boolean_T SCF_LwPwrDwn;
} SCF_BUS;

#endif

#ifndef DEFINED_TYPEDEF_FOR_HSPF_BUS_
#define DEFINED_TYPEDEF_FOR_HSPF_BUS_

typedef struct {
  real32_T HSPF_uKl30Flt;
  real32_T HSPF_tDBCTempUFlt;
  real32_T HSPF_tDBCTempVFlt;
  real32_T HSPF_tDBCTempWFlt;
  real32_T HSPF_tStrrTemp1Flt;
  real32_T HSPF_tStrrTemp2Flt;
  real32_T HSPF_nSlowFlt;
  real32_T HSPF_tCoolantTempFlt;
  real32_T HSPF_tDrvBoardTempFlt;
  real32_T HSPF_iDcLnkEstFlt;
  real32_T HSPF_PwrDcLnk;
  boolean_T HSPF_bt15;
  boolean_T HSPF_Crash;
  boolean_T HSPF_INV_Open;
  boolean_T HSPF_Motor_Open;
  real32_T HSPF_uDcLnkSlowFlt;
  boolean_T HSPF_Wake;
  real32_T HSPF_iPhaUOffset;
  real32_T HSPF_iPhaVOffset;
  real32_T HSPF_iPhaWOffset;
  uint8_T HSPF_stIphaOffCal;
  real32_T HSPF_tStrrTempFlt;
  real32_T HSPF_tIGBTTjFlt;
  real32_T HSPF_tCoolantTjFlt;
  real32_T HSPF_VerMatchFailureErr;
  uint8_T HSPF_tDBCTempCmpErrSt;
  uint8_T HSPF_MotorOpenErrSt;
  uint8_T HSPF_InvOpenErrSt;
  uint8_T HSPF_checkstatus;
  boolean_T HSPF_bSwtTempSttr1;
  boolean_T HSPF_bSwtTempSttr2;
} HSPF_BUS;

#endif

typedef struct tag_RTM_SWC_HSPF_IG_T RT_MODEL_SWC_HSPF_IG_T;

#endif

