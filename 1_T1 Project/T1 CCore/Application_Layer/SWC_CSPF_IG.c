#include "SWC_CSPF_IG.h"
#include "SWC_CSPF_IG_private.h"
#include "div_nde_s32_floor.h"

MdlrefDW_SWC_CSPF_IG_T SWC_CSPF_IG_MdlrefDW;
B_SWC_CSPF_IG_c_T SWC_CSPF_IG_B;
const uint8_T *SWC_CSPF_IG_rtu_a_ccvs_hcu;
const uint8_T *SWC_CSPF_IG_rtu_a_hcu_mcu;
void SWC_CSPF_IG_CCVS_HCUToDisp(void)
{
  if (PMSM_bool_ParkingBrkSW_CCVS) {
    SWC_CSPF_IG_B.Switch6_k = PMSM_st_ParkingBrkSW_CCVS;
  } else {
    SWC_CSPF_IG_B.Switch6_k = SWC_CSPF_IG_B.Switch2_c;
  }

  if (PMSM_bool_FootBrake_CCVS) {
    SWC_CSPF_IG_B.Switch10_a = PMSM_sC_bool_FootBrake_CCVS;
  } else {
    SWC_CSPF_IG_B.Switch10_a = SWC_CSPF_IG_B.Switch3_g;
  }
}

void SWC_CSPF_IG_ECT1ToDisp(void)
{
  if (PMSM_bool_ShiftInProcess_ETC1) {
    SWC_CSPF_IG_B.Switch6_b = PMSM_st_ShiftInProcess_ETC1;
  } else {
    SWC_CSPF_IG_B.Switch6_b = SWC_CSPF_IG_ConstB.ShiftArithmetic_f;
  }
}

void SWC_CSPF_IG_ECT2ToDisp(void)
{
  if (PMSM_bool_GearRatio_ETC2) {
    SWC_CSPF_IG_B.Switch6_m = PMSM_z_GearRatio_ETC2;
  } else {
    SWC_CSPF_IG_B.Switch6_m = SWC_CSPF_IG_ConstB.Product1_a;
  }

  if (PMSM_bool_SelectGear_ETC2) {
    SWC_CSPF_IG_B.Switch1_m = PMSM_gear_SelectGear_ETC2;
  } else {
    SWC_CSPF_IG_B.Switch1_m = SWC_CSPF_IG_ConstB.Add2_b;
  }

  if (PMSM_bool_CurrentGear_ETC2) {
    SWC_CSPF_IG_B.Switch2_p = PMSM_gear_CurrentGear_ETC2;
  } else {
    SWC_CSPF_IG_B.Switch2_p = SWC_CSPF_IG_ConstB.Add1_g;
  }
}

void SWC_CSPF_IG_ECToDisp(void)
{
  if (PMSM_bool_ReferenceMCTorque_EC) {
    SWC_CSPF_IG_B.Switch6_i = PMSM_Nm_ReferenceMCTorque_EC;
  } else {
    SWC_CSPF_IG_B.Switch6_i = SWC_CSPF_IG_B.Switch2;
  }
}

void SWC_CSPF_IG_EEC1_HCUToDisp(void)
{
  if (PMSM_bool_EngDrvTorq_EEC1) {
    SWC_CSPF_IG_B.Switch6_a = PMSM_perc_EngDrvTorq_EEC1;
  } else {
    SWC_CSPF_IG_B.Switch6_a = SWC_CSPF_IG_ConstB.u25125;
  }

  if (PMSM_bool_NmEngDrvTorq_EEC1) {
    SWC_CSPF_IG_B.Switch10 = PMSM_Nm_EngDrvTorq_EEC1;
  } else {
    SWC_CSPF_IG_B.Switch10 = SWC_CSPF_IG_B.Switch2;
  }
}

void SWC_CSPF_IG_EEC2_HCUToDisp(void)
{
  if (PMSM_bool_EngPedal_EEC2) {
    SWC_CSPF_IG_B.Switch6 = PMSM_perc_EngPedal_EEC2;
  } else {
    SWC_CSPF_IG_B.Switch6 = SWC_CSPF_IG_ConstB.DataTypeConversion2_c;
  }
}

