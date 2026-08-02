/*
********************************************************************************
*
*  File name:   CanTrcv_Cfg.h
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangCong/2019.10.01
* Change: New
* Cause: New
********************************************************************************
*/
#ifndef CANTRCV_CFG_H_
#define CANTRCV_CFG_H_

/*
*******************************************************************************
*    Includes
*******************************************************************************
*/
#include "CanTrcv_Types.h"

/*
*******************************************************************************
*    Global Macros
*******************************************************************************
*/

#define CANTRCV_CHN_ALL_NUM                  (1U)

#define CANTRCV_DEV_ERROR_DETECT             (STD_OFF)

#define CANTRCV_GETVERSIONINFO_API           (STD_OFF)

#define CANTRCV_MAINFUNC_DIAG_PERIOD         (5U)

#define CANTRCV_MAINFUNC_PERIOD              (5U)


#define CANTRCV_INDEX                        (0U)
#define CANTRCV_TIMER_TYPE                   (CANTRCV_TIMERTYPE_NONE)
#define CANTRCV_WAIT_TIME                    (0U)
#define CANTRCV_ECUMWUEVENT_CFG              (STD_OFF)
#define CANTRCV_CANBUSERRFLAG_CFG            (STD_OFF)
#define CANTRCV_DEMEVENT_CFG                 (STD_OFF)
#define CANTRCV_HWPNSUPPORT_ENABLE           (STD_OFF)
#define CANTRCV_ICUCHN_CFG                   (STD_OFF)
#define CANTRCV_SPICOMM_RETRIES              (0U)
#define CANTRCV_SPICOMM_TIMEOUT              (0U)
#define CANTRCV_WAKEUP_SUPPORT               (CANTRCV_WAKEUP_BY_POLLING)

/*
*******************************************************************************
*    Global Types
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Variables
*******************************************************************************
*/
/*
*******************************************************************************
*    Global Constants
*******************************************************************************
*/
extern CONST(CanTrcv_ChannelType, CANTRCV_CONFIG_DATA) CanTrcv_ChannelInfo[CANTRCV_CHN_ALL_NUM + 1U];

/*
*******************************************************************************
*    Global Functions
*******************************************************************************
*/

#endif /* CANTRCV_CFG_H_ */




