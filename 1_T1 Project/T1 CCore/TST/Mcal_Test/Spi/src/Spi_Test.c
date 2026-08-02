

#include "Spi.h"
#include "CCFC3007PT.h"
#include "Spi_Test.h"
#include "Gpt_Stm_LLDriver.h"
#include "intc_lld.h"
// #include "console.h"
#include "Shell.h"
#include "Spi_LLDriver.h"
#include "Spi_Irq.h"
/* Variables to store last DET error */
extern VAR(uint8, DET_VAR) Det_InstanceId;     /**< @brief DET instance ID*/
extern VAR(uint8, DET_VAR) Det_ApiId;          /**< @brief DET API ID*/
extern VAR(uint8, DET_VAR) Det_ErrorId;        /**< @brief DET Error ID*/

/* Variables to store last DET error */
extern VAR(uint16, DET_VAR) Det_ModuleId;       /**< @brief DET module ID*/

#define VERIFICATION_RESULT                  0
#define DSPI_HALT_VERIFICATION_RESULT          1



CONST(IntrPrior, SPI_CODE) dspi_Intc_Tcf_Priority[MAX_DSPI] = {DSPI0_TCF_INTPRI,DSPI1_TCF_INTPRI, \
                                                               DSPI2_TCF_INTPRI,DSPI3_TCF_INTPRI, \
                                                               DSPI4_TCF_INTPRI,DSPI5_TCF_INTPRI, \
                                                               DSPI6_TCF_INTPRI,DSPI12_TCF_INTPRI \
                                                              };

CONST(IntrId, SPI_CODE) dspi_Intc_Tcf_TntId[MAX_DSPI] = {DSPI0_TCF_IntID,DSPI1_TCF_IntID, \
                                                         DSPI2_TCF_IntID,DSPI3_TCF_IntID, \
                                                         DSPI4_TCF_IntID,DSPI5_TCF_IntID, \
                                                         DSPI6_TCF_IntID,DSPI12_TCF_IntID \
                                                        };

void (* const Tcf_Irq[MAX_DSPI])(void) = {dspi_0_Tcf_Irq,dspi_1_Tcf_Irq, \
                                          dspi_2_Tcf_Irq,dspi_3_Tcf_Irq, \
                                          dspi_4_Tcf_Irq,dspi_5_Tcf_Irq, \
                                          dspi_6_Tcf_Irq,dspi_12_Tcf_Irq \
                                         };

uint8 data[160];

static SpifuncMachine spi_funcs[] = {
    {"spi_0000", NULL},
    {"spi_0001", NULL},
    {"spi_0002", NULL},
    {"spi_0003", NULL},
    {"spi_0004", NULL},
    {"spi_0005", NULL},
    {"spi_0006", NULL},
    {"spi_0007", NULL},
    {"spi_0008", NULL},
    {"spi_0009", NULL},
    {"spi_0010", NULL},
    {"spi_0011", NULL},
    {"spi_0012", NULL},
    {"spi_0013", NULL},
    {"spi_0014", NULL},
    {"spi_0015", NULL},
    {"spi_0016", NULL},
    {"spi_0017", NULL},
    {"spi_0018", NULL},
    {"spi_0019", NULL},
    {"spi_0020", NULL},
    {"spi_0021", NULL},
    {"spi_0022", NULL},
    {"spi_0023", spi_0023},
    {"spi_0024", spi_0024},
    {"spi_0025", spi_0025},
    {"spi_0026", spi_0026},
    {"spi_0027", spi_0027},
    {"spi_0028", spi_0028},
    {"spi_0029", spi_0029},
    {"spi_0030", spi_0030},
    {"spi_0031", spi_0031},
    {"spi_0032", spi_0032},
    {"spi_0033", spi_0033},
    {"spi_0034", spi_0034},
    {"spi_0035", spi_0035},
    {"spi_0036", spi_0036},
    {"spi_0037", spi_0037},
    {"spi_0038", spi_0038},
    {"spi_0039", spi_0039},
    {"spi_0040", spi_0040},
    {"spi_0041", spi_0041},
    {"spi_0042", spi_0042},
    {"spi_0043", spi_0043},
    {"spi_0044", spi_0044},
    {"spi_0045", spi_0045},
    {"spi_0046", spi_0046},
    {"spi_0047", spi_0047},
    {"spi_0048", spi_0048},
    {"spi_0049", spi_0049},
    {"spi_0050", spi_0050},
    {"spi_0051", spi_0051},
    {"spi_0052", spi_0052},
    {"spi_0053", spi_0053},
    {"spi_0054", spi_0054},
    {"spi_0055", spi_0055},
    {"spi_0056", spi_0056},
    {"spi_0057", spi_0057},
    {"spi_0058", spi_0058},
    {"spi_0059", spi_0059},
    {"spi_0060", spi_0060},
    {"spi_0061", spi_0061},
    {"spi_0062", spi_0062},
    {"spi_0063", spi_0063},
    {"spi_0064", spi_0064},
    {"spi_0065", spi_0065},
    {"spi_0066", spi_0066},
    {"spi_0067", spi_0067},
    {"spi_0068", spi_0068},
    {"spi_0069", spi_0069},
    {"spi_0070", spi_0070},
    {"spi_0071", spi_0071},
    {"spi_0072", spi_0072},
    {"spi_0073", spi_0073},
    {"spi_0074", spi_0074},
    {"spi_0075", spi_0075},
    {"spi_0076", spi_0076},
    {"spi_0077", spi_0077},
    {"spi_0078", spi_0078},
    {"spi_0079", spi_0079},

    {"spi_0080", spi_0080},
    {"spi_0081", spi_0081},
    {"spi_0082", spi_0082},
    {"spi_0083", spi_0083},
    {"spi_0084", spi_0084},
    {"spi_0085", spi_0085},
    {"spi_0086", spi_0086},
    {"spi_0087", spi_0087},
    {"spi_0088", spi_0088},
    {"spi_0089", spi_0089},

    {"spi_0090", spi_0090},
    {"spi_0091", spi_0091},
    {"spi_0092", spi_0092},
	{"spi_0093", spi_0093},
	{"spi_0094", spi_0094},
	{"spi_0095", spi_0095},
	{"spi_0096", spi_0096},
    {"spi_0097", spi_0097},
    {"spi_0098", spi_0098},
	{"spi_0099", spi_0099},
	{"spi_0100", spi_0100},
	{"spi_0101", spi_0101},
    {"spi_0102", spi_0102},
	{"spi_0103", spi_0103},
};


