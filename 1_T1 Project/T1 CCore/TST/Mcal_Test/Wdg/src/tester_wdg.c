#include "tester_wdg.h"
#include "Wdg_Cfg.h"
#include "Det.h"
#include "shell.h"
#include "Mcu_LLDriver.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"
#include "Gpt_irq.h"
#include "Dio.h"
#include "wdg_176_ModId0.h"
#include "wdg_176_ModId1.h"
#include "wdg_176_ModId2.h"
#include "wdg_176_ModId3.h"
#include "wdg_irq.h"
extern CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet;


#define WDG_TEST_CASE_MAX sizeof(wdg_funcs) / sizeof(WdgfuncMachine)

int testwdg_flag=10;

static WdgfuncMachine wdg_funcs[] = {

    {"WDG_0001", NULL },
    {"WDG_0002", NULL },
    {"WDG_0003", NULL },
    {"WDG_0004", NULL },
    {"WDG_0005", NULL },
    {"WDG_0006", NULL },
    {"WDG_0007", NULL },
    {"WDG_0008", NULL },
    {"WDG_0009", NULL },
    {"WDG_0010", NULL },
    {"WDG_0011", NULL },
    {"WDG_0012", NULL },
    {"WDG_0013", NULL },
    {"WDG_0014", NULL },
    {"WDG_0015", NULL },
    {"WDG_0016", NULL },
    {"WDG_0017", NULL },
    {"WDG_0018", NULL },
    {"WDG_0019", NULL },
    {"WDG_0020", NULL },
    {"WDG_0021", NULL },
    {"WDG_0022", NULL },
    {"WDG_0023", NULL },
    {"WDG_0024", NULL },
    {"WDG_0025", testwdg0025},
    {"WDG_0026", testwdg0026},
    {"WDG_0027", testwdg0027},
    {"WDG_0028", testwdg0028},
    {"WDG_0029", testwdg0029},
    {"WDG_0030", testwdg0030},
    {"WDG_0031", testwdg0031},
    {"WDG_0032", testwdg0032},
    {"WDG_0033", testwdg0033},
    {"WDG_0034", testwdg0034},
    {"WDG_0035", testwdg0035},
    {"WDG_0036", testwdg0036},
    {"WDG_0037", testwdg0037},
    {"WDG_0038", testwdg0038},
    {"WDG_0039", testwdg0039},
    {"WDG_0040", testwdg0040},
    {"WDG_0041", testwdg0041},
    {"WDG_0042", testwdg0042},
    {"WDG_0043", testwdg0043},
    {"WDG_0044", testwdg0044},
    {"WDG_0045", testwdg0045},
    {"WDG_0046", testwdg0046},
    {"WDG_0047", testwdg0047},
    {"WDG_0048", testwdg0048},
    {"WDG_0049", testwdg0049},
    {"WDG_0050", testwdg0050},
    {"WDG_0051", testwdg0051},
    {"WDG_0052", testwdg0052},
    {"WDG_0053", testwdg0053},
    {"WDG_0054", testwdg0054},
    {"WDG_0055", testwdg0055},
    {"WDG_0056", testwdg0056},
    {"WDG_0057", testwdg0057},
    {"WDG_0058", testwdg0058},
    {"WDG_0059", testwdg0059},
    {"WDG_0060", testwdg0060},
    {"WDG_0061", testwdg0061},
    {"WDG_0062", testwdg0062},
    {"WDG_0063", testwdg0063},
    {"WDG_0064", testwdg0064},
    {"WDG_0065", testwdg0065},
    {"WDG_0066", testwdg0066},
    {"WDG_0067", testwdg0067},
    {"WDG_0068", testwdg0068},
    {"WDG_0069", testwdg0069},
    {"WDG_0070", testwdg0070},
    {"WDG_0071", testwdg0071},
    {"WDG_0072", testwdg0072},
    {"WDG_0073", testwdg0073},
    {"WDG_0074", testwdg0074},
    {"WDG_0075", testwdg0075},
    {"WDG_0076", testwdg0076},
    {"WDG_0077", testwdg0077},
    {"WDG_0078", testwdg0078},
    {"WDG_0079", testwdg0079},
    {"WDG_0080", testwdg0080},
    {"WDG_0081", testwdg0081},
    {"WDG_0082", testwdg0082},
    {"WDG_0083", testwdg0083},
    {"WDG_0084", testwdg0084},
    {"WDG_0085", testwdg0085},
    {"WDG_0086", testwdg0086},
    {"WDG_0087", testwdg0087},
    {"WDG_0088", testwdg0088},
    {"WDG_0089", testwdg0089},
    {"WDG_0090", testwdg0090},
    {"WDG_0091", testwdg0091},
    {"WDG_0092", testwdg0092},
    {"WDG_0093", testwdg0093},
    {"WDG_0094", testwdg0094},
    {"WDG_0095", testwdg0095},
    {"WDG_0096", testwdg0096},
    {"WDG_0097", testwdg0097},
    {"WDG_0098", testwdg0098},
    {"WDG_0099", testwdg0099},
    {"WDG_0100", testwdg0100},
    {"WDG_0101", testwdg0101},
    {"WDG_0102", testwdg0102},
    {"WDG_0103", testwdg0103},
    {"WDG_0104", testwdg0104},
    {"WDG_0105", testwdg0105},
    {"WDG_0106", testwdg0106},
    {"WDG_0107", testwdg0107},
    {"WDG_0108", testwdg0108},
    {"WDG_0109", testwdg0109},
    {"WDG_0110", testwdg0110},
    {"WDG_0111", testwdg0111},
    {"WDG_0112", testwdg0112},
    {"WDG_0113", testwdg0113},
    {"WDG_0114", testwdg0114},
    {"WDG_0115", testwdg0115},
    {"WDG_0116", testwdg0116},
    {"WDG_0117", testwdg0117},
    {"WDG_0118", testwdg0118},
    {"WDG_0119", testwdg0119},
    {"WDG_0120", testwdg0120},
    {"WDG_0121", testwdg0121},
    {"WDG_0122", testwdg0122},
    {"WDG_0123", testwdg0123},
    {"WDG_0124", testwdg0124},
    {"WDG_0125", testwdg0125},
    {"WDG_0126", testwdg0126},
    {"WDG_0127", testwdg0127},
    {"WDG_0128", testwdg0128},
    {"WDG_0129", testwdg0129},
    {"WDG_0130", testwdg0130},
    {"WDG_0131", testwdg0131},
    {"WDG_0132", testwdg0132},
    {"WDG_0133", testwdg0133},
    {"WDG_0134", testwdg0134},
    {"WDG_0135", testwdg0135},
    {"WDG_0136", testwdg0136},
    {"WDG_0137", testwdg0137},
    {"WDG_0138", testwdg0138},
    {"WDG_0139", testwdg0139},
    {"WDG_0140", testwdg0140},
    {"WDG_0141", testwdg0141},
    {"WDG_0142", testwdg0142},
    {"WDG_0143", testwdg0143},
    {"WDG_0144", testwdg0144},
    {"WDG_0145", testwdg0145},
    {"WDG_0146", testwdg0146},
    {"WDG_0147", testwdg0147},
    {"WDG_0148", testwdg0148},
    {"WDG_0149", testwdg0149},
    {"WDG_0150", testwdg0150},
    {"WDG_0151", testwdg0151},
    {"WDG_0152", testwdg0152},
    {"WDG_0153", testwdg0153},
    {"WDG_0154", testwdg0154},
    {"WDG_0155", testwdg0155},
    {"WDG_0156", testwdg0156},
    {"WDG_0157", testwdg0157},
    {"WDG_0158", testwdg0158},
    {"WDG_0159", testwdg0159},
    {"WDG_0160", testwdg0160},
    {"WDG_0161", testwdg0161},
    {"WDG_0162", testwdg0162},
    {"WDG_0163", testwdg0163},
    {"WDG_0164", testwdg0164},
    {"WDG_0165", testwdg0165},
    {"WDG_0166", testwdg0166},
    {"WDG_0167", testwdg0167},
    {"WDG_0168", testwdg0168},
    {"WDG_0169", testwdg0169},
    {"WDG_0170", testwdg0170},
    {"WDG_0171", testwdg0171},
    {"WDG_0172", testwdg0172},
    {"WDG_0173", testwdg0173},
	{"WDG_0173", testwdg0174},
	{"WDG_0173", testwdg0175},
	{"WDG_0173", testwdg0176},
	{"WDG_0173", testwdg0177},
    {"WDG_0178", testwdg0178},
    {"WDG_0179", testwdg0179},
    {"WDG_0180", testwdg0180},
    {"WDG_0181", testwdg0181},
    {"WDG_0182", testwdg0182},
    {"WDG_0183", testwdg0183},
    {"WDG_0184", testwdg0184},
    {"WDG_0185", testwdg0185},
    {"WDG_0186", testwdg0186},
    {"WDG_0187", testwdg0187},
    {"WDG_0188", testwdg0188},
    {"WDG_0189", testwdg0189},
    {"WDG_0190", testwdg0190},
    {"WDG_0191", testwdg0191},
    {"WDG_0192", testwdg0192},
    {"WDG_0193", testwdg0193},

};

