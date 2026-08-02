#ifndef RTW_HEADER_SWC_BCC_IG_private_h_
#define RTW_HEADER_SWC_BCC_IG_private_h_
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

extern const real32_T rtCP_pooled_L1EYruj6sQ1k[68];
extern const real32_T rtCP_pooled_DqHckVIEEV7X[17];
extern const real32_T rtCP_pooled_6GvjCyock7wm[4];
extern const real32_T rtCP_pooled_q5ZyQfGjIXKJ[68];
extern const real32_T rtCP_pooled_IAP8ccyn3DOT[17];
extern const uint32_T rtCP_pooled_nyEQAg4QO5wu[2];

#define rtCP_uDLookupTable_tableData   rtCP_pooled_L1EYruj6sQ1k
#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_DqHckVIEEV7X
#define rtCP_uDLookupTable_bp02Data    rtCP_pooled_6GvjCyock7wm
#define rtCP_uDLookupTable1_tableData  rtCP_pooled_q5ZyQfGjIXKJ
#define rtCP_uDLookupTable1_bp01Data   rtCP_pooled_IAP8ccyn3DOT
#define rtCP_uDLookupTable1_bp02Data   rtCP_pooled_6GvjCyock7wm
#define rtCP_uDLookupTable_maxIndex    rtCP_pooled_nyEQAg4QO5wu
#define rtCP_uDLookupTable1_maxIndex   rtCP_pooled_nyEQAg4QO5wu

extern const ConstB_SWC_BCC_IG_h_T SWC_BCC_IG_ConstB;

#endif

