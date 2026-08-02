/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS, " AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* @file     SDAdc.h
* @version  3.0.0
* @date     2024 - 02 - 28
* @brief    Initial version.
*
*****************************************************************************/
/* PRQA S 0722,3432,1535 EOF*/

#ifndef SDADC_H
#define SDADC_H

#include "SDAdc_Cfg.h"
#include "SDAdc_LLDriver.h"
#include "SchM_Sdadc.h"

#define SDADC_H_VENDOR_ID                     176
#define SDADC_H_AR_REL_MAJOR_VER              4
#define SDADC_H_AR_REL_MINOR_VER              4
#define SDADC_H_AR_REL_REV_VER                0
#define SDADC_H_SW_MAJOR_VER                  3
#define SDADC_H_SW_MINOR_VER                  0
#define SDADC_H_SW_PATCH_VER                  0

#if (SDADC_CFG_H_VENDOR_ID               != SDADC_H_VENDOR_ID)
    #error " NON-MATCHED DATA : SDADC_H_VENDOR_ID "
#endif
#if (SDADC_CFG_H_AR_REL_MAJOR_VER    != SDADC_H_AR_REL_MAJOR_VER)
    #error " NON-MATCHED DATA : SDADC_H_AR_REL_MAJOR_VER "
#endif
#if (SDADC_CFG_H_AR_REL_MINOR_VER    != SDADC_H_AR_REL_MINOR_VER)
    #error " NON-MATCHED DATA : SDADC_H_AR_REL_MINOR_VER "
#endif
#if (SDADC_CFG_H_AR_REL_REV_VER != SDADC_H_AR_REL_REV_VER)
    #error " NON-MATCHED DATA : SDADC_H_AR_REL_REV_VER "
#endif
#if (SDADC_CFG_H_SW_MAJOR_VER        != SDADC_H_SW_MAJOR_VER)
    #error " NON-MATCHED DATA : SDADC_H_SW_MAJOR_VER "
#endif
#if (SDADC_CFG_H_SW_MINOR_VER        != SDADC_H_SW_MINOR_VER)
    #error " NON-MATCHED DATA : SDADC_H_SW_MINOR_VER "
#endif
#if (SDADC_CFG_H_SW_PATCH_VER        != SDADC_H_SW_PATCH_VER)
    #error " NON-MATCHED DATA : SDADC_H_SW_PATCH_VER "
#endif

#define SDADC_SID_INIT                              ((uint8)0x1AU)
#define SDADC_SID_DEINIT                            ((uint8)0x1BU)
#define SDADC_SID_START_MODULATION                  ((uint8)0x1CU)
#define SDADC_SID_STOP_MODULATION                   ((uint8)0x1DU)
#define SDADC_SID_READ_STREAM_RESULTS               ((uint8)0x1EU)
#define SDADC_SID_READ_RESULT                       ((uint8)0x1FU)
#define SDADC_SID_GET_STATUS                        ((uint8)0x20U)
#define SDADC_SID_SETUP_RESULT_BUFFER               ((uint8)0x21U)
#define SDADC_SID_START_CARRIER_SIGNAL              ((uint8)0x22U) //not supported
#define SDADC_SID_STOP_CARRIER_SIGNAL               ((uint8)0x23U) //not supported
#define SDADC_SID_ENABLE_NOTIFICATIONS              ((uint8)0x24U)
#define SDADC_SID_DISABLE_NOTIFICATIONS             ((uint8)0x25U)
#define SDADC_SID_GET_TIMESTAMP                     ((uint8)0x26U) //not supported
#define SDADC_SID_START_CALIBRATION                 ((uint8)0x27U)
#define SDADC_SID_GET_CALIBRATION_STATUS            ((uint8)0x28U) //not supported
#define SDADC_SID_INITCHECK                         ((uint8)0x29U)
#define SDADC_SID_ISR                               ((uint8)0x2AU)
#define SDADC_SID_TIMERISR                          ((uint8)0x2BU)
#define SDADC_SID_GET_VERSION_INFO                  ((uint8)0x2CU)
#define SDADC_SID_RESTART_DEMODULATOR               ((uint8)0x2DU) //not supported
#define SDADC_SID_GET_IRMS_VALUE                    ((uint8)0x2EU) //not supported
#define SDADC_SID_SET_GAINCORR_REG_VALUE            ((uint8)0xF0U)
#define SDADC_SID_RESTART_INTEGRATOR                ((uint8)0xF1U)
#define SDADC_SID_GET_SDCAP_VALUE                   ((uint8)0xF2U) //not supported
#define SDADC_SID_MAIN_FUNCTION                     ((uint8)0xF3U)

