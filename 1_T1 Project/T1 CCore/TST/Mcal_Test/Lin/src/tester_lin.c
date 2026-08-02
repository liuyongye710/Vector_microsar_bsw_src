#include <string.h>
#include "tester_lin.h"
#include "common.h"
#include "console.h"
#include "intc_lld.h"
#include "shell.h"
#include "Lin_Cfg.h"
#include "Lin_LLDriver.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#define LIN_TEST_CASE_MAX sizeof(lin_funcs) / sizeof(LinfuncMachine)

#define LIN_GETSTATUS_TIMEOUT 500U
#define LIN_SEND_DATA_LEN  0x8u

#define PRINTF_FUNCNAME() PSPRINTF("\r\n[%s]\r\n", __func__);

#define TSC_LIN_0099_0106_CHANNEL 0U
#define TSC_LIN_0107_0112_CHANNEL 0U
#define TSC_LIN_0118_0125_CHANNEL 0U
#define TSC_LIN_0126_0130_CHANNEL 0U
#define TSC_LIN_0131_0138_CHANNEL 0U
#define TSC_LIN_0139_0143_CHANNEL 0U

/* Specification of Lin Driver : [SWS_Lin_00156] */
FUNC(void, LIN_CODE) Lin_LLD_Init_IrqIsrEnable(void)
{

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_376, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_376, &LINFLEX0_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_376);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_377, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_377, &LINFLEX0_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_377);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_378, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_378, &LINFLEX0_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_378);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_380, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_380, &LINFLEX1_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_380);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_381, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_381, &LINFLEX1_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_381);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_382, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_382, &LINFLEX1_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_382);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_384, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_384, &LINFLEX2_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_384);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_385, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_385, &LINFLEX2_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_385);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_386, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_386, &LINFLEX2_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_386);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_479, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_479, &LINFLEX3_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_479);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_480, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_480, &LINFLEX3_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_480);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_481, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_481, &LINFLEX3_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_481);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_482, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_482, &LINFLEX4_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_482);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_483, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_483, &LINFLEX4_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_483);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_484, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_484, &LINFLEX4_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_484);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_485, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_485, &LINFLEX5_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_485);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_486, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_486, &LINFLEX5_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_486);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_487, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_487, &LINFLEX5_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_487);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_435, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_435, &LINFLEX6_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_435);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_439, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_439, &LINFLEX6_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_439);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_492, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_492, &LINFLEX6_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_492);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_539, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_539, &LINFLEX7_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_539);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_540, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_540, &LINFLEX7_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_540);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_541, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_541, &LINFLEX7_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_541);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_554, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_554, &LINFLEX8_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_554);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_555, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_555, &LINFLEX8_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_555);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_556, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_556, &LINFLEX8_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_556);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_609, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_609, &LINFLEX9_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_609);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_610, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_610, &LINFLEX9_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_610);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_611, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_611, &LINFLEX9_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_611);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_642, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_642, &LINFLEX10_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_642);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_643, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_643, &LINFLEX10_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_643);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_644, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_644, &LINFLEX10_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_644);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_645, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_645, &LINFLEX11_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_645);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_646, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_646, &LINFLEX11_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_646);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_647, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_647, &LINFLEX11_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_647);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_493, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_493, &LINFLEX12_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_493);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_542, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_542, &LINFLEX12_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_542);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_557, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_557, &LINFLEX12_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_557);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_432, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_432, &LINFLEX14_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_432);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_433, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_433, &LINFLEX14_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_433);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_434, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_434, &LINFLEX14_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_434);

//        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_436, INTR_PRI_40);
//        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_436, &LINFLEX15_LLD_RXI_IRQ_HANDLER);
//        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_436);
//        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_437, INTR_PRI_40);
//        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_437, &LINFLEX15_LLD_TXI_IRQ_HANDLER);
//        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_437);
//        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_438, INTR_PRI_40);
//        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_438, &LINFLEX15_LLD_ERR_IRQ_HANDLER);
//        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_438);

        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_416, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_416, &LINFLEX16_LLD_RXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_416);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_417, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_417, &LINFLEX16_LLD_TXI_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_417);
        (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_418, INTR_PRI_40);
        (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_418, &LINFLEX16_LLD_ERR_IRQ_HANDLER);
        (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_418);
        
}

VAR(uint8,AUTOMATIC) linSdu[8] = {0};
uint32 ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;


static uint8 lindata[][LIN_SEND_DATA_LEN] = {
    {0x00u, 0x50u, 0x90u, 0xD0u, 0x10u, 0xa1u, 0x42u, 0x85u},
    {0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u, 0x08u},
    {0x02u, 0x08u, 0x36u, 0xD0u, 0x10u, 0xa1u, 0x42u, 0x86u},
    {0x45u, 0x39u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u, 0x08u}
};

const Lin_PduType linPduInfo[]={
    {
        .Pid= 0x17u,
        .Cs = LIN_CLASSIC_CS,
        .Drc= LIN_FRAMERESPONSE_TX,
        .Dl = LIN_SEND_DATA_LEN,
        .SduPtr = lindata[0],
    },

    {
        .Pid= 0x18u,
        .Cs = LIN_CLASSIC_CS,
        .Drc= LIN_FRAMERESPONSE_RX,
        .Dl = LIN_SEND_DATA_LEN,
        .SduPtr =  lindata[1],
    },
    {
        .Pid= 0x19u,
        .Cs = LIN_ENHANCED_CS,
        .Drc= LIN_FRAMERESPONSE_TX,
        .Dl = LIN_SEND_DATA_LEN,
        .SduPtr = lindata[2],
    },

    {
        .Pid= 0x1Au,
        .Cs = LIN_ENHANCED_CS,
        .Drc= LIN_FRAMERESPONSE_RX,
        .Dl = LIN_SEND_DATA_LEN,
        .SduPtr =  lindata[3],
    },
};