void SWC_CSPF_IG_HCU_MCU2ToDisp(void)
{
  if (PMSM_bool_HCUReqMotWorkMode_MCU2) {
    SWC_CSPF_IG_B.Switch6_ma = PMSM_mod_HCUReqMotWorkMode_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch6_ma = SWC_CSPF_IG_ConstB.BitwiseOperator1_ji;
  }

  if (PMSM_bool_HCUReqMotRotaDir_MCU2) {
    SWC_CSPF_IG_B.Switch10_l = PMSM_st_HCUReqMotRotaDir_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch10_l = SWC_CSPF_IG_ConstB.ShiftArithmetic1_a;
  }

  if (PMSM_bool_HCUReqMCUTq_MCU2) {
    SWC_CSPF_IG_B.Switch1 = PMSM_Nm_HCUReqMCUTq_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch1 = SWC_CSPF_IG_B.Switch2_j;
  }

  if (PMSM_bool_HCUReqMCUSpd_MCU2) {
    SWC_CSPF_IG_B.Switch4_b = PMSM_rpm_HCUReqMCUSpd_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch4_b = SWC_CSPF_IG_ConstB.Divide8;
  }

  if (PMSM_bool_HCUAllowMotWorkEn_MCU2) {
    SWC_CSPF_IG_B.Switch3_d = PMSM_st_HCUAllowMotWorkEn_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch3_d = SWC_CSPF_IG_ConstB.BitwiseOperator4_g;
  }

  if (PMSM_bool_NegtvRelayState_MCU2) {
    SWC_CSPF_IG_B.Switch2_i = PMSM_st_NegtvRelayState_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch2_i = SWC_CSPF_IG_ConstB.ShiftArithmetic4_l;
  }

  if (PMSM_bool_PostvRelayState_MCU2) {
    SWC_CSPF_IG_B.Switch8_e = PMSM_st_PostvRelayState_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch8_e = SWC_CSPF_IG_ConstB.ShiftArithmetic7;
  }

  if (PMSM_bool_PreChargHiVoltRelayState_MCU2) {
    SWC_CSPF_IG_B.Switch7_d = PMSM_st_PreChargHiVoltRelayState_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch7_d = SWC_CSPF_IG_ConstB.ShiftArithmetic8;
  }

  if (PMSM_bool_HCUReqHiPowerOff_MCU2) {
    SWC_CSPF_IG_B.Switch5_o = PMSM_st_HCUReqHiPowerOff_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch5_o = SWC_CSPF_IG_ConstB.BitwiseOperator8;
  }

  if (PMSM_bool_ActvDischgCommand_MCU2) {
    SWC_CSPF_IG_B.Switch11 = PMSM_st_ActvDischgCommand_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch11 = SWC_CSPF_IG_ConstB.ShiftArithmetic9;
  }

  if (PMSM_bool_TMCurAvalMaxSpeed_MCU2) {
    SWC_CSPF_IG_B.Switch9_e = PMSM_rpm_TMCurAvalMaxSpeed_MCU2;
  } else {
    SWC_CSPF_IG_B.Switch9_e = SWC_CSPF_IG_ConstB.DataTypeConversion5;
  }
}

