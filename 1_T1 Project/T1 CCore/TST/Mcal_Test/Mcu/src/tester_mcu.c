
#include "tester_mcu.h"
#include "intc_lld.h"
#include "console.h"
#include "Mcu.h"
#include "Mcu_Irq.h"
#include "Port.h"
#include "Gpt.h"
#include "StandardTypes.h"
#include "tester_gpt.h"
#include "Gpt_cfg.h"
#include "shell.h"
#include "Gpt_Stm_LLDriver.h"
#include "Gpt_Irq.h"
#include "Gpt_AUtoSAR_Wrapper.h"

extern CONST(Gpt_ConfigType, GPT_CONST) GptChannelConfigSet;
extern VAR(uint8, DET_VAR) Det_InstanceId;     /**< @brief DET instance ID*/
extern VAR(uint8, DET_VAR) Det_ApiId;          /**< @brief DET API ID*/
extern VAR(uint8, DET_VAR) Det_ErrorId;        /**< @brief DET Error ID*/
extern VAR(uint16, DET_VAR) Det_ModuleId;      /**< @brief DET module ID*/

#define GPT_RTC_CON_INSTANCE		13

void Mcu_100(void)
{
    int retVal = 0;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INIT_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_100 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_100 is NOT OK\n");
    }
}

void Mcu_101(void)
{
    int retVal = 0;
    Det_ErrorId = 0;
    Mcu_Init(NULL_PTR);

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INIT_ID || Det_ErrorId != MCU_E_PARAM_POINTER)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_101 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_101 is NOT OK\n");
    }
}

void Mcu_102(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
//    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitRamSection(0U);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITRAMSECTION_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    if(StdRet != E_NOT_OK)
    {
        retVal++;
    }
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_102 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_102 is NOT OK\n");
    }
}

void Mcu_103(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitRamSection(McuModuleConfiguration.NoRamSectionConfig);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITRAMSECTION_ID || Det_ErrorId != MCU_E_PARAM_RAMSECTION)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    if(StdRet != E_NOT_OK)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_103 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_103 is NOT OK\n");
    }
}

void Mcu_104(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
//    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitClock(0);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITCLOCK_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    if(StdRet != E_NOT_OK)
    {
        retVal++;
    }
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_104 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_104 is NOT OK\n");
    }
}

void Mcu_105(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitClock(McuModuleConfiguration.NoClockConfig);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITCLOCK_ID || Det_ErrorId != MCU_E_PARAM_CLOCK)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    if(StdRet != E_NOT_OK)
    {
        retVal++;
    }
    // Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_105 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_105 is NOT OK\n");
    }
}

void Mcu_106(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
//    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_DistributePllClock();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_DISTRIBUTEPLLCLOCK_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    if(StdRet != E_NOT_OK)
    {
        retVal++;
    }
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_106 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_106 is NOT OK\n");
    }
}


void Mcu_107(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_DistributePllClock();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_DISTRIBUTEPLLCLOCK_ID || Det_ErrorId != MCU_E_PLL_NOT_LOCKED)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    if(StdRet != E_NOT_OK)
    {
        retVal++;
    }
    // Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_107 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_107 is NOT OK\n");
    }
}


void Mcu_108(void)
{
    int retVal = 0;
    Mcu_PllStatusType pllStatus;
    pllStatus = Mcu_GetPllStatus();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETPLLSTATUS_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    if(pllStatus != MCU_PLL_STATUS_UNDEFINED)
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_108 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_108 is NOT OK\n");
    }
}

void Mcu_109(void)
{
    int retVal = 0;
    Mcu_ResetType Reset;
    Reset = Mcu_GetResetReason();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRESETREASON_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    if(Reset != MCU_RESET_UNDEFINED)
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_109 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_109 is NOT OK\n");
    }
}


void Mcu_110(void)
{
    int retVal = 0;
    Mcu_RawResetType Reset;
    Reset = Mcu_GetResetRawValue();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRESETRAWVALUE_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    if(Reset != 0xffffffffU)
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_110 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_110 is NOT OK\n");
    }
}


void Mcu_111(void)
{
    int retVal = 0;
    Mcu_PerformReset();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_PERFORMRESET_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_111 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_111 is NOT OK\n");
    }
}

void Mcu_112(void)
{
    int retVal = 0;
    Mcu_SetMode(0);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_SETMODE_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_112 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_112 is NOT OK\n");
    }
}


void Mcu_113(void)
{
    int retVal = 0;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_SetMode(McuModuleConfiguration.NoModeConfig);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_SETMODE_ID || Det_ErrorId != MCU_E_PARAM_MODE)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    // Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_113 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_113 is NOT OK\n");
    }
}



void Mcu_114(void)
{
    int retVal = 0;
    Det_ErrorId = 0;
    
    Mcu_GetVersionInfo(NULL_PTR);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETVERSIONINFO_ID || Det_ErrorId != MCU_E_PARAM_POINTER)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_114 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_114 is NOT OK\n");
    }
}


void Mcu_115(void)
{
    int retVal = 0;
    Mcu_RamStateType RamStatus;
    RamStatus = Mcu_GetRamState();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRAMSTATE_ID || Det_ErrorId != MCU_E_UNINIT)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }

    if(RamStatus != MCU_RAMSTATE_INVALID)
    {
        retVal++;
    }

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_115 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_115 is NOT OK\n");
    }
}


void Mcu_130(void)
{
    int retVal = 0;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_Init(&McuModuleConfiguration);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INIT_ID || Det_ErrorId != MCU_E_INIT_FAILED)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();

    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_130 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_130 is NOT OK\n");
    }
}


void Mcu_131(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitRamSection(0U);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITRAMSECTION_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    if(StdRet != E_OK)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();

    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_131 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_131 is NOT OK\n");
    }
}