static LinfuncMachine lin_funcs[] = {
#if (LIN_VERSION_INFO_API == STD_ON)
   {"LIN_0033", TSC_Lin_0033},
   {"LIN_0034", TSC_Lin_0034},
#endif
#if (LIN_MASTER_NODE_USED == STD_ON)
   {"LIN_0027", TSC_Lin_0027},
   {"LIN_0028", TSC_Lin_0028},
   {"LIN_0029", TSC_Lin_0029},
   {"LIN_0030", TSC_Lin_0030},
   {"LIN_0031", TSC_Lin_0031},
   {"LIN_0032", TSC_Lin_0032},
   {"LIN_0035", TSC_Lin_0035},
   {"LIN_0036", TSC_Lin_0036},
   {"LIN_0037", TSC_Lin_0037},
   {"LIN_0038", TSC_Lin_0038},
   {"LIN_0039", TSC_Lin_0039},
   {"LIN_0040", TSC_Lin_0040},
   {"LIN_0041", TSC_Lin_0041},
   {"LIN_0042", TSC_Lin_0042},
   {"LIN_0043", TSC_Lin_0043},
   {"LIN_0044", TSC_Lin_0044},
   {"LIN_0045", TSC_Lin_0045},
   {"LIN_0046", TSC_Lin_0046},
   {"LIN_0047", TSC_Lin_0047},
   {"LIN_0048", TSC_Lin_0048},
   {"LIN_0049", TSC_Lin_0049},
   {"LIN_0050", TSC_Lin_0050},
   {"LIN_0051", TSC_Lin_0051},
   {"LIN_0052_0053", TSC_Lin_0052_0053},
   {"LIN_0054", TSC_Lin_0054},
   {"LIN_0055", TSC_Lin_0055},
   {"LIN_0056", TSC_Lin_0056},
   {"LIN_0057", TSC_Lin_0057},
   {"LIN_0058", TSC_Lin_0058},
   {"LIN_0059_0065", TSC_Lin_0059_0065},
   {"LIN_0072_0079", TSC_Lin_0072_0079},
   {"LIN_0085_0092", TSC_Lin_0085_0092},
   {"LIN_0099_0106", TSC_Lin_0099_0106},
   {"LIN_0118_0125", TSC_Lin_0118_0125},
   {"LIN_0131_0138", TSC_Lin_0131_0138},
   {"LIN_0144_0146", TSC_Lin_0144_0146},
   {"LIN_0147_0152", TSC_Lin_0147_0152},
   {"LIN_0153_0157", TSC_Lin_0153_0157},
   {"LIN_0158_0166", TSC_Lin_0158_0166},
   {"LIN_0173_0180", TSC_Lin_0173_0180},
   {"LIN_0188_0195", TSC_Lin_0188_0195},
   {"LIN_0201_0208", TSC_Lin_0201_0208},
   {"LIN_0214_0221", TSC_Lin_0214_0221}, 
   {"LIN_0227_0234", TSC_Lin_0227_0234},
   {"LIN_0240_0247", TSC_Lin_0240_0247},
   {"LIN_0253_0260", TSC_Lin_0253_0260},
   {"LIN_0266_0273", TSC_Lin_0266_0273},
   {"LIN_0279_0286", TSC_Lin_0279_0286},
   {"LIN_0292_0299", TSC_Lin_0292_0299},
   {"LIN_0305_0312", TSC_Lin_0305_0312},
   {"LIN_0318_0332", TSC_Lin_0318_0332},
//    {"LIN_0333", TSC_Lin_0333},
//    {"LIN_0333_1", TSC_Lin_0333_1},
//    {"LIN_0333_2", TSC_Lin_0333_2},
#endif

   {"LIN_0066_0071", TSC_Lin_0066_0071},
   {"LIN_0080_0084", TSC_Lin_0080_0084},
   {"LIN_0093_0098", TSC_Lin_0093_0098},
   {"LIN_0107_0112", TSC_Lin_0107_0112},
   {"LIN_0126_0130", TSC_Lin_0126_0130},
   {"LIN_0139_0143", TSC_Lin_0139_0143},
   {"LIN_0167_0172", TSC_Lin_0167_0172},
   {"LIN_0181_0185", TSC_Lin_0181_0185},
   {"LIN_0196_0200", TSC_Lin_0196_0200},
   {"LIN_0209_0213", TSC_Lin_0209_0213},
   {"LIN_0222_0226", TSC_Lin_0222_0226},
   {"LIN_0235_0239", TSC_Lin_0235_0239},
   {"LIN_0248_0252", TSC_Lin_0248_0252},
   {"LIN_0261_0265", TSC_Lin_0261_0265},
   {"LIN_0274_0278", TSC_Lin_0274_0278},
   {"LIN_0287_0291", TSC_Lin_0287_0291},
   {"LIN_0300_0304", TSC_Lin_0300_0304},
   {"LIN_0313_0317", TSC_Lin_0313_0317},
};


extern VAR(Lin_DriveState_Type,LIN_VAR) eLin_DrvStatus;
extern volatile VAR(uint8, LIN_VAR) u8Lin_ChStatus[LIN_HW_MAX_AVAILABLE_MODULES];

#if (LIN_VERSION_INFO_API == STD_ON)

void TSC_Lin_0033(const Lin_ConfigType *LinDriverConfig)
{
    Std_VersionInfoType *VersionInfo = (Std_VersionInfoType *)linSdu;
    PRINTF_FUNCNAME();
    Lin_GetVersionInfo(VersionInfo);

    PSPRINTF("VersionInfo->vendorID = %d\r\n", VersionInfo->vendorID);
    PSPRINTF("VersionInfo->moduleID= %d\r\n", VersionInfo->moduleID);
    PSPRINTF("VersionInfo->sw_major_version= %d\r\n", VersionInfo->sw_major_version);
    PSPRINTF("VersionInfo->sw_minor_version= %d\r\n", VersionInfo->sw_minor_version);
    PSPRINTF("VersionInfo->sw_patch_version= %d\r\n", VersionInfo->sw_patch_version);
}

void TSC_Lin_0034(const Lin_ConfigType *LinDriverConfig)
{
    PRINTF_FUNCNAME();
    Lin_GetVersionInfo(NULL_PTR);

}
#endif

#if (LIN_MASTER_NODE_USED == STD_ON)

void TSC_Lin_0027(const Lin_ConfigType *LinDriverConfig)
{
    PRINTF_FUNCNAME();
    Lin_Init(NULL_PTR);
}

void TSC_Lin_0028(const Lin_ConfigType *LinDriverConfig)
{
    PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);
    int i = 0;
    if (eLin_DrvStatus == LIN_INIT)
    {
        PSPRINTF("Lin_Init is Ok\r\n");
        for (i = 0; i < LIN_HW_MAX_MODULES; i++)
        {
        	PSPRINTF("Lin Channel %d state: %d\r\n", i ,u8Lin_ChStatus[LinDriverConfig->pLin_Channel[i]->u8LinHwChannel]);
        }
    }
    else
    {
        PSPRINTF("Test Error\r\n");
    }
}

void TSC_Lin_0029(const Lin_ConfigType *LinDriverConfig)
{
    PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);
    int i = 0;
    if (eLin_DrvStatus == LIN_INIT)
    {
        PSPRINTF("Lin_Init is Ok\r\n");
        for (i = 0; i < LIN_HW_MAX_MODULES; i++)
        {
            PSPRINTF("Lin Channel %d ",i);
        	PSPRINTF("state: %d\r\n", u8Lin_ChStatus[LinDriverConfig->pLin_Channel[i]->u8LinHwChannel]);
        }
    }
    else
    {
        PSPRINTF("Test Error\r\n");
    }

    Lin_Init(LinDriverConfig);
}