void SWC_CSPF_IG_HCU_MCUToDisp(void)
{
  if (PMSM_bool_HCUReqMotWorkMode_MCU1) {
    SWC_CSPF_IG_B.Switch6_l = PMSM_mod_HCUReqMotWorkMode_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch6_l = SWC_CSPF_IG_B.Switch10_b;
  }

  if (PMSM_bool_HCUReqMotRotaDir_MCU1) {
    SWC_CSPF_IG_B.Switch10_c = PMSM_st_HCUReqMotRotaDir_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch10_c = SWC_CSPF_IG_B.Switch6_l4;
  }

  if (PMSM_bool_HCUReqMCUTq_MCU1) {
    SWC_CSPF_IG_B.Switch2_j = PMSM_Nm_HCUReqMCUTq_MCU1;
  }

  if (PMSM_bool_HCUReqMCUSpd_MCU1) {
    SWC_CSPF_IG_B.Switch3_o = PMSM_rpm_HCUReqMCUSpd_MCU1;
  }

  if (PMSM_bool_HCUAllowMotWorkEn_MCU1) {
    SWC_CSPF_IG_B.Switch3_f = PMSM_st_HCUAllowMotWorkEn_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch3_f = SWC_CSPF_IG_B.Switch1_l;
  }

  if (PMSM_bool_NegtvRelayState_MCU1) {
    SWC_CSPF_IG_B.Switch2_e = PMSM_st_NegtvRelayState_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch2_e = SWC_CSPF_IG_B.Switch6_ic;
  }

  if (PMSM_bool_PostvRelayState_MCU1) {
    SWC_CSPF_IG_B.Switch8 = PMSM_st_PostvRelayState_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch8 = SWC_CSPF_IG_B.Switch10_i;
  }

  if (PMSM_bool_PreChargHiVoltRelayState_MCU1) {
    SWC_CSPF_IG_B.Switch7 = PMSM_st_PreChargHiVoltRelayState_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch7 = SWC_CSPF_IG_B.Switch10_h;
  }

  if (PMSM_bool_HCUReqHiPowerOff_MCU1) {
    SWC_CSPF_IG_B.Switch5 = PMSM_st_HCUReqHiPowerOff_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch5 = SWC_CSPF_IG_B.Switch6_d;
  }

  if (PMSM_bool_ActvDischgCommand_MCU1) {
    SWC_CSPF_IG_B.Switch1_k = PMSM_st_ActvDischgCommand_MCU1;
  }

  if (PMSM_bool_TMCurAvalMaxSpeed_MCU1) {
    SWC_CSPF_IG_B.Switch9 = PMSM_rpm_TMCurAvalMaxSpeed_MCU1;
  } else {
    SWC_CSPF_IG_B.Switch9 = SWC_CSPF_IG_B.Switch4_p;
  }
}

void SWC_CSPF_IG_Msg_CCVS_HCU(void)
{
  SWC_CSPF_IG_B.Switch2_c = (uint8_T)((int32_T)((uint32_T)
    SWC_CSPF_IG_rtu_a_ccvs_hcu[0] >> 2) & 3);
  SWC_CSPF_IG_B.Switch3_g = (uint8_T)((uint32_T)(SWC_CSPF_IG_rtu_a_ccvs_hcu[3] &
    48) >> 4);
}

void SWC_CSPF_IG_Msg_EC(void)
{
  if ((DCEMS_sC_Nm_EngRefTorqHighLmt >= SWC_CSPF_IG_ConstB.Add12) &&
      (SWC_CSPF_IG_ConstB.Add12 >= DCEMS_sC_Nm_EngRefTorqLowLmt)) {
    SWC_CSPF_IG_B.Switch2 = (int16_T)SWC_CSPF_IG_ConstB.Add12;
  } else {
    SWC_CSPF_IG_B.Switch2 = DCEMS_sC_Nm_EngRefTorqDefault;
  }
}

void SWC_CSPF_IG_Msg_EEC1_HCU(void)
{
  SWC_CSPF_IG_B.Switch2 = (int16_T)(SWC_CSPF_IG_ConstB.u25125 << 2);
}

void SWC_CSPF_IG_TC1_HCUToDisp(void)
{
  if (PMSM_bool_TransmissionRequestedGear_TC1HCU) {
    SWC_CSPF_IG_B.Switch6_ib = PMSM_gear_TransmissionRequestedGear_TC1HCU;
  } else {
    SWC_CSPF_IG_B.Switch6_ib = SWC_CSPF_IG_ConstB.TmpSignalConversionAtDataTy;
  }

  if (PMSM_bool_EPSwitch_TC1HCU) {
    SWC_CSPF_IG_B.Switch10_f = PMSM_st_EPSwitch_TC1HCU;
  } else {
    SWC_CSPF_IG_B.Switch10_f = SWC_CSPF_IG_ConstB.BitwiseOperator2_i;
  }

  if (PMSM_bool_MsgSwitchC_TC1HCU) {
    SWC_CSPF_IG_B.Switch1_p = PMSM_st_MsgSwitchC_TC1HCU;
  } else {
    SWC_CSPF_IG_B.Switch1_p = SWC_CSPF_IG_ConstB.ShiftArithmetic1_j;
  }

  if (PMSM_bool_MsgSwitchL_TC1HCU) {
    SWC_CSPF_IG_B.Switch4_n = PMSM_st_MsgSwitchL_TC1HCU;
  } else {
    SWC_CSPF_IG_B.Switch4_n = SWC_CSPF_IG_ConstB.ShiftArithmetic4;
  }

  if (PMSM_bool_HCUReqInhibitSftGear_TC1HCU) {
    SWC_CSPF_IG_B.Switch3_g = PMSM_st_HCUReqInhibitSftGear_TC1HCU;
  } else {
    SWC_CSPF_IG_B.Switch3_g = SWC_CSPF_IG_ConstB.BitwiseOperator1_j;
  }

  if (PMSM_bool_HCUReqAutoChgN_TC1HCU) {
    SWC_CSPF_IG_B.Switch2_c = PMSM_st_HCUReqAutoChgN_TC1HCU;
  } else {
    SWC_CSPF_IG_B.Switch2_c = SWC_CSPF_IG_ConstB.BitwiseOperator3_a;
  }
}

