#ifndef RTW_HEADER_SWC_CSPF_IG_h_
#define RTW_HEADER_SWC_CSPF_IG_h_
#ifndef SWC_CSPF_IG_COMMON_INCLUDES_
#define SWC_CSPF_IG_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_CSPF_IG_types.h"

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  int16_T Switch4;
  int16_T Switch3;
  int16_T Switch9;
  int16_T Switch1;
  int16_T Switch4_b;
  int16_T Switch9_e;
  int16_T Switch6;
  int16_T Switch6_a;
  int16_T Switch10;
  int16_T Switch6_i;
  int16_T Switch6_m;
  int16_T Switch4_p;
  int16_T Switch3_o;
  int16_T Switch2;
  int16_T Switch2_j;
  uint8_T Switch6_ib;
  uint8_T Switch10_f;
  uint8_T Switch1_p;
  uint8_T Switch4_n;
  uint8_T Switch6_l;
  uint8_T Switch10_c;
  uint8_T Switch3_f;
  uint8_T Switch2_e;
  uint8_T Switch8;
  uint8_T Switch7;
  uint8_T Switch5;
  uint8_T Switch6_ma;
  uint8_T Switch10_l;
  uint8_T Switch3_d;
  uint8_T Switch2_i;
  uint8_T Switch8_e;
  uint8_T Switch7_d;
  uint8_T Switch5_o;
  uint8_T Switch11;
  uint8_T Switch1_m;
  uint8_T Switch2_p;
  uint8_T Switch6_b;
  uint8_T Switch6_k;
  uint8_T Switch10_a;
  uint8_T Switch10_b;
  uint8_T Switch6_l4;
  uint8_T Switch1_l;
  uint8_T Switch10_h;
  uint8_T Switch6_d;
  uint8_T Switch10_i;
  uint8_T Switch6_ic;
  uint8_T Switch3_g;
  uint8_T Switch2_c;
  uint8_T Switch1_k;
} B_SWC_CSPF_IG_c_T;

#endif

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  const uint32_T Product1;
  const uint32_T Product1_i;
  const uint16_T DataTypeConversion3;
  const uint16_T ShiftArithmetic2;
  const uint16_T Add;
  const uint16_T DataTypeConversion3_n;
  const uint16_T ShiftArithmetic2_d;
  const uint16_T Add_a;
  const uint16_T DataTypeConversion1;
  const uint16_T ShiftArithmetic;
  const uint16_T Add_p;
  const uint16_T DataTypeConversion2;
  const uint16_T ShiftArithmetic3;
  const uint16_T Add2;
  const uint16_T DataTypeConversion4;
  const uint16_T ShiftArithmetic5;
  const uint16_T Subtract2;
  const uint16_T ShiftArithmetic6;
  const uint16_T DataTypeConversion27;
  const uint16_T ShiftArithmetic13;
  const uint16_T Add12;
  const int16_T DataTypeConversion1_k;
  const int16_T Add1;
  const int16_T DataTypeConversion;
  const int16_T Product2;
  const int16_T DataTypeConversion1_p;
  const int16_T Add1_i;
  const int16_T DataTypeConversion_h;
  const int16_T Product2_h;
  const int16_T DataTypeConversion_b;
  const int16_T Product1_a;
  const int16_T Add3;
  const int16_T Saturation1;
  const int16_T Divide8;
  const int16_T DataTypeConversion5;
  const int16_T DataTypeConversion2_c;
  const int16_T Add2_l;
  const int16_T u25125;
  const uint8_T BitwiseOperator1;
  const uint8_T BitwiseOperator2;
  const uint8_T BitwiseOperator3;
  const uint8_T ShiftArithmetic_h;
  const uint8_T ShiftArithmetic1;
  const uint8_T BitwiseOperator4;
  const uint8_T BitwiseOperator1_e;
  const uint8_T BitwiseOperator2_g;
  const uint8_T BitwiseOperator3_m;
  const uint8_T ShiftArithmetic_i;
  const uint8_T ShiftArithmetic1_d;
  const uint8_T BitwiseOperator4_k;
  const uint8_T TmpSignalConversionAtDataTy;
  const uint8_T BitwiseOperator2_i;
  const uint8_T BitwiseOperator4_o;
  const uint8_T BitwiseOperator5;
  const uint8_T ShiftArithmetic1_j;
  const uint8_T ShiftArithmetic4;
  const uint8_T BitwiseOperator1_j;
  const uint8_T BitwiseOperator3_a;
  const uint8_T TmpSignalConversionAtData_n;
  const uint8_T BitwiseOperator2_e;
  const uint8_T Add2_b;
  const uint8_T Add1_g;
  const uint8_T BitwiseOperator1_k;
  const uint8_T ShiftArithmetic_f;
  const uint8_T BitwiseOperator1_ji;
  const uint8_T BitwiseOperator2_d;
  const uint8_T BitwiseOperator3_f;
  const uint8_T ShiftArithmetic1_a;
  const uint8_T ShiftArithmetic2_l;
  const uint8_T BitwiseOperator4_g;
  const uint8_T BitwiseOperator5_n;
  const uint8_T BitwiseOperator6;
  const uint8_T BitwiseOperator7;
  const uint8_T ShiftArithmetic4_l;
  const uint8_T ShiftArithmetic7;
  const uint8_T ShiftArithmetic8;
  const uint8_T BitwiseOperator8;
  const uint8_T BitwiseOperator9;
  const uint8_T ShiftArithmetic9;
} ConstB_SWC_CSPF_IG_h_T;

