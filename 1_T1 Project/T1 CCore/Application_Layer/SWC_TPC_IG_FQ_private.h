#ifndef RTW_HEADER_SWC_TPC_IG_FQ_private_h_
#define RTW_HEADER_SWC_TPC_IG_FQ_private_h_
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

extern const real32_T rtCP_pooled_ql5zQ4h8iTSR[561];
extern const real32_T rtCP_pooled_WDXHwAzWNUP4[33];
extern const real32_T rtCP_pooled_Yv73sTDj9iJR[17];
extern const uint32_T rtCP_pooled_g1xfL3KrJTm2[2];
extern const uint32_T rtCP_pooled_My5wKaBX7VxP[2];
extern const uint32_T rtCP_pooled_UBlgixWDJp3V[2];
extern const uint32_T rtCP_pooled_FId2DsqWqW8M[2];

#define rtCP_uDLookupTable_tableData   rtCP_pooled_ql5zQ4h8iTSR
#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_WDXHwAzWNUP4
#define rtCP_uDLookupTable_bp02Data    rtCP_pooled_Yv73sTDj9iJR
#define rtCP_uDLookupTable_tableData_b rtCP_pooled_ql5zQ4h8iTSR
#define rtCP_uDLookupTable_bp01Data_p  rtCP_pooled_WDXHwAzWNUP4
#define rtCP_uDLookupTable_bp02Data_a  rtCP_pooled_Yv73sTDj9iJR
#define rtCP_uDLookupTable_maxIndex    rtCP_pooled_g1xfL3KrJTm2
#define rtCP_uDLookupTable_maxIndex_i  rtCP_pooled_g1xfL3KrJTm2
#define rtCP_GenExCTable_maxIndex      rtCP_pooled_My5wKaBX7VxP
#define rtCP_ElecExCTable_maxIndex     rtCP_pooled_UBlgixWDJp3V
#define rtCP_CoolantFlow2L_maxIndex    rtCP_pooled_FId2DsqWqW8M
#define rtCP_CoolantFlow4L_maxIndex    rtCP_pooled_FId2DsqWqW8M
#define rtCP_CoolantFlow6L_maxIndex    rtCP_pooled_FId2DsqWqW8M
#endif