void SWT_IRQ()
{
#ifdef USER_SWT0_IRQ
    (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_32, INTR_PRI_1);
    /*Install interrupt handler*/
    (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_32, &SWT0_ISR);
    /*Switch interrupt process to current core*/
    (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_32);
#endif
#ifdef USER_SWT1_IRQ
    /*Set interrupt priority*/
    (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_33, INTR_PRI_1);
    /*Install interrupt handler*/
    (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_33, &SWT1_ISR);
    /*Switch interrupt process to current core*/
    (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_33);
#endif
#ifdef USER_SWT2_IRQ

    /*Set interrupt priority*/
    (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_34, INTR_PRI_1);
    /*Install interrupt handler*/
    (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_34, &SWT2_ISR);
    /*Switch interrupt process to current core*/
    (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_34);
#endif
#ifdef USER_SWT3_IRQ
    /*Set interrupt priority*/
    (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_35, INTR_PRI_1);
    /*Install interrupt handler*/
    (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_35, &SWT3_ISR);
    /*Switch interrupt process to current core*/
    (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_35);
#endif
}
CONST(SWT_Module_Config_Type, WDG_CONST)WdgConfigSetTypeerror0 =
{
	    .SWT_ModuleID = SWT0,
	    .SWT_DefaultRunMode = 10,
	    .u8Wdg_GptTimerChannel = (Gpt_ChannelType)0U,
	    .u32Wdg_TriggerSourceClock = (uint32)60000,
	    .SWT_Config = { 0, 0, 0},
	    .SWT_Callback =NULL_PTR
};
CONST(Wdg_ConfigType, CAN_CONST) WdgSettingerrorConfig_0 =
{
			&WdgConfigSetTypeerror0,
};
CONST(SWT_Module_Config_Type, WDG_CONST)WdgConfigSetTypeerror1 =
{
	    .SWT_ModuleID = SWT1,
	    .SWT_DefaultRunMode = 10,
	    .u8Wdg_GptTimerChannel = (Gpt_ChannelType)0U,
	    .u32Wdg_TriggerSourceClock = (uint32)60000,
	    .SWT_Config = { 0, 0, 0},
	    .SWT_Callback =NULL_PTR
};
CONST(Wdg_ConfigType, CAN_CONST) WdgSettingerrorConfig_1 =
{
			&WdgConfigSetTypeerror1,
};
CONST(SWT_Module_Config_Type, WDG_CONST)WdgConfigSetTypeerror2 =
{
	    .SWT_ModuleID = SWT2,
	    .SWT_DefaultRunMode = 10,
	    .u8Wdg_GptTimerChannel = (Gpt_ChannelType)0U,
	    .u32Wdg_TriggerSourceClock = (uint32)60000,
	    .SWT_Config = { 0, 0, 0},
	    .SWT_Callback =NULL_PTR
};
CONST(Wdg_ConfigType, CAN_CONST) WdgSettingerrorConfig_2 =
{
			&WdgConfigSetTypeerror2,
};
CONST(SWT_Module_Config_Type, WDG_CONST)WdgConfigSetTypeerror3 =
{
	    .SWT_ModuleID = SWT3,
	    .SWT_DefaultRunMode = 10,
	    .u8Wdg_GptTimerChannel = (Gpt_ChannelType)0U,
	    .u32Wdg_TriggerSourceClock = (uint32)60000,
	    .SWT_Config = { 0, 0, 0},
	    .SWT_Callback =NULL_PTR
};
CONST(Wdg_ConfigType, CAN_CONST) WdgSettingerrorConfig_3 =
{
			&WdgConfigSetTypeerror3,
};
void SWT_FCCU_Init(void)
{
    Mcu_FccuInit();
	//(void)Mcu_LLD_FccuInit(&Mcu_FccuCfg);
}


