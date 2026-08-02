#ifndef RTW_HEADER_SWC_MCF_IG_private_h_
#define RTW_HEADER_SWC_MCF_IG_private_h_
#include "rtwtypes.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
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

extern const real32_T rtCP_pooled_lRa8o5hRGBX2[4096];
extern const real32_T rtCP_pooled_7EBUHCewpktf[4096];
extern const real32_T rtCP_pooled_Bh75GlUU3XVK[6];
extern const real32_T rtCP_pooled_AF8s6d0pwfT5[6];
extern const real32_T rtCP_pooled_HX74WORaU2Uv[6];
extern const real32_T rtCP_pooled_d0Rw9Fa8SJyj[6];
extern const real32_T rtCP_pooled_1mfAfq82KMlL[7168];
extern const real32_T rtCP_pooled_I3FPh32EaiBC[1024];
extern const real32_T rtCP_pooled_SWe1yiAh0Q0i[7];
extern const real32_T rtCP_pooled_WZltfjIEz15y[1024];
extern const uint32_T rtCP_pooled_ILBMoq4R8vx2[2];
extern const uint16_T rtCP_pooled_5tL1grgvQpCw[1025];

#define rtCP_Constant_Value_m          rtCP_pooled_lRa8o5hRGBX2
#define rtCP_McFwc_SinTable_table      rtCP_pooled_7EBUHCewpktf
#define rtCP_DirectLookupTablenD_table rtCP_pooled_Bh75GlUU3XVK
#define rtCP_DirectLookupTablenD1_table rtCP_pooled_AF8s6d0pwfT5
#define rtCP_DirectLookupTablenD2_table rtCP_pooled_HX74WORaU2Uv
#define rtCP_DirectLookupTablenD3_table rtCP_pooled_d0Rw9Fa8SJyj
#define rtCP_LookupCosTable_table      rtCP_pooled_lRa8o5hRGBX2
#define rtCP_LookupCosineTab_table     rtCP_pooled_lRa8o5hRGBX2
#define rtCP_LookupSineTab_table       rtCP_pooled_7EBUHCewpktf
#define rtCP_LookupSinTable_table      rtCP_pooled_7EBUHCewpktf
#define rtCP_OmTable_tableData         rtCP_pooled_1mfAfq82KMlL
#define rtCP_OmTable_bp01Data          rtCP_pooled_I3FPh32EaiBC
#define rtCP_OmTable_bp02Data          rtCP_pooled_SWe1yiAh0Q0i
#define rtCP_Constant_Value_lx         rtCP_pooled_WZltfjIEz15y
#define rtCP_LookupCosTable_table_b    rtCP_pooled_lRa8o5hRGBX2
#define rtCP_LookupSinTable_table_a    rtCP_pooled_7EBUHCewpktf
#define rtCP_LookupCosTable_table_g    rtCP_pooled_lRa8o5hRGBX2
#define rtCP_LookupSinTable_table_e    rtCP_pooled_7EBUHCewpktf
#define rtCP_OmTable_maxIndex          rtCP_pooled_ILBMoq4R8vx2
#define rtCP_DirectLookupTablenD_table_ rtCP_pooled_5tL1grgvQpCw
#define rtCP_DirectLookupTablenD_tabl_j rtCP_pooled_5tL1grgvQpCw
#endif

