/*
********************************************************************************
*
* File name: Dcm_Lcfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: Tanlx/20190501
* Change: Autosar
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: Tanlx/20190513
* Change: Autosar
* Cause: Modify format.
********************************************************************************
* Version: 1.2
* Author/Date : Liuziyang/2019.11.22
* Change: The format of code and comment.
* Cause: Modify the code according to the coding specification.
********************************************************************************
* Version: 1.3
* Author/Date : Songqingwei/2020.01.22
* Change: Change the DCM_INVALID_BLOCKID from 0xFFFFFFFF to 0xFFFF.
* Cause: Invalid NvM BlockId is error.
********************************************************************************
* Version: 3.0
* Author/Date : ZhuCY/2021.10.27
* Change: Modify header file name.
* Cause: Optimization.
********************************************************************************
* Version: 3.1
* Author/Date: ZhuCY/2021.10.28
* Change: Modify header file.
* Cause: Optimization.
********************************************************************************
* Version: 3.2
* Author/Date: LQiao/2023.02.06
* Change: Add Struct. Add 38 service. 
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date: LQiao/2023.02.13
* Change: Del redundant struct.
* Cause: Optimization
********************************************************************************
*/
#ifndef DCM_LCFG_H_
#define DCM_LCFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Dcm_Cfg.h"
#include "Dcm_Cbk.h"
#include "ComM.h"
#include "ComStack_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define DCM_NUM_ZERO                                (0x0U)
#define DCM_MAX_CAN_CHANNEL                         COMM_ACTIVE_CHANNEL
#define DCM_INVALID_BLOCKID                         (0xFFFFU)
#define DCM_NUM_CHECKCOND 	                        (5U)
#define DCM_PHY 			                        (0x01U)
#define DCM_FUN                                     (0x02U)
#define DCM_PHY_FUN                                 (0x03U)
#define DCM_SERVICE_OBD                             (0x00U)
#define DCM_SERVICE_UDS                             (0x01U)

#ifndef DCM_E_GENERALREJECT
#define DCM_E_GENERALREJECT                         (0x10U)
#endif

#ifndef DCM_E_SERVICENOTSUPPORTED
#define DCM_E_SERVICENOTSUPPORTED                   (0x11U)
#endif

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#define DCM_E_SUBFUNCTIONNOTSUPPORTED               (0x12U)
#endif

#ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (0x13U)
#endif

#ifndef DCM_E_RESPONSETOOLONG
#define DCM_E_RESPONSETOOLONG                       (0x14U)
#endif

#ifndef DCM_E_BUSYREPEATREQUEST
#define DCM_E_BUSYREPEATREQUEST                     (0x21U)
#endif

#ifndef DCM_E_CONDITIONSNOTCORRECT
#define DCM_E_CONDITIONSNOTCORRECT                  (0x22U)
#endif

#ifndef DCM_E_REQUESTSEQUENCEERROR
#define DCM_E_REQUESTSEQUENCEERROR                  (0x24U)
#endif

#ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT         (0x25U)
#endif

#ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION (0x26U)
#endif

#ifndef DCM_E_REQUESTOUTOFRANGE
#define DCM_E_REQUESTOUTOFRANGE                     (0x31U)
#endif

#ifndef DCM_E_SECURITYACCESSDENIED
#define DCM_E_SECURITYACCESSDENIED                  (0x33U)
#endif

#ifndef DCM_E_INVALIDKEY
#define DCM_E_INVALIDKEY                            (0x35U)
#endif

#ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                (0x36U)
#endif

#ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED           (0x37U)
#endif

#ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED             (0x70U)
#endif

#ifndef DCM_E_TRANSFERDATASUSPENDED
#define DCM_E_TRANSFERDATASUSPENDED                 (0x71U)
#endif

#ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#define DCM_E_GENERALPROGRAMMINGFAILURE             (0x72U)
#endif

#ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER             (0x73U)
#endif

#ifndef DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING (0x78U)
#endif

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION   (0x7EU)
#endif

#ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION    (0x7FU)
#endif

#ifndef DCM_E_RPMTOOHIGH
#define DCM_E_RPMTOOHIGH                            (0x81U)
#endif

#ifndef DCM_E_RPMTOOLOW
#define DCM_E_RPMTOOLOW                             (0x82U)
#endif

#ifndef DCM_E_ENGINEISRUNNING
#define DCM_E_ENGINEISRUNNING                       (0x83U)
#endif

#ifndef DCM_E_ENGINEISNOTRUNNING
#define DCM_E_ENGINEISNOTRUNNING                    (0x84U)
#endif

#ifndef DCM_E_ENGINERUNTIMETOOLOW
#define DCM_E_ENGINERUNTIMETOOLOW                   (0x85U)
#endif

#ifndef DCM_E_TEMPERATURETOOHIGH
#define DCM_E_TEMPERATURETOOHIGH                    (0x86U)
#endif

#ifndef DCM_E_TEMPERATURETOOLOW
#define DCM_E_TEMPERATURETOOLOW                     (0x87U)
#endif

#ifndef DCM_E_VEHICLESPEEDTOOHIGH
#define DCM_E_VEHICLESPEEDTOOHIGH                   (0x88U)
#endif

#ifndef DCM_E_VEHICLESPEEDTOOLOW
#define DCM_E_VEHICLESPEEDTOOLOW                    (0x89U)
#endif

#ifndef DCM_E_THROTTLE_PEDALTOOHIGH
#define DCM_E_THROTTLE_PEDALTOOHIGH                 (0x8AU)
#endif

#ifndef DCM_E_THROTTLE_PEDALTOOLOW
#define DCM_E_THROTTLE_PEDALTOOLOW                  (0x8BU)
#endif

#ifndef DCM_E_TRANSMISSIONRANGENOTINNEUTRAL
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL         (0x8CU)
#endif

#ifndef DCM_E_TRANSMISSIONRANGENOTINGEAR
#define DCM_E_TRANSMISSIONRANGENOTINGEAR            (0x8DU)
#endif

#ifndef DCM_E_BRAKESWITCH_NOTCLOSED
#define DCM_E_BRAKESWITCH_NOTCLOSED                 (0x8FU)
#endif

#ifndef DCM_E_SHIFTERLEVERNOTINPARK
#define DCM_E_SHIFTERLEVERNOTINPARK                 (0x90U)
#endif

#ifndef DCM_E_TORQUECONVERTERCLUTCHLOCKED
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED           (0x91U)
#endif

#ifndef DCM_E_VOLTAGETOOHIGH
#define DCM_E_VOLTAGETOOHIGH                        (0x92U)
#endif

#ifndef DCM_E_VOLTAGETOOLOW
#define DCM_E_VOLTAGETOOLOW                         (0x93U)
#endif

#ifndef DCM_E_KEYON
#define DCM_E_KEYON                                 (0xF0U)
#endif

#ifndef DCM_E_HVSTATE
#define DCM_E_HVSTATE                               (0xF1U)
#endif

#define DCM_SESSION_DEFAULT_LEVEL                   (0x00U)
#define DCM_SESSION_PROG_LEVEL                      (0x01U)
#define DCM_SESSION_EXTEND_LEVEL                    (0x02U)

#define DCM_DSL_BUFFERRX                            (0x00U)
#define DCM_DSL_BUFFERTX                            (0x01U)
#define DCM_DSL_BUFFERTESTERPRESENT                 (0x02U)

