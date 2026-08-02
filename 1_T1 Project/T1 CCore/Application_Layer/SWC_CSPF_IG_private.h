#ifndef RTW_HEADER_SWC_CSPF_IG_private_h_
#define RTW_HEADER_SWC_CSPF_IG_private_h_
#include "rtwtypes.h"

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

extern const ConstB_SWC_CSPF_IG_h_T SWC_CSPF_IG_ConstB;

#endif

