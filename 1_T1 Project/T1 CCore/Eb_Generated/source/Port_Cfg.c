/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
*   Project              : AUTOSAR 4.4.0 MCAL
*   Platform             : PowerPC e200
*   Peripheral           : PORT
*   Dependencies         : -
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : 
*   Autosar Conf.Variant :
*   SW Version           : 
*   Build Version        : 
*  
*****************************************************************************/
/**
* @file    Port_PBcfg.c
* @implements Port_PBcfg.c_Artifact
*
* @version 3.0.0
* @brief   AUTOSAR Port - PORT driver configuration.
* @details This file contains the PORT driver postbuild configuration.
*
* @addtogroup  Port
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif
/* PRQA S 2053,0380,1258,1259,0704,1533 EOF */
/*==============================================INCLUDE FILES=======================================*/
#include "Port.h"
#include "CCFC3007PT_features.h"
    

/*=====================================SOURCE FILE VERSION INFORMATION==============================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
* @details The integration of incompatible files shall be avoided.
*
*/
#define PORT_C_VENDOR_ID_PBCFG                       176
/*
* @violates @ref PORT_PBCFG_REF_3 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_C_AR_RELEASE_MAJOR_VERSION_PBCFG        4
/*
* @violates @ref PORT_PBCFG_REF_3 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_C_AR_RELEASE_MINOR_VERSION_PBCFG        4

/** @violates @ref PORT_PBCFG_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*   ensure that 31 character significance and case sensitivity are supported for external
*   identifiers.
*/
#define PORT_C_AR_RELEASE_REVISION_VERSION_PBCFG     0
#define PORT_C_SW_MAJOR_VERSION_PBCFG                3
#define PORT_C_SW_MINOR_VERSION_PBCFG                0
#define PORT_C_SW_PATCH_VERSION_PBCFG                0

/*============================================FILE VERSION CHECKS===================================*/

/* Check if Port_PBcfg.c and Port.h are of the same vendor */
#if (PORT_C_VENDOR_ID_PBCFG != PORT_VENDOR_ID)
    #error "NON-MATCHED DATA : PORT_VENDOR_ID"
#endif
/* Check if Port_PBcfg.c and Port.h are of the same Autosar version */
#if (PORT_C_AR_RELEASE_MAJOR_VERSION_PBCFG    != PORT_AR_RELEASE_MAJOR_VERSION) 
    #error "NON-MATCHED DATA : PORT_AR_RELEASE_MAJOR_VERSION"
#endif

#if (PORT_C_AR_RELEASE_MINOR_VERSION_PBCFG    != PORT_AR_RELEASE_MINOR_VERSION) 
    #error "NON-MATCHED DATA : PORT_AR_RELEASE_MINOR_VERSION"
#endif

#if (PORT_C_AR_RELEASE_REVISION_VERSION_PBCFG != PORT_AR_RELEASE_REV_VERSION) 
    #error "NON-MATCHED DATA : PORT_AR_RELEASE_REV_VERSION"
#endif

/* Check if Port_PBcfg.c and Port.h are of the same software version */
#if (PORT_C_SW_MAJOR_VERSION_PBCFG != PORT_SW_MAJOR_VERSION)
    #error "NON-MATCHED DATA : PORT_SW_MAJOR_VERSION"
#endif

#if (PORT_C_SW_MINOR_VERSION_PBCFG != PORT_SW_MINOR_VERSION)
    #error "NON-MATCHED DATA : PORT_SW_MINOR_VERSION"
#endif

#if (PORT_C_SW_PATCH_VERSION_PBCFG != PORT_SW_PATCH_VERSION)
    #error "NON-MATCHED DATA : PORT_SW_PATCH_VERSION"
#endif

/*=========================LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)===============================*/


/*======================================LOCAL MACROS================================================*/


/*======================================LOCAL CONSTANTS=============================================*/


/*======================================LOCAL VARIABLES=============================================*/


/*======================================GLOBAL CONSTANTS============================================*/
#define PORT_START_SEC_CONFIG_DATA

#include "Port_MemMap.h"
static CONST(Port_CoreMapItemType, PORT_CONST) Port_CoreMap[PORT_MAX_CONFIGURED_PADS_U16];
#define PORT_STOP_SEC_CONFIG_DATA

#include "Port_MemMap.h"

/*
* @violates @ref PORT_PBCFG_REF_2 Violates MISRA 2004 Required Rules 10.1,Implicit conversion changes signedness.
*/
#if (PORT_MAX_UNUSED_PADS_U16 != 0U)
/**
* @brief NoDefaultPadsArray is an array containing Unimplemented pads and User pads
* @violates @ref PORT_PBCFG_REF_4 The compiler/linker shall be checked to ensure that 31 character

*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(uint16, PORT_CONST) Port_au16NoUnUsedPadsArrayDefault[PORT_MAX_UNUSED_PADS_U16]=
{
    (uint16)8,
    (uint16)9,
    (uint16)12,
    (uint16)22,
    (uint16)23,
    (uint16)24,
    (uint16)26,
    (uint16)31,
    (uint16)32,
    (uint16)34,
    (uint16)35,
    (uint16)36,
    (uint16)40,
    (uint16)41,
    (uint16)42,
    (uint16)45,
    (uint16)67,
    (uint16)79,
    (uint16)81,
    (uint16)89,
    (uint16)90,
    (uint16)92,
    (uint16)97,
    (uint16)98,
    (uint16)99,
    (uint16)100,
    (uint16)101,
    (uint16)102,
    (uint16)110,
    (uint16)112,
    (uint16)117,
    (uint16)120,
    (uint16)121,
    (uint16)131,
    (uint16)133,
    (uint16)138,
    (uint16)141,
    (uint16)142,
    (uint16)143,
    (uint16)156,
    (uint16)158,
    (uint16)161,
    (uint16)162,
    (uint16)165,
    (uint16)167,
    (uint16)168,
    (uint16)169,
    (uint16)170,
    (uint16)171,
    (uint16)172,
    (uint16)173,
    (uint16)174,
    (uint16)175,
    (uint16)176,
    (uint16)178,
    (uint16)180,
    (uint16)181,
    (uint16)182,
    (uint16)185,
    (uint16)206,
    (uint16)207,
    (uint16)208,
    (uint16)210,
    (uint16)213,
    (uint16)216,
    (uint16)223,
    (uint16)240,
    (uint16)241,
    (uint16)242,
    (uint16)247,
    (uint16)248,
    (uint16)251,
    (uint16)252,
    (uint16)254,
    (uint16)255,
    (uint16)256,
    (uint16)258,
    (uint16)259,
    (uint16)260,
    (uint16)261,
    (uint16)262,
    (uint16)263,
    (uint16)264,
    (uint16)265,
    (uint16)266,
    (uint16)267,
    (uint16)268,
    (uint16)269,
    (uint16)270,
    (uint16)271,
    (uint16)272,
    (uint16)273,
    (uint16)274,
    (uint16)275,
    (uint16)276,
    (uint16)277,
    (uint16)278,
    (uint16)279,
    (uint16)280,
    (uint16)281,
    (uint16)282,
    (uint16)283,
    (uint16)284,
    (uint16)285,
    (uint16)286,
    (uint16)287,
    (uint16)288,
    (uint16)291,
    (uint16)318,
    (uint16)319,
    (uint16)320,
    (uint16)321,
    (uint16)322,
    (uint16)323,
    (uint16)324,
    (uint16)325,
    (uint16)326,
    (uint16)327,
    (uint16)328,
    (uint16)329,
    (uint16)330,
    (uint16)331,
    (uint16)332,
    (uint16)333,
    (uint16)338,
    (uint16)339,
    (uint16)340
};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
#endif
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(uint8, PORT_CONST) u8Port_Etpu_Input_Select[6]={
    0,
    0,
    0,
    0,
    0,
    0,
};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"

/**
 * @brief Default Configuration for Pins not initialized
*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(Port_Siul2_UnUsedPinConfigType, PORT_CONST) Port_UnUsedPin =
{
   /**
   * @note: Configuration of Default pin
   */
      (uint32)0x00080000, (uint8)0, (uint8)0
   };
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
/**
* @brief Pin default configuration data for configPB

*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(Port_Siul2_PinConfigType, PORT_CONST) Port_aPinConfigDefaultPB[PORT_MAX_CONFIGURED_PADS_U16]=
{
    {(Port_InternalPinIdType)16, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)17, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)18, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)19, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)20, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)21, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)28, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)29, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)30, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)59, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)60, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)64, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)65, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)66, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)68, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)77, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)78, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)96, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)103, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)104, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)105, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)106, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)107, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)108, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)128, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)129, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)130, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)132, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)134, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)135, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)136, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)137, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)160, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)163, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)164, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)166, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)243, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)244, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)245, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)246, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)249, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)250, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)334, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)335, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)336, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)337, (uint32)0x00000000, (uint32)0x00400000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)0, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)82, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)239, (uint32)0x00000000, (uint32)0x008c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)233, (uint32)0x00000000, (uint32)0x008c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)10, (uint32)0x02000000, (uint32)0x32800001, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)11, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)215, (uint32)0x02000000, (uint32)0x3280000d, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)144, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)184, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)187, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)218, (uint32)0x02000000, (uint32)0x3280000e, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)219, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)86, (uint32)0x02000000, (uint32)0x3280000d, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)87, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)83, (uint32)0x02000000, (uint32)0x32000003, (uint8)1, (uint8)1, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)183, (uint32)0x02000000, (uint32)0x32840003, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)37, (uint32)0x02000000, (uint32)0x32840003, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)38, (uint32)0x00000000, (uint32)0x308c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)69, (uint32)0x02000000, (uint32)0x32840004, (uint8)1, (uint8)1, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)46, (uint32)0x02000000, (uint32)0x32840004, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)119, (uint32)0x02000000, (uint32)0x32840004, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)84, (uint32)0x00000000, (uint32)0x008c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)109, (uint32)0x02000000, (uint32)0x32000003, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)159, (uint32)0x02000000, (uint32)0x32840003, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)155, (uint32)0x02000000, (uint32)0x32840003, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)157, (uint32)0x00000000, (uint32)0x008c0000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)188, (uint32)0x02000000, (uint32)0x32840003, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)189, (uint32)0x00000000, (uint32)0x30080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)190, (uint32)0x02000000, (uint32)0x32840003, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)191, (uint32)0x02000000, (uint32)0x32840003, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)257, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)13, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)39, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)70, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)71, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)72, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)73, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)75, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)76, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)139, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)140, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)147, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)148, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)149, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)150, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)151, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)152, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)153, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)55, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)194, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)195, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)196, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)197, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)198, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)199, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)200, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)224, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)226, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)227, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)228, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)229, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)230, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)305, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)306, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)307, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)308, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)309, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)310, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)311, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)58, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)62, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)302, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)303, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)304, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)93, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)253, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)225, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)290, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)300, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)301, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)94, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)74, (uint32)0x00000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)111, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)1, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)2, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)3, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)4, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)14, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)43, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)44, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)48, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)49, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)50, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)51, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)52, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)53, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)54, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)56, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)57, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)91, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)145, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)209, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)211, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)212, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)221, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)222, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)201, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)202, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)203, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)204, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)192, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)193, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)146, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)154, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)179, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)234, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)235, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)236, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)237, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)238, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)289, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)292, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)294, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)293, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)295, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)296, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)297, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)298, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)299, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)312, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)313, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)314, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)315, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)316, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)317, (uint32)0x02000000, (uint32)0x32000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)27, (uint32)0x02000000, (uint32)0x22000000, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)115, (uint32)0x02000000, (uint32)0x02000009, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)33, (uint32)0x02000000, (uint32)0x02000009, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)15, (uint32)0x02000000, (uint32)0x32000009, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)63, (uint32)0x02000000, (uint32)0x02000009, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)186, (uint32)0x02000000, (uint32)0x02000008, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)205, (uint32)0x02000000, (uint32)0x02000008, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)85, (uint32)0x02000000, (uint32)0x3200000a, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)95, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)88, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)116, (uint32)0x02000000, (uint32)0x3200000a, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)123, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)124, (uint32)0x02000000, (uint32)0x3200000a, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)122, (uint32)0x02000000, (uint32)0x3200000a, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)113, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)114, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)177, (uint32)0x02000000, (uint32)0x32000008, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)118, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)126, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)127, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)125, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)25, (uint32)0x02000000, (uint32)0x1200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)80, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)47, (uint32)0x02000000, (uint32)0x3200000b, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)61, (uint32)0x02000000, (uint32)0x12000008, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)214, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)217, (uint32)0x01000000, (uint32)0x00080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)220, (uint32)0x02000000, (uint32)0x2200000d, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)231, (uint32)0x02000000, (uint32)0x3200000c, (uint8)1, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE},
    {(Port_InternalPinIdType)232, (uint32)0x02000000, (uint32)0x30080000, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)TRUE, (boolean)FALSE}

};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
/**
* @brief Pad selection default configuration for configPB

*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(Port_Siul2_PadSelConfigType, PORT_CONST) Port_aPadSelConfigDefaultPB[PORT_NMBR_INMUX_REGS_U16]=
{
        (uint32)0x0000000b, /*"MSCR_MUX_0"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_1"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_2"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_3"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_4"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_5"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_6"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_7"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_8"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_9"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_10"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_11"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_12"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_13"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_14"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_15"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_16"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_17"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_18"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_19"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_20"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_21"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_22"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_23"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_24"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_25"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_26"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_27"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_28"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_29"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_30"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_31"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_32"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_33"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_34"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_35"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_36"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_37"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_38"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_39"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_40"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_41"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_42"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_43"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_44"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_45"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_46"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_47"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_48"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_49"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_50"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_51"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_52"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_53"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_54"*/ 
        (uint32)0x00000001, /*"MSCR_MUX_55"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_56"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_57"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_58"*/ 
        (uint32)0x00000001, /*"MSCR_MUX_59"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_60"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_61"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_62"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_63"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_64"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_65"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_66"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_67"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_68"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_69"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_70"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_71"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_72"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_73"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_74"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_75"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_76"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_77"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_78"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_79"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_82"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_83"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_84"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_85"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_86"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_87"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_88"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_89"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_90"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_91"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_96"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_97"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_98"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_99"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_100"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_101"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_102"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_103"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_104"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_105"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_106"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_112"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_113"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_114"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_115"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_116"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_117"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_118"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_119"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_120"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_121"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_122"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_128"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_129"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_130"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_131"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_132"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_133"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_134"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_135"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_136"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_137"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_144"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_145"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_146"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_147"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_148"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_149"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_150"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_151"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_152"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_153"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_154"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_155"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_156"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_157"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_158"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_159"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_160"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_161"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_162"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_163"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_164"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_165"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_166"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_167"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_168"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_169"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_170"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_171"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_172"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_173"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_174"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_175"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_176"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_177"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_178"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_179"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_180"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_181"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_182"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_183"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_184"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_185"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_186"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_187"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_188"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_189"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_190"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_191"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_192"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_193"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_194"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_195"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_196"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_197"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_198"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_199"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_200"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_201"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_202"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_203"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_204"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_205"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_206"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_207"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_208"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_209"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_210"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_211"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_212"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_213"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_214"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_215"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_216"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_217"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_218"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_219"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_220"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_221"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_222"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_223"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_224"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_225"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_226"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_227"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_228"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_229"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_230"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_231"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_232"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_233"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_234"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_235"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_236"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_237"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_238"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_239"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_240"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_241"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_242"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000002, /*"MSCR_MUX_246"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_247"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_248"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_249"*/ 
        (uint32)0x00000001, /*"MSCR_MUX_250"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_251"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_252"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_253"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_254"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_255"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_256"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_257"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_258"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_259"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_260"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_261"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_262"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_264"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_265"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_266"*/ 
        (uint32)0x00000001, /*"MSCR_MUX_267"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_268"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_269"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_270"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_271"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_272"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_273"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_276"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_277"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_278"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_279"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_280"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_281"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_282"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_283"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_284"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_285"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_286"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_287"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_288"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_289"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_290"*/ 
        (uint32)0x00000001, /*"MSCR_MUX_291"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_292"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_293"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_294"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_295"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_296"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_297"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_298"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_299"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_304"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_305"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_306"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_307"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_308"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_309"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_310"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_311"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_312"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_313"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_314"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_315"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_316"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_317"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_318"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_319"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_320"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_321"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_322"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_323"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_331"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_332"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_333"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_334"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_335"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_336"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_337"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_338"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_339"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_340"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_341"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_342"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_343"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_344"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_345"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_346"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_347"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_348"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_350"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_351"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_352"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000004, /*"MSCR_MUX_368"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_369"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_370"*/ 
        (uint32)0x00000003, /*"MSCR_MUX_371"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_372"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_373"*/ 
        (uint32)0x00000008, /*"MSCR_MUX_374"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_375"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_376"*/ 
        (uint32)0x00000001, /*"MSCR_MUX_377"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_378"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_379"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_380"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_381"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_382"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_383"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_384"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_385"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_386"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_387"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_388"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_404"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_405"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_406"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_407"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_410"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_411"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_412"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_413"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_414"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_415"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_416"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_417"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_418"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_419"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_420"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_445"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_446"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_447"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_448"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_449"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_450"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_451"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_452"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_485"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_486"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_488"*/ 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0xFFFFFFFFU, 
        (uint32)0x00000000, /*"MSCR_MUX_493"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_494"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_495"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_496"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_497"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_498"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_499"*/ 
        (uint32)0x00000000, /*"MSCR_MUX_500"*/ 

};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"