void testwdg0166()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
    {
        PSPRINTF("testwdg0166 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0166 is E_NOT_OK\n");
    }
#endif
}

void testwdg0167()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
    {
        PSPRINTF("testwdg0167 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0167 is E_NOT_OK\n");
    }
#endif
}
void testwdg0168()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
    {
        PSPRINTF("testwdg0168 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0168 is E_NOT_OK\n");
    }
#endif
}
void testwdg0169()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
    {
        PSPRINTF("testwdg0169 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0169 is E_NOT_OK\n");
    }
#endif
}
void testwdg0170()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
    {
        PSPRINTF("testwdg0170 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0170 is E_NOT_OK\n");
    }
#endif
}
void testwdg0171()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
       {
           PSPRINTF("testwdg0171 is E_OK\n");
       }
       else{
           PSPRINTF("testwdg0171 is E_NOT_OK\n");
       }
#endif
}
void testwdg0172()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
          {
              PSPRINTF("testwdg0172 is E_OK\n");
          }
          else{
              PSPRINTF("testwdg0172 is E_NOT_OK\n");
          }
#endif
}
void testwdg0173()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
    {
        PSPRINTF("testwdg0173 is E_OK\n");
    }
    else{
       PSPRINTF("testwdg0173 is E_NOT_OK\n");
   }
#endif
}

void testwdg0174()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);

    if(Wdg_176_ModId0_SetMode(10)==1)
    {
        PSPRINTF("testwdg0174() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0174() is E_NOT_OK\n");
    }
}
void testwdg0175()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    if(Wdg_176_ModId1_SetMode(10)==1)
    {
        PSPRINTF("testwdg0175() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0175() is E_NOT_OK\n");
    }
}
void testwdg0176()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    if(Wdg_176_ModId2_SetMode(10)==1)
    {
        PSPRINTF("testwdg0176() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0176() is E_NOT_OK\n");
    }
}
void testwdg0177()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    if(Wdg_176_ModId3_SetMode(10)==1)
    {
        PSPRINTF("testwdg0177() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0177() is E_NOT_OK\n");
    }
}



#if (WDGINSTANCE0 == STD_ON)
void testwdg0025()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(NULL);
    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
        PSPRINTF("testwdg0025 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0025 is E_NOT_OK\n");
    }
}
void testwdg0026()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(NULL);

    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
    	Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
        PSPRINTF("testwdg0026 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0026 is E_NOT_OK\n");
    }
}
void testwdg0027()
{
    if(WDG_DISABLE_ALLOWED==STD_OFF && WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
        if(Wdg_E_Disable_Rejected.id==1 && Wdg_E_Disable_Rejected.state == STD_ON )
        {
            PSPRINTF("testwdg0027 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0027 is E_NOT_OK\n");
        }
    }
}



void testwdg0028()
{
    if(WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId0_Init(&WdgSettingerrorConfig_0);
        if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
        {
            PSPRINTF("testwdg0028 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0028 is E_NOT_OK\n");
        }
    }
}
void testwdg0029()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId0_Init(&WdgSettingerrorConfig_0);
        if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
        {
            PSPRINTF("testwdg0029 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0029 is E_NOT_OK\n");
        }
    }
}
extern eWdg_DriverStatus[WDG_INSTANCES_NUM];
void testwdg0030()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
        PSPRINTF("eWdg_DriverStatus[0]:%d\n",eWdg_DriverStatus[0]);
    }
}
void testwdg0031()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    if(Wdg_176_ModId0_SetMode(WDGIF_OFF_MODE)==0)
    {
        PSPRINTF("testwdg0031() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0031() is E_NOT_OK\n");
    }
}

void testwdg0032()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(10);
    if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON )
    {
        PSPRINTF("testwdg0032 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0032 is E_NOT_OK\n");
    }

}


void testwdg0033()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    if(WDG_DISABLE_ALLOWED==STD_OFF)
    {
        Wdg_176_ModId0_SetMode(WDGIF_OFF_MODE);
        if(Wdg_E_Disable_Rejected.id==1&&Wdg_E_Disable_Rejected.state==STD_ON )
        {
            PSPRINTF("testwdg0033 is E_OK\n");
        }else{
            PSPRINTF("testwdg0033 is E_NOT_OK\n");
        }

    }
}

void testwdg0034()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
        if(WDG_E_DRIVER_STATE==Det_ErrorId &&Det_ApiId == WDG_SETMODE_ID)
        {
            PSPRINTF("testwdg0034 is E_OK\n");
        }else{
            PSPRINTF("testwdg0034 is E_NOT_OK\n");
        }
    }
}


void testwdg0035()
{
	Gpt_Init(&GptChannelConfigSet);
	Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId0_SetTriggerCondition(6000);
        if(WDG_E_PARAM_TIMEOUT==Det_ErrorId &&Det_ApiId == WDG_SETTRIGGERCONDITION_ID)
        {
            PSPRINTF("testwdg0035 is E_OK\n");
        }else{
            PSPRINTF("testwdg0035 is E_NOT_OK\n");
        }
    }
}
void testwdg0036()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId0_GetVersionInfo(NULL);
        if(WDG_E_PARAM_POINTER==Det_ErrorId &&Det_ApiId == WDG_GETVERSION_ID )
        {
            PSPRINTF("testwdg0036 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0036 is E_NOT_OK\n");
        }
    }
}
#else

void testwdg0025()
{

    PSPRINTF("testwdg0025 NULL\n");
}
void testwdg0026()
{

    PSPRINTF("testwdg0026 NULL\n");
}