void SWC_CSPF_IG_TC1_handleToDisp(void)
{
  if (PMSM_bool_TransmissionRequestedGear_TC1Hd) {
    SWC_CSPF_IG_B.Switch6_l4 = PMSM_gear_TransmissionRequestedGear_TC1Hd;
  } else {
    SWC_CSPF_IG_B.Switch6_l4 = SWC_CSPF_IG_ConstB.TmpSignalConversionAtData_n;
  }

  if (PMSM_bool_EPSwitch_TC1Hd) {
    SWC_CSPF_IG_B.Switch10_b = PMSM_st_EPSwitch_TC1Hd;
  } else {
    SWC_CSPF_IG_B.Switch10_b = SWC_CSPF_IG_ConstB.BitwiseOperator2_e;
  }
}

void SWC_CSPF_IG_TSC1_MTR1ToDisp(void)
{
  if (PMSM_bool_overridConMode_MTR1) {
    SWC_CSPF_IG_B.Switch6_d = PMSM_overridConMode_MTR1;
  } else {
    SWC_CSPF_IG_B.Switch6_d = SWC_CSPF_IG_ConstB.BitwiseOperator1_e;
  }

  if (PMSM_bool_ReqSpdContCond_MTR1) {
    SWC_CSPF_IG_B.Switch10_h = PMSM_sC_ReqSpdContCond_MTR1;
  } else {
    SWC_CSPF_IG_B.Switch10_h = SWC_CSPF_IG_ConstB.ShiftArithmetic_i;
  }

  if (PMSM_bool_OverrideConModePriority_MTR1) {
    SWC_CSPF_IG_B.Switch1_l = PMSM_sC_OverrideConModePriority_MTR1;
  } else {
    SWC_CSPF_IG_B.Switch1_l = SWC_CSPF_IG_ConstB.ShiftArithmetic1_d;
  }

  if (PMSM_bool_ReqSpdLimit_MTR1) {
    SWC_CSPF_IG_B.Switch4 = PMSM_rpm_ReqSpdLimit_MTR1;
  } else {
    SWC_CSPF_IG_B.Switch4 = SWC_CSPF_IG_ConstB.DataTypeConversion1_p;
  }

  if (PMSM_bool_ReqTqLimit_MTR1) {
    SWC_CSPF_IG_B.Switch3 = PMSM_Nm_ReqTqLimit_MTR1;
  } else {
    SWC_CSPF_IG_B.Switch3 = SWC_CSPF_IG_ConstB.Add1_i;
  }

  if (PMSM_bool_ReqTqFric_MTR1) {
    SWC_CSPF_IG_B.Switch2 = PMSM_Nm_ReqTqFric_MTR1;
  } else {
    SWC_CSPF_IG_B.Switch2 = SWC_CSPF_IG_ConstB.Product2_h;
  }
}