void TSC_Lin_0030(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    u8Lin_ReturnValue = Lin_CheckWakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0031(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_CheckWakeup(0xFF);

    PSPRINTF("[TSC_Lin_0031] u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0032(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    INTC_LLD_Set_IRQ_Disable(INTR_ID_376);

    (void)delay_ms(3000);

    u8Lin_ReturnValue = Lin_CheckWakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    if (u8Lin_ReturnValue == E_OK)
    {
        PSPRINTF("Lin_CheckWakeup is Ok\r\n");
    }
    else
    {
        PSPRINTF("Test is not Ok\r\n");
    }
}

void TSC_Lin_0035(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    if (u8Lin_ReturnValue == E_OK)
    {
        PSPRINTF("Lin_GoToSleep is Ok");
    }
    else
    {
        PSPRINTF("Lin_GoToSleep is not Ok");
    }
}

void TSC_Lin_0036(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_GoToSleep(0xFF);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    if (u8Lin_ReturnValue == E_OK)
    {
        PSPRINTF("Lin_GoToSleep is Ok\n");
    }
    else
    {
        PSPRINTF("Lin_GoToSleep is not Ok\n");
    }
}

void TSC_Lin_0037(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[TSC_Lin_0037] u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    if(u8Lin_ReturnValue == 0)
    {
        PSPRINTF("[TSC_Lin_0037] Lin_GoToSleep is Ok\n");
    }
    else
    {
        PSPRINTF("[TSC_Lin_0037] Lin_GoToSleep is not Ok\n");
    }

}

void TSC_Lin_0038(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    if(u8Lin_ReturnValue == 0)
    {
        PSPRINTF("Lin_GoToSleep is Ok\n");
    }
    else
    {
        PSPRINTF("Lin_GoToSleep is not Ok\n");
    }
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("Lin Channel %d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
}

/***************************Lin_GoToSleepInternal************************************/

void TSC_Lin_0039(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    u8Lin_ReturnValue = Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0040(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_GoToSleepInternal(0xFF);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0041(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    Lin_WakeupInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    u8Lin_ReturnValue = Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
}

/***************************End************************************/

/***************************Lin_Wakeup************************************/
void TSC_Lin_0042(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0043(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_Wakeup(0xFF);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0044(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("Lin Channel %d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
}

void TSC_Lin_0045(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("First u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("Lin Channel %d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);


    PSPRINTF("Second call\r\n");
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("Second u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
}

/***************************End************************************/

/***************************Lin_WakeupInternal************************************/
void TSC_Lin_0046(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    u8Lin_ReturnValue = Lin_WakeupInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0047(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_WakeupInternal(0xFF);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0048(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_WakeupInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
}
/***************************End************************************/

/***************************Lin_GetStatus************************************/
void TSC_Lin_0049(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0050(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_GetStatus(0xFF, pu8linSduPtr);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0051(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, NULL_PTR);

    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0052_0053(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("Lin_WakeupInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);

    PSPRINTF("Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);

        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(1);
            }
            else
            {
                PSPRINTF("LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("Lin_GoToSleep u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
    PSPRINTF("Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
}

/***************************End************************************/

/***************************Lin_SendFrame************************************/
void TSC_Lin_0054(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0055(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);
    u8Lin_ReturnValue = Lin_SendFrame(0xFF, &linPduInfo[2]);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0056(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);
    u8Lin_ReturnValue = Lin_SendFrame(0, NULL_PTR);
    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}

void TSC_Lin_0057(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);
    PSPRINTF("Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
}

void TSC_Lin_0058(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    Lin_Init(LinDriverConfig);

    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("Lin_Wakeup  u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);
    PSPRINTF("Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}
/***************************End************************************/

/***************************Lin_StateMachine************************************/

// Master Node
void TSC_Lin_0059_0065(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0059
    Lin_Init(LinDriverConfig);
    PSPRINTF("[Lin_0060] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);

    // Lin_0060
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0060] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0060] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);

    // Lin_0061
    u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0061] Lin_GoToSleep u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0061] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);

    // Lin_0062
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
    PSPRINTF("[Lin_0062] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0062] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    // Lin_0063
    u8Lin_ReturnValue = Lin_WakeupInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0063] Lin_WakeupInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0063] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    // Lin_0064
    u8Lin_ReturnValue = Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0064] Lin_GoToSleepInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0064] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);

    // Lin_0065
    u8Lin_ReturnValue = Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0065] Lin_GoToSleepInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0065] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
}

/***************************StateMachine_End************************************/

/***************************Transmit-Receive************************************/
/*
LinChannelId: 0
BaudRate: 9600
BreakLength: 13
LinHwChannel: 0
LinNodeType: Master
*/
void TSC_Lin_0072_0079(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0073
    Lin_Init(LinDriverConfig);

    // Lin_0074
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0074] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0074] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0075
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0075]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0075] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0076
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0076]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0076] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0077
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0077] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0077]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0078
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[3]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0078]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0078] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0079
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0079] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0079]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}


/*
LinChannelId: 1
BaudRate: 19.2K
BreakLength: 13
LinHwChannel: 1
LinNodeType: MASTER
*/
void TSC_Lin_0085_0092(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0086
    Lin_Init(LinDriverConfig);

    // Lin_0087
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0087] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0087] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0088
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[1]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0088]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0088] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0089
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, &linPduInfo[0]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0089]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0089] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0090
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0090] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0090]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0091
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0091]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0091] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0092
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0092] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0092]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

/*
LinChannelId: 3
BaudRate: 19.2K
BreakLength: 20
LinHwChannel: 14
LinNodeType: MASTER
*/
void TSC_Lin_0099_0106(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0100
    Lin_Init(LinDriverConfig);

    // Lin_0101
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[2]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0101] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0101] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0102
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[2]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0102]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0102] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }
    (void)delay_ms(100);
    // lin_0103
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[2]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0103]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0103] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0104
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[2]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0104] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0104]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0105
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[2]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0105]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0105] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0106
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[2]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0106] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0106]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

/*
LinChannelId: 4
BaudRate: 19.2K
BreakLength: 21
LinHwChannel: 16
LinNodeType: MASTER
*/
void TSC_Lin_0118_0125(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0119
    Lin_Init(LinDriverConfig);

    // Lin_0120
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[3]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0120] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0120] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0121
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[3]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0121]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0121] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0122
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[3]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0122]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0122] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0123
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[3]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0123] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0123]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0124
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[3]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0124]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0124] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0125
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[3]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0125] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0125]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

