#include "tester_adc.h"
#include "Adc_Cfg.h"
#include "intc_lld.h"
#include "Gpt_Stm_LLDriver.h"

extern CONST(Adc_ConfigType, ADC_CONST) Config;
extern VAR(Adc_RunningGroupType, ADC_VAR) sAdc_RunningGroup[ADC_CONFIG_GROUPS];
#define ADC_TEST_CASE_MAX sizeof(adc_funcs) / sizeof(AdcfuncMachine)

const static AdcfuncMachine adc_funcs[] =
{
#if 0
    {"ADC_0001", ADC_0001},
    {"ADC_0002", ADC_0002},
    {"ADC_0003", ADC_0003},
    {"ADC_0004", ADC_0004},
    {"ADC_0005", ADC_0005},
    {"ADC_0006", ADC_0006},
    {"ADC_0007", ADC_0007},
 #if (ADC_DEINIT_API == STD_ON)
     {"ADC_0008", ADC_0008},
     {"ADC_0009", ADC_0009},
 #endif
 #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
     {"ADC_0010", ADC_0010},
     {"ADC_0011", ADC_0011},
     {"ADC_0012", ADC_0012},
     {"ADC_0013", ADC_0013},
     {"ADC_0014", ADC_0014},
     {"ADC_0015", ADC_0015},
     {"ADC_0016", ADC_0016},
     {"ADC_0017", ADC_0017},
	 {"ADC_0207", ADC_0207},
	 {"ADC_0208", ADC_0208},
	 {"ADC_0212_213", ADC_0212_213},
	 {"ADC_0214_215", ADC_0214_215},
	 {"ADC_0216", ADC_0216},
	 {"ADC_0217", ADC_0217},
	 {"ADC_0218", ADC_0218},
	 {"ADC_0219_220", ADC_0219_220},
	 {"ADC_0262_265", ADC_0262_265},
	 {"ADC_0266_267", ADC_0266_267},
	 {"ADC_0268", ADC_0268},
	 {"ADC_0269", ADC_0269},
	 {"ADC_0270_271", ADC_0270_271},
	 {"ADC_0272_275", ADC_0272_275},
	 {"ADC_0276", ADC_0276},
	 {"ADC_0277", ADC_0277},
	 {"ADC_0278", ADC_0278},
	 {"ADC_0279", ADC_0279},
	 {"ADC_0280", ADC_0280},
	 {"ADC_0281", ADC_0281},
	 {"ADC_0282", ADC_0282},
	 {"ADC_0283", ADC_0283},
	 {"ADC_0284", ADC_0284},
	 {"ADC_0285", ADC_0285},
	 {"ADC_0286_287", ADC_0286_287},
	 {"ADC_0288_291", ADC_0288_291},
	 {"ADC_0292", ADC_0292},
	 {"ADC_0293", ADC_0293},
	 {"ADC_0294", ADC_0294},
	 {"ADC_0295", ADC_0295},
	 {"ADC_0296", ADC_0296},
	 {"ADC_0297", ADC_0297},
	 {"ADC_0298", ADC_0298},
	 {"ADC_0299", ADC_0299},
	 {"ADC_0300", ADC_0300},
	 {"ADC_0301_302", ADC_0301_302},
	 {"demo_AllChannel", demo_AllChannel},
 #endif
 #if (ADC_READ_GROUP_API == STD_ON)
     {"ADC_0018", ADC_0018},
     {"ADC_0019", ADC_0019},
     {"ADC_0020", ADC_0020},
	 {"ADC_0206", ADC_0206},
 #endif
 #if (ADC_HW_TRIGGER_API == STD_ON)
     {"ADC_0021", ADC_0021},
     {"ADC_0022", ADC_0022},
     {"ADC_0023", ADC_0023},
     {"ADC_0024", ADC_0024},
     {"ADC_0025", ADC_0025},
     {"ADC_0026", ADC_0026},
     {"ADC_0027", ADC_0027},
     {"ADC_0028", ADC_0028},
     {"ADC_0029", ADC_0029},
	 {"ADC_0209", ADC_0209},
	 {"ADC_0210", ADC_0210},
	 {"ADC_0211", ADC_0211},
	 {"ADC_0221_224", ADC_0221_224},
	 {"ADC_0225_226", ADC_0225_226},
	 {"ADC_0227", ADC_0227},
	 {"ADC_0228", ADC_0228},
	 {"ADC_0229_230", ADC_0229_230},
	 {"ADC_0231_234", ADC_0231_234},
	 {"ADC_0235", ADC_0235},
	 {"ADC_0236", ADC_0236},
	 {"ADC_0237", ADC_0237},
	 {"ADC_0238", ADC_0238},
	 {"ADC_0239", ADC_0239},
	 {"ADC_0240", ADC_0240},
	 {"ADC_0241", ADC_0241},
	 {"ADC_0242", ADC_0242},
	 {"ADC_0243", ADC_0243},
	 {"ADC_0244", ADC_0244},
	 {"ADC_0245_246", ADC_0245_246},
	 {"ADC_0247_250", ADC_0247_250},
	 {"ADC_0251", ADC_0251},
	 {"ADC_0252", ADC_0252},
	 {"ADC_0253", ADC_0253},
	 {"ADC_0254", ADC_0254},
	 {"ADC_0255", ADC_0255},
	 {"ADC_0256", ADC_0256},
	 {"ADC_0257", ADC_0257},
	 {"ADC_0258", ADC_0258},
	 {"ADC_0259", ADC_0259},
	 {"ADC_0260_261", ADC_0260_261},
 #endif
 #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
     {"ADC_0030", ADC_0030},
     {"ADC_0031", ADC_0031},
     {"ADC_0032", ADC_0032},
     {"ADC_0033", ADC_0033},
     {"ADC_0034", ADC_0034},
     {"ADC_0035", ADC_0035},
     {"ADC_0036", ADC_0036},
     {"ADC_0037", ADC_0037},
 #endif
     {"ADC_0038", ADC_0038},
     {"ADC_0039", ADC_0039},
     {"ADC_0040", ADC_0040},
     {"ADC_0041", ADC_0041},
     {"ADC_0042", ADC_0042},
     {"ADC_0043", ADC_0043},
     {"ADC_0044", ADC_0044},
 #if (ADC_VERSION_INFO_API == STD_ON)
     {"ADC_0045", ADC_0045},
     {"ADC_0046", ADC_0046},
 #endif
 #if (ADC_POWER_STATE_SUPPORTED == STD_ON)
     {"ADC_0047", ADC_0047},
     {"ADC_0048", ADC_0048},
     {"ADC_0049", ADC_0049},
     {"ADC_0050", ADC_0050},
 #endif
    {"demo", ADC_demo},
	{"demo_dma", ADC_demo_Dma},
	{"demo_int_dma", ADC_demo_Int_Dma},
#if (ADC_HW_TRIGGER_API == STD_ON)
	{"demo_etpu", ADC_demo_Etpu},
	{"demo_MultiGroup", ADC_demo_MultiGroup},
#endif
	{"demo_Mux", ADC_demo_ExternalMux},
	{"demo_PrioQueue", ADC_demo_PrioQueue},
	{"demo_Queue", ADC_demo_Queue},
#endif
	{"demo_service1", ADC_Project_Service1},
	{"demo_service2", ADC_Project_Service2},
	{"demo_service3", ADC_Project_Service3},
};

static CONST(IntrPrior, ADC_CONST) EQAdc_Intr_Prior[ADC_EQADC_MAX_INSTANCE * EQADC_RFIFO_COUNT] = {INTR_PRI_7, INTR_PRI_8, INTR_PRI_9, INTR_PRI_10, INTR_PRI_11, INTR_PRI_12, \
                                            INTR_PRI_7, INTR_PRI_8, INTR_PRI_9, INTR_PRI_10, INTR_PRI_11, INTR_PRI_12, \
                                            INTR_PRI_7, INTR_PRI_8, INTR_PRI_9, INTR_PRI_10, INTR_PRI_11, INTR_PRI_12, \
                                            INTR_PRI_7, INTR_PRI_8, INTR_PRI_9, INTR_PRI_10, INTR_PRI_11, INTR_PRI_12, \
                                            INTR_PRI_7, INTR_PRI_8, INTR_PRI_9, INTR_PRI_10, INTR_PRI_11, INTR_PRI_12};

static CONST(IntrId, ADC_CONST) EQAdc_Intr_Id[ADC_EQADC_MAX_INSTANCE * EQADC_RFIFO_COUNT] = {EQADC0_ADC01_GRP0_IRQ965, EQADC0_ADC01_GRP1_IRQ966, EQADC0_ADC01_GRP2_IRQ967, EQADC0_ADC01_GRP3_IRQ968, EQADC0_ADC01_GRP4_IRQ969, EQADC0_ADC01_GRP5_IRQ970, \
                                            EQADC1_ADC23_GRP0_IRQ971, EQADC1_ADC23_GRP1_IRQ972, EQADC1_ADC23_GRP2_IRQ973, EQADC1_ADC23_GRP3_IRQ974, EQADC1_ADC23_GRP4_IRQ975, EQADC1_ADC23_GRP5_IRQ976, \
                                            EQADC2_ADC45_GRP0_IRQ977, EQADC2_ADC45_GRP1_IRQ978, EQADC2_ADC45_GRP2_IRQ979, EQADC2_ADC45_GRP3_IRQ980, EQADC2_ADC45_GRP4_IRQ981, EQADC2_ADC45_GRP5_IRQ982, \
                                            EQADC3_ADC67_GRP0_IRQ983, EQADC3_ADC67_GRP1_IRQ984, EQADC3_ADC67_GRP2_IRQ985, EQADC3_ADC67_GRP3_IRQ986, EQADC3_ADC67_GRP4_IRQ987, EQADC3_ADC67_GRP5_IRQ988, \
                                            EQADC4_ADC89_GRP0_IRQ989, EQADC4_ADC89_GRP1_IRQ990, EQADC4_ADC89_GRP2_IRQ991, EQADC4_ADC89_GRP3_IRQ992, EQADC4_ADC89_GRP4_IRQ993, EQADC4_ADC89_GRP5_IRQ994};

static VAR(void, AUTOMATIC) (* const EQAdc_Irq_Func[ADC_EQADC_MAX_INSTANCE * EQADC_RFIFO_COUNT])(void) = {ADC01_GRP0, ADC01_GRP1, ADC01_GRP2, ADC01_GRP3, ADC01_GRP4, ADC01_GRP5, \
                                            ADC23_GRP0, ADC23_GRP1, ADC23_GRP2, ADC23_GRP3, ADC23_GRP4, ADC23_GRP5, \
                                            ADC45_GRP0, ADC45_GRP1, ADC45_GRP2, ADC45_GRP3, ADC45_GRP4, ADC45_GRP5, \
                                            ADC67_GRP0, ADC67_GRP1, ADC67_GRP2, ADC67_GRP3, ADC67_GRP4, ADC67_GRP5, \
                                            ADC89_GRP0, ADC89_GRP1, ADC89_GRP2, ADC89_GRP3, ADC89_GRP4, ADC89_GRP5};

FUNC(void, ADC_CODE) EQADC_EnableInterrupt \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_Fifo \
)
{
    VAR(uint16, AUTOMATIC) u16Adc_IrqIdx = u8Adc_Instance * EQADC_RFIFO_COUNT + u8Adc_Fifo;
    (void)INTC_LLD_Set_IRQ_Handle(EQAdc_Intr_Id[u16Adc_IrqIdx], EQAdc_Irq_Func[u16Adc_IrqIdx]);
    (void)INTC_LLD_Set_IRQ_Priority(EQAdc_Intr_Id[u16Adc_IrqIdx],EQAdc_Intr_Prior[u16Adc_IrqIdx]);
    (void)INTC_LLD_Set_IRQ_Enable(EQAdc_Intr_Id[u16Adc_IrqIdx]);
}

FUNC(void, ADC_CODE) EQADC_DisableInterrupt \
( \
    CONST(uint8, ADC_CONST) u8Adc_Instance, \
    CONST(uint8, ADC_CONST) u8Adc_Fifo \
)
{
    VAR(uint16, AUTOMATIC) u16Adc_IrqIdx = u8Adc_Instance * EQADC_RFIFO_COUNT + u8Adc_Fifo;
    (void)INTC_LLD_Set_IRQ_Disable(u16Adc_IrqIdx);
}

void EnableAdcInterrupt(void)
{
	EQADC_EnableInterrupt(0, 0);
	EQADC_EnableInterrupt(0, 1);

	EQADC_EnableInterrupt(1, 0);
	EQADC_EnableInterrupt(1, 1);

    EQADC_EnableInterrupt(2, 0);
	EQADC_EnableInterrupt(2, 1);

    EQADC_EnableInterrupt(3, 0);
	EQADC_EnableInterrupt(3, 1);

    EQADC_EnableInterrupt(4, 0);
	EQADC_EnableInterrupt(4, 1);
    EQADC_EnableInterrupt(4, 2);
    EQADC_EnableInterrupt(4, 3);
    EQADC_EnableInterrupt(4, 4);
    EQADC_EnableInterrupt(4, 5);
}

#if 0
extern boolean TesterDemoADC;

void AdcNotification_func(void)
{

}

//Adc_Init
void ADC_0001(void)
{
    Adc_Init(&Config);
    int i;
    for (i = 0; i < ADC_CONFIG_GROUPS; i++)
    {
        if(sAdc_RunningGroup[i].GroupStatus == ADC_IDLE)
        {
            PSPRINTF("ADC_0001 is OK, group status is %d\n", sAdc_RunningGroup[i].GroupStatus);
        }
        else
        {
            PSPRINTF("ADC_0001 is not OK, group status is %d\n", sAdc_RunningGroup[i].GroupStatus);
        }
    }
}

