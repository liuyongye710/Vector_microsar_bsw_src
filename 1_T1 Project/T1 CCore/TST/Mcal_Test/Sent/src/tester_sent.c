#include "Sent.h"
#include "Sent_LLDriver.h"
#include "intc_lld.h"
#include "Sent_Irq.h"
#include "tester_sent.h"
#include "shell.h"
#include "console.h"

#include <string.h>

#define SENT_PORT_TEST 0

#define FEATURE_SRX_IRQS {{{SENT0_CH0_FAST_IRQ564, SENT0_CH0_SLOW_IRQ565, SENT0_CH0_ERR_IRQ566},\
                          {SENT0_CH1_FAST_IRQ567, SENT0_CH1_SLOW_IRQ568, SENT0_CH1_ERR_IRQ569},\
						  {SENT0_CH2_FAST_IRQ570, SENT0_CH2_SLOW_IRQ571, SENT0_CH2_ERR_IRQ572},\
						  {SENT0_CH3_FAST_IRQ573, SENT0_CH3_SLOW_IRQ574, SENT0_CH3_ERR_IRQ575},\
						  {SENT0_CH4_FAST_IRQ576, SENT0_CH4_SLOW_IRQ577, SENT0_CH4_ERR_IRQ578},\
						  {SENT0_CH5_FAST_IRQ594, SENT0_CH5_SLOW_IRQ595, SENT0_CH5_ERR_IRQ596},\
						  {SENT0_CH6_FAST_IRQ597, SENT0_CH6_SLOW_IRQ598, SENT0_CH6_ERR_IRQ599},\
						  {SENT0_CH7_FAST_IRQ600, SENT0_CH7_SLOW_IRQ601, SENT0_CH7_ERR_IRQ602},},\
                          {{SENT1_CH0_FAST_IRQ579, SENT1_CH0_SLOW_IRQ580, SENT1_CH0_ERR_IRQ581},\
						   {SENT1_CH1_FAST_IRQ582, SENT1_CH1_SLOW_IRQ583, SENT1_CH1_ERR_IRQ584},\
						   {SENT1_CH2_FAST_IRQ585, SENT1_CH2_SLOW_IRQ586, SENT1_CH2_ERR_IRQ587},\
						   {SENT1_CH3_FAST_IRQ588, SENT1_CH3_SLOW_IRQ589, SENT1_CH3_ERR_IRQ590},\
						   {SENT1_CH4_FAST_IRQ591, SENT1_CH4_SLOW_IRQ592, SENT1_CH4_ERR_IRQ593},\
						   {SENT1_CH5_FAST_IRQ603, SENT1_CH5_SLOW_IRQ604, SENT1_CH5_ERR_IRQ605},\
						   {SENT1_CH6_FAST_IRQ606, SENT1_CH6_SLOW_IRQ607, SENT1_CH6_ERR_IRQ608},\
                          {NotAvail_IRQn, NotAvail_IRQn, NotAvail_IRQn}}}
/**
 * Array containing interrupt mappings.
 */
static const IntrId s_srxInterruptMappings[SRX_INSTANCE_COUNT][8U][3U] = FEATURE_SRX_IRQS;

void SRX_LLD_IRQ_EnableIRQ(const uint32 instance, const uint32 channel, const srx_interrupt_id_t id);
void Sensor_srxNotification(uint8_t channel, srx_callback_type_t type);
int sent_func(int argc, char *agrv[]);

#define SENT_TEST_CASE_MAX 20
static SentfuncMachine sent_funcs[] = {
    {"Sent_001", TEM00441_ReadIntFastMsg},
    {"Sent_002", TEM00441_ReadIntSlowMsg},
    {"Sent_003", Sensor0280B_ReadIntFastMsg},
    {"Sent_004", Sensor0280B_ReadIntSlowMsg},
    {"Sent_005", sent_test005},
    {"Sent_006", sent_test006},
    {"Sent_007", sent_test007},
    {"Sent_008", sent_test008},
    {"Sent_009", sent_test009},
    {"Sent_010", sent_test010},
    {"Sent_011", sent_test011},
    {"Sent_012", sent_test012},
    {"Sent_013", sent_test013},
    {"Sent_014", sent_test014},
    {"Sent_015", sent_test015},
    {"Sent_016", sent_test016},
    {"Sent_017", sent_test017},
    {"Sent_018", sent_test018},
    {"Sent_019", sent_test019},
};

