/*
 * File: PDU.h
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

#ifndef RTW_HEADER_PDU_h_
#define RTW_HEADER_PDU_h_
#ifndef PDU_COMMON_INCLUDES_
#define PDU_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* PDU_COMMON_INCLUDES_ */

#include "PDU_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<S43>/SR_latch' */
typedef struct {
  boolean_T UnitDelay_DSTATE;          /* '<S54>/Unit Delay' */
} DW_SR_latch_PDU_T;

/* Block states (default storage) for system '<S3>/PDU_ATTPRECHARGE' */
typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<S32>/Unit Delay1' */
  boolean_T UnitDelay6_DSTATE;         /* '<S23>/Unit Delay6' */
  boolean_T UnitDelay2_DSTATE;         /* '<S32>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE;         /* '<S32>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE;         /* '<S32>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE;         /* '<S32>/Unit Delay5' */
  boolean_T UnitDelay_DSTATE;          /* '<S23>/Unit Delay' */
  DW_SR_latch_PDU_T SR_latch;          /* '<S32>/SR_latch' */
} DW_PDU_ATTPRECHARGE_PDU_T;

/* Block states (default storage) for system '<S3>/PDU_MAINPRECHARGE' */
typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<S86>/Unit Delay1' */
  boolean_T UnitDelay1_DSTATE_n;       /* '<S29>/Unit Delay1' */
  boolean_T UnitDelay2_DSTATE;         /* '<S86>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE;         /* '<S86>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE;         /* '<S86>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE;         /* '<S86>/Unit Delay5' */
  boolean_T UnitDelay_DSTATE;          /* '<S29>/Unit Delay' */
  DW_SR_latch_PDU_T SR_latch;          /* '<S86>/SR_latch' */
} DW_PDU_MAINPRECHARGE_PDU_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<S96>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_c;          /* '<S44>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_j;          /* '<S45>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_k;          /* '<S46>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_h;          /* '<S47>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_p;          /* '<S48>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_e;          /* '<S49>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_i;          /* '<S50>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_l;          /* '<S51>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_i1;         /* '<S71>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_o;          /* '<S72>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_oy;         /* '<S73>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_a;          /* '<S74>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_n;          /* '<S75>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_pr;         /* '<S43>/Unit Delay1' */
  real_T PDU_timeAttPreCharge;         /* '<S3>/Chart' */
  real_T PDU_timeMainPreCharge;        /* '<S3>/Chart' */
  real32_T UnitDelay_DSTATE;           /* '<S52>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_lr;       /* '<S52>/Unit Delay1' */
  real32_T UnitDelay2_DSTATE;          /* '<S52>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE;          /* '<S52>/Unit Delay3' */
  real32_T UnitDelay4_DSTATE;          /* '<S52>/Unit Delay4' */
  boolean_T UnitDelay1_DSTATE_g;       /* '<S3>/Unit Delay1' */
  boolean_T UnitDelay4_DSTATE_a;       /* '<S3>/Unit Delay4' */
  boolean_T UnitDelay2_DSTATE_j;       /* '<S3>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_d;       /* '<S3>/Unit Delay3' */
  boolean_T UnitDelay5_DSTATE;         /* '<S3>/Unit Delay5' */
  boolean_T UnitDelay6_DSTATE;         /* '<S3>/Unit Delay6' */
  boolean_T UnitDelay7_DSTATE;         /* '<S3>/Unit Delay7' */
  boolean_T UnitDelay8_DSTATE;         /* '<S3>/Unit Delay8' */
  boolean_T UnitDelay9_DSTATE;         /* '<S3>/Unit Delay9' */
  boolean_T UnitDelay10_DSTATE;        /* '<S3>/Unit Delay10' */
  boolean_T UnitDelay2_DSTATE_o;       /* '<S96>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_e;       /* '<S96>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_i;       /* '<S96>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_j;       /* '<S96>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_oa;      /* '<S44>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_b;       /* '<S44>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_m;       /* '<S44>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_b;       /* '<S44>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_p;       /* '<S45>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_n;       /* '<S45>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_mw;      /* '<S45>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_n;       /* '<S45>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_g;       /* '<S46>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_bq;      /* '<S46>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_e;       /* '<S46>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_e;       /* '<S46>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_a;       /* '<S47>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_a;       /* '<S47>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_g;       /* '<S47>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_a;       /* '<S47>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_on;      /* '<S48>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_l;       /* '<S48>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_n;       /* '<S48>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_nr;      /* '<S48>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_oaz;     /* '<S49>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_en;      /* '<S49>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_c;       /* '<S49>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_i;       /* '<S49>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_f;       /* '<S50>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_h;       /* '<S50>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_cs;      /* '<S50>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_i1;      /* '<S50>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_aw;      /* '<S51>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_bqz;     /* '<S51>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_o;       /* '<S51>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_o;       /* '<S51>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_d;       /* '<S71>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_g;       /* '<S71>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_et;      /* '<S71>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_c;       /* '<S71>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_fq;      /* '<S72>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_do;      /* '<S72>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_cm;      /* '<S72>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_h;       /* '<S72>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_i;       /* '<S73>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_li;      /* '<S73>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_b;       /* '<S73>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_m;       /* '<S73>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_c;       /* '<S74>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_dd;      /* '<S74>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_p;       /* '<S74>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_f;       /* '<S74>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_jy;      /* '<S75>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_hu;      /* '<S75>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_pw;      /* '<S75>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_ch;      /* '<S75>/Unit Delay5' */
  boolean_T UnitDelay2_DSTATE_gh;      /* '<S43>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_m;       /* '<S43>/Unit Delay3' */
  boolean_T UnitDelay4_DSTATE_f;       /* '<S43>/Unit Delay4' */
  boolean_T UnitDelay5_DSTATE_nf;      /* '<S43>/Unit Delay5' */
  boolean_T Delay_DSTATE;              /* '<S13>/Delay' */
  boolean_T Delay1_DSTATE;             /* '<S13>/Delay1' */
  boolean_T UnitDelay2_DSTATE_ds;      /* '<S13>/Unit Delay2' */
  boolean_T Delay_DSTATE_k;            /* '<S12>/Delay' */
  boolean_T Delay1_DSTATE_b;           /* '<S12>/Delay1' */
  boolean_T UnitDelay2_DSTATE_ono;     /* '<S12>/Unit Delay2' */
  boolean_T Delay_DSTATE_g;            /* '<S11>/Delay' */
  boolean_T Delay1_DSTATE_g;           /* '<S11>/Delay1' */
  boolean_T UnitDelay2_DSTATE_b;       /* '<S11>/Unit Delay2' */
  boolean_T Delay_DSTATE_o;            /* '<S10>/Delay' */
  boolean_T Delay1_DSTATE_m;           /* '<S10>/Delay1' */
  boolean_T UnitDelay2_DSTATE_cb;      /* '<S10>/Unit Delay2' */
  boolean_T Delay_DSTATE_c;            /* '<S8>/Delay' */
  boolean_T Delay1_DSTATE_i;           /* '<S8>/Delay1' */
  boolean_T UnitDelay2_DSTATE_gd;      /* '<S8>/Unit Delay2' */
  boolean_T Delay_DSTATE_d;            /* '<S7>/Delay' */
  boolean_T Delay1_DSTATE_k;           /* '<S7>/Delay1' */
  boolean_T UnitDelay2_DSTATE_bk;      /* '<S7>/Unit Delay2' */
  boolean_T Delay_DSTATE_gd;           /* '<S9>/Delay' */
  boolean_T Delay1_DSTATE_h;           /* '<S9>/Delay1' */
  boolean_T UnitDelay2_DSTATE_je;      /* '<S9>/Unit Delay2' */
  uint8_T is_c3_PDU;                   /* '<S3>/Chart' */
  uint8_T is_ACTIVE;                   /* '<S3>/Chart' */
  uint8_T is_active_c3_PDU;            /* '<S3>/Chart' */
  boolean_T icLoad;                    /* '<S13>/Delay' */
  boolean_T icLoad_p;                  /* '<S13>/Delay1' */
  boolean_T icLoad_d;                  /* '<S12>/Delay' */
  boolean_T icLoad_l;                  /* '<S12>/Delay1' */
  boolean_T icLoad_m;                  /* '<S11>/Delay' */
  boolean_T icLoad_g;                  /* '<S11>/Delay1' */
  boolean_T icLoad_a;                  /* '<S10>/Delay' */
  boolean_T icLoad_f;                  /* '<S10>/Delay1' */
  boolean_T icLoad_mo;                 /* '<S8>/Delay' */
  boolean_T icLoad_n;                  /* '<S8>/Delay1' */
  boolean_T icLoad_c;                  /* '<S7>/Delay' */
  boolean_T icLoad_gz;                 /* '<S7>/Delay1' */
  boolean_T icLoad_nc;                 /* '<S9>/Delay' */
  boolean_T icLoad_l3;                 /* '<S9>/Delay1' */
  DW_SR_latch_PDU_T SR_latch_h5;       /* '<S96>/SR_latch' */
  DW_PDU_MAINPRECHARGE_PDU_T PDU_MAINPRECHARGE;/* '<S3>/PDU_MAINPRECHARGE' */
  DW_PDU_ATTPRECHARGE_PDU_T PDU_ATTPRECHARGE;/* '<S3>/PDU_ATTPRECHARGE' */
  DW_SR_latch_PDU_T SR_latch_l;        /* '<S75>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_d;        /* '<S74>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_m;        /* '<S73>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_h;        /* '<S72>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_ne;       /* '<S71>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_f;        /* '<S51>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_e0;       /* '<S50>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_ny;       /* '<S49>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_el;       /* '<S48>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_eq;       /* '<S47>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_n;        /* '<S46>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_o;        /* '<S45>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch_e;        /* '<S44>/SR_latch' */
  DW_SR_latch_PDU_T SR_latch;          /* '<S43>/SR_latch' */
} DW_PDU_T;

