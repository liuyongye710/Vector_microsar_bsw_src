#ifndef RTW_HEADER_SWC_CSPF_IG_types_h_
#define RTW_HEADER_SWC_CSPF_IG_types_h_
#include "rtwtypes.h"

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

typedef struct tag_RTM_SWC_CSPF_IG_T RT_MODEL_SWC_CSPF_IG_T;

#endif