void testwdg0027()
{

    PSPRINTF("testwdg0027 NULL\n");
}
void testwdg0028()
{
    PSPRINTF("testwdg0028 NULL\n");
}
void testwdg0029()
{
    PSPRINTF("testwdg0029 NULL\n");
}
void testwdg0030()
{
    PSPRINTF("testwdg0030 NULL\n");
}
void testwdg0031()
{
    PSPRINTF("testwdg0031 NULL\n");
}
void testwdg0032()
{
    PSPRINTF("testwdg0032 NULL\n");
}
void testwdg0033()
{
    PSPRINTF("testwdg0033 NULL\n");
}
void testwdg0034()
{
    PSPRINTF("testwdg0034 NULL\n");
}
void testwdg0035()
{
    PSPRINTF("testwdg0035 NULL\n");
}
void testwdg0036()
{
    PSPRINTF("testwdg0036 NULL\n");
}
#endif

#if (WDGINSTANCE1 == STD_ON)
void testwdg0037()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(NULL);
    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
        PSPRINTF("testwdg0037 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0037 is E_NOT_OK\n");
    }
}
void testwdg0038()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(NULL);

    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
    	Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
        PSPRINTF("testwdg0038 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0038 is E_NOT_OK\n");
    }
}
void testwdg0039()
{
    if(WDG_DISABLE_ALLOWED==STD_OFF && WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
        if(Wdg_E_Disable_Rejected.id==1 && Wdg_E_Disable_Rejected.state == STD_ON)
        {
            PSPRINTF("testwdg0039 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0039 is E_NOT_OK\n");
        }
    }
}

void testwdg0040()
{
    if(WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId1_Init(&WdgSettingerrorConfig_1);
        if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
        {
            PSPRINTF("testwdg0040 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0040 is E_NOT_OK\n");
        }
    }
}
void testwdg0041()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId1_Init(&WdgSettingerrorConfig_1);
        if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
        {
            PSPRINTF("testwdg0041 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0041 is E_NOT_OK\n");
        }
    }
}

void testwdg0042()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
        PSPRINTF("eWdg_DriverStatus[1]:%d\n",eWdg_DriverStatus[1]);
    }
}
void testwdg0043()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    if(Wdg_176_ModId1_SetMode(WDGIF_OFF_MODE)==0)
    {
        PSPRINTF("testwdg0043() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0043() is E_NOT_OK\n");
    }
}

void testwdg0044()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(10);
    if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
    {
        PSPRINTF("testwdg0044 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0044 is E_NOT_OK\n");
    }

}


void testwdg0045()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    if(WDG_DISABLE_ALLOWED==STD_OFF)
    {
        Wdg_176_ModId1_SetMode(WDGIF_OFF_MODE);
        if(Wdg_E_Disable_Rejected.id==1&&Wdg_E_Disable_Rejected.state==STD_ON)
        {
            PSPRINTF("testwdg0045 is E_OK\n");
        }else{
            PSPRINTF("testwdg0045 is E_NOT_OK\n");
        }

    }
}

void testwdg0046()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
        if(WDG_E_DRIVER_STATE==Det_ErrorId &&Det_ApiId == WDG_SETMODE_ID)
        {
            PSPRINTF("testwdg0046 is E_OK\n");
        }else{
            PSPRINTF("testwdg0046 is E_NOT_OK\n");
        }
    }
}


void testwdg0047()
{
	Gpt_Init(&GptChannelConfigSet);
	Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId1_SetTriggerCondition(6000);
        if(WDG_E_PARAM_TIMEOUT==Det_ErrorId &&Det_ApiId == WDG_SETTRIGGERCONDITION_ID)
        {
            PSPRINTF("testwdg0047 is E_OK\n");
        }else{
            PSPRINTF("testwdg0047 is E_NOT_OK\n");
        }
    }
}
void testwdg0048()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId1_GetVersionInfo(NULL);
        if(WDG_E_PARAM_POINTER==Det_ErrorId &&Det_ApiId == WDG_GETVERSION_ID )
        {
            PSPRINTF("testwdg0048 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0048 is E_NOT_OK\n");
        }
    }
}
#else
void testwdg0037()
{

    PSPRINTF("testwdg0037 NULL\n");
}
void testwdg0038()
{
    PSPRINTF("testwdg0038 NULL\n");
}
void testwdg0039()
{

    PSPRINTF("testwdg0039 NULL\n");
}
void testwdg0040()
{
    PSPRINTF("testwdg0040 NULL\n");
}
void testwdg0041()
{
    PSPRINTF("testwdg0041 NULL\n");
}
void testwdg0042()
{
    PSPRINTF("testwdg0042 NULL\n");
}
void testwdg0043()
{
    PSPRINTF("testwdg0043 NULL\n");
}
void testwdg0044()
{
    PSPRINTF("testwdg0044 NULL\n");
}
void testwdg0045()
{
    PSPRINTF("testwdg0045 NULL\n");
}
void testwdg0046()
{
    PSPRINTF("testwdg0046 NULL\n");
}
void testwdg0047()
{
    PSPRINTF("testwdg0047 NULL\n");
}
void testwdg0048()
{
    PSPRINTF("testwdg0048 NULL\n");
}
#endif
#if (WDGINSTANCE2 == STD_ON)
void testwdg0049()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(NULL);
    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
        PSPRINTF("testwdg0049 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0049 is E_NOT_OK\n");
    }
}
void testwdg0050()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(NULL);

    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
    	Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
        PSPRINTF("testwdg0050 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0050 is E_NOT_OK\n");
    }
}
void testwdg0051()
{
    if(WDG_DISABLE_ALLOWED==STD_OFF && WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
        if(Wdg_E_Disable_Rejected.id==1 && Wdg_E_Disable_Rejected.state == STD_ON)
        {
            PSPRINTF("testwdg0051 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0051 is E_NOT_OK\n");
        }
    }
}

void testwdg0052()
{
    if(WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId2_Init(&WdgSettingerrorConfig_2);
        if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
        {
            PSPRINTF("testwdg0052 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0052 is E_NOT_OK\n");
        }
    }
}
void testwdg0053()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId2_Init(&WdgSettingerrorConfig_2);
        if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
        {
            PSPRINTF("testwdg0053 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0053 is E_NOT_OK\n");
        }
    }
}

void testwdg0054()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
        PSPRINTF("eWdg_DriverStatus[2]:%d\n",eWdg_DriverStatus[2]);
    }
}
void testwdg0055()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    if(Wdg_176_ModId2_SetMode(WDGIF_OFF_MODE)==0)
    {
        PSPRINTF("testwdg0055() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0055() is E_NOT_OK\n");
    }
}