#if (PORT_SET_SIUL2_API == STD_ON)
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(Port_siul2_request_config, PORT_CONST) Port_Siul2_config[0] =
{
    
};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
#endif
/**
* @brief This table contains all the Configured Port Pin parameters and the
*        number of Port Pins configured by the tool for the post-build mode NotUsedPortPin
* @violates @ref PORT_PBCFG_REF_4 Violates MISRA 2004 Required Rule 8.10
*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
CONST(Port_ConfigType, PORT_CONST) NotUsedPortPin =
{
      .Port_UsedPin={
            PORT_MAX_CONFIGURED_PADS_U16,
            Port_aPinConfigDefaultPB,
            Port_aPadSelConfigDefaultPB
        },
        .Port_UnusedPin={
            PORT_MAX_UNUSED_PADS_U16,
    #if (PORT_MAX_UNUSED_PADS_U16 != 0U)
      Port_au16NoUnUsedPadsArrayDefault,
    #else
      NULL_PTR,
    #endif
            &Port_UnUsedPin
        },
        .Etpu_IS=u8Port_Etpu_Input_Select,
        .coreMap = Port_CoreMap,
#if (PORT_SET_SIUL2_API == STD_ON)
        .reqConfig = Port_Siul2_config
#endif
};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
/**
* @brief This table contains all the Configured Port Pin parameters and the
*        number of Port Pins configured by the tool for the post-build mode PortContainer
* @violates @ref PORT_PBCFG_REF_4 Violates MISRA 2004 Required Rule 8.10
*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
CONST(Port_ConfigType, PORT_CONST) PortContainer =
{
      .Port_UsedPin={
            PORT_MAX_CONFIGURED_PADS_U16,
            Port_aPinConfigDefaultPB,
            Port_aPadSelConfigDefaultPB
        },
        .Port_UnusedPin={
            PORT_MAX_UNUSED_PADS_U16,
    #if (PORT_MAX_UNUSED_PADS_U16 != 0U)
      Port_au16NoUnUsedPadsArrayDefault,
    #else
      NULL_PTR,
    #endif
            &Port_UnUsedPin
        },
        .Etpu_IS=u8Port_Etpu_Input_Select,
        .coreMap = Port_CoreMap,
#if (PORT_SET_SIUL2_API == STD_ON)
        .reqConfig = Port_Siul2_config
#endif
};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief Port INOUT settings data
*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
CONST(Port_InoutSettingType,PORT_CONST) Port_aPadFunctInoutMuxSettings[PORT_INOUT_TABLE_NUM_ENTRIES_U16] = 
{
 

  /* Inout settings for pad PORT13:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT13 input func */
  {13U, 88U, 525U, 4U},

  /* Inout settings for pad PORT24:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_5_SCK_5_IN_OUT24 input func */
  {24U, 88U, 536U, 3U},

  /* Inout settings for pad PORT24:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT24 input func */
  {24U, 89U, 536U, 4U},

  /* Inout settings for pad PORT36:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_3_SCK_3_IN_OUT36 input func */
  {36U, 88U, 548U, 3U},

  /* Inout settings for pad PORT38:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_0_SCL0_IN_OUT38 input func */
  {38U, 88U, 550U, 1U},

  /* Inout settings for pad PORT39:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_0_SDA0_IN_OUT39 input func */
  {39U, 88U, 551U, 1U},

  /* Inout settings for pad PORT39:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_12_SCK_12_IN_OUT39 input func */
  {39U, 89U, 551U, 4U},

  /* Inout settings for pad PORT43:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* FEC_FEC_MDIO_IN_OUT43 input func */
  {43U, 88U, 555U, 1U},

  /* Inout settings for pad PORT43:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* QSPI1_QSCK_1_IN_OUT43 input func */
  {43U, 89U, 555U, 13U},

  /* Inout settings for pad PORT46:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT46 input func */
  {46U, 88U, 558U, 2U},

  /* Inout settings for pad PORT46:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_1_SCK_1_IN_OUT46 input func */
  {46U, 89U, 558U, 4U},

  /* Inout settings for pad PORT48:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT48 input func */
  {48U, 88U, 560U, 3U},

  /* Inout settings for pad PORT49:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_0_SDA0_IN_OUT49 input func */
  {49U, 88U, 561U, 1U},

  /* Inout settings for pad PORT49:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT49 input func */
  {49U, 89U, 561U, 3U},

  /* Inout settings for pad PORT50:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_0_SCL0_IN_OUT50 input func */
  {50U, 88U, 562U, 1U},

  /* Inout settings for pad PORT50:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT50 input func */
  {50U, 89U, 562U, 2U},

  /* Inout settings for pad PORT50:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT50 input func */
  {50U, 90U, 562U, 4U},

  /* Inout settings for pad PORT50:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT50 input func */
  {50U, 91U, 562U, 12U},

  /* Inout settings for pad PORT51:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT51 input func */
  {51U, 88U, 563U, 2U},

  /* Inout settings for pad PORT51:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT51 input func */
  {51U, 89U, 563U, 4U},

  /* Inout settings for pad PORT52:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_0_SCK_0_IN_OUT52 input func */
  {52U, 88U, 564U, 3U},

  /* Inout settings for pad PORT61:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT61 input func */
  {61U, 88U, 573U, 2U},

  /* Inout settings for pad PORT82:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_12_SCK_12_IN_OUT82 input func */
  {82U, 88U, 594U, 4U},

  /* Inout settings for pad PORT85:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_1_SCK_1_IN_OUT85 input func */
  {85U, 88U, 597U, 4U},

  /* Inout settings for pad PORT89:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_5_SCK_5_IN_OUT89 input func */
  {89U, 88U, 601U, 2U},

  /* Inout settings for pad PORT90:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_5_SCK_5_IN_OUT90 input func */
  {90U, 88U, 602U, 2U},

  /* Inout settings for pad PORT90:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_5_SCK_5_IN_OUT90 input func */
  {90U, 89U, 602U, 13U},

  /* Inout settings for pad PORT92:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_5_SCK_5_IN_OUT92 input func */
  {92U, 88U, 604U, 3U},

  /* Inout settings for pad PORT113:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT113 input func */
  {113U, 88U, 625U, 4U},

  /* Inout settings for pad PORT114:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_12_SCK_12_IN_OUT114 input func */
  {114U, 88U, 626U, 5U},

  /* Inout settings for pad PORT120:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_1_SCK_1_IN_OUT120 input func */
  {120U, 88U, 632U, 4U},

  /* Inout settings for pad PORT124:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_3_SCK_3_IN_OUT124 input func */
  {124U, 88U, 636U, 3U},

  /* Inout settings for pad PORT137:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_4_SCK_4_IN_OUT137 input func */
  {137U, 88U, 649U, 2U},

  /* Inout settings for pad PORT140:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT140 input func */
  {140U, 88U, 652U, 2U},

  /* Inout settings for pad PORT156:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_0_SCK_0_IN_OUT156 input func */
  {156U, 88U, 668U, 3U},

  /* Inout settings for pad PORT159:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_0_SCK_0_IN_OUT159 input func */
  {159U, 88U, 671U, 3U},

  /* Inout settings for pad PORT183:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_3_SCK_3_IN_OUT183 input func */
  {183U, 88U, 695U, 3U},

  /* Inout settings for pad PORT190:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_2_SCK_2_IN_OUT190 input func */
  {190U, 88U, 702U, 3U},

  /* Inout settings for pad PORT192:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_1_SCL1_IN_OUT192 input func */
  {192U, 88U, 704U, 1U},

  /* Inout settings for pad PORT195:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_1_SDA1_IN_OUT195 input func */
  {195U, 88U, 707U, 1U},

  /* Inout settings for pad PORT199:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* FEC_FEC_MDIO_IN_OUT199 input func */
  {199U, 88U, 711U, 1U},

  /* Inout settings for pad PORT220:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_5_SCK_5_IN_OUT220 input func */
  {220U, 88U, 732U, 12U},

  /* Inout settings for pad PORT232:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_6_SCK_6_IN_OUT232 input func */
  {232U, 88U, 744U, 1U},

  /* Inout settings for pad PORT233:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_6_SCK_6_IN_OUT233 input func */
  {233U, 88U, 745U, 2U},

  /* Inout settings for pad PORT237:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_1_SCL1_IN_OUT237 input func */
  {237U, 88U, 749U, 4U},

  /* Inout settings for pad PORT239:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* I2C_1_SDA1_IN_OUT239 input func */
  {239U, 88U, 751U, 1U},

  /* Inout settings for pad PORT296:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* QSPI0_QSCK_0_IN_OUT296 input func */
  {296U, 88U, 808U, 11U},

  /* Inout settings for pad PORT331:     {MSCR, MODE, INMUX reg, PADSEL val} */
  /* DSPI_6_SCK_6_IN_OUT331 input func */
  {331U, 88U, 843U, 3U}


};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"