/* Invariant block signals (default storage) */
typedef struct {
  const uint8_T BitwiseOperator1;      /* '<S35>/Bitwise Operator1' */
  const uint8_T BitwiseOperator3;      /* '<S35>/Bitwise Operator3' */
  const uint8_T BitwiseOperator2;      /* '<S35>/Bitwise Operator2' */
  const uint8_T BitwiseOperator3_g;    /* '<S36>/Bitwise Operator3' */
  const uint8_T BitwiseOperator3_f;    /* '<S37>/Bitwise Operator3' */
  const uint8_T BitwiseOperator3_d;    /* '<S38>/Bitwise Operator3' */
  const uint8_T BitwiseOperator3_fl;   /* '<S39>/Bitwise Operator3' */
  const uint8_T BitwiseOperator3_h;    /* '<S40>/Bitwise Operator3' */
  const uint8_T BitwiseOperator3_e;    /* '<S41>/Bitwise Operator3' */
  const uint8_T BitwiseOperator3_i;    /* '<S42>/Bitwise Operator3' */
} ConstB_PDU_T;

/* Real-time Model Data Structure */
struct tag_RTM_PDU_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_PDU_T PDU_DW;
extern const ConstB_PDU_T PDU_ConstB;  /* constant block i/o */

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T PDU_EfuseT3Current;    /* '<Root>/PDU_EfuseT3Current' */
extern real32_T PDU_EfuseT5Current;    /* '<Root>/PDU_EfuseT5Current' */
extern real32_T PDU_EfuseT1Current;    /* '<Root>/PDU_EfuseT1Current' */
extern real32_T PDU_EfuseT2Current;    /* '<Root>/PDU_EfuseT2Current' */
extern real32_T PDU_EfuseT4Current;    /* '<Root>/PDU_EfuseT4Current' */
extern boolean_T PDU_flgK9StateRaw;    /* '<Root>/PDU_flgK9StateRaw' */
extern real32_T PDU_EfuseTemp;         /* '<Root>/PDU_EfuseTemp' */
extern boolean_T PDU_EfuseT3CutFaultRead;/* '<Root>/PDU_EfuseT3CutFaultRead' */
extern boolean_T PDU_EfuseT5CutFaultRead;/* '<Root>/PDU_EfuseT5CutFaultRead' */
extern boolean_T PDU_EfuseT1CutFaultRead;/* '<Root>/PDU_EfuseT1CutFaultRead' */
extern boolean_T PDU_EfuseT2CutFaultRead;/* '<Root>/PDU_EfuseT2CutFaultRead' */
extern boolean_T PDU_EfuseT4CutFaultRead;/* '<Root>/PDU_EfuseT4CutFaultRead' */
extern boolean_T PDU_flgKL15;          /* '<Root>/PDU_flgKL15' */
extern real32_T PDU_BatteryVoltage;    /* '<Root>/PDU_BatteryVoltage' */
extern real32_T PDU_MainPosVoltage;    /* '<Root>/PDU_MainPosVoltage' */
extern boolean_T PDU_flgChargeCAN;     /* '<Root>/PDU_flgChargeCAN' */
extern real32_T PDU_AttVoltage;        /* '<Root>/PDU_AttVoltage' */
extern boolean_T PDU_flgK5StateRaw;    /* '<Root>/PDU_flgK5StateRaw' */
extern boolean_T PDU_flgK6StateRaw;    /* '<Root>/PDU_flgK6StateRaw' */
extern boolean_T PDU_flgK7StateRaw;    /* '<Root>/PDU_flgK7StateRaw' */
extern boolean_T PDU_flgK8StateRaw;    /* '<Root>/PDU_flgK8StateRaw' */
extern boolean_T PDU_flgK12StateRaw;   /* '<Root>/PDU_flgK12StateRaw' */
extern boolean_T PDU_flgOverVol;       /* '<Root>/PDU_flgOverVol' */
extern uint8_T PDU_HCU3[8];            /* '<S1>/Constant' */
extern uint8_T PDU_flgReverseState;    /* '<S4>/Data Type Conversion6' */
extern uint8_T PDU_flgBatHeatState;    /* '<S4>/Data Type Conversion5' */
extern uint8_T PDU_flgPTCState;        /* '<S4>/Data Type Conversion4' */
extern uint8_T PDU_flgMECUState;       /* '<S4>/Data Type Conversion7' */
extern uint8_T PDU_flgACState;         /* '<S4>/Data Type Conversion8' */
extern uint8_T PDU_flgK9State;         /* '<S4>/Data Type Conversion9' */
extern uint8_T PDU_flgMainPosState;    /* '<S4>/Data Type Conversion3' */
extern uint8_T PDU_flgAttState;        /* '<S4>/Data Type Conversion2' */
extern uint8_T PDU_state;              /* '<S3>/Chart' */
extern uint8_T PDU_EfuseFault;         /* '<S42>/Switch1' */
extern boolean_T PDU_K10Cmd;           /* '<S3>/Data Type Conversion' */
extern boolean_T PDU_K9Cmd;            /* '<S3>/Data Type Conversion1' */
extern boolean_T PDU_K4Cmd;            /* '<S3>/Data Type Conversion10' */
extern boolean_T PDU_ReserveCmd;       /* '<S3>/Data Type Conversion11' */
extern boolean_T PDU_PTCCmd;           /* '<S3>/Data Type Conversion12' */
extern boolean_T PDU_BatHeatCmd;       /* '<S3>/Data Type Conversion13' */
extern boolean_T PDU_MECUCmd;          /* '<S3>/Data Type Conversion14' */
extern boolean_T PDU_ACCmd;            /* '<S3>/Data Type Conversion15' */
extern boolean_T PDU_MainNegCmd;       /* '<S3>/Data Type Conversion16' */
extern boolean_T PDU_K3Cmd;            /* '<S3>/Data Type Conversion2' */
extern boolean_T PDU_MainPosCmd;       /* '<S3>/Data Type Conversion3' */
extern boolean_T PDU_AttCmd;           /* '<S3>/Data Type Conversion4' */
extern boolean_T PDU_EfuseT3Cmd;       /* '<S3>/Data Type Conversion5' */
extern boolean_T PDU_EfuseT5Cmd;       /* '<S3>/Data Type Conversion6' */
extern boolean_T PDU_EfuseT1Cmd;       /* '<S3>/Data Type Conversion7' */
extern boolean_T PDU_EfuseT2Cmd;       /* '<S3>/Data Type Conversion8' */
extern boolean_T PDU_EfuseT4Cmd;       /* '<S3>/Data Type Conversion9' */
extern boolean_T PDU_flgShutDown;      /* '<S95>/Logical Operator' */
extern boolean_T PDU_flgShutDown2Init; /* '<S96>/Logical Operator NOT1' */
extern boolean_T PDU_flgAttPreChargeCom;/* '<S93>/Logical Operator' */
extern boolean_T PDU_flgMainPreChargeCom;/* '<S92>/Logical Operator' */
extern boolean_T PDU_flgInitOK;        /* '<S91>/Logical Operator1' */
extern boolean_T PDU_flgDrive2Charge;  /* '<S90>/PDU_flgChargeCAN' */
extern boolean_T PDU_flgCharge2Init;   /* '<S89>/Logical Operator' */
extern boolean_T PDU_MainPreChargeTimeout;/* '<S3>/Chart' */
extern boolean_T PDU_AttPreChargeTimeout;/* '<S3>/Chart' */
extern boolean_T PDU_flgAttAdhesion;   /* '<S44>/Logical Operator NOT1' */
extern boolean_T PDU_flgMainPosAdhesion;/* '<S45>/Logical Operator NOT1' */
extern boolean_T PDU_flgK5Adhesion;    /* '<S46>/Logical Operator NOT1' */
extern boolean_T PDU_flgK6Adhesion;    /* '<S47>/Logical Operator NOT1' */
extern boolean_T PDU_flgK7Adhesion;    /* '<S48>/Logical Operator NOT1' */
extern boolean_T PDU_flgK8Adhesion;    /* '<S49>/Logical Operator NOT1' */
extern boolean_T PDU_flgK9Adhesion;    /* '<S50>/Logical Operator NOT1' */
extern boolean_T PDU_flgK12Adhesion;   /* '<S51>/Logical Operator NOT1' */
extern boolean_T PDU_flgRelayAdhesion; /* '<S27>/Logical Operator' */
extern boolean_T PDU_flgEfuseT3ConOverCut;/* '<S71>/Logical Operator NOT1' */
extern boolean_T PDU_flgEfuseT3InsOverCut;/* '<S52>/Logical Operator1' */
extern boolean_T PDU_flgEfuseT5ConOverCut;/* '<S72>/Logical Operator NOT1' */
extern boolean_T PDU_flgEfuseT5InsOverCut;/* '<S52>/Logical Operator3' */
extern boolean_T PDU_flgEfuseT1ConOverCut;/* '<S73>/Logical Operator NOT1' */
extern boolean_T PDU_flgEfuseT1InsOverCut;/* '<S52>/Logical Operator5' */
extern boolean_T PDU_flgEfuseT2ConOverCut;/* '<S74>/Logical Operator NOT1' */
extern boolean_T PDU_flgEfuseT2InsOverCut;/* '<S52>/Logical Operator7' */
extern boolean_T PDU_flgEfuseT4ConOverCut;/* '<S75>/Logical Operator NOT1' */
extern boolean_T PDU_flgEfuseT4InsOverCut;/* '<S52>/Logical Operator9' */
extern boolean_T PDU_flgEfuseOverCut;  /* '<S52>/Logical Operator10' */
extern boolean_T PDU_EfuseT3CutFault;  /* '<S27>/Logical Operator3' */
extern boolean_T PDU_EfuseT5CutFault;  /* '<S27>/Logical Operator4' */
extern boolean_T PDU_EfuseT1CutFault;  /* '<S27>/Logical Operator5' */
extern boolean_T PDU_EfuseT2CutFault;  /* '<S27>/Logical Operator6' */
extern boolean_T PDU_EfuseT4CutFault;  /* '<S27>/Logical Operator7' */
extern boolean_T PDU_EfuseCutFault;    /* '<S27>/Logical Operator19' */
extern boolean_T PDU_flgFault;         /* '<S27>/Logical Operator1' */
extern boolean_T PDU_flgEfuseOverTemp; /* '<S43>/Logical Operator NOT1' */
extern boolean_T HCU3ACCmdRaw;         /* '<S6>/Data Type Conversion17' */
extern boolean_T PDU_HCU3ACCmd;        /* '<S5>/Switch7' */
extern boolean_T HCU3MECUCmdRaw;       /* '<S6>/Data Type Conversion16' */
extern boolean_T PDU_HCU3MECUCmd;      /* '<S5>/Switch6' */
extern boolean_T HCU3PTCCmdRaw;        /* '<S6>/Data Type Conversion15' */
extern boolean_T PDU_HCU3PTCCmd;       /* '<S5>/Switch5' */
extern boolean_T HCU3AttCmdRaw;        /* '<S6>/Data Type Conversion14' */
extern boolean_T PDU_HCU3AttCmd;       /* '<S5>/Switch4' */
extern boolean_T HCU3BatHeatCmdRaw;    /* '<S6>/Data Type Conversion13' */
extern boolean_T PDU_HCU3BatHeatCmd;   /* '<S5>/Switch3' */
extern boolean_T HCU3MainNegCmdRaw;    /* '<S6>/Data Type Conversion12' */
extern boolean_T PDU_HCU3MainNegCmd;   /* '<S5>/Switch2' */
extern boolean_T HCU3MainPosCmdRaw;    /* '<S6>/Data Type Conversion11' */
extern boolean_T PDU_HCU3MainPosCmd;   /* '<S5>/Switch1' */
extern boolean_T PDU_flgMainPreRelayCommandCom;/* '<S29>/Logical Operator3' */
extern boolean_T PDU_flgAttPreRelayCommandCom;/* '<S23>/Logical Operator3' */

