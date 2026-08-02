/*
 * File: PDU.c
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

#include "PDU.h"
#include "rtwtypes.h"
#include "PDU_private.h"
#include "PDU_Interface.h"

/* Named constants for Chart: '<S3>/Chart' */
#define PDU_IN_ACTIVE                  ((uint8_T)1U)
#define PDU_IN_ATTON                   ((uint8_T)2U)
#define PDU_IN_ATTPRECHARGE            ((uint8_T)3U)
#define PDU_IN_CHARGEMODE              ((uint8_T)1U)
#define PDU_IN_DRIVEMODE               ((uint8_T)2U)
#define PDU_IN_INIT                    ((uint8_T)4U)
#define PDU_IN_MAINPRECHARGE           ((uint8_T)5U)
#define PDU_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define PDU_IN_SHUTDOWN                ((uint8_T)6U)

/* Exported block signals */
real32_T PDU_EfuseT3Current;           /* '<Root>/PDU_EfuseT3Current' */
real32_T PDU_EfuseT5Current;           /* '<Root>/PDU_EfuseT5Current' */
real32_T PDU_EfuseT1Current;           /* '<Root>/PDU_EfuseT1Current' */
real32_T PDU_EfuseT2Current;           /* '<Root>/PDU_EfuseT2Current' */
real32_T PDU_EfuseT4Current;           /* '<Root>/PDU_EfuseT4Current' */
boolean_T PDU_flgK9StateRaw;           /* '<Root>/PDU_flgK9StateRaw' */
real32_T PDU_EfuseTemp;                /* '<Root>/PDU_EfuseTemp' */
boolean_T PDU_EfuseT3CutFaultRead;     /* '<Root>/PDU_EfuseT3CutFaultRead' */
boolean_T PDU_EfuseT5CutFaultRead;     /* '<Root>/PDU_EfuseT5CutFaultRead' */
boolean_T PDU_EfuseT1CutFaultRead;     /* '<Root>/PDU_EfuseT1CutFaultRead' */
boolean_T PDU_EfuseT2CutFaultRead;     /* '<Root>/PDU_EfuseT2CutFaultRead' */
boolean_T PDU_EfuseT4CutFaultRead;     /* '<Root>/PDU_EfuseT4CutFaultRead' */
boolean_T PDU_flgKL15;                 /* '<Root>/PDU_flgKL15' */
real32_T PDU_BatteryVoltage;           /* '<Root>/PDU_BatteryVoltage' */
real32_T PDU_MainPosVoltage;           /* '<Root>/PDU_MainPosVoltage' */
boolean_T PDU_flgChargeCAN;            /* '<Root>/PDU_flgChargeCAN' */
real32_T PDU_AttVoltage;               /* '<Root>/PDU_AttVoltage' */
boolean_T PDU_flgK5StateRaw;           /* '<Root>/PDU_flgK5StateRaw' */
boolean_T PDU_flgK6StateRaw;           /* '<Root>/PDU_flgK6StateRaw' */
boolean_T PDU_flgK7StateRaw;           /* '<Root>/PDU_flgK7StateRaw' */
boolean_T PDU_flgK8StateRaw;           /* '<Root>/PDU_flgK8StateRaw' */
boolean_T PDU_flgK12StateRaw;          /* '<Root>/PDU_flgK12StateRaw' */
boolean_T PDU_flgOverVol;              /* '<Root>/PDU_flgOverVol' */
uint8_T PDU_HCU3[8];                   /* '<S1>/Constant' */
uint8_T PDU_flgReverseState;           /* '<S4>/Data Type Conversion6' */
uint8_T PDU_flgBatHeatState;           /* '<S4>/Data Type Conversion5' */
uint8_T PDU_flgPTCState;               /* '<S4>/Data Type Conversion4' */
uint8_T PDU_flgMECUState;              /* '<S4>/Data Type Conversion7' */
uint8_T PDU_flgACState;                /* '<S4>/Data Type Conversion8' */
uint8_T PDU_flgK9State;                /* '<S4>/Data Type Conversion9' */
uint8_T PDU_flgMainPosState;           /* '<S4>/Data Type Conversion3' */
uint8_T PDU_flgAttState;               /* '<S4>/Data Type Conversion2' */
uint8_T PDU_state;                     /* '<S3>/Chart' */
uint8_T PDU_EfuseFault;                /* '<S42>/Switch1' */
boolean_T PDU_K10Cmd;                  /* '<S3>/Data Type Conversion' */
boolean_T PDU_K9Cmd;                   /* '<S3>/Data Type Conversion1' */
boolean_T PDU_K4Cmd;                   /* '<S3>/Data Type Conversion10' */
boolean_T PDU_ReserveCmd;              /* '<S3>/Data Type Conversion11' */
boolean_T PDU_PTCCmd;                  /* '<S3>/Data Type Conversion12' */
boolean_T PDU_BatHeatCmd;              /* '<S3>/Data Type Conversion13' */
boolean_T PDU_MECUCmd;                 /* '<S3>/Data Type Conversion14' */
boolean_T PDU_ACCmd;                   /* '<S3>/Data Type Conversion15' */
boolean_T PDU_MainNegCmd;              /* '<S3>/Data Type Conversion16' */
boolean_T PDU_K3Cmd;                   /* '<S3>/Data Type Conversion2' */
boolean_T PDU_MainPosCmd;              /* '<S3>/Data Type Conversion3' */
boolean_T PDU_AttCmd;                  /* '<S3>/Data Type Conversion4' */
boolean_T PDU_EfuseT3Cmd;              /* '<S3>/Data Type Conversion5' */
boolean_T PDU_EfuseT5Cmd;              /* '<S3>/Data Type Conversion6' */
boolean_T PDU_EfuseT1Cmd;              /* '<S3>/Data Type Conversion7' */
boolean_T PDU_EfuseT2Cmd;              /* '<S3>/Data Type Conversion8' */
boolean_T PDU_EfuseT4Cmd;              /* '<S3>/Data Type Conversion9' */
boolean_T PDU_flgShutDown;             /* '<S95>/Logical Operator' */
boolean_T PDU_flgShutDown2Init;        /* '<S96>/Logical Operator NOT1' */
boolean_T PDU_flgAttPreChargeCom;      /* '<S93>/Logical Operator' */
boolean_T PDU_flgMainPreChargeCom;     /* '<S92>/Logical Operator' */
boolean_T PDU_flgInitOK;               /* '<S91>/Logical Operator1' */
boolean_T PDU_flgDrive2Charge;         /* '<S90>/PDU_flgChargeCAN' */
boolean_T PDU_flgCharge2Init;          /* '<S89>/Logical Operator' */
boolean_T PDU_MainPreChargeTimeout;    /* '<S3>/Chart' */
boolean_T PDU_AttPreChargeTimeout;     /* '<S3>/Chart' */
boolean_T PDU_flgAttAdhesion;          /* '<S44>/Logical Operator NOT1' */
boolean_T PDU_flgMainPosAdhesion;      /* '<S45>/Logical Operator NOT1' */
boolean_T PDU_flgK5Adhesion;           /* '<S46>/Logical Operator NOT1' */
boolean_T PDU_flgK6Adhesion;           /* '<S47>/Logical Operator NOT1' */
boolean_T PDU_flgK7Adhesion;           /* '<S48>/Logical Operator NOT1' */
boolean_T PDU_flgK8Adhesion;           /* '<S49>/Logical Operator NOT1' */
boolean_T PDU_flgK9Adhesion;           /* '<S50>/Logical Operator NOT1' */
boolean_T PDU_flgK12Adhesion;          /* '<S51>/Logical Operator NOT1' */
boolean_T PDU_flgRelayAdhesion;        /* '<S27>/Logical Operator' */
boolean_T PDU_flgEfuseT3ConOverCut;    /* '<S71>/Logical Operator NOT1' */
boolean_T PDU_flgEfuseT3InsOverCut;    /* '<S52>/Logical Operator1' */
boolean_T PDU_flgEfuseT5ConOverCut;    /* '<S72>/Logical Operator NOT1' */
boolean_T PDU_flgEfuseT5InsOverCut;    /* '<S52>/Logical Operator3' */
boolean_T PDU_flgEfuseT1ConOverCut;    /* '<S73>/Logical Operator NOT1' */
boolean_T PDU_flgEfuseT1InsOverCut;    /* '<S52>/Logical Operator5' */
boolean_T PDU_flgEfuseT2ConOverCut;    /* '<S74>/Logical Operator NOT1' */
boolean_T PDU_flgEfuseT2InsOverCut;    /* '<S52>/Logical Operator7' */
boolean_T PDU_flgEfuseT4ConOverCut;    /* '<S75>/Logical Operator NOT1' */
boolean_T PDU_flgEfuseT4InsOverCut;    /* '<S52>/Logical Operator9' */
boolean_T PDU_flgEfuseOverCut;         /* '<S52>/Logical Operator10' */
boolean_T PDU_EfuseT3CutFault;         /* '<S27>/Logical Operator3' */
boolean_T PDU_EfuseT5CutFault;         /* '<S27>/Logical Operator4' */
boolean_T PDU_EfuseT1CutFault;         /* '<S27>/Logical Operator5' */
boolean_T PDU_EfuseT2CutFault;         /* '<S27>/Logical Operator6' */
boolean_T PDU_EfuseT4CutFault;         /* '<S27>/Logical Operator7' */
boolean_T PDU_EfuseCutFault;           /* '<S27>/Logical Operator19' */
boolean_T PDU_flgFault;                /* '<S27>/Logical Operator1' */
boolean_T PDU_flgEfuseOverTemp;        /* '<S43>/Logical Operator NOT1' */
boolean_T HCU3ACCmdRaw;                /* '<S6>/Data Type Conversion17' */
boolean_T PDU_HCU3ACCmd;               /* '<S5>/Switch7' */
boolean_T HCU3MECUCmdRaw;              /* '<S6>/Data Type Conversion16' */
boolean_T PDU_HCU3MECUCmd;             /* '<S5>/Switch6' */
boolean_T HCU3PTCCmdRaw;               /* '<S6>/Data Type Conversion15' */
boolean_T PDU_HCU3PTCCmd;              /* '<S5>/Switch5' */
boolean_T HCU3AttCmdRaw;               /* '<S6>/Data Type Conversion14' */
boolean_T PDU_HCU3AttCmd;              /* '<S5>/Switch4' */
boolean_T HCU3BatHeatCmdRaw;           /* '<S6>/Data Type Conversion13' */
boolean_T PDU_HCU3BatHeatCmd;          /* '<S5>/Switch3' */
boolean_T HCU3MainNegCmdRaw;           /* '<S6>/Data Type Conversion12' */
boolean_T PDU_HCU3MainNegCmd;          /* '<S5>/Switch2' */
boolean_T HCU3MainPosCmdRaw;           /* '<S6>/Data Type Conversion11' */
boolean_T PDU_HCU3MainPosCmd;          /* '<S5>/Switch1' */
boolean_T PDU_flgMainPreRelayCommandCom;/* '<S29>/Logical Operator3' */
boolean_T PDU_flgAttPreRelayCommandCom;/* '<S23>/Logical Operator3' */

/* Exported data definition */
#pragma section ".CAL_CONST"
/* ConstVolatile memory section */
/* Definition for custom storage class: ConstVolatile */
const volatile uint8_T HCU_3[8] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U } ;/* Referenced by: '<S1>/Constant' */

const volatile uint32_T PDU_AdhesionThresh = 10U;/* Referenced by:
                                                  * '<S27>/Constant23'
                                                  * '<S27>/Constant26'
                                                  */
const volatile uint32_T PDU_AdhesionTimeThresh = 100U;/* Referenced by:
                                                       * '<S27>/Constant21'
                                                       * '<S27>/Constant25'
                                                       * '<S27>/Constant29'
                                                       * '<S27>/Constant31'
                                                       * '<S27>/Constant33'
                                                       * '<S27>/Constant35'
                                                       * '<S27>/Constant37'
                                                       * '<S27>/Constant39'
                                                       */
const volatile uint32_T PDU_ConOverCurrent = 300U;/* Referenced by:
                                                   * '<S52>/Constant'
                                                   * '<S52>/Constant10'
                                                   * '<S52>/Constant15'
                                                   * '<S52>/Constant20'
                                                   * '<S52>/Constant5'
                                                   */
const volatile real_T PDU_ConOverCutTime = 1000.0;/* Referenced by:
                                                   * '<S52>/Constant12'
                                                   * '<S52>/Constant17'
                                                   * '<S52>/Constant2'
                                                   * '<S52>/Constant22'
                                                   * '<S52>/Constant7'
                                                   */
const volatile uint8_T PDU_EfuseOverTempThresh = 70U;/* Referenced by: '<S27>/Constant1' */
const volatile uint32_T PDU_EfuseOverTempTime = 500U;/* Referenced by: '<S27>/Constant7' */
const volatile uint32_T PDU_InstantOverCurrent = 500U;/* Referenced by:
                                                       * '<S52>/Constant13'
                                                       * '<S52>/Constant14'
                                                       * '<S52>/Constant18'
                                                       * '<S52>/Constant19'
                                                       * '<S52>/Constant23'
                                                       * '<S52>/Constant24'
                                                       * '<S52>/Constant3'
                                                       * '<S52>/Constant4'
                                                       * '<S52>/Constant8'
                                                       * '<S52>/Constant9'
                                                       */
const volatile boolean_T PDU_OverrideHCU3ACCmd = false;/* Referenced by: '<S6>/Constant12' */
const volatile boolean_T PDU_OverrideHCU3AttCmd = false;/* Referenced by: '<S6>/Constant6' */
const volatile boolean_T PDU_OverrideHCU3BatHeatCmd = false;/* Referenced by: '<S6>/Constant4' */
const volatile boolean_T PDU_OverrideHCU3MECUCmd = false;/* Referenced by: '<S6>/Constant10' */
const volatile boolean_T PDU_OverrideHCU3MainNegCmd = false;/* Referenced by: '<S6>/Constant2' */
const volatile boolean_T PDU_OverrideHCU3MainPosCmd = false;/* Referenced by: '<S6>/Constant' */
const volatile boolean_T PDU_OverrideHCU3PTCCmd = false;/* Referenced by: '<S6>/Constant8' */
const volatile real32_T PDU_PreChargeFactor = 0.95F;/* Referenced by:
                                                     * '<S4>/Constant1'
                                                     * '<S4>/Constant11'
                                                     * '<S23>/Constant11'
                                                     * '<S29>/Constant11'
                                                     * '<S92>/Constant'
                                                     * '<S93>/Constant'
                                                     */
const volatile real_T PDU_TIME = 10.0; /* Referenced by:
                                        * '<S23>/Constant10'
                                        * '<S27>/Constant20'
                                        * '<S27>/Constant24'
                                        * '<S27>/Constant28'
                                        * '<S27>/Constant30'
                                        * '<S27>/Constant32'
                                        * '<S27>/Constant34'
                                        * '<S27>/Constant36'
                                        * '<S27>/Constant38'
                                        * '<S27>/Constant6'
                                        * '<S29>/Constant10'
                                        * '<S52>/Constant1'
                                        * '<S52>/Constant11'
                                        * '<S52>/Constant16'
                                        * '<S52>/Constant21'
                                        * '<S52>/Constant6'
                                        * '<S94>/Constant6'
                                        */
const volatile uint32_T PDU_WaitAttTime = 30U;/* Referenced by: '<S23>/Constant12' */
const volatile uint8_T PDU_WaitMainPosTime = 30U;/* Referenced by: '<S29>/Constant12' */
const volatile boolean_T PDU_flgACRelayCmdUseCal = false;/* Referenced by: '<S23>/Constant25' */
const volatile boolean_T PDU_flgBatHeatRelayCmdUseCal = false;/* Referenced by: '<S23>/Constant7' */
const volatile boolean_T PDU_flgMECURelayCmdUseCal = true;/* Referenced by: '<S23>/Constant23' */
const volatile boolean_T PDU_flgOverrideACRelay = false;/* Referenced by: '<S3>/Constant20' */
const volatile boolean_T PDU_flgOverrideAttRelay = false;/* Referenced by: '<S3>/Constant' */
const volatile boolean_T PDU_flgOverrideBatHeatRelay = true;/* Referenced by: '<S3>/Constant16' */
const volatile boolean_T PDU_flgOverrideK10Relay = false;/* Referenced by: '<S3>/Constant8' */
const volatile boolean_T PDU_flgOverrideK3Relay = true;/* Referenced by: '<S3>/Constant4' */
const volatile boolean_T PDU_flgOverrideK4Relay = false;/* Referenced by: '<S3>/Constant10' */
const volatile boolean_T PDU_flgOverrideK9Relay = false;/* Referenced by: '<S3>/Constant6' */
const volatile boolean_T PDU_flgOverrideMECURelay = false;/* Referenced by: '<S3>/Constant18' */
const volatile boolean_T PDU_flgOverrideMainNegRelay = false;/* Referenced by: '<S3>/Constant22' */
const volatile boolean_T PDU_flgOverrideMainPosRelay = false;/* Referenced by: '<S3>/Constant2' */
const volatile boolean_T PDU_flgOverridePTCRelay = true;/* Referenced by: '<S3>/Constant14' */
const volatile boolean_T PDU_flgOverrideReverseRelay = true;/* Referenced by: '<S3>/Constant12' */
const volatile boolean_T PDU_flgOverrideT1 = false;/* Referenced by: '<S3>/Constant28' */
const volatile boolean_T PDU_flgOverrideT2 = false;/* Referenced by: '<S3>/Constant30' */
const volatile boolean_T PDU_flgOverrideT3 = false;/* Referenced by: '<S3>/Constant24' */
const volatile boolean_T PDU_flgOverrideT4 = false;/* Referenced by: '<S3>/Constant32' */
const volatile boolean_T PDU_flgOverrideT5 = false;/* Referenced by: '<S3>/Constant26' */
const volatile boolean_T PDU_flgPTCRelayCmdUseCal = false;/* Referenced by: '<S23>/Constant21' */
const volatile boolean_T PDU_flgReserveRelayCmdUseCal = false;/* Referenced by: '<S23>/Constant9' */
const volatile boolean_T PDU_manACCmd = false;/* Referenced by: '<S3>/Constant21' */
const volatile boolean_T PDU_manAttCmd = false;/* Referenced by: '<S3>/Constant1' */
const volatile boolean_T PDU_manBatHeatCmd = true;/* Referenced by: '<S3>/Constant17' */
const volatile boolean_T PDU_manK10Cmd = false;/* Referenced by: '<S3>/Constant9' */
const volatile boolean_T PDU_manK3Cmd = true;/* Referenced by: '<S3>/Constant5' */
const volatile boolean_T PDU_manK4Cmd = false;/* Referenced by: '<S3>/Constant11' */
const volatile boolean_T PDU_manK9Cmd = false;/* Referenced by: '<S3>/Constant7' */
const volatile boolean_T PDU_manMECUCmd = false;/* Referenced by: '<S3>/Constant19' */
const volatile boolean_T PDU_manMainNegCmd = false;/* Referenced by: '<S3>/Constant23' */
const volatile boolean_T PDU_manMainPosCmd = false;/* Referenced by: '<S3>/Constant3' */
const volatile boolean_T PDU_manPTCCmd = true;/* Referenced by: '<S3>/Constant15' */
const volatile boolean_T PDU_manReverseCmd = false;/* Referenced by: '<S3>/Constant13' */
const volatile boolean_T PDU_manT1Cmd = false;/* Referenced by: '<S3>/Constant29' */
const volatile boolean_T PDU_manT2Cmd = false;/* Referenced by: '<S3>/Constant31' */
const volatile boolean_T PDU_manT3Cmd = false;/* Referenced by: '<S3>/Constant25' */
const volatile boolean_T PDU_manT4Cmd = false;/* Referenced by: '<S3>/Constant33' */
const volatile boolean_T PDU_manT5Cmd = false;/* Referenced by: '<S3>/Constant27' */
const volatile uint8_T PDU_numEfuseFaultReact = 0U;/* Referenced by: '<S26>/Constant1' */
const volatile boolean_T PDU_orHCU3ACCmd = false;/* Referenced by: '<S6>/Constant13' */
const volatile boolean_T PDU_orHCU3AttCmd = false;/* Referenced by: '<S6>/Constant7' */
const volatile uint8_T PDU_orHCU3BatHeatCmd = 0U;/* Referenced by: '<S6>/Constant5' */
const volatile boolean_T PDU_orHCU3MECUCmd = false;/* Referenced by: '<S6>/Constant11' */
const volatile boolean_T PDU_orHCU3MainNegCmd = false;/* Referenced by: '<S6>/Constant3' */
const volatile boolean_T PDU_orHCU3MainPosCmd = false;/* Referenced by: '<S6>/Constant1' */
const volatile boolean_T PDU_orHCU3PTCCmd = false;/* Referenced by: '<S6>/Constant9' */
const volatile boolean_T PDU_overEfuseFaultReact = false;/* Referenced by: '<S26>/Constant' */
const volatile uint16_T PDU_reInitTime = 100U;/* Referenced by: '<S94>/Constant7' */
#pragma section
/* Block states (default storage) */
DW_PDU_T PDU_DW;

/* Real-time model */
static RT_MODEL_PDU_T PDU_M_;
RT_MODEL_PDU_T *const PDU_M = &PDU_M_;
void PDU_SR_latch(boolean_T rtu_flg_set, boolean_T rtu_flg_reset, boolean_T
                  *rty_flg_out, DW_SR_latch_PDU_T *localDW)
{
  /* Logic: '<S54>/Logical Operator3' incorporates:
   *  Logic: '<S54>/Logical Operator'
   *  Logic: '<S54>/Logical Operator1'
   *  UnitDelay: '<S54>/Unit Delay'
   */
  *rty_flg_out = ((localDW->UnitDelay_DSTATE || rtu_flg_set) && (!rtu_flg_reset));
}

/*
 * Update for atomic system:
 *    '<S43>/SR_latch'
 *    '<S44>/SR_latch'
 *    '<S45>/SR_latch'
 *    '<S46>/SR_latch'
 *    '<S47>/SR_latch'
 *    '<S48>/SR_latch'
 *    '<S49>/SR_latch'
 *    '<S50>/SR_latch'
 *    '<S51>/SR_latch'
 *    '<S71>/SR_latch'
 *    ...
 */
void PDU_SR_latch_Update(boolean_T *rty_flg_out, DW_SR_latch_PDU_T *localDW)
{
  /* Update for UnitDelay: '<S54>/Unit Delay' */
  localDW->UnitDelay_DSTATE = *rty_flg_out;
}