void ADC_0002(void)
{
    ADC_0001();
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        Adc_Init(&Config);
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_INIT_ID)  && (Det_ErrorId == ADC_E_ALREADY_INITIALIZED))
        {
            PSPRINTF("ADC_0002 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0002 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0003(void)
{
    Adc_Init(NULL_PTR);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_INIT_ID)  && (Det_ErrorId == ADC_E_PARAM_CONFIG))
        {
            PSPRINTF("ADC_0003 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0003 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_Init

//Adc_SetupResultBuffer
void ADC_0004(void)
{
    Adc_ValueGroupType resultbuffer[20];
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    ADC_0001();
    u8Adc_TempReturn = Adc_SetupResultBuffer(0, resultbuffer);
    if(u8Adc_TempReturn == (Std_ReturnType)E_OK)
    {
        PSPRINTF("ADC_0004 is OK\n");
    }
    else
    {
        PSPRINTF("ADC_0004 is not OK\n");
    }
}

void ADC_0005(void)
{
    Adc_ValueGroupType resultbuffer[20];
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    u8Adc_TempReturn = Adc_SetupResultBuffer(0, resultbuffer);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_SETUPRESULTBUFFER_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(u8Adc_TempReturn == (Std_ReturnType)E_NOT_OK)
            {
                PSPRINTF("ADC_0005 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0005 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0006(void)
{
    Adc_ValueGroupType resultbuffer[20];
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    ADC_0001();
    u8Adc_TempReturn = Adc_SetupResultBuffer(100, resultbuffer);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_SETUPRESULTBUFFER_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            if(u8Adc_TempReturn == (Std_ReturnType)E_NOT_OK)
            {
                PSPRINTF("ADC_0006 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0006 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0007(void)
{
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    ADC_0001();
    u8Adc_TempReturn = Adc_SetupResultBuffer(0, NULL_PTR);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_SETUPRESULTBUFFER_ID)  && (Det_ErrorId == ADC_E_PARAM_POINTER))
        {
            if(u8Adc_TempReturn == (Std_ReturnType)E_NOT_OK)
            {
                PSPRINTF("ADC_0007 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0007 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_SetupResultBuffer


#if (ADC_DEINIT_API == STD_ON)
//Adc_DeInit
void ADC_0008(void)
{
    ADC_0001();
    Adc_DeInit();
    int i;
    for (i = 0; i < ADC_CONFIG_GROUPS; i++)
    {
        if(Adc_GetGroupStatus(0) == ADC_IDLE)
        {
            PSPRINTF("ADC_0008 is OK, group status is %d\n", Adc_GetGroupStatus(0));
        }
        else
        {
            PSPRINTF("ADC_0008 is not OK, group status is %d\n", Adc_GetGroupStatus(0));
        }
    }
}

void ADC_0009(void)
{
    Adc_DeInit();
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DEINIT_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0009 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0009 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_DeInit
#endif


#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
//Adc_StartGroupConversion
void ADC_0010(void)
{
    ADC_0004();
    Adc_StartGroupConversion(0);
    if(Adc_GetGroupStatus(0) == ADC_BUSY)
    {
        PSPRINTF("ADC_0010 is OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
    else
    {
        PSPRINTF("ADC_0010 is not OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
}

void ADC_0011(void)
{
    Adc_StartGroupConversion(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STARTGROUPCONVERSION_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0011 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0011 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0012(void)
{
    ADC_0004();
    Adc_StartGroupConversion(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STARTGROUPCONVERSION_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0012 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0012 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0013(void)
{
    ADC_0001();
    Adc_StartGroupConversion(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STARTGROUPCONVERSION_ID)  && (Det_ErrorId == ADC_E_BUFFER_UNINIT))
        {
            PSPRINTF("ADC_0013 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0013 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0014(void)
{
    ADC_0004();
    Adc_StartGroupConversion(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STARTGROUPCONVERSION_ID)  && (Det_ErrorId == ADC_E_WRONG_TRIGG_SRC))
        {
            PSPRINTF("ADC_0014 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0014 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_StartGroupConversion

//Adc_StopGroupConversion
void ADC_0015(void)
{
    ADC_0010();
    Adc_StopGroupConversion(0);
    if(Adc_GetGroupStatus(0) == ADC_IDLE)
    {
        PSPRINTF("ADC_0015 is OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
    else
    {
        PSPRINTF("ADC_0015 is not OK, group status is %d\n", Adc_GetGroupStatus(0));
    }

}

void ADC_0016(void)
{
    Adc_StopGroupConversion(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STOPGROUPCONVERSION_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0016 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0016 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0017(void)
{
    ADC_0010();
    Adc_StopGroupConversion(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STOPGROUPCONVERSION_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0017 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0017 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_StopGroupConversion
#endif

#if (ADC_READ_GROUP_API == STD_ON)
//Adc_ReadGroup
void ADC_0018(void)
{
    Adc_ValueGroupType resultbuffer[20];
    Adc_ValueGroupType result[20];
    INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    u8Adc_TempReturn = Adc_SetupResultBuffer(0, resultbuffer);
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    Adc_StartGroupConversion(0);
#endif
    while((Adc_GetGroupStatus(0) != ADC_COMPLETED) && (Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	u8Adc_TempReturn = Adc_ReadGroup(0, result);
		if(u8Adc_TempReturn == E_OK)
		{
			PSPRINTF("ADC_0018 is OK, result is %d", result[0]);
		}
		else
		{
			PSPRINTF("ADC_0018 is not OK\n");
		}
    }
    else
    {
    	PSPRINTF("ADC_0018 is timeout\n");
    }

    INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP0_IRQ965);
}

void ADC_0019(void)
{
    Adc_ValueGroupType resultbuffer[20];
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    u8Adc_TempReturn = Adc_ReadGroup(0, resultbuffer);

    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_READGROUP_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(u8Adc_TempReturn == E_NOT_OK)
            {
                PSPRINTF("ADC_0019 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0019 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0020(void)
{
    Adc_ValueGroupType resultbuffer[20];
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    ADC_0010();
#endif
    u8Adc_TempReturn = Adc_ReadGroup(100, resultbuffer);

    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_READGROUP_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            if(u8Adc_TempReturn == E_NOT_OK)
            {
                PSPRINTF("ADC_0020 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0020 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_ReadGroup
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
//Adc_EnableHardwareTrigger
void ADC_0021(void)
{
    ADC_0004();
    Adc_EnableHardwareTrigger(0);
    if(Adc_GetGroupStatus(0) == ADC_BUSY && sAdc_RunningGroup[0].GroupSwitchHwTrig == ADC_GROUP_HWTRIGGER_ENABLED)
    {
        PSPRINTF("ADC_0021 is OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
    else
    {
        PSPRINTF("ADC_0021 is not OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
}

void ADC_0022(void)
{
    Adc_EnableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0022 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0022 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0023(void)
{
    ADC_0004();
    Adc_EnableHardwareTrigger(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0023 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0023 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0024(void)
{
    ADC_0004();
    Adc_EnableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_WRONG_TRIGG_SRC))
        {
            PSPRINTF("ADC_0024 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0024 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0025(void)
{
    ADC_0004();
    Adc_EnableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_WRONG_CONV_MODE))
        {
            PSPRINTF("ADC_0025 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0025 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0026(void)
{
    ADC_0001();
    Adc_EnableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_BUFFER_UNINIT))
        {
            PSPRINTF("ADC_0026 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0026 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

//Adc_DisableHardwareTrigger
void ADC_0027(void)
{
    ADC_0021();
    Adc_DisableHardwareTrigger(0);
    if(Adc_GetGroupStatus(0) == ADC_IDLE && sAdc_RunningGroup[0].GroupSwitchHwTrig == ADC_GROUP_HWTRIGGER_DISABLED)
    {
        PSPRINTF("ADC_0027 is OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
    else
    {
        PSPRINTF("ADC_0027 is not OK, group status is %d\n", Adc_GetGroupStatus(0));
    }
}

void ADC_0028(void)
{
    Adc_DisableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0028 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0028 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0029(void)
{
    ADC_0021();
    Adc_DisableHardwareTrigger(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0029 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0029 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}
#endif//ADC_HW_TRIGGER_API == STD_ON

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
//Adc_EnableGroupNotification
void ADC_0030(void)
{
    ADC_0001();
    Adc_EnableGroupNotification(0);
    if(sAdc_RunningGroup[0].GroupSwitchNotifCall == ADC_GROUP_NOTIFICATION_ENABLED)
    {
        PSPRINTF("ADC_0030 is OK, group eNotification is %d\n", sAdc_RunningGroup[0].GroupSwitchNotifCall);
    }
    else
    {
        PSPRINTF("ADC_0030 is not OK, group eNotification is %d\n", sAdc_RunningGroup[0].GroupSwitchNotifCall);
    }
}

void ADC_0031(void)
{
    Adc_EnableGroupNotification(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEGROUPNOTIFICATION_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0031 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0031 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0032(void)
{
    ADC_0001();
    Adc_EnableGroupNotification(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEGROUPNOTIFICATION_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0032 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0032 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0033(void)
{
    ADC_0001();
    Adc_EnableGroupNotification(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_ENABLEGROUPNOTIFICATION_ID)  && (Det_ErrorId == ADC_E_NOTIF_CAPABILITY))
        {
            PSPRINTF("ADC_0033 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0033 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_EnableGroupNotification

//Adc_DisableGroupNotification
void ADC_0034(void)
{
    ADC_0001();
    Adc_DisableGroupNotification(0);
    if(sAdc_RunningGroup[0].GroupSwitchNotifCall == ADC_GROUP_NOTIFICATION_DISABLED)
    {
        PSPRINTF("ADC_0034 is OK, group eNotification is %d\n", sAdc_RunningGroup[0].GroupSwitchNotifCall);
    }
    else
    {
        PSPRINTF("ADC_0034 is not OK, group eNotification is %d\n", sAdc_RunningGroup[0].GroupSwitchNotifCall);
    }
}

void ADC_0035(void)
{
    Adc_DisableGroupNotification(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEGROUPNOTIFICATION_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0035 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0035 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0036(void)
{
    ADC_0001();
    Adc_DisableGroupNotification(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEGROUPNOTIFICATION_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0036 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0036 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0037(void)
{
    ADC_0001();
    Adc_DisableGroupNotification(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEGROUPNOTIFICATION_ID)  && (Det_ErrorId == ADC_E_NOTIF_CAPABILITY))
        {
            PSPRINTF("ADC_0037 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0037 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_DisableGroupNotification
#endif

//Adc_GetGroupStatus
void ADC_0038(void)
{
    ADC_0001();
    Adc_StatusType eTempReturn = ADC_IDLE;
    eTempReturn = Adc_GetGroupStatus(0);
    if(eTempReturn == ADC_IDLE)
    {
        PSPRINTF("ADC_0038 is OK\n");
    }
    else
    {
        PSPRINTF("ADC_0038 is not OK\n");
    }
}

void ADC_0039(void)
{
    Adc_GetGroupStatus(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETGROUPSTATUS_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            PSPRINTF("ADC_0039 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0039 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0040(void)
{
    ADC_0001();
    Adc_GetGroupStatus(100);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETGROUPSTATUS_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            PSPRINTF("ADC_0040 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0040 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0041(void)
{
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    ADC_0004();
    Adc_StartGroupConversion(0);
    Adc_StopGroupConversion(0);
#endif
    Adc_StatusType eTempReturn = ADC_IDLE;
    eTempReturn = Adc_GetGroupStatus(0);
    if(eTempReturn == ADC_IDLE)
    {
        PSPRINTF("ADC_0041 is OK\n");
    }
    else
    {
        PSPRINTF("ADC_0041 is not OK\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP0_IRQ965);
}//Adc_GetGroupStatus

//Adc_GetStreamLastPointer
void ADC_0042(void)
{
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    ADC_0004();
    Adc_StartGroupConversion(0);
#endif

    Adc_ValueGroupType PtrToSample = 0;
    Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_StreamNumSampleType ResultIndex;
    uint32 Adc_timeout = ADC_TIMEOUT;
    while((Adc_GetGroupStatus(0) != ADC_COMPLETED) && (Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED))
	{
		Adc_timeout--;
	}
    ResultIndex = Adc_GetStreamLastPointer(0, &PtrToSamplePtr);
    if(PtrToSamplePtr != NULL_PTR)
    {
        PSPRINTF("ADC_0042 is OK, number of valid samples is %d\n", ResultIndex);
    }
    else
    {
        PSPRINTF("ADC_0042 is not OK\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP0_IRQ965);
}

void ADC_0043(void)
{
    Adc_ValueGroupType PtrToSample = 0;
    Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_StreamNumSampleType ResultIndex;
    ResultIndex = Adc_GetStreamLastPointer(0, &PtrToSamplePtr);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETSTREAMLASTPOINTER_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(ResultIndex == 0U)
            {
                PSPRINTF("ADC_0043 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0043 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0044(void)
{
    ADC_0001();
    Adc_ValueGroupType PtrToSample = 0;
    Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_StreamNumSampleType ResultIndex;
    ResultIndex = Adc_GetStreamLastPointer(100, &PtrToSamplePtr);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETSTREAMLASTPOINTER_ID)  && (Det_ErrorId == ADC_E_PARAM_GROUP))
        {
            if(*PtrToSamplePtr == 0U)
            {
                PSPRINTF("ADC_0044 is OK, number of valid samples is %d\n", ResultIndex);
            }
            else
            {
                PSPRINTF("ADC_0044 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}//Adc_GetStreamLastPointer

#if (ADC_VERSION_INFO_API == STD_ON)
//Adc_GetVersionInfo
void ADC_0045(void)
{
    ADC_0001();
    Std_VersionInfoType versioninfo;
    Adc_GetVersionInfo(&versioninfo);
    PSPRINTF("ADC_0045 is OK, vendorID:%d moduleID:%d sw_major_version:%d sw_minor_version:%d sw_patch_version:%d\n", versioninfo.vendorID, versioninfo.moduleID, versioninfo.sw_major_version, versioninfo.sw_minor_version, versioninfo.sw_patch_version);
}//ADC_VERSION_INFO_API == STD_ON

void ADC_0046(void)
{
    ADC_0001();
    Adc_GetVersionInfo(NULL_PTR);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETVERSIONINFO_ID)  && (Det_ErrorId == ADC_E_PARAM_POINTER))
        {
            PSPRINTF("ADC_0046 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0046 is not OK\n");
        }
    }
}//Adc_GetVersionInfo
#endif

#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
//Adc_SetPowerState
void ADC_0047(void)
{
    Adc_PowerStateRequestResultType Result = ADC_NOT_INIT;
    Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
    RetVal = Adc_SetPowerState(&Result);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_SETPOWERSTATE_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(RetVal == E_NOT_OK)
            {
                PSPRINTF("ADC_0047 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0047 is not OK\n");
            }
        }
    }
}//Adc_SetPowerState

//Adc_GetCurrentPowerState
void ADC_0048(void)
{
    Adc_PowerStateType CurrentPowerState = ADC_FULL_POWER;
    Adc_PowerStateRequestResultType Result = ADC_NOT_INIT;
    Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
    RetVal = Adc_GetCurrentPowerState(&CurrentPowerState, &Result);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETCURRENTPOWERSTATE_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(RetVal == E_NOT_OK)
            {
                PSPRINTF("ADC_0048 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0048 is not OK\n");
            }
        }
    }
}//Adc_GetCurrentPowerState

//Adc_GetTargetPowerState
void ADC_0049(void)
{
    Adc_PowerStateType TargetPowerState = ADC_FULL_POWER;
    Adc_PowerStateRequestResultType Result = ADC_NOT_INIT;
    Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
    RetVal = Adc_GetTargetPowerState(&TargetPowerState, &Result);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_GETTARGETPOWERSTATE_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(RetVal == E_NOT_OK)
            {
                PSPRINTF("ADC_0049 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0049 is not OK\n");
            }
        }
    }
}//Adc_GetTargetPowerState

//Adc_PreparePowerState
void ADC_0050(void)
{
    Adc_PowerStateType PowerState = ADC_FULL_POWER;
    Adc_PowerStateRequestResultType Result = ADC_NOT_INIT;
    Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
    RetVal = Adc_PreparePowerState(PowerState, &Result);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_PREPAREPOWERSTATE_ID)  && (Det_ErrorId == ADC_E_UNINIT))
        {
            if(RetVal == E_NOT_OK)
            {
                PSPRINTF("ADC_0050 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0050 is not OK\n");
            }
        }
    }
}//Adc_PreparePowerState
#endif//ADC_POWER_STATE_SUPPORTED == STD_ON


#include "Gpt_Pit_LLDriver.h"
#include "Gpt_Cfg.h"
#include "Gpt.h"
#include "tester_pwm.h"
#include "Port.h"
#include "Pwm_Cfg.h"
GPT_CONFIG_DECLARATION;
void ADC_demo(void)
{
    uint32 Adc_timeout = ADC_TIMEOUT;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    static Adc_ValueGroupType resultbuffer_0[20];
    static Adc_ValueGroupType resultbuffer_1[20];
    static Adc_ValueGroupType resultbuffer_2[20];
    static Adc_ValueGroupType resultbuffer_3[20];
    static Adc_ValueGroupType resultbuffer_4[20];
    static Adc_ValueGroupType resultbuffer_5[20];
#if (ADC_HW_TRIGGER_API == STD_ON)
    static Adc_ValueGroupType resultbuffer_6[20];
    static Adc_ValueGroupType resultbuffer_7[20];
    static Adc_ValueGroupType resultbuffer_8[20];
#endif
    static Adc_ValueGroupType resultbuffer_9[20];
    Adc_Init(&Config);
#ifdef DioConf_DioChannel_DioChannel_A2
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
    int i = 0U;
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    PSPRINTF("\n===============================================DEMO TEST===============================================\n");
    PSPRINTF("\nTest0:ADC0 SW ADC_CONV_MODE_ONESHOT CFIFO0 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP1_IRQ966, ADC01_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP1_IRQ966, INTR_PRI_8);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP1_IRQ966);
    Adc_SetupResultBuffer(0, resultbuffer_0);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(0);
    Adc_ValueGroupType result_0[20];
    while((Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(0, result_0);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC0 test is OK, result is %d\n", result_0[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC0 test is timeout\n");
        }
        PSPRINTF("\nADC0 test is not OK\n");
    }
    //Adc_StopGroupConversion(0);
    INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP1_IRQ966);

    PSPRINTF("\nTest1:ADC1 SW ADC_CONV_MODE_ONESHOT CFIFO1 RFIFO2 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP2_IRQ967, ADC01_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP2_IRQ967, INTR_PRI_9);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP2_IRQ967);
    Adc_SetupResultBuffer(1, resultbuffer_1);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(1);
    Adc_ValueGroupType result_1[20];
    while((Adc_GetGroupStatus(1) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(1, result_1);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC1 test is OK, result is %d\n", result_1[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC1 test is timeout\n");
        }
        PSPRINTF("\nADC1 test is not OK\n");
    }
    //Adc_StopGroupConversion(1);
    INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP2_IRQ967);

    PSPRINTF("\nTest2:ADC2 SW ADC_CONV_MODE_CONTINUOUS CFIFO2 RFIFO2 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP2_IRQ973, ADC23_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP2_IRQ973, INTR_PRI_9);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP2_IRQ973);
    Adc_SetupResultBuffer(2, resultbuffer_2);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(2);
    for(int i = 0U; i < 100000U; i++);
    Adc_ValueGroupType result_2[20];
    for(i = 0U; i < 10U; i++)
    {
	#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(2, result_2);
	#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\n conv: %d ,ADC2 test is OK, result is %d\n", i, result_2[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC2 test is timeout\n");
			}
			PSPRINTF("\nADC2 test is not OK\n");
		}
    }

    Adc_StopGroupConversion(2);
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP2_IRQ973);

    PSPRINTF("\nTest3:ADC3 SW ADC_CONV_MODE_CONTINUOUS CFIFO4 RFIFO5 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP5_IRQ976, ADC23_GRP5);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP5_IRQ976, INTR_PRI_12);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP5_IRQ976);
    Adc_SetupResultBuffer(3, resultbuffer_3);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(3);
    for(int i = 0U; i < 100000U; i++);
    Adc_ValueGroupType result_3[20];
    for(i = 0U; i < 10U; i++)
	{
	#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(3, result_3);
	#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\n conv: %d ,ADC3 test is OK, result is %d\n", i, result_3[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC3 test is timeout\n");
			}
			PSPRINTF("\nADC3 test is not OK\n");
		}
	}
    Adc_StopGroupConversion(3);
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP5_IRQ976);

    PSPRINTF("\nTest4:ADC4 SW ADC_CONV_MODE_ONESHOT CFIFO5 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT10\n");
    INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP0_IRQ977, ADC45_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP0_IRQ977, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP0_IRQ977);
    Adc_SetupResultBuffer(4, resultbuffer_4);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(4);
    Adc_ValueGroupType result_4[20];
    while((Adc_GetGroupStatus(4) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(4, result_4);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC4 test is OK, result is %d\n", result_4[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC4 test is timeout\n");
        }
        PSPRINTF("\nADC4 test is not OK\n");
    }
    //Adc_StopGroupConversion(4);
    INTC_LLD_Set_IRQ_Disable(EQADC2_ADC45_GRP0_IRQ977);

    PSPRINTF("\nTest5:ADC5 SW ADC_CONV_MODE_ONESHOT CFIFO2 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT8\n");
    INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP0_IRQ977, ADC45_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP0_IRQ977, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP0_IRQ977);
    Adc_SetupResultBuffer(5, resultbuffer_5);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(5);
    Adc_ValueGroupType result_5[20];
    while((Adc_GetGroupStatus(5) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(5, result_5);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC5 test is OK, result is %d\n", result_5[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC5 test is timeout\n");
        }
        PSPRINTF("\nADC5 test is not OK\n");
    }
    //Adc_StopGroupConversion(5);
    INTC_LLD_Set_IRQ_Disable(EQADC2_ADC45_GRP0_IRQ977);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
#if (ADC_HW_TRIGGER_API == STD_ON)
    PSPRINTF("\nTest6:ADC6 HW ADC_CONV_MODE_ONESHOT CFIFO1 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_ETRIG0\n");
    INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP0_IRQ983, ADC67_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP0_IRQ983, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP0_IRQ983);
    Adc_SetupResultBuffer(6, resultbuffer_6);
    Adc_timeout = ADC_TIMEOUT;
    Adc_EnableHardwareTrigger(6);
    Adc_ValueGroupType result_6[20];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
    while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(6, result_6);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC6 test is OK, result is %d\n", result_6[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC6 test is timeout\n");
        }
        PSPRINTF("\nADC6 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(6);
    INTC_LLD_Set_IRQ_Disable(EQADC3_ADC67_GRP0_IRQ983);

    PSPRINTF("\nTest7:ADC7 HW ADC_CONV_MODE_ONESHOT CFIFO2 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT10 EQADC_HW_TRIG_EMIOS0_CH16\n");
	INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP1_IRQ984, ADC67_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP1_IRQ984, INTR_PRI_8);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP1_IRQ984);
    Adc_SetupResultBuffer(7, resultbuffer_7);
    Adc_timeout = ADC_TIMEOUT;
    Adc_EnableHardwareTrigger(7);
    Adc_ValueGroupType result_7[20];
//    EMIOS_0.MCR.B.GPRE  = 63U;  /* Divide 64 MHz sysclk by 63+1 = 64 for 1MHz eMIOS clk*/
//    EMIOS_0.MCR.B.ETB   = 0U;   /* External time base is disabled; Ch 23 drives ctr bus A */
//    EMIOS_0.MCR.B.GPREN = 1U;   /* Enable eMIOS clock */
//    EMIOS_0.MCR.B.GTBE  = 1U;   /* Enable global time base */
//    EMIOS_0.MCR.B.FRZ   = 1U;   /* Enable stopping channels when in debug mode */
//    /* eMIOS_InitChan_ForTest */
//    EMIOS_0.UC[16].C.B.MODE  = 0x01U;
//    EMIOS_0.UC[16].C.B.EDPOL = 1U;   /* Output Set High */
//    /* change */
//    EMIOS_0.UC[16].C.B.EDPOL = 1U;
//    EMIOS_0.UC[16].C.B.EDPOL = 0U;
    Pwm_Init(&Pwm_Config);
    while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
    
//    EMIOS_0.MCR.R = 0U;
//    EMIOS_0.UC[16].C.R = 0UL;
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(7, result_7);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC7 test is OK, result is %d\n", result_7[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC7 test is timeout\n");
        }
        PSPRINTF("\nADC7 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(7);
    Pwm_DeInit();
	INTC_LLD_Set_IRQ_Disable(EQADC3_ADC67_GRP1_IRQ984);

    PSPRINTF("\nTest8:ADC8 HW ADC_CONV_MODE_ONESHOT CFIFO3 RFIFO0 channel:1(CH1) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_PIT0_CH0\n");
    INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP0_IRQ989, ADC89_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP0_IRQ989, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP0_IRQ989);
    Gpt_Init(&GptChannelConfigSet);
    Adc_timeout = ADC_TIMEOUT;
    Adc_SetupResultBuffer(8, resultbuffer_8);
    Adc_EnableHardwareTrigger(8);
    Adc_ValueGroupType result_8[20];
    Gpt_StartTimer(5, 10000);
    while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(8, result_8);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC8 test is OK, result is %d\n", result_8[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC8 test is timeout\n");
        }
        PSPRINTF("\nADC8 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(8);
    Gpt_StopTimer(5);
    INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP0_IRQ989);
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    PSPRINTF("\nTest9:ADC9 SW ADC_CONV_MODE_ONESHOT CFIFO4 RFIFO3 channel:3(CH4 CH5 CH6) ADC_RESOLUTION_BIT12\n");
	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP3_IRQ992, ADC89_GRP3);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP3_IRQ992, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP3_IRQ992);
    Adc_SetupResultBuffer(9, resultbuffer_9);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(9);
    Adc_ValueGroupType result_9[20];
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(9, result_9);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC9 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[9].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_9[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9 test is timeout\n");
        }
        PSPRINTF("\nADC9 test is not OK\n");
    }

    //Adc_StopGroupConversion(9);
	INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP3_IRQ992);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
    Gpt_DeInit();
    Adc_DeInit();

    PSPRINTF("\n===============================================DEMO END================================================\n");
}

void Eqadc0_Adc0_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc0_Adc1_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc1_Adc2_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc1_Adc3_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc2_Adc4_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc2_Adc5_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc3_Adc6_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc3_Adc7_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc4_Adc8_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void Eqadc4_Adc9_CmdCallback(void *parameter, eDMAChnStatusType status, uint8 mappedChannel)/* PRQA S 3673 */
{
    (void) parameter; /* PRQA S 3119 */
    (void) status; /* PRQA S 3119 */
    (void) mappedChannel;
    EQADC_DET_ERR(status == EDMA_CHN_STATUS_NORMAL);
}

void ADC_demo_Dma(void)
{
    uint32 Adc_timeout = ADC_TIMEOUT;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    static Adc_ValueGroupType resultbuffer_0[20];
    static Adc_ValueGroupType resultbuffer_1[20];
    static Adc_ValueGroupType resultbuffer_2[20];
    static Adc_ValueGroupType resultbuffer_3[20];
    static Adc_ValueGroupType resultbuffer_4[20];
    static Adc_ValueGroupType resultbuffer_5[20];
#if (ADC_HW_TRIGGER_API == STD_ON)
    static Adc_ValueGroupType resultbuffer_6[20];
    static Adc_ValueGroupType resultbuffer_7[20];
    static Adc_ValueGroupType resultbuffer_8[20];
#endif
    static Adc_ValueGroupType resultbuffer_9[20];
    int i = 0;
    Adc_Init(&Config);
#ifdef DioConf_DioChannel_DioChannel_A2
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    PSPRINTF("\n===========================================DMA DEMO TEST===============================================\n");
    PSPRINTF("\nTest0:ADC0 SW ADC_CONV_MODE_ONESHOT CFIFO0 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT12 DMA:CH2 CH3\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH2_IRQ55, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH3_IRQ56, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH2_IRQ55, &EDMA_Ch2_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH3_IRQ56, &EDMA_Ch3_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH2_IRQ55);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH3_IRQ56);
    Adc_SetupResultBuffer(0, resultbuffer_0);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(0);
    Adc_ValueGroupType result_0[20];
    while((Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(0, result_0);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC0 test is OK, result is %d\n", result_0[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC0 test is timeout\n");
        }
        PSPRINTF("\nADC0 test is not OK\n");
    }
    //Adc_StopGroupConversion(0);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH2_IRQ55);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH3_IRQ56);

    PSPRINTF("\nTest1:ADC1 SW ADC_CONV_MODE_ONESHOT CFIFO1 RFIFO2 channel:1(CH0) ADC_RESOLUTION_BIT10 DMA:CH4 CH5\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH4_IRQ57, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH5_IRQ58, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH4_IRQ57, &EDMA_Ch4_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH5_IRQ58, &EDMA_Ch5_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH4_IRQ57);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH5_IRQ58);
    Adc_SetupResultBuffer(1, resultbuffer_1);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(1);
    Adc_ValueGroupType result_1[20];
    while((Adc_GetGroupStatus(1) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(1, result_1);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC1 test is OK, result is %d\n", result_1[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC1 test is timeout\n");
        }
        PSPRINTF("\nADC1 test is not OK\n");
    }
    //Adc_StopGroupConversion(1);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH4_IRQ57);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH5_IRQ58);

    PSPRINTF("\nTest2:ADC2 SW ADC_CONV_MODE_ONESHOT CFIFO2 RFIFO3 channel:1(CH0) ADC_RESOLUTION_BIT12 DMA:CH16 CH17\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH16_IRQ69, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH17_IRQ70, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH16_IRQ69, &EDMA_Ch16_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH17_IRQ70, &EDMA_Ch17_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH16_IRQ69);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH17_IRQ70);
    Adc_SetupResultBuffer(2, resultbuffer_2);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(2);
    Adc_ValueGroupType result_2[20];
    while((Adc_GetGroupStatus(2) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(2, result_2);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC2 test is OK, result is %d\n", result_2[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC2 test is timeout\n");
        }
        PSPRINTF("\nADC2 test is not OK\n");
    }
    //Adc_StopGroupConversion(2);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH16_IRQ69);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH17_IRQ70);

    PSPRINTF("\nTest3:ADC3 SW ADC_CONV_MODE_ONESHOT CFIFO4 RFIFO5 channel:1(CH0) ADC_RESOLUTION_BIT10 DMA:CH18 CH19\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH18_IRQ71, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH19_IRQ72, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH18_IRQ71, &EDMA_Ch18_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH19_IRQ72, &EDMA_Ch19_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH18_IRQ71);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH19_IRQ72);
    Adc_SetupResultBuffer(3, resultbuffer_3);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(3);
    Adc_ValueGroupType result_3[20];
    while((Adc_GetGroupStatus(3) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(3, result_3);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC3 test is OK, result is %d\n", result_3[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC3 test is timeout\n");
        }
        PSPRINTF("\nADC3 test is not OK\n");
    }
    //Adc_StopGroupConversion(3);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH18_IRQ71);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH19_IRQ72);

    PSPRINTF("\nTest4:ADC4 SW ADC_CONV_MODE_CONTINUOUS CFIFO0 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT12 DMA:CH24 CH25\n");
//    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH24_IRQ77, INTR_PRI_7);
//	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH25_IRQ78, INTR_PRI_8);
//	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH24_IRQ77, &EDMA_Ch24_IRQHandler);
//	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH25_IRQ78, &EDMA_Ch25_IRQHandler);
//	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH24_IRQ77);
//	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH25_IRQ78);
    Adc_SetupResultBuffer(4, resultbuffer_4);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(4);
    for(int i = 0U; i < 100000U; i++);
    Adc_ValueGroupType result_4[20];
    for(i = 0U; i < 10U; i++)
	{
#if (ADC_READ_GROUP_API == STD_ON)
    	u8Adc_TempReturn = Adc_ReadGroup(4, result_4);
#endif
    	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
    		PSPRINTF("\n conv: %d ,ADC4 test is OK, result is %d\n", i, result_4[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC4 test is timeout\n");
			}
			PSPRINTF("\nADC4 test is not OK\n");
		}
	}
    Adc_StopGroupConversion(4);
//    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH24_IRQ77);
//	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH25_IRQ78);

    PSPRINTF("\nTest5:ADC5 SW ADC_CONV_MODE_CONTINUOUS CFIFO2 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT10 DMA:CH26 CH27\n");
//    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH26_IRQ79, INTR_PRI_7);
//	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH27_IRQ80, INTR_PRI_8);
//	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH26_IRQ79, &EDMA_Ch26_IRQHandler);
//	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH27_IRQ80, &EDMA_Ch27_IRQHandler);
//	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH26_IRQ79);
//	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH27_IRQ80);
    Adc_SetupResultBuffer(5, resultbuffer_5);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(5);
    for(int i = 0U; i < 100000U; i++);
    Adc_ValueGroupType result_5[20];
    for(i = 0U; i < 10U; i++)
	{
#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(5, result_5);
#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\n conv: %d ,ADC5 test is OK, result is %d\n", i, result_5[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC5 test is timeout\n");
			}
			PSPRINTF("\nADC5 test is not OK\n");
		}
	}
    Adc_StopGroupConversion(5);
//    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH26_IRQ79);
//	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH27_IRQ80);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
#if (ADC_HW_TRIGGER_API == STD_ON)
    PSPRINTF("\nTest6:ADC6 HW ADC_CONV_MODE_ONESHOT CFIFO1 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_ETRIG0 DMA:CH32 CH33\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH32_IRQ85, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH33_IRQ86, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH32_IRQ85, &EDMA_Ch32_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH33_IRQ86, &EDMA_Ch33_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH32_IRQ85);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH33_IRQ86);
    Adc_SetupResultBuffer(6, resultbuffer_6);
    Adc_timeout = ADC_TIMEOUT;
    Adc_EnableHardwareTrigger(6);
    Adc_ValueGroupType result_6[20];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
    while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(6, result_6);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC6 test is OK, result is %d\n", result_6[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC6 test is timeout\n");
        }
        PSPRINTF("\nADC6 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(6);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH32_IRQ85);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH33_IRQ86);

    PSPRINTF("\nTest7:ADC7 HW ADC_CONV_MODE_ONESHOT CFIFO2 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT10 EQADC_HW_TRIG_EMIOS0_CH16 DMA:CH34 CH35\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH34_IRQ87, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH35_IRQ88, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH34_IRQ87, &EDMA_Ch34_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH35_IRQ88, &EDMA_Ch35_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH34_IRQ87);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH35_IRQ88);
    Adc_SetupResultBuffer(7, resultbuffer_7);
    Adc_timeout = ADC_TIMEOUT;
    Adc_EnableHardwareTrigger(7);
    Adc_ValueGroupType result_7[20];
//    EMIOS_0.MCR.B.GPRE  = 63U;  /* Divide 64 MHz sysclk by 63+1 = 64 for 1MHz eMIOS clk*/
//    EMIOS_0.MCR.B.ETB   = 0U;   /* External time base is disabled; Ch 23 drives ctr bus A */
//    EMIOS_0.MCR.B.GPREN = 1U;   /* Enable eMIOS clock */
//    EMIOS_0.MCR.B.GTBE  = 1U;   /* Enable global time base */
//    EMIOS_0.MCR.B.FRZ   = 1U;   /* Enable stopping channels when in debug mode */
//    /* eMIOS_InitChan_ForTest */
//    EMIOS_0.UC[16].C.B.MODE  = 0x01U;
//    EMIOS_0.UC[16].C.B.EDPOL = 1U;   /* Output Set High */
//    /* change */
//    EMIOS_0.UC[16].C.B.EDPOL = 1U;
//    EMIOS_0.UC[16].C.B.EDPOL = 0U;
    Pwm_Init(&Pwm_Config);

    while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}

//    EMIOS_0.MCR.R = 0U;
//    EMIOS_0.UC[16].C.R = 0UL;
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(7, result_7);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC7 test is OK, result is %d\n", result_7[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC7 test is timeout\n");
        }
        PSPRINTF("\nADC7 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(7);
    Pwm_DeInit();
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH34_IRQ87);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH35_IRQ88);

    PSPRINTF("\nTest8:ADC8 HW ADC_CONV_MODE_ONESHOT CFIFO3 RFIFO0 channel:1(CH1) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_PIT0_CH0 DMA:CH48 CH49\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH48_IRQ101, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH49_IRQ102, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH48_IRQ101, &EDMA_Ch48_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH49_IRQ102, &EDMA_Ch49_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH48_IRQ101);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH49_IRQ102);
    Gpt_Init(&GptChannelConfigSet);
    Adc_timeout = ADC_TIMEOUT;
    Adc_SetupResultBuffer(8, resultbuffer_8);
    Adc_EnableHardwareTrigger(8);
    Adc_ValueGroupType result_8[20];
    Gpt_StartTimer(5, 10000);
    while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(8, result_8);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC8 test is OK, result is %d\n", result_8[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC8 test is timeout\n");
        }
        PSPRINTF("\nADC8 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(8);
    Gpt_StopTimer(5);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH48_IRQ101);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH49_IRQ102);
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    PSPRINTF("\nTest9:ADC9 SW ADC_CONV_MODE_ONESHOT CFIFO4 RFIFO3 channel:3(CH4 CH5 CH6) ADC_RESOLUTION_BIT12 DMA:CH50 CH51\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH50_IRQ103, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH51_IRQ104, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH50_IRQ103, &EDMA_Ch50_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH51_IRQ104, &EDMA_Ch51_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH50_IRQ103);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH51_IRQ104);
    Adc_SetupResultBuffer(9, resultbuffer_9);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(9);
    Adc_ValueGroupType result_9[20];
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(9, result_9);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC9 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[9].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_9[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9 test is timeout\n");
        }
        PSPRINTF("\nADC9 test is not OK\n");
    }

    //Adc_StopGroupConversion(9);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH50_IRQ103);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH51_IRQ104);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
    Gpt_DeInit();
    Adc_DeInit();

    PSPRINTF("\n===============================================DEMO END================================================\n");
}

void ADC_demo_Int_Dma(void)
{
    uint32 Adc_timeout = ADC_TIMEOUT;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    static Adc_ValueGroupType resultbuffer_0[20];
    static Adc_ValueGroupType resultbuffer_1[20];
    static Adc_ValueGroupType resultbuffer_2[20];
    static Adc_ValueGroupType resultbuffer_3[20];
    static Adc_ValueGroupType resultbuffer_4[20];
    static Adc_ValueGroupType resultbuffer_5[20];
#if (ADC_HW_TRIGGER_API == STD_ON)
    static Adc_ValueGroupType resultbuffer_6[20];
    static Adc_ValueGroupType resultbuffer_7[20];
    static Adc_ValueGroupType resultbuffer_8[20];
#endif
    static Adc_ValueGroupType resultbuffer_9[20];
    Adc_Init(&Config);
#ifdef DioConf_DioChannel_DioChannel_A2
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
    int i = 0U;
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    PSPRINTF("\n==========================================INT DMA DEMO TEST=============================================\n");
    PSPRINTF("\nTest0:ADC0 SW ADC_CONV_MODE_ONESHOT CFIFO0 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
    INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP1_IRQ966, ADC01_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP1_IRQ966, INTR_PRI_8);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP1_IRQ966);
    Adc_SetupResultBuffer(0, resultbuffer_0);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(0);
    Adc_ValueGroupType result_0[20];
    while((Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(0, result_0);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC0 test is OK, result is %d\n", result_0[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC0 test is timeout\n");
        }
        PSPRINTF("\nADC0 test is not OK\n");
    }
    //Adc_StopGroupConversion(0);
    INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP1_IRQ966);

    PSPRINTF("\nTest1:ADC1 SW ADC_CONV_MODE_ONESHOT CFIFO1 RFIFO2 channel:1(CH0) ADC_RESOLUTION_BIT12 DMA:CH4 CH5\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH4_IRQ57, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH5_IRQ58, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH4_IRQ57, &EDMA_Ch4_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH5_IRQ58, &EDMA_Ch5_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH4_IRQ57);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH5_IRQ58);
    Adc_SetupResultBuffer(1, resultbuffer_1);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(1);
    Adc_ValueGroupType result_1[20];
    while((Adc_GetGroupStatus(1) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(1, result_1);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC1 test is OK, result is %d\n", result_1[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC1 test is timeout\n");
        }
        PSPRINTF("\nADC1 test is not OK\n");
    }
    //Adc_StopGroupConversion(1);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH4_IRQ57);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH5_IRQ58);

    PSPRINTF("\nTest2:ADC2 SW ADC_CONV_MODE_ONESHOT CFIFO2 RFIFO3 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP3_IRQ974, ADC23_GRP3);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP3_IRQ974, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP3_IRQ974);
    Adc_SetupResultBuffer(2, resultbuffer_2);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(2);
    Adc_ValueGroupType result_2[20];
    while((Adc_GetGroupStatus(2) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(2, result_2);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC2 test is OK, result is %d\n", result_2[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC2 test is timeout\n");
        }
        PSPRINTF("\nADC2 test is not OK\n");
    }
    //Adc_StopGroupConversion(2);
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP3_IRQ974);

    PSPRINTF("\nTest3:ADC3 SW ADC_CONV_MODE_ONESHOT CFIFO4 RFIFO5 channel:1(CH0) ADC_RESOLUTION_BIT12 DMA:CH18 CH19\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH18_IRQ71, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH19_IRQ72, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH18_IRQ71, &EDMA_Ch18_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH19_IRQ72, &EDMA_Ch19_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH18_IRQ71);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH19_IRQ72);
    Adc_SetupResultBuffer(3, resultbuffer_3);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(3);
    Adc_ValueGroupType result_3[20];
    while((Adc_GetGroupStatus(3) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(3, result_3);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC3 test is OK, result is %d\n", result_3[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC3 test is timeout\n");
        }
        PSPRINTF("\nADC3 test is not OK\n");
    }
    //Adc_StopGroupConversion(3);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH18_IRQ71);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH19_IRQ72);

    PSPRINTF("\nTest4:ADC4 SW ADC_CONV_MODE_CONTINUOUS CFIFO0 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT12\n");
    INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP0_IRQ977, ADC45_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP0_IRQ977, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP0_IRQ977);
    Adc_SetupResultBuffer(4, resultbuffer_4);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(4);
    for(int i = 0U; i < 100000U; i++);
    Adc_ValueGroupType result_4[20];
    for(i = 0U; i < 10U; i++)
	{
	#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(4, result_4);
	#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\n conv: %d ,ADC4 test is OK, result is %d\n", i, result_4[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC4 test is timeout\n");
			}
			PSPRINTF("\nADC4 test is not OK\n");
		}
	}
    Adc_StopGroupConversion(4);
    INTC_LLD_Set_IRQ_Disable(EQADC2_ADC45_GRP0_IRQ977);

    PSPRINTF("\nTest5:ADC5 SW ADC_CONV_MODE_CONTINUOUS CFIFO2 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT12 DMA:CH26 CH27\n");
//    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH26_IRQ79, INTR_PRI_7);
//	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH27_IRQ80, INTR_PRI_8);
//	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH26_IRQ79, &EDMA_Ch26_IRQHandler);
//	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH27_IRQ80, &EDMA_Ch27_IRQHandler);
//	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH26_IRQ79);
//	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH27_IRQ80);
    Adc_SetupResultBuffer(5, resultbuffer_5);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(5);
    for(int i = 0U; i < 100000U; i++);
    Adc_ValueGroupType result_5[20];
    for(i = 0U; i < 10U; i++)
	{
#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(5, result_5);
#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\n conv: %d ,ADC5 test is OK, result is %d\n", i, result_5[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC5 test is timeout\n");
			}
			PSPRINTF("\nADC5 test is not OK\n");
		}
	}
    Adc_StopGroupConversion(5);
//    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH26_IRQ79);
//	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH27_IRQ80);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
#if (ADC_HW_TRIGGER_API == STD_ON)
    PSPRINTF("\nTest6:ADC6 HW ADC_CONV_MODE_ONESHOT CFIFO1 RFIFO0 channel:1(CH0) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_ETRIG0\n");
    INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP0_IRQ983, ADC67_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP0_IRQ983, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP0_IRQ983);
    Adc_SetupResultBuffer(6, resultbuffer_6);
    Adc_timeout = ADC_TIMEOUT;
    Adc_EnableHardwareTrigger(6);
    Adc_ValueGroupType result_6[20];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
    while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(6, result_6);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC6 test is OK, result is %d\n", result_6[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC6 test is timeout\n");
        }
        PSPRINTF("\nADC6 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(6);
    INTC_LLD_Set_IRQ_Disable(EQADC3_ADC67_GRP0_IRQ983);

    PSPRINTF("\nTest7:ADC7 HW ADC_CONV_MODE_ONESHOT CFIFO2 RFIFO1 channel:1(CH0) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_EMIOS0_CH16 DMA:CH34 CH35\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH34_IRQ87, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH35_IRQ88, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH34_IRQ87, &EDMA_Ch34_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH35_IRQ88, &EDMA_Ch35_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH34_IRQ87);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH35_IRQ88);
    Adc_SetupResultBuffer(7, resultbuffer_7);
    Adc_timeout = ADC_TIMEOUT;
    Adc_EnableHardwareTrigger(7);
    Adc_ValueGroupType result_7[20];
//    EMIOS_0.MCR.B.GPRE  = 63U;  /* Divide 64 MHz sysclk by 63+1 = 64 for 1MHz eMIOS clk*/
//    EMIOS_0.MCR.B.ETB   = 0U;   /* External time base is disabled; Ch 23 drives ctr bus A */
//    EMIOS_0.MCR.B.GPREN = 1U;   /* Enable eMIOS clock */
//    EMIOS_0.MCR.B.GTBE  = 1U;   /* Enable global time base */
//    EMIOS_0.MCR.B.FRZ   = 1U;   /* Enable stopping channels when in debug mode */
//    /* eMIOS_InitChan_ForTest */
//    EMIOS_0.UC[16].C.B.MODE  = 0x01U;
//    EMIOS_0.UC[16].C.B.EDPOL = 1U;   /* Output Set High */
//    /* change */
//    EMIOS_0.UC[16].C.B.EDPOL = 1U;
//    EMIOS_0.UC[16].C.B.EDPOL = 0U;
    Pwm_Init(&Pwm_Config);
    while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}

//    EMIOS_0.MCR.R = 0U;
//    EMIOS_0.UC[16].C.R = 0UL;
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(7, result_7);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC7 test is OK, result is %d\n", result_7[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC7 test is timeout\n");
        }
        PSPRINTF("\nADC7 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(7);
    Pwm_DeInit();
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH34_IRQ87);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH35_IRQ88);

    PSPRINTF("\nTest8:ADC8 HW ADC_CONV_MODE_ONESHOT CFIFO3 RFIFO0 channel:1(CH1) ADC_RESOLUTION_BIT12 EQADC_HW_TRIG_PIT0_CH0\n");
    INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP0_IRQ989, ADC89_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP0_IRQ989, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP0_IRQ989);
    Gpt_Init(&GptChannelConfigSet);
    Adc_timeout = ADC_TIMEOUT;
    Adc_SetupResultBuffer(8, resultbuffer_8);
    Adc_EnableHardwareTrigger(8);
    Adc_ValueGroupType result_8[20];
    Gpt_StartTimer(5, 10000);
    while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
    {
        Adc_timeout--;
    }
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(8, result_8);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC8 test is OK, result is %d\n", result_8[0]);
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC8 test is timeout\n");
        }
        PSPRINTF("\nADC8 test is not OK\n");
    }
    Adc_DisableHardwareTrigger(8);
    Gpt_StopTimer(5);
    INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP0_IRQ989);
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    PSPRINTF("\nTest9:ADC9 SW ADC_CONV_MODE_ONESHOT CFIFO4 RFIFO3 channel:3(CH4 CH5 CH6) ADC_RESOLUTION_BIT12 DMA:CH50 CH51\n");
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_CH50_IRQ103, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH51_IRQ104, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH50_IRQ103, &EDMA_Ch50_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH51_IRQ104, &EDMA_Ch51_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH50_IRQ103);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH51_IRQ104);
    Adc_SetupResultBuffer(9, resultbuffer_9);
    Adc_timeout = ADC_TIMEOUT;
    Adc_StartGroupConversion(9);
    Adc_ValueGroupType result_9[20];
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(9, result_9);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
    {
        PSPRINTF("\nADC9 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[9].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_9[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9 test is timeout\n");
        }
        PSPRINTF("\nADC9 test is not OK\n");
    }

    //Adc_StopGroupConversion(9);
    (void) INTC_LLD_Set_IRQ_Disable(DMA0_CH50_IRQ103);
	(void) INTC_LLD_Set_IRQ_Disable(DMA0_CH51_IRQ104);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
    Gpt_DeInit();
    Adc_DeInit();

    PSPRINTF("\n===============================================DEMO END================================================\n");
}

#if (ADC_HW_TRIGGER_API == STD_ON)
void ADC_demo_Etpu(void)
{
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	static Adc_ValueGroupType resultbuffer_0[20];
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_EnableHardwareTrigger(0);
	Adc_ValueGroupType result_0[20];
	Pwm_Init(&Pwm_Config);
	while((Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(0, result_0);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nEtpu test is OK, result is %d\n", result_0[0]);
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nEtpu test is timeout\n");
		}
		PSPRINTF("\nEtpu test is not OK\n");
	}
	Adc_DisableHardwareTrigger(0);
	Pwm_DeInit();
	Adc_DeInit();
	INTC_LLD_Set_IRQ_Disable(EQADC0_ADC01_GRP0_IRQ965);
}
#endif

void ADC_demo_ExternalMux(void)
{
	uint32 Adc_timeout = ADC_TIMEOUT;
	Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	static Adc_ValueGroupType resultbuffer_0[20];
	static Adc_ValueGroupType resultbuffer_1[20];
	static Adc_ValueGroupType resultbuffer_2[20];
	static Adc_ValueGroupType resultbuffer_3[20];
	int i = 0U;
	Adc_Init(&Config);
	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP0_IRQ989, ADC89_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP0_IRQ989, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP0_IRQ989);
	Adc_SetupResultBuffer(1, resultbuffer_0);
	Adc_StartGroupConversion(1);
	Adc_ValueGroupType result_0[20];
	while((Adc_GetGroupStatus(1) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(1, result_0);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nANW test is OK\n");
		for(i = 0; i < Config.Adc_GroupConfig[1].ChannelCount; i++)
		{
			PSPRINTF("result buffer[%d] is %d\n", i, result_0[i]);
		}
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nANW test is timeout\n");
		}
		PSPRINTF("\nANW test is not OK\n");
	}
	Adc_StopGroupConversion(1);
	INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP0_IRQ989);

	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP1_IRQ990, ADC89_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP1_IRQ990, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP1_IRQ990);
	Adc_SetupResultBuffer(2, resultbuffer_1);
	Adc_StartGroupConversion(2);
	Adc_ValueGroupType result_1[20];
	while((Adc_GetGroupStatus(2) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(2, result_1);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nANX test is OK\n");
		for(i = 0; i < Config.Adc_GroupConfig[2].ChannelCount; i++)
		{
			PSPRINTF("result buffer[%d] is %d\n", i, result_1[i]);
		}
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nANX test is timeout\n");
		}
		PSPRINTF("\nANX test is not OK\n");
	}
	Adc_StopGroupConversion(2);
	INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP1_IRQ990);

	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP2_IRQ991, ADC89_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP2_IRQ991, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP2_IRQ991);
	Adc_SetupResultBuffer(3, resultbuffer_2);
	Adc_StartGroupConversion(3);
	Adc_ValueGroupType result_2[20];
	while((Adc_GetGroupStatus(3) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(3, result_2);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nANY test is OK\n");
		for(i = 0; i < Config.Adc_GroupConfig[3].ChannelCount; i++)
		{
			PSPRINTF("result buffer[%d] is %d\n", i, result_2[i]);
		}
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nANY test is timeout\n");
		}
		PSPRINTF("\nANY test is not OK\n");
	}
	Adc_StopGroupConversion(3);
	INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP2_IRQ991);

	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP4_IRQ993, ADC89_GRP4);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP4_IRQ993, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP4_IRQ993);
	Adc_SetupResultBuffer(4, resultbuffer_3);
	Adc_StartGroupConversion(4);
	for(int i = 0U; i < 100000U; i++);
	Adc_ValueGroupType result_3[20];
	int j = 0U;
	for(i = 0U; i < 10U; i++)
	{
#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(4, result_3);
#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\nconv: %d,ANZ test is OK\n", i);
			for(j = 0; j < Config.Adc_GroupConfig[4].ChannelCount; j++)
			{
				PSPRINTF("result buffer[%d] is %d\n", j, result_3[j]);
			}
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nANZ test is timeout\n");
			}
			PSPRINTF("\nANZ test is not OK\n");
		}
	}
	Adc_StopGroupConversion(4);
	INTC_LLD_Set_IRQ_Disable(EQADC4_ADC89_GRP4_IRQ993);

	Adc_DeInit();

}

void Group0_Notification(void)
{
    Adc_ValueGroupType result_0[20];
    Adc_ReadGroup(0, result_0);
	PSPRINTF("group0 is OK, result is %d\n", result_0[0]);
	return;
}

void Group1_Notification(void)
{
    Adc_ValueGroupType result_1[20];
    Adc_ReadGroup(1, result_1);
	PSPRINTF("group1 is OK, result is %d\n", result_1[0]);
	return;
}

void Group2_Notification(void)
{
    Adc_ValueGroupType result_2[20];
    Adc_ReadGroup(2, result_2);
	PSPRINTF("group2 is OK, result is %d\n", result_2[0]);
	return;
}

void Group3_Notification(void)
{
    Adc_ValueGroupType result_3[20];
    Adc_ReadGroup(3, result_3);
	PSPRINTF("group3 is OK, result is %d\n", result_3[0]);
	return;
}

void Group4_Notification(void)
{
    Adc_ValueGroupType result_4[20];
    Adc_ReadGroup(4, result_4);
	PSPRINTF("group4 is OK, result is %d\n", result_4[0]);
	return;
}

void ADC_demo_PrioQueue(void)
{
	static Adc_ValueGroupType resultbuffer_0[20];
	static Adc_ValueGroupType resultbuffer_1[20];
	static Adc_ValueGroupType resultbuffer_2[20];
	static Adc_ValueGroupType resultbuffer_3[20];
	static Adc_ValueGroupType resultbuffer_4[20];
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP1_IRQ966, ADC01_GRP1);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP1_IRQ966, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP1_IRQ966);
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP2_IRQ967, ADC01_GRP2);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP2_IRQ967, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP2_IRQ967);
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP3_IRQ968, ADC01_GRP3);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP3_IRQ968, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP3_IRQ968);

	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH2_IRQ55, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH3_IRQ56, INTR_PRI_8);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH2_IRQ55, &EDMA_Ch2_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH3_IRQ56, &EDMA_Ch3_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH2_IRQ55);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH3_IRQ56);

	PSPRINTF("\nPriority:group0 is 0, group 1 is 1, group 2 is 2, group 3 is 2, group 4 is 3; QueueMaxDepth:10\n");
	PSPRINTF("\nCase 1: start 0 1 2 3 4\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif

	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(3);
	Adc_StartGroupConversion(4);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);

    Adc_StopGroupConversion(0);
    Adc_StopGroupConversion(1);
    Adc_StopGroupConversion(2);
    Adc_StopGroupConversion(3);
    Adc_StopGroupConversion(4);
    Adc_DeInit();

    PSPRINTF("\nCase 2: start 2 0 4 1 3\n");
    Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 3: start 2 0 4 1 3 stop 2\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(2);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 4: start 2 0 4 1 3 stop 1\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(1);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 5: start 2 0 4 1 3 stop 3\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(3);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 6: start 2 0 4 1 3 stop 4\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(4);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();
}

