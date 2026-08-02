#include "Icu.h"
#include "console.h"
#include "Icu_Cfg.h"
#include "shell.h"
#include "tester_icu.h"
#include <string.h>
#include "eDma_LLDriver.h"
#include "eTPU_LLDrivers.h"
#include "eTPU_HAL_Irq.h"
#include "tester_icu_etpu.h"
#include "Gpt_Stm_LLDriver.h"
//ICU_CONFIG_DECLARATION
extern CONST(Icu_ConfigType, ICU_CONST) Icu_Cfg;

#define FS_ETPU_ENTRY_TABLE  0x0000U
#define FS_ETPU_MISC         0x0E3EBB08U

const static uint32_t etpu_globals[] = {0x000000FFU, 0x00000000U};

const static uint32_t etpu_code[] = { 0x40434049U,0x40434049U,0x405A002EU,0xC088C088U,
                               0xC0884075U,0xC0884066U,0xC0884075U,0xC0884066U,
                               0x4082C088U,0x4082C088U,0x4082C088U,0x4082C088U,
                               0x40824075U,0x40824066U,0x40824075U,0x40824066U,
                               0xC0C9C0C9U,0xC0C9C0C9U,0xC0C9C0C9U,0xC0C9009FU,
                               0x009C008FU,0x40A140C5U,0x40A140C5U,0x40A140C5U,
                               0x40A140C5U,0x40A140C5U,0x40A140C5U,0x40A140C5U,
                               0xC0C9C0C9U,0xC0C9C0C9U,0x40A140C5U,0x40A140C5U,
                               0xF320047FU,0x3BF93FB4U,0x0003301DU,0xF28004BFU,
                               0x00033099U,0xF2C004FFU,0x00033119U,0xF200053FU,
                               0x00033219U,0xF240057FU,0x00033819U,0x9FF37A00U,
                               0xFFFFCCF9U,0x4FEFF6BFU,0x580FF7E5U,0xCFE9F980U,
                               0x0802ABA2U,0xCFFFF980U,0x4FF33FFFU,0xF3A806FFU,
                               0x39FD2FF4U,0x4FF00FFFU,0x39FC2FF4U,0xBFEFFB81U,
                               0x3B1E3FF4U,0xBFF37A85U,0xF3E007FFU,0xFB3F0CFBU,
                               0x4F58FDFEU,0xF7E00D9FU,0xFFFBFCF9U,0x4FF8FBFEU,
                               0xFFFAFCF9U,0xF7E00F7FU,0x4F3FFFFFU,0xBFEFFB84U,
                               0xBFE80A81U,0xBF197A85U,0xBFE80A80U,0xF7E009BFU,
                               0x7C193FDBU,0xBFEFFB84U,0xBFE80A81U,0xBF197A85U,
                               0x7FF83FDBU,0xBFEFFB81U,0x3BF8FFF4U,0xF0C00ABFU,
                               0xF3C00A7FU,0xF7E00A9FU,0x4AFFFFFFU,0x49FFFFFFU,
                               0x6FFFFFFFU,0xF3C00B1FU,0xF7E00B3FU,0x49FFFFFFU,
                               0x4AFFFFFFU,0x6FFFFFFFU,0xBFEFFB84U,0xBFE80A83U,
                               0xBF197A85U,0xCFEFF980U,0xF5000C3FU,0xBFEFFB85U,
                               0x7FF83FDBU,0xBFEFFB82U,0xBFFFFB80U,0xBFEFFB83U,
                               0xF7E009BFU,0xBFFFFB81U,0xCFE8F980U,0x0BF2ABD2U,
                               0xCFFFF980U,0xFFFF3CF9U,0xCFEF7A80U,0x3B1E2FF4U,
                               0xBFEFFB81U,0x3BF8FFF4U,0xF0C00E3FU,0xF7E00E5FU,
                               0x4AFFFFFFU,0x49FFFFFFU,0xBFFE7A84U,0xDFEF3A81U,
                               0xAF1E7A85U,0xCFE8F980U,0x0BF2ABD2U,0xCFFFF980U,
                               0xFFFF3CF9U,0xCFEF7A80U,0x3B1E2FF4U,0xBFEFFB81U,
                               0x3BF8FFF4U,0xF0C0101FU,0xF7E0103FU,0x49FFFFFFU,
                               0x4AFFFFFFU,0xF7C00E5FU,0xBFEFFB85U,0x3BF83FF4U,
                               0xCFE9F980U,0x0802ABA2U,0xCFFFF980U,0x6FFFFF9FU,
                               0xFFC0041FU,0x6FFFFFFFU,0x3BF01FD4U,0x3BF11FD4U,
                               0x3BF71FD4U,0xFFFFCCF9U,0x3BF21FD4U,0xFFF8FCF9U,
                               0x4FF00FFFU,0x5B7FFFF9U,0xCFEFF980U,0xF548131FU,
                               0x593FFFFFU,0xCFEFF980U,0xF508131FU,0x5A5FFFFFU,
                               0x4FF9FFFFU,0xBFFFFF01U,0xFF3FFCFBU,0x47EFF6BFU,
                               0xFFF8FCF9U,0xF7E0123FU,0x4FF33FFFU,0xF7E0121FU,
                               0xFFF9FCF9U,0xBFEFFB81U,0xBDF87A81U,0xBFE80A80U,
                               0x3819FFF4U,0xF480151FU,0xBFFE7A83U,0xF7C0167FU,
                               0xBFFE7A82U,0xFFFF3CF9U,0xF3A0161FU,0xFFFF7CF9U,
                               0xCFEFF885U,0xFFC0115FU,0xCFEFF886U,0xFFC0115FU,
                               0xF3C0167FU,0xFF7FFCFBU,0x47EFF6BFU,0xF240189FU,
                               0xBFEFFB81U,0xBFE80A80U,0x3819FFF4U,0xF480175FU,
                               0xBFF37A83U,0x6FFFFFFFU,0xBFF37A82U,0xFFFF3CF9U,
                               0xF3A0185FU,0xFFFF7CF9U,0xCFEFF885U,0xFFC0115FU,
                               0xCFEFF886U,0xFFC0115FU,0xF3C0189FU,0xFF7FFCFBU,
                               0x47EFF6BFU,0xBFEFFB84U,0x3BF82FF4U,0xF7E0143FU,
                               0x3BFE3FF4U,0xFFC0041FU,0x6FFFFFFFU,0x00000000U,
                               0x00000000U,0x00000000U,0x00000000U,0x00000000U,
};

