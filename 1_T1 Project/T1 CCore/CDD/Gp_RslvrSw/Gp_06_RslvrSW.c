//#include "Gp_06_RslvrSW.h"
#include "intc_lld.h"
#include "Sdadc_Irq.h"
#if 0
static const uint32 PwmP_Table_Rad[32] = {
							125,149,171,191,208,222,232,238,\
							239,236,228,216,200,181,160,137,\
							114,90,68,48,31,17,7,1,\
							0,3,11,23,39,58,79,102
							};

static const uint32 PwmN_Table_Rad[32] = {
							114,90,68,48,31,17,7,1,\
							0,3,11,23,39,58,79,102,\
							125,149,171,191,208,222,232,238,\
							239,236,228,216,200,181,160,137
							};
#endif
static const uint32 PwmP_Table_Rad[32] = {
					134,159,182,204,222,237,248,254,\
					255,252,243,230,213,193,171,146,\
					121,96,73,51,33,18,7,1,\
					0,3,12,25,42,62,84,109
							};

static const uint32 PwmN_Table_Rad[32] = {
					121,96,73,51,33,18,7,1,\
					0,3,12,25,42,62,84,109,\
					134,159,182,204,222,237,248,254,\
					255,252,243,230,213,193,171,146
							};


uint32 (*MCS_SIN_Buffer)[32];
uint32 (*MCS_Cos_Buffer)[32];
int mcssin;
int mcscos;
int mcssin_temp;
int mcscos_temp;
uint32 *SinValue;
uint32 *CosValue;
uint32 *Gp_RslvrSw_Mcs_SinValShiftNum_u32;
uint32 SDADC_TIMESTAMP;


#define	UI32_RSLVRSW_REG_MCS3_STRG			(*(uint32*)0xFFD3302C)		/*MCS2 STRG register*/

#define PUI32_RSLVRSW_MCS3_INSIN_ADDR 	    (0xFFD50044U)	    /*variable insin address*/
#define PUI32_RSLVRSW_MCS3_INCOS_ADDR 	    (0xFFD500C4U)	    /*variable incos address*/

#define PUI32_RSLVRSW_MCS3_OUTSIN_ADDR 	    (0xFFD50024U)	    /*variable insin address*/
#define PUI32_RSLVRSW_MCS3_OUTCOS_ADDR 	    (0xFFD50028U)	    /*variable incos address*/

#define PUI32_RSLVRSW_MCS3_CROSSCNT_ADDR 	(0xFFD5044cU)	    /*variable incos address*/

#define PUI32_RSLVRSW_MCS3_MAIN_ADDR		(0xFFD50450U)	    /*variable incos address*/

