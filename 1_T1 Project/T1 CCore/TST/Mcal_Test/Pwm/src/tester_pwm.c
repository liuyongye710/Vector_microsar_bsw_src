#include "Pwm.h"
#include "console.h"
#include "shell.h"
#include "tester_pwm.h"
#include "common.h"
#include "intc_lld.h"
#include "Pwm_LLDriver.h"
#include "GTM_TIM_LLDrivers.h"
#include <string.h>
#include "Gpt_Gtm_LLDriver.h"
#include "eMIOS_LLDriver.h"
#include "Pwm_Irq.h"

#define PWM_TEST_ATOM_CH          0
#define PWM_TEST_TOM_CH           1
#define PWM_TEST_EMIOS_OPWFMB_CH  2
#define PWM_TEST_ETPU_CH          3
#define PWM_TEST_EMIOS_SAOC_CH    4
#define PWM_TEST_EMIOS_DAOC_CH    5
#define PWM_TEST_EMIOS_OPWMCB_CH  6
#define PWM_TEST_EMIOS_OPWMB_CH   7

#define PWM_TEST_CASE_MAX sizeof(pwm_funcs) / sizeof(PwmfuncMachine)

#define PRINTF_FUNCNAME() PSPRINTF("\r\n    [%s]\r\n", __func__);

#define TSC_GTM_ATOM 1
#define TSC_GTM_TOM 0

static uint8_t tom_clk_flag=0;
static uint8_t atom_clk_flag=0;

void TSC_Pwm_Clock(uint8_t type);

static PwmfuncMachine pwm_funcs[] = {
   {"PWM_0038", TSC_Pwm_0038},
   {"PWM_0039", TSC_Pwm_0039},
   {"PWM_0040", TSC_Pwm_0040},
   {"PWM_0041", TSC_Pwm_0041},

   {"PWM_0042", TSC_Pwm_0042},
   {"PWM_0043", TSC_Pwm_0043},

   {"PWM_0044", TSC_Pwm_0044},
   {"PWM_0045", TSC_Pwm_0045},
   {"PWM_0046", TSC_Pwm_0046},
   {"PWM_0047", TSC_Pwm_0047},
   {"PWM_0048", TSC_Pwm_0048},
   {"PWM_0049", TSC_Pwm_0049},
   {"PWM_0050", TSC_Pwm_0050},
   {"PWM_0051", TSC_Pwm_0051},

   {"PWM_0052", TSC_Pwm_0052},
   {"PWM_0053", TSC_Pwm_0053},
   {"PWM_0054", TSC_Pwm_0054},
   {"PWM_0055", TSC_Pwm_0055},
   {"PWM_0056", TSC_Pwm_0056},
   {"PWM_0057", TSC_Pwm_0057},
   {"PWM_0058", TSC_Pwm_0058},
   {"PWM_0059", TSC_Pwm_0059},
   {"PWM_0060", TSC_Pwm_0060},
   {"PWM_0061", TSC_Pwm_0061}, 
   {"PWM_0062", TSC_Pwm_0062},
   {"PWM_0063", TSC_Pwm_0063},

   {"PWM_0064", TSC_Pwm_0064},
   {"PWM_0065", TSC_Pwm_0065},
   {"PWM_0066", TSC_Pwm_0066},
   {"PWM_0067", TSC_Pwm_0067},

   {"PWM_0068", TSC_Pwm_0068},
   {"PWM_0069", TSC_Pwm_0069},
   {"PWM_0070", TSC_Pwm_0070},
   {"PWM_0071", TSC_Pwm_0071},

   {"PWM_0072", TSC_Pwm_0072},
   {"PWM_0073", TSC_Pwm_0073},
   {"PWM_0074", TSC_Pwm_0074},
   {"PWM_0075", TSC_Pwm_0075},
   {"PWM_0076", TSC_Pwm_0076},
   {"PWM_0077", TSC_Pwm_0077},
   {"PWM_0078", TSC_Pwm_0078},
   {"PWM_0079", TSC_Pwm_0079},
   {"PWM_0080", TSC_Pwm_0080},
   {"PWM_0081", TSC_Pwm_0081},
   {"PWM_0082", TSC_Pwm_0082},
   {"PWM_0083", TSC_Pwm_0083},
   {"PWM_0084", TSC_Pwm_0084},

   {"PWM_0085", TSC_Pwm_0085},
   {"PWM_0086", TSC_Pwm_0086},

   {"PWM_0087", TSC_Pwm_0087},
   {"PWM_0088", TSC_Pwm_0088},
   {"PWM_0089", TSC_Pwm_0089},
   {"PWM_0090", TSC_Pwm_0090},
   {"PWM_0091", TSC_Pwm_0091},
   {"PWM_0092", TSC_Pwm_0092},
   {"PWM_0093", TSC_Pwm_0093},
   {"PWM_6005", TSC_Pwm_6005},

   {"PWM_0094_0106", TSC_Pwm_0094_106},
   {"PWM_0120_0132", TSC_Pwm_0120_132},
   {"PWM_0300_0312", TSC_Pwm_0300_312},
   {"PWM_0313_0325", TSC_Pwm_0313_325},
   {"PWM_0326_0333", TSC_Pwm_0326_333},
   {"PWM_0334_0341", TSC_Pwm_0334_341},
   {"PWM_0342_0349", TSC_Pwm_0342_349},
   {"PWM_0350", TSC_Pwm_0350},
   {"PWM_0351_0352", TSC_Pwm_0351_352},
   {"PWM_0353_0354", TSC_Pwm_0353_354},
   {"PWM_0355_0356", TSC_Pwm_0355_356},
   {"PWM_0357_0358", TSC_Pwm_0357_358},
   {"PWM_0359", TSC_Pwm_0359},
   {"PWM_0360", TSC_Pwm_0360},
   {"PWM_0361", TSC_Pwm_0361},
   {"PWM_0362", TSC_Pwm_0362},
   {"PWM_0363", TSC_Pwm_0363},
   {"PWM_0364", TSC_Pwm_0364},
   {"PWM_0365", TSC_Pwm_0365},
   {"PWM_0366", TSC_Pwm_0366},
   {"PWM_0367", TSC_Pwm_0367},
   {"PWM_0368", TSC_Pwm_0368},
   {"PWM_0369", TSC_Pwm_0369},

   {"PWM_5001", TSC_Pwm_5001},
   {"PWM_5002", TSC_Pwm_5002},
   {"PWM_5003", TSC_Pwm_5003},
   {"PWM_5004", TSC_Pwm_5004},
   {"PWM_5005", TSC_Pwm_5005},
   {"PWM_5006", TSC_Pwm_5006},

   {"PWM_5007", TSC_Pwm_5007},
   {"PWM_5008", TSC_Pwm_5008},
   {"PWM_5009", TSC_Pwm_5009},
   {"PWM_5010", TSC_Pwm_5010},
   {"PWM_5011", TSC_Pwm_5011},
   {"PWM_5012", TSC_Pwm_5012},

   {"PWM_5013", TSC_Pwm_5013},
   {"PWM_5014", TSC_Pwm_5014},
   {"PWM_5015", TSC_Pwm_5015},
   {"PWM_5016", TSC_Pwm_5016},
   {"PWM_5017", TSC_Pwm_5017},
   {"PWM_5018", TSC_Pwm_5018},

   {"PWM_5019", TSC_Pwm_5019},
   {"PWM_5020", TSC_Pwm_5020},
   {"PWM_5021", TSC_Pwm_5021},
   {"PWM_5022", TSC_Pwm_5022},
   {"PWM_5023", TSC_Pwm_5023},
   {"PWM_5024", TSC_Pwm_5024},

   {"PWM_0107", TSC_Pwm_0107},
   {"PWM_0108", TSC_Pwm_0108},

   {"PWM_0109", TSC_Pwm_0109},
   {"PWM_0110", TSC_Pwm_0110},
   {"PWM_0111", TSC_Pwm_0111},
   {"PWM_0112", TSC_Pwm_0112},
   {"PWM_0113", TSC_Pwm_0113},
   {"PWM_0114", TSC_Pwm_0114},
};
 

