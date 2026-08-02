/*
********************************************************************************
*
* File name: Rte_Dem_Type.h
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
#ifndef RTE_DEM_TYPE_H_
#define RTE_DEM_TYPE_H_

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
#ifndef Rte_TypeDef_Dem_OperationCycleStateType
#define Rte_TypeDef_Dem_OperationCycleStateType 
typedef uint8 Dem_OperationCycleStateType;
#endif

#ifndef Rte_TypeDef_Dem_PID21valueType
#define Rte_TypeDef_Dem_PID21valueType 
typedef uint8 Dem_PID21valueType;
#endif

#ifndef Rte_TypeDef_Dem_PID31valuetype
#define Rte_TypeDef_Dem_PID31valuetype 
typedef uint8 Dem_PID31valuetype;
#endif

#ifndef Rte_TypeDef_Dem_MaxDataValueType
#define Rte_TypeDef_Dem_MaxDataValueType 
typedef uint8 Dem_MaxDataValueType;
#endif

#ifndef Rte_TypeDef_Dem_DTCFormatType
#define Rte_TypeDef_Dem_DTCFormatType
typedef uint8 Dem_DTCFormatType;
#endif

#ifndef Rte_TypeDef_Dem_DTCOriginType
#define Rte_TypeDef_Dem_DTCOriginType
typedef uint8 Dem_DTCOriginType;
#endif

#ifndef Rte_TypeDef_Dem_ComponentIdType
#define Rte_TypeDef_Dem_ComponentIdType
typedef uint16 Dem_ComponentIdType;
#endif

#ifndef Rte_TypeDef_Dem_EventIdType
#define Rte_TypeDef_Dem_EventIdType
typedef uint16 Dem_EventIdType;
#endif

#ifndef Rte_TypeDef_Dem_DebouncingStateType
#define Rte_TypeDef_Dem_DebouncingStateType
typedef uint8 Dem_DebouncingStateType;
#endif

#ifndef Rte_TypeDef_Dem_IndicatorStatusType
#define Rte_TypeDef_Dem_IndicatorStatusType
typedef uint8 Dem_IndicatorStatusType;
#endif

#ifndef Rte_TypeDef_Dem_DebounceResetStatusType
#define Rte_TypeDef_Dem_DebounceResetStatusType
typedef uint8 Dem_DebounceResetStatusType;
#endif

#ifndef Rte_TypeDef_Dem_EventStatusType
#define Rte_TypeDef_Dem_EventStatusType
typedef uint8 Dem_EventStatusType;
#endif

#ifndef Rte_TypeDef_Dem_DTRControlType
#define Rte_TypeDef_Dem_DTRControlType
typedef uint8 Dem_DTRControlType;
#endif

#ifndef Rte_TypeDef_Dem_RatioIdType
#define Rte_TypeDef_Dem_RatioIdType
typedef uint16 Dem_RatioIdType;
#endif

#ifndef Rte_TypeDef_Dem_IumprDenomCondIdType
#define Rte_TypeDef_Dem_IumprDenomCondIdType
typedef uint8 Dem_IumprDenomCondIdType;
#endif

#ifndef Rte_TypeDef_Dem_IumprDenomCondStatusType
#define Rte_TypeDef_Dem_IumprDenomCondStatusType
typedef uint8 Dem_IumprDenomCondStatusType;
#endif

#ifndef Rte_TypeDef_Dem_UdsStatusByteType
#define Rte_TypeDef_Dem_UdsStatusByteType
typedef uint8 Dem_UdsStatusByteType;
#endif

#ifndef Rte_TypeDef_Dem_DTCKindType
#define Rte_TypeDef_Dem_DTCKindType
typedef uint8 Dem_DTCKindType;
#endif

typedef uint8 Dem_ReturnControlDTCSettingType;

typedef uint8 Dem_ReturnClearDTCType;

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

#endif /* RTE_DEM_TYPE_H_ */

