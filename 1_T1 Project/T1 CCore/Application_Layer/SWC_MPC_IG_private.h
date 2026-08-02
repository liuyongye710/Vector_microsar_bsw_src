#ifndef RTW_HEADER_SWC_MPC_IG_private_h_
#define RTW_HEADER_SWC_MPC_IG_private_h_
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

extern const real32_T rtCP_pooled_Dh95aD0Am6kv[361];
extern const real32_T rtCP_pooled_37MDcRPbVHws[19];
extern const real32_T rtCP_pooled_9Q2hLrDpFiAh[361];
extern const real32_T rtCP_pooled_ljuOUscWsJAs[23];
extern const real32_T rtCP_pooled_xuUWXdcdSa4I[23];
extern const uint32_T rtCP_pooled_yqMFYTK1Tdk5[2];
extern const uint32_T rtCP_pooled_15wuF2dardNf[2];
extern const uint32_T rtCP_pooled_BoorZ2pYYSMY[2];
extern const uint32_T rtCP_pooled_A3Si0v18G9NS[2];
extern const uint32_T rtCP_pooled_FdMmXpDiCfxO[2];

#define rtCP_uD_LqTable_tableData      rtCP_pooled_Dh95aD0Am6kv
#define rtCP_uD_LqTable_bp01Data       rtCP_pooled_37MDcRPbVHws
#define rtCP_uD_LqTable_bp02Data       rtCP_pooled_37MDcRPbVHws
#define rtCP_uD_LdTable_tableData      rtCP_pooled_9Q2hLrDpFiAh
#define rtCP_uD_LdTable_bp01Data       rtCP_pooled_37MDcRPbVHws
#define rtCP_uD_LdTable_bp02Data       rtCP_pooled_37MDcRPbVHws
#define rtCP_Rs_TempStr_Tab_tableData  rtCP_pooled_ljuOUscWsJAs
#define rtCP_Rs_TempStr_Tab_bp01Data   rtCP_pooled_xuUWXdcdSa4I
#define rtCP_uD_LqTable_maxIndex       rtCP_pooled_yqMFYTK1Tdk5
#define rtCP_LdSubLqMot_maxIndex       rtCP_pooled_15wuF2dardNf
#define rtCP_LdSubLqGen_maxIndex       rtCP_pooled_15wuF2dardNf
#define rtCP_uD_LdTable_maxIndex       rtCP_pooled_yqMFYTK1Tdk5
#define rtCP_MTPV_Mot_maxIndex         rtCP_pooled_BoorZ2pYYSMY
#define rtCP_MTPV_Gen_maxIndex         rtCP_pooled_BoorZ2pYYSMY
#define rtCP_MPC_isdFFTable_isd_maxInde rtCP_pooled_A3Si0v18G9NS
#define rtCP_VFTable_maxIndex          rtCP_pooled_FdMmXpDiCfxO
#endif