void Mcu_132(void)
{
    int retVal = 0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitClock(0);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITCLOCK_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }

    if((uint32)MC_ME.GS.B.S_XOSC != (uint32)McuModuleConfiguration.Mcu_ClockConfigPtr[0].mode_configuration.clocksEnabled.xosc0)
    {
        retVal++;
    }
    if((uint32)MC_ME.GS.B.S_PLL0 != (uint32)McuModuleConfiguration.Mcu_ClockConfigPtr[0].mode_configuration.clocksEnabled.pll0)
    {
        retVal++;
    }
    if((uint32)MC_ME.GS.B.S_PLL1 != (uint32)McuModuleConfiguration.Mcu_ClockConfigPtr[0].mode_configuration.clocksEnabled.pll1)
    {
        retVal++;
    }
    if(StdRet != E_OK)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
//    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();

    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_132 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_132 is NOT OK\n");
    }
}



void Mcu_133(void)
{
    int retVal = 0;
    int i=0;
    Std_ReturnType StdRet;
    Det_ErrorId = 0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitClock(0);
    for(i=0;i<10000;i++)
    {
        ;
    }
    Mcu_DistributePllClock();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_DISTRIBUTEPLLCLOCK_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    if((uint32)MC_ME.GS.B.S_SYSCLK != (uint32)McuModuleConfiguration.Mcu_ClockConfigPtr[0].mode_configuration.sysclk)
    {
        retVal++;
    }

    if(StdRet != E_OK)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
//    Mcu_InitClock(0);
//    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
//    {
//       /* wait until all enabled PLLs are locked */
//    }
//    Mcu_DistributePllClock();

    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_133 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_133 is NOT OK\n");
    }
}



void Mcu_134(void)
{
    int retVal = 0;
    Mcu_PllStatusType pllStatus;
    Std_ReturnType StdRet;
    int i=0;
    Mcu_Init(&McuModuleConfiguration);
    StdRet = Mcu_InitClock(0);
    for(i=0;i<10000;i++)
    {
        ;
    }
    pllStatus = Mcu_GetPllStatus();

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETPLLSTATUS_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    if(StdRet != E_OK)
    {
        retVal++;
    }
    if(pllStatus != MCU_PLL_LOCKED)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
//    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_134 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_134 is NOT OK\n");
    }
}



void Mcu_135(void)
{
    int retVal = 0;
    Mcu_PllStatusType pllStatus;

    Mcu_Init(&McuModuleConfiguration);

    pllStatus = Mcu_GetPllStatus();

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETPLLSTATUS_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }

    if(pllStatus != MCU_PLL_UNLOCKED)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_135 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_135 is NOT OK\n");
    }
}


void Mcu_136(void)
{
    int retVal = 0;
    Mcu_ResetType Reset;
    Mcu_Init(&McuModuleConfiguration);
    Reset = Mcu_GetResetReason();

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRESETREASON_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }

    if(Reset != MCU_POWER_ON_RESET)
    {
        retVal++;
    }

    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_136 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_136 is NOT OK\n");
    }
}


void Mcu_137(void)
{
    int retVal = 0;
    Mcu_ResetType Reset;
    Mcu_Init(&McuModuleConfiguration);
    Reset = Mcu_GetResetReason();

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRESETREASON_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }

    if(Reset != MCU_EXT_POWER_ON_RESET)
    {
        retVal++;
    }

    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_137 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_137 is NOT OK\n");
    }
}


void Mcu_138(void)
{
    int retVal = 0;
    Mcu_RawResetType Reset;
    Mcu_Init(&McuModuleConfiguration);
    Reset = Mcu_GetResetRawValue();

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRESETRAWVALUE_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }

    if(Reset != 1U)
    {
        retVal++;
    }

    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_138 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_138 is NOT OK\n");
    }
}


void Mcu_139(void)
{
    int retVal = 0;
    Mcu_RawResetType Reset;
    Mcu_Init(&McuModuleConfiguration);
    Reset = Mcu_GetResetRawValue();

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRESETRAWVALUE_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }

    if(Reset != 2U)
    {
        retVal++;
    }

    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_139 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_139 is NOT OK\n");
    }
}


void Mcu_140(void)
{
    int i;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    for(i=0;i<80000000;i++);
    PSPRINTF("Mcu_PerformReset() Output once per second\n");
    Mcu_PerformReset();
}


void Mcu_141(void)
{
    int retVal = 0;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Mcu_SetMode(0);

    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_SETMODE_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    if(MC_ME.GS.B.S_CURRENT_MODE != McuModuleConfiguration.Mcu_ModeConfigPtr[0].Mcu_ChipMode)
    {
        retVal++;
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_141 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_141 is NOT OK\n");
    }
}



void Mcu_142(void)
{
    int retVal = 0;
    Mcu_RamStateType RamStatus;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    RamStatus = Mcu_GetRamState();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETRAMSTATE_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    if ((MEMU.ERR_FLAG.B.SR_CE == TRUE) || (MEMU.ERR_FLAG.B.F_UCE == TRUE))
    {
        if(RamStatus != MCU_RAMSTATE_INVALID)
        {
            retVal++;
        }
    }
    else
    {
        if(RamStatus != MCU_RAMSTATE_VALID)
        {
            retVal++;
        }
    }
    if(retVal == 0)
    {
        PSPRINTF("Mcu_142 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_142 is NOT OK\n");
    }
}



void Mcu_160(void)
{
    int retVal = 0;
    Mcu_Init(&McuModuleConfiguration);
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeIntrConfiguration.InvalidCfgIntEn_Core != MC_ME.IM.B.M_ICONF_CC)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeIntrConfiguration.InvalidCfgIntEn_Clock != MC_ME.IM.B.M_ICONF_CU)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeIntrConfiguration.InvalidCfgIntEn != MC_ME.IM.B.M_ICONF)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeIntrConfiguration.InvalidModeIntEn != MC_ME.IM.B.M_IMODE)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeIntrConfiguration.SafeModeIntEn != MC_ME.IM.B.M_SAFE)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeIntrConfiguration.ModeCompleteIntEn != MC_ME.IM.B.M_MTC)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_160 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_160 is NOT OK\n");
    }
}