void testwdg0056()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(10);
    if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
    {
        PSPRINTF("testwdg0056 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0056 is E_NOT_OK\n");
    }

}


void testwdg0057()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    if(WDG_DISABLE_ALLOWED==STD_OFF)
    {
        Wdg_176_ModId2_SetMode(WDGIF_OFF_MODE);
        if(Wdg_E_Disable_Rejected.id==1&&Wdg_E_Disable_Rejected.state==STD_ON)
        {
            PSPRINTF("testwdg0057 is E_OK\n");
        }else{
            PSPRINTF("testwdg0057 is E_NOT_OK\n");
        }

    }
}

void testwdg0058()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
        if(WDG_E_DRIVER_STATE==Det_ErrorId &&Det_ApiId == WDG_SETMODE_ID)
        {
            PSPRINTF("testwdg0058 is E_OK\n");
        }else{
            PSPRINTF("testwdg0058 is E_NOT_OK\n");
        }
    }
}


void testwdg0059()
{
	Gpt_Init(&GptChannelConfigSet);
	Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId2_SetTriggerCondition(6000);
        if(WDG_E_PARAM_TIMEOUT==Det_ErrorId &&Det_ApiId == WDG_SETTRIGGERCONDITION_ID)
        {
            PSPRINTF("testwdg0059 is E_OK\n");
        }else{
            PSPRINTF("testwdg0059 is E_NOT_OK\n");
        }
    }
}
void testwdg0060()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId2_GetVersionInfo(NULL);
        if(WDG_E_PARAM_POINTER==Det_ErrorId &&Det_ApiId == WDG_GETVERSION_ID )
        {
            PSPRINTF("testwdg0060 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0060 is E_NOT_OK\n");
        }
    }
}
#else
void testwdg0049()
{
    PSPRINTF("testwdg0049 NULL\n");
}
void testwdg0050()
{
    PSPRINTF("testwdg0050 NULL\n");
}
void testwdg0051()
{
    PSPRINTF("testwdg0051 NULL\n");
}
void testwdg0052()
{
    PSPRINTF("testwdg0052 NULL\n");
}
void testwdg0053()
{
    PSPRINTF("testwdg0053 NULL\n");
}
void testwdg0054()
{
    PSPRINTF("testwdg0054 NULL\n");
}
void testwdg0055()
{
    PSPRINTF("testwdg0055 NULL\n");
}
void testwdg0056()
{
    PSPRINTF("testwdg0056 NULL\n");
}
void testwdg0057()
{
    PSPRINTF("testwdg0057 NULL\n");
}
void testwdg0058()
{
    PSPRINTF("testwdg0058 NULL\n");
}
void testwdg0059()
{
    PSPRINTF("testwdg0059 NULL\n");
}
void testwdg0060()
{
    PSPRINTF("testwdg0060 NULL\n");
}
#endif
#if (WDGINSTANCE3 == STD_ON)
void testwdg0061()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(NULL);
    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
        PSPRINTF("testwdg0061 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0061 is E_NOT_OK\n");
    }
}
void testwdg0062()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(NULL);

    if(WDG_DEV_ERROR_REPORT == STD_ON && Det_ErrorId == WDG_E_INIT_FAILED)
    {
    	Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
        PSPRINTF("testwdg0062 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0062 is E_NOT_OK\n");
    }
}
void testwdg0063()
{
    if(WDG_DISABLE_ALLOWED==STD_OFF && WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
        if(Wdg_E_Disable_Rejected.id==1 && Wdg_E_Disable_Rejected.state == STD_ON)
        {
            PSPRINTF("testwdg0063 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0063 is E_NOT_OK\n");
        }
    }
}

void testwdg0064()
{
    if(WDG_DEM_REPORT_ERROR_ENADBLE == STD_OFF&&WDG_DEV_ERROR_REPORT==STD_OFF)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId3_Init(&WdgSettingerrorConfig_3);
        if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
        {
            PSPRINTF("testwdg0064 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0064 is E_NOT_OK\n");
        }
    }
}
void testwdg0065()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId3_Init(&WdgSettingerrorConfig_3);
        if(WDG_E_PARAM_CONFIG==Det_ErrorId &&Det_ApiId == WDG_INIT_ID)
        {
            PSPRINTF("testwdg0065 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0065 is E_NOT_OK\n");
        }
    }
}

void testwdg0066()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
        PSPRINTF("eWdg_DriverStatus[3]:%d\n",eWdg_DriverStatus[3]);
    }
}
void testwdg0067()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    if(Wdg_176_ModId3_SetMode(WDGIF_OFF_MODE)==0)
    {
        PSPRINTF("testwdg0067() is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0067() is E_NOT_OK\n");
    }
}

void testwdg0068()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(10);
    if(Wdg_E_Mode_Failed.id==2 && Wdg_E_Mode_Failed.state == STD_ON)
    {
        PSPRINTF("testwdg0068 is E_OK\n");
    }
    else{
        PSPRINTF("testwdg0068 is E_NOT_OK\n");
    }

}


void testwdg0069()
{
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    if(WDG_DISABLE_ALLOWED==STD_OFF)
    {
        Wdg_176_ModId3_SetMode(WDGIF_OFF_MODE);
        if(Wdg_E_Disable_Rejected.id==1&&Wdg_E_Disable_Rejected.state==STD_ON)
        {
            PSPRINTF("testwdg0069 is E_OK\n");
        }else{
            PSPRINTF("testwdg0069 is E_NOT_OK\n");
        }

    }
}

void testwdg0070()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Gpt_Init(&GptChannelConfigSet);
        Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
        if(WDG_E_DRIVER_STATE==Det_ErrorId &&Det_ApiId == WDG_SETMODE_ID)
        {
            PSPRINTF("testwdg0070 is E_OK\n");
        }else{
            PSPRINTF("testwdg0070 is E_NOT_OK\n");
        }
    }
}


