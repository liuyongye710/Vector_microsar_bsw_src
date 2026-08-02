#include "StandardTypes.h"
#include "tester_gpt.h"
#include "Gpt_cfg.h"
#include "shell.h"
#include "Gpt_Stm_LLDriver.h"
#include "Cdd_9945_LLDriver.h"
#include "Gpt_Irq.h"
#include "Gpt_AUtoSAR_Wrapper.h"
#include "PowerCtrl_Cfg.h"

GPT_CONFIG_DECLARATION;
#define GPT_TEST_CASE_MAX 6

static GptfuncMachine gpt_funcs[] = {
	{"GPT_0001", gpt_test_1ms},
	{"GPT_0002", gpt_test_10ms},
	{"GPT_0003", gpt_test_100ms},
	{"GPT_0004", gpt_test_1000ms},
	{"GPT_0005", gpt_test_stop}
};

#define NULL ((void *)0)

#if 0
#define PRINTF PSPRINTF
#else
#define PRINTF(...)
#endif

#define GPT_PIT_CON_1MS_INSTANCE		0
#define GPT_PIT_CON_10MS_INSTANCE		1
#define GPT_PIT_CON_100MS_INSTANCE		2
#define GPT_PIT_CON_1000MS_INSTANCE		3

#define GPT_PIT_CONTINUE_1MS		(1000 * 1)
#define GPT_PIT_CONTINUE_10MS		(1000 * 10)
#define GPT_PIT_CONTINUE_50MS		(1000 * 50)
#define GPT_PIT_CONTINUE_100MS		(1000 * 100)
#define GPT_PIT_CONTINUE_1000MS		(1000 * 1000)

#define GPT_ERROR_INSTANCE 255

#define POWER_CTRL_TEST STD_ON

uint8 sgpt_init = 0;
uint32 pit_1ms_cnt = 0;
uint32 pit_10ms_cnt = 0;
uint32 pit_100ms_cnt = 0;
uint32 pit_1000ms_cnt = 0;
uint8  Flag_50ms = 0;
extern uint8 count_cddtime;

void gpt_stop_timer_all(void)
{
	uint32 i = 0;
	for(i=0; i<3;i++)
	{
		if (Gpt_GetChannelStatus(i) == 4) {// running
			Gpt_StopTimer(i); // stop timer, otherwise can't deinit
		}
	}
}
void gpt_init_test(void)
{
	if (sgpt_init == 0)
	{
		Gpt_Init(&GptChannelConfigSet);
		sgpt_init = 1;
	}
	else
	{
		gpt_stop_timer_all();
	}
}

void gpt_deinit_test(void)
{
    if (sgpt_init == 1){// if gpt init already, deinit for test
    	gpt_stop_timer_all();
		Gpt_DeInit();
		sgpt_init = 0;
	}
}


void Gpt_Pit_Cbk_1ms_Notification(void)
{

	pit_1ms_cnt++;
	if(pit_1ms_cnt >= GPT_PIT_CONTINUE_1MS)
	{
		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,1);
		PRINTF("pit 1ms - 1s timer callback counter:%d\r\n", pit_1ms_cnt);
		pit_1ms_cnt = 0;
	}
	else
	{
		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,0);
	}
}

void Gpt_Pit_Cbk_10ms_Notification(void)
{
#if (POWER_CTRL_TEST == STD_ON)
	if(pit_10ms_cnt % 2 == 1)
	{
		Power_WdgFeeding(NULL_PTR);
	}
	else if(pit_10ms_cnt % 2 == 0)
	{
	    Pwm_SetOutputToIdle(1);
	}
#endif
	if(Flag_50ms == 1)
	{
		CDD_9945_Keep_Communication(CDD_9945_CHIP_1);
		CDD_9945_Keep_Communication(CDD_9945_CHIP_2);
		CDD_9945_Keep_Communication(CDD_9945_CHIP_3);
		CDD_9945_Keep_Communication(CDD_9945_CHIP_4);
		CDD_9945_Keep_Communication(CDD_9945_CHIP_5);

		count_cddtime++;
	}

	pit_10ms_cnt++;
//	if(pit_10ms_cnt >= 100u)
//	{
//	   Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,1);
//	   PRINTF("pit 10ms timer callback counter:%d\r\n", pit_10ms_cnt);
//	   pit_10ms_cnt = 0;
//	}
//	else
//	{
//		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,0);
//	}
}

