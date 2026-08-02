#include "tester_dio.h"
#include <stdbool.h>
#include "console.h"
#include "Det.h"
#include "shell.h"
#include <string.h>
#define NULL_PTR ((void *)0)
#define DIO_TEST_CASE_MAX sizeof(dio_funcs) / sizeof(DiofuncMachine)

#define Dio_error_port 23
#define Dio_error_channel2 500



static DiofuncMachine dio_funcs[] = {
#if 0
    {"testdio0001", NULL},
    {"testdio0002", NULL},
    {"testdio0003", NULL},
    {"testdio0004", NULL},
    {"testdio0005", NULL},
    {"testdio0006", NULL},
    {"testdio0007", NULL},
    {"testdio0008", NULL},
    {"testdio0009", NULL},
    {"testdio0010", NULL},
    {"testdio0011", NULL},
    {"testdio0012", NULL},
    {"testdio0013", NULL},
    {"testdio0014", NULL},
    {"testdio0015", NULL},
    {"testdio0016", testdio0016},
    {"testdio0017", testdio0017},
    {"testdio0018", testdio0018},
    {"testdio0019", testdio0019},
    {"testdio0020", testdio0020},
    {"testdio0021", testdio0021},
    {"testdio0022", testdio0022},
    {"testdio0023", testdio0023},
    {"testdio0024", testdio0024},
    {"testdio0025", testdio0025},
    {"testdio0026", testdio0026},
    {"testdio0027", testdio0027},
    {"testdio0028", testdio0028},
    {"testdio0029", testdio0029},
    {"testdio0030", testdio0030},
    {"testdio0031", testdio0031},
    {"testdio0032", testdio0032},
    {"testdio0033", testdio0033},
    {"testdio0034", testdio0034},
    {"testdio0035", testdio0035},
    {"testdio0036", testdio0036},
    {"testdio0037", testdio0037},
    {"testdio0038", testdio0038},
    {"testdio0039", testdio0039},
    {"testdio0040", testdio0040},
    {"testdio0041", testdio0041},
    {"testdio0042", testdio0042},
    {"testdio0043", testdio0043},
    {"testdio0044", testdio0044},
    {"testdio0045", testdio0045},
    {"testdio0046", testdio0046},
    {"testdio0047", testdio0047},
    {"testdio0048", testdio0048},
    {"testdio0049", testdio0049},
    {"testdio0050", testdio0050},
    {"testdio0051", testdio0051},
    {"testdio0052", testdio0052},
    {"testdio0053", testdio0053},
    {"testdio0054", testdio0054},
    {"testdio0055", testdio0055},
    {"testdio0056", testdio0056},
    {"testdio0057", testdio0057},
    {"testdio0058", testdio0058},
    {"testdio0059", testdio0059},
    {"testdio0060", testdio0060},
    {"testdio0061", testdio0061},
    {"testdio0062", testdio0062},
    {"testdio0063", testdio0063},
    {"testdio0064", testdio0064},
#endif
	{"testdio0001", testdio0001},
	{"testdio0002", testdio0002},
	{"testdio0003", testdio0003},
	{"testdio0004", testdio0004},
	{"testdio0005", testdio0005},
	{"testdio0006", testdio0006},
	{"testdio0007", testdio0007},
	{"testdio0008", testdio0008},
};
#if 0
void testdio0016()  //Dio_WriteChannel 
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WriteChannel(Dio_error_channel2,STD_HIGH);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITECHANNEL_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_CHANNEL_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_CHANNEL_ID\n");
            PSPRINTF("testdio00016() is  ok\n");
        }else{
            PSPRINTF("testdio00016() is  not ok\n");
        }
    }
}

void testdio0017()  //Dio_WriteChannel
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WriteChannel(Dio_error_channel2,STD_LOW);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITECHANNEL_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_CHANNEL_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_CHANNEL_ID\n");
            PSPRINTF("testdio0017() is  ok\n");
        }else{
            PSPRINTF("testdio0017() is not ok\n");
        }
    }
}

void testdio0018()  //Dio_ReadChannel
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        (void)Dio_ReadChannel(Dio_error_channel2);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_READCHANNEL_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_CHANNEL_ID)
        {
                PSPRINTF("DIO_E_PARAM_INVALID_CHANNEL_ID\n");
                PSPRINTF("testdio0018() is  ok\n");
        }else{
            PSPRINTF("testdio0018() is not ok\n");
        }
    }
}