void testwdg0071()
{
	Gpt_Init(&GptChannelConfigSet);
	Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId3_SetTriggerCondition(6000);
        if(WDG_E_PARAM_TIMEOUT==Det_ErrorId &&Det_ApiId == WDG_SETTRIGGERCONDITION_ID)
        {
            PSPRINTF("testwdg0071 is E_OK\n");
        }else{
            PSPRINTF("testwdg0071 is E_NOT_OK\n");
        }
    }
}
void testwdg0072()
{
    if(WDG_DEV_ERROR_REPORT==STD_ON)
    {
        Wdg_176_ModId3_GetVersionInfo(NULL);
        if(WDG_E_PARAM_POINTER==Det_ErrorId &&Det_ApiId == WDG_GETVERSION_ID )
        {
            PSPRINTF("testwdg0072 is E_OK\n");
        }
        else{
            PSPRINTF("testwdg0072 is E_NOT_OK\n");
        }
    }
}
#else
void testwdg0061()
{

    PSPRINTF("testwdg0061 NULL\n");
}
void testwdg0062()
{
    PSPRINTF("testwdg0062 NULL\n");
}
void testwdg0063()
{

    PSPRINTF("testwdg0063 NULL\n");
}
void testwdg0064()
{
    PSPRINTF("testwdg0064 NULL\n");
}
void testwdg0065()
{
    PSPRINTF("testwdg0065 NULL\n");
}
void testwdg0066()
{
    PSPRINTF("testwdg0066 NULL\n");
}
void testwdg0067()
{
    PSPRINTF("testwdg0067 NULL\n");
}
void testwdg0068()
{
    PSPRINTF("testwdg0068 NULL\n");
}
void testwdg0069()
{
    PSPRINTF("testwdg0069 NULL\n");
}
void testwdg0070()
{
    PSPRINTF("testwdg0070 NULL\n");
}
void testwdg0071()
{
    PSPRINTF("testwdg0071 NULL\n");
}
void testwdg0072()
{
    PSPRINTF("testwdg0072 NULL\n");

}

#endif



void testwdg0073()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
#else
    PSPRINTF("testwdg0073 is NULL\n");
#endif
}

void testwdg0074()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#else
    PSPRINTF("testwdg0074 is NULL\n");
#endif
}


void testwdg0075()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1; 
#else
    PSPRINTF("testwdg0075 is NULL\n");
#endif
}

void testwdg0076()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#else
    PSPRINTF("testwdg0076 is NULL\n");
#endif
}


void testwdg0077()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;

#else
    PSPRINTF("testwdg0077 is NULL\n");
#endif
}

void testwdg0078()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#else
    PSPRINTF("testwdg0078 is NULL\n");
#endif
}


void testwdg0079()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
#else
    PSPRINTF("testwdg0079 is NULL\n");
#endif
}

void testwdg0080()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#else
    PSPRINTF("testwdg0080 is NULL\n");
#endif
}

void testwdg0081()
{
#if (WDGINSTANCE3==STD_ON)
    Std_VersionInfoType Versioninfo;
    Wdg_176_ModId3_GetVersionInfo(&Versioninfo);
    PSPRINTF("vendorID[%d] moduleID[%d] sw_major_version[%d] sw_minor_version[%d] sw_patch_version[%d]\n",
                 Versioninfo.vendorID, Versioninfo.moduleID, Versioninfo.sw_major_version, Versioninfo.sw_minor_version, Versioninfo.sw_patch_version);
#endif
}

void testwdg0082()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0082 is NULL\n");
#endif
}
void testwdg0083()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0083 is NULL\n");
#endif
}


void testwdg0084()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0084 is NULL\n");
#endif
}
void testwdg0085()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0085 is NULL\n");
#endif
}


void testwdg0086()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0086 is NULL\n");
#endif
}
void testwdg0087()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0087 is NULL\n");
#endif
}


void testwdg0088()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0088 is NULL\n");
#endif
}
void testwdg0089()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0089 is NULL\n");
#endif
}
void testwdg0090()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
#else
    PSPRINTF("testwdg0090 is NULL\n");
#endif
}

void testwdg0091()
{
#if( WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#else
    PSPRINTF("testwdg0091 is NULL\n");
#endif
}


void testwdg0092()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
#else
    PSPRINTF("testwdg0092 is NULL\n");
#endif
}

void testwdg0093()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#else
    PSPRINTF("testwdg0093 is NULL\n");
#endif
}


void testwdg0094()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
#else
    PSPRINTF("testwdg0094 is NULL\n");
#endif
}

void testwdg0095()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#else
    PSPRINTF("testwdg0095 is NULL\n");
#endif
}


void testwdg0096()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
#else
    PSPRINTF("testwdg0096 is NULL\n");
#endif
}

void testwdg0097()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#else
    PSPRINTF("testwdg0097 is NULL\n");
#endif
}

void testwdg0098()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0098 is NULL\n");
#endif
}
void testwdg0099()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0099 is NULL\n");
#endif
}


void testwdg0100()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0100 is NULL\n");
#endif
}
void testwdg0101()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0101 is NULL\n");
#endif
}


void testwdg0102()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0102 is NULL\n");
#endif
}
void testwdg0103()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0103 is NULL\n");
#endif
}


void testwdg0104()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0104 is NULL\n");
#endif
}
void testwdg0105()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0105 is NULL\n");
#endif
}
void testwdg0106()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
#else
    PSPRINTF("testwdg0106 is NULL\n");
#endif
}

void testwdg0107()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#else
    PSPRINTF("testwdg0107 is NULL\n");
#endif
}


void testwdg0108()
{
#if( WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
#else
    PSPRINTF("testwdg0108 is NULL\n");
#endif
}

void testwdg0109()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#else
    PSPRINTF("testwdg0109 is NULL\n");
#endif
}


void testwdg0110()
{
#if (WDGINSTANCE2 == STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
#else
    PSPRINTF("testwdg0110 is NULL\n");
#endif
}

void testwdg0111()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#else
    PSPRINTF("testwdg0111 is NULL\n");
#endif
}


void testwdg0112()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
#else
    PSPRINTF("testwdg0112 is NULL\n");
#endif
}

void testwdg0113()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#else
    PSPRINTF("testwdg0113 is NULL\n");
#endif
}

void testwdg0114()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0114 is NULL\n");
#endif
}
void testwdg0115()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0115 is NULL\n");
#endif
}


void testwdg0116()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#else
    PSPRINTF("testwdg0116 is NULL\n");
#endif
}
void testwdg0117()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0117 is NULL\n");
#endif
}


