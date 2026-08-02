#include "tester_fee.h"
#include <string.h>

#define FEE_TEST_CASE_MAX sizeof(fee_funcs) / sizeof(FeefuncMachine)

extern VAR(Fee_JobResult_Type, FEE_VAR) Fee_JobConfig;
extern VAR(uint32, FLS_VAR) gFls_MaxRead;
extern VAR(uint32, FLS_VAR) gFls_MaxWrite;

static FeefuncMachine fee_funcs[] = {
    {"fee_019", test_fee_019},
    {"fee_020", test_fee_020},
    {"fee_021", test_fee_021},
    {"fee_022", test_fee_022},
    {"fee_023", test_fee_023},
    {"fee_024", test_fee_024},
    {"fee_025", test_fee_025},
    {"fee_026", test_fee_026},
    {"fee_027", test_fee_027},
    {"fee_028", test_fee_028},
    {"fee_029", test_fee_029},
    {"fee_030", test_fee_030},
    {"fee_031", test_fee_031},
    {"fee_032", test_fee_032},
    {"fee_033", test_fee_033},
    {"fee_034", test_fee_034},
    {"fee_035", test_fee_035},
    {"fee_036", test_fee_036},
    {"fee_037", test_fee_037},
    {"fee_038", test_fee_038},
    {"fee_039", test_fee_039},
    {"fee_040", test_fee_040},
    {"fee_041", test_fee_041},
    {"fee_042", test_fee_042},
    {"fee_043", test_fee_043},
    {"fee_044", test_fee_044},
    {"fee_045", test_fee_045},
    {"fee_046", test_fee_046},
    {"fee_047", test_fee_047},
    {"fee_048", test_fee_048},
    {"fee_049", test_fee_049},
    {"fee_050", test_fee_050},
    {"fee_051", test_fee_051},
    {"fee_052", test_fee_052},
    {"fee_053", test_fee_053},
    {"fee_054", test_fee_054},
    {"fee_055", test_fee_055},
    {"fee_056", test_fee_056},
    {"fee_057", test_fee_057},
    {"fee_058", test_fee_058},
    {"fee_059", test_fee_059},
    {"fee_060", test_fee_060},
    {"fee_061", test_fee_061},
    {"fee_062", test_fee_062},
    {"fee_063", test_fee_063},
    {"fee_064", test_fee_064},
    {"fee_065", test_fee_065},
    {"fee_066", test_fee_066},
    {"fee_067", test_fee_067},
    {"fee_068", test_fee_068},
    {"fee_069", test_fee_069},
    {"fee_070", test_fee_070},
    {"fee_071", test_fee_071},
    {"fee_072", test_fee_072},
    {"fee_073", test_fee_073},
    {"fee_074", test_fee_074},
    {"fee_075", test_fee_075},
    {"fee_076", test_fee_076},
    {"fee_077", test_fee_077},
    {"fee_078", test_fee_078},
    {"fee_079", test_fee_079},
    {"fee_080", test_fee_080},
    {"fee_081", test_fee_081},
    {"fee_082", test_fee_082},
    {"fee_083", test_fee_083},
    {"fee_084", test_fee_084},
    {"fee_085", test_fee_085},
    {"fee_086", test_fee_086},
    {"demo_service", Fee_Project_Service},
    {"fee_0116", test_fee_0116},
    {"fee_0117", test_fee_0117},
    {"fee_0118", test_fee_0118},
};

void test_fee_019()
{
    PSPRINTF("[%s]",__func__);
    MemIf_JobResultType result = MEMIF_JOB_OK;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    result = Fee_GetStatus();


    PSPRINTF("Fee_GetStatus() = %d\n", result);
}

void test_fee_020()
{
    PSPRINTF("[%s]\n",__func__);

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_SetMode(MEMIF_MODE_SLOW);
    PSPRINTF("Mode set success:%d\n",MEMIF_MODE_SLOW);
}

void test_fee_021()
{
    PSPRINTF("[%s]\n",__func__);

    Fee_SetMode(MEMIF_MODE_SLOW);
}


void test_fee_022()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    uint8 array[5] = {1, 2, 3, 4, 5};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1, array);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    Fee_SetMode(MEMIF_MODE_SLOW);
}

