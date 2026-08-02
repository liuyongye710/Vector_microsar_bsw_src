/*
********************************************************************************
*
* File name: Xcp_Lcfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: yong.zhang/2019.12.27
* Change: New created
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: fangtao/2020.08.11
* Change: Added channel name and length.
* Cause: Bugfix.
********************************************************************************
* Version: 3.0
* Author/Date: FangT/2021.03.03
* Change: Add checksum and Multi pudid functions.
* Cause: Optimization
********************************************************************************
* Version: 3.1
* Author/Date: lqiao/2022.09.16
* Change: Add XCP_gcaCAN_Msg_CRO and XCP_gcaCAN_Msg_DTO
* Cause: new.
********************************************************************************
* Version: 3.2
* Author/Date: ChenQJ/2023.10.31
* Change: Fix compile warning.
* Cause: Bugfix.
********************************************************************************
* Version: 3.3
* Author/Date: lqiao/2024.03.14
* Change: Delete XCP_DAQ_LIST_NUM、XCP_DTO_NUM、XCP_ODT_NUM、XCP_ODTENTRY_NUM
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: lqiao/2024.05.16
* Change: Add XCP_REMAPPING_CNT、Xcp_InitRam_Addr、XCP_SINGLE_PT_CN、
          Xcp_Single_Pointer.
          Delete XcpEventName_Array_Define.
		  Modify XcpEventName.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: KangJH/2024.06.20
* Change: 1.Modify coding specification problems.
*         2.Add Memmap segment definition.
* Cause: Update
********************************************************************************
*/
#ifndef XCP_LCFG_H_
#define XCP_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"
#include "Xcp_Cfg.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define XcpConf_XcpEventChannel_0          (0U)
#define XcpConf_XcpEventChannel_1          (1U)
#define XcpConf_XcpEventChannel_2          (2U)

#define XCP_EVENT_CHANNEL_NUM              (3U)
#define XCP_PDU_LIST                            (1U)   /* Xcp/XcpConfig/XcpPdus/ */
#define XCP_TXPDU_LIST                     (1U)
#define XCP_RXPDU_LIST                     (1U)
#define XCP_SAFELEN                        (4U)
#define XCP_BLOCK_NUM                      (0U)
#define XCP_OVERLAY_CNT                    (1U)
#define XCP_CONNECTION_CFG_NUM             (1U)
/* DAQ Timestamp Unit. */
#define DAQ_TIMESTAMP_UNIT_1NS              (0u << 4u)
#define DAQ_TIMESTAMP_UNIT_10NS             (1u << 4u)
#define DAQ_TIMESTAMP_UNIT_100NS            (2u << 4u)
#define DAQ_TIMESTAMP_UNIT_1US              (3u << 4u)
#define DAQ_TIMESTAMP_UNIT_10US             (4u << 4u)
#define DAQ_TIMESTAMP_UNIT_100US            (5u << 4u)
#define DAQ_TIMESTAMP_UNIT_1MS              (6u << 4u)
#define DAQ_TIMESTAMP_UNIT_10MS             (7u << 4u)
#define DAQ_TIMESTAMP_UNIT_100MS            (8u << 4u)
#define DAQ_TIMESTAMP_UNIT_1S               (9u << 4u)
#define DAQ_TIMESTAMP_UNIT_1PS              (10u << 4u)
#define DAQ_TIMESTAMP_UNIT_10PS             (11u << 4u)
#define DAQ_TIMESTAMP_UNIT_100PS            (12u << 4u)
/* DAQ Timestamp Unit Tick,base 1ms. */
#define DAQ_TIMESTAMP_UNIT_TICK_1PS         (0.000000001f)
#define DAQ_TIMESTAMP_UNIT_TICK_10PS        (0.00000001f)
#define DAQ_TIMESTAMP_UNIT_TICK_100PS       (0.0000001f)
#define DAQ_TIMESTAMP_UNIT_TICK_1NS         (0.0000001f)
#define DAQ_TIMESTAMP_UNIT_TICK_10NS        (0.00001f)
#define DAQ_TIMESTAMP_UNIT_TICK_100NS       (0.0001f)
#define DAQ_TIMESTAMP_UNIT_TICK_1US         (0.001f)
#define DAQ_TIMESTAMP_UNIT_TICK_10US        (0.01f)
#define DAQ_TIMESTAMP_UNIT_TICK_100US       (0.1f)
#define DAQ_TIMESTAMP_UNIT_TICK_1MS         (1.0f)
#define DAQ_TIMESTAMP_UNIT_TICK_10MS        (10.0f)
#define DAQ_TIMESTAMP_UNIT_TICK_100MS       (100.0f)
#define DAQ_TIMESTAMP_UNIT_TICK_1S          (1000.0f)
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef enum
{
    XCP_BUS_NULL = 0U,
    XCP_BUS_CAN ,
    XCP_BUS_CANFD,
    XCP_BUS_ETHERNET
}Xcp_BusType;

typedef struct
{
    uint8 XcpEventChannelConsistency;
    uint8 XcpEventChannelMaxDaqList;
    uint8 XcpEventChannelNumber;
    uint8 XcpEventChannelPriority;
    uint8 XcpEventChannelTimeCycle;
    uint8 XcpEventChannelTimeUnit;
    uint8 XcpEventChannelType;
    uint8 XcpEventChannelTriggeredDaqListRef;
}Xcp_EventChannelType;

