#include "tester_fls.h"
#include "Gpt_Stm_LLDriver.h"
#include "shell.h"
#include <string.h>

#define FLS_TEST_CASE_MAX sizeof(fls_funcs) / sizeof(FlsfuncMachine)
 
extern VAR(MemIf_StatusType, FLS_VAR) gFls_ModuleStatus;
extern P2CONST(Fls_ConfigType, FLS_VAR, FLS_APPL_CONST) gFls_ConfigPtr;
extern VAR(uint32, FLS_VAR) gFls_MaxRead;
extern VAR(uint32, FLS_VAR) gFls_MaxWrite;


const static FlsfuncMachine fls_funcs[] = {
    {"fls_0059",test_fls_0059},
    {"fls_0060",test_fls_0060},
    {"fls_0061",test_fls_0061},
    {"fls_0062",test_fls_0062},
    {"fls_0063",test_fls_0063},
    {"fls_0064",test_fls_0064},
    {"fls_0065",test_fls_0065},
    {"fls_0066",test_fls_0066},
    {"fls_0067",test_fls_0067},
    {"fls_0068",test_fls_0068},
    {"fls_0069",test_fls_0069},
    {"fls_0070",test_fls_0070},
    {"fls_0071",test_fls_0071},
    {"fls_0072",test_fls_0072},
    {"fls_0073",test_fls_0073},
    {"fls_0074",test_fls_0074},
    {"fls_0075",test_fls_0075},
    {"fls_0076",test_fls_0076},
    {"fls_0077",test_fls_0077},
    {"fls_0078",test_fls_0078},
    {"fls_0079",test_fls_0079},
    {"fls_0080",test_fls_0080},
    {"fls_0081",test_fls_0081},
    {"fls_0082",test_fls_0082},
    {"fls_0083",test_fls_0083},
    {"fls_0084",test_fls_0084},
    {"fls_0085",test_fls_0085},
    {"fls_0086",test_fls_0086},
    {"fls_0087",test_fls_0087},
    {"fls_0088",test_fls_0088},
    {"fls_0089",test_fls_0089},
    {"fls_0090",test_fls_0090},
    {"fls_0091",test_fls_0091},
    {"fls_0092",test_fls_0092},
    {"fls_0093",test_fls_0093},
    {"fls_0094",test_fls_0094},
    {"fls_0095",test_fls_0095},
    {"fls_0096",test_fls_0096},
    {"fls_0097",test_fls_0097},
    {"fls_0098",test_fls_0098},
    {"fls_0099",test_fls_0099},
    {"fls_0100",test_fls_0100},
    {"fls_0101",test_fls_0101},
    {"fls_0102",test_fls_0102},
    {"fls_0103",test_fls_0103},
    {"fls_0104",test_fls_0104},
    {"fls_0105",test_fls_0105},
    {"fls_0106",test_fls_0106},
    {"fls_0107",test_fls_0107},
    {"fls_0108",test_fls_0108},
    {"fls_0109",test_fls_0109},
    {"fls_0110",test_fls_0110},
    {"fls_0111",test_fls_0111},
    {"fls_0112",test_fls_0112},
    {"fls_0113",test_fls_0113},
    {"fls_0114",test_fls_0114},
    {"fls_0115",test_fls_0115},
    {"fls_0116",test_fls_0116},
    {"fls_0117",test_fls_0117},
    {"fls_0118",test_fls_0118},
    {"fls_0119",test_fls_0119},
    {"fls_0120",test_fls_0120},
    {"fls_0121",test_fls_0121},
    {"fls_0122",test_fls_0122},
    {"fls_0123",test_fls_0123},
    {"fls_0124",test_fls_0124},
    {"fls_0125",test_fls_0125},
    {"fls_0126",test_fls_0126},
    {"fls_0127",test_fls_0127},
    {"fls_0128",test_fls_0128},
    {"fls_0129",test_fls_0129},
    {"fls_0130",test_fls_0130},
    {"fls_0131",test_fls_0131},
    {"fls_0132",test_fls_0132},
    {"fls_0133",test_fls_0133},
    {"fls_0134",test_fls_0134},
    {"fls_0135",test_fls_0135},
    {"fls_0136",test_fls_0136},
    {"fls_0137",test_fls_0137},
    {"fls_0138",test_fls_0138},
    {"fls_0139",test_fls_0139},
    {"fls_0140",test_fls_0140},
    {"fls_0141",test_fls_0141},
    {"fls_0142",test_fls_0142},
    {"fls_0143",test_fls_0143},
    {"fls_0144",test_fls_0144},
    {"fls_0145",test_fls_0145},
    {"fls_0146",test_fls_0146},
    {"fls_0147",test_fls_0147},
    {"fls_0148",test_fls_0148},
    {"fls_0149",test_fls_0149},
    {"fls_0150",test_fls_0150},
    {"fls_0151",test_fls_0151},
    {"fls_0152",test_fls_0152},
    {"fls_0153",test_fls_0153},
    {"fls_0154",test_fls_0154},
    {"fls_0155",test_fls_0155},
    {"fls_0156",test_fls_0156},
    {"fls_0157",test_fls_0157},
    {"fls_0158",test_fls_0158},
    {"fls_0159",test_fls_0159},
    {"fls_0160",test_fls_0160},
    {"fls_0161",test_fls_0161},
    {"fls_0162",test_fls_0162},
    {"fls_0163",test_fls_0163},
    {"fls_0170",test_fls_0170},
    {"fls_0171",test_fls_0171},
};

