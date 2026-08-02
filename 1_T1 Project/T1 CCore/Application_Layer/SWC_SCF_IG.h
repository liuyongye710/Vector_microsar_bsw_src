#ifndef RTW_HEADER_SWC_SCF_IG_h_
#define RTW_HEADER_SWC_SCF_IG_h_
#include <math.h>
#ifndef SWC_SCF_IG_COMMON_INCLUDES_
#define SWC_SCF_IG_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "SWC_SCF_IG_types.h"

#include "model_reference_types.h"

#ifndef SWC_SCF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  uint32_T presentTicks;
  uint32_T elapsedTicks;
  uint32_T previousTicks;
  uint16_T temporalCounter_i1;
  uint8_T is_active_c1_SWC_SCF_IG;
  uint8_T is_c1_SWC_SCF_IG;
  uint8_T is_Drv;
} DW_SWC_SCF_IG_f_T;

#endif

#ifndef SWC_SCF_IG_MDLREF_HIDE_CHILD_

struct tag_RTM_SWC_SCF_IG_T {
  const char_T **errorStatus;
  struct {
    int_T mdlref_TriggerTID;
  } Timing;
};

#endif

#ifndef SWC_SCF_IG_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SWC_SCF_IG_T rtm;
} MdlrefDW_SWC_SCF_IG_T;

#endif

extern uint8_T SCF_stGateDrv;
extern uint8_T Var_stPWMmode_AfEmrgncy_u8;
extern uint8_T SCF_stSysCtl;
extern uint8_T SCF_stPreDrvCtl;
extern uint8_T SCF_stSys;
extern uint8_T SCF_stDisChg;
extern uint8_T SCF_stDrvCtl;
extern uint8_T SCF_stModeReqToTdc;
extern boolean_T SCF_flginitPI;
extern boolean_T SCF_flgEnDchaToMc;
extern boolean_T SCF_flgUdcLowToTpc;
extern boolean_T SCF_flgDataStrgBgnToBsw;
extern boolean_T SCF_LwPwrDwn;
extern void SWC_SCF_IG_Init(void);
extern void SWC_SCF_IG_Enable(void);
extern void SWC_SCF_IG_Disable(void);
extern void SWC_SCF_IG(const boolean_T *rtu_HSPF_BUS_HSPF_bt15, const real32_T
  *rtu_HSPF_BUS_HSPF_uDcLnkSlowFlt, const boolean_T *rtu_PDU_stMainRly, const
  boolean_T *rtu_PDU_stPreChgRly, const uint8_T *rtu_CSPF_BUS_Calc_mod_HCUReqMot,
  const boolean_T *rtu_CSPF_BUS_Calc_st_ActvDischg, const real32_T
  *rtu_Rdc_nWoFlt, const boolean_T *rtu_flg_ov, const boolean_T *rtu_flg_oc,
  boolean_T *rty_SCF_BUS_SCF_flgDataStrgBgnT, uint8_T *rty_SCF_BUS_SCF_stSysCtl,
  uint8_T *rty_SCF_BUS_SCF_stGateDrv, uint8_T *rty_SCF_BUS_SCF_stDrvCtl, uint8_T
  *rty_SCF_BUS_SCF_stDisChg, uint8_T *rty_SCF_BUS_SCF_stPreDrvCtl, boolean_T
  *rty_SCF_BUS_SCF_flginitPI, boolean_T *rty_SCF_BUS_SCF_flgEnDchaToMc, uint8_T *
  rty_SCF_BUS_SCF_stSys, uint8_T *rty_SCF_BUS_SCF_stModeReqToTdc, uint8_T
  *rty_SCF_BUS_SCF_stPwmMode, boolean_T *rty_SCF_BUS_SCF_flgUdcLowToTpc,
  boolean_T *rty_SCF_BUS_SCF_bHvReady_write, boolean_T
  *rty_SCF_BUS_SCF_flgEmgReqInvDch, boolean_T *rty_SCF_BUS_SCF_flgActvDcha,
  uint8_T *rty_SCF_BUS_SCF_stFFAction, uint8_T *rty_SCF_BUS_SCF_FIM_ReqFailrMod,
  boolean_T *rty_SCF_BUS_SCF_LwPwrDwn);
extern void SWC_SCF_IG_initialize(const char_T **rt_errorStatus, const
  rtTimingBridge *timingBridge, int_T mdlref_TID0, int_T mdlref_TriggerTID);

#pragma section ".CAL_CONST"

extern const volatile real32_T CAL_TpcSmp_ThresOverSpd_f32;

#pragma section

#ifndef SWC_SCF_IG_MDLREF_HIDE_CHILD_

extern MdlrefDW_SWC_SCF_IG_T SWC_SCF_IG_MdlrefDW;

#endif

#ifndef SWC_SCF_IG_MDLREF_HIDE_CHILD_

extern DW_SWC_SCF_IG_f_T SWC_SCF_IG_DW;

#endif
#endif