void test_fee_023()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;
    MemIf_StatusType state_type = 0;
    MemIf_JobResultType result;
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Read(1,0,b,32);
    state_type = Fee_GetStatus();
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
    PSPRINTF("Fee_Read() = %d\n", ret);
}

void test_fee_024()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;
    MemIf_StatusType state_type = 0;
    uint8 b[32] = {0};

    ret = Fee_Read(1,0,b,32);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    PSPRINTF("Fee_Read() = %d\n", ret);
}

void test_fee_025()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;
    MemIf_StatusType state_type = 0;
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    state_type = Fee_GetStatus();

    if(state_type == MEMIF_BUSY) {
        ret = Fee_Read(1,0,b,32);
        PSPRINTF("Fee_GetStatus() = %d\n", state_type);
        PSPRINTF("Fee_Read() = %d\n", ret);
    }
}

void test_fee_026()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Read(1000,0,b,32);
    PSPRINTF("Fee_Read() = %d\n", ret);
}

void test_fee_027()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Read(1,10000,b,32);
    PSPRINTF("Fee_Read() = %d\n", ret);
}

void test_fee_028()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Read(1,0,NULL,32);
    PSPRINTF("Fee_Read() = %d\n", ret);
}

void test_fee_029()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret;
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Read(1,0,b,6666);
    PSPRINTF("Fee_Read() = %d\n", ret);
}

void test_fee_030()
{
    Std_ReturnType ret;
    static uint8 buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Write(1,buff);
    PSPRINTF("Fee_Write() = %d\n", ret);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
       Fls_MainFunction();
       Fee_MainFunction();
    }
     
    ret = Fee_Read(1, 0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }

    PSPRINTF("\nFee_Write() = %d\n", ret);
}

void test_fee_031()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    MemIf_JobResultType result;
    Std_ReturnType ret;
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                           0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                           0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                           0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Read(1,0,b,32);
    ret = Fee_Write(1, buff);
    state_type = Fee_GetStatus();
    result = Fee_GetJobResult();

    PSPRINTF("Fee_Write() = %d\n", ret);
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_032()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    MemIf_JobResultType result;
    Std_ReturnType ret;
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                           0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                           0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                           0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    ret = Fee_Write(1, buff);
    state_type = Fee_GetStatus();
    result = Fee_GetJobResult();

    PSPRINTF("Fee_Write() = %d\n", ret);
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_033()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    MemIf_JobResultType result;
    Std_ReturnType ret;
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                           0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                           0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                           0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Write(1000, buff);
    state_type = Fee_GetStatus();
    result = Fee_GetJobResult();

    PSPRINTF("Fee_Write() = %d\n", ret);
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_034()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_JobResultType result;
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_Write(1, NULL);
    result = Fee_GetJobResult();

    PSPRINTF("Fee_Write() = %d\n", ret);
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_035()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    MemIf_JobResultType result;
    uint8 a[5] = {0};

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1, a);
    Fee_Cancel();
    Fee_MainFunction();
    state_type = Fee_GetStatus();
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_036()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;

    Fee_Cancel();
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_037()
{
    PSPRINTF("[%s]\n",__func__);

    Fee_Init(&Fee_Config);
    Fee_Cancel();
}

void test_fee_038()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_JobResultType result = MEMIF_JOB_OK;

    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_039()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;

    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_040()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_041()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    uint8 a[5] = {0};

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1, a);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_042()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    Fee_MainFunction();
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_043()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    Std_ReturnType ret = E_NOT_OK;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_InvalidateBlock(1);
    PSPRINTF("Fee_InvalidateBlock() = %d\n", ret);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_044()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    Std_ReturnType ret = E_NOT_OK;

    ret = Fee_InvalidateBlock(1);
    PSPRINTF("Fee_InvalidateBlock() = %d\n", ret);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_045()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    Std_ReturnType ret = E_NOT_OK;
    uint8 a[5] = {0};

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1, a);
    ret = Fee_InvalidateBlock(1);
    PSPRINTF("Fee_InvalidateBlock() = %d\n", ret);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_046()
{
    PSPRINTF("[%s]\n",__func__);
    MemIf_StatusType state_type = 0;
    Std_ReturnType ret = E_NOT_OK;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_InvalidateBlock(1000);
    PSPRINTF("Fee_InvalidateBlock() = %d\n", ret);
    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_047()
{
    PSPRINTF("[%s]\n",__func__);
    Std_VersionInfoType version_info;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_GetVersionInfo(&version_info);

    PSPRINTF("vendorID:%d\n",version_info.vendorID);
    PSPRINTF("moduleID:%d\n",version_info.moduleID);
    PSPRINTF("sw_major_version:%d\n",version_info.sw_major_version);
    PSPRINTF("sw_minor_version:%d\n",version_info.sw_minor_version);
    PSPRINTF("sw_patch_version:%d\n",version_info.sw_patch_version);
}

void test_fee_048()
{
    PSPRINTF("[%s]\n",__func__);

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_GetVersionInfo(NULL);
}

void test_fee_049()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret = E_NOT_OK;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_EraseImmediateBlock(1);
    PSPRINTF("ret:%d\n",ret);
}

