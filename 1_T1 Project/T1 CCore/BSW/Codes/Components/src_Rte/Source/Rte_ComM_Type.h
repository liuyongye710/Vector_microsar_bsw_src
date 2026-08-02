/*
********************************************************************************
*
* File name: Rte_ComM_Type.h
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
#ifndef RTE_COMM_TYPE_H_
#define RTE_COMM_TYPE_H_

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
#ifndef COMM_NO_COMMUNICATION
#define COMM_NO_COMMUNICATION        (0U)
#endif

#ifndef COMM_SILENT_COMMUNICATION
#define COMM_SILENT_COMMUNICATION    (1U)
#endif

#ifndef COMM_FULL_COMMUNICATION
#define COMM_FULL_COMMUNICATION      (2U)
#endif

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
#ifndef Rte_TypeDef_ComM_UserHandleType
#define Rte_TypeDef_ComM_UserHandleType
typedef uint8 ComM_UserHandleType;
#endif

#ifndef Rte_TypeDef_ComM_ModeType
#define Rte_TypeDef_ComM_ModeType
typedef uint8 ComM_ModeType;
#endif

#ifndef Rte_TypeDef_ComM_InhibitionStatusType
#define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;
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

#endif /* RTE_COMM_TYPE_H_ */