/*
LinChannelId: 5
BaudRate: 19.2K
BreakLength: 22
LinHwChannel: 2
LinNodeType: MASTER
*/
void TSC_Lin_0131_0138(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0132
    Lin_Init(LinDriverConfig);

    // Lin_0133
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[4]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0133] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0133] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0134
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[4]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0134]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0134] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0135
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[4]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0135]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0135] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0136
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[4]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0136] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0136]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0137
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[4]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0137]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0137] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0138
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[4]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0138] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0138]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0144_0146(const Lin_ConfigType *LinDriverConfig)
{
	Lin_Init(LinDriverConfig);
    VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);


    PSPRINTF("u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    // Lin_0145
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0145]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0145] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0146
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0146] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0146]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

}


void TSC_Lin_0147_0152(const Lin_ConfigType *LinDriverConfig)
{
	//Lin_147
    VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

	Lin_Init(LinDriverConfig);
    ////Lin_148
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
    PSPRINTF("[Lin_0148]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    //Lin_0149
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0149]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0149] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }
    //Lin_150
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
    PSPRINTF("[Lin_0150]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    //Lin_151
    u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    if (u8Lin_ReturnValue == E_OK)
    {
        PSPRINTF("[Lin_0151]Lin_CheckWakeup is Ok");
    }
    else
    {
        PSPRINTF("[Lin_0151]Lin_CheckWakeup is not Ok");
    }
    PSPRINTF("[Lin_0151]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    //Lin_0152
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
    PSPRINTF("[Lin_0152]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
}

void TSC_Lin_0153_0157(const Lin_ConfigType *LinDriverConfig)
{
	//Lin_0153
	VAR(uint8, AUTOMATIC) * pu8linSduPtr[1];
	Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

	Lin_Init(LinDriverConfig);
	//Lin_0154
	u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
	if (u8Lin_ReturnValue != E_OK)
	{
		PSPRINTF("[Lin_0154]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
		return;
	}
	else
	{
		PSPRINTF("[Lin_0154] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	}
    //Lin_0155
	u8Lin_ReturnValue = Lin_GoToSleep(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
	if (u8Lin_ReturnValue == E_OK)
	{
		PSPRINTF("[Lin_0155]Lin_CheckWakeup is Ok\r\n");
	}
	else
	{
		PSPRINTF("[Lin_0155]Lin_CheckWakeup is not Ok\r\n");
	}
	PSPRINTF("[Lin_0155]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	//Lin_156
	u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	PSPRINTF("[Lin_0156]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    //Lin_0157
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);
    PSPRINTF("[Lin_0157]u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);

}
void TSC_Lin_0158_0166(const Lin_ConfigType *LinDriverConfig)
{
	VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
	    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
	    pu8linSduPtr[0] = linSdu;

	    // Lin_0160
	    Lin_Init(LinDriverConfig);

	    // Lin_0161
	    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
	    {
	        PSPRINTF("[Lin_0161] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
	        return;
	    }
	    else
	    {
	        PSPRINTF("[Lin_0161] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    // Lin_0162
	    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
	    if (u8Lin_ReturnValue != E_OK)
	    {
	        PSPRINTF("[Lin_0162]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
	        return;
	    }
	    else
	    {
	        PSPRINTF("[Lin_0162] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    // lin_0163
	    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[2]);
	    if (u8Lin_ReturnValue != E_OK)
	    {
	        PSPRINTF("[lin_0163]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
	        return;
	    }else
	    {
	        PSPRINTF("[lin_0163] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    //Lin_0164
	    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
	    do
	    {
	        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
	        {
	            PSPRINTF("[Lin_0164] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	            break;
	        }
	        else
	        {
	            if (ulGetStatusTimeout > 0)
	            {
	                (void)delay_ms(1);
	                ulGetStatusTimeout--;
	            }
	            else
	            {
	                PSPRINTF("[Lin_0164]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
	                return;
	            }
	        }
	    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

	    (void)delay_ms(500);

	    // lin_0165
	    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[3]);
	    if (u8Lin_ReturnValue != E_OK)
	    {
	        PSPRINTF("[lin_0165]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
	        return;
	    }
	    else
	    {
	        PSPRINTF("[lin_0165] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    // lin_0166
	    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
	    do
	    {
	        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
	        {
	            PSPRINTF("[lin_0166] recv response: ");
	            for(int i = 0; i < 8; i++)
	            {
	                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
	            }
	            PSPRINTF("\r\n");
	            break;
	        }
	        else
	        {
	            if (ulGetStatusTimeout > 0)
	            {
	                ulGetStatusTimeout--;
	                (void)delay_ms(10);
	            }
	            else
	            {
	                PSPRINTF("[lin_0166]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
	                return;
	            }
	        }
	    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}
void TSC_Lin_0173_0180(const Lin_ConfigType *LinDriverConfig)
{
	VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
	    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();
	    pu8linSduPtr[0] = linSdu;

	    // Lin_0174
	    Lin_Init(LinDriverConfig);

	    // Lin_0175
	    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
	    {
	        PSPRINTF("[Lin_0175] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
	        return;
	    }
	    else
	    {
	        PSPRINTF("[Lin_0175] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    // Lin_0176
	    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
	    if (u8Lin_ReturnValue != E_OK)
	    {
	        PSPRINTF("[Lin_0176]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
	        return;
	    }
	    else
	    {
	        PSPRINTF("[Lin_0176] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    // lin_0177
	    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[2]);
	    if (u8Lin_ReturnValue != E_OK)
	    {
	        PSPRINTF("[lin_0177]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
	        return;
	    }else
	    {
	        PSPRINTF("[lin_0177] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    //Lin_0178
	    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
	    do
	    {
	        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
	        {
	            PSPRINTF("[Lin_0178] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	            break;
	        }
	        else
	        {
	            if (ulGetStatusTimeout > 0)
	            {
	                (void)delay_ms(1);
	                ulGetStatusTimeout--;
	            }
	            else
	            {
	                PSPRINTF("[Lin_0178]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
	                return;
	            }
	        }
	    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

	    (void)delay_ms(500);

	    // lin_0179
	    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[3]);
	    if (u8Lin_ReturnValue != E_OK)
	    {
	        PSPRINTF("[lin_0179]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
	        return;
	    }
	    else
	    {
	        PSPRINTF("[lin_0179] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	    }

	    // lin_0180
	    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
	    do
	    {
	        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
	        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
	        {
	            PSPRINTF("[lin_0180] recv response: ");
	            for(int i = 0; i < 8; i++)
	            {
	                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
	            }
	            PSPRINTF("\r\n");
	            break;
	        }
	        else
	        {
	            if (ulGetStatusTimeout > 0)
	            {
	                ulGetStatusTimeout--;
	                (void)delay_ms(10);
	            }
	            else
	            {
	                PSPRINTF("[lin_0180]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
	                return;
	            }
	        }
	    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}



/*
LinChannelId: 5
BaudRate: 19.2K
BreakLength: 22
LinHwChannel: 2
LinNodeType: MASTER
*/
void TSC_Lin_0188_0195(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0189
    Lin_Init(LinDriverConfig);

    // Lin_0190
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[5]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0190] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0190] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0191
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[5]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0191]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0191] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0192
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[5]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0192]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0192] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0193
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[5]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0193] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0193]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0194
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[5]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0194]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0194] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0195
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[5]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0195] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0195]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

/*
LinChannelId: 5
BaudRate: 19.2K
BreakLength: 22
LinHwChannel: 2
LinNodeType: MASTER
*/
void TSC_Lin_0201_0208(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0202
    Lin_Init(LinDriverConfig);

    // Lin_0203
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[6]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0203] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0203] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0204
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[6]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0204]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0204] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0205
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[6]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0205]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0205] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0206
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[6]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0206] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0206]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0207
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[6]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0207]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0207] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0208
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[6]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0208] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0208]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0214_0221(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0215
    Lin_Init(LinDriverConfig);

    // Lin_0216
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[7]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0216] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0216] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0217
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[7]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0217]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0217] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0218
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[7]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0218]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0218] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0219
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[7]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0219] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0219]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0220
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[7]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0220]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0220] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0221
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[7]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0221] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0221]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0227_0234(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0228
    Lin_Init(LinDriverConfig);

    // Lin_0229
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[8]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0229] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0229] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0230
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[8]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0230]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0230] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0231
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[8]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0231]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0231] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0232
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[8]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0232] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0232]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0233
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[8]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0233]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0233] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0234
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[8]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0234] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0234]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0240_0247(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0241
    Lin_Init(LinDriverConfig);

    // Lin_0242
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[9]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0242] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0242] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0243
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[9]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0243]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0243] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0244
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[9]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0244]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0244] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0245
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[9]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0245] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0245]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0246
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[9]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0246]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0246] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0247
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[9]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0247] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0247]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0253_0260(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0254
    Lin_Init(LinDriverConfig);

    // Lin_0255
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[10]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0255] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0255] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0256
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[10]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0256]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0256] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0257
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[10]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0257]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0257] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0258
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[10]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0258] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0258]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0259
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[10]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0259]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0259] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0260
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[10]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0260] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0260]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}