uint32 Fls_Get_PhyStartAddress()
{
    VAR( uint32, AUTOMATIC) u32Fls_PhyStartAddr = 0U; 
    VAR( uint32, AUTOMATIC) u32Fls_PhyIndex = 0U;

    u32Fls_PhyIndex = (*(gFls_ConfigPtr->pSectorList))[gFls_JobSectorIt];
    u32Fls_PhyStartAddr = flashInfo[u32Fls_PhyIndex].addrStart;

    return u32Fls_PhyStartAddr;
}

void test_fls_0059(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    Fls_Init(NULL_PTR);
}

void test_fls_0060(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    MemIf_JobResultType type = MEMIF_BLOCK_INVALID;

    Fls_Init(Fls_Config);
    
    type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);
}

void test_fls_0061(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    gFls_ModuleStatus = MEMIF_BUSY;

    Fls_Init(Fls_Config);
}

void test_fls_0062(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    MemIf_JobResultType type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_BUSY;

    Fls_Init(Fls_Config);
    type = Fls_GetJobResult();
    state_type = Fls_GetStatus();
    PSPRINTF("type:%d\n",type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0063(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("type:%d\n",type);
}

void test_fls_0064(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x10000);
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0065(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x10000);
    job_type = Fls_GetJobResult();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
}

void test_fls_0066(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(999999999,0x10000);
    PSPRINTF("type:%d\n",type);/*E_NOT_OK*/
}

void test_fls_0067(const Fls_ConfigType *Fls_Config)
{   
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x10001);
    PSPRINTF("type:%d\n",type);/*E_NOT_OK*/
}

void test_fls_0068(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    type = Fls_Erase(0x38000,0x10000);
    PSPRINTF("type:%d\n",type);
}