void Mcu_161(void)
{
    int retVal = 0;
    Mcu_Init(&McuModuleConfiguration);
   if(McuModuleConfiguration.Mcu_CoreConfigPtr->Mcme_Cctrl1_Config != MC_ME.CCTL1.R)
   {
       retVal++;
   }
//    if(McuModuleConfiguration.Mcu_CoreConfigPtr->CoreMode_Z7_0.run0 != MC_ME.CCTL1.B.RUN0)
//    {
//        retVal++;
//    }
//    if(McuModuleConfiguration.Mcu_CoreConfigPtr->CoreMode_Z7_0.run1 != MC_ME.CCTL1.B.RUN1)
//    {
//        retVal++;
//    }
//    if(McuModuleConfiguration.Mcu_CoreConfigPtr->CoreMode_Z7_0.run2 != MC_ME.CCTL1.B.RUN2)
//    {
//        retVal++;
//    }
//    if(McuModuleConfiguration.Mcu_CoreConfigPtr->CoreMode_Z7_0.run3 != MC_ME.CCTL1.B.RUN3)
//    {
//        retVal++;
//    }
//    if(McuModuleConfiguration.Mcu_CoreConfigPtr->CoreMode_Z7_0.safe != MC_ME.CCTL1.B.SAFE)
//    {
//        retVal++;
//    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_161 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_161 is NOT OK\n");
    }
}


void Mcu_162(void)
{
    int retVal = 0;
    Mcu_Init(&McuModuleConfiguration);
    if(McuModuleConfiguration.Mcu_CoreConfigPtr->Mcme_Cctrl3_Config != MC_ME.CCTL3.R)
    {
        retVal++;
    }
   
    //Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_162 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_162 is NOT OK\n");
    }
}

void Mcu_163(void)
{
    int retVal = 0;
    Mcu_Init(&McuModuleConfiguration);
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeMe.halt0 != MC_ME.ME.B.HALT0)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeMe.stop0 != MC_ME.ME.B.STOP0)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeMe.run1 != MC_ME.ME.B.RUN1)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeMe.run2 != MC_ME.ME.B.RUN2)
    {
        retVal++;
    }
    if(McuModuleConfiguration.Mcu_McMeConfigPtr->McMeMe.run3 != MC_ME.ME.B.RUN3)
    {
        retVal++;
    }

//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_163 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_163 is NOT OK\n");
    }
}

void Mcu_164(void)
{
    int retVal = 0;
    uint32 u32Mcu_RamCounterLimit;
    uint32 u32Mcu_RamCounter;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitRamSection(0);
    P2CONST( Mcu_RamConfigType, AUTOMATIC, MCU_APPL_CONST) pMcu_RamConfigPtr = &McuModuleConfiguration.Mcu_RamConfigPtr[0];

    u32Mcu_RamCounterLimit = (uint32)( (pMcu_RamConfigPtr->Mcu_RamSize) \
                               / (pMcu_RamConfigPtr->Mcu_RamWriteSize) );
    for (u32Mcu_RamCounter = (uint32)0UL; (u32Mcu_RamCounter < u32Mcu_RamCounterLimit); u32Mcu_RamCounter++)
    {
        switch (pMcu_RamConfigPtr->Mcu_RamWriteSize)
        {
            case (uint8)1U:
            {
                if(((uint8 *)pMcu_RamConfigPtr->Mcu_RamBaseAddrPtr)[u32Mcu_RamCounter]\
                    != (uint8) pMcu_RamConfigPtr->Mcu_RamDefaultValue)
                {
                    retVal++;
                }
                break;
            }
            case (uint8)2U:
            {
                if(((uint16 *)pMcu_RamConfigPtr->Mcu_RamBaseAddrPtr)[u32Mcu_RamCounter]\
                    != (uint16) pMcu_RamConfigPtr->Mcu_RamDefaultValue)
                {
                    retVal++;
                }
                break;
            }
            case (uint8)4U:
            {
                if(((uint32 *)pMcu_RamConfigPtr->Mcu_RamBaseAddrPtr)[u32Mcu_RamCounter]\
                    != (uint32) pMcu_RamConfigPtr->Mcu_RamDefaultValue)
                {
                    retVal++;
                }
                break;
            }
            case (uint8)8U:
            {
                if(((uint64 *)pMcu_RamConfigPtr->Mcu_RamBaseAddrPtr)[u32Mcu_RamCounter]\
                    != (uint64) pMcu_RamConfigPtr->Mcu_RamDefaultValue)
                {
                    retVal++;
                }
                break;
            }
            default:
            {
                retVal++;
                break;
            }
        }
    }
//    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_164 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_164 is NOT OK\n");
    }
}


void Mcu_165(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    if(ClockConfig->cgmcsConfig.xosc0Config.startupDelay != XOSC.CTL.B.EOCV)
    {
        retVal++;
    }
    if(ClockConfig->cgmcsConfig.xosc0Config.bypassOption != XOSC.CTL.B.OSCBYP)
    {
        retVal++;
    }
    if(ClockConfig->cgmcsConfig.xosc0Config.Mcu_xoscInterruptEn != XOSC.CTL.B.M_OSC)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_165 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_165 is NOT OK\n");
    }
}

void Mcu_166(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    if(ClockConfig->cgmConfig.ac3_sc != MC_CGM.AC3_SC.B.SELCTL)
    {
        retVal++;
    }

//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_166 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_166 is NOT OK\n");
    }
}


void Mcu_167(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    if(ClockConfig->cgmConfig.ac4_sc != MC_CGM.AC4_SC.B.SELCTL)
    {
        retVal++;
    }

//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_167 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_167 is NOT OK\n");
    }
}