/**
* @brief Port INPUT INMUX settings data
*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
CONST(Port_InMuxSettingType,PORT_CONST) Port_aPadFunctInMuxSettings[PORT_INPUT_INMUX_TABLE_NUM_ENTRIES_U16]=
{
 
  /* INMUX settings for pad not available:  */ 
  { NO_INPUTMUX_U16, 0U},
  /* INMUX settings for pad PORT0:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 4U},
  /* GTM_TIM3_7 input func */
  {31U, 4U},
  /* DSPI_2_SIN_2 input func */
  {374U, 2U},
  /* SENT_0_SENTRX6_0 input func */
  {287U, 1U},
  /* INMUX settings for pad PORT1:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 4U},
  /* GTM_TIM3_4 input func */
  {28U, 4U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 4U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 2U},
  /* INMUX settings for pad PORT2:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 4U},
  /* GTM_TIM3_3 input func */
  {27U, 4U},
  /* INMUX settings for pad PORT3:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 3U},
  /* GTM_TIM3_0 input func */
  {24U, 3U},
  /* DSPI_2_SIN_2 input func */
  {374U, 12U},
  /* DSPI_5_SIN_5 input func */
  {383U, 1U},
  /* INMUX settings for pad PORT8:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 6U},
  /* GTM_TIM1_4 input func */
  {12U, 6U},
  /* INMUX settings for pad PORT9:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 5U},
  /* GTM_TIM1_5 input func */
  {13U, 5U},
  /* INMUX settings for pad PORT10:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 7U},
  /* GTM_TIM1_3 input func */
  {11U, 7U},
  /* SENT_0_SENTRX7_0 input func */
  {288U, 1U},
  /* INMUX settings for pad PORT11:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 7U},
  /* GTM_TIM1_4 input func */
  {12U, 7U},
  /* M_CAN_1_MCAN1RX input func */
  {246U, 2U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 2U},
  /* FlexRay_0_RXDA_0 input func */
  {260U, 2U},
  /* FlexRay_0_RXDB_0 input func */
  {261U, 2U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 2U},
  /* SENT_1_SENTRX5_1 input func */
  {289U, 1U},
  /* INMUX settings for pad PORT12:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 4U},
  /* GTM_TIM3_5 input func */
  {29U, 4U},
  /* DSPI_2_SS_2 input func */
  {376U, 1U},
  /* DSPI_4_SS_4 input func */
  {382U, 2U},
  /* SENT_0_SENTRX5_0 input func */
  {286U, 1U},
  /* eMIOS_1_EMIOS28 input func */
  {60U, 0U},
  /* INMUX settings for pad PORT13:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 4U},
  /* GTM_TIM3_6 input func */
  {30U, 4U},
  /* M_CAN_1_MCAN1RX input func */
  {246U, 1U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 1U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 1U},
  /* DSPI_2_SCK_2 input func */
  {375U, 1U},
  /* INMUX settings for pad PORT14:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 6U},
  /* GTM_TIM1_3 input func */
  {11U, 6U},
  /* INMUX settings for pad PORT15:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 3U},
  /* GTM_TIM1_5 input func */
  {13U, 3U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 7U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 2U},
  /* DSPI_5_SS_5 input func */
  {385U, 4U},
  /* INMUX settings for pad PORT24:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 4U},
  /* GTM_TIM1_2 input func */
  {10U, 4U},
  /* GTM_TIM2_2 input func */
  {18U, 13U},
  /* DSPI_2_SCK_2 input func */
  {375U, 5U},
  /* DSPI_5_SCK_5 input func */
  {384U, 1U},
  /* INMUX settings for pad PORT25:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 4U},
  /* GTM_TIM1_0 input func */
  {8U, 4U},
  /* M_CAN_1_MCAN1RX input func */
  {246U, 5U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 11U},
  /* DSPI_2_SS_2 input func */
  {376U, 3U},
  /* DSPI_5_SS_5 input func */
  {385U, 1U},
  /* SENT_1_SENTRX5_1 input func */
  {289U, 5U},
  /* FEC_FEC_RXD2 input func */
  {417U, 2U},
  /* INMUX settings for pad PORT26:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 4U},
  /* GTM_TIM1_1 input func */
  {9U, 4U},
  /* INMUX settings for pad PORT27:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 3U},
  /* GTM_TIM1_4 input func */
  {12U, 3U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 5U},
  /* DSPI_5_SIN_5 input func */
  {383U, 13U},
  /* DSPI_12_SIN_12 input func */
  {404U, 7U},
  /* INMUX settings for pad PORT28:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX4_1 input func */
  {285U, 3U},
  /* ETPU_1_ETPU1_31 input func */
  {452U, 1U},
  /* eMIOS_0_EMIOS16 input func */
  {48U, 0U},
  /* INMUX settings for pad PORT29:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX3_1 input func */
  {283U, 3U},
  /* ETPU_1_ETPU1_30 input func */
  {451U, 1U},
  /* eMIOS_0_EMIOS17 input func */
  {49U, 0U},
  /* INMUX settings for pad PORT30:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX4_0 input func */
  {284U, 3U},
  /* ETPU_1_ETPU1_29 input func */
  {450U, 1U},
  /* eMIOS_0_EMIOS18 input func */
  {50U, 0U},
  /* INMUX settings for pad PORT31:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX2_1 input func */
  {282U, 3U},
  /* ETPU_1_ETPU1_28 input func */
  {449U, 1U},
  /* eMIOS_0_EMIOS19 input func */
  {51U, 0U},
  /* INMUX settings for pad PORT32:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 2U},
  /* GTM_TIM3_1 input func */
  {25U, 2U},
  /* SENT_0_SENTRX1_0 input func */
  {277U, 1U},
  /* ETPU_3_ETPU3_1 input func */
  {486U, 1U},
  /* INMUX settings for pad PORT33:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 1U},
  /* GTM_TIM3_1 input func */
  {25U, 1U},
  /* SENT_0_SENTRX0_0 input func */
  {276U, 1U},
  /* PSI5_0_SDIN0_PSI5_0 input func */
  {304U, 2U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 6U},
  /* SENT_0_SENTRX2_0 input func */
  {278U, 4U},
  /* INMUX settings for pad PORT34:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 2U},
  /* GTM_TIM3_0 input func */
  {24U, 2U},
  /* DSPI_4_DSI0 input func */
  {144U, 2U},
  /* DSPI_4_DSI1 input func */
  {145U, 2U},
  /* DSPI_4_DSI2 input func */
  {146U, 2U},
  /* DSPI_4_DSI3 input func */
  {147U, 2U},
  /* DSPI_4_DSI4 input func */
  {148U, 2U},
  /* DSPI_4_DSI5 input func */
  {149U, 2U},
  /* DSPI_4_DSI6 input func */
  {150U, 2U},
  /* DSPI_4_DSI7 input func */
  {151U, 2U},
  /* DSPI_4_DSI8 input func */
  {152U, 2U},
  /* DSPI_4_DSI9 input func */
  {153U, 2U},
  /* DSPI_4_DSI10 input func */
  {154U, 2U},
  /* DSPI_4_DSI11 input func */
  {155U, 2U},
  /* DSPI_4_DSI12 input func */
  {156U, 2U},
  /* DSPI_4_DSI13 input func */
  {157U, 2U},
  /* DSPI_4_DSI14 input func */
  {158U, 2U},
  /* DSPI_4_DSI15 input func */
  {159U, 2U},
  /* DSPI_4_DSI16 input func */
  {160U, 2U},
  /* DSPI_4_DSI17 input func */
  {161U, 2U},
  /* DSPI_4_DSI18 input func */
  {162U, 2U},
  /* DSPI_4_DSI19 input func */
  {163U, 2U},
  /* DSPI_4_DSI20 input func */
  {164U, 2U},
  /* DSPI_4_DSI21 input func */
  {165U, 2U},
  /* DSPI_4_DSI22 input func */
  {166U, 2U},
  /* DSPI_4_DSI23 input func */
  {167U, 2U},
  /* DSPI_4_DSI24 input func */
  {168U, 2U},
  /* DSPI_4_DSI25 input func */
  {169U, 2U},
  /* DSPI_4_DSI26 input func */
  {170U, 2U},
  /* DSPI_4_DSI27 input func */
  {171U, 2U},
  /* DSPI_4_DSI28 input func */
  {172U, 2U},
  /* DSPI_4_DSI29 input func */
  {173U, 2U},
  /* DSPI_4_DSI30 input func */
  {174U, 2U},
  /* DSPI_4_DSI31 input func */
  {175U, 2U},
  /* DSPI_5_DSI0 input func */
  {176U, 2U},
  /* DSPI_5_DSI1 input func */
  {177U, 2U},
  /* DSPI_5_DSI2 input func */
  {178U, 2U},
  /* DSPI_5_DSI3 input func */
  {179U, 2U},
  /* DSPI_5_DSI4 input func */
  {180U, 2U},
  /* DSPI_5_DSI5 input func */
  {181U, 2U},
  /* DSPI_5_DSI6 input func */
  {182U, 2U},
  /* DSPI_5_DSI7 input func */
  {183U, 2U},
  /* DSPI_5_DSI8 input func */
  {184U, 2U},
  /* DSPI_5_DSI9 input func */
  {185U, 2U},
  /* DSPI_5_DSI10 input func */
  {186U, 2U},
  /* DSPI_5_DSI11 input func */
  {187U, 2U},
  /* DSPI_5_DSI12 input func */
  {188U, 2U},
  /* DSPI_5_DSI13 input func */
  {189U, 2U},
  /* DSPI_5_DSI14 input func */
  {190U, 2U},
  /* DSPI_5_DSI15 input func */
  {191U, 2U},
  /* DSPI_5_DSI16 input func */
  {192U, 2U},
  /* DSPI_5_DSI17 input func */
  {193U, 2U},
  /* DSPI_5_DSI18 input func */
  {194U, 2U},
  /* DSPI_5_DSI19 input func */
  {195U, 2U},
  /* DSPI_5_DSI20 input func */
  {196U, 2U},
  /* DSPI_5_DSI21 input func */
  {197U, 2U},
  /* DSPI_5_DSI22 input func */
  {198U, 2U},
  /* DSPI_5_DSI23 input func */
  {199U, 2U},
  /* DSPI_5_DSI24 input func */
  {200U, 2U},
  /* DSPI_5_DSI25 input func */
  {201U, 2U},
  /* DSPI_5_DSI26 input func */
  {202U, 2U},
  /* DSPI_5_DSI27 input func */
  {203U, 2U},
  /* DSPI_5_DSI28 input func */
  {204U, 2U},
  /* DSPI_5_DSI29 input func */
  {205U, 2U},
  /* DSPI_5_DSI30 input func */
  {206U, 2U},
  /* DSPI_5_DSI31 input func */
  {207U, 2U},
  /* INMUX settings for pad PORT35:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 1U},
  /* GTM_TIM3_0 input func */
  {24U, 1U},
  /* SDADC_3_EXT_DATA3 input func */
  {70U, 1U},
  /* SENT_0_SENTRX0_0 input func */
  {276U, 2U},
  /* INMUX settings for pad PORT36:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 1U},
  /* GTM_TIM1_7 input func */
  {15U, 1U},
  /* SDADC_3_EXT_CLKIN3 input func */
  {71U, 1U},
  /* SENT_0_SENTRX1_0 input func */
  {277U, 2U},
  /* PSI5_1_SDIN0_PSI5_1 input func */
  {312U, 1U},
  /* PSI5_S_RX_PSI5_S input func */
  {331U, 3U},
  /* DSPI_3_SCK_3 input func */
  {378U, 1U},
  /* LINFlexD_4_LIN4RX input func */
  {340U, 0U},
  /* INMUX settings for pad PORT37:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 1U},
  /* GTM_TIM1_6 input func */
  {14U, 1U},
  /* SDADC_4_EXT_DATA4 input func */
  {72U, 1U},
  /* SENT_0_SENTRX2_0 input func */
  {278U, 2U},
  /* DSPI_3_SIN_3 input func */
  {377U, 2U},
  /* DSPI_5_SIN_5 input func */
  {383U, 11U},
  /* INMUX settings for pad PORT38:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 1U},
  /* GTM_TIM1_5 input func */
  {13U, 1U},
  /* SDADC_4_EXT_CLKIN4 input func */
  {73U, 1U},
  /* M_TTCAN_0_TTCAN_0_EVT input func */
  {241U, 2U},
  /* SENT_0_SENTRX3_0 input func */
  {279U, 2U},
  /* I2C_0_SCL0 input func */
  {297U, 1U},
  /* PSI5_0_SDIN1_PSI5_0 input func */
  {308U, 1U},
  /* PSI5_S_RX_PSI5_S input func */
  {331U, 2U},
  /* DSPI_3_SIN_3 input func */
  {377U, 1U},
  /* DSPI_5_SIN_5 input func */
  {383U, 10U},
  /* LINFlexD_5_LIN5RX input func */
  {341U, 0U},
  /* INMUX settings for pad PORT39:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 1U},
  /* GTM_TIM1_4 input func */
  {12U, 1U},
  /* M_TTCAN_0_TTCAN_0_RX input func */
  {240U, 4U},
  /* M_TTCAN_0_TTCAN_0_EVT input func */
  {241U, 1U},
  /* I2C_0_SDA0 input func */
  {296U, 1U},
  /* DSPI_3_SS_3 input func */
  {379U, 1U},
  /* DSPI_12_SCK_12 input func */
  {405U, 1U},
  /* INMUX settings for pad PORT40:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 1U},
  /* GTM_TIM1_3 input func */
  {11U, 1U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 3U},
  /* FlexRay_0_RXDB_0 input func */
  {261U, 1U},
  /* PSI5_0_SDIN0_PSI5_0 input func */
  {304U, 1U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 6U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 1U},
  /* INMUX settings for pad PORT41:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 1U},
  /* GTM_TIM1_2 input func */
  {10U, 1U},
  /* DSPI_12_SS_12 input func */
  {406U, 1U},
  /* INMUX settings for pad PORT42:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 6U},
  /* GTM_TIM3_7 input func */
  {31U, 6U},
  /* FEC_FEC_TXCLK_REFCLK input func */
  {411U, 1U},
  /* SENT_1_SENTRX0_1 input func */
  {280U, 4U},
  /* INMUX settings for pad PORT43:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 6U},
  /* GTM_TIM3_6 input func */
  {30U, 6U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 4U},
  /* DSPI_0_SS_0 input func */
  {370U, 5U},
  /* DSPI_4_SS_4 input func */
  {382U, 6U},
  /* FEC_FEC_MDIO input func */
  {412U, 4U},
  /* FEC_FEC_RXDV input func */
  {413U, 1U},
  /* FEC_FEC_CRS input func */
  {414U, 1U},
  /* INMUX settings for pad PORT44:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 6U},
  /* GTM_TIM3_5 input func */
  {29U, 6U},
  /* FlexRay_0_RXDB_0 input func */
  {261U, 4U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 3U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 10U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 2U},
  /* DSPI_1_SS_1 input func */
  {373U, 1U},
  /* FEC_FEC_RXD0 input func */
  {415U, 1U},
  /* SENT_0_SENTRX2_A input func */
  {278U, 5U},
  /* INMUX settings for pad PORT45:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 6U},
  /* GTM_TIM3_4 input func */
  {28U, 6U},
  /* FlexRay_0_RXDA_0 input func */
  {260U, 4U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 8U},
  /* DSPI_1_SIN_1 input func */
  {371U, 2U},
  /* FEC_FEC_RXD1 input func */
  {416U, 1U},
  /* SENT_0_SENTRX5_0 input func */
  {286U, 5U},
  /* INMUX settings for pad PORT46:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 6U},
  /* GTM_TIM3_3 input func */
  {27U, 6U},
  /* DSPI_1_SCK_1 input func */
  {372U, 1U},
  /* DSPI_4_SCK_4 input func */
  {381U, 3U},
  /* DSPI_4_SS_4 input func */
  {382U, 4U},
  /* FEC_FEC_RXCLK input func */
  {410U, 1U},
  /* INMUX settings for pad PORT47:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 5U},
  /* GTM_TIM3_2 input func */
  {26U, 5U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 6U},
  /* DSPI_1_SIN_1 input func */
  {371U, 1U},
  /* INMUX settings for pad PORT48:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 6U},
  /* GTM_TIM3_0 input func */
  {24U, 6U},
  /* INMUX settings for pad PORT49:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 5U},
  /* GTM_TIM3_7 input func */
  {31U, 5U},
  /* I2C_0_SDA0 input func */
  {296U, 2U},
  /* DSPI_2_SIN_2 input func */
  {374U, 5U},
  /* DSPI_2_SS_2 input func */
  {376U, 4U},
  /* LINFlexD_6_LIN6RX input func */
  {342U, 0U},
  /* INMUX settings for pad PORT50:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 5U},
  /* GTM_TIM3_6 input func */
  {30U, 5U},
  /* I2C_0_SCL0 input func */
  {297U, 2U},
  /* DSPI_2_SCK_2 input func */
  {375U, 6U},
  /* INMUX settings for pad PORT51:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 5U},
  /* GTM_TIM3_5 input func */
  {29U, 5U},
  /* DSPI_2_SIN_2 input func */
  {374U, 14U},
  /* LINFlexD_7_LIN7RX input func */
  {343U, 0U},
  /* INMUX settings for pad PORT52:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 3U},
  /* GTM_TIM3_7 input func */
  {31U, 3U},
  /* DSPI_0_SCK_0 input func */
  {369U, 1U},
  /* SENT_1_SENTRX1_1 input func */
  {281U, 4U},
  /* INMUX settings for pad PORT53:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 4U},
  /* GTM_TIM3_0 input func */
  {24U, 4U},
  /* DSPI_0_SIN_0 input func */
  {368U, 1U},
  /* INMUX settings for pad PORT54:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 6U},
  /* GTM_TIM1_2 input func */
  {10U, 6U},
  /* LINFlexD_8_LIN8RX input func */
  {344U, 0U},
  /* INMUX settings for pad PORT55:      {INMUX reg, PADSEL val} */
  /* DSPI_2_SIN_2 input func */
  {374U, 6U},
  /* DSPI_5_SIN_5 input func */
  {383U, 6U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 9U},
  /* GTM_TIM0_1 input func */
  {1U, 6U},
  /* GTM_TIM1_1 input func */
  {9U, 6U},
  /* DSPI_1_SIN_1 input func */
  {371U, 6U},
  /* DSPI_4_SIN_4 input func */
  {380U, 6U},
  /* INMUX settings for pad PORT56:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 3U},
  /* GTM_TIM3_1 input func */
  {25U, 3U},
  /* DSPI_4_DSI0 input func */
  {144U, 3U},
  /* DSPI_4_DSI1 input func */
  {145U, 3U},
  /* DSPI_4_DSI2 input func */
  {146U, 3U},
  /* DSPI_4_DSI3 input func */
  {147U, 3U},
  /* DSPI_4_DSI4 input func */
  {148U, 3U},
  /* DSPI_4_DSI5 input func */
  {149U, 3U},
  /* DSPI_4_DSI6 input func */
  {150U, 3U},
  /* DSPI_4_DSI7 input func */
  {151U, 3U},
  /* DSPI_4_DSI8 input func */
  {152U, 3U},
  /* DSPI_4_DSI9 input func */
  {153U, 3U},
  /* DSPI_4_DSI10 input func */
  {154U, 3U},
  /* DSPI_4_DSI11 input func */
  {155U, 3U},
  /* DSPI_4_DSI12 input func */
  {156U, 3U},
  /* DSPI_4_DSI13 input func */
  {157U, 3U},
  /* DSPI_4_DSI14 input func */
  {158U, 3U},
  /* DSPI_4_DSI15 input func */
  {159U, 3U},
  /* DSPI_4_DSI16 input func */
  {160U, 3U},
  /* DSPI_4_DSI17 input func */
  {161U, 3U},
  /* DSPI_4_DSI18 input func */
  {162U, 3U},
  /* DSPI_4_DSI19 input func */
  {163U, 3U},
  /* DSPI_4_DSI20 input func */
  {164U, 3U},
  /* DSPI_4_DSI21 input func */
  {165U, 3U},
  /* DSPI_4_DSI22 input func */
  {166U, 3U},
  /* DSPI_4_DSI23 input func */
  {167U, 3U},
  /* DSPI_4_DSI24 input func */
  {168U, 3U},
  /* DSPI_4_DSI25 input func */
  {169U, 3U},
  /* DSPI_4_DSI26 input func */
  {170U, 3U},
  /* DSPI_4_DSI27 input func */
  {171U, 3U},
  /* DSPI_4_DSI28 input func */
  {172U, 3U},
  /* DSPI_4_DSI29 input func */
  {173U, 3U},
  /* DSPI_4_DSI30 input func */
  {174U, 3U},
  /* DSPI_4_DSI31 input func */
  {175U, 3U},
  /* DSPI_5_DSI0 input func */
  {176U, 3U},
  /* DSPI_5_DSI1 input func */
  {177U, 3U},
  /* DSPI_5_DSI2 input func */
  {178U, 3U},
  /* DSPI_5_DSI3 input func */
  {179U, 3U},
  /* DSPI_5_DSI4 input func */
  {180U, 3U},
  /* DSPI_5_DSI5 input func */
  {181U, 3U},
  /* DSPI_5_DSI6 input func */
  {182U, 3U},
  /* DSPI_5_DSI7 input func */
  {183U, 3U},
  /* DSPI_5_DSI8 input func */
  {184U, 3U},
  /* DSPI_5_DSI9 input func */
  {185U, 3U},
  /* DSPI_5_DSI10 input func */
  {186U, 3U},
  /* DSPI_5_DSI11 input func */
  {187U, 3U},
  /* DSPI_5_DSI12 input func */
  {188U, 3U},
  /* DSPI_5_DSI13 input func */
  {189U, 3U},
  /* DSPI_5_DSI14 input func */
  {190U, 3U},
  /* DSPI_5_DSI15 input func */
  {191U, 3U},
  /* DSPI_5_DSI16 input func */
  {192U, 3U},
  /* DSPI_5_DSI17 input func */
  {193U, 3U},
  /* DSPI_5_DSI18 input func */
  {194U, 3U},
  /* DSPI_5_DSI19 input func */
  {195U, 3U},
  /* DSPI_5_DSI20 input func */
  {196U, 3U},
  /* DSPI_5_DSI21 input func */
  {197U, 3U},
  /* DSPI_5_DSI22 input func */
  {198U, 3U},
  /* DSPI_5_DSI23 input func */
  {199U, 3U},
  /* DSPI_5_DSI24 input func */
  {200U, 3U},
  /* DSPI_5_DSI25 input func */
  {201U, 3U},
  /* DSPI_5_DSI26 input func */
  {202U, 3U},
  /* DSPI_5_DSI27 input func */
  {203U, 3U},
  /* DSPI_5_DSI28 input func */
  {204U, 3U},
  /* DSPI_5_DSI29 input func */
  {205U, 3U},
  /* DSPI_5_DSI30 input func */
  {206U, 3U},
  /* DSPI_5_DSI31 input func */
  {207U, 3U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 9U},
  /* DSPI_2_SIN_2 input func */
  {374U, 13U},
  /* DSPI_5_SIN_5 input func */
  {383U, 2U},
  /* INMUX settings for pad PORT57:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 3U},
  /* GTM_TIM1_2 input func */
  {10U, 3U},
  /* GTM_TIM2_2 input func */
  {18U, 12U},
  /* SDADC_0_EXT_DATA0 input func */
  {64U, 2U},
  /* SENT_1_SENTRX0_1 input func */
  {280U, 2U},
  /* INMUX settings for pad PORT58:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 3U},
  /* GTM_TIM1_3 input func */
  {11U, 3U},
  /* INMUX settings for pad PORT60:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 1U},
  /* GTM_TIM3_5 input func */
  {29U, 1U},
  /* SDADC_2_EXT_DATA2 input func */
  {68U, 1U},
  /* SENT_1_SENTRX1_1 input func */
  {281U, 1U},
  /* DSPI_4_SIN_4 input func */
  {380U, 2U},
  /* ETPU_3_ETPU3_15 input func */
  {500U, 1U},
  /* eMIOS_1_EMIOS24 input func */
  {56U, 0U},
  /* INMUX settings for pad PORT61:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 1U},
  /* GTM_TIM3_6 input func */
  {30U, 1U},
  /* SDADC_4_EXT_CLKIN4 input func */
  {73U, 2U},
  /* SENT_1_SENTRX4_1 input func */
  {285U, 1U},
  /* DSPI_4_SCK_4 input func */
  {381U, 1U},
  /* ETPU_3_ETPU3_0 input func */
  {485U, 1U},
  /* SENT_0_SENTRX0_0 input func */
  {276U, 4U},
  /* INMUX settings for pad PORT62:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 1U},
  /* GTM_TIM1_0 input func */
  {8U, 1U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 7U},
  /* DSPI_3_SIN_3 input func */
  {377U, 7U},
  /* DSPI_5_SIN_5 input func */
  {383U, 14U},
  /* DSPI_12_SIN_12 input func */
  {404U, 3U},
  /* INMUX settings for pad PORT63:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 1U},
  /* GTM_TIM1_1 input func */
  {9U, 1U},
  /* M_TTCAN_0_TTCAN_0_RX input func */
  {240U, 1U},
  /* FlexRay_0_RXDA_0 input func */
  {260U, 1U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 1U},
  /* DSPI_5_SIN_5 input func */
  {383U, 9U},
  /* DSPI_12_SIN_12 input func */
  {404U, 1U},
  /* INMUX settings for pad PORT64:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 1U},
  /* GTM_TIM3_2 input func */
  {26U, 1U},
  /* SDADC_3_EXT_CLKIN3 input func */
  {71U, 2U},
  /* M_CAN_3_MCAN3RX input func */
  {248U, 1U},
  /* SENT_0_SENTRX2_0 input func */
  {278U, 1U},
  /* PSI5_0_SDIN1_PSI5_0 input func */
  {308U, 2U},
  /* ETPU_3_ETPU3_14 input func */
  {499U, 1U},
  /* eMIOS_1_EMIOS25 input func */
  {57U, 0U},
  /* INMUX settings for pad PORT65:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 1U},
  /* GTM_TIM3_3 input func */
  {27U, 1U},
  /* SDADC_3_EXT_DATA3 input func */
  {70U, 2U},
  /* SENT_0_SENTRX3_0 input func */
  {279U, 1U},
  /* DSPI_4_SS_4 input func */
  {382U, 1U},
  /* ETPU_3_ETPU3_13 input func */
  {498U, 1U},
  /* eMIOS_1_EMIOS26 input func */
  {58U, 0U},
  /* INMUX settings for pad PORT66:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 1U},
  /* GTM_TIM3_4 input func */
  {28U, 1U},
  /* SDADC_2_EXT_CLKIN2 input func */
  {69U, 1U},
  /* SENT_1_SENTRX0_1 input func */
  {280U, 1U},
  /* PSI5_1_SDIN0_PSI5_1 input func */
  {312U, 2U},
  /* DSPI_4_SIN_4 input func */
  {380U, 1U},
  /* ETPU_3_ETPU3_12 input func */
  {497U, 1U},
  /* eMIOS_1_EMIOS27 input func */
  {59U, 0U},
  /* INMUX settings for pad PORT67:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 1U},
  /* GTM_TIM3_7 input func */
  {31U, 1U},
  /* SDADC_4_EXT_DATA4 input func */
  {72U, 2U},
  /* SENT_1_SENTRX3_1 input func */
  {283U, 1U},
  /* ETPU_3_TCRCLKC input func */
  {501U, 0U},
  /* SIUL_2_IRQ6 input func */
  {273U, 1U},
  /* INMUX settings for pad PORT68:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 2U},
  /* GTM_TIM1_0 input func */
  {8U, 2U},
  /* SDADC_1_EXT_CLKIN1 input func */
  {67U, 1U},
  /* SENT_0_SENTRX4_0 input func */
  {284U, 1U},
  /* ETPU_1_ETPU1_27 input func */
  {448U, 1U},
  /* eMIOS_0_EMIOS20 input func */
  {52U, 0U},
  /* INMUX settings for pad PORT69:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 5U},
  /* GTM_TIM1_7 input func */
  {15U, 5U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 5U},
  /* DSPI_0_SS_0 input func */
  {370U, 3U},
  /* DSPI_1_SS_1 input func */
  {373U, 2U},
  /* eMIOS_1_EMIOS24 input func */
  {56U, 1U},
  /* INMUX settings for pad PORT70:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 3U},
  /* GTM_TIM3_5 input func */
  {29U, 3U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 1U},
  /* INMUX settings for pad PORT71:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 3U},
  /* GTM_TIM3_6 input func */
  {30U, 3U},
  /* INMUX settings for pad PORT72:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 4U},
  /* GTM_TIM3_1 input func */
  {25U, 4U},
  /* DSPI_0_SS_0 input func */
  {370U, 1U},
  /* INMUX settings for pad PORT73:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 3U},
  /* GTM_TIM3_2 input func */
  {26U, 3U},
  /* DSPI_0_SIN_0 input func */
  {368U, 2U},
  /* INMUX settings for pad PORT74:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 6U},
  /* GTM_TIM1_6 input func */
  {14U, 6U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 6U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 2U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 1U},
  /* DSPI_5_SIN_5 input func */
  {383U, 15U},
  /* DSPI_12_SIN_12 input func */
  {404U, 2U},
  /* INMUX settings for pad PORT75:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 6U},
  /* GTM_TIM1_7 input func */
  {15U, 6U},
  /* INMUX settings for pad PORT76:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 5U},
  /* GTM_TIM3_1 input func */
  {25U, 5U},
  /* SENT_0_SENTRX3_0 input func */
  {279U, 4U},
  /* INMUX settings for pad PORT80:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 3U},
  /* GTM_TIM1_1 input func */
  {9U, 3U},
  /* SDADC_0_EXT_CLKIN0 input func */
  {65U, 2U},
  /* SENT_1_SENTRX1_1 input func */
  {281U, 2U},
  /* PSI5_1_SDIN0_PSI5_1 input func */
  {312U, 3U},
  /* INMUX settings for pad PORT81:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 3U},
  /* GTM_TIM1_0 input func */
  {8U, 3U},
  /* SDADC_1_EXT_DATA1 input func */
  {66U, 2U},
  /* SENT_1_SENTRX4_1 input func */
  {285U, 2U},
  /* ETPU_1_ETPU1_31 input func */
  {452U, 0U},
  /* INMUX settings for pad PORT82:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 8U},
  /* GTM_TIM1_3 input func */
  {11U, 8U},
  /* PSI5_0_SDIN2_PSI5_0 input func */
  {316U, 1U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 6U},
  /* DSPI_3_SIN_3 input func */
  {377U, 3U},
  /* DSPI_5_SIN_5 input func */
  {383U, 12U},
  /* DSPI_12_SIN_12 input func */
  {404U, 4U},
  /* DSPI_12_SCK_12 input func */
  {405U, 2U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 7U},
  /* INMUX settings for pad PORT83:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 9U},
  /* GTM_TIM1_2 input func */
  {10U, 9U},
  /* M_CAN_4_MCAN4RX input func */
  {249U, 1U},
  /* DSPI_4_DSI0 input func */
  {144U, 4U},
  /* DSPI_4_DSI1 input func */
  {145U, 4U},
  /* DSPI_4_DSI2 input func */
  {146U, 4U},
  /* DSPI_4_DSI3 input func */
  {147U, 4U},
  /* DSPI_4_DSI4 input func */
  {148U, 4U},
  /* DSPI_4_DSI5 input func */
  {149U, 4U},
  /* DSPI_4_DSI6 input func */
  {150U, 4U},
  /* DSPI_4_DSI7 input func */
  {151U, 4U},
  /* DSPI_4_DSI8 input func */
  {152U, 4U},
  /* DSPI_4_DSI9 input func */
  {153U, 4U},
  /* DSPI_4_DSI10 input func */
  {154U, 4U},
  /* DSPI_4_DSI11 input func */
  {155U, 4U},
  /* DSPI_4_DSI12 input func */
  {156U, 4U},
  /* DSPI_4_DSI13 input func */
  {157U, 4U},
  /* DSPI_4_DSI14 input func */
  {158U, 4U},
  /* DSPI_4_DSI15 input func */
  {159U, 4U},
  /* DSPI_4_DSI16 input func */
  {160U, 4U},
  /* DSPI_4_DSI17 input func */
  {161U, 4U},
  /* DSPI_4_DSI18 input func */
  {162U, 4U},
  /* DSPI_4_DSI19 input func */
  {163U, 4U},
  /* DSPI_4_DSI20 input func */
  {164U, 4U},
  /* DSPI_4_DSI21 input func */
  {165U, 4U},
  /* DSPI_4_DSI22 input func */
  {166U, 4U},
  /* DSPI_4_DSI23 input func */
  {167U, 4U},
  /* DSPI_4_DSI24 input func */
  {168U, 4U},
  /* DSPI_4_DSI25 input func */
  {169U, 4U},
  /* DSPI_4_DSI26 input func */
  {170U, 4U},
  /* DSPI_4_DSI27 input func */
  {171U, 4U},
  /* DSPI_4_DSI28 input func */
  {172U, 4U},
  /* DSPI_4_DSI29 input func */
  {173U, 4U},
  /* DSPI_4_DSI30 input func */
  {174U, 4U},
  /* DSPI_4_DSI31 input func */
  {175U, 4U},
  /* DSPI_5_DSI0 input func */
  {176U, 4U},
  /* DSPI_5_DSI1 input func */
  {177U, 4U},
  /* DSPI_5_DSI2 input func */
  {178U, 4U},
  /* DSPI_5_DSI3 input func */
  {179U, 4U},
  /* DSPI_5_DSI4 input func */
  {180U, 4U},
  /* DSPI_5_DSI5 input func */
  {181U, 4U},
  /* DSPI_5_DSI6 input func */
  {182U, 4U},
  /* DSPI_5_DSI7 input func */
  {183U, 4U},
  /* DSPI_5_DSI8 input func */
  {184U, 4U},
  /* DSPI_5_DSI9 input func */
  {185U, 4U},
  /* DSPI_5_DSI10 input func */
  {186U, 4U},
  /* DSPI_5_DSI11 input func */
  {187U, 4U},
  /* DSPI_5_DSI12 input func */
  {188U, 4U},
  /* DSPI_5_DSI13 input func */
  {189U, 4U},
  /* DSPI_5_DSI14 input func */
  {190U, 4U},
  /* DSPI_5_DSI15 input func */
  {191U, 4U},
  /* DSPI_5_DSI16 input func */
  {192U, 4U},
  /* DSPI_5_DSI17 input func */
  {193U, 4U},
  /* DSPI_5_DSI18 input func */
  {194U, 4U},
  /* DSPI_5_DSI19 input func */
  {195U, 4U},
  /* DSPI_5_DSI20 input func */
  {196U, 4U},
  /* DSPI_5_DSI21 input func */
  {197U, 4U},
  /* DSPI_5_DSI22 input func */
  {198U, 4U},
  /* DSPI_5_DSI23 input func */
  {199U, 4U},
  /* DSPI_5_DSI24 input func */
  {200U, 4U},
  /* DSPI_5_DSI25 input func */
  {201U, 4U},
  /* DSPI_5_DSI26 input func */
  {202U, 4U},
  /* DSPI_5_DSI27 input func */
  {203U, 4U},
  /* DSPI_5_DSI28 input func */
  {204U, 4U},
  /* DSPI_5_DSI29 input func */
  {205U, 4U},
  /* DSPI_5_DSI30 input func */
  {206U, 4U},
  /* DSPI_5_DSI31 input func */
  {207U, 4U},
  /* DSPI_3_SS_3 input func */
  {379U, 2U},
  /* eMIOS_1_EMIOS25 input func */
  {57U, 1U},
  /* INMUX settings for pad PORT84:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 9U},
  /* GTM_TIM1_1 input func */
  {9U, 9U},
  /* DSPI_1_SIN_1 input func */
  {371U, 3U},
  /* ETPU_1_ETPU1_24 input func */
  {445U, 0U},
  /* INMUX settings for pad PORT85:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 8U},
  /* GTM_TIM1_2 input func */
  {10U, 8U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 6U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 5U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 3U},
  /* DSPI_1_SCK_1 input func */
  {372U, 2U},
  /* DSPI_4_SS_4 input func */
  {382U, 9U},
  /* ETPU_3_ETPU3_11 input func */
  {496U, 0U},
  /* INMUX settings for pad PORT86:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 2U},
  /* GTM_TIM3_2 input func */
  {26U, 2U},
  /* ETPU_1_ETPU1_25 input func */
  {446U, 0U},
  /* INMUX settings for pad PORT87:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 2U},
  /* GTM_TIM3_3 input func */
  {27U, 2U},
  /* ETPU_1_ETPU1_26 input func */
  {447U, 0U},
  /* INMUX settings for pad PORT88:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 3U},
  /* GTM_TIM1_6 input func */
  {14U, 3U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 5U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 3U},
  /* ETPU_1_ETPU1_27 input func */
  {448U, 0U},
  /* INMUX settings for pad PORT89:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 5U},
  /* GTM_TIM1_1 input func */
  {9U, 5U},
  /* DSPI_5_SIN_5 input func */
  {383U, 3U},
  /* DSPI_5_SCK_5 input func */
  {384U, 2U},
  /* INMUX settings for pad PORT90:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 5U},
  /* GTM_TIM1_0 input func */
  {8U, 5U},
  /* DSPI_5_SIN_5 input func */
  {383U, 4U},
  /* DSPI_5_SCK_5 input func */
  {384U, 4U},
  /* INMUX settings for pad PORT91:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 5U},
  /* GTM_TIM1_3 input func */
  {11U, 5U},
  /* DSPI_5_SIN_5 input func */
  {383U, 5U},
  /* DSPI_5_SS_5 input func */
  {385U, 2U},
  /* M_CAN_3_MCAN3RX input func */
  {248U, 6U},
  /* INMUX settings for pad PORT92:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 5U},
  /* GTM_TIM1_4 input func */
  {12U, 5U},
  /* DSPI_5_SCK_5 input func */
  {384U, 3U},
  /* INMUX settings for pad PORT93:      {INMUX reg, PADSEL val} */
  /* DSPI_5_SIN_5 input func */
  {383U, 7U},
  /* DSPI_2_SIN_2 input func */
  {374U, 1U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 10U},
  /* GTM_TIM0_0 input func */
  {0U, 6U},
  /* GTM_TIM1_0 input func */
  {8U, 6U},
  /* DSPI_1_SIN_1 input func */
  {371U, 7U},
  /* DSPI_4_SIN_4 input func */
  {380U, 7U},
  /* SIUL_2_IRQ6 input func */
  {273U, 0U},
  /* INMUX settings for pad PORT94:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 5U},
  /* GTM_TIM1_6 input func */
  {14U, 5U},
  /* M_CAN_3_MCAN3RX input func */
  {248U, 3U},
  /* INMUX settings for pad PORT95:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 3U},
  /* GTM_TIM3_4 input func */
  {28U, 3U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 5U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 7U},
  /* ETPU_1_ETPU1_28 input func */
  {449U, 0U},
  /* INMUX settings for pad PORT96:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 2U},
  /* GTM_TIM1_1 input func */
  {9U, 2U},
  /* SDADC_1_EXT_DATA1 input func */
  {66U, 1U},
  /* SENT_1_SENTRX2_1 input func */
  {282U, 1U},
  /* DSPI_4_SIN_4 input func */
  {380U, 3U},
  /* ETPU_1_ETPU1_26 input func */
  {447U, 1U},
  /* eMIOS_0_EMIOS21 input func */
  {53U, 0U},
  /* INMUX settings for pad PORT101:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX1_0 input func */
  {277U, 3U},
  /* INMUX settings for pad PORT102:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX0_0 input func */
  {276U, 3U},
  /* INMUX settings for pad PORT109:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 2U},
  /* GTM_TIM3_6 input func */
  {30U, 2U},
  /* DSPI_0_SS_0 input func */
  {370U, 2U},
  /* DSPI_2_SS_2 input func */
  {376U, 2U},
  /* DSPI_4_SS_4 input func */
  {382U, 3U},
  /* INMUX settings for pad PORT110:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 2U},
  /* GTM_TIM3_7 input func */
  {31U, 2U},
  /* M_TTCAN_0_TTCAN_0_RX input func */
  {240U, 2U},
  /* INMUX settings for pad PORT111:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 5U},
  /* GTM_TIM3_0 input func */
  {24U, 5U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 3U},
  /* DSPI_2_SIN_2 input func */
  {374U, 3U},
  /* DSPI_4_SS_4 input func */
  {382U, 10U},
  /* INMUX settings for pad PORT112:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 7U},
  /* GTM_TIM1_1 input func */
  {9U, 7U},
  /* DSPI_2_SIN_2 input func */
  {374U, 4U},
  /* INMUX settings for pad PORT113:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 7U},
  /* GTM_TIM1_2 input func */
  {10U, 7U},
  /* DSPI_2_SCK_2 input func */
  {375U, 2U},
  /* ETPU_3_ETPU3_10 input func */
  {495U, 0U},
  /* SENT_1_SENTRX5_1 input func */
  {289U, 6U},
  /* INMUX settings for pad PORT114:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 6U},
  /* GTM_TIM1_5 input func */
  {13U, 6U},
  /* DSPI_12_SCK_12 input func */
  {405U, 3U},
  /* eMIOS_1_EMIOS29 input func */
  {61U, 0U},
  /* INMUX settings for pad PORT115:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 7U},
  /* GTM_TIM1_0 input func */
  {8U, 7U},
  /* DSPI_2_SIN_2 input func */
  {374U, 11U},
  /* DSPI_12_SS_12 input func */
  {406U, 2U},
  /* INMUX settings for pad PORT116:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 8U},
  /* GTM_TIM1_1 input func */
  {9U, 8U},
  /* eMIOS_1_EMIOS30 input func */
  {62U, 0U},
  /* INMUX settings for pad PORT117:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 4U},
  /* GTM_TIM1_7 input func */
  {15U, 4U},
  /* DSPI_5_SS_5 input func */
  {385U, 3U},
  /* INMUX settings for pad PORT118:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 5U},
  /* GTM_TIM1_2 input func */
  {10U, 5U},
  /* INMUX settings for pad PORT119:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 15U},
  /* GTM_TIM2_4 input func */
  {20U, 5U},
  /* GTM_TIM3_4 input func */
  {28U, 5U},
  /* DSPI_0_SS_0 input func */
  {370U, 4U},
  /* DSPI_1_SIN_1 input func */
  {371U, 8U},
  /* DSPI_2_SIN_2 input func */
  {374U, 9U},
  /* DSPI_4_SS_4 input func */
  {382U, 5U},
  /* INMUX settings for pad PORT120:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 15U},
  /* GTM_TIM2_3 input func */
  {19U, 5U},
  /* GTM_TIM3_3 input func */
  {27U, 5U},
  /* DSPI_1_SCK_1 input func */
  {372U, 3U},
  /* DSPI_2_SIN_2 input func */
  {374U, 10U},
  /* INMUX settings for pad PORT121:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 4U},
  /* GTM_TIM2_3 input func */
  {19U, 15U},
  /* GTM_TIM3_2 input func */
  {26U, 4U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 5U},
  /* FlexRay_0_RXDA_0 input func */
  {260U, 3U},
  /* FlexRay_1_RXDA_1 input func */
  {264U, 2U},
  /* LINFlexD_1_LIN1RX input func */
  {337U, 4U},
  /* DSPI_1_SIN_1 input func */
  {371U, 5U},
  /* INMUX settings for pad PORT122:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 8U},
  /* GTM_TIM1_0 input func */
  {8U, 8U},
  /* FlexRay_0_RXDB_0 input func */
  {261U, 3U},
  /* FlexRay_1_RXDB_1 input func */
  {265U, 2U},
  /* M_CAN_6_MCAN6RX input func */
  {251U, 1U},
  /* INMUX settings for pad PORT123:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 3U},
  /* GTM_TIM3_3 input func */
  {27U, 3U},
  /* INMUX settings for pad PORT124:      {INMUX reg, PADSEL val} */
  /* DSPI_3_SCK_3 input func */
  {378U, 2U},
  /* GTM_TIM0_5 input func */
  {5U, 7U},
  /* GTM_TIM1_5 input func */
  {13U, 7U},
  /* M_CAN_4_MCAN4RX input func */
  {249U, 2U},
  /* INMUX settings for pad PORT125:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 9U},
  /* GTM_TIM1_0 input func */
  {8U, 9U},
  /* DSPI_3_SIN_3 input func */
  {377U, 4U},
  /* DSPI_5_SIN_5 input func */
  {383U, 8U},
  /* ETPU_3_ETPU3_13 input func */
  {498U, 0U},
  /* INMUX settings for pad PORT126:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 7U},
  /* GTM_TIM1_6 input func */
  {14U, 7U},
  /* DSPI_0_SS_0 input func */
  {370U, 7U},
  /* DSPI_1_SIN_1 input func */
  {371U, 4U},
  /* DSPI_1_SS_1 input func */
  {373U, 3U},
  /* DSPI_4_SS_4 input func */
  {382U, 8U},
  /* INMUX settings for pad PORT127:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 8U},
  /* GTM_TIM1_4 input func */
  {12U, 8U},
  /* eMIOS_1_EMIOS26 input func */
  {58U, 1U},
  /* INMUX settings for pad PORT128:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX1_1 input func */
  {281U, 3U},
  /* INMUX settings for pad PORT129:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX0_1 input func */
  {280U, 3U},
  /* INMUX settings for pad PORT132:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX3_0 input func */
  {279U, 3U},
  /* ETPU_3_ETPU3_9 input func */
  {494U, 1U},
  /* eMIOS_1_EMIOS30 input func */
  {62U, 1U},
  /* LINFlexD_3_LIN3RX input func */
  {339U, 2U},
  /* INMUX settings for pad PORT133:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX2_0 input func */
  {278U, 3U},
  /* ETPU_3_ETPU3_8 input func */
  {493U, 1U},
  /* eMIOS_1_EMIOS31 input func */
  {63U, 0U},
  /* LINFlexD_4_LIN4RX input func */
  {340U, 2U},
  /* INMUX settings for pad PORT136:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 2U},
  /* GTM_TIM1_2 input func */
  {10U, 2U},
  /* GTM_TIM2_2 input func */
  {18U, 11U},
  /* SDADC_0_EXT_CLKIN0 input func */
  {65U, 1U},
  /* DSPI_4_SIN_4 input func */
  {380U, 4U},
  /* ETPU_1_ETPU1_25 input func */
  {446U, 1U},
  /* eMIOS_0_EMIOS22 input func */
  {54U, 0U},
  /* INMUX settings for pad PORT137:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 2U},
  /* GTM_TIM1_3 input func */
  {11U, 2U},
  /* SDADC_0_EXT_DATA0 input func */
  {64U, 1U},
  /* DSPI_4_SCK_4 input func */
  {381U, 2U},
  /* ETPU_1_ETPU1_24 input func */
  {445U, 1U},
  /* eMIOS_0_EMIOS23 input func */
  {55U, 0U},
  /* LINFlexD_3_LIN3RX input func */
  {339U, 0U},
  /* INMUX settings for pad PORT138:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 2U},
  /* GTM_TIM1_7 input func */
  {15U, 2U},
  /* SDADC_1_EXT_CLKIN1 input func */
  {67U, 2U},
  /* SENT_1_SENTRX3_1 input func */
  {283U, 2U},
  /* PSI5_0_SDIN1_PSI5_0 input func */
  {308U, 3U},
  /* ETPU_3_ETPU3_8 input func */
  {493U, 0U},
  /* INMUX settings for pad PORT139:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 2U},
  /* GTM_TIM1_6 input func */
  {14U, 2U},
  /* SDADC_2_EXT_DATA2 input func */
  {68U, 2U},
  /* SENT_0_SENTRX4_0 input func */
  {284U, 2U},
  /* INMUX settings for pad PORT140:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 2U},
  /* GTM_TIM1_5 input func */
  {13U, 2U},
  /* SDADC_2_EXT_CLKIN2 input func */
  {69U, 2U},
  /* SENT_1_SENTRX2_1 input func */
  {282U, 2U},
  /* PSI5_0_SDIN0_PSI5_0 input func */
  {304U, 3U},
  /* PSI5_S_RX_PSI5_S input func */
  {331U, 1U},
  /* DSPI_2_SCK_2 input func */
  {375U, 4U},
  /* INMUX settings for pad PORT141:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 2U},
  /* GTM_TIM1_4 input func */
  {12U, 2U},
  /* INMUX settings for pad PORT142:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 2U},
  /* GTM_TIM3_4 input func */
  {28U, 2U},
  /* DSPI_5_SIN_5 input func */
  {383U, 16U},
  /* INMUX settings for pad PORT143:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 2U},
  /* GTM_TIM3_5 input func */
  {29U, 2U},
  /* DSPI_5_SIN_5 input func */
  {383U, 17U},
  /* INMUX settings for pad PORT144:      {INMUX reg, PADSEL val} */
  /* M_CAN_5_MCAN5RX input func */
  {250U, 1U},
  /* GTM_TIM0_3 input func */
  {3U, 4U},
  /* GTM_TIM1_3 input func */
  {11U, 4U},
  /* M_CAN_3_MCAN3RX input func */
  {248U, 2U},
  /* LINFlexD_14_LIN14RX input func */
  {350U, 4U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 8U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 12U},
  /* INMUX settings for pad PORT145:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 4U},
  /* GTM_TIM1_4 input func */
  {12U, 4U},
  /* INMUX settings for pad PORT146:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 4U},
  /* GTM_TIM1_5 input func */
  {13U, 4U},
  /* INMUX settings for pad PORT147:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 4U},
  /* GTM_TIM1_6 input func */
  {14U, 4U},
  /* LINFlexD_15_LIN15RX input func */
  {351U, 4U},
  /* M_CAN_7_MCAN7RX input func */
  {252U, 1U},
  /* INMUX settings for pad PORT148:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 3U},
  /* GTM_TIM1_7 input func */
  {15U, 3U},
  /* DSPI_4_DSI0 input func */
  {144U, 5U},
  /* DSPI_4_DSI1 input func */
  {145U, 5U},
  /* DSPI_4_DSI2 input func */
  {146U, 5U},
  /* DSPI_4_DSI3 input func */
  {147U, 5U},
  /* DSPI_4_DSI4 input func */
  {148U, 5U},
  /* DSPI_4_DSI5 input func */
  {149U, 5U},
  /* DSPI_4_DSI6 input func */
  {150U, 5U},
  /* DSPI_4_DSI7 input func */
  {151U, 5U},
  /* DSPI_4_DSI8 input func */
  {152U, 5U},
  /* DSPI_4_DSI9 input func */
  {153U, 5U},
  /* DSPI_4_DSI10 input func */
  {154U, 5U},
  /* DSPI_4_DSI11 input func */
  {155U, 5U},
  /* DSPI_4_DSI12 input func */
  {156U, 5U},
  /* DSPI_4_DSI13 input func */
  {157U, 5U},
  /* DSPI_4_DSI14 input func */
  {158U, 5U},
  /* DSPI_4_DSI15 input func */
  {159U, 5U},
  /* DSPI_4_DSI16 input func */
  {160U, 5U},
  /* DSPI_4_DSI17 input func */
  {161U, 5U},
  /* DSPI_4_DSI18 input func */
  {162U, 5U},
  /* DSPI_4_DSI19 input func */
  {163U, 5U},
  /* DSPI_4_DSI20 input func */
  {164U, 5U},
  /* DSPI_4_DSI21 input func */
  {165U, 5U},
  /* DSPI_4_DSI22 input func */
  {166U, 5U},
  /* DSPI_4_DSI23 input func */
  {167U, 5U},
  /* DSPI_4_DSI24 input func */
  {168U, 5U},
  /* DSPI_4_DSI25 input func */
  {169U, 5U},
  /* DSPI_4_DSI26 input func */
  {170U, 5U},
  /* DSPI_4_DSI27 input func */
  {171U, 5U},
  /* DSPI_4_DSI28 input func */
  {172U, 5U},
  /* DSPI_4_DSI29 input func */
  {173U, 5U},
  /* DSPI_4_DSI30 input func */
  {174U, 5U},
  /* DSPI_4_DSI31 input func */
  {175U, 5U},
  /* DSPI_5_DSI0 input func */
  {176U, 5U},
  /* DSPI_5_DSI1 input func */
  {177U, 5U},
  /* DSPI_5_DSI2 input func */
  {178U, 5U},
  /* DSPI_5_DSI3 input func */
  {179U, 5U},
  /* DSPI_5_DSI4 input func */
  {180U, 5U},
  /* DSPI_5_DSI5 input func */
  {181U, 5U},
  /* DSPI_5_DSI6 input func */
  {182U, 5U},
  /* DSPI_5_DSI7 input func */
  {183U, 5U},
  /* DSPI_5_DSI8 input func */
  {184U, 5U},
  /* DSPI_5_DSI9 input func */
  {185U, 5U},
  /* DSPI_5_DSI10 input func */
  {186U, 5U},
  /* DSPI_5_DSI11 input func */
  {187U, 5U},
  /* DSPI_5_DSI12 input func */
  {188U, 5U},
  /* DSPI_5_DSI13 input func */
  {189U, 5U},
  /* DSPI_5_DSI14 input func */
  {190U, 5U},
  /* DSPI_5_DSI15 input func */
  {191U, 5U},
  /* DSPI_5_DSI16 input func */
  {192U, 5U},
  /* DSPI_5_DSI17 input func */
  {193U, 5U},
  /* DSPI_5_DSI18 input func */
  {194U, 5U},
  /* DSPI_5_DSI19 input func */
  {195U, 5U},
  /* DSPI_5_DSI20 input func */
  {196U, 5U},
  /* DSPI_5_DSI21 input func */
  {197U, 5U},
  /* DSPI_5_DSI22 input func */
  {198U, 5U},
  /* DSPI_5_DSI23 input func */
  {199U, 5U},
  /* DSPI_5_DSI24 input func */
  {200U, 5U},
  /* DSPI_5_DSI25 input func */
  {201U, 5U},
  /* DSPI_5_DSI26 input func */
  {202U, 5U},
  /* DSPI_5_DSI27 input func */
  {203U, 5U},
  /* DSPI_5_DSI28 input func */
  {204U, 5U},
  /* DSPI_5_DSI29 input func */
  {205U, 5U},
  /* DSPI_5_DSI30 input func */
  {206U, 5U},
  /* DSPI_5_DSI31 input func */
  {207U, 5U},
  /* INMUX settings for pad PORT149:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_7 input func */
  {31U, 8U},
  /* GTM_TIM5_7 input func */
  {47U, 8U},
  /* INMUX settings for pad PORT150:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_5 input func */
  {29U, 8U},
  /* GTM_TIM5_5 input func */
  {45U, 9U},
  /* M_TTCAN_1_TTCAN_1_RX input func */
  {254U, 1U},
  /* INMUX settings for pad PORT151:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_6 input func */
  {30U, 8U},
  /* GTM_TIM5_6 input func */
  {46U, 8U},
  /* M_CAN_2_MCAN2RX input func */
  {247U, 7U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 3U},
  /* DSPI_12_SIN_12 input func */
  {404U, 5U},
  /* INMUX settings for pad PORT152:      {INMUX reg, PADSEL val} */
  /* GTM_TIM1_3 input func */
  {11U, 9U},
  /* GTM_TIM4_3 input func */
  {35U, 10U},
  /* M_TTCAN_1_TTCAN_1_RX input func */
  {254U, 2U},
  /* INMUX settings for pad PORT153:      {INMUX reg, PADSEL val} */
  /* GTM_TIM1_2 input func */
  {10U, 10U},
  /* GTM_TIM4_2 input func */
  {34U, 10U},
  /* INMUX settings for pad PORT154:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_0 input func */
  {24U, 8U},
  /* M_TTCAN_1_TTCAN_1_RX input func */
  {254U, 3U},
  /* INMUX settings for pad PORT155:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_1 input func */
  {25U, 7U},
  /* PSI5_1_SDIN1_PSI5_1 input func */
  {320U, 1U},
  /* DSPI_0_SIN_0 input func */
  {368U, 3U},
  /* INMUX settings for pad PORT156:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_3 input func */
  {27U, 7U},
  /* DSPI_0_SCK_0 input func */
  {369U, 2U},
  /* M_TTCAN_1_TTCAN_1_RX input func */
  {254U, 4U},
  /* INMUX settings for pad PORT157:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_2 input func */
  {26U, 6U},
  /* DSPI_0_SIN_0 input func */
  {368U, 4U},
  /* INMUX settings for pad PORT158:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_5 input func */
  {29U, 7U},
  /* DSPI_0_SIN_0 input func */
  {368U, 5U},
  /* INMUX settings for pad PORT159:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_4 input func */
  {28U, 7U},
  /* DSPI_0_SCK_0 input func */
  {369U, 3U},
  /* INMUX settings for pad PORT172:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_7 input func */
  {31U, 7U},
  /* INMUX settings for pad PORT173:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_6 input func */
  {30U, 7U},
  /* DSPI_0_SIN_0 input func */
  {368U, 6U},
  /* INMUX settings for pad PORT174:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 8U},
  /* GTM_TIM4_3 input func */
  {35U, 9U},
  /* INMUX settings for pad PORT175:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 7U},
  /* GTM_TIM4_4 input func */
  {36U, 8U},
  /* FEC_FEC_RXD3 input func */
  {418U, 1U},
  /* SENT_1_SENTRX2_1 input func */
  {282U, 4U},
  /* INMUX settings for pad PORT176:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 9U},
  /* GTM_TIM4_3 input func */
  {35U, 8U},
  /* M_CAN_1_MCAN1RX input func */
  {246U, 4U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 10U},
  /* LINFlexD_2_LIN2RX input func */
  {338U, 4U},
  /* DSPI_12_SIN_12 input func */
  {404U, 6U},
  /* INMUX settings for pad PORT177:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 10U},
  /* GTM_TIM4_2 input func */
  {34U, 8U},
  /* INMUX settings for pad PORT178:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 7U},
  /* GTM_TIM4_7 input func */
  {39U, 8U},
  /* INMUX settings for pad PORT179:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 8U},
  /* GTM_TIM4_6 input func */
  {38U, 8U},
  /* M_CAN_1_MCAN1RX input func */
  {246U, 3U},
  /* INMUX settings for pad PORT180:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 8U},
  /* GTM_TIM4_5 input func */
  {37U, 8U},
  /* DSPI_3_SS_3 input func */
  {379U, 3U},
  /* INMUX settings for pad PORT181:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 7U},
  /* GTM_TIM5_3 input func */
  {43U, 8U},
  /* DSPI_3_SIN_3 input func */
  {377U, 5U},
  /* INMUX settings for pad PORT182:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 7U},
  /* GTM_TIM5_5 input func */
  {45U, 8U},
  /* DSPI_3_SIN_3 input func */
  {377U, 6U},
  /* INMUX settings for pad PORT183:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 7U},
  /* GTM_TIM5_7 input func */
  {47U, 7U},
  /* DSPI_3_SCK_3 input func */
  {378U, 3U},
  /* INMUX settings for pad PORT184:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 7U},
  /* GTM_TIM5_2 input func */
  {42U, 8U},
  /* INMUX settings for pad PORT185:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 9U},
  /* GTM_TIM5_3 input func */
  {43U, 9U},
  /* INMUX settings for pad PORT186:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 8U},
  /* GTM_TIM5_4 input func */
  {44U, 8U},
  /* M_CAN_4_MCAN4RX input func */
  {249U, 3U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 7U},
  /* ETPU_3_ETPU3_15 input func */
  {500U, 0U},
  /* INMUX settings for pad PORT187:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 9U},
  /* GTM_TIM5_5 input func */
  {45U, 10U},
  /* ETPU_1_ETPU1_29 input func */
  {450U, 0U},
  /* INMUX settings for pad PORT188:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 8U},
  /* GTM_TIM5_6 input func */
  {46U, 9U},
  /* DSPI_2_SIN_2 input func */
  {374U, 7U},
  /* SENT_1_SENTRX3_1 input func */
  {283U, 4U},
  /* INMUX settings for pad PORT189:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 9U},
  /* GTM_TIM5_7 input func */
  {47U, 9U},
  /* DSPI_2_SIN_2 input func */
  {374U, 8U},
  /* INMUX settings for pad PORT190:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 8U},
  /* GTM_TIM5_0 input func */
  {40U, 9U},
  /* DSPI_2_SCK_2 input func */
  {375U, 3U},
  /* SENT_1_SENTRX4_1 input func */
  {285U, 4U},
  /* INMUX settings for pad PORT191:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 7U},
  /* GTM_TIM5_1 input func */
  {41U, 9U},
  /* ETPU_1_ETPU1_30 input func */
  {451U, 0U},
  /* INMUX settings for pad PORT192:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 8U},
  /* GTM_TIM4_7 input func */
  {39U, 9U},
  /* I2C_1_SCL1 input func */
  {299U, 1U},
  /* FEC_FEC_RXDV input func */
  {413U, 2U},
  /* FEC_FEC_CRS input func */
  {414U, 2U},
  /* SENT_0_SENTRX1_0 input func */
  {277U, 4U},
  /* INMUX settings for pad PORT193:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 8U},
  /* GTM_TIM4_5 input func */
  {37U, 9U},
  /* INMUX settings for pad PORT194:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 8U},
  /* GTM_TIM4_7 input func */
  {39U, 10U},
  /* FEC_FEC_COL input func */
  {419U, 1U},
  /* INMUX settings for pad PORT195:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 7U},
  /* GTM_TIM4_6 input func */
  {38U, 9U},
  /* I2C_1_SDA1 input func */
  {298U, 1U},
  /* FEC_FEC_RXER input func */
  {420U, 1U},
  /* INMUX settings for pad PORT196:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 6U},
  /* GTM_TIM4_1 input func */
  {33U, 9U},
  /* LINFlexD_3_LIN3RX input func */
  {339U, 1U},
  /* INMUX settings for pad PORT197:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 7U},
  /* GTM_TIM4_0 input func */
  {32U, 9U},
  /* ETPU_3_ETPU3_14 input func */
  {499U, 0U},
  /* INMUX settings for pad PORT198:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 6U},
  /* GTM_TIM4_2 input func */
  {34U, 9U},
  /* FEC_FEC_RXCLK input func */
  {410U, 3U},
  /* LINFlexD_4_LIN4RX input func */
  {340U, 1U},
  /* INMUX settings for pad PORT199:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_1 input func */
  {25U, 6U},
  /* GTM_TIM4_1 input func */
  {33U, 10U},
  /* FEC_FEC_MDIO input func */
  {412U, 3U},
  /* DSPI_4_SIN_4 input func */
  {380U, 5U},
  /* INMUX settings for pad PORT200:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_0 input func */
  {24U, 7U},
  /* GTM_TIM4_0 input func */
  {32U, 10U},
  /* M_TTCAN_0_TTCAN_0_RX input func */
  {240U, 3U},
  /* INMUX settings for pad PORT201:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 10U},
  /* GTM_TIM1_0 input func */
  {8U, 10U},
  /* DSPI_5_SS_5 input func */
  {385U, 5U},
  /* LINFlexD_5_LIN5RX input func */
  {341U, 1U},
  /* INMUX settings for pad PORT202:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 10U},
  /* GTM_TIM1_3 input func */
  {11U, 10U},
  /* DSPI_0_SS_0 input func */
  {370U, 6U},
  /* DSPI_1_SIN_1 input func */
  {371U, 9U},
  /* DSPI_4_SS_4 input func */
  {382U, 7U},
  /* ETPU_3_ETPU3_12 input func */
  {497U, 0U},
  /* INMUX settings for pad PORT203:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_1 input func */
  {1U, 10U},
  /* GTM_TIM4_1 input func */
  {33U, 8U},
  /* SENT_0_SENTRX5_0 input func */
  {286U, 2U},
  /* ETPU_3_TCRCLKC input func */
  {501U, 1U},
  /* LINFlexD_7_LIN7RX input func */
  {343U, 2U},
  /* INMUX settings for pad PORT204:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_2 input func */
  {2U, 11U},
  /* GTM_TIM4_2 input func */
  {34U, 7U},
  /* SENT_0_SENTRX6_0 input func */
  {287U, 2U},
  /* LINFlexD_6_LIN6RX input func */
  {342U, 1U},
  /* INMUX settings for pad PORT205:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_7 input func */
  {7U, 9U},
  /* GTM_TIM4_7 input func */
  {39U, 7U},
  /* INMUX settings for pad PORT206:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_3 input func */
  {3U, 11U},
  /* GTM_TIM4_3 input func */
  {35U, 7U},
  /* SENT_0_SENTRX7_0 input func */
  {288U, 2U},
  /* INMUX settings for pad PORT207:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_4 input func */
  {4U, 9U},
  /* GTM_TIM4_4 input func */
  {36U, 7U},
  /* SENT_1_SENTRX5_1 input func */
  {289U, 2U},
  /* INMUX settings for pad PORT208:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_5 input func */
  {5U, 9U},
  /* GTM_TIM4_5 input func */
  {37U, 7U},
  /* SENT_1_SENTRX6_1 input func */
  {290U, 1U},
  /* INMUX settings for pad PORT209:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_0 input func */
  {32U, 1U},
  /* GTM_TIM5_0 input func */
  {40U, 1U},
  /* INMUX settings for pad PORT210:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_2 input func */
  {34U, 1U},
  /* GTM_TIM5_2 input func */
  {42U, 6U},
  /* LINFlexD_7_LIN7RX input func */
  {343U, 1U},
  /* INMUX settings for pad PORT211:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_3 input func */
  {35U, 1U},
  /* GTM_TIM5_3 input func */
  {43U, 1U},
  /* M_CAN_4_MCAN4RX input func */
  {249U, 4U},
  /* eMIOS_0_EMIOS17 input func */
  {49U, 1U},
  /* INMUX settings for pad PORT212:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_1 input func */
  {33U, 1U},
  /* GTM_TIM5_1 input func */
  {41U, 1U},
  /* LINFlexD_8_LIN8RX input func */
  {344U, 1U},
  /* INMUX settings for pad PORT213:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_4 input func */
  {36U, 1U},
  /* GTM_TIM5_4 input func */
  {44U, 1U},
  /* M_CAN_3_MCAN3RX input func */
  {248U, 4U},
  /* INMUX settings for pad PORT214:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_1 input func */
  {33U, 2U},
  /* GTM_TIM5_1 input func */
  {41U, 2U},
  /* FlexRay_1_RXDA_1 input func */
  {264U, 1U},
  /* SENT_0_SENTRX5_0 input func */
  {286U, 3U},
  /* INMUX settings for pad PORT215:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_5 input func */
  {37U, 1U},
  /* GTM_TIM5_5 input func */
  {45U, 1U},
  /* SDADC_7_EXT_CLKIN7 input func */
  {79U, 1U},
  /* INMUX settings for pad PORT216:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_4 input func */
  {36U, 2U},
  /* GTM_TIM5_4 input func */
  {44U, 2U},
  /* M_CAN_4_MCAN4RX input func */
  {249U, 5U},
  /* FlexRay_1_RXDB_1 input func */
  {265U, 1U},
  /* SENT_0_SENTRX7_0 input func */
  {288U, 3U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 8U},
  /* M_CAN_8_MCAN8RX input func */
  {253U, 1U},
  /* INMUX settings for pad PORT217:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_2 input func */
  {34U, 2U},
  /* GTM_TIM5_2 input func */
  {42U, 1U},
  /* SENT_0_SENTRX6_0 input func */
  {287U, 3U},
  /* INMUX settings for pad PORT218:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_5 input func */
  {37U, 2U},
  /* GTM_TIM5_5 input func */
  {45U, 2U},
  /* SENT_1_SENTRX5_1 input func */
  {289U, 3U},
  /* INMUX settings for pad PORT219:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_7 input func */
  {39U, 1U},
  /* GTM_TIM5_7 input func */
  {47U, 1U},
  /* SENT_1_SENTRX6_1 input func */
  {290U, 2U},
  /* INMUX settings for pad PORT220:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_0 input func */
  {32U, 2U},
  /* GTM_TIM5_0 input func */
  {40U, 2U},
  /* DSPI_5_SCK_5 input func */
  {384U, 5U},
  /* INMUX settings for pad PORT221:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_3 input func */
  {35U, 2U},
  /* GTM_TIM5_3 input func */
  {43U, 2U},
  /* eMIOS_0_EMIOS16 input func */
  {48U, 1U},
  /* INMUX settings for pad PORT222:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_6 input func */
  {38U, 2U},
  /* GTM_TIM5_6 input func */
  {46U, 2U},
  /* INMUX settings for pad PORT223:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_6 input func */
  {38U, 1U},
  /* GTM_TIM5_6 input func */
  {46U, 1U},
  /* SDADC_7_EXT_DATA7 input func */
  {78U, 1U},
  /* INMUX settings for pad PORT224:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_7 input func */
  {39U, 2U},
  /* GTM_TIM5_7 input func */
  {47U, 2U},
  /* SDADC_6_EXT_CLKIN6 input func */
  {77U, 1U},
  /* INMUX settings for pad PORT225:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_0 input func */
  {32U, 3U},
  /* GTM_TIM5_0 input func */
  {40U, 3U},
  /* SDADC_6_EXT_DATA6 input func */
  {76U, 1U},
  /* M_CAN_8_MCAN8RX input func */
  {253U, 2U},
  /* INMUX settings for pad PORT226:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_1 input func */
  {33U, 3U},
  /* GTM_TIM5_1 input func */
  {41U, 3U},
  /* eMIOS_0_EMIOS18 input func */
  {50U, 1U},
  /* INMUX settings for pad PORT227:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_1 input func */
  {25U, 10U},
  /* GTM_TIM5_1 input func */
  {41U, 8U},
  /* eMIOS_0_EMIOS19 input func */
  {51U, 1U},
  /* INMUX settings for pad PORT228:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_4 input func */
  {28U, 10U},
  /* GTM_TIM5_4 input func */
  {44U, 7U},
  /* LINFlexD_16_LIN16RX input func */
  {352U, 1U},
  /* INMUX settings for pad PORT229:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_3 input func */
  {27U, 10U},
  /* GTM_TIM5_3 input func */
  {43U, 7U},
  /* eMIOS_0_EMIOS20 input func */
  {52U, 1U},
  /* INMUX settings for pad PORT230:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_2 input func */
  {26U, 9U},
  /* GTM_TIM5_2 input func */
  {42U, 7U},
  /* DSPI_6_SS_6 input func */
  {388U, 1U},
  /* eMIOS_0_EMIOS21 input func */
  {53U, 1U},
  /* INMUX settings for pad PORT231:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_6 input func */
  {30U, 11U},
  /* GTM_TIM5_6 input func */
  {46U, 7U},
  /* DSPI_6_DSI0 input func */
  {208U, 2U},
  /* DSPI_6_DSI1 input func */
  {209U, 2U},
  /* DSPI_6_DSI2 input func */
  {210U, 2U},
  /* DSPI_6_DSI3 input func */
  {211U, 2U},
  /* DSPI_6_DSI4 input func */
  {212U, 2U},
  /* DSPI_6_DSI5 input func */
  {213U, 2U},
  /* DSPI_6_DSI6 input func */
  {214U, 2U},
  /* DSPI_6_DSI7 input func */
  {215U, 2U},
  /* DSPI_6_DSI8 input func */
  {216U, 2U},
  /* DSPI_6_DSI9 input func */
  {217U, 2U},
  /* DSPI_6_DSI10 input func */
  {218U, 2U},
  /* DSPI_6_DSI11 input func */
  {219U, 2U},
  /* DSPI_6_DSI12 input func */
  {220U, 2U},
  /* DSPI_6_DSI13 input func */
  {221U, 2U},
  /* DSPI_6_DSI14 input func */
  {222U, 2U},
  /* DSPI_6_DSI15 input func */
  {223U, 2U},
  /* DSPI_6_DSI16 input func */
  {224U, 2U},
  /* DSPI_6_DSI17 input func */
  {225U, 2U},
  /* DSPI_6_DSI18 input func */
  {226U, 2U},
  /* DSPI_6_DSI19 input func */
  {227U, 2U},
  /* DSPI_6_DSI20 input func */
  {228U, 2U},
  /* DSPI_6_DSI21 input func */
  {229U, 2U},
  /* DSPI_6_DSI22 input func */
  {230U, 2U},
  /* DSPI_6_DSI23 input func */
  {231U, 2U},
  /* DSPI_6_DSI24 input func */
  {232U, 2U},
  /* DSPI_6_DSI25 input func */
  {233U, 2U},
  /* DSPI_6_DSI26 input func */
  {234U, 2U},
  /* DSPI_6_DSI27 input func */
  {235U, 2U},
  /* DSPI_6_DSI28 input func */
  {236U, 2U},
  /* DSPI_6_DSI29 input func */
  {237U, 2U},
  /* DSPI_6_DSI30 input func */
  {238U, 2U},
  /* DSPI_6_DSI31 input func */
  {239U, 2U},
  /* eMIOS_0_EMIOS22 input func */
  {54U, 1U},
  /* INMUX settings for pad PORT232:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_3 input func */
  {27U, 9U},
  /* GTM_TIM5_3 input func */
  {43U, 6U},
  /* PSI5_1_SDIN1_PSI5_1 input func */
  {320U, 2U},
  /* DSPI_6_SS_6 input func */
  {388U, 2U},
  /* eMIOS_0_EMIOS23 input func */
  {55U, 1U},
  /* INMUX settings for pad PORT233:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_4 input func */
  {28U, 9U},
  /* GTM_TIM5_4 input func */
  {44U, 6U},
  /* eMIOS_1_EMIOS27 input func */
  {59U, 1U},
  /* INMUX settings for pad PORT234:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_5 input func */
  {29U, 10U},
  /* GTM_TIM5_5 input func */
  {45U, 6U},
  /* eMIOS_1_EMIOS31 input func */
  {63U, 1U},
  /* INMUX settings for pad PORT235:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_6 input func */
  {30U, 10U},
  /* GTM_TIM5_6 input func */
  {46U, 6U},
  /* INMUX settings for pad PORT236:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_0 input func */
  {24U, 11U},
  /* GTM_TIM5_0 input func */
  {40U, 8U},
  /* INMUX settings for pad PORT237:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 11U},
  /* GTM_TIM4_7 input func */
  {39U, 6U},
  /* I2C_1_SCL1 input func */
  {299U, 2U},
  /* INMUX settings for pad PORT238:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_1 input func */
  {25U, 9U},
  /* GTM_TIM5_1 input func */
  {41U, 7U},
  /* PSI5_0_SDIN2_PSI5_0 input func */
  {316U, 2U},
  /* INMUX settings for pad PORT239:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_0 input func */
  {0U, 11U},
  /* GTM_TIM4_0 input func */
  {32U, 8U},
  /* M_CAN_3_MCAN3RX input func */
  {248U, 5U},
  /* I2C_1_SDA1 input func */
  {298U, 2U},
  /* LINFlexD_16_LIN16RX input func */
  {352U, 2U},
  /* INMUX settings for pad PORT240:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_2 input func */
  {26U, 8U},
  /* GTM_TIM5_2 input func */
  {42U, 5U},
  /* INMUX settings for pad PORT253:      {INMUX reg, PADSEL val} */
  /* ETPU_3_ETPU3_9 input func */
  {494U, 2U},
  /* SENT_1_SENTRX4_1 input func */
  {285U, 5U},
  /* INMUX settings for pad PORT254:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX7_0 input func */
  {288U, 4U},
  /* ETPU_3_ETPU3_3 input func */
  {488U, 1U},
  /* SENT_0_SENTRX4_0 input func */
  {284U, 4U},
  /* INMUX settings for pad PORT255:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX5_1 input func */
  {289U, 4U},
  /* ETPU_3_ETPU3_11 input func */
  {496U, 1U},
  /* eMIOS_1_EMIOS28 input func */
  {60U, 1U},
  /* INMUX settings for pad PORT256:      {INMUX reg, PADSEL val} */
  /* SENT_1_SENTRX6_1 input func */
  {290U, 3U},
  /* ETPU_3_ETPU3_10 input func */
  {495U, 1U},
  /* eMIOS_1_EMIOS29 input func */
  {61U, 1U},
  /* INMUX settings for pad PORT257:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 9U},
  /* ETPU_3_ETPU3_1 input func */
  {486U, 0U},
  /* INMUX settings for pad PORT258:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 8U},
  /* INMUX settings for pad PORT259:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 8U},
  /* INMUX settings for pad PORT260:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 10U},
  /* INMUX settings for pad PORT261:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 9U},
  /* INMUX settings for pad PORT262:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 10U},
  /* INMUX settings for pad PORT263:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 9U},
  /* INMUX settings for pad PORT264:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_7 input func */
  {23U, 10U},
  /* INMUX settings for pad PORT265:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_0 input func */
  {40U, 4U},
  /* INMUX settings for pad PORT266:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_1 input func */
  {41U, 4U},
  /* INMUX settings for pad PORT267:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_2 input func */
  {42U, 2U},
  /* INMUX settings for pad PORT268:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_3 input func */
  {43U, 3U},
  /* INMUX settings for pad PORT269:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_4 input func */
  {44U, 3U},
  /* INMUX settings for pad PORT270:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_5 input func */
  {45U, 3U},
  /* INMUX settings for pad PORT271:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_6 input func */
  {46U, 3U},
  /* INMUX settings for pad PORT272:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_7 input func */
  {47U, 3U},
  /* INMUX settings for pad PORT273:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_0 input func */
  {32U, 4U},
  /* INMUX settings for pad PORT274:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_1 input func */
  {33U, 4U},
  /* INMUX settings for pad PORT275:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_2 input func */
  {34U, 3U},
  /* INMUX settings for pad PORT276:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_3 input func */
  {35U, 3U},
  /* INMUX settings for pad PORT277:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_4 input func */
  {36U, 3U},
  /* INMUX settings for pad PORT278:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_5 input func */
  {37U, 3U},
  /* INMUX settings for pad PORT279:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_6 input func */
  {38U, 3U},
  /* INMUX settings for pad PORT280:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_7 input func */
  {39U, 3U},
  /* INMUX settings for pad PORT281:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_0 input func */
  {40U, 5U},
  /* INMUX settings for pad PORT282:      {INMUX reg, PADSEL val} */
  /* LINFlexD_8_LIN8RX input func */
  {344U, 2U},
  /* GTM_TIM5_1 input func */
  {41U, 5U},
  /* INMUX settings for pad PORT283:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_2 input func */
  {42U, 3U},
  /* INMUX settings for pad PORT284:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_3 input func */
  {43U, 4U},
  /* INMUX settings for pad PORT285:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_4 input func */
  {44U, 4U},
  /* INMUX settings for pad PORT286:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_5 input func */
  {45U, 4U},
  /* INMUX settings for pad PORT287:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_6 input func */
  {46U, 4U},
  /* INMUX settings for pad PORT288:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_7 input func */
  {47U, 4U},
  /* INMUX settings for pad PORT289:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_0 input func */
  {24U, 9U},
  /* INMUX settings for pad PORT290:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_1 input func */
  {25U, 8U},
  /* ETPU_3_ETPU3_0 input func */
  {485U, 0U},
  /* INMUX settings for pad PORT291:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_2 input func */
  {26U, 7U},
  /* INMUX settings for pad PORT292:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_3 input func */
  {27U, 8U},
  /* INMUX settings for pad PORT293:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_4 input func */
  {28U, 8U},
  /* INMUX settings for pad PORT294:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_5 input func */
  {29U, 9U},
  /* INMUX settings for pad PORT295:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_6 input func */
  {30U, 9U},
  /* INMUX settings for pad PORT296:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_7 input func */
  {31U, 9U},
  /* INMUX settings for pad PORT297:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_0 input func */
  {32U, 5U},
  /* INMUX settings for pad PORT298:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_1 input func */
  {33U, 5U},
  /* INMUX settings for pad PORT299:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_2 input func */
  {34U, 4U},
  /* INMUX settings for pad PORT300:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_3 input func */
  {35U, 4U},
  /* ETPU_3_ETPU3_9 input func */
  {494U, 0U},
  /* INMUX settings for pad PORT301:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_4 input func */
  {36U, 4U},
  /* INMUX settings for pad PORT302:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_5 input func */
  {37U, 4U},
  /* ETPU_3_ETPU3_3 input func */
  {488U, 0U},
  /* INMUX settings for pad PORT303:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_6 input func */
  {38U, 4U},
  /* INMUX settings for pad PORT304:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_7 input func */
  {39U, 4U},
  /* INMUX settings for pad PORT305:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_0 input func */
  {32U, 6U},
  /* INMUX settings for pad PORT306:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_1 input func */
  {33U, 6U},
  /* INMUX settings for pad PORT307:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_2 input func */
  {34U, 5U},
  /* INMUX settings for pad PORT308:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_3 input func */
  {35U, 5U},
  /* INMUX settings for pad PORT309:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_4 input func */
  {36U, 5U},
  /* INMUX settings for pad PORT310:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_5 input func */
  {37U, 5U},
  /* LINFlexD_6_LIN6RX input func */
  {342U, 2U},
  /* INMUX settings for pad PORT311:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_6 input func */
  {38U, 5U},
  /* INMUX settings for pad PORT312:      {INMUX reg, PADSEL val} */
  /* GTM_TIM4_7 input func */
  {39U, 5U},
  /* INMUX settings for pad PORT313:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_0 input func */
  {40U, 6U},
  /* INMUX settings for pad PORT314:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_1 input func */
  {41U, 6U},
  /* INMUX settings for pad PORT315:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_2 input func */
  {42U, 4U},
  /* INMUX settings for pad PORT316:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_3 input func */
  {43U, 5U},
  /* INMUX settings for pad PORT317:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_4 input func */
  {44U, 5U},
  /* INMUX settings for pad PORT318:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_5 input func */
  {45U, 5U},
  /* INMUX settings for pad PORT319:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_6 input func */
  {46U, 5U},
  /* INMUX settings for pad PORT320:      {INMUX reg, PADSEL val} */
  /* GTM_TIM5_7 input func */
  {47U, 5U},
  /* INMUX settings for pad PORT321:      {INMUX reg, PADSEL val} */
  /* GTM_TIM0_6 input func */
  {6U, 9U},
  /* GTM_TIM4_6 input func */
  {38U, 7U},
  /* INMUX settings for pad PORT322:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_0 input func */
  {24U, 10U},
  /* GTM_TIM5_0 input func */
  {40U, 7U},
  /* LINFlexD_0_LIN0RX input func */
  {336U, 9U},
  /* INMUX settings for pad PORT323:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_5 input func */
  {29U, 11U},
  /* GTM_TIM5_5 input func */
  {45U, 7U},
  /* DSPI_6_DSI0 input func */
  {208U, 3U},
  /* DSPI_6_DSI1 input func */
  {209U, 3U},
  /* DSPI_6_DSI2 input func */
  {210U, 3U},
  /* DSPI_6_DSI3 input func */
  {211U, 3U},
  /* DSPI_6_DSI4 input func */
  {212U, 3U},
  /* DSPI_6_DSI5 input func */
  {213U, 3U},
  /* DSPI_6_DSI6 input func */
  {214U, 3U},
  /* DSPI_6_DSI7 input func */
  {215U, 3U},
  /* DSPI_6_DSI8 input func */
  {216U, 3U},
  /* DSPI_6_DSI9 input func */
  {217U, 3U},
  /* DSPI_6_DSI10 input func */
  {218U, 3U},
  /* DSPI_6_DSI11 input func */
  {219U, 3U},
  /* DSPI_6_DSI12 input func */
  {220U, 3U},
  /* DSPI_6_DSI13 input func */
  {221U, 3U},
  /* DSPI_6_DSI14 input func */
  {222U, 3U},
  /* DSPI_6_DSI15 input func */
  {223U, 3U},
  /* DSPI_6_DSI16 input func */
  {224U, 3U},
  /* DSPI_6_DSI17 input func */
  {225U, 3U},
  /* DSPI_6_DSI18 input func */
  {226U, 3U},
  /* DSPI_6_DSI19 input func */
  {227U, 3U},
  /* DSPI_6_DSI20 input func */
  {228U, 3U},
  /* DSPI_6_DSI21 input func */
  {229U, 3U},
  /* DSPI_6_DSI22 input func */
  {230U, 3U},
  /* DSPI_6_DSI23 input func */
  {231U, 3U},
  /* DSPI_6_DSI24 input func */
  {232U, 3U},
  /* DSPI_6_DSI25 input func */
  {233U, 3U},
  /* DSPI_6_DSI26 input func */
  {234U, 3U},
  /* DSPI_6_DSI27 input func */
  {235U, 3U},
  /* DSPI_6_DSI28 input func */
  {236U, 3U},
  /* DSPI_6_DSI29 input func */
  {237U, 3U},
  /* DSPI_6_DSI30 input func */
  {238U, 3U},
  /* DSPI_6_DSI31 input func */
  {239U, 3U},
  /* PSI5_0_SDIN2_PSI5_0 input func */
  {316U, 3U},
  /* INMUX settings for pad PORT324:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_7 input func */
  {31U, 10U},
  /* GTM_TIM5_7 input func */
  {47U, 6U},
  /* INMUX settings for pad PORT325:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_0 input func */
  {16U, 10U},
  /* GTM_TIM4_0 input func */
  {32U, 7U},
  /* INMUX settings for pad PORT326:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_1 input func */
  {17U, 9U},
  /* GTM_TIM4_1 input func */
  {33U, 7U},
  /* DSPI_6_SIN_6 input func */
  {386U, 1U},
  /* INMUX settings for pad PORT327:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_2 input func */
  {18U, 9U},
  /* GTM_TIM4_2 input func */
  {34U, 6U},
  /* DSPI_6_SS_6 input func */
  {388U, 3U},
  /* INMUX settings for pad PORT328:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_3 input func */
  {19U, 11U},
  /* GTM_TIM4_3 input func */
  {35U, 6U},
  /* INMUX settings for pad PORT329:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_4 input func */
  {20U, 10U},
  /* GTM_TIM4_4 input func */
  {36U, 6U},
  /* DSPI_6_SS_6 input func */
  {388U, 4U},
  /* LINFlexD_5_LIN5RX input func */
  {341U, 2U},
  /* INMUX settings for pad PORT330:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_5 input func */
  {21U, 11U},
  /* GTM_TIM4_5 input func */
  {37U, 6U},
  /* INMUX settings for pad PORT331:      {INMUX reg, PADSEL val} */
  /* GTM_TIM2_6 input func */
  {22U, 10U},
  /* GTM_TIM4_6 input func */
  {38U, 6U},
  /* DSPI_6_SCK_6 input func */
  {387U, 1U},
  /* INMUX settings for pad PORT339:      {INMUX reg, PADSEL val} */
  /* SENT_0_SENTRX5_0 input func */
  {286U, 4U},
  /* INMUX settings for pad PORT340:      {INMUX reg, PADSEL val} */
  /* GTM_TIM3_6 input func */
  {30U, 12U}

};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"


