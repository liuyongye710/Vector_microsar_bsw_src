#ifndef RTW_HEADER_SWC_BCC_IG_FQ_types_h_
#define RTW_HEADER_SWC_BCC_IG_FQ_types_h_
#include "rtwtypes.h"

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

#ifndef DEFINED_TYPEDEF_FOR_MPC_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_MPC_BUS_FQ_

typedef struct {
  real32_T MPC_LdSubLq;
  real32_T MPC_Ld;
  real32_T MPC_Lq;
  real32_T MPC_Rs;
  real32_T MPC_TrqMech;
  real32_T MPC_TrqMechFlt;
  real32_T MPC_psiExc;
  real32_T MPC_IsFlt;
  real32_T MPC_idActFlt;
  real32_T MPC_iqActFlt;
  real32_T MPC_dtCorFac;
  real32_T MPC_isdMTPA;
  real32_T MPC_isdFF;
  real32_T MPC_isdMTPV;
  real32_T MPC_OmBw;
  real32_T MPC_Rv;
  real32_T MPC_frqPwmVF;
  real32_T MPC_CofRandomPwm;
} MPC_BUS_FQ;

#endif

#ifndef DEFINED_TYPEDEF_FOR_HSPF_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_HSPF_BUS_FQ_

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
} HSPF_BUS_FQ;

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

#ifndef DEFINED_TYPEDEF_FOR_BCC_BUS_FQ_
#define DEFINED_TYPEDEF_FOR_BCC_BUS_FQ_

typedef struct {
  real32_T BCC_iDcLnkEst;
  real32_T BCC_tIGBTTj;
  real32_T BCC_tCoolantTj;
} BCC_BUS_FQ;

#endif

typedef struct tag_RTM_SWC_BCC_IG_FQ_T RT_MODEL_SWC_BCC_IG_FQ_T;

#endif