void SRX_LLD_IRQ_EnableIRQ(const uint32 instance, const uint32 channel, const srx_interrupt_id_t id)
{
       (void)id; /* Shared */

    (void)INTC_LLD_Set_IRQ_Enable(s_srxInterruptMappings[instance][channel][id]);
    (void)INTC_LLD_Set_IRQ_Priority(s_srxInterruptMappings[instance][channel][id], INTR_PRI_15);
	if(instance == 0U)
	{
		if(channel == 0U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH0_IRQHandler);//install IRQ handler
		}
		else if(channel == 1U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH1_IRQHandler);//install IRQ handler
		}
		else if(channel == 2U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH2_IRQHandler);//install IRQ handler
		}
		else if(channel == 3U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH3_IRQHandler);//install IRQ handler
		}
		else if(channel == 4U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH4_IRQHandler);//install IRQ handler
		}
		else if(channel == 5U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH5_IRQHandler);//install IRQ handler
		}
		else if(channel == 6U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH6_IRQHandler);//install IRQ handler
		}
		else
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX0_CH7_IRQHandler);//install IRQ handler
		}
	}
	else
	{
		if(channel == 0U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH0_IRQHandler);//install IRQ handler
		}
		else if(channel == 1U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH1_IRQHandler);//install IRQ handler
		}
		else if(channel == 2U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH2_IRQHandler);//install IRQ handler
		}
		else if(channel == 3U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH3_IRQHandler);//install IRQ handler
		}
		else if(channel == 4U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH4_IRQHandler);//install IRQ handler
		}
		else if(channel == 5U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH5_IRQHandler);//install IRQ handler
		}
		else if(channel == 6U)
		{
		    (void)INTC_LLD_Set_IRQ_Handle(s_srxInterruptMappings[instance][channel][id], &SRX1_CH6_IRQHandler);//install IRQ handler
		}
		else
		{
			//do nothing
		}
	}
}

#if (SENT_PORT_TEST == 1)
static void SRX_GPIO_Init(void)/*PRQA S 0554*/
{

	//SENT7_0 PM[14] input
	SIUL2.MSCR_IO[206].R = 0x308C0000;
	SIUL2.MSCR_MUX[288].R = 2;

	//SENT6_0 PM[12] input
	SIUL2.MSCR_IO[204].R = 0x308C0000;
	SIUL2.MSCR_MUX[287].R = 2;

	//SENT5_0 PA[12] input
	SIUL2.MSCR_IO[12].R = 0x308C0000;
	SIUL2.MSCR_MUX[286].R = 1;

	//SENT4_0 PE[4] input
	SIUL2.MSCR_IO[68].R = 0x308C0000;
	SIUL2.MSCR_MUX[284].R = 1;

	//SENT3_0 PC[6] input
	SIUL2.MSCR_IO[38].R = 0x308C0000;
	SIUL2.MSCR_MUX[279].R = 2;

	//SENT2_0 PE[0] input
	SIUL2.MSCR_IO[64].R = 0x308C0000;
	SIUL2.MSCR_MUX[278].R = 1;

	//SENT1_0 PC[0] input
	SIUL2.MSCR_IO[32].R = 0x308C0000;
	SIUL2.MSCR_MUX[277].R = 1;

	//SENT0_0 PC[1] input
	SIUL2.MSCR_IO[33].R = 0x308C0000;
	SIUL2.MSCR_MUX[276].R = 1;

	//SENT0_1 PI[1] input
	SIUL2.MSCR_IO[129].R = 0x308C0000;
	SIUL2.MSCR_MUX[280].R = 3;


	//SENT0_1 PE[2] input
//	SIUL2.MSCR_IO[66].R = 0x308C0000;
//	SIUL2.MSCR_MUX[280].R = 1;


	//SENT1_1 PD[12] input
	SIUL2.MSCR_IO[60].R = 0x308C0000;
	SIUL2.MSCR_MUX[281].R = 1;

	//SENT2_1 PG[0] input
	SIUL2.MSCR_IO[96].R = 0x308C0000;
	SIUL2.MSCR_MUX[282].R = 1;

	//SENT3_1 PB[13] input
	SIUL2.MSCR_IO[29].R = 0x308C0000;
	SIUL2.MSCR_MUX[283].R = 3;

	//SENT4_1 PD[13] input
	SIUL2.MSCR_IO[61].R = 0x308C0000;
	SIUL2.MSCR_MUX[285].R = 1;

	//SENT5_1 PA[11] input
	SIUL2.MSCR_IO[11].R = 0x308C0000;
	SIUL2.MSCR_MUX[289].R = 1;

	//SENT6_1 PN[11] input
	SIUL2.MSCR_IO[219].R = 0x308C0000;
	SIUL2.MSCR_MUX[290].R = 2;
	
	//SENT6_1 PR[15] input
//	SIUL2.MSCR_IO[256].R = 0x00080000;
//	SIUL2.MSCR_MUX[290].R = 3;

}