#define SDADC_E_NO_ERR                              ((uint8)0x00U)
#define SDADC_E_PARAM_CONFIG                        ((uint8)0x01U)
#define SDADC_E_ALREADY_INITIALIZED                 ((uint8)0x02U)
#define SDADC_E_UNINIT                              ((uint8)0x03U)
#define SDADC_E_BUSY                                ((uint8)0x04U)
#define SDADC_E_PARAM_CHANNEL                       ((uint8)0x05U)
#define SDADC_E_PARAM_POINTER                       ((uint8)0x06U)
#define SDADC_E_INV_LINEAR_BUFFER_CONFIG            ((uint8)0x07U)
#define SDADC_E_INV_CIRCULAR_BUFFER_CONFIG          ((uint8)0x08U)
#define SDADC_E_INVALID_BUFFER_CONFIG               ((uint8)0x09U)
#define SDADC_E_UNIDLE                              ((uint8)0x0AU)
#define SDADC_E_CARRIER_ALREADY_RUNNING             ((uint8)0x0BU)
#define SDADC_E_NOTIF_CAPABILITY                    ((uint8)0x0CU)
#define SDADC_E_SINGLE_ACCESSMODE_TIMESTAMP         ((uint8)0x0DU)
#define SDADC_E_CALIB_RUNNING                       ((uint8)0x0EU)
#define SDADC_E_INV_BUFFER_SIZE                     ((uint8)0x0FU)
#define SDADC_E_INVALID_BUFFER_POINTER              ((uint8)0x10U)
#define SDADC_E_INVALID_PARAM_VALUE                 ((uint8)0x11U)
#define SDADC_E_INVALID_PARAM_DELAY                 ((uint8)0x12U)
#define SDADC_E_BUFFER_FULL                         ((uint8)0x13U)
#define SDADC_E_PARAM_ERROR                         ((uint8)0x14U)

#define SDADC_IDLE                             ((Sdadc_ChannelstatusType)0x0U)
#define SDADC_BUSY                             ((Sdadc_ChannelstatusType)0x1U)
#define SDADC_RESULT_READY                     ((Sdadc_ChannelstatusType)0x2U)

#define SDADC_READSTREAM_ERROR               (0xFFFFU)
#define SDADC_MAX_BUFFER_LENGTH              (0xFFFEU)

#define SOFTWARE_TRIG (0x0U)
#define HARDWARE_TRIG (0x1U)

#if (SDADC_ENABLE_MULTICORE == STD_ON)
    #define SDAdc_GetCoreID()     (1U << GetCoreID())
#else
    #define SDAdc_GetCoreID()     (1U << SDADC_DEFAULT_COREID)
#endif


typedef uint8 Sdadc_ChannelType;
typedef uint16 Sdadc_SizeType;
typedef sint16 Sdadc_ResultType;
typedef uint8 Sdadc_ChannelStatusType;
typedef uint16 Sdadc_TimeStampType;
typedef uint8 Sdadc_CalibrationStatusType;
typedef uint32 Sdadc_ChannelMaskType;
typedef uint16 Sdadc_IrmsValueType;
typedef uint8 Sdadc_GainCorrType;
typedef uint32 Sdadc_DelayType;
typedef uint8 Sdadc_SdcapValueType;
typedef uint8 Sdadc_ChannelstatusType;

typedef void (*Sdadc_NotifyType)(void);