typedef struct
{
    uint8 XcpDtoPid;
    uint8 XcpDto2PduMapping;
}Xcp_DtoType;

typedef struct
{
    uint32 XcpOdtEntryAddress;
    uint8 XcpOdtEntryBitOffset;
    uint8 XcpOdtEntryLength;
    uint8 XcpOdtEntryNumber;
}Xcp_OdtEntryType;

typedef struct
{
    uint8 XcpOdtEntryMaxSize;
    uint8 XcpOdtNumber;
    uint8 XcpOdt2DtoMapping;
    const Xcp_OdtEntryType* XcpOdtEntry;
}Xcp_OdtType;

typedef struct
{
    uint8 XcpDaqListNumber;
    uint8 XcpDaqListType;
    uint8 XcpMaxOdt;
    uint8 XcpMaxOdtEntries;
    const Xcp_DtoType* XcpDto;
    const Xcp_OdtType* XcpOdt;
}Xcp_DaqListType;

typedef struct
{
    uint16 XcpPduId;
    uint16 XcpPduRef;
}Xcp_PduType;

typedef struct{
    uint8 accessType;            /* page access Permission. */
    uint8 accessScope;           /* calibration,DAQ/STIM */
    uint32 addr_wp;              /* Starting address of Working Page. */
    uint32 addr_rp;              /* Starting address of Reference Page. */
    uint32 len;                  /* Ram partition length. */
}Xcp_Addr_st;

typedef struct{
    uint16 BlockId;
    uint8 RequestResp;
    uint8 ReadResp;
    uint8* DataPtr;
    uint16 DataSize;
}Xcp_NvmBlockId_st;

/* Configuration data structure for Xcp connection. */
typedef struct
{
    uint8 XcpConnectionId;       /* Xcp connection ID, equivalent sequence number. */
    Xcp_BusType XcpBusType;      /* Xcp Transport Layer Bus type. */
    uint16 RxXcpPduIdRef;        /* Reference the value of XcpPduId in Xcp_RxPdu. */
    uint16 TxXcpPduIdRef;        /* Reference the value of XcpPduId in Xcp_TxPdu. */
    uint16 XcpOpenSocketPduRef;  /* Reference the value of SoAdTxPduId. */
    uint8 Xcp_Max_Cto;           /* connection specific MAX_CTO. */
    uint16 Xcp_Max_Dto;          /* connection specific MAX_DTO. */
    uint8 XcpOdtEntriesCount;    /* connection Odt entry count. */
    uint8 XcpTimestampType;      /* connection time tamp type. */
}Xcp_ConnectionCfgType;

/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/
#define XCP_START_SEC_CONFIG_DATA
#include "Xcp_MemMap.h"
extern CONST(Xcp_EventChannelType, XCP_CONFIG_DATA) Xcp_EventChannel[XCP_EVENT_CHANNEL_NUM];
extern CONST(uint8, XCP_CONFIG_DATA) XcpEventName[XCP_EVENT_CHANNEL_NUM][15];
extern CONST(uint8, XCP_CONFIG_DATA) XcpEventNameLength[XCP_EVENT_CHANNEL_NUM];
extern CONST(Xcp_PduType, XCP_CONFIG_DATA) Xcp_RxPdu[XCP_RXPDU_LIST];
extern CONST(Xcp_PduType, XCP_CONFIG_DATA) Xcp_TxPdu[XCP_TXPDU_LIST];
extern CONST(Xcp_ConnectionCfgType, XCP_CONFIG_DATA) Xcp_ConnectionCfg[XCP_CONNECTION_CFG_NUM + 1U];
#define XCP_STOP_SEC_CONFIG_DATA
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"
extern VAR(uint8, XCP_VAR_NO_INIT) XCP_gcaCAN_Msg_CRO[64U];
extern VAR(uint8, XCP_VAR_NO_INIT) XCP_gcaCAN_Msg_DTO[64U];
#if( RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY )
extern VAR(Xcp_Addr_st, XCP_VAR_NO_INIT) Xcp_Addr_Temp[XCP_OVERLAY_CNT];
#endif
#define XCP_STOP_SEC_VAR_NO_INIT
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_INIT
#include "Xcp_MemMap.h"
extern VAR(uint8, XCP_VAR_INIT) Xcp_Resource_Array[XCP_SAFELEN];
extern VAR(Xcp_NvmBlockId_st, XCP_VAR_INIT)Xcp_NvmBlockId[XCP_BLOCK_NUM + 1];
#define XCP_STOP_SEC_VAR_INIT
#include "Xcp_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

extern FUNC(void, XCP_CODE) XcpGetSeed(void);
extern FUNC(uint8, XCP_CODE) XcpUnlock
(
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)avcpKey,
    uint8 avcLength
);

extern FUNC(uint8, XCP_CODE) XcpAppl_FlashClear
(
    uint32 setMta,
    uint32 clearSize
);
extern FUNC(uint8, XCP_CODE) XcpAppl_FlashProgram
(
    uint32 setMta,
    P2CONST(uint8, AUTOMATIC, XCP_APPL_CONST)dataPtr,
    uint32 writeSize
);
extern FUNC(uint8, XCP_CODE) XcpAppl_Reset(void);

#if( (RTECALIBRATIONSUPPORT == XCP_CAL_METHOD_OVERLAY) )
extern FUNC(uint8, XCP_CODE) XcpOverlayMapping
(
    uint8 segment,
    uint8 page,
    uint8 mode
);
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#endif  /* XCP_LCFG_H_ */


