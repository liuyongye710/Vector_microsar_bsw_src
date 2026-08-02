/****************************************************************************
 *
 * Copyright (c) 2023  C*Core -   All Rights Reserved
 *
 * THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
 * INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *   Project              : AUTOSAR 4.4.0 MCAL
 *   Platform             : PowerPC e200
 *   Peripheral           :
 *   Dependencies         :
 *
 *   Autosar Version      : 4.4.0
 *   Autosar Revision     :
 *   Autosar Conf.Variant :
 *   SW Version           :
 *   Build Version        :
 *
 *****************************************************************************/

/**
 *   @file    Dio_Cfg.h
 *   @version 3.0.0
 *
 *   @brief   AUTOSAR 4.4.0 - Common Level Driver source file.
 *   @details Autosar layer of Dio MCAL driver.
 *
 *   @addtogroup Dio
 *   @{
 */

#ifdef __cplusplus
extern "C"
{
#endif
/*PRQA S 0380,0686 EOF*/
/*==============================================INCLUDE FILES=======================================*/
#include "Dio_Cfg.h"
/*=============================SOURCE FILE VERSION INFORMATION==================================*/
#define DIO_CFG_C_VENDOR_ID 176
#define DIO_CFG_C_MAJOR_VERSION 4
#define DIO_CFG_C_MINOR_VERSION 4
#define DIO_CFG_C_patch_VERSION 0
#define DIO_CFG_C_SW_MAJOR_VERSION 3
#define DIO_CFG_C_SW_MINOR_VERSION 0
#define DIO_CFG_C_SW_PATCH_VERSION 0
/*====================================FILE VERSION CHECKS=======================================*/
#if (DIO_CFG_C_VENDOR_ID != DIO_CFG_H_VENDOR_ID)
    #error " NON-MATCHED DATA : DIO_CFG_C_VENDOR_ID "
#endif
#if (DIO_CFG_C_MAJOR_VERSION != DIO_CFG_H_MAJOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_C_MAJOR_VERSION "
#endif
#if (DIO_CFG_C_MINOR_VERSION != DIO_CFG_H_MINOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_C_MINOR_VERSION "
#endif
#if (DIO_CFG_C_patch_VERSION != DIO_CFG_H_patch_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_C_patch_VERSION "
#endif
#if (DIO_CFG_C_SW_MAJOR_VERSION != DIO_CFG_H_SW_MAJOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_C_SW_MAJOR_VERSION "
#endif
#if (DIO_CFG_C_SW_MINOR_VERSION != DIO_CFG_H_SW_MINOR_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_C_SW_MINOR_VERSION "
#endif
#if (DIO_CFG_C_SW_PATCH_VERSION != DIO_CFG_H_SW_PATCH_VERSION)
    #error " NON-MATCHED DATA : DIO_CFG_C_SW_PATCH_VERSION "
#endif
/*=========================================CONSTANTS============================================*/


#define DIO_START_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
CONST(Dio_PortLevelType, DIO_CONST) Dio_ReadAvailablePins[DIO_NUM_PORTS_U16] =
{
    (Dio_PortLevelType)0xF8FF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFE,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFC,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFF8F,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x1E67,
    (Dio_PortLevelType)0xF080,
    (Dio_PortLevelType)0x0000,
    (Dio_PortLevelType)0x7FFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x2003,
    (Dio_PortLevelType)0xC000
};
#define DIO_STOP_SEC_CONFIG_DATA
#include "Dio_MemMap.h"


#define DIO_START_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
CONST(Dio_PortLevelType, DIO_CONST) Dio_WriteAvailablePins[DIO_NUM_PORTS_U16] =
{
    (Dio_PortLevelType)0xF8FF,
    (Dio_PortLevelType)0x00F0,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFEF,
    (Dio_PortLevelType)0xFFF8,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x8007,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x00FC,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x000F,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x0000,
    (Dio_PortLevelType)0x7080,
    (Dio_PortLevelType)0x0000,
    (Dio_PortLevelType)0x7FFF,
    (Dio_PortLevelType)0xFFFF,
    (Dio_PortLevelType)0x2000,
    (Dio_PortLevelType)0x0000
};
#define DIO_STOP_SEC_CONFIG_DATA
#include "Dio_MemMap.h"






#define DIO_START_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
static CONST(pu32Dio_PortToPartitionMap, DIO_CONST) u32PortToPartitionMap[DIO_NUM_PORTS_U16] =
{


    {
        .nDioPortId = 0,
        .coreid =  4

    },


    {
        .nDioPortId = 1,
        .coreid =  4

    },


    {
        .nDioPortId = 2,
        .coreid =  4

    },


    {
        .nDioPortId = 3,
        .coreid =  4

    },


    {
        .nDioPortId = 4,
        .coreid =  4

    },


    {
        .nDioPortId = 5,
        .coreid =  4

    },


    {
        .nDioPortId = 6,
        .coreid =  4

    },


    {
        .nDioPortId = 7,
        .coreid =  4

    },


    {
        .nDioPortId = 8,
        .coreid =  4

    },


    {
        .nDioPortId = 9,
        .coreid =  4

    },


    {
        .nDioPortId = 10,
        .coreid =  4

    },


    {
        .nDioPortId = 11,
        .coreid =  4

    },


    {
        .nDioPortId = 12,
        .coreid =  4

    },


    {
        .nDioPortId = 13,
        .coreid =  4

    },


    {
        .nDioPortId = 14,
        .coreid =  4

    },


    {
        .nDioPortId = 15,
        .coreid =  4

    },


    {
        .nDioPortId = 16,
        .coreid =  4

    },


    {
        .nDioPortId = 17,
        .coreid =  4

    },


    {
        .nDioPortId = 18,
        .coreid =  4

    },


    {
        .nDioPortId = 19,
        .coreid =  4

    },


};
#define DIO_STOP_SEC_CONFIG_DATA
#include "Dio_MemMap.h"

#define DIO_START_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
static CONST(pu32Dio_ChannelToPartitionMap, DIO_CONST) u32ChannelToPartitionMap[DIO_NUM_CHANNELS_U16] =
{
                                            
        {
            .nDioChannelId = 13,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 1,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 2,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 3,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 4,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 14,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 27,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 39,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 43,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 44,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 55,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 58,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 62,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 48,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 49,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 50,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 51,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 52,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 53,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 54,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 56,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 57,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 70,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 71,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 72,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 73,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 75,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 76,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 91,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 109,
            .coreid =  4
        },                                                        
        {
            .nDioChannelId = 139,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 140,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 147,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 148,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 149,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 150,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 151,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 152,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 153,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 145,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 146,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 154,
            .coreid =  4
        },                                                        
        {
            .nDioChannelId = 179,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 194,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 195,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 196,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 197,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 198,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 199,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 200,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 192,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 193,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 201,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 202,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 203,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 204,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 208,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 209,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 211,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 212,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 221,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 222,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 224,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 226,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 227,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 228,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 229,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 230,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 234,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 235,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 236,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 237,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 238,
            .coreid =  4
        },                                                        
        {
            .nDioChannelId = 258,
            .coreid =  4
        },                                                        
        {
            .nDioChannelId = 294,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 302,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 303,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 304,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 289,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 292,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 293,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 295,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 296,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 297,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 298,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 299,
            .coreid =  4
        },                                                
        {
            .nDioChannelId = 305,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 306,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 307,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 308,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 309,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 310,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 311,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 312,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 313,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 314,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 315,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 316,
            .coreid =  4
        },                                        
        {
            .nDioChannelId = 317,
            .coreid =  4
        },    
};
#define DIO_STOP_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
#define DIO_START_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
CONST(Dio_ConfigType, DIO_CONST) Dio_ConfigPC=
{
    .u8NumChannelGroups = (uint8)0x0,
    .pChannelGroupList = NULL_PTR,    
    .Dio_u32ChannelToPartitionMap = u32ChannelToPartitionMap,
    .Dio_u32PortToPartitionMap = u32PortToPartitionMap
};
#define DIO_STOP_SEC_CONFIG_DATA
#include "Dio_MemMap.h"
#ifdef __cplusplus
}
#endif