typedef enum
{
    SDADC_UNINIT = 0U,
    SDADC_INITED = 1U,
} Sdadc_InitStateType;

typedef enum
{
    SDADC_STREAM_LINEAR_BUFFER=0U,
    SDADC_CIRCULAR_BUFFER = 1U,
} Sdadc_BufferModeType;

typedef enum
{
    SDADC_USE_INTERRUPT = 0U,
    SDADC_USE_DMA = 1U,
    SDADC_USE_POLLING = 2U,
} Sdadc_ConvMethodType;

typedef enum 
{
    HWTRIGSEL_TOM2_4 = 0U,
    HWTRIGSEL_TOM2_5 = 1U,
    HWTRIGSEL_TOM2_6 = 2U,
    HWTRIGSEL_TOM2_7 = 3U,
    HWTRIGSEL_TOM2_8 = 4U,
    HWTRIGSEL_TOM2_9 = 5U,
    HWTRIGSEL_TOM2_10 = 6U,
    HWTRIGSEL_TOM2_11 = 7U,
    HWTRIGSEL_ATOM3_0 = 8U,
    HWTRIGSEL_ATOM3_1 = 9U,
    HWTRIGSEL_ATOM3_2 = 10U,
    HWTRIGSEL_ATOM3_3 = 11U,
    HWTRIGSEL_ATOM3_4 = 12U,
    HWTRIGSEL_ATOM3_5 = 13U,
    HWTRIGSEL_ATOM3_6 = 14U,
    HWTRIGSEL_ATOM3_7 = 15U,
    HWTRIGSEL_SDADC0 = 16U,
    HWTRIGSEL_SDADC1 = 17U,
    HWTRIGSEL_SDADC2 = 18U,
    HWTRIGSEL_SDADC3 = 19U,
    HWTRIGSEL_SDADC4 = 20U,
    HWTRIGSEL_SDADC6 = 21U,
    HWTRIGSEL_SDADC7 = 22U,
    HWTRIGSEL_SDADC8 = 23U,
	NO_HWTRIG = 255U,
} Sdadc_HwTrigChSelType;

typedef enum 
{
    SOURCE_DISABLE = 0U,
    TOM2_4_SOURCE = 0x10U,
    TOM2_5_SOURCE = 0x11U,
    TOM2_6_SOURCE = 0x12U,
    TOM2_7_SOURCE = 0x13U,
    TOM2_8_SOURCE = 0x14U,
    TOM2_9_SOURCE = 0x15U,
    TOM2_10_SOURCE = 0x16U,
    TOM2_11_SOURCE = 0x17U,
    ATOM3_0_SOURCE = 0x18U,
    ATOM3_1_SOURCE = 0x19U,
    ATOM3_2_SOURCE = 0x1aU,
    ATOM3_3_SOURCE = 0x1bU,
    ATOM3_4_SOURCE = 0x1cU,
    ATOM3_5_SOURCE = 0x1dU,
    ATOM3_6_SOURCE = 0x1eU,
    ATOM3_7_SOURCE = 0x1fU,
} Sdadc_HwTrigSourceType;