void testdio0019()  //Dio_WritePort
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WritePort(Dio_error_port,0xFFFF);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITEPORT_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_PORT_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_PORT_ID\n");
            PSPRINTF("testdio0019() is  ok\n");

        }else{
                PSPRINTF("testdio0019() is not ok\n");
             }
    }
}

void testdio0020()  //Dio_WritePort
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WritePort(Dio_error_port,0x0);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITEPORT_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_PORT_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_PORT_ID\n");
            PSPRINTF("testdio0020() is  ok\n");
        }else{
                PSPRINTF("testdio0020() is not ok\n");
             }
    }
}

void testdio0021()  //Dio_ReadPort
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        (void)Dio_ReadPort(Dio_error_port);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_READPORT_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_PORT_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_PORT_ID\n");
            PSPRINTF("testdio0021() is  ok\n");
        }else{
                PSPRINTF("testdio0021() is not ok\n");
            }
    }
}

void testdio0022()  //Dio_ReadChannelGroup
{
#if (DIO_VERSION_INFO_API == STD_ON)
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_GetVersionInfo(NULL_PTR);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_GETVERSIONINFO_ID) &&Det_ErrorId==DIO_E_PARAM_POINTER)
        {
            PSPRINTF("DIO_E_PARAM_POINTER\n");
            PSPRINTF("testdio0022() is  ok\n");
        }else{
            PSPRINTF("testdio0022() is not ok\n");
        }
    }
#else
    PSPRINTF("testdio0022() is NULL\n");
#endif
}

void testdio0023()  //Dio_WriteChannelGroup
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0,0x7);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITECHANNELGROUP_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_GROUP_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_GROUP_ID\n");
            PSPRINTF("testdio0023() is  ok\n");
        }else{
            PSPRINTF("testdio0023() is not ok\n");
        }
    }
}
void testdio0024()  //Dio_WriteChannelGroup
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0,0x7);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITECHANNELGROUP_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_GROUP_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_GROUP_ID\n");
            PSPRINTF("testdio0024() is  ok\n");
        }else{
            PSPRINTF("testdio0024() is not ok\n");
        }
    }
}
void testdio0025()  //Dio_WriteChannelGroup
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        Dio_WriteChannelGroup(NULL,0x7);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_WRITECHANNELGROUP_ID) &&Det_ErrorId==DIO_E_PARAM_POINTER)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_GROUP_ID\n");
            PSPRINTF("testdio0025() is  ok\n");
        }else{
            PSPRINTF("testdio0025() is not ok\n");
        }
    }
}

void testdio0026()  //Dio_ReadChannelGroup
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        (void)Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_READCHANNELGROUP_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_GROUP_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_GROUP_ID\n");
            PSPRINTF("testdio0026() is  ok\n");
        }else{
            PSPRINTF("testdio0026() is not ok\n");
        }
    }
}
void testdio0027()  //Dio_ReadChannelGroup
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        (void)Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_READCHANNELGROUP_ID) &&Det_ErrorId==DIO_E_PARAM_INVALID_GROUP_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_GROUP_ID\n");
            PSPRINTF("testdio0027() is  ok\n");
        }else{
            PSPRINTF("testdio0027() is not ok\n");
        }
    }
}
void testdio0028()  //Dio_ReadChannelGroup
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        (void)Dio_ReadChannelGroup(NULL);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_READCHANNELGROUP_ID) &&Det_ErrorId==DIO_E_PARAM_POINTER)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_GROUP_ID\n");
            PSPRINTF("testdio0028() is  ok\n");
        }else{
            PSPRINTF("testdio0028() is not ok\n");
        }
    }
}

void testdio0029()  //Dio_FlipChannel
{
    if(DIO_DEV_ERROR_DETECT==STD_ON)
    {
        testdio0030();
        (void)Dio_FlipChannel(Dio_error_channel2);
        if(Det_ModuleId == DIO_H_MODULE_ID && (Det_ApiId == DIO_FLIPCHANNEL_ID) &&Det_ErrorId== DIO_E_PARAM_INVALID_CHANNEL_ID)
        {
            PSPRINTF("DIO_E_PARAM_INVALID_CHANNEL_ID\n");
            PSPRINTF("testdio0029() is  ok\n");
        }else{
            PSPRINTF("testdio0029() is not ok\n");
        }
    }
}

