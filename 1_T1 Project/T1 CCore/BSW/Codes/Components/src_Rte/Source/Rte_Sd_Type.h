/*
********************************************************************************
*
* File name: Rte_Sd_Type.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : SongQW/2023.03.24
* Change: New created.
* Cause: New
********************************************************************************
*/
#ifndef RTE_SD_TYPE_H_
#define RTE_SD_TYPE_H_

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
/* [SWS_SD_00118] This type defines the Server states that are reported to the SD
   using the expected API Sd_ServerServiceSetState. */
#ifndef Rte_TypeDef_Sd_ServerServiceSetStateType
#define Rte_TypeDef_Sd_ServerServiceSetStateType
typedef enum
{
    SD_SERVER_SERVICE_DOWN,
    SD_SERVER_SERVICE_AVAILABLE
} Sd_ServerServiceSetStateType;
#endif

/* [SWS_SD_00405] This type defines the Client states that are reported to the BswM
   using the expected API Sd_ClientServiceSetState. */
#ifndef Rte_TypeDef_ClientServiceSetStateType
#define Rte_TypeDef_ClientServiceSetStateType
typedef enum
{
    SD_CLIENT_SERVICE_RELEASED,
    SD_CLIENT_SERVICE_REQUESTED
} Sd_ClientServiceSetStateType;
#endif

/* [SWS_SD_00550] This type defines the subscription policy by consumed EventGroup for
   the Client Service.*/
#ifndef Rte_TypeDef_Sd_ConsumedEventGroupSetStateType
#define Rte_TypeDef_Sd_ConsumedEventGroupSetStateType
typedef enum
{
    SD_CONSUMED_EVENTGROUP_RELEASED,
    SD_CONSUMED_EVENTGROUP_REQUESTED
} Sd_ConsumedEventGroupSetStateType;
#endif

/* [SWS_SD_00007] The following CurrentStates shall be available for reporting to BswM module via BswM_Sd_ClientServiceCurrentState(),
                  BswM_Sd_ConsumedEventGroupCurrentState(), and BswM_Sd_EventHandlerCurrentState() respectively: */
/* [SWS_SD_00551] This type defines the modes to indicate the current mode request of a Client Service. */
#ifndef Rte_TypeDef_Sd_ClientServiceCurrentStateType
#define Rte_TypeDef_Sd_ClientServiceCurrentStateType
typedef enum
{
    SD_CLIENT_SERVICE_DOWN,
    SD_CLIENT_SERVICE_AVAILABLE
} Sd_ClientServiceCurrentStateType;
#endif

/* [SWS_SD_00552] This type defines the subscription policy by consumed EventGroup for
   the Client Service. */
#ifndef Rte_TypeDef_Sd_ConsumedEventGroupCurrentStateType
#define Rte_TypeDef_Sd_ConsumedEventGroupCurrentStateType
typedef enum
{
    SD_CONSUMED_EVENTGROUP_DOWN,
    SD_CONSUMED_EVENTGROUP_AVAILABLE
} Sd_ConsumedEventGroupCurrentStateType;
#endif

/* [SWS_SD_00553] This type defines the subscription policy by EventHandler for
   the Server Service. */
#ifndef Rte_TypeDef_Sd_EventHandlerCurrentStateType
#define Rte_TypeDef_Sd_EventHandlerCurrentStateType
typedef enum
{
    SD_EVENT_HANDLER_RELEASED,
    SD_EVENT_HANDLER_REQUESTED
} Sd_EventHandlerCurrentStateType;
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

#endif /* RTE_SD_TYPE_H_ */