void spi0_port_init()
{

    // J11 OUT
    // J13 IN
    // J15 SCK
    // G13 CS
    SIUL2.MSCR_IO[109].R = 0x32840003;        //DSPI0_CS0    PG[13] output
    SIUL2.MSCR_IO[159].R = 0x32840003;        //DSPI0_SCK    PJ[15] output
    SIUL2.MSCR_IO[155].R = 0x32840003;        //DSPI0_SOUT0  PJ[11] output
    SIUL2.MSCR_IO[157].R = 0x308C0000;         //DSPI0_SIN    PJ[13] input
    SIUL2.MSCR_MUX[368].R = 0x4;
}



FUNC(void, SPI_CODE) dspi_Int_Enable(VAR(uint8, SPI_VAR) u8Spi_HandleIdx)
{
    INTC_LLD_Set_IRQ_Handle(dspi_Intc_Tcf_TntId[u8Spi_HandleIdx], Tcf_Irq[u8Spi_HandleIdx]);
    INTC_LLD_Set_IRQ_Priority \
    ( \
        dspi_Intc_Tcf_TntId[u8Spi_HandleIdx], \
        dspi_Intc_Tcf_Priority[u8Spi_HandleIdx] \
    );
    INTC_LLD_Set_IRQ_Enable(dspi_Intc_Tcf_TntId[u8Spi_HandleIdx]);

}

void EnableSpiInterrupt(void)
{
    dspi_Int_Enable(0);
    dspi_Int_Enable(1);
    dspi_Int_Enable(2);
    dspi_Int_Enable(3);
    dspi_Int_Enable(4);
    dspi_Int_Enable(5);
    dspi_Int_Enable(6);
    dspi_Int_Enable(7);
}

extern void Spi_Dspi_IsrTCF_DSPI_0(void);

void spi_Env_Init()
{
    EnableSpiInterrupt();
}

void spi_0023()
{
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);

    if((Spi_gHWUnitStatus[0] == (Spi_StatusType)SPI_IDLE) && DSPI_0.MCR.B.MDIS == VERIFICATION_RESULT
        && DSPI_0.MCR.B.FRZ == VERIFICATION_RESULT && DSPI_0.MCR.B.HALT == DSPI_HALT_VERIFICATION_RESULT)
    {
        PSPRINTF("spi_0023 is ok\n");
    }
    else
    {
        PSPRINTF("spi_0023 is not ok\n");
    }
}

void spi_0024()
{
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_Init(&Spi_Configuration);
    if(Det_ErrorId == SPI_E_ALREADY_INITIALIZED)
    {
        PSPRINTF("spi_0024 is ok\n");
    }
    else
    {
        PSPRINTF("spi_0024 is not ok\n");
    }
}

void spi_0025()
{
    spi_Env_Init();
    Spi_Init(NULL_PTR);
    if(Det_ErrorId == SPI_E_PARAM_POINTER)
    {
        PSPRINTF("spi_0025 is ok\n");
    }
    else
    {
        PSPRINTF("spi_0025 is not ok\n");
    }
}