void Mcu_168(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    if(ClockConfig->cgmcsConfig.pll0Config.predivider != PLLDIG.PLL0DV.B.PREDIV)
    {
        retVal++;
    }
    if(ClockConfig->cgmcsConfig.pll0Config.mulFactorDiv != PLLDIG.PLL0DV.B.MFD)
    {
        retVal++;
    }
    if(ClockConfig->cgmcsConfig.pll0Config.phi0Divider != PLLDIG.PLL0DV.B.RFDPHI)
    {
        retVal++;
    }
    if(ClockConfig->cgmcsConfig.pll0Config.phi1Divider != PLLDIG.PLL0DV.B.RFDPHI1)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_168 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_168 is NOT OK\n");
    }
}

void Mcu_169(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);

    if(ClockConfig->cgmcsConfig.pll1Config.mulFactorDiv != PLLDIG.PLL1DV.B.MFD)
    {
        retVal++;
    }
    if(ClockConfig->cgmcsConfig.pll1Config.phi0Divider != PLLDIG.PLL1DV.B.RFDPHI)
    {
        retVal++;
    }

//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_169 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_169 is NOT OK\n");
    }
}


void Mcu_170(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);

    if(ClockConfig->cgmConfig.sc_dc0 != MC_CGM.SC_DC0.B.DIV)
    {
        retVal++;
    }
    if(ClockConfig->cgmConfig.sc_dc1 != MC_CGM.SC_DC1.B.DIV)
    {
        retVal++;
    }
    if(ClockConfig->cgmConfig.sc_dc2 != MC_CGM.SC_DC2.B.DIV)
    {
        retVal++;
    }
    if(ClockConfig->cgmConfig.sc_dc3 != MC_CGM.SC_DC3.B.DIV)
    {
        retVal++;
    }
    if(ClockConfig->cgmConfig.sc_dc4 != MC_CGM.SC_DC4.B.DIV)
    {
        retVal++;
    }
//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_170 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_170 is NOT OK\n");
    }
}



void Mcu_171(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);

//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();

    if(ClockConfig->mode_configuration.sysclk != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_171 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_171 is NOT OK\n");
    }
}



void Mcu_172(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);

//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();

    Mcu_SetMode(0);
    if(ModeConfig->Mcu_ChipMode == me_mc_drun_mode)
    {
        if(ModeConfig->Mcu_IRC_En != MC_ME.DRUN_MC.B.IRCON)
        {
             retVal++;
        }
        if(ModeConfig->Mcu_XOSC_En != MC_ME.DRUN_MC.B.XOSCON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL0_En != MC_ME.DRUN_MC.B.PLL0ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL1_En != MC_ME.DRUN_MC.B.PLL1ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_TargetClock != MC_ME.DRUN_MC.B.SYSCLK)
        {
            retVal++;
        }
    }
    else if(ModeConfig->Mcu_ChipMode >= me_mc_run0_mode && ModeConfig->Mcu_ChipMode <= me_mc_run3_mode)
    {
        if(ModeConfig->Mcu_IRC_En != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.IRCON)
        {
             retVal++;
        }
        if(ModeConfig->Mcu_XOSC_En != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.XOSCON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL0_En != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.PLL0ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL1_En != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.PLL1ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_TargetClock != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.SYSCLK)
        {
            retVal++;
        }
    }
    else if(ModeConfig->Mcu_ChipMode == me_mc_halt0_mode)
    {
        if(ModeConfig->Mcu_IRC_En != MC_ME.HALT0_MC.B.IRCON)
        {
             retVal++;
        }
        if(ModeConfig->Mcu_XOSC_En != MC_ME.HALT0_MC.B.XOSCON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL0_En != MC_ME.HALT0_MC.B.PLL0ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL1_En != MC_ME.HALT0_MC.B.PLL1ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_TargetClock != MC_ME.HALT0_MC.B.SYSCLK)
        {
            retVal++;
        }
    }
    else if(ModeConfig->Mcu_ChipMode == me_mc_stop0_mode)
    {
        if(ModeConfig->Mcu_IRC_En != MC_ME.STOP0_MC.B.IRCON)
        {
             retVal++;
        }
        if(ModeConfig->Mcu_XOSC_En != MC_ME.STOP0_MC.B.XOSCON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL0_En != MC_ME.STOP0_MC.B.PLL0ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_PLL1_En != MC_ME.STOP0_MC.B.PLL1ON)
        {
            retVal++;
        }
        if(ModeConfig->Mcu_TargetClock != MC_ME.STOP0_MC.B.SYSCLK)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_172 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_172 is NOT OK\n");
    }
}


void Mcu_173(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);

//    Mcu_Init(&McuModuleConfiguration);
    // Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();

    Mcu_SetMode(0);
    if(ModeConfig->Mcu_ChipMode == me_mc_drun_mode)
    {
        if(MC_ME.GS.B.S_IRC != MC_ME.DRUN_MC.B.IRCON)
        {
             retVal++;
        }
        if(MC_ME.GS.B.S_XOSC != MC_ME.DRUN_MC.B.XOSCON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL0 != MC_ME.DRUN_MC.B.PLL0ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL1 != MC_ME.DRUN_MC.B.PLL1ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_SYSCLK != MC_ME.DRUN_MC.B.SYSCLK)
        {
            retVal++;
        }
    }
    else if(ModeConfig->Mcu_ChipMode >= me_mc_run0_mode && ModeConfig->Mcu_ChipMode <= me_mc_run3_mode)
    {
        if(MC_ME.GS.B.S_IRC != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.IRCON)
        {
             retVal++;
        }
        if(MC_ME.GS.B.S_XOSC != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.XOSCON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL0 != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.PLL0ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL1 != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.PLL1ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_SYSCLK != MC_ME.RUN_MC[ModeConfig->Mcu_ChipMode - me_mc_run0_mode].B.SYSCLK)
        {
            retVal++;
        }
    }
    else if(ModeConfig->Mcu_ChipMode == me_mc_halt0_mode)
    {
        if(MC_ME.GS.B.S_IRC != MC_ME.HALT0_MC.B.IRCON)
        {
             retVal++;
        }
        if(MC_ME.GS.B.S_XOSC != MC_ME.HALT0_MC.B.XOSCON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL0 != MC_ME.HALT0_MC.B.PLL0ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL1 != MC_ME.HALT0_MC.B.PLL1ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_SYSCLK != MC_ME.HALT0_MC.B.SYSCLK)
        {
            retVal++;
        }
    }
    else if(ModeConfig->Mcu_ChipMode == me_mc_stop0_mode)
    {
        if(MC_ME.GS.B.S_IRC != MC_ME.STOP0_MC.B.IRCON)
        {
             retVal++;
        }
        if(MC_ME.GS.B.S_XOSC != MC_ME.STOP0_MC.B.XOSCON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL0 != MC_ME.STOP0_MC.B.PLL0ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_PLL1 != MC_ME.STOP0_MC.B.PLL1ON)
        {
            retVal++;
        }
        if(MC_ME.GS.B.S_SYSCLK != MC_ME.STOP0_MC.B.SYSCLK)
        {
            retVal++;
        }
    }
    else
    {
        retVal++;
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_173 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_173 is NOT OK\n");
    }
}