#endif
typedef struct {
    float pressure;
    float temperature;
} tem00441_t;

typedef struct {
    float pressure;
    float temperature;
    float humidity;
    uint32 mass;
} sensor0280B_t;

typedef struct {
	uint32 fast_convert_state[15];
	uint32 slow_convert_state[15];
} convert_status;

tem00441_t result;
sensor0280B_t sensor_result;

static convert_status convert_sta;

static Sent_RxSerialDataType sentSlowSerialDataBuffer[1];

/* Active event flags */
//static uint32_t srxActiveEvents;

uint32 SensorData = 0;
void Sensor_srxNotification(uint8_t channel, srx_callback_type_t type)
 {
//	uint8 u8SentModule = (uint8)(((channel) >> (uint8)5) & (uint8)0x7);
//	uint8 u8SentChannel = (uint8)((channel) & (uint8)0x1F);
     switch(type)
     {
     case SRX_CALLBACK_SLOW_DMA_RX_COMPLETE:
         /* Convert buffer to fast messages */
         //SRX_LLD_GetSlowMsgFromRaw(&srxSlowMessageBuffer[0], &srxRawMessageBuffer_slow[0]);
         convert_sta.slow_convert_state[channel] = STATUS_SUCCESS;
         break;

     case SRX_CALLBACK_FAST_DMA_RX_COMPLETE:
         /* Convert buffer to fast messages */
        //SRX_LLD_GetFastMsgFromRaw(&srxFastMessageBuffer, &srxRawMessageBuffer_fast[0]);
        convert_sta.fast_convert_state[channel] = STATUS_SUCCESS;
         break;

     case SRX_CALLBACK_SLOW_RX_COMPLETE:
    	 Sent_ReadSerialData(channel, sentSlowSerialDataBuffer);
         convert_sta.slow_convert_state[channel] = STATUS_SUCCESS;
         break;

     case SRX_CALLBACK_FAST_RX_COMPLETE:
     {
    	 SensorData = Sent_ReadData(channel);
         convert_sta.fast_convert_state[channel] = STATUS_SUCCESS;
         break;
     }
     case SRX_CALLBACK_RX_ERROR:
         //(void)SRX_LLD_GetEvents(u8SentModule, u8SentChannel, &srxActiveEvents);
         break;

     default:
         //*(uint32_t*) param = (uint8_t)STATUS_ERROR;
         break;
     }
 }