void spi_0026()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    retVal = Spi_DeInit();
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0026 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0026 is NG\n");
    }
}

void spi_0027()
{
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Std_ReturnType retVal;
    retVal = Spi_DeInit();
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0027 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0027 is NG\n");
    }
}

void spi_0028()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);

    retVal = Spi_WriteIB(0,DataBufferPtr);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0028 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0028 is NG\n");
    }
}

void spi_0029()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);

    retVal = Spi_WriteIB(0,NULL_PTR);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0029 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0029 is NG\n");
    }
}

void spi_0030()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);

    retVal = Spi_WriteIB(255,NULL_PTR);
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0030 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0030 is NG\n");
    }
}


void spi_0031()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);

    retVal = Spi_WriteIB(0,NULL_PTR);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0031 first is OK\n");
    }
    else
    {
        PSPRINTF("spi_0031 first is NG\n");
    }

    retVal = Spi_WriteIB(0,DataBufferPtr);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0031 second is OK\n");
    }
    else
    {
        PSPRINTF("spi_0031 second is NG\n");
    }
}


void spi_0032()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_WriteIB(0,DataBufferPtr);
    if(retVal == E_OK)
    {
        retVal = Spi_AsyncTransmit(0);
        if(retVal == E_OK)
        {
            PSPRINTF("spi_0032 is OK\n");
        }
        else
        {
            PSPRINTF("spi_0032 is NG\n");
        }
    }
    else
    {
        PSPRINTF("spi_0032 is NG\n");
    }
}


void spi_0033()
{
    Std_ReturnType retVal;
    Spi_JobResultType job_result;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    job_result = Spi_GetJobResult(0);
    if(job_result == SPI_JOB_OK)
    {
        retVal = Spi_AsyncTransmit(0);
        if(retVal == E_OK)
        {
            job_result = Spi_GetJobResult(0);
            if(job_result == SPI_JOB_PENDING);
            {
                Gpt_Stm_LLD_DelayMs(STM1,100U);
                job_result = Spi_GetJobResult(0);
                if(job_result == SPI_JOB_OK)
                {
                    PSPRINTF("spi_0033 is OK\n");
                }
            }
        }
    }

    PSPRINTF("spi_0033 is End\n");
}



void spi_0034()
{
    Std_ReturnType retVal1,retVal2,retVal3;
    uint8 tranbuffer[10] = {1,2,3,4,5,6,7,8,9,0};
    uint8 recbuffer[10] = {0};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(1,tranbuffer,recbuffer,10);
    retVal1 = Spi_AsyncTransmit(0);
    retVal2 = Spi_AsyncTransmit(1);
    retVal3 = Spi_AsyncTransmit(2);

    if(retVal1 == E_OK)
    {
        PSPRINTF("Transmit Seq0 is OK\n");
    }

    if(retVal2 == E_OK)
    {
        PSPRINTF("Transmit Seq1 is OK\n");
    }

    if(retVal3 == E_OK)
    {
        PSPRINTF("Transmit Seq2 is OK\n");
    }
}


void spi_0035()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    retVal = Spi_AsyncTransmit(0);
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0035 is ok \n");
    }
    else
    {
        PSPRINTF("spi_0035 is not ok \n");
    }

}

void spi_0036()
{
    int i=0;
    uint8 DataBufferPtr[4] = {0xff,0xff,0xff,0xff};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);

    Spi_ReadIB(0,DataBufferPtr);

    for(i=0;i<4;i++)
    {
        PSPRINTF("DataBufferPtr[i] = %x\n",DataBufferPtr[i]);
    }

}

void spi_0037()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {0xff,0xff,0xff,0xff};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_ReadIB(255,DataBufferPtr);
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0037 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0037 is NG\n");
    }
}

void spi_0038()
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_SetupEB(1,transmitBuffer,receiveBuffer,10);
    if(retVal == E_OK)
    {
        retVal = Spi_AsyncTransmit(1);
        if(retVal == E_OK)
        {
            PSPRINTF("spi_0038 is OK\n");
        }
    }
    PSPRINTF("spi_0038 is End\n");
}

void spi_0039()
{
    Std_ReturnType retVal;
    uint8 recData[10] = {0};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_SetupEB(1,NULL_PTR,recData,10);
    if(retVal == E_OK)
    {
        retVal = Spi_AsyncTransmit(1);
        if(retVal == E_OK)
        {
            PSPRINTF("spi_0039 is OK\n");
        }
    }
    PSPRINTF("spi_0039 is End\n");
}

void spi_0040()
{
    Spi_StatusType Spi_Status;
    spi_Env_Init();
    Spi_Status = Spi_GetStatus();
    if(Spi_Status == SPI_UNINIT)
    {
        Spi_Init(&Spi_Configuration);
        Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
        Spi_Status = Spi_GetStatus();
        if(Spi_Status == SPI_IDLE)
        {
            Spi_AsyncTransmit(0);
            Spi_Status = Spi_GetStatus();
            if(Spi_Status == SPI_BUSY)
            {
                PSPRINTF("spi_0040 is OK\n");
            }
        }
    }
    PSPRINTF("spi_0040 is End\n");
}

