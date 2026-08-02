/********************************************************************************
*
*  File name:   Nvm_Appl.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Nvm_Appl.h"
#include "NvM.h"
#include "ComM.h"
#include "Dio.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
const uint8 dsm_default_data[DSM_NVM_DATA_LENGTH] = {0};
const uint8 app_default_data[APP_NVM_DATA_LENGTH] = {0};
const uint8 data_onfly_default[DATA_NVM_ONFLY_LENGTH] = {0};

uint8 dsm_nvm_data[DSM_NVM_DATA_LENGTH] = {0};
uint8 app_nvm_data[APP_NVM_DATA_LENGTH] = {0};
uint8 data_nvm_onfly[DATA_NVM_ONFLY_LENGTH] = {0};

uint8 lv_power_down_enable = 0;

uint8 kl15On_counter = 0;
uint8 kl15Off_counter = 0;
uint8 kl15Sts = STD_ON;
uint8 commSts = STD_ON;
Dio_LevelType kl15Status = 0;
uint32 shutDownDelay;
uint8 EcuReleaseFlag;

#if (SHUTDOWN_DELAY == STD_ON)
#define XCP_START_SEC_CONST_CORE0_BLOCK0
#include "FAW_MemMap.h"
     /*const*/
const volatile uint32 shutDownDelayTime_20ms = 0;
#define XCP_STOP_SEC_CONST_CORE0_BLOCK0
#include "FAW_MemMap.h"
#endif
/*********************************************************************************
*   Local Variables
*********************************************************************************/
/*********************************************************************************
*   Global Functions
*********************************************************************************/

/*********************************************************************************
*   Local Functions
*********************************************************************************/

void Appl_RequestPowerDown(void)
{
    uint8 nvmBlkCnt = 0;

    for(nvmBlkCnt = 2; nvmBlkCnt < NVM_NUM_OF_BLOCK_TOTAL; nvmBlkCnt++)
    {
        (void)NvM_SetRamBlockStatus(nvmBlkCnt, TRUE);
    }
    ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
    ComM_RequestComMode(1, COMM_NO_COMMUNICATION);
    ComM_RequestComMode(2, COMM_NO_COMMUNICATION);
    ComM_RequestComMode(3, COMM_NO_COMMUNICATION);
}

uint8 Action_GetPowerDownPermission(void)
{
    return lv_power_down_enable;
}

uint8 Appl_NvMonFlyRestoreRequest(void)
{
    uint8 retNvm = E_NOT_OK;

    retNvm = (uint8)NvM_WriteBlock(NVM_BLOCKID_DATA_NVM_ONFLY_BLOCK, data_nvm_onfly);
    
    return retNvm;
}

void debounceKeyStatusFilter(void) //BHY
{
    kl15Status = Dio_ReadChannel(DioConf_DioChannel_DI_IN_KL15);

    if(STD_HIGH == kl15Status)
    {
        kl15Off_counter++;
        kl15On_counter = 0;
    }
    else
    {
        kl15Off_counter = 0;
        kl15On_counter++;
    }

    if(kl15Off_counter == 10)
    {
        kl15Off_counter = 0;
        kl15On_counter = 0;
        kl15Sts = STD_OFF;
    }
    if(kl15On_counter == 10)
    {
        kl15Off_counter = 0;
        kl15On_counter = 0;
        kl15Sts = STD_ON;
        EcuReleaseFlag = NOT_RELEASED;
    }
}

#if (SHUTDOWN_DELAY == STD_ON)
void SetShutDowmDelay()
{
	shutDownDelay = shutDownDelayTime_20ms;
}

void checkShutDownDelay()//BHY
{
    if(shutDownDelay > 0)
    {
    	shutDownDelay--;
        if(shutDownDelay == 0 || Action_GetPowerDownPermission())
        {
        	commSts = STD_OFF;
        	Appl_RequestPowerDown();
        }
    }
    else
    {
    	if(Action_GetPowerDownPermission())
    	{
    		commSts = STD_OFF;
    		Appl_RequestPowerDown();
    	}
    }
}
#endif

void shutDownRequest(void)//BHY
{
    if((kl15Sts == STD_OFF)&&(commSts == STD_ON))
    {
#if (SHUTDOWN_DELAY == STD_ON)
    	if(EcuReleaseFlag == NOT_RELEASED)
    	{
    		SetShutDowmDelay();
    		EcuReleaseFlag = IS_RELEASED;
    	}
        checkShutDownDelay();
#else
    	if(Action_GetPowerDownPermission())
    	{
    		commSts = STD_OFF;
    		Appl_RequestPowerDown();
    	}
#endif
    }
    if((kl15Sts == STD_ON)&&(commSts == STD_OFF))
    {
    	EcuReleaseFlag = NOT_RELEASED;
    	commSts = STD_ON;
        ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
        ComM_RequestComMode(1, COMM_FULL_COMMUNICATION);
        ComM_RequestComMode(2, COMM_FULL_COMMUNICATION);
        ComM_RequestComMode(3, COMM_FULL_COMMUNICATION);
    }
}