#define DCM_DSL_CHANNEL_NUM                          (0x01U)
#define DCM_READ_BLOCK_NUM                           (0x00U)
#define DCM_MAINTASK_CYCLE                           (10U)
#define DCM_NUM_SERVICES                             (0x10U)
#define DCM_TIMEOUT_S3                               (5000U / DCM_MAINTASK_CYCLE)
#define DCM_DSL_BUFFERNUM                            (0x02U)
#define DCM_DSL_BUFFERLENRX                          (0x0C00U)
#define DCM_DSL_BUFFERLENTX                          (0x0C00U)
#define DCM_DSL_RESPPENDDING_NUM                     (0x0000U)
#define DCM_SPT_ADDRESSANDLENGTH_FORMAT              (0x0044U)
#define DCM_NUMOFBLOCKSIZE                           (0x0200U)
#define DCM_DSL_PROTOCOL_TX_NUM                      (1U)
#define DCM_DSL_PROTOCOL_NUM                         (2U)
#define DCM_DSL_PROTOCOL_TYPE1 (0x01U)
#define DCM_DSL_PROTOCOL_TYPE2 (0x02U)
#define DCM_NUMOFBLOCKSIZE_FILETRANS                 (0x0200U)
#if (STD_ON == DCM_SERVICE_10_ENABLED)
#define DCM_10_SUBID                                 (0x0008U)
#define DCM_10_SESSION_04_LEVEL                      (0x0003U)
#define DCM_P2_TIME_01                               (0x0032U)
#define DCM_P2EX_TIME_01                             (0x1388U)
#define DCM_P2_TIME_02                               (0x0032U)
#define DCM_P2EX_TIME_02                             (0x1388U)
#define DCM_P2_TIME_03                               (0x0032U)
#define DCM_P2EX_TIME_03                             (0x1388U)
#define DCM_P2_TIME_04                               (0x0032U)
#define DCM_P2EX_TIME_04                             (0x1388U)
#endif
#if (STD_ON == DCM_SERVICE_11_ENABLED)
#define DCM_11_SUBID                                 (0x0002U)
#define DCM_11_BLOCKIDREF                            (0xFFFFU)
#define DCM_11_BLOCKSIZE                             (4U)
#endif
#if (STD_ON == DCM_SERVICE_27_ENABLED)
#define DCM_27_ATTDELAY_ENABLE                       (STD_ON)
#define DCM_27_ATTEMPT_MONITOR                       (STD_ON)
#define DCM_27_MAX_SEED_LENGTH                       (0x04U)
#define DCM_27_SUB_NUM                               (0x0004U)
#define DCM_2701_MAX_SEED_LENGTH                     (0x04U)
#define DCM_2701_MAX_KEY_LENGTH                      (0x04U)
#define DCM_2701_ATTDELAY                            (0x2710U)
#define DCM_2701_ATTCOUNTER                          (0x03U)
#define DCM_2705_MAX_SEED_LENGTH                     (0x04U)
#define DCM_2705_MAX_KEY_LENGTH                      (0x04U)
#define DCM_2705_ATTDELAY                            (0x2710U)
#define DCM_2705_ATTCOUNTER                          (0x03U)
#define DCM_2703_MAX_SEED_LENGTH                     (0x04U)
#define DCM_2703_MAX_KEY_LENGTH                      (0x04U)
#define DCM_2703_ATTDELAY                            (0x2710U)
#define DCM_2703_ATTCOUNTER                          (0x03U)
#define DCM_2741_MAX_SEED_LENGTH                     (0x04U)
#define DCM_2741_MAX_KEY_LENGTH                      (0x04U)
#define DCM_2741_ATTDELAY                            (0x2710U)
#define DCM_2741_ATTCOUNTER                          (0x03U)
#endif
#if (STD_ON == DCM_SERVICE_28_ENABLED)
#define DCM_28_SUBID_NUM                             (0x0004U)
#define DCM_28_CONTROL_STATE_NUM                     (0x03U)
#define DCM_28_CHANNLE_NUM                           (0x04U)
#endif
#if (STD_ON == DCM_SERVICE_3E_ENABLED)
#define DCM_3E_SUBID                                 (0x0002U)
#endif
#if (STD_ON == DCM_SERVICE_85_ENABLED)
#define DCM_85_SUBID_NUM                             (0x0004U)
#endif
#if (STD_ON == DCM_SERVICE_14_ENABLED)
#define DCM_14_SUBID_NUM                             (0x0000U)
#endif
#if (STD_ON == DCM_SERVICE_2F_ENABLED)
#define DCM_2F_MAX_SUB_DID_NUM                       (0x0055U)
#endif
#if (STD_ON == DCM_SERVICE_31_ENABLED)
#define DCM_31_SUBID_NUM                             (0x0003U)
#endif
#if (STD_ON == DCM_SERVICE_87_ENABLED)
#define DCM_87_SUBID_NUM                             (0x0006U)
#endif /* STD_ON == DCM_SERVICE_87_ENABLED */
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )
#define DCM_22_MAX_DID_LIST_NUM                      (1U)
#define DCM_NUM_DIDS                                 (0x2F5U)
#define DCM_RAED_ACESS                               (0x01U)
#define DCM_WRITE_ACESS                              (0x02U)
#define DCM_RAED_AND_WRITE_ACESS                     (0x03U)
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) */
#define DCM_CANTP_SUPPORT                            (STD_ON)
#define DCM_DSP_READMEMORY_NUM (0x0000U)
#define DCM_DSP_WRITEMEMORY_NUM (0x0001U)

#define DCM_23_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_2E_WRITTIMEOUT                          (20000U / DCM_MAINTASK_CYCLE)
#define DCM_34_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_3D_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_2F_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_31_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_11_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_35_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_27_WRITTIMEOUT                          (1500U / DCM_MAINTASK_CYCLE)
#define DCM_86_WRITTIMEOUT                          (1500U / DCM_MAINTASK_CYCLE)
#define DCM_38_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_37_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)
#define DCM_36_WRITTIMEOUT                          (60000U / DCM_MAINTASK_CYCLE)

#define DCM_PROGRM_APPEAR                           (0x01U)
#define DCM_PROGRM_DISAPPEAR                        (0x00U)

#if (STD_ON == DCM_SERVICE_36_ENABLED)
#define DCM_36_PROGRAM_FLASH_NO_FINISH              (0x00U)
#define DCM_36_PROGRAM_FLASH_WAITFINISH             (0x01U)
#endif /* STD_ON == DCM_SERVICE_36_ENABLED */

#if (STD_ON == DCM_SERVICE_37_ENABLED)
#define DCM_37_REQUEST_LENGTH                       (0x00U)
#endif /* STD_ON == DCM_SERVICE_37_ENABLED */

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
#define DCM_01_SUBID                                (8U)
#define DCM_01_SUPPRORTPID (0U)
#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
#define DCM_02_SUBID                                (6U)
#define DCM_02_SUPPRORTPID (0U)
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
#define DCM_09_SUBID                                (8U)
#define DCM_09_SUPPRORTPID (0U)
#define OBD_INFOTYPE_MAX_NUM                        (0x06U)
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
#define DCM_2C_SUB_NUM_DIDS                         (3U)
#define DCM_2C_NUM_DIDS (0U)
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if ( STD_ON == DCM_SERVICE_2A_ENABLED )
#define DCM_2A_TRANSMODE_SIZE                       (3U)
#define DCM_2A_UUDT_TXBUFFER_SIZE                   (8U)
#define DCM_2A_MAX_DID_LIST_NUM                      (1U)
#define DCM_2A_TX_CHANNEL_NUM                        (0U)
#define DCM_2A_NUM_DIDS                              (0U)
#define DCM_2A_SCHEDULER_SIZE                        (1U)
#endif /* STD_ON == DCM_SERVICE_2A_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
#define DCM_86_EVENTTYPE_NUM                        (8U)