void spi_0041()
{
    Spi_JobResultType jobResult;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    jobResult = Spi_GetJobResult(0);
    if(jobResult == SPI_JOB_OK)
    {
        Spi_AsyncTransmit(0);
        jobResult = Spi_GetJobResult(0);
        if(jobResult == SPI_JOB_PENDING)
        {
            Gpt_Stm_LLD_DelayMs(STM1,100U);
            jobResult = Spi_GetJobResult(0);
            if(jobResult == SPI_JOB_OK)
            {
                PSPRINTF("spi_0041 is OK\n");
            }
        }
    }
    PSPRINTF("spi_0041 is End\n");
}

void spi_0042()
{
    Spi_SeqResultType SeqResult;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    SeqResult = Spi_GetSequenceResult(0);
    if(SeqResult == SPI_SEQ_OK)
    {
        Spi_AsyncTransmit(0);
        SeqResult = Spi_GetSequenceResult(0);
        if(SeqResult == SPI_SEQ_PENDING)
        {
            Gpt_Stm_LLD_DelayMs(STM1,100U);
            SeqResult = Spi_GetSequenceResult(0);
            if(SeqResult == SPI_SEQ_OK)
            {
                PSPRINTF("spi_0042 is OK\n");
            }
        }
    }
    PSPRINTF("spi_0042 is End\n");
}

void spi_0043()
{
    Spi_GetVersionInfo(NULL_PTR);
}


void spi_0044()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    retVal = Spi_SyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0044 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0044 is NG\n");
    }
}


void spi_0045()
{
    Spi_StatusType hwStatus;
    spi_Env_Init();
    hwStatus = Spi_GetHWUnitStatus(0);
    if(hwStatus == SPI_UNINIT)
    {
        Spi_Init(&Spi_Configuration);
        Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
        hwStatus = Spi_GetHWUnitStatus(0);
        if(hwStatus == SPI_IDLE)
        {
            Spi_AsyncTransmit(0);
            hwStatus = Spi_GetHWUnitStatus(0);
            if(hwStatus == SPI_BUSY)
            {
                PSPRINTF("spi_0045 is OK\n");
            }
        }
    }
    PSPRINTF("spi_0045 is END\n");
}

void spi_0046()
{
    Spi_SeqResultType SeqResult;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_AsyncTransmit(0);
    Spi_AsyncTransmit(2);
    Spi_Cancel(2);
    SeqResult = Spi_GetSequenceResult(2);
    if(SeqResult == SPI_SEQ_CANCELED)
    {
        PSPRINTF("spi_0046 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0046 is NG\n");
    }
}

#if (SPI_LEVEL_DELIVERED == LEVEL2)
void spi_0047()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0047 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0047 is NG\n");
    }
}


void spi_0048()
{
    /*
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetAsyncMode(SPI_POLLING_MODE);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0048 first is OK\n");
    }
    else
    {
        PSPRINTF("spi_0048 first is NG\n");
    }
    retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0048 second is OK\n");
    }
    else
    {
        PSPRINTF("spi_0048 second is NG\n");
    }
    */
}
#endif

#if (SPI_LEVEL_DELIVERED == LEVEL2)
void spi_0049()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_AsyncTransmit(0);
    retVal = Spi_SetAsyncMode(SPI_POLLING_MODE);
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0049 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0048 is NG\n");
    }
}
#endif

void spi_0050()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    retVal = Spi_SyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0050 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0050 is NG\n");
    }
}

void spi_0051()
{
    Std_ReturnType retVal;
    uint8 TraData[4] = {'a','b','c','d'};
    uint8 RecData[4] = {0};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,TraData);
    retVal = Spi_SyncTransmit(0);
    if(retVal == E_OK)
    {
        retVal = Spi_ReadIB(0,RecData);
        if(RecData[0] == 'a' && RecData[1] == 'b' && RecData[2] == 'c' && RecData[3] == 'd' && retVal == E_OK)
        {
            PSPRINTF("spi_0051 is OK\n");
        }
    }
    PSPRINTF("spi_0051 is END\n");
}



void spi_0052()
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(1,transmitBuffer,receiveBuffer,10);
    Spi_SyncTransmit(1);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0052 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0052 is NG\n");
    }
}