void testdio0030()
{
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_c4,STD_HIGH);
}
void testdio0031()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c4,STD_LOW);

}

void testdio0032()
{
    int level=Dio_ReadChannel(DioConf_DioChannel_DioChannel_c4);
    if(level==1)
    {
        PSPRINTF("testdio0032 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0032 read low\n");
    }else{
        PSPRINTF("error\n");
    }
}
void testdio0033()
{
    int level =Dio_ReadChannel(DioConf_DioChannel_DioChannel_c4);
    if(level==1)
    {
        PSPRINTF("testdio0033 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0033 read  low\n");
    }else{
        PSPRINTF("error\n");
    }
}
void testdio0034()
{
    Dio_WritePort(DioConf_DioPort_DioPort_C,0xFFFF);
}

void testdio0035()
{
    Dio_WritePort(DioConf_DioPort_DioPort_C,STD_LOW);
}

void testdio0036()
{
    int port_level=Dio_ReadPort(DioConf_DioPort_DioPort_C);
    PSPRINTF("%d\n",port_level);
    if((port_level&0x0F00)==0x0F00)
    {
        PSPRINTF("testdio0036 read high\n");
    }
    else if((port_level&0x0F00)==0)
    {
        PSPRINTF("testdio0036 read low\n");
    }else{
        PSPRINTF("error\n");
    }
}
void testdio0037()
{
    int port_level =Dio_ReadPort(DioConf_DioPort_DioPort_C);
    PSPRINTF("port_level:%d\n",port_level);
    if((port_level&0x0F00)==0x0F00)
    {
        PSPRINTF("testdio0037 read high\n");
    }
    else if((port_level&0x0F00)==0x0)
    {
        PSPRINTF("testdio0037 read low\n");
    }else{
        PSPRINTF("error\n");
    }
}




void testdio0038()  //Dio_WriteChannelGroup
{
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0,0x3);
}
void testdio0039()  //Dio_WriteChannelGroup
{
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0,0x0);
}

void testdio0040()  //Dio_WriteChannelGroup
{
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0,0x3);
#ifdef DioConf_DioChannelGroup_DioChannelGroup_1
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_1,0x3);
#endif
}
void testdio0041()  //Dio_WriteChannelGroup
{
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0,0x0);
#ifdef DioConf_DioChannelGroup_DioChannelGroup_1
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_1,0x0);
#endif
}
void testdio0042()  //Dio_WriteChannelGroup
{
#ifdef DioConf_DioChannelGroup_DioChannelGroup_1
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_1,0x3);
#else
    PSPRINTF("testdio0042 is NULL\n");
#endif
}
void testdio0043()  //Dio_WriteChannelGroup
{
#ifdef DioConf_DioChannelGroup_DioChannelGroup_1
    Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_1,0x0);
#else
    PSPRINTF("testdio0043 is NULL\n");
#endif
}

void testdio0044()  //Dio_ReadChannelGroup
{
    int level_group=Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0);
    PSPRINTF("level_group:%d\n",level_group);
    if(level_group==0)
    {
        PSPRINTF("testdio0044 is low\n");
    }else{
        PSPRINTF("testdio0044 is high\n");
    }
}

void testdio0045()  //Dio_ReadChannelGroup
{
    int level_group=Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_0);
    PSPRINTF("level_group:%d\n",level_group);
    if(level_group==0)
    {
        PSPRINTF("testdio0045 is low\n");
    }else{
        PSPRINTF("testdio0045 is high\n");
    }
}
void testdio0046()  //Dio_ReadChannelGroup
{
#ifdef DioConf_DioChannelGroup_DioChannelGroup_1
    int level_group=Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_1);
    PSPRINTF("level_group:%d\n",level_group);
    if(level_group==0)
    {
        PSPRINTF("testdio0046 is low\n");
    }else{
        PSPRINTF("testdio0046 is high\n");
    }
#else
    PSPRINTF("testdio0046 is NULL\n");
#endif
}

void testdio0047()  //Dio_ReadChannelGroup
{
#ifdef DioConf_DioChannelGroup_DioChannelGroup_1
    int level_group=Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_1);
    PSPRINTF("level_group:%d\n",level_group);
    if(level_group==0)
    {
        PSPRINTF("testdio0047 is low\n");
    }else{
        PSPRINTF("testdio0047 is high\n");
    }