/* Output and update for function-call system: '<S3>/PDU_INIT' */
void PDU_PDU_INIT(boolean_T rtu_PDU_HCU3MainNegCmd, boolean_T
                  *rty_PDU_flgMainPosRelayCmdCharg, boolean_T
                  *rty_PDU_flgMainNegRelayCmdCharg, boolean_T
                  *rty_PDU_flgAttRelayCmdCharge, boolean_T
                  *rty_PDU_flgK4RelayCmdCharge, boolean_T
                  *rty_PDU_flgK3RelayCmdCharge, boolean_T
                  *rty_PDU_flgReverseRelayCmdCharg, boolean_T
                  *rty_PDU_flgPTCRelayCmdCharge, boolean_T
                  *rty_PDU_flgBatHeatRelayCmdCharg, boolean_T
                  *rty_PDU_flgMECURelayCmdCharge, boolean_T
                  *rty_PDU_flgACRelayCmdCharge, boolean_T
                  *rty_PDU_flgK9RelayCmdCharge, boolean_T
                  *rty_PDU_flgK10RelayCmdCharge, boolean_T
                  *rty_PDU_flgEfuseT3CmdCharge, boolean_T
                  *rty_PDU_flgEfuseT5CmdCharge, boolean_T
                  *rty_PDU_flgEfuseT1CmdCharge, boolean_T
                  *rty_PDU_flgEfuseT2CmdCharge, boolean_T
                  *rty_PDU_flgEfuseT4CmdCharge)
{
  /* SignalConversion generated from: '<S28>/PDU_flgMainPosRelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant2'
   */
  *rty_PDU_flgMainPosRelayCmdCharg = false;

  /* SignalConversion generated from: '<S28>/PDU_flgAttRelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant16'
   */
  *rty_PDU_flgAttRelayCmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgK4RelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant1'
   */
  *rty_PDU_flgK4RelayCmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgK3RelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant10'
   */
  *rty_PDU_flgK3RelayCmdCharge = true;

  /* SignalConversion generated from: '<S28>/PDU_flgReverseRelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant6'
   */
  *rty_PDU_flgReverseRelayCmdCharg = true;

  /* SignalConversion generated from: '<S28>/PDU_flgPTCRelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant12'
   */
  *rty_PDU_flgPTCRelayCmdCharge = true;

  /* SignalConversion generated from: '<S28>/PDU_flgBatHeatRelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant13'
   */
  *rty_PDU_flgBatHeatRelayCmdCharg = true;

  /* SignalConversion generated from: '<S28>/PDU_flgMECURelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant14'
   */
  *rty_PDU_flgMECURelayCmdCharge = true;

  /* SignalConversion generated from: '<S28>/PDU_flgACRelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant15'
   */
  *rty_PDU_flgACRelayCmdCharge = true;

  /* SignalConversion generated from: '<S28>/PDU_flgK9RelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant3'
   */
  *rty_PDU_flgK9RelayCmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgK10RelayCmdCharge' incorporates:
   *  Constant: '<S28>/Constant4'
   */
  *rty_PDU_flgK10RelayCmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgEfuseT3CmdCharge' incorporates:
   *  Constant: '<S28>/Constant5'
   */
  *rty_PDU_flgEfuseT3CmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgEfuseT5CmdCharge' incorporates:
   *  Constant: '<S28>/Constant7'
   */
  *rty_PDU_flgEfuseT5CmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgEfuseT1CmdCharge' incorporates:
   *  Constant: '<S28>/Constant8'
   */
  *rty_PDU_flgEfuseT1CmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgEfuseT2CmdCharge' incorporates:
   *  Constant: '<S28>/Constant11'
   */
  *rty_PDU_flgEfuseT2CmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_flgEfuseT4CmdCharge' incorporates:
   *  Constant: '<S28>/Constant9'
   */
  *rty_PDU_flgEfuseT4CmdCharge = false;

  /* SignalConversion generated from: '<S28>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdCharg = rtu_PDU_HCU3MainNegCmd;
}

/* System initialize for function-call system: '<S3>/PDU_ATTPRECHARGE' */
void PDU_PDU_ATTPRECHARGE_Init(DW_PDU_ATTPRECHARGE_PDU_T *localDW)
{
  /* InitializeConditions for UnitDelay: '<S32>/Unit Delay4' */
  localDW->UnitDelay4_DSTATE = true;

  /* InitializeConditions for UnitDelay: '<S32>/Unit Delay5' */
  localDW->UnitDelay5_DSTATE = true;
}

/* Output and update for function-call system: '<S3>/PDU_ATTPRECHARGE' */
void PDU_PDU_ATTPRECHARGE(real32_T rtu_PDU_AttVoltage, real32_T
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
  DW_PDU_ATTPRECHARGE_PDU_T *localDW)
{
  real32_T rtb_Switch4_nd;
  boolean_T rtb_LogicalOperator1_i;
  boolean_T rtb_LogicalOperator2_im;
  boolean_T rtb_RelationalOperator3_n;
  boolean_T rtb_Switch5_ln;
  boolean_T rtb_UnitDelay3_ee;

  /* SignalConversion generated from: '<S23>/PDU_flgMainPosRelayCmdPreA' incorporates:
   *  Constant: '<S23>/Constant1'
   */
  *rty_PDU_flgMainPosRelayCmdPreA = false;

  /* SignalConversion generated from: '<S23>/PDU_flgEfuseT5CmdPreA' incorporates:
   *  Constant: '<S23>/Constant6'
   */
  *rty_PDU_flgEfuseT5CmdPreA = false;

  /* SignalConversion generated from: '<S23>/PDU_flgK3RelayCmdPreA' incorporates:
   *  Constant: '<S23>/Constant6'
   */
  *rty_PDU_flgK3RelayCmdPreA = false;

  /* SignalConversion generated from: '<S23>/PDU_flgK9RelayCmdPreA' incorporates:
   *  Constant: '<S23>/Constant3'
   */
  *rty_PDU_flgK9RelayCmdPreA = false;

  /* SignalConversion generated from: '<S23>/PDU_flgK10RelayCmdPreA' incorporates:
   *  Constant: '<S23>/Constant4'
   */
  *rty_PDU_flgK10RelayCmdPreA = false;

  /* SignalConversion generated from: '<S23>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdPreA = rtu_PDU_HCU3MainNegCmd;

  /* UnitDelay: '<S23>/Unit Delay6' */
  *rty_PDU_flgEfuseT3CmdPreA = localDW->UnitDelay6_DSTATE;

  /* RelationalOperator: '<S23>/Relational Operator' incorporates:
   *  Constant: '<S23>/Constant11'
   *  Product: '<S23>/Product'
   */
  rtb_RelationalOperator3_n = (rtu_PDU_AttVoltage <= PDU_PreChargeFactor *
    rtu_PDU_BatteryVoltage);

  /* Logic: '<S23>/Logical Operator1' */
  rtb_LogicalOperator1_i = !rtb_RelationalOperator3_n;

  /* Switch: '<S23>/Switch2' */
  rtb_Switch5_ln = (rtb_LogicalOperator1_i && rtu_PDU_HCU3AttCmd);

  /* SignalConversion generated from: '<S23>/PDU_flgAttRelayCmdPreA' */
  *rty_PDU_flgAttRelayCmdPreA = rtb_Switch5_ln;

  /* Logic: '<S23>/Logical Operator2' */
  rtb_LogicalOperator2_im = !rtb_LogicalOperator1_i;

  /* UnitDelay: '<S32>/Unit Delay3' */
  rtb_UnitDelay3_ee = localDW->UnitDelay3_DSTATE;

  /* Outputs for Atomic SubSystem: '<S32>/SR_latch' */
  /* Logic: '<S32>/Logical Operator' incorporates:
   *  Logic: '<S32>/Logical Operator NOT4'
   *  Logic: '<S32>/Logical Operator NOT5'
   *  Logic: '<S32>/Logical Operator2'
   *  UnitDelay: '<S32>/Unit Delay3'
   *  UnitDelay: '<S32>/Unit Delay4'
   *  UnitDelay: '<S32>/Unit Delay5'
   */
  PDU_SR_latch(rtb_LogicalOperator1_i && (!localDW->UnitDelay4_DSTATE),
               rtb_LogicalOperator2_im && (!localDW->UnitDelay5_DSTATE),
               &localDW->UnitDelay3_DSTATE, &localDW->SR_latch);

  /* End of Outputs for SubSystem: '<S32>/SR_latch' */

  /* Switch: '<S32>/Switch1' incorporates:
   *  Switch: '<S32>/Switch'
   *  UnitDelay: '<S32>/Unit Delay3'
   */
  if (rtb_LogicalOperator2_im) {
    /* Switch: '<S32>/Switch1' incorporates:
     *  Constant: '<S32>/Constant1'
     */
    localDW->UnitDelay1_DSTATE = 0.0;
  } else {
    real_T tmp;
    if (localDW->UnitDelay3_DSTATE) {
      /* Switch: '<S32>/Switch3' incorporates:
       *  Constant: '<S23>/Constant10'
       *  Constant: '<S32>/Constant4'
       *  Constant: '<S32>/Constant6'
       *  Logic: '<S32>/Logical Operator NOT2'
       *  Logic: '<S32>/Logical Operator NOT3'
       *  Logic: '<S32>/Logical Operator1'
       *  RelationalOperator: '<S32>/Relational Operator4'
       *  Switch: '<S32>/Switch'
       *  Switch: '<S32>/Switch5'
       *  UnitDelay: '<S32>/Unit Delay2'
       */
      if (rtb_LogicalOperator1_i && (!localDW->UnitDelay2_DSTATE) &&
          (!rtb_UnitDelay3_ee)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S32>/Switch5' incorporates:
         *  Constant: '<S23>/Constant10'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S32>/Switch3' */
    } else {
      /* Switch: '<S32>/Switch' incorporates:
       *  Constant: '<S32>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S32>/Switch1' incorporates:
     *  Sum: '<S32>/Sum'
     *  Switch: '<S32>/Switch'
     *  UnitDelay: '<S32>/Unit Delay1'
     */
    localDW->UnitDelay1_DSTATE += tmp;
  }

  /* End of Switch: '<S32>/Switch1' */

  /* Switch: '<S32>/Switch4' incorporates:
   *  Constant: '<S23>/Constant12'
   *  Constant: '<S32>/Constant3'
   *  RelationalOperator: '<S32>/Relational Operator3'
   */
  if (PDU_WaitAttTime > 0.0F) {
    rtb_Switch4_nd = (real32_T)PDU_WaitAttTime;
  } else {
    rtb_Switch4_nd = 0.0F;
  }

  /* End of Switch: '<S32>/Switch4' */

  /* RelationalOperator: '<S32>/Relational Operator' */
  rtb_UnitDelay3_ee = (localDW->UnitDelay1_DSTATE < rtb_Switch4_nd);

  /* Switch: '<S23>/Switch' incorporates:
   *  Constant: '<S23>/Constant2'
   *  Logic: '<S23>/Logical Operator'
   *  Logic: '<S32>/Logical Operator NOT1'
   *  UnitDelay: '<S23>/Unit Delay'
   */
  if (rtb_RelationalOperator3_n && rtu_PDU_flgKL15) {
    localDW->UnitDelay_DSTATE = true;
  } else {
    localDW->UnitDelay_DSTATE = (rtb_UnitDelay3_ee && localDW->UnitDelay_DSTATE);
  }

  /* End of Switch: '<S23>/Switch' */

  /* Logic: '<S23>/Logical Operator3' incorporates:
   *  Logic: '<S23>/Logical Operator4'
   *  UnitDelay: '<S23>/Unit Delay'
   */
  PDU_flgAttPreRelayCommandCom = (rtb_Switch5_ln && (!localDW->UnitDelay_DSTATE));

  /* SignalConversion generated from: '<S23>/PDU_flgEfuseT1CmdPreA' */
  *rty_PDU_flgEfuseT1CmdPreA = false;

  /* Switch: '<S23>/Switch9' incorporates:
   *  Constant: '<S23>/Constant9'
   */
  *rty_PDU_flgReserveRelayCmdPreA = !PDU_flgReserveRelayCmdUseCal;

  /* Switch: '<S23>/Switch3' */
  rtb_Switch5_ln = (PDU_flgAttPreRelayCommandCom && rtu_PDU_HCU3BatHeatCmd);

  /* SignalConversion generated from: '<S23>/PDU_flgEfuseT2CmdPreA' */
  *rty_PDU_flgEfuseT2CmdPreA = rtb_Switch5_ln;

  /* Switch: '<S23>/Switch8' incorporates:
   *  Constant: '<S23>/Constant7'
   */
  *rty_PDU_flgBatHeatRelayCmdPreA = ((!PDU_flgBatHeatRelayCmdUseCal) ||
    rtb_Switch5_ln);

  /* Switch: '<S23>/Switch5' */
  rtb_Switch5_ln = (PDU_flgAttPreRelayCommandCom && rtu_PDU_HCU3PTCCmd);

  /* SignalConversion generated from: '<S23>/PDU_flgEfuseT4CmdPreA' */
  *rty_PDU_flgEfuseT4CmdPreA = rtb_Switch5_ln;

  /* Switch: '<S23>/Switch10' incorporates:
   *  Constant: '<S23>/Constant21'
   */
  *rty_PDU_flgPTCRelayCmdPreA = ((!PDU_flgPTCRelayCmdUseCal) || rtb_Switch5_ln);

  /* Switch: '<S23>/Switch11' incorporates:
   *  Constant: '<S23>/Constant22'
   *  Constant: '<S23>/Constant23'
   *  Switch: '<S23>/Switch6'
   */
  if (PDU_flgMECURelayCmdUseCal) {
    *rty_PDU_flgMECURelayCmdPreA = (PDU_flgAttPreRelayCommandCom &&
      rtu_PDU_HCU3MECUCmd);
  } else {
    *rty_PDU_flgMECURelayCmdPreA = true;
  }

  /* End of Switch: '<S23>/Switch11' */

  /* Switch: '<S23>/Switch12' incorporates:
   *  Constant: '<S23>/Constant24'
   *  Constant: '<S23>/Constant25'
   *  Switch: '<S23>/Switch7'
   */
  if (PDU_flgACRelayCmdUseCal) {
    *rty_PDU_flgACRelayCmdPreA = (PDU_flgAttPreRelayCommandCom &&
      rtu_PDU_HCU3ACCmd);
  } else {
    *rty_PDU_flgACRelayCmdPreA = true;
  }

  /* End of Switch: '<S23>/Switch12' */

  /* SignalConversion generated from: '<S23>/PDU_flgK4RelayCmdPreA' incorporates:
   *  UnitDelay: '<S23>/Unit Delay'
   */
  *rty_PDU_flgK4RelayCmdPreA = localDW->UnitDelay_DSTATE;

  /* Switch: '<S32>/Switch2' */
  if (!rtb_UnitDelay3_ee) {
    /* Switch: '<S32>/Switch1' */
    localDW->UnitDelay1_DSTATE = rtb_Switch4_nd;
  }

  /* End of Switch: '<S32>/Switch2' */

  /* Update for UnitDelay: '<S23>/Unit Delay6' incorporates:
   *  UnitDelay: '<S23>/Unit Delay'
   */
  localDW->UnitDelay6_DSTATE = localDW->UnitDelay_DSTATE;

  /* Update for UnitDelay: '<S32>/Unit Delay2' */
  localDW->UnitDelay2_DSTATE = rtb_LogicalOperator1_i;

  /* Update for UnitDelay: '<S32>/Unit Delay4' */
  localDW->UnitDelay4_DSTATE = rtb_LogicalOperator1_i;

  /* Update for UnitDelay: '<S32>/Unit Delay5' */
  localDW->UnitDelay5_DSTATE = rtb_LogicalOperator2_im;

  /* Update for Atomic SubSystem: '<S32>/SR_latch' */
  /* UnitDelay: '<S32>/Unit Delay3' */
  PDU_SR_latch_Update(&localDW->UnitDelay3_DSTATE, &localDW->SR_latch);

  /* End of Update for SubSystem: '<S32>/SR_latch' */
}

/* System initialize for function-call system: '<S3>/PDU_MAINPRECHARGE' */
void PDU_PDU_MAINPRECHARGE_Init(DW_PDU_MAINPRECHARGE_PDU_T *localDW)
{
  /* InitializeConditions for UnitDelay: '<S86>/Unit Delay4' */
  localDW->UnitDelay4_DSTATE = true;

  /* InitializeConditions for UnitDelay: '<S86>/Unit Delay5' */
  localDW->UnitDelay5_DSTATE = true;
}

/* Output and update for function-call system: '<S3>/PDU_MAINPRECHARGE' */
void PDU_PDU_MAINPRECHARGE(real32_T rtu_PDU_MainPosVoltage, real32_T
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
  *rty_PDU_flgEfuseT4CmdPre, DW_PDU_MAINPRECHARGE_PDU_T *localDW)
{
  int32_T rtb_Switch4_h;
  boolean_T rtb_LogicalOperator1_bi;
  boolean_T rtb_LogicalOperator2_ch;
  boolean_T rtb_RelationalOperator3_d;
  boolean_T rtb_Switch2_gk;
  boolean_T rtb_UnitDelay3_di;

  /* SignalConversion generated from: '<S29>/PDU_flgK4RelayCmdPre' incorporates:
   *  Constant: '<S29>/Constant6'
   */
  *rty_PDU_flgK4RelayCmdPre = false;

  /* SignalConversion generated from: '<S29>/PDU_flgEfuseT1CmdPre' incorporates:
   *  Constant: '<S29>/Constant1'
   */
  *rty_PDU_flgEfuseT1CmdPre = false;

  /* SignalConversion generated from: '<S29>/PDU_flgReverseRelayCmdPre' incorporates:
   *  Constant: '<S29>/Constant1'
   */
  *rty_PDU_flgReverseRelayCmdPre = false;

  /* SignalConversion generated from: '<S29>/PDU_flgK9RelayCmdPre' incorporates:
   *  Constant: '<S29>/Constant3'
   */
  *rty_PDU_flgK9RelayCmdPre = false;

  /* SignalConversion generated from: '<S29>/PDU_flgK10RelayCmdPre' incorporates:
   *  Constant: '<S29>/Constant4'
   */
  *rty_PDU_flgK10RelayCmdPre = false;

  /* SignalConversion generated from: '<S29>/PDU_flgEfuseT3CmdPre' incorporates:
   *  Constant: '<S29>/Constant5'
   */
  *rty_PDU_flgEfuseT3CmdPre = false;

  /* SignalConversion generated from: '<S29>/PDU_flgEfuseT4CmdPre' incorporates:
   *  SignalConversion generated from: '<S29>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgEfuseT4CmdPre = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S29>/PDU_flgPTCRelayCmdPre' incorporates:
   *  SignalConversion generated from: '<S29>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgPTCRelayCmdPre = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S29>/PDU_flgBatHeatRelayCmdPre' incorporates:
   *  SignalConversion generated from: '<S29>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgBatHeatRelayCmdPre = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S29>/PDU_flgEfuseT2CmdPre' incorporates:
   *  SignalConversion generated from: '<S29>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgEfuseT2CmdPre = rtu_PDU_HCU3BatHeatCmd;

  /* UnitDelay: '<S29>/Unit Delay1' */
  *rty_PDU_flgEfuseT5CmdPre = localDW->UnitDelay1_DSTATE_n;

  /* RelationalOperator: '<S29>/Relational Operator' incorporates:
   *  Constant: '<S29>/Constant11'
   *  Product: '<S29>/Product'
   */
  rtb_RelationalOperator3_d = (rtu_PDU_MainPosVoltage <= PDU_PreChargeFactor *
    rtu_PDU_BatteryVoltage);

  /* Logic: '<S29>/Logical Operator1' */
  rtb_LogicalOperator1_bi = !rtb_RelationalOperator3_d;

  /* Switch: '<S29>/Switch2' */
  rtb_Switch2_gk = (rtb_LogicalOperator1_bi && rtu_PDU_HCU3MainPosCmd);

  /* SignalConversion generated from: '<S29>/PDU_flgMainPosRelayCmdPre' */
  *rty_PDU_flgMainPosRelayCmdPre = rtb_Switch2_gk;

  /* Logic: '<S29>/Logical Operator2' */
  rtb_LogicalOperator2_ch = !rtb_LogicalOperator1_bi;

  /* UnitDelay: '<S86>/Unit Delay3' */
  rtb_UnitDelay3_di = localDW->UnitDelay3_DSTATE;

  /* Outputs for Atomic SubSystem: '<S86>/SR_latch' */
  /* Logic: '<S86>/Logical Operator' incorporates:
   *  Logic: '<S86>/Logical Operator NOT4'
   *  Logic: '<S86>/Logical Operator NOT5'
   *  Logic: '<S86>/Logical Operator2'
   *  UnitDelay: '<S86>/Unit Delay3'
   *  UnitDelay: '<S86>/Unit Delay4'
   *  UnitDelay: '<S86>/Unit Delay5'
   */
  PDU_SR_latch(rtb_LogicalOperator1_bi && (!localDW->UnitDelay4_DSTATE),
               rtb_LogicalOperator2_ch && (!localDW->UnitDelay5_DSTATE),
               &localDW->UnitDelay3_DSTATE, &localDW->SR_latch);

  /* End of Outputs for SubSystem: '<S86>/SR_latch' */

  /* Switch: '<S86>/Switch1' incorporates:
   *  Switch: '<S86>/Switch'
   *  UnitDelay: '<S86>/Unit Delay3'
   */
  if (rtb_LogicalOperator2_ch) {
    /* Switch: '<S86>/Switch1' incorporates:
     *  Constant: '<S86>/Constant1'
     */
    localDW->UnitDelay1_DSTATE = 0.0;
  } else {
    real_T tmp;
    if (localDW->UnitDelay3_DSTATE) {
      /* Switch: '<S86>/Switch3' incorporates:
       *  Constant: '<S29>/Constant10'
       *  Constant: '<S86>/Constant4'
       *  Constant: '<S86>/Constant6'
       *  Logic: '<S86>/Logical Operator NOT2'
       *  Logic: '<S86>/Logical Operator NOT3'
       *  Logic: '<S86>/Logical Operator1'
       *  RelationalOperator: '<S86>/Relational Operator4'
       *  Switch: '<S86>/Switch'
       *  Switch: '<S86>/Switch5'
       *  UnitDelay: '<S86>/Unit Delay2'
       */
      if (rtb_LogicalOperator1_bi && (!localDW->UnitDelay2_DSTATE) &&
          (!rtb_UnitDelay3_di)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S86>/Switch5' incorporates:
         *  Constant: '<S29>/Constant10'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S86>/Switch3' */
    } else {
      /* Switch: '<S86>/Switch' incorporates:
       *  Constant: '<S86>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S86>/Switch1' incorporates:
     *  Sum: '<S86>/Sum'
     *  Switch: '<S86>/Switch'
     *  UnitDelay: '<S86>/Unit Delay1'
     */
    localDW->UnitDelay1_DSTATE += tmp;
  }

  /* End of Switch: '<S86>/Switch1' */

  /* Switch: '<S86>/Switch4' incorporates:
   *  Constant: '<S29>/Constant12'
   *  Constant: '<S86>/Constant3'
   *  RelationalOperator: '<S86>/Relational Operator3'
   */
  if (PDU_WaitMainPosTime > 0) {
    rtb_Switch4_h = PDU_WaitMainPosTime;
  } else {
    rtb_Switch4_h = 0;
  }

  /* End of Switch: '<S86>/Switch4' */

  /* RelationalOperator: '<S86>/Relational Operator' */
  rtb_UnitDelay3_di = (localDW->UnitDelay1_DSTATE < rtb_Switch4_h);

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant2'
   *  Logic: '<S29>/Logical Operator'
   *  Logic: '<S86>/Logical Operator NOT1'
   *  UnitDelay: '<S29>/Unit Delay'
   */
  if (rtb_RelationalOperator3_d && rtu_PDU_flgKL15) {
    localDW->UnitDelay_DSTATE = true;
  } else {
    localDW->UnitDelay_DSTATE = (rtb_UnitDelay3_di && localDW->UnitDelay_DSTATE);
  }

  /* End of Switch: '<S29>/Switch' */

  /* Logic: '<S29>/Logical Operator3' incorporates:
   *  Logic: '<S29>/Logical Operator4'
   *  UnitDelay: '<S29>/Unit Delay'
   */
  PDU_flgMainPreRelayCommandCom = (rtb_Switch2_gk && (!localDW->UnitDelay_DSTATE));

  /* SignalConversion generated from: '<S29>/PDU_flgK3RelayCmdPre' incorporates:
   *  UnitDelay: '<S29>/Unit Delay'
   */
  *rty_PDU_flgK3RelayCmdPre = localDW->UnitDelay_DSTATE;

  /* Switch: '<S86>/Switch2' */
  if (!rtb_UnitDelay3_di) {
    /* Switch: '<S86>/Switch1' */
    localDW->UnitDelay1_DSTATE = rtb_Switch4_h;
  }

  /* End of Switch: '<S86>/Switch2' */

  /* SignalConversion generated from: '<S29>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdPre = rtu_PDU_HCU3MainNegCmd;

  /* SignalConversion generated from: '<S29>/PDU_HCU3AttCmd' */
  *rty_PDU_flgAttRelayCmdPre = rtu_PDU_HCU3AttCmd;

  /* SignalConversion generated from: '<S29>/PDU_HCU3MECUCmd' */
  *rty_PDU_flgMECURelayCmdPre = rtu_PDU_HCU3MECUCmd;

  /* SignalConversion generated from: '<S29>/PDU_HCU3ACCmd' */
  *rty_PDU_flgACRelayCmdPre = rtu_PDU_HCU3ACCmd;

  /* Update for UnitDelay: '<S29>/Unit Delay1' incorporates:
   *  UnitDelay: '<S29>/Unit Delay'
   */
  localDW->UnitDelay1_DSTATE_n = localDW->UnitDelay_DSTATE;

  /* Update for UnitDelay: '<S86>/Unit Delay2' */
  localDW->UnitDelay2_DSTATE = rtb_LogicalOperator1_bi;

  /* Update for UnitDelay: '<S86>/Unit Delay4' */
  localDW->UnitDelay4_DSTATE = rtb_LogicalOperator1_bi;

  /* Update for UnitDelay: '<S86>/Unit Delay5' */
  localDW->UnitDelay5_DSTATE = rtb_LogicalOperator2_ch;

  /* Update for Atomic SubSystem: '<S86>/SR_latch' */
  /* UnitDelay: '<S86>/Unit Delay3' */
  PDU_SR_latch_Update(&localDW->UnitDelay3_DSTATE, &localDW->SR_latch);

  /* End of Update for SubSystem: '<S86>/SR_latch' */
}

/* Output and update for function-call system: '<S3>/PDU_DRIVE' */
void PDU_PDU_DRIVE(boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
                   rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd,
                   boolean_T rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd,
                   boolean_T rtu_PDU_HCU3ACCmd, boolean_T rtu_PDU_HCU3AttCmd,
                   boolean_T *rty_PDU_flgMainPosRelayCmdDrive, boolean_T
                   *rty_PDU_flgMainNegRelayCmdDrive, boolean_T
                   *rty_PDU_flgAttRelayCmdDrive, boolean_T
                   *rty_PDU_flgK4RelayCmdDrive, boolean_T
                   *rty_PDU_flgK3RelayCmdDrive, boolean_T
                   *rty_PDU_flgReverseRelayCmdDrive, boolean_T
                   *rty_PDU_flgPTCRelayCmdDrive, boolean_T
                   *rty_PDU_flgBatHeatRelayCmdDrive, boolean_T
                   *rty_PDU_flgMECURelayCmdDrive, boolean_T
                   *rty_PDU_flgACRelayCmdDrive, boolean_T
                   *rty_PDU_flgK9RelayCmdDrive, boolean_T
                   *rty_PDU_flgK10RelayCmdDrive, boolean_T
                   *rty_PDU_flgEfuseT3CmdDrive, boolean_T
                   *rty_PDU_flgEfuseT5CmdDrive, boolean_T
                   *rty_PDU_flgEfuseT1CmdDrive, boolean_T
                   *rty_PDU_flgEfuseT2CmdDrive, boolean_T
                   *rty_PDU_flgEfuseT4CmdDrive)
{
  /* SignalConversion generated from: '<S25>/PDU_flgEfuseT3CmdDrive' incorporates:
   *  Constant: '<S25>/Constant1'
   */
  *rty_PDU_flgEfuseT3CmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgK4RelayCmdDrive' incorporates:
   *  Constant: '<S25>/Constant1'
   */
  *rty_PDU_flgK4RelayCmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgEfuseT5CmdDrive' incorporates:
   *  Constant: '<S25>/Constant10'
   */
  *rty_PDU_flgEfuseT5CmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgK3RelayCmdDrive' incorporates:
   *  Constant: '<S25>/Constant10'
   */
  *rty_PDU_flgK3RelayCmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgEfuseT1CmdDrive' incorporates:
   *  Constant: '<S25>/Constant6'
   */
  *rty_PDU_flgEfuseT1CmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgReverseRelayCmdDrive' incorporates:
   *  Constant: '<S25>/Constant6'
   */
  *rty_PDU_flgReverseRelayCmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgK9RelayCmdDrive' incorporates:
   *  Constant: '<S25>/Constant3'
   */
  *rty_PDU_flgK9RelayCmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgK10RelayCmdDrive' incorporates:
   *  Constant: '<S25>/Constant4'
   */
  *rty_PDU_flgK10RelayCmdDrive = false;

  /* SignalConversion generated from: '<S25>/PDU_flgEfuseT4CmdDrive' incorporates:
   *  SignalConversion generated from: '<S25>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgEfuseT4CmdDrive = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S25>/PDU_flgPTCRelayCmdDrive' incorporates:
   *  SignalConversion generated from: '<S25>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgPTCRelayCmdDrive = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S25>/PDU_flgBatHeatRelayCmdDrive' incorporates:
   *  SignalConversion generated from: '<S25>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgBatHeatRelayCmdDrive = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S25>/PDU_flgEfuseT2CmdDrive' incorporates:
   *  SignalConversion generated from: '<S25>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgEfuseT2CmdDrive = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S25>/PDU_HCU3MainPosCmd' */
  *rty_PDU_flgMainPosRelayCmdDrive = rtu_PDU_HCU3MainPosCmd;

  /* SignalConversion generated from: '<S25>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdDrive = rtu_PDU_HCU3MainNegCmd;

  /* SignalConversion generated from: '<S25>/PDU_HCU3AttCmd' */
  *rty_PDU_flgAttRelayCmdDrive = rtu_PDU_HCU3AttCmd;

  /* SignalConversion generated from: '<S25>/PDU_HCU3MECUCmd' */
  *rty_PDU_flgMECURelayCmdDrive = rtu_PDU_HCU3MECUCmd;

  /* SignalConversion generated from: '<S25>/PDU_HCU3ACCmd' */
  *rty_PDU_flgACRelayCmdDrive = rtu_PDU_HCU3ACCmd;
}

/* Output and update for function-call system: '<S3>/PDU_CHARGE' */
void PDU_PDU_CHARGE(boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
                    rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd,
                    boolean_T rtu_PDU_HCU3AttCmd, boolean_T rtu_PDU_HCU3PTCCmd,
                    boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
                    boolean_T *rty_PDU_flgMainPosRelayCmdCharg, boolean_T
                    *rty_PDU_flgMainNegRelayCmdCharg, boolean_T
                    *rty_PDU_flgAttRelayCmdCharge, boolean_T
                    *rty_PDU_flgK4RelayCmdCharge, boolean_T
                    *rty_PDU_flgK3RelayCmdCharge, boolean_T
                    *rty_PDU_flgReverseRelayCmdCharg, boolean_T
                    *rty_PDU_flgPTCRelayCmdCharge, boolean_T
                    *rty_PDU_flgBatHeatRelayCmdCharg, boolean_T
                    *rty_PDU_flgMECURelayCmdCharge, boolean_T
                    *rty_PDU_flgACRelayCmdCharge, boolean_T
                    *rty_PDU_flgK9RelayCmdCharge, boolean_T
                    *rty_PDU_flgK10RelayCmdCharge, boolean_T
                    *rty_PDU_flgEfuseT3CmdCharge, boolean_T
                    *rty_PDU_flgEfuseT5CmdCharge, boolean_T
                    *rty_PDU_flgEfuseT1CmdCharge, boolean_T
                    *rty_PDU_flgEfuseT2CmdCharge, boolean_T
                    *rty_PDU_flgEfuseT4CmdCharge)
{
  /* SignalConversion generated from: '<S24>/PDU_flgEfuseT3CmdCharge' incorporates:
   *  Constant: '<S24>/Constant1'
   */
  *rty_PDU_flgEfuseT3CmdCharge = false;

  /* SignalConversion generated from: '<S24>/PDU_flgK4RelayCmdCharge' incorporates:
   *  Constant: '<S24>/Constant1'
   */
  *rty_PDU_flgK4RelayCmdCharge = false;

  /* SignalConversion generated from: '<S24>/PDU_flgEfuseT5CmdCharge' incorporates:
   *  Constant: '<S24>/Constant10'
   */
  *rty_PDU_flgEfuseT5CmdCharge = false;

  /* SignalConversion generated from: '<S24>/PDU_flgK3RelayCmdCharge' incorporates:
   *  Constant: '<S24>/Constant10'
   */
  *rty_PDU_flgK3RelayCmdCharge = false;

  /* SignalConversion generated from: '<S24>/PDU_flgEfuseT1CmdCharge' incorporates:
   *  Constant: '<S24>/Constant6'
   */
  *rty_PDU_flgEfuseT1CmdCharge = false;

  /* SignalConversion generated from: '<S24>/PDU_flgReverseRelayCmdCharge' incorporates:
   *  Constant: '<S24>/Constant6'
   */
  *rty_PDU_flgReverseRelayCmdCharg = false;

  /* SignalConversion generated from: '<S24>/PDU_flgK9RelayCmdCharge' incorporates:
   *  Constant: '<S24>/Constant3'
   */
  *rty_PDU_flgK9RelayCmdCharge = true;

  /* SignalConversion generated from: '<S24>/PDU_flgK10RelayCmdCharge' incorporates:
   *  Constant: '<S24>/Constant4'
   */
  *rty_PDU_flgK10RelayCmdCharge = true;

  /* SignalConversion generated from: '<S24>/PDU_flgEfuseT4CmdCharge' incorporates:
   *  SignalConversion generated from: '<S24>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgEfuseT4CmdCharge = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S24>/PDU_flgPTCRelayCmdCharge' incorporates:
   *  SignalConversion generated from: '<S24>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgPTCRelayCmdCharge = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S24>/PDU_flgBatHeatRelayCmdCharge' incorporates:
   *  SignalConversion generated from: '<S24>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgBatHeatRelayCmdCharg = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S24>/PDU_flgEfuseT2CmdCharge' incorporates:
   *  SignalConversion generated from: '<S24>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgEfuseT2CmdCharge = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S24>/PDU_HCU3MainPosCmd' */
  *rty_PDU_flgMainPosRelayCmdCharg = rtu_PDU_HCU3MainPosCmd;

  /* SignalConversion generated from: '<S24>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdCharg = rtu_PDU_HCU3MainNegCmd;

  /* SignalConversion generated from: '<S24>/PDU_HCU3AttCmd' */
  *rty_PDU_flgAttRelayCmdCharge = rtu_PDU_HCU3AttCmd;

  /* SignalConversion generated from: '<S24>/PDU_HCU3MECUCmd' */
  *rty_PDU_flgMECURelayCmdCharge = rtu_PDU_HCU3MECUCmd;

  /* SignalConversion generated from: '<S24>/PDU_HCU3ACCmd' */
  *rty_PDU_flgACRelayCmdCharge = rtu_PDU_HCU3ACCmd;
}

/* Output and update for function-call system: '<S3>/PDU_SHUTDOWN' */
void PDU_PDU_SHUTDOWN(boolean_T rtu_PDU_flgShutDown, boolean_T
                      rtu_PDU_HCU3MainPosCmd, boolean_T rtu_PDU_HCU3MainNegCmd,
                      boolean_T rtu_PDU_HCU3BatHeatCmd, boolean_T
                      rtu_PDU_HCU3AttCmd, boolean_T rtu_PDU_HCU3PTCCmd,
                      boolean_T rtu_PDU_HCU3MECUCmd, boolean_T rtu_PDU_HCU3ACCmd,
                      boolean_T *rty_PDU_flgMainPosRelayCmdSD, boolean_T
                      *rty_PDU_flgMainNegRelayCmdSD, boolean_T
                      *rty_PDU_flgAttRelayCmdSD, boolean_T
                      *rty_PDU_flgK4RelayCmdSD, boolean_T
                      *rty_PDU_flgK3RelayCmdSD, boolean_T
                      *rty_PDU_flgReverseRelayCmdSD, boolean_T
                      *rty_PDU_flgPTCRelayCmdSD, boolean_T
                      *rty_PDU_flgBatHeatRelayCmdSD, boolean_T
                      *rty_PDU_flgMECURelayCmdSD, boolean_T
                      *rty_PDU_flgACRelayCmdSD, boolean_T
                      *rty_PDU_flgK9RelayCmdSD, boolean_T
                      *rty_PDU_flgK10RelayCmdSD, boolean_T
                      *rty_PDU_flgEfuseT3CmdSD, boolean_T
                      *rty_PDU_flgEfuseT5CmdSD, boolean_T
                      *rty_PDU_flgEfuseT1CmdSD, boolean_T
                      *rty_PDU_flgEfuseT2CmdSD, boolean_T
                      *rty_PDU_flgEfuseT4CmdSD)
{
  boolean_T rtb_Switch3_aa;
  boolean_T rtb_Switch_b;
  boolean_T rtb_Switch_mj_tmp;

  /* Logic: '<S31>/Logical Operator' incorporates:
   *  Logic: '<S31>/Logical Operator11'
   */
  rtb_Switch_mj_tmp = !rtu_PDU_flgShutDown;

  /* Switch: '<S31>/Switch' incorporates:
   *  Logic: '<S31>/Logical Operator'
   *  Logic: '<S31>/Logical Operator12'
   */
  rtb_Switch_b = (rtu_PDU_HCU3AttCmd && rtb_Switch_mj_tmp);

  /* Logic: '<S31>/Logical Operator10' incorporates:
   *  Logic: '<S31>/Logical Operator4'
   *  Logic: '<S31>/Logical Operator6'
   *  Logic: '<S31>/Logical Operator8'
   */
  rtb_Switch_mj_tmp = (rtb_Switch_b || rtb_Switch_mj_tmp);

  /* Switch: '<S31>/Switch5' incorporates:
   *  Logic: '<S31>/Logical Operator10'
   */
  *rty_PDU_flgACRelayCmdSD = (rtb_Switch_mj_tmp && rtu_PDU_HCU3ACCmd);

  /* SignalConversion generated from: '<S31>/PDU_flgEfuseT1CmdSD' */
  *rty_PDU_flgEfuseT1CmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_flgReverseRelayCmdSD' */
  *rty_PDU_flgReverseRelayCmdSD = false;

  /* Switch: '<S31>/Switch2' */
  rtb_Switch3_aa = (rtb_Switch_mj_tmp && rtu_PDU_HCU3PTCCmd);

  /* SignalConversion generated from: '<S31>/PDU_flgEfuseT4CmdSD' */
  *rty_PDU_flgEfuseT4CmdSD = rtb_Switch3_aa;

  /* SignalConversion generated from: '<S31>/PDU_flgPTCRelayCmdSD' */
  *rty_PDU_flgPTCRelayCmdSD = rtb_Switch3_aa;

  /* Switch: '<S31>/Switch3' */
  rtb_Switch3_aa = (rtb_Switch_mj_tmp && rtu_PDU_HCU3BatHeatCmd);

  /* SignalConversion generated from: '<S31>/PDU_flgBatHeatRelayCmdSD' */
  *rty_PDU_flgBatHeatRelayCmdSD = rtb_Switch3_aa;

  /* SignalConversion generated from: '<S31>/PDU_flgEfuseT2CmdSD' */
  *rty_PDU_flgEfuseT2CmdSD = rtb_Switch3_aa;

  /* Switch: '<S31>/Switch4' */
  *rty_PDU_flgMECURelayCmdSD = (rtb_Switch_mj_tmp && rtu_PDU_HCU3MECUCmd);

  /* SignalConversion generated from: '<S31>/PDU_flgAttRelayCmdSD' */
  *rty_PDU_flgAttRelayCmdSD = rtb_Switch_b;

  /* SignalConversion generated from: '<S31>/PDU_flgK4RelayCmdSD' incorporates:
   *  Constant: '<S31>/Constant6'
   */
  *rty_PDU_flgK4RelayCmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_flgK3RelayCmdSD' incorporates:
   *  Constant: '<S31>/Constant11'
   */
  *rty_PDU_flgK3RelayCmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_flgK9RelayCmdSD' incorporates:
   *  Constant: '<S31>/Constant12'
   */
  *rty_PDU_flgK9RelayCmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_flgK10RelayCmdSD' incorporates:
   *  Constant: '<S31>/Constant13'
   */
  *rty_PDU_flgK10RelayCmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_flgEfuseT3CmdSD' incorporates:
   *  Constant: '<S31>/Constant8'
   */
  *rty_PDU_flgEfuseT3CmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_flgEfuseT5CmdSD' incorporates:
   *  Constant: '<S31>/Constant9'
   */
  *rty_PDU_flgEfuseT5CmdSD = false;

  /* SignalConversion generated from: '<S31>/PDU_HCU3MainPosCmd' */
  *rty_PDU_flgMainPosRelayCmdSD = rtu_PDU_HCU3MainPosCmd;

  /* SignalConversion generated from: '<S31>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdSD = rtu_PDU_HCU3MainNegCmd;
}

/* Output and update for function-call system: '<S3>/PDU_ATTON' */
void PDU_PDU_ATTON(boolean_T rtu_PDU_HCU3MainPosCmd, boolean_T
                   rtu_PDU_HCU3MainNegCmd, boolean_T rtu_PDU_HCU3BatHeatCmd,
                   boolean_T rtu_PDU_HCU3PTCCmd, boolean_T rtu_PDU_HCU3MECUCmd,
                   boolean_T rtu_PDU_HCU3ACCmd, boolean_T rtu_PDU_HCU3AttCmd,
                   boolean_T *rty_PDU_flgMainPosRelayCmdON, boolean_T
                   *rty_PDU_flgMainNegRelayCmdON, boolean_T
                   *rty_PDU_flgAttRelayCmdON, boolean_T *rty_PDU_flgK4RelayCmdON,
                   boolean_T *rty_PDU_flgK3RelayCmdON, boolean_T
                   *rty_PDU_flgReverseRelayCmdON, boolean_T
                   *rty_PDU_flgPTCRelayCmdON, boolean_T
                   *rty_PDU_flgBatHeatRelayCmdON, boolean_T
                   *rty_PDU_flgMECURelayCmdON, boolean_T
                   *rty_PDU_flgACRelayCmdON, boolean_T *rty_PDU_flgK9RelayCmdON,
                   boolean_T *rty_PDU_flgK10RelayCmdON, boolean_T
                   *rty_PDU_flgEfuseT3CmdON, boolean_T *rty_PDU_flgEfuseT5CmdON,
                   boolean_T *rty_PDU_flgEfuseT1CmdON, boolean_T
                   *rty_PDU_flgEfuseT2CmdON, boolean_T *rty_PDU_flgEfuseT4CmdON)
{
  /* SignalConversion generated from: '<S22>/PDU_flgEfuseT3CmdON' incorporates:
   *  Constant: '<S22>/Constant1'
   */
  *rty_PDU_flgEfuseT3CmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgK4RelayCmdON' incorporates:
   *  Constant: '<S22>/Constant1'
   */
  *rty_PDU_flgK4RelayCmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgEfuseT5CmdON' incorporates:
   *  Constant: '<S22>/Constant10'
   */
  *rty_PDU_flgEfuseT5CmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgK3RelayCmdON' incorporates:
   *  Constant: '<S22>/Constant10'
   */
  *rty_PDU_flgK3RelayCmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgEfuseT1CmdON' incorporates:
   *  Constant: '<S22>/Constant6'
   */
  *rty_PDU_flgEfuseT1CmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgReverseRelayCmdON' incorporates:
   *  Constant: '<S22>/Constant6'
   */
  *rty_PDU_flgReverseRelayCmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgK9RelayCmdON' incorporates:
   *  Constant: '<S22>/Constant3'
   */
  *rty_PDU_flgK9RelayCmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgK10RelayCmdON' incorporates:
   *  Constant: '<S22>/Constant4'
   */
  *rty_PDU_flgK10RelayCmdON = false;

  /* SignalConversion generated from: '<S22>/PDU_flgEfuseT4CmdON' incorporates:
   *  SignalConversion generated from: '<S22>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgEfuseT4CmdON = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S22>/PDU_flgPTCRelayCmdON' incorporates:
   *  SignalConversion generated from: '<S22>/PDU_HCU3PTCCmd'
   */
  *rty_PDU_flgPTCRelayCmdON = rtu_PDU_HCU3PTCCmd;

  /* SignalConversion generated from: '<S22>/PDU_flgBatHeatRelayCmdON' incorporates:
   *  SignalConversion generated from: '<S22>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgBatHeatRelayCmdON = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S22>/PDU_flgEfuseT2CmdON' incorporates:
   *  SignalConversion generated from: '<S22>/PDU_HCU3BatHeatCmd'
   */
  *rty_PDU_flgEfuseT2CmdON = rtu_PDU_HCU3BatHeatCmd;

  /* SignalConversion generated from: '<S22>/PDU_HCU3MainPosCmd' */
  *rty_PDU_flgMainPosRelayCmdON = rtu_PDU_HCU3MainPosCmd;

  /* SignalConversion generated from: '<S22>/PDU_HCU3MainNegCmd' */
  *rty_PDU_flgMainNegRelayCmdON = rtu_PDU_HCU3MainNegCmd;

  /* SignalConversion generated from: '<S22>/PDU_HCU3AttCmd' */
  *rty_PDU_flgAttRelayCmdON = rtu_PDU_HCU3AttCmd;

  /* SignalConversion generated from: '<S22>/PDU_HCU3MECUCmd' */
  *rty_PDU_flgMECURelayCmdON = rtu_PDU_HCU3MECUCmd;

  /* SignalConversion generated from: '<S22>/PDU_HCU3ACCmd' */
  *rty_PDU_flgACRelayCmdON = rtu_PDU_HCU3ACCmd;
}

/* Model step function */
void PDU_ReMain(void)
{
  real_T rtb_Switch1_d2;
  real_T rtb_Switch1_g;
  real_T rtb_Switch1_h1;
  real_T rtb_Switch1_mx;
  real_T rtb_Switch1_o1;
  real_T rtb_Switch1_of;
  real_T tmp;
  int32_T i;
  real32_T rtb_Switch4_c;
  real32_T rtb_Switch4_f;
  real32_T rtb_Switch4_hs;
  real32_T rtb_Switch4_k;
  real32_T rtb_Switch4_l3;
  real32_T rtb_Switch4_lt;
  real32_T rtb_Switch4_m0;
  real32_T rtb_Switch4_o;
  uint32_T Switch7_tmp;
  uint8_T rtb_Switch_i;
  boolean_T rtb_LogicalOperator13;
  boolean_T rtb_LogicalOperator14;
  boolean_T rtb_LogicalOperator16;
  boolean_T rtb_LogicalOperator22;
  boolean_T rtb_LogicalOperator25;
  boolean_T rtb_LogicalOperator28;
  boolean_T rtb_LogicalOperator2_mu;
  boolean_T rtb_LogicalOperator2_pt;
  boolean_T rtb_LogicalOperator31;
  boolean_T rtb_LogicalOperator34;
  boolean_T rtb_LogicalOperator37;
  boolean_T rtb_LogicalOperator4;
  boolean_T rtb_LogicalOperator6;
  boolean_T rtb_LogicalOperator8;
  boolean_T rtb_LogicalOperator_lz;
  boolean_T rtb_RelationalOperator_a;
  boolean_T rtb_RelationalOperator_b;
  boolean_T rtb_RelationalOperator_d;
  boolean_T rtb_RelationalOperator_ez;
  boolean_T rtb_RelationalOperator_fa;
  boolean_T rtb_RelationalOperator_fe;
  boolean_T rtb_RelationalOperator_g;
  boolean_T rtb_RelationalOperator_iz;
  boolean_T rtb_RelationalOperator_jp;
  boolean_T rtb_RelationalOperator_jw;
  boolean_T rtb_RelationalOperator_l;
  boolean_T rtb_RelationalOperator_p;
  boolean_T rtb_UnitDelay3_bs;
  boolean_T rtb_UnitDelay3_c;
  boolean_T rtb_UnitDelay3_d;
  boolean_T rtb_UnitDelay3_ds;
  boolean_T rtb_UnitDelay3_f2;
  boolean_T rtb_UnitDelay3_i;
  boolean_T rtb_UnitDelay3_j;
  boolean_T rtb_UnitDelay3_jl;
  boolean_T rtb_UnitDelay3_k;
  boolean_T rtb_UnitDelay3_lf;
  boolean_T rtb_UnitDelay3_n;
  boolean_T rtb_UnitDelay3_n4;
  boolean_T rtb_UnitDelay3_nw;
  boolean_T rtb_UnitDelay3_p;

  /* RootInportFunctionCallGenerator generated from: '<Root>/PDU_ReMain' incorporates:
   *  SubSystem: '<Root>/PDU_REMAIN'
   */
  for (i = 0; i < 8; i++) {
    /* Constant: '<S1>/Constant' */
    PDU_HCU3[i] = HCU_3[i];
  }

  /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/PDU_IN'
   */
  /* Switch: '<S6>/Switch6' incorporates:
   *  Constant: '<S6>/Constant12'
   *  Constant: '<S6>/Constant13'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND6'
   */
  if (PDU_OverrideHCU3ACCmd) {
    rtb_Switch_i = PDU_orHCU3ACCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[5] & 3);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion17' incorporates:
   *  Switch: '<S6>/Switch6'
   */
  HCU3ACCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S13>/Delay' */
  if (PDU_DW.icLoad) {
    PDU_DW.Delay_DSTATE = HCU3ACCmdRaw;
  }

  /* End of Delay: '<S13>/Delay' */

  /* Switch: '<S5>/Switch7' */
  PDU_HCU3ACCmd = HCU3ACCmdRaw;

  /* Switch: '<S6>/Switch5' incorporates:
   *  Constant: '<S6>/Constant10'
   *  Constant: '<S6>/Constant11'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND5'
   */
  if (PDU_OverrideHCU3MECUCmd) {
    rtb_Switch_i = PDU_orHCU3MECUCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[4] & 48);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion16' incorporates:
   *  Switch: '<S6>/Switch5'
   */
  HCU3MECUCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S12>/Delay' */
  if (PDU_DW.icLoad_d) {
    PDU_DW.Delay_DSTATE_k = HCU3MECUCmdRaw;
  }

  /* End of Delay: '<S12>/Delay' */

  /* Switch: '<S5>/Switch6' */
  PDU_HCU3MECUCmd = HCU3MECUCmdRaw;

  /* Switch: '<S6>/Switch4' incorporates:
   *  Constant: '<S6>/Constant8'
   *  Constant: '<S6>/Constant9'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND4'
   */
  if (PDU_OverrideHCU3PTCCmd) {
    rtb_Switch_i = PDU_orHCU3PTCCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[4] & 12);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion15' incorporates:
   *  Switch: '<S6>/Switch4'
   */
  HCU3PTCCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S11>/Delay' */
  if (PDU_DW.icLoad_m) {
    PDU_DW.Delay_DSTATE_g = HCU3PTCCmdRaw;
  }

  /* End of Delay: '<S11>/Delay' */

  /* Switch: '<S5>/Switch5' */
  PDU_HCU3PTCCmd = HCU3PTCCmdRaw;

  /* Switch: '<S6>/Switch3' incorporates:
   *  Constant: '<S6>/Constant6'
   *  Constant: '<S6>/Constant7'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND3'
   */
  if (PDU_OverrideHCU3AttCmd) {
    rtb_Switch_i = PDU_orHCU3AttCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[4] & 3);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion14' incorporates:
   *  Switch: '<S6>/Switch3'
   */
  HCU3AttCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S10>/Delay' */
  if (PDU_DW.icLoad_a) {
    PDU_DW.Delay_DSTATE_o = HCU3AttCmdRaw;
  }

  /* End of Delay: '<S10>/Delay' */

  /* Switch: '<S5>/Switch4' */
  PDU_HCU3AttCmd = HCU3AttCmdRaw;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S6>/Constant4'
   *  Constant: '<S6>/Constant5'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND2'
   */
  if (PDU_OverrideHCU3BatHeatCmd) {
    rtb_Switch_i = PDU_orHCU3BatHeatCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[1] & 48);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion13' incorporates:
   *  Switch: '<S6>/Switch2'
   */
  HCU3BatHeatCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S8>/Delay' */
  if (PDU_DW.icLoad_mo) {
    PDU_DW.Delay_DSTATE_c = HCU3BatHeatCmdRaw;
  }

  /* End of Delay: '<S8>/Delay' */

  /* Switch: '<S5>/Switch3' */
  PDU_HCU3BatHeatCmd = HCU3BatHeatCmdRaw;

  /* Switch: '<S6>/Switch1' incorporates:
   *  Constant: '<S6>/Constant2'
   *  Constant: '<S6>/Constant3'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND1'
   */
  if (PDU_OverrideHCU3MainNegCmd) {
    rtb_Switch_i = PDU_orHCU3MainNegCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[0] & 12);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion12' incorporates:
   *  Switch: '<S6>/Switch1'
   */
  HCU3MainNegCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S7>/Delay' */
  if (PDU_DW.icLoad_c) {
    PDU_DW.Delay_DSTATE_d = HCU3MainNegCmdRaw;
  }

  /* End of Delay: '<S7>/Delay' */

  /* Switch: '<S5>/Switch2' */
  PDU_HCU3MainNegCmd = HCU3MainNegCmdRaw;

  /* Switch: '<S6>/Switch' incorporates:
   *  Constant: '<S6>/Constant'
   *  Constant: '<S6>/Constant1'
   *  S-Function (sfix_bitop): '<S6>/Bitwise AND'
   */
  if (PDU_OverrideHCU3MainPosCmd) {
    rtb_Switch_i = PDU_orHCU3MainPosCmd;
  } else {
    rtb_Switch_i = (uint8_T)(PDU_HCU3[0] & 3);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion11' incorporates:
   *  Switch: '<S6>/Switch'
   */
  HCU3MainPosCmdRaw = (rtb_Switch_i != 0);

  /* Delay: '<S9>/Delay' */
  if (PDU_DW.icLoad_nc) {
    PDU_DW.Delay_DSTATE_gd = HCU3MainPosCmdRaw;
  }

  /* End of Delay: '<S9>/Delay' */

  /* Switch: '<S5>/Switch1' */
  PDU_HCU3MainPosCmd = HCU3MainPosCmdRaw;

  /* Update for Delay: '<S13>/Delay' */
  PDU_DW.icLoad = false;

  /* Update for Delay: '<S13>/Delay1' */
  PDU_DW.icLoad_p = false;
  PDU_DW.Delay1_DSTATE = HCU3ACCmdRaw;

  /* Update for UnitDelay: '<S13>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_ds = false;

  /* Update for Delay: '<S12>/Delay' */
  PDU_DW.icLoad_d = false;

  /* Update for Delay: '<S12>/Delay1' */
  PDU_DW.icLoad_l = false;
  PDU_DW.Delay1_DSTATE_b = HCU3MECUCmdRaw;

  /* Update for UnitDelay: '<S12>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_ono = false;

  /* Update for Delay: '<S11>/Delay' */
  PDU_DW.icLoad_m = false;

  /* Update for Delay: '<S11>/Delay1' */
  PDU_DW.icLoad_g = false;
  PDU_DW.Delay1_DSTATE_g = HCU3PTCCmdRaw;

  /* Update for UnitDelay: '<S11>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_b = false;

  /* Update for Delay: '<S10>/Delay' */
  PDU_DW.icLoad_a = false;

  /* Update for Delay: '<S10>/Delay1' */
  PDU_DW.icLoad_f = false;
  PDU_DW.Delay1_DSTATE_m = HCU3AttCmdRaw;

  /* Update for UnitDelay: '<S10>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_cb = false;

  /* Update for Delay: '<S8>/Delay' */
  PDU_DW.icLoad_mo = false;

  /* Update for Delay: '<S8>/Delay1' */
  PDU_DW.icLoad_n = false;
  PDU_DW.Delay1_DSTATE_i = HCU3BatHeatCmdRaw;

  /* Update for UnitDelay: '<S8>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_gd = false;

  /* Update for Delay: '<S7>/Delay' */
  PDU_DW.icLoad_c = false;

  /* Update for Delay: '<S7>/Delay1' */
  PDU_DW.icLoad_gz = false;
  PDU_DW.Delay1_DSTATE_k = HCU3MainNegCmdRaw;

  /* Update for UnitDelay: '<S7>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_bk = false;

  /* Update for Delay: '<S9>/Delay' */
  PDU_DW.icLoad_nc = false;

  /* Update for Delay: '<S9>/Delay1' */
  PDU_DW.icLoad_l3 = false;
  PDU_DW.Delay1_DSTATE_h = HCU3MainPosCmdRaw;

  /* Update for UnitDelay: '<S9>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_je = false;

  /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/PDU_MAIN'
   */
  /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
   *  SubSystem: '<S3>/PDU_FAULTMON'
   */
  /* Logic: '<S27>/Logical Operator14' incorporates:
   *  Constant: '<S27>/Constant23'
   *  Inport: '<Root>/PDU_AttVoltage'
   *  Inport: '<Root>/PDU_BatteryVoltage'
   *  Logic: '<S27>/Logical Operator15'
   *  RelationalOperator: '<S27>/Relational Operator1'
   *  Sum: '<S27>/Add'
   *  UnitDelay: '<S3>/Unit Delay2'
   */
  rtb_LogicalOperator14 = ((!PDU_DW.UnitDelay2_DSTATE_j) && (PDU_BatteryVoltage
    - PDU_AttVoltage >= PDU_AdhesionThresh));

  /* UnitDelay: '<S44>/Unit Delay3' */
  rtb_UnitDelay3_d = PDU_DW.UnitDelay3_DSTATE_b;

  /* Logic: '<S27>/Logical Operator13' */
  rtb_LogicalOperator13 = !rtb_LogicalOperator14;

  /* Outputs for Atomic SubSystem: '<S44>/SR_latch' */
  /* Logic: '<S44>/Logical Operator' incorporates:
   *  Logic: '<S44>/Logical Operator NOT4'
   *  Logic: '<S44>/Logical Operator NOT5'
   *  Logic: '<S44>/Logical Operator2'
   *  UnitDelay: '<S44>/Unit Delay3'
   *  UnitDelay: '<S44>/Unit Delay4'
   *  UnitDelay: '<S44>/Unit Delay5'
   */
  PDU_SR_latch(rtb_LogicalOperator14 && (!PDU_DW.UnitDelay4_DSTATE_m),
               rtb_LogicalOperator13 && (!PDU_DW.UnitDelay5_DSTATE_b),
               &PDU_DW.UnitDelay3_DSTATE_b, &PDU_DW.SR_latch_e);

  /* End of Outputs for SubSystem: '<S44>/SR_latch' */

  /* Switch: '<S44>/Switch1' incorporates:
   *  Constant: '<S44>/Constant1'
   *  Sum: '<S44>/Sum'
   *  Switch: '<S44>/Switch'
   *  UnitDelay: '<S44>/Unit Delay1'
   *  UnitDelay: '<S44>/Unit Delay3'
   */
  if (rtb_LogicalOperator13) {
    rtb_Switch1_mx = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_b) {
      /* Switch: '<S44>/Switch3' incorporates:
       *  Constant: '<S27>/Constant20'
       *  Constant: '<S44>/Constant4'
       *  Constant: '<S44>/Constant6'
       *  Logic: '<S44>/Logical Operator NOT2'
       *  Logic: '<S44>/Logical Operator NOT3'
       *  Logic: '<S44>/Logical Operator1'
       *  RelationalOperator: '<S44>/Relational Operator4'
       *  Switch: '<S44>/Switch'
       *  Switch: '<S44>/Switch5'
       *  UnitDelay: '<S44>/Unit Delay2'
       */
      if (rtb_LogicalOperator14 && (!PDU_DW.UnitDelay2_DSTATE_oa) &&
          (!rtb_UnitDelay3_d)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S44>/Switch5' incorporates:
         *  Constant: '<S27>/Constant20'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S44>/Switch3' */
    } else {
      /* Switch: '<S44>/Switch' incorporates:
       *  Constant: '<S44>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_mx = PDU_DW.UnitDelay1_DSTATE_c + tmp;
  }

  /* End of Switch: '<S44>/Switch1' */

  /* Switch: '<S44>/Switch4' incorporates:
   *  Constant: '<S27>/Constant21'
   *  Constant: '<S44>/Constant3'
   *  RelationalOperator: '<S44>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_m0 = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_m0 = 0.0F;
  }

  /* End of Switch: '<S44>/Switch4' */

  /* RelationalOperator: '<S44>/Relational Operator' */
  rtb_RelationalOperator_ez = (rtb_Switch1_mx < rtb_Switch4_m0);

  /* Switch: '<S44>/Switch2' incorporates:
   *  UnitDelay: '<S44>/Unit Delay1'
   */
  if (rtb_RelationalOperator_ez) {
    PDU_DW.UnitDelay1_DSTATE_c = rtb_Switch1_mx;
  } else {
    PDU_DW.UnitDelay1_DSTATE_c = rtb_Switch4_m0;
  }

  /* End of Switch: '<S44>/Switch2' */

  /* Logic: '<S44>/Logical Operator NOT1' */
  PDU_flgAttAdhesion = !rtb_RelationalOperator_ez;

  /* Logic: '<S27>/Logical Operator17' incorporates:
   *  Constant: '<S27>/Constant26'
   *  Inport: '<Root>/PDU_BatteryVoltage'
   *  Inport: '<Root>/PDU_MainPosVoltage'
   *  Logic: '<S27>/Logical Operator18'
   *  RelationalOperator: '<S27>/Relational Operator2'
   *  Sum: '<S27>/Add1'
   *  UnitDelay: '<S3>/Unit Delay3'
   */
  rtb_UnitDelay3_d = ((!PDU_DW.UnitDelay3_DSTATE_d) && (PDU_MainPosVoltage -
    PDU_BatteryVoltage >= PDU_AdhesionThresh));

  /* Logic: '<S27>/Logical Operator16' */
  rtb_LogicalOperator16 = !rtb_UnitDelay3_d;

  /* UnitDelay: '<S45>/Unit Delay3' */
  rtb_UnitDelay3_c = PDU_DW.UnitDelay3_DSTATE_n;

  /* Outputs for Atomic SubSystem: '<S45>/SR_latch' */
  /* Logic: '<S45>/Logical Operator' incorporates:
   *  Logic: '<S45>/Logical Operator NOT4'
   *  Logic: '<S45>/Logical Operator NOT5'
   *  Logic: '<S45>/Logical Operator2'
   *  UnitDelay: '<S45>/Unit Delay3'
   *  UnitDelay: '<S45>/Unit Delay4'
   *  UnitDelay: '<S45>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_d && (!PDU_DW.UnitDelay4_DSTATE_mw),
               rtb_LogicalOperator16 && (!PDU_DW.UnitDelay5_DSTATE_n),
               &PDU_DW.UnitDelay3_DSTATE_n, &PDU_DW.SR_latch_o);

  /* End of Outputs for SubSystem: '<S45>/SR_latch' */

  /* Switch: '<S45>/Switch1' incorporates:
   *  Constant: '<S45>/Constant1'
   *  Sum: '<S45>/Sum'
   *  Switch: '<S45>/Switch'
   *  UnitDelay: '<S45>/Unit Delay1'
   *  UnitDelay: '<S45>/Unit Delay3'
   */
  if (rtb_LogicalOperator16) {
    rtb_Switch1_mx = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_n) {
      /* Switch: '<S45>/Switch3' incorporates:
       *  Constant: '<S27>/Constant24'
       *  Constant: '<S45>/Constant4'
       *  Constant: '<S45>/Constant6'
       *  Logic: '<S45>/Logical Operator NOT2'
       *  Logic: '<S45>/Logical Operator NOT3'
       *  Logic: '<S45>/Logical Operator1'
       *  RelationalOperator: '<S45>/Relational Operator4'
       *  Switch: '<S45>/Switch'
       *  Switch: '<S45>/Switch5'
       *  UnitDelay: '<S45>/Unit Delay2'
       */
      if (rtb_UnitDelay3_d && (!PDU_DW.UnitDelay2_DSTATE_p) &&
          (!rtb_UnitDelay3_c)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S45>/Switch5' incorporates:
         *  Constant: '<S27>/Constant24'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S45>/Switch3' */
    } else {
      /* Switch: '<S45>/Switch' incorporates:
       *  Constant: '<S45>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_mx = PDU_DW.UnitDelay1_DSTATE_j + tmp;
  }

  /* End of Switch: '<S45>/Switch1' */

  /* Switch: '<S45>/Switch4' incorporates:
   *  Constant: '<S27>/Constant25'
   *  Constant: '<S45>/Constant3'
   *  RelationalOperator: '<S45>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_m0 = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_m0 = 0.0F;
  }

  /* End of Switch: '<S45>/Switch4' */

  /* RelationalOperator: '<S45>/Relational Operator' */
  rtb_RelationalOperator_ez = (rtb_Switch1_mx < rtb_Switch4_m0);

  /* Logic: '<S45>/Logical Operator NOT1' */
  PDU_flgMainPosAdhesion = !rtb_RelationalOperator_ez;

  /* Logic: '<S27>/Logical Operator20' incorporates:
   *  Inport: '<Root>/PDU_flgK5StateRaw'
   *  Logic: '<S27>/Logical Operator21'
   *  UnitDelay: '<S3>/Unit Delay5'
   */
  rtb_UnitDelay3_c = ((!PDU_DW.UnitDelay5_DSTATE) && PDU_flgK5StateRaw);

  /* Logic: '<S27>/Logical Operator22' */
  rtb_LogicalOperator22 = !rtb_UnitDelay3_c;

  /* UnitDelay: '<S46>/Unit Delay3' */
  rtb_UnitDelay3_n4 = PDU_DW.UnitDelay3_DSTATE_bq;

  /* Outputs for Atomic SubSystem: '<S46>/SR_latch' */
  /* Logic: '<S46>/Logical Operator' incorporates:
   *  Logic: '<S46>/Logical Operator NOT4'
   *  Logic: '<S46>/Logical Operator NOT5'
   *  Logic: '<S46>/Logical Operator2'
   *  UnitDelay: '<S46>/Unit Delay3'
   *  UnitDelay: '<S46>/Unit Delay4'
   *  UnitDelay: '<S46>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_c && (!PDU_DW.UnitDelay4_DSTATE_e),
               rtb_LogicalOperator22 && (!PDU_DW.UnitDelay5_DSTATE_e),
               &PDU_DW.UnitDelay3_DSTATE_bq, &PDU_DW.SR_latch_n);

  /* End of Outputs for SubSystem: '<S46>/SR_latch' */

  /* Switch: '<S46>/Switch1' incorporates:
   *  Switch: '<S46>/Switch'
   *  UnitDelay: '<S46>/Unit Delay3'
   */
  if (rtb_LogicalOperator22) {
    /* Switch: '<S46>/Switch1' incorporates:
     *  Constant: '<S46>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_k = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_bq) {
      /* Switch: '<S46>/Switch3' incorporates:
       *  Constant: '<S27>/Constant28'
       *  Constant: '<S46>/Constant4'
       *  Constant: '<S46>/Constant6'
       *  Logic: '<S46>/Logical Operator NOT2'
       *  Logic: '<S46>/Logical Operator NOT3'
       *  Logic: '<S46>/Logical Operator1'
       *  RelationalOperator: '<S46>/Relational Operator4'
       *  Switch: '<S46>/Switch'
       *  Switch: '<S46>/Switch5'
       *  UnitDelay: '<S46>/Unit Delay2'
       */
      if (rtb_UnitDelay3_c && (!PDU_DW.UnitDelay2_DSTATE_g) &&
          (!rtb_UnitDelay3_n4)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S46>/Switch5' incorporates:
         *  Constant: '<S27>/Constant28'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S46>/Switch3' */
    } else {
      /* Switch: '<S46>/Switch' incorporates:
       *  Constant: '<S46>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S46>/Switch1' incorporates:
     *  Sum: '<S46>/Sum'
     *  Switch: '<S46>/Switch'
     *  UnitDelay: '<S46>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_k += tmp;
  }

  /* End of Switch: '<S46>/Switch1' */

  /* Switch: '<S46>/Switch4' incorporates:
   *  Constant: '<S27>/Constant29'
   *  Constant: '<S46>/Constant3'
   *  RelationalOperator: '<S46>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_f = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_f = 0.0F;
  }

  /* End of Switch: '<S46>/Switch4' */

  /* RelationalOperator: '<S46>/Relational Operator' */
  rtb_RelationalOperator_g = (PDU_DW.UnitDelay1_DSTATE_k < rtb_Switch4_f);

  /* Logic: '<S46>/Logical Operator NOT1' */
  PDU_flgK5Adhesion = !rtb_RelationalOperator_g;

  /* Logic: '<S27>/Logical Operator23' incorporates:
   *  Inport: '<Root>/PDU_flgK6StateRaw'
   *  Logic: '<S27>/Logical Operator24'
   *  UnitDelay: '<S3>/Unit Delay6'
   */
  rtb_UnitDelay3_n4 = ((!PDU_DW.UnitDelay6_DSTATE) && PDU_flgK6StateRaw);

  /* Logic: '<S27>/Logical Operator25' */
  rtb_LogicalOperator25 = !rtb_UnitDelay3_n4;

  /* UnitDelay: '<S47>/Unit Delay3' */
  rtb_UnitDelay3_f2 = PDU_DW.UnitDelay3_DSTATE_a;

  /* Outputs for Atomic SubSystem: '<S47>/SR_latch' */
  /* Logic: '<S47>/Logical Operator' incorporates:
   *  Logic: '<S47>/Logical Operator NOT4'
   *  Logic: '<S47>/Logical Operator NOT5'
   *  Logic: '<S47>/Logical Operator2'
   *  UnitDelay: '<S47>/Unit Delay3'
   *  UnitDelay: '<S47>/Unit Delay4'
   *  UnitDelay: '<S47>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_n4 && (!PDU_DW.UnitDelay4_DSTATE_g),
               rtb_LogicalOperator25 && (!PDU_DW.UnitDelay5_DSTATE_a),
               &PDU_DW.UnitDelay3_DSTATE_a, &PDU_DW.SR_latch_eq);

  /* End of Outputs for SubSystem: '<S47>/SR_latch' */

  /* Switch: '<S47>/Switch1' incorporates:
   *  Switch: '<S47>/Switch'
   *  UnitDelay: '<S47>/Unit Delay3'
   */
  if (rtb_LogicalOperator25) {
    /* Switch: '<S47>/Switch1' incorporates:
     *  Constant: '<S47>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_h = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_a) {
      /* Switch: '<S47>/Switch3' incorporates:
       *  Constant: '<S27>/Constant30'
       *  Constant: '<S47>/Constant4'
       *  Constant: '<S47>/Constant6'
       *  Logic: '<S47>/Logical Operator NOT2'
       *  Logic: '<S47>/Logical Operator NOT3'
       *  Logic: '<S47>/Logical Operator1'
       *  RelationalOperator: '<S47>/Relational Operator4'
       *  Switch: '<S47>/Switch'
       *  Switch: '<S47>/Switch5'
       *  UnitDelay: '<S47>/Unit Delay2'
       */
      if (rtb_UnitDelay3_n4 && (!PDU_DW.UnitDelay2_DSTATE_a) &&
          (!rtb_UnitDelay3_f2)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S47>/Switch5' incorporates:
         *  Constant: '<S27>/Constant30'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S47>/Switch3' */
    } else {
      /* Switch: '<S47>/Switch' incorporates:
       *  Constant: '<S47>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S47>/Switch1' incorporates:
     *  Sum: '<S47>/Sum'
     *  Switch: '<S47>/Switch'
     *  UnitDelay: '<S47>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_h += tmp;
  }

  /* End of Switch: '<S47>/Switch1' */

  /* Switch: '<S47>/Switch4' incorporates:
   *  Constant: '<S27>/Constant31'
   *  Constant: '<S47>/Constant3'
   *  RelationalOperator: '<S47>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_hs = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_hs = 0.0F;
  }

  /* End of Switch: '<S47>/Switch4' */

  /* RelationalOperator: '<S47>/Relational Operator' */
  rtb_RelationalOperator_fa = (PDU_DW.UnitDelay1_DSTATE_h < rtb_Switch4_hs);

  /* Logic: '<S47>/Logical Operator NOT1' */
  PDU_flgK6Adhesion = !rtb_RelationalOperator_fa;

  /* Logic: '<S27>/Logical Operator26' incorporates:
   *  Inport: '<Root>/PDU_flgK7StateRaw'
   *  Logic: '<S27>/Logical Operator27'
   *  UnitDelay: '<S3>/Unit Delay7'
   */
  rtb_UnitDelay3_f2 = ((!PDU_DW.UnitDelay7_DSTATE) && PDU_flgK7StateRaw);

  /* Logic: '<S27>/Logical Operator28' */
  rtb_LogicalOperator28 = !rtb_UnitDelay3_f2;

  /* UnitDelay: '<S48>/Unit Delay3' */
  rtb_UnitDelay3_p = PDU_DW.UnitDelay3_DSTATE_l;

  /* Outputs for Atomic SubSystem: '<S48>/SR_latch' */
  /* Logic: '<S48>/Logical Operator' incorporates:
   *  Logic: '<S48>/Logical Operator NOT4'
   *  Logic: '<S48>/Logical Operator NOT5'
   *  Logic: '<S48>/Logical Operator2'
   *  UnitDelay: '<S48>/Unit Delay3'
   *  UnitDelay: '<S48>/Unit Delay4'
   *  UnitDelay: '<S48>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_f2 && (!PDU_DW.UnitDelay4_DSTATE_n),
               rtb_LogicalOperator28 && (!PDU_DW.UnitDelay5_DSTATE_nr),
               &PDU_DW.UnitDelay3_DSTATE_l, &PDU_DW.SR_latch_el);

  /* End of Outputs for SubSystem: '<S48>/SR_latch' */

  /* Switch: '<S48>/Switch1' incorporates:
   *  Switch: '<S48>/Switch'
   *  UnitDelay: '<S48>/Unit Delay3'
   */
  if (rtb_LogicalOperator28) {
    /* Switch: '<S48>/Switch1' incorporates:
     *  Constant: '<S48>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_p = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_l) {
      /* Switch: '<S48>/Switch3' incorporates:
       *  Constant: '<S27>/Constant32'
       *  Constant: '<S48>/Constant4'
       *  Constant: '<S48>/Constant6'
       *  Logic: '<S48>/Logical Operator NOT2'
       *  Logic: '<S48>/Logical Operator NOT3'
       *  Logic: '<S48>/Logical Operator1'
       *  RelationalOperator: '<S48>/Relational Operator4'
       *  Switch: '<S48>/Switch'
       *  Switch: '<S48>/Switch5'
       *  UnitDelay: '<S48>/Unit Delay2'
       */
      if (rtb_UnitDelay3_f2 && (!PDU_DW.UnitDelay2_DSTATE_on) &&
          (!rtb_UnitDelay3_p)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S48>/Switch5' incorporates:
         *  Constant: '<S27>/Constant32'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S48>/Switch3' */
    } else {
      /* Switch: '<S48>/Switch' incorporates:
       *  Constant: '<S48>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S48>/Switch1' incorporates:
     *  Sum: '<S48>/Sum'
     *  Switch: '<S48>/Switch'
     *  UnitDelay: '<S48>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_p += tmp;
  }

  /* End of Switch: '<S48>/Switch1' */

  /* Switch: '<S48>/Switch4' incorporates:
   *  Constant: '<S27>/Constant33'
   *  Constant: '<S48>/Constant3'
   *  RelationalOperator: '<S48>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_c = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_c = 0.0F;
  }

  /* End of Switch: '<S48>/Switch4' */

  /* RelationalOperator: '<S48>/Relational Operator' */
  rtb_RelationalOperator_jw = (PDU_DW.UnitDelay1_DSTATE_p < rtb_Switch4_c);

  /* Logic: '<S48>/Logical Operator NOT1' */
  PDU_flgK7Adhesion = !rtb_RelationalOperator_jw;

  /* Logic: '<S27>/Logical Operator29' incorporates:
   *  Inport: '<Root>/PDU_flgK8StateRaw'
   *  Logic: '<S27>/Logical Operator30'
   *  UnitDelay: '<S3>/Unit Delay8'
   */
  rtb_UnitDelay3_p = ((!PDU_DW.UnitDelay8_DSTATE) && PDU_flgK8StateRaw);

  /* Logic: '<S27>/Logical Operator31' */
  rtb_LogicalOperator31 = !rtb_UnitDelay3_p;

  /* UnitDelay: '<S49>/Unit Delay3' */
  rtb_UnitDelay3_k = PDU_DW.UnitDelay3_DSTATE_en;

  /* Outputs for Atomic SubSystem: '<S49>/SR_latch' */
  /* Logic: '<S49>/Logical Operator' incorporates:
   *  Logic: '<S49>/Logical Operator NOT4'
   *  Logic: '<S49>/Logical Operator NOT5'
   *  Logic: '<S49>/Logical Operator2'
   *  UnitDelay: '<S49>/Unit Delay3'
   *  UnitDelay: '<S49>/Unit Delay4'
   *  UnitDelay: '<S49>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_p && (!PDU_DW.UnitDelay4_DSTATE_c),
               rtb_LogicalOperator31 && (!PDU_DW.UnitDelay5_DSTATE_i),
               &PDU_DW.UnitDelay3_DSTATE_en, &PDU_DW.SR_latch_ny);

  /* End of Outputs for SubSystem: '<S49>/SR_latch' */

  /* Switch: '<S49>/Switch1' incorporates:
   *  Switch: '<S49>/Switch'
   *  UnitDelay: '<S49>/Unit Delay3'
   */
  if (rtb_LogicalOperator31) {
    /* Switch: '<S49>/Switch1' incorporates:
     *  Constant: '<S49>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_e = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_en) {
      /* Switch: '<S49>/Switch3' incorporates:
       *  Constant: '<S27>/Constant34'
       *  Constant: '<S49>/Constant4'
       *  Constant: '<S49>/Constant6'
       *  Logic: '<S49>/Logical Operator NOT2'
       *  Logic: '<S49>/Logical Operator NOT3'
       *  Logic: '<S49>/Logical Operator1'
       *  RelationalOperator: '<S49>/Relational Operator4'
       *  Switch: '<S49>/Switch'
       *  Switch: '<S49>/Switch5'
       *  UnitDelay: '<S49>/Unit Delay2'
       */
      if (rtb_UnitDelay3_p && (!PDU_DW.UnitDelay2_DSTATE_oaz) &&
          (!rtb_UnitDelay3_k)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S49>/Switch5' incorporates:
         *  Constant: '<S27>/Constant34'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S49>/Switch3' */
    } else {
      /* Switch: '<S49>/Switch' incorporates:
       *  Constant: '<S49>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S49>/Switch1' incorporates:
     *  Sum: '<S49>/Sum'
     *  Switch: '<S49>/Switch'
     *  UnitDelay: '<S49>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_e += tmp;
  }

  /* End of Switch: '<S49>/Switch1' */

  /* Switch: '<S49>/Switch4' incorporates:
   *  Constant: '<S27>/Constant35'
   *  Constant: '<S49>/Constant3'
   *  RelationalOperator: '<S49>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_o = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_o = 0.0F;
  }

  /* End of Switch: '<S49>/Switch4' */

  /* RelationalOperator: '<S49>/Relational Operator' */
  rtb_RelationalOperator_d = (PDU_DW.UnitDelay1_DSTATE_e < rtb_Switch4_o);

  /* Logic: '<S49>/Logical Operator NOT1' */
  PDU_flgK8Adhesion = !rtb_RelationalOperator_d;

  /* Logic: '<S27>/Logical Operator32' incorporates:
   *  Inport: '<Root>/PDU_flgK9StateRaw'
   *  Logic: '<S27>/Logical Operator33'
   *  UnitDelay: '<S3>/Unit Delay9'
   */
  rtb_UnitDelay3_k = ((!PDU_DW.UnitDelay9_DSTATE) && PDU_flgK9StateRaw);

  /* Logic: '<S27>/Logical Operator34' */
  rtb_LogicalOperator34 = !rtb_UnitDelay3_k;

  /* UnitDelay: '<S50>/Unit Delay3' */
  rtb_UnitDelay3_bs = PDU_DW.UnitDelay3_DSTATE_h;

  /* Outputs for Atomic SubSystem: '<S50>/SR_latch' */
  /* Logic: '<S50>/Logical Operator' incorporates:
   *  Logic: '<S50>/Logical Operator NOT4'
   *  Logic: '<S50>/Logical Operator NOT5'
   *  Logic: '<S50>/Logical Operator2'
   *  UnitDelay: '<S50>/Unit Delay3'
   *  UnitDelay: '<S50>/Unit Delay4'
   *  UnitDelay: '<S50>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_k && (!PDU_DW.UnitDelay4_DSTATE_cs),
               rtb_LogicalOperator34 && (!PDU_DW.UnitDelay5_DSTATE_i1),
               &PDU_DW.UnitDelay3_DSTATE_h, &PDU_DW.SR_latch_e0);

  /* End of Outputs for SubSystem: '<S50>/SR_latch' */

  /* Switch: '<S50>/Switch1' incorporates:
   *  Switch: '<S50>/Switch'
   *  UnitDelay: '<S50>/Unit Delay3'
   */
  if (rtb_LogicalOperator34) {
    /* Switch: '<S50>/Switch1' incorporates:
     *  Constant: '<S50>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_i = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_h) {
      /* Switch: '<S50>/Switch3' incorporates:
       *  Constant: '<S27>/Constant36'
       *  Constant: '<S50>/Constant4'
       *  Constant: '<S50>/Constant6'
       *  Logic: '<S50>/Logical Operator NOT2'
       *  Logic: '<S50>/Logical Operator NOT3'
       *  Logic: '<S50>/Logical Operator1'
       *  RelationalOperator: '<S50>/Relational Operator4'
       *  Switch: '<S50>/Switch'
       *  Switch: '<S50>/Switch5'
       *  UnitDelay: '<S50>/Unit Delay2'
       */
      if (rtb_UnitDelay3_k && (!PDU_DW.UnitDelay2_DSTATE_f) &&
          (!rtb_UnitDelay3_bs)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S50>/Switch5' incorporates:
         *  Constant: '<S27>/Constant36'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S50>/Switch3' */
    } else {
      /* Switch: '<S50>/Switch' incorporates:
       *  Constant: '<S50>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S50>/Switch1' incorporates:
     *  Sum: '<S50>/Sum'
     *  Switch: '<S50>/Switch'
     *  UnitDelay: '<S50>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_i += tmp;
  }

  /* End of Switch: '<S50>/Switch1' */

  /* Switch: '<S50>/Switch4' incorporates:
   *  Constant: '<S27>/Constant37'
   *  Constant: '<S50>/Constant3'
   *  RelationalOperator: '<S50>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_lt = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_lt = 0.0F;
  }

  /* End of Switch: '<S50>/Switch4' */

  /* RelationalOperator: '<S50>/Relational Operator' */
  rtb_RelationalOperator_a = (PDU_DW.UnitDelay1_DSTATE_i < rtb_Switch4_lt);

  /* Logic: '<S50>/Logical Operator NOT1' */
  PDU_flgK9Adhesion = !rtb_RelationalOperator_a;

  /* Logic: '<S27>/Logical Operator35' incorporates:
   *  Inport: '<Root>/PDU_flgK12StateRaw'
   *  Logic: '<S27>/Logical Operator36'
   *  UnitDelay: '<S3>/Unit Delay10'
   */
  rtb_UnitDelay3_bs = ((!PDU_DW.UnitDelay10_DSTATE) && PDU_flgK12StateRaw);

  /* Logic: '<S27>/Logical Operator37' */
  rtb_LogicalOperator37 = !rtb_UnitDelay3_bs;

  /* UnitDelay: '<S51>/Unit Delay3' */
  rtb_UnitDelay3_n = PDU_DW.UnitDelay3_DSTATE_bqz;

  /* Outputs for Atomic SubSystem: '<S51>/SR_latch' */
  /* Logic: '<S51>/Logical Operator' incorporates:
   *  Logic: '<S51>/Logical Operator NOT4'
   *  Logic: '<S51>/Logical Operator NOT5'
   *  Logic: '<S51>/Logical Operator2'
   *  UnitDelay: '<S51>/Unit Delay3'
   *  UnitDelay: '<S51>/Unit Delay4'
   *  UnitDelay: '<S51>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_bs && (!PDU_DW.UnitDelay4_DSTATE_o),
               rtb_LogicalOperator37 && (!PDU_DW.UnitDelay5_DSTATE_o),
               &PDU_DW.UnitDelay3_DSTATE_bqz, &PDU_DW.SR_latch_f);

  /* End of Outputs for SubSystem: '<S51>/SR_latch' */

  /* Switch: '<S51>/Switch1' incorporates:
   *  Switch: '<S51>/Switch'
   *  UnitDelay: '<S51>/Unit Delay3'
   */
  if (rtb_LogicalOperator37) {
    /* Switch: '<S51>/Switch1' incorporates:
     *  Constant: '<S51>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_l = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_bqz) {
      /* Switch: '<S51>/Switch3' incorporates:
       *  Constant: '<S27>/Constant38'
       *  Constant: '<S51>/Constant4'
       *  Constant: '<S51>/Constant6'
       *  Logic: '<S51>/Logical Operator NOT2'
       *  Logic: '<S51>/Logical Operator NOT3'
       *  Logic: '<S51>/Logical Operator1'
       *  RelationalOperator: '<S51>/Relational Operator4'
       *  Switch: '<S51>/Switch'
       *  Switch: '<S51>/Switch5'
       *  UnitDelay: '<S51>/Unit Delay2'
       */
      if (rtb_UnitDelay3_bs && (!PDU_DW.UnitDelay2_DSTATE_aw) &&
          (!rtb_UnitDelay3_n)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S51>/Switch5' incorporates:
         *  Constant: '<S27>/Constant38'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S51>/Switch3' */
    } else {
      /* Switch: '<S51>/Switch' incorporates:
       *  Constant: '<S51>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S51>/Switch1' incorporates:
     *  Sum: '<S51>/Sum'
     *  Switch: '<S51>/Switch'
     *  UnitDelay: '<S51>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_l += tmp;
  }

  /* End of Switch: '<S51>/Switch1' */

  /* Switch: '<S51>/Switch4' incorporates:
   *  Constant: '<S27>/Constant39'
   *  Constant: '<S51>/Constant3'
   *  RelationalOperator: '<S51>/Relational Operator3'
   */
  if (PDU_AdhesionTimeThresh > 0.0F) {
    rtb_Switch4_k = (real32_T)PDU_AdhesionTimeThresh;
  } else {
    rtb_Switch4_k = 0.0F;
  }

  /* End of Switch: '<S51>/Switch4' */

  /* RelationalOperator: '<S51>/Relational Operator' */
  rtb_RelationalOperator_l = (PDU_DW.UnitDelay1_DSTATE_l < rtb_Switch4_k);

  /* Logic: '<S51>/Logical Operator NOT1' */
  PDU_flgK12Adhesion = !rtb_RelationalOperator_l;

  /* Logic: '<S27>/Logical Operator' */
  PDU_flgRelayAdhesion = (PDU_flgAttAdhesion || PDU_flgMainPosAdhesion ||
    PDU_flgK5Adhesion || PDU_flgK6Adhesion || PDU_flgK7Adhesion ||
    PDU_flgK8Adhesion || PDU_flgK9Adhesion || PDU_flgK12Adhesion);

  /* RelationalOperator: '<S52>/Relational Operator' incorporates:
   *  Constant: '<S52>/Constant'
   *  Inport: '<Root>/PDU_EfuseT3Current'
   */
  rtb_UnitDelay3_n = (PDU_EfuseT3Current >= PDU_ConOverCurrent);

  /* Logic: '<S52>/Logical Operator' */
  rtb_LogicalOperator_lz = !rtb_UnitDelay3_n;

  /* UnitDelay: '<S71>/Unit Delay3' */
  rtb_UnitDelay3_lf = PDU_DW.UnitDelay3_DSTATE_g;

  /* Outputs for Atomic SubSystem: '<S71>/SR_latch' */
  /* Logic: '<S71>/Logical Operator' incorporates:
   *  Logic: '<S71>/Logical Operator NOT4'
   *  Logic: '<S71>/Logical Operator NOT5'
   *  Logic: '<S71>/Logical Operator2'
   *  UnitDelay: '<S71>/Unit Delay3'
   *  UnitDelay: '<S71>/Unit Delay4'
   *  UnitDelay: '<S71>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_n && (!PDU_DW.UnitDelay4_DSTATE_et),
               rtb_LogicalOperator_lz && (!PDU_DW.UnitDelay5_DSTATE_c),
               &PDU_DW.UnitDelay3_DSTATE_g, &PDU_DW.SR_latch_ne);

  /* End of Outputs for SubSystem: '<S71>/SR_latch' */

  /* Switch: '<S71>/Switch1' incorporates:
   *  Constant: '<S71>/Constant1'
   *  Sum: '<S71>/Sum'
   *  Switch: '<S71>/Switch'
   *  UnitDelay: '<S71>/Unit Delay1'
   *  UnitDelay: '<S71>/Unit Delay3'
   */
  if (rtb_LogicalOperator_lz) {
    rtb_Switch1_h1 = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_g) {
      /* Switch: '<S71>/Switch3' incorporates:
       *  Constant: '<S52>/Constant1'
       *  Constant: '<S71>/Constant4'
       *  Constant: '<S71>/Constant6'
       *  Logic: '<S71>/Logical Operator NOT2'
       *  Logic: '<S71>/Logical Operator NOT3'
       *  Logic: '<S71>/Logical Operator1'
       *  RelationalOperator: '<S71>/Relational Operator4'
       *  Switch: '<S71>/Switch'
       *  Switch: '<S71>/Switch5'
       *  UnitDelay: '<S71>/Unit Delay2'
       */
      if (rtb_UnitDelay3_n && (!PDU_DW.UnitDelay2_DSTATE_d) &&
          (!rtb_UnitDelay3_lf)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S71>/Switch5' incorporates:
         *  Constant: '<S52>/Constant1'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S71>/Switch3' */
    } else {
      /* Switch: '<S71>/Switch' incorporates:
       *  Constant: '<S71>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_h1 = PDU_DW.UnitDelay1_DSTATE_i1 + tmp;
  }

  /* End of Switch: '<S71>/Switch1' */

  /* Switch: '<S71>/Switch4' incorporates:
   *  Constant: '<S52>/Constant2'
   *  RelationalOperator: '<S71>/Relational Operator3'
   */
  if (PDU_ConOverCutTime > 0.0) {
    /* Switch: '<S71>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_i1 = PDU_ConOverCutTime;
  } else {
    /* Switch: '<S71>/Switch4' incorporates:
     *  Constant: '<S71>/Constant3'
     */
    PDU_DW.UnitDelay1_DSTATE_i1 = 0.0;
  }

  /* End of Switch: '<S71>/Switch4' */

  /* RelationalOperator: '<S71>/Relational Operator' */
  rtb_RelationalOperator_p = (rtb_Switch1_h1 < PDU_DW.UnitDelay1_DSTATE_i1);

  /* Logic: '<S71>/Logical Operator NOT1' */
  PDU_flgEfuseT3ConOverCut = !rtb_RelationalOperator_p;

  /* Logic: '<S52>/Logical Operator1' incorporates:
   *  Constant: '<S52>/Constant3'
   *  Constant: '<S52>/Constant4'
   *  Inport: '<Root>/PDU_EfuseT3Current'
   *  RelationalOperator: '<S52>/Relational Operator1'
   *  RelationalOperator: '<S52>/Relational Operator2'
   *  UnitDelay: '<S52>/Unit Delay'
   */
  PDU_flgEfuseT3InsOverCut = ((PDU_EfuseT3Current >= PDU_InstantOverCurrent) &&
    (PDU_DW.UnitDelay_DSTATE < PDU_InstantOverCurrent));

  /* RelationalOperator: '<S52>/Relational Operator3' incorporates:
   *  Constant: '<S52>/Constant5'
   *  Inport: '<Root>/PDU_EfuseT5Current'
   */
  rtb_UnitDelay3_lf = (PDU_EfuseT5Current >= PDU_ConOverCurrent);

  /* Logic: '<S52>/Logical Operator2' */
  rtb_LogicalOperator2_mu = !rtb_UnitDelay3_lf;

  /* UnitDelay: '<S72>/Unit Delay3' */
  rtb_UnitDelay3_i = PDU_DW.UnitDelay3_DSTATE_do;

  /* Outputs for Atomic SubSystem: '<S72>/SR_latch' */
  /* Logic: '<S72>/Logical Operator' incorporates:
   *  Logic: '<S72>/Logical Operator NOT4'
   *  Logic: '<S72>/Logical Operator NOT5'
   *  Logic: '<S72>/Logical Operator2'
   *  UnitDelay: '<S72>/Unit Delay3'
   *  UnitDelay: '<S72>/Unit Delay4'
   *  UnitDelay: '<S72>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_lf && (!PDU_DW.UnitDelay4_DSTATE_cm),
               rtb_LogicalOperator2_mu && (!PDU_DW.UnitDelay5_DSTATE_h),
               &PDU_DW.UnitDelay3_DSTATE_do, &PDU_DW.SR_latch_h);

  /* End of Outputs for SubSystem: '<S72>/SR_latch' */

  /* Switch: '<S72>/Switch1' incorporates:
   *  Constant: '<S72>/Constant1'
   *  Sum: '<S72>/Sum'
   *  Switch: '<S72>/Switch'
   *  UnitDelay: '<S72>/Unit Delay1'
   *  UnitDelay: '<S72>/Unit Delay3'
   */
  if (rtb_LogicalOperator2_mu) {
    rtb_Switch1_o1 = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_do) {
      /* Switch: '<S72>/Switch3' incorporates:
       *  Constant: '<S52>/Constant6'
       *  Constant: '<S72>/Constant4'
       *  Constant: '<S72>/Constant6'
       *  Logic: '<S72>/Logical Operator NOT2'
       *  Logic: '<S72>/Logical Operator NOT3'
       *  Logic: '<S72>/Logical Operator1'
       *  RelationalOperator: '<S72>/Relational Operator4'
       *  Switch: '<S72>/Switch'
       *  Switch: '<S72>/Switch5'
       *  UnitDelay: '<S72>/Unit Delay2'
       */
      if (rtb_UnitDelay3_lf && (!PDU_DW.UnitDelay2_DSTATE_fq) &&
          (!rtb_UnitDelay3_i)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S72>/Switch5' incorporates:
         *  Constant: '<S52>/Constant6'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S72>/Switch3' */
    } else {
      /* Switch: '<S72>/Switch' incorporates:
       *  Constant: '<S72>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_o1 = PDU_DW.UnitDelay1_DSTATE_o + tmp;
  }

  /* End of Switch: '<S72>/Switch1' */

  /* Switch: '<S72>/Switch4' incorporates:
   *  Constant: '<S52>/Constant7'
   *  RelationalOperator: '<S72>/Relational Operator3'
   */
  if (PDU_ConOverCutTime > 0.0) {
    /* Switch: '<S72>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_o = PDU_ConOverCutTime;
  } else {
    /* Switch: '<S72>/Switch4' incorporates:
     *  Constant: '<S72>/Constant3'
     */
    PDU_DW.UnitDelay1_DSTATE_o = 0.0;
  }

  /* End of Switch: '<S72>/Switch4' */

  /* RelationalOperator: '<S72>/Relational Operator' */
  rtb_RelationalOperator_jp = (rtb_Switch1_o1 < PDU_DW.UnitDelay1_DSTATE_o);

  /* Logic: '<S72>/Logical Operator NOT1' */
  PDU_flgEfuseT5ConOverCut = !rtb_RelationalOperator_jp;

  /* Logic: '<S52>/Logical Operator3' incorporates:
   *  Constant: '<S52>/Constant8'
   *  Constant: '<S52>/Constant9'
   *  Inport: '<Root>/PDU_EfuseT5Current'
   *  RelationalOperator: '<S52>/Relational Operator4'
   *  RelationalOperator: '<S52>/Relational Operator5'
   *  UnitDelay: '<S52>/Unit Delay1'
   */
  PDU_flgEfuseT5InsOverCut = ((PDU_EfuseT5Current >= PDU_InstantOverCurrent) &&
    (PDU_DW.UnitDelay1_DSTATE_lr < PDU_InstantOverCurrent));

  /* RelationalOperator: '<S52>/Relational Operator6' incorporates:
   *  Constant: '<S52>/Constant10'
   *  Inport: '<Root>/PDU_EfuseT1Current'
   */
  rtb_UnitDelay3_i = (PDU_EfuseT1Current >= PDU_ConOverCurrent);

  /* Logic: '<S52>/Logical Operator4' */
  rtb_LogicalOperator4 = !rtb_UnitDelay3_i;

  /* UnitDelay: '<S73>/Unit Delay3' */
  rtb_UnitDelay3_jl = PDU_DW.UnitDelay3_DSTATE_li;

  /* Outputs for Atomic SubSystem: '<S73>/SR_latch' */
  /* Logic: '<S73>/Logical Operator' incorporates:
   *  Logic: '<S73>/Logical Operator NOT4'
   *  Logic: '<S73>/Logical Operator NOT5'
   *  Logic: '<S73>/Logical Operator2'
   *  UnitDelay: '<S73>/Unit Delay3'
   *  UnitDelay: '<S73>/Unit Delay4'
   *  UnitDelay: '<S73>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_i && (!PDU_DW.UnitDelay4_DSTATE_b),
               rtb_LogicalOperator4 && (!PDU_DW.UnitDelay5_DSTATE_m),
               &PDU_DW.UnitDelay3_DSTATE_li, &PDU_DW.SR_latch_m);

  /* End of Outputs for SubSystem: '<S73>/SR_latch' */

  /* Switch: '<S73>/Switch1' incorporates:
   *  Constant: '<S73>/Constant1'
   *  Sum: '<S73>/Sum'
   *  Switch: '<S73>/Switch'
   *  UnitDelay: '<S73>/Unit Delay1'
   *  UnitDelay: '<S73>/Unit Delay3'
   */
  if (rtb_LogicalOperator4) {
    rtb_Switch1_g = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_li) {
      /* Switch: '<S73>/Switch3' incorporates:
       *  Constant: '<S52>/Constant11'
       *  Constant: '<S73>/Constant4'
       *  Constant: '<S73>/Constant6'
       *  Logic: '<S73>/Logical Operator NOT2'
       *  Logic: '<S73>/Logical Operator NOT3'
       *  Logic: '<S73>/Logical Operator1'
       *  RelationalOperator: '<S73>/Relational Operator4'
       *  Switch: '<S73>/Switch'
       *  Switch: '<S73>/Switch5'
       *  UnitDelay: '<S73>/Unit Delay2'
       */
      if (rtb_UnitDelay3_i && (!PDU_DW.UnitDelay2_DSTATE_i) &&
          (!rtb_UnitDelay3_jl)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S73>/Switch5' incorporates:
         *  Constant: '<S52>/Constant11'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S73>/Switch3' */
    } else {
      /* Switch: '<S73>/Switch' incorporates:
       *  Constant: '<S73>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_g = PDU_DW.UnitDelay1_DSTATE_oy + tmp;
  }

  /* End of Switch: '<S73>/Switch1' */

  /* Switch: '<S73>/Switch4' incorporates:
   *  Constant: '<S52>/Constant12'
   *  RelationalOperator: '<S73>/Relational Operator3'
   */
  if (PDU_ConOverCutTime > 0.0) {
    /* Switch: '<S73>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_oy = PDU_ConOverCutTime;
  } else {
    /* Switch: '<S73>/Switch4' incorporates:
     *  Constant: '<S73>/Constant3'
     */
    PDU_DW.UnitDelay1_DSTATE_oy = 0.0;
  }

  /* End of Switch: '<S73>/Switch4' */

  /* RelationalOperator: '<S73>/Relational Operator' */
  rtb_RelationalOperator_fe = (rtb_Switch1_g < PDU_DW.UnitDelay1_DSTATE_oy);

  /* Logic: '<S73>/Logical Operator NOT1' */
  PDU_flgEfuseT1ConOverCut = !rtb_RelationalOperator_fe;

  /* Logic: '<S52>/Logical Operator5' incorporates:
   *  Constant: '<S52>/Constant13'
   *  Constant: '<S52>/Constant14'
   *  Inport: '<Root>/PDU_EfuseT1Current'
   *  RelationalOperator: '<S52>/Relational Operator7'
   *  RelationalOperator: '<S52>/Relational Operator8'
   *  UnitDelay: '<S52>/Unit Delay2'
   */
  PDU_flgEfuseT1InsOverCut = ((PDU_EfuseT1Current >= PDU_InstantOverCurrent) &&
    (PDU_DW.UnitDelay2_DSTATE < PDU_InstantOverCurrent));

  /* RelationalOperator: '<S52>/Relational Operator9' incorporates:
   *  Constant: '<S52>/Constant15'
   *  Inport: '<Root>/PDU_EfuseT2Current'
   */
  rtb_UnitDelay3_jl = (PDU_EfuseT2Current >= PDU_ConOverCurrent);

  /* Logic: '<S52>/Logical Operator6' */
  rtb_LogicalOperator6 = !rtb_UnitDelay3_jl;

  /* UnitDelay: '<S74>/Unit Delay3' */
  rtb_UnitDelay3_nw = PDU_DW.UnitDelay3_DSTATE_dd;

  /* Outputs for Atomic SubSystem: '<S74>/SR_latch' */
  /* Logic: '<S74>/Logical Operator' incorporates:
   *  Logic: '<S74>/Logical Operator NOT4'
   *  Logic: '<S74>/Logical Operator NOT5'
   *  Logic: '<S74>/Logical Operator2'
   *  UnitDelay: '<S74>/Unit Delay3'
   *  UnitDelay: '<S74>/Unit Delay4'
   *  UnitDelay: '<S74>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_jl && (!PDU_DW.UnitDelay4_DSTATE_p),
               rtb_LogicalOperator6 && (!PDU_DW.UnitDelay5_DSTATE_f),
               &PDU_DW.UnitDelay3_DSTATE_dd, &PDU_DW.SR_latch_d);

  /* End of Outputs for SubSystem: '<S74>/SR_latch' */

  /* Switch: '<S74>/Switch1' incorporates:
   *  Constant: '<S74>/Constant1'
   *  Sum: '<S74>/Sum'
   *  Switch: '<S74>/Switch'
   *  UnitDelay: '<S74>/Unit Delay1'
   *  UnitDelay: '<S74>/Unit Delay3'
   */
  if (rtb_LogicalOperator6) {
    rtb_Switch1_of = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_dd) {
      /* Switch: '<S74>/Switch3' incorporates:
       *  Constant: '<S52>/Constant16'
       *  Constant: '<S74>/Constant4'
       *  Constant: '<S74>/Constant6'
       *  Logic: '<S74>/Logical Operator NOT2'
       *  Logic: '<S74>/Logical Operator NOT3'
       *  Logic: '<S74>/Logical Operator1'
       *  RelationalOperator: '<S74>/Relational Operator4'
       *  Switch: '<S74>/Switch'
       *  Switch: '<S74>/Switch5'
       *  UnitDelay: '<S74>/Unit Delay2'
       */
      if (rtb_UnitDelay3_jl && (!PDU_DW.UnitDelay2_DSTATE_c) &&
          (!rtb_UnitDelay3_nw)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S74>/Switch5' incorporates:
         *  Constant: '<S52>/Constant16'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S74>/Switch3' */
    } else {
      /* Switch: '<S74>/Switch' incorporates:
       *  Constant: '<S74>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_of = PDU_DW.UnitDelay1_DSTATE_a + tmp;
  }

  /* End of Switch: '<S74>/Switch1' */

  /* Switch: '<S74>/Switch4' incorporates:
   *  Constant: '<S52>/Constant17'
   *  RelationalOperator: '<S74>/Relational Operator3'
   */
  if (PDU_ConOverCutTime > 0.0) {
    /* Switch: '<S74>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_a = PDU_ConOverCutTime;
  } else {
    /* Switch: '<S74>/Switch4' incorporates:
     *  Constant: '<S74>/Constant3'
     */
    PDU_DW.UnitDelay1_DSTATE_a = 0.0;
  }

  /* End of Switch: '<S74>/Switch4' */

  /* RelationalOperator: '<S74>/Relational Operator' */
  rtb_RelationalOperator_iz = (rtb_Switch1_of < PDU_DW.UnitDelay1_DSTATE_a);

  /* Logic: '<S74>/Logical Operator NOT1' */
  PDU_flgEfuseT2ConOverCut = !rtb_RelationalOperator_iz;

  /* Logic: '<S52>/Logical Operator7' incorporates:
   *  Constant: '<S52>/Constant18'
   *  Constant: '<S52>/Constant19'
   *  Inport: '<Root>/PDU_EfuseT2Current'
   *  RelationalOperator: '<S52>/Relational Operator10'
   *  RelationalOperator: '<S52>/Relational Operator11'
   *  UnitDelay: '<S52>/Unit Delay3'
   */
  PDU_flgEfuseT2InsOverCut = ((PDU_EfuseT2Current >= PDU_InstantOverCurrent) &&
    (PDU_DW.UnitDelay3_DSTATE < PDU_InstantOverCurrent));

  /* RelationalOperator: '<S52>/Relational Operator12' incorporates:
   *  Constant: '<S52>/Constant20'
   *  Inport: '<Root>/PDU_EfuseT4Current'
   */
  rtb_UnitDelay3_nw = (PDU_EfuseT4Current >= PDU_ConOverCurrent);

  /* Logic: '<S52>/Logical Operator8' */
  rtb_LogicalOperator8 = !rtb_UnitDelay3_nw;

  /* UnitDelay: '<S75>/Unit Delay3' */
  rtb_UnitDelay3_j = PDU_DW.UnitDelay3_DSTATE_hu;

  /* Outputs for Atomic SubSystem: '<S75>/SR_latch' */
  /* Logic: '<S75>/Logical Operator' incorporates:
   *  Logic: '<S75>/Logical Operator NOT4'
   *  Logic: '<S75>/Logical Operator NOT5'
   *  Logic: '<S75>/Logical Operator2'
   *  UnitDelay: '<S75>/Unit Delay3'
   *  UnitDelay: '<S75>/Unit Delay4'
   *  UnitDelay: '<S75>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_nw && (!PDU_DW.UnitDelay4_DSTATE_pw),
               rtb_LogicalOperator8 && (!PDU_DW.UnitDelay5_DSTATE_ch),
               &PDU_DW.UnitDelay3_DSTATE_hu, &PDU_DW.SR_latch_l);

  /* End of Outputs for SubSystem: '<S75>/SR_latch' */

  /* Switch: '<S75>/Switch1' incorporates:
   *  Constant: '<S75>/Constant1'
   *  Sum: '<S75>/Sum'
   *  Switch: '<S75>/Switch'
   *  UnitDelay: '<S75>/Unit Delay1'
   *  UnitDelay: '<S75>/Unit Delay3'
   */
  if (rtb_LogicalOperator8) {
    rtb_Switch1_d2 = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_hu) {
      /* Switch: '<S75>/Switch3' incorporates:
       *  Constant: '<S52>/Constant21'
       *  Constant: '<S75>/Constant4'
       *  Constant: '<S75>/Constant6'
       *  Logic: '<S75>/Logical Operator NOT2'
       *  Logic: '<S75>/Logical Operator NOT3'
       *  Logic: '<S75>/Logical Operator1'
       *  RelationalOperator: '<S75>/Relational Operator4'
       *  Switch: '<S75>/Switch'
       *  Switch: '<S75>/Switch5'
       *  UnitDelay: '<S75>/Unit Delay2'
       */
      if (rtb_UnitDelay3_nw && (!PDU_DW.UnitDelay2_DSTATE_jy) &&
          (!rtb_UnitDelay3_j)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S75>/Switch5' incorporates:
         *  Constant: '<S52>/Constant21'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S75>/Switch3' */
    } else {
      /* Switch: '<S75>/Switch' incorporates:
       *  Constant: '<S75>/Constant2'
       */
      tmp = 0.0;
    }

    rtb_Switch1_d2 = PDU_DW.UnitDelay1_DSTATE_n + tmp;
  }

  /* End of Switch: '<S75>/Switch1' */

  /* Switch: '<S75>/Switch4' incorporates:
   *  Constant: '<S52>/Constant22'
   *  RelationalOperator: '<S75>/Relational Operator3'
   */
  if (PDU_ConOverCutTime > 0.0) {
    /* Switch: '<S75>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_n = PDU_ConOverCutTime;
  } else {
    /* Switch: '<S75>/Switch4' incorporates:
     *  Constant: '<S75>/Constant3'
     */
    PDU_DW.UnitDelay1_DSTATE_n = 0.0;
  }

  /* End of Switch: '<S75>/Switch4' */

  /* RelationalOperator: '<S75>/Relational Operator' */
  rtb_RelationalOperator_b = (rtb_Switch1_d2 < PDU_DW.UnitDelay1_DSTATE_n);

  /* Logic: '<S75>/Logical Operator NOT1' */
  PDU_flgEfuseT4ConOverCut = !rtb_RelationalOperator_b;

  /* Logic: '<S52>/Logical Operator9' incorporates:
   *  Constant: '<S52>/Constant23'
   *  Constant: '<S52>/Constant24'
   *  Inport: '<Root>/PDU_EfuseT4Current'
   *  RelationalOperator: '<S52>/Relational Operator13'
   *  RelationalOperator: '<S52>/Relational Operator14'
   *  UnitDelay: '<S52>/Unit Delay4'
   */
  PDU_flgEfuseT4InsOverCut = ((PDU_EfuseT4Current >= PDU_InstantOverCurrent) &&
    (PDU_DW.UnitDelay4_DSTATE < PDU_InstantOverCurrent));

  /* Logic: '<S52>/Logical Operator10' */
  PDU_flgEfuseOverCut = (PDU_flgEfuseT1ConOverCut || PDU_flgEfuseT1InsOverCut ||
    PDU_flgEfuseT2ConOverCut || PDU_flgEfuseT2InsOverCut ||
    PDU_flgEfuseT4ConOverCut || PDU_flgEfuseT4InsOverCut ||
    PDU_flgEfuseT3ConOverCut || PDU_flgEfuseT3InsOverCut ||
    PDU_flgEfuseT5ConOverCut || PDU_flgEfuseT5InsOverCut);

  /* Logic: '<S27>/Logical Operator3' incorporates:
   *  Inport: '<Root>/PDU_EfuseT3CutFaultRead'
   */
  PDU_EfuseT3CutFault = !PDU_EfuseT3CutFaultRead;

  /* Logic: '<S27>/Logical Operator4' incorporates:
   *  Inport: '<Root>/PDU_EfuseT5CutFaultRead'
   */
  PDU_EfuseT5CutFault = !PDU_EfuseT5CutFaultRead;

  /* Logic: '<S27>/Logical Operator5' incorporates:
   *  Inport: '<Root>/PDU_EfuseT1CutFaultRead'
   */
  PDU_EfuseT1CutFault = !PDU_EfuseT1CutFaultRead;

  /* Logic: '<S27>/Logical Operator6' incorporates:
   *  Inport: '<Root>/PDU_EfuseT2CutFaultRead'
   */
  PDU_EfuseT2CutFault = !PDU_EfuseT2CutFaultRead;

  /* Logic: '<S27>/Logical Operator7' incorporates:
   *  Inport: '<Root>/PDU_EfuseT4CutFaultRead'
   */
  PDU_EfuseT4CutFault = !PDU_EfuseT4CutFaultRead;

  /* Logic: '<S27>/Logical Operator19' */
  PDU_EfuseCutFault = (PDU_flgEfuseOverCut || PDU_EfuseT3CutFault ||
                       PDU_EfuseT5CutFault || PDU_EfuseT1CutFault ||
                       PDU_EfuseT2CutFault || PDU_EfuseT4CutFault);

  /* Logic: '<S27>/Logical Operator1' incorporates:
   *  Inport: '<Root>/PDU_flgOverVol'
   */
  PDU_flgFault = (PDU_flgRelayAdhesion || PDU_flgEfuseOverCut || PDU_flgOverVol ||
                  PDU_EfuseCutFault);

  /* Switch: '<S36>/Switch' incorporates:
   *  Constant: '<S27>/Constant5'
   *  Logic: '<S27>/Logical Operator8'
   *  Logic: '<S27>/Logical Operator9'
   *  S-Function (sfix_bitop): '<S36>/Bitwise Operator1'
   *  S-Function (sfix_bitop): '<S36>/Bitwise Operator2'
   *  Switch: '<S35>/Switch'
   */
  if (PDU_EfuseT5CutFault || PDU_flgEfuseT5ConOverCut ||
      PDU_flgEfuseT5InsOverCut) {
    /* Switch: '<S35>/Switch' incorporates:
     *  Logic: '<S27>/Logical Operator8'
     */
    if (PDU_EfuseT3CutFault || PDU_flgEfuseT3ConOverCut ||
        PDU_flgEfuseT3InsOverCut) {
      rtb_Switch_i = PDU_ConstB.BitwiseOperator1;
    } else {
      rtb_Switch_i = PDU_ConstB.BitwiseOperator2;
    }

    rtb_Switch_i = (uint8_T)(rtb_Switch_i | 2);
  } else {
    if (PDU_EfuseT3CutFault || PDU_flgEfuseT3ConOverCut ||
        PDU_flgEfuseT3InsOverCut) {
      /* Switch: '<S35>/Switch' */
      rtb_Switch_i = PDU_ConstB.BitwiseOperator1;
    } else {
      /* Switch: '<S35>/Switch' */
      rtb_Switch_i = PDU_ConstB.BitwiseOperator2;
    }

    rtb_Switch_i &= PDU_ConstB.BitwiseOperator3_g;
  }

  /* End of Switch: '<S36>/Switch' */

  /* Switch: '<S37>/Switch' incorporates:
   *  Constant: '<S27>/Constant9'
   *  Logic: '<S27>/Logical Operator10'
   *  S-Function (sfix_bitop): '<S37>/Bitwise Operator1'
   *  S-Function (sfix_bitop): '<S37>/Bitwise Operator2'
   *  Switch: '<S36>/Switch1'
   */
  if (PDU_EfuseT1CutFault || PDU_flgEfuseT1ConOverCut ||
      PDU_flgEfuseT1InsOverCut) {
    rtb_Switch_i = (uint8_T)(rtb_Switch_i | 4);
  } else {
    rtb_Switch_i &= PDU_ConstB.BitwiseOperator3_f;
  }

  /* End of Switch: '<S37>/Switch' */

  /* Switch: '<S38>/Switch' incorporates:
   *  Constant: '<S27>/Constant11'
   *  Logic: '<S27>/Logical Operator11'
   *  S-Function (sfix_bitop): '<S38>/Bitwise Operator1'
   *  S-Function (sfix_bitop): '<S38>/Bitwise Operator2'
   *  Switch: '<S37>/Switch1'
   */
  if (PDU_EfuseT2CutFault || PDU_flgEfuseT2ConOverCut ||
      PDU_flgEfuseT2InsOverCut) {
    rtb_Switch_i = (uint8_T)(rtb_Switch_i | 8);
  } else {
    rtb_Switch_i &= PDU_ConstB.BitwiseOperator3_d;
  }

  /* End of Switch: '<S38>/Switch' */

  /* Switch: '<S39>/Switch' incorporates:
   *  Constant: '<S27>/Constant13'
   *  Logic: '<S27>/Logical Operator12'
   *  S-Function (sfix_bitop): '<S39>/Bitwise Operator1'
   *  S-Function (sfix_bitop): '<S39>/Bitwise Operator2'
   *  Switch: '<S38>/Switch1'
   */
  if (PDU_EfuseT4CutFault || PDU_flgEfuseT4ConOverCut ||
      PDU_flgEfuseT4InsOverCut) {
    rtb_Switch_i = (uint8_T)(rtb_Switch_i | 16);
  } else {
    rtb_Switch_i &= PDU_ConstB.BitwiseOperator3_fl;
  }

  /* End of Switch: '<S39>/Switch' */

  /* RelationalOperator: '<S27>/Relational Operator' incorporates:
   *  Constant: '<S27>/Constant1'
   *  Inport: '<Root>/PDU_EfuseTemp'
   */
  rtb_UnitDelay3_j = (PDU_EfuseTemp >= PDU_EfuseOverTempThresh);

  /* Logic: '<S27>/Logical Operator2' */
  rtb_LogicalOperator2_pt = !rtb_UnitDelay3_j;

  /* UnitDelay: '<S43>/Unit Delay3' */
  rtb_UnitDelay3_ds = PDU_DW.UnitDelay3_DSTATE_m;

  /* Outputs for Atomic SubSystem: '<S43>/SR_latch' */
  /* Logic: '<S43>/Logical Operator' incorporates:
   *  Logic: '<S43>/Logical Operator NOT4'
   *  Logic: '<S43>/Logical Operator NOT5'
   *  Logic: '<S43>/Logical Operator2'
   *  UnitDelay: '<S43>/Unit Delay3'
   *  UnitDelay: '<S43>/Unit Delay4'
   *  UnitDelay: '<S43>/Unit Delay5'
   */
  PDU_SR_latch(rtb_UnitDelay3_j && (!PDU_DW.UnitDelay4_DSTATE_f),
               rtb_LogicalOperator2_pt && (!PDU_DW.UnitDelay5_DSTATE_nf),
               &PDU_DW.UnitDelay3_DSTATE_m, &PDU_DW.SR_latch);

  /* End of Outputs for SubSystem: '<S43>/SR_latch' */

  /* Switch: '<S43>/Switch1' incorporates:
   *  Switch: '<S43>/Switch'
   *  UnitDelay: '<S43>/Unit Delay3'
   */
  if (rtb_LogicalOperator2_pt) {
    /* Switch: '<S43>/Switch1' incorporates:
     *  Constant: '<S43>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE_pr = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_m) {
      /* Switch: '<S43>/Switch3' incorporates:
       *  Constant: '<S27>/Constant6'
       *  Constant: '<S43>/Constant4'
       *  Constant: '<S43>/Constant6'
       *  Logic: '<S43>/Logical Operator NOT2'
       *  Logic: '<S43>/Logical Operator NOT3'
       *  Logic: '<S43>/Logical Operator1'
       *  RelationalOperator: '<S43>/Relational Operator4'
       *  Switch: '<S43>/Switch'
       *  Switch: '<S43>/Switch5'
       *  UnitDelay: '<S43>/Unit Delay2'
       */
      if (rtb_UnitDelay3_j && (!PDU_DW.UnitDelay2_DSTATE_gh) &&
          (!rtb_UnitDelay3_ds)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S43>/Switch5' incorporates:
         *  Constant: '<S27>/Constant6'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S43>/Switch3' */
    } else {
      /* Switch: '<S43>/Switch' incorporates:
       *  Constant: '<S43>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S43>/Switch1' incorporates:
     *  Sum: '<S43>/Sum'
     *  Switch: '<S43>/Switch'
     *  UnitDelay: '<S43>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE_pr += tmp;
  }

  /* End of Switch: '<S43>/Switch1' */

  /* Switch: '<S43>/Switch4' incorporates:
   *  Constant: '<S27>/Constant7'
   *  Constant: '<S43>/Constant3'
   *  RelationalOperator: '<S43>/Relational Operator3'
   */
  if (PDU_EfuseOverTempTime > 0.0F) {
    rtb_Switch4_l3 = (real32_T)PDU_EfuseOverTempTime;
  } else {
    rtb_Switch4_l3 = 0.0F;
  }

  /* End of Switch: '<S43>/Switch4' */

  /* RelationalOperator: '<S43>/Relational Operator' */
  rtb_UnitDelay3_ds = (PDU_DW.UnitDelay1_DSTATE_pr < rtb_Switch4_l3);

  /* Logic: '<S43>/Logical Operator NOT1' */
  PDU_flgEfuseOverTemp = !rtb_UnitDelay3_ds;

  /* Switch: '<S40>/Switch' incorporates:
   *  Constant: '<S27>/Constant15'
   *  S-Function (sfix_bitop): '<S40>/Bitwise Operator1'
   *  S-Function (sfix_bitop): '<S40>/Bitwise Operator2'
   *  Switch: '<S39>/Switch1'
   */
  if (PDU_flgEfuseOverTemp) {
    rtb_Switch_i = (uint8_T)(rtb_Switch_i | 32);
  } else {
    rtb_Switch_i &= PDU_ConstB.BitwiseOperator3_h;
  }

  /* Switch: '<S42>/Switch1' incorporates:
   *  S-Function (sfix_bitop): '<S41>/Bitwise Operator2'
   *  S-Function (sfix_bitop): '<S42>/Bitwise Operator2'
   *  Switch: '<S40>/Switch'
   */
  PDU_EfuseFault = (uint8_T)(rtb_Switch_i & PDU_ConstB.BitwiseOperator3_e &
    PDU_ConstB.BitwiseOperator3_i);

  /* Switch: '<S43>/Switch2' */
  if (!rtb_UnitDelay3_ds) {
    /* Switch: '<S43>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_pr = rtb_Switch4_l3;
  }

  /* End of Switch: '<S43>/Switch2' */

  /* Switch: '<S75>/Switch2' */
  if (rtb_RelationalOperator_b) {
    /* Switch: '<S75>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_n = rtb_Switch1_d2;
  }

  /* End of Switch: '<S75>/Switch2' */

  /* Switch: '<S74>/Switch2' */
  if (rtb_RelationalOperator_iz) {
    /* Switch: '<S74>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_a = rtb_Switch1_of;
  }

  /* End of Switch: '<S74>/Switch2' */

  /* Switch: '<S73>/Switch2' */
  if (rtb_RelationalOperator_fe) {
    /* Switch: '<S73>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_oy = rtb_Switch1_g;
  }

  /* End of Switch: '<S73>/Switch2' */

  /* Switch: '<S72>/Switch2' */
  if (rtb_RelationalOperator_jp) {
    /* Switch: '<S72>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_o = rtb_Switch1_o1;
  }

  /* End of Switch: '<S72>/Switch2' */

  /* Switch: '<S71>/Switch2' */
  if (rtb_RelationalOperator_p) {
    /* Switch: '<S71>/Switch4' */
    PDU_DW.UnitDelay1_DSTATE_i1 = rtb_Switch1_h1;
  }

  /* End of Switch: '<S71>/Switch2' */

  /* Switch: '<S51>/Switch2' */
  if (!rtb_RelationalOperator_l) {
    /* Switch: '<S51>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_l = rtb_Switch4_k;
  }

  /* End of Switch: '<S51>/Switch2' */

  /* Switch: '<S50>/Switch2' */
  if (!rtb_RelationalOperator_a) {
    /* Switch: '<S50>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_i = rtb_Switch4_lt;
  }

  /* End of Switch: '<S50>/Switch2' */

  /* Switch: '<S49>/Switch2' */
  if (!rtb_RelationalOperator_d) {
    /* Switch: '<S49>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_e = rtb_Switch4_o;
  }

  /* End of Switch: '<S49>/Switch2' */

  /* Switch: '<S48>/Switch2' */
  if (!rtb_RelationalOperator_jw) {
    /* Switch: '<S48>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_p = rtb_Switch4_c;
  }

  /* End of Switch: '<S48>/Switch2' */

  /* Switch: '<S47>/Switch2' */
  if (!rtb_RelationalOperator_fa) {
    /* Switch: '<S47>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_h = rtb_Switch4_hs;
  }

  /* End of Switch: '<S47>/Switch2' */

  /* Switch: '<S46>/Switch2' */
  if (!rtb_RelationalOperator_g) {
    /* Switch: '<S46>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE_k = rtb_Switch4_f;
  }

  /* End of Switch: '<S46>/Switch2' */

  /* Switch: '<S45>/Switch2' incorporates:
   *  UnitDelay: '<S45>/Unit Delay1'
   */
  if (rtb_RelationalOperator_ez) {
    PDU_DW.UnitDelay1_DSTATE_j = rtb_Switch1_mx;
  } else {
    PDU_DW.UnitDelay1_DSTATE_j = rtb_Switch4_m0;
  }

  /* End of Switch: '<S45>/Switch2' */

  /* Update for UnitDelay: '<S44>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_oa = rtb_LogicalOperator14;

  /* Update for UnitDelay: '<S44>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_m = rtb_LogicalOperator14;

  /* Update for UnitDelay: '<S44>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_b = rtb_LogicalOperator13;

  /* Update for Atomic SubSystem: '<S44>/SR_latch' */
  /* UnitDelay: '<S44>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_b, &PDU_DW.SR_latch_e);

  /* End of Update for SubSystem: '<S44>/SR_latch' */

  /* Update for UnitDelay: '<S45>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_p = rtb_UnitDelay3_d;

  /* Update for UnitDelay: '<S45>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_mw = rtb_UnitDelay3_d;

  /* Update for UnitDelay: '<S45>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_n = rtb_LogicalOperator16;

  /* Update for Atomic SubSystem: '<S45>/SR_latch' */
  /* UnitDelay: '<S45>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_n, &PDU_DW.SR_latch_o);

  /* End of Update for SubSystem: '<S45>/SR_latch' */

  /* Update for UnitDelay: '<S46>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_g = rtb_UnitDelay3_c;

  /* Update for UnitDelay: '<S46>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_e = rtb_UnitDelay3_c;

  /* Update for UnitDelay: '<S46>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_e = rtb_LogicalOperator22;

  /* Update for Atomic SubSystem: '<S46>/SR_latch' */
  /* UnitDelay: '<S46>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_bq, &PDU_DW.SR_latch_n);

  /* End of Update for SubSystem: '<S46>/SR_latch' */

  /* Update for UnitDelay: '<S47>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_a = rtb_UnitDelay3_n4;

  /* Update for UnitDelay: '<S47>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_g = rtb_UnitDelay3_n4;

  /* Update for UnitDelay: '<S47>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_a = rtb_LogicalOperator25;

  /* Update for Atomic SubSystem: '<S47>/SR_latch' */
  /* UnitDelay: '<S47>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_a, &PDU_DW.SR_latch_eq);

  /* End of Update for SubSystem: '<S47>/SR_latch' */

  /* Update for UnitDelay: '<S48>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_on = rtb_UnitDelay3_f2;

  /* Update for UnitDelay: '<S48>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_n = rtb_UnitDelay3_f2;

  /* Update for UnitDelay: '<S48>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_nr = rtb_LogicalOperator28;

  /* Update for Atomic SubSystem: '<S48>/SR_latch' */
  /* UnitDelay: '<S48>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_l, &PDU_DW.SR_latch_el);

  /* End of Update for SubSystem: '<S48>/SR_latch' */

  /* Update for UnitDelay: '<S49>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_oaz = rtb_UnitDelay3_p;

  /* Update for UnitDelay: '<S49>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_c = rtb_UnitDelay3_p;

  /* Update for UnitDelay: '<S49>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_i = rtb_LogicalOperator31;

  /* Update for Atomic SubSystem: '<S49>/SR_latch' */
  /* UnitDelay: '<S49>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_en, &PDU_DW.SR_latch_ny);

  /* End of Update for SubSystem: '<S49>/SR_latch' */

  /* Update for UnitDelay: '<S50>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_f = rtb_UnitDelay3_k;

  /* Update for UnitDelay: '<S50>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_cs = rtb_UnitDelay3_k;

  /* Update for UnitDelay: '<S50>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_i1 = rtb_LogicalOperator34;

  /* Update for Atomic SubSystem: '<S50>/SR_latch' */
  /* UnitDelay: '<S50>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_h, &PDU_DW.SR_latch_e0);

  /* End of Update for SubSystem: '<S50>/SR_latch' */

  /* Update for UnitDelay: '<S51>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_aw = rtb_UnitDelay3_bs;

  /* Update for UnitDelay: '<S51>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_o = rtb_UnitDelay3_bs;

  /* Update for UnitDelay: '<S51>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_o = rtb_LogicalOperator37;

  /* Update for Atomic SubSystem: '<S51>/SR_latch' */
  /* UnitDelay: '<S51>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_bqz, &PDU_DW.SR_latch_f);

  /* End of Update for SubSystem: '<S51>/SR_latch' */

  /* Update for UnitDelay: '<S71>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_d = rtb_UnitDelay3_n;

  /* Update for UnitDelay: '<S71>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_et = rtb_UnitDelay3_n;

  /* Update for UnitDelay: '<S71>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_c = rtb_LogicalOperator_lz;

  /* Update for Atomic SubSystem: '<S71>/SR_latch' */
  /* UnitDelay: '<S71>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_g, &PDU_DW.SR_latch_ne);

  /* End of Update for SubSystem: '<S71>/SR_latch' */

  /* Update for UnitDelay: '<S52>/Unit Delay' incorporates:
   *  Inport: '<Root>/PDU_EfuseT3Current'
   */
  PDU_DW.UnitDelay_DSTATE = PDU_EfuseT3Current;

  /* Update for UnitDelay: '<S72>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_fq = rtb_UnitDelay3_lf;

  /* Update for UnitDelay: '<S72>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_cm = rtb_UnitDelay3_lf;

  /* Update for UnitDelay: '<S72>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_h = rtb_LogicalOperator2_mu;

  /* Update for Atomic SubSystem: '<S72>/SR_latch' */
  /* UnitDelay: '<S72>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_do, &PDU_DW.SR_latch_h);

  /* End of Update for SubSystem: '<S72>/SR_latch' */

  /* Update for UnitDelay: '<S52>/Unit Delay1' incorporates:
   *  Inport: '<Root>/PDU_EfuseT5Current'
   */
  PDU_DW.UnitDelay1_DSTATE_lr = PDU_EfuseT5Current;

  /* Update for UnitDelay: '<S73>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_i = rtb_UnitDelay3_i;

  /* Update for UnitDelay: '<S73>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_b = rtb_UnitDelay3_i;

  /* Update for UnitDelay: '<S73>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_m = rtb_LogicalOperator4;

  /* Update for Atomic SubSystem: '<S73>/SR_latch' */
  /* UnitDelay: '<S73>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_li, &PDU_DW.SR_latch_m);

  /* End of Update for SubSystem: '<S73>/SR_latch' */

  /* Update for UnitDelay: '<S52>/Unit Delay2' incorporates:
   *  Inport: '<Root>/PDU_EfuseT1Current'
   */
  PDU_DW.UnitDelay2_DSTATE = PDU_EfuseT1Current;

  /* Update for UnitDelay: '<S74>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_c = rtb_UnitDelay3_jl;

  /* Update for UnitDelay: '<S74>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_p = rtb_UnitDelay3_jl;

  /* Update for UnitDelay: '<S74>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_f = rtb_LogicalOperator6;

  /* Update for Atomic SubSystem: '<S74>/SR_latch' */
  /* UnitDelay: '<S74>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_dd, &PDU_DW.SR_latch_d);

  /* End of Update for SubSystem: '<S74>/SR_latch' */

  /* Update for UnitDelay: '<S52>/Unit Delay3' incorporates:
   *  Inport: '<Root>/PDU_EfuseT2Current'
   */
  PDU_DW.UnitDelay3_DSTATE = PDU_EfuseT2Current;

  /* Update for UnitDelay: '<S75>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_jy = rtb_UnitDelay3_nw;

  /* Update for UnitDelay: '<S75>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_pw = rtb_UnitDelay3_nw;

  /* Update for UnitDelay: '<S75>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_ch = rtb_LogicalOperator8;

  /* Update for Atomic SubSystem: '<S75>/SR_latch' */
  /* UnitDelay: '<S75>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_hu, &PDU_DW.SR_latch_l);

  /* End of Update for SubSystem: '<S75>/SR_latch' */

  /* Update for UnitDelay: '<S52>/Unit Delay4' incorporates:
   *  Inport: '<Root>/PDU_EfuseT4Current'
   */
  PDU_DW.UnitDelay4_DSTATE = PDU_EfuseT4Current;

  /* Update for UnitDelay: '<S43>/Unit Delay2' */
  PDU_DW.UnitDelay2_DSTATE_gh = rtb_UnitDelay3_j;

  /* Update for UnitDelay: '<S43>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_f = rtb_UnitDelay3_j;

  /* Update for UnitDelay: '<S43>/Unit Delay5' */
  PDU_DW.UnitDelay5_DSTATE_nf = rtb_LogicalOperator2_pt;

  /* Update for Atomic SubSystem: '<S43>/SR_latch' */
  /* UnitDelay: '<S43>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_m, &PDU_DW.SR_latch);

  /* End of Update for SubSystem: '<S43>/SR_latch' */

  /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
   *  Chart: '<S3>/Chart'
   */
  /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
   *  SubSystem: '<S3>/PDU_FAULT'
   */
  /* Chart: '<S3>/Chart' incorporates:
   *  Switch: '<S26>/Switch13'
   *  Switch: '<S26>/Switch2'
   */
  rtb_UnitDelay3_d = !PDU_MainPreChargeTimeout;
  rtb_LogicalOperator13 = !PDU_AttPreChargeTimeout;

  /* Switch: '<S26>/Switch' incorporates:
   *  Constant: '<S26>/Constant'
   */
  if (PDU_overEfuseFaultReact) {
    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant1'
     */
    rtb_Switch_i = PDU_numEfuseFaultReact;
  } else {
    /* Switch: '<S26>/Switch1' */
    rtb_Switch_i = PDU_EfuseFault;
  }

  /* End of Switch: '<S26>/Switch' */

  /* S-Function (sfix_bitop): '<S26>/Bitwise AND4' incorporates:
   *  S-Function (sfix_bitop): '<S3>/Bitwise AND1'
   *  S-Function (sfix_bitop): '<S3>/Bitwise AND4'
   *  Switch: '<S3>/Switch17'
   *  Switch: '<S3>/Switch8'
   */
  Switch7_tmp = rtb_Switch_i & 16U;

  /* Switch: '<S26>/Switch7' incorporates:
   *  S-Function (sfix_bitop): '<S26>/Bitwise AND4'
   */
  rtb_LogicalOperator14 = ((Switch7_tmp == 0U) && PDU_HCU3PTCCmd);

  /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
   *  Chart: '<S3>/Chart'
   */
  /* Chart: '<S3>/Chart' incorporates:
   *  Inport: '<Root>/PDU_AttVoltage'
   *  Inport: '<Root>/PDU_BatteryVoltage'
   *  Inport: '<Root>/PDU_MainPosVoltage'
   *  Inport: '<Root>/PDU_flgKL15'
   */
  if (PDU_DW.is_active_c3_PDU == 0U) {
    PDU_DW.is_active_c3_PDU = 1U;
    PDU_DW.is_c3_PDU = PDU_IN_INIT;
    PDU_state = 0U;

    /* Outputs for Function Call SubSystem: '<S3>/PDU_INIT' */
    PDU_PDU_INIT(PDU_HCU3MainNegCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                 &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                 &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                 &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                 &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                 &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                 &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                 &PDU_EfuseT4Cmd);

    /* End of Outputs for SubSystem: '<S3>/PDU_INIT' */
  } else {
    switch (PDU_DW.is_c3_PDU) {
     case PDU_IN_ACTIVE:
      if (PDU_flgShutDown || (!PDU_HCU3AttCmd) || (!PDU_HCU3MainPosCmd)) {
        PDU_DW.is_ACTIVE = PDU_IN_NO_ACTIVE_CHILD;
        PDU_DW.is_c3_PDU = PDU_IN_SHUTDOWN;
        PDU_state = 5U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_SHUTDOWN' */
        PDU_PDU_SHUTDOWN(PDU_flgShutDown, PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd,
                         PDU_HCU3BatHeatCmd, PDU_HCU3AttCmd, PDU_HCU3PTCCmd,
                         PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_SHUTDOWN' */
      } else if (PDU_flgCharge2Init) {
        PDU_DW.is_ACTIVE = PDU_IN_NO_ACTIVE_CHILD;
        PDU_DW.is_c3_PDU = PDU_IN_INIT;
        PDU_state = 0U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_INIT' */
        PDU_PDU_INIT(PDU_HCU3MainNegCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                     &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                     &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                     &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                     &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                     &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                     &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                     &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_INIT' */
      } else {
        PDU_state = 4U;
        if (PDU_DW.is_ACTIVE == PDU_IN_CHARGEMODE) {
          /* Outputs for Function Call SubSystem: '<S3>/PDU_CHARGE' */
          PDU_PDU_CHARGE(true, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd, true,
                         PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

          /* End of Outputs for SubSystem: '<S3>/PDU_CHARGE' */

          /* case IN_DRIVEMODE: */
        } else if (PDU_flgDrive2Charge) {
          PDU_DW.is_ACTIVE = PDU_IN_CHARGEMODE;

          /* Outputs for Function Call SubSystem: '<S3>/PDU_CHARGE' */
          PDU_PDU_CHARGE(true, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd, true,
                         PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

          /* End of Outputs for SubSystem: '<S3>/PDU_CHARGE' */
        } else {
          /* Outputs for Function Call SubSystem: '<S3>/PDU_DRIVE' */
          PDU_PDU_DRIVE(true, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                        PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd, true,
                        &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                        &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                        &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                        &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                        &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                        &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                        &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

          /* End of Outputs for SubSystem: '<S3>/PDU_DRIVE' */
        }
      }
      break;

     case PDU_IN_ATTON:
      if (PDU_flgShutDown || (!PDU_HCU3AttCmd)) {
        PDU_DW.is_c3_PDU = PDU_IN_SHUTDOWN;
        PDU_state = 5U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_SHUTDOWN' */
        PDU_PDU_SHUTDOWN(PDU_flgShutDown, PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd,
                         PDU_HCU3BatHeatCmd, PDU_HCU3AttCmd, PDU_HCU3PTCCmd,
                         PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_SHUTDOWN' */
      } else if (PDU_HCU3MainPosCmd && rtb_UnitDelay3_d) {
        PDU_DW.is_c3_PDU = PDU_IN_MAINPRECHARGE;
        PDU_state = 3U;
        PDU_DW.PDU_timeMainPreCharge = 0.0;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_MAINPRECHARGE' */
        PDU_PDU_MAINPRECHARGE(PDU_MainPosVoltage, PDU_BatteryVoltage,
                              PDU_flgKL15, true, PDU_HCU3MainNegCmd,
                              PDU_HCU3BatHeatCmd, true, PDU_HCU3PTCCmd,
                              PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                              &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                              &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                              &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                              &PDU_DW.UnitDelay5_DSTATE,
                              &PDU_DW.UnitDelay6_DSTATE,
                              &PDU_DW.UnitDelay7_DSTATE,
                              &PDU_DW.UnitDelay8_DSTATE,
                              &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd,
                              &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd,
                              &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd,
                              &PDU_DW.PDU_MAINPRECHARGE);

        /* End of Outputs for SubSystem: '<S3>/PDU_MAINPRECHARGE' */
      } else {
        /* Outputs for Function Call SubSystem: '<S3>/PDU_ATTON' */
        PDU_PDU_ATTON(PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                      PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd, true,
                      &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                      &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                      &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                      &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                      &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                      &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                      &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_ATTON' */
      }
      break;

     case PDU_IN_ATTPRECHARGE:
      if (PDU_flgAttPreChargeCom && (PDU_DW.PDU_timeAttPreCharge < 3000.0)) {
        PDU_DW.is_c3_PDU = PDU_IN_ATTON;
        PDU_state = 2U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_ATTON' */
        PDU_PDU_ATTON(PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                      PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                      PDU_HCU3AttCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                      &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                      &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                      &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                      &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                      &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                      &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                      &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_ATTON' */
      } else if (PDU_flgShutDown || (!PDU_HCU3AttCmd)) {
        PDU_DW.is_c3_PDU = PDU_IN_SHUTDOWN;
        PDU_state = 5U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_SHUTDOWN' */
        PDU_PDU_SHUTDOWN(PDU_flgShutDown, PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd,
                         PDU_HCU3BatHeatCmd, PDU_HCU3AttCmd, PDU_HCU3PTCCmd,
                         PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_SHUTDOWN' */
      } else if ((PDU_DW.PDU_timeAttPreCharge >= 3000.0) &&
                 (!PDU_flgAttPreChargeCom)) {
        PDU_AttPreChargeTimeout = true;
        PDU_DW.is_c3_PDU = PDU_IN_INIT;
        PDU_state = 0U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_INIT' */
        PDU_PDU_INIT(PDU_HCU3MainNegCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                     &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                     &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                     &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                     &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                     &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                     &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                     &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_INIT' */
      } else {
        PDU_DW.PDU_timeAttPreCharge += 10.0;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_ATTPRECHARGE' */
        PDU_PDU_ATTPRECHARGE(PDU_AttVoltage, PDU_BatteryVoltage, PDU_flgKL15,
                             PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                             PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                             true, &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                             &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                             &PDU_DW.UnitDelay10_DSTATE,
                             &PDU_DW.UnitDelay5_DSTATE,
                             &PDU_DW.UnitDelay6_DSTATE,
                             &PDU_DW.UnitDelay7_DSTATE,
                             &PDU_DW.UnitDelay8_DSTATE,
                             &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd,
                             &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd,
                             &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd,
                             &PDU_DW.PDU_ATTPRECHARGE);

        /* End of Outputs for SubSystem: '<S3>/PDU_ATTPRECHARGE' */
      }
      break;

     case PDU_IN_INIT:
      if (PDU_flgInitOK && PDU_HCU3AttCmd && rtb_LogicalOperator13) {
        PDU_DW.is_c3_PDU = PDU_IN_ATTPRECHARGE;
        PDU_state = 1U;
        PDU_DW.PDU_timeAttPreCharge = 0.0;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_ATTPRECHARGE' */
        PDU_PDU_ATTPRECHARGE(PDU_AttVoltage, PDU_BatteryVoltage, PDU_flgKL15,
                             PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                             PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                             true, &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                             &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                             &PDU_DW.UnitDelay10_DSTATE,
                             &PDU_DW.UnitDelay5_DSTATE,
                             &PDU_DW.UnitDelay6_DSTATE,
                             &PDU_DW.UnitDelay7_DSTATE,
                             &PDU_DW.UnitDelay8_DSTATE,
                             &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd,
                             &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd,
                             &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd,
                             &PDU_DW.PDU_ATTPRECHARGE);

        /* End of Outputs for SubSystem: '<S3>/PDU_ATTPRECHARGE' */
      } else if (PDU_flgShutDown) {
        PDU_DW.is_c3_PDU = PDU_IN_SHUTDOWN;
        PDU_state = 5U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_SHUTDOWN' */
        PDU_PDU_SHUTDOWN(true, PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd,
                         PDU_HCU3BatHeatCmd, PDU_HCU3AttCmd, PDU_HCU3PTCCmd,
                         PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_SHUTDOWN' */
      } else {
        /* Outputs for Function Call SubSystem: '<S3>/PDU_INIT' */
        PDU_PDU_INIT(PDU_HCU3MainNegCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                     &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                     &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                     &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                     &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                     &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                     &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                     &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_INIT' */
      }
      break;

     case PDU_IN_MAINPRECHARGE:
      if (PDU_flgMainPreChargeCom && (PDU_DW.PDU_timeMainPreCharge < 3000.0)) {
        PDU_DW.is_c3_PDU = PDU_IN_ACTIVE;
        PDU_state = 4U;
        PDU_DW.is_ACTIVE = PDU_IN_DRIVEMODE;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_DRIVE' */
        PDU_PDU_DRIVE(PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                      PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                      PDU_HCU3AttCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                      &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                      &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                      &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                      &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                      &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                      &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                      &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_DRIVE' */
      } else if (PDU_flgShutDown || (!PDU_HCU3AttCmd) || (!PDU_HCU3MainPosCmd))
      {
        PDU_DW.is_c3_PDU = PDU_IN_SHUTDOWN;
        PDU_state = 5U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_SHUTDOWN' */
        PDU_PDU_SHUTDOWN(PDU_flgShutDown, PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd,
                         PDU_HCU3BatHeatCmd, PDU_HCU3AttCmd, PDU_HCU3PTCCmd,
                         PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_SHUTDOWN' */
      } else if (PDU_DW.PDU_timeMainPreCharge >= 3000.0) {
        PDU_MainPreChargeTimeout = true;
        PDU_DW.is_c3_PDU = PDU_IN_ATTON;
        PDU_state = 2U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_ATTON' */
        PDU_PDU_ATTON(true, PDU_HCU3MainNegCmd, PDU_HCU3BatHeatCmd,
                      PDU_HCU3PTCCmd, PDU_HCU3MECUCmd, PDU_HCU3ACCmd, true,
                      &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                      &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                      &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                      &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                      &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                      &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                      &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_ATTON' */
      } else {
        PDU_DW.PDU_timeMainPreCharge += 10.0;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_MAINPRECHARGE' */
        PDU_PDU_MAINPRECHARGE(PDU_MainPosVoltage, PDU_BatteryVoltage,
                              PDU_flgKL15, true, PDU_HCU3MainNegCmd,
                              PDU_HCU3BatHeatCmd, true, PDU_HCU3PTCCmd,
                              PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                              &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                              &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                              &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                              &PDU_DW.UnitDelay5_DSTATE,
                              &PDU_DW.UnitDelay6_DSTATE,
                              &PDU_DW.UnitDelay7_DSTATE,
                              &PDU_DW.UnitDelay8_DSTATE,
                              &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd,
                              &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd,
                              &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd,
                              &PDU_DW.PDU_MAINPRECHARGE);

        /* End of Outputs for SubSystem: '<S3>/PDU_MAINPRECHARGE' */
      }
      break;

     default:
      /* case IN_SHUTDOWN: */
      if (PDU_flgShutDown2Init) {
        PDU_DW.is_c3_PDU = PDU_IN_INIT;
        PDU_state = 0U;

        /* Outputs for Function Call SubSystem: '<S3>/PDU_INIT' */
        PDU_PDU_INIT(PDU_HCU3MainNegCmd, &PDU_DW.UnitDelay3_DSTATE_d,
                     &PDU_MainNegCmd, &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd,
                     &PDU_K3Cmd, &PDU_DW.UnitDelay10_DSTATE,
                     &PDU_DW.UnitDelay5_DSTATE, &PDU_DW.UnitDelay6_DSTATE,
                     &PDU_DW.UnitDelay7_DSTATE, &PDU_DW.UnitDelay8_DSTATE,
                     &PDU_DW.UnitDelay9_DSTATE, &PDU_K10Cmd, &PDU_EfuseT3Cmd,
                     &PDU_EfuseT5Cmd, &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd,
                     &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_INIT' */
      } else {
        /* Outputs for Function Call SubSystem: '<S3>/PDU_SHUTDOWN' */
        PDU_PDU_SHUTDOWN(PDU_flgShutDown, PDU_HCU3MainPosCmd, PDU_HCU3MainNegCmd,
                         PDU_HCU3BatHeatCmd, PDU_HCU3AttCmd, PDU_HCU3PTCCmd,
                         PDU_HCU3MECUCmd, PDU_HCU3ACCmd,
                         &PDU_DW.UnitDelay3_DSTATE_d, &PDU_MainNegCmd,
                         &PDU_DW.UnitDelay2_DSTATE_j, &PDU_K4Cmd, &PDU_K3Cmd,
                         &PDU_DW.UnitDelay10_DSTATE, &PDU_DW.UnitDelay5_DSTATE,
                         &PDU_DW.UnitDelay6_DSTATE, &PDU_DW.UnitDelay7_DSTATE,
                         &PDU_DW.UnitDelay8_DSTATE, &PDU_DW.UnitDelay9_DSTATE,
                         &PDU_K10Cmd, &PDU_EfuseT3Cmd, &PDU_EfuseT5Cmd,
                         &PDU_EfuseT1Cmd, &PDU_EfuseT2Cmd, &PDU_EfuseT4Cmd);

        /* End of Outputs for SubSystem: '<S3>/PDU_SHUTDOWN' */
      }
      break;
    }
  }

  /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
   *  SubSystem: '<S3>/PDU_SC'
   */
  /* Outputs for Atomic SubSystem: '<S30>/PDU_INIT' */
  /* Logic: '<S91>/Logical Operator1' incorporates:
   *  Inport: '<Root>/PDU_flgKL15'
   *  Logic: '<S91>/Logical Operator'
   */
  PDU_flgInitOK = ((!PDU_flgFault) && PDU_flgKL15);

  /* End of Outputs for SubSystem: '<S30>/PDU_INIT' */

  /* Outputs for Atomic SubSystem: '<S30>/PowerDown' */
  /* Outputs for Atomic SubSystem: '<S30>/PDU_SHUTDOWN' */
  /* Logic: '<S94>/Logical Operator' incorporates:
   *  Inport: '<Root>/PDU_flgKL15'
   *  Logic: '<S95>/Logical Operator'
   */
  PDU_flgShutDown = !PDU_flgKL15;

  /* End of Outputs for SubSystem: '<S30>/PowerDown' */

  /* UnitDelay: '<S96>/Unit Delay3' */
  rtb_LogicalOperator16 = PDU_DW.UnitDelay3_DSTATE_e;

  /* Outputs for Atomic SubSystem: '<S96>/SR_latch' */
  /* Logic: '<S96>/Logical Operator' incorporates:
   *  Inport: '<Root>/PDU_flgKL15'
   *  Logic: '<S94>/Logical Operator'
   *  Logic: '<S96>/Logical Operator NOT4'
   *  Logic: '<S96>/Logical Operator NOT5'
   *  Logic: '<S96>/Logical Operator2'
   *  UnitDelay: '<S96>/Unit Delay3'
   *  UnitDelay: '<S96>/Unit Delay4'
   *  UnitDelay: '<S96>/Unit Delay5'
   */
  PDU_SR_latch(PDU_flgShutDown && (!PDU_DW.UnitDelay4_DSTATE_i), PDU_flgKL15 &&
               (!PDU_DW.UnitDelay5_DSTATE_j), &PDU_DW.UnitDelay3_DSTATE_e,
               &PDU_DW.SR_latch_h5);

  /* End of Outputs for SubSystem: '<S96>/SR_latch' */

  /* Switch: '<S96>/Switch1' incorporates:
   *  Inport: '<Root>/PDU_flgKL15'
   *  Switch: '<S96>/Switch'
   *  UnitDelay: '<S96>/Unit Delay3'
   */
  if (PDU_flgKL15) {
    /* Switch: '<S96>/Switch1' incorporates:
     *  Constant: '<S96>/Constant1'
     */
    PDU_DW.UnitDelay1_DSTATE = 0.0;
  } else {
    if (PDU_DW.UnitDelay3_DSTATE_e) {
      /* Switch: '<S96>/Switch3' incorporates:
       *  Constant: '<S94>/Constant6'
       *  Constant: '<S96>/Constant4'
       *  Constant: '<S96>/Constant6'
       *  Logic: '<S94>/Logical Operator'
       *  Logic: '<S96>/Logical Operator NOT2'
       *  Logic: '<S96>/Logical Operator NOT3'
       *  Logic: '<S96>/Logical Operator1'
       *  RelationalOperator: '<S96>/Relational Operator4'
       *  Switch: '<S96>/Switch'
       *  Switch: '<S96>/Switch5'
       *  UnitDelay: '<S96>/Unit Delay2'
       */
      if (PDU_flgShutDown && (!PDU_DW.UnitDelay2_DSTATE_o) &&
          (!rtb_LogicalOperator16)) {
        tmp = 0.0;
      } else if (PDU_TIME > 1.0) {
        /* Switch: '<S96>/Switch5' incorporates:
         *  Constant: '<S94>/Constant6'
         */
        tmp = PDU_TIME;
      } else {
        tmp = 1.0;
      }

      /* End of Switch: '<S96>/Switch3' */
    } else {
      /* Switch: '<S96>/Switch' incorporates:
       *  Constant: '<S96>/Constant2'
       */
      tmp = 0.0;
    }

    /* Switch: '<S96>/Switch1' incorporates:
     *  Sum: '<S96>/Sum'
     *  Switch: '<S96>/Switch'
     *  UnitDelay: '<S96>/Unit Delay1'
     */
    PDU_DW.UnitDelay1_DSTATE += tmp;
  }

  /* End of Switch: '<S96>/Switch1' */

  /* Switch: '<S96>/Switch4' incorporates:
   *  Constant: '<S94>/Constant7'
   *  Constant: '<S96>/Constant3'
   *  RelationalOperator: '<S96>/Relational Operator3'
   */
  if (PDU_reInitTime > 0) {
    i = PDU_reInitTime;
  } else {
    i = 0;
  }

  /* End of Switch: '<S96>/Switch4' */

  /* RelationalOperator: '<S96>/Relational Operator' */
  rtb_LogicalOperator16 = (PDU_DW.UnitDelay1_DSTATE < i);

  /* Logic: '<S96>/Logical Operator NOT1' */
  PDU_flgShutDown2Init = !rtb_LogicalOperator16;

  /* Switch: '<S96>/Switch2' */
  if (!rtb_LogicalOperator16) {
    /* Switch: '<S96>/Switch1' */
    PDU_DW.UnitDelay1_DSTATE = i;
  }

  /* End of Switch: '<S96>/Switch2' */
  /* End of Outputs for SubSystem: '<S30>/PDU_SHUTDOWN' */

  /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/PDU_OUT'
   */
  /* Outputs for Atomic SubSystem: '<S30>/PDU_PRECHARGE1' */
  /* Outputs for Atomic SubSystem: '<S30>/PDU_PRECHARGE' */
  /* Product: '<S92>/Product' incorporates:
   *  Constant: '<S92>/Constant'
   *  Inport: '<Root>/PDU_BatteryVoltage'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S93>/Product'
   *  Switch: '<S4>/Switch1'
   *  Switch: '<S4>/Switch4'
   */
  rtb_Switch4_m0 = PDU_PreChargeFactor * PDU_BatteryVoltage;

  /* End of Outputs for SubSystem: '<S30>/PDU_PRECHARGE1' */

  /* Logic: '<S92>/Logical Operator' incorporates:
   *  Inport: '<Root>/PDU_MainPosVoltage'
   *  Product: '<S92>/Product'
   *  RelationalOperator: '<S92>/Relational Operator'
   *  UnitDelay: '<S3>/Unit Delay1'
   */
  PDU_flgMainPreChargeCom = ((PDU_MainPosVoltage <= rtb_Switch4_m0) &&
    PDU_DW.UnitDelay1_DSTATE_g);

  /* End of Outputs for SubSystem: '<S30>/PDU_PRECHARGE' */

  /* Outputs for Atomic SubSystem: '<S30>/PDU_PRECHARGE1' */
  /* Logic: '<S93>/Logical Operator' incorporates:
   *  Inport: '<Root>/PDU_AttVoltage'
   *  RelationalOperator: '<S93>/Relational Operator'
   *  UnitDelay: '<S3>/Unit Delay4'
   */
  PDU_flgAttPreChargeCom = ((PDU_AttVoltage <= rtb_Switch4_m0) &&
    PDU_DW.UnitDelay4_DSTATE_a);

  /* End of Outputs for SubSystem: '<S30>/PDU_PRECHARGE1' */

  /* Outputs for Atomic SubSystem: '<S30>/PDU_ACTIVE_CHARGE' */
  /* Logic: '<S89>/Logical Operator' incorporates:
   *  Inport: '<Root>/PDU_flgChargeCAN'
   */
  PDU_flgCharge2Init = !PDU_flgChargeCAN;

  /* End of Outputs for SubSystem: '<S30>/PDU_ACTIVE_CHARGE' */

  /* Outputs for Atomic SubSystem: '<S30>/PDU_ACTIVE_DRIVE' */
  /* SignalConversion generated from: '<S90>/PDU_flgChargeCAN' incorporates:
   *  Inport: '<Root>/PDU_flgChargeCAN'
   */
  PDU_flgDrive2Charge = PDU_flgChargeCAN;

  /* End of Outputs for SubSystem: '<S30>/PDU_ACTIVE_DRIVE' */

  /* Update for Atomic SubSystem: '<S30>/PDU_SHUTDOWN' */
  /* Outputs for Atomic SubSystem: '<S30>/PDU_SHUTDOWN' */
  /* Update for UnitDelay: '<S96>/Unit Delay2' incorporates:
   *  Logic: '<S94>/Logical Operator'
   */
  PDU_DW.UnitDelay2_DSTATE_o = PDU_flgShutDown;

  /* Update for UnitDelay: '<S96>/Unit Delay4' incorporates:
   *  Logic: '<S94>/Logical Operator'
   */
  PDU_DW.UnitDelay4_DSTATE_i = PDU_flgShutDown;

  /* End of Outputs for SubSystem: '<S30>/PDU_SHUTDOWN' */

  /* Update for UnitDelay: '<S96>/Unit Delay5' incorporates:
   *  Inport: '<Root>/PDU_flgKL15'
   */
  PDU_DW.UnitDelay5_DSTATE_j = PDU_flgKL15;

  /* Update for Atomic SubSystem: '<S96>/SR_latch' */
  /* UnitDelay: '<S96>/Unit Delay3' */
  PDU_SR_latch_Update(&PDU_DW.UnitDelay3_DSTATE_e, &PDU_DW.SR_latch_h5);

  /* End of Update for SubSystem: '<S96>/SR_latch' */
  /* End of Update for SubSystem: '<S30>/PDU_SHUTDOWN' */
  /* End of Outputs for S-Function (fcgen): '<S3>/Function-Call Generator' */

  /* Switch: '<S3>/Switch5' incorporates:
   *  Constant: '<S3>/Constant8'
   */
  if (PDU_flgOverrideK10Relay) {
    /* DataTypeConversion: '<S3>/Data Type Conversion' incorporates:
     *  Constant: '<S3>/Constant9'
     */
    PDU_K10Cmd = PDU_manK10Cmd;
  }

  /* End of Switch: '<S3>/Switch5' */

  /* Switch: '<S3>/Switch4' incorporates:
   *  Constant: '<S3>/Constant6'
   *  Constant: '<S3>/Constant7'
   *  UnitDelay: '<S3>/Unit Delay9'
   */
  if (PDU_flgOverrideK9Relay) {
    PDU_DW.UnitDelay9_DSTATE = PDU_manK9Cmd;
  }

  /* End of Switch: '<S3>/Switch4' */

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  UnitDelay: '<S3>/Unit Delay9'
   */
  PDU_K9Cmd = PDU_DW.UnitDelay9_DSTATE;

  /* Switch: '<S3>/Switch6' incorporates:
   *  Constant: '<S3>/Constant10'
   */
  if (PDU_flgOverrideK4Relay) {
    /* DataTypeConversion: '<S3>/Data Type Conversion10' incorporates:
     *  Constant: '<S3>/Constant11'
     */
    PDU_K4Cmd = PDU_manK4Cmd;
  }

  /* End of Switch: '<S3>/Switch6' */

  /* Switch: '<S3>/Switch7' incorporates:
   *  Constant: '<S3>/Constant12'
   *  Constant: '<S3>/Constant13'
   *  UnitDelay: '<S3>/Unit Delay10'
   */
  if (PDU_flgOverrideReverseRelay) {
    PDU_DW.UnitDelay10_DSTATE = PDU_manReverseCmd;
  }

  /* End of Switch: '<S3>/Switch7' */

  /* DataTypeConversion: '<S3>/Data Type Conversion11' incorporates:
   *  UnitDelay: '<S3>/Unit Delay10'
   */
  PDU_ReserveCmd = PDU_DW.UnitDelay10_DSTATE;

  /* Switch: '<S3>/Switch8' incorporates:
   *  Constant: '<S3>/Constant14'
   *  Constant: '<S3>/Constant15'
   *  Switch: '<S3>/Switch20'
   *  UnitDelay: '<S3>/Unit Delay5'
   */
  if (PDU_flgOverridePTCRelay) {
    PDU_DW.UnitDelay5_DSTATE = PDU_manPTCCmd;
  } else if (Switch7_tmp != 0U) {
    /* Switch: '<S3>/Switch20' incorporates:
     *  UnitDelay: '<S3>/Unit Delay5'
     */
    PDU_DW.UnitDelay5_DSTATE = rtb_LogicalOperator14;
  }

  /* DataTypeConversion: '<S3>/Data Type Conversion12' incorporates:
   *  UnitDelay: '<S3>/Unit Delay5'
   */
  PDU_PTCCmd = PDU_DW.UnitDelay5_DSTATE;

  /* Switch: '<S3>/Switch9' incorporates:
   *  Constant: '<S3>/Constant16'
   *  Constant: '<S3>/Constant17'
   *  S-Function (sfix_bitop): '<S3>/Bitwise AND3'
   *  Switch: '<S3>/Switch21'
   *  UnitDelay: '<S3>/Unit Delay6'
   */
  if (PDU_flgOverrideBatHeatRelay) {
    PDU_DW.UnitDelay6_DSTATE = PDU_manBatHeatCmd;
  } else if ((rtb_Switch_i & 8U) != 0U) {
    /* Switch: '<S3>/Switch21' incorporates:
     *  UnitDelay: '<S3>/Unit Delay6'
     */
    PDU_DW.UnitDelay6_DSTATE = rtb_LogicalOperator14;
  }

  /* End of Switch: '<S3>/Switch9' */

  /* DataTypeConversion: '<S3>/Data Type Conversion13' incorporates:
   *  UnitDelay: '<S3>/Unit Delay6'
   */
  PDU_BatHeatCmd = PDU_DW.UnitDelay6_DSTATE;

  /* Switch: '<S3>/Switch10' incorporates:
   *  Constant: '<S3>/Constant18'
   *  Constant: '<S3>/Constant19'
   *  UnitDelay: '<S3>/Unit Delay7'
   */
  if (PDU_flgOverrideMECURelay) {
    PDU_DW.UnitDelay7_DSTATE = PDU_manMECUCmd;
  }

  /* End of Switch: '<S3>/Switch10' */

  /* DataTypeConversion: '<S3>/Data Type Conversion14' incorporates:
   *  UnitDelay: '<S3>/Unit Delay7'
   */
  PDU_MECUCmd = PDU_DW.UnitDelay7_DSTATE;

  /* Switch: '<S3>/Switch11' incorporates:
   *  Constant: '<S3>/Constant20'
   *  Constant: '<S3>/Constant21'
   *  UnitDelay: '<S3>/Unit Delay8'
   */
  if (PDU_flgOverrideACRelay) {
    PDU_DW.UnitDelay8_DSTATE = PDU_manACCmd;
  }

  /* End of Switch: '<S3>/Switch11' */

  /* DataTypeConversion: '<S3>/Data Type Conversion15' incorporates:
   *  UnitDelay: '<S3>/Unit Delay8'
   */
  PDU_ACCmd = PDU_DW.UnitDelay8_DSTATE;

  /* Switch: '<S3>/Switch12' incorporates:
   *  Constant: '<S3>/Constant22'
   */
  if (PDU_flgOverrideMainNegRelay) {
    /* DataTypeConversion: '<S3>/Data Type Conversion16' incorporates:
     *  Constant: '<S3>/Constant23'
     */
    PDU_MainNegCmd = PDU_manMainNegCmd;
  }

  /* End of Switch: '<S3>/Switch12' */

  /* Switch: '<S3>/Switch3' incorporates:
   *  Constant: '<S3>/Constant4'
   */
  if (PDU_flgOverrideK3Relay) {
    /* DataTypeConversion: '<S3>/Data Type Conversion2' incorporates:
     *  Constant: '<S3>/Constant5'
     */
    PDU_K3Cmd = PDU_manK3Cmd;
  }

  /* End of Switch: '<S3>/Switch3' */

  /* Switch: '<S3>/Switch1' incorporates:
   *  Constant: '<S3>/Constant2'
   *  Constant: '<S3>/Constant3'
   *  Switch: '<S3>/Switch19'
   *  UnitDelay: '<S3>/Unit Delay3'
   */
  if (PDU_flgOverrideMainPosRelay) {
    PDU_DW.UnitDelay3_DSTATE_d = PDU_manMainPosCmd;
  } else if (PDU_MainPreChargeTimeout) {
    /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
     *  SubSystem: '<S3>/PDU_FAULT'
     */
    /* Switch: '<S3>/Switch19' incorporates:
     *  Switch: '<S26>/Switch13'
     *  UnitDelay: '<S3>/Unit Delay3'
     */
    PDU_DW.UnitDelay3_DSTATE_d = (rtb_UnitDelay3_d && PDU_HCU3MainPosCmd);

    /* End of Outputs for S-Function (fcgen): '<S3>/Function-Call Generator' */
  }

  /* End of Switch: '<S3>/Switch1' */

  /* DataTypeConversion: '<S3>/Data Type Conversion3' incorporates:
   *  UnitDelay: '<S3>/Unit Delay3'
   */
  PDU_MainPosCmd = PDU_DW.UnitDelay3_DSTATE_d;

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Switch: '<S3>/Switch18'
   *  UnitDelay: '<S3>/Unit Delay2'
   */
  if (PDU_flgOverrideAttRelay) {
    PDU_DW.UnitDelay2_DSTATE_j = PDU_manAttCmd;
  } else if (PDU_AttPreChargeTimeout) {
    /* S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
     *  SubSystem: '<S3>/PDU_FAULT'
     */
    /* Switch: '<S3>/Switch18' incorporates:
     *  Switch: '<S26>/Switch2'
     *  UnitDelay: '<S3>/Unit Delay2'
     */
    PDU_DW.UnitDelay2_DSTATE_j = (rtb_LogicalOperator13 && PDU_HCU3AttCmd);

    /* End of Outputs for S-Function (fcgen): '<S3>/Function-Call Generator' */
  }

  /* End of Switch: '<S3>/Switch2' */

  /* DataTypeConversion: '<S3>/Data Type Conversion4' incorporates:
   *  UnitDelay: '<S3>/Unit Delay2'
   */
  PDU_AttCmd = PDU_DW.UnitDelay2_DSTATE_j;

  /* Switch: '<S3>/Switch13' incorporates:
   *  Constant: '<S3>/Constant24'
   */
  if (PDU_flgOverrideT3) {
    /* DataTypeConversion: '<S3>/Data Type Conversion5' incorporates:
     *  Constant: '<S3>/Constant25'
     */
    PDU_EfuseT3Cmd = PDU_manT3Cmd;
  }

  /* End of Switch: '<S3>/Switch13' */

  /* Switch: '<S3>/Switch14' incorporates:
   *  Constant: '<S3>/Constant26'
   */
  if (PDU_flgOverrideT5) {
    /* DataTypeConversion: '<S3>/Data Type Conversion6' incorporates:
     *  Constant: '<S3>/Constant27'
     */
    PDU_EfuseT5Cmd = PDU_manT5Cmd;
  }

  /* End of Switch: '<S3>/Switch14' */

  /* Switch: '<S3>/Switch15' incorporates:
   *  Constant: '<S3>/Constant28'
   */
  if (PDU_flgOverrideT1) {
    /* DataTypeConversion: '<S3>/Data Type Conversion7' incorporates:
     *  Constant: '<S3>/Constant29'
     */
    PDU_EfuseT1Cmd = PDU_manT1Cmd;
  }

  /* End of Switch: '<S3>/Switch15' */

  /* Switch: '<S3>/Switch16' incorporates:
   *  Constant: '<S3>/Constant30'
   *  S-Function (sfix_bitop): '<S3>/Bitwise AND2'
   *  Switch: '<S3>/Switch23'
   */
  if (PDU_flgOverrideT2) {
    /* DataTypeConversion: '<S3>/Data Type Conversion8' incorporates:
     *  Constant: '<S3>/Constant31'
     */
    PDU_EfuseT2Cmd = PDU_manT2Cmd;
  } else if ((rtb_Switch_i & 8U) != 0U) {
    /* Switch: '<S3>/Switch23' incorporates:
     *  DataTypeConversion: '<S3>/Data Type Conversion8'
     */
    PDU_EfuseT2Cmd = rtb_LogicalOperator14;
  }

  /* End of Switch: '<S3>/Switch16' */

  /* Switch: '<S3>/Switch17' incorporates:
   *  Constant: '<S3>/Constant32'
   *  Switch: '<S3>/Switch22'
   */
  if (PDU_flgOverrideT4) {
    /* DataTypeConversion: '<S3>/Data Type Conversion9' incorporates:
     *  Constant: '<S3>/Constant33'
     */
    PDU_EfuseT4Cmd = PDU_manT4Cmd;
  } else if (Switch7_tmp != 0U) {
    /* Switch: '<S3>/Switch22' incorporates:
     *  DataTypeConversion: '<S3>/Data Type Conversion9'
     */
    PDU_EfuseT4Cmd = rtb_LogicalOperator14;
  }

  /* Update for UnitDelay: '<S3>/Unit Delay1' */
  PDU_DW.UnitDelay1_DSTATE_g = PDU_flgMainPreRelayCommandCom;

  /* Update for UnitDelay: '<S3>/Unit Delay4' */
  PDU_DW.UnitDelay4_DSTATE_a = PDU_flgAttPreRelayCommandCom;

  /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/PDU_OUT'
   */
  /* DataTypeConversion: '<S4>/Data Type Conversion6' incorporates:
   *  Constant: '<S4>/Constant14'
   *  Inport: '<Root>/PDU_EfuseT1Current'
   *  RelationalOperator: '<S4>/Relational Operator4'
   */
  PDU_flgReverseState = (uint8_T)(PDU_EfuseT1Current > 1.0F);

  /* DataTypeConversion: '<S4>/Data Type Conversion5' incorporates:
   *  Constant: '<S4>/Constant10'
   *  Inport: '<Root>/PDU_EfuseT2Current'
   *  RelationalOperator: '<S4>/Relational Operator3'
   */
  PDU_flgBatHeatState = (uint8_T)(PDU_EfuseT2Current > 1.0F);

  /* DataTypeConversion: '<S4>/Data Type Conversion4' incorporates:
   *  Constant: '<S4>/Constant7'
   *  Inport: '<Root>/PDU_EfuseT4Current'
   *  RelationalOperator: '<S4>/Relational Operator2'
   */
  PDU_flgPTCState = (uint8_T)(PDU_EfuseT4Current > 1.0F);

  /* Switch: '<S4>/Switch8' */
  if (PDU_flgK7Adhesion) {
    /* DataTypeConversion: '<S4>/Data Type Conversion7' incorporates:
     *  Constant: '<S4>/Constant17'
     */
    PDU_flgMECUState = 2U;
  } else {
    /* DataTypeConversion: '<S4>/Data Type Conversion7' incorporates:
     *  Inport: '<Root>/PDU_flgK7StateRaw'
     */
    PDU_flgMECUState = PDU_flgK7StateRaw;
  }

  /* End of Switch: '<S4>/Switch8' */

  /* Switch: '<S4>/Switch10' */
  if (PDU_flgK8Adhesion) {
    /* DataTypeConversion: '<S4>/Data Type Conversion8' incorporates:
     *  Constant: '<S4>/Constant20'
     */
    PDU_flgACState = 2U;
  } else {
    /* DataTypeConversion: '<S4>/Data Type Conversion8' incorporates:
     *  Inport: '<Root>/PDU_flgK8StateRaw'
     */
    PDU_flgACState = PDU_flgK8StateRaw;
  }

  /* End of Switch: '<S4>/Switch10' */

  /* Switch: '<S4>/Switch12' */
  if (PDU_flgK9Adhesion) {
    /* DataTypeConversion: '<S4>/Data Type Conversion9' incorporates:
     *  Constant: '<S4>/Constant23'
     */
    PDU_flgK9State = 2U;
  } else {
    /* DataTypeConversion: '<S4>/Data Type Conversion9' incorporates:
     *  Inport: '<Root>/PDU_flgK9StateRaw'
     */
    PDU_flgK9State = PDU_flgK9StateRaw;
  }

  /* End of Switch: '<S4>/Switch12' */

  /* Switch: '<S4>/Switch1' */
  if (PDU_flgMainPosAdhesion) {
    /* DataTypeConversion: '<S4>/Data Type Conversion3' incorporates:
     *  Constant: '<S4>/Constant3'
     */
    PDU_flgMainPosState = 2U;
  } else {
    /* DataTypeConversion: '<S4>/Data Type Conversion3' incorporates:
     *  Inport: '<Root>/PDU_MainPosVoltage'
     *  RelationalOperator: '<S4>/Relational Operator1'
     */
    PDU_flgMainPosState = (uint8_T)(PDU_MainPosVoltage > rtb_Switch4_m0);
  }

  /* Switch: '<S4>/Switch4' */
  if (PDU_flgAttAdhesion) {
    /* DataTypeConversion: '<S4>/Data Type Conversion2' incorporates:
     *  Constant: '<S4>/Constant6'
     */
    PDU_flgAttState = 2U;
  } else {
    /* DataTypeConversion: '<S4>/Data Type Conversion2' incorporates:
     *  Inport: '<Root>/PDU_AttVoltage'
     *  RelationalOperator: '<S4>/Relational Operator'
     */
    PDU_flgAttState = (uint8_T)(PDU_AttVoltage > rtb_Switch4_m0);
  }

  /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of Outputs for RootInportFunctionCallGenerator generated from: '<Root>/PDU_ReMain' */
}

/* Model initialize function */
void PDU_initialize(void)
{
  {
    int32_T i;

    /* SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/PDU_ReMain' incorporates:
     *  SubSystem: '<Root>/PDU_REMAIN'
     */
    for (i = 0; i < 8; i++) {
      /* Start for Constant: '<S1>/Constant' */
      PDU_HCU3[i] = HCU_3[i];
    }

    /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/PDU_IN'
     */
    /* InitializeConditions for Delay: '<S13>/Delay' */
    PDU_DW.icLoad = true;

    /* InitializeConditions for Delay: '<S13>/Delay1' */
    PDU_DW.icLoad_p = true;

    /* InitializeConditions for Delay: '<S12>/Delay' */
    PDU_DW.icLoad_d = true;

    /* InitializeConditions for Delay: '<S12>/Delay1' */
    PDU_DW.icLoad_l = true;

    /* InitializeConditions for Delay: '<S11>/Delay' */
    PDU_DW.icLoad_m = true;

    /* InitializeConditions for Delay: '<S11>/Delay1' */
    PDU_DW.icLoad_g = true;

    /* InitializeConditions for Delay: '<S10>/Delay' */
    PDU_DW.icLoad_a = true;

    /* InitializeConditions for Delay: '<S10>/Delay1' */
    PDU_DW.icLoad_f = true;

    /* InitializeConditions for Delay: '<S8>/Delay' */
    PDU_DW.icLoad_mo = true;

    /* InitializeConditions for Delay: '<S8>/Delay1' */
    PDU_DW.icLoad_n = true;

    /* InitializeConditions for Delay: '<S7>/Delay' */
    PDU_DW.icLoad_c = true;

    /* InitializeConditions for Delay: '<S7>/Delay1' */
    PDU_DW.icLoad_gz = true;

    /* InitializeConditions for Delay: '<S9>/Delay' */
    PDU_DW.icLoad_nc = true;

    /* InitializeConditions for Delay: '<S9>/Delay1' */
    PDU_DW.icLoad_l3 = true;

    /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/PDU_MAIN'
     */
    /* SystemInitialize for S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
     *  SubSystem: '<S3>/PDU_FAULTMON'
     */
    /* InitializeConditions for UnitDelay: '<S44>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_m = true;

    /* InitializeConditions for UnitDelay: '<S44>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_b = true;

    /* InitializeConditions for UnitDelay: '<S45>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_mw = true;

    /* InitializeConditions for UnitDelay: '<S45>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_n = true;

    /* InitializeConditions for UnitDelay: '<S46>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_e = true;

    /* InitializeConditions for UnitDelay: '<S46>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_e = true;

    /* InitializeConditions for UnitDelay: '<S47>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_g = true;

    /* InitializeConditions for UnitDelay: '<S47>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_a = true;

    /* InitializeConditions for UnitDelay: '<S48>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_n = true;

    /* InitializeConditions for UnitDelay: '<S48>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_nr = true;

    /* InitializeConditions for UnitDelay: '<S49>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_c = true;

    /* InitializeConditions for UnitDelay: '<S49>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_i = true;

    /* InitializeConditions for UnitDelay: '<S50>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_cs = true;

    /* InitializeConditions for UnitDelay: '<S50>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_i1 = true;

    /* InitializeConditions for UnitDelay: '<S51>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_o = true;

    /* InitializeConditions for UnitDelay: '<S51>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_o = true;

    /* InitializeConditions for UnitDelay: '<S71>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_et = true;

    /* InitializeConditions for UnitDelay: '<S71>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_c = true;

    /* InitializeConditions for UnitDelay: '<S72>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_cm = true;

    /* InitializeConditions for UnitDelay: '<S72>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_h = true;

    /* InitializeConditions for UnitDelay: '<S73>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_b = true;

    /* InitializeConditions for UnitDelay: '<S73>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_m = true;

    /* InitializeConditions for UnitDelay: '<S74>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_p = true;

    /* InitializeConditions for UnitDelay: '<S74>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_f = true;

    /* InitializeConditions for UnitDelay: '<S75>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_pw = true;

    /* InitializeConditions for UnitDelay: '<S75>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_ch = true;

    /* InitializeConditions for UnitDelay: '<S43>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_f = true;

    /* InitializeConditions for UnitDelay: '<S43>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_nf = true;

    /* SystemInitialize for S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
     *  Chart: '<S3>/Chart'
     */
    /* SystemInitialize for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S3>/PDU_ATTPRECHARGE'
     */
    PDU_PDU_ATTPRECHARGE_Init(&PDU_DW.PDU_ATTPRECHARGE);

    /* SystemInitialize for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S3>/PDU_MAINPRECHARGE'
     */
    PDU_PDU_MAINPRECHARGE_Init(&PDU_DW.PDU_MAINPRECHARGE);

    /* SystemInitialize for S-Function (fcgen): '<S3>/Function-Call Generator' incorporates:
     *  SubSystem: '<S3>/PDU_SC'
     */
    /* SystemInitialize for Atomic SubSystem: '<S30>/PDU_SHUTDOWN' */
    /* InitializeConditions for UnitDelay: '<S96>/Unit Delay4' */
    PDU_DW.UnitDelay4_DSTATE_i = true;

    /* InitializeConditions for UnitDelay: '<S96>/Unit Delay5' */
    PDU_DW.UnitDelay5_DSTATE_j = true;

    /* End of SystemInitialize for SubSystem: '<S30>/PDU_SHUTDOWN' */
    /* End of SystemInitialize for S-Function (fcgen): '<S3>/Function-Call Generator' */
    /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' */
    /* End of SystemInitialize for RootInportFunctionCallGenerator generated from: '<Root>/PDU_ReMain' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