void spi_0053()
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {'a','b','c','d','e','f','g','h','i','j'};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(1,transmitBuffer,receiveBuffer,10);
    Spi_SyncTransmit(1);

    if(retVal == E_OK && receiveBuffer[0] == 'a'
        && receiveBuffer[1] == 'b'
        && receiveBuffer[2] == 'c'
        && receiveBuffer[3] == 'd'
        && receiveBuffer[4] == 'e'
        && receiveBuffer[5] == 'f'
        && receiveBuffer[6] == 'g'
        && receiveBuffer[7] == 'h'
        && receiveBuffer[8] == 'i'
        && receiveBuffer[9] == 'j' )
    {
        PSPRINTF("spi_0053 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0053 is NG\n");
    }
}


void spi_0054()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_AsyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0054 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0054 is NG\n");
    }
}

void spi_0055()
{
    Std_ReturnType retVal;

    uint8 TraData[4] = {'a','b','c','d'};
    uint8 RecData[4] = {0};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,TraData);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_AsyncTransmit(0);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    Spi_ReadIB(0,RecData);
    if(retVal == E_OK && RecData[0] == 'a' && RecData[1] == 'b' && RecData[2] == 'c' && RecData[3] == 'd')
    {
        PSPRINTF("spi_0055 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0055 is NG\n");
    }
}


void spi_0056()
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(1,transmitBuffer,receiveBuffer,10);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_AsyncTransmit(1);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0056 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0056 is NG\n");
    }
}

void spi_0057()
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {'a','b','c','d','e','f','g','h','i','j'};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(1,transmitBuffer,receiveBuffer,10);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_AsyncTransmit(1);
    Gpt_Stm_LLD_DelayMs(STM1,100U);
    if(retVal == E_OK && receiveBuffer[0] == 'a'
        && receiveBuffer[1] == 'b'
        && receiveBuffer[2] == 'c'
        && receiveBuffer[3] == 'd'
        && receiveBuffer[4] == 'e'
        && receiveBuffer[5] == 'f'
        && receiveBuffer[6] == 'g'
        && receiveBuffer[7] == 'h'
        && receiveBuffer[8] == 'i'
        && receiveBuffer[9] == 'j' )
    {
        PSPRINTF("spi_0057 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0057 is NG\n");
    }
}

void spi_0058()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    uint8 tranData1[4] = {5,6,7,8};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(2,tranData);
    Spi_WriteIB(3,tranData1);
    retVal = Spi_SyncTransmit(2);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0058 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0058 is NG\n");
    }
}


void spi_0059()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    uint8 tranData1[4] = {5,6,7,8};
    uint8 tranData2[4] = {9,10,11,12};
    uint8 tranData3[4] = {13,14,15,16};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(4,tranData);
    Spi_WriteIB(5,tranData1);
    Spi_SetupEB(6,tranData2,NULL_PTR,4);
    Spi_SetupEB(7,tranData3,NULL_PTR,4);
    retVal = Spi_SyncTransmit(3);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0059 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0059 is NG\n");
    }
}

void spi_0060()
{
    Std_ReturnType retVal1,retVal2;
    uint8 tranData[4] = {1,2,3,4};
    uint8 tranData1[4] = {5,6,7,8};
    uint8 tranData2[4] = {9,10,11,12};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    Spi_WriteIB(2,tranData1);
    Spi_WriteIB(3,tranData2);
    retVal1 = Spi_SyncTransmit(0);
    retVal2 = Spi_SyncTransmit(2);
    if(retVal1 == E_OK)
    {
        PSPRINTF("spi_0060 first transmit is OK\n");
    }
    else
    {
        PSPRINTF("spi_0060 first transmit is NG\n");
    }
    if(retVal2 == E_OK)
    {
        PSPRINTF("spi_0060 second transmit is OK\n");
    }
    else
    {
        PSPRINTF("spi_0060 second transmit is NG\n");
    }
}


void spi_0061()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    uint8 tranData1[4] = {5,6,7,8};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(2,tranData);
    Spi_WriteIB(3,tranData1);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal = Spi_AsyncTransmit(2);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0061 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0061 is NG\n");
    }
}

void spi_0062()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    uint8 tranData1[4] = {5,6,7,8};
    uint8 tranData2[4] = {9,10,11,12};
    uint8 tranData3[4] = {13,14,15,16};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_WriteIB(4,tranData);
    Spi_WriteIB(5,tranData1);
    Spi_SetupEB(6,tranData2,NULL_PTR,4);
    Spi_SetupEB(7,tranData3,NULL_PTR,4);
    retVal = Spi_AsyncTransmit(3);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0062 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0062 is NG\n");
    }
}

