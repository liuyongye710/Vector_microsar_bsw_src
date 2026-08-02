/*
********************************************************************************
*
* File name: Rte_Type.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: Gaol/2022.6.14
* Change: New created.
* Cause: New
********************************************************************************
*/
#ifndef RTE_TYPE_H_
#define RTE_TYPE_H_
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os.h"
#include "Rte.h"
#include "ComStack_Cfg.h" 
#include "ComStack_Types.h"
#include "Rte_Compiler_Cfg.h"
#include "Rte_BswM_Type.h"
#include "Rte_ComM_Type.h"
#include "Rte_Csm_Type.h"
#include "Rte_Dcm_Type.h"
#include "Rte_Dem_Type.h"
#include "Rte_Det_Type.h"
#include "Rte_Dlt_Type.h"
#include "Rte_EcuM_Type.h"
#include "Rte_FiM_Type.h"
#include "Rte_KeyM_Type.h"
#include "Rte_NvM_Type.h"
#include "Rte_Sd_Type.h"
#include "Rte_SecOC_Type.h"
#include "Rte_StbM_Type.h"
#include "Rte_WdgM_Type.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define RTE_CALL_STACK_LENGTH_SYNC            (4U)
#define RTE_CALL_STACK_LENGTH_ASYNC           (1U)

#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
#define RTE_CORE_STATE_UNINIT                 (0U)
#define RTE_CORE_STATE_SCHM_INIT              (1U)
#define RTE_CORE_STATE_INIT                   (2U)
#define RTE_CORE_NO_USE                       (0U)
#define RTE_CORE_IN_USE                       (1U)
#define RTE_CORE_NOT_INIT_OK                  (0U)
#define RTE_CORE_ALL_INIT_OK                  (1U)
#define RTE_CORE_COUNT                        (3U)
#define RTE_CORE_MASTER_ID                    (2U)
#endif

/*
********************************************************************************
*    Data type definitions include custom array struct
********************************************************************************
*/
#define RTE_COM_SENDSIGNALPROXY_NOCHANGE       (0U)
#define RTE_COM_SENDSIGNALPROXY_SEND           (1U)
#define RTE_COM_SENDSIGNALPROXY_INVALIDATE     (2U)

#ifndef Rte_TypeDef_dtRef_VOID
#define Rte_TypeDef_dtRef_VOID
typedef void * dtRef_VOID;
#endif

#ifndef Rte_TypeDef_dtRef_const_VOID
#define Rte_TypeDef_dtRef_const_VOID
typedef const void * dtRef_const_VOID;
#endif


#ifndef Rte_TypeDef_Rte_Cs_TransactionHandleType
#define Rte_TypeDef_Rte_Cs_TransactionHandleType
typedef struct
{
    uint16 clientId;
    uint16 sequenceCounter;
} Rte_Cs_TransactionHandleType;
#endif

#ifndef Rte_TypeDef_Rte_ClientIdType
#define Rte_TypeDef_Rte_ClientIdType
typedef struct
{
    uint8 clientId;
    uint8 subClientId;
}Rte_ClientIdType;
#endif

#ifndef Rte_TypeDef_Rte_CS_Server_Property_Type
#define Rte_TypeDef_Rte_CS_Server_Property_Type
typedef struct
{
    boolean Rte_ServerCompleted;
    boolean Rte_Call_Busy;
} Rte_CS_Server_Property_Type;
#endif


/*
********************************************************************************
*    Signal Grounp User Types
********************************************************************************
*/
/*
********************************************************************************
*    RTE and BSW User Types
********************************************************************************
*/
#ifndef Rte_TypeDef_RteQueueBufferType
#define Rte_TypeDef_RteQueueBufferType
typedef struct
{
    uint32 maxCnt;      /* The max number of elements in the list */
    uint32 currCnt;     /* Current number of elements in the list */
    uint32 dataSize;    /* Size of the elements in the list */
    void *head;         /* Head of the elements in the list */
    void *tail;         /* Tail of the elements in the list */
    void *bufStart;     /* Start of buffer */
    void *bufEnd;       /* End of buffer */
} RteQueueBufferType;
#endif

#ifndef Rte_TypeDef_RteStackBufferType
#define Rte_TypeDef_RteStackBufferType
typedef struct
{
    uint32 maxCnt;      /* The max number of elements in the list */
    uint32 currCnt;     /* Current number of elements in the list */
    uint32 dataSize;    /* Size of the elements in the list */
    void *top;          /* Top of the elements in the list */
    void *bufStart;     /* Start of buffer */
    void *bufEnd;       /* End of buffer */
} RteStackBufferType;
#endif

#ifndef Rte_TypeDef_ComM_InhibitionStatusType
#define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;
#endif

#ifndef Rte_TypeDef_Rte_BitType
#define Rte_TypeDef_Rte_BitType
typedef unsigned int Rte_BitType;
#endif