typedef enum
{
    SDADC_TRIGREG_DISABLE,
    SDADC_TRIGREG_HW5,
    SDADC_TRIGREG_HW9,
    SDADC_TRIGREG_HW11,
    SDADC_TRIGREG_HW12,
    SDADC_TRIGREG_HW13,
    SDADC_TRIGREG_HW14,
    SDADC_TRIGREG_HW15,
} Sdadc_HwTrigRegIdType;
typedef enum 
{
    SDADC_TRIG_DEFAULT = 0U,
    SDADC_TRIG_RTI,
    SDADC_TRIG_PIT0,
    SDADC_TRIG_PIT1,
    SDADC_TRIG_PIT2,
    SDADC_TRIG_PIT3,
    SDADC_TRIG_ETPUA28,
    SDADC_TRIG_ETPUA29,
    SDADC_TRIG_ETPUA30,
    SDADC_TRIG_ETPUA31,
    SDADC_TRIG_ETPUB28,
    SDADC_TRIG_ETPUB29,
    SDADC_TRIG_ETPUB30,
    SDADC_TRIG_ETPUB31,
    SDADC_TRIG_ETPUC28,
    SDADC_TRIG_ETPUC29,
    SDADC_TRIG_ETPUC30,
    SDADC_TRIG_ETPUC31,
    SDADC_TRIG_EMIOS0_CH16,
    SDADC_TRIG_EMIOS0_CH17,
    SDADC_TRIG_EMIOS0_CH18,
    SDADC_TRIG_EMIOS0_CH19,
    SDADC_TRIG_EMIOS0_CH20,
    SDADC_TRIG_EMIOS0_CH21,
    SDADC_TRIG_EMIOS0_CH22,
    SDADC_TRIG_EMIOS0_CH23,
    SDADC_TRIG_EMIOS1_CH2,
    SDADC_TRIG_EMIOS1_CH3,
    SDADC_TRIG_EMIOS1_CH4,
    SDADC_TRIG_EMIOS1_CH5,
    SDADC_TRIG_EMIOS1_CH6,
    SDADC_TRIG_EMIOS1_CH7,
    SDADC_TRIG_ETRIG1_ADDR7,
    SDADC_TRIG_ETRIG0_ADDR7,
    SDADC_TRIG_ETRIG1_ADDR96,
    SDADC_TRIG_ETRIG0_ADDR96,
    SDADC_TRIG_ETPUA7,
    SDADC_TRIG_ETPUA14,
    SDADC_TRIG_ETPUA22,
    SDADC_TRIG_ETPUA26,
    SDADC_TRIG_ETPUA27,
    SDADC_TRIG_ETPUA30_PIT0,
    SDADC_TRIG_ETPUA30_PIT1,
    SDADC_TRIG_ETPUC28_LSL9,
    SDADC_TRIG_ETPUC29_LSL9,
    SDADC_TRIG_ETPUC30_LSL9,
    SDADC_TRIG_ETPUC31_LSL9,
    SDADC_TRIG_EMIOS1_CH2_PIT2,
    SDADC_TRIG_EMIOS1_CH2_PIT3,
} Sdadc_HwTrigChIDType;

typedef struct
{
    P2VAR(uint32, SDADC_VAR, SDADC_APPL_CONST) ChannelResBuffer;
    VAR(Sdadc_SizeType, SDADC_VAR) NumofValidConRes;
    VAR(Sdadc_SizeType, SDADC_VAR) ChannelBufferSize;
    VAR(Sdadc_ChannelstatusType, SDADC_VAR) ChannelStatus;
    VAR(boolean, SDADC_VAR) NotifyStatus;
} Sdadc_ChannelDataType;

typedef struct 
{
    VAR(Sdadc_InstanceType, SDADC_VAR) Sdadc_InstanceId;
    P2CONST(Sdadc_ConfigType, SDADC_CONST, ADC_APPL_CONST) Sdadc_Config;
    VAR(Sdadc_BufferModeType, SDADC_VAR) Sdadc_BufferMode;
    VAR(Sdadc_ConvMethodType, SDADC_VAR) Sdadc_ConvMethod;
    VAR(Sdadc_NotifyType, SDADC_VAR) Sdadc_NewResultNotify;
    VAR(Sdadc_NotifyType, SDADC_VAR) Sdadc_BufferFullNotifyPtr;
    VAR(uint8, SDADC_VAR) Sdadc_SwOrHw;
    VAR(Sdadc_HwTrigChSelType, SDADC_VAR) Sdadc_HwTrigSrc;
    VAR(Sdadc_HwTrigRegIdType, SDADC_VAR) Sdadc_HwTrigRegId;
    VAR(Sdadc_HwTrigChIDType, SDADC_VAR) Sdadc_HwTrigChID;
} SdAdc_InstanceConfigType; 

typedef struct{
    VAR(uint16, SDADC_VAR) SdAdc_ChannelIndex;
    VAR(uint8, SDADC_VAR) SdAdc_CoreId;
} SdAdc_CoreMapItemType;

