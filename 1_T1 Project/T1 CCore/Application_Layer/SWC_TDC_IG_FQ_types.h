#ifndef RTW_HEADER_SWC_TDC_IG_FQ_types_h_
#define RTW_HEADER_SWC_TDC_IG_FQ_types_h_
#include "rtwtypes.h"

#ifndef DEFINED_TYPEDEF_FOR_TPC_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_TPC_BUS_FQ_

typedef struct {
  real32_T TPC_TrqMax;
  real32_T TPC_TrqMin;
  boolean_T TPC_bDernExcMax;
  boolean_T TPC_bDernExcMin;
  boolean_T TPC_bDernStrTemp;
  boolean_T TPC_bDernDbcTemp;
  boolean_T TPC_bDernCoolantTemp;
  boolean_T TPC_bDernDrvBoardTemp;
  boolean_T TPC_bDernMtrSpd;
  boolean_T TPC_bDernUndrUdc;
  boolean_T TPC_bDernOvrUdc;
  boolean_T TPC_bDernCAN;
  uint8_T TPC_stTrqEmMax;
  uint8_T TPC_stTrqEmMin;
  uint8_T TPC_stMotorMod;
  real32_T TPC_TDbcTrqMax;
  uint8_T TPC_SgnRotDir;
  uint8_T TPC_SgnTrqMechDir;
  boolean_T TPC_bDernElecOvrIdc;
  boolean_T TPC_bDernGenOvrIdc;
  boolean_T TPC_bDernOvrIdc;
  real32_T TPC_TrqMaxTrans;
  real32_T TPC_TrqMinTrans;
  boolean_T TPC_bDernIGBTTemp;
} TPC_BUS_FQ;

#endif

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

#ifndef DEFINED_TYPEDEF_FOR_TDC_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_TDC_BUS_FQ_

typedef struct {
  real32_T TDC_TrqDes;
  boolean_T TDC_flgTrqLmtActv;
} TDC_BUS_FQ;

#endif

typedef struct tag_RTM_SWC_TDC_IG_FQ_T RT_MODEL_SWC_TDC_IG_FQ_T;

#endif

