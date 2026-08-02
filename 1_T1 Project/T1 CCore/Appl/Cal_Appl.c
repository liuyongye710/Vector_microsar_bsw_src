/********************************************************************************
*
*  File name:   Cal_Appl.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Cal_Appl.h"
#include "flash_lld.h"
#include "Os_Arch_Mach_CCFC3008.h"
#include "Xcp.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/
#define CAL_APPL_BLOCK_SIZE         (0x40000U) /* 256k */
#define CAL_APPL_SIZE               (0xC0000U) /* 768k */
#define CAL_APPL_BLOCK0             (0U)
#define CAL_APPL_BLOCK1             (1U)
#define CAL_APPL_BLOCK2             (2U)
#define CAL_APPL_BLOCKMAX           (3U)
#define CAL_APPL_FLASH_ADDR0        (0x01680000U)
#define CAL_APPL_FLASH_ADDR1        (0x016C0000U)
#define CAL_APPL_FLASH_ADDR2        (0x01700000U)
#define CAL_APPL_MIRRFLASH_ADDR0    (0x09680000U)
#define CAL_APPL_MIRRFLASH_ADDR1    (0x096C0000U)
#define CAL_APPL_MIRRFLASH_ADDR2    (0x09700000U)
#define CAL_APPL_RAM_ADDR0          (0x40000000U)
#define CAL_APPL_RAM_ADDR1          (0x40040000U)
#define CAL_APPL_RAM_ADDR2          (0x40080000U)

#define OS_HAL_NVIC_SYSTICK_CURRENT_VALUE_REG	               (*((volatile uint32*)((OS_HAL_STM0_BASE_ADDRESS) + (OS_HAL_STM_CNT_OFFSET))))
/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
#define XCP_START_SEC_CONST_CORE0_BLOCK0 
#include "FAW_MemMap.h"
    /* const */
#define XCP_STOP_SEC_CONST_CORE0_BLOCK0 
#include "FAW_MemMap.h"

/*********************************************************************************
*   Local Variables
*********************************************************************************/
static uint8 Xcp_Key_Array[XCP_SAFELEN];
uint8 isCalibrationProgrammed = 0;

/*********************************************************************************
*   Global Functions
*********************************************************************************/

/*********************************************************************************
*   Local Functions
*********************************************************************************/
uint8 CalAppl_ChangeOVC(void)
{
    status_t ret = STATUS_SUCCESS;
    uint32 flashMirrAddr[CAL_APPL_BLOCKMAX] = {CAL_APPL_MIRRFLASH_ADDR0, CAL_APPL_MIRRFLASH_ADDR1, CAL_APPL_MIRRFLASH_ADDR2};
    uint32 sramAddr[CAL_APPL_BLOCKMAX] = {CAL_APPL_RAM_ADDR0, CAL_APPL_RAM_ADDR1, CAL_APPL_RAM_ADDR2};
    uint32 remapSize = CAL_APPL_BLOCK_SIZE; /* 256KByte */
    flash_remap_config_t remapConfig;
    
    for(uint8 i = CAL_APPL_BLOCK0; i < CAL_APPL_BLOCKMAX; i++)
    {
        /* Step 1: Copy data from Flash Mirror Address to Sram Address */
        //cc_memcpy((uint8 *)(sramAddr[i]), (const uint8 *)(flashMirrAddr[i]), remapSize);

        /* Step 2: Overlay Config Enable (remap Flash Mirror Address to Sram Address) */
        remapConfig.flsLogicAddr = flashMirrAddr[i];
        remapConfig.ramPhyAddr = sramAddr[i];
        remapConfig.remapSize = REMAP_SIZE_256KB;
        FLASH_LLD_Overlay_Config_Enable(i, &remapConfig);
        FLASH_LLD_Overlay_Golbal_Enable();
    }
    
    return ret;
}

void CalAppl_CalSramInit()
{
	/* HighTec link bug: Copy Calibration data from Flash Mirror Address to Sram Address */
	cc_memcpy((uint8 *)(CAL_APPL_RAM_ADDR0), (const uint8 *)(CAL_APPL_FLASH_ADDR0), CAL_APPL_SIZE);
}

void CalAppl_WriteFlash(void)
{
    uint32 flashAddr[CAL_APPL_BLOCKMAX] = {CAL_APPL_FLASH_ADDR0, CAL_APPL_FLASH_ADDR1, CAL_APPL_FLASH_ADDR2};
    uint32 sramAddr[CAL_APPL_BLOCKMAX] = {CAL_APPL_RAM_ADDR0, CAL_APPL_RAM_ADDR1, CAL_APPL_RAM_ADDR2};
    uint32 remapSize = CAL_APPL_BLOCK_SIZE; /* 256KByte */

    if(isCalibrationProgrammed == 1)
    {
      INTC_LLD_Set_Global_Disable();
      FLASH_LLD_Overlay_Config_Disable(0U);
      FLASH_LLD_Overlay_Golbal_Disable();

      for(uint8 i = CAL_APPL_BLOCK0; i < CAL_APPL_BLOCKMAX; i++)
      {
    	   FLASH_HAL_Erase(flashAddr[i], remapSize, FLS_OP_SYNC);
    	   FLASH_HAL_Write(flashAddr[i], (uint8 *)(sramAddr[i]), remapSize, FLS_OP_SYNC);
      }

      INTC_LLD_Set_Global_Enable();
    }
}

uint8 CalAppl_GetRand(uint8 *Cal_RandValue, uint16 length)
{
    uint8 retVal = E_NOT_OK;
#if (CAL_RAND_SEED == STD_ON)
    uint32 random_number = 0;
    static uint32 curtime = 0, lasttime = 0;
    
    if((Cal_RandValue != NULL_PTR) && (length > 0))
    {
        curtime = OS_HAL_NVIC_SYSTICK_CURRENT_VALUE_REG;
        if (curtime == lasttime)
        {
            curtime = curtime + 1;
        }
        lasttime = curtime;

        srand(curtime);
        for (uint8 i = 0; i < (length/2); i++)
        {
            random_number = rand();
            Cal_RandValue[0 + i * 2] = (uint8)((random_number >> 8) & 0xFF);
            Cal_RandValue[1 + i * 2] = (uint8)((random_number) & 0xFF);
        }
        retVal = E_OK;
    }
#else
    if((Cal_RandValue != NULL_PTR) && (length > 0))
    {
        for (uint8 i = 0; i < (length/2); i++)
        {
            Cal_RandValue[0 + i * 2] = 0;
            Cal_RandValue[1 + i * 2] = 0;
        }
        retVal = E_OK;
    }
#endif
	return retVal;
}

void  CalAppl_CalKey(uint8 *Cal_KeyValue)
{
    for (uint8 i = 0; i < XCP_SAFELEN; i++)
    {
    	Xcp_Key_Array[i] = *(Cal_KeyValue + XCP_SAFELEN -1 -i) + 5;
    }
    
}

uint8 CalAppl_CompareKey(uint8 *Cal_CompareKey, uint16 length)
{
    uint8 retVal = E_OK;
    
    if((Cal_CompareKey != NULL_PTR) && (length > 0))
    {
        for(uint8 i = 0; i < length; i++)
        {
            if(Xcp_Key_Array[i] != Cal_CompareKey[i])
            {
                retVal = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}