void ADC_demo_Queue(void)
{
	static Adc_ValueGroupType resultbuffer_0[20];
	static Adc_ValueGroupType resultbuffer_1[20];
	static Adc_ValueGroupType resultbuffer_2[20];
	static Adc_ValueGroupType resultbuffer_3[20];
	static Adc_ValueGroupType resultbuffer_4[20];
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP1_IRQ966, ADC01_GRP1);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP1_IRQ966, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP1_IRQ966);
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP2_IRQ967, ADC01_GRP2);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP2_IRQ967, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP2_IRQ967);
	(void) INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP3_IRQ968, ADC01_GRP3);
	(void) INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP3_IRQ968, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP3_IRQ968);

	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH2_IRQ55, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH3_IRQ56, INTR_PRI_7);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH2_IRQ55, &EDMA_Ch2_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH3_IRQ56, &EDMA_Ch3_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH2_IRQ55);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH3_IRQ56);

	PSPRINTF("\nQueueMaxDepth:10\n");
	PSPRINTF("\nCase 1: start 0 1 2 3 4\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif

	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(3);
	Adc_StartGroupConversion(4);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);

    Adc_StopGroupConversion(0);
    Adc_StopGroupConversion(1);
    Adc_StopGroupConversion(2);
    Adc_StopGroupConversion(3);
    Adc_StopGroupConversion(4);
    Adc_DeInit();

    PSPRINTF("\nCase 2: start 2 0 4 1 3\n");
    Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 3: start 2 0 4 1 3 stop 1\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(1);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 4: start 2 0 4 1 3 stop 3\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(3);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();

	PSPRINTF("\nCase 5: start 2 0 4 1 3 stop 4\n");
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(2, resultbuffer_2);
	Adc_SetupResultBuffer(3, resultbuffer_3);
	Adc_SetupResultBuffer(4, resultbuffer_4);

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_EnableGroupNotification(0);
	Adc_EnableGroupNotification(1);
	Adc_EnableGroupNotification(2);
	Adc_EnableGroupNotification(3);
	Adc_EnableGroupNotification(4);