#else
    PSPRINTF("testdio0047 is NULL\n");
#endif
}
void testdio0048()  //Dio_FlipChannel
{
#if (STD_ON == DIO_FLIP_CHANNEL_API)
    testdio0030();
    int levelFlip=Dio_FlipChannel(DioConf_DioChannel_DioChannel_c4);
    if(levelFlip==1)
    {
        PSPRINTF("testdio0048 read high\n");
    }
    else if(levelFlip==0)
    {
        PSPRINTF("testdio0048 read low\n");
    }else{
        PSPRINTF("error");
    }
#else
    PSPRINTF("testdio0048 NULL\n");
#endif
}

void testdio0049()  //Dio_FlipChannel
{
#if (STD_ON == DIO_FLIP_CHANNEL_API)
    testdio0031();
    int levelFlip=Dio_FlipChannel(DioConf_DioChannel_DioChannel_c4);
    if(levelFlip==1)
    {
        PSPRINTF("testdio0049 read high\n");
    }
    else if(levelFlip==0)
    {
          PSPRINTF("testdio0049 read low\n");
    }else{
        PSPRINTF("error\n");
    }
#else
    PSPRINTF("testdio0049 NULL\n");
#endif
}



void testdio0050()  //Dio_MaskedWritePort
{
#if (STD_ON == DIO_MASKEDWRITEPORT_API)
    Dio_MaskedWritePort(DioConf_DioPort_DioPort_C,0xFFFF,0xFC00);
#else
    PSPRINTF("testdio0050 NULL\n");
#endif
}
void testdio0051()  //Dio_MaskedWritePort
{
#if (STD_ON == DIO_MASKEDWRITEPORT_API)
    Dio_MaskedWritePort(DioConf_DioPort_DioPort_C,0x0,0xFC00);
#else
    PSPRINTF("testdio0051 NULL\n");
#endif
}


void testdio0052()  //Dio_GetVersionInfo
{
#if (STD_ON == DIO_VERSION_INFO_API)
    Std_VersionInfoType versioninfo;
    Dio_GetVersionInfo(&versioninfo);
    PSPRINTF("vendorID[%d] moduleID[%d] sw_major_version[%d] sw_minor_version[%d] sw_patch_version[%d]\n",
        versioninfo.vendorID, versioninfo.moduleID, versioninfo.sw_major_version, versioninfo.sw_minor_version, versioninfo.sw_patch_version);
#else
    PSPRINTF("testdio0052 is NULL");
#endif
}

void testdio0053()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c5,STD_HIGH);
}
void testdio0054()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c5,STD_LOW);
}

void testdio0055()
{
    int level=Dio_ReadChannel(DioConf_DioChannel_DioChannel_c5);
    if(level==1)
    {
        PSPRINTF("testdio0055 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0055 read low\n");
    }else{
        PSPRINTF("error\n");
    }
}
void testdio0056()
{
    int level =Dio_ReadChannel(DioConf_DioChannel_DioChannel_c5);
    if(level==1)
    {
        PSPRINTF("testdio0056 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0056 read  low\n");
    }else{
        PSPRINTF("error\n");
    }
}

void testdio0057()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c6,STD_HIGH);
}
void testdio0058()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c6,STD_LOW);
}

void testdio0059()
{
    int level=Dio_ReadChannel(DioConf_DioChannel_DioChannel_c6);
    if(level==1)
    {
        PSPRINTF("testdio0059 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0059 read low\n");
    }else{
        PSPRINTF("error\n");
    }
}
void testdio0060()
{
    int level =Dio_ReadChannel(DioConf_DioChannel_DioChannel_c6);
    if(level==1)
    {
        PSPRINTF("testdio0060 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0060 read  low\n");
    }else{
        PSPRINTF("error\n");
    }
}

void testdio0061()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c7,STD_HIGH);
}
void testdio0062()
{
    Dio_WriteChannel(DioConf_DioChannel_DioChannel_c7,STD_LOW);
}

void testdio0063()
{
    int level=Dio_ReadChannel(DioConf_DioChannel_DioChannel_c7);
    if(level==1)
    {
        PSPRINTF("testdio0063 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0063 read low\n");
    }else{
        PSPRINTF("error\n");
    }
}
void testdio0064()
{
    int level =Dio_ReadChannel(DioConf_DioChannel_DioChannel_c7);
    if(level==1)
    {
        PSPRINTF("testdio0064 read high\n");
    }
    else if(level==0)
    {
        PSPRINTF("testdio0064 read  low\n");
    }else{
        PSPRINTF("error\n");
    }
}
#endif