/* Model entry point functions */
extern void PDU_initialize(void);

/* Exported entry point function */
extern void PDU_ReMain(void);

/* Exported data declaration */

/* ConstVolatile memory section */
/* Declaration for custom storage class: ConstVolatile */
extern const volatile uint8_T HCU_3[8];/* Referenced by: '<S1>/Constant' */
extern const volatile uint32_T PDU_AdhesionThresh;/* Referenced by:
                                                   * '<S27>/Constant23'
                                                   * '<S27>/Constant26'
                                                   */
extern const volatile uint32_T PDU_AdhesionTimeThresh;/* Referenced by:
                                                       * '<S27>/Constant21'
                                                       * '<S27>/Constant25'
                                                       * '<S27>/Constant29'
                                                       * '<S27>/Constant31'
                                                       * '<S27>/Constant33'
                                                       * '<S27>/Constant35'
                                                       * '<S27>/Constant37'
                                                       * '<S27>/Constant39'
                                                       */
extern const volatile uint32_T PDU_ConOverCurrent;/* Referenced by:
                                                   * '<S52>/Constant'
                                                   * '<S52>/Constant10'
                                                   * '<S52>/Constant15'
                                                   * '<S52>/Constant20'
                                                   * '<S52>/Constant5'
                                                   */
extern const volatile real_T PDU_ConOverCutTime;/* Referenced by:
                                                 * '<S52>/Constant12'
                                                 * '<S52>/Constant17'
                                                 * '<S52>/Constant2'
                                                 * '<S52>/Constant22'
                                                 * '<S52>/Constant7'
                                                 */