#endif
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(1);
	Adc_StartGroupConversion(3);
	Adc_StopGroupConversion(4);

	Gpt_Stm_LLD_DelayMs(STM1, 1000U);
	Adc_StopGroupConversion(0);
	Adc_StopGroupConversion(1);
	Adc_StopGroupConversion(2);
	Adc_StopGroupConversion(3);
	Adc_StopGroupConversion(4);

	Adc_DeInit();
}

#if (ADC_HW_TRIGGER_API == STD_ON)
void ADC_demo_MultiGroup(void)
{
	Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	int i = 0U;
	int j = 0U;
	static Adc_ValueGroupType resultbuffer[ADC_CONFIG_GROUPS][10];

	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP1_IRQ966, ADC01_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP1_IRQ966, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP1_IRQ966);
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP2_IRQ967, ADC01_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP2_IRQ967, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP2_IRQ967);
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP3_IRQ968, ADC01_GRP3);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP3_IRQ968, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP3_IRQ968);
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP4_IRQ969, ADC01_GRP4);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP4_IRQ969, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP4_IRQ969);

	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP1_IRQ972, ADC23_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP1_IRQ972, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP1_IRQ972);

	INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP0_IRQ977, ADC45_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP0_IRQ977, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP0_IRQ977);
	INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP1_IRQ978, ADC45_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP1_IRQ978, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP1_IRQ978);
	INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP2_IRQ979, ADC45_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP2_IRQ979, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP2_IRQ979);

	INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP0_IRQ983, ADC67_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP0_IRQ983, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP0_IRQ983);
	INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP2_IRQ985, ADC67_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP2_IRQ985, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP2_IRQ985);
	INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP3_IRQ986, ADC67_GRP3);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP3_IRQ986, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP3_IRQ986);

	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP0_IRQ989, ADC89_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP0_IRQ989, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP0_IRQ989);
	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP5_IRQ994, ADC89_GRP5);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP5_IRQ994, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP5_IRQ994);
	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP2_IRQ991, ADC89_GRP2);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP2_IRQ991, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP2_IRQ991);
	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP1_IRQ990, ADC89_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP1_IRQ990, INTR_PRI_10);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP1_IRQ990);

	PSPRINTF("\n============================================MULTIGROUP TEST============================================\n");
	Adc_ValueGroupType result[ADC_CONFIG_GROUPS][10];
	Adc_Init(&Config);
	for(i = 0U; i < ADC_CONFIG_GROUPS; i++)
	{
		Adc_SetupResultBuffer(i, &resultbuffer[i][0]);
	}
	Adc_EnableHardwareTrigger(1);
	Adc_EnableHardwareTrigger(3);
	Adc_EnableHardwareTrigger(8);
	Adc_EnableHardwareTrigger(11);
	Adc_EnableHardwareTrigger(14);

	Adc_StartGroupConversion(0);
	Adc_StartGroupConversion(2);
	Adc_StartGroupConversion(4);
	Adc_StartGroupConversion(5);
	Adc_StartGroupConversion(6);
	Adc_StartGroupConversion(7);
	Adc_StartGroupConversion(9);
	Adc_StartGroupConversion(10);
	Adc_StartGroupConversion(12);
	Adc_StartGroupConversion(13);
	Adc_StartGroupConversion(15);
	Adc_StartGroupConversion(16);

	Pwm_Init(&Pwm_Config);
	for(i = 0U; i < 10000U; i++);

	for(i = 0U; i < ADC_CONFIG_GROUPS; i++)
	{
		memset(&result[i][0], 0, 10U);
		u8Adc_TempReturn = Adc_ReadGroup(i, &result[i][0]);
		if(u8Adc_TempReturn == E_OK)
		{
			for(j = 0; j < Config.Adc_GroupConfig[i].ChannelCount; j++)
			{
				if(result[i][j] != 0)
				{
					PSPRINTF("\ngroup %d is ok\n", i);
					PSPRINTF("\nresult_adc[%d][%d] is %d\n", i, j, result[i][j]);
				}
				else
				{
					PSPRINTF("\ngroup %d is not ok\n", i);
				}
			}
		}
	}

	Adc_DisableHardwareTrigger(1);
	Adc_DisableHardwareTrigger(3);
	Adc_DisableHardwareTrigger(8);
	Adc_DisableHardwareTrigger(11);
	Adc_DisableHardwareTrigger(14);

	Pwm_DeInit();
	Adc_DeInit();
	PSPRINTF("\n===============================================DEMO END================================================\n");
}
#endif