extern void Irq_DsadcSMA_Core2(void);
unsigned int read_data = 0;
void EMIOS_DMA_INIT(uint32_t src_addr, uint32_t des_addr)
{
	//DMA CH16-23
	eDMA_0.TCD[16].SADDR.R = src_addr;
	eDMA_0.TCD[16].ATTR.R = 0x0202;
	eDMA_0.TCD[16].SOFF.R = 0;
	eDMA_0.TCD[16].DOFF.R = 0;
	eDMA_0.TCD[16].NBYTES.MLNO.R = 0x4;
	eDMA_0.TCD[16].SLAST.R = 0;
	eDMA_0.TCD[16].DLASTSGA.R = 0;
	eDMA_0.TCD[16].DADDR.R = des_addr;
	eDMA_0.TCD[16].CITER.ELINKNO.R = 0x01;
	eDMA_0.TCD[16].BITER.ELINKNO.R = 0x01;
	eDMA_0.TCD[16].CSR.R = 0x0;
	eDMA_0.TCD[16].CSR.B.INTMAJOR = 0x1;

	//Source request select ATOM1_0 IRQ
	DMAMUX_2.CHCFG[0].B.ENBL = 1;
	DMAMUX_2.CHCFG[0].B.SOURCE = 23;

	//enable CH16 DMA request
	eDMA_0.SERQ.R = 16;
}
void Gp_06_RslvrSW_Init(void)
{

	EMIOS_DMA_INIT(&EMIOS_0.UC[7].CNT.R, &read_data);


    SinValue=PUI32_RSLVRSW_MCS3_OUTSIN_ADDR;
    CosValue=PUI32_RSLVRSW_MCS3_OUTCOS_ADDR;
    MCS_SIN_Buffer=PUI32_RSLVRSW_MCS3_INSIN_ADDR;
    MCS_Cos_Buffer=PUI32_RSLVRSW_MCS3_INCOS_ADDR;
    Gp_RslvrSw_Mcs_SinValShiftNum_u32=PUI32_RSLVRSW_MCS3_CROSSCNT_ADDR;



	//INTC_LLD_Set_IRQ_Handle(DMA0_CH3_IRQ56, &Irq_DsadcSMA_Core2);
	//INTC_LLD_Set_IRQ_Priority(DMA0_CH3_IRQ56, INTR_PRI_58);
	//INTC_LLD_Set_IRQ_Enable(DMA0_CH3_IRQ56);

	/*FIFO initialization*/
	GTM_FIFO_0.CHANNEL[2].CTRL.B.RBM=1;//Ring buffer mode
	GTM_FIFO_0.CHANNEL[2].CTRL.B.RAP=1;//GTM_PSM_RAM_ACCESS_PRIORITY_AEI_IF

	GTM_FIFO_0.CHANNEL[3].CTRL.B.RBM=1;//Ring buffer mode
	GTM_FIFO_0.CHANNEL[3].CTRL.B.RAP=1;//GTM_PSM_RAM_ACCESS_PRIORITY_AEI_IF

	GTM_F2A_0.CH_STR_CFG[2].B.TMODE=1;//GTM_PSM_STREAM_MODE_HIGH_WORD
	GTM_F2A_0.CH_STR_CFG[2].B.DIR=1;//Transport from FIFO to ARU

	GTM_F2A_0.CH_STR_CFG[3].B.TMODE=1;//GTM_PSM_STREAM_MODE_HIGH_WORD
	GTM_F2A_0.CH_STR_CFG[3].B.DIR=1;//Transport from FIFO to ARU

	uint32 PsmDataID_u32 = 0U;
	for(PsmDataID_u32 = 0; PsmDataID_u32 < 32; PsmDataID_u32++)
	{
		GTM_AFD_0.CH[2].BUF_ACC.B.DATA=PwmP_Table_Rad[PsmDataID_u32];
		GTM_AFD_0.CH[3].BUF_ACC.B.DATA=PwmP_Table_Rad[PsmDataID_u32];
	}
	GTM_F2A_0.ENABLE.B.STR2_EN=2;
	GTM_F2A_0.ENABLE.B.STR3_EN=2;




	GTM_TIM_0.CH0_CTRL.B.TIM_MODE=2;
	GTM_TIM_0.CH0_CTRL.B.GPR0_SEL=1;
	GTM_TIM_0.CH0_CTRL.B.GPR1_SEL=1;
	GTM_TIM_0.CH0_CTRL.B.DSL=1;
	GTM_TIM_0.CH0_CTRL.B.TIM_EN=1;

	GTM_TIM_1.CH4_CTRL.B.TIM_MODE=2;
	GTM_TIM_1.CH4_CTRL.B.GPR0_SEL=1;
	GTM_TIM_1.CH4_CTRL.B.GPR1_SEL=1;
	GTM_TIM_1.CH4_CTRL.B.DSL=1;
	GTM_TIM_1.CH4_CTRL.B.TIM_EN=1;
	SIUL2.MSCR_MUX[524-512].B.SSS=0x11;


	SIUL2.MSCR_MUX[512-512].B.SSS=0x0B;
	//SIUL2.MSCR_MUX[122].B.SSS=0x0A;

	GTM_ATOM_3.CH0_CTRL.B.MODE=2;
	GTM_ATOM_3.CH0_CM0.B.CM0=256;
	GTM_ATOM_3.CH0_CM1.B.CM1=128;
	GTM_ATOM_3.CH0_SR0.B.SR0=256;
	GTM_ATOM_3.CH0_SR1.B.SR1=128;

	GTM_ATOM_3.CH1_CTRL.B.MODE=2;
	GTM_ATOM_3.CH1_CTRL.B.ARU_EN=1;
	GTM_ATOM_3.CH1_CTRL.B.ACB=2;
	GTM_ATOM_3.CH1_RDADDR.B.RDADDR0=0x53;
	GTM_ATOM_3.CH1_RDADDR.B.RDADDR1=0x53;
	GTM_ATOM_3.CH1_CM0.B.CM0=256;
	GTM_ATOM_3.CH1_CM1.B.CM1=128;
	GTM_ATOM_3.CH1_SR0.B.SR0=256;
	GTM_ATOM_3.CH1_SR1.B.SR1=128;

	GTM_ATOM_3.CH2_CTRL.B.MODE=2;
	GTM_ATOM_3.CH2_CTRL.B.ARU_EN=1;
	GTM_ATOM_3.CH2_CTRL.B.ACB=2;
	GTM_ATOM_3.CH2_CTRL.B.SL=1;
	GTM_ATOM_3.CH2_RDADDR.B.RDADDR0=0x54;
	GTM_ATOM_3.CH2_RDADDR.B.RDADDR1=0x54;
	GTM_ATOM_3.CH2_CM0.B.CM0=256;
	GTM_ATOM_3.CH2_CM1.B.CM1=128;
	GTM_ATOM_3.CH2_SR0.B.SR0=256;
	GTM_ATOM_3.CH2_SR1.B.SR1=128;


	GTM_ATOM_3.AGC_OUTEN_STAT.B.OUTEN_STAT0=2;
	GTM_ATOM_3.AGC_OUTEN_STAT.B.OUTEN_STAT1=2;
	GTM_ATOM_3.AGC_OUTEN_STAT.B.OUTEN_STAT2=2;

	GTM_ATOM_3.AGC_ENDIS_CTRL.B.ENDIS_CTRL0=2;
	GTM_ATOM_3.AGC_ENDIS_CTRL.B.ENDIS_CTRL1=2;
	GTM_ATOM_3.AGC_ENDIS_CTRL.B.ENDIS_CTRL2=2;

	GTM_ATOM_3.AGC_OUTEN_CTRL.B.OUTEN_CTRL0=2;
	GTM_ATOM_3.AGC_OUTEN_CTRL.B.OUTEN_CTRL1=2;
	GTM_ATOM_3.AGC_OUTEN_CTRL.B.OUTEN_CTRL2=2;

	GTM_ATOM_3.AGC_GLB_CTRL.B.UPEN_CTRL0=2;
	GTM_ATOM_3.AGC_GLB_CTRL.B.UPEN_CTRL1=2;
	GTM_ATOM_3.AGC_GLB_CTRL.B.UPEN_CTRL2=2;

	Sdadc_Init(&SdAdc_TotalConfig);
	Sdadc_SetupResultBuffer(SDADC_CFG_CHANNEL_ID_0,MCS_SIN_Buffer , 32);
	Sdadc_SetupResultBuffer(SDADC_CFG_CHANNEL_ID_1, MCS_Cos_Buffer, 32);

	Sdadc_StartModulation(SDADC_CFG_CHANNEL_ID_0);
	Sdadc_StartModulation(SDADC_CFG_CHANNEL_ID_1);
	//GTM_ATOM_3.AGC_ENDIS_STAT.B.ENDIS_STAT0=2;
	GTM_ATOM_3.AGC_ENDIS_STAT.R=0X2A;
	//GTM_ATOM_3.AGC_ENDIS_STAT.B.ENDIS_STAT0=2;
	SDADC_LLD_SetSoftTrigger(SDADC_INSTANCE_0);

#if 0
    uint32    major_loop_time = (uint32)(1);
    uint32    minor_transfer_byte = 1U * sizeof(uint32);
    uint32    DmaRet;
      VAR(eDMALoopTransferConfigType, SDADC_VAR) sdadcLoopConfig =
                {
                    .dstAddrOffsetEn    = TRUE,
                    .srcAddrOffsetEn    = FALSE,
                    .minorLpOffset      = 0,
                    .minorLpLinkEn      = FALSE,
                    .minorLpLinkChn     = 0U,
                    .majorLpLinkEn      = FALSE,
                    .majorLpLinkChn     = 0U,
                    .majorLpIterCnt     = major_loop_time
                };

                VAR(eDMATransferConfigType, SDADC_VAR) dmaConfigforsdadc =
                {
                    .srcAddr = (uint32)&(GTM_TIM_1.CH4_GPR0.R), /* Modified by function */
                    .destAddr = (uint32)&SDADC_TIMESTAMP, /* Modified by function */
                    .srcTransDataSize = EDMA_TRANSFER_SIZE_4B,
                    .destTransDataSize = EDMA_TRANSFER_SIZE_4B,
                    .srcAddrOffset = (sint16)0,
                    .destAddrOffset = (sint16)sizeof(uint32),
                    .srcAddrAdjustLast = 0,
                    .destAddrAdjustLast = -((sint32)major_loop_time * (sint32)minor_transfer_byte), /* Modified by function */
                    .srcAddrModulo = EDMA_ADDRESS_MODULO_OFF,
                    .destAddrModulo = EDMA_ADDRESS_MODULO_OFF,
                    .minorTransByte = minor_transfer_byte, /* Modified by function */
                    .featureScatterGatherEn = FALSE,
                    .featureScatterGatherNextDescriptor = 0U,
                    .completeIntEn = TRUE,
                    .lpTransConfigPtr = &sdadcLoopConfig,
                };
                DmaRet = EDMA_SetLoopTransferConfig(21, &dmaConfigforsdadc);
                if(DmaRet == (Std_ReturnType)E_OK)
                {
                    EDMA_SetChnDisRequestsOnTransferComplete \
                    (
                        21, \
                        0 \
                    );
                    DmaRet = EDMA_SetChannelRequest(21);
                    if(DmaRet == (Std_ReturnType)E_OK)
                    {
                       // Sdadc_ChannelData[ChannelId][u32Sdadc_ICoreId].NumofValidConRes = Sdadc_ChannelData[ChannelId][u32Sdadc_ICoreId].ChannelBufferSize;
                      //  Sdadc_ChannelData[ChannelId][u32Sdadc_ICoreId].ChannelStatus = SDADC_RESULT_READY;
                    }
                }
#endif
}