void TSC_Lin_0266_0273(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0267
    Lin_Init(LinDriverConfig);

    // Lin_0268
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[11]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0268] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0268] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0269
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[11]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0269]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0269] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0270
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[11]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0270]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0270] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0271
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[11]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0271] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0271]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0272
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[11]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0272]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0272] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0273
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[11]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0273] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0273]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0279_0286(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0280
    Lin_Init(LinDriverConfig);

    // Lin_0281
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[12]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0281] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0281] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0282
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[12]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0282]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0282] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0283
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[12]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0283]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0283] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0284
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[12]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0284] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0284]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0285
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[12]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0286]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0286] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0286
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[12]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0286] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0286]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0292_0299(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0293
    Lin_Init(LinDriverConfig);

    // Lin_0294
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[13]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0294] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0294] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0295
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[13]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0295]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0295] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0296
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[13]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0296]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0296] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0297
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[13]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0297] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0297]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0298
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[13]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0298]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0298] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0299
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[13]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0299] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0299]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0305_0312(const Lin_ConfigType *LinDriverConfig)
{
    VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();
    pu8linSduPtr[0] = linSdu;

    // Lin_0306
    Lin_Init(LinDriverConfig);

    // Lin_0307
    u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[14]->u8LinChannelID, pu8linSduPtr);
    if (u8Lin_ReturnValue != LIN_CH_SLEEP)
    {
        PSPRINTF("[Lin_0307] u8Lin_ReturnValue != LIN_CH_SLEEP\r\n");
        return;
    }
    else
    {
        PSPRINTF("[Lin_0307] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // Lin_0308
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[14]->u8LinChannelID);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0308]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[Lin_0308] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0309
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[14]->u8LinChannelID, &linPduInfo[2]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0309]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[lin_0309] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    //Lin_0310
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[14]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
        {
            PSPRINTF("[Lin_0310] Lin_GetStatus u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                (void)delay_ms(1);
                ulGetStatusTimeout--;
            }
            else
            {
                PSPRINTF("[Lin_0310]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

    (void)delay_ms(500);

    // lin_0311
    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[14]->u8LinChannelID, &linPduInfo[1]);
    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[lin_0311]LIN Error %d returned by Lin_SendFrame\n", u8Lin_ReturnValue);
        return;
    }
    else
    {
        PSPRINTF("[lin_0311] Lin_SendFrame u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    }

    // lin_0312
    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
    do
    {
        u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[14]->u8LinChannelID, pu8linSduPtr);
        if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
        {
            PSPRINTF("[lin_0312] recv response: ");
            for(int i = 0; i < 8; i++)
            {
                PSPRINTF("%x ", (pu8linSduPtr[0][i]));
            }
            PSPRINTF("\r\n");
            break;
        }
        else
        {
            if (ulGetStatusTimeout > 0)
            {
                ulGetStatusTimeout--;
                (void)delay_ms(10);
            }
            else
            {
                PSPRINTF("[lin_0312]LIN Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                return;
            }
        }
    } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}

void TSC_Lin_0318_0332(const Lin_ConfigType *LinDriverConfig)
{
   VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
   Std_ReturnType u8Lin_ReturnValue;
   PRINTF_FUNCNAME();
   pu8linSduPtr[0] = linSdu;

   // Lin_0319
   Lin_Init(LinDriverConfig);

   // Lin_0321
   u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
   if (u8Lin_ReturnValue != E_OK)
   {
       PSPRINTF("[Lin_0321]LIN Error %d returned by Lin_WakeUp0(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
       return;
   }
   else
   {
       PSPRINTF("[Lin_0321] Lin_Wakeup0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
   }

   // Lin_0322
   u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[1]->u8LinChannelID);
   if (u8Lin_ReturnValue != E_OK)
   {
       PSPRINTF("[Lin_0322]LIN Error %d returned by Lin_WakeUp1(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
       return;
   }
   else
   {
       PSPRINTF("[Lin_0322] Lin_Wakeup1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
   }


   // Lin_0323
   u8Lin_ReturnValue = u8Lin_ChStatus[2];
	if (u8Lin_ReturnValue != LIN_CH_OPERATIONAL)
	{
		PSPRINTF("[Lin_0323]LIN Error %d returned by Lin_WakeUp2(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
		return;
	}
	else
	{
		PSPRINTF("[Lin_0323] Lin_Wakeup2 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	}
	u8Lin_ReturnValue = u8Lin_ChStatus[14];
	if (u8Lin_ReturnValue != LIN_CH_OPERATIONAL)
	{
		PSPRINTF("[Lin_0324]LIN Error %d returned by Lin_WakeUp3(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
		return;
	}
	else
	{
		PSPRINTF("[Lin_0324] Lin_Wakeup3 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	}


///////////////////////////////////////////////////////////////

	PSPRINTF("\r\n---------LIN_FRAMERESPONSE_TX-----------------\r\n");

   // lin_0325
   u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);
   if (u8Lin_ReturnValue != E_OK)
   {
       PSPRINTF("[lin_0322]LIN Error %d returned by Lin_SendFrame0\n", u8Lin_ReturnValue);
       return;
   }else
   {
       PSPRINTF("[lin_0322] Lin_SendFrame0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
   }

   // lin_0326
   u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, &linPduInfo[2]);
   if (u8Lin_ReturnValue != E_OK)
	{
		PSPRINTF("[lin_0326]LIN Error %d returned by Lin_SendFrame1\n", u8Lin_ReturnValue);
		return;
	}else
	{
		PSPRINTF("[lin_0326] Lin_SendFrame1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	}

   //Lin_0327
   ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
   do
   {
       u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
       if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
       {
           PSPRINTF("[Lin_0327] Lin_GetStatus0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
           break;
       }
       else
       {
           if (ulGetStatusTimeout > 0)
           {
               (void)delay_ms(1);
               ulGetStatusTimeout--;
           }
           else
           {
               PSPRINTF("[Lin_0327]LIN0 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
               return;
           }
       }
   } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

   //Lin_0328
   do
      {
          u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
          if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
          {
              PSPRINTF("[Lin_0328] Lin_GetStatus1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
              break;
          }
          else
          {
              if (ulGetStatusTimeout > 0)
              {
                  (void)delay_ms(1);
                  ulGetStatusTimeout--;
              }
              else
              {
                  PSPRINTF("[Lin_0328]LIN1 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                  return;
              }
          }
      } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

   (void)delay_ms(500);



	PSPRINTF("\r\n---------LIN_FRAMERESPONSE_RX-----------------\r\n");
   // lin_0329
   u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[1]);
   if (u8Lin_ReturnValue != E_OK)
   {
       PSPRINTF("[lin_0329]LIN Error %d returned by Lin_SendFrame0\n", u8Lin_ReturnValue);
       return;
   }
   else
   {
       PSPRINTF("[lin_0329] Lin_SendFrame0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
   }

   // lin_0330
   u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, &linPduInfo[3]);
   if (u8Lin_ReturnValue != E_OK)
	{
		PSPRINTF("[lin_0330]LIN Error %d returned by Lin_SendFrame1\n", u8Lin_ReturnValue);
		return;
	}
	else
	{
		PSPRINTF("[lin_0330] Lin_SendFrame1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
	}

   // lin_0331
   ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
   do
   {
       u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
       if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
       {
           PSPRINTF("[lin_0331] recv0 response: ");
           for(int i = 0; i < 8; i++)
           {
               PSPRINTF("%x ", (pu8linSduPtr[0][i]));
           }
           PSPRINTF("\r\n");
           break;
       }
       else
       {
           if (ulGetStatusTimeout > 0)
           {
               ulGetStatusTimeout--;
               (void)delay_ms(10);
           }
           else
           {
               PSPRINTF("[lin_0331]LIN0 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
               return;
           }
       }
   } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);


   // lin_0332
       ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
       do
       {
           u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
           if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
           {
               PSPRINTF("[lin_0332] recv1 response: ");
               for(int i = 0; i < 8; i++)
               {
                   PSPRINTF("%x ", (pu8linSduPtr[0][i]));
               }
               PSPRINTF("\r\n");
               break;
           }
           else
           {
               if (ulGetStatusTimeout > 0)
               {
                   ulGetStatusTimeout--;
                   (void)delay_ms(10);
               }
               else
               {
                   PSPRINTF("[lin_0332]LIN1 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
                   return;
               }
           }
       } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
}



#endif
// extern boolean TesterDemoLIN;
// static uint32 lin_case_id_10ms = 0U;
// static uint32 lin_case_id_20ms = 0U;
// static uint32 lin_case_id_30ms = 0U;
// static uint32 lin_case_id_main = 0U;

// void LIN_GPT_Callback_30ms_Function()
// {
//     switch (lin_case_id_30ms)
//     {
//     case 1:
//     {
//     	lin_case_id_30ms = 0;
//     	TSC_Lin_0333_1(&LinGlobalConfig);
//         break;
//     }
//     default:
//         break;
//     }
// }



// Slave
void TSC_Lin_0066_0071(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0067
    Lin_Init(LinDriverConfig);
    PSPRINTF("[Lin_0067] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    // Lin_0068
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0068] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0068] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    // Lin_0069
    u8Lin_ReturnValue = Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0069] Lin_GoToSleepInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0069] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    // Lin_0070
    u8Lin_ReturnValue = Lin_WakeupInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0070] Lin_WakeupInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0070] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    // Lin_0071
    u8Lin_ReturnValue = Lin_GoToSleepInternal(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
    PSPRINTF("[Lin_0071] Lin_GoToSleepInternal u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
    PSPRINTF("[Lin_0071] Lin Channel%d state: %d\r\n", \
            LinDriverConfig->pLin_Channel[0]->u8LinChannelID,\
            u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
}

/*
LinChannelId: 0
BaudRate: 9600
BreakLength: 13
LinHwChannel: 0
LinNodeType: SLAVE
*/
void TSC_Lin_0080_0084(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0081
    Lin_Init(LinDriverConfig);

    // Lin_0082
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0082]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0082] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0082] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    }
}

/*
LinChannelId: 1
BaudRate: 19.2K
BreakLength: 13
LinHwChannel: 1
LinNodeType: SLAVE
*/
void TSC_Lin_0093_0098(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0094
    Lin_Init(LinDriverConfig);

    // Lin_0096
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[1]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0096]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0096] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0096] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[1]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[1]->u8LinHwChannel]);
    }

}



/*
LinChannelId: 3
BaudRate: 19.2K
BreakLength: 20
LinHwChannel: 14
LinNodeType: SLAVE
*/
void TSC_Lin_0107_0112(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0108
    Lin_Init(LinDriverConfig);

    // Lin_0110
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[2]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0110]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0110] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0110] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[2]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[2]->u8LinHwChannel]);
    }
}