#if 1

void testdio0001()
{
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_VBST_SD,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS17,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ERROR0,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB2_DIR,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_ICx_JTAG_TDI,STD_HIGH);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB3_HIZ,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS08,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS16,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB2_HIZ,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ADMUXB,STD_HIGH);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS_01,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS2,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS05,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS13,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB3_DIR,STD_HIGH);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS18,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS_02,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS3,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS_WDT,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HSS05,STD_HIGH);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS19,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS21,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS06,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ADMUXC,STD_HIGH);
	//Dio_WriteChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS07,STD_HIGH);//g

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS03,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS07,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS12,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS20,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS22,STD_HIGH);//g

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB1_DIR,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB1_HIZ,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ADMUXA,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS04,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HSS06,STD_HIGH);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HSS07,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS07_EN,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS11,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS1,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS4,STD_HIGH);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_ICx_JTAG_TDO,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_ICx_JTAG_TMS,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_MRLY,STD_HIGH);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS15,STD_HIGH);
}



void testdio0002()
{
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_VBST_SD,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS17,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ERROR0,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB2_DIR,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_ICx_JTAG_TDI,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB3_HIZ,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS08,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS16,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB2_HIZ,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ADMUXB,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS_01,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS2,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS05,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS13,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB3_DIR,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS18,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS_02,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS3,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS_WDT,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HSS05,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS19,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS21,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS06,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ADMUXC,STD_LOW);
	//Dio_WriteChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS07,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS03,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS07,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS12,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS20,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS22,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB1_DIR,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HB1_HIZ,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_ADMUXA,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS04,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HSS06,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_HSS07,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS07_EN,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS11,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS1,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_DIS4,STD_LOW);

	Dio_WriteChannel(DioConf_DioChannel_DioChannel_ICx_JTAG_TDO,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_ICx_JTAG_TMS,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_MRLY,STD_LOW);
	Dio_WriteChannel(DioConf_DioChannel_DioChannel_O_D_UC_LSS15,STD_LOW);
}