#endif

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_CSPF_IG_T {
  const char_T **errorStatus;
};

#endif

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_CSPF_IG_T rtm;
} MdlrefDW_SWC_CSPF_IG_T;

#endif

extern void SWC_CSPF_IG(const uint8_T rtu_a_ccvs_hcu[8], const uint8_T
  rtu_a_hcu_mcu[8], int16_T *rty_CSPF_BUS_Calc_perc_TotDrv_e, int16_T
  *rty_CSPF_BUS_Calc_Nm_TotDrvTo_g, int16_T *rty_CSPF_BUS_Calc_perc_EngPed_c,
  uint8_T *rty_CSPF_BUS_Calc_st_ParkingB_e, uint8_T
  *rty_CSPF_BUS_Calc_gear_Transm_n, uint8_T *rty_CSPF_BUS_Calc_st_EPSwitch,
  uint8_T *rty_CSPF_BUS_Calc_st_MsgSwitc_k, uint8_T
  *rty_CSPF_BUS_Calc_st_MsgSwitc_h, uint8_T *rty_CSPF_BUS_Calc_bool_FootBr_k,
  uint8_T *rty_CSPF_BUS_Calc_st_HCUReqIn_k, uint8_T
  *rty_CSPF_BUS_Calc_st_HCUReqAu_k, uint8_T *rty_CSPF_BUS_Calc_mod_HCUReqM_e,
  uint8_T *rty_CSPF_BUS_Calc_st_HCUReqMo_c, real32_T
  *rty_CSPF_BUS_Nm_HCUReqMCUTq, real32_T *rty_CSPF_BUS_rpm_HCUReqMCUSpd, uint8_T
  *rty_CSPF_BUS_Calc_st_HCUAllow_p, uint8_T *rty_CSPF_BUS_Calc_st_NegtvRel_d,
  uint8_T *rty_CSPF_BUS_Calc_st_PostvRel_d, uint8_T
  *rty_CSPF_BUS_Calc_st_PreCharg_g, uint8_T *rty_CSPF_BUS_Calc_st_HCUReqHi_m,
  boolean_T *rty_CSPF_BUS_Calc_st_ActvDisc_p, int16_T
  *rty_CSPF_BUS_Calc_rpm_TMCurAv_i, uint8_T *rty_CSPF_BUS_Calc_mod_HCUMCU2_p,
  uint8_T *rty_CSPF_BUS_Calc_st_HCUMCU2_pe, int16_T
  *rty_CSPF_BUS_Nm_HCUMCU2ReqMCU_o, int16_T *rty_CSPF_BUS_rpm_HCUMCU2ReqMC_e,
  uint8_T *rty_CSPF_BUS_Calc_st_HCUMCU2A_m, uint8_T
  *rty_CSPF_BUS_Calc_st_MCU2Negt_j, uint8_T *rty_CSPF_BUS_Calc_st_MCU2Post_p,
  uint8_T *rty_CSPF_BUS_Calc_st_MCU2PreC_m, uint8_T
  *rty_CSPF_BUS_Calc_st_HCUMCU2_p2, uint8_T *rty_CSPF_BUS_Calc_st_MCU2Actv_i,
  int16_T *rty_CSPF_BUS_Calc_rpm_MCU2TMC_k, int16_T
  *rty_CSPF_BUS_Calc_Nm_Referenc_h, uint8_T *rty_CSPF_BUS_Calc_gear_HTrans_b,
  uint8_T *rty_CSPF_BUS_Calc_st_TCHandEP_n, uint8_T
  *rty_CSPF_BUS_Calc_st_ShiftInP_g, int16_T *rty_CSPF_BUS_Calc_z_ETC2GearR_g,
  uint8_T *rty_CSPF_BUS_Calc_gear_ETC2Se_e, uint8_T
  *rty_CSPF_BUS_Calc_gear_ETC2Cu_k, uint8_T *rty_CSPF_BUS_Calc_st_MtrOverr_b,
  uint8_T *rty_CSPF_BUS_Calc_st_MtrReqSp_c, uint8_T
  *rty_CSPF_BUS_Calc_st_MtrOver_lb, int16_T *rty_CSPF_BUS_Calc_rpm_MtrReqS_p,
  int16_T *rty_CSPF_BUS_Cale_Nm_MtrReqTq_p, int16_T
  *rty_CSPF_BUS_Calc_Nm_MtrReqTq_e, uint8_T *rty_CSPF_BUS_Calc_st_Mtr2Over_p,
  uint8_T *rty_CSPF_BUS_Calc_st_Mtr2ReqS_m, uint8_T
  *rty_CSPF_BUS_Calc_st_Mtr2Ove_nk, int16_T *rty_CSPF_BUS_Calc_rpm_Mtr2Req_f,
  int16_T *rty_CSPF_BUS_Calc_Nm_Mtr2ReqT_d, int16_T
  *rty_CSPF_BUS_Calc_Nm_Mtr2ReqT_m);