const static etpu_global_param_t etpuConfigParameter1 =
{
    //ETPU_MISC_DISABLE
	/*MCR register*/
    ETPU_MISC_ENABLE,

	FS_ETPU_MISC,           /*MISC value from eTPU compiler link file*/

    /*Configure eTPU engine A*/
	ETPU_FILTER_CLOCK_DIV8 +
    ETPU_CHAN_FILTER_3SAMPLE +
	FS_ETPU_ENTRY_TABLE,

    /*Configure eTPU engine A timebases*/
    ETPU_TCR2CTL_DIV8 + /*TCR2  8 (7+1)*/	/*PRQA S 0499 */
    (24U << 16U) +     /*TCR2 prescaler of 20 (19+1)*/	/*PRQA S 0499 */
    ETPU_TCR1CTL_DIV2 +
    31U,               /*TCR1 prescaler of 32 (31+1) applied to sysclk/2*/
    0U,

    /*Configure eTPU engine B*/
	ETPU_TCR2CTL_DIV8 +
    ETPU_CHAN_FILTER_3SAMPLE +
	FS_ETPU_ENTRY_TABLE,

    /*Configure eTPU engine B timebases*/
    ETPU_TCR2CTL_DIV8 +
    (24U << 16U) +     /*TCR2 prescaler of 8 (7+1)*/	/*PRQA S 0499 */
    ETPU_TCR1CTL_DIV2 +
    3U,              /*TCR1 prescaler of 4 (3+1)*/
    0U
};