void Mcu_174(void)
{
    int retVal = 0;
    Std_VersionInfoType versionInfo;
    Mcu_GetVersionInfo(&versionInfo);
    if(versionInfo.moduleID != MCU_MODULE_ID)
    {
        retVal++;
    }
    if(versionInfo.vendorID != MCU_VENDOR_ID)
    {
        retVal++;
    }
    if(versionInfo.sw_major_version != MCU_AR_MAJOR_VER)
    {
        retVal++;
    }
    if(versionInfo.sw_minor_version != MCU_AR_MINOR_VER)
    {
        retVal++;
    }
    if(versionInfo.sw_patch_version != MCU_AR_PATCH_VER)
    {
        retVal++;
    }
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_174 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_174 is NOT OK\n");
    }
}

void Mcu_175(void)
{
    int retVal = 0;
    Mcu_RamStateType RamStatus;
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    RamStatus = Mcu_GetRamState();
    if ((MEMU.ERR_FLAG.B.SR_CE == TRUE) || (MEMU.ERR_FLAG.B.F_UCE == TRUE))
    {
        if(RamStatus != MCU_RAMSTATE_INVALID)
        {
            retVal++;
        }
    }
    else
    {
        if(RamStatus != MCU_RAMSTATE_VALID)
        {
            retVal++;
        }
    }
    if(retVal == 0)
    {
        PSPRINTF("Mcu_175 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_175 is NOT OK\n");
    }
}

void Mcu_176(void)
{
    int retVal = 0;
    Mcu_ResetType Reset;

    uint32 des;
    uint32 fes;

    des = (MC_RGM.DES.R & RGM_DES_RWBITS_MASK32);
    fes = (MC_RGM.FES.R & RGM_FES_RWBITS_MASK32);

    uint32 Index = 0U;
    uint32 ResetOffset = 0U;
    uint32 Count = 0U;

    for(Index = (uint32)0x00U; Index < (uint32)0x20U; Index++)
    {
        if((((uint32)0x01U << Index) & RGM_DES_RWBITS_MASK32) != 0U)
        {
            if((des & (( uint32)0x01U << Index)) != 0U)
            {
                if(Count == (uint32)0U)
                {
                    Reset = (Mcu_ResetType) ResetOffset;
                    Count++;
                }
                else
                {
                    Reset = (Mcu_ResetType) MCU_MULTIPLE_RESET_REASON;
                    break;
                }
            }
            ResetOffset++;
        }
    }

    for(Index = (uint32)0x00U; Index < (uint32)0x20U; Index++)
    {
        if((((uint32)0x01U << Index) & RGM_FES_RWBITS_MASK32) != 0U)
        {
            if((fes & (( uint32)0x01U << Index)) != 0U)
            {
                if(Count == (uint32)0U)
                {
                    Reset = (Mcu_ResetType) ResetOffset;
                    Count++;
                }
                else
                {
                    Reset = (Mcu_ResetType) MCU_MULTIPLE_RESET_REASON;
                    break;
                }
            }
            ResetOffset++;
        }
    }

    Mcu_Init(&McuModuleConfiguration);

    if(Reset != Mcu_GetResetReason())
    {
        retVal++;
    }


    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();

    if(retVal == 0)
    {
        PSPRINTF("Mcu_176 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_176 is NOT OK\n");
    }
}

void Mcu_177(void)
{
    int retVal = 0;
    Mcu_RawResetType Reset;

    uint32 des;
    uint32 fes;

    des = (MC_RGM.DES.R & RGM_DES_RWBITS_MASK32);
    fes = (MC_RGM.FES.R & RGM_FES_RWBITS_MASK32);

    uint32 Index = 0U;
    uint32 ResetOffset = 0U;
    uint32 Count = 0U;

    for(Index = (uint32)0x00U; Index < (uint32)0x20U; Index++)
    {
        if((((uint32)0x01U << Index) & RGM_DES_RWBITS_MASK32) != 0U)
        {
            if((des & (( uint32)0x01U << Index)) != 0U)
            {
                Reset |= ((uint32)0x01U << ResetOffset);
            }
            ResetOffset++;
        }
    }
    for(Index = (uint32)0x00U; Index < (uint32)0x20U; Index++)
    {
        if((((uint32)0x01U << Index) & RGM_FES_RWBITS_MASK32) != 0U)
        {
            if((fes & (( uint32)0x01U << Index)) != 0U)
            {
                Reset |= ((uint32)0x01U << ResetOffset);
            }
            ResetOffset++;
        }
    }

    Mcu_Init(&McuModuleConfiguration);

    if(Reset != Mcu_GetResetRawValue())
    {
        retVal++;
    }


    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_177 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_177 is NOT OK\n");
    }
}