/*
LinChannelId: 4
BaudRate: 19.2K
BreakLength: 21
LinHwChannel: 15
LinNodeType: SLAVE
*/
void TSC_Lin_0126_0130(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0127
    Lin_Init(LinDriverConfig);

    // Lin_0128
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[3]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0128]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0128] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0128] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[3]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[3]->u8LinHwChannel]);
    }
}
/*
LinChannelId: 2
BaudRate: 19.2K
BreakLength: 22
LinHwChannel: 2
LinNodeType: SLAVE
*/
void TSC_Lin_0139_0143(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0140
    Lin_Init(LinDriverConfig);

    // Lin_0141
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[4]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0141]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0141] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0141] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[4]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[4]->u8LinHwChannel]);
    }
}

void TSC_Lin_0167_0172(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0169
    Lin_Init(LinDriverConfig);

    // Lin_0170
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0170]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0170] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0170] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    }
}

/*
LinChannelId: 0
BaudRate: 9600
BreakLength: 13
LinHwChannel: 0
LinNodeType: SLAVE
*/
extern Lin_PduType linslvPduInfoTable[5];
void TSC_Lin_0181_0185(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;
    PRINTF_FUNCNAME();

    // Lin_0182
    Lin_Init(LinDriverConfig);

    // Lin_0183
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0183]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0183] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0183] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[0]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[0]->u8LinHwChannel]);
    }
    //Lin_0184
    linslvPduInfoTable[0].Drc = LIN_FRAMERESPONSE_IGNORE;
    //Lin_0185
    linslvPduInfoTable[1].Drc = LIN_FRAMERESPONSE_IGNORE;

}

