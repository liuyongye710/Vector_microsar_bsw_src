/********************************************************************************
*
*  File name:   Test_NvM.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Test_NvM.h"
#include "NvM.h"
#include "Nvm_Appl.h"
#include "flash_hal.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
#if( TEST_NVM_ENABLE == STD_ON )
uint8 Read_Block1[DSM_NVM_DATA_LENGTH] = {0};
uint8 Read_Block2[APP_NVM_DATA_LENGTH] = {0};
uint8 Read_Block3[DATA_NVM_ONFLY_LENGTH] = {0};
uint8 test_NvM_counter = 0;
uint8 ret = 0;
uint8 nvm_sts = 0;
uint8 Test_PowerDownPermission = 0;
#endif
/*********************************************************************************
*   Local Functions
*********************************************************************************/
#if( TEST_NVM_ENABLE == STD_ON )
void Test_GetPowerDownPermission(void)
{
    Test_PowerDownPermission = Action_GetPowerDownPermission();
}

void Test_NvM(void)
{
    switch (test_NvM_counter)
    {
    /* Block 0 */
    case 0:
        for(uint8 i = 0;i<100;i++)
        {
            dsm_nvm_data[i] = i;
        }
        ret = NvM_WriteBlock(NVM_BLOCKID_DSM_NVM_DATA_BLOCK,dsm_nvm_data);
        if(ret == 0)
        {
            test_NvM_counter = 1;
        }
        break;
    case 1:
        NvM_GetErrorStatus(NVM_BLOCKID_DSM_NVM_DATA_BLOCK,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 2;
        }
        break;
    case 2:
        ret = NvM_ReadBlock(NVM_BLOCKID_DSM_NVM_DATA_BLOCK,Read_Block1);
        if(ret == 0)
        {
            test_NvM_counter = 3;
        }
        break;
    case 3:
        NvM_GetErrorStatus(NVM_BLOCKID_DSM_NVM_DATA_BLOCK,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 4;
        }
        break;
    /* Block 1 */
    case 4:
        for(uint8 i = 0;i<100;i++)
        {
            app_nvm_data[i] = i;
        }
        ret = NvM_WriteBlock(NVM_BLOCKID_APP_NVM_DATA_BLOCK,app_nvm_data);
        if(ret == 0)
        {
            test_NvM_counter = 5;
        }
        break;
    case 5:
        NvM_GetErrorStatus(NVM_BLOCKID_APP_NVM_DATA_BLOCK,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 6;
        }
        break;
    case 6:
        ret = NvM_ReadBlock(NVM_BLOCKID_APP_NVM_DATA_BLOCK,Read_Block2);
        if(ret == 0)
        {
            test_NvM_counter = 7;
        }
        break;
    case 7:
        NvM_GetErrorStatus(NVM_BLOCKID_APP_NVM_DATA_BLOCK,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 8;
        }
        break;
    /* Block 2 */
    case 8:
        for(uint8 i = 0;i<100;i++)
        {
            data_nvm_onfly[i] = i;
        }
        ret = Appl_NvMonFlyRestoreRequest();
        if(ret == 0)
        {
            test_NvM_counter = 9;
        }
        break;
    case 9:
        NvM_GetErrorStatus(NVM_BLOCKID_DATA_NVM_ONFLY_BLOCK,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 10;
        }
        break;
    case 10:
        ret = NvM_ReadBlock(NVM_BLOCKID_DATA_NVM_ONFLY_BLOCK,Read_Block3);
        if(ret == 0)
        {
            test_NvM_counter = 11;
        }
        break;
    case 11:
        NvM_GetErrorStatus(NVM_BLOCKID_DATA_NVM_ONFLY_BLOCK,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 12;
        }
        break;
    /* Write All */
    case 12:
        for(uint8 i = 0;i<100;i++)
        {
            dsm_nvm_data[i] = 1;
            app_nvm_data[i] = 1;
            data_nvm_onfly[i] = 1;
        }
        /*Appl_RequestPowerDown();
        NvM_WriteAll();*/
        test_NvM_counter = 13;
        break;
    /*case 13:
        NvM_GetErrorStatus(0,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 14;
        }
        break;
    // Read All
    case 14:
        for(uint8 i = 0;i<100;i++)
        {
            dsm_nvm_data[i] = 0;
            app_nvm_data[i] = 0;
            data_nvm_onfly[i] = 0;
        }
        NvM_ReadAll();
        test_NvM_counter = 15;
        break;
    case 15:
        NvM_GetErrorStatus(0,&nvm_sts);
        if(nvm_sts == NVM_REQ_OK)
        {
            test_NvM_counter = 16;
        }
        break;*/
    default:
        break;
    }
}
#if 0
void Test_Fls(void)
{
    switch (test_NvM_counter)
    {
     case 0:
          ret = Fls_Erase(0x38000,0x10000);
          if(ret == 0)
          {
               test_NvM_counter = 1;
          }
          break;
     case 1:
          nvm_sts = Fls_GetJobResult();
          if(nvm_sts == NVM_REQ_OK)
          {
               test_NvM_counter = 2;
          }
          break;
     case 2:
          ret = Fls_Write(0x38000,dsm_nvm_data,1024*30);
          if(ret == 0)
          {
               test_NvM_counter = 3;
          }
          break;
     case 3:
          nvm_sts = Fls_GetJobResult();;
          if(nvm_sts == NVM_REQ_OK)
          {
               test_NvM_counter = 4;
          }
          break;

     case 4:
          ret = Fls_Read(0x38000,Read_Block1,1024*30);
          if(ret == 0)
          {
               test_NvM_counter = 5;
          }
          break;
     case 5:
          nvm_sts = Fls_GetJobResult();;
          if(nvm_sts == NVM_REQ_OK)
          {
               test_NvM_counter = 6;
          }
          break;
     default:
          break;
    }
}

#define TEST_LEN  0x10000
uint8 Write_Block1[TEST_LEN] = {1,2,3,4,5,6,7,8};
uint8 Read_Block_Sync[TEST_LEN] = {0};
void Test_Fls_Sync(void)
{
    switch (test_NvM_counter)
    {
     case 0:
        ret = FLASH_HAL_Erase(0x00FE0000, 0x10000, FLS_OP_SYNC);
        ret = FLASH_HAL_Erase(0x00FF0000, 0x10000, FLS_OP_SYNC);
        if(ret == 0)
        {
            test_NvM_counter = 1;
        }
        break;
     case 1:
        ret = FLASH_HAL_Write(0x00FE0000, Write_Block1, TEST_LEN, FLS_OP_SYNC);
        ret = FLASH_HAL_Write(0x00FF0000, Write_Block1, TEST_LEN, FLS_OP_SYNC);
        if(ret == 0)
        {
            test_NvM_counter = 2;
        }
        break;
     case 2:
        ret = FLASH_HAL_Read(0x00FE0000, Read_Block_Sync, TEST_LEN);
        if(ret == 0)
        {
            test_NvM_counter = 3;
        }
        break;
     default:
          break;
    }
}
#endif
#endif