void Gpt_Pit_Cbk_100ms_Notification(void)
{
	pit_100ms_cnt++;
	if(pit_100ms_cnt >= 10)
	{
		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,1);
		PRINTF("pit 100ms - 1s timer callback counter:%d\r\n", pit_100ms_cnt);
		pit_100ms_cnt = 0;
	}
	else
	{
		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,0);
	}
}

void Gpt_Pit_Cbk_1000ms_Notification(void)
{
	pit_1000ms_cnt++;

	if(pit_1000ms_cnt % 2 == 0)
	{
		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,1);
	}
	else
	{
		Dio_WriteChannel(POWER_DIS_WDG_CHANNEL,0);
	}

	PRINTF("pit 1000ms timer callback counter:%d\r\n", pit_1000ms_cnt);
}


void gpt_test_1ms(void)
{
	gpt_init_test();
	Gpt_EnableNotification(GPT_PIT_CON_1MS_INSTANCE);
	Gpt_EnableWakeup(GPT_PIT_CON_1MS_INSTANCE);
	Gpt_StartTimer(GPT_PIT_CON_1MS_INSTANCE, GPT_PIT_CONTINUE_1MS);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void gpt_test_10ms(void)
{
	gpt_init_test();
	Gpt_EnableNotification(GPT_PIT_CON_10MS_INSTANCE);
	Gpt_EnableWakeup(GPT_PIT_CON_10MS_INSTANCE);
	Gpt_StartTimer(GPT_PIT_CON_10MS_INSTANCE, GPT_PIT_CONTINUE_10MS);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}


void gpt_test_50ms(void)
{
	gpt_init_test();
	Gpt_EnableNotification(GPT_PIT_CON_10MS_INSTANCE);
	Gpt_EnableWakeup(GPT_PIT_CON_10MS_INSTANCE);
	Gpt_StartTimer(GPT_PIT_CON_10MS_INSTANCE, GPT_PIT_CONTINUE_50MS);
	Flag_50ms = 1;
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void gpt_test_100ms(void)
{
	gpt_init_test();
	Gpt_EnableNotification(GPT_PIT_CON_100MS_INSTANCE);
	Gpt_EnableWakeup(GPT_PIT_CON_100MS_INSTANCE);
	Gpt_StartTimer(GPT_PIT_CON_100MS_INSTANCE, GPT_PIT_CONTINUE_100MS);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}
void gpt_test_1000ms(void)
{
	gpt_init_test();
	Gpt_EnableNotification(GPT_PIT_CON_1000MS_INSTANCE);
	Gpt_EnableWakeup(GPT_PIT_CON_1000MS_INSTANCE);
	Gpt_StartTimer(GPT_PIT_CON_1000MS_INSTANCE, GPT_PIT_CONTINUE_1000MS);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void gpt_test_stop(void)
{
	Gpt_StopTimer(GPT_PIT_CON_1MS_INSTANCE);
	Gpt_StopTimer(GPT_PIT_CON_10MS_INSTANCE);
	Gpt_StopTimer(GPT_PIT_CON_100MS_INSTANCE);
	Gpt_StopTimer(GPT_PIT_CON_1000MS_INSTANCE);
}

FUNC(void, GPT_CODE) GPT_GTM_TOM_LLD_SetIRQ(void)
{
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_813, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_813, &TOM0_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_813);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_814, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_814, &TOM0_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_814);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_815, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_815, &TOM0_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_815);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_816, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_816, &TOM0_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_816);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_817, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_817, &TOM0_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_817);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_818, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_818, &TOM0_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_818);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_819, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_819, &TOM0_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_819);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_820, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_820, &TOM0_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_820);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_821, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_821, &TOM1_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_821);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_822, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_822, &TOM1_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_822);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_823, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_823, &TOM1_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_823);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_824, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_824, &TOM1_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_824);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_825, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_825, &TOM1_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_825);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_826, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_826, &TOM1_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_826);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_827, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_827, &TOM1_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_827);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_828, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_828, &TOM1_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_828);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_829, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_829, &TOM2_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_829);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_830, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_830, &TOM2_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_830);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_831, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_831, &TOM2_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_831);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_832, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_832, &TOM2_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_832);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_833, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_833, &TOM2_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_833);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_834, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_834, &TOM2_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_834);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_835, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_835, &TOM2_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_835);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_836, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_836, &TOM2_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_836);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_899, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_899, &TOM3_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_899);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_900, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_900, &TOM3_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_900);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_901, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_901, &TOM3_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_901);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_902, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_902, &TOM3_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_902);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_903, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_903, &TOM3_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_903);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_904, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_904, &TOM3_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_904);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_905, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_905, &TOM3_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_905);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_906, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_906, &TOM3_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_906);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_907, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_907, &TOM4_CH0_CH1_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_907);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_908, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_908, &TOM4_CH2_CH3_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_908);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_909, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_909, &TOM4_CH4_CH5_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_909);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_910, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_910, &TOM4_CH6_CH7_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_910);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_911, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_911, &TOM4_CH8_CH9_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_911);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_912, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_912, &TOM4_CH10_CH11_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_912);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_913, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_913, &TOM4_CH12_CH13_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_913);

	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_914, INTR_PRI_38);
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_914, &TOM4_CH14_CH15_ISR);
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_914);
}