extern const volatile uint8_T PDU_EfuseOverTempThresh;/* Referenced by: '<S27>/Constant1' */
extern const volatile uint32_T PDU_EfuseOverTempTime;/* Referenced by: '<S27>/Constant7' */
extern const volatile uint32_T PDU_InstantOverCurrent;/* Referenced by:
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
extern const volatile boolean_T PDU_OverrideHCU3ACCmd;/* Referenced by: '<S6>/Constant12' */
extern const volatile boolean_T PDU_OverrideHCU3AttCmd;/* Referenced by: '<S6>/Constant6' */
extern const volatile boolean_T PDU_OverrideHCU3BatHeatCmd;/* Referenced by: '<S6>/Constant4' */
extern const volatile boolean_T PDU_OverrideHCU3MECUCmd;/* Referenced by: '<S6>/Constant10' */
extern const volatile boolean_T PDU_OverrideHCU3MainNegCmd;/* Referenced by: '<S6>/Constant2' */
extern const volatile boolean_T PDU_OverrideHCU3MainPosCmd;/* Referenced by: '<S6>/Constant' */
extern const volatile boolean_T PDU_OverrideHCU3PTCCmd;/* Referenced by: '<S6>/Constant8' */
extern const volatile real32_T PDU_PreChargeFactor;/* Referenced by:
                                                    * '<S4>/Constant1'
                                                    * '<S4>/Constant11'
                                                    * '<S23>/Constant11'
                                                    * '<S29>/Constant11'
                                                    * '<S92>/Constant'
                                                    * '<S93>/Constant'
                                                    */
