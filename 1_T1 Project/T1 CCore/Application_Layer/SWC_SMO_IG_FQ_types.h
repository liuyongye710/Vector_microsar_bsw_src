#ifndef RTW_HEADER_SWC_SMO_IG_FQ_types_h_
#define RTW_HEADER_SWC_SMO_IG_FQ_types_h_
#include "rtwtypes.h"

#ifndef DEFINED_TYPEDEF_FOR_SCF_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_SCF_BUS_FQ_

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
  uint8_T SCF_stMotor_state;
  uint8_T SCF_flginitEn_Nctl;
  uint8_T SCF_flgZReset;
} SCF_BUS_FQ;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MCF_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_MCF_BUS_FQ_

typedef struct {
  real32_T MCF_idDes;
  real32_T MCF_iqDes;
  real32_T MCF_udDes;
  real32_T MCF_uqDes;
  real32_T MCF_dycU;
  real32_T MCF_dycV;
  real32_T MCF_dycW;
  uint8_T MCF_SecVolt;
  real32_T MCF_frqPwm;
  real32_T MCF_cofFrqPwm;
  real32_T MCF_dtPwm;
  real32_T MCF_tiLock;
  uint8_T MCF_stpwmMode;
  real32_T MCF_Is;
  real32_T MCF_idAct;
  real32_T MCF_iqAct;
  real32_T MCF_uDcLnk;
  real32_T MCF_iU;
  real32_T MCF_iV;
  real32_T MCF_iW;
  real32_T MCF_VoltModuRate;
  real32_T MCF_ialpha;
  real32_T MCF_ibeta;
  real32_T MCF_uAlCalc;
  real32_T MCF_uBCalc;
} MCF_BUS_FQ;

#endif

typedef struct tag_RTM_SWC_SMO_IG_FQ_T RT_MODEL_SWC_SMO_IG_FQ_T;

#endif