static void TEM00441Convert(tem00441_t * tem, uint32 data)
{
    /* Get status field */
//	tem->status = msg->statusField;

	data = data & (SRX_FMSG_DATA_DNIB1_MASK
				| SRX_FMSG_DATA_DNIB2_MASK
				| SRX_FMSG_DATA_DNIB3_MASK
				| SRX_FMSG_DATA_DNIB4_MASK
				| SRX_FMSG_DATA_DNIB5_MASK
				| SRX_FMSG_DATA_DNIB6_MASK);

	tem->pressure = (float)((((((data)>>12) & 0xFFF)*390) - 38240)/3703.0); /* Scale based on value */

    /* Compute temperature */
	tem->temperature = (float)((((data & 0xFu)<<8)|((data & 0xF0u))|((data & 0xF00u)>>8))/8.0 - 73.15);
}

static void Sersor0280B_FastConvert(sensor0280B_t * sensor, uint32 data)
{
    /* Get status field */
//	tem->status = msg->statusField;

	data = data & (SRX_FMSG_DATA_DNIB1_MASK
				| SRX_FMSG_DATA_DNIB2_MASK
				| SRX_FMSG_DATA_DNIB3_MASK
				| SRX_FMSG_DATA_DNIB4_MASK
				| SRX_FMSG_DATA_DNIB5_MASK
				| SRX_FMSG_DATA_DNIB6_MASK);

	float pre = (float)((data) & 0x3FF);
	uint32 mass = ((data >> 10) & 0x3FFFU);

	sensor->pressure = (float)(((pre - 47) / 9.23f) + 15); /* Scale based on value */
	sensor->mass = mass;
}

static void Sersor0280B_SlowConvert(sensor0280B_t * sensor, Sent_RxSerialDataType* DataBuffer)
{
	sensor->temperature = (float)(((DataBuffer->Data / 8.0) + 200.0) - 273.15);

	sensor->humidity = (float)((DataBuffer->Data - 444.0) * 0.01 / 32.0);
}

extern CONST(Sent_ConfigType, SENT_CONST)SentChannelConfigSet;

void TEM00441_ReadIntFastMsg()
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)2);


	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(0, SENT_ENABLE);

	while(1)
	{
		delay_ms(1000);
		while(convert_sta.fast_convert_state[0] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};

		/* In DMA mode a notification will be received on each successful transfer.
		 * Please see srxNotification function for more details. */
		/* Convert values */
		TEM00441Convert(&result, SensorData);
		convert_sta.fast_convert_state[0] = (uint8_t)STATUS_ERROR;

		/* print out */
		PSPRINTF("Pressure: %3.3f Kpa uT\nTemperature: %3.3f C\n\n",
					(double)result.pressure,
					(double)result.temperature);
	}
}

void TEM00441_ReadIntSlowMsg()
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(0, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.slow_convert_state[0] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};

		convert_sta.slow_convert_state[0] = (uint8_t)STATUS_ERROR;
		/* print out */
		PSPRINTF("id: 0x%x ",sentSlowSerialDataBuffer[0].MsgId);
		PSPRINTF("data: %d\r\n", sentSlowSerialDataBuffer[0].Data);
	}
}
void Sensor0280B_ReadIntFastMsg()
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif

	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(0, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.fast_convert_state[0] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};

		/* In DMA mode a notification will be received on each successful transfer.
		 * Please see srxNotification function for more details. */
		/* Convert values */
		Sersor0280B_FastConvert(&sensor_result, SensorData);
		convert_sta.fast_convert_state[0] = (uint8_t)STATUS_ERROR;

		/* print out */
		PSPRINTF("Pressure: %3.3f Kpa uT\n mass: %d\n\n",
				(double)sensor_result.pressure,
				sensor_result.mass);
	}
}
void Sensor0280B_ReadIntSlowMsg()
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif

	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(1,6,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(0, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.slow_convert_state[0] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};
		convert_sta.slow_convert_state[0] = (uint8_t)STATUS_ERROR;
		Sersor0280B_SlowConvert(&sensor_result, &sentSlowSerialDataBuffer[0]);

		/* print out */
		PSPRINTF("id: 0x%x, data: %x\r\n",sentSlowSerialDataBuffer[0].MsgId, sentSlowSerialDataBuffer[0].Data);
		//PSPRINTF("sensor->temperature: %3.3f\r\n", sensor_result.temperature);
	}
}