extern const volatile real_T PDU_TIME; /* Referenced by:
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
extern const volatile uint32_T PDU_WaitAttTime;/* Referenced by: '<S23>/Constant12' */
extern const volatile uint8_T PDU_WaitMainPosTime;/* Referenced by: '<S29>/Constant12' */
extern const volatile boolean_T PDU_flgACRelayCmdUseCal;/* Referenced by: '<S23>/Constant25' */
extern const volatile boolean_T PDU_flgBatHeatRelayCmdUseCal;/* Referenced by: '<S23>/Constant7' */
extern const volatile boolean_T PDU_flgMECURelayCmdUseCal;/* Referenced by: '<S23>/Constant23' */
extern const volatile boolean_T PDU_flgOverrideACRelay;/* Referenced by: '<S3>/Constant20' */
extern const volatile boolean_T PDU_flgOverrideAttRelay;/* Referenced by: '<S3>/Constant' */
extern const volatile boolean_T PDU_flgOverrideBatHeatRelay;/* Referenced by: '<S3>/Constant16' */
extern const volatile boolean_T PDU_flgOverrideK10Relay;/* Referenced by: '<S3>/Constant8' */
extern const volatile boolean_T PDU_flgOverrideK3Relay;/* Referenced by: '<S3>/Constant4' */
extern const volatile boolean_T PDU_flgOverrideK4Relay;/* Referenced by: '<S3>/Constant10' */
extern const volatile boolean_T PDU_flgOverrideK9Relay;/* Referenced by: '<S3>/Constant6' */
extern const volatile boolean_T PDU_flgOverrideMECURelay;/* Referenced by: '<S3>/Constant18' */
extern const volatile boolean_T PDU_flgOverrideMainNegRelay;/* Referenced by: '<S3>/Constant22' */
extern const volatile boolean_T PDU_flgOverrideMainPosRelay;/* Referenced by: '<S3>/Constant2' */
extern const volatile boolean_T PDU_flgOverridePTCRelay;/* Referenced by: '<S3>/Constant14' */
extern const volatile boolean_T PDU_flgOverrideReverseRelay;/* Referenced by: '<S3>/Constant12' */
extern const volatile boolean_T PDU_flgOverrideT1;/* Referenced by: '<S3>/Constant28' */
extern const volatile boolean_T PDU_flgOverrideT2;/* Referenced by: '<S3>/Constant30' */
extern const volatile boolean_T PDU_flgOverrideT3;/* Referenced by: '<S3>/Constant24' */
extern const volatile boolean_T PDU_flgOverrideT4;/* Referenced by: '<S3>/Constant32' */
extern const volatile boolean_T PDU_flgOverrideT5;/* Referenced by: '<S3>/Constant26' */
extern const volatile boolean_T PDU_flgPTCRelayCmdUseCal;/* Referenced by: '<S23>/Constant21' */
extern const volatile boolean_T PDU_flgReserveRelayCmdUseCal;/* Referenced by: '<S23>/Constant9' */
extern const volatile boolean_T PDU_manACCmd;/* Referenced by: '<S3>/Constant21' */
extern const volatile boolean_T PDU_manAttCmd;/* Referenced by: '<S3>/Constant1' */
extern const volatile boolean_T PDU_manBatHeatCmd;/* Referenced by: '<S3>/Constant17' */
extern const volatile boolean_T PDU_manK10Cmd;/* Referenced by: '<S3>/Constant9' */
extern const volatile boolean_T PDU_manK3Cmd;/* Referenced by: '<S3>/Constant5' */
extern const volatile boolean_T PDU_manK4Cmd;/* Referenced by: '<S3>/Constant11' */
extern const volatile boolean_T PDU_manK9Cmd;/* Referenced by: '<S3>/Constant7' */
extern const volatile boolean_T PDU_manMECUCmd;/* Referenced by: '<S3>/Constant19' */
extern const volatile boolean_T PDU_manMainNegCmd;/* Referenced by: '<S3>/Constant23' */
extern const volatile boolean_T PDU_manMainPosCmd;/* Referenced by: '<S3>/Constant3' */
extern const volatile boolean_T PDU_manPTCCmd;/* Referenced by: '<S3>/Constant15' */
extern const volatile boolean_T PDU_manReverseCmd;/* Referenced by: '<S3>/Constant13' */
extern const volatile boolean_T PDU_manT1Cmd;/* Referenced by: '<S3>/Constant29' */
extern const volatile boolean_T PDU_manT2Cmd;/* Referenced by: '<S3>/Constant31' */
extern const volatile boolean_T PDU_manT3Cmd;/* Referenced by: '<S3>/Constant25' */
extern const volatile boolean_T PDU_manT4Cmd;/* Referenced by: '<S3>/Constant33' */
extern const volatile boolean_T PDU_manT5Cmd;/* Referenced by: '<S3>/Constant27' */
extern const volatile uint8_T PDU_numEfuseFaultReact;/* Referenced by: '<S26>/Constant1' */
extern const volatile boolean_T PDU_orHCU3ACCmd;/* Referenced by: '<S6>/Constant13' */
extern const volatile boolean_T PDU_orHCU3AttCmd;/* Referenced by: '<S6>/Constant7' */
extern const volatile uint8_T PDU_orHCU3BatHeatCmd;/* Referenced by: '<S6>/Constant5' */
extern const volatile boolean_T PDU_orHCU3MECUCmd;/* Referenced by: '<S6>/Constant11' */
extern const volatile boolean_T PDU_orHCU3MainNegCmd;/* Referenced by: '<S6>/Constant3' */
extern const volatile boolean_T PDU_orHCU3MainPosCmd;/* Referenced by: '<S6>/Constant1' */
extern const volatile boolean_T PDU_orHCU3PTCCmd;/* Referenced by: '<S6>/Constant9' */
extern const volatile boolean_T PDU_overEfuseFaultReact;/* Referenced by: '<S26>/Constant' */
extern const volatile uint16_T PDU_reInitTime;/* Referenced by: '<S94>/Constant7' */

