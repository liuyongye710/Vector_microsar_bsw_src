#include "Port.h"
#include "Port_Cfg.h"
#include "Det.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "tester_port.h"
#include "shell.h"

#define NULL ((void *)0)

Std_VersionInfoType versioninfo;
static PortfuncMachine port_test_funcs[] = {
        {"port_test_0000", NULL},
        {"port_test_0001", NULL},
        {"port_test_0002", NULL},
        {"port_test_0003", NULL},
        {"port_test_0004", NULL},
        {"port_test_0005", NULL},
        {"port_test_0006", NULL},
        {"port_test_0007", NULL},
        {"port_test_0008", NULL},
        {"port_test_0009", NULL},
        {"port_test_0010", NULL},
        {"port_test_0011", NULL},
        {"port_test_0012", NULL},
        {"port_test_0013", NULL},
        {"port_test_0014", NULL},
        {"port_test_0015", NULL},
        {"port_test_0016", NULL},
        {"port_test_0017", NULL},
        {"port_test_0018", NULL},
        {"port_test_0019", NULL},
        {"port_test_0020", port_test_0020},
        {"port_test_0021", port_test_0021},
        {"port_test_0022", port_test_0022},
        {"port_test_0023", port_test_0023},
        {"port_test_0024", port_test_0024},
        {"port_test_0025", port_test_0025},
        {"port_test_0026", port_test_0026},
        {"port_test_0027", port_test_0027},
        {"port_test_0028", port_test_0028}
};

void port_test_0020(void)
{
    Det_ModuleId=0;
    Port_Init(NULL);                      //设置Port_Init无效参数
    if ((Det_ModuleId == PORT_MODULE_ID && Det_ErrorId==PORT_E_INIT_FAILED)){
        PSPRINTF("PORT_0020 is ok\n");
        PSPRINTF("Det_ErrorId: PORT_E_INIT_FAILED\n\n");
    } else {
        PSPRINTF("PORT_0020 is not ok\n\n");
    }
}

void port_test_0021(void)
{
    Det_ModuleId=0;
    //Port_Init(&PortContainer);                      //设置Port_Init有效参数
    if ((Det_ModuleId != PORT_MODULE_ID)){
        PSPRINTF("PORT_0021 is ok\n\n");
    } else {
        PSPRINTF("PORT_0021 is not ok\n\n");
    }
}

void port_test_0022(void)
{
    Det_ModuleId=0;
    Port_SetPinDirection(0xFFFFFFFF,PORT_PIN_OUT);  //设置Pin参数超出范围
    if ((Det_ModuleId == PORT_MODULE_ID && Det_ErrorId==PORT_E_PARAM_PIN)){
        PSPRINTF("PORT_0022 is ok\n");
        PSPRINTF("Det_ErrorId: PORT_E_PARAM_PIN\n\n");
    } else {
        PSPRINTF("PORT_0022 is not ok\n\n");
    }
}

void port_test_0023(void)
{
    Det_ModuleId=0;
    Port_SetPinDirection(34,PORT_PIN_OUT);          //设置Port_SetPinDirection有效参数
    if ((Det_ModuleId != PORT_MODULE_ID)){
        PSPRINTF("PORT_0023 is ok\n\n");
    } else {
        PSPRINTF("PORT_0023 is not ok\n\n");
    }
}

void port_test_0024(void)
{
    Det_ModuleId=0;
    Port_RefreshPortDirection();                    //Port_RefreshPortDirection测试
    if ((Det_ModuleId != PORT_MODULE_ID)){
        PSPRINTF("PORT_0024 is ok\n\n");
    } else {
        PSPRINTF("PORT_0024 is not ok\n\n");
    }
}

void port_test_0025(void)
{
    Det_ModuleId=0;
    Port_GetVersionInfo(NULL);                      //Port_GetVersionInfo设置参数为NULL
    if ((Det_ModuleId == PORT_MODULE_ID && Det_ErrorId==PORT_E_PARAM_POINTER)){
        PSPRINTF("PORT_0025 is ok\n");
        PSPRINTF("Det_ErrorId: PORT_E_PARAM_POINTER\n\n");
    } else {
        PSPRINTF("PORT_0025 is not ok\n\n");
    }
}

