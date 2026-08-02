/*
 * File: PDU_private.h
 *
 * Code generated for Simulink model 'PDU'.
 *
 * Model version                  : 2.37
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Sep  4 14:33:20 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PDU_private_h_
#define RTW_HEADER_PDU_private_h_
#include "rtwtypes.h"
#include "PDU.h"
#include "PDU_types.h"

extern void PDU_SR_latch_Update(boolean_T *rty_flg_out, DW_SR_latch_PDU_T
  *localDW);
extern void PDU_SR_latch(boolean_T rtu_flg_set, boolean_T rtu_flg_reset,
  boolean_T *rty_flg_out, DW_SR_latch_PDU_T *localDW);
extern void PDU_PDU_INIT(boolean_T rtu_PDU_HCU3MainNegCmd, boolean_T
  *rty_PDU_flgMainPosRelayCmdCharg, boolean_T *rty_PDU_flgMainNegRelayCmdCharg,
  boolean_T *rty_PDU_flgAttRelayCmdCharge, boolean_T
  *rty_PDU_flgK4RelayCmdCharge, boolean_T *rty_PDU_flgK3RelayCmdCharge,
  boolean_T *rty_PDU_flgReverseRelayCmdCharg, boolean_T
  *rty_PDU_flgPTCRelayCmdCharge, boolean_T *rty_PDU_flgBatHeatRelayCmdCharg,
  boolean_T *rty_PDU_flgMECURelayCmdCharge, boolean_T
  *rty_PDU_flgACRelayCmdCharge, boolean_T *rty_PDU_flgK9RelayCmdCharge,
  boolean_T *rty_PDU_flgK10RelayCmdCharge, boolean_T
  *rty_PDU_flgEfuseT3CmdCharge, boolean_T *rty_PDU_flgEfuseT5CmdCharge,
  boolean_T *rty_PDU_flgEfuseT1CmdCharge, boolean_T *rty_PDU_flgEfuseT2CmdCharge,
  boolean_T *rty_PDU_flgEfuseT4CmdCharge);
extern void PDU_PDU_ATTPRECHARGE_Init(DW_PDU_ATTPRECHARGE_PDU_T *localDW);
extern void PDU_PDU_ATTPRECHARGE(real32_T rtu_PDU_AttVoltage, real32_T
  rtu_PDU_BatteryVoltage, boolean_T rtu_PDU_flgKL15, boolean_T
  rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd, boolean_T
  rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
  boolean_T rtu_PDU_HCU3AttCmd, boolean_T *rty_PDU_flgMainPosRelayCmdPreA,
  boolean_T *rty_PDU_flgMainNegRelayCmdPreA, boolean_T
  *rty_PDU_flgAttRelayCmdPreA, boolean_T *rty_PDU_flgK4RelayCmdPreA, boolean_T
  *rty_PDU_flgK3RelayCmdPreA, boolean_T *rty_PDU_flgReserveRelayCmdPreA,
  boolean_T *rty_PDU_flgPTCRelayCmdPreA, boolean_T
  *rty_PDU_flgBatHeatRelayCmdPreA, boolean_T *rty_PDU_flgMECURelayCmdPreA,
  boolean_T *rty_PDU_flgACRelayCmdPreA, boolean_T *rty_PDU_flgK9RelayCmdPreA,
  boolean_T *rty_PDU_flgK10RelayCmdPreA, boolean_T *rty_PDU_flgEfuseT3CmdPreA,
  boolean_T *rty_PDU_flgEfuseT5CmdPreA, boolean_T *rty_PDU_flgEfuseT1CmdPreA,
  boolean_T *rty_PDU_flgEfuseT2CmdPreA, boolean_T *rty_PDU_flgEfuseT4CmdPreA,
  DW_PDU_ATTPRECHARGE_PDU_T *localDW);
extern void PDU_PDU_MAINPRECHARGE_Init(DW_PDU_MAINPRECHARGE_PDU_T *localDW);
extern void PDU_PDU_MAINPRECHARGE(real32_T rtu_PDU_MainPosVoltage, real32_T
  rtu_PDU_BatteryVoltage, boolean_T rtu_PDU_flgKL15, boolean_T
  rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
  rtu_PDU_HCU3BatHeatCmd, boolean_T rtu_PDU_HCU3AttCmd, boolean_T
  rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
  boolean_T *rty_PDU_flgMainPosRelayCmdPre, boolean_T
  *rty_PDU_flgMainNegRelayCmdPre, boolean_T *rty_PDU_flgAttRelayCmdPre,
  boolean_T *rty_PDU_flgK4RelayCmdPre, boolean_T *rty_PDU_flgK3RelayCmdPre,
  boolean_T *rty_PDU_flgReverseRelayCmdPre, boolean_T *rty_PDU_flgPTCRelayCmdPre,
  boolean_T *rty_PDU_flgBatHeatRelayCmdPre, boolean_T
  *rty_PDU_flgMECURelayCmdPre, boolean_T *rty_PDU_flgACRelayCmdPre, boolean_T
  *rty_PDU_flgK9RelayCmdPre, boolean_T *rty_PDU_flgK10RelayCmdPre, boolean_T
  *rty_PDU_flgEfuseT3CmdPre, boolean_T *rty_PDU_flgEfuseT5CmdPre, boolean_T
  *rty_PDU_flgEfuseT1CmdPre, boolean_T *rty_PDU_flgEfuseT2CmdPre, boolean_T
  *rty_PDU_flgEfuseT4CmdPre, DW_PDU_MAINPRECHARGE_PDU_T *localDW);
extern void PDU_PDU_DRIVE(boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
  rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd, boolean_T
  rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
  boolean_T rtu_PDU_HCU3AttCmd, boolean_T *rty_PDU_flgMainPosRelayCmdDrive,
  boolean_T *rty_PDU_flgMainNegRelayCmdDrive, boolean_T
  *rty_PDU_flgAttRelayCmdDrive, boolean_T *rty_PDU_flgK4RelayCmdDrive, boolean_T
  *rty_PDU_flgK3RelayCmdDrive, boolean_T *rty_PDU_flgReverseRelayCmdDrive,
  boolean_T *rty_PDU_flgPTCRelayCmdDrive, boolean_T
  *rty_PDU_flgBatHeatRelayCmdDrive, boolean_T *rty_PDU_flgMECURelayCmdDrive,
  boolean_T *rty_PDU_flgACRelayCmdDrive, boolean_T *rty_PDU_flgK9RelayCmdDrive,
  boolean_T *rty_PDU_flgK10RelayCmdDrive, boolean_T *rty_PDU_flgEfuseT3CmdDrive,
  boolean_T *rty_PDU_flgEfuseT5CmdDrive, boolean_T *rty_PDU_flgEfuseT1CmdDrive,
  boolean_T *rty_PDU_flgEfuseT2CmdDrive, boolean_T *rty_PDU_flgEfuseT4CmdDrive);
extern void PDU_PDU_CHARGE(boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
  rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd, boolean_T
  rtu_PDU_HCU3AttCmd, boolean_T rtu_PDU_HCU3PTCCmd, boolean_T
  rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd, boolean_T
  *rty_PDU_flgMainPosRelayCmdCharg, boolean_T *rty_PDU_flgMainNegRelayCmdCharg,
  boolean_T *rty_PDU_flgAttRelayCmdCharge, boolean_T
  *rty_PDU_flgK4RelayCmdCharge, boolean_T *rty_PDU_flgK3RelayCmdCharge,
  boolean_T *rty_PDU_flgReverseRelayCmdCharg, boolean_T
  *rty_PDU_flgPTCRelayCmdCharge, boolean_T *rty_PDU_flgBatHeatRelayCmdCharg,
  boolean_T *rty_PDU_flgMECURelayCmdCharge, boolean_T
  *rty_PDU_flgACRelayCmdCharge, boolean_T *rty_PDU_flgK9RelayCmdCharge,
  boolean_T *rty_PDU_flgK10RelayCmdCharge, boolean_T
  *rty_PDU_flgEfuseT3CmdCharge, boolean_T *rty_PDU_flgEfuseT5CmdCharge,
  boolean_T *rty_PDU_flgEfuseT1CmdCharge, boolean_T *rty_PDU_flgEfuseT2CmdCharge,
  boolean_T *rty_PDU_flgEfuseT4CmdCharge);
extern void PDU_PDU_SHUTDOWN(boolean_T rtu_PDU_flgShutDown, boolean_T
  rtu_PDU_HCU3MainPosCmd, boolean_T rtu_PDU_HCU3MainNegCmd, boolean_T
  rtu_PDU_HCU3BatHeatCmd, boolean_T rtu_PDU_HCU3AttCmd, boolean_T
  rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
  boolean_T *rty_PDU_flgMainPosRelayCmdSD, boolean_T
  *rty_PDU_flgMainNegRelayCmdSD, boolean_T *rty_PDU_flgAttRelayCmdSD, boolean_T *
  rty_PDU_flgK4RelayCmdSD, boolean_T *rty_PDU_flgK3RelayCmdSD, boolean_T
  *rty_PDU_flgReverseRelayCmdSD, boolean_T *rty_PDU_flgPTCRelayCmdSD, boolean_T *
  rty_PDU_flgBatHeatRelayCmdSD, boolean_T *rty_PDU_flgMECURelayCmdSD, boolean_T *
  rty_PDU_flgACRelayCmdSD, boolean_T *rty_PDU_flgK9RelayCmdSD, boolean_T
  *rty_PDU_flgK10RelayCmdSD, boolean_T *rty_PDU_flgEfuseT3CmdSD, boolean_T
  *rty_PDU_flgEfuseT5CmdSD, boolean_T *rty_PDU_flgEfuseT1CmdSD, boolean_T
  *rty_PDU_flgEfuseT2CmdSD, boolean_T *rty_PDU_flgEfuseT4CmdSD);
extern void PDU_PDU_ATTON(boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
  rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd, boolean_T
  rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
  boolean_T rtu_PDU_HCU3AttCmd, boolean_T *rty_PDU_flgMainPosRelayCmdON,
  boolean_T *rty_PDU_flgMainNegRelayCmdON, boolean_T *rty_PDU_flgAttRelayCmdON,
  boolean_T *rty_PDU_flgK4RelayCmdON, boolean_T *rty_PDU_flgK3RelayCmdON,
  boolean_T *rty_PDU_flgReverseRelayCmdON, boolean_T *rty_PDU_flgPTCRelayCmdON,
  boolean_T *rty_PDU_flgBatHeatRelayCmdON, boolean_T *rty_PDU_flgMECURelayCmdON,
  boolean_T *rty_PDU_flgACRelayCmdON, boolean_T *rty_PDU_flgK9RelayCmdON,
  boolean_T *rty_PDU_flgK10RelayCmdON, boolean_T *rty_PDU_flgEfuseT3CmdON,
  boolean_T *rty_PDU_flgEfuseT5CmdON, boolean_T *rty_PDU_flgEfuseT1CmdON,
  boolean_T *rty_PDU_flgEfuseT2CmdON, boolean_T *rty_PDU_flgEfuseT4CmdON);

#endif                                 /* RTW_HEADER_PDU_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