void spi_0063()
{
    Std_ReturnType retVal1,retVal2;
    uint8 tranData[4] = {1,2,3,4};
    uint8 tranData1[4] = {5,6,7,8};
    uint8 tranData2[4] = {9,10,11,12};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    Spi_WriteIB(2,tranData1);
    Spi_WriteIB(3,tranData2);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    retVal1 = Spi_AsyncTransmit(0);
    retVal2 = Spi_AsyncTransmit(2);
    if(retVal1 == E_OK)
    {
        PSPRINTF("spi_0063 first transmit is OK\n");
    }
    else
    {
        PSPRINTF("spi_0063 first transmit is NG\n");
    }
    if(retVal2 == E_OK)
    {
        PSPRINTF("spi_0063 second transmit is OK\n");
    }
    else
    {
        PSPRINTF("spi_0063 second transmit is NG\n");
    }
}


void spi_0064()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    retVal = Spi_SyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0064 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0064 is NG\n");
    }
}


void spi_0065()
{
    Std_ReturnType retVal;
    uint8 tranData[4] = {1,2,3,4};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_WriteIB(0,tranData);
    retVal = Spi_SyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0065 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0065 is NG\n");
    }
}

void spi_0066()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    retVal = Spi_DeInit();
    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0066 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0066 is NG\n");
    }
}

void spi_0067()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_AsyncTransmit(200);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_ASYNCTRANSMIT_SID && Det_ErrorId == SPI_E_PARAM_SEQ)
    {
        PSPRINTF("spi_0067 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0067 is NG\n");
    }
}

void spi_0068()
{

    Std_ReturnType retVal;

    retVal = Spi_AsyncTransmit(0);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_ASYNCTRANSMIT_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0068 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0068 is NG\n");
    }
}

void spi_0069()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {0xff,0xff,0xff,0xff};
    retVal = Spi_ReadIB(0,DataBufferPtr);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_READIB_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0069 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0069 is NG\n");
    }
}

void spi_0070()
{
    Std_ReturnType retVal;
    retVal = Spi_GetStatus();

    if(retVal == SPI_UNINIT && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId == SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETSTATUS_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0070 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0070 is NG\n");
    }
}

void spi_0071()
{
    Std_ReturnType retVal;
    retVal = Spi_GetJobResult(0);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETJOBRESULT_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0071 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0071 is NG\n");
    }
}

void spi_0072()
{
    Std_ReturnType retVal;
    retVal = Spi_GetSequenceResult(0);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETSEQUENCERESULT_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0072 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0072 is NG\n");
    }
}

void spi_0073()
{
    Std_ReturnType retVal;
    retVal = Spi_SyncTransmit(0);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SYNCTRANSMIT_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0073 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0073 is NG\n");
    }
}

void spi_0074()
{
    Std_ReturnType retVal;
    retVal = Spi_GetHWUnitStatus(0);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETHWUNITSTATUS_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0074 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0074 is NG\n");
    }
}

void spi_0075()
{
    Std_ReturnType retVal;
    Spi_Cancel(0);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_CANCEL_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0075 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0075 is NG\n");
    }
}

void spi_0076()
{
    Std_ReturnType retVal;

    retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SETAYNCMODE_SID && Det_ErrorId == SPI_E_UNINIT)       
    {
        PSPRINTF("spi_0076 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0076 is NG\n");
    }
}

void spi_0077()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {0xff,0xff,0xff,0xff};
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_ReadIB(200,DataBufferPtr);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_READIB_SID && Det_ErrorId == SPI_E_PARAM_CHANNEL)
    {
        PSPRINTF("spi_0077 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0077 is NG\n");
    }
}

void spi_0078()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_ReadIB(0,NULL_PTR);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId == SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_READIB_SID && Det_ErrorId == SPI_E_PARAM_POINTER)
    {
        PSPRINTF("spi_0078 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0078 is NG\n");
    }
}

void spi_0079()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_GetSequenceResult(200);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETSEQUENCERESULT_SID && Det_ErrorId == SPI_E_PARAM_SEQ)
    {
        PSPRINTF("spi_0079 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0079 is NG\n");
    }
}

void spi_0080()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SyncTransmit(200);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SYNCTRANSMIT_SID && Det_ErrorId == SPI_E_PARAM_SEQ)
    {
        PSPRINTF("spi_0080 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0080 is NG\n");
    }
}

void spi_0081()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_GetHWUnitStatus(200);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETHWUNITSTATUS_SID && Det_ErrorId == SPI_E_PARAM_UNIT)
    {
        PSPRINTF("spi_0081 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0081 is NG\n");
    }
}

void spi_0082()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_Cancel(200);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_CANCEL_SID && Det_ErrorId == SPI_E_PARAM_SEQ)
    {
        PSPRINTF("spi_0082 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0082 is NG\n");
    }
}

void spi_0083()
{
    Std_ReturnType retVal;
    uint8 DataBufferPtr[4] = {1,2,3,4};
    retVal = Spi_WriteIB(0,DataBufferPtr);
    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_WRITEIB_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0083 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0083 is NG\n");
    }
}