void Mcu_200(void)
{
    int retVal = 0;
    Mcu_Init(&McuModuleConfiguration);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INIT_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    Mcu_InitClock(0);
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_INITCLOCK_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_GETPLLSTATUS_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    Mcu_DistributePllClock();
    if(Det_ModuleId == MCU_MODULE_ID && Det_ErrorId != 0)
    {
        if(Det_InstanceId != MCU_INSTANCE_ID || Det_ApiId != MCU_DISTRIBUTEPLLCLOCK_ID || Det_ErrorId != 0)
        {
            retVal++;
        }
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_200 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_200 is NOT OK\n");
    }
}


void Mcu_201(void)
{
    int retVal = 0;
    Mcu_PllStatusType PllStatus;
    Mcu_Init(&McuModuleConfiguration);
    PllStatus = Mcu_GetPllStatus();
    if(PllStatus != MCU_PLL_UNLOCKED)
    {
        retVal++;
    }
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    PllStatus = Mcu_GetPllStatus();
    if(PllStatus != MCU_PLL_LOCKED)
    {
        retVal++;
    }
    Mcu_DistributePllClock();
    PllStatus = Mcu_GetPllStatus();
    if(PllStatus != MCU_PLL_LOCKED)
    {
        retVal++;
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_201 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_201 is NOT OK\n");
    }
}


void Mcu_202(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    if(CGM_SYSTEM_CLOCK_SRC_IRCOSC != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    Mcu_InitClock(0);
    if(CGM_SYSTEM_CLOCK_SRC_IRCOSC != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    if(CGM_SYSTEM_CLOCK_SRC_IRCOSC != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    Mcu_DistributePllClock();
    if(ClockConfig->mode_configuration.sysclk != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_202 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_202 is NOT OK\n");
    }
}



void Mcu_203(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    Mcu_SetMode(0);
    if(ModeConfig->Mcu_ChipMode != MC_ME.GS.B.S_CURRENT_MODE)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_IRC_En != MC_ME.GS.B.S_IRC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_XOSC_En != MC_ME.GS.B.S_XOSC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL0_En != MC_ME.GS.B.S_PLL0)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL1_En != MC_ME.GS.B.S_PLL1)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_TargetClock != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    if(retVal == 0)
    {
        PSPRINTF("Mcu_203 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_203 is NOT OK\n");
    }
}


void Mcu_204(void)
{
    Mcu_ResetType Reset;
    int i;
    Mcu_Init(&McuModuleConfiguration);
    Reset = Mcu_GetResetReason();
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(Reset == MCU_SOFT_FUNC_RESET)
    {
        PSPRINTF("Mcu_204 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_204 is NOT OK\n");
    }
    for(i=0;i<80000000;i++);
    PSPRINTF("Mcu_PerformReset() Output once per second\n");
    Mcu_PerformReset();
}

// XOSC TEST
void Mcu_205(void)
{
    Intc_Init();
    INTC_LLD_Set_IRQ_Handle(INTR_ID_242, Mcu_Xosc_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_242, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_242);

    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
}

//MC_ME_IMTC
void Mcu_206(void)
{
    Intc_Init();
    INTC_LLD_Set_IRQ_Handle(INTR_ID_252, Mcu_ModeComplete_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_252, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_252);
    Mcu_Init(&McuModuleConfiguration);
}

//MC_ME_INVCONFIG
void Mcu_207(void)
{
    Intc_Init();
    INTC_LLD_Set_IRQ_Handle(INTR_ID_254, Mcu_InvalidConfig_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_254, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_254);
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_253, Mcu_InvalidMode_Isr);
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_253, 15);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_253);
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_251, Mcu_SafeMode_Isr);
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_251, 15);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_251);

    Mcu_Init(&McuModuleConfiguration);
    Mcu_SetMode(0);
}

//MC_ME_MODE
void Mcu_208(void)
{
    Intc_Init();
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_254, Mcu_InvalidConfig_Isr);
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_254, 15);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_254);
    INTC_LLD_Set_IRQ_Handle(INTR_ID_253, Mcu_InvalidMode_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_253, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_253);
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_251, Mcu_SafeMode_Isr);
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_251, 15);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_251);

    Mcu_Init(&McuModuleConfiguration);
    Mcu_SetMode(1);
}


void Mcu_209(void)
{
    Intc_Init();
    INTC_LLD_Set_IRQ_Handle(INTR_ID_488, Mcu_Fccu_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_488, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_488);
    Mcu_Init(&McuModuleConfiguration);
    Mcu_FccuInit();
    FCCU_LLD_SetRfFake(FCCU_FAILURE_CMU_0_OSC_CH_31);
}


void Mcu_210(void)
{
    Intc_Init();
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_478, Mcu_TemperatureError_Isr);
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_478, 15);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_478);
    INTC_LLD_Set_IRQ_Handle(INTR_ID_477, Mcu_VoltageError_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_477, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_477);
    INTC_LLD_Set_IRQ_Handle(INTR_ID_488, Mcu_Fccu_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_488, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_488);
    Mcu_Init(&McuModuleConfiguration);
    Mcu_FccuInit();
    FCCU_LLD_SetRfFake(FCCU_FAILURE_LVD_ERROR_CH_1);
}


void Mcu_211(void)
{
    Intc_Init();
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_478, Mcu_TemperatureError_Isr);
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_478, 15);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_478);
    INTC_LLD_Set_IRQ_Handle(INTR_ID_477, Mcu_VoltageError_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_477, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_477);
    INTC_LLD_Set_IRQ_Handle(INTR_ID_488, Mcu_Fccu_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_488, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_488);
    Mcu_Init(&McuModuleConfiguration);
    Mcu_FccuInit();
    FCCU_LLD_SetRfFake(FCCU_FAILURE_HVD_ERROR_CH_2);
}