#define DCM_86_EVENTWINDOWTIME_NUM                  (0U)
#define DCM_ROE_CLEARED                             (0U)
#define DCM_ROE_STOPPED                             (1U)
#define DCM_ROE_EVENT_WINDOW_INFINITE               (1U)
#define DCM_ROE_EVENT_WINDOW_CURRENT_CYCLE          (2U)
#define DCM_ROE_BLOCKSIZE                           (20U)
#define DCM_ROE_BLOCKIDREF                          (0xFFFFU)
#define DCM_ROE_BLOCKINVALIDID                      (0xFFFFU)
#define DCM_ROE_INTERMESSAGETIME                    (1U)
#define DCM_86_EEP_EVENTNUM                         ((DCM_ROE_BLOCKSIZE - sizeof(Dcm_86_DslInfo_st))/sizeof(Dcm_86_InfoData_st))
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_27_ENABLED)
#define DCM_27_BLOCKSIZE                            DCM_27_SUB_NUM
#define DCM_27_BLOCKIDREF                           (0xFFFFU)
#define DCM_2701_SCURITYLEVEL_INDEX                 (0x00U)
#define DCM_2705_SCURITYLEVEL_INDEX                 (0x01U)
#define DCM_2703_SCURITYLEVEL_INDEX                 (0x02U)
#define DCM_2741_SCURITYLEVEL_INDEX                 (0x03U)
#define DCM_27_BLOCKINVALIDID                       (0xFFFFU)
#endif /* STD_ON == DCM_SERVICE_27_ENABLED */
 

#if (STD_ON == DCM_SERVICE_19_ENABLED)
#define DCM_19_SUBIDNUM                              (0x0010U)
#define DCM_STOP_DTC                                 (0x01U)
#define DCM_NO_STOP_DTC                              (0x00U)
#endif
#if (STD_ON == DCM_SERVICE_29_ENABLED)
#define DCM_29_AUT_CONN_NUM                          (0U)
#define DCM_29_AUT_ROLE_NUM                          (0U)
#define DCM_29_AUT_TRANSCERT_NUM                     (0U)
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#if ( STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED )
#define  DCM_SERVICEREQUESTMANUFACTURERNOTIFICATION_NUM (0U)
#endif /* STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED */

#if ( STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED )
#define  DCM_SERVICEREQUESTSUPPLIERNOTIFICATION_NUM (0U)
#endif /* STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED */

#if (STD_ON == DCM_SERVICE_35_ENABLED)
#define DCM_35_UPLOAD_BLOCKLEN                       (0x0200U)
#endif /* STD_ON == DCM_SERVICE_35_ENABLED */

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef struct{
    uint16 BlockId;
    uint8 RequestResp;
    uint8 ReadResp;
    uint8 *DataPtr;
    uint8 *DataInitPtr;
    uint16 DataSize;
} Dcm_ReadBlockId_st;

typedef struct Dcm_PROGCONDITIONSTYPE_TAG
{
    uint16  TesterSourceAddr;     /* The client ID (source address). */
    uint8   ProtocolId;           /* The protocol ID. */
    uint8   Sid;                  /* The request SID to be responded to. */
    uint8   SubFuncId;            /* The sub-function ID to be responded to. */
    boolean ReprogrammingRequest; /* Specifies whether an ECU preprogramming is needed
                                 	 (TRUE - ECU reprogramming, FALSE - no ECU reprogramming). */
    boolean ApplUpdated;          /* Specifies whether the application has been updated
                                	 (TRUE - application updated, FALSE - no application updated). */
    boolean ResponseRequired;     /* Specifies whether a response to the SID and sub-function 
	                                 has to be sent (TRUE) or just the requested diagnostic session
          					     	 shall be entered (FALSE). */
} Dcm_ProgConditionsType;

typedef uint8 (*Dcm_CheckRuleRef_p) (void);
typedef uint8 (*Dcm_CheckPreCondition_p) (void);
typedef void (*Dcm_ClearCallBackType_p) (void);

typedef struct
{
    uint32 Dcm_Session;
    uint32 Dcm_Security;
} Dcm_ServiceFilter_st;

typedef struct
{
    uint32 Dcm_AutVal;
    uint8* Dcm_CurrAutState;
} Dcm_AutFilter_st;

typedef struct
{
    uint8* BufferPtr;
    uint16 BufferLength;
}Dcm_DslBufferType;

typedef struct
{
    PduIdType RxPduId;
    PduIdType TxPduId;
    uint8 RxAdrTyp;
    Dcm_ProtocolType ActiveProtocol;
    uint8 Priority;
    uint8 ServiceTbl;
    uint16 AuthConnId;
    uint32 ClientSrcAdr;
    boolean SendRcrrpOnTransBoot;
    uint8 ComMChannel;
}Dcm_DslProtocol_st;

typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_ServiceType;
    uint16 Dcm_MinReqLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    uint16 Dcm_ProtocolFilter;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    void (*Dcm_ServiceProcessorType_p)(void);
    void (*Dcm_ServiceInitType_p)(void);
    void (*Dcm_ServicePostProcessorType_p)(uint8 acParm);
} Dcm_ServiceTableType_st;

typedef struct
{
    const Dcm_ServiceTableType_st *Dcm_DspServiceInfoTable;
} Dcm_DSDInfo_st;

typedef struct
{
    uint16 Dcm_TimeOutP2;
    uint32 Dcm_TimeOutP2Ex;
} Dcm_TimerSettingType_st;

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_MResp;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint32 Dcm_Data_ABCD;
} Dcm_01_ServiceInfoType_st;

typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_RespLen;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint8 (*Dcm_PidProcessorType_p)(uint8*, uint16*, uint8);
} Dcm_01_PidType_st;

typedef struct{
    const Dcm_01_ServiceInfoType_st* Dcm_ServiceInfoTable;
    const Dcm_01_PidType_st* Dcm_SupportPidTable;
} Dcm_01_DispatherInfo_st;

typedef enum
{
  DCM_01_NO_MRESQ = DCM_NUM_ZERO,
  DCM_01_MRESQ,
} Service01RESPType_e;
#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_MResp;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint32 Dcm_Data_ABCD;
} Dcm_02_ServiceInfoType_st;

typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_RespLen;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint8 (*Dcm_PidProcessorType_p)(uint8*, uint16*, uint8);
    uint8 Dcm_PidDataElement;
} Dcm_02_PidType_st;

typedef struct{
    const Dcm_02_ServiceInfoType_st* Dcm_ServiceInfoTable;
    const Dcm_02_PidType_st* Dcm_SupportPidTable;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Dcm_02_PidList;
} Dcm_02_DispatherInfo_st;

typedef enum
{
  DCM_02_NO_MRESQ = DCM_NUM_ZERO,
  DCM_02_MRESQ,
} Service02RESPType_e;
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_MResp;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    uint32 Dcm_Data_ABCD;
} Dcm_09_ServiceInfoType_st;

