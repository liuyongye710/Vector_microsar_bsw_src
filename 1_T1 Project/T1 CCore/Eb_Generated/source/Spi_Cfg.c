#ifdef __cplusplus
extern "C"{
#endif

/*PRQA S 0380,0499 EOF*/
/*PRQA S 0704,4397,0686 EOF*/ /*QAC_CWE*/

#include "Spi.h"
#if(SPI_DMA_USED == STD_ON)
#include "eDma.h"
#endif

/*==================================================================================================
SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SPI_CFG_C_VENDOR_ID                    176
#define SPI_CFG_C_AR_MAJOR_VER                 4
#define SPI_CFG_C_AR_MINOR_VER                 4
#define SPI_CFG_C_AR_PATCH_VER                 0
#define SPI_CFG_C_SW_MAJOR_VER                 3
#define SPI_CFG_C_SW_MINOR_VER                 0
#define SPI_CFG_C_SW_PATCH_VER                 0

/*==================================================================================================
FILE VERSION CHECKS
==================================================================================================*/
#if (SPI_CFG_C_VENDOR_ID != MCAL_VENDOR_ID)
#error "NON-MATCHED DATA : SPI_CFG_C_VENDOR_ID"
#endif

/* Check if current file and SPI header file are of the same Autosar version */
#if (SPI_CFG_C_AR_MAJOR_VER != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "NON-MATCHED DATA : SPI_CFG_C_AR_MAJOR_VER"
#endif
#if (SPI_CFG_C_AR_MINOR_VER != MCAL_AR_RELEASE_MINOR_VERSION)
#error "NON-MATCHED DATA : SPI_CFG_C_AR_MINOR_VER"
#endif
#if (SPI_CFG_C_AR_PATCH_VER != MCAL_AR_RELEASE_REVISION_VERSION)
#error "NON-MATCHED DATA : SPI_CFG_C_AR_PATCH_VER"
#endif

/* Check if current file and SPI header file are of the same Software version */
#if (SPI_CFG_C_SW_MAJOR_VER != MCAL_SW_MAJOR_VERSION)
#error "NON-MATCHED DATA : SPI_CFG_C_SW_MAJOR_VER"
#endif
#if (SPI_CFG_C_SW_MINOR_VER != MCAL_SW_MINOR_VERSION)
#error "NON-MATCHED DATA : SPI_CFG_C_SW_MINOR_VER"
#endif
#if (SPI_CFG_C_SW_PATCH_VER != MCAL_SW_PATCH_VERSION)
#error "NON-MATCHED DATA : SPI_CFG_C_SW_PATCH_VER"
#endif




#define SPI_START_SEC_VAR_INIT
#include "Spi_MemMap.h"
static VAR(Spi_EBDataType, SPI_VAR) EB_SpiChannel_0 = {
    .Length = 0,
    .ReadBuffer = NULL_PTR,
    .WriteBuffer = NULL_PTR,
    .WriteBufferReverse = NULL_PTR
};
#define SPI_STOP_SEC_VAR_INIT
#include "Spi_MemMap.h"
#define SPI_START_SEC_VAR_INIT
#include "Spi_MemMap.h"
static VAR(Spi_EBDataType, SPI_VAR) EB_SpiChannel_1 = {
    .Length = 0,
    .ReadBuffer = NULL_PTR,
    .WriteBuffer = NULL_PTR,
    .WriteBufferReverse = NULL_PTR
};
#define SPI_STOP_SEC_VAR_INIT
#include "Spi_MemMap.h"
#define SPI_START_SEC_VAR_INIT
#include "Spi_MemMap.h"
static VAR(Spi_EBDataType, SPI_VAR) EB_SpiChannel_2 = {
    .Length = 0,
    .ReadBuffer = NULL_PTR,
    .WriteBuffer = NULL_PTR,
    .WriteBufferReverse = NULL_PTR
};
#define SPI_STOP_SEC_VAR_INIT
#include "Spi_MemMap.h"
#define SPI_START_SEC_VAR_INIT
#include "Spi_MemMap.h"
static VAR(Spi_EBDataType, SPI_VAR) EB_SpiChannel_3 = {
    .Length = 0,
    .ReadBuffer = NULL_PTR,
    .WriteBuffer = NULL_PTR,
    .WriteBufferReverse = NULL_PTR
};
#define SPI_STOP_SEC_VAR_INIT
#include "Spi_MemMap.h"
#define SPI_START_SEC_VAR_INIT
#include "Spi_MemMap.h"
static VAR(Spi_EBDataType, SPI_VAR) EB_SpiChannel_4 = {
    .Length = 0,
    .ReadBuffer = NULL_PTR,
    .WriteBuffer = NULL_PTR,
    .WriteBufferReverse = NULL_PTR
};
#define SPI_STOP_SEC_VAR_INIT
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_ChannelCfgType, SPI_CONST) SpiChannelConfiguration[SPI_TOTAL_CHANNEL] =
{
    {
        /* SpiChannel_0*/
        .ChannelId = 0,
        .ChannelBufferType = EB,
        .DataWidth = 8U,
        .BufferSize = 64U,
        .EB_Buffer = &EB_SpiChannel_0,
        .TransferType = MSB,
        .DefaultValue = 0U,
    },
    {
        /* SpiChannel_1*/
        .ChannelId = 1,
        .ChannelBufferType = EB,
        .DataWidth = 16U,
        .BufferSize = 64U,
        .EB_Buffer = &EB_SpiChannel_1,
        .TransferType = MSB,
        .DefaultValue = 0U,
    },
    {
        /* SpiChannel_2*/
        .ChannelId = 2,
        .ChannelBufferType = EB,
        .DataWidth = 8U,
        .BufferSize = 64U,
        .EB_Buffer = &EB_SpiChannel_2,
        .TransferType = MSB,
        .DefaultValue = 0U,
    },
    {
        /* SpiChannel_3*/
        .ChannelId = 3,
        .ChannelBufferType = EB,
        .DataWidth = 16U,
        .BufferSize = 64U,
        .EB_Buffer = &EB_SpiChannel_3,
        .TransferType = MSB,
        .DefaultValue = 0U,
    },
    {
        /* SpiChannel_4*/
        .ChannelId = 4,
        .ChannelBufferType = EB,
        .DataWidth = 16U,
        .BufferSize = 64U,
        .EB_Buffer = &EB_SpiChannel_4,
        .TransferType = MSB,
        .DefaultValue = 0U,
    },
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_ChannelType, SPI_CONST) SpiJob_0_ChannelList[1] = 
{
    0U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_ChannelType, SPI_CONST) SpiJob_1_ChannelList[1] = 
{
    1U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_ChannelType, SPI_CONST) SpiJob_2_ChannelList[1] = 
{
    2U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_ChannelType, SPI_CONST) SpiJob_3_ChannelList[1] = 
{
    3U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_ChannelType, SPI_CONST) SpiJob_4_ChannelList[1] = 
{
    4U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"





#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_JobCfgType, SPI_CONST) SpiJobConfiguration[SPI_TOTAL_JOB] = 
{
    {
        .JobId = 0U,
        .HwUnit = 0U, /* @index */
        .HwDeviceIdx = 0U,
        .HwDevice = DSPI0,
        .CSPin = PCS0,
        .CSFunc = TRUE,
        .CSPolarity = LOW,
        .CSCountinue =0x8000U,
        .ClockPolarity = LOW,
        .ClockShift = TRAILING,
        .Ctar = (uint32)( /* Real Frequency 5000000 Hz */ /* CSC = 2 */ /* ASC = 2 */ /* DT = 2 */ 
            /* Prescaler */   (2U << 16U) 
            /* Scaler */    | (1U << 0U)
            /* PCSSCK */    | (0U << 22U)
            /* CSSCK */     | (0U << 12U)
            /* PASC */      | (0U << 20U)
            /* ASC */       | (0U << 8U)
            /* PDT */       | (0U << 18U)
            /* DT */        | (0U << 4U) ),
        .CtarSel = 0U,
        .SpiJobPriority = 0U,
        .JobEndNotification = NULL_PTR,
        .NoOfChannels = 1U,
        .ChannelList = SpiJob_0_ChannelList,
    },
    {
        .JobId = 1U,
        .HwUnit = 1U, /* @index */
        .HwDeviceIdx = 1U,
        .HwDevice = DSPI1,
        .CSPin = PCS0,
        .CSFunc = TRUE,
        .CSPolarity = LOW,
        .CSCountinue =0x8000U,
        .ClockPolarity = LOW,
        .ClockShift = TRAILING,
        .Ctar = (uint32)( /* Real Frequency 1041666 Hz */ /* CSC = 512 */ /* ASC = 512 */ /* DT = 512 */ 
            /* Prescaler */   (1U << 16U) 
            /* Scaler */    | (5U << 0U)
            /* PCSSCK */    | (0U << 22U)
            /* CSSCK */     | (8U << 12U)
            /* PASC */      | (0U << 20U)
            /* ASC */       | (8U << 8U)
            /* PDT */       | (0U << 18U)
            /* DT */        | (8U << 4U) ),
        .CtarSel = 0U,
        .SpiJobPriority = 0U,
        .JobEndNotification = NULL_PTR,
        .NoOfChannels = 1U,
        .ChannelList = SpiJob_1_ChannelList,
    },
    {
        .JobId = 2U,
        .HwUnit = 2U, /* @index */
        .HwDeviceIdx = 2U,
        .HwDevice = DSPI3,
        .CSPin = PCS0,
        .CSFunc = TRUE,
        .CSPolarity = LOW,
        .CSCountinue =0x8000U,
        .ClockPolarity = LOW,
        .ClockShift = TRAILING,
        .Ctar = (uint32)( /* Real Frequency 1041666 Hz */ /* CSC = 512 */ /* ASC = 512 */ /* DT = 512 */ 
            /* Prescaler */   (1U << 16U) 
            /* Scaler */    | (5U << 0U)
            /* PCSSCK */    | (0U << 22U)
            /* CSSCK */     | (8U << 12U)
            /* PASC */      | (0U << 20U)
            /* ASC */       | (8U << 8U)
            /* PDT */       | (0U << 18U)
            /* DT */        | (8U << 4U) ),
        .CtarSel = 0U,
        .SpiJobPriority = 0U,
        .JobEndNotification = NULL_PTR,
        .NoOfChannels = 1U,
        .ChannelList = SpiJob_2_ChannelList,
    },
    {
        .JobId = 3U,
        .HwUnit = 0U, /* @index */
        .HwDeviceIdx = 0U,
        .HwDevice = DSPI0,
        .CSPin = PCS0,
        .CSFunc = TRUE,
        .CSPolarity = LOW,
        .CSCountinue =0x8000U,
        .ClockPolarity = LOW,
        .ClockShift = TRAILING,
        .Ctar = (uint32)( /* Real Frequency 5000000 Hz */ /* CSC = 2 */ /* ASC = 2 */ /* DT = 2 */ 
            /* Prescaler */   (2U << 16U) 
            /* Scaler */    | (1U << 0U)
            /* PCSSCK */    | (0U << 22U)
            /* CSSCK */     | (0U << 12U)
            /* PASC */      | (0U << 20U)
            /* ASC */       | (0U << 8U)
            /* PDT */       | (0U << 18U)
            /* DT */        | (0U << 4U) ),
        .CtarSel = 0U,
        .SpiJobPriority = 0U,
        .JobEndNotification = NULL_PTR,
        .NoOfChannels = 1U,
        .ChannelList = SpiJob_3_ChannelList,
    },
    {
        .JobId = 4U,
        .HwUnit = 3U, /* @index */
        .HwDeviceIdx = 3U,
        .HwDevice = DSPI2,
        .CSPin = PCS3,
        .CSFunc = TRUE,
        .CSPolarity = LOW,
        .CSCountinue =0x8000U,
        .ClockPolarity = LOW,
        .ClockShift = LEADING,
        .Ctar = (uint32)( /* Real Frequency 1041666 Hz */ /* CSC = 512 */ /* ASC = 512 */ /* DT = 512 */ 
            /* Prescaler */   (1U << 16U) 
            /* Scaler */    | (5U << 0U)
            /* PCSSCK */    | (0U << 22U)
            /* CSSCK */     | (8U << 12U)
            /* PASC */      | (0U << 20U)
            /* ASC */       | (8U << 8U)
            /* PDT */       | (0U << 18U)
            /* DT */        | (8U << 4U) ),
        .CtarSel = 0U,
        .SpiJobPriority = 0U,
        .JobEndNotification = NULL_PTR,
        .NoOfChannels = 1U,
        .ChannelList = SpiJob_4_ChannelList,
    },
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_JobType, SPI_CONST) SpiSequence_0_JobList[1] = 
{
    0U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_JobType, SPI_CONST) SpiSequence_1_JobList[1] = 
{
    1U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_JobType, SPI_CONST) SpiSequence_2_JobList[1] = 
{
    2U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_JobType, SPI_CONST) SpiSequence_3_JobList[1] = 
{
    3U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_JobType, SPI_CONST) SpiSequence_4_JobList[1] = 
{
    4U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_SequenceCfgType, SPI_CONST) SpiSequenceConfiguration[SPI_TOTAL_SEQUENCE] =
{
    {
        /* SpiSequence_0 */
        .SequenceId = 0U,
        .InterruptableSequence = FALSE,
        .NoOfJobs = 1U,
        .JobList = SpiSequence_0_JobList,
        .SequenceEndNotification = NULL_PTR,
    },
    {
        /* SpiSequence_1 */
        .SequenceId = 1U,
        .InterruptableSequence = FALSE,
        .NoOfJobs = 1U,
        .JobList = SpiSequence_1_JobList,
        .SequenceEndNotification = NULL_PTR,
    },
    {
        /* SpiSequence_2 */
        .SequenceId = 2U,
        .InterruptableSequence = FALSE,
        .NoOfJobs = 1U,
        .JobList = SpiSequence_2_JobList,
        .SequenceEndNotification = NULL_PTR,
    },
    {
        /* SpiSequence_3 */
        .SequenceId = 3U,
        .InterruptableSequence = FALSE,
        .NoOfJobs = 1U,
        .JobList = SpiSequence_3_JobList,
        .SequenceEndNotification = NULL_PTR,
    },
    {
        /* SpiSequence_4 */
        .SequenceId = 4U,
        .InterruptableSequence = FALSE,
        .NoOfJobs = 1U,
        .JobList = SpiSequence_4_JobList,
        .SequenceEndNotification = NULL_PTR,
    },
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_HwUnitCfgType, SPI_CONST) Spi_HwConfiguration[SPI_TOTAL_HWUNIT] = 
{
    {
        .HwDeviceIdx = 0,
        .HwDevice = DSPI0
    },
    {
        .HwDeviceIdx = 1,
        .HwDevice = DSPI1
    },
    {
        .HwDeviceIdx = 2,
        .HwDevice = DSPI3
    },
    {
        .HwDeviceIdx = 3,
        .HwDevice = DSPI2
    },
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"


#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(Spi_HwDeviceCfgType, SPI_CONST) Spi_HwDeviceConfiguration[SPI_TOTAL_HWUNIT] = 
{
    {
        .HwIdx = 0,
        .HwDevice = DSPI0,
    },
    {
        .HwIdx = 1,
        .HwDevice = DSPI1,
    },
    {
        .HwIdx = 2,
        .HwDevice = DSPI3,
    },
    {
        .HwIdx = 3,
        .HwDevice = DSPI2,
    },
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
static CONST(uint8, SPI_CONST) Spi_DeviceMap[] =
{
    (uint8)(0U),
    (uint8)(0U),
    (uint8)(2U),
    (uint8)(2U)
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
CONST(Spi_ConfigType, SPI_CONST) Spi_Configuration = 
{
    .SequenceNum = 5U,
    .JobNum = 5U,
    .ChannelNum = 5U,
    .HwUnitNum = 4U,
    .HwDeviceNum = 4U,
    .ChannelConfiguration = SpiChannelConfiguration,
    .JobConfiguration = SpiJobConfiguration,
    .SequenceConfiguration = SpiSequenceConfiguration,
    .HwConfiguration = Spi_HwConfiguration,
    .HwDeviceConfiguration = Spi_HwDeviceConfiguration,
    .DeviceMap = Spi_DeviceMap
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONFIG_DATA
#include "Spi_MemMap.h"
CONST(uint32, SPI_CONST) Spi_HandleMap[8U] = 
{
    0U,
    1U,
    3U,
    2U,
    0U,
    0U,
    0U,
    0U,
};
#define SPI_STOP_SEC_CONFIG_DATA
#include "Spi_MemMap.h"

#ifdef __cplusplus
}
#endif