FUNC(Std_ReturnType, GPT_CODE) Gpt_Pit_SetIRQ(void)
{
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_226, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_226, &PIT0_CH0_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_226);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_227, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_227, &PIT0_CH1_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_227);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_228, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_228, &PIT0_CH2_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_228);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_229, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_229, &PIT0_CH3_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_229);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_230, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_230, &PIT0_CH4_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_230);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_231, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_231, &PIT0_CH5_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_231);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_232, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_232, &PIT0_CH6_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_232);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_233, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_233, &PIT0_CH7_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_233);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_239, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_239, &RTI_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_239);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_240, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_240, &PIT1_CH0_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_240);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_241, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_241, &PIT1_CH1_ISR);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_241);
}

FUNC(Std_ReturnType, GPT_CODE) Gpt_Stm_SetIRQ(void)
{
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_36, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_36, &STM0_CH0_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_36);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_37, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_37, &STM0_CH1_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_37);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_38, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_38, &STM0_CH2_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_38);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_39, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_39, &STM0_CH3_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_39);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_40, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_40, &STM1_CH0_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_40);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_41, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_41, &STM1_CH1_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_41);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_42, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_42, &STM1_CH2_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_42);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_43, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_43, &STM1_CH3_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_43);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_44, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_44, &STM2_CH0_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_44);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_45, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_45, &STM2_CH1_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_45);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_46, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_46, &STM2_CH2_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_46);
	/*Set interrupt priority*/
	(void)INTC_LLD_Set_IRQ_Priority(INTR_ID_47, INTR_PRI_38);
	/*Install interrupt handler*/
	(void)INTC_LLD_Set_IRQ_Handle(INTR_ID_47, &STM2_CH3_Handler);
	/*Switch interrupt process to current core*/
	(void)INTC_LLD_Set_IRQ_Enable(INTR_ID_47);
}

int gpt_func(int argc, char *agrv[])
{
	static uint8 setIrqFlag = 1;

	if(setIrqFlag)
	{
		gpt_init_test();
		GPT_GTM_TOM_LLD_SetIRQ();
		Gpt_Pit_SetIRQ();
		Gpt_Stm_SetIRQ();
		setIrqFlag = 0;
	}

    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
    }
    else
    {
        if (argc == 2)
        {
            if (!strcmp(agrv[1], "help"))
            {
            	PSPRINTF("CCFC3008\n");
                PSPRINTF("[1 - %d] ----- CMD ------- ID of the test case\n", GPT_TEST_CASE_MAX);
            }
            else
            {
                uint32 id = (uint32)atoi(agrv[1]);
                PSPRINTF("%d\r\n", id);
                if ((id >= 1) && (id < GPT_TEST_CASE_MAX))
                {
                    if (gpt_funcs[id - 1].gptfunc != NULL_PTR)
                    {
                        gpt_funcs[id - 1].gptfunc();
                    }
                    else
                    {
                        PSPRINTF("error: The ID entered does not correspond to the test code\n");
                    }
                }
                else
                {
                    PSPRINTF("error: Input invalid parameters[%d], please output [1 - %d] range parameters\n", id, GPT_TEST_CASE_MAX);
                }
            }
        }
    }
	return 0;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), gpt_test, gpt_func, number of test case);
