#ifndef RTW_HEADER_SWC_SCF_IG_types_h_
#define RTW_HEADER_SWC_SCF_IG_types_h_
#include "rtwtypes.h"

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

typedef struct tag_RTM_SWC_SCF_IG_T RT_MODEL_SWC_SCF_IG_T;

#endif

