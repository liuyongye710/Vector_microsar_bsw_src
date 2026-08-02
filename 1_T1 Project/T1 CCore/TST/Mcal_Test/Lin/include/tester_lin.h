
#ifndef TESTER_LIN_H
#define TESTER_LIN_H

#include "Lin.h"

typedef void (*Linfunc)(const Lin_ConfigType *LinDriverConfig);
typedef struct _LinfuncMachine
{
    char *name;
    Linfunc linfunc;
}LinfuncMachine;
#define IIN_TEST  0
FUNC(void, LIN_CODE) Lin_LLD_Init_IrqIsrEnable(void);
void LIN_GPT_Callback_10ms_Function(void);
void LIN_GPT_Callback_20ms_Function(void);
void LIN_GPT_Callback_30ms_Function(void);
void TSC_Lin_0027(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0028(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0029(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0030(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0031(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0032(const Lin_ConfigType *LinDriverConfig);
#if (LIN_VERSION_INFO_API == STD_ON)
void TSC_Lin_0033(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0034(const Lin_ConfigType *LinDriverConfig);
#endif
void TSC_Lin_0035(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0036(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0037(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0038(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0039(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0040(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0041(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0042(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0043(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0044(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0045(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0046(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0047(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0048(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0049(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0050(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0051(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0052_0053(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0054(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0055(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0056(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0057(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0058(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0059_0065(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0066_0071(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0072_0079(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0080_0084(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0085_0092(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0093_0098(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0099_0106(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0107_0112(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0118_0125(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0126_0130(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0131_0138(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0139_0143(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0144_0146(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0147_0152(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0153_0157(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0158_0166(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0167_0172(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0173_0180(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0181_0185(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0188_0195(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0196_0200(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0201_0208(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0209_0213(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0214_0221(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0222_0226(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0227_0234(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0235_0239(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0240_0247(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0248_0252(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0253_0260(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0261_0265(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0266_0273(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0274_0278(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0279_0286(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0287_0291(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0292_0299(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0300_0304(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0305_0312(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0313_0317(const Lin_ConfigType *LinDriverConfig);
void TSC_Lin_0318_0332(const Lin_ConfigType *LinDriverConfig);
// void TSC_Lin_0333();
// void TSC_Lin_0333_1(const Lin_ConfigType *LinDriverConfig);
// void TSC_Lin_0333_2(const Lin_ConfigType *LinDriverConfig);
// void TSC_Lin_0333_2();
// void TSC_Lin_main(const Lin_ConfigType *LinDriverConfig);

#endif //TESTER_LIN_H