static void ETPU_PIN_INIT(void)
{
    SIUL2.MSCR_IO[204U].R = (0x320C0000U | 0x0DU); //ETPU_A CH0
    SIUL2.MSCR_IO[10U].R = 0x80000U; //ETPU_A CH2
    SIUL2.MSCR_IO[112U].R = (0x320C0000U | 0x0CU); //ETPU_B CH0
    SIUL2.MSCR_IO[1U].R = (0x320C0000U | 0x0CU); //ETPU_C CH21
}


typedef struct{
	uint32 last;
	uint32 final;
}temp_meas_t;
static temp_meas_t temp_meas[100];
static uint32 idd = 0;
static void ETPU_IC_TEST_Callbcak(void)
{
	ETPU_LLD_ClearChannelInterruptFlag(ETPU_INSTANCE_A_B, ETPU_A_CHANNLE(2U));
	if (idd < 100) {
		uint32 u32ChannelTempA = ETPU_LLD_IC_Read_Last_Time(ETPU_INSTANCE_A_B, ETPU_A_CHANNLE(2U));
		uint32 u32ChannelTempB = ETPU_LLD_IC_Read_Final_Time(ETPU_INSTANCE_A_B, ETPU_A_CHANNLE(2U));
		temp_meas[idd].last = u32ChannelTempA;
		temp_meas[idd].final = u32ChannelTempB;
		idd++;
	}
	else
	{
		PSPRINTF("\r\n ETPU_IC_TEST_Callbcak Finish.\r\n");
	}
}