void Mcu_212(void)
{
    Intc_Init();
    INTC_LLD_Set_IRQ_Handle(INTR_ID_488, Mcu_Fccu_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_488, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_488);
    Mcu_Init(&McuModuleConfiguration);
    Mcu_FccuInit();
    FCCU_LLD_SetRfFake(FCCU_FAILURE_FM_PLL_0_CH_29);
}

void Mcu_213(void)
{
    Intc_Init();
    INTC_LLD_Set_IRQ_Handle(INTR_ID_488, Mcu_Fccu_Isr);
    INTC_LLD_Set_IRQ_Priority(INTR_ID_488, 15);
    INTC_LLD_Set_IRQ_Enable(INTR_ID_488);
    Mcu_Init(&McuModuleConfiguration);
    Mcu_FccuInit();
    FCCU_LLD_SetRfFake(FCCU_FAILURE_FM_PLL_1_CH_30);
}

void Mcu_214(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    Mcu_SetMode(0);
    if(ModeConfig->Mcu_ChipMode != MC_ME.GS.B.S_CURRENT_MODE)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_IRC_En != MC_ME.GS.B.S_IRC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_XOSC_En != MC_ME.GS.B.S_XOSC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL0_En != MC_ME.GS.B.S_PLL0)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL1_En != MC_ME.GS.B.S_PLL1)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_TargetClock != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    if(retVal == 0)
    {
        PSPRINTF("Mcu_214 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_214 is NOT OK\n");
    }
}

void Mcu_215(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[1];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    Mcu_SetMode(1);
    if(ModeConfig->Mcu_ChipMode != MC_ME.GS.B.S_CURRENT_MODE)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_IRC_En != MC_ME.GS.B.S_IRC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_XOSC_En != MC_ME.GS.B.S_XOSC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL0_En != MC_ME.GS.B.S_PLL0)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL1_En != MC_ME.GS.B.S_PLL1)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_TargetClock != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    if(retVal == 0)
    {
        PSPRINTF("Mcu_215 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_215 is NOT OK\n");
    }
}

void Mcu_216(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[2];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    Mcu_SetMode(2);
    if(ModeConfig->Mcu_ChipMode != MC_ME.GS.B.S_CURRENT_MODE)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_IRC_En != MC_ME.GS.B.S_IRC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_XOSC_En != MC_ME.GS.B.S_XOSC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL0_En != MC_ME.GS.B.S_PLL0)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL1_En != MC_ME.GS.B.S_PLL1)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_TargetClock != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    if(retVal == 0)
    {
        PSPRINTF("Mcu_216 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_216 is NOT OK\n");
    }
}

void Mcu_217(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[3];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    Mcu_SetMode(3);
    if(ModeConfig->Mcu_ChipMode != MC_ME.GS.B.S_CURRENT_MODE)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_IRC_En != MC_ME.GS.B.S_IRC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_XOSC_En != MC_ME.GS.B.S_XOSC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL0_En != MC_ME.GS.B.S_PLL0)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL1_En != MC_ME.GS.B.S_PLL1)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_TargetClock != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    if(retVal == 0)
    {
        PSPRINTF("Mcu_217 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_217 is NOT OK\n");
    }
}

void Mcu_218(void)
{
    int retVal = 0;
    Mcu_ModeConfigType *ModeConfig = &McuModuleConfiguration.Mcu_ModeConfigPtr[4];
    Mcu_Init(&McuModuleConfiguration);
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    Mcu_SetMode(4);
    if(ModeConfig->Mcu_ChipMode != MC_ME.GS.B.S_CURRENT_MODE)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_IRC_En != MC_ME.GS.B.S_IRC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_XOSC_En != MC_ME.GS.B.S_XOSC)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL0_En != MC_ME.GS.B.S_PLL0)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_PLL1_En != MC_ME.GS.B.S_PLL1)
    {
        retVal++;
    }
    if(ModeConfig->Mcu_TargetClock != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }

    if(retVal == 0)
    {
        PSPRINTF("Mcu_218 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_218 is NOT OK\n");
    }
}

void Mcu_219(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[0];
    Mcu_Init(&McuModuleConfiguration);
    if(CGM_SYSTEM_CLOCK_SRC_IRCOSC != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    Mcu_InitClock(0);
    if(CGM_SYSTEM_CLOCK_SRC_IRCOSC != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    if(CGM_SYSTEM_CLOCK_SRC_IRCOSC != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    Mcu_DistributePllClock();
    if(ClockConfig->mode_configuration.sysclk != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    Intc_Init();
    Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_219 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_219 is NOT OK\n");
    }
}

void Mcu_220(void)
{
	int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[1];
    Mcu_Init(&McuModuleConfiguration);

    Mcu_InitClock(0);

    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
        /* wait until all enabled PLLs are locked */
    }

    Mcu_DistributePllClock();
    Mcu_InitClock(1);
    if(ClockConfig->mode_configuration.sysclk != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
//    Intc_Init();
//    Console_Init();

    if(retVal == 0)
    {
        PSPRINTF("Mcu_220 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_220 is NOT OK\n");
    }
}

void Mcu_221(void)
{
    int retVal = 0;
    Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[2];
    Mcu_Init(&McuModuleConfiguration);

    Mcu_InitClock(0);

    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
        /* wait until all enabled PLLs are locked */
    }

    Mcu_DistributePllClock();
    Mcu_InitClock(1);
    Mcu_InitClock(2);

    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    if(ClockConfig->mode_configuration.sysclk != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
     Intc_Init();
     Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_221 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_221 is NOT OK\n");
    }
}

void Mcu_222(void)
{
	int retVal = 0;
	Mcu_ClockConfigType *ClockConfig = &McuModuleConfiguration.Mcu_ClockConfigPtr[3];
	Mcu_Init(&McuModuleConfiguration);

	Mcu_InitClock(0);

	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	       /* wait until all enabled PLLs are locked */
	}

	Mcu_DistributePllClock();

//	    Intc_Init();
//	    Console_Init();


    Mcu_InitClock(1);

    //    Intc_Init();
    //    Console_Init();


    Mcu_InitClock(2);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }

    Mcu_DistributePllClock();


    Mcu_InitClock(3);
    if(ClockConfig->mode_configuration.sysclk != MC_ME.GS.B.S_SYSCLK)
    {
        retVal++;
    }
    
    // Intc_Init();
    // Console_Init();
    if(retVal == 0)
    {
        PSPRINTF("Mcu_222 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_222 is NOT OK\n");
    }
}