void spi_0084()
{
    Std_ReturnType retVal;
    retVal = Spi_SetupEB(1,NULL_PTR,NULL_PTR,0);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SETUPEB_SID && Det_ErrorId == SPI_E_UNINIT)
    {
        PSPRINTF("spi_0084 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0084 is NG\n");
    }
}

void spi_0085()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(200,NULL_PTR,NULL_PTR,0);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SETUPEB_SID && Det_ErrorId == SPI_E_PARAM_CHANNEL)
    {
        PSPRINTF("spi_0085 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0085 is NG\n");
    }
}

void spi_0086()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(200,NULL_PTR,NULL_PTR,0);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId == SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SETUPEB_SID && Det_ErrorId == SPI_E_PARAM_CHANNEL)
    {
        PSPRINTF("spi_0086 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0086 is NG\n");
    }
}

void spi_0087()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(0,NULL_PTR,NULL_PTR,200);

    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_SETUPEB_SID && Det_ErrorId == SPI_E_PARAM_LENGTH)
    {
        PSPRINTF("spi_0087 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0087 is NG\n");
    }
}

void spi_0088()
{
    VAR(Std_VersionInfoType, AUTOMATIC) versioninfo;
    Spi_GetVersionInfo(&versioninfo);

    if(versioninfo.vendorID == SPI_VENDOR_ID
        && versioninfo.moduleID == SPI_MODULE_ID
        && versioninfo.sw_major_version == SPI_AR_MAJOR_VER
        && versioninfo.sw_minor_version == SPI_AR_MINOR_VER
        && versioninfo.sw_patch_version == SPI_AR_PATCH_VER)
    {
        PSPRINTF("spi_0088 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0088 is NG\n");
    }
}

void spi_0089()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    uint8 DataBufferPtr[4] = {1,2,3,4};
    retVal = Spi_WriteIB(200,DataBufferPtr);
    if(retVal == E_NOT_OK && Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_WRITEIB_SID && Det_ErrorId == SPI_E_PARAM_CHANNEL)
    {
        PSPRINTF("spi_0089 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0089 is NG\n");
    }
}

void spi_0090()
{
    Std_ReturnType retVal;
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_GetJobResult(200);

    if(Det_ModuleId == SPI_MODULE_ID && Det_InstanceId ==  SPI_INSTANCE_ID 
        && Det_ApiId ==  SPI_GETJOBRESULT_SID && Det_ErrorId == SPI_E_PARAM_JOB)
    {
        PSPRINTF("spi_0090 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0090 is NG\n");
    }
}

void spi_0091()
{
    Std_ReturnType retVal;

    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_AsyncTransmit(0);
    retVal = Spi_SetAsyncMode(SPI_POLLING_MODE);

    if(retVal == E_NOT_OK)
    {
        PSPRINTF("spi_0091 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0091 is NG\n");
    }
}

void spi_0092()
{
    Std_ReturnType retVal;

    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);

    if(retVal == E_OK)       
    {
        PSPRINTF("spi_0092 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0092 is NG\n");
    }
}

void spi_0093(void)
{
	Std_ReturnType retVal;

    int i;
    for(i=0;i<160;i++)
    {
        data[i]=i;
    }
	spi_Env_Init();
	Spi_Init(&Spi_Configuration);
	retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(0,&data[0],&data[10],10);
    Spi_SetupEB(1,&data[20],&data[30],10);
    Spi_SetupEB(2,&data[40],&data[50],10);
    Spi_SetupEB(3,&data[60],&data[70],10);
    Spi_SetupEB(4,&data[80],&data[90],10);
    Spi_SetupEB(5,&data[100],&data[110],10);
    Spi_SetupEB(6,&data[120],&data[130],10);
    Spi_SetupEB(7,&data[140],&data[150],10);
    Spi_AsyncTransmit(0);
    Spi_AsyncTransmit(1);
}



void spi_0094(void)
{
	Std_ReturnType retVal;

    int i;
    for(i=0;i<160;i++)
    {
        data[i]=i;
    }
	spi_Env_Init();
	Spi_Init(&Spi_Configuration);
	retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(0,&data[0],&data[10],10);
    Spi_SetupEB(1,&data[20],&data[30],10);
    Spi_SetupEB(2,&data[40],&data[50],10);
    Spi_SetupEB(3,&data[60],&data[70],10);
    Spi_SetupEB(4,&data[80],&data[90],10);
    Spi_SetupEB(5,&data[100],&data[110],10);
    Spi_SetupEB(6,&data[120],&data[130],10);
    Spi_SetupEB(7,&data[140],&data[150],10);
    Spi_AsyncTransmit(0);
    Spi_AsyncTransmit(1);
    Spi_Cancel(1);
}