void test_fls_0069(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
    uint8 data[5] = {1,2,3,4,5};

    Fls_Init(Fls_Config);
    type = Fls_Write(0x38000,data,0x10000);
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0070(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {1,2,3,4,5};

    Fls_Init(Fls_Config);
    type = Fls_Write(999999999,data,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0071(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {1,2,3,4,5};

    Fls_Init(Fls_Config);
    type = Fls_Write(0x38000,data,0x10001);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0072(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {1,2,3,4,5};

    //Fls_Init(Fls_Config);
    type = Fls_Write(0x38000,data,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0073(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {1,2,3,4,5};

    Fls_Init(Fls_Config);
    Fls_Erase(0x38000,0x10000);

    type = Fls_Write(0,data,0x10000);
    PSPRINTF("type:%d\n",type);

}

void test_fls_0074(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    type = Fls_Write(0x38000,NULL_PTR,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0075(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
    uint8 data[5] = {1,2,3,4,5};

    Fls_Init(Fls_Config);
    type = Fls_Write(0x38000,data,0x10000);
    Fls_Cancel();
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0076(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Fls_Cancel();
}

void test_fls_0077(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    MemIf_StatusType state_type = MEMIF_IDLE;

    Fls_Init(Fls_Config);
    state_type = Fls_GetStatus();

    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0078(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    MemIf_StatusType state_type = MEMIF_IDLE;

    state_type = Fls_GetStatus();

    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0079(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[5] = {1,2,3,4,5};

    Fls_Init(Fls_Config);
    Fls_Write(0x38000,data,0x10000);
    job_type = Fls_GetJobResult();

    PSPRINTF("job_type:%d\n",job_type);
}

void test_fls_0080(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    job_type = Fls_GetJobResult();

    PSPRINTF("job_type:%d\n",job_type);
}

void test_fls_0081(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
    uint8 data[5] = {0};
    
    Fls_Init(Fls_Config);
    type = Fls_Read(0x38000,data,0x10000);
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0082(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    type = Fls_Read(999999999,data,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0083(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    type = Fls_Read(0x38000,data,0x1000000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0084(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    Fls_Erase(0,0x10000);
    type = Fls_Read(0x38000,data,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0085(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    type = Fls_Read(0x38000,NULL_PTR,0x101);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0086(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    //Fls_Init(Fls_Config);
    type = Fls_Read(999999999,data,0x101);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0087(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    type = Fls_Compare(0x38000,data,0x10000);
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0088(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    type = Fls_Compare(999999999,data,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0089(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    type = Fls_Compare(0x38000,data,0x1000000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0090(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    type = Fls_Compare(0x38000,NULL_PTR,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0091(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    Fls_Init(Fls_Config);
    Fls_Erase(0,0x10000);
    type = Fls_Compare(0x38000,data,0x10000);

    PSPRINTF("type:%d\n",type);
}

void test_fls_0092(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    uint8 data[5] = {0};

    //Fls_Init(Fls_Config);
    type = Fls_Compare(999999999,data,0x101);
    
    PSPRINTF("type:%d\n",type);
}

void test_fls_0093(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    MemIf_ModeType mode_type = MEMIF_MODE_FAST;

    Fls_Init(Fls_Config);
    Fls_SetMode(mode_type);
}

void test_fls_0094(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    MemIf_ModeType mode_type = MEMIF_MODE_FAST;
    Fls_Init(Fls_Config);
    Fls_Erase(0x38000,0x10000);
    Fls_SetMode(mode_type);
}

void test_fls_0095(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_VersionInfoType version_info;
#if( FLS_VERSION_INFO_API == STD_ON)
    Fls_Init(Fls_Config);
    Fls_GetVersionInfo(&version_info);
    PSPRINTF("vendorID:%d\n",version_info.vendorID);
    PSPRINTF("moduleID:%d\n",version_info.moduleID);
    PSPRINTF("sw_major_version:%d\n",version_info.sw_major_version);
    PSPRINTF("sw_minor_version:%d\n",version_info.sw_minor_version);
    PSPRINTF("sw_patch_version:%d\n",version_info.sw_patch_version);
#endif
}

void test_fls_0096(const Fls_ConfigType *Fls_Config)
{
#if( FLS_VERSION_INFO_API == STD_ON)
    PSPRINTF("[%s]",__func__);
    Fls_Init(Fls_Config);
    Fls_GetVersionInfo(NULL_PTR);
#endif
}

void test_fls_0097(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_Init(Fls_Config);
    type = Fls_BlankCheck(0x38000,0x10000);
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
#endif
}

void test_fls_0098(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_Init(Fls_Config);
    type = Fls_BlankCheck(999999999,0x10000);

    PSPRINTF("type:%d\n",type);
#endif
}

void test_fls_0099(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_Init(Fls_Config);
    type = Fls_BlankCheck(0x38000,0x1000000);

    PSPRINTF("type:%d\n",type);
#endif
}

void test_fls_0100(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;

    Fls_Init(Fls_Config);
    Fls_Erase(0,0x10000);
#if (FLS_BLANK_CHECK_API == STD_ON)
    type = Fls_BlankCheck(0x38000,0x10000);
    PSPRINTF("type:%d\n",type);
#endif
}

void test_fls_0101(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
#if (FLS_BLANK_CHECK_API == STD_ON)
    type = Fls_BlankCheck(0x38000,0x10000);

    PSPRINTF("type:%d\n",type);
#endif
}

void test_fls_0102(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x10000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,0x10000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0103(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,0x10000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0104(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x98000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x98000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0105(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x3b8000,262144);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x3b8000,262144);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0106(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x3f8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x3f8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0107(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x438000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x438000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0108(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Erase(0x48000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    Gpt_Stm_LLD_DelayMs(STM1, 100U);
    Fls_MainFunction();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Erase(0x98000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    Fls_MainFunction();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x98000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0109(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x10000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,0x10000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,data,16);
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x38000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0110(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,0x10000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,0x10000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x48000,data,16);
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x48000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0111(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x98000,0x10000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x98000,0x10000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x98000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x98000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0112(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x3b8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x3b8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x3b8000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x3b8000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0113(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x3f8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x3f8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x3f8000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x3f8000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0114(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x438000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x438000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x438000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x438000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0115(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x38000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Erase(0x48000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x48000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x48000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0116(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {0};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x38000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x38000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0117(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {0};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x48000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x48000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x48000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0118(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {0};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x98000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x98000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x98000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x98000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x98000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0119(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {0};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x3b8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x3b8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x3b8000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x3b8000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x3b8000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0120(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {0};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x3f8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x3f8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x3f8000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x3f8000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x3f8000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0121(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {0};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x438000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x438000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x438000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x438000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x438000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0122(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 data1[16] = {3,3,3,3,3,3,3,3,7,7,7,7,7,7,7,7};
#if (Fls_Compare_API == STD_ON)
    uint8 data2[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 data3[16] = {3,3,3,3,3,3,3,3,7,7,7,7,7,7,7,7};
#endif
    uint8 array1[16] = {0};
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,data,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x38000,data2,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Erase(0x48000,65536);
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x48000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x48000,data3,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    PSPRINTF("---After MainFunction Compare---\n");
    Fls_Cancel();
    type = Fls_Read(0x38000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Fls_Cancel();
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data:%d\n",array1[i]);
    }

    type = Fls_Read(0x48000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Fls_Cancel();
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0123(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0xb8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0xb8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0xb8000,data,16);
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0xb8000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0124(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x138000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x138000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x138000,data,16);
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x138000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0125(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0xb8000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0xb8000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0126(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x138000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x138000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0127(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    type = Fls_BlankCheck(0x38000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0128(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0129(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x47FF0,data,16);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x47FF0,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0130(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x57FF0,data,16);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x57FF0,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
}

void test_fls_0131(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 array1[16] = {0};
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x47FF0,array,16);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    PSPRINTF("---After MainFunction Write---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x47FF0,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x47FF0,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0132(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 array1[16] = {0};
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x57FF0,array,16);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(0x57FF0,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x57FF0,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0133(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x47FF0,array,16);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
    Fls_Cancel();
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x47FF0,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0134(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    MemIf_StatusType state_type = MEMIF_IDLE;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x48000,0x20000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x48000,0x20000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x57FF0,array,16);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
    Fls_Cancel();
    type = Fls_Compare(0x57FF0,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    state_type = Fls_GetStatus();

    PSPRINTF("type:%d\n",type);
    PSPRINTF("job_type:%d\n",job_type);
    PSPRINTF("state_type:%d\n",state_type);
}

void test_fls_0135(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
	test_fls_0109(Fls_Config);
}

void test_fls_0136(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
	test_fls_0102(Fls_Config);
}

void test_fls_0137(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
	test_fls_0102(Fls_Config);
}

void test_fls_0138(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
	test_fls_0105(Fls_Config);
}

void test_fls_0139(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    static uint8 array[2048] = {0};
    static uint8 array1[2048] = {0};
    
    uint16 i = 0;
    uint16 j = 0;

    for(i = 0;i < 2048; i++)
    {
        array[i] = 0x11;
    }

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("type:%d\n",type);/*E_OK*/
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,2048);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x38000,array,2048);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Read(0x38000,array1,2048);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }

    for(j = 0;j < 2048; j++)
    {
        if(array1[j] != 0x11)
        {
            break;
        }
    }

    if(j == 2048) {
        PSPRINTF("test_fls_0139 is OK\n");
    }
    else {
        PSPRINTF("test_fls_0139 is NG:%d\n",j);
    }
}

void test_fls_0140(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    static uint8 array[4096] = {0};
    static uint8 array1[4096] = {0};
    
    uint16 i = 0;
    uint16 j = 0;

    for(i = 0;i < 4096; i++)
    {
        array[i] = 0x11;
    }

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("type:%d\n",type);/*E_OK*/
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,4096);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x38000,array,4096);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Read(0x38000,array1,4096);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }

    for(j = 0;j < 4096; j++)
    {
        if(array1[j] != 0x11)
        {
            break;
        }
    }

    if(j == 4096) {
        PSPRINTF("test_fls_0140 is OK\n");
    }
    else {
        PSPRINTF("test_fls_0140 is NG:%d\n",j);
    }
}

void test_fls_0141(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    static uint8 array[4096] = {0};
    static uint8 array1[4096] = {0};
    
    uint16 i = 0;
    uint16 j = 0;

    for(i = 0;i < 4096; i++)
    {
        array[i] = 0x11;
    }

    Fls_Init(Fls_Config);
#if (FLS_SET_MODE_API == STD_ON)
    Fls_SetMode(MEMIF_MODE_FAST);
#endif
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("type:%d\n",type);/*E_OK*/
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,4096);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x38000,array,4096);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Read(0x38000,array1,4096);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }

    for(j = 0;j < 4096; j++)
    {
        if(array1[j] != 0x11)
        {
            break;
        }
    }

    if(j == 4096) {
        PSPRINTF("test_fls_0139 is OK\n");
    }
    else {
        PSPRINTF("test_fls_0139 is NG:%d\n",j);
    }
}

void test_fls_0142(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 array1[16] = {0};

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,16);
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x38000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x38000,array1,16);
    Fls_MainFunction();
    PSPRINTF("---After MainFunction Read---\n");
    Fls_Cancel();
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
}

void test_fls_0143(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,16);
    PSPRINTF("---After MainFunction Write---\n");
    Fls_Cancel();
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
}

void test_fls_0144(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 array1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,16);
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
    Fls_Cancel();
    type = Fls_Compare(0x38000,array1,16);
    PSPRINTF("---After MainFunction Compare---\n");
    Fls_Cancel();
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
}

void test_fls_0145(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 array1[16] = {0};
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x478000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x478000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x478000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x478000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x478000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0146(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 array1[16] = {0};
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x878000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x878000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x878000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x878000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0x878000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0147(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#if (Fls_Compare_API == STD_ON)
    uint8 data1[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
#endif
    uint8 array1[165] = {0};
    uint8 i = 0;

    Fls_Init(Fls_Config);
    type = Fls_Erase(0xc78000,0x40000);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    job_type = Fls_GetJobResult();
    PSPRINTF("type:%d\n",type);/*E_OK*/
    PSPRINTF("job_type:%d\n",job_type);
    Fls_MainFunction();
    Gpt_Stm_LLD_DelayMs(STM1, 5U);
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0xc78000,0x40000);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0xc78000,array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0xc78000,data1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Cancel();
    type = Fls_Read(0xc78000,array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Read---\n");
    for(i = 0;i < 16;i++)
    {
        PSPRINTF("data1:%d\n",array1[i]);
    }
}

void test_fls_0148(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("\n==============================Fls DEMO TEST===============================\n");
    Std_ReturnType type = E_NOT_OK;
    uint8 WriteBuffer[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    uint8 ReadBuffer[16] = {0};
    uint8 i = 0;
    uint32 FlsStartAddr = 0x38000;

    Fls_Init(Fls_Config);
    for(int j = 0; j < 8; j++)
    {
        type = Fls_Erase(FlsStartAddr,65536);
        Fls_MainFunction();
        type = Fls_Write(FlsStartAddr,WriteBuffer,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        Fls_Cancel();
        type = Fls_Read(FlsStartAddr,ReadBuffer,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        PSPRINTF("\nReadBuffer:");
        for(i = 0;i < 16;i++)
        {
            PSPRINTF("%d ",ReadBuffer[i]);
        }
        PSPRINTF("---Block %d Test Finish---\n",j);
        FlsStartAddr += 0x10000;
        PSPRINTF("type:%d\n",type);/*E_OK*/
    }
    PSPRINTF("\n==============================Fls DEMO END=================================\n");
}

void test_fls_0149(const Fls_ConfigType *Fls_Config) /*CCFC3008PT async*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    uint32 FlsStartAddr = 0x4000;
    uint32 Lenth = 0x4000;
    uint8 i = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0150(const Fls_ConfigType *Fls_Config) /*CCFC3008PT sync*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    uint32 FlsStartAddr = 0x4000;
    uint32 Lenth = 0x4000;
    uint8 i = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0151(const Fls_ConfigType *Fls_Config) /*CCFC3008PT async*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[256] = {0};
    static uint8 array1[256] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        for(count = 0;count < Lenth; count++)
        {
            array[i] = 0x11;
        }
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (Lenth/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }

        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x40000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0152(const Fls_ConfigType *Fls_Config) /*CCFC3008PT sync*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[256] = {0};
    static uint8 array1[256] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        for(count = 0;count < Lenth; count++)
        {
            array[i] = 0x11;
        }
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (Lenth/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }

        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x40000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0153(const Fls_ConfigType *Fls_Config) /*CCFC3008PT async*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    static uint8 array1[16] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }

    FlsStartAddr = 0x7FF8;
    Lenth = 0x4000;
    for(i = 0;i < 2; i++)
    {
        Fls_Write(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr+(Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x4000;
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x18000;
    Fls_Write(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Read(FlsStartAddr + (0x10000 - 8),array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x38000;

    for(i = 0;i < 6; i++)
    {

        Fls_Write(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }

        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x40000;
    #endif
    }
    
    FlsStartAddr = 0x3b8000;
    for(i = 0;i < 2; i++)
    {

        Fls_Write(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (0x40000 - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0154(const Fls_ConfigType *Fls_Config) /*CCFC3008PT sync*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    static uint8 array1[16] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }

    FlsStartAddr = 0x7FF8;
    Lenth = 0x4000;
    for(i = 0;i < 2; i++)
    {
        Fls_Write(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr+(Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x4000;
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x18000;
    Fls_Write(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Read(FlsStartAddr + (0x10000 - 8),array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x38000;

    for(i = 0;i < 6; i++)
    {

        Fls_Write(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }

        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x40000;
    #endif
    }
    
    FlsStartAddr = 0x3b8000;
    for(i = 0;i < 2; i++)
    {

        Fls_Write(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (0x40000 - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0155(const Fls_ConfigType *Fls_Config) /*CCFC3007PT async*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    uint32 FlsStartAddr = 0x4000;
    uint32 Lenth = 0x4000;
    uint8 i = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 35; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0156(const Fls_ConfigType *Fls_Config) /*CCFC3007PT sync*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    uint32 FlsStartAddr = 0x4000;
    uint32 Lenth = 0x4000;
    uint8 i = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 35; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0157(const Fls_ConfigType *Fls_Config) /*CCFC3007PT async*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[256] = {0};
    static uint8 array1[256] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        for(count = 0;count < Lenth; count++)
        {
            array[i] = 0x11;
        }
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (Lenth/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }

        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 35; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x40000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0158(const Fls_ConfigType *Fls_Config) /*CCFC3007PT sync*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[256] = {0};
    static uint8 array1[256] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        for(count = 0;count < Lenth; count++)
        {
            array[i] = 0x11;
        }
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (Lenth/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }

        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,65536);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x10000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 35; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        WriteAddr= FlsStartAddr;
        for(count = 0;count < (0x40000/256); count++)
        {
            Fls_Write(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            
        #if (Fls_Compare_API == STD_ON)
            Fls_Compare(WriteAddr,array,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
        #endif
            Fls_Read(WriteAddr,array1,256);
            while(Fls_GetStatus() != MEMIF_IDLE)
            {
                Fls_MainFunction();
            }
            WriteAddr += 256;
        }
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0159(const Fls_ConfigType *Fls_Config) /*CCFC3007PT async*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    static uint8 array1[16] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }

    FlsStartAddr = 0x7FF8;
    Lenth = 0x4000;
    for(i = 0;i < 2; i++)
    {
        Fls_Write(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr+(Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x4000;
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x18000;
    Fls_Write(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Read(FlsStartAddr + (0x10000 - 8),array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x38000;

    for(i = 0;i < 6; i++)
    {

        Fls_Write(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }

        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 35; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x40000;
    #endif
    }
    
    FlsStartAddr = 0x3b8000;
    for(i = 0;i < 33; i++)
    {
        Fls_Write(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (0x40000 - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0160(const Fls_ConfigType *Fls_Config) /*CCFC3007PT sync*/
{
    PSPRINTF("[%s]\n",__func__);
    Std_ReturnType type = E_NOT_OK;
    static uint8 array[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
    static uint8 array1[16] = {0};
    uint32 FlsStartAddr = 0x4000;
    Fls_AddressType WriteAddr = 0U;
    uint32 Lenth = 0x4000;
    uint8 i = 0;
    uint32 count = 0;

    Fls_Init(Fls_Config);

    /* Low Block Erase and BlankCheck*/
    for(i = 0;i < 4; i++)
    {
        Fls_Erase(FlsStartAddr,Lenth);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,Lenth);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x4000;
        if(i == 2) {
            Lenth = 0x8000;
            FlsStartAddr = 0x10000;
        }
    }

    FlsStartAddr = 0x7FF8;
    Lenth = 0x4000;
    for(i = 0;i < 2; i++)
    {
        Fls_Write(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr+(Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr+(Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x4000;
    }
    
    FlsStartAddr = 0x18000;
    for(i = 0;i < 2; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x18000;
    Fls_Write(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
#if (Fls_Compare_API == STD_ON)
    Fls_Compare(FlsStartAddr + (0x10000 - 8),array,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Read(FlsStartAddr + (0x10000 - 8),array1,16);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    
    FlsStartAddr = 0x38000;
    Lenth = 0x10000;
    /* High Block Erase and BlankCheck*/
    for(i = 0;i < 8; i++)
    {
        Fls_Erase(FlsStartAddr,0x10000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x10000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        FlsStartAddr += 0x10000;
    }
    FlsStartAddr = 0x38000;

    for(i = 0;i < 6; i++)
    {

        Fls_Write(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (Lenth - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (Lenth - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }

        FlsStartAddr += 0x10000;  
    }

    FlsStartAddr = 0x3b8000;
    Lenth = 0x40000;

    /* 256K Block Erase and BlankCheck*/
    for(i = 0;i < 35; i++)
    {
        Fls_Erase(FlsStartAddr,0x40000);
        PSPRINTF("--Block LogicAddr:0x%x PhyAddr:0x%x Test Finish--\n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #if (FLS_BLANK_CHECK_API == STD_ON)
        Fls_BlankCheck(FlsStartAddr,0x40000);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        FlsStartAddr += 0x40000;
    #endif
    }
    
    FlsStartAddr = 0x3b8000;
    for(i = 0;i < 33; i++)
    {
        Fls_Write(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
        
    #if (Fls_Compare_API == STD_ON)
        Fls_Compare(FlsStartAddr + (0x40000 - 8),array,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    #endif
        Fls_Read(FlsStartAddr + (0x40000 - 8),array1,16);
        while(Fls_GetStatus() != MEMIF_IDLE)
        {
            Fls_MainFunction();
        }
    
        FlsStartAddr += 0x40000;
    }
}

void test_fls_0161(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    static uint8 array[2048] = {0};
    static uint8 array1[2048] = {0};
    
    uint16 i = 0;
    uint16 j = 0;

    for(i = 0;i < 2048; i++)
    {
        array[i] = 0x11;
    }

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("type:%d\n",type);/*E_OK*/
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Write(0x38000,array,2048);
    Fls_MainFunction();
    
    Fls_Erase(0x38000,65536);
    Fls_MainFunction();
}

void test_fls_0162(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    static uint8 array[2048] = {0};
    static uint8 array1[2048] = {0};
    
    uint16 i = 0;
    uint16 j = 0;

    for(i = 0;i < 2048; i++)
    {
        array[i] = 0x11;
    }

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("type:%d\n",type);/*E_OK*/
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Write(0x38000,array,2048);
    Fls_MainFunction();

    Fls_Read(0x38000,array1,2048);
    Fls_MainFunction();
}

void test_fls_0163(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    Std_ReturnType type = E_NOT_OK;
    MemIf_JobResultType job_type = MEMIF_JOB_OK;
    static uint8 array[2048] = {0};
    static uint8 array1[2048] = {0};
    
    uint16 i = 0;
    uint16 j = 0;

    for(i = 0;i < 2048; i++)
    {
        array[i] = 0x11;
    }

    Fls_Init(Fls_Config);
    type = Fls_Erase(0x38000,65536);
    PSPRINTF("LogicAddr:0x%x PhyAddr:0x%x \n",gFls_JobAddrIt,Fls_Get_PhyStartAddress());
    PSPRINTF("type:%d\n",type);/*E_OK*/
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    job_type = Fls_GetJobResult();
    PSPRINTF("---After MainFunction Erase---\n");
    PSPRINTF("job_type:%d\n",job_type);
#if (FLS_BLANK_CHECK_API == STD_ON)
    Fls_BlankCheck(0x38000,65536);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    type = Fls_Write(0x38000,array,2048);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
    PSPRINTF("---After MainFunction Write---\n");
    job_type = Fls_GetJobResult();
    PSPRINTF("job_type:%d\n",job_type);
#if (Fls_Compare_API == STD_ON)
    type = Fls_Compare(0x38000,array,2048);
    while(Fls_GetStatus() != MEMIF_IDLE)
    {
        Fls_MainFunction();
    }
#endif
    Fls_Read(0x38000,array1,2048);
    Fls_MainFunction();
    Fls_Erase(0x38000,65536);
    Fls_MainFunction();
}

void test_fls_0170(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    VAR(uint32, FLS_VAR) gFls_MaxWrite_flag = 0U;
    VAR(uint32, FLS_VAR) gFls_MaxRead_flag  = 0U;

    Fls_Init(Fls_Config);
    gFls_MaxWrite_flag = gFls_MaxWrite;
    gFls_MaxRead_flag  = gFls_MaxRead;
    Fls_SetMode(3);

    if(gFls_MaxWrite_flag == gFls_MaxWrite &&
       gFls_MaxRead_flag  == gFls_MaxRead)
    {
        PSPRINTF("test_fls_0170 is ok\n");
    }
    else
    {
        PSPRINTF("test_fls_0170 is fail\n");
    }
}

void test_fls_0171(const Fls_ConfigType *Fls_Config)
{
    PSPRINTF("[%s]",__func__);
    uint8 data[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};

    Fls_Init(Fls_Config);

    Fls_Erase(0,0x4000);
    Fls_Cancel();
    Fls_Erase(0x478000,0x40000);
    Fls_Cancel();
    Fls_Write(0,data,0x4000);
    Fls_Cancel();
    Fls_Write(0x478000,data,0x40000);
    Fls_Cancel();
    Fls_Read(0,data,0x4000);
    Fls_Cancel();
    Fls_Read(0x478000,data,0x40000);
    Fls_Cancel();
    Fls_BlankCheck(0,0x4000);
    Fls_Cancel();
    Fls_BlankCheck(0x478000,0x40000);
    Fls_Cancel();
    Fls_Compare(0,data,0x4000);
    Fls_Cancel();
    Fls_Compare(0x478000,data,0x40000);
    Fls_Cancel();
}

FUNC( void, FLS_CODE ) FLASH_Cmd_Done_ISR(void)
{
    VAR( uint32_t, AUTOMATIC) FLS_EHV_Val = 0U;
    
    FLS_FMC.MCR.B.PECIE = 0U;
    if (FLS_FMC.MCR.B.EHV != 0U)
    {
        FLS_FMC.MCR.B.EHV = 0U;
        FLS_EHV_Val = 1U;
    }
    else
    {
        FLS_EHV_Val = 0U;
    }
}

FUNC( status_t, FLS_CODE ) FLASH_Irq_Init(void)
{
    VAR( status_t, AUTOMATIC) sFls_Ret = STATUS_SUCCESS;
    
    sFls_Ret = INTC_LLD_Set_IRQ_Priority(INTR_ID_185, INTR_PRI_1);
    if (sFls_Ret != STATUS_SUCCESS)
    {
        return sFls_Ret;
    }

    sFls_Ret = INTC_LLD_Set_IRQ_Handle(INTR_ID_185, &FLASH_Cmd_Done_ISR);
    if (sFls_Ret != STATUS_SUCCESS)
    {
        return sFls_Ret;
    }

    sFls_Ret = INTC_LLD_Set_IRQ_Enable(INTR_ID_185);
    if (sFls_Ret != STATUS_SUCCESS)
    {
        return sFls_Ret;
    }
}

int tsc_fls_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
    }

   if (argc == 2)
   {
       if (!strcmp(agrv[1], "help"))
       {

            PSPRINTF("irq ---------- CMD ------- Register/enable FLS interrupt numbers\n \
                      stop --------- CMD ------- Migrate the module status to stop\n");
                    
            PSPRINTF("ID of the test case:\n");
            for(uint8 i = 0; i < FLS_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", fls_funcs[i].name);
            }
        }
        else
        {
            for(uint8 i = 0; i < FLS_TEST_CASE_MAX; i++)
            {
                if(!strcmp(agrv[1], fls_funcs[i].name))
                {
                    fls_funcs[i].flsfunc(&Fls_Config);
                    return 0;
                }
            }
            PSPRINTF("error: Input invalid parameters[%s], please Use the 'fls_test help' command to see the supported test instructions\n", agrv[1]);
        }
   }

    return 0;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), fls_test , tsc_fls_func, deint or number of test case);





