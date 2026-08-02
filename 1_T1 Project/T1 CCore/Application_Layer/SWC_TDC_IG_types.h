#ifndef RTW_HEADER_SWC_TDC_IG_types_h_
#define RTW_HEADER_SWC_TDC_IG_types_h_
#include "rtwtypes.h"

#ifndef DEFINED_TYPEDEF_FOR_TPC_BUS_
#define DEFINED_TYPEDEF_FOR_TPC_BUS_

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
} TPC_BUS;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CSPF_BUS_
#define DEFINED_TYPEDEF_FOR_CSPF_BUS_

typedef struct {
  int16_T Calc_perc_TotDrvTorqRaw;
  int16_T Calc_Nm_TotDrvTorqRaw;
  int16_T Calc_perc_EngPedalRaw;
  uint8_T Calc_st_ParkingBrkSW;
  uint8_T Calc_gear_TransmissionRequestedGear;
  uint8_T Calc_st_EPSwitch;
  uint8_T Calc_st_MsgSwitchC;
  uint8_T Calc_st_MsgSwitchL;
  uint8_T Calc_bool_FootBrake;
  uint8_T Calc_st_HCUReqInhibitSftGear;
  uint8_T Calc_st_HCUReqAutoChgN;
  uint8_T Calc_mod_HCUReqMotWorkMode;
  uint8_T Calc_st_HCUReqMotRotaDir;
  real32_T Nm_HCUReqMCUTq;
  real32_T rpm_HCUReqMCUSpd;
  uint8_T Calc_st_HCUAllowMotWorkEn;
  uint8_T Calc_st_NegtvRelayState;
  uint8_T Calc_st_PostvRelayState;
  uint8_T Calc_st_PreChargHiVoltRelayState;
  uint8_T Calc_st_HCUReqHiPowerOff;
  boolean_T Calc_st_ActvDischgCommand;
  int16_T Calc_rpm_TMCurAvalMaxSpeed;
  uint8_T Calc_mod_HCUMCU2ReqMotWorkMode;
  uint8_T Calc_st_HCUMCU2ReqMotRotaDir;
  int16_T Nm_HCUMCU2ReqMCUTq;
  int16_T rpm_HCUMCU2ReqMCUSpd;
  uint8_T Calc_st_HCUMCU2AllowMotWorkEn;
  uint8_T Calc_st_MCU2NegtvRelayState;
  uint8_T Calc_st_MCU2PostvRelayState;
  uint8_T Calc_st_MCU2PreChargHiVoltRelayState;
  uint8_T Calc_st_HCUMCU2ReqHiPowerOff;
  uint8_T Calc_st_MCU2ActvDischgCommand;
  int16_T Calc_rpm_MCU2TMCurAvalMaxSpeed;
  int16_T Calc_Nm_ReferenceMCTorque;
  uint8_T Calc_gear_HTransmissionRequestedGear;
  uint8_T Calc_st_TCHandEPSwitch;
  uint8_T Calc_st_ShiftInProcess;
  int16_T Calc_z_ETC2GearRatio;
  uint8_T Calc_gear_ETC2SelectGear;
  uint8_T Calc_gear_ETC2CurrentGear;
  uint8_T Calc_st_MtrOverridConMode;
  uint8_T Calc_st_MtrReqSpdContCond;
  uint8_T Calc_st_MtrOverrideConModePriority;
  int16_T Calc_rpm_MtrReqSpdLimit;
  int16_T Cale_Nm_MtrReqTqLimit;
  int16_T Calc_Nm_MtrReqTqFric;
  uint8_T Calc_st_Mtr2OverridConMode;
  uint8_T Calc_st_Mtr2ReqSpdContCond;
  uint8_T Calc_st_Mtr2OverrideConModePriority;
  int16_T Calc_rpm_Mtr2ReqSpdLimit;
  int16_T Calc_Nm_Mtr2ReqTqLimit;
  int16_T Calc_Nm_Mtr2ReqTqFric;
} CSPF_BUS;

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

#ifndef DEFINED_TYPEDEF_FOR_TDC_BUS_
#define DEFINED_TYPEDEF_FOR_TDC_BUS_

typedef struct {
  real32_T TDC_TrqDes;
  boolean_T TDC_flgTrqLmtActv;
} TDC_BUS;

#endif

typedef struct tag_RTM_SWC_TDC_IG_T RT_MODEL_SWC_TDC_IG_T;

#endif

