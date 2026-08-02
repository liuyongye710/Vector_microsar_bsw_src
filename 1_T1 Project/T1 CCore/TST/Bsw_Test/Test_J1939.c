/********************************************************************************
*
*  File name:   Test_J1939.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Test_J1939.h"
#include "Com.h"
#include "Com_Appl.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/
#define ECMCU_CNT    (0U)
#define DM1MCU_CNT   (1U)
#define DM1MCU2_CNT  (2U)

#define DM1APCU_CNT  (0U)
#define DM1DCDC_CNT  (1U)
#define DM1OPCU_CNT  (2U)
#define DM1PTU_CNT   (3U)
/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
#if( TEST_J1939_ENABLE == STD_ON )
uint8 TestJ1939_Cnt_1 = 0;
uint8 TestJ1939_Cnt_3 = 0;
#endif
/*********************************************************************************
*   Local Variables
*********************************************************************************/
/*********************************************************************************
*   Local Functions
*****/
#if( TEST_J1939_ENABLE == STD_ON )
void Test_J1939_SendMessage(void)
{
    uint8 ECMCU_Test[34]   = {1,2,3,4,5,6,7,8,9,10};
    uint8 DM1MCU_Test[48]  = {11,12,13,14,15,16,17,18,19,20};
    uint8 DM1MCU2_Test[48] = {21,22,23,24,25,26,27,28,29,30};
    uint8 DM1APCU_Test[48] = {1,2,3,4,5,6,7,8,9,10};
    uint8 DM1DCDC_Test[48] = {11,12,13,14,15,16,17,18,19,20};
    uint8 DM1OPCU_Test[48] = {21,22,23,24,25,26,27,28,29,30};
    uint8 DM1PTU_Test[48]  = {31,32,33,34,35,36,37,38,39,40};
    switch (TestJ1939_Cnt_1)
    {
        case ECMCU_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_ECMCU_D3_sO0, ECMCU_Test);
            TestJ1939_Cnt_1 = DM1MCU_CNT;
            break;
        case DM1MCU_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_DM1MCU_D3_sO0, DM1MCU_Test);
            TestJ1939_Cnt_1 = DM1MCU2_CNT;
            break;
        case DM1MCU2_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_DM1MCU2_D3_sO0, DM1MCU2_Test);
            TestJ1939_Cnt_1 = ECMCU_CNT;
            break;
        default:
            break;
    }

    switch (TestJ1939_Cnt_3)
    {
        case DM1APCU_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_DM1APCU_OjcG_c, DM1APCU_Test);
            TestJ1939_Cnt_3 = DM1DCDC_CNT;
            break;
        case DM1DCDC_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_DM1DCDC_OjcG_c, DM1DCDC_Test);
            TestJ1939_Cnt_3 = DM1OPCU_CNT;
            break;
        case DM1OPCU_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_DM1OPCU_OjcG_c, DM1OPCU_Test);
            TestJ1939_Cnt_3 = DM1PTU_CNT;
            break;
        case DM1PTU_CNT:
            Com_WriteTxMessage(Hnd_Msg_Tx_DM1PTU_OjcG_c, DM1PTU_Test);
            TestJ1939_Cnt_3 = DM1APCU_CNT;
            break;
        default:
            break;
    }
}
#endif