void testwdg0118()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
    testwdg_flag=2;
#else
    PSPRINTF("testwdg0118 is NULL\n");
#endif
}
void testwdg0119()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0119 is NULL\n");
#endif
}


void testwdg0120()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0120 is NULL\n");
#endif
}
void testwdg0121()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0121 is NULL\n");
#endif
}
void testwdg0122()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
#else
    PSPRINTF("testwdg0122 is NULL\n");
#endif
}

void testwdg0123()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#else
    PSPRINTF("testwdg0123 is NULL\n");
#endif
}


void testwdg0124()
{
#if( WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
#else
    PSPRINTF("testwdg0124 is NULL\n");
#endif
}

void testwdg0125()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#else
    PSPRINTF("testwdg0125 is NULL\n");
#endif
}


void testwdg0126()
{
#if( WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
#else
    PSPRINTF("testwdg0126 is NULL\n");
#endif
}

void testwdg0127()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#else
    PSPRINTF("testwdg0127 is NULL\n");
#endif
}


void testwdg0128()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
#else
    PSPRINTF("testwdg0128 is NULL\n");
#endif
}

void testwdg0129()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#else
    PSPRINTF("testwdg0129 is NULL\n");
#endif
}
void testwdg0130()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0130 is NULL\n");
#endif
}
void testwdg0131()
{
#if (WDGINSTANCE0==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0131 is NULL\n");
#endif
}


void testwdg0132()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#else
    PSPRINTF("testwdg0132 is NULL\n");
#endif
}
void testwdg0133()
{
#if (WDGINSTANCE1==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0133 is NULL\n");
#endif
}


void testwdg0134()
{
#if (WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0134 is NULL\n");
#endif
}
void testwdg0135()
{
#if( WDGINSTANCE2==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0135 is NULL\n");
#endif
}


void testwdg0136()
{
#if (WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0136 is NULL\n");
#endif
}
void testwdg0137()
{
#if( WDGINSTANCE3==STD_ON)
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

#else
    PSPRINTF("testwdg0137 is NULL\n");
#endif
}

void testwdg0138()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
    testwdg_flag=4;
}
void testwdg0139()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
}
void testwdg0140()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
    testwdg_flag=4;
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
#endif
}
void testwdg0141()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
#endif
}

void testwdg0142()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
    testwdg_flag=4;
}
void testwdg0143()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
}
void testwdg0144()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
    testwdg_flag=4;
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
#endif
}
void testwdg0145()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
#endif
}



void testwdg0146()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
    testwdg_flag=4;
}
void testwdg0147()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
}
void testwdg0148()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
    testwdg_flag=4;
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
#endif
}
void testwdg0149()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
#endif
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
#endif
}

void testwdg0150()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag=0;
    Wdg_176_ModId0_SetMode(WDGIF_OFF_MODE);
#endif
}
void testwdg0151()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0152()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);
    testwdg_flag=0;
    Wdg_176_ModId0_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0153()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_FAST_MODE);

    Wdg_176_ModId0_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0154()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag=1;
    Wdg_176_ModId1_SetMode(WDGIF_OFF_MODE);
#endif
}
void testwdg0155()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0156()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);
    testwdg_flag=1;
    Wdg_176_ModId1_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0157()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_FAST_MODE);

    Wdg_176_ModId1_SetMode(WDGIF_OFF_MODE);
#endif
}
void testwdg0158()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag=2;
    Wdg_176_ModId2_SetMode(WDGIF_OFF_MODE);
#endif
}
void testwdg0159()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0160()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);
    testwdg_flag=2;
    Wdg_176_ModId2_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0161()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_FAST_MODE);

    Wdg_176_ModId2_SetMode(WDGIF_OFF_MODE);
#endif
}
void testwdg0162()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag=3;
    Wdg_176_ModId3_SetMode(WDGIF_OFF_MODE);
#endif
}
void testwdg0163()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0164()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);
    testwdg_flag=3;
    Wdg_176_ModId3_SetMode(WDGIF_OFF_MODE);
#endif
}

void testwdg0165()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_FAST_MODE);

    Wdg_176_ModId3_SetMode(WDGIF_OFF_MODE);
#endif
}


void testwdg0178()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag = 0;
#endif
}
void testwdg0179()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
#endif
}
void testwdg0180()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag = 1;
#endif
}
void testwdg0181()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
#endif
}
void testwdg0182()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag = 2;
#endif
}
void testwdg0183()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
#endif
}
void testwdg0184()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag = 3;
#endif
}
void testwdg0185()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
#endif
}


void testwdg0186()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    testwdg_flag = 0;
    Wdg_176_ModId0_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0187()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE0==STD_ON)
    Wdg_176_ModId0_Init(&WdgSettingsConfig_0);
    Wdg_176_ModId0_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0188()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    testwdg_flag = 1;
    Wdg_176_ModId1_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0189()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE1==STD_ON)
    Wdg_176_ModId1_Init(&WdgSettingsConfig_1);
    Wdg_176_ModId1_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0190()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    testwdg_flag = 2;
    Wdg_176_ModId2_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0191()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE2==STD_ON)
    Wdg_176_ModId2_Init(&WdgSettingsConfig_2);
    Wdg_176_ModId2_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0192()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    testwdg_flag = 3;
    Wdg_176_ModId3_SetMode(WDGIF_SLOW_MODE);
#endif
}
void testwdg0193()
{
    SWT_FCCU_Init();
    Gpt_Init(&GptChannelConfigSet);
#if (WDGINSTANCE3==STD_ON)
    Wdg_176_ModId3_Init(&WdgSettingsConfig_3);
    Wdg_176_ModId3_SetMode(WDGIF_SLOW_MODE);
#endif
}







