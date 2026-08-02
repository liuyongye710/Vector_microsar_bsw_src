#ifndef RTW_HEADER_SWC_SCF_IG_FQ_h_
#define RTW_HEADER_SWC_SCF_IG_FQ_h_
#include <math.h>
#ifndef SWC_SCF_IG_FQ_COMMON_INCLUDES_
#define SWC_SCF_IG_FQ_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_SCF_IG_FQ_types.h"

#include "model_reference_types.h"

#ifndef SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  uint8_T RestsSingal;
  uint8_T ZReset;
} B_SWC_SCF_IG_FQ_c_T;

#endif

#ifndef SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  uint32_T presentTicks;
  uint32_T elapsedTicks;
  uint32_T previousTicks;
  uint16_T temporalCounter_i1;
  uint16_T temporalCounter_i2;
  uint8_T is_active_c1_SWC_SCF_IG_FQ;
  uint8_T is_c1_SWC_SCF_IG_FQ;
  uint8_T is_Drv;
  uint8_T is_Action;
  uint8_T cnt;
} DW_SWC_SCF_IG_FQ_f_T;

#endif

#ifndef SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_SCF_IG_FQ_T {
  const char_T **errorStatus;
  struct {
    int_T mdlref_TriggerTID;
  } Timing;
};

#endif

#ifndef SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_SCF_IG_FQ_T rtm;
} MdlrefDW_SWC_SCF_IG_FQ_T;

#endif

extern uint8_T SCF_stGateDrv_FQ;
extern uint8_T Var_stPWMmode_AfEmrgncy_u8_FQ;
extern uint8_T SCF_stSysCtl_FQ;
extern uint8_T SCF_stPreDrvCtl_FQ;
extern uint8_T SCF_stSys_FQ;
extern uint8_T SCF_stDisChg_FQ;
extern uint8_T SCF_stDrvCtl_FQ;
extern uint8_T SCF_stModeReqToTdc_FQ;
extern uint8_T SCF_stMotor_state_FQ;
extern boolean_T SCF_flginitPI_FQ;
extern boolean_T SCF_flgUdcLowToTpc_FQ;
extern boolean_T Var_flgEnMosSwitch_b_FQ;
extern boolean_T SCF_flgDataStrgBgnToBsw_FQ;
extern boolean_T SCF_flgEnDchaToMc_FQ;
extern boolean_T SCF_LwPwrDwn_FQ;
extern void SWC_SCF_IG_FQ_Init(void);
extern void SWC_SCF_IG_FQ_Enable(void);
extern void SWC_SCF_IG_FQ_Disable(void);
extern void SWC_SCF_IG_FQ(const boolean_T *rtu_HSPF_BUS_HSPF_bt15, const
  real32_T *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const boolean_T *rtu_PDU_stMainRly,
  const boolean_T *rtu_PDU_stPreChgRly, const real32_T *rtu_Rdc_nWoFlt, const
  boolean_T *rtu_flg_ov, const boolean_T *rtu_flg_oc, boolean_T
  *rty_SCF_BUS_SCF_flgDataStrgBgnT, uint8_T *rty_SCF_BUS_SCF_stSysCtl, uint8_T
  *rty_SCF_BUS_SCF_stGateDrv, uint8_T *rty_SCF_BUS_SCF_stDrvCtl, uint8_T
  *rty_SCF_BUS_SCF_stDisChg, uint8_T *rty_SCF_BUS_SCF_stPreDrvCtl, boolean_T
  *rty_SCF_BUS_SCF_flginitPI, boolean_T *rty_SCF_BUS_SCF_flgEnDchaToMc, uint8_T *
  rty_SCF_BUS_SCF_stSys, uint8_T *rty_SCF_BUS_SCF_stModeReqToTdc, uint8_T
  *rty_SCF_BUS_SCF_stPwmMode, boolean_T *rty_SCF_BUS_SCF_flgUdcLowToTpc,
  boolean_T *rty_SCF_BUS_SCF_bHvReady_write, boolean_T
  *rty_SCF_BUS_SCF_flgEmgReqInvDch, boolean_T *rty_SCF_BUS_SCF_flgActvDcha,
  uint8_T *rty_SCF_BUS_SCF_stFFAction, uint8_T *rty_SCF_BUS_SCF_FIM_ReqFailrMod,
  boolean_T *rty_SCF_BUS_SCF_LwPwrDwn, uint8_T *rty_SCF_BUS_SCF_stMotor_state,
  uint8_T *rty_SCF_BUS_SCF_flginitEn_Nctl, uint8_T *rty_SCF_BUS_SCF_flgZReset);
extern void SWC_SCF_IG_FQ_initialize(const char_T **rt_errorStatus, const
  rtTimingBridge *timingBridge, int_T mdlref_TID0, int_T mdlref_TriggerTID);

#pragma section ".CAL_CONST"

extern const volatile uint8_T CAL_SCF_stModeReq_b_FQ;
extern const volatile real32_T CAL_TpcSmp_ThresOverSpd_f32_FQ;

#pragma section

#ifndef SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_SCF_IG_FQ_T SWC_SCF_IG_FQ_MdlrefDW;

#endif

#ifndef SWC_SCF_IG_FQ_MDLREF_HIDE_CHILD_

extern B_SWC_SCF_IG_FQ_c_T SWC_SCF_IG_FQ_B;
extern DW_SWC_SCF_IG_FQ_f_T SWC_SCF_IG_FQ_DW;

#endif
#endif