void TSC_Lin_0196_0200(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0197
    Lin_Init(LinDriverConfig);

    // Lin_0198
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[5]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0198]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0198] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0198] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[5]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[5]->u8LinHwChannel]);
    }
}

void TSC_Lin_0209_0213(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0210
    Lin_Init(LinDriverConfig);

    // Lin_0211
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[6]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0211]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0211] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0211] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[6]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[6]->u8LinHwChannel]);
    }
}

void TSC_Lin_0222_0226(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0223
    Lin_Init(LinDriverConfig);

    // Lin_0224
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[7]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0224]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0224] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0224] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[7]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[7]->u8LinHwChannel]);
    }
}

void TSC_Lin_0235_0239(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0236
    Lin_Init(LinDriverConfig);

    // Lin_0237
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[8]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0237]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0237] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0237] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[8]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[8]->u8LinHwChannel]);
    }
}

void TSC_Lin_0248_0252(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0249
    Lin_Init(LinDriverConfig);

    // Lin_0250
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[9]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0250]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0250] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0250] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[9]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[9]->u8LinHwChannel]);
    }
}

void TSC_Lin_0261_0265(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0262
    Lin_Init(LinDriverConfig);

    // Lin_0263
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[10]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0263]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0263] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0263] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[10]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[10]->u8LinHwChannel]);
    }
}

void TSC_Lin_0274_0278(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0275
    Lin_Init(LinDriverConfig);

    // Lin_0276
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[11]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0276]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0276] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0276] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[11]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[11]->u8LinHwChannel]);
    }
}

void TSC_Lin_0287_0291(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0288
    Lin_Init(LinDriverConfig);

    // Lin_0289
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[12]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0289]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0289] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0289] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[12]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[12]->u8LinHwChannel]);
    }
}

void TSC_Lin_0300_0304(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0301
    Lin_Init(LinDriverConfig);

    // Lin_0302
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[13]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0302]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0302] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0302] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[13]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[13]->u8LinHwChannel]);
    }
}