#if (ADC_READ_GROUP_API == STD_ON)
void ADC_0206(void)
{
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    ADC_0010();
#endif
    u8Adc_TempReturn = Adc_ReadGroup(0, NULL_PTR);

    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_READGROUP_ID)  && (Det_ErrorId == ADC_E_PARAM_POINTER))
        {
            if(u8Adc_TempReturn == E_NOT_OK)
            {
                PSPRINTF("ADC_0206 is OK\n");
            }
            else
            {
                PSPRINTF("ADC_0206 is not OK\n");
            }
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void ADC_0207(void)
{
	Adc_Init(&Config);
	Adc_StopGroupConversion(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_STOPGROUPCONVERSION_ID) && (Det_ErrorId == ADC_E_WRONG_TRIGG_SRC))
        {
        	if(Det_ErrorId == ADC_E_WRONG_TRIGG_SRC)
        	{
        		PSPRINTF("ADC_0207 is OK\n");
        	}
        	else
        	{
        		PSPRINTF("ADC_0207 is not OK\n");
        	}

        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0208(void)
{
	Adc_Init(&Config);
	Adc_StopGroupConversion(0);
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
void ADC_0209(void)
{
	Adc_Init(&Config);
    Adc_DisableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_WRONG_TRIGG_SRC))
        {
            PSPRINTF("ADC_0209 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0209 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0210(void)
{
	Adc_Init(&Config);
    Adc_DisableHardwareTrigger(0);
    if(ADC_DEV_ERROR_DETECT == STD_ON)
    {
        if((Det_ModuleId == ADC_MODULE_ID) && (Det_ApiId == ADC_DISABLEHARDWARETRIGGER_ID)  && (Det_ErrorId == ADC_E_WRONG_CONV_MODE))
        {
            PSPRINTF("ADC_0210 is OK\n");
        }
        else
        {
            PSPRINTF("ADC_0210 is not OK\n");
        }
    }//ADC_DEV_ERROR_DETECT == STD_ON
}

void ADC_0211(void)
{
	Adc_Init(&Config);
    Adc_DisableHardwareTrigger(0);
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
void ADC_0212_213(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer);
    Adc_StartGroupConversion(5);
    if(Adc_GetGroupStatus(5) == ADC_BUSY)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(5, result);
    	if(Adc_GetGroupStatus(5) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0212 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0212 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(5, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(5) == ADC_BUSY)
		{
			PSPRINTF("ADC_0213 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0213 is not OK\n");
		}
    }
}

void ADC_0214_215(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer);
    Adc_StartGroupConversion(5);
    while((Adc_GetGroupStatus(5) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	PSPRINTF("ADC_0214 is OK\n");
    	Adc_StopGroupConversion(5);
    	if(Adc_GetGroupStatus(5) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0215 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0215 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0216(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType result[20];
    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer);
    Adc_StartGroupConversion(5);
    while((Adc_GetGroupStatus(5) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(5, result);
    	if(Adc_GetGroupStatus(5) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0216 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0216 is not OK\n");
    	}
#endif
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0217(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer);
    Adc_StartGroupConversion(5);
    while((Adc_GetGroupStatus(5) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_GetStreamLastPointer(5, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(5) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0217 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0217 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0218(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer);
    Adc_StartGroupConversion(5);
    while((Adc_GetGroupStatus(5) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_StartGroupConversion(5);
    	if(Adc_GetGroupStatus(5) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0218 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0218 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0219_220(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer);
    if(Adc_GetGroupStatus(5) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(5, result);
    	if(Adc_GetGroupStatus(5) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0219 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0219 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(5, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(5) == ADC_IDLE)
		{
			PSPRINTF("ADC_0220 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0220 is not OK\n");
		}
    }
}

void ADC_0262_265(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(9, resultbuffer);
    Adc_StartGroupConversion(9);
    if(Adc_GetGroupStatus(9) == ADC_BUSY)
    {
    	PSPRINTF("ADC_0262 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(9, result);
    	if(Adc_GetGroupStatus(9) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0263 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0263 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(9, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(9) == ADC_BUSY)
		{
			PSPRINTF("ADC_0264 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0264 is not OK\n");
		}
		Adc_StopGroupConversion(9);
		if(Adc_GetGroupStatus(9) == ADC_IDLE)
		{
			PSPRINTF("ADC_0265 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0265 is not OK\n");
		}
    }
}

void ADC_0266_267(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(9, resultbuffer);
    Adc_StartGroupConversion(9);
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	PSPRINTF("ADC_0266 is OK\n");
    	Adc_StopGroupConversion(9);
    	if(Adc_GetGroupStatus(9) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0267 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0267 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0268(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType result[20];
    Adc_Init(&Config);
    Adc_SetupResultBuffer(9, resultbuffer);
    Adc_StartGroupConversion(9);
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
    if(Adc_timeout > 0U)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(9, result);
    	if(Adc_GetGroupStatus(9) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0268 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0268 is not OK\n");
    	}
#endif
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }

}

void ADC_0269(void)
{
    Adc_ValueGroupType resultbuffer[20];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(9, resultbuffer);
    Adc_StartGroupConversion(9);
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
    if(Adc_timeout > 0U)
    {
    	Adc_GetStreamLastPointer(9, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(9) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0269 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0269 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
}

void ADC_0270_271(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(9, resultbuffer);
    if(Adc_GetGroupStatus(9) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(9, result);
    	if(Adc_GetGroupStatus(9) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0270 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0270 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(9, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(9) == ADC_IDLE)
		{
			PSPRINTF("ADC_0271 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0271 is not OK\n");
		}
    }
}

void ADC_0272_275(void)
{
	static Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    if(Adc_GetGroupStatus(10) == ADC_BUSY)
    {
    	PSPRINTF("ADC_0272 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(10, result);
    	if(Adc_GetGroupStatus(10) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0273 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0273 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(10, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(10) == ADC_BUSY)
		{
			PSPRINTF("ADC_0274 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0274 is not OK\n");
		}
		Adc_StopGroupConversion(10);
		if(Adc_GetGroupStatus(10) == ADC_IDLE)
		{
			PSPRINTF("ADC_0275 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0275 is not OK\n");
		}
    }
}

void ADC_0276(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	PSPRINTF("ADC_0276 is OK\n");
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0277(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	PSPRINTF("ADC_0277 is OK\n");
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0278(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType result[100];
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(10, result);
    	if(Adc_GetGroupStatus(10) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0278 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0278 is not OK\n");
    	}
#endif
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0279(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_GetStreamLastPointer(10, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(10) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0279 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0279 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0280(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_StopGroupConversion(10);
    	if(Adc_GetGroupStatus(10) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0280 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0280 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0281(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_timeout = ADC_TIMEOUT;
    	while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
		{
			Adc_timeout--;
		}
    	if(Adc_timeout > 0U)
    	{
    		PSPRINTF("ADC_0281 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0281 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0282(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_timeout = ADC_TIMEOUT;
    	while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
    	{
			Adc_timeout--;
		}
		if(Adc_timeout > 0U)
    	{
    		PSPRINTF("ADC_0282 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0282 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0283(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType result[100];
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(10, result);
    	if(Adc_GetGroupStatus(10) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0283 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0283 is not OK\n");
    	}
#endif
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0284(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_GetStreamLastPointer(10, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(10) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0284 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0284 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0285(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_StopGroupConversion(10);
    	if(Adc_GetGroupStatus(10) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0285 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0285 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0286_287(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(10, resultbuffer);
    if(Adc_GetGroupStatus(10) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(10, result);
    	if(Adc_GetGroupStatus(10) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0286 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0286 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(10, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(10) == ADC_IDLE)
		{
			PSPRINTF("ADC_0287 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0287 is not OK\n");
		}
    }
}

void ADC_0288_291(void)
{
	static Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    if(Adc_GetGroupStatus(11) == ADC_BUSY)
    {
    	PSPRINTF("ADC_0288 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(11, result);
    	if(Adc_GetGroupStatus(11) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0289 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0289 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(11, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(11) == ADC_BUSY)
		{
			PSPRINTF("ADC_0290 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0290 is not OK\n");
		}
		Adc_StopGroupConversion(11);
		if(Adc_GetGroupStatus(11) == ADC_IDLE)
		{
			PSPRINTF("ADC_0291 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0291 is not OK\n");
		}
    }
}

void ADC_0292(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	PSPRINTF("ADC_0292 is OK\n");
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0293(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	PSPRINTF("ADC_0293 is OK\n");
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0294(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType result[100];
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(11, result);
    	if(Adc_GetGroupStatus(11) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0294 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0294 is not OK\n");
    	}
#endif
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0295(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_GetStreamLastPointer(11, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(11) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0295 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0295 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0296(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_StopGroupConversion(11);
    	if(Adc_GetGroupStatus(11) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0296 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0296 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0297(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_timeout = ADC_TIMEOUT;
    	while((Adc_GetGroupStatus(11) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
		{
			Adc_timeout--;
		}
    	if(Adc_timeout > 0U)
    	{
    		PSPRINTF("ADC_0297 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0297 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0298(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType result[100];
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(11, result);
    	if(Adc_GetGroupStatus(11) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0298 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0298 is not OK\n");
    	}
#endif
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0299(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_GetStreamLastPointer(11, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(11) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0299 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0299 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0300(void)
{
    Adc_ValueGroupType resultbuffer[100];
    INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
    uint32 Adc_timeout = ADC_TIMEOUT;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
    if(Adc_timeout > 0U)
    {
    	Adc_StopGroupConversion(11);
    	if(Adc_GetGroupStatus(11) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0300 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0300 is not OK\n");
    	}
    }
    else
    {
    	PSPRINTF("timeout......\n");
    }
    INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0301_302(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(11, resultbuffer);
    if(Adc_GetGroupStatus(11) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(11, result);
    	if(Adc_GetGroupStatus(11) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0301 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0301 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(11, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(11) == ADC_IDLE)
		{
			PSPRINTF("ADC_0302 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0302 is not OK\n");
		}
    }
}

void demo_AllChannel(void)
{
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP0_IRQ965, ADC01_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP0_IRQ965, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP0_IRQ965);
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	INTC_LLD_Set_IRQ_Handle(EQADC2_ADC45_GRP0_IRQ977, ADC45_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC2_ADC45_GRP0_IRQ977, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC2_ADC45_GRP0_IRQ977);
	INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP0_IRQ983, ADC67_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP0_IRQ983, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP0_IRQ983);
	INTC_LLD_Set_IRQ_Handle(EQADC4_ADC89_GRP0_IRQ989, ADC89_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC4_ADC89_GRP0_IRQ989, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC4_ADC89_GRP0_IRQ989);
	static Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
	uint32 Adc_timeout = ADC_TIMEOUT;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	uint8 Index = 0U;
	uint8 Index_Temp = 0U;
    uint8 ResultIndex = 0U;
	Adc_Init(&Config);
	for(Index = 0U; Index < ADC_CONFIG_GROUPS; Index++)
	{
		Adc_timeout = ADC_TIMEOUT;
		Adc_SetupResultBuffer(Index, resultbuffer);
		Adc_StartGroupConversion(Index);
		while((Adc_GetGroupStatus(Index) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
		{
			Adc_timeout--;
		}
		if(Adc_timeout > 0U)
		{
#if (ADC_READ_GROUP_API == STD_ON)
			u8Adc_TempReturn = Adc_ReadGroup(Index, result);
			if(u8Adc_TempReturn == (Std_ReturnType)E_OK)
			{
				for(ResultIndex = 0U; ResultIndex < Config.Adc_GroupConfig[Index].ChannelCount; ResultIndex++)
				{
					PSPRINTF("group %d: channel %d result is %d\n", Index, ResultIndex, result[ResultIndex]);
				}
			}
			else
			{
				PSPRINTF("group %d is not ok\n", Index);
			}
			for(Index_Temp = 0U; Index_Temp < 100U; Index_Temp++)
			{
				resultbuffer[Index_Temp] = 0U;
				result[Index_Temp] = 0U;
			}
#endif
		}
		else
		{
			PSPRINTF("group %d is timeout, %d\n\n", Index);
		}
	}
	Adc_DeInit();
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
void ADC_0221_224(void)
{
	static Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(6, resultbuffer);
    Adc_EnableHardwareTrigger(6);
    if(Adc_GetGroupStatus(6) == ADC_BUSY)
    {
    	PSPRINTF("ADC_0221 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(6, result);
    	if(Adc_GetGroupStatus(6) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0222 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0222 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(6, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(6) == ADC_BUSY)
		{
			PSPRINTF("ADC_0223 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0223 is not OK\n");
		}

		Adc_DisableHardwareTrigger(6);
		if(Adc_GetGroupStatus(6) == ADC_IDLE)
		{
			PSPRINTF("ADC_0224 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0224 is not OK\n");
		}
    }
}

void ADC_0225_226(void)
{
	Adc_ValueGroupType resultbuffer[20];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	Adc_ValueGroupType result[20];
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(6, resultbuffer);
	Adc_EnableHardwareTrigger(6);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		PSPRINTF("ADC_0225 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(6, result);
		if(Adc_GetGroupStatus(6) == ADC_BUSY)
		{
			PSPRINTF("ADC_0226 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0226 is not OK\n");
		}
#endif
	}
	else
	{
		PSPRINTF("timeout......\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0227(void)
{
	Adc_ValueGroupType resultbuffer[20];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(6, resultbuffer);
	Adc_EnableHardwareTrigger(6);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_GetStreamLastPointer(6, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(6) == ADC_BUSY)
		{
			PSPRINTF("ADC_0227 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0227 is not OK\n");
		}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0228(void)
{
	Adc_ValueGroupType resultbuffer[20];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(6, resultbuffer);
	Adc_EnableHardwareTrigger(6);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_DisableHardwareTrigger(6);
		if(Adc_GetGroupStatus(6) == ADC_IDLE)
		{
			PSPRINTF("ADC_0228 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0228 is not OK\n");
		}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0229_230(void)
{
	Adc_ValueGroupType resultbuffer[20];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(6, resultbuffer);
    if(Adc_GetGroupStatus(6) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(6, result);
    	if(Adc_GetGroupStatus(6) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0229 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0229 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(6, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(6) == ADC_IDLE)
		{
			PSPRINTF("ADC_0230 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0230 is not OK\n");
		}
    }
}

void ADC_0231_234(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(7, resultbuffer);
    Adc_EnableHardwareTrigger(7);
    if(Adc_GetGroupStatus(7) == ADC_BUSY)
    {
    	PSPRINTF("ADC_0231 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(7, result);
    	if(Adc_GetGroupStatus(7) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0232 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0232 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(7, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(7) == ADC_BUSY)
		{
			PSPRINTF("ADC_0233 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0233 is not OK\n");
		}

		Adc_DisableHardwareTrigger(7);
		if(Adc_GetGroupStatus(7) == ADC_IDLE)
		{
			PSPRINTF("ADC_0234 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0234 is not OK\n");
		}
    }
}

void ADC_0235(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_COMPLETED)  && (Adc_timeout > 0U));
	if(Adc_timeout > 0U)
	{
		PSPRINTF("ADC_0235 is OK\n");
	}
	else
	{
		PSPRINTF("ADC_0235 is not OK\n");
	}
	while(Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED);
}

void ADC_0236(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		if(Adc_GetGroupStatus(7) == ADC_STREAM_COMPLETED)
		{
			PSPRINTF("ADC_0236 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0236 is not OK\n");
		}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}
}

void ADC_0237(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
	if(Adc_timeout > 0U)
	{
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(7, result);
    	if(Adc_GetGroupStatus(7) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0237 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0237 is not OK\n");
    	}
#endif
	}
	else
	{
		PSPRINTF("ADC_0237 is timeout\n");
	}

}

void ADC_0238(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
	if(Adc_timeout > 0U)
	{
		Adc_GetStreamLastPointer(7, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(7) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0238 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0238 is not OK\n");
    	}
	}
}

void ADC_0239(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_DisableHardwareTrigger(7);
    	if(Adc_GetGroupStatus(7) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0239 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0239 is not OK\n");
    	}
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0240(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_timeout = ADC_TIMEOUT;
		while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
		{
			Adc_timeout--;
		}
		if(Adc_timeout > 0U)
		{
			if(Adc_GetGroupStatus(7) == ADC_STREAM_COMPLETED)
			{
				PSPRINTF("ADC_0240 is OK\n");
			}
			else
			{
				PSPRINTF("ADC_0240 is not OK\n");
			}
		}
		else
		{
			PSPRINTF("timeout......\n");
		}
	}
	else
	{
		PSPRINTF("ADC_0240 is not OK\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0241(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
	if(Adc_timeout > 0U)
	{
		Adc_EnableHardwareTrigger(7);
		if(Adc_GetGroupStatus(7) == ADC_BUSY)
		{
			PSPRINTF("ADC_0241 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0241 is not OK\n");
		}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}
}

void ADC_0242(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(7, result);
    	if(Adc_GetGroupStatus(7) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0242 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0242 is not OK\n");
    	}
#endif
	}
	else
	{
		PSPRINTF("timeout......\n");
	}

	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0243(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_GetStreamLastPointer(7, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(7) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0243 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0243 is not OK\n");
    	}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}

	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0244(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(7, resultbuffer);
	Adc_EnableHardwareTrigger(7);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_DisableHardwareTrigger(7);
    	if(Adc_GetGroupStatus(7) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0244 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0244 is not OK\n");
    	}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}

	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0245_246(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(7, resultbuffer);
    if(Adc_GetGroupStatus(7) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(7, result);
    	if(Adc_GetGroupStatus(7) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0245 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0245 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(7, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(7) == ADC_IDLE)
		{
			PSPRINTF("ADC_0246 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0246 is not OK\n");
		}
    }
}

void ADC_0247_250(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(8, resultbuffer);
    Adc_EnableHardwareTrigger(8);
    if(Adc_GetGroupStatus(8) == ADC_BUSY)
    {
    	PSPRINTF("ADC_0247 is OK\n");
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(8, result);
    	if(Adc_GetGroupStatus(8) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0248 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0248 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(8, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(8) == ADC_BUSY)
		{
			PSPRINTF("ADC_0249 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0249 is not OK\n");
		}

		Adc_DisableHardwareTrigger(8);
		if(Adc_GetGroupStatus(8) == ADC_IDLE)
		{
			PSPRINTF("ADC_0250 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0250 is not OK\n");
		}
    }
}

void ADC_0251(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		PSPRINTF("ADC_0251 is OK\n");
	}
	else
	{
		PSPRINTF("ADC_0251 is not OK\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0252(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		if(Adc_GetGroupStatus(8) == ADC_STREAM_COMPLETED)
		{
			PSPRINTF("ADC_0252 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0252 is not OK\n");
		}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0253(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(8, result);
    	if(Adc_GetGroupStatus(8) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0253 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0253 is not OK\n");
    	}
#endif
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0254(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_GetStreamLastPointer(8, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(8) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0254 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0254 is not OK\n");
    	}
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0255(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_DisableHardwareTrigger(8);
    	if(Adc_GetGroupStatus(8) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0255 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0255 is not OK\n");
    	}
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0256(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_timeout = ADC_TIMEOUT;
		while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
		{
			Adc_timeout--;
		}
		if(Adc_timeout > 0U)
		{
			if(Adc_GetGroupStatus(8) == ADC_STREAM_COMPLETED)
			{
				PSPRINTF("ADC_0256 is OK\n");
			}
			else
			{
				PSPRINTF("ADC_0256 is not OK\n");
			}
		}
		else
		{
			PSPRINTF("timeout......\n");
		}
	}
	else
	{
		PSPRINTF("ADC_0256 is not OK\n");
	}
	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0257(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(8, result);
    	if(Adc_GetGroupStatus(8) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0257 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0257 is not OK\n");
    	}
#endif
	}
	else
	{
		PSPRINTF("timeout......\n");
	}

	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0258(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_GetStreamLastPointer(8, &PtrToSamplePtr);
    	if(Adc_GetGroupStatus(8) == ADC_BUSY)
    	{
    		PSPRINTF("ADC_0258 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0258 is not OK\n");
    	}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}

	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0259(void)
{
	Adc_ValueGroupType resultbuffer[100];
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
#endif
	INTC_LLD_Set_IRQ_Handle(EQADC1_ADC23_GRP0_IRQ971, ADC23_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC1_ADC23_GRP0_IRQ971, INTR_PRI_7);
	INTC_LLD_Set_IRQ_Enable(EQADC1_ADC23_GRP0_IRQ971);
	uint32 Adc_timeout = ADC_TIMEOUT;
	Adc_Init(&Config);
	Adc_SetupResultBuffer(8, resultbuffer);
	Adc_EnableHardwareTrigger(8);
#ifdef DioConf_DioChannel_DioChannel_A2
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
#endif
	while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED)  && (Adc_timeout > 0U))
	{
		Adc_timeout--;
	}
	if(Adc_timeout > 0U)
	{
		Adc_DisableHardwareTrigger(8);
    	if(Adc_GetGroupStatus(8) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0259 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0259 is not OK\n");
    	}
	}
	else
	{
		PSPRINTF("timeout......\n");
	}

	INTC_LLD_Set_IRQ_Disable(EQADC1_ADC23_GRP0_IRQ971);
}

void ADC_0260_261(void)
{
	Adc_ValueGroupType resultbuffer[100];
	Adc_ValueGroupType result[20];
	Adc_ValueGroupType PtrToSample = 0;
	Adc_ValueGroupType *PtrToSamplePtr = &PtrToSample;
    Adc_Init(&Config);
    Adc_SetupResultBuffer(8, resultbuffer);
    if(Adc_GetGroupStatus(8) == ADC_IDLE)
    {
#if (ADC_READ_GROUP_API == STD_ON)
    	Adc_ReadGroup(8, result);
    	if(Adc_GetGroupStatus(8) == ADC_IDLE)
    	{
    		PSPRINTF("ADC_0260 is OK\n");
    	}
    	else
    	{
    		PSPRINTF("ADC_0260 is not OK\n");
    	}
#endif
    	Adc_GetStreamLastPointer(8, &PtrToSamplePtr);
		if(Adc_GetGroupStatus(8) == ADC_IDLE)
		{
			PSPRINTF("ADC_0261 is OK\n");
		}
		else
		{
			PSPRINTF("ADC_0261 is not OK\n");
		}
    }
}
#endif

void ADC_0320(void)
{
	INTC_LLD_Set_IRQ_Handle(EQADC0_ADC01_GRP1_IRQ966, ADC01_GRP1);
	INTC_LLD_Set_IRQ_Priority(EQADC0_ADC01_GRP1_IRQ966, INTR_PRI_39);
	INTC_LLD_Set_IRQ_Enable(EQADC0_ADC01_GRP1_IRQ966);
	(void) INTC_LLD_Set_IRQ_Priority(DMA0_CH5_IRQ58, INTR_PRI_39);
	(void) INTC_LLD_Set_IRQ_Handle(DMA0_CH5_IRQ58, &EDMA_Ch5_IRQHandler);
	(void) INTC_LLD_Set_IRQ_Enable(DMA0_CH5_IRQ58);
	INTC_LLD_Set_IRQ_Handle(EQADC3_ADC67_GRP0_IRQ983, ADC67_GRP0);
	INTC_LLD_Set_IRQ_Priority(EQADC3_ADC67_GRP0_IRQ983, INTR_PRI_39);
	INTC_LLD_Set_IRQ_Enable(EQADC3_ADC67_GRP0_IRQ983);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 0);
	static Adc_ValueGroupType resultbuffer_0[20];
	static Adc_ValueGroupType resultbuffer_1[20];
	static Adc_ValueGroupType resultbuffer_5[20];
	static Adc_ValueGroupType resultbuffer_6[20];
	Adc_Init(&Config);
	Adc_SetupResultBuffer(0, resultbuffer_0);
	Adc_SetupResultBuffer(1, resultbuffer_1);
	Adc_SetupResultBuffer(5, resultbuffer_5);
	Adc_SetupResultBuffer(6, resultbuffer_6);
	TesterDemoADC = true;
}

void ADC_0320_Main(void)
{
	if(TesterDemoADC == TRUE)
	{
		uint32 Adc_timeout = ADC_TIMEOUT;
		Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
		Adc_StartGroupConversion(1);
		Adc_ValueGroupType result_1[20];
		for(int i = 0; i < 1000U; i++);
	#if (ADC_READ_GROUP_API == STD_ON)
		u8Adc_TempReturn = Adc_ReadGroup(1, result_1);
	#endif
		if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
		{
			PSPRINTF("\nADC1 result is %d\n", result_1[0]);
		}
		else
		{
			if(Adc_timeout == 0)
			{
				PSPRINTF("\nADC1 is timeout\n");
			}
			PSPRINTF("\nADC1 is not OK\n");
		}
	}
}

void ADC_GPT_Callback_10ms_Function(void)
{
	static uint32 Adc_timeout = ADC_TIMEOUT;
	Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	Adc_StartGroupConversion(0);
	Adc_ValueGroupType result_0[20];
	for(int i = 0; i < 1000U; i++);
	if ((Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED))
	{
		Adc_timeout--;
		if (Adc_timeout == 0)
		{
			Adc_timeout = ADC_TIMEOUT;
		}
		else
		{
			return;
		}
	}
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(0, result_0);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nADC0 result is %d\n", result_0[0]);
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nADC0 is timeout\n");
		}
		PSPRINTF("\nADC0 is not OK\n");
	}
}

void ADC_GPT_Callback_20ms_Function(void)
{
	uint32 Adc_timeout = ADC_TIMEOUT;
	Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	Adc_StartGroupConversion(5);
	Adc_ValueGroupType result_5[20];
	for(int i = 0; i < 1000U; i++);
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(5, result_5);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nADC5 result is %d\n", result_5[0]);
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nADC5 is timeout\n");
		}
		PSPRINTF("\nADC5 is not OK\n");
	}

	Adc_StopGroupConversion(5);
}

void ADC_GPT_Callback_30ms_Function(void)
{
	static uint32 Adc_timeout = ADC_TIMEOUT;
	Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
	Adc_EnableHardwareTrigger(6);
	Adc_ValueGroupType result_6[20];
	for(int i = 0; i < 1000U; i++);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_A2 , 1);
	if ((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED))
	{
		Adc_timeout--;
		if (Adc_timeout == 0)
		{
			Adc_timeout = ADC_TIMEOUT;
		}
		else
		{
			return;
		}
	}
#if (ADC_READ_GROUP_API == STD_ON)
	u8Adc_TempReturn = Adc_ReadGroup(6, result_6);
#endif
	if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0U))
	{
		PSPRINTF("\nADC6 result is %d\n", result_6[0]);
	}
	else
	{
		if(Adc_timeout == 0)
		{
			PSPRINTF("\nADC6 is timeout\n");
		}
		PSPRINTF("\nADC6 is not OK\n");
	}
	Adc_DisableHardwareTrigger(6);
}
#endif

void ADC_Project_Service1(void)
{
    PSPRINTF("\n============================================SERVICE1 DEMO TEST==========================================\n");
    uint32 Adc_timeout = ADC_TIMEOUT;
    int i = 0;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    static Adc_ValueGroupType resultbuffer_0[20];
    static Adc_ValueGroupType resultbuffer_1[20];
    static Adc_ValueGroupType resultbuffer_2[20];
    static Adc_ValueGroupType resultbuffer_3[20];
    static Adc_ValueGroupType resultbuffer_4[20];

    Adc_Init(&Config);
    Adc_SetupResultBuffer(0, resultbuffer_0);
    Adc_SetupResultBuffer(1, resultbuffer_1);
    Adc_SetupResultBuffer(2, resultbuffer_2);
    Adc_SetupResultBuffer(3, resultbuffer_3);
    Adc_SetupResultBuffer(4, resultbuffer_4);
    EQADC_EnableInterrupt(0, 0);
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    Adc_StartGroupConversion(0);
    while((Adc_GetGroupStatus(0) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_0[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(0, result_0);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC0 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[0].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_0[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC0 test is timeout\n");
        }
        PSPRINTF("\nADC0 test is not OK\n");
    }
    Adc_StopGroupConversion(0);
    EQADC_DisableInterrupt(0, 0);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(0, 1);
    Adc_StartGroupConversion(1);
    while((Adc_GetGroupStatus(1) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_1[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(1, result_1);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC1 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[1].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_1[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC1 test is timeout\n");
        }
        PSPRINTF("\nADC1 test is not OK\n");
    }
    Adc_StopGroupConversion(1);
    EQADC_DisableInterrupt(0, 1);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(1, 0);
    Adc_StartGroupConversion(2);
    while((Adc_GetGroupStatus(2) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_2[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(2, result_2);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC2 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[2].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_2[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC2 test is timeout\n");
        }
        PSPRINTF("\nADC2 test is not OK\n");
    }
    Adc_StopGroupConversion(2);
    EQADC_DisableInterrupt(1, 0);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(1, 1);
    Adc_StartGroupConversion(3);
    while((Adc_GetGroupStatus(3) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_3[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(3, result_3);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC3 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[3].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_3[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC3 test is timeout\n");
        }
        PSPRINTF("\nADC3 test is not OK\n");
    }
    Adc_StopGroupConversion(3);
    EQADC_DisableInterrupt(1, 1);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(2, 0);
    Adc_StartGroupConversion(4);
    while((Adc_GetGroupStatus(4) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_4[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(4, result_4);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC4 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[4].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_4[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC4 test is timeout\n");
        }
        PSPRINTF("\nADC4 test is not OK\n");
    }
    Adc_StopGroupConversion(4);
    EQADC_DisableInterrupt(2, 0);
    Adc_timeout = ADC_TIMEOUT;
#endif

    Adc_DeInit();
    PSPRINTF("\n===============================================DEMO END================================================\n");
}

void ADC_Project_Service2(void)
{
    PSPRINTF("\n============================================SERVICE2 DEMO TEST==========================================\n");
    uint32 Adc_timeout = ADC_TIMEOUT;
    int i = 0;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;

    static Adc_ValueGroupType resultbuffer_5[20];
    static Adc_ValueGroupType resultbuffer_6[20];
    static Adc_ValueGroupType resultbuffer_7[20];
    static Adc_ValueGroupType resultbuffer_8[20];

    Adc_Init(&Config);
    Adc_SetupResultBuffer(5, resultbuffer_5);
    Adc_SetupResultBuffer(6, resultbuffer_6);
    Adc_SetupResultBuffer(7, resultbuffer_7);
    Adc_SetupResultBuffer(8, resultbuffer_8);

    EQADC_EnableInterrupt(2, 1);
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    Adc_StartGroupConversion(5);
    while((Adc_GetGroupStatus(5) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_5[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(5, result_5);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC5 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[5].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_5[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC5 test is timeout\n");
        }
        PSPRINTF("\nADC5 test is not OK\n");
    }
    Adc_StopGroupConversion(5);
    EQADC_DisableInterrupt(2, 1);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(3, 0);
    Adc_StartGroupConversion(6);
    while((Adc_GetGroupStatus(6) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_6[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(6, result_6);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC6 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[6].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_6[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC6 test is timeout\n");
        }
        PSPRINTF("\nADC6 test is not OK\n");
    }
    Adc_StopGroupConversion(6);
    EQADC_DisableInterrupt(3, 0);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(3, 1);
    Adc_StartGroupConversion(7);
    while((Adc_GetGroupStatus(7) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_7[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(7, result_7);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC7 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[7].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_7[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC7 test is timeout\n");
        }
        PSPRINTF("\nADC7 test is not OK\n");
    }
    Adc_StopGroupConversion(7);
    EQADC_DisableInterrupt(3, 1);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(4, 0);
    Adc_StartGroupConversion(8);
    while((Adc_GetGroupStatus(8) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_8[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(8, result_8);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC8 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[8].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_8[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC8 test is timeout\n");
        }
        PSPRINTF("\nADC8 test is not OK\n");
    }
    Adc_StopGroupConversion(8);
    EQADC_DisableInterrupt(4, 0);
    Adc_timeout = ADC_TIMEOUT;
#endif

    Adc_DeInit();
    PSPRINTF("\n===============================================DEMO END================================================\n");
}

void ADC_Project_Service3(void)
{
    PSPRINTF("\n============================================SERVICE3 DEMO TEST==========================================\n");
    uint32 Adc_timeout = ADC_TIMEOUT;
    int i = 0;
    Std_ReturnType u8Adc_TempReturn = (Std_ReturnType)E_NOT_OK;
    static Adc_ValueGroupType resultbuffer_9[20];
    static Adc_ValueGroupType resultbuffer_10[20];
    static Adc_ValueGroupType resultbuffer_11[20];
    static Adc_ValueGroupType resultbuffer_12[20];
    static Adc_ValueGroupType resultbuffer_13[20];

    Adc_Init(&Config);
    Adc_SetupResultBuffer(9, resultbuffer_9);
    Adc_SetupResultBuffer(10, resultbuffer_10);
    Adc_SetupResultBuffer(11, resultbuffer_11);
    Adc_SetupResultBuffer(12, resultbuffer_12);
    Adc_SetupResultBuffer(13, resultbuffer_13);

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    EQADC_EnableInterrupt(4, 1);
    Adc_StartGroupConversion(9);
    while((Adc_GetGroupStatus(9) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_9[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(9, result_9);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC9_Group0 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[9].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_9[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9_Group0 test is timeout\n");
        }
        PSPRINTF("\nADC9_Group0 test is not OK\n");
    }
    Adc_StopGroupConversion(9);
    EQADC_DisableInterrupt(4, 1);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(4, 2);
    Adc_StartGroupConversion(10);
    while((Adc_GetGroupStatus(10) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_10[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(10, result_10);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC9_Group1 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[10].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_10[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9_Group1 test is timeout\n");
        }
        PSPRINTF("\nADC9_Group1 test is not OK\n");
    }
    Adc_StopGroupConversion(10);
    EQADC_DisableInterrupt(4, 2);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(4, 3);
    Adc_StartGroupConversion(11);
    while((Adc_GetGroupStatus(11) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_11[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(11, result_11);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC9_Group2 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[11].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_11[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9_Group2 test is timeout\n");
        }
        PSPRINTF("\nADC9_Group2 test is not OK\n");
    }
    Adc_StopGroupConversion(11);
    EQADC_DisableInterrupt(4, 3);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(4, 4);
    Adc_StartGroupConversion(12);
    while((Adc_GetGroupStatus(12) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_12[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(12, result_12);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC9_Group3 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[12].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_12[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9_Group3 test is timeout\n");
        }
        PSPRINTF("\nADC9_Group3 test is not OK\n");
    }
    Adc_StopGroupConversion(12);
    EQADC_DisableInterrupt(4, 4);
    Adc_timeout = ADC_TIMEOUT;

    EQADC_EnableInterrupt(4, 5);
    Adc_StartGroupConversion(13);
    while((Adc_GetGroupStatus(13) != ADC_STREAM_COMPLETED) && (Adc_timeout > 0))
	{
		Adc_timeout--;
	}
	Adc_ValueGroupType result_13[20];
#if (ADC_READ_GROUP_API == STD_ON)
    u8Adc_TempReturn = Adc_ReadGroup(13, result_13);
#endif
    if((u8Adc_TempReturn == E_OK) && (Adc_timeout > 0))
    {
        PSPRINTF("\nADC9_Group4 test is OK\n");
        for(i = 0; i < Config.Adc_GroupConfig[13].ChannelCount; i++)
        {
            PSPRINTF("result buffer[%d] is %d\n", i, result_13[i]);
        }
    }
    else
    {
        if(Adc_timeout == 0)
        {
            PSPRINTF("\nADC9_Group4 test is timeout\n");
        }
        PSPRINTF("\nADC9_Group4 test is not OK\n");
    }
    Adc_StopGroupConversion(13);
    EQADC_DisableInterrupt(4, 5);
#endif

    Adc_DeInit();
    PSPRINTF("\n===============================================DEMO END================================================\n");
}

int adc_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
    }
    else
    {
        if (argc == 2)
        {
            if (!strcmp(agrv[1], "deinit"))
            {
                #if (ADC_DEINIT_API == STD_ON)
                    Adc_DeInit();
                    PSPRINTF("Adc_DeInit end!\n");
                #else
                    PSPRINTF("ADC_DEINIT_API == STD_OFF\n");
                #endif

            }
            else if (!strcmp(agrv[1], "help"))
            {
                PSPRINTF("deinit ---------- CMD ------- Adc_DeInit()\n");
                PSPRINTF("id -------------- CMD ------- ID of the test case:\n");

                for(uint8 i = 0; i < ADC_TEST_CASE_MAX; i++)
                {
                    PSPRINTF("%s\n", adc_funcs[i].name);
                }
            }
            else
            {
                for(uint8 i = 0; i < ADC_TEST_CASE_MAX; i++)
                {
                    if(!strcmp(agrv[1], adc_funcs[i].name))
                    {
                        adc_funcs[i].adcfunc();
                        return 0;
                    }
                }
                PSPRINTF("error: Input invalid parameters[%s], please Use the 'adc_test help' command to see the supported test instructions\n", agrv[1]);
            }
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), adc_test, adc_func, deinit irq or number of test case);