void testdio0003()
{
	int I_S_UC_DS08 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS08);
	int I_S_UC_DS03 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS03);
	int I_S_UC_DS09 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS09);
	int I_S_UC_DS18 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS18);
	int I_S_UC_DS00 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS00);
	int I_S_UC_DS01 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS01);


	int num = I_S_UC_DS08+I_S_UC_DS03+I_S_UC_DS09+I_S_UC_DS18+I_S_UC_DS00+I_S_UC_DS01;
		 PSPRINTF("num:%d\n",num);
		if(num==0)
		{
			PSPRINTF("all pin low\n");
		}
        else if(num==6)
        {
            PSPRINTF("all pin high\n");
		}else{
            PSPRINTF("error\n");
        }
}
void testdio0004()
{
	int I_S_UC_DS11 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS11);
	int I_S_UC_DS12 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS12);
	int I_S_UC_DS13 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS13);
	int I_S_UC_DS14 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS14);
	int I_S_UC_DS15 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS15);
	int I_S_UC_DS16 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS16);
	int I_S_UC_DS17 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS17);
	int I_S_UC_DS04 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS04);
	int I_S_UC_DS07 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS07);
	int num = I_S_UC_DS11+I_S_UC_DS12+I_S_UC_DS13+I_S_UC_DS14+I_S_UC_DS15+I_S_UC_DS16+I_S_UC_DS17+I_S_UC_DS04+I_S_UC_DS07;
	PSPRINTF("num:%d\n",num);
	if(num==0)
	{
		PSPRINTF("all pin low\n");
	}
    else if(num==9)
    {
           PSPRINTF("all pin high\n");
	}else{
           PSPRINTF("error\n");
    }
}
void testdio0005()
{
	int I_S_UC_DS10 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS10);
	int I_S_UC_DS05 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS05);
	int I_D_UC_nRST_DRV_REQ = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_nRST_DRV_REQ);
	int I_D_UC_WDT_DIS_REQ = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_WDT_DIS_REQ);
	int I_S_UC_DS02 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS02);
	int I_S_UC_DS06 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS06);

	int I_D_UC_KL15 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_KL15);
	int num = I_S_UC_DS10+I_S_UC_DS05+I_D_UC_nRST_DRV_REQ+I_D_UC_WDT_DIS_REQ+I_S_UC_DS02+I_S_UC_DS06+I_D_UC_KL15;
	PSPRINTF("num:%d\n",num);
	if(num==0)
	{
		PSPRINTF("all pin low\n");
	}
    else if(num==7)
    {
           PSPRINTF("all pin high\n");
	}else{
           PSPRINTF("error\n");
    }
}
void testdio0006()
{
	int I_S_UC_DS08 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS08);
	int I_S_UC_DS03 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS03);
	int I_S_UC_DS09 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS09);
	int I_S_UC_DS18 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS18);
	int I_S_UC_DS00 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS00);
	int I_S_UC_DS01 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS01);


	int num = I_S_UC_DS08+I_S_UC_DS03+I_S_UC_DS09+I_S_UC_DS18+I_S_UC_DS00+I_S_UC_DS01;
	PSPRINTF("num:%d\n",num);
	if(num==0)
	{
		PSPRINTF("all pin low\n");
	}
    else if(num==6)
    {
           PSPRINTF("all pin high\n");
	}else{
           PSPRINTF("error\n");
    }
}
void testdio0007()
{
	int I_S_UC_DS11 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS11);
	int I_S_UC_DS12 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS12);
	int I_S_UC_DS13 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS13);
	int I_S_UC_DS14 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS14);
	int I_S_UC_DS15 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS15);
	int I_S_UC_DS16 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS16);
	int I_S_UC_DS17 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS17);
	int I_S_UC_DS04 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS04);
	int I_S_UC_DS07 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS07);
	int num = I_S_UC_DS11+I_S_UC_DS12+I_S_UC_DS13+I_S_UC_DS14+I_S_UC_DS15+I_S_UC_DS16+I_S_UC_DS17+I_S_UC_DS04+I_S_UC_DS07;
	PSPRINTF("num:%d\n",num);
	if(num==0)
	{
		PSPRINTF("all pin low\n");
	}
    else if(num==9)
    {
           PSPRINTF("all pin high\n");
	}else{
           PSPRINTF("error\n");
    }
}
void testdio0008()
{
	int I_S_UC_DS10 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS10);
	int I_S_UC_DS05 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS05);
	int I_D_UC_nRST_DRV_REQ = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_nRST_DRV_REQ);
	int I_D_UC_WDT_DIS_REQ = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_WDT_DIS_REQ);
	int I_S_UC_DS02 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS02);
	int I_S_UC_DS06 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_S_UC_DS06);
	int I_D_UC_KL15 = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_KL15);
	int num = I_S_UC_DS10+I_S_UC_DS05+I_D_UC_nRST_DRV_REQ+I_D_UC_WDT_DIS_REQ+I_S_UC_DS02+I_S_UC_DS06+I_D_UC_KL15;
	PSPRINTF("num:%d\n",num);
	if(num==0)
	{
		PSPRINTF("all pin low\n");
	}
    else if(num==7)
    {
           PSPRINTF("all pin high\n");
	}else{
           PSPRINTF("error\n");
    }
}
#endif

int dio_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
        return 1;
    }

    if (argc == 2)
    {
        if (!strcmp(agrv[1], "help"))
        {
            PSPRINTF("help ----- CMD ------- ID of the test case\r\n");
                    
            for(uint8 i = 0; i < DIO_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", dio_funcs[i].name);
            }
        }
        else
        {
                uint32 id = (uint32)atoi(agrv[1]);
                PSPRINTF("%d\r\n", id);
                if((id >= 1) && (id <=DIO_TEST_CASE_MAX))
                {
                    if (dio_funcs[id - 1].diofunc != NULL_PTR)
                    {
                        dio_funcs[id - 1].diofunc();
                    }
                    else if(dio_funcs[id].diofunc==NULL)
                    {
                        PSPRINTF("error: Test case is undefined\n");
                        return 0;
                    }
                    else
                    {
                        PSPRINTF("error: The ID entered does not correspond to the test code\n");
                    }
                }
                 else
                {
                    PSPRINTF("error: Input invalid parameters[%d], please output [1 - %d] range parameters\n", id, DIO_TEST_CASE_MAX);
                }}
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), dio_test, dio_func, deint or number of test case);