#ifndef Rte_TypeDef_NvM_RequestResultType
#define Rte_TypeDef_NvM_RequestResultType 
typedef uint8 NvM_RequestResultType;
#endif

#ifndef Rte_TypeDef_Dem_OperationCycleStateType
#define Rte_TypeDef_Dem_OperationCycleStateType 
typedef uint8 Dem_OperationCycleStateType;
#endif

typedef struct
{
    Rte_BitType Rte_ComCbk_RxNeverReceived;
    Rte_BitType Rte_ComCbk_RxUpdate : 1;
    Rte_BitType Rte_ComCbk_RxUpdate_Sender : 1;
    Rte_BitType Rte_ComCbk_RxInvalid;
    Rte_BitType Rte_ComCbk_RxTimeout;
}Rte_ComCbk_Struct;



#define RTE_TRANSFORMER_UNSPECIFIED   0x00U
#define RTE_TRANSFORMER_SERIALIZER    0x01U
#define RTE_TRANSFORMER_SAFETY        0x02U
#define RTE_TRANSFORMER_SECURITY      0x03U
#define RTE_TRANSFORMER_CUSTOM        0xFFU

#ifndef Rte_TypeDef_Rte_TransformerErrorCode
#define Rte_TypeDef_Rte_TransformerErrorCode
typedef uint8 Rte_TransformerErrorCode;
#endif

#ifndef Rte_TypeDef_Rte_TransformerClass
#define Rte_TypeDef_Rte_TransformerClass
typedef uint8 Rte_TransformerClass;
#endif

#ifndef Rte_TypeDef_Rte_TransformerError
#define Rte_TypeDef_Rte_TransformerError
typedef struct 
{
    Rte_TransformerErrorCode errorCode;
    Rte_TransformerClass transformerClass;
 } Rte_TransformerError;
#endif

#ifndef Rte_TypeDef_Rte_LdComTpFlagType
#define Rte_TypeDef_Rte_LdComTpFlagType
typedef struct 
{
    boolean isLocked;
    uint32 iBufferLength;
    uint32 iUsedLength;
    uint8 iTransformationStatus;
} Rte_LdComTpFlagType;
#endif

/*
********************************************************************************
*    Memory Block User Types
********************************************************************************
*/

/* 
******************************************************************************** 
*    Data type definitions of Tx Confirmation Flag 
******************************************************************************** 
*/

/*
********************************************************************************
*    DataType definitions for implicit access to S/R port elements
********************************************************************************
*/

/*
********************************************************************************
*    extern Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
********************************************************************************
*/

/*
********************************************************************************
*    extern declaration of Calibration component and SW-C local calibration parameters
********************************************************************************
*/

/*
********************************************************************************
*    extern declaration Rte_Pim (Per-Instance Memory)
********************************************************************************
*/

/*
********************************************************************************
*    extern declarations of RTE internal variables
********************************************************************************
*/

/*
********************************************************************************
*    extern declarations of RTE PRPort variables
********************************************************************************
*/

/*
********************************************************************************
*    Data type definitions of Update Flag
********************************************************************************
*/

/*
********************************************************************************
*    Data type definitions of Timeout Flag
********************************************************************************
*/

/*
********************************************************************************
*    Data type definitions of Invalid Flag
********************************************************************************
*/

/*
********************************************************************************
*    Data type definitions of Never Receive Flag
********************************************************************************
*/

/* 
******************************************************************************** 
*    extern declaration of Buffer for Tx Confirmation Flag 
******************************************************************************** 
*/
/*
********************************************************************************
*    extern declaration of Buffer for IOC and TxUpdate variables
********************************************************************************
*/

/*
********************************************************************************
*    extern declaration of Buffer for Invalid variables
********************************************************************************
*/

/*
********************************************************************************
*    extern declaration of Buffer for Com Call Back variables
********************************************************************************
*/

/*
********************************************************************************
*    extern declaration of Buffer for inter-runnable variables
********************************************************************************
*/

/*
********************************************************************************
*    extern declarations of RTE implicit variables
********************************************************************************
*/

/*
********************************************************************************
*    extern Rte.c global variables
********************************************************************************
*/
#if(STD_ON == RTE_MULTI_CORE_SYNC_ENABLE)
#define RTE_START_SEC_VAR_INIT
#include "Rte_MemMap.h"
extern VAR(uint8, RTE_VAR_INIT) Rte_CoreState[RTE_CORE_COUNT];
#define RTE_STOP_SEC_VAR_INIT
#include "Rte_MemMap.h"

#define RTE_START_SEC_CONST
#include "Rte_MemMap.h"
extern CONST(uint8, RTE_CONST) Rte_CoreInUseState[RTE_CORE_COUNT];
#define RTE_STOP_SEC_CONST
#include "Rte_MemMap.h"

#endif

#endif /* RTE_TYPE_H_ */
