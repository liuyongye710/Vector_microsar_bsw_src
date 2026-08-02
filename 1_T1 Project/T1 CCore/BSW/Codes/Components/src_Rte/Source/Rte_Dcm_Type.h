/*
********************************************************************************
*
* File name: Rte_Dcm_Type.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangJP/2021.11.11
* Change: New created.
* Cause: New
********************************************************************************
*/

/*
********************************************************************************
*    double include preventio and include files
********************************************************************************
*/
#ifndef _RTE_DCM_TYPE_H
#define _RTE_DCM_TYPE_H

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
#ifndef Rte_TypeDef_Dcm_38_ServiceInfoType_Req
#define Rte_TypeDef_Dcm_38_ServiceInfoType_Req
typedef struct{
    uint64 fileSizeUnCompressed;
    uint64 fileSizeCompressed;
    uint8 *filePathAndName;
    uint16 filePathAndNameLength;
    uint8 modeOfOperation;
    uint8 dataFormatIdentifier;
    uint8 fileSizeParameterLength;
}Dcm_38_ServiceInfoType_Req;
#endif

#ifndef Rte_TypeDef_Dcm_38_ServiceInfoType_Res
#define Rte_TypeDef_Dcm_38_ServiceInfoType_Res
typedef struct{
    uint8 md5Value[16];
    uint8 filePosition[8];
}Dcm_38_ServiceInfoType_Res;
#endif

#ifndef Rte_TypeDef_Dcm_OpStatusType
#define Rte_TypeDef_Dcm_OpStatusType
typedef uint8 Dcm_OpStatusType;
#endif

#ifndef Rte_TypeDef_Dcm_ProtocolType
#define Rte_TypeDef_Dcm_ProtocolType
typedef uint8 Dcm_ProtocolType;
#endif

#ifndef Rte_TypeDef_Dcm_SecLevelType
#define Rte_TypeDef_Dcm_SecLevelType
typedef uint8 Dcm_SecLevelType;
#endif

#ifndef Rte_TypeDef_Dcm_SesCtrlType
#define Rte_TypeDef_Dcm_SesCtrlType
typedef uint8 Dcm_SesCtrlType;
#endif

#ifndef Rte_TypeDef_DcmEcuReset
#define Rte_TypeDef_DcmEcuReset
typedef enum
{
    DCM_NONE,
    DCM_HARD,
    DCM_KEYONOFF,
    DCM_SOFT,
    DCM_JUMPTOBOOTLOADER,
    DCM_JUMPTOSYSSUPPLIERBOOTLOADER,
    DCM_EXECUTE,
} DcmEcuReset;
#endif

/*
********************************************************************************
*    Range, Invalidation, Enumeration and Bit Field Definitions
********************************************************************************
*/


/*
********************************************************************************
*    Definitions for Mode Management
********************************************************************************
*/

#endif
