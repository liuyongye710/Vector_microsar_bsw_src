/********************************************************************************
*
*  File name:   Test_ShutDown.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Test_ShutDown.h"
#include "Dio.h"
#include "ComM.h"
#include "Nvm_Appl.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
#if( TEST_SHUTDOWN_ENABLE == STD_ON )
uint8 kl15On_counter = 0;
uint8 kl15Off_counter = 0;
uint8 kl15Sts = STD_ON;
uint8 commSts = STD_ON;
Dio_LevelType DIO_read = 1;
#endif
/*********************************************************************************
*   Local Variables
*********************************************************************************/
/*********************************************************************************
*   Local Functions
*********************************************************************************/
#if( TEST_SHUTDOWN_ENABLE == STD_ON )
void test_kl15(void)
{ 
    // Dio_LevelType DIO_read = 1;
    // DIO_read = Dio_ReadChannel(DioConf_DioChannel_DioChannel_I_D_UC_KL15);

    if(STD_LOW == DIO_read)
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
    }
}

void test_ComM(void)
{
    if((kl15Sts == STD_OFF)&&(commSts == STD_ON))
    {
        commSts = STD_OFF;
        Appl_RequestPowerDown();
        // ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
        // ComM_RequestComMode(1, COMM_NO_COMMUNICATION);
        // ComM_RequestComMode(2, COMM_NO_COMMUNICATION);
        // ComM_RequestComMode(3, COMM_NO_COMMUNICATION);
    }
    if((kl15Sts == STD_ON)&&(commSts == STD_OFF))
    {
        commSts = STD_ON;
        ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
        ComM_RequestComMode(1, COMM_FULL_COMMUNICATION);
        ComM_RequestComMode(2, COMM_FULL_COMMUNICATION);
        ComM_RequestComMode(3, COMM_FULL_COMMUNICATION);
    }
}

#endif