void SWC_CSPF_IG_TSC1_MTR2ToDisp(void)
{
  if (PMSM_bool_overridConMode_MTR2) {
    SWC_CSPF_IG_B.Switch6_ic = PMSM_overridConMode_MTR2;
  } else {
    SWC_CSPF_IG_B.Switch6_ic = SWC_CSPF_IG_ConstB.BitwiseOperator1;
  }

  if (PMSM_bool_ReqSpdContCond_MTR2) {
    SWC_CSPF_IG_B.Switch10_i = PMSM_sC_ReqSpdContCond_MTR2;
  } else {
    SWC_CSPF_IG_B.Switch10_i = SWC_CSPF_IG_ConstB.ShiftArithmetic_h;
  }

  if (PMSM_bool_OverrideConModePriority_MTR2) {
    SWC_CSPF_IG_B.Switch1_k = PMSM_sC_OverrideConModePriority_MTR2;
  } else {
    SWC_CSPF_IG_B.Switch1_k = SWC_CSPF_IG_ConstB.ShiftArithmetic1;
  }

  if (PMSM_bool_ReqSpdLimit_MTR2) {
    SWC_CSPF_IG_B.Switch4_p = PMSM_rpm_ReqSpdLimit_MTR2;
  } else {
    SWC_CSPF_IG_B.Switch4_p = SWC_CSPF_IG_ConstB.DataTypeConversion1_k;
  }

  if (PMSM_bool_ReqTqLimit_MTR2) {
    SWC_CSPF_IG_B.Switch3_o = PMSM_Nm_ReqTqLimit_MTR2;
  } else {
    SWC_CSPF_IG_B.Switch3_o = SWC_CSPF_IG_ConstB.Add1;
  }

  if (PMSM_bool_ReqTqFric_MTR2) {
    SWC_CSPF_IG_B.Switch2_j = PMSM_Nm_ReqTqFric_MTR2;
  } else {
    SWC_CSPF_IG_B.Switch2_j = SWC_CSPF_IG_ConstB.Product2;
  }
}

void SWC_CSPF_IG_msg_HCU_MCU(void)
{
  int16_T SWC_CSPF_IG_rtu_a_hcu_mcu_0;
  if ((int16_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[1] - 125) > 100) {
    SWC_CSPF_IG_rtu_a_hcu_mcu_0 = 100;
  } else if ((int16_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[1] - 125) < -100) {
    SWC_CSPF_IG_rtu_a_hcu_mcu_0 = -100;
  } else {
    SWC_CSPF_IG_rtu_a_hcu_mcu_0 = (int16_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[1] - 125);
  }

  SWC_CSPF_IG_B.Switch2_j = (int16_T)div_nde_s32_floor((((int32_T)((uint32_T)
    (SWC_CSPF_IG_rtu_a_hcu_mcu[0] & 240) >> 4) * SWC_CSPF_IG_B.Switch6_i) >> 3)
    + SWC_CSPF_IG_rtu_a_hcu_mcu_0 * SWC_CSPF_IG_B.Switch6_i, 100);
  SWC_CSPF_IG_B.Switch10_b = (uint8_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[0] & 3);
  SWC_CSPF_IG_B.Switch6_l4 = (uint8_T)((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[0] &
    12) >> 2);
  SWC_CSPF_IG_B.Switch1_l = (uint8_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[4] & 3);
  SWC_CSPF_IG_B.Switch10_h = (uint8_T)((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[4] &
    192) >> 6);
  SWC_CSPF_IG_B.Switch6_d = (uint8_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[5] & 3);
  SWC_CSPF_IG_B.Switch1_k = (uint8_T)((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[5] &
    12) >> 2);
  SWC_CSPF_IG_B.Switch10_i = (uint8_T)((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[4] &
    48) >> 4);
  SWC_CSPF_IG_B.Switch6_ic = (uint8_T)((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[4] &
    12) >> 2);
  SWC_CSPF_IG_B.Switch3_o = (int16_T)(((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[3] <<
    8) + SWC_CSPF_IG_rtu_a_hcu_mcu[2]) >> 1);
  SWC_CSPF_IG_B.Switch4_p = (int16_T)(((uint32_T)(SWC_CSPF_IG_rtu_a_hcu_mcu[7] <<
    8) + SWC_CSPF_IG_rtu_a_hcu_mcu[6]) >> 1);
}

void SWC_CSPF_IG_msg_HCU_MCU2(void)
{
  SWC_CSPF_IG_B.Switch2_j = (int16_T)div_nde_s32_floor
    (((SWC_CSPF_IG_ConstB.ShiftArithmetic2_l * SWC_CSPF_IG_B.Switch6_i) >> 3) +
     SWC_CSPF_IG_ConstB.Saturation1 * SWC_CSPF_IG_B.Switch6_i, 100);
}