typedef struct 
{
    P2CONST(SdAdc_InstanceConfigType, SDADC_VAR, SDADC_APPL_CONST) SdAdc_InstanceConfig;
    P2CONST(SdAdc_CoreMapItemType, SDADC_CONST, SDADC_APPL_CONST) SdAdc_CoreMapItem;
} SdAdc_TotalConfigType;

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) Sdadc_Init(CONSTP2CONST(SdAdc_TotalConfigType, SDADC_CONST, SDADC_APPL_CONST) ConfigPtr);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) Sdadc_DeInit(void);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_StartModulation(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_StopModulation(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Sdadc_SizeType, SDADC_CODE) Sdadc_ReadStreamResults \
(
    CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId, \
    CONSTP2VAR(Sdadc_ResultType, SDADC_CONST, SDADC_APPL_CONST) ResultLinearBufferPtr \
);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_ReadResult \
(
    CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId, \
    CONSTP2VAR(Sdadc_ResultType, SDADC_CONST, SDADC_APPL_CONST) ResultPtr \
);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Sdadc_ChannelStatusType, SDADC_CODE) Sdadc_GetStatus(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_SetupResultBuffer \
(
    CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId,\
	P2VAR(uint32, SDADC_VAR, SDADC_APPL_CONST) DataBufferPtr, \
    CONST(Sdadc_SizeType, SDADC_CONST) Size \
);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_StartCarrierSignal(void);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_StopCarrierSignal(void);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) Sdadc_EnableNotifications(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) Sdadc_DisableNotifications(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Sdadc_TimeStampType, SDADC_CODE) Sdadc_GetTimestamp(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_StartCalibration(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Sdadc_CalibrationStatusType, SDADC_CODE) Sdadc_GetCalibrationStatus(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_InitCheck(CONSTP2CONST(SdAdc_TotalConfigType, SDADC_CONST, SDADC_APPL_CONST) ConfigPtr);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) Sdadc_GetVersionInfo(CONSTP2VAR(Std_VersionInfoType, SDADC_CONST, SDADC_APPL_CONST) versioninfo);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_RestartDemodulator(CONST(Sdadc_ChannelMaskType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Sdadc_IrmsValueType, SDADC_CODE) Sdadc_GetIrmsValue(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h" 

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_SetGainCorrRegValue \
(
    CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId, \
    CONST(Sdadc_GainCorrType, SDADC_CONST) RegValue \
);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Std_ReturnType, SDADC_CODE) Sdadc_RestartIntegrator \
( \
    CONST(Sdadc_ChannelMaskType, SDADC_CONST) ChannelId, \
    CONST(Sdadc_DelayType, SDADC_CONST) Delay \
);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(Sdadc_SdcapValueType, SDADC_CODE) Sdadc_GetSdcapValue(CONST(Sdadc_ChannelType, SDADC_CONST) ChannelId);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

#define SDADC_START_SEC_CODE
#include "Sdadc_MemMap.h"
FUNC(void, SDADC_CODE) Sdadc_MainFunction(void);
#define SDADC_STOP_SEC_CODE
#include "Sdadc_MemMap.h"

extern CONST(SdAdc_TotalConfigType, SDADC_CONST) SdAdc_TotalConfig;
extern P2CONST(SdAdc_TotalConfigType, SDADC_CONST, SDADC_APPL_CONST) sdAdc_ConfigPtr[SDADC_CORE_NUM];
extern VAR(Sdadc_ChannelDataType, SDADC_VAR) Sdadc_ChannelData[SDADC_INSTANCE_CDG_NUM][SDADC_CORE_NUM];
extern CONSTP2VAR(SDADC_TagType, SDADC_CONST, SDADC_APPL_CONST) Adc_SdadcBase0[ADC_SDADC_MAX_INSTANCE];
extern VAR(Sdadc_ChannelType, ADC_VAR) SDAdc_gIrqMapping[ADC_SDADC_MAX_INSTANCE][SDADC_CORE_NUM];

#endif /* SDADC_H */