int Pwm_Channel = 0;

void PwmNotification_cb()
{}


void TSC_Pwm_0038(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    Pwm_Init(NULL_PTR);
}

void TSC_Pwm_0039(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    Pwm_Init(ConfigPtr);
    Pwm_DeInit();
}

void TSC_Pwm_0040(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    Pwm_Init(ConfigPtr);

    Pwm_Init(ConfigPtr);
    Pwm_DeInit();
}

void TSC_Pwm_0041(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    TSC_Pwm_Clock(TSC_GTM_TOM);
    Pwm_Init(ConfigPtr);
    PSPRINTF("First Call Pwm_Init()\r\n");
#if (PWM_DEINIT_API == STD_ON)
    Pwm_DeInit();
    PSPRINTF("Call Pwm_DeInit()\r\n");

    Pwm_Init(ConfigPtr);
    PSPRINTF("Second Call Pwm_Init()\r\n");
#else
    {
        PSPRINTF("Error: undefined function\r\n");
    }
#endif
    Pwm_DeInit();
}

void TSC_Pwm_0042(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    Pwm_DeInit();
}

void TSC_Pwm_0043(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_DeInit();
}

void TSC_Pwm_0044(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(0,0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0045(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(2,0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0046(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(4,0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0047(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(5,0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0048(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(0,0);
    Pwm_DeInit();
}

void TSC_Pwm_0049(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(0,0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0050(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(0,0x8000);
    Pwm_DeInit();
}

void TSC_Pwm_0051(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetDutyCycle(0,0x8001);
    Pwm_DeInit();
}

void TSC_Pwm_0052(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 1000, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0053(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(2, 1000, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0054(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(4, 1000, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0055(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(5, 1000, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0056(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 0, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0057(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 1000, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0058(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 65535, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0059(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 65536, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0060(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 1000, 0);
    Pwm_DeInit();
}

void TSC_Pwm_0061(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 1000, 0x4000);
    Pwm_DeInit();
}

void TSC_Pwm_0062(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 1000, 0x8000);
    Pwm_DeInit();
}

void TSC_Pwm_0063(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetPeriodAndDuty(0, 1000, 0x8001);
    Pwm_DeInit();
}

void TSC_Pwm_0064(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetOutputToIdle(0);
    Pwm_DeInit();
}

void TSC_Pwm_0065(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetOutputToIdle(2);
    Pwm_DeInit();
}

void TSC_Pwm_0066(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetOutputToIdle(4);
    Pwm_DeInit();
}

void TSC_Pwm_0067(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_SetOutputToIdle(5);
    Pwm_DeInit();
}

void TSC_Pwm_0068(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;
    Pwm_Init(ConfigPtr);
    retVal = Pwm_GetOutputState(0);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    Pwm_DeInit();
}

void TSC_Pwm_0069(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;
    Pwm_Init(ConfigPtr);
    retVal = Pwm_GetOutputState(2);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    Pwm_DeInit();
}

void TSC_Pwm_0070(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;
    Pwm_Init(ConfigPtr);
    retVal = Pwm_GetOutputState(4);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    Pwm_DeInit();
}

void TSC_Pwm_0071(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;
    Pwm_Init(ConfigPtr);
    retVal = Pwm_GetOutputState(5);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    Pwm_DeInit();
}

void TSC_Pwm_0072(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_DisableNotification(0);
    Pwm_DeInit();
}

void TSC_Pwm_0073(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_DisableNotification(2);
    Pwm_DeInit();
}

void TSC_Pwm_0074(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_DisableNotification(4);
    Pwm_DeInit();
}

void TSC_Pwm_0075(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_DisableNotification(5);
    Pwm_DeInit();
}

void TSC_Pwm_0076(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(0,PWM_BOTH_EDGES);
    Pwm_DeInit();
}

void TSC_Pwm_0077(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(2,PWM_BOTH_EDGES);
    Pwm_DeInit();
}

void TSC_Pwm_0078(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(4,PWM_BOTH_EDGES);
    Pwm_DeInit();
}

void TSC_Pwm_0079(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(5,PWM_BOTH_EDGES);
    Pwm_DeInit();
}

void TSC_Pwm_0080(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(0,PWM_RISING_EDGE);
    Pwm_DeInit();
}

void TSC_Pwm_0081(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(0,PWM_FALLING_EDGE);
    Pwm_DeInit();
}

void TSC_Pwm_0082(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(0,PWM_BOTH_EDGES);
    Pwm_DeInit();
}

void TSC_Pwm_0083(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(0,4);
    Pwm_DeInit();
}

void TSC_Pwm_0084(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_Init(ConfigPtr);
    Pwm_EnableNotification(1,PWM_BOTH_EDGES);
    Pwm_DeInit();
}

void TSC_Pwm_0085(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    Pwm_GetVersionInfo(NULL_PTR);
}

void TSC_Pwm_0086(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    Std_VersionInfoType VersionInfo;

    PRINTF_FUNCNAME();

    Pwm_GetVersionInfo(&VersionInfo);
    PSPRINTF("VersionInfo->vendorID = %d\r\n", VersionInfo.vendorID);
    PSPRINTF("VersionInfo->moduleID= %d\r\n", VersionInfo.moduleID);
    PSPRINTF("VersionInfo->sw_major_version= %d\r\n", VersionInfo.sw_major_version);
    PSPRINTF("VersionInfo->sw_minor_version= %d\r\n", VersionInfo.sw_minor_version);
    PSPRINTF("VersionInfo->sw_patch_version= %d\r\n", VersionInfo.sw_patch_version);
}

void TSC_Pwm_0087(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_SetDutyCycle(0,0x4000);
}

void TSC_Pwm_0088(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_SetPeriodAndDuty(0,1000,0x4000);
}

void TSC_Pwm_0089(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_SetOutputToIdle(0);
}

void TSC_Pwm_0090(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_GetOutputState(0);
}

void TSC_Pwm_0091(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_DisableNotification(0);
}

void TSC_Pwm_0092(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_EnableNotification(0,PWM_BOTH_EDGES);
}

void TSC_Pwm_0093(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	PRINTF_FUNCNAME();
	Pwm_Init(ConfigPtr);
	Pwm_SetPeriodAndDuty(1,1000,0x4000);
}

void TSC_Pwm_6005(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;
    retVal = Pwm_GetOutputState(0);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
}

//ATOM
void TSC_Pwm_0094_106(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();
    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0094
    Pwm_Init(ConfigPtr);
    (void)(void)delay_ms(second_5);

    //PWM_0095
    Pwm_SetDutyCycle(PWM_TEST_ATOM_CH, 0x2000);
    (void)(void)delay_ms(second_5);

    //PWM_0096
    Pwm_SetDutyCycle(PWM_TEST_ATOM_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0097
    Pwm_SetDutyCycle(PWM_TEST_ATOM_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0098
    Pwm_SetPeriodAndDuty(PWM_TEST_ATOM_CH,6000,0x6000);
    (void)delay_ms(second_5);

    //PWM_0099
    Pwm_SetPeriodAndDuty(PWM_TEST_ATOM_CH,6000,0);
    (void)delay_ms(second_5);

    //PWM_0100
    Pwm_SetPeriodAndDuty(PWM_TEST_ATOM_CH,6000,0x8000);
    (void)delay_ms(second_5);

    //PWM_0101
    Pwm_SetOutputToIdle(PWM_TEST_ATOM_CH);
    (void)delay_ms(second_5);

    //PWM_0102
    Pwm_SetPeriodAndDuty(PWM_TEST_ATOM_CH,6000,0x4000);
    (void)delay_ms(second_5);

    //PWM_0103
    Pwm_SetOutputToIdle(PWM_TEST_ATOM_CH);
    (void)delay_ms(second_5);

    //PWM_0104
    Pwm_SetDutyCycle(PWM_TEST_ATOM_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0105
    retVal = Pwm_GetOutputState(PWM_TEST_ATOM_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    (void)delay_ms(second_5);

    //PWM_0106
    Pwm_DeInit();
}

//TOM
void TSC_Pwm_0120_132(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0120
    Pwm_Init(ConfigPtr);
    (void)delay_ms(second_5);

    //PWM_0121
    Pwm_SetDutyCycle(PWM_TEST_TOM_CH, 0x2000);
    (void)delay_ms(second_5);

    //PWM_0122
    Pwm_SetDutyCycle(PWM_TEST_TOM_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0123
    Pwm_SetDutyCycle(PWM_TEST_TOM_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0124
    Pwm_SetPeriodAndDuty(PWM_TEST_TOM_CH,6000,0x6000);
    (void)delay_ms(second_5);

    //PWM_0125
    Pwm_SetPeriodAndDuty(PWM_TEST_TOM_CH,6000,0);
    (void)delay_ms(second_5);

    //PWM_0126
    Pwm_SetPeriodAndDuty(PWM_TEST_TOM_CH,6000,0x8000);
    (void)delay_ms(second_5);

    //PWM_0127
    Pwm_SetOutputToIdle(PWM_TEST_TOM_CH);
    (void)delay_ms(second_5);

    //PWM_0128
    Pwm_SetPeriodAndDuty(PWM_TEST_TOM_CH,6000,0x4000);
    (void)delay_ms(second_5);

    //PWM_0129
    Pwm_SetOutputToIdle(PWM_TEST_TOM_CH);
    (void)delay_ms(second_5);

    //PWM_0130
    Pwm_SetDutyCycle(PWM_TEST_TOM_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0131
    retVal = Pwm_GetOutputState(PWM_TEST_TOM_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    (void)delay_ms(second_5);

    //PWM_0132
    Pwm_DeInit();
}

//OPWFMB
void TSC_Pwm_0300_312(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0300
    Pwm_Init(ConfigPtr);
    (void)delay_ms(second_5);

    //PWM_0301
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWFMB_CH, 0x2000);
    (void)delay_ms(second_5);

    //PWM_0302
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWFMB_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0303
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWFMB_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0304
    Pwm_SetPeriodAndDuty(PWM_TEST_EMIOS_OPWFMB_CH,500,0x6000);
    (void)delay_ms(second_5);

    //PWM_0305
    Pwm_SetPeriodAndDuty(PWM_TEST_EMIOS_OPWFMB_CH,500,0);
    (void)delay_ms(second_5);

    //PWM_0306
    Pwm_SetPeriodAndDuty(PWM_TEST_EMIOS_OPWFMB_CH,500,0x8000);
    (void)delay_ms(second_5);

    //PWM_0307
    Pwm_SetOutputToIdle(PWM_TEST_EMIOS_OPWFMB_CH);
    (void)delay_ms(second_5);

    //PWM_0308
    Pwm_SetPeriodAndDuty(PWM_TEST_EMIOS_OPWFMB_CH,500,0x4000);
    (void)delay_ms(second_5);

    //PWM_0309
    Pwm_SetOutputToIdle(PWM_TEST_EMIOS_OPWFMB_CH);
    (void)delay_ms(second_5);

    //PWM_0310
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWFMB_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0311
    retVal = Pwm_GetOutputState(PWM_TEST_EMIOS_OPWFMB_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }

    //PWM_0312
    (void)delay_ms(second_5);
    Pwm_DeInit();
}

//ETPU
void TSC_Pwm_0313_325(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0313
    Pwm_Init(ConfigPtr);
    (void)delay_ms(second_5);

    //PWM_0314
    Pwm_SetDutyCycle(PWM_TEST_ETPU_CH, 0x2000);
    (void)delay_ms(second_5);

    //PWM_0315
    Pwm_SetDutyCycle(PWM_TEST_ETPU_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0316
    Pwm_SetDutyCycle(PWM_TEST_ETPU_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0317
    Pwm_SetPeriodAndDuty(PWM_TEST_ETPU_CH,500,0x6000);
    (void)delay_ms(second_5);

    //PWM_0318
    Pwm_SetPeriodAndDuty(PWM_TEST_ETPU_CH,500,0);
    (void)delay_ms(second_5);

    //PWM_0319
    Pwm_SetPeriodAndDuty(PWM_TEST_ETPU_CH,500,0x8000);
    (void)delay_ms(second_5);

    //PWM_0320
    Pwm_SetOutputToIdle(PWM_TEST_ETPU_CH);
    (void)delay_ms(second_5);

    //PWM_0321
    Pwm_SetPeriodAndDuty(PWM_TEST_ETPU_CH,500,0x4000);
    (void)delay_ms(second_5);

    //PWM_0322
    Pwm_SetOutputToIdle(PWM_TEST_ETPU_CH);
    (void)delay_ms(second_5);

    //PWM_0323
    Pwm_SetDutyCycle(PWM_TEST_ETPU_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0324
    retVal = Pwm_GetOutputState(PWM_TEST_ETPU_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    (void)delay_ms(second_5);

    //PWM_0325
    Pwm_DeInit();
}

//OPWMCB
void TSC_Pwm_0326_333(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0326
    Pwm_Init(ConfigPtr);
    (void)delay_ms(second_5);

    //PWM_0327
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMCB_CH, 0x2000);
    (void)delay_ms(second_5);

    //PWM_0328
    Pwm_SetOutputToIdle(PWM_TEST_EMIOS_OPWMCB_CH);
    (void)delay_ms(second_5);

    //PWM_0329
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMCB_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0330
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMCB_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0331
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMCB_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0332
    retVal = Pwm_GetOutputState(PWM_TEST_EMIOS_OPWMCB_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    (void)delay_ms(second_5);

    //PWM_0333
    Pwm_DeInit();
}

//OPWMB
void TSC_Pwm_0334_341(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0334
    Pwm_Init(ConfigPtr);
    (void)delay_ms(second_5);

    //PWM_0335
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMB_CH, 0x2000);
    (void)delay_ms(second_5);

    //PWM_0336
    Pwm_SetOutputToIdle(PWM_TEST_EMIOS_OPWMB_CH);
    (void)delay_ms(second_5);

    //PWM_0337
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMB_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0338
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMB_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0339
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_OPWMB_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0340
    retVal = Pwm_GetOutputState(PWM_TEST_EMIOS_OPWMB_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    (void)delay_ms(second_5);

    //PWM_0341
    Pwm_DeInit();
}

void Atom0_0_1_IRQ_Handle(void)
{
	Pwm_Atom_isr_handle(0,0,1);
}

void Tom0_0_1IRQ_Handle(void)
{
	Pwm_Tom_isr_handle(0,0,1);
}

void Emios0_5_IRQ_Handle(void)
{
	Pwm_Emios_isr_handle(0,5);
}

void Etpu0_0_IRQ_Handle(void)
{
	Pwm_Etpu_isr_handle(0,0);
}

void Emios0_2_IRQ_Handle(void)
{
	Pwm_Emios_DAOC_Isr_handle(0,2);
	eMIOS_LLD_UC_ClearFlag(0,2);
}

//DAOC
void TSC_Pwm_0342_349(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    PRINTF_FUNCNAME();

    VAR(Pwm_OutputStateType, AUTOMATIC) retVal;

    int second_5 = 100;

    //PWM_0342
    Pwm_Init(ConfigPtr);
    (void)INTC_LLD_Set_IRQ_Handle((IntrId)INTR_ID_945, (IntrHandle)&Emios0_2_IRQ_Handle);
    (void)INTC_LLD_Set_IRQ_Enable((IntrId)INTR_ID_945);
    (void)INTC_LLD_Set_IRQ_Priority((IntrId)INTR_ID_945, INTR_PRI_15);
    (void)delay_ms(second_5);

    //PWM_0343
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_DAOC_CH, 0x2000);
    (void)delay_ms(second_5);

    //PWM_0344
    Pwm_SetOutputToIdle(PWM_TEST_EMIOS_DAOC_CH);
    (void)delay_ms(second_5);

    //PWM_0345
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_DAOC_CH, 0x8000);
    (void)delay_ms(second_5);

    //PWM_0346
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_DAOC_CH, 0);
    (void)delay_ms(second_5);

    //PWM_0347
    Pwm_SetDutyCycle(PWM_TEST_EMIOS_DAOC_CH,0x2000);
    (void)delay_ms(second_5);

    //PWM_0348
    retVal = Pwm_GetOutputState(PWM_TEST_EMIOS_DAOC_CH);
    if (retVal == PWM_LOW)
    {
        PSPRINTF("retVal = PWM_LOW\r\n");
    }
    else
    {
        PSPRINTF("retVal = PWM_HIGH\r\n");
    }
    (void)delay_ms(second_5);

    //PWM_0349
    Pwm_DeInit();
}

//SAOC
void TSC_Pwm_0350(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 100;

	//PWM_0353
	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

//ATOM Notification
void TSC_Pwm_0351_352(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 100;

	SIUL2.MSCR_IO[0U].R = 0x32840000U;
	(void)INTC_LLD_Set_IRQ_Handle((IntrId)837, &Atom0_0_1_IRQ_Handle);
	(void)INTC_LLD_Set_IRQ_Priority((IntrId)837, INTR_PRI_15);
	(void)INTC_LLD_Set_IRQ_Enable((IntrId)837);
	Pwm_Init(ConfigPtr);

	//PWM_0351
	Pwm_EnableNotification(PWM_TEST_ATOM_CH,PWM_BOTH_EDGES);
	(void)delay_ms(second_5);
	//PWM_0352
	Pwm_DisableNotification(PWM_TEST_ATOM_CH);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

//TOM Notification
void TSC_Pwm_0353_354(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 100;

	SIUL2.MSCR_IO[0U].R = 0x32840000U;
	(void)INTC_LLD_Set_IRQ_Handle((IntrId)813, &Tom0_0_1IRQ_Handle);
	(void)INTC_LLD_Set_IRQ_Priority((IntrId)813, INTR_PRI_15);
	(void)INTC_LLD_Set_IRQ_Enable((IntrId)813);
	Pwm_Init(ConfigPtr);

	//PWM_0353
	Pwm_EnableNotification(PWM_TEST_TOM_CH,PWM_BOTH_EDGES);
	(void)delay_ms(second_5);
	//PWM_0354
	Pwm_DisableNotification(PWM_TEST_TOM_CH);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

//EMIOS Notification
void TSC_Pwm_0355_356(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 100;

	SIUL2.MSCR_IO[0U].R = 0x32840000U;
	Pwm_Init(ConfigPtr);
	(void)INTC_LLD_Set_IRQ_Handle((IntrId)EMIOS0_CH5_IRQ997, &Emios0_5_IRQ_Handle);
	(void)INTC_LLD_Set_IRQ_Priority((IntrId)EMIOS0_CH5_IRQ997, INTR_PRI_15);
	(void)INTC_LLD_Set_IRQ_Enable((IntrId)EMIOS0_CH5_IRQ997);

	//PWM_0355
	Pwm_EnableNotification(PWM_TEST_EMIOS_OPWFMB_CH,PWM_BOTH_EDGES);
	(void)delay_ms(second_5);
	//PWM_0356
	Pwm_DisableNotification(PWM_TEST_EMIOS_OPWFMB_CH);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

//ETPU Notification
void TSC_Pwm_0357_358(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 100;

	SIUL2.MSCR_IO[0U].R = 0x32840000U;
	Pwm_Init(ConfigPtr);
	(void)INTC_LLD_Set_IRQ_Handle((IntrId)INTR_ID_236, &Etpu0_0_IRQ_Handle);
	(void)INTC_LLD_Set_IRQ_Priority((IntrId)INTR_ID_236, INTR_PRI_15);
	(void)INTC_LLD_Set_IRQ_Enable((IntrId)INTR_ID_236);

	//PWM_0357
	Pwm_EnableNotification(PWM_TEST_ETPU_CH,PWM_BOTH_EDGES);
	(void)delay_ms(second_5);
	//PWM_0358
	Pwm_DisableNotification(PWM_TEST_ETPU_CH);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0359(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 15000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
    Pwm_SetOutputToIdle(0);
    (void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0360(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 200;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
    Pwm_SetOutputToIdle(1);
    (void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0361(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0362(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0363(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0364(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0365(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0366(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0367(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 1000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0368(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 15000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}

void TSC_Pwm_0369(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	int second_5 = 150000;

	Pwm_Init(ConfigPtr);
	(void)delay_ms(second_5);
	Pwm_DeInit();
}
void TSC_Pwm_5001(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_Init(ConfigPtr);
}

void TSC_Pwm_5002(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<72;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5003(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<72;i++)
	{
		Pwm_SetPeriodAndDuty(i,6000,0x6000);
	}
}

void TSC_Pwm_5004(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<72;i++)
	{
		Pwm_SetOutputToIdle(i);
	}
}

void TSC_Pwm_5005(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<72;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5006(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_DeInit();
}

void TSC_Pwm_5007(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_Init(ConfigPtr);
}

void TSC_Pwm_5008(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<80;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5009(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<80;i++)
	{
		Pwm_SetPeriodAndDuty(i,6000,0x6000);
	}
}

void TSC_Pwm_5010(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<80;i++)
	{
		Pwm_SetOutputToIdle(i);
	}
}

void TSC_Pwm_5011(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<80;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5012(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_DeInit();
}
const eMIOS_GlobalParamType eMIOS_InitGlobalConfig;
void TSC_Pwm_5013(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    eMIOS_LLD_InitGlobalParam(1, &eMIOS_InitGlobalConfig);
    eMIOS_LLD_SetEnDisGlobal(1, TRUE);
	Pwm_Init(ConfigPtr);
}

void TSC_Pwm_5014(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<32;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5015(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<32;i++)
	{
		Pwm_SetPeriodAndDuty(i,500,0x6000);
	}
}

void TSC_Pwm_5016(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<32;i++)
	{
		Pwm_SetOutputToIdle(i);
	}
}

void TSC_Pwm_5017(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<32;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5018(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_DeInit();
}

void TSC_Pwm_5019(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_Init(ConfigPtr);
}

void TSC_Pwm_5020(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<96;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5021(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<96;i++)
	{
		Pwm_SetPeriodAndDuty(i,500,0x6000);
	}
}

void TSC_Pwm_5022(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<96;i++)
	{
		Pwm_SetOutputToIdle(i);
	}
}

void TSC_Pwm_5023(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	for(int i=0;i<96;i++)
	{
		Pwm_SetDutyCycle(i,0x2000);
	}
}

void TSC_Pwm_5024(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_DeInit();
}

void Pwm_Notification_0(void)
{
	SIUL2.GPDO[0U].R ^= 1U;
}

void Pwm_Notification_1(void)
{
	SIUL2.GPDO[0U].R ^= 1U;
}

void Pwm_Notification_2(void)
{
	SIUL2.GPDO[0U].R ^= 1U;
}

void Pwm_Notification_3(void)
{
	SIUL2.GPDO[0U].R ^= 1U;
}

FUNC(void, PWM_CODE) Pwm_Tom_Atom_Isr(void);
FUNC(void, PWM_CODE) Pwm_Emios_Isr(VAR(uint8_t, AUTOMATIC) emiosIndex, VAR(uint8_t, AUTOMATIC) ChanNum);
void TSC_Pwm_0107(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	//(void)INTC_LLD_Set_IRQ_Handle((IntrId)813, &Pwm_Tom_Atom_Isr);
	(void)INTC_LLD_Set_IRQ_Priority((IntrId)813, INTR_PRI_15);
	(void)INTC_LLD_Set_IRQ_Enable((IntrId)813);

	SIUL2.MSCR_IO[0U].R = 0x32840000U;  /* GPIO PA[0] output */
	TSC_Pwm_Clock(TSC_GTM_TOM);
	Pwm_Init(ConfigPtr);
	Pwm_EnableNotification(0,PWM_BOTH_EDGES);
}

void TSC_Pwm_0108(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	Pwm_DisableNotification(2);
}

const eMIOS_GlobalParamType eMIOS_InitGlobalConfig =
{
    .LowPowerModeEn         = FALSE,        /*!< Low power mode or normal mode                                              */
    .FreezeInDebugMode      = FALSE,        /*!< If true, all channel in eMIOS group can enter debug mode                   */
    .GlobalPreClkDiv        = 80U,           /*!< Select the clock divider value for the global prescaler in range(1-256)    */
    .ExternalTimeBaseSel    = EMIOS_ETB_DIS_COUNTER_BUSA_TO_UC,        /*!< Enable or disable external timebase                                        */
    .ServerTimeSlotSel      = 0U            /*!< Select the address of a specific STAC server to which the STAC is assigned */
};

const eMIOS_MC_ParamType eMIOS_Mc1_CntChnConfig_0 =
{
    .mode                   = EMIOS_UC_MODE_MCB_UP_COUNTER_INT_CLK,   /*!< Sub-mode selected                                                    */
    .period                 = 1000UL,                             /*!< Period value                                                         */
    .divid                  = 1U,                                   /*!< Internal prescaler value                                             */
    .filter                 = EMIOS_INPUT_FILTER_BYPASS,           /*!< Filter value, ignore if not select external clock mode               */
    .trigger                = EMIOS_TRIG_EDGE_FALLING           /*!< Input signal trigger mode, ignore if not select external clock mode  */
};

const eMIOS_MC_ParamType eMIOS_Mc1_CntChnConfig_1 =
{
    .mode                   = EMIOS_UC_MODE_MCB_UP_COUNTER_INT_CLK,   /*!< Sub-mode selected                                                    */
    .period                 = 1000UL,                             /*!< Period value                                                         */
    .divid                  = 1U,                                  /*!< Internal prescaler value                                             */
    .filter                 = EMIOS_INPUT_FILTER_BYPASS,           /*!< Filter value, ignore if not select external clock mode               */
    .trigger                = EMIOS_TRIG_EDGE_FALLING           /*!< Input signal trigger mode, ignore if not select external clock mode  */
};

const eMIOS_MC_ParamType eMIOS_Mc1_CntChnConfig_2 =
{
    .mode                   = EMIOS_UC_MODE_MCB_UPDOWN_CNT_FLAGX1_INT_CLK, /*!< Sub-mode selected                                                    */
    .period                 = 1000UL,                             /*!< Period value                                                         */
    .divid                  = 1U,              /*!< Internal prescaler value                                             */
    .filter                 = EMIOS_INPUT_FILTER_BYPASS,           /*!< Filter value, ignore if not select external clock mode               */
    .trigger                = EMIOS_TRIG_EDGE_FALLING           /*!< Input signal trigger mode, ignore if not select external clock mode  */
};

//OPWFMB
void TSC_Pwm_0109(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    eMIOS_PWM_PinInit(0, 1U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    Pwm_Init(ConfigPtr);
}

//OPWMB
void TSC_Pwm_0110(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    eMIOS_PWM_PinInit(0, 2U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    (void)eMIOS_LLD_MC_Init(0, (uint8_t)EMIOS_CNT_BUSA_DRIVEN_CHANNEL, &eMIOS_Mc1_CntChnConfig_0);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    Pwm_Init(ConfigPtr);
}

void TSC_Pwm_3110(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    eMIOS_PWM_PinInit(0, 1U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    (void)eMIOS_LLD_MC_Init(0, (uint8_t)EMIOS_CNT_BUSA_DRIVEN_CHANNEL, &eMIOS_Mc1_CntChnConfig_0);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    Pwm_Init(ConfigPtr);
}

//OPWMCB
void TSC_Pwm_0111(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    eMIOS_PWM_PinInit(0, 3U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    (void)eMIOS_LLD_MC_Init(0, (uint8_t)EMIOS_CNT_BUSA_DRIVEN_CHANNEL, &eMIOS_Mc1_CntChnConfig_2);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    Pwm_Init(ConfigPtr);
}
FUNC(void, PWM_CODE) Pwm_Set_Emios_SAOC_A(uint8 u8hw_index,uint8 u8ch_index,uint32 value);
FUNC(void, PWM_CODE) Pwm_Set_Emios_SAOC_B(uint8 u8hw_index,uint8 u8ch_index,uint32 value);
void Emios_IRQ_Handle(void);
//DAOC
void TSC_Pwm_0113(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
//    int i=0;
	eMIOS_PWM_PinInit(0, 0U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    (void)eMIOS_LLD_MC_Init(0, (uint8_t)EMIOS_CNT_BUSA_DRIVEN_CHANNEL, &eMIOS_Mc1_CntChnConfig_0);
    (void)eMIOS_LLD_MC_Init(0, (uint8_t)EMIOS_CNT_BUSB_DRIVEN_CHANNEL, &eMIOS_Mc1_CntChnConfig_2);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);

    SIUL2.MSCR_IO[0U].R = 0x32840000U;

//    Pwm_Init(ConfigPtr);
//    (void)INTC_LLD_Set_IRQ_Handle((IntrId)EMIOS0_CH16_IRQ1008, (IntrHandle)&Emios_IRQ_Handle);
//    (void)INTC_LLD_Set_IRQ_Enable((IntrId)EMIOS0_CH16_IRQ1008);
//    (void)INTC_LLD_Set_IRQ_Priority((IntrId)EMIOS0_CH16_IRQ1008, INTR_PRI_15);
////    Pwm_Set_Emios_SAOC_A(0, 2U, 126U);
////    Pwm_Set_Emios_SAOC_B(0, 2U, 1U);
//	eMIOS_UC_Bn_SetValue(0, 16U, 126U);
//	eMIOS_UC_An_SetValue(0, 16U, 1U);

	delay_ms(50);
//	for(int i = 0U; i < 5U; i++)
//	{
//		eMIOS_UC_Bn_SetValue(0, 2U, 126U);
//		eMIOS_UC_An_SetValue(0, 2U, 1U);
//		delay_ms(50);
//	}
}

//SAOC
void TSC_Pwm_0112(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
	eMIOS_PWM_PinInit(0, 0U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    (void)eMIOS_LLD_MC_Init(0, (uint8_t)EMIOS_CNT_BUSA_DRIVEN_CHANNEL, &eMIOS_Mc1_CntChnConfig_0);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    Pwm_Init(ConfigPtr);

}

void Emios_IRQ_Handle(void)
{
	//Pwm_Emios_Isr(0,1);
	eMIOS_LLD_UC_ClearFlag(0,2);
//	eMIOS_UC_Bn_SetValue(0, 2U, 502U);
//	eMIOS_UC_An_SetValue(0, 2U, 1U);
	eMIOS_UC_Bn_SetValue(0, 2U, 126U);
	eMIOS_UC_An_SetValue(0, 2U, 1U);

	SIUL2.GPDO[0U].R ^= 1U;
}





void TSC_Pwm_0114(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{
    eMIOS_PWM_PinInit(0, 1U);
    eMIOS_LLD_InitGlobalParam(0, &eMIOS_InitGlobalConfig);
    eMIOS_LLD_SetEnDisGlobal(0, TRUE);
    Pwm_Init(ConfigPtr);

    //eMIOS_UC_Cn_SetFEN(0, 1, (boolean)TRUE);
    (void)INTC_LLD_Set_IRQ_Handle((IntrId)INTR_ID_944, (IntrHandle)&Emios_IRQ_Handle);
    (void)INTC_LLD_Set_IRQ_Enable((IntrId)INTR_ID_944);
    (void)INTC_LLD_Set_IRQ_Priority((IntrId)INTR_ID_944, INTR_PRI_15);

    //eMIOS_LLD_UC_SetIntcRequestEn(0,1);
    Pwm_EnableNotification(2,PWM_BOTH_EDGES);

	SIUL2.MSCR_IO[0U].R = 0x32840000U;  /* GPIO PA[0] output */
}

void TSC_Pwm_Clock(uint8_t type)
{
    if(type == TSC_GTM_ATOM && tom_clk_flag == 0)
    {
        (void)GPT_GTMINT_LLD_IsEnableModule(GPT_GTM_Enable);
        (void)GPT_GTM_CMU_LLD_IsEnableClock(GPT_GTM_CMU_CLK0,GPT_GTM_Enable);
        tom_clk_flag=1;
    }
    else if(type == TSC_GTM_TOM && atom_clk_flag == 0)
    {
        (void)GPT_GTMINT_LLD_IsEnableModule(GPT_GTM_Enable);
        (void)GPT_GTM_CMU_LLD_IsEnableClock(GPT_GTM_CMU_FXCLK,GPT_GTM_Enable);
        (void)GPT_GTM_CMU_LLD_IsEnableClock(GPT_GTM_CMU_CLK0,GPT_GTM_Enable);
        atom_clk_flag=1;
    }
}


int tsc_pwm_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
        return 1;
    }

    if (argc == 2)
       {
           if (!strcmp(agrv[1], "help"))
           {
               PSPRINTF("tom  ----- CMD -------  Enable TOM Clock\r\n");
               PSPRINTF("atom ----- CMD ------- Enable ATOM Clock\r\n");
               PSPRINTF("help ----- CMD ------- ID of the test case\r\n");

               for(uint8 i = 0; i < PWM_TEST_CASE_MAX; i++)
               {
                   PSPRINTF("%s\n", pwm_funcs[i].name);
               }
           }

           else if (!strcmp(agrv[1], "tom"))
           {
               TSC_Pwm_Clock(TSC_GTM_TOM);
               PSPRINTF("Enable TOM Clock\r\n");
           }

           else if (!strcmp(agrv[1], "atom"))
           {
               TSC_Pwm_Clock(TSC_GTM_ATOM);
               PSPRINTF("Enable ATOM Clock\r\n");
           }
        else
        {
            for(uint8 i = 0; i < PWM_TEST_CASE_MAX; i++)
            {
                if(!strcmp(agrv[1], pwm_funcs[i].name))
                {
                    pwm_funcs[i].pwmfunc(&Pwm_Config);
                    return 0;
                }
            }
            PSPRINTF("error: Input invalid parameters[%s], please Use the 'Pwm_test help' command to see the supported test instructions\n", agrv[1]);
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), pwm_test, tsc_pwm_func, deint or number of test case);