void sent_test005(void)
{
	Sent_Init(NULL_PTR);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test006(void)
{
	Sent_Init(&SentChannelConfigSet);
	Sent_Init(&SentChannelConfigSet);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test007(void)
{
	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(1, SENT_ENABLE);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test008(void)
{
	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(0, (Sent_StatType)3);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}
void sent_test009(void)
{
	Sent_Init(&SentChannelConfigSet);
	(void)Sent_ReadData(1);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}
void sent_test010(void)
{
	Sent_Init(&SentChannelConfigSet);
	Sent_RxSerialDataType rxbuffer;
	Sent_ReadSerialData(1, &rxbuffer);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test011(void)
{
	Sent_Init(&SentChannelConfigSet);
	Sent_ReadSerialData(0, NULL_PTR);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test012(void)
{
	Sent_GetVersionInfo(NULL_PTR);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test013(void)
{
	Std_VersionInfoType versioninfo;

	Sent_GetVersionInfo(&versioninfo);

	PSPRINTF("vendorID[%d] moduleID[%d] sw_major_version[%d] "
        "sw_minor_version[%d] sw_patch_version[%d]\r\n",
    versioninfo.vendorID, versioninfo.moduleID,
    versioninfo.sw_major_version, versioninfo.sw_minor_version,
    versioninfo.sw_patch_version);
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test014(void)
{
	Sent_DeInit();
	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}

void sent_test015(void)
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif
	SRX_LLD_IRQ_EnableIRQ(0,6,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(0,6,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(0,6,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(1, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.slow_convert_state[1] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};
		convert_sta.slow_convert_state[1] = (uint8_t)STATUS_ERROR;
		/* print out */
		PSPRINTF("id: 0x%x ",sentSlowSerialDataBuffer[0].MsgId);
		PSPRINTF("data: %d\r\n", sentSlowSerialDataBuffer[0].Data);
	}
}

void sent_test016(void)
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif

	SRX_LLD_IRQ_EnableIRQ(0,6,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(0,6,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(0,6,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(1, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.fast_convert_state[1] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};

		/* In DMA mode a notification will be received on each successful transfer.
		 * Please see srxNotification function for more details. */
		/* Convert values */
		Sersor0280B_FastConvert(&sensor_result, SensorData);
		convert_sta.fast_convert_state[1] = (uint8_t)STATUS_ERROR;

		/* print out */
		PSPRINTF("Pressure: %3.3f Kpa uT\n mass: %d\n\n",
				(double)sensor_result.pressure,
				sensor_result.mass);
	}
	
}

void sent_test017(void)
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif
	SRX_LLD_IRQ_EnableIRQ(0,0,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(0,0,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(0,0,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(2, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.slow_convert_state[2] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};
		convert_sta.slow_convert_state[2] = (uint8_t)STATUS_ERROR;
		/* print out */
		PSPRINTF("id: 0x%x ",sentSlowSerialDataBuffer[0].MsgId);
		PSPRINTF("data: %d\r\n", sentSlowSerialDataBuffer[0].Data);
	}
	
}

void sent_test018(void)
{
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif

	SRX_LLD_IRQ_EnableIRQ(0,0,(srx_interrupt_id_t)0);
	SRX_LLD_IRQ_EnableIRQ(0,0,(srx_interrupt_id_t)1);
	SRX_LLD_IRQ_EnableIRQ(0,0,(srx_interrupt_id_t)2);

	Sent_Init(&SentChannelConfigSet);
	Sent_SetChannel(2, SENT_ENABLE);

	while(1)
	{

		delay_ms(1000);
		while(convert_sta.fast_convert_state[2] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
        {};

		/* In DMA mode a notification will be received on each successful transfer.
		 * Please see srxNotification function for more details. */
		/* Convert values */
		Sersor0280B_FastConvert(&sensor_result, SensorData);
		convert_sta.fast_convert_state[2] = (uint8_t)STATUS_ERROR;

		/* print out */
		PSPRINTF("Pressure: %3.3f Kpa uT\n mass: %d\n\n",
				(double)sensor_result.pressure,
				sensor_result.mass);
	}
	
}

void sent_test019(void)
{
	static uint8 cnt = 0;
#if (SENT_PORT_TEST == 1)
	SRX_GPIO_Init();
#endif

	for(uint8 i = 0; i < 8; i++)
	{
		SRX_LLD_IRQ_EnableIRQ(0,i,(srx_interrupt_id_t)0);
		SRX_LLD_IRQ_EnableIRQ(0,i,(srx_interrupt_id_t)1);
		SRX_LLD_IRQ_EnableIRQ(0,i,(srx_interrupt_id_t)2);
	}

	for(uint8 i = 0; i < 7; i++)
	{
		SRX_LLD_IRQ_EnableIRQ(1,i,(srx_interrupt_id_t)0);
		SRX_LLD_IRQ_EnableIRQ(1,i,(srx_interrupt_id_t)1);
		SRX_LLD_IRQ_EnableIRQ(1,i,(srx_interrupt_id_t)2);
	}

	Sent_Init(&SentChannelConfigSet);
	for(uint8 i = 0; i < 15; i++)
	{
		Sent_SetChannel(i, SENT_ENABLE);

		while(1)
		{

			cnt++;
			PSPRINTF("<----The current test channel is: %d, cnt is: %d---->\n\n",i, cnt);
			delay_ms(500);
			while(convert_sta.fast_convert_state[i] == (uint8_t)STATUS_ERROR)/*PRQA S 2872*/
	        {};

			/* In DMA mode a notification will be received on each successful transfer.
			 * Please see srxNotification function for more details. */
			/* Convert values */
			Sersor0280B_FastConvert(&sensor_result, SensorData);
			convert_sta.fast_convert_state[i] = (uint8_t)STATUS_ERROR;

			/* print out */
			PSPRINTF("Pressure: %3.3f Kpa uT\n mass: %d\n\n",
					(double)sensor_result.pressure,
					sensor_result.mass);
			if(cnt >= 5)
			{
				cnt = 0;
				break;
			}
		}
	}


	PSPRINTF("%s is E_OK\r\n", __FUNCTION__);
}



int sent_func(int argc, char *agrv[])
{

	static uint8 setIrqFlag[3] = {0};

	uint8 temp =2u;
	if(setIrqFlag[temp] == 0)
	{
		for(uint8 i = 0; i < 15; i++)
		{
			convert_sta.slow_convert_state[i] = (uint8_t)STATUS_ERROR;
			convert_sta.fast_convert_state[i] = (uint8_t)STATUS_ERROR;
		}
		setIrqFlag[temp] = 1;
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
                PSPRINTF("[1 - %d] ----- CMD ------- ID of the test case\n", SENT_TEST_CASE_MAX);
            }
            else
            {
                uint32 id = (uint32)atoi(agrv[1]);
                PSPRINTF("%d\r\n", id);
                if ((id >= 1) && (id < SENT_TEST_CASE_MAX))
                {
                    if (sent_funcs[id - 1].sentfunc != NULL_PTR)
                    {
                    	sent_funcs[id - 1].sentfunc();
                    }
                    else
                    {
                        PSPRINTF("error: The ID entered does not correspond to the test code\n");
                    }
                }
                else
                {
                    PSPRINTF("error: Input invalid parameters[%d], please output [1 - %d] range parameters\n", id, SENT_TEST_CASE_MAX);
                }
            }
        }
    }
	return 0;
}

#if defined(__GNUC__) || defined(__HIGHTEC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), sent_test, sent_func, number of test case);
#if defined(__GNUC__) || defined(__HIGHTEC__)
#pragma GCC diagnostic pop
#endif