extern void SWC_CSPF_IG_initialize(const char_T **rt_errorStatus);

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

extern void SWC_CSPF_IG_CCVS_HCUToDisp(void);
extern void SWC_CSPF_IG_ECT1ToDisp(void);
extern void SWC_CSPF_IG_ECT2ToDisp(void);
extern void SWC_CSPF_IG_ECToDisp(void);
extern void SWC_CSPF_IG_EEC1_HCUToDisp(void);
extern void SWC_CSPF_IG_EEC2_HCUToDisp(void);
extern void SWC_CSPF_IG_HCU_MCU2ToDisp(void);
extern void SWC_CSPF_IG_HCU_MCUToDisp(void);
extern void SWC_CSPF_IG_Msg_CCVS_HCU(void);
extern void SWC_CSPF_IG_Msg_EC(void);
extern void SWC_CSPF_IG_Msg_EEC1_HCU(void);
extern void SWC_CSPF_IG_TC1_HCUToDisp(void);
extern void SWC_CSPF_IG_TC1_handleToDisp(void);
extern void SWC_CSPF_IG_TSC1_MTR1ToDisp(void);
extern void SWC_CSPF_IG_TSC1_MTR2ToDisp(void);
extern void SWC_CSPF_IG_msg_HCU_MCU(void);
extern void SWC_CSPF_IG_msg_HCU_MCU2(void);

#endif

#pragma section ".CAL_CONST"