void port_test_0026(void)
{
    Det_ModuleId=0;
    Port_GetVersionInfo(&versioninfo);              //Port_GetVersionInfo设置参数为有效参数
    if ((Det_ModuleId != PORT_MODULE_ID)){
        PSPRINTF("PORT_0026 is ok\n\n");
    } else {
        PSPRINTF("PORT_0026 is not ok\n\n");
    }
}

void port_test_0027(void)
{
    Det_ModuleId=0;
    Port_SetPinMode(0xFFFF,PORT51_SIUL2_GPIO);  //设置Pin参数超出范围
    if ((Det_ModuleId == PORT_MODULE_ID && Det_ErrorId==PORT_E_PARAM_PIN)){
        PSPRINTF("PORT_0027 is ok\n");
        PSPRINTF("Det_ErrorId: PORT_E_PARAM_PIN\n\n");
    } else {
        PSPRINTF("PORT_0027 is not ok\n\n");
    }
}

void port_test_0028(void)
{
    Det_ModuleId=0;
    Port_SetPinMode(34,PORT51_SIUL2_GPIO);          //设置 Port_SetPinMode设置为有效参数
    if ((Det_ModuleId != PORT_MODULE_ID)){
        PSPRINTF("PORT_0028 is ok\n\n");
    } else {
        PSPRINTF("PORT_0028 is not ok\n\n");
    }
}



//void port_app_0349(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0350(void)
//{
//    Port_SetPinMode(51,PORT51_SIUL2_GPIO);
//}
//
//void port_app_0351(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0352(void)
//{
//    Port_SetPinMode(51,PORT51_DSPI_4_SCK_4_IN_OUT);
//}
//
//void port_app_0353(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0354(void)
//{
//    Port_SetPinMode(51,PORT51_DSPI_2_SCK_2_IN_OUT);
//}
//
//void port_app_0355(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0356(void)
//{
//    Port_SetPinMode(51,PORT51_DSPI_4_CS1_4_OUT);
//}
//
//void port_app_0357(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0358(void)
//{
//    Port_SetPinMode(51,PORT51_GTM_TOM0_5_OUT);
//}
//
//void port_app_0359(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0360(void)
//{
//    Port_SetPinMode(51,PORT51_GTM_TOM2_5_OUT);
//}
//
//void port_app_0361(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0362(void)
//{
//    Port_SetPinMode(51,PORT51_GTM_ATOM2_5_OUT);
//}
//
//void port_app_0363(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0364(void)
//{
//    Port_SetPinMode(51,PORT51_GTM_ATOM3_5_OUT);
//}
//
//void port_app_0365(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0366(void)
//{
//    Port_SetPinMode(51,PORT51_GTM_TIM2_5_IN);
//}
//
//void port_app_0367(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_OUT);
//}
//
//void port_app_0368(void)
//{
//    Port_SetPinMode(51,PORT51_GTM_TIM3_5_IN);
//}
//
//void port_app_0369(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_IN);
//}
//
//void port_app_0370(void)
//{
//    Port_SetPinMode(51,PORT51_DSPI_C_SINC_SIN_2_IN);
//}
//
//void port_app_0371(void)
//{
//    Mcu_Init(&McuModuleConfiguration_0);
//    Port_Init(&PortContainer);
//    Port_SetPinDirection(51,PORT_PIN_IN);
//}
//
//void port_app_0372(void)
//{
//    Port_SetPinMode(51,PORT51_LINFlexD_7_LIN7RX_IN);
//}

int port_func(int argc, char *agrv[])
{
    if (argc!=2)
    {
        PSPRINTF("error: Parameter number error\n");
        return 0;
    }

    int id = (uint32)atoi(agrv[1]);

    if(id<0 || id>(sizeof(port_test_funcs)/sizeof(port_test_funcs[0]))-1)
    {
        PSPRINTF("error: Parameter out of range\n");
        return 0;
    }

    if(port_test_funcs[id].portfunc==NULL)
    {
        PSPRINTF("error: Test case is undefined\n");
        return 0;
    }

    port_test_funcs[id].portfunc();

    return 0;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), port_test, port_func, deint or number of test case);
