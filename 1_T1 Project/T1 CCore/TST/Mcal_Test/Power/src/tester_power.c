#include "tester_power.h"
#include <stdbool.h>
#include "console.h"
#include "Det.h"
#include "shell.h"
#include "tester_gpt.h"
#include "Gpt_Stm_LLDriver.h"

#define NULL_PTR ((void *)0)
#define POWER_TEST_CASE_MAX sizeof(power_funcs) / sizeof(PowerfuncMachine)

static PowerfuncMachine power_funcs[] = {
    {"power0001", testpower0001},
    {"power0002", testpower0002},
    {"power0003", testpower0003},
    {"power0004", testpower0004},
    {"power0005", testpower0005},
    {"power0006", testpower0006},
    {"power0007", testpower0007},
    {"power0007", testpower0008},
};

void testpower0001()  //Get_External_WdgReq
{
    PSPRINTF("[%s]",__func__);
	int level = Get_External_WdgReq();
	PSPRINTF("Wdg_Req = %d\n", level);
}

void testpower0002()  //Get_SMUFSP_St
{
    PSPRINTF("[%s]",__func__);
//	Get_SMUFSP_St();
}

void testpower0003()  //Enable_External_Wdg
{
	PSPRINTF("[%s]",__func__);
	Power_Init();
	Power_SetExternalWdg(WDG_ENABLE);
	PSPRINTF("Enable_External_Wdg\n");
}

void testpower0004()  //Disable_External_Wdg
{
	PSPRINTF("[%s]",__func__);
	Power_Init();

	Power_SetExternalWdg(WDG_DISABLE);

	PSPRINTF("Disable_External_Wdg\n");
}

void testpower0005()
{
    PSPRINTF("[%s]",__func__);
	Power_Init();
    Pwm_Init(&Pwm_Config);

	Power_SetExternalWdg(WDG_ENABLE);

//    gpt_test_10ms();
}

void testpower0006()
{
    PSPRINTF("[%s]",__func__);
	Power_Init();
    Pwm_Init(&Pwm_Config);

	Power_SetExternalWdg(WDG_DISABLE);

//    gpt_test_10ms();
}

void testpower0007()
{
    PSPRINTF("[%s]",__func__);
	Power_Init();
    Pwm_Init(&Pwm_Config);

	Power_SetExternalWdg(WDG_ENABLE);

	Power_WdgFeeding(NULL_PTR);

	Gpt_Stm_LLD_DelayMs(STM1, 10U);

    Pwm_SetOutputToIdle(1);
}

void testpower0008()
{
    PSPRINTF("[%s]",__func__);
	Power_Init();
    Pwm_Init(&Pwm_Config);

	Power_SetExternalWdg(WDG_DISABLE);

	Power_WdgFeeding(NULL_PTR);

	Gpt_Stm_LLD_DelayMs(STM1, 10U);

    Pwm_SetOutputToIdle(1);
}

int power_func(int argc, char *agrv[])
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
                    
            for(uint8 i = 0; i < POWER_TEST_CASE_MAX; i++)
            {
                PSPRINTF("%s\n", power_funcs[i].name);
            }
        }
        else
        {
				uint32 id = (uint32)atoi(agrv[1]);
                PSPRINTF("%d\r\n", id);
                if((id >= 1) && (id <=POWER_TEST_CASE_MAX))
				{
					if (power_funcs[id - 1].powerfunc != NULL_PTR)
                    {
                        power_funcs[id - 1].powerfunc();
                    }
					else if(power_funcs[id].powerfunc==NULL)
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
                    PSPRINTF("error: Input invalid parameters[%d], please output [1 - %d] range parameters\n", id, POWER_TEST_CASE_MAX);
                }}
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), power_test, power_func, deint or number of test case);