FUNC(void, GPT_CODE) Wdg_GPT_GTM_TOM_LLD_SetIRQ(void)
{
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_813, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_813, &TOM0_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_813);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_813, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_813, &TOM0_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_813);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_814, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_814, &TOM0_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_814);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_814, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_814, &TOM0_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_814);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_815, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_815, &TOM0_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_815);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_815, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_815, &TOM0_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_815);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_816, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_816, &TOM0_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_816);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_816, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_816, &TOM0_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_816);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_817, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_817, &TOM0_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_817);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_817, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_817, &TOM0_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_817);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_818, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_818, &TOM0_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_818);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_818, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_818, &TOM0_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_818);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_819, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_819, &TOM0_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_819);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_819, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_819, &TOM0_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_819);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_820, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_820, &TOM0_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_820);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_820, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_820, &TOM0_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_820);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_821, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_821, &TOM1_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_821);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_821, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_821, &TOM1_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_821);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_822, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_822, &TOM1_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_822);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_822, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_822, &TOM1_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_822);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_823, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_823, &TOM1_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_823);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_823, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_823, &TOM1_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_823);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_824, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_824, &TOM1_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_824);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_824, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_824, &TOM1_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_824);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_825, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_825, &TOM1_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_825);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_825, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_825, &TOM1_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_825);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_826, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_826, &TOM1_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_826);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_826, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_826, &TOM1_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_826);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_827, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_827, &TOM1_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_827);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_827, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_827, &TOM1_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_827);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_828, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_828, &TOM1_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_828);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_828, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_828, &TOM1_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_828);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_829, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_829, &TOM2_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_829);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_829, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_829, &TOM2_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_829);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_830, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_830, &TOM2_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_830);
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_830, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_830, &TOM2_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_830);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_831, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_831, &TOM2_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_831);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_831, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_831, &TOM2_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_831);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_832, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_832, &TOM2_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_832);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_832, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_832, &TOM2_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_832);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_833, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_833, &TOM2_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_833);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_833, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_833, &TOM2_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_833);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_834, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_834, &TOM2_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_834);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_834, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_834, &TOM2_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_834);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_835, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_835, &TOM2_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_835);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_835, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_835, &TOM2_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_835);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_836, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_836, &TOM2_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_836);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_836, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_836, &TOM2_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_836);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_899, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_899, &TOM3_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_899);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_899, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_899, &TOM3_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_899);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_900, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_900, &TOM3_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_900);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_900, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_900, &TOM3_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_900);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_901, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_901, &TOM3_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_901);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_901, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_901, &TOM3_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_901);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_902, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_902, &TOM3_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_902);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_902, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_902, &TOM3_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_902);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_903, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_903, &TOM3_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_903);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_903, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_903, &TOM3_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_903);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_904, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_904, &TOM3_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_904);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_904, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_904, &TOM3_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_904);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_905, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_905, &TOM3_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_905);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_905, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_905, &TOM3_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_905);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_906, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_906, &TOM3_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_906);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_906, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_906, &TOM3_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_906);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_907, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_907, &TOM4_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_907);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_907, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_907, &TOM4_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_907);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_908, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_908, &TOM4_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_908);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_908, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_908, &TOM4_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_908);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_909, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_909, &TOM4_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_909);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_909, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_909, &TOM4_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_909);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_910, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_910, &TOM4_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_910);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_910, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_910, &TOM4_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_910);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_911, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_911, &TOM4_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_911);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_911, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_911, &TOM4_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_911);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_912, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_912, &TOM4_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_912);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_912, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_912, &TOM4_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_912);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_913, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_913, &TOM4_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_913);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_913, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_913, &TOM4_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_913);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_914, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_914, &TOM4_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_914);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_914, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_914, &TOM4_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_914);

}

FUNC(Std_ReturnType, GPT_CODE) Wdg_Gpt_Pit_SetIRQ(void)
{
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_226, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_226, &PIT0_CH0_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_226);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_227, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_227, &PIT0_CH1_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_227);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_228, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_228, &PIT0_CH2_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_228);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_229, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_229, &PIT0_CH3_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_229);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_230, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_230, &PIT0_CH4_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_230);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_231, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_231, &PIT0_CH5_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_231);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_232, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_232, &PIT0_CH6_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_232);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_233, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_233, &PIT0_CH7_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_233);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_239, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_239, &RTI_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_239);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_240, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_240, &PIT1_CH0_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_240);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_241, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_241, &PIT1_CH1_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_241);
}

FUNC(Std_ReturnType, GPT_CODE) Wdg_Gpt_Stm_SetIRQ(void)
{
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_36, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_36, &STM0_CH0_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_36);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_37, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_37, &STM0_CH1_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_37);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_38, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_38, &STM0_CH2_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_38);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_39, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_39, &STM0_CH3_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_39);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_40, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_40, &STM1_CH0_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_40);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_41, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_41, &STM1_CH1_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_41);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_42, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_42, &STM1_CH2_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_42);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_43, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_43, &STM1_CH3_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_43);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_44, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_44, &STM2_CH0_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_44);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_45, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_45, &STM2_CH1_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_45);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_46, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_46, &STM2_CH2_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_46);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_47, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_47, &STM2_CH3_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_47);
}
int wdg_func(int argc, char *agrv[])
{
	static uint8 wdgsetIrqFlag = 1;

	if(wdgsetIrqFlag)
	{
		Wdg_GPT_GTM_TOM_LLD_SetIRQ();
		Wdg_Gpt_Pit_SetIRQ();
		Wdg_Gpt_Stm_SetIRQ();
		wdgsetIrqFlag = 0;
	}


    if (argc == 2)
    {
        if (!strcmp(agrv[1], "swt_irq"))
        {
            SWT_IRQ();
        }

        else if (!strcmp(agrv[1], "help"))
        {
            PSPRINTF( "swt_irq ----- CMD ------- SWT_IRQ()\r\n");
            PSPRINTF( "help ----- CMD ------- ID of the test case\r\n");

            for(uint8 i = 0; i < WDG_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", wdg_funcs[i].name);
            }
        }
        else
        {
            uint32 id = (uint32)atoi(agrv[1]);
            PSPRINTF("%d\r\n", id);
            if((id >= 1) && (id <=WDG_TEST_CASE_MAX))
            {
                if(wdg_funcs[id-1].wdgfunc != NULL_PTR)
                {
                    wdg_funcs[id-1].wdgfunc();
                    return 0;
                }
                else if(wdg_funcs[id].wdgfunc == NULL_PTR)
                {
                    PSPRINTF("error: Test case is undefined\n");
                    return 0;
                }
            }
            PSPRINTF("error: Input invalid parameters[%s], please Use the 'wdg_test help' command to see the supported test instructions\n", agrv[1]);
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), wdg_test , wdg_func, deint or number of test case);





















