extern const volatile int16_T DCEMS_sC_Nm_EngRefTorqDefault;
extern const volatile int16_T DCEMS_sC_Nm_EngRefTorqHighLmt;
extern const volatile int16_T DCEMS_sC_Nm_EngRefTorqLowLmt;
extern const volatile int16_T PMSM_Nm_EngDrvTorq_EEC1;
extern const volatile int16_T PMSM_Nm_HCUReqMCUTq_MCU1;
extern const volatile int16_T PMSM_Nm_HCUReqMCUTq_MCU2;
extern const volatile int16_T PMSM_Nm_ReferenceMCTorque_EC;
extern const volatile int16_T PMSM_Nm_ReqTqFric_MTR1;
extern const volatile int16_T PMSM_Nm_ReqTqFric_MTR2;
extern const volatile int16_T PMSM_Nm_ReqTqLimit_MTR1;
extern const volatile int16_T PMSM_Nm_ReqTqLimit_MTR2;
extern const volatile boolean_T PMSM_bool_ActvDischgCommand_MCU1;
extern const volatile boolean_T PMSM_bool_ActvDischgCommand_MCU2;
extern const volatile boolean_T PMSM_bool_CurrentGear_ETC2;
extern const volatile boolean_T PMSM_bool_EPSwitch_TC1HCU;
extern const volatile boolean_T PMSM_bool_EPSwitch_TC1Hd;
extern const volatile boolean_T PMSM_bool_EngDrvTorq_EEC1;
extern const volatile boolean_T PMSM_bool_EngPedal_EEC2;
extern const volatile boolean_T PMSM_bool_FootBrake_CCVS;
extern const volatile boolean_T PMSM_bool_GearRatio_ETC2;
extern const volatile boolean_T PMSM_bool_HCUAllowMotWorkEn_MCU1;
extern const volatile boolean_T PMSM_bool_HCUAllowMotWorkEn_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqAutoChgN_TC1HCU;
extern const volatile boolean_T PMSM_bool_HCUReqHiPowerOff_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqHiPowerOff_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqInhibitSftGear_TC1HCU;
extern const volatile boolean_T PMSM_bool_HCUReqMCUSpd_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMCUSpd_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqMCUTq_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMCUTq_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqMotRotaDir_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMotRotaDir_MCU2;
extern const volatile boolean_T PMSM_bool_HCUReqMotWorkMode_MCU1;
extern const volatile boolean_T PMSM_bool_HCUReqMotWorkMode_MCU2;
extern const volatile boolean_T PMSM_bool_MsgSwitchC_TC1HCU;
extern const volatile boolean_T PMSM_bool_MsgSwitchL_TC1HCU;
extern const volatile boolean_T PMSM_bool_NegtvRelayState_MCU1;
extern const volatile boolean_T PMSM_bool_NegtvRelayState_MCU2;
extern const volatile boolean_T PMSM_bool_NmEngDrvTorq_EEC1;
extern const volatile boolean_T PMSM_bool_OverrideConModePriority_MTR1;
extern const volatile boolean_T PMSM_bool_OverrideConModePriority_MTR2;
extern const volatile boolean_T PMSM_bool_ParkingBrkSW_CCVS;
extern const volatile boolean_T PMSM_bool_PostvRelayState_MCU1;
extern const volatile boolean_T PMSM_bool_PostvRelayState_MCU2;
extern const volatile boolean_T PMSM_bool_PreChargHiVoltRelayState_MCU1;
extern const volatile boolean_T PMSM_bool_PreChargHiVoltRelayState_MCU2;
extern const volatile boolean_T PMSM_bool_ReferenceMCTorque_EC;
extern const volatile boolean_T PMSM_bool_ReqSpdContCond_MTR1;
extern const volatile boolean_T PMSM_bool_ReqSpdContCond_MTR2;
extern const volatile boolean_T PMSM_bool_ReqSpdLimit_MTR1;
extern const volatile boolean_T PMSM_bool_ReqSpdLimit_MTR2;
extern const volatile boolean_T PMSM_bool_ReqTqFric_MTR1;
extern const volatile boolean_T PMSM_bool_ReqTqFric_MTR2;
extern const volatile boolean_T PMSM_bool_ReqTqLimit_MTR1;
extern const volatile boolean_T PMSM_bool_ReqTqLimit_MTR2;
extern const volatile boolean_T PMSM_bool_SelectGear_ETC2;
extern const volatile boolean_T PMSM_bool_ShiftInProcess_ETC1;
extern const volatile boolean_T PMSM_bool_TMCurAvalMaxSpeed_MCU1;
extern const volatile boolean_T PMSM_bool_TMCurAvalMaxSpeed_MCU2;
extern const volatile boolean_T PMSM_bool_TransmissionRequestedGear_TC1HCU;
extern const volatile boolean_T PMSM_bool_TransmissionRequestedGear_TC1Hd;
extern const volatile boolean_T PMSM_bool_overridConMode_MTR1;
extern const volatile boolean_T PMSM_bool_overridConMode_MTR2;
extern const volatile uint8_T PMSM_gear_CurrentGear_ETC2;
extern const volatile uint8_T PMSM_gear_SelectGear_ETC2;
extern const volatile uint8_T PMSM_gear_TransmissionRequestedGear_TC1HCU;
extern const volatile uint8_T PMSM_gear_TransmissionRequestedGear_TC1Hd;
extern const volatile uint8_T PMSM_mod_HCUReqMotWorkMode_MCU1;
extern const volatile uint8_T PMSM_mod_HCUReqMotWorkMode_MCU2;
extern const volatile uint8_T PMSM_overridConMode_MTR1;
extern const volatile uint8_T PMSM_overridConMode_MTR2;
extern const volatile int16_T PMSM_perc_EngDrvTorq_EEC1;
extern const volatile int16_T PMSM_perc_EngPedal_EEC2;
extern const volatile int16_T PMSM_rpm_HCUReqMCUSpd_MCU1;
extern const volatile int16_T PMSM_rpm_HCUReqMCUSpd_MCU2;
extern const volatile int16_T PMSM_rpm_ReqSpdLimit_MTR1;
extern const volatile int16_T PMSM_rpm_ReqSpdLimit_MTR2;
extern const volatile int16_T PMSM_rpm_TMCurAvalMaxSpeed_MCU1;
extern const volatile int16_T PMSM_rpm_TMCurAvalMaxSpeed_MCU2;
extern const volatile uint8_T PMSM_sC_OverrideConModePriority_MTR1;
extern const volatile uint8_T PMSM_sC_OverrideConModePriority_MTR2;
extern const volatile uint8_T PMSM_sC_ReqSpdContCond_MTR1;
extern const volatile uint8_T PMSM_sC_ReqSpdContCond_MTR2;
extern const volatile uint8_T PMSM_sC_bool_FootBrake_CCVS;
extern const volatile uint8_T PMSM_st_ActvDischgCommand_MCU1;
extern const volatile uint8_T PMSM_st_ActvDischgCommand_MCU2;
extern const volatile uint8_T PMSM_st_EPSwitch_TC1HCU;
extern const volatile uint8_T PMSM_st_EPSwitch_TC1Hd;
extern const volatile uint8_T PMSM_st_HCUAllowMotWorkEn_MCU1;
extern const volatile uint8_T PMSM_st_HCUAllowMotWorkEn_MCU2;
extern const volatile uint8_T PMSM_st_HCUReqAutoChgN_TC1HCU;
extern const volatile uint8_T PMSM_st_HCUReqHiPowerOff_MCU1;
extern const volatile uint8_T PMSM_st_HCUReqHiPowerOff_MCU2;
extern const volatile uint8_T PMSM_st_HCUReqInhibitSftGear_TC1HCU;
extern const volatile uint8_T PMSM_st_HCUReqMotRotaDir_MCU1;
extern const volatile uint8_T PMSM_st_HCUReqMotRotaDir_MCU2;
extern const volatile uint8_T PMSM_st_MsgSwitchC_TC1HCU;
extern const volatile uint8_T PMSM_st_MsgSwitchL_TC1HCU;
extern const volatile uint8_T PMSM_st_NegtvRelayState_MCU1;
extern const volatile uint8_T PMSM_st_NegtvRelayState_MCU2;
extern const volatile uint8_T PMSM_st_ParkingBrkSW_CCVS;
extern const volatile uint8_T PMSM_st_PostvRelayState_MCU1;
extern const volatile uint8_T PMSM_st_PostvRelayState_MCU2;
extern const volatile uint8_T PMSM_st_PreChargHiVoltRelayState_MCU1;
extern const volatile uint8_T PMSM_st_PreChargHiVoltRelayState_MCU2;
extern const volatile uint8_T PMSM_st_ShiftInProcess_ETC1;
extern const volatile int16_T PMSM_z_GearRatio_ETC2;

#pragma section

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_CSPF_IG_T SWC_CSPF_IG_MdlrefDW;

#endif

#ifndef SWC_CSPF_IG_MDLREF_HIDE_CHILD_

extern B_SWC_CSPF_IG_c_T SWC_CSPF_IG_B;

#endif
#endif

