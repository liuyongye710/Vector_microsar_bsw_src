/*
********************************************************************************
*
* File name: CanSM_Cfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved. 
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangCong/2019.10.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: TianL/2024.8.5
* Change: Modify copyright.
* Cause: Update
********************************************************************************
*/
#ifndef CANSM_CFG_H_
#define CANSM_CFG_H_

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
#define CANSM_MANAGER_NW_NUM                   (4U)
#define CANSM_MODE_REQ_REPETITION_MAX          (0xFFU)
#define CANSM_MODE_REQ_REPETITION_TIME         (0U)
#define CANSM_DEV_ERROR_DETECT                 (STD_OFF)
#define CANSM_ICOM_SUPPORT                     (STD_OFF)
#define CANSM_MAINFUNC_PERIOD                  (5U)
#define CANSM_PNC_SUPPORT                      (STD_OFF)
#define CANSM_SET_BAUDRATE_API                 (STD_OFF)
#define CANSM_TXOFFLINE_ACT_SUPPORT            (STD_OFF)
#define CANSM_VERSION_INFO_API                 (STD_OFF)
#define CANSM_REPORT_DEM_ENABLE                (STD_OFF)

#define CANSM_CANTRCV_SUPPORT                  (STD_OFF)
#define CANSM_BORTXCFMPOLLING_SUPPORT          (STD_OFF)
#define CANSM_CANTRCV_PN_SUPPORT               (STD_OFF)
#define CANSM_PRENOCOM_SPCLHANDL_NOSLEEP       (STD_OFF)
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
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

#endif /* CANSM_CFG_H_ */