void ETPU_IC_Init(void)
{
#if 1
    uint32_t error_code = 0;
    uint32_t final_time = 0U;
    uint32_t last_time = 0U;
    uint32_t icu_count = 0U;
    uint32_t ips = 0U;
#endif
    uint32_t i;

    static etpu_ic_param_t ic_parameter =
    {
        .priority = ETPU_PRIORITY_MIDDLE,
        .mode = ETPU_IC_MODE_CONT,
        .timebase = ETPU_TCR2,
        .edge = ETPU_IC_ANY_EDGE,
        .max_count = 2U,
    };

    ETPU_PIN_INIT();
#if 1
    eTPU_LLD_SetIRQ(eTPU_A, 0);
    eTPU_LLD_SetIRQ(eTPU_A, 2);
    eTPU_LLD_SetIRQ(eTPU_B, 0);
    eTPU_LLD_SetIRQ(eTPU_C, 0);
#else
#if (IC_USE_INTC_MODE == IC_USE_INTC_ON)
    /*Set interrupt priority*/
    (void)INTC_LLD_Set_IRQ_Priority(INTR_ID_238, INTR_PRI_1);
    /*Install interrupt handler*/
    (void)INTC_LLD_Set_IRQ_Handle(INTR_ID_238, &ETPU_IC_TEST_Callbcak);
    /*Switch interrupt process to current core*/
    (void)INTC_LLD_Set_IRQ_Enable(INTR_ID_238);
#endif
#endif
    /* Clear all ETPU SRAM memories due to ECC */
    for (i =  eTPUInstance[ETPU_INSTANCE_A_B].data_ram_start; i <  eTPUInstance[ETPU_INSTANCE_A_B].data_ram_end; i = i + 4U)
    {
       (*(uint32_t *) i) = 0U;
    }

    if(ETPU_LLD_Init (ETPU_INSTANCE_A_B,
                      (etpu_global_param_t const*)&etpuConfigParameter1,
                      (uint32_t const*) etpu_code,
                      sizeof (etpu_code),
                      (uint32_t const*) etpu_globals,
                      sizeof (etpu_globals)))
    {
        PSPRINTF("EPTU INIT failed \r\n");
        while(1);
    }

    ETPU_LLD_Init (ETPU_INSTANCE_C,
					  (etpu_global_param_t const*)&etpuConfigParameter1,
					  (uint32_t const*) etpu_code,
					  sizeof (etpu_code),
					  (uint32_t const*) etpu_globals,
					  sizeof (etpu_globals));

    ETPU_LLD_TimerStart(ETPU_INSTANCE_A_B);
    ETPU_LLD_TimerStart(ETPU_INSTANCE_C);

   // Icu_Init(&Icu_Cfg);
   // Icu_StartSignalMeasurement(2);
#if 0
    error_code = (uint32_t)ETPU_LLD_IC_Init(ETPU_INSTANCE_A_B,
                                  ETPU_A_CHANNLE(2U),
                                  &ic_parameter);

    if (error_code) {
        while(1);
    }

#if (IC_USE_INTC_MODE == IC_USE_INTC_ON)
    /*Enable etpu channel interrupt*/
	ETPU_LLD_SetInterruptMask_A(ETPU_INSTANCE_A_B, 0xFFFFFFFF);
#endif

#if 0 ///
#if 1
    while(final_time == 0U)
    {
        final_time = (uint32_t)ETPU_LLD_IC_Read_Final_Time(ETPU_INSTANCE_A_B, ETPU_A_CHANNLE(2U));
    }
    last_time = (uint32_t)ETPU_LLD_IC_Read_Last_Time(ETPU_INSTANCE_A_B, ETPU_A_CHANNLE(2U));

    PSPRINTF("\r\n measure final_time = %d\r\n", final_time);
    PSPRINTF("\r\n measure last_time = %d\r\n", last_time);
    PSPRINTF("\r\n measure freq = %d hz\r\n", 1000000U / (final_time - last_time));
#else
    delay_ms(1000);
    icu_count = (uint32_t)ETPU_LLD_IC_Read_Trans_Count(ETPU_INSTANCE_A_B, ETPU_A_CHANNLE(2U));
    PSPRINTF("\r\n measure icu_count = %d\r\n", icu_count);
#endif

    /* Note: Get Channel Input Pin State (PA10(ETPU_A CH2)) */
    i = 20U;
    while(i)
    {
    	ips = eTPUInstance[ETPU_INSTANCE_A_B].eTPU->CHAN[ETPU_A_CHANNLE(2U)].SCR.B.IPS;
    	PSPRINTF("\r\n Channel Input Pin State (PA10(ETPU_A CH2)): %d .\r\n", ips);
    	i--;
    }
#endif
#endif ///
}

#define ICU_MEAS_HANDLE             2
#define ICU_TIMET_HANDLE            2
#define ICU_COUNT_HANDLE            2