void test_fee_050()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret = E_NOT_OK;
    MemIf_StatusType state_type = 0;

    ret = Fee_EraseImmediateBlock(1);
    PSPRINTF("ret:%d\n",ret);

    state_type = Fee_GetStatus();
    PSPRINTF("Fee_GetStatus() = %d\n", state_type);
}

void test_fee_051()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret = E_NOT_OK;
    uint8 a[5] = {0};

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1, a);
    ret = Fee_EraseImmediateBlock(1);
    PSPRINTF("ret:%d\n",ret);
}

void test_fee_052()
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType ret = E_NOT_OK;

    Fee_Init(&Fee_Config);
    Fls_Init(&Fls_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_EraseImmediateBlock(1000);
    PSPRINTF("ret:%d\n",ret);
}

void test_fee_053()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
}

void test_fee_054()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
}

void test_fee_055()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 c[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
    Fee_Read(1,0,c,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("c:%x ",c[i]);
    }
}

void test_fee_056()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
}

void test_fee_057()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
}

void test_fee_058()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 c[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
    Fee_Read(1,0,c,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("c:%x ",c[i]);
    }
}

void test_fee_059()
{
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);
}

void test_fee_060()
{
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);
}

void test_fee_061()
{
    MemIf_JobResultType result;

    result = Fee_GetJobResult();

    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_062()
{
    MemIf_JobResultType result;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_JobConfig.Fee_JobResult = MEMIF_BLOCK_INCONSISTENT;
    result = Fee_GetJobResult();

    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_063()
{
    MemIf_JobResultType result;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Cancel();

    result = Fee_GetJobResult();

    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_064()
{
    MemIf_JobResultType result;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_InvalidateBlock(1);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_065()
{
    MemIf_JobResultType result;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_EraseImmediateBlock(1);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_066()
{
    MemIf_JobResultType result;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_SetMode(MEMIF_MODE_SLOW);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_067()
{
    MemIf_JobResultType result;
    uint8 b[32] = {0};
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_068()
{
    MemIf_JobResultType result;
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(1,buff);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_069()
{
    MemIf_JobResultType result;
    uint8 b[32] = {0};


    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    
    result = Fee_GetJobResult();
    PSPRINTF("Fee_GetJobResult() = %d\n", result);
}

void test_fee_070()
{
    uint8 b[32] = {0};
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                          0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                          0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                          0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    Fee_Write(1,buff);
}

void test_fee_071()
{
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(1,0,b,32);
    Fee_SetMode(MEMIF_MODE_SLOW);
}

void test_fee_072()
{
    uint8 b[32] = {0};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_InvalidateBlock(1);
    Fee_Read(1,0,b,32);
}

void test_fee_073()
{
    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_EraseImmediateBlock(1);
    Fee_InvalidateBlock(1);
}

void test_fee_074()
{
    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_InvalidateBlock(1);
    Fee_EraseImmediateBlock(1);
}

void test_fee_075()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
}

void test_fee_076()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
}

void test_fee_077()
{
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);
}

void test_fee_078()
{
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    ret = Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);
}

void test_fee_079()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(2,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
}

void test_fee_080()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(2,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
}

void test_fee_081()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 c[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Read(2,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
    Fee_Read(2,0,c,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("c:%x ",c[i]);
    }
}

void test_fee_082()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 c[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Read(2,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
    Fee_Read(2,0,c,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("c:%x ",c[i]);
    }
}

void test_fee_083()
{
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    ret = Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);

    ret = Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);
}

void test_fee_084()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 c[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
    Fee_Read(2,0,c,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("c:%x ",c[i]);
    }
}

void test_fee_085()
{
    VAR (uint8, AUTOMATIC) buff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 b[32] = {0};
    uint8 c[32] = {0};
    uint8 i = 0;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(1,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Write(2,buff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    Fee_Read(1,0,b,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    for(i = 0;i < 32; i++) {
        PSPRINTF("b:%x ",b[i]);
    }
    Fee_Read(2,0,c,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    for(i = 0;i < 32; i++) {
        PSPRINTF("c:%x ",c[i]);
    }
}

void test_fee_086()
{
    Std_ReturnType ret;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    ret = Fee_EraseImmediateBlock(1);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);

    ret = Fee_EraseImmediateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    PSPRINTF("Erase ret :%d\n",ret);
}

void Fee_Project_Service(void)
{
    PSPRINTF("\n==============================Fee DEMO TEST===============================\n");

    uint8 WriteBuff[32]={0x33,0x33,0x33,0x33,0x33,0x33,0x55,0xAA,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x23,
                                       0x55,0xAA,0x55,0xAA,0x55,0xAA,0x11,0xAA};
    uint8 ReadBuffer[32] = {0};
    uint8 i = 0;
    uint8 BlockId = 1;

    Fls_Init(&Fls_Config);
    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_EraseImmediateBlock(BlockId);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(BlockId,WriteBuff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(BlockId,0,ReadBuffer,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    PSPRINTF("\nReadBuffer:");
    for(i = 0;i < 32; i++) {
        PSPRINTF("%x ",ReadBuffer[i]);
    }
    PSPRINTF("\n");
    PSPRINTF("\n============================Block:%d Operation end============================\n",BlockId); 
    BlockId = 2; //对块号2进行擦读写操作

    Fee_EraseImmediateBlock(BlockId);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Write(BlockId,WriteBuff);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_Read(BlockId,0,ReadBuffer,32);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    PSPRINTF("\nReadBuffer:");
    for(i = 0;i < 32; i++) {
        PSPRINTF("%x ",ReadBuffer[i]);
    }
    PSPRINTF("\n");
    PSPRINTF("\n============================Block:%d Operation end============================\n",BlockId); 
    PSPRINTF("\n");
    PSPRINTF("\n==============================Fee DEMO END=================================\n");
}

void test_fee_0116()
{
    Fee_Init(NULL);
}

void test_fee_0117()
{
    VAR(uint32, FLS_VAR) gFls_MaxWrite_flag = 0U;
    VAR(uint32, FLS_VAR) gFls_MaxRead_flag  = 0U;

    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
    gFls_MaxWrite_flag = gFls_MaxWrite;
    gFls_MaxRead_flag  = gFls_MaxRead;

    Fee_SetMode(3);

    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    if(gFls_MaxWrite_flag == gFls_MaxWrite &&
    gFls_MaxRead_flag == gFls_MaxRead)
    {
        PSPRINTF("test_fee_0117 is ok\n");
    }
    else
    {
        PSPRINTF("test_fee_0117 is fail\n");
    }
}

void test_fee_0118()
{
    Fee_Init(&Fee_Config);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }

    Fee_InvalidateBlock(2);
    while(Fee_GetStatus() != MEMIF_IDLE ||
    Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
    }
}

int tsc_fee_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
    }

   if (argc == 2)
   {
        if (!strcmp(agrv[1], "help"))
        {
            PSPRINTF("irq ---------- CMD ------- Register/enable FEE interrupt numbers\n \
                      stop --------- CMD ------- Migrate the module status to stop\n");
                    
            PSPRINTF("ID of the test case:\n");
            for(uint8 i = 0; i < FEE_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", fee_funcs[i].name);
            }
        }
        else
        {
            for(uint8 i = 0; i < FEE_TEST_CASE_MAX; i++)
            {
                if(!strcmp(agrv[1], fee_funcs[i].name))
                {
                    Fls_Init(&Fls_Config);
                    fee_funcs[i].func();
                    return 0;
                }
            }
            PSPRINTF("error: Input invalid parameters[%s], please Use the 'fee_test help' command to see the supported test instructions\n", agrv[1]);
        }
   }

   return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), fee_test , tsc_fee_func, deint or number of test case);