void Gp_06_RslvrSw_GetPos(sint16 *SinValue_s16, sint16 *CosValue_s16)
{

	 mcssin=*SinValue;
	mcscos=*CosValue;

	if(mcssin&0x800000)
	{
	 mcssin_temp=-(0x1000000-mcssin)*0.0125;
	}else
	{
		 mcssin_temp=mcssin*0.0125;
	}
	if(mcscos&0x800000)
	{
		mcscos_temp=-(0x1000000-mcscos)*0.0125;
	}else
	{
		 mcscos_temp=mcscos*0.0125;
	}

	//*SinValue_s16 = mcssin_temp;
	//*CosValue_s16 = mcscos_temp;

	*SinValue_s16 = mcscos_temp;
	*CosValue_s16 = mcssin_temp;
}

void Gp_06_RslvrSw_CddIo()
{

	UI32_RSLVRSW_REG_MCS3_STRG=1;

}

void Gp_06_RslvrSw_GetTimeStampSig(uint32 *TimeStamp_pu32)
{
	*TimeStamp_pu32 =SDADC_TIMESTAMP;
}


void Gp_06_RslvrSw_GetCurTimeStampSig(uint32 *TimeStamp_pu32)
{
	*TimeStamp_pu32 =GTM_TIM_0.CH0_GPR0.B.GPR0;
}