void icu_169(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(3);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(3,&DutyCycle);
    Icu_StopSignalMeasurement(3);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_170(void)
{
    uint32 BufferPtr[10];
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(2,ICU_FALLING_EDGE);
    Icu_StartTimestamp(2,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(2);
    u16Icu_value = Icu_GetTimestampIndex(2);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value+1; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    if (((BufferPtr[1] - BufferPtr[0]) > (0.9*100)) && ((BufferPtr[1] - BufferPtr[0]) < (1.1*100)))
	{
		PSPRINTF("timestamp test ok\r\n");
	}
	else
	{
		PSPRINTF("timestamp test not ok\r\n");
	}
    Icu_DeInit();
}

void icu_171(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(5);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(5,&DutyCycle);
    Icu_StopSignalMeasurement(5);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_172(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(6);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(6,&DutyCycle);
    Icu_StopSignalMeasurement(6);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_173(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(7);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(7,&DutyCycle);
    Icu_StopSignalMeasurement(7);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_174(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(8);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(8,&DutyCycle);
    Icu_StopSignalMeasurement(8);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_175(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_176(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_177(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(11);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(11,&DutyCycle);
    Icu_StopSignalMeasurement(11);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_178(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(12);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(12,&DutyCycle);
    Icu_StopSignalMeasurement(12);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_179(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(13);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(13,&DutyCycle);
    Icu_StopSignalMeasurement(13);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_291(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(14);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(14,&DutyCycle);
    Icu_StopSignalMeasurement(14);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_292(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(15);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(15,&DutyCycle);
    Icu_StopSignalMeasurement(15);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_293(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(16);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(16,&DutyCycle);
    Icu_StopSignalMeasurement(16);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_180(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(17);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(17,&DutyCycle);
    Icu_StopSignalMeasurement(17);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_181(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_182(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(19,&DutyCycle);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_183(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(20);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(20,&DutyCycle);
    Icu_StopSignalMeasurement(20);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_184(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(21);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(21,&DutyCycle);
    Icu_StopSignalMeasurement(21);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_185(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(22);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(22,&DutyCycle);
    Icu_StopSignalMeasurement(22);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_186(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(23);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(23,&DutyCycle);
    Icu_StopSignalMeasurement(23);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_187(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(24);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(24,&DutyCycle);
    Icu_StopSignalMeasurement(24);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_188(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(25);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(25,&DutyCycle);
    Icu_StopSignalMeasurement(25);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_189(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(26);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(26,&DutyCycle);
    Icu_StopSignalMeasurement(26);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_190(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(27);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(27,&DutyCycle);
    Icu_StopSignalMeasurement(27);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_191(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(28);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(28,&DutyCycle);
    Icu_StopSignalMeasurement(28);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_192(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(29);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(29,&DutyCycle);
    Icu_StopSignalMeasurement(29);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_193(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(30);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(30,&DutyCycle);
    Icu_StopSignalMeasurement(30);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_194(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(31);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(31,&DutyCycle);
    Icu_StopSignalMeasurement(31);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_195(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(32);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(32,&DutyCycle);
    Icu_StopSignalMeasurement(32);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_196(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(33);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(33,&DutyCycle);
    Icu_StopSignalMeasurement(33);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_197(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(34);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(34,&DutyCycle);
    Icu_StopSignalMeasurement(34);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_198(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(35);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(35,&DutyCycle);
    Icu_StopSignalMeasurement(35);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_199(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(36);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(36,&DutyCycle);
    Icu_StopSignalMeasurement(36);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_200(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(37);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(37,&DutyCycle);
    Icu_StopSignalMeasurement(37);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_201(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(38);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(38,&DutyCycle);
    Icu_StopSignalMeasurement(38);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_202(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(39);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(39,&DutyCycle);
    Icu_StopSignalMeasurement(39);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_203(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(40);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(40,&DutyCycle);
    Icu_StopSignalMeasurement(40);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_204(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(41);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(41,&DutyCycle);
    Icu_StopSignalMeasurement(41);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_205(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(42);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(42,&DutyCycle);
    Icu_StopSignalMeasurement(42);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_206(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(43);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(43,&DutyCycle);
    Icu_StopSignalMeasurement(43);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_207(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(44);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(44,&DutyCycle);
    Icu_StopSignalMeasurement(44);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_208(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(45);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(45,&DutyCycle);
    Icu_StopSignalMeasurement(45);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_209(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(46);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(46,&DutyCycle);
    Icu_StopSignalMeasurement(46);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_210(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(47);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(47,&DutyCycle);
    Icu_StopSignalMeasurement(47);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_211(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(48);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(48,&DutyCycle);
    Icu_StopSignalMeasurement(48);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_212(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(49);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(49,&DutyCycle);
    Icu_StopSignalMeasurement(49);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_213(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(50);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(50,&DutyCycle);
    Icu_StopSignalMeasurement(50);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_214(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(51);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(51,&DutyCycle);
    Icu_StopSignalMeasurement(51);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_215(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(52);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(52,&DutyCycle);
    Icu_StopSignalMeasurement(52);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_216(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(53);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(53,&DutyCycle);
    Icu_StopSignalMeasurement(53);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_217(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(54);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(54,&DutyCycle);
    Icu_StopSignalMeasurement(54);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_218(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(55);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(55,&DutyCycle);
    Icu_StopSignalMeasurement(55);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_219(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(56);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(56,&DutyCycle);
    Icu_StopSignalMeasurement(56);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_220(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(57);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(57,&DutyCycle);
    Icu_StopSignalMeasurement(57);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_221(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(0);
    Icu_EnableEdgeCount(0);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(0);
    EdgeNumber = Icu_GetEdgeNumbers(0);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_222(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(1);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value = Icu_GetTimeElapsed(1);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(1);
    u32Icu_value = Icu_GetTimeElapsed(1);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(1);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}

void icu_223(void)
{
	   VAR(boolean, AUTOMATIC) bstatus = FALSE;
	   Icu_Init(&Icu_Cfg);
	   Icu_SetActivationCondition(2,ICU_FALLING_EDGE);
	   Icu_EnableNotification(2);
	   Icu_EnableWakeup(2);
	   bstatus = Icu_GetWakeupStatus(2);
	   PSPRINTF("%s  is E_OK, bstatus:%d\r\n",__FUNCTION__,bstatus);
	   Icu_DeInit();
}

void icu_224(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(3);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(3,&DutyCycle);
    Icu_StopSignalMeasurement(3);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_225(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(4);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(4,&DutyCycle);
    Icu_StopSignalMeasurement(4);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_226(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(5);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(5,&DutyCycle);
    Icu_StopSignalMeasurement(5);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_227(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(6);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(6,&DutyCycle);
    Icu_StopSignalMeasurement(6);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_228(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(7);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(7,&DutyCycle);
    Icu_StopSignalMeasurement(7);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_229(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(8);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(8,&DutyCycle);
    Icu_StopSignalMeasurement(8);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_230(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(9);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(9,&DutyCycle);
    Icu_StopSignalMeasurement(9);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_231(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(10);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(10,&DutyCycle);
    Icu_StopSignalMeasurement(10);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_232(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(11);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(11,&DutyCycle);
    Icu_StopSignalMeasurement(11);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_233(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(12);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(12,&DutyCycle);
    Icu_StopSignalMeasurement(12);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_234(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(13);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(13,&DutyCycle);
    Icu_StopSignalMeasurement(13);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_235(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(14);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(14,&DutyCycle);
    Icu_StopSignalMeasurement(14);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_236(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(15);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(15,&DutyCycle);
    Icu_StopSignalMeasurement(15);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_237(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(16);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(16,&DutyCycle);
    Icu_StopSignalMeasurement(16);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_238(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(17);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(17,&DutyCycle);
    Icu_StopSignalMeasurement(17);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_239(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(18);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(18,&DutyCycle);
    Icu_StopSignalMeasurement(18);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_240(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(19);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(19,&DutyCycle);
    Icu_StopSignalMeasurement(19);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_241(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(20);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(20,&DutyCycle);
    Icu_StopSignalMeasurement(20);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_242(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(21);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(21,&DutyCycle);
    Icu_StopSignalMeasurement(21);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_243(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(22);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(22,&DutyCycle);
    Icu_StopSignalMeasurement(22);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_244(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(23);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(23,&DutyCycle);
    Icu_StopSignalMeasurement(23);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_245(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(24);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(24,&DutyCycle);
    Icu_StopSignalMeasurement(24);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_246(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(25);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(25,&DutyCycle);
    Icu_StopSignalMeasurement(25);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_247(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(26);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(26,&DutyCycle);
    Icu_StopSignalMeasurement(26);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_248(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(27);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(27,&DutyCycle);
    Icu_StopSignalMeasurement(27);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_249(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(28);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(28,&DutyCycle);
    Icu_StopSignalMeasurement(28);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_255(void)
{
    uint32 BufferPtr[10]= {0};
    uint32 i = 0;
    uint32 delay = 500U;
    VAR(Icu_IndexType, AUTOMATIC) u16Icu_value = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_SetActivationCondition(30,ICU_FALLING_EDGE);
    Icu_StartTimestamp(30,BufferPtr,10,100);
    Gpt_Stm_LLD_DelayMs(STM1,delay);
    Icu_StopTimestamp(30);
    u16Icu_value = Icu_GetTimestampIndex(30);
    PSPRINTF("index:%d, timestamp: ",u16Icu_value);
    for(i=0; i<u16Icu_value+1; i++)
    {
    	PSPRINTF("%lu ", BufferPtr[i]);
    }
    PSPRINTF("\r\n");
    if (((BufferPtr[1] - BufferPtr[0]) > (0.9*100)) && ((BufferPtr[1] - BufferPtr[0]) < (1.1*100)))
    {
        PSPRINTF("timestamp test ok\r\n");
    }
    else
    {
        PSPRINTF("timestamp test not ok\r\n");
    }
    Icu_DeInit();
}

void icu_254(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(29);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(29,&DutyCycle);
    Icu_StopSignalMeasurement(29);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_252(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(93);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(93,&DutyCycle);
    Icu_StopSignalMeasurement(93);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_253(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(94);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(94,&DutyCycle);
    Icu_StopSignalMeasurement(94);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_250(void)
{
    Icu_DutyCycleType DutyCycle = {0};
    Icu_Init(&Icu_Cfg);
    Icu_StartSignalMeasurement(95);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_GetDutyCycleValues(95,&DutyCycle);
    Icu_StopSignalMeasurement(95);
    PSPRINTF("%d %d\n",DutyCycle.ActiveTime,DutyCycle.PeriodTime);
    //Icu_DeInit();
}

void icu_251(void)
{
    Icu_EdgeNumberType EdgeNumber = 0;
    Icu_Init(&Icu_Cfg);
    Icu_SetMode(0);
    Icu_ResetEdgeCount(0);
    Icu_EnableEdgeCount(0);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Icu_DisableEdgeCount(0);
    EdgeNumber = Icu_GetEdgeNumbers(0);
    PSPRINTF("%d\n",EdgeNumber);
}

void icu_256(void)
{
    VAR(uint32, AUTOMATIC) u32Icu_state = 0U;
    Icu_Init(&Icu_Cfg);
    Icu_EnableEdgeDetection(1);
    u32Icu_state = Icu_GetInputState(1);
    PSPRINTF("%d\n",u32Icu_state);
    Gpt_Stm_LLD_DelayMs(STM1,10U);
    Icu_EnableNotification(1);
    u32Icu_state = Icu_GetInputState(1);
    PSPRINTF("%d\n",u32Icu_state);
    Gpt_Stm_LLD_DelayMs(STM1,30U);
    u32Icu_state = Icu_GetInputState(1);
    PSPRINTF("%d\n",u32Icu_state);
    Icu_SetActivationCondition(1,ICU_FALLING_EDGE);
    Icu_EnableNotification(1);
    Gpt_Stm_LLD_DelayMs(STM1,10U);
    u32Icu_state = Icu_GetInputState(1);
    PSPRINTF("%d\n",u32Icu_state);
    Icu_DeInit();
}

void icu_257(void)
{
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value = 0U;
    VAR(Icu_ValueType, AUTOMATIC) u32Icu_value1 = 0U;
    Icu_Init(&Icu_Cfg);
    /*SignalMeasurement  LowTime*/
    Icu_StartSignalMeasurement(4);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value = Icu_GetTimeElapsed(4);
    PSPRINTF("%d\n",u32Icu_value);
    Icu_StopSignalMeasurement(4);
    u32Icu_value = Icu_GetTimeElapsed(4);
    PSPRINTF("%d\n",u32Icu_value);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    u32Icu_value1 = Icu_GetTimeElapsed(4);
    PSPRINTF("%d\n",u32Icu_value1);/*0*/

    if (u32Icu_value && (u32Icu_value1 == 0))
    {
        PSPRINTF("elapse test ok\n");
    }
    else
    {
        PSPRINTF("elapse test not ok\n");
    }
}