void TSC_Lin_0313_0317(const Lin_ConfigType *LinDriverConfig)
{
    Std_ReturnType u8Lin_ReturnValue;PRINTF_FUNCNAME();

    // Lin_0314
    Lin_Init(LinDriverConfig);

    // Lin_0315
    u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[14]->u8LinChannelID);

    if (u8Lin_ReturnValue != E_OK)
    {
        PSPRINTF("[Lin_0315]LIN Error %d returned by Lin_WakeUp(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
        return;
    }else
    {
        PSPRINTF("[Lin_0315] Lin_Wakeup u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
        PSPRINTF("[Lin_0315] Lin Channel%d state: %d\r\n", LinDriverConfig->pLin_Channel[14]->u8LinChannelID, \
                u8Lin_ChStatus[LinDriverConfig->pLin_Channel[14]->u8LinHwChannel]);
    }
}

// void TSC_Lin_0333_1(const Lin_ConfigType *LinDriverConfig)
// {
//     VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
//     Std_ReturnType u8Lin_ReturnValue;
//     PRINTF_FUNCNAME();
//     pu8linSduPtr[0] = linSdu;

//     // Lin_0333_1_1
//     //Lin_Init(LinDriverConfig);

//     // Lin_0333_1_2
//     u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[0]->u8LinChannelID);
//     if (u8Lin_ReturnValue != E_OK)
//     {
//         PSPRINTF("[Lin_0333_1_2]LIN Error %d returned by Lin_WakeUp0(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
//         return;
//     }
//     else
//     {
//         PSPRINTF("[Lin_0333_1_2] Lin_Wakeup0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//     }
//     // Lin_0333_1_3
//     u8Lin_ReturnValue = u8Lin_ChStatus[2];
//     if (u8Lin_ReturnValue != LIN_CH_OPERATIONAL)
//     {
//         PSPRINTF("[Lin_0333_1_3]LIN Error %d returned by Lin_WakeUp2(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
//         return;
//     }
//     else
//     {
//         PSPRINTF("[Lin_0333_1_3] Lin_Wakeup2 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//     }

//     ///////////////////////////////////////////////////////////////

//     PSPRINTF("\r\n---------LIN_FRAMERESPONSE_TX-----------------\r\n");

//     // lin_0333_1_4
//     u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[0]);
//     if (u8Lin_ReturnValue != E_OK)
//     {
//         PSPRINTF("[lin_0333_1_4]LIN Error %d returned by Lin_SendFrame0\n", u8Lin_ReturnValue);
//         return;
//     }else
//     {
//         PSPRINTF("[lin_0333_1_4] Lin_SendFrame0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//     }

//     //Lin_0333_1_5
//     ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
//     do
//     {
//         u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
//         if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
//         {
//             PSPRINTF("[Lin_0333_1_5] Lin_GetStatus0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//             break;
//         }
//         else
//         {
//             if (ulGetStatusTimeout > 0)
//             {
//                 (void)delay_ms(1);
//                 ulGetStatusTimeout--;
//             }
//             else
//             {
//                 PSPRINTF("[Lin_00333_1_5]LIN0 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
//                 return;
//             }
//         }
//     } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);


//     (void)delay_ms(500);

//         PSPRINTF("\r\n---------LIN_FRAMERESPONSE_RX-----------------\r\n");
//     // lin_0333_1_6
//     u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, &linPduInfo[1]);
//     if (u8Lin_ReturnValue != E_OK)
//     {
//         PSPRINTF("[lin_0333_1_6]LIN Error %d returned by Lin_SendFrame0\n", u8Lin_ReturnValue);
//         return;
//     }
//     else
//     {
//         PSPRINTF("[lin_0333_1_6] Lin_SendFrame0 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//     }

//     // lin_0333_1_7
//     ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
//     do
//     {
//         u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[0]->u8LinChannelID, pu8linSduPtr);
//         if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
//         {
//             PSPRINTF("[lin_0333_1_7] recv0 response: ");
//             for(int i = 0; i < 8; i++)
//             {
//                 PSPRINTF("%x ", (pu8linSduPtr[0][i]));
//             }
//             PSPRINTF("\r\n");
//             break;
//         }
//         else
//         {
//             if (ulGetStatusTimeout > 0)
//             {
//                 ulGetStatusTimeout--;
//                 (void)delay_ms(10);
//             }
//             else
//             {
//                 PSPRINTF("[lin_0333_1_7]LIN0 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
//                 return;
//             }
//         }
//     } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
// }

// void TSC_Lin_0333_2(const Lin_ConfigType *LinDriverConfig)
// {
//     VAR(uint8, AUTOMATIC) *pu8linSduPtr[1];
//    Std_ReturnType u8Lin_ReturnValue;
//    PRINTF_FUNCNAME();
//    pu8linSduPtr[0] = linSdu;

//     // Lin_0333_2_1
//     //Lin_Init(LinDriverConfig);

//     // Lin_0333_2_2
//     u8Lin_ReturnValue = Lin_Wakeup(LinDriverConfig->pLin_Channel[1]->u8LinChannelID);
//     if (u8Lin_ReturnValue != E_OK)
//     {
//         PSPRINTF("[Lin_0333_2_2]LIN Error %d returned by Lin_WakeUp1(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
//         return;
//     }
//     else
//     {
//         PSPRINTF("[Lin_0333_2_2] Lin_Wakeup1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//     }
//     // Lin_0333_2_3
// 	u8Lin_ReturnValue = u8Lin_ChStatus[14];
// 	if (u8Lin_ReturnValue != LIN_CH_OPERATIONAL)
// 	{
// 		PSPRINTF("[Lin_0333_2_3]LIN Error %d returned by Lin_WakeUp3(LIN_LOGICAL_CHANNEL)\n", u8Lin_ReturnValue);
// 		return;
// 	}
// 	else
// 	{
// 		PSPRINTF("[Lin_0333_2_3] Lin_Wakeup3 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
// 	}


// ///////////////////////////////////////////////////////////////

// 	PSPRINTF("\r\n---------LIN_FRAMERESPONSE_TX-----------------\r\n");

//    // lin_0333_2_4
//    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, &linPduInfo[2]);
//    if (u8Lin_ReturnValue != E_OK)
// 	{
// 		PSPRINTF("[lin_0333_2_4]LIN Error %d returned by Lin_SendFrame1\n", u8Lin_ReturnValue);
// 		return;
// 	}else
// 	{
// 		PSPRINTF("[lin_0333_2_4] Lin_SendFrame1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
// 	}

//    ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
//    //Lin_0333_2_5
//    do
//       {
//           u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
//           if (u8Lin_ReturnValue == LIN_TX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // send success
//           {
//               PSPRINTF("[Lin_0333_2_5] Lin_GetStatus1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
//               break;
//           }
//           else
//           {
//               if (ulGetStatusTimeout > 0)
//               {
//                   (void)delay_ms(1);
//                   ulGetStatusTimeout--;
//               }
//               else
//               {
//                   PSPRINTF("[Lin_0333_2_5]LIN1 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
//                   return;
//               }
//           }
//       } while (u8Lin_ReturnValue != LIN_TX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);

//    (void)delay_ms(500);



// 	PSPRINTF("\r\n---------LIN_FRAMERESPONSE_RX-----------------\r\n");
//    // lin_0333_2_6
//    u8Lin_ReturnValue = Lin_SendFrame(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, &linPduInfo[3]);
//    if (u8Lin_ReturnValue != E_OK)
// 	{
// 		PSPRINTF("[lin_0333_2_6]LIN Error %d returned by Lin_SendFrame1\n", u8Lin_ReturnValue);
// 		return;
// 	}
// 	else
// 	{
// 		PSPRINTF("[lin_0333_2_6] Lin_SendFrame1 u8Lin_ReturnValue = %d\r\n", u8Lin_ReturnValue);
// 	}

// // lin_0333_2_7
//        ulGetStatusTimeout = LIN_GETSTATUS_TIMEOUT;
//        do
//        {
//            u8Lin_ReturnValue = Lin_GetStatus(LinDriverConfig->pLin_Channel[1]->u8LinChannelID, pu8linSduPtr);
//            if (u8Lin_ReturnValue == LIN_RX_OK || u8Lin_ReturnValue == LIN_OPERATIONAL) // recvive success
//            {
//                PSPRINTF("[lin_0333_2_7] recv1 response: ");
//                for(int i = 0; i < 8; i++)
//                {
//                    PSPRINTF("%x ", (pu8linSduPtr[0][i]));
//                }
//                PSPRINTF("\r\n");
//                break;
//            }
//            else
//            {
//                if (ulGetStatusTimeout > 0)
//                {
//                    ulGetStatusTimeout--;
//                    (void)delay_ms(10);
//                }
//                else
//                {
//                    PSPRINTF("[lin_0333_2_7]LIN1 Error - transmission timeout : %d\n", u8Lin_ReturnValue);
//                    return;
//                }
//            }
//        } while (u8Lin_ReturnValue != LIN_RX_OK || u8Lin_ReturnValue != LIN_OPERATIONAL);
// }

// void TSC_Lin_0333()
// {
// 	TesterDemoLIN = 1;
//     lin_case_id_30ms = 1;
//     lin_case_id_main = 1;
//     TSC_Lin_0333_2(&LinGlobalConfig);
// }


int tsc_lin_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
        return 1;
    }

    static uint8 init_flag = 0;
    if (init_flag == 0)
    {
    	Lin_LLD_Init_IrqIsrEnable();
    	init_flag = 1;
    }

    if (argc == 2)
    {
        if (!strcmp(agrv[1], "help"))
        {
            PSPRINTF("irq ---------- CMD ------- Register/enable LIN interrupt numbers\n"\
                      "help ----- CMD ------- ID of the test case\r\n");
                    
            for(uint8 i = 0; i < LIN_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", lin_funcs[i].name);
            }
        }
        else
        {
            for(uint8 i = 0; i < LIN_TEST_CASE_MAX; i++)
            {
                if(!strcmp(agrv[1], lin_funcs[i].name))
                {
                    lin_funcs[i].linfunc(&LinGlobalConfig);
                    return 0;
                }
            }
            PSPRINTF("error: Input invalid parameters[%s], please Use the 'lin_test help' command to see the supported test instructions\n", agrv[1]);
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), lin_test , tsc_lin_func, deint or number of test case);