void SWC_CSPF_IG(const uint8_T rtu_a_ccvs_hcu[8], const uint8_T rtu_a_hcu_mcu[8],
                 int16_T *rty_CSPF_BUS_Calc_perc_TotDrv_e, int16_T
                 *rty_CSPF_BUS_Calc_Nm_TotDrvTo_g, int16_T
                 *rty_CSPF_BUS_Calc_perc_EngPed_c, uint8_T
                 *rty_CSPF_BUS_Calc_st_ParkingB_e, uint8_T
                 *rty_CSPF_BUS_Calc_gear_Transm_n, uint8_T
                 *rty_CSPF_BUS_Calc_st_EPSwitch, uint8_T
                 *rty_CSPF_BUS_Calc_st_MsgSwitc_k, uint8_T
                 *rty_CSPF_BUS_Calc_st_MsgSwitc_h, uint8_T
                 *rty_CSPF_BUS_Calc_bool_FootBr_k, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUReqIn_k, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUReqAu_k, uint8_T
                 *rty_CSPF_BUS_Calc_mod_HCUReqM_e, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUReqMo_c, real32_T
                 *rty_CSPF_BUS_Nm_HCUReqMCUTq, real32_T
                 *rty_CSPF_BUS_rpm_HCUReqMCUSpd, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUAllow_p, uint8_T
                 *rty_CSPF_BUS_Calc_st_NegtvRel_d, uint8_T
                 *rty_CSPF_BUS_Calc_st_PostvRel_d, uint8_T
                 *rty_CSPF_BUS_Calc_st_PreCharg_g, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUReqHi_m, boolean_T
                 *rty_CSPF_BUS_Calc_st_ActvDisc_p, int16_T
                 *rty_CSPF_BUS_Calc_rpm_TMCurAv_i, uint8_T
                 *rty_CSPF_BUS_Calc_mod_HCUMCU2_p, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUMCU2_pe, int16_T
                 *rty_CSPF_BUS_Nm_HCUMCU2ReqMCU_o, int16_T
                 *rty_CSPF_BUS_rpm_HCUMCU2ReqMC_e, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUMCU2A_m, uint8_T
                 *rty_CSPF_BUS_Calc_st_MCU2Negt_j, uint8_T
                 *rty_CSPF_BUS_Calc_st_MCU2Post_p, uint8_T
                 *rty_CSPF_BUS_Calc_st_MCU2PreC_m, uint8_T
                 *rty_CSPF_BUS_Calc_st_HCUMCU2_p2, uint8_T
                 *rty_CSPF_BUS_Calc_st_MCU2Actv_i, int16_T
                 *rty_CSPF_BUS_Calc_rpm_MCU2TMC_k, int16_T
                 *rty_CSPF_BUS_Calc_Nm_Referenc_h, uint8_T
                 *rty_CSPF_BUS_Calc_gear_HTrans_b, uint8_T
                 *rty_CSPF_BUS_Calc_st_TCHandEP_n, uint8_T
                 *rty_CSPF_BUS_Calc_st_ShiftInP_g, int16_T
                 *rty_CSPF_BUS_Calc_z_ETC2GearR_g, uint8_T
                 *rty_CSPF_BUS_Calc_gear_ETC2Se_e, uint8_T
                 *rty_CSPF_BUS_Calc_gear_ETC2Cu_k, uint8_T
                 *rty_CSPF_BUS_Calc_st_MtrOverr_b, uint8_T
                 *rty_CSPF_BUS_Calc_st_MtrReqSp_c, uint8_T
                 *rty_CSPF_BUS_Calc_st_MtrOver_lb, int16_T
                 *rty_CSPF_BUS_Calc_rpm_MtrReqS_p, int16_T
                 *rty_CSPF_BUS_Cale_Nm_MtrReqTq_p, int16_T
                 *rty_CSPF_BUS_Calc_Nm_MtrReqTq_e, uint8_T
                 *rty_CSPF_BUS_Calc_st_Mtr2Over_p, uint8_T
                 *rty_CSPF_BUS_Calc_st_Mtr2ReqS_m, uint8_T
                 *rty_CSPF_BUS_Calc_st_Mtr2Ove_nk, int16_T
                 *rty_CSPF_BUS_Calc_rpm_Mtr2Req_f, int16_T
                 *rty_CSPF_BUS_Calc_Nm_Mtr2ReqT_d, int16_T
                 *rty_CSPF_BUS_Calc_Nm_Mtr2ReqT_m)
{
  SWC_CSPF_IG_rtu_a_ccvs_hcu = rtu_a_ccvs_hcu;
  SWC_CSPF_IG_rtu_a_hcu_mcu = rtu_a_hcu_mcu;
  SWC_CSPF_IG_Msg_EEC1_HCU();
  SWC_CSPF_IG_EEC1_HCUToDisp();
  SWC_CSPF_IG_EEC2_HCUToDisp();
  SWC_CSPF_IG_Msg_CCVS_HCU();
  SWC_CSPF_IG_CCVS_HCUToDisp();
  SWC_CSPF_IG_TC1_HCUToDisp();
  SWC_CSPF_IG_Msg_EC();
  SWC_CSPF_IG_ECToDisp();
  SWC_CSPF_IG_msg_HCU_MCU();
  SWC_CSPF_IG_HCU_MCUToDisp();
  *rty_CSPF_BUS_Nm_HCUReqMCUTq = SWC_CSPF_IG_B.Switch2_j;
  *rty_CSPF_BUS_rpm_HCUReqMCUSpd = SWC_CSPF_IG_B.Switch3_o;
  *rty_CSPF_BUS_Calc_st_ActvDisc_p = (SWC_CSPF_IG_B.Switch1_k != 0);
  SWC_CSPF_IG_msg_HCU_MCU2();
  SWC_CSPF_IG_HCU_MCU2ToDisp();
  SWC_CSPF_IG_TC1_handleToDisp();
  SWC_CSPF_IG_ECT1ToDisp();
  SWC_CSPF_IG_ECT2ToDisp();
  SWC_CSPF_IG_TSC1_MTR1ToDisp();
  SWC_CSPF_IG_TSC1_MTR2ToDisp();
  *rty_CSPF_BUS_Calc_perc_TotDrv_e = SWC_CSPF_IG_B.Switch6_a;
  *rty_CSPF_BUS_Calc_st_HCUReqIn_k = SWC_CSPF_IG_B.Switch3_g;
  *rty_CSPF_BUS_Calc_st_HCUReqAu_k = SWC_CSPF_IG_B.Switch2_c;
  *rty_CSPF_BUS_Calc_mod_HCUReqM_e = SWC_CSPF_IG_B.Switch6_l;
  *rty_CSPF_BUS_Calc_st_HCUReqMo_c = SWC_CSPF_IG_B.Switch10_c;
  *rty_CSPF_BUS_Calc_st_HCUAllow_p = SWC_CSPF_IG_B.Switch3_f;
  *rty_CSPF_BUS_Calc_st_NegtvRel_d = SWC_CSPF_IG_B.Switch2_e;
  *rty_CSPF_BUS_Calc_st_PostvRel_d = SWC_CSPF_IG_B.Switch8;
  *rty_CSPF_BUS_Calc_st_PreCharg_g = SWC_CSPF_IG_B.Switch7;
  *rty_CSPF_BUS_Calc_Nm_TotDrvTo_g = SWC_CSPF_IG_B.Switch10;
  *rty_CSPF_BUS_Calc_st_HCUReqHi_m = SWC_CSPF_IG_B.Switch5;
  *rty_CSPF_BUS_Calc_rpm_TMCurAv_i = SWC_CSPF_IG_B.Switch9;
  *rty_CSPF_BUS_Calc_mod_HCUMCU2_p = SWC_CSPF_IG_B.Switch6_ma;
  *rty_CSPF_BUS_Calc_st_HCUMCU2_pe = SWC_CSPF_IG_B.Switch10_l;
  *rty_CSPF_BUS_Nm_HCUMCU2ReqMCU_o = SWC_CSPF_IG_B.Switch1;
  *rty_CSPF_BUS_rpm_HCUMCU2ReqMC_e = SWC_CSPF_IG_B.Switch4_b;
  *rty_CSPF_BUS_Calc_st_HCUMCU2A_m = SWC_CSPF_IG_B.Switch3_d;
  *rty_CSPF_BUS_Calc_st_MCU2Negt_j = SWC_CSPF_IG_B.Switch2_i;
  *rty_CSPF_BUS_Calc_st_MCU2Post_p = SWC_CSPF_IG_B.Switch8_e;
  *rty_CSPF_BUS_Calc_perc_EngPed_c = SWC_CSPF_IG_B.Switch6;
  *rty_CSPF_BUS_Calc_st_MCU2PreC_m = SWC_CSPF_IG_B.Switch7_d;
  *rty_CSPF_BUS_Calc_st_HCUMCU2_p2 = SWC_CSPF_IG_B.Switch5_o;
  *rty_CSPF_BUS_Calc_st_MCU2Actv_i = SWC_CSPF_IG_B.Switch11;
  *rty_CSPF_BUS_Calc_rpm_MCU2TMC_k = SWC_CSPF_IG_B.Switch9_e;
  *rty_CSPF_BUS_Calc_Nm_Referenc_h = SWC_CSPF_IG_B.Switch6_i;
  *rty_CSPF_BUS_Calc_gear_HTrans_b = SWC_CSPF_IG_B.Switch6_l4;
  *rty_CSPF_BUS_Calc_st_TCHandEP_n = SWC_CSPF_IG_B.Switch10_b;
  *rty_CSPF_BUS_Calc_st_ShiftInP_g = SWC_CSPF_IG_B.Switch6_b;
  *rty_CSPF_BUS_Calc_z_ETC2GearR_g = SWC_CSPF_IG_B.Switch6_m;
  *rty_CSPF_BUS_Calc_gear_ETC2Se_e = SWC_CSPF_IG_B.Switch1_m;
  *rty_CSPF_BUS_Calc_st_ParkingB_e = SWC_CSPF_IG_B.Switch6_k;
  *rty_CSPF_BUS_Calc_gear_ETC2Cu_k = SWC_CSPF_IG_B.Switch2_p;
  *rty_CSPF_BUS_Calc_st_MtrOverr_b = SWC_CSPF_IG_B.Switch6_d;
  *rty_CSPF_BUS_Calc_st_MtrReqSp_c = SWC_CSPF_IG_B.Switch10_h;
  *rty_CSPF_BUS_Calc_st_MtrOver_lb = SWC_CSPF_IG_B.Switch1_l;
  *rty_CSPF_BUS_Calc_rpm_MtrReqS_p = SWC_CSPF_IG_B.Switch4;
  *rty_CSPF_BUS_Cale_Nm_MtrReqTq_p = SWC_CSPF_IG_B.Switch3;
  *rty_CSPF_BUS_Calc_Nm_MtrReqTq_e = SWC_CSPF_IG_B.Switch2;
  *rty_CSPF_BUS_Calc_st_Mtr2Over_p = SWC_CSPF_IG_B.Switch6_ic;
  *rty_CSPF_BUS_Calc_st_Mtr2ReqS_m = SWC_CSPF_IG_B.Switch10_i;
  *rty_CSPF_BUS_Calc_st_Mtr2Ove_nk = SWC_CSPF_IG_B.Switch1_k;
  *rty_CSPF_BUS_Calc_gear_Transm_n = SWC_CSPF_IG_B.Switch6_ib;
  *rty_CSPF_BUS_Calc_rpm_Mtr2Req_f = SWC_CSPF_IG_B.Switch4_p;
  *rty_CSPF_BUS_Calc_Nm_Mtr2ReqT_d = SWC_CSPF_IG_B.Switch3_o;
  *rty_CSPF_BUS_Calc_Nm_Mtr2ReqT_m = SWC_CSPF_IG_B.Switch2_j;
  *rty_CSPF_BUS_Calc_st_EPSwitch = SWC_CSPF_IG_B.Switch10_f;
  *rty_CSPF_BUS_Calc_st_MsgSwitc_k = SWC_CSPF_IG_B.Switch1_p;
  *rty_CSPF_BUS_Calc_st_MsgSwitc_h = SWC_CSPF_IG_B.Switch4_n;
  *rty_CSPF_BUS_Calc_bool_FootBr_k = SWC_CSPF_IG_B.Switch10_a;
}

void SWC_CSPF_IG_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SWC_CSPF_IG_T *const SWC_CSPF_IG_M = &(SWC_CSPF_IG_MdlrefDW.rtm);
  rtmSetErrorStatusPointer(SWC_CSPF_IG_M, rt_errorStatus);
}
