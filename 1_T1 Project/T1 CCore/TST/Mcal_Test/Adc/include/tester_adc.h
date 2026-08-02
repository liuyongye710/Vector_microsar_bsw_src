#ifndef _TESTER_ADC_H_
#define _TESTER_ADC_H_
#include "Adc.h"
#include "Adc_Irq.h"
#include "Det.h"
#include "Dio.h"
#include "Dio_Cfg.h"
#include "shell.h"
#include "string.h"

#define ADC_TEST_FUN 0

typedef void (*Adcfunc)(void);
typedef struct AdcfuncMachine
{
    char *name;
    Adcfunc adcfunc;
}AdcfuncMachine;

#if 0
//Adc_Init
void ADC_0001(void);
void ADC_0002(void);
void ADC_0003(void);

//Adc_SetupResultBuffer
void ADC_0004(void);
void ADC_0005(void);
void ADC_0006(void);
void ADC_0007(void);

#if (ADC_DEINIT_API == STD_ON)
//Adc_DeInit
void ADC_0008(void);
void ADC_0009(void);
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
//Adc_StartGroupConversion
void ADC_0010(void);
void ADC_0011(void);
void ADC_0012(void);
void ADC_0013(void);
void ADC_0014(void);

//Adc_StopGroupConversion
void ADC_0015(void);
void ADC_0016(void);
void ADC_0017(void);

void ADC_0207(void);
void ADC_0208(void);
void ADC_0212_213(void);
void ADC_0214_215(void);
void ADC_0216(void);
void ADC_0217(void);
void ADC_0218(void);
void ADC_0219_220(void);
void ADC_0262_265(void);
void ADC_0266_267(void);
void ADC_0268(void);
void ADC_0269(void);
void ADC_0270_271(void);
void ADC_0272_275(void);
void ADC_0276(void);
void ADC_0277(void);
void ADC_0278(void);
void ADC_0279(void);
void ADC_0280(void);
void ADC_0281(void);
void ADC_0282(void);
void ADC_0283(void);
void ADC_0284(void);
void ADC_0285(void);
void ADC_0286_287(void);
void ADC_0288_291(void);
void ADC_0292(void);
void ADC_0293(void);
void ADC_0294(void);
void ADC_0295(void);
void ADC_0296(void);
void ADC_0297(void);
void ADC_0298(void);
void ADC_0299(void);
void ADC_0300(void);
void ADC_0301_302(void);
void demo_AllChannel(void);
#endif

#if (ADC_READ_GROUP_API == STD_ON)
//Adc_ReadGroup
void ADC_0018(void);
void ADC_0019(void);
void ADC_0020(void);
void ADC_0206(void);
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
//Adc_EnableHardwareTrigger
void ADC_0021(void);
void ADC_0022(void);
void ADC_0023(void);
void ADC_0024(void);
void ADC_0025(void);
void ADC_0026(void);

//Adc_DisableHardwareTrigger
void ADC_0027(void);
void ADC_0028(void);
void ADC_0029(void);

void ADC_0209(void);
void ADC_0210(void);
void ADC_0211(void);
void ADC_0221_224(void);
void ADC_0225_226(void);
void ADC_0227(void);
void ADC_0228(void);
void ADC_0229_230(void);
void ADC_0231_234(void);
void ADC_0235(void);
void ADC_0236(void);
void ADC_0237(void);
void ADC_0238(void);
void ADC_0239(void);
void ADC_0240(void);
void ADC_0241(void);
void ADC_0242(void);
void ADC_0243(void);
void ADC_0244(void);
void ADC_0245_246(void);
void ADC_0247_250(void);
void ADC_0251(void);
void ADC_0252(void);
void ADC_0253(void);
void ADC_0254(void);
void ADC_0255(void);
void ADC_0256(void);
void ADC_0257(void);
void ADC_0258(void);
void ADC_0259(void);
void ADC_0260_261(void);
#endif


#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
//Adc_EnableGroupNotification
void ADC_0030(void);
void ADC_0031(void);
void ADC_0032(void);
void ADC_0033(void);

//Adc_DisableGroupNotification
void ADC_0034(void);
void ADC_0035(void);
void ADC_0036(void);
void ADC_0037(void);
#endif

//Adc_GetGroupStatus
void ADC_0038(void);
void ADC_0039(void);
void ADC_0040(void);
void ADC_0041(void);

//Adc_GetStreamLastPointer
void ADC_0042(void);
void ADC_0043(void);
void ADC_0044(void);

#if (ADC_VERSION_INFO_API == STD_ON)
//Adc_GetVersionInfo
void ADC_0045(void);
void ADC_0046(void);
#endif

#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
//Adc_SetPowerState
void ADC_0047(void);

//Adc_GetCurrentPowerState
void ADC_0048(void);

//Adc_GetTargetPowerState
void ADC_0049(void);

//Adc_PreparePowerState
void ADC_0050(void);
#endif

void EnableAdcInterrupt(void);

void ADC_demo(void);
void ADC_demo_Dma(void);
void ADC_demo_Int_Dma(void);
#if (ADC_HW_TRIGGER_API == STD_ON)
void ADC_demo_Etpu(void);
void ADC_demo_MultiGroup(void);
#endif
void ADC_demo_ExternalMux(void);
void ADC_demo_PrioQueue(void);
void ADC_demo_Queue(void);
#endif
void ADC_Project_Service1(void);
void ADC_Project_Service2(void);
void ADC_Project_Service3(void);

#endif //_TESTER_ADC_H_
