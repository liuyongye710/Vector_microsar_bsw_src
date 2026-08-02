/********************************************************************************
*
*  File name:   task.c
*
*********************************************************************************
*
* History
*--------------------------------------------------------------------------------
*********************************************************************************
* Version: 1.0
* Author/Date : WangM/2023.10.01
* Change: New created 
* Cause: New
*********************************************************************************/

/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Platform_Types.h"
#include "CCFC3007PT.h"
//#include "LinSM.h"
#include "Can.h"
#include "status.h"
#include "intc_lld.h"
#include "Os_Arch_Mach_CCFC3008.h"
#include "Test_Can.h"
#include "Test_NvM.h"
#include "Test_ShutDown.h"
#include "Test_J1939.h"
#include "Test_Lin.h"
#include "Mcu.h"
#include "Dio.h"
#include "Cal_Appl.h"
#include "flash_hal.h"
#include "T1_AppInterface.h"/* for T1 */
#include "Dcm_Cbk.h"
#include "Os_Core.h"
#include "Vol_DiagForCanLin.h"
/*********************************************************************************
*   Local  Macros
*********************************************************************************/
#define CAL_RAM_ADDR              (*(uint32*)(0x40000000U))
#define PROGRAMMING_CAN_FLAG      (0x5AA5)
#define PROGRAMMING_CANFD_FLAG    (0x6BB6)
#define PROGRAMMING_ADDR          (0x00FC4000U)
#define PROGRAMMING_BLOCK_LENGTH  (0x4000)
#define PROGRAMMING_LENGTH        (16)
#define PROGRAMMING_OFFSET        (0x0E/2)
#define DCM_FUN_CAN               (0)
#define DCM_PHY_CAN               (1)
#define DCM_FUN_CANFD             (2)
#define DCM_PHY_CANFD             (3)

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/
uint8  corex_DefaultInitCnt[3];
uint8  corex_InitCnt[3];
uint32 corex_1msCnt[1];
uint32 corex_5msCnt[3];
uint32 corex_10msCnt[3];
uint32 corex_20msCnt[3];
uint32 corex_50msCnt[3];
uint32 corex_100msCnt[3];
uint32 corex_200msCnt[3];
uint32 corex_500msCnt[3];
uint32 corex_1000msCnt[3];
/*********************************************************************************
*   Local Functions
*********************************************************************************/
float Get_STM0_TimerMs(void)
{
    float tempTimer = 0;

    tempTimer = ((float)(*((volatile uint32*)((OS_HAL_STM0_BASE_ADDRESS) + (OS_HAL_STM_CNT_OFFSET)))))*20u/1000000u;
    
    return tempTimer;
}
void Ecu_PowerOff(void)
{
    uint32 coreId = Os_Core_GetLogicId();

    if(OS_CORE_ID_2 == coreId )
    {
    	CalAppl_WriteFlash();
    	Dio_WriteChannel(DioConf_DioChannel_DO_POWER_Down,STD_LOW);
    }
}
void Dcm_10_JumpBoot(void)
{
    uint16 proIndex = 0;
    uint16 Programming_Buffer[8] = {0};

    Dcm_GetCurActiveProtocolIndex(&proIndex);

    INTC_LLD_Set_Global_Disable();

    memcpy(Programming_Buffer,PROGRAMMING_ADDR,PROGRAMMING_LENGTH);
    
    if((proIndex == DCM_FUN_CAN)||(proIndex == DCM_PHY_CAN))
    {
        Programming_Buffer[PROGRAMMING_OFFSET] = PROGRAMMING_CAN_FLAG;
    }
    else if((proIndex == DCM_FUN_CANFD)||(proIndex == DCM_PHY_CANFD))
    {
        Programming_Buffer[PROGRAMMING_OFFSET] = PROGRAMMING_CANFD_FLAG;
    }
    else
    {
        /* do nothing */
    }
    
    FLASH_HAL_Erase(PROGRAMMING_ADDR, PROGRAMMING_BLOCK_LENGTH, FLS_OP_SYNC);
    FLASH_HAL_Write(PROGRAMMING_ADDR, Programming_Buffer, PROGRAMMING_LENGTH, FLS_OP_SYNC);

    INTC_LLD_Set_Global_Enable();
    
    Mcu_PerformReset();
}
//void LinRequestComM(void)
//{
//    Std_ReturnType LinSts = E_NOT_OK;
//
//    if(LinSM_Sts_Req != LinSM_Sts_Cur)
//    {
//        LinSts = LinSM_ScheduleRequest(5,LinSM_Sts_Req);
//        if(E_OK == LinSts)
//        {
//            LinSM_Sts_Cur = LinSM_Sts_Req;
//        }
//    }
//}