/**
* @brief Port INOUT settings data
*/

/**
* @brief Port INPUT INMUX settings data
*/

#endif 



#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief Port Pin description data
*/
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
CONST (uint16, PORT_CONST) Port_au16PinDescription[93][22] =
{

/*  Mode PORT_GPIO_MODE: */
{
(uint16)0xff1e,
(uint16)0x0f00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xff00,
(uint16)0xffff,
(uint16)0xf000,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0001,
(uint16)0xfffe,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0fff,
(uint16)0x0010
},
/*  Mode PORT_ALT1_FUNC_MODE: */
{
(uint16)0x9404,
(uint16)0x0c00,
(uint16)0x4ecd,
(uint16)0x4006,
(uint16)0x1024,
(uint16)0xc704,
(uint16)0x0000,
(uint16)0x2080,
(uint16)0x0000,
(uint16)0x0042,
(uint16)0x0000,
(uint16)0x0212,
(uint16)0x04d9,
(uint16)0x2084,
(uint16)0xa106,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT2_FUNC_MODE: */
{
(uint16)0xbc0f,
(uint16)0x0400,
(uint16)0x6eff,
(uint16)0xf10f,
(uint16)0x1c9f,
(uint16)0x5e38,
(uint16)0xc001,
(uint16)0x43e4,
(uint16)0x1f00,
(uint16)0x0052,
(uint16)0x0000,
(uint16)0x0202,
(uint16)0x0400,
(uint16)0x0016,
(uint16)0x6fe8,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT3_FUNC_MODE: */
{
(uint16)0x3408,
(uint16)0x0f00,
(uint16)0x1ff8,
(uint16)0xf733,
(uint16)0x13f8,
(uint16)0xdb0f,
(uint16)0xa000,
(uint16)0x71fc,
(uint16)0x0800,
(uint16)0xfa02,
(uint16)0x3000,
(uint16)0xf8fa,
(uint16)0x0080,
(uint16)0x2816,
(uint16)0x2007,
(uint16)0x0001,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0f80,
(uint16)0x0000
},
/*  Mode PORT_ALT4_FUNC_MODE: */
{
(uint16)0xbc09,
(uint16)0x0f00,
(uint16)0xfe84,
(uint16)0x010f,
(uint16)0x1de0,
(uint16)0x813d,
(uint16)0xa000,
(uint16)0xc79f,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0012,
(uint16)0x0600,
(uint16)0x0010,
(uint16)0x2000,
(uint16)0x2000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT5_FUNC_MODE: */
{
(uint16)0x0400,
(uint16)0x0800,
(uint16)0xcead,
(uint16)0xf208,
(uint16)0x1e06,
(uint16)0x000a,
(uint16)0x0000,
(uint16)0x019c,
(uint16)0xc800,
(uint16)0x0440,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0014,
(uint16)0x0000
},
/*  Mode PORT_ALT6_FUNC_MODE: */
{
(uint16)0x0400,
(uint16)0x0e00,
(uint16)0x46c4,
(uint16)0xc400,
(uint16)0x0400,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0198,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x7000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT7_FUNC_MODE: */
{
(uint16)0x0000,
(uint16)0x0800,
(uint16)0x0204,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0180,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT8_FUNC_MODE: */
{
(uint16)0xff0f,
(uint16)0x0f00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xff00,
(uint16)0xffff,
(uint16)0xf000,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0001,
(uint16)0xfffe,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0fff,
(uint16)0x0010
},
/*  Mode PORT_ALT9_FUNC_MODE: */
{
(uint16)0xff0f,
(uint16)0x0f00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xff00,
(uint16)0xffff,
(uint16)0xf000,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0001,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0ffe,
(uint16)0x0000
},
/*  Mode PORT_ALT10_FUNC_MODE: */
{
(uint16)0xff0f,
(uint16)0x0f00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xff00,
(uint16)0xffff,
(uint16)0xe000,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0001,
(uint16)0xfffe,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0fff,
(uint16)0x0010
},
/*  Mode PORT_ALT11_FUNC_MODE: */
{
(uint16)0xff0f,
(uint16)0x0f00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xff00,
(uint16)0x1f7f,
(uint16)0xc000,
(uint16)0x5101,
(uint16)0xffea,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0001,
(uint16)0x000e,
(uint16)0x0204,
(uint16)0x7104,
(uint16)0x0083,
(uint16)0x0fff,
(uint16)0x0000
},
/*  Mode PORT_ALT12_FUNC_MODE: */
{
(uint16)0xfc0b,
(uint16)0x0700,
(uint16)0x7ffb,
(uint16)0xf7f7,
(uint16)0x1fff,
(uint16)0xdfff,
(uint16)0xe001,
(uint16)0xfaff,
(uint16)0x3f00,
(uint16)0x033e,
(uint16)0x8000,
(uint16)0x5000,
(uint16)0xff48,
(uint16)0xffff,
(uint16)0xbfff,
(uint16)0x0000,
(uint16)0x000c,
(uint16)0x0000,
(uint16)0x4000,
(uint16)0x0000,
(uint16)0x0942,
(uint16)0x0000
},
/*  Mode PORT_ALT13_FUNC_MODE: */
{
(uint16)0x7c01,
(uint16)0x0a00,
(uint16)0x7afe,
(uint16)0xe6f5,
(uint16)0x0380,
(uint16)0x9c47,
(uint16)0x2000,
(uint16)0x0a4f,
(uint16)0x3c00,
(uint16)0x0016,
(uint16)0x8000,
(uint16)0x4000,
(uint16)0xfe48,
(uint16)0xfefb,
(uint16)0x9fff,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT14_FUNC_MODE: */
{
(uint16)0x0400,
(uint16)0x0800,
(uint16)0x403c,
(uint16)0x0210,
(uint16)0x0100,
(uint16)0x1007,
(uint16)0x0000,
(uint16)0x0009,
(uint16)0x1400,
(uint16)0x0004,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0xf800,
(uint16)0xfe4b,
(uint16)0x07ef,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ALT15_FUNC_MODE: */
{
(uint16)0x0000,
(uint16)0x0800,
(uint16)0x0004,
(uint16)0x0200,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0xc000,
(uint16)0x9441,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ONLY_OUTPUT_MODE: */
{
(uint16)0x0200,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_ANALOG_INPUT_MODE: */
{
(uint16)0x0000,
(uint16)0xf0ff,
(uint16)0x0003,
(uint16)0x3800,
(uint16)0xe01f,
(uint16)0x0000,
(uint16)0x1fff,
(uint16)0x0000,
(uint16)0x03ff,
(uint16)0x0000,
(uint16)0x0fff,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0xfffe,
(uint16)0x0001,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0xf000,
(uint16)0x000f
},
/*  Mode PORT_ONLY_INPUT_MODE: */
{
(uint16)0xfd1f,
(uint16)0xfdff,
(uint16)0x73f4,
(uint16)0xcfca,
(uint16)0xe7c1,
(uint16)0xe1fd,
(uint16)0xdffe,
(uint16)0xbe5b,
(uint16)0x3aff,
(uint16)0xf77f,
(uint16)0x7fff,
(uint16)0xabff,
(uint16)0xff76,
(uint16)0xff50,
(uint16)0xa7ff,
(uint16)0xfffe,
(uint16)0x000f,
(uint16)0x0008,
(uint16)0x300c,
(uint16)0x0082,
(uint16)0xf042,
(uint16)0x000f
},
/*  Mode PORT_INPUT1_MODE: */
{
(uint16)0xff0f,
(uint16)0xff00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe061,
(uint16)0xffff,
(uint16)0xff33,
(uint16)0xffff,
(uint16)0xf000,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0x0fff,
(uint16)0x0018
},
/*  Mode PORT_INPUT2_MODE: */
{
(uint16)0xff0f,
(uint16)0xff00,
(uint16)0xffff,
(uint16)0xf7ff,
(uint16)0x1fff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xffff,
(uint16)0xff30,
(uint16)0xffff,
(uint16)0xe000,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0x0003,
(uint16)0x0400,
(uint16)0x5004,
(uint16)0x0040,
(uint16)0x0ffe,
(uint16)0x0000
},
/*  Mode PORT_INPUT3_MODE: */
{
(uint16)0xbc0b,
(uint16)0xfb00,
(uint16)0xffff,
(uint16)0xf3fe,
(uint16)0x177f,
(uint16)0xffff,
(uint16)0xe001,
(uint16)0xf7bf,
(uint16)0xdf30,
(uint16)0x19d9,
(uint16)0x8000,
(uint16)0xfcf9,
(uint16)0xdffd,
(uint16)0xbffd,
(uint16)0xe7ff,
(uint16)0xc000,
(uint16)0x0001,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0acc,
(uint16)0x0000
},
/*  Mode PORT_INPUT4_MODE: */
{
(uint16)0xb80b,
(uint16)0x0b00,
(uint16)0xfdff,
(uint16)0xf39e,
(uint16)0x043f,
(uint16)0xaf3f,
(uint16)0xa001,
(uint16)0x778e,
(uint16)0x1f30,
(uint16)0x0099,
(uint16)0x8000,
(uint16)0x5401,
(uint16)0x1ec9,
(uint16)0x0148,
(uint16)0x81c2,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0208,
(uint16)0x0000
},
/*  Mode PORT_INPUT5_MODE: */
{
(uint16)0xb800,
(uint16)0x0b00,
(uint16)0x79f6,
(uint16)0xf382,
(uint16)0x043f,
(uint16)0xa92f,
(uint16)0xa001,
(uint16)0x6782,
(uint16)0x1700,
(uint16)0x0091,
(uint16)0x0000,
(uint16)0x0401,
(uint16)0x0c01,
(uint16)0x0100,
(uint16)0x8180,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT6_MODE: */
{
(uint16)0x3800,
(uint16)0x0200,
(uint16)0x79f6,
(uint16)0xf182,
(uint16)0x043f,
(uint16)0x202c,
(uint16)0x0001,
(uint16)0x4280,
(uint16)0x1700,
(uint16)0x0011,
(uint16)0x0000,
(uint16)0x0001,
(uint16)0x0401,
(uint16)0x0100,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT7_MODE: */
{
(uint16)0x0800,
(uint16)0x0200,
(uint16)0x39d4,
(uint16)0xb180,
(uint16)0x0407,
(uint16)0x202c,
(uint16)0x0001,
(uint16)0x0280,
(uint16)0x1300,
(uint16)0x0011,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0100,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT8_MODE: */
{
(uint16)0x0800,
(uint16)0x0200,
(uint16)0x1854,
(uint16)0x0100,
(uint16)0x0005,
(uint16)0x202c,
(uint16)0x0000,
(uint16)0x0200,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT9_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x1044,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x000c,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT10_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0044,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT11_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0044,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT12_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT13_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT14_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT15_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT16_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT17_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT18_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT19_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT20_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT21_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT22_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT23_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT24_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT25_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT26_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT27_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT28_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT29_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT30_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT31_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT32_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT33_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT34_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT35_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0080,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000
},
/*  Mode PORT_INPUT36_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT37_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT38_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT39_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT40_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT41_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT42_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT43_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT44_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT45_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT46_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT47_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT48_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT49_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT50_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT51_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT52_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT53_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT54_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT55_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT56_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT57_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT58_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT59_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT60_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT61_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT62_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT63_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT64_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT65_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT66_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0004,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0010,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT67_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT68_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INPUT69_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0100,
(uint16)0x0000,
(uint16)0x0008,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INOUT1_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INOUT2_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INOUT3_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INOUT4_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
},
/*  Mode PORT_INOUT5_MODE: */
{
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000,
(uint16)0x0000
}

};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"

/**
* @brief Port index to address the INPUT INDEX data
*/  
#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
CONST(uint16,PORT_CONST) Port_au16PadFunctInMuxIndex[341]=
{
 
  /* Index to address the input settings for pad 0*/
  (uint16)1,
  /* Index to address the input settings for pad 1*/
  (uint16)5,
  /* Index to address the input settings for pad 2*/
  (uint16)9,
  /* Index to address the input settings for pad 3*/
  (uint16)11,
  /* Index to address the input settings for pad 4*/
  (uint16)0,
  /* Index to address the input settings for pad 5*/
  (uint16)0,
  /* Index to address the input settings for pad 6*/
  (uint16)0,
  /* Index to address the input settings for pad 7*/
  (uint16)0,
  /* Index to address the input settings for pad 8*/
  (uint16)15,
  /* Index to address the input settings for pad 9*/
  (uint16)17,
  /* Index to address the input settings for pad 10*/
  (uint16)19,
  /* Index to address the input settings for pad 11*/
  (uint16)22,
  /* Index to address the input settings for pad 12*/
  (uint16)30,
  /* Index to address the input settings for pad 13*/
  (uint16)36,
  /* Index to address the input settings for pad 14*/
  (uint16)42,
  /* Index to address the input settings for pad 15*/
  (uint16)44,
  /* Index to address the input settings for pad 16*/
  (uint16)0,
  /* Index to address the input settings for pad 17*/
  (uint16)0,
  /* Index to address the input settings for pad 18*/
  (uint16)0,
  /* Index to address the input settings for pad 19*/
  (uint16)0,
  /* Index to address the input settings for pad 20*/
  (uint16)0,
  /* Index to address the input settings for pad 21*/
  (uint16)0,
  /* Index to address the input settings for pad 22*/
  (uint16)0,
  /* Index to address the input settings for pad 23*/
  (uint16)0,
  /* Index to address the input settings for pad 24*/
  (uint16)49,
  /* Index to address the input settings for pad 25*/
  (uint16)54,
  /* Index to address the input settings for pad 26*/
  (uint16)62,
  /* Index to address the input settings for pad 27*/
  (uint16)64,
  /* Index to address the input settings for pad 28*/
  (uint16)69,
  /* Index to address the input settings for pad 29*/
  (uint16)72,
  /* Index to address the input settings for pad 30*/
  (uint16)75,
  /* Index to address the input settings for pad 31*/
  (uint16)78,
  /* Index to address the input settings for pad 32*/
  (uint16)81,
  /* Index to address the input settings for pad 33*/
  (uint16)85,
  /* Index to address the input settings for pad 34*/
  (uint16)91,
  /* Index to address the input settings for pad 35*/
  (uint16)157,
  /* Index to address the input settings for pad 36*/
  (uint16)161,
  /* Index to address the input settings for pad 37*/
  (uint16)169,
  /* Index to address the input settings for pad 38*/
  (uint16)175,
  /* Index to address the input settings for pad 39*/
  (uint16)186,
  /* Index to address the input settings for pad 40*/
  (uint16)193,
  /* Index to address the input settings for pad 41*/
  (uint16)200,
  /* Index to address the input settings for pad 42*/
  (uint16)203,
  /* Index to address the input settings for pad 43*/
  (uint16)207,
  /* Index to address the input settings for pad 44*/
  (uint16)215,
  /* Index to address the input settings for pad 45*/
  (uint16)224,
  /* Index to address the input settings for pad 46*/
  (uint16)231,
  /* Index to address the input settings for pad 47*/
  (uint16)237,
  /* Index to address the input settings for pad 48*/
  (uint16)241,
  /* Index to address the input settings for pad 49*/
  (uint16)243,
  /* Index to address the input settings for pad 50*/
  (uint16)249,
  /* Index to address the input settings for pad 51*/
  (uint16)253,
  /* Index to address the input settings for pad 52*/
  (uint16)257,
  /* Index to address the input settings for pad 53*/
  (uint16)261,
  /* Index to address the input settings for pad 54*/
  (uint16)264,
  /* Index to address the input settings for pad 55*/
  (uint16)267,
  /* Index to address the input settings for pad 56*/
  (uint16)274,
  /* Index to address the input settings for pad 57*/
  (uint16)343,
  /* Index to address the input settings for pad 58*/
  (uint16)348,
  /* Index to address the input settings for pad 59*/
  (uint16)0,
  /* Index to address the input settings for pad 60*/
  (uint16)350,
  /* Index to address the input settings for pad 61*/
  (uint16)357,
  /* Index to address the input settings for pad 62*/
  (uint16)364,
  /* Index to address the input settings for pad 63*/
  (uint16)370,
  /* Index to address the input settings for pad 64*/
  (uint16)377,
  /* Index to address the input settings for pad 65*/
  (uint16)385,
  /* Index to address the input settings for pad 66*/
  (uint16)392,
  /* Index to address the input settings for pad 67*/
  (uint16)400,
  /* Index to address the input settings for pad 68*/
  (uint16)406,
  /* Index to address the input settings for pad 69*/
  (uint16)412,
  /* Index to address the input settings for pad 70*/
  (uint16)418,
  /* Index to address the input settings for pad 71*/
  (uint16)421,
  /* Index to address the input settings for pad 72*/
  (uint16)423,
  /* Index to address the input settings for pad 73*/
  (uint16)426,
  /* Index to address the input settings for pad 74*/
  (uint16)429,
  /* Index to address the input settings for pad 75*/
  (uint16)436,
  /* Index to address the input settings for pad 76*/
  (uint16)438,
  /* Index to address the input settings for pad 77*/
  (uint16)0,
  /* Index to address the input settings for pad 78*/
  (uint16)0,
  /* Index to address the input settings for pad 79*/
  (uint16)0,
  /* Index to address the input settings for pad 80*/
  (uint16)441,
  /* Index to address the input settings for pad 81*/
  (uint16)446,
  /* Index to address the input settings for pad 82*/
  (uint16)451,
  /* Index to address the input settings for pad 83*/
  (uint16)460,
  /* Index to address the input settings for pad 84*/
  (uint16)529,
  /* Index to address the input settings for pad 85*/
  (uint16)533,
  /* Index to address the input settings for pad 86*/
  (uint16)541,
  /* Index to address the input settings for pad 87*/
  (uint16)544,
  /* Index to address the input settings for pad 88*/
  (uint16)547,
  /* Index to address the input settings for pad 89*/
  (uint16)552,
  /* Index to address the input settings for pad 90*/
  (uint16)556,
  /* Index to address the input settings for pad 91*/
  (uint16)560,
  /* Index to address the input settings for pad 92*/
  (uint16)565,
  /* Index to address the input settings for pad 93*/
  (uint16)568,
  /* Index to address the input settings for pad 94*/
  (uint16)576,
  /* Index to address the input settings for pad 95*/
  (uint16)579,
  /* Index to address the input settings for pad 96*/
  (uint16)584,
  /* Index to address the input settings for pad 97*/
  (uint16)0,
  /* Index to address the input settings for pad 98*/
  (uint16)0,
  /* Index to address the input settings for pad 99*/
  (uint16)0,
  /* Index to address the input settings for pad 100*/
  (uint16)0,
  /* Index to address the input settings for pad 101*/
  (uint16)591,
  /* Index to address the input settings for pad 102*/
  (uint16)592,
  /* Index to address the input settings for pad 103*/
  (uint16)0,
  /* Index to address the input settings for pad 104*/
  (uint16)0,
  /* Index to address the input settings for pad 105*/
  (uint16)0,
  /* Index to address the input settings for pad 106*/
  (uint16)0,
  /* Index to address the input settings for pad 107*/
  (uint16)0,
  /* Index to address the input settings for pad 108*/
  (uint16)0,
  /* Index to address the input settings for pad 109*/
  (uint16)593,
  /* Index to address the input settings for pad 110*/
  (uint16)598,
  /* Index to address the input settings for pad 111*/
  (uint16)601,
  /* Index to address the input settings for pad 112*/
  (uint16)606,
  /* Index to address the input settings for pad 113*/
  (uint16)609,
  /* Index to address the input settings for pad 114*/
  (uint16)614,
  /* Index to address the input settings for pad 115*/
  (uint16)618,
  /* Index to address the input settings for pad 116*/
  (uint16)622,
  /* Index to address the input settings for pad 117*/
  (uint16)625,
  /* Index to address the input settings for pad 118*/
  (uint16)628,
  /* Index to address the input settings for pad 119*/
  (uint16)630,
  /* Index to address the input settings for pad 120*/
  (uint16)637,
  /* Index to address the input settings for pad 121*/
  (uint16)642,
  /* Index to address the input settings for pad 122*/
  (uint16)650,
  /* Index to address the input settings for pad 123*/
  (uint16)655,
  /* Index to address the input settings for pad 124*/
  (uint16)657,
  /* Index to address the input settings for pad 125*/
  (uint16)661,
  /* Index to address the input settings for pad 126*/
  (uint16)666,
  /* Index to address the input settings for pad 127*/
  (uint16)672,
  /* Index to address the input settings for pad 128*/
  (uint16)675,
  /* Index to address the input settings for pad 129*/
  (uint16)676,
  /* Index to address the input settings for pad 130*/
  (uint16)0,
  /* Index to address the input settings for pad 131*/
  (uint16)0,
  /* Index to address the input settings for pad 132*/
  (uint16)677,
  /* Index to address the input settings for pad 133*/
  (uint16)681,
  /* Index to address the input settings for pad 134*/
  (uint16)0,
  /* Index to address the input settings for pad 135*/
  (uint16)0,
  /* Index to address the input settings for pad 136*/
  (uint16)685,
  /* Index to address the input settings for pad 137*/
  (uint16)692,
  /* Index to address the input settings for pad 138*/
  (uint16)699,
  /* Index to address the input settings for pad 139*/
  (uint16)705,
  /* Index to address the input settings for pad 140*/
  (uint16)709,
  /* Index to address the input settings for pad 141*/
  (uint16)716,
  /* Index to address the input settings for pad 142*/
  (uint16)718,
  /* Index to address the input settings for pad 143*/
  (uint16)721,
  /* Index to address the input settings for pad 144*/
  (uint16)724,
  /* Index to address the input settings for pad 145*/
  (uint16)731,
  /* Index to address the input settings for pad 146*/
  (uint16)733,
  /* Index to address the input settings for pad 147*/
  (uint16)735,
  /* Index to address the input settings for pad 148*/
  (uint16)739,
  /* Index to address the input settings for pad 149*/
  (uint16)805,
  /* Index to address the input settings for pad 150*/
  (uint16)807,
  /* Index to address the input settings for pad 151*/
  (uint16)810,
  /* Index to address the input settings for pad 152*/
  (uint16)815,
  /* Index to address the input settings for pad 153*/
  (uint16)818,
  /* Index to address the input settings for pad 154*/
  (uint16)820,
  /* Index to address the input settings for pad 155*/
  (uint16)822,
  /* Index to address the input settings for pad 156*/
  (uint16)825,
  /* Index to address the input settings for pad 157*/
  (uint16)828,
  /* Index to address the input settings for pad 158*/
  (uint16)830,
  /* Index to address the input settings for pad 159*/
  (uint16)832,
  /* Index to address the input settings for pad 160*/
  (uint16)0,
  /* Index to address the input settings for pad 161*/
  (uint16)0,
  /* Index to address the input settings for pad 162*/
  (uint16)0,
  /* Index to address the input settings for pad 163*/
  (uint16)0,
  /* Index to address the input settings for pad 164*/
  (uint16)0,
  /* Index to address the input settings for pad 165*/
  (uint16)0,
  /* Index to address the input settings for pad 166*/
  (uint16)0,
  /* Index to address the input settings for pad 167*/
  (uint16)0,
  /* Index to address the input settings for pad 168*/
  (uint16)0,
  /* Index to address the input settings for pad 169*/
  (uint16)0,
  /* Index to address the input settings for pad 170*/
  (uint16)0,
  /* Index to address the input settings for pad 171*/
  (uint16)0,
  /* Index to address the input settings for pad 172*/
  (uint16)834,
  /* Index to address the input settings for pad 173*/
  (uint16)835,
  /* Index to address the input settings for pad 174*/
  (uint16)837,
  /* Index to address the input settings for pad 175*/
  (uint16)839,
  /* Index to address the input settings for pad 176*/
  (uint16)843,
  /* Index to address the input settings for pad 177*/
  (uint16)849,
  /* Index to address the input settings for pad 178*/
  (uint16)851,
  /* Index to address the input settings for pad 179*/
  (uint16)853,
  /* Index to address the input settings for pad 180*/
  (uint16)856,
  /* Index to address the input settings for pad 181*/
  (uint16)859,
  /* Index to address the input settings for pad 182*/
  (uint16)862,
  /* Index to address the input settings for pad 183*/
  (uint16)865,
  /* Index to address the input settings for pad 184*/
  (uint16)868,
  /* Index to address the input settings for pad 185*/
  (uint16)870,
  /* Index to address the input settings for pad 186*/
  (uint16)872,
  /* Index to address the input settings for pad 187*/
  (uint16)877,
  /* Index to address the input settings for pad 188*/
  (uint16)880,
  /* Index to address the input settings for pad 189*/
  (uint16)884,
  /* Index to address the input settings for pad 190*/
  (uint16)887,
  /* Index to address the input settings for pad 191*/
  (uint16)891,
  /* Index to address the input settings for pad 192*/
  (uint16)894,
  /* Index to address the input settings for pad 193*/
  (uint16)900,
  /* Index to address the input settings for pad 194*/
  (uint16)902,
  /* Index to address the input settings for pad 195*/
  (uint16)905,
  /* Index to address the input settings for pad 196*/
  (uint16)909,
  /* Index to address the input settings for pad 197*/
  (uint16)912,
  /* Index to address the input settings for pad 198*/
  (uint16)915,
  /* Index to address the input settings for pad 199*/
  (uint16)919,
  /* Index to address the input settings for pad 200*/
  (uint16)923,
  /* Index to address the input settings for pad 201*/
  (uint16)926,
  /* Index to address the input settings for pad 202*/
  (uint16)930,
  /* Index to address the input settings for pad 203*/
  (uint16)936,
  /* Index to address the input settings for pad 204*/
  (uint16)941,
  /* Index to address the input settings for pad 205*/
  (uint16)945,
  /* Index to address the input settings for pad 206*/
  (uint16)947,
  /* Index to address the input settings for pad 207*/
  (uint16)950,
  /* Index to address the input settings for pad 208*/
  (uint16)953,
  /* Index to address the input settings for pad 209*/
  (uint16)956,
  /* Index to address the input settings for pad 210*/
  (uint16)958,
  /* Index to address the input settings for pad 211*/
  (uint16)961,
  /* Index to address the input settings for pad 212*/
  (uint16)965,
  /* Index to address the input settings for pad 213*/
  (uint16)968,
  /* Index to address the input settings for pad 214*/
  (uint16)971,
  /* Index to address the input settings for pad 215*/
  (uint16)975,
  /* Index to address the input settings for pad 216*/
  (uint16)978,
  /* Index to address the input settings for pad 217*/
  (uint16)985,
  /* Index to address the input settings for pad 218*/
  (uint16)988,
  /* Index to address the input settings for pad 219*/
  (uint16)991,
  /* Index to address the input settings for pad 220*/
  (uint16)994,
  /* Index to address the input settings for pad 221*/
  (uint16)997,
  /* Index to address the input settings for pad 222*/
  (uint16)1000,
  /* Index to address the input settings for pad 223*/
  (uint16)1002,
  /* Index to address the input settings for pad 224*/
  (uint16)1005,
  /* Index to address the input settings for pad 225*/
  (uint16)1008,
  /* Index to address the input settings for pad 226*/
  (uint16)1012,
  /* Index to address the input settings for pad 227*/
  (uint16)1015,
  /* Index to address the input settings for pad 228*/
  (uint16)1018,
  /* Index to address the input settings for pad 229*/
  (uint16)1021,
  /* Index to address the input settings for pad 230*/
  (uint16)1024,
  /* Index to address the input settings for pad 231*/
  (uint16)1028,
  /* Index to address the input settings for pad 232*/
  (uint16)1063,
  /* Index to address the input settings for pad 233*/
  (uint16)1068,
  /* Index to address the input settings for pad 234*/
  (uint16)1071,
  /* Index to address the input settings for pad 235*/
  (uint16)1074,
  /* Index to address the input settings for pad 236*/
  (uint16)1076,
  /* Index to address the input settings for pad 237*/
  (uint16)1078,
  /* Index to address the input settings for pad 238*/
  (uint16)1081,
  /* Index to address the input settings for pad 239*/
  (uint16)1084,
  /* Index to address the input settings for pad 240*/
  (uint16)1089,
  /* Index to address the input settings for pad 241*/
  (uint16)0,
  /* Index to address the input settings for pad 242*/
  (uint16)0,
  /* Index to address the input settings for pad 243*/
  (uint16)0,
  /* Index to address the input settings for pad 244*/
  (uint16)0,
  /* Index to address the input settings for pad 245*/
  (uint16)0,
  /* Index to address the input settings for pad 246*/
  (uint16)0,
  /* Index to address the input settings for pad 247*/
  (uint16)0,
  /* Index to address the input settings for pad 248*/
  (uint16)0,
  /* Index to address the input settings for pad 249*/
  (uint16)0,
  /* Index to address the input settings for pad 250*/
  (uint16)0,
  /* Index to address the input settings for pad 251*/
  (uint16)0,
  /* Index to address the input settings for pad 252*/
  (uint16)0,
  /* Index to address the input settings for pad 253*/
  (uint16)1091,
  /* Index to address the input settings for pad 254*/
  (uint16)1093,
  /* Index to address the input settings for pad 255*/
  (uint16)1096,
  /* Index to address the input settings for pad 256*/
  (uint16)1099,
  /* Index to address the input settings for pad 257*/
  (uint16)1102,
  /* Index to address the input settings for pad 258*/
  (uint16)1104,
  /* Index to address the input settings for pad 259*/
  (uint16)1105,
  /* Index to address the input settings for pad 260*/
  (uint16)1106,
  /* Index to address the input settings for pad 261*/
  (uint16)1107,
  /* Index to address the input settings for pad 262*/
  (uint16)1108,
  /* Index to address the input settings for pad 263*/
  (uint16)1109,
  /* Index to address the input settings for pad 264*/
  (uint16)1110,
  /* Index to address the input settings for pad 265*/
  (uint16)1111,
  /* Index to address the input settings for pad 266*/
  (uint16)1112,
  /* Index to address the input settings for pad 267*/
  (uint16)1113,
  /* Index to address the input settings for pad 268*/
  (uint16)1114,
  /* Index to address the input settings for pad 269*/
  (uint16)1115,
  /* Index to address the input settings for pad 270*/
  (uint16)1116,
  /* Index to address the input settings for pad 271*/
  (uint16)1117,
  /* Index to address the input settings for pad 272*/
  (uint16)1118,
  /* Index to address the input settings for pad 273*/
  (uint16)1119,
  /* Index to address the input settings for pad 274*/
  (uint16)1120,
  /* Index to address the input settings for pad 275*/
  (uint16)1121,
  /* Index to address the input settings for pad 276*/
  (uint16)1122,
  /* Index to address the input settings for pad 277*/
  (uint16)1123,
  /* Index to address the input settings for pad 278*/
  (uint16)1124,
  /* Index to address the input settings for pad 279*/
  (uint16)1125,
  /* Index to address the input settings for pad 280*/
  (uint16)1126,
  /* Index to address the input settings for pad 281*/
  (uint16)1127,
  /* Index to address the input settings for pad 282*/
  (uint16)1128,
  /* Index to address the input settings for pad 283*/
  (uint16)1130,
  /* Index to address the input settings for pad 284*/
  (uint16)1131,
  /* Index to address the input settings for pad 285*/
  (uint16)1132,
  /* Index to address the input settings for pad 286*/
  (uint16)1133,
  /* Index to address the input settings for pad 287*/
  (uint16)1134,
  /* Index to address the input settings for pad 288*/
  (uint16)1135,
  /* Index to address the input settings for pad 289*/
  (uint16)1136,
  /* Index to address the input settings for pad 290*/
  (uint16)1137,
  /* Index to address the input settings for pad 291*/
  (uint16)1139,
  /* Index to address the input settings for pad 292*/
  (uint16)1140,
  /* Index to address the input settings for pad 293*/
  (uint16)1141,
  /* Index to address the input settings for pad 294*/
  (uint16)1142,
  /* Index to address the input settings for pad 295*/
  (uint16)1143,
  /* Index to address the input settings for pad 296*/
  (uint16)1144,
  /* Index to address the input settings for pad 297*/
  (uint16)1145,
  /* Index to address the input settings for pad 298*/
  (uint16)1146,
  /* Index to address the input settings for pad 299*/
  (uint16)1147,
  /* Index to address the input settings for pad 300*/
  (uint16)1148,
  /* Index to address the input settings for pad 301*/
  (uint16)1150,
  /* Index to address the input settings for pad 302*/
  (uint16)1151,
  /* Index to address the input settings for pad 303*/
  (uint16)1153,
  /* Index to address the input settings for pad 304*/
  (uint16)1154,
  /* Index to address the input settings for pad 305*/
  (uint16)1155,
  /* Index to address the input settings for pad 306*/
  (uint16)1156,
  /* Index to address the input settings for pad 307*/
  (uint16)1157,
  /* Index to address the input settings for pad 308*/
  (uint16)1158,
  /* Index to address the input settings for pad 309*/
  (uint16)1159,
  /* Index to address the input settings for pad 310*/
  (uint16)1160,
  /* Index to address the input settings for pad 311*/
  (uint16)1162,
  /* Index to address the input settings for pad 312*/
  (uint16)1163,
  /* Index to address the input settings for pad 313*/
  (uint16)1164,
  /* Index to address the input settings for pad 314*/
  (uint16)1165,
  /* Index to address the input settings for pad 315*/
  (uint16)1166,
  /* Index to address the input settings for pad 316*/
  (uint16)1167,
  /* Index to address the input settings for pad 317*/
  (uint16)1168,
  /* Index to address the input settings for pad 318*/
  (uint16)1169,
  /* Index to address the input settings for pad 319*/
  (uint16)1170,
  /* Index to address the input settings for pad 320*/
  (uint16)1171,
  /* Index to address the input settings for pad 321*/
  (uint16)1172,
  /* Index to address the input settings for pad 322*/
  (uint16)1174,
  /* Index to address the input settings for pad 323*/
  (uint16)1177,
  /* Index to address the input settings for pad 324*/
  (uint16)1212,
  /* Index to address the input settings for pad 325*/
  (uint16)1214,
  /* Index to address the input settings for pad 326*/
  (uint16)1216,
  /* Index to address the input settings for pad 327*/
  (uint16)1219,
  /* Index to address the input settings for pad 328*/
  (uint16)1222,
  /* Index to address the input settings for pad 329*/
  (uint16)1224,
  /* Index to address the input settings for pad 330*/
  (uint16)1228,
  /* Index to address the input settings for pad 331*/
  (uint16)1230,
  /* Index to address the input settings for pad 332*/
  (uint16)0,
  /* Index to address the input settings for pad 333*/
  (uint16)0,
  /* Index to address the input settings for pad 334*/
  (uint16)0,
  /* Index to address the input settings for pad 335*/
  (uint16)0,
  /* Index to address the input settings for pad 336*/
  (uint16)0,
  /* Index to address the input settings for pad 337*/
  (uint16)0,
  /* Index to address the input settings for pad 338*/
  (uint16)0,
  /* Index to address the input settings for pad 339*/
  (uint16)1233,
  /* Index to address the input settings for pad 340*/
  (uint16)1234,

};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"

/**
* @brief Port Pin description data
*/

/**
* @brief Port index to address the INPUT INDEX data
*/

#endif 


/*======================================GLOBAL VARIABLES============================================*/


/*==================================LOCAL FUNCTION PROTOTYPES=======================================*/


/*======================================LOCAL FUNCTIONS=============================================*/


/*======================================GLOBAL FUNCTIONS============================================*/




/** @} */


#define PORT_START_SEC_CONFIG_DATA
#include "Port_MemMap.h"
static CONST(Port_CoreMapItemType, PORT_CONST) Port_CoreMap[PORT_MAX_CONFIGURED_PADS_U16]=
{
    {
        .u16Port_Pin = 16,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 17,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 18,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 19,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 20,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 21,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 28,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 29,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 30,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 59,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 60,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 64,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 65,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 66,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 68,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 77,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 78,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 96,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 103,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 104,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 105,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 106,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 107,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 108,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 128,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 129,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 130,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 132,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 134,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 135,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 136,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 137,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 160,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 163,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 164,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 166,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 243,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 244,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 245,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 246,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 249,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 250,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 334,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 335,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 336,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 337,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 0,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 82,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 239,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 233,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 10,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 11,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 215,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 144,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 184,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 187,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 218,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 219,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 86,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 87,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 83,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 183,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 37,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 38,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 69,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 46,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 119,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 84,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 109,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 159,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 155,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 157,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 188,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 189,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 190,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 191,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 257,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 13,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 39,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 70,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 71,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 72,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 73,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 75,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 76,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 139,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 140,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 147,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 148,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 149,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 150,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 151,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 152,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 153,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 55,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 194,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 195,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 196,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 197,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 198,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 199,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 200,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 224,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 226,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 227,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 228,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 229,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 230,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 305,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 306,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 307,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 308,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 309,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 310,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 311,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 58,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 62,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 302,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 303,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 304,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 93,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 253,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 225,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 290,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 300,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 301,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 94,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 74,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 111,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 1,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 2,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 3,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 4,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 14,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 43,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 44,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 48,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 49,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 50,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 51,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 52,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 53,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 54,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 56,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 57,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 91,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 145,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 209,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 211,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 212,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 221,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 222,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 201,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 202,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 203,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 204,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 192,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 193,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 146,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 154,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 179,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 234,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 235,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 236,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 237,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 238,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 289,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 292,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 294,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 293,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 295,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 296,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 297,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 298,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 299,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 312,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 313,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 314,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 315,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 316,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 317,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 27,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 115,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 33,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 15,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 63,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 186,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 205,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 85,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 95,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 88,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 116,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 123,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 124,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 122,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 113,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 114,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 177,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 118,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 126,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 127,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 125,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 25,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 80,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 47,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 61,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 214,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 217,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 220,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 231,
        .u8CoreId =4
    },
    {
        .u16Port_Pin = 232,
        .u8CoreId =4
    },
};
#define PORT_STOP_SEC_CONFIG_DATA
#include "Port_MemMap.h"
/* End of File */


#ifdef __cplusplus
}
#endif