void Mcu_223(void)
{
    Mcu_ResetType Reset;
    int i;
    Mcu_Init(&McuModuleConfiguration);
    Reset = Mcu_GetResetReason();
    Mcu_InitClock(0);
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
       /* wait until all enabled PLLs are locked */
    }
    Mcu_DistributePllClock();
    Intc_Init();
    Console_Init();
    if(Reset == MCU_SOFT_DEST_RESET)
    {
        PSPRINTF("Mcu_223 is OK\n");
    }
    else
    {
        PSPRINTF("Mcu_223 is NOT OK\n");
    }
    for(i=0;i<80000000;i++);
    PSPRINTF("Mcu_PerformReset() Output once per second\n");
    Mcu_PerformReset();
}

void Mcu_224(void)
{
    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(0);
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	   /* wait until all enabled PLLs are locked */
	}
    Mcu_DistributePllClock();
    
    Console_Init();

    PPCASM ("wrteei 0");
    PSPRINTF("The lowpower mode is after 5s\n");

    for(uint32 i = 0; i < 66000000; i++);
    PSPRINTF("enter lowpower mode\n");
    SIUL2.SCR0.R &= ~0x40000000U;
    SIUL2.MSCR_IO[PS0].R = 0xA00FFU;

    Mcu_SetMode(2);
    Console_Init();
    PSPRINTF("wake up\n");
}

void Mcu_225(void)
{
    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(0);
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	   /* wait until all enabled PLLs are locked */
	}
    Mcu_DistributePllClock();
    
    Console_Init();

    PPCASM ("wrteei 0");
    PSPRINTF("The lowpower mode is after 5s\n");

    for(uint32 i = 0; i < 66000000; i++);
    PSPRINTF("enter lowpower mode\n");
    SIUL2.SCR0.R &= ~0x40000000U;
    SIUL2.MSCR_IO[PS0].R = 0xA00FFU;

    Mcu_SetMode(3);
//    Console_Init();
//    PSPRINTF("wake up\n");
}

void Mcu_226(void)
{
    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(0);
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	   /* wait until all enabled PLLs are locked */
	}
    Mcu_DistributePllClock();
    
    Console_Init();

    PPCASM ("wrteei 0");
    PSPRINTF("The lowpower mode is after 5s\n");

    for(uint32 i = 0; i < 66000000; i++);
    PSPRINTF("enter lowpower mode\n");
    Port_Init(&PortContainer);
    Console_Init();
    PSPRINTF("port init ok\n");

    Mcu_SetMode(2);
    Console_Init();
    PSPRINTF("wake up\n");
}

void Mcu_227(void)
{
    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(0);
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	   /* wait until all enabled PLLs are locked */
	}
    Mcu_DistributePllClock();

    Console_Init();

    PPCASM ("wrteei 0");
    PSPRINTF("The lowpower mode is after 5s\n");

    for(uint32 i = 0; i < 66000000; i++);
    PSPRINTF("enter lowpower mode\n");
    Port_Init(&PortContainer);
    Console_Init();
    PSPRINTF("port init ok\n");

    Mcu_SetMode(3);
//    Console_Init();
//    PSPRINTF("wake up\n");
}

void Mcu_228(void)
{
    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(0);
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	   /* wait until all enabled PLLs are locked */
	}
    Mcu_DistributePllClock();

    Console_Init();

    PPCASM ("wrteei 0");
    Gpt_Init(&GptChannelConfigSet);
    Gpt_EnableNotification(GPT_RTC_CON_INSTANCE);
    Gpt_StartTimer(GPT_RTC_CON_INSTANCE, 30);
    PSPRINTF("The lowpower mode is after 5s\n");

    for(uint32 i = 0; i < 66000000; i++);
    PSPRINTF("enter lowpower mode\n");

    Mcu_SetMode(2);
    Console_Init();
    PSPRINTF("wake up\n");
}

void Mcu_229(void)
{
    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(0);
	while ( MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	   /* wait until all enabled PLLs are locked */
	}
    Mcu_DistributePllClock();

    Console_Init();

    PPCASM ("wrteei 0");
    Gpt_Init(&GptChannelConfigSet);
    Gpt_EnableNotification(GPT_RTC_CON_INSTANCE);
    Gpt_StartTimer(GPT_RTC_CON_INSTANCE, 30);
    PSPRINTF("The lowpower mode is after 5s\n");

    for(uint32 i = 0; i < 66000000; i++);
    PSPRINTF("enter lowpower mode\n");

    Mcu_SetMode(3);
//    Console_Init();
//    PSPRINTF("wake up\n");
}

void Mcu_Test(void)
{
	Mcu_228();
	for(;;)
	{

	}
}


FUNC(void, MCU_CODE)Mcu_ClockFailureCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_XoscCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_InvalidConfigCoreCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_InvalidConfigClockCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_InvalidConfigCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_InvalidModeCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_SafeModeCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_ModeCompleteCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_PmcVoltageErrorCallback(void)
{
    return;
}
FUNC(void, MCU_CODE)Mcu_PmcTempErrorCallback(void)
{
    return;
}

FUNC(void, MCU_CODE)FccuAlarmCallback(void)
{
    return;
}

FUNC(void, MCU_CODE)FccuTimeoutCallback(void)
{
    return;
}