void Test_Runnable_Core2_DefaultInit(void)
{
	corex_DefaultInitCnt[2]++;
}
void Test_Runnable_Core2_Init(void)
{
    corex_InitCnt[2]++;
}
void Test_Runnable_Core2_1ms(void)
{
#if( TEST_BUSOFF_ENABLE == STD_ON )
    Test_BusOff_Send_Cycle();
#endif
    corex_1msCnt[0]++;
}
void Test_Runnable_Core2_5ms(void)
{
    corex_5msCnt[2]++;
}
void Test_Runnable_Core2_10ms(void)
{
    T1_AppHandler();/* for T1 */
//    LinRequestComM();
    corex_10msCnt[2]++;
}
void Test_Runnable_Core2_20ms(void)
{
#if( TEST_SHUTDOWN_ENABLE == STD_ON )
    test_kl15();
    test_ComM();
#endif
    corex_20msCnt[2]++;
}
void Test_Runnable_Core2_50ms(void)
{
    corex_50msCnt[2]++;
}
void Test_Runnable_Core2_100ms(void)
{
    corex_100msCnt[2]++;
}
void Test_Runnable_Core2_200ms(void)
{
    corex_200msCnt[2]++;
}
void Test_Runnable_Core2_500ms(void)
{
#if( TEST_NVM_ENABLE == STD_ON )
    Test_NvM();
    //Test_GetPowerDownPermission();
#endif
    corex_500msCnt[2]++;
}
void Test_Runnable_Core2_1000ms(void)
{
#if( TEST_CAN_ENABLE == STD_ON )
    Test_Can_SendMessage();
    Test_Can_ReceiveMessage();
#endif

#if( TEST_J1939_ENABLE == STD_ON )
    Test_J1939_SendMessage();
#endif

#if( TEST_LIN_ENABLE == STD_ON )
    Test_Lin_SendMessage();
    Test_Lin_ReceiveMessage();
#endif
    corex_1000msCnt[2]++;
}


void Test_Runnable_Core0_DefaultInit(void)
{
	INTC_LLD_Set_IRQ_Disable(INTR_ID_36);
    Os_Monitor_init();
    corex_DefaultInitCnt[0]++;
}
void Test_Runnable_Core0_Init(void)
{
    corex_InitCnt[0]++;
}
void Test_Runnable_Core0_2ms(void)
{
    corex_5msCnt[0]++;
}
void Test_Runnable_Core0_10ms(void)
{
    // Voltage_CheckForControlCAN();
    // Voltage_CheckForControlDiag();
    // Voltage_CheckForControlLIN();
    T1_AppHandler();/* for T1 */
    corex_10msCnt[0]++;
}
void Test_Runnable_Core0_20ms(void)
{
    corex_20msCnt[0]++;
}
void Test_Runnable_Core0_50ms(void)
{
    corex_50msCnt[0]++;
}
void Test_Runnable_Core0_100ms(void)
{
    corex_100msCnt[0]++;
}
void Test_Runnable_Core0_200ms(void)
{
    corex_200msCnt[0]++;
}
void Test_Runnable_Core0_500ms(void)
{
    corex_500msCnt[0]++;
}
void Test_Runnable_Core0_1000ms(void)
{
    Os_Monitor_MainFunction();
    corex_1000msCnt[0]++;
}


void Test_Runnable_Core1_DefaultInit(void)
{
    corex_DefaultInitCnt[1]++;
}
void Test_Runnable_Core1_Init(void)
{
    corex_InitCnt[1]++;
}
void Test_Runnable_Core1_5ms(void)
{
    corex_5msCnt[1]++;
}
void Test_Runnable_Core1_10ms(void)
{
    T1_AppHandler();/* for T1 */
    corex_10msCnt[1]++;
}
void Test_Runnable_Core1_20ms(void)
{
    corex_20msCnt[1]++;
}
void Test_Runnable_Core1_50ms(void)
{
    corex_50msCnt[1]++;
}
void Test_Runnable_Core1_100ms(void)
{
    corex_100msCnt[1]++;
}
void Test_Runnable_Core1_200ms(void)
{
    corex_200msCnt[1]++;
}
void Test_Runnable_Core1_500ms(void)
{
    corex_500msCnt[1]++;
}
void Test_Runnable_Core1_1000ms(void)
{
    corex_1000msCnt[1]++;
}

void CDS_Init(void)
{

}
void CDS_Mainfunction(void)
{
    
}

void Dsm_MainFunction(void)
{

}

void CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{

}
/* END task.c */