/* Real-time Model object */
extern RT_MODEL_PDU_T *const PDU_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S26>/Bitwise AND' : Unused code path elimination
 * Block '<S26>/Bitwise AND1' : Unused code path elimination
 * Block '<S26>/Bitwise AND2' : Unused code path elimination
 * Block '<S26>/Bitwise AND3' : Unused code path elimination
 * Block '<S26>/Constant10' : Unused code path elimination
 * Block '<S26>/Constant11' : Unused code path elimination
 * Block '<S26>/Constant15' : Unused code path elimination
 * Block '<S26>/Constant17' : Unused code path elimination
 * Block '<S26>/Constant18' : Unused code path elimination
 * Block '<S26>/Constant19' : Unused code path elimination
 * Block '<S26>/Constant20' : Unused code path elimination
 * Block '<S26>/Constant3' : Unused code path elimination
 * Block '<S26>/Constant4' : Unused code path elimination
 * Block '<S26>/Constant5' : Unused code path elimination
 * Block '<S26>/Constant6' : Unused code path elimination
 * Block '<S26>/Constant7' : Unused code path elimination
 * Block '<S26>/Switch14' : Unused code path elimination
 * Block '<S26>/Switch16' : Unused code path elimination
 * Block '<S26>/Switch3' : Unused code path elimination
 * Block '<S26>/Switch4' : Unused code path elimination
 * Block '<S26>/Switch5' : Unused code path elimination
 * Block '<S26>/Switch6' : Unused code path elimination
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion10' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion7' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion8' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S23>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S29>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S92>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S93>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S4>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S35>/Constant' : Unused code path elimination
 * Block '<S36>/Constant' : Unused code path elimination
 * Block '<S37>/Constant' : Unused code path elimination
 * Block '<S38>/Constant' : Unused code path elimination
 * Block '<S39>/Constant' : Unused code path elimination
 * Block '<S40>/Constant' : Unused code path elimination
 * Block '<S41>/Bitwise Operator1' : Unused code path elimination
 * Block '<S41>/Constant' : Unused code path elimination
 * Block '<S42>/Bitwise Operator1' : Unused code path elimination
 * Block '<S42>/Constant' : Unused code path elimination
 * Block '<S27>/Constant' : Unused code path elimination
 * Block '<S27>/Constant10' : Unused code path elimination
 * Block '<S27>/Constant12' : Unused code path elimination
 * Block '<S27>/Constant14' : Unused code path elimination
 * Block '<S27>/Constant16' : Unused code path elimination
 * Block '<S27>/Constant18' : Unused code path elimination
 * Block '<S27>/Constant22' : Unused code path elimination
 * Block '<S27>/Constant27' : Unused code path elimination
 * Block '<S27>/Constant4' : Unused code path elimination
 * Block '<S27>/Constant8' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PDU'
 * '<S1>'   : 'PDU/PDU_REMAIN'
 * '<S2>'   : 'PDU/PDU_REMAIN/PDU_IN'
 * '<S3>'   : 'PDU/PDU_REMAIN/PDU_MAIN'
 * '<S4>'   : 'PDU/PDU_REMAIN/PDU_OUT'
 * '<S5>'   : 'PDU/PDU_REMAIN/PDU_IN/Subsystem'
 * '<S6>'   : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/HCU3_RAW'
 * '<S7>'   : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory1'
 * '<S8>'   : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory2'
 * '<S9>'   : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory213'
 * '<S10>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory3'
 * '<S11>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory4'
 * '<S12>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory5'
 * '<S13>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory6'
 * '<S14>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory1/DocBlockDescription'
 * '<S15>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory2/DocBlockDescription'
 * '<S16>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory213/DocBlockDescription'
 * '<S17>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory3/DocBlockDescription'
 * '<S18>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory4/DocBlockDescription'
 * '<S19>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory5/DocBlockDescription'
 * '<S20>'  : 'PDU/PDU_REMAIN/PDU_IN/Subsystem/IP_Diag_RisingEdgeMemory6/DocBlockDescription'
 * '<S21>'  : 'PDU/PDU_REMAIN/PDU_MAIN/Chart'
 * '<S22>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_ATTON'
 * '<S23>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_ATTPRECHARGE'
 * '<S24>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_CHARGE'
 * '<S25>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_DRIVE'
 * '<S26>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULT'
 * '<S27>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON'
 * '<S28>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_INIT'
 * '<S29>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_MAINPRECHARGE'
 * '<S30>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC'
 * '<S31>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SHUTDOWN'
 * '<S32>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_ATTPRECHARGE/Stopwatch1'
 * '<S33>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_ATTPRECHARGE/Stopwatch1/DocBlockDescription'
 * '<S34>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_ATTPRECHARGE/Stopwatch1/SR_latch'
 * '<S35>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite'
 * '<S36>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite1'
 * '<S37>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite2'
 * '<S38>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite3'
 * '<S39>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite4'
 * '<S40>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite5'
 * '<S41>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite6'
 * '<S42>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/BitWrite7'
 * '<S43>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch1'
 * '<S44>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch2'
 * '<S45>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch3'
 * '<S46>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch4'
 * '<S47>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch5'
 * '<S48>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch6'
 * '<S49>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch7'
 * '<S50>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch8'
 * '<S51>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch9'
 * '<S52>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem'
 * '<S53>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch1/DocBlockDescription'
 * '<S54>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch1/SR_latch'
 * '<S55>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch2/DocBlockDescription'
 * '<S56>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch2/SR_latch'
 * '<S57>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch3/DocBlockDescription'
 * '<S58>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch3/SR_latch'
 * '<S59>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch4/DocBlockDescription'
 * '<S60>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch4/SR_latch'
 * '<S61>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch5/DocBlockDescription'
 * '<S62>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch5/SR_latch'
 * '<S63>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch6/DocBlockDescription'
 * '<S64>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch6/SR_latch'
 * '<S65>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch7/DocBlockDescription'
 * '<S66>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch7/SR_latch'
 * '<S67>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch8/DocBlockDescription'
 * '<S68>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch8/SR_latch'
 * '<S69>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch9/DocBlockDescription'
 * '<S70>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Stopwatch9/SR_latch'
 * '<S71>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch'
 * '<S72>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch1'
 * '<S73>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch2'
 * '<S74>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch3'
 * '<S75>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch4'
 * '<S76>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch/DocBlockDescription'
 * '<S77>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch/SR_latch'
 * '<S78>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch1/DocBlockDescription'
 * '<S79>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch1/SR_latch'
 * '<S80>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch2/DocBlockDescription'
 * '<S81>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch2/SR_latch'
 * '<S82>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch3/DocBlockDescription'
 * '<S83>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch3/SR_latch'
 * '<S84>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch4/DocBlockDescription'
 * '<S85>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_FAULTMON/Subsystem/Stopwatch4/SR_latch'
 * '<S86>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_MAINPRECHARGE/Stopwatch1'
 * '<S87>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_MAINPRECHARGE/Stopwatch1/DocBlockDescription'
 * '<S88>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_MAINPRECHARGE/Stopwatch1/SR_latch'
 * '<S89>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_ACTIVE_CHARGE'
 * '<S90>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_ACTIVE_DRIVE'
 * '<S91>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_INIT'
 * '<S92>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_PRECHARGE'
 * '<S93>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_PRECHARGE1'
 * '<S94>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_SHUTDOWN'
 * '<S95>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PowerDown'
 * '<S96>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_SHUTDOWN/Stopwatch'
 * '<S97>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_SHUTDOWN/Stopwatch/DocBlockDescription'
 * '<S98>'  : 'PDU/PDU_REMAIN/PDU_MAIN/PDU_SC/PDU_SHUTDOWN/Stopwatch/SR_latch'
 */
#endif                                 /* RTW_HEADER_PDU_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