void spi_0095(void)
{
	Std_ReturnType retVal;

    int i;
    for(i=0;i<160;i++)
    {
        data[i]=i;
    }
	spi_Env_Init();
	Spi_Init(&Spi_Configuration);
	retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(0,&data[0],&data[10],10);
    Spi_SetupEB(1,&data[20],&data[30],10);
    Spi_SetupEB(2,&data[40],&data[50],10);
    Spi_SetupEB(3,&data[60],&data[70],10);
    Spi_SetupEB(4,&data[80],&data[90],10);
    Spi_SetupEB(5,&data[100],&data[110],10);
    Spi_SetupEB(6,&data[120],&data[130],10);
    Spi_SetupEB(7,&data[140],&data[150],10);
    Spi_AsyncTransmit(1);
    Spi_AsyncTransmit(0);
}

void spi_0096(void)
{
	Std_ReturnType retVal;

    int i;
    for(i=0;i<160;i++)
    {
        data[i]=i;
    }
	spi_Env_Init();
	Spi_Init(&Spi_Configuration);
	// retVal = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(0,&data[0],&data[10],10);
    Spi_SetupEB(1,&data[20],&data[30],10);
    Spi_SetupEB(2,&data[40],&data[50],10);
    Spi_SetupEB(3,&data[60],&data[70],10);
    Spi_SetupEB(4,&data[80],&data[90],10);
    Spi_SetupEB(5,&data[100],&data[110],10);
    Spi_SetupEB(6,&data[120],&data[130],10);
    Spi_SetupEB(7,&data[140],&data[150],10);
    Spi_AsyncTransmit(0);
    Spi_AsyncTransmit(1);
    for(i=0;i<65535;i++)
    {
    	Spi_MainFunction_Handling();
    }
}

void spi_0097(void)
{
    Std_ReturnType retVal;
    uint8 data[20];
    int i=0;

    spi_Env_Init();
	Spi_Init(&Spi_Configuration);

    for(i=0;i<20;i++)
    {
        data[i]=i;
    }

    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(0,&data[0],&data[10],10);
    retVal = Spi_AsyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0097 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0097 is NG\n");
    }
}

void spi_0098(void)
{
    Std_ReturnType retVal;
    static uint8 data[20];
    int i=0;

    spi_Env_Init();
	Spi_Init(&Spi_Configuration);

    for(i=0;i<20;i++)
    {
        data[i]=i;
    }

    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(1,&data[0],&data[10],10);
    retVal = Spi_AsyncTransmit(1);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0098 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0098 is NG\n");
    }
}

void spi_0099(void)
{
    Std_ReturnType retVal;
    uint8 data[20];
    int i=0;

    spi_Env_Init();
	Spi_Init(&Spi_Configuration);

    for(i=0;i<20;i++)
    {
        data[i]=i;
    }

    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(2,&data[0],&data[10],10);
    retVal = Spi_AsyncTransmit(2);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0099 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0099 is NG\n");
    }
}

void spi_0100(void)
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(0,transmitBuffer,receiveBuffer,10);
    Spi_SyncTransmit(0);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0100 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0100 is NG\n");
    }
}

void spi_0101(void)
{
    Std_ReturnType retVal;
    static uint8 data[20];
    int i=0;

    spi_Env_Init();
	Spi_Init(&Spi_Configuration);

    for(i=0;i<20;i++)
    {
        data[i]=i;
    }

    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Spi_SetupEB(1,&data[0],&data[10],10);
    retVal = Spi_AsyncTransmit(1);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0101 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0101 is NG\n");
    }
}

void spi_0102(void)
{
    Std_ReturnType retVal;
    uint8 transmitBuffer[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 receiveBuffer[10];
    spi_Env_Init();
    Spi_Init(&Spi_Configuration);
    retVal = Spi_SetupEB(4,transmitBuffer,receiveBuffer,10);
    Spi_SyncTransmit(5);
    if(retVal == E_OK)
    {
        PSPRINTF("spi_0102 is OK\n");
    }
    else
    {
        PSPRINTF("spi_0102 is NG\n");
    }
}

void spi_0103(void)
{
    
}

int spi_func(int argc, char *agrv[])
{
    if (argc!=2)
    {
        PSPRINTF("error: Parameter number error\n");
        return 0;
    }

    if(!strcmp(agrv[1], "help"))
    {
        PSPRINTF("Test valid ID: 23-65\n");
        PSPRINTF("Note: Modify configuration when switching between synchronous and asynchronous test cases\n");
        return 0;
    }

    int id = (uint32)atoi(agrv[1]);

    if(id<0 || id>(sizeof(spi_funcs)/sizeof(spi_funcs[0]))-1)
    {
        PSPRINTF("error: Parameter out of range\n");
        return 0;
    }

    if(spi_funcs[id].spifunc==NULL)
    {
        PSPRINTF("error: Test case is undefined\n");
        return 0;
    }

    spi_funcs[id].spifunc();

    return 0;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), spi_test, spi_func, deint or number of test case);