typedef struct{
    uint8 Dcm_ID;
    uint8 Dcm_RespLen;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    void (*Dcm_PidProcessorType_p)(uint8, uint8*, uint16*, uint8);
} Dcm_09_PidType_st;

typedef struct{
    const Dcm_09_ServiceInfoType_st* Dcm_ServiceInfoTable;
    const Dcm_09_PidType_st* Dcm_SupportPidTable;
} Dcm_09_DispatherInfo_st;

typedef enum
{
  DCM_09_NO_MRESQ = DCM_NUM_ZERO,
  DCM_09_MRESQ,
} Service09RESPType_e;
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if (STD_ON == DCM_SERVICE_10_ENABLED)
typedef struct
{
    uint8 Dcm_IsBoot;
    uint8 Dcm_BootPos;
} Dcm_BootSettingType_st;
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_TimerSettingType_st Dcm_RespTime;
    uint8 Dcm_DspSessionForBoot;
    uint8 Dcm_CurSession;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_10_ServiceInfoType_st;
typedef struct
{
    const Dcm_10_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_10_DispatherInfo_st;
/* This parameter defines whether this diagnostic session allows to jump to
  Bootloader (OEM Bootloader or System Supplier Bootloader) and determines, 
  from which unit the final response will be sent. */
enum
{
  DCM_NO_BOOT = DCM_NUM_ZERO,  /* This diagnostic session doesn't allow to jump to Bootloader. */
  DCM_OEM_BOOT ,  /* This diagnostic session allows to jump to OEM Bootloader and bootloader sends final response. */
  DCM_OEM_BOOT_RESPAPP,  /* This diagnostic session allows to jump to OEM Bootloader and application sends final response. */
  DCM_SYS_BOOT,  /* This diagnostic session allows to jump to System Supplier Bootloader and bootloader sends final response. */
  DCM_SYS_BOOT_RESPAPP  /* This diagnostic session allows to jump to System Supplier Bootloader and application sends final response. */
};
#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

#if (STD_ON == DCM_SERVICE_11_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_RespToEcuRst;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
}Dcm_11_ServiceInfoType_st;
typedef struct
{
    const Dcm_11_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_11_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_11_ENABLED */

#if (STD_ON == DCM_SERVICE_14_ENABLED)
typedef struct
{
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    Dcm_ClearCallBackType_p Dcm_CallBackRef;
} Dcm_14_ServiceInfoType_st;
typedef struct
{
    const Dcm_14_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_g14DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_14_ENABLED */

#if (STD_ON == DCM_SERVICE_19_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_NeedStopDtc;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    uint16 Dcm_ReqDataLength;
    void (*Dcm_ServiceProcessorType_p)(void);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_19_ServiceInfoType_st;
typedef struct
{
    const Dcm_19_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_19_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_19_ENABLED */
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )

typedef uint8 (*Dcm_CheckValueCallBackType_p) (void);
typedef Std_ReturnType (*Dcm_DidReadData_sync)(uint8* Data);
typedef Std_ReturnType (*Dcm_DidReadData_async)(Dcm_OpStatusType OpStatus, uint8* Data, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidWriteData_sync)(uint8* Data, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidWriteData_async)(Dcm_OpStatusType OpStatus, uint8* Data, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidReadDataLength)(uint16* DataLength);
typedef Std_ReturnType (*Dcm_DidConditionCheckRead_sync)(Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidConditionCheckRead_async)(Dcm_OpStatusType OpStatus,Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*Dcm_DidConditionCheckWrite)(Dcm_NegativeResponseCodeType* ErrorCode);

typedef struct
{
	Dcm_DidReadData_sync Dcm_DidReadData_sync;  
	Dcm_DidReadData_async Dcm_DidReadData_async;
}Dcm_DidReadData_st;

typedef struct
{
	Dcm_DidWriteData_sync Dcm_DidWriteData_sync;  
	Dcm_DidWriteData_async Dcm_DidWriteData_async;
}Dcm_DidWriteData_st;

typedef struct
{
	Dcm_DidConditionCheckRead_sync Dcm_DidConditionCheckRead_sync;
	Dcm_DidConditionCheckRead_async Dcm_DidConditionCheckRead_async;
}Dcm_DidConditionCheckRead_st;

typedef enum
{
	USE_BLOCK_ID = 0u,
	USE_DATA_ASYNCH_CLIENT_SERVER,
	USE_DATA_ASYNCH_CLIENT_SERVER_ERROR,
	USE_DATA_ASYNCH_FNC,
	USE_DATA_ASYNCH_FNC_ERROR,
	USE_DATA_ASYNCH_FNC_PROXY,
	USE_DATA_SENDER_RECEIVER,
	USE_DATA_SENDER_RECEIVER_AS_SERVICE,
	USE_DATA_SYNCH_CLIENT_SERVER,
	USE_DATA_SYNCH_FNC,
	USE_DATA_SYNCH_FNC_PROXY
}Dcm_DataUsedPort_e;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_Used;
    uint16 Dcm_Length;
    uint16 Dcm_BlockIdRef;
    uint8 *Dcm_BlockStarAdr;
    uint8 *Dcm_BlockDataPtr;
    uint8 Dcm_RorW;
    Dcm_DataUsedPort_e Dcm_DataUsedPort;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
    Dcm_AutFilter_st Dcm_ReadAutFilter;
    Dcm_ServiceFilter_st Dcm_WriteFilter;
    Dcm_AutFilter_st Dcm_WriteAutFilter;
    Dcm_DidReadData_st Dcm_DidReadData;    
    Dcm_DidReadDataLength Dcm_DidReadDataLength;
    Dcm_DidConditionCheckRead_st Dcm_DidCondCheckRead;
    Dcm_DidWriteData_st Dcm_DidWriteData;
	Dcm_DidConditionCheckWrite Dcm_DidCondCheckWrite;
	Dcm_CheckPreCondition_p Dcm_PreCondition;
}Dcm_22_2E_ServiceInfoType_st;

typedef struct
{
    uint16 *Dcm_22_DidList;
    uint16 *Dcm_22_DidResLen;
    const Dcm_22_2E_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_22_2E_DispatherInfo_st;
#endif

#if (STD_ON == DCM_SERVICE_27_ENABLED)
typedef struct
{
    uint8 AttemptCounter;
} Dcm_27_Security_cfg;

typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_SeedFilter;
    Dcm_ServiceFilter_st Dcm_KeyFilter;
    Dcm_AutFilter_st Dcm_ReadAutFilter;
    uint8 Dcm_NumMaxAttDelay;
    uint16 Dcm_SeedLength;
    uint16 Dcm_KeyLength;
    uint32 Dcm_DelayInvKey;
    Std_ReturnType (*Dcm_GetSeedCallBackType_p)(Dcm_OpStatusType OpStatus, uint8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode);
    Std_ReturnType (*Dcm_SendKeyCallBackType_p)(uint8* Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    Dcm_27_Security_cfg* Dcm_27_SecurityData;
    Std_ReturnType (*Dcm_GetAttemptCounterCallBackType_p)(Dcm_OpStatusType OpStatus, uint8* AttemptCounter);
    Std_ReturnType (*Dcm_SetAttemptCounterCallBackType_p)(Dcm_OpStatusType OpStatus, uint8 AttemptCounter);
}Dcm_27_ServiceInfoType_st;
typedef struct
{
    const Dcm_27_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_27_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_27_ENABLED */
#if (STD_ON == DCM_SERVICE_28_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_28_ServiceInfoType_st;

typedef struct
{
    const uint8* Dcm_ControlStete;
    const Dcm_28_ServiceInfoType_st* Dcm_ServiceInfoTable;
} Dcm_28_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_28_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
typedef struct
{
    uint8 Dcm_CertVerfCallNotifyRef;
    uint8 Dcm_RandSeedCallNotifyRef;
    uint8 Dcm_SignatureGenerateNotifyRef;
    uint8 Dcm_SignatureVerifyNotifyRef;
    uint16 Dcm_EcuChallengeLength;
    uint16 Dcm_ClientCertIdx;
    uint16 Dcm_ConnectionCertIdx;
    uint16 Dcm_ConnectionMainConnectionIdx;
    uint16 Dcm_ECUCertificateKeyElmtIdx;
    uint16 Dcm_ECUCertificateIdx;
    uint16 Dcm_PublicKeyElmtIdx;
    uint16 Dcm_RoleElmtIdx;
    uint16 Dcm_WLDIDElmtIdx;
    uint16 Dcm_WLMemorySelectionElmtIdx;
    uint16 Dcm_WLRIDElementIdx;
    uint16 Dcm_WLServicesElementIdx;
    uint32 Dcm_CertPublicKeyStoreJobIdx;
    uint32 Dcm_ClientChallengeSignJobIdx;
    uint32 Dcm_RandomJobIdx;
    uint32 Dcm_VerifyPOWNJobIdx;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_29_AutConn_st;

typedef struct
{
    uint16 Dcm_AutTransCertEvalId;
    uint16 KeyMCertId;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
}Dcm_29_AutTransCert_st;

typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Used;
    uint16 Dcm_Length;
    Dcm_ServiceFilter_st Dcm_Filter;
    void (*Dcm_ServiceProcessorType_p)(void);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_29_ServiceInfoType_st;

typedef struct
{
    const Dcm_29_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_29_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
    Dcm_AutFilter_st Dcm_AutFilter;
    Std_ReturnType (*Dcm_38_Info_Trans)(const Dcm_38_ServiceInfoType_Req* DataInVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Std_ReturnType (*Dcm_38_Info_Capture)(Dcm_38_ServiceInfoType_Res* DataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
} Dcm_38_ServiceInfoType_st;

typedef struct
{
    const Dcm_38_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_38_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#if ( (STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED) || (STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED) )
typedef Std_ReturnType (*Dcm_ServiceRequestNotification_Indication)
(
    uint8 SID,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) RequestData,
    uint16 DataSize,
    uint8 ReqType,
    uint16 SourceAddress,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);

typedef Std_ReturnType (*Dcm_ServiceRequestNotification_Confirmation)
(
    uint8 SID,
    uint8 ReqType,
    uint16 SourceAddress,
    Std_ReturnType ConfirmationStatus
);
#endif/* (STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED) || (STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED) */

#if ( STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED )
typedef struct
{
    Dcm_ServiceRequestNotification_Indication indication[DCM_SERVICEREQUESTMANUFACTURERNOTIFICATION_NUM  + 1U];
    Dcm_ServiceRequestNotification_Confirmation confirmation[DCM_SERVICEREQUESTMANUFACTURERNOTIFICATION_NUM  + 1U];
} Dcm_ServiceRequestManufacturerNotification_st;
#endif /* STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED */

#if ( STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED )
typedef struct
{
    Dcm_ServiceRequestNotification_Indication indication[DCM_SERVICEREQUESTSUPPLIERNOTIFICATION_NUM + 1U];
    Dcm_ServiceRequestNotification_Confirmation confirmation[DCM_SERVICEREQUESTSUPPLIERNOTIFICATION_NUM + 1U];
} Dcm_ServiceRequestSupplierNotification_st;
#endif /* STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED */

#if (STD_ON == DCM_SERVICE_2F_ENABLED)
enum
{
    DCM_2F_SIGNAL_TYPE_FIXED = 0x00U,
    DCM_2F_SIGNAL_TYPE_VARIABLE
};

typedef struct
{
    uint8 Dcm_length_Sub00_Sub01_Sub02;
    uint8 Dcm_length_Sub03;
    uint8 Dcm_length_Mask;
} Dcm_2F_RequestDataLen_st;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_DspDidUsed;
    uint8 Dcm_FixedLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_2F_RequestDataLen_st Dcm_Length;
    uint8 (*Dcm_00_IOControlCallBackType_p)(const uint8* DataInVar, uint16 ReqLength, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    uint8 (*Dcm_01_IOControlCallBackType_p)(const uint8* DataInVar, uint16 ReqLength, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    uint8 (*Dcm_02_IOControlCallBackType_p)(const uint8* DataInVar, uint16 ReqLength, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    uint8 (*Dcm_03_IOControlCallBackType_p)(const uint8* DataInVar, uint16 ReqLength, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16* RespLength, Dcm_NegativeResponseCodeType* ErrorCode);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_2F_ServiceInfoType_st;
typedef struct
{
    const Dcm_2F_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_2F_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */
#if (STD_ON == DCM_SERVICE_31_ENABLED)
enum
{
    DCM_31_SIGNAL_TYPE_FIXED = 0x00U,
    DCM_31_SIGNAL_TYPE_VARIABLE
};

typedef struct
{
    uint16 Dcm_ReqLen;
    uint16 Dcm_ResLen;
} Dcm_ReqResLen_st;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_DspRoutineUsed; 
    uint8 Dcm_FixedLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_StarAutFilter;
    Dcm_AutFilter_st Dcm_StopAutFilter;
    Dcm_AutFilter_st Dcm_ReqResultAutFilter;
    Dcm_ReqResLen_st Dcm_StartLen;
    Dcm_ReqResLen_st Dcm_StopLen;
    Dcm_ReqResLen_st Dcm_ReqResultLen;
    Std_ReturnType  (*Dcm_RouteControl_01_p)(const uint8* DataInVar, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16 CurrentLengthDataInVar, uint16* CurrentLengthDataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Std_ReturnType  (*Dcm_RouteControl_02_p)(const uint8* DataInVar, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16 CurrentLengthDataInVar, uint16* CurrentLengthDataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Std_ReturnType  (*Dcm_RouteControl_03_p)(const uint8* DataInVar, Dcm_OpStatusType OpStatus, uint8* DataOutVar, uint16 CurrentLengthDataInVar, uint16* CurrentLengthDataOutVar, Dcm_NegativeResponseCodeType* ErrorPtr);
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
}Dcm_31_ServiceInfoType_st;

typedef struct
{
    const Dcm_31_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_31_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

#if (STD_ON == DCM_SERVICE_3E_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint8 Dcm_ReqLen;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_3E_ServiceInfoType_st;

typedef struct
{
    const Dcm_3E_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_3E_DispatherInfo_st;
#endif/* STD_ON == DCM_SERVICE_3E_ENABLED */

#if (STD_ON == DCM_SERVICE_85_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_85_ServiceInfoType_st;

typedef struct
{
    const Dcm_85_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_85_DispatherInfo_st;
#endif  /* STD_ON == DCM_SERVICE_85_ENABLED */
#if ( STD_ON == DCM_SERVICE_34_ENABLED )
typedef struct
{
    uint8 Dcm_DataFormatId;
    uint8 Dcm_AddrAndLenFmtId;
    uint32 Dcm_MemoryAddress;
    uint32 Dcm_MemorySize;
    uint8* Dcm_ReqBuffer;
    uint16* Dcm_ReqBufferLen;
} Dcm_34_RepeaterProxyContextType_st;

#endif /* STD_ON == DCM_SERVICE_34_ENABLED */

#if (STD_ON == DCM_SERVICE_35_ENABLED)
typedef struct
{
    uint8 Dcm_DataFormatId;
    uint8 Dcm_AddrAndLenFmtId;
    uint32 Dcm_MemoryAddress;
    uint32 Dcm_MemorySize;
} Dcm_35_RepeaterProxyContextType_st;
#endif /* STD_ON == DCM_SERVICE_35_ENABLED */

typedef struct
{
    uint32 Dcm_MemoryAddress_Low;
    uint32 Dcm_MemoryAddress_High;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_DspMemoryInfoType_st;

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
typedef struct
{
    uint32 Dcm_MemAddr;
    uint32 Dcm_MemSize;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
	Dcm_AutFilter_st Dcm_AutFilter;
} Dcm_2C_DDDid_Info_st;
typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_DDDidMaxElmt;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
	Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_2C_DDDid_Info_st* Dcm_2C_DDDid_Info;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_2C_ServiceInfoType_st;
typedef struct
{
    const uint8* Dcm_SubServiceInfoTable;
    const Dcm_2C_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_2C_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_2A_ENABLED)
typedef struct
{
    uint16 Dcm_LocPduIdx;
    uint16 Dcm_TxPduId;
} Dcm_2A_Channel_st;

typedef struct
{
    uint16 Dcm_ID;
    uint8 Dcm_Used;
    uint16 Dcm_Length;
    Dcm_DataUsedPort_e Dcm_DataUsedPort;
    Dcm_ServiceFilter_st Dcm_ReadFilter;
    Dcm_AutFilter_st Dcm_AutFilter;
    Dcm_DidReadData_st Dcm_DidReadData;
    Dcm_DidReadDataLength Dcm_DidReadDataLength;
    Dcm_DidConditionCheckRead_st Dcm_DidCondCheckRead;
    Dcm_CheckRuleRef_p Dcm_CheckRuleRef;
} Dcm_2A_ServiceInfoType_st;

typedef struct
{
    const Dcm_2A_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_2A_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_2A_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
typedef struct
{
    PduIdType RxPduId;
    PduIdType TxPduId;
    uint32 ClientSrcAddr;
} Dcm_86_DslInfo_st;

typedef struct
{
    uint8 Dcm_EventId;
    uint8 Dcm_EventState; /* EventState: Start, Stop, Clear. */
    uint8 Dcm_EventWndTime;
    uint8 Dcm_StorageStatus;
    uint8 Dcm_EventMask; /* EventType = onDTCStatusChange */
    uint16 Dcm_DidValue; /* EventType = onChangeOfDataIdentifier */
} Dcm_86_InfoData_st;

typedef struct
{
    Dcm_86_DslInfo_st Dcm_DslInfo;
    Dcm_86_InfoData_st Dcm_InfoData[DCM_86_EEP_EVENTNUM];
} Dcm_86_NvMInfo_st;

typedef struct {
	union
	{
		uint8 NvMRamData[DCM_ROE_BLOCKSIZE];
		Dcm_86_NvMInfo_st NvMInfoData;
	}NvmInfo;
}Dcm_86_NvMEventInfo_st;

typedef struct
{
	uint8 Dcm_TransType; /* DcmDslProtocolTransType. */
    uint8 Dcm_Priority;
    PduIdType Dcm_RxPduId;
    PduIdType Dcm_TxPduId;
} Dcm_86_DslProtocol_st;

typedef struct
{
    uint8 Dcm_EventType;
    uint8 Dcm_MsgLength; /* Request message length except the service ID( one byte). */
} Dcm_86_RequestMsg_st;

typedef struct
{
    uint8 Dcm_EventID;
    uint8 Dcm_EventInitStatus;
	uint8 Dcm_DidValid;
    uint16 Dcm_DidValue;
} Dcm_86_ServiceInfoType_st;

typedef struct
{
    const Dcm_86_ServiceInfoType_st* Dcm_ServiceInfoTable;
} Dcm_86_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_87_ENABLED)
typedef struct
{
    uint8 Dcm_ID;
    uint8 Dcm_Phy_FuncAddrFilter;
    uint16 Dcm_ReqDataLength;
    Dcm_ServiceFilter_st Dcm_Filter;
    Dcm_AutFilter_st Dcm_AutFilter;
    void (*Dcm_ServiceProcessorType_p)(void);
    Std_ReturnType  (*Dcm_LinkControl_01_02_03)(Dcm_OpStatusType OpStatus, uint8 ID, uint8 LinkControlModeId, uint32* LinkRecord, Dcm_NegativeResponseCodeType* ErrorCode);
} Dcm_87_ServiceInfoType_st;

typedef struct
{
    const Dcm_87_ServiceInfoType_st *Dcm_ServiceInfoTable;
} Dcm_87_DispatherInfo_st;
#endif /* STD_ON == DCM_SERVICE_87_ENABLED */

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define DCM_START_SEC_VAR_INIT
#include "Dcm_MemMap.h"
extern VAR(uint8, DCM_VAR_INIT) Dcm_DslBufferRx[DCM_DSL_BUFFERLENRX];
extern VAR(Dcm_ReadBlockId_st, DCM_VAR_INIT) Dcm_ReadBlockId[DCM_READ_BLOCK_NUM + 1];
extern VAR(uint32, DCM_VAR_INIT) Dcm_ProgrammingLength;

#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) )
extern VAR(uint16, DCM_VAR_INIT) Dcm_22_DidList[DCM_22_MAX_DID_LIST_NUM];
extern VAR(uint16, DCM_VAR_INIT) Dcm_22_DidResLen[DCM_22_MAX_DID_LIST_NUM];
 
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0120Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0121Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0122Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0123Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0124Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0125Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0126Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0127Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0128Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0129Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did012ABuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did012BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did012CBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did012DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did012EBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did012FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0130Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0131Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0132Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0210Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0212Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0211Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0214Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0215Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0216Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0217Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0218Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0219Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did021ABuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did021BBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did021CBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did021DBuffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did021EBuffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did021FBuffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0220Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0221Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0222Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0223Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0224Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0225Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0226Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0213Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0133Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0134Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0135Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0136Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0137Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0138Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0139Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did013ABuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did013BBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did013CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did013DBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did013EBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did013FBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0140Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0141Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0142Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0143Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0144Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0145Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0146Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0147Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0148Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0149Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did014ABuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did014BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did014CBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did014DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did014EBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did014FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0150Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0151Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0152Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0153Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0154Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0155Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0156Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0157Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0158Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0159Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did015ABuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did015BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did015CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did015DBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did015EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did015FBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0160Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0161Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0162Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0163Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0164Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0165Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0166Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0167Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0168Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0169Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did016ABuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did016BBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did016CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did016DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did016EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did016FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0170Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0171Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0172Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0173Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0174Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0175Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0176Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0177Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0178Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0179Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did017ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did017BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did017CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did017DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did017EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did017FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0180Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0181Buffer[90U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0182Buffer[90U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0185Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did018CBuffer[15U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did018DBuffer[15U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did018EBuffer[15U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did018FBuffer[15U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0190Buffer[15U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0191Buffer[15U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0192Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0193Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0194Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0195Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0196Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0197Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0198Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0199Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF120Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did019ABuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did019BBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did019CBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did019DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did019FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did019EBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A0Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A2Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A4Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A6Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A8Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01A9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01AABuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01ABBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01ACBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01ADBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01AEBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01AFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B0Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B2Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B3Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B4Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B5Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B6Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B7Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B8Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01B9Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01BABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01BBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01BCBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01BDBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01BEBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01BFBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C0Buffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C1Buffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C2Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C3Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C4Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C5Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C6Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C7Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01C9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01CABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01CBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01CCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01CDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01CEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01CFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D4Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D5Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D6Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D8Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01D9Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01DABuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01DBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01DCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01DDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01DEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E0Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01DFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E1Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E3Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E4Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E5Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E6Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E7Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01E9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01EABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01EBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01ECBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01EDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01EEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01EFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01F9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01FABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01FBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01FCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01FDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01FEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did01FFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0250Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0251Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0252Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0253Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0254Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0255Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0256Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0257Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0258Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0259Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did025ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did025BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did025CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did025DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did025EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did025FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0260Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0261Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0262Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0263Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0264Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0265Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0266Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0267Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0268Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0269Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did026ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did026BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did026CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did026DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did026EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did026FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0270Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0271Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0272Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0273Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0274Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0275Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0276Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0277Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0278Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0279Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did027ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did027BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did027CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did027DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did027EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did027FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0280Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0281Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0282Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0283Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0284Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0285Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0286Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0287Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0288Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0289Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did028ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did028BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did028CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did028DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did028EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did028FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0290Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0291Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0292Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0293Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0294Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0295Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0296Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0297Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0298Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0299Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did029ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did029BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did029CBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did029DBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did029EBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did029FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A0Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A1Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02A9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02AABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02ABBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02ACBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02ADBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02AEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02AFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02B9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02BABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02BBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02BCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02BDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02BEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02BFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02C9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02CABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02CBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02CCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02CDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02CEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02CFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02D9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02DABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02DBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02DCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02DDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02DEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02DFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02E9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02EABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02EBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02ECBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02EDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02EEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02EFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02F9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02FABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02FBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02FCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02FDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02FEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did02FFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0300Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0301Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0302Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0303Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0304Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0305Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0306Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0307Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0308Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0309Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did030ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did030BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did030CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did030DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did030EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did030FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0310Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0311Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0312Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0313Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0314Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0315Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0316Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0317Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0318Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0319Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did031ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did031BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did031CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did031DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did031EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did031FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0320Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0321Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0322Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0323Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0324Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0325Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0326Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0327Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0328Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0329Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did032ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did032BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did032CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did032DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did032EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did032FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0330Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0331Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0332Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0333Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0334Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0335Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0336Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0337Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0338Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0339Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did033ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did033BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did033CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did033DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did033EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did033FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0340Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0341Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0342Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0343Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0344Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0345Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0346Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0347Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0348Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0349Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did034ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did034BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did034CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did034DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did034EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did034FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0350Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0351Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0352Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0353Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0354Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0355Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0356Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0357Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0358Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0359Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did035ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did035BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did035CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did035DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did035EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did035FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0360Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0361Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0362Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0363Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0364Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0365Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0366Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0367Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0368Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0369Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did036ABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did036BBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did036CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did036DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did036EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF187Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF15ABuffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF182Buffer[40U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF189Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF18ABuffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF190Buffer[17U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF192Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF193Buffer[8U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF195Buffer[13U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF197Buffer[22U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF1A5Buffer[22U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF1A6Buffer[17U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0201Buffer[48U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0202Buffer[16U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0203Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0204Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0205Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0206Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0207Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0208Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_Did0209Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF400Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF401Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF402Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF404Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF405Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF40BBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF40CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF40DBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF40FBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF410Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF411Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF41CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF41EBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF41FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF420Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF421Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF423Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF42CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF42DBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF42FBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF430Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF431Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF432Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF433Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF43CBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF43DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF43EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF43FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF440Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF441Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF442Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF444Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF445Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF446Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF449Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF44ABuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF44CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF44DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF44EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF44FBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF450Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF459Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF45ABuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF45CBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF45DBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF45EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF460Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF461Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF462Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF463Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF464Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF465Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF466Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF467Buffer[3U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF468Buffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF469Buffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF46BBuffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF46CBuffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF46DBuffer[11U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF46EBuffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF46FBuffer[3U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF470Buffer[10U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF471Buffer[6U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF472Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF473Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF474Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF475Buffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF476Buffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF477Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF478Buffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF47ABuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF47BBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF47CBuffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF47DBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF47EBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF47FBuffer[13U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF480Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF481Buffer[41U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF482Buffer[41U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF483Buffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF485Buffer[10U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF486Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF487Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF488Buffer[13U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF489Buffer[41U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF48BBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF48CBuffer[17U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF48EBuffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF48FBuffer[7U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF490Buffer[3U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF491Buffer[5U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF492Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF493Buffer[3U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF494Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF498Buffer[9U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF49DBuffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF49EBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF49FBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A0Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A6Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4AABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ABBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ACBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ADBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4AEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4AFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DCBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E8Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E9Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EABuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EBBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ECBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EDBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EEBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EFBuffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F0Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F1Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F2Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F3Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F4Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F5Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F6Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F7Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4FFBuffer[10U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C0Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E0Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF800Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF802Buffer[17U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF804Buffer[16U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF806Buffer[4U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF80ABuffer[20U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF80BBuffer[36U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF80DBuffer[17U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF810Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF811Buffer[11U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF812Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF813Buffer[12U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF814Buffer[2U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF815Buffer[1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF816Buffer[32U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF817Buffer[16U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF818Buffer[16U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF819Buffer[24U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF81ABuffer[24U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF81BBuffer[16U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF81CBuffer[24U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF81DBuffer[32U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_DidF15BBuffer[40U];
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) */

#if ( STD_ON == DCM_SERVICE_11_ENABLED )
extern VAR(uint8, DCM_VAR_INIT) Dcm_11_NvMBuf[4];
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */

#if (STD_ON == DCM_SERVICE_27_ENABLED)
extern VAR(uint32, DCM_VAR_INIT) Dcm_27_TimerEngine[DCM_27_SUB_NUM + 1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_security_key[DCM_27_MAX_SEED_LENGTH + 1U];
extern VAR(uint8, DCM_VAR_INIT) Dcm_security_seed[DCM_27_MAX_SEED_LENGTH + 1U];
extern VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_Data[DCM_27_SUB_NUM + 1U];
extern VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_INIT_Data[DCM_27_SUB_NUM + 1U];
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
extern VAR(uint8, DCM_VAR_INIT) Dcm_AuthenticationState[DCM_29_AUT_ROLE_NUM + 1U][DCM_29_AUT_CONN_NUM + 1U];
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)

extern VAR(Dcm_86_NvMEventInfo_st, DCM_VAR_INIT) Dcm_86_NvMInfo;
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

#define DCM_STOP_SEC_VAR_INIT
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONFIG_DATA
#include "Dcm_MemMap.h"
#if (STD_ON == DCM_SERVICE_29_ENABLED)
extern CONST(Dcm_29_AutConn_st, DCM_CONFIG_DATA) Dcm_29_AutConn[DCM_29_AUT_CONN_NUM + 1U];
extern CONST(Dcm_29_AutTransCert_st, DCM_CONFIG_DATA) Dcm_29_AutTransCert[DCM_29_AUT_TRANSCERT_NUM + 1U];
extern CONST(Dcm_29_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_29_ServiceInfo[DCM_29_SUBID_NUM + 1U];
extern CONST(Dcm_29_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_29_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
extern CONST(Dcm_38_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_38_ServiceInfo[DCM_38_SUBID_NUM + 1];
extern CONST(Dcm_38_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_38_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#if ( STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED )
extern CONST(Dcm_ServiceRequestManufacturerNotification_st, DCM_CONFIG_DATA) Dcm_ServiceRequestManufacturerNotification;
#endif /* STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED */

#if ( STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED )
extern CONST(Dcm_ServiceRequestSupplierNotification_st, DCM_CONFIG_DATA) Dcm_ServiceRequestSupplierNotification;
#endif /* STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED */

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
extern CONST(Dcm_ServiceTableType_st, DCM_CONFIG_DATA) Dcm_DspServiceInfoTable[DCM_NUM_SERVICES + 1];
extern CONST(Dcm_DslBufferType, DCM_CONFIG_DATA) Dcm_DslBuffer[DCM_DSL_BUFFERNUM + 1];
extern CONST(Dcm_DslProtocol_st, DCM_CONFIG_DATA) Dcm_DslProtocol[DCM_DSL_PROTOCOL_NUM + 1];
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_CfgNetConnComMChannelMap[DCM_DSL_CHANNEL_NUM + 1];
extern CONST(Dcm_DSDInfo_st, DCM_CONFIG_DATA) Dcm_gcaDSDInfo;

#if ( STD_ON == DCM_SERVICE_01_ENABLED )
extern CONST(Dcm_01_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_01_PIDInfo[DCM_01_SUBID + 1U];
extern CONST(Dcm_01_PidType_st, DCM_CONFIG_DATA) Dcm_01_SupportPID[DCM_01_SUPPRORTPID + 1U];
extern CONST(Dcm_01_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_01_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
extern CONST(Dcm_02_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_02_PIDInfo[DCM_02_SUBID + 1U];
extern CONST(Dcm_02_PidType_st, DCM_CONFIG_DATA) Dcm_02_SupportPID[DCM_02_SUPPRORTPID + 1U];
extern CONST(Dcm_02_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_02_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
extern CONST(Dcm_09_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_09_PIDInfo[DCM_09_SUBID + 1U];
extern CONST(Dcm_09_PidType_st, DCM_CONFIG_DATA) Dcm_09_SupportPID[DCM_09_SUPPRORTPID + 1U];
extern CONST(Dcm_09_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_09_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

#if ( STD_ON == DCM_SERVICE_10_ENABLED )
extern CONST(Dcm_10_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_10_ServiceInfo[DCM_10_SUBID + 1U];
extern CONST(Dcm_10_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_10_Dispatcher;

#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

#if ( STD_ON == DCM_SERVICE_11_ENABLED )
extern CONST(Dcm_11_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_11_ServiceInfo[DCM_11_SUBID + 1U];
extern CONST(Dcm_11_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_11_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */

#if ( STD_ON == DCM_SERVICE_14_ENABLED )
extern CONST(Dcm_14_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_14_ServiceInfo[DCM_14_SUBID_NUM + 1U];
extern CONST(Dcm_g14DispatherInfo_st, DCM_CONFIG_DATA) Dcm_14_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_14_ENABLED */

#if ( STD_ON == DCM_SERVICE_19_ENABLED )
extern CONST(Dcm_19_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_19_ServiceInfo[DCM_19_SUBIDNUM + 1U];
extern CONST(Dcm_19_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_19_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_19_ENABLED */

#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) )
extern CONST(Dcm_22_2E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_22_2E_ServiceInfo[DCM_NUM_DIDS + 1U];
extern CONST(Dcm_22_2E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_22_2E_Dispatcher;
#endif /* (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) */

#if (STD_ON == DCM_SERVICE_27_ENABLED)
extern CONST(Dcm_27_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_27_ServiceInfo[DCM_27_SUB_NUM + 1U];
extern CONST(Dcm_27_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_27_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

#if (STD_ON == DCM_SERVICE_28_ENABLED)
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ChannelId[DCM_28_CHANNLE_NUM + 1U];
extern CONST(Dcm_28_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_28_ServiceInfoTable[DCM_28_SUBID_NUM + 1U];
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ControlState[DCM_28_CONTROL_STATE_NUM];
extern CONST(Dcm_28_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_28_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_28_ENABLED */

#if (STD_ON == DCM_SERVICE_2F_ENABLED)
extern CONST(Dcm_2F_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2F_ServiceInfo[DCM_2F_MAX_SUB_DID_NUM + 1U];
extern CONST(Dcm_2F_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2F_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */

#if (STD_ON == DCM_SERVICE_31_ENABLED)
extern CONST(Dcm_31_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_31_ServiceInfo[DCM_31_SUBID_NUM + 1U];
extern CONST(Dcm_31_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_31_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

#if (STD_ON == DCM_SERVICE_3E_ENABLED)
extern CONST(Dcm_3E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_3E_ServiceInfo[DCM_3E_SUBID + 1U];
extern CONST(Dcm_3E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_3E_Dispatcher;
#endif/* STD_ON == DCM_SERVICE_3E_ENABLED */

#if ( STD_ON == DCM_SERVICE_85_ENABLED )
extern CONST(Dcm_85_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_85_ServiceInfo[DCM_85_SUBID_NUM + 1U];
extern CONST(Dcm_85_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_85_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_85_ENABLED */

#if (STD_ON == DCM_SERVICE_87_ENABLED)
extern CONST(Dcm_87_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_87_ServiceInfo[DCM_87_SUBID_NUM + 1U];
extern CONST(Dcm_87_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_87_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_87_ENABLED */

extern CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspReadMemoryInfo[DCM_DSP_READMEMORY_NUM + 1U];
extern CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspWriteMemoryInfo[DCM_DSP_WRITEMEMORY_NUM + 1U];

#if (STD_ON == DCM_SERVICE_2A_ENABLED)
extern CONST(Dcm_2A_Channel_st, DCM_CONFIG_DATA) Dcm_2A_Channel[DCM_2A_TX_CHANNEL_NUM + 1U];
extern CONST(uint16, DCM_CONFIG_DATA) Dcm_2A_TransmissionRate[DCM_2A_TRANSMODE_SIZE + 1U];
extern CONST(Dcm_2A_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2A_ServiceInfo[DCM_2A_NUM_DIDS + 1U];
extern CONST(Dcm_2A_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2A_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_2A_ENABLED */

#if (STD_ON == DCM_SERVICE_2C_ENABLED)
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_2C_SubFunc[DCM_2C_SUB_NUM_DIDS];
extern CONST(Dcm_2C_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2C_ServiceInfo[DCM_2C_NUM_DIDS + 1U];
extern CONST(Dcm_2C_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2C_Dispatcher;


#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
extern CONST(Dcm_86_DslProtocol_st, DCM_CONFIG_DATA) Dcm_86_DslProtocol[DCM_86_ROE_DSL_NUM + 1U];
extern CONST(Dcm_86_RequestMsg_st, DCM_CONFIG_DATA) Dcm_86_RequestMsg[DCM_86_EVENTTYPE_NUM];
extern CONST(uint8, DCM_CONFIG_DATA) Dcm_86_WindowTime[DCM_86_EVENTWINDOWTIME_NUM + 1U];
extern CONST(Dcm_86_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_86_ServiceInfo[DCM_86_EVENT_NUM + 1U];
extern CONST(Dcm_86_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_86_Dispatcher;
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */



#define DCM_STOP_SEC_CONFIG_DATA
#include "Dcm_MemMap.h"
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if ( (STD_ON == DCM_SERVICE_10_ENABLED) || (STD_ON == DCM_SERVICE_28_ENABLED) )
extern FUNC(void, DCM_CODE) Dcm_ControlCommunication(uint8 subfunc, uint8 comtype);
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif /* DCM_LCFG_H_ */

