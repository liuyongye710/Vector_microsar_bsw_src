/*
********************************************************************************
*
* File name: Rte_NvM_Type.h
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
* Version: 3.1
* Author/Date : LiDY/2023.03.08
* Change: Add Variable about NvM.
* Cause: New
********************************************************************************
*/
#ifndef RTE_NVM_TYPE_H_
#define RTE_NVM_TYPE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* Identification of a NVRAM block via a unique block identifier. */
#ifndef Rte_TypeDef_NvM_BlockIdType
#define Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;
#endif

/* The type NvM_RequestResultType is an asynchronous request result, which will
be returned by the API service NvM_GetErrorStatus*/
#ifndef Rte_TypeDef_NvM_RequestResultType
#define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;
#endif

/* Configuration data structure of the NvM module. */
#ifndef Rte_TypeDef_NvM_ConfigType
#define Rte_TypeDef_NvM_ConfigType
typedef struct
{
    uint8 reserve;
} NvM_ConfigType;
#endif

/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
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

#endif /* RTE_H_ */
