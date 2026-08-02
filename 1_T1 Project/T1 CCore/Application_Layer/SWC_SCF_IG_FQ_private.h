#ifndef RTW_HEADER_SWC_SCF_IG_FQ_private_h_
#define RTW_HEADER_SWC_SCF_IG_FQ_private_h_
#include "rtwtypes.h"
#include "model_reference_types.h"

#ifndef rtmIsSampleHit
#define rtmIsSampleHit(sti, tid)       (SWC_SCF_IG_FQ_TimingBrdg->taskCounter[SWC_SCF_IG_FQ_GlobalTID[sti]] == 0)
#endif

#ifndef rtmGetClockTick0
#define rtmGetClockTick0(rtm)          ( *((SWC_SCF_IG_FQ_TimingBrdg->clockTick[(rtm)->Timing.mdlref_TriggerTID])) )
#endif

#ifndef rtmGetClockTickH0
#define rtmGetClockTickH0(rtm)         ( *(SWC_SCF_IG_FQ_TimingBrdg->clockTickH[(rtm)->Timing.mdlref_TriggerTID]) )
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT()                      (*(SWC_SCF_IG_FQ_TimingBrdg->taskTime[0]))
#endif

extern int_T SWC_SCF_IG_FQ_GlobalTID[1];
extern const rtTimingBridge *SWC_SCF_IG_FQ_TimingBrdg;

#endif